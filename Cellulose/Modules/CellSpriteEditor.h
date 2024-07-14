#pragma once

#include "Locales\PlaybackControlsLocale.h"
#include "Locales\ToolTipLocale.h"

using namespace Microsoft::WRL;

static void __declspec(naked) DecoupleFontListCharColumnWidth()
{
	static void* returnAddr = (void*)0x41AD19;

	__asm
	{
		push edx
		push 2
		push 0x101B

		/* Set column width for
		   Picture ID and Crop ID */
		mov  ebp, 68

		jmp  [returnAddr]
	}
}

class CellSpriteEditor
{
public:
	inline static void SetupCommonDialog(IFileDialog* dlg, OPENFILENAMEA* arg)
	{
		const auto title = MakeWideString(arg->lpstrTitle);
		const auto fileName = MakeWideString(arg->lpstrFile);
		const auto defaultExt = MakeWideString(arg->lpstrDefExt);

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
				dlg->SetFolder(folder.Get());
		}

		dlg->SetFileName(fileName.c_str());
		dlg->SetDefaultExtension(defaultExt.c_str());
		dlg->SetFileTypes(filters.size(), filters.data());
		dlg->SetTitle(title.c_str());

		ComPtr<IFileDialogCustomize> customize;
		dlg->QueryInterface(IID_PPV_ARGS(&customize));

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
		dlg->Advise(handler, &handlerCookie);
	}

	INLINE_HOOK(BOOL, WINAPI, MyGetOpenFileNameA, PROC_ADDRESS("COMDLG32", "GetOpenFileNameA"), OPENFILENAMEA* arg)
	{
		ComPtr<IFileOpenDialog> ofn{};

		if (!SUCCEEDED(CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&ofn))))
			return FALSE;
		
		SetupCommonDialog(ofn.Get(), arg);

		if (!SUCCEEDED(ofn->Show(arg->hwndOwner)))
			return FALSE;

		ComPtr<IShellItem> result{};
		ofn->GetResult(&result);

		wchar_t* path{};
		wchar_t* fileTitle{};
		result->GetDisplayName(SIGDN_FILESYSPATH, &path);
		result->GetDisplayName(SIGDN_NORMALDISPLAY, &fileTitle);

		if (!path)
			return FALSE;

		WideCharToMultiByte(CP_ACP, 0, path, wcslen(path), arg->lpstrFile, arg->nMaxFile, nullptr, nullptr);
		WideCharToMultiByte(CP_ACP, 0, fileTitle, wcslen(fileTitle), arg->lpstrFileTitle, arg->nMaxFileTitle, nullptr, nullptr);
		const auto* fileName = PathFindFileNameA(arg->lpstrFile);
		const auto* extension = PathFindExtensionA(arg->lpstrFile);

		if (fileName != nullptr)
		{
			arg->nFileOffset = fileName - arg->lpstrFile;
		}

		if (extension != nullptr)
		{
			arg->nFileExtension = extension - arg->lpstrFile;
		}

		CoTaskMemFree(path);
		CoTaskMemFree(fileTitle);

		return TRUE;
	}

	INLINE_HOOK(BOOL, WINAPI, MyGetSaveFileNameA, PROC_ADDRESS("COMDLG32", "GetSaveFileNameA"), OPENFILENAMEA* arg)
	{
		ComPtr<IFileSaveDialog> sfn{};

		if (!SUCCEEDED(CoCreateInstance(CLSID_FileSaveDialog, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&sfn))))
			return FALSE;

		SetupCommonDialog(sfn.Get(), arg);

		if (!SUCCEEDED(sfn->Show(arg->hwndOwner)))
			return FALSE;

		ComPtr<IShellItem> result{};
		sfn->GetResult(&result);

		wchar_t* path{};
		wchar_t* fileTitle{};
		result->GetDisplayName(SIGDN_FILESYSPATH, &path);
		result->GetDisplayName(SIGDN_NORMALDISPLAY, &fileTitle);

		if (!path)
			return FALSE;

		sfn->GetFileTypeIndex((UINT*)&arg->nFilterIndex);
		WideCharToMultiByte(CP_ACP, 0, path, wcslen(path), arg->lpstrFile, arg->nMaxFile, nullptr, nullptr);
		WideCharToMultiByte(CP_ACP, 0, fileTitle, wcslen(fileTitle), arg->lpstrFileTitle, arg->nMaxFileTitle, nullptr, nullptr);

		const auto* fileName = PathFindFileNameA(arg->lpstrFile);
		const auto* extension = PathFindExtensionA(arg->lpstrFile);
		
		if (fileName != nullptr)
		{
			arg->nFileOffset = fileName - arg->lpstrFile;
		}

		if (extension != nullptr)
		{
			arg->nFileExtension = extension - arg->lpstrFile;
		}

		CoTaskMemFree(path);
		CoTaskMemFree(fileTitle);

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

	INLINE_HOOK(PIDLIST_ABSOLUTE, WINAPI, MySHBrowseForFolderA, PROC_ADDRESS("SHELL32", "SHBrowseForFolderA"), BROWSEINFOA* info)
	{
		ComPtr<IFileOpenDialog> ofn{};

		if (!SUCCEEDED(CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&ofn))))
			return nullptr;

		const auto title = MakeWideString(info->lpszTitle);

		if (info->pszDisplayName)
		{
			ComPtr<IShellItem> folder{};
			const auto initialDir = MakeWideString(info->pszDisplayName);
			SHCreateItemFromParsingName(initialDir.c_str(), nullptr, IID_PPV_ARGS(&folder));

			if (folder)
				ofn->SetFolder(folder.Get());
		}

		ofn->SetTitle(title.c_str());
		ofn->SetOptions(FOS_PICKFOLDERS);
		ofn->Show(info->hwndOwner);

		ComPtr<IShellItem> result{};
		ofn->GetResult(&result);

		if (!result)
		{
			return nullptr;
		}

		wchar_t* path{};
		result->GetDisplayName(SIGDN_FILESYSPATH, &path);

		LPITEMIDLIST pidl{};
		SHGetIDListFromObject(result.Get(), &pidl);

		return pidl;
	}

	inline static void __fastcall SetRecalculateCropSize(void* wnd, void* _, int id, BOOL state)
	{
		const auto hwnd = *reinterpret_cast<HWND*>(static_cast<char*>(wnd) + 0x20);

		FileDialogHandler::wnd_handlers.find(hwnd)->second->customize->SetControlState(id, state ? CDCS_ENABLEDVISIBLE : CDCS_VISIBLE);
	}

	INLINE_HOOK(int, __fastcall, CWinApp_InitApplicationHook, PROC_ADDRESS("MFC42", (LPCSTR)3922), void* app)
	{
		auto result = originalCWinApp_InitApplicationHook(app);

		TCHAR dir[MAX_PATH];
		ULONG_PTR ulpActivationCookie = FALSE;
		ACTCTX actCtx =
		{
			sizeof(actCtx),
			ACTCTX_FLAG_RESOURCE_NAME_VALID
				| ACTCTX_FLAG_SET_PROCESS_DEFAULT
				| ACTCTX_FLAG_ASSEMBLY_DIRECTORY_VALID,
			TEXT("shell32.dll"), 0, 0, dir, (LPCTSTR)124
		};

		UINT cch = GetSystemDirectory(dir, sizeof(dir) / sizeof(*dir));
		dir[cch] = TEXT('\0');
		ActivateActCtx(CreateActCtx(&actCtx), &ulpActivationCookie);

		return result;
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
		INSTALL_HOOK(MyGetSaveFileNameA);
		INSTALL_HOOK(MySHBrowseForFolderA);
		INSTALL_HOOK(MyCheckDlgButton);
		INSTALL_HOOK(MyIsDlgButtonChecked);

		INSTALL_HOOK(CWinApp_InitApplicationHook);
	}

	static void InstallLocales()
	{
		LocaleService::Localise(0x413EE5, "CellSpriteEditor_Menu_AnimationBank_None");
		LocaleService::Localise(0x413F4B, "CellSpriteEditor_Menu_AnimationBank_BankEntry");
		LocaleService::LocaliseRaw(0x46270C, "CellSpriteEditor_Menu_AnimationBank_ChangeBank");

		LocaleService::Localise(0x402D38, "CellSpriteEditor_Caption_Backstage_PriorityDisplay");
		LocaleService::Localise(0x4129C5, "CellSpriteEditor_Misc_Backstage_SceneInfo");
		LocaleService::Localise(0x4129F3, "CellSpriteEditor_Misc_Backstage_NoSceneInfo");
		LocaleService::Localise(0x413594, "CellSpriteEditor_Caption_Backstage_RenameScene");
		LocaleService::Localise(0x413599, "CellSpriteEditor_Message_Backstage_SceneRenameError");
		LocaleService::Localise(0x4135DE, "CellSpriteEditor_Caption_Backstage_RenameFolder");
		LocaleService::Localise(0x414850, "CellSpriteEditor_Caption_Backstage_CopyCastParameters");
		LocaleService::Localise(0x414855, "CellSpriteEditor_Message_Backstage_TwoOrMoreCastsSelected");
		LocaleService::Localise(0x414866, "CellSpriteEditor_Caption_Backstage_CopyCastParameters");
		LocaleService::Localise(0x414F27, "CellSpriteEditor_Caption_Backstage_Offset");
		LocaleService::Localise(0x41504E, "CellSpriteEditor_Caption_Backstage_DuplicateFolder");
		LocaleService::Localise(0x415053, "CellSpriteEditor_Message_Backstage_RootFolderDuplicateError");
		LocaleService::Localise(0x4154AD, "CellSpriteEditor_Message_Backstage_SelectCastInstantiate");
		LocaleService::Localise(0x4154D9, "CellSpriteEditor_Message_Backstage_CastInstantiateError");
		LocaleService::LocaliseRaw(0x46278C, "CellSpriteEditor_Message_Backstage_NoCastSelected");
		LocaleService::LocaliseRaw(0x4627E0, "CellSpriteEditor_Message_Backstage_NoCastsToPaste");
		LocaleService::LocaliseRaw(0x462800, "CellSpriteEditor_Caption_Backstage_PasteCastParameters");
		LocaleService::LocaliseRaw(0x462818, "CellSpriteEditor_Message_Backstage_SelectCast");
		LocaleService::LocaliseRaw(0x4628C8, "CellSpriteEditor_Caption_Backstage_CreateInstance");

		LocaleService::Localise(0x408879, "CellSpriteEditor_Caption_CastProperties_Caption");
		LocaleService::Localise(0x40899A, "CellSpriteEditor_Caption_CastProperties_Caption");
		LocaleService::Localise(0x4089EF, "CellSpriteEditor_Caption_CastProperties_PropertiesForCast");
		LocaleService::Localise(0x408A2D, "CellSpriteEditor_Caption_CastProperties_PropertiesForCasts");
		LocaleService::Localise(0x40A134, "CellSpriteEditor_Caption_CastProperties_PropertiesForCasts");

		LocaleService::Localise(0x408C75, "Common_Column_PictureID");
		LocaleService::Localise(0x408C8B, "Common_Column_CropID");
		LocaleService::Localise(0x4091B4, "CellSpriteEditor_Message_CropList_CropNotFound");
		LocaleService::Localise(0x40A0A7, "CellSpriteEditor_Caption_CropList_Caption");
		LocaleService::Localise(0x40A0F8, "CellSpriteEditor_Caption_CropList_CropsForCast");
		LocaleService::Localise(0x40A134, "CellSpriteEditor_Caption_CropList_Caption");

		LocaleService::Localise(0x41FFCE, "Common_Filter_SupportedImageFiles");
		LocaleService::Localise(0x436BDF, "Common_Filter_TGA");

		LocaleService::Localise(0x41ACD9, "CellSpriteEditor_Column_FontList_Code");
		LocaleService::Localise(0x41AD04, "CellSpriteEditor_Column_FontList_Char");
		LocaleService::Localise(0x41AD2E, "Common_Column_PictureID");
		LocaleService::Localise(0x41AD58, "Common_Column_CropID");
		LocaleService::Localise(0x41B48E, "CellSpriteEditor_Caption_FontList_EditText");
		LocaleService::Localise(0x41B493, "CellSpriteEditor_Message_FontList_UnsupportedChar");
		LocaleService::Localise(0x41BECA, "CellSpriteEditor_Column_FontList_FontName");
		LocaleService::Localise(0x41BEFC, "Common_Column_Type");
		LocaleService::Localise(0x41BFED, "CellSpriteEditor_Caption_FontList_CreateFont");
		LocaleService::Localise(0x41C557, "CellSpriteEditor_Caption_FontList_DeleteFont");
		LocaleService::Localise(0x41C53A, "CellSpriteEditor_Message_FontList_DeleteFont");
		LocaleService::LocaliseRaw(0x462BD8, "CellSpriteEditor_Caption_FontList_RenameFont");

		LocaleService::Localise(0x41DD6A, "CellSpriteEditor_Misc_NewProject_IncludeTextureListInProject");
		LocaleService::Localise(0x41DFAB, "CellSpriteEditor_Misc_NewProject_IncludeTextureListInProject");
		LocaleService::Localise(0x41E0D0, "CellSpriteEditor_Misc_NewProject_CreateTextureListInDir");
		LocaleService::Localise(0x41E1F0, "CellSpriteEditor_Misc_NewProject_UseExistingTextureList");
		LocaleService::Localise(0x41E2FD, "CellSpriteEditor_Message_NewProject_ChooseTextureListDir");
		LocaleService::Localise(0x41E5CE, "CellSpriteEditor_Caption_NewProject_ChooseTextureListFile");
		LocaleService::Localise(0x41EB4D, "CellSpriteEditor_Message_NewProject_ChooseProjectDir");
		LocaleService::Localise(0x41ED15, "CellSpriteEditor_Misc_NewProject_ProjectType");
		LocaleService::Localise(0x41EEAD, "CellSpriteEditor_Misc_NewProject_TextureListType");
		LocaleService::Localise(0x41EFB5, "CellSpriteEditor_Message_NewProject_OverwriteFile");

		LocaleService::Localise(0x41F646, "CellSpriteEditor_Column_PictureList_FileName");
		LocaleService::Localise(0x41F676, "Common_Column_Type");
		LocaleService::Localise(0x41F6A6, "CellSpriteEditor_Column_PictureList_Format");
		LocaleService::Localise(0x41F6D4, "CellSpriteEditor_Column_PictureList_Width");
		LocaleService::Localise(0x41F702, "CellSpriteEditor_Column_PictureList_Height");
		LocaleService::LocaliseRaw(0x4622EC, "CellSpriteEditor_Column_PictureList_Image");

		LocaleService::Localise(0x422127, "CellSpriteEditor_Misc_Picture_NoPictures");

		PlaybackControlsLocale::Install();

		LocaleService::Localise(0x40D679, "CellSpriteEditor_Caption_Timeline_CopyKey");
		LocaleService::Localise(0x40E847, "CellSpriteEditor_Misc_Timeline_Frame");
		LocaleService::Localise(0x40E84C, "CellSpriteEditor_Caption_Timeline_MoveToFrame");
		LocaleService::Localise(0x41AAEF, "CellSpriteEditor_Caption_Timeline_MoveToFrame");
		LocaleService::Localise(0x42E077, "CellSpriteEditor_Caption_Timeline_FunctionCurve");
		LocaleService::Localise(0x42E6C0, "CellSpriteEditor_Caption_Timeline_FunctionCurve");
		LocaleService::Localise(0x42E6F0, "CellSpriteEditor_Caption_Timeline_DopeSheet");
		LocaleService::Localise(0x40D770, "CellSpriteEditor_Message_Timeline_CopyKey");
		LocaleService::Localise(0x40DB34, "CellSpriteEditor_Message_Timeline_CopyKey");
		LocaleService::Localise(0x42EC3C, "CellSpriteEditor_Node_Timeline_SelectedCasts");
		LocaleService::Localise(0x42EBDD, "CellSpriteEditor_Node_Timeline_SelectedCastsLocked");
		LocaleService::Localise(0x42ED9C, "Transform (TRS)");
		LocaleService::Localise(0x42EDDE, "Common_Misc_TX");
		LocaleService::Localise(0x42EE20, "Common_Misc_TY");
		LocaleService::Localise(0x42EE62, "Common_Misc_RZ");
		LocaleService::Localise(0x42EEA4, "Common_Misc_SX");
		LocaleService::Localise(0x42EEE6, "Common_Misc_SY");
		LocaleService::Localise(0x42EF50, "CellSpriteEditor_Node_Timeline_VertexColour");
		LocaleService::Localise(0x42EF97, "Common_Misc_TopLeft");
		LocaleService::Localise(0x42EFDE, "Common_Misc_TopRight");
		LocaleService::Localise(0x42F025, "Common_Misc_BottomLeft");
		LocaleService::Localise(0x42F06C, "Common_Misc_BottomRight");
		LocaleService::Localise(0x42F0C7, "Common_Misc_Material");
		LocaleService::Localise(0x42F109, "Common_Misc_Hide");
		LocaleService::Localise(0x42F156, "Common_Misc_Pattern");
		LocaleService::Localise(0x42F19E, "Common_Misc_UserData");
		LocaleService::Localise(0x42F1E5, "Common_Misc_UserData1");
		LocaleService::Localise(0x42F22C, "Common_Misc_UserData2");
		LocaleService::Localise(0x42F273, "Common_Misc_UserData3");
		LocaleService::LocaliseRaw(0x4624C0, "CellSpriteEditor_Message_Timeline_SelectKey");
		LocaleService::LocaliseRaw(0x4624EC, "CellSpriteEditor_Message_Timeline_EmptyClipboard");
		LocaleService::LocaliseRaw(0x462514, "CellSpriteEditor_Message_Timeline_PlaceMarker");
		LocaleService::LocaliseRaw(0x46259C, "CellSpriteEditor_Caption_Timeline_PasteKey");
		LocaleService::LocaliseRaw(0x4625D0, "CellSpriteEditor_Misc_Timeline_Frame");

		ToolTipLocale::InstallCse();

		LocaleService::Localise(0x40181A, "CellSpriteEditor_Menu_Export");
		LocaleService::Localise(0x407E21, "Common_Misc_UserData1");
		LocaleService::Localise(0x407E81, "Common_Misc_UserData2");
		LocaleService::Localise(0x407EE1, "Common_Misc_UserData3");
		LocaleService::Localise(0x4343D0, "Common_Misc_MainTools");
		LocaleService::Localise(0x4343E0, "Common_Misc_ViewTools");
		LocaleService::Localise(0x4343EC, "Common_Misc_StageTools");
		LocaleService::Localise(0x4343F8, "Common_Misc_CropTools");
		LocaleService::Localise(0x434664, "Common_Misc_PlaybackControls");
		LocaleService::Localise(0x4346BF, "Common_Misc_KeyframeFilter");
		LocaleService::Localise(0x4368D0, "CellSpriteEditor_Caption_TextureListReference");
		LocaleService::Localise(0x4368F2, "CellSpriteEditor_Caption_TextureListExternal");
		LocaleService::Localise(0x4368FD, "CellSpriteEditor_Caption_TextureListInternal");
		LocaleService::Localise(0x436C25, "CellSpriteEditor_Caption_ExportStageToTexture");
		LocaleService::Localise(0x460BF8, "CellSpriteEditor_Misc_ProgramExited");
		LocaleService::LocaliseRaw(0x463414, "Common_Menu_PluginTools");

		// Backstage: don't display "(None/None)" for scenes without animation banks.
		WRITE_MEMORY(0x462690, uint8_t, 0);

		// Change column widths for Crop List.
		WRITE_MEMORY(0x408C5B, uint8_t, 32); // No.
		WRITE_MEMORY(0x408C71, uint8_t, 65); // Picture ID

		// Change column text alignment for Font List.
		WRITE_MEMORY(0x41AD22, int, 0); // Picture ID
		WRITE_MEMORY(0x41AD4C, int, 0); // Crop ID

		// Change column widths for Font List.
		WRITE_MEMORY(0x41BEF4, int, 52); // Type
		WRITE_MEMORY(0x41ACD1, int, 40); // Code
		WRITE_MEMORY(0x41ACEE, int, 40); // Char
		WRITE_JUMP(0x41AD11, &DecoupleFontListCharColumnWidth);

		// Change column text alignment for Picture List.
		WRITE_MEMORY(0x41F6C4, int, 0); // Width
		WRITE_MEMORY(0x41F6F2, int, 0); // Height

		// Change column widths for Picture List.
		WRITE_MEMORY(0x41F6CC, int, 48); // Width
		WRITE_MEMORY(0x41F6FA, int, 48); // Height

		// Change track copy message from Timeline to MB_ICONWARNING.
		WRITE_MEMORY(0x40D769, uint8_t, 0x34);
		WRITE_MEMORY(0x40DB2D, uint8_t, 0x34);
	}
};