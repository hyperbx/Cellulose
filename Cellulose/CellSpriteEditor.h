#pragma once

#include "Locales\AnimationBankLocale.h"
#include "Locales\BackstageLocale.h"
#include "Locales\CastPropertiesLocale.h"
#include "Locales\CropListLocale.h"
#include "Locales\FilterLocale.h"
#include "Locales\FontListLocale.h"
#include "Locales\NewProjectLocale.h"
#include "Locales\PictureListLocale.h"
#include "Locales\PictureLocale.h"
#include "Locales\PlaybackControlsLocale.h"
#include "Locales\TimelineLocale.h"
#include "Locales\ToolTipLocale.h"

class CellSpriteEditor
{
public:
	static void InstallLocales()
	{
		AnimationBankLocale::InstallCse();
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
		ToolTipLocale::InstallCse();

		// Menus.
		WRITE_MEMORY(0x40181A, const char*, "&Export");
		WRITE_MEMORY(0x463414, const char, "Plugin &Tools (&T)");

		// Captions.
		WRITE_MEMORY(0x4368D0, const char*, "Texture List: Reference (%s%s.ctf)");
		WRITE_MEMORY(0x4368F2, const char*, "Texture List: External (%s%s.ctf)");
		WRITE_MEMORY(0x4368FD, const char*, "Texture List: Internal");

		// Miscellaneous.
		WRITE_MEMORY(0x407E21, const char*, "User Data 1");
		WRITE_MEMORY(0x407E81, const char*, "User Data 2");
		WRITE_MEMORY(0x407EE1, const char*, "User Data 3");
		WRITE_MEMORY(0x4343D0, const char*, "Main Tools");
		WRITE_MEMORY(0x4343E0, const char*, "View Tools");
		WRITE_MEMORY(0x4343EC, const char*, "Stage Tools");
		WRITE_MEMORY(0x4343F8, const char*, "Crop Tools");
		WRITE_MEMORY(0x434664, const char*, "Playback Controls");
		WRITE_MEMORY(0x4346BF, const char*, "Keyframe Filter");
		WRITE_MEMORY(0x460BF8, const char*, "The program 'CellSpriteEditor.exe' has exited with code 0 (0x0).")
	}
};