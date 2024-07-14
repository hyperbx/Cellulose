#pragma once

class PlaybackControlsLocale
{
	inline static const char* m_strPlaybackControlsFilters[24] =
	{
		"Common_Misc_All",
		"------------------",
		"Common_Misc_TX",
		"Common_Misc_TY",
		"Common_Misc_TXY",
		"Common_Misc_RZ",
		"Common_Misc_SX",
		"Common_Misc_SY",
		"Common_Misc_SXY",
		"Common_Misc_TRS",
		"------------------",
		"Common_Misc_TopLeft",
		"Common_Misc_TopRight",
		"Common_Misc_BottomLeft",
		"Common_Misc_BottomRight",
		"Common_Misc_AllVertices",
		"------------------",
		"Common_Misc_Material",
		"Common_Misc_Hide",
		"Common_Misc_Pattern",
		"------------------",
		"Common_Misc_UserData1",
		"Common_Misc_UserData2",
		"Common_Misc_UserData3"
	};

public:
	static void Install()
	{
		for (int i = 0; i < 24; i++)
			WRITE_MEMORY(0x4524C4 + i * (sizeof(int) * 2), const char*, LocaleService::Localise(m_strPlaybackControlsFilters[i]));
	}
};