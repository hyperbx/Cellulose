#pragma once

class StageAccess
{
public:
	static void InstallLocales()
	{
		auto base = GetModuleBase("StageAccess");

		LocaleService::Localise(base + 0x1103, "StageAccess_PluginName");
		LocaleService::Localise(base + 0x12CE, "Common_Filter_TGA");
		LocaleService::Localise(base + 0x12F1, "StageAccess_Common_Caption");
		LocaleService::Localise(base + 0x1370, "StageAccess_Common_Caption");
		LocaleService::Localise(base + 0x1375, "Common_Message_SaveError");
	}
};