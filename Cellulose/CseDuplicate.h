#pragma once

class CseDuplicate
{
	inline static size_t pModuleBase;

public:
	static void InstallLocales()
	{
		pModuleBase = (size_t)GetModuleHandle("CseDuplicate");

		CHECK_MODULE(pModuleBase, "CseDuplicate.dll");

		// Miscellaneous.
		WRITE_MEMORY(pModuleBase + 0x5010, const char, "_Copy_(%d)\0");
		WRITE_MEMORY(pModuleBase + 0x5020, const char, "_Copy\0");
	}
};