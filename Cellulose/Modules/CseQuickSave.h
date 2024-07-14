#pragma once

class CseQuickSave
{
public:
	static void InstallLocales()
	{
		auto base = GetModuleBase("CseQuickSave");

		LocaleService::Localise(base + 0x19D4, "CseQuickSave_Caption_QuickSaveError");
		LocaleService::Localise(base + 0x19D9, "Common_Message_CreateDirectoryError");
		LocaleService::Localise(base + 0x2B59, "CseQuickSave_Misc_File");
		LocaleService::Localise(base + 0x2B87, "CseQuickSave_Misc_Date");
		LocaleService::Localise(base + 0x2BB5, "CseQuickSave_Misc_Time");
		LocaleService::Localise(base + 0x2BE3, "CseQuickSave_Misc_Remarks");
		LocaleService::Localise(base + 0x2F5E, "CseQuickSave_Caption_DeleteQuickSave");
		LocaleService::Localise(base + 0x33AE, "CseQuickSave_Caption_DeleteQuickSave");
		LocaleService::Localise(base + 0x33B3, "CseQuickSave_Message_DeleteQuickSave");
	}
};