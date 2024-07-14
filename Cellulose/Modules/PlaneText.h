#pragma once

class PlaneText
{
public:
	static void InstallLocales()
	{
		auto base = GetModuleBase("PlaneText");

		LocaleService::Localise(base + 0x2E4D, "Common_Caption_OutputDirectory");
		LocaleService::Localise(base + 0x3183, "PlaneText_PluginName");
	}
};