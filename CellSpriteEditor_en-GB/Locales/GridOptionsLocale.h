#pragma once

class GridOptionsLocale
{
public:
	static void InstallCseDialog(size_t in_base)
	{
		// Captions.
		WRITE_MEMORY(in_base + 0x64A6, const char*, "Invalid grid size");

		// Messages.
		WRITE_MEMORY(in_base + 0x64AB, const char*, "The grid size must be set to 1 or higher.");

		// Change "Invalid grid size" message to MB_ICONERROR.
		WRITE_MEMORY(in_base + 0x64A4, uint8_t, 0x10);
	}
};