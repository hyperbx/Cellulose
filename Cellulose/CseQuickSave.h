#pragma once

class CseQuickSave
{
	inline static size_t pModuleBase;

public:
	static void InstallLocales()
	{
		pModuleBase = (size_t)GetModuleHandle("CseQuickSave");

		CHECK_MODULE(pModuleBase, "CseQuickSave.dll");

		// Captions.
		WRITE_MEMORY(pModuleBase + 0x2F5E, const char*, "Delete Quick Save");
		WRITE_MEMORY(pModuleBase + 0x33AE, const char*, "Delete Quick Save");
		WRITE_MEMORY(pModuleBase + 0x19D4, const char*, "Quick Save Error");

		// Messages.
		WRITE_MEMORY(pModuleBase + 0x19D9, const char*, "Failed to create directory.");
		WRITE_MEMORY(pModuleBase + 0x33B3, const char*, "Are you sure you want to delete the selected save file?");

		// Miscellaneous.
		WRITE_MEMORY(pModuleBase + 0x2B59, const char*, "File");
		WRITE_MEMORY(pModuleBase + 0x2B87, const char*, "Date");
		WRITE_MEMORY(pModuleBase + 0x2BB5, const char*, "Time");
		WRITE_MEMORY(pModuleBase + 0x2BE3, const char*, "Remarks");
	}
};