#pragma once

class CropListLocale
{
public:
	static void InstallCse()
	{
		// Captions.
		WRITE_MEMORY(0x40A134, const char*, "Crop List");
		WRITE_MEMORY(0x40A0F8, const char*, "Crops for %s");
		WRITE_MEMORY(0x40A0A7, const char*, "Crop List");

		// Columns.
		WRITE_MEMORY(0x408C75, const char*, "Picture ID");
		WRITE_MEMORY(0x408C8B, const char*, "Crop ID");

		// Messages.
		WRITE_MEMORY(0x4091B4, const char*, "That crop is not in the project.");

		// Change column widths.
		WRITE_MEMORY(0x408C5B, uint8_t, 32); // No.
		WRITE_MEMORY(0x408C71, uint8_t, 65); // Picture ID
	}
};