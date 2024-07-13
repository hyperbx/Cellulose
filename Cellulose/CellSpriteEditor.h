#pragma once

#include <commdlg.h>
#include <wrl/client.h>
#include <ShlObj.h>
#include <vector>
#include <string>
#include "DialogHelpers.h"

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

using namespace Microsoft::WRL;

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

	INLINE_HOOK(BOOL, WINAPI, MyGetOpenFileNameA, PROC_ADDRESS("COMDLG32", "GetOpenFileNameA"), OPENFILENAMEA* arg)
	{
		ComPtr<IFileOpenDialog> ofn{};

		if (!SUCCEEDED(CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&ofn))))
			return FALSE;
		
		ComPtr<IExplorerBrowserEvents> explorerEvents{};
		ofn->QueryInterface(IID_PPV_ARGS(&explorerEvents));

		const auto title = MakeWideString(arg->lpstrTitle);
		const auto fileName = MakeWideString(arg->lpstrFile);
		std::vector<COMDLG_FILTERSPEC> filters{};
		std::vector<std::wstring> strings{};

		const auto* cFilter = arg->lpstrFilter;

		if (cFilter)
		{
			while (*cFilter)
			{
				const auto filterName = cFilter;
				const auto filterType = cFilter + strlen(filterName) + 1;

				strings.emplace_back(MakeWideString(filterName));
				strings.emplace_back(MakeWideString(filterType));

				filters.emplace_back(strings[strings.size() - 2].c_str(), strings[strings.size() - 1].c_str());

				cFilter = filterType + strlen(filterType) + 1;
			}
		}

		if (arg->lpstrInitialDir)
		{
			ComPtr<IShellItem> folder{};
			const auto initialDir = MakeWideString(arg->lpstrInitialDir);
			SHCreateItemFromParsingName(initialDir.c_str(), nullptr, IID_PPV_ARGS(&folder));

			if (folder)
				ofn->SetFolder(folder.Get());
		}

		ofn->SetFileName(fileName.c_str());
		ofn->SetFileTypes(filters.size(), filters.data());
		ofn->SetTitle(title.c_str());

		ComPtr<IFileDialogCustomize> customize;
		ofn->QueryInterface(IID_PPV_ARGS(&customize));

		if (arg->Flags & OFN_ENABLETEMPLATE)
		{
			const auto resource = FindResourceA(arg->hInstance, arg->lpTemplateName, MAKEINTRESOURCEA(RT_DIALOG));
			const auto dlgTemplate = static_cast<DLGTEMPLATE*>(LoadResource(arg->hInstance, resource));

			auto* current = reinterpret_cast<char*>(dlgTemplate + 1);
			const auto* menu = reinterpret_cast<wchar_t*>(current);

			current += (wcslen(menu) + 1) * sizeof(wchar_t);

			const auto* wndClass = reinterpret_cast<wchar_t*>(current);
			current += (wcslen(wndClass) + 1) * sizeof(wchar_t);

			const auto* wndTitle = reinterpret_cast<wchar_t*>(current);
			current += (wcslen(wndTitle) + 1) * sizeof(wchar_t);

			if (dlgTemplate->style & DS_SETFONT)
			{
				WORD fntSize = *reinterpret_cast<WORD*>(current);
				current += sizeof(WORD);

				const auto* fntName = reinterpret_cast<wchar_t*>(current);
				current += (wcslen(fntName) + 1) * sizeof(wchar_t);
			}

			for (size_t i = 0; i < dlgTemplate->cdit; i++)
			{
				auto* item = reinterpret_cast<DLGITEMTEMPLATE*>(current);

				current += sizeof(DLGITEMTEMPLATE);

				const auto itemCls = reinterpret_cast<wchar_t*>(current);
				current += (wcslen(itemCls) + 1) * sizeof(wchar_t);

				const auto itemTitle = reinterpret_cast<wchar_t*>(current);
				current += (wcslen(itemTitle) + 1) * sizeof(wchar_t);

				if (item->style & BS_CHECKBOX)
					customize->AddCheckButton(item->id, itemCls, FALSE);
			}
		}

		auto* handler = new FileDialogHandler();
		handler->customize = customize.Get();
		handler->data = arg->lCustData;
		handler->callback = arg->lpfnHook;
		handler->params = arg;

		DWORD handlerCookie;
		ofn->Advise(handler, &handlerCookie);

		if (!SUCCEEDED(ofn->Show(arg->hwndOwner)))
			return FALSE;

		ComPtr<IShellItem> result{};
		ofn->GetResult(&result);

		wchar_t* path{};
		result->GetDisplayName(SIGDN_FILESYSPATH, &path);

		if (!path)
			return FALSE;

		WideCharToMultiByte(CP_ACP, 0, path, wcslen(path), arg->lpstrFile, arg->nMaxFile, nullptr, nullptr);
		CoTaskMemFree(path);

		return TRUE;
	}

	INLINE_HOOK(BOOL, WINAPI, MyCheckDlgButton, PROC_ADDRESS("USER32", "CheckDlgButton"), HWND dlg, int id, UINT checked)
	{
		const auto handler = FileDialogHandler::wnd_handlers.find(dlg);

		if (handler != FileDialogHandler::wnd_handlers.end())
		{
			handler->second->customize->SetCheckButtonState(id, checked);
			return TRUE;
		}

		return originalMyCheckDlgButton(dlg, id, checked);
	}

	INLINE_HOOK(UINT, WINAPI, MyIsDlgButtonChecked, PROC_ADDRESS("USER32", "IsDlgButtonChecked"), HWND dlg, int id)
	{
		const auto handler = FileDialogHandler::wnd_handlers.find(dlg);

		if (handler != FileDialogHandler::wnd_handlers.end())
		{
			BOOL checked{};
			handler->second->customize->GetCheckButtonState(id, &checked);
			return checked;
		}

		return originalMyIsDlgButtonChecked(dlg, id);
	}

	inline static void __fastcall SetRecalculateCropSize(void* wnd, void* _, int id, BOOL state)
	{
		const auto hwnd = *reinterpret_cast<HWND*>(static_cast<char*>(wnd) + 0x20);

		FileDialogHandler::wnd_handlers.find(hwnd)->second->customize->SetControlState(id, state ? CDCS_ENABLEDVISIBLE : CDCS_VISIBLE);
	}

	static void Init()
	{
#if _DEBUG
		INIT_CONSOLE();
#endif
		// Disable license authentication.
		WRITE_MEMORY(0x439430, uint8_t, 0x31, 0xC0, 0xC3);

		WRITE_NOP(0x41F3DF, 7);
		WRITE_CALL(0x41F3DA, SetRecalculateCropSize);

		INSTALL_HOOK(MyGetOpenFileNameA);
		INSTALL_HOOK(MyCheckDlgButton);
		INSTALL_HOOK(MyIsDlgButtonChecked);
	}
};