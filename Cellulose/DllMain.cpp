#pragma comment(linker, "/EXPORT:Direct3DCreate8=C:\\Windows\\System32\\d3d8.Direct3DCreate8")

#include "CellSpriteEditor.h"
#include "CropPropertyEdit.h"
#include "CseConfig.h"
#include "CseCore.h"
#include "CseDialog.h"
#include "CseDuplicate.h"
#include "CseFile.h"
#include "CseOption.h"
#include "CseQuickSave.h"
#include "CseUndo.h"
#include "FileRender.h"
#include "PlaneText.h"
#include "StageAccess.h"

static void Init()
{
	CellSpriteEditor::Init();

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
			Configuration::Read();

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
