#pragma once

class CseDuplicate
{
public:
	static void InstallLocales()
	{
		auto base = GetModuleBase("CseDuplicate");

		LocaleService::LocaliseRaw(base + 0x5010, "CseDuplicate_Misc_CopyOrdinal");
		LocaleService::LocaliseRaw(base + 0x5020, "CseDuplicate_Misc_Copy");
	}
};