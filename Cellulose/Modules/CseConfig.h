#pragma once

class CseConfig
{
public:
	static void InstallLocales()
	{
		auto base = GetModuleBase("CseConfig");

		LocaleService::Localise(base + 0x10D9, "CseConfig_Caption_ProjectSetup");
		LocaleService::Localise(base + 0x181D, "Common_Caption_OutputDirectory");
		LocaleService::Localise(base + 0x21E1, "Common_Filter_SupportedImageFiles");
		LocaleService::Localise(base + 0x2563, "CseConfig_Caption_ChangingActualResolution");
		LocaleService::Localise(base + 0x6FFE, "CseConfig_Message_ChangingActualResolution");
	}
};