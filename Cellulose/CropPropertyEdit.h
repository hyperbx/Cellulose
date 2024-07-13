#pragma once

class CropPropertyEdit
{
	inline static size_t pModuleBase;

public:
	static void InstallLocales()
	{
		pModuleBase = (size_t)GetModuleHandle("CropPropertyEdit");

		CHECK_MODULE(pModuleBase, "CropPropertyEdit.dll");

		// Plugin name.
		WRITE_MEMORY(pModuleBase + 0x4030, const char*, "C&rop Properties... (&R)");
	}
};