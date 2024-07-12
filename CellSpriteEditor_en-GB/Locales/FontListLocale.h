#pragma once

class FontListLocale
{
public:
	static void InstallCse()
	{
		WRITE_MEMORY(0x41BFED, const char*, "Create Font");
		WRITE_MEMORY(0x462BD8, const char, "Rename Font\0");
		WRITE_MEMORY(0x41C557, const char*, "Delete Font");
		WRITE_MEMORY(0x41C53A, const char*, "Are you sure you want to delete \"%s\"? There are text casts currently using this font.");
		WRITE_MEMORY(0x41BECA, const char*, "Font name");
		WRITE_MEMORY(0x41BEFC, const char*, "Type");
		WRITE_MEMORY(0x41ACD9, const char*, "Code");
		WRITE_MEMORY(0x41AD04, const char*, "Char");
		WRITE_MEMORY(0x41AD2E, const char*, "Picture ID");
		WRITE_MEMORY(0x41AD58, const char*, "Crop ID");

		// Change column widths.
		WRITE_MEMORY(0x41ACD1, int, 64);
		WRITE_MEMORY(0x41ACEE, int, 64);
		WRITE_MEMORY(0x41AD22, int, 0);
		WRITE_MEMORY(0x41AD4C, int, 0);
	}

	static void InstallCseDialog(size_t in_base)
	{
		WRITE_MEMORY(in_base + 0x56EB, const char*, "Edit Text [%s]");
	}
};