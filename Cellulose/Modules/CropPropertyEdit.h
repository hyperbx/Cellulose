#pragma once

class CropPropertyEdit
{
	inline static size_t pModuleBase;

public:
	static void InstallLocales()
	{
		pModuleBase = (size_t)GetModuleHandle("CropPropertyEdit");

		CHECK_MODULE(pModuleBase, "CropPropertyEdit.dll");

		LocaleService::Localise(pModuleBase + 0x4030, "CropPropertyEdit_PluginName");
	}
};