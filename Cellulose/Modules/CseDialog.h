#pragma once

class CseDialog
{
public:
	static void InstallLocales()
	{
		auto base = GetModuleBase("CseDialog");

		LocaleService::Localise(base + 0x17E0, "Common_Column_Name");
		LocaleService::Localise(base + 0x2100, "CseDialog_Caption_AnimationBank_DeleteBank");
		LocaleService::Localise(base + 0x2105, "CseDialog_Message_AnimationBank_DeleteBank");
		LocaleService::Localise(base + 0x22B7, "CseDialog_Misc_AnimationBank_NewBank");
		LocaleService::Localise(base + 0x28F6, "CseDialog_Caption_AnimationBank_SetEndFrameAuto");
		LocaleService::Localise(base + 0x28FB, "CseDialog_Message_AnimationBank_SetEndFrameAuto");
		LocaleService::Localise(base + 0x56EB, "CseDialog_Caption_FontList_EditText");
		LocaleService::Localise(base + 0x68B7, "CseDialog_Caption_CastInstanceEditor_ChangeReferenceCast");
		LocaleService::Localise(base + 0x68BC, "CseDialog_Message_CastInstanceEditor_ChangeReferenceCast");
		LocaleService::Localise(base + 0x64A6, "CseDialog_Caption_GridOptions_InvalidGridSize");
		LocaleService::Localise(base + 0x64AB, "CseDialog_Message_GridOptions_InvalidGridSize");
		LocaleService::Localise(base + 0x6A15, "CseDialog_Misc_CastInstanceEditor_InvalidCastID");
		LocaleService::Localise(base + 0x6FE5, "CseDialog_Message_FontNameTooLong");
		LocaleService::Localise(base + 0x6FFE, "CseDialog_Message_SpecifyFontName");
		LocaleService::LocaliseRaw(base + 0xF10C, "CseDialog_Caption_AnimationBank_SetEndFrame");
		LocaleService::LocaliseRaw(base + 0xF124, "CseDialog_Field_AnimationBank_EndFrame");
		LocaleService::LocaliseRaw(base + 0xF13C, "CseDialog_Caption_OffsetOptions");

		// Change "Invalid Grid Size" message to MB_ICONERROR.
		WRITE_MEMORY(base + 0x64A4, uint8_t, 0x10);
	}
};