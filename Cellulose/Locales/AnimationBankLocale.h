#pragma once

class AnimationBankLocale
{
public:
	static void InstallCse()
	{
		// Menus.
		WRITE_MEMORY(0x413EE5, const char*, "None");
		WRITE_MEMORY(0x413F4B, const char*, "%d : %s");
		WRITE_MEMORY(0x46270C, const char, "Change Animation Bank (&S)");
	}

	static void InstallCseCore(size_t in_base)
	{
		// Captions.
		WRITE_MEMORY(in_base + 0x14C7, const char*, "Copy Animation");

		// Messages.
		WRITE_MEMORY(in_base + 0x14AA, const char*, "Failed to copy animation ID: %d");

		// Miscellaneous.
		WRITE_MEMORY(in_base + 0x101D8, const char*, "Copy of ");
		WRITE_MEMORY(in_base + 0x12BF0, const char*, "Generated Animation Bank");
	}

	static void InstallCseDialog(size_t in_base)
	{
		// Captions.
		WRITE_MEMORY(in_base + 0x2100, const char*, "Delete Animation Bank");
		WRITE_MEMORY(in_base + 0x28F6, const char*, "Set End Frame (Auto)");
		WRITE_MEMORY(in_base + 0xF10C, const char, "Set End Frame\0");

		// Messages.
		WRITE_MEMORY(in_base + 0x2105, const char*, "Are you sure you want to delete this animation bank?");
		WRITE_MEMORY(in_base + 0x28FB, const char*, "Do you want to automatically calculate the end frame for the selected animation bank?");

		// Columns.
		WRITE_MEMORY(in_base + 0x17E0, const char*, "Name");

		// Fields.
		WRITE_MEMORY(in_base + 0xF124, const char, "End frame\0");

		// Miscellaneous.
		WRITE_MEMORY(in_base + 0x22B7, const char*, "NewAnimationBank");
	}
};