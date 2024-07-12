#pragma once

class StageAccess
{
	inline static size_t pModuleBase;

	inline static const char* m_strCommonCaption = "Export Stage to Texture with Alpha...";

public:
	static void InstallLocales()
	{
		pModuleBase = (size_t)GetModuleHandle("StageAccess");

		CHECK_MODULE(pModuleBase, "StageAccess.dll");

		// Plugin name.
		WRITE_MEMORY(pModuleBase + 0x1103, const char*, "Export Stage to Texture with Al&pha...");

		// Filters.
		WRITE_MEMORY(pModuleBase + 0x12CE, const char*, "TGA (*.tga)|*.tga||");

		// Captions.
		WRITE_MEMORY(pModuleBase + 0x12F1, const char*, m_strCommonCaption);
		WRITE_MEMORY(pModuleBase + 0x1370, const char*, m_strCommonCaption);

		// Messages.
		WRITE_MEMORY(pModuleBase + 0x1375, const char*, "An error occurred during saving.");
	}
};