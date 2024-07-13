#pragma once

class CseUndo
{
	inline static size_t pModuleBase;

public:
	static void InstallLocales()
	{
		pModuleBase = (size_t)GetModuleHandle("CseUndo");

		CHECK_MODULE(pModuleBase, "CseUndo.dll");

		// Miscellaneous.
		WRITE_MEMORY(pModuleBase + 0x11BA, const char*, "Project Stack %05d");
	}
};