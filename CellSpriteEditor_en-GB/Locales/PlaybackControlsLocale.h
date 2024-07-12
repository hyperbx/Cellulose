#pragma once

class PlaybackControlsLocale
{
	inline static int m_strPlaybackControlsFilters[48] =
	{
		0xFFF,  (int)"All",
		0,      (int)"------------------",
		1,      (int)"X (TX)",
		2,      (int)"Y (TY)",
		3,      (int)"X/Y (TXY)",
		4,      (int)"Rotation (RZ)",
		8,      (int)"Scale X (SX)",
		0x10,   (int)"Scale Y (SY)",
		0x18,   (int)"Scale X/Y (SXY)",
		0x1F,   (int)"Transform (TRS)",
		0,      (int)"------------------",
		0x100,  (int)"Top Left",
		0x400,  (int)"Top Right",
		0x200,  (int)"Bottom Left",
		0x800,  (int)"Bottom Right",
		0xF00,  (int)"All Vertices",
		0,      (int)"------------------",
		0x40,   (int)"Material",
		0x80,   (int)"Hide",
		0x20,   (int)"Pattern",
		0,      (int)"------------------",
		0x1000, (int)"User Data 1",
		0x2000, (int)"User Data 2",
		0x4000, (int)"User Data 3"
	};

public:
	static void InstallCse()
	{
		for (int i = 0; i < 48; i++)
			WRITE_MEMORY(0x4524C0 + i * sizeof(int), int, m_strPlaybackControlsFilters[i]);
	}
};