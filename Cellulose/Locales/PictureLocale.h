#pragma once

class PictureLocale
{
public:
	static void InstallCse()
	{
		// Miscellaneous.
		WRITE_MEMORY(0x422127, const char*, "There are no pictures to display.");
	}
};