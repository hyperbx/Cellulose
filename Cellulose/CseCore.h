#pragma once

#include "Locales\AnimationBankLocale.h"

class CseCore
{
	inline static size_t pModuleBase;

public:
	static void InstallLocales()
	{
		pModuleBase = (size_t)GetModuleHandle("CseCore");

		CHECK_MODULE(pModuleBase, "CseCore.dll");

		AnimationBankLocale::InstallCseCore(pModuleBase);
	}
};