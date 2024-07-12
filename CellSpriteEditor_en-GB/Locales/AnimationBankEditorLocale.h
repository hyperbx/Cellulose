#pragma once

class AnimationBankEditorLocale
{
public:
	static void InstallCseDialog(size_t in_base)
	{
		WRITE_MEMORY(in_base + 0x2100, const char*, "Delete Animation Bank");
		WRITE_MEMORY(in_base + 0x2105, const char*, "Are you sure you want to delete this animation bank?");
		WRITE_MEMORY(in_base + 0x22B7, const char*, "NewAnimationBank");
		WRITE_MEMORY(in_base + 0x28F6, const char*, "Set End Frame (Auto)");
		WRITE_MEMORY(in_base + 0x28FB, const char*, "Do you want to automatically calculate the end frame for the selected animation bank?");
		WRITE_MEMORY(in_base + 0xF02C, const char, "Name\0");
		WRITE_MEMORY(in_base + 0xF10C, const char, "Set End Frame\0");
		WRITE_MEMORY(in_base + 0xF124, const char, "End frame\0");
	}
};