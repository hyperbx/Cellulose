#pragma once

class NewProjectLocale
{
	inline static const char* m_strIncludeTextureListInProject =
		"A texture list file will be created in the same directory as the project.\r\n"
		"The project file and the texture list file are always managed in synergy.\r\n"
		"If you save the project under a different name, the texture list will follow.";

	inline static const char* m_strCreateTextureListInFolder =
		"A texture list file will be created in the specified directory.\r\n"
		"If you save the project under a different name, the texture list will always\r\n"
		"be written to the specified location.";

	inline static const char* m_strUseExistingTextureLists =
		"Load and use an existing texture list file.\r\n"
		"The original texture list file will be updated after saving changes.\r\n"
		"If you save the project under a different name, the texture list will always\r\n"
		"be written to the specified location.";

public:
	static void InstallCse()
	{
		// Captions.
		WRITE_MEMORY(0x41E5CE, const char*, "Choose a texture list file...");

		// Messages.
		WRITE_MEMORY(0x41E2FD, const char*, "Choose a texture list directory...");
		WRITE_MEMORY(0x41EB4D, const char*, "Choose a project directory...");
		WRITE_MEMORY(0x41EFB5, const char*, "There is already a %s file at this location.\nDo you want to overwrite it?");

		// Miscellaneous.
		WRITE_MEMORY(0x41DD6A, const char*, m_strIncludeTextureListInProject);
		WRITE_MEMORY(0x41DFAB, const char*, m_strIncludeTextureListInProject);
		WRITE_MEMORY(0x41E0D0, const char*, m_strCreateTextureListInFolder);
		WRITE_MEMORY(0x41E1F0, const char*, m_strUseExistingTextureLists);
		WRITE_MEMORY(0x41EEAD, const char*, "texture list");
		WRITE_MEMORY(0x41ED15, const char*, "project");
	}
};