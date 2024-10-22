std::string GetModuleName(HINSTANCE in_hInstance)
{
    char buffer[MAX_PATH];

    if (!GetModuleFileNameA(in_hInstance, buffer, MAX_PATH))
        return "";

    return std::string(buffer);
}

HINSTANCE GetRedirectedModule(HINSTANCE in_hOrigInstance)
{
    auto work         = std::filesystem::current_path();
    auto modulePath   = std::filesystem::path(GetModuleName(in_hOrigInstance));
    auto relativePath = std::filesystem::relative(modulePath, work);
    auto resourceName = GetSubstringBeforeLastChar(relativePath.string(), '.') + ".res.dll";
    auto resourcePath = (work / "res" / Configuration::Language / resourceName).string();

    if (!FileExists(resourcePath))
        return in_hOrigInstance;

#if _DEBUG
    printf("Redirecting resource to %s...\n", resourceName.c_str());
#endif

    return LoadLibraryA(resourcePath.c_str());
}

HOOK(HRSRC, __stdcall, _FindResourceA, PROC_ADDRESS("KERNEL32", "FindResourceA"), HMODULE in_hModule, LPCSTR in_lpName, LPCSTR in_lpType)
{
    return original_FindResourceA(GetRedirectedModule(in_hModule), in_lpName, in_lpType);
}

HOOK(HGLOBAL, __stdcall, _LoadResource, PROC_ADDRESS("KERNEL32", "LoadResource"), HMODULE in_hModule, HRSRC in_hResInfo)
{
    return original_LoadResource(GetRedirectedModule(in_hModule), in_hResInfo);
}

HOOK(HMENU, __stdcall, _LoadMenuA, PROC_ADDRESS("USER32", "LoadMenuA"), HINSTANCE in_hInstance, LPCSTR in_lpMenuName)
{
    return original_LoadMenuA(GetRedirectedModule(in_hInstance), in_lpMenuName);
}

HOOK(int, __stdcall, _LoadStringA, PROC_ADDRESS("USER32", "LoadStringA"), HINSTANCE in_hInstance, UINT in_uID, LPSTR in_lpBuffer, int in_cchBufferMax)
{
    return original_LoadStringA(GetRedirectedModule(in_hInstance), in_uID, in_lpBuffer, in_cchBufferMax);
}

void ResourceRedirector::Install()
{
    INSTALL_HOOK(_FindResourceA);
    INSTALL_HOOK(_LoadResource);
    INSTALL_HOOK(_LoadMenuA);
    INSTALL_HOOK(_LoadStringA);
}