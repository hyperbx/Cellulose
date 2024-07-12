#pragma once

static void __declspec(naked) DecoupleCharColumnWidth()
{
	static void* returnAddr = (void*)0x41AD19;

	__asm
	{
		push edx
		push 2
		push 0x101B

		/* Set column width for
		   Picture ID and Crop ID */
		mov  ebp, 68

		jmp  [returnAddr]
	}
}

class FontListLocale
{
public:
	static void InstallCse()
	{
		// Columns.
		WRITE_MEMORY(0x41ACD9, const char*, "Code");
		WRITE_MEMORY(0x41AD04, const char*, "Char");
		WRITE_MEMORY(0x41AD2E, const char*, "Picture ID");
		WRITE_MEMORY(0x41AD58, const char*, "Crop ID");
		WRITE_MEMORY(0x41BECA, const char*, "Font name");
		WRITE_MEMORY(0x41BEFC, const char*, "Type");

		// Captions.
		WRITE_MEMORY(0x41B48E, const char*, "Edit Text");
		WRITE_MEMORY(0x41BFED, const char*, "Create Font");
		WRITE_MEMORY(0x41C557, const char*, "Delete Font");
		WRITE_MEMORY(0x462BD8, const char, "Rename Font\0");

		// Messages.
		WRITE_MEMORY(0x41B493, const char*, "The specified character is not supported.");
		WRITE_MEMORY(0x41C53A, const char*, "Are you sure you want to delete \"%s\"? There are text casts currently using this font.");

		// Change column text alignment.
		WRITE_MEMORY(0x41AD22, int, 0); // Picture ID
		WRITE_MEMORY(0x41AD4C, int, 0); // Crop ID

		// Change column widths.
		WRITE_MEMORY(0x41BEF4, int, 52); // Type
		WRITE_MEMORY(0x41ACD1, int, 40); // Code
		WRITE_MEMORY(0x41ACEE, int, 40); // Char
		WRITE_JUMP(0x41AD11, &DecoupleCharColumnWidth);
	}

	static void InstallCseDialog(size_t in_base)
	{
		// Captions.
		WRITE_MEMORY(in_base + 0x56EB, const char*, "Edit Text [%s]");
	}
};