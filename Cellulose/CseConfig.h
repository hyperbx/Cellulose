#pragma once

#include "Locales\FilterLocale.h"

class CseConfig
{
	inline static size_t pModuleBase;

public:
	static void InstallLocales()
	{
		pModuleBase = (size_t)GetModuleHandle("CseConfig");

		CHECK_MODULE(pModuleBase, "CseConfig.dll");

		FilterLocale::InstallCseConfig(pModuleBase);

		// Messages.
		WRITE_MEMORY(pModuleBase + 0x181D, const char*, "Choose an output directory...");
		WRITE_MEMORY(pModuleBase + 0x6FFE, const char*, "The co-ordinates of casts and their X and Y transforms will remain as they are, "
			"even after changing the actual device resolution. Are you sure you want to continue?");

		// Captions.
		WRITE_MEMORY(pModuleBase + 0x10D9, const char*, "Project Setup...");
		WRITE_MEMORY(pModuleBase + 0x2563, const char*, "Changing Actual Resolution");
	}
};