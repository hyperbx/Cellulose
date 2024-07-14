#pragma once

class CseOption
{
public:
	static void InstallLocales()
	{
		auto base = GetModuleBase("CseOption");

		LocaleService::Localise(base + 0x10E6, "CseOption_Caption_Options");
		LocaleService::Localise(base + 0x1875, "CseOption_Caption_ClearUndoHistory");
		LocaleService::Localise(base + 0x187B, "CseOption_Message_ClearUndoHistory");
	}
};