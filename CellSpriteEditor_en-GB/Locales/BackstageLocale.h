#pragma once

class BackstageLocale
{
public:
	static void InstallCse()
	{
		WRITE_MEMORY(0x402D38, const char*, "Backstage - Priority");
	}
};