// CDDVRMD_Filter.h  : Declaration of ActiveX Control wrapper class(es) created by Microsoft Visual C++

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CDDVRMD_Filter

class CDDVRMD_Filter : public CWnd
{
protected:
	DECLARE_DYNCREATE(CDDVRMD_Filter)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x23D5C5C, 0x2FFE, 0x4054, { 0x8C, 0xE9, 0x45, 0xC4, 0x92, 0x77, 0x8C, 0x52 } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID, 
						CCreateContext* pContext = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); 
	}

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, 
				UINT nID, CFile* pPersist = NULL, BOOL bStorage = FALSE,
				BSTR bstrLicKey = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); 
	}

// Attributes
public:

// Operations
public:

	void AboutBox()
	{
		InvokeHelper(DISPID_ABOUTBOX, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	long OpenFile(LPCTSTR bstrFile)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bstrFile);
		return result;
	}
	BOOL Login(LPCTSTR bstrUsername, LPCTSTR bstrPassword, LPCTSTR bstrIP, long lPort)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 ;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, bstrUsername, bstrPassword, bstrIP, lPort);
		return result;
	}
	void Logout()
	{
		InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	unsigned long SetRenderWindowSize(unsigned long lWidth, long lHeight)
	{
		unsigned long result;
		static BYTE parms[] = VTS_UI4 VTS_I4 ;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_UI4, (void*)&result, parms, lWidth, lHeight);
		return result;
	}
	unsigned long GetRenderWindowSize(long * lWidth, long * lHeight)
	{
		unsigned long result;
		static BYTE parms[] = VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_UI4, (void*)&result, parms, lWidth, lHeight);
		return result;
	}


};
