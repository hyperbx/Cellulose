#pragma comment(linker, "/EXPORT:Direct3DCreate8=C:\\Windows\\System32\\d3d8.Direct3DCreate8")

#include "Locales\CellSpriteEditor.h"
#include "Locales\CseDialog.h"
#include "Locales\CseFile.h"

static void Init()
{
	CellSpriteEditor::InstallLocales();
	CseDialog::InstallLocales();
	CseFile::InstallLocales();
}

BOOL WINAPI DllMain(_In_ HINSTANCE instance, _In_ DWORD reason, _In_ LPVOID reserved)
{
	switch (reason)
	{
		case DLL_PROCESS_ATTACH:
			Init();
			break;

		case DLL_PROCESS_DETACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
			break;
	}

	return TRUE;
}
