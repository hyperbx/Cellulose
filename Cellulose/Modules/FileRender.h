#pragma once

class FileRender
{
public:
	static void InstallLocales()
	{
		auto base = GetModuleBase("FileRender");

		LocaleService::Localise(base + 0x12A3, "FileRender_PluginName");
		LocaleService::Localise(base + 0x191B, "Common_Message_CreateDirectoryError");
		LocaleService::Localise(base + 0x1C55, "FileRender_Misc_Progress");
		LocaleService::Localise(base + 0x1D82, "FileRender_Caption_Common");
		LocaleService::Localise(base + 0x1D87, "Common_Message_SaveError");
		LocaleService::Localise(base + 0x1DA1, "FileRender_Caption_Common");
		LocaleService::Localise(base + 0x1DA6, "FileRender_Message_StageCaptureError");
		LocaleService::LocaliseRaw(base + 0x415C, "Common_Caption_OutputDirectory");
	}
};