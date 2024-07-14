#pragma once

class CseUndo
{
public:
	static void InstallLocales()
	{
		auto base = GetModuleBase("CseUndo");

		LocaleService::Localise(base + 0x11BA, "CseUndo_Misc_ProjectStack");
	}
};