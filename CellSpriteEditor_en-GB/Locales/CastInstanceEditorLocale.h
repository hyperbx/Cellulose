#pragma once

class CastInstanceEditorLocale
{
public:
	static void InstallCseDialog(size_t in_base)
	{
		WRITE_MEMORY(in_base + 0x6A15, const char*, "(invalid cast ID)");
		WRITE_MEMORY(in_base + 0x68B7, const char*, "Change reference cast");
		WRITE_MEMORY(in_base + 0x68BC, const char*, "You cannot reference an instance cast.");
	}
};