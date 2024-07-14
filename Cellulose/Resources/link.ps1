param
(
    [String]$Configuration = "Release",
    [String]$Language = "en-GB"
)

$vs = ./vswhere.exe -nologo -latest -prerelease -property installationPath
$vsCommonTools = [System.IO.Path]::Combine($vs, "Common7\Tools")

# Get Visual Studio environment variables.
pushd $vsCommonTools
    cmd /c "VsDevCmd.bat&set" |
    foreach {
        if ($_ -match "=") {
            $v = $_.split("=", 2); set-item -force -path "ENV:\$($v[0])"  -value "$($v[1])" 
        }
    }
popd

$dummyObj  = "..\obj\Win32\${Configuration}\rsrc.obj"

# Copy internal string definitions to output resource path.
Copy-Item -Path ".\${Language}\Internal.json" -Destination "..\bin\Win32\${Configuration}\res\${Language}\Internal.json" -Force

# Create dummy object for resource DLLs.
Invoke-Expression "cl /c rsrc.c /Fo""${dummyObj}"""

foreach ($res in [System.IO.Directory]::EnumerateFiles([System.IO.Path]::Combine($pwd, $Language), "*.res", 1))
{
    $relativePath = Resolve-Path -Path $res -Relative
    $relativePath = $relativePath -Replace '^\.\\', ''

    if ($relativePath -like "${Language}\*")
    {
        $relativePath = $relativePath.Substring($Language.Length, $relativePath.Length - $Language.Length)
    }

    $outputPath = "..\bin\Win32\${Configuration}\res\${Language}\${relativePath}.dll"
    $outputDir  = [System.IO.Path]::GetDirectoryName($outputPath)

    if (!(Test-Path $outputDir -PathType Container))
    {
        New-Item -ItemType Directory -Path $outputDir
    }

    & link /DLL /NOENTRY /OUT:"${outputPath}" "${dummyObj}" "${res}"

    echo "Created resource module: ${outputPath}"
    echo ""
}