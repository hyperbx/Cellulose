#pragma once
#include <combaseapi.h>
#include <map>

class FileDialogHandler;

using namespace Microsoft::WRL;
template<typename T>
class TUnknown : public IUnknown
{
public:
	LONG RefCount{ 0 };

	HRESULT STDMETHODCALLTYPE QueryInterface(const IID& riid, void** ppvObject) override
	{
		if (riid == __uuidof(IUnknown))
		{
			AddRef();
			*ppvObject = this;
			return S_OK;
		}
		return E_NOINTERFACE;
	}

	ULONG STDMETHODCALLTYPE AddRef() override
	{
		InterlockedIncrement(&RefCount);
		return RefCount;
	}

	ULONG STDMETHODCALLTYPE Release() override
	{
		InterlockedDecrement(&RefCount);

		if (RefCount <= 0)
		{
			delete static_cast<T*>(this);
		}

		return RefCount;
	}
};

class FileDialogHandler : public TUnknown<FileDialogHandler>, public IFileDialogEvents, public IFileDialogControlEvents
{
public:
	inline static std::map<HWND, FileDialogHandler*> wnd_handlers{};

	LPOFNHOOKPROC callback{};
	LPARAM data{};
	IFileDialogCustomize* customize{};
	HWND wnd{};
	bool init{};
	OPENFILENAMEA* params{};

	~FileDialogHandler()
	{
		wnd_handlers.erase(wnd);
	}

	HRESULT STDMETHODCALLTYPE QueryInterface(const IID& riid, void** ppvObject) override
	{
		if (riid == IID_IFileDialogEvents)
		{
			TUnknown::AddRef();
			*ppvObject = static_cast<IFileDialogEvents*>(this);
			return S_OK;
		}
		else if (riid == IID_IFileDialogControlEvents)
		{
			TUnknown::AddRef();
			*ppvObject = static_cast<IFileDialogControlEvents*>(this);
			return S_OK;
		}

		return TUnknown::QueryInterface(riid, ppvObject);
	}

	ULONG STDMETHODCALLTYPE AddRef() override { return TUnknown::AddRef(); }
	ULONG STDMETHODCALLTYPE Release() override { return TUnknown::Release(); }

	HRESULT STDMETHODCALLTYPE OnFileOk(IFileDialog* pfd) override
	{
		if (callback)
		{
			const auto msg = RegisterWindowMessageA(FILEOKSTRING);
			callback(wnd, msg, 0, (LPARAM)params);

			FUNCTION_PTR(void*, WINAPI, CWnd_FromHandlePermanent, PROC_ADDRESS("MFC42", (LPCSTR)2867), HWND);
			FUNCTION_PTR(BOOL, __fastcall, PictureReplacePicker_ExecRecalculateCommand, 0x0041F3A0, void*);
			auto* window = CWnd_FromHandlePermanent(wnd);

			// i give up
			if (window && *(void**)window == (void*)0x00451300) // compare vtable with replace file picker
			{
				PictureReplacePicker_ExecRecalculateCommand(window);
			}
		}
		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE OnFolderChange(IFileDialog* pfd) override
	{
		if (!init)
		{
			init = true;
			ComPtr<IOleWindow> window{};
			pfd->QueryInterface(IID_PPV_ARGS(&window));
			
			window->GetWindow(&wnd);

			wnd_handlers.emplace(wnd, this);
			if (callback)
			{
				callback(wnd, WM_INITDIALOG, FALSE, data);
			}
		}
		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE OnFolderChanging(IFileDialog* pfd, IShellItem* psiFolder) override { return E_NOTIMPL; }
	HRESULT STDMETHODCALLTYPE OnOverwrite(IFileDialog* pfd, IShellItem* psi, FDE_OVERWRITE_RESPONSE* pResponse) override { return E_NOTIMPL; }
	HRESULT STDMETHODCALLTYPE OnSelectionChange(IFileDialog* pfd) override { return E_NOTIMPL; }
	HRESULT STDMETHODCALLTYPE OnShareViolation(IFileDialog* pfd, IShellItem* psi, FDE_SHAREVIOLATION_RESPONSE* pResponse) override { return E_NOTIMPL; }
	HRESULT STDMETHODCALLTYPE OnTypeChange(IFileDialog* pfd) override { return E_NOTIMPL; }

	HRESULT STDMETHODCALLTYPE OnButtonClicked(IFileDialogCustomize* pfdc, DWORD dwIDCtl) override { return E_NOTIMPL; }
	HRESULT STDMETHODCALLTYPE OnCheckButtonToggled(IFileDialogCustomize* pfdc, DWORD dwIDCtl, BOOL bChecked) override
	{
		if (callback)
		{
			ComPtr<IOleWindow> window{};
			pfdc->QueryInterface(IID_PPV_ARGS(&window));
			
			auto wparam = bChecked | (dwIDCtl << 16);
			callback(wnd, WM_COMMAND, wparam, 0);
			return S_OK;
		}
		return E_NOTIMPL;
	}

	HRESULT STDMETHODCALLTYPE OnControlActivating(IFileDialogCustomize* pfdc, DWORD dwIDCtl) override { return E_NOTIMPL; }
	HRESULT STDMETHODCALLTYPE OnItemSelected(IFileDialogCustomize* pfdc, DWORD dwIDCtl, DWORD dwIDItem) override { return E_NOTIMPL; }
};