#pragma once

class CastPropertiesLocale
{
public:
	static void InstallCse()
	{
		// Captions.
		WRITE_MEMORY(0x408879, const char*, "Cast Properties");
		WRITE_MEMORY(0x40899A, const char*, "Cast Properties");
		WRITE_MEMORY(0x4089EF, const char*, "Properties for %s");
		WRITE_MEMORY(0x408A2D, const char*, "Properties for multiple casts");
		WRITE_MEMORY(0x40A134, const char*, "Properties for multiple casts");
	}
};