// DVRMD_FilterCtrl.cpp : Implementation of the CDVRMD_FilterCtrl ActiveX Control class.

#include "stdafx.h"
#include "DVRMD_Filter.h"
#include "DVRMD_FilterCtrl.h"
#include "DVRMD_FilterPropPage.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CDVRMD_FilterCtrl, COleControl)



// Message map

BEGIN_MESSAGE_MAP(CDVRMD_FilterCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_WM_CREATE()
	
	ON_WM_DESTROY()
END_MESSAGE_MAP()



// Dispatch map

BEGIN_DISPATCH_MAP(CDVRMD_FilterCtrl, COleControl)
	DISP_FUNCTION_ID(CDVRMD_FilterCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CDVRMD_FilterCtrl, "OpenFile", dispidOpenFile, OpenFile, VT_I4, VTS_BSTR)
	DISP_STOCKFUNC_DOCLICK()
	DISP_FUNCTION_ID(CDVRMD_FilterCtrl, "Login", dispidLogin, Login, VT_BOOL, VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4)
	DISP_FUNCTION_ID(CDVRMD_FilterCtrl, "Logout", dispidLogout, Logout, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CDVRMD_FilterCtrl, "IsChannelEnable", dispidIsChannelEnable, IsChannelEnable, VT_BOOL, VTS_UI4)
	DISP_FUNCTION_ID(CDVRMD_FilterCtrl, "EnableChannel", dispidEnableChannel, EnableChannel, VT_UI4, VTS_UI4 VTS_BOOL)
	DISP_FUNCTION_ID(CDVRMD_FilterCtrl, "SetRenderWindowSize", dispidSetRenderWindowSize, SetRenderWindowSize, VT_UI4, VTS_UI4 VTS_I4)
	DISP_FUNCTION_ID(CDVRMD_FilterCtrl, "GetRenderWindowSize", dispidGetRenderWindowSize, GetRenderWindowSize, VT_UI4, VTS_PI4 VTS_PI4)
	DISP_FUNCTION_ID(CDVRMD_FilterCtrl, "GetMediaServer", dispidGetMediaServer, GetMediaServer, VT_UI4, VTS_PBSTR VTS_PI4)
	DISP_FUNCTION_ID(CDVRMD_FilterCtrl, "SetMediaServer", dispidSetMediaServer, SetMediaServer, VT_UI4, VTS_BSTR)
	DISP_FUNCTION_ID(CDVRMD_FilterCtrl, "StartMonitor", dispidStartMonitor, StartMonitor, VT_UI4, VTS_NONE)
	DISP_FUNCTION_ID(CDVRMD_FilterCtrl, "StopMonitor", dispidStopMonitor, StopMonitor, VT_UI4, VTS_NONE)
END_DISPATCH_MAP()



// Event map

BEGIN_EVENT_MAP(CDVRMD_FilterCtrl, COleControl)
	EVENT_STOCK_DBLCLICK()
END_EVENT_MAP()



// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CDVRMD_FilterCtrl, 1)
	PROPPAGEID(CDVRMD_FilterPropPage::guid)
END_PROPPAGEIDS(CDVRMD_FilterCtrl)



// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CDVRMD_FilterCtrl, "DVRMD_FILTER.DVRMD_FilterCtrl.1",
	0x23d5c5c, 0x2ffe, 0x4054, 0x8c, 0xe9, 0x45, 0xc4, 0x92, 0x77, 0x8c, 0x52)



// Type library ID and version

IMPLEMENT_OLETYPELIB(CDVRMD_FilterCtrl, _tlid, _wVerMajor, _wVerMinor)



// Interface IDs

const IID BASED_CODE IID_DDVRMD_Filter =
		{ 0xEC35B6AB, 0x684F, 0x4FE3, { 0x8E, 0xAD, 0x4A, 0xAA, 0xBE, 0x2, 0x4E, 0xA2 } };
const IID BASED_CODE IID_DDVRMD_FilterEvents =
		{ 0x67DC81BA, 0xE0EC, 0x4122, { 0xAD, 0x13, 0xDE, 0xF7, 0x2A, 0x4B, 0xEC, 0x27 } };



// Control type information

static const DWORD BASED_CODE _dwDVRMD_FilterOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CDVRMD_FilterCtrl, IDS_DVRMD_FILTER, _dwDVRMD_FilterOleMisc)



// CDVRMD_FilterCtrl::CDVRMD_FilterCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CDVRMD_FilterCtrl

BOOL CDVRMD_FilterCtrl::CDVRMD_FilterCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_DVRMD_FILTER,
			IDB_DVRMD_FILTER,
			afxRegApartmentThreading,
			_dwDVRMD_FilterOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}



// CDVRMD_FilterCtrl::CDVRMD_FilterCtrl - Constructor

CDVRMD_FilterCtrl::CDVRMD_FilterCtrl()
{
	InitializeIIDs(&IID_DDVRMD_Filter, &IID_DDVRMD_FilterEvents);
	// TODO: Initialize your control's instance data here.
}



// CDVRMD_FilterCtrl::~CDVRMD_FilterCtrl - Destructor

CDVRMD_FilterCtrl::~CDVRMD_FilterCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


// CDVRMD_FilterCtrl::DoPropExchange - Persistence support

void CDVRMD_FilterCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.
}



// CDVRMD_FilterCtrl::OnResetState - Reset control to default state

void CDVRMD_FilterCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}



// CDVRMD_FilterCtrl::AboutBox - Display an "About" box to the user

void CDVRMD_FilterCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_DVRMD_FILTER);
	dlgAbout.DoModal();
}



// CDVRMD_FilterCtrl message handlers

int CDVRMD_FilterCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_MainDialog.Create(IDD_PLAYER_DIALOG, this);
	m_MainDialog.ShowWindow(SW_SHOW);

	return 0;
}


// CDVRMD_FilterCtrl::OnDraw - Drawing function

void CDVRMD_FilterCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	/*if (!pdc)
		return;*/

	// TODO: Replace the following code with your own drawing code.
	//pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	//pdc->Ellipse(rcBounds);

	if (::IsWindow(m_MainDialog.m_hWnd) && !m_MainDialog.IsFullScreen())
	{
		m_MainDialog.MoveWindow(rcBounds, TRUE);
	}
}


void CDVRMD_FilterCtrl::OnDestroy()
{
	COleControl::OnDestroy();

	if (::IsWindow(m_MainDialog.m_hWnd))
	{
		m_MainDialog.DestroyWindow();
	}
}

LONG CDVRMD_FilterCtrl::OpenFile(LPCTSTR bstrFile)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	
	m_MainDialog.OpenFile(bstrFile);
	return 0;
}


VARIANT_BOOL CDVRMD_FilterCtrl::Login(LPCTSTR bstrUsername, LPCTSTR bstrPassword, LPCTSTR bstrIP, LONG lPort)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	BOOL bRet = GetDVRPlayer()->Login(bstrUsername, bstrPassword, bstrIP, lPort);

	return bRet ? VARIANT_TRUE: VARIANT_FALSE;
}


void CDVRMD_FilterCtrl::Logout(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	GetDVRPlayer()->Logout();
}


VARIANT_BOOL CDVRMD_FilterCtrl::IsChannelEnable(ULONG lChannel)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	std::map<int, bool>::iterator it = GetDVRSettings().m_mapEnableChannel.find(lChannel);
	if (it != GetDVRSettings().m_mapEnableChannel.end())
	{
		return it->second ? VARIANT_TRUE : VARIANT_FALSE;
	}

	return VARIANT_FALSE;
}


ULONG CDVRMD_FilterCtrl::EnableChannel(ULONG lChannel, VARIANT_BOOL bEnable)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	GetDVRSettings().m_mapEnableChannel[lChannel] = (bEnable == VARIANT_TRUE);

	return 0;
}


ULONG CDVRMD_FilterCtrl::SetRenderWindowSize(ULONG lWidth, LONG lHeight)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	GetDVRSettings().m_nRenderWidth = lWidth;
	GetDVRSettings().m_nRenderHeight = lHeight;

	if (IsWindow(m_MainDialog.m_hWnd))
	{
		m_MainDialog.InitWindowSize();
	}

	return 0;
}


ULONG CDVRMD_FilterCtrl::GetRenderWindowSize(LONG* lWidth, LONG* lHeight)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	*lWidth = GetDVRSettings().m_nRenderWidth;

	*lHeight = GetDVRSettings().m_nRenderHeight;

	return 0;
}

ULONG CDVRMD_FilterCtrl::GetMediaServer(BSTR* bstrMediaServerIP, LONG* lPort)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	* bstrMediaServerIP = GetDVRSettings().m_csMediaServerIP.AllocSysString();
	* lPort = GetDVRSettings().m_lPort;

	return 0;
}


ULONG CDVRMD_FilterCtrl::SetMediaServer(LPCTSTR bstrMediaServerIP, LONG lPort)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	GetDVRSettings().m_csMediaServerIP = bstrMediaServerIP;
	GetDVRSettings().m_lPort = lPort;

	return 0;
}


ULONG CDVRMD_FilterCtrl::StartMonitor(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	return 0;
}


ULONG CDVRMD_FilterCtrl::StopMonitor(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	return 0;
}
