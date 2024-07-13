#pragma once

class CseOption
{
	inline static size_t pModuleBase;

public:
	static void InstallLocales()
	{
		pModuleBase = (size_t)GetModuleHandle("CseOption");

		CHECK_MODULE(pModuleBase, "CseOption.dll");

		// Captions.
		WRITE_MEMORY(pModuleBase + 0x10E6, const char*, "CellSpriteEditor Options");
		WRITE_MEMORY(pModuleBase + 0x1875, const char*, "Clear Undo History");

		// Messages.
		WRITE_MEMORY(pModuleBase + 0x187B, const char*, "Are you sure you want to clear undo history?");
	}
};