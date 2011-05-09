// SonicIMVPlayerProp.h : Declaration of the CSonicIMVPlayerProp


#pragma once
#include "resource.h"       // main symbols
#include "SonicIMVPlayer.h"

// CSonicIMVPlayerProp

class ATL_NO_VTABLE CSonicIMVPlayerProp :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSonicIMVPlayerProp, &CLSID_SonicIMVPlayerProp>,
	public IPropertyPageImpl<CSonicIMVPlayerProp>,
	public CDialogImpl<CSonicIMVPlayerProp>
{
public:
	CSonicIMVPlayerProp()
	{
		m_dwTitleID = IDS_TITLESONICIMVPLAYERPROP;
		m_dwHelpFileID = IDS_HELPFILESONICIMVPLAYERPROP;
		m_dwDocStringID = IDS_DOCSTRINGSONICIMVPLAYERPROP;
	}

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

	enum {IDD = IDD_SONICIMVPLAYERPROP};

DECLARE_REGISTRY_RESOURCEID(IDR_SONICIMVPLAYERPROP)


BEGIN_COM_MAP(CSonicIMVPlayerProp)
	COM_INTERFACE_ENTRY(IPropertyPage)
END_COM_MAP()

BEGIN_MSG_MAP(CSonicIMVPlayerProp)
	COMMAND_HANDLER(IDC_BUTTON_BROWSE, BN_CLICKED, OnBnClickedButtonBrowse)
	COMMAND_HANDLER(IDC_EDIT_URL, EN_CHANGE, OnEnChangeEditUrl)
	CHAIN_MSG_MAP(IPropertyPageImpl<CSonicIMVPlayerProp>)
END_MSG_MAP()

// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	STDMETHOD(Apply)(void)
	{
		ATLTRACE(_T("CSonicIMVPlayerProp::Apply\n"));
		if(!m_bDirty)
			return S_FALSE;

		for (UINT i = 0; i < m_nObjects; i++)
		{
			CComQIPtr<ISonicIMVPlayer, &IID_ISonicIMVPlayer> pIMVPlayerCtrl(m_ppUnk[i]);
			CComBSTR bstrURL;
			GetDlgItemText(IDC_EDIT_URL,(BSTR&)bstrURL);
			if FAILED(pIMVPlayerCtrl->put_URL(bstrURL))
			{
				CComPtr<IErrorInfo> pError;
				CComBSTR strError;
				GetErrorInfo(0, &pError);
				pError->GetDescription(&strError);
				MessageBoxW(strError, _T("Open Moive Error"), MB_ICONEXCLAMATION);
				return E_FAIL;
			}
		}
		m_bDirty = FALSE;
		return S_OK;
	}
LRESULT OnBnClickedButtonBrowse(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
LRESULT OnEnChangeEditUrl(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
};


OBJECT_ENTRY_AUTO(__uuidof(SonicIMVPlayerProp), CSonicIMVPlayerProp)
