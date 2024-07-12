#pragma once

class TimelineLocale
{
public:
	static void InstallCse()
	{
		WRITE_MEMORY(0x42E077, const char*, "Timeline - Function Curve");
		WRITE_MEMORY(0x42E6C0, const char*, "Timeline - Function Curve");
		WRITE_MEMORY(0x42E6F0, const char*, "Timeline - Dope Sheet");
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
	}
};