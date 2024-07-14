#pragma once

class CseFile
{
public:
	static void InstallLocales()
	{
		auto base = GetModuleBase("CseFile");

		LocaleService::Localise(base + 0x131E, "CseFile_Message_TextureListNotFound");
		LocaleService::Localise(base + 0x1332, "CseFile_Message_InvalidTextureList");
		LocaleService::Localise(base + 0x1346, "CseFile_Message_InvalidTextureListVersion");
		LocaleService::Localise(base + 0x135A, "CseFile_Message_TextureListLoadError");
		LocaleService::Localise(base + 0x1647, "CseFile_Message_PictureAlreadyLoaded");
		LocaleService::Localise(base + 0x3925, "CseFile_Message_ProjectNotFound");
		LocaleService::Localise(base + 0x3936, "CseFile_Message_InvalidProject");
		LocaleService::Localise(base + 0x3947, "CseFile_Message_InvalidProjectVersion");
		LocaleService::Localise(base + 0x3958, "CseFile_Message_ProjectLoadError");
		LocaleService::Localise(base + 0x9AC7, "CseFile_Message_FontLoadError");
		LocaleService::Localise(base + 0x2CF6, "CseFile_Caption_OpenProject");
		LocaleService::Localise(base + 0x3078, "CseFile_Caption_SaveAs");
		LocaleService::Localise(base + 0x9AE0, "CseFile_Caption_LoadFont");
	}
};