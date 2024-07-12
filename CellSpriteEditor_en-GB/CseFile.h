#pragma once

class CseFile
{
	inline static size_t pModuleBase;

public:
	static void InstallLocales()
	{
		pModuleBase = (size_t)GetModuleHandle("CseFile");

		CHECK_MODULE(pModuleBase, "CseFile.dll");

		// Messages.
		WRITE_MEMORY(pModuleBase + 0x131E, const char*, "Texture list file not found.");
		WRITE_MEMORY(pModuleBase + 0x1332, const char*, "This is not a texture list file.");
		WRITE_MEMORY(pModuleBase + 0x1346, const char*, "The texture list file version is different.");
		WRITE_MEMORY(pModuleBase + 0x135A, const char*, "An error occurred whilst loading the texture list file.");
		WRITE_MEMORY(pModuleBase + 0x1647, const char*, "The picture \"%s\" is already in the project and will not be loaded.");
		WRITE_MEMORY(pModuleBase + 0x3925, const char*, "Project file not found.");
		WRITE_MEMORY(pModuleBase + 0x3936, const char*, "This is not a project file.");
		WRITE_MEMORY(pModuleBase + 0x3947, const char*, "The project file version is different.");
		WRITE_MEMORY(pModuleBase + 0x3958, const char*, "An error occurred whilst loading the project file.");
		WRITE_MEMORY(pModuleBase + 0x9AC7, const char*, "Failed to load font: %s");

		// Captions.
		WRITE_MEMORY(pModuleBase + 0x2CF6, const char*, "Open Project...");
		WRITE_MEMORY(pModuleBase + 0x3078, const char*, "Save As...");
		WRITE_MEMORY(pModuleBase + 0x9AE0, const char*, "Load Font...");
	}
};