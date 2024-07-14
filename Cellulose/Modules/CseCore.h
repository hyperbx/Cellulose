#pragma once

class CseCore
{
public:
	static void InstallLocales()
	{
		auto base = GetModuleBase("CseCore");

		LocaleService::Localise(base + 0x14AA, "CseCore_Message_AnimationBank_CopyAnimation");
		LocaleService::Localise(base + 0x14C7, "CseCore_Caption_AnimationBank_CopyAnimation");
		LocaleService::Localise(base + 0x101D8, "CseCore_Misc_AnimationBank_Copy");
		LocaleService::Localise(base + 0x12BF0, "CseCore_Misc_AnimationBank_GeneratedBank");
	}
};