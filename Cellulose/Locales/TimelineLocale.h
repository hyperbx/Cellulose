#pragma once

class TimelineLocale
{
	inline static const char* m_strCopyToTrackOfDifferentPropertyWarning =
		"Copying keys to tracks of different cast properties may have unexpected results. Do you want to continue?";

public:
	static void InstallCse()
	{
		// Captions.
		WRITE_MEMORY(0x40D679, const char*, "Copy Key");
		WRITE_MEMORY(0x40E84C, const char*, "Move to Specific Frame...");
		WRITE_MEMORY(0x41AAEF, const char*, "Move to Specific Frame...");
		WRITE_MEMORY(0x42E077, const char*, "Timeline - Function Curve");
		WRITE_MEMORY(0x42E6C0, const char*, "Timeline - Function Curve");
		WRITE_MEMORY(0x42E6F0, const char*, "Timeline - Dope Sheet");
		WRITE_MEMORY(0x46259C, const char, "Paste Key\0");

		// Messages.
		WRITE_MEMORY(0x40D770, const char*, m_strCopyToTrackOfDifferentPropertyWarning);
		WRITE_MEMORY(0x40DB34, const char*, m_strCopyToTrackOfDifferentPropertyWarning);
		WRITE_MEMORY(0x4624C0, const char, "Please select a key.\0");
		WRITE_MEMORY(0x4624EC, const char, "There is no data on the clipboard.\0");
		WRITE_MEMORY(0x462514, const char, "Please place a marker.\0");

		// Change track copy message to MB_ICONWARNING.
		WRITE_MEMORY(0x40D769, uint8_t, 0x34);
		WRITE_MEMORY(0x40DB2D, uint8_t, 0x34);

		// Nodes.
		WRITE_MEMORY(0x42EC3C, const char*, "Selected Casts");
		WRITE_MEMORY(0x42ED9C, const char*, "Transform (TRS)");
		WRITE_MEMORY(0x42EDDE, const char*, "X (TX)");
		WRITE_MEMORY(0x42EE20, const char*, "Y (TY)");
		WRITE_MEMORY(0x42EE62, const char*, "Rotation (RZ)");
		WRITE_MEMORY(0x42EEA4, const char*, "Scale X (SX)");
		WRITE_MEMORY(0x42EEE6, const char*, "Scale Y (SY)");
		WRITE_MEMORY(0x42EF50, const char*, "Vertex Colour (VC)");
		WRITE_MEMORY(0x42EF97, const char*, "Top Left");
		WRITE_MEMORY(0x42EFDE, const char*, "Top Right");
		WRITE_MEMORY(0x42F025, const char*, "Bottom Left");
		WRITE_MEMORY(0x42F06C, const char*, "Bottom Right");
		WRITE_MEMORY(0x42F0C7, const char*, "Material");
		WRITE_MEMORY(0x42F109, const char*, "Hide");
		WRITE_MEMORY(0x42F156, const char*, "Pattern");
		WRITE_MEMORY(0x42F19E, const char*, "User Data");
		WRITE_MEMORY(0x42F1E5, const char*, "User 1");
		WRITE_MEMORY(0x42F22C, const char*, "User 2");
		WRITE_MEMORY(0x42F273, const char*, "User 3");

		// Miscellaneous.
		WRITE_MEMORY(0x40E847, const char*, "Frame");
		WRITE_MEMORY(0x4625D0, const char, "Frame\0");
	}
};