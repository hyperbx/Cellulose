#pragma once

class BackstageLocale
{
public:
	static void InstallCse()
	{
		// Captions.
		WRITE_MEMORY(0x402D38, const char*, "Backstage - Priority Display");
		WRITE_MEMORY(0x4135DE, const char*, "Rename Folder");
		WRITE_MEMORY(0x413594, const char*, "Rename Scene");
		WRITE_MEMORY(0x414850, const char*, "Copy Cast Parameters");
		WRITE_MEMORY(0x414866, const char*, "Copy Cast Parameters");
		WRITE_MEMORY(0x414F27, const char*, "Offset");
		WRITE_MEMORY(0x41504E, const char*, "Duplicate Folder");
		WRITE_MEMORY(0x462800, const char, "Paste Cast Parameters\0");
		WRITE_MEMORY(0x4628C8, const char, "Create Instance\0");

		// Messages.
		WRITE_MEMORY(0x413599, const char*, "Unable to change scene to the specified name.");
		WRITE_MEMORY(0x414855, const char*, "Two or more casts are selected.");
		WRITE_MEMORY(0x415053, const char*, "Unable to duplicate the root folder.");
		WRITE_MEMORY(0x4154AD, const char*, "Please select a cast to instantiate.");
		WRITE_MEMORY(0x4154D9, const char*, "Unable to create an instance of cast: %s");
		WRITE_MEMORY(0x46278C, const char, "No cast selected.\0");
		WRITE_MEMORY(0x4627E0, const char, "There are no casts to paste.\0");
		WRITE_MEMORY(0x462818, const char, "Please select a cast.\0");

		// Miscellaneous.
		WRITE_MEMORY(0x4129C5, const char*, " [%s] [%d/%d] [End: %d]");
		WRITE_MEMORY(0x4129F3, const char*, " [None]");
		WRITE_MEMORY(0x462690, uint8_t, 0);
	}
};