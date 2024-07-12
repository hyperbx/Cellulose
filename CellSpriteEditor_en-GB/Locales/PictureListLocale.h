#pragma once

class PictureListLocale
{
public:
	static void InstallCse()
	{
		WRITE_MEMORY(0x4622EC, const char, "Image\0");
		WRITE_MEMORY(0x41F646, const char*, "File name");
		WRITE_MEMORY(0x41F676, const char*, "Type");
		WRITE_MEMORY(0x41F6A6, const char*, "Format");
		WRITE_MEMORY(0x41F6D4, const char*, "Width");
		WRITE_MEMORY(0x41F702, const char*, "Height");

		// Change column widths.
		WRITE_MEMORY(0x41F6C4, int, 0);
		WRITE_MEMORY(0x41F6CC, int, 48);
		WRITE_MEMORY(0x41F6F2, int, 0);
		WRITE_MEMORY(0x41F6FA, int, 48);
	}
};