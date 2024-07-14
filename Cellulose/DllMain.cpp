#pragma comment(linker, "/EXPORT:Direct3DCreate8=C:\\Windows\\System32\\d3d8.Direct3DCreate8")

#include "Modules\CellSpriteEditor.h"
#include "Modules\CropPropertyEdit.h"
#include "Modules\CseConfig.h"
#include "Modules\CseCore.h"
#include "Modules\CseDialog.h"
#include "Modules\CseDuplicate.h"
#include "Modules\CseFile.h"
#include "Modules\CseOption.h"
#include "Modules\CseQuickSave.h"
#include "Modules\CseUndo.h"
#include "Modules\FileRender.h"
#include "Modules\PlaneText.h"
#include "Modules\StageAccess.h"

static void Init()
{
	Configuration::Read();

	CellSpriteEditor::Init();

	if (Configuration::IsJapanese())
		return;

	LocaleService::Read(std::format("res\\{}\\Internal.json", Configuration::Language));

	CellSpriteEditor::InstallLocales();
	CseConfig::InstallLocales();
	CseCore::InstallLocales();
	CseDialog::InstallLocales();
	CseDuplicate::InstallLocales();
	CseFile::InstallLocales();
	CseOption::InstallLocales();
	CseQuickSave::InstallLocales();
	CseUndo::InstallLocales();

	ResourceRedirector::Install();
}

static void OnPluginLoad(const char* in_pFileName)
{
	if (Configuration::IsJapanese())
		return;

	if (!strcmp(in_pFileName, "CropPropertyEdit.dll"))
		CropPropertyEdit::InstallLocales();

	if (!strcmp(in_pFileName, "FileRender.dll"))
		FileRender::InstallLocales();

	if (!strcmp(in_pFileName, "PlaneText.dll"))
		PlaneText::InstallLocales();

	if (!strcmp(in_pFileName, "StageAccess.dll"))
		StageAccess::InstallLocales();
}

HOOK(int, __fastcall, LoadPlugin, 0x427EF0, void* in_pThis, void* _, const char* in_pFileName, int in_a3)
{
	LoadLibraryA(in_pFileName);
	OnPluginLoad(in_pFileName);

	return originalLoadPlugin(in_pThis, _, in_pFileName, in_a3);
}

BOOL WINAPI DllMain(HINSTANCE in_hInstance, DWORD in_fdwReason, LPVOID in_lpvReserved)
{
	switch (in_fdwReason)
	{
		case DLL_PROCESS_ATTACH:
		{
			Init();

			INSTALL_HOOK(LoadPlugin);

			break;
		}

		case DLL_PROCESS_DETACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
			break;
	}

	return TRUE;
}
