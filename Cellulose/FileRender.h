#pragma once

class FileRender
{
	inline static size_t pModuleBase;

	inline static const char* m_strCommonCaption = "Export Stage to Image Sequence...";

public:
	static void InstallLocales()
	{
		pModuleBase = (size_t)GetModuleHandle("FileRender");

		CHECK_MODULE(pModuleBase, "FileRender.dll");

		// Plugin name.
		WRITE_MEMORY(pModuleBase + 0x12A3, const char*, "&Export Stage to Image Sequence...");

		// Captions.
		WRITE_MEMORY(pModuleBase + 0x1D82, const char*, m_strCommonCaption);
		WRITE_MEMORY(pModuleBase + 0x1DA1, const char*, m_strCommonCaption);
		WRITE_MEMORY(pModuleBase + 0x415C, const char, "Choose an output directory...\0");

		// Messages.
		WRITE_MEMORY(pModuleBase + 0x191B, const char*, "Failed to create output directory.");
		WRITE_MEMORY(pModuleBase + 0x1D87, const char*, "An error occurred whilst saving.");
		WRITE_MEMORY(pModuleBase + 0x1DA6, const char*, "Failed to capture stage surface.");

		// Miscellaneous.
		WRITE_MEMORY(pModuleBase + 0x1C55, const char*, "Exporting (%d/%d)... [%s]");
	}
};