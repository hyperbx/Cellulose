#pragma once

#include "Locales\NewProjectLocale.h"
#include "Locales\PictureLocale.h"
#include "Locales\PictureListLocale.h"
#include "Locales\CropListLocale.h"
#include "Locales\BackstageLocale.h"
#include "Locales\CastPropertiesLocale.h"
#include "Locales\TimelineLocale.h"
#include "Locales\FontListLocale.h"
#include "Locales\PlaybackControlsLocale.h"
#include "Locales\FilterLocale.h"

class CellSpriteEditor
{
public:
	static void InstallLocales()
	{
		BackstageLocale::InstallCse();
		CastPropertiesLocale::InstallCse();
		CropListLocale::InstallCse();
		FilterLocale::InstallCse();
		FontListLocale::InstallCse();
		NewProjectLocale::InstallCse();
		PictureListLocale::InstallCse();
		PictureLocale::InstallCse();
		PlaybackControlsLocale::InstallCse();
		TimelineLocale::InstallCse();

		// Window captions.
		WRITE_MEMORY(0x4368D0, const char*, "Texture List: Reference (%s%s.ctf)");
		WRITE_MEMORY(0x4368F2, const char*, "Texture List: External (%s%s.ctf)");
		WRITE_MEMORY(0x4368FD, const char*, "Texture List: Internal");

		// Miscellaneous.
		WRITE_MEMORY(0x462818, const char, "No cast is selected.\0");
		WRITE_MEMORY(0x4343D0, const char*, "Main Tools");
		WRITE_MEMORY(0x4343E0, const char*, "View Tools");
		WRITE_MEMORY(0x4343EC, const char*, "Stage Tools");
		WRITE_MEMORY(0x4343F8, const char*, "Crop Tools");
		WRITE_MEMORY(0x434664, const char*, "Playback Controls");
		WRITE_MEMORY(0x4346BF, const char*, "Keyframe Filter");
	}
};