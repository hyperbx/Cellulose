#pragma once

class PlaneText
{
	inline static size_t pModuleBase;

public:
	static void InstallLocales()
	{
		pModuleBase = (size_t)GetModuleHandle("PlaneText");

		CHECK_MODULE(pModuleBase, "PlaneText.dll");

		// Plugin name.
		WRITE_MEMORY(pModuleBase + 0x3183, const char*, "Plain &Text...");

		// Messages.
		WRITE_MEMORY(pModuleBase + 0x2E4D, const char*, "Choose an output directory...");
	}
};