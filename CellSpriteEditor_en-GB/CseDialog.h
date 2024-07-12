#pragma once

#include "Locales\AnimationBankEditorLocale.h"
#include "Locales\CastInstanceEditorLocale.h"
#include "Locales\FontListLocale.h"
#include "Locales\GridOptionsLocale.h"

class CseDialog
{
	inline static size_t pModuleBase;

public:
	static void InstallLocales()
	{
		pModuleBase = (size_t)GetModuleHandle("CseDialog");

		CHECK_MODULE(pModuleBase, "CseDialog.dll");

		AnimationBankEditorLocale::InstallCseDialog(pModuleBase);
		CastInstanceEditorLocale::InstallCseDialog(pModuleBase);
		FontListLocale::InstallCseDialog(pModuleBase);
		GridOptionsLocale::InstallCseDialog(pModuleBase);

		// Messages.
		WRITE_MEMORY(pModuleBase + 0x6FFE, const char*, "Please specify a font name.");
		WRITE_MEMORY(pModuleBase + 0x6FE5, const char*, "The font name is too long (32 character limit).");

		// Window captions.
		WRITE_MEMORY(pModuleBase + 0xF13C, const char, "Offset Options\0");
	}
};