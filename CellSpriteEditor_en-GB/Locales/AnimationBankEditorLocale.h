#pragma once

class AnimationBankEditorLocale
{
public:
	static void InstallCseDialog(size_t in_base)
	{
		WRITE_MEMORY(in_base + 0xF10C, const char, "Set End Frame\0");
		WRITE_MEMORY(in_base + 0xF124, const char, "End frame\0");
	}
};