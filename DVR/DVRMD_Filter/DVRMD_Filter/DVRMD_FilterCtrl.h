#pragma once

// DVRMD_FilterCtrl.h : Declaration of the CDVRMD_FilterCtrl ActiveX Control class.

#include "PlayerDlg.h"
// CDVRMD_FilterCtrl : See DVRMD_FilterCtrl.cpp for implementation.

class CDVRMD_FilterCtrl : public COleControl
{
	DECLARE_DYNCREATE(CDVRMD_FilterCtrl)

// Constructor
public:
	CDVRMD_FilterCtrl();

// Overrides
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// Implementation
protected:
	~CDVRMD_FilterCtrl();

	DECLARE_OLECREATE_EX(CDVRMD_FilterCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CDVRMD_FilterCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CDVRMD_FilterCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CDVRMD_FilterCtrl)		// Type name and misc status

// Message maps
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
		dispidFaster = 17L,
		dispidSetCapturePath = 16L,
		dispidGetCapturePath = 15L,
		dispidCapPic = 14L,
		dispidStop = 13L,
		dispidPause = 12L,
		dispidPlay = 11L,
		dispidSetWndChannel = 10L,
		dispidStopMonitor = 9L,
		dispidStartMonitor = 8L,
		dispidSetMediaServer = 7L,
		dispidGetMediaServer = 6L,
		dispidGetRenderWindowSize = 5L,
		dispidSetRenderWindowSize = 4L,
		dispidLogout = 3L,
		dispidLogin = 2L,
		dispidOpenFile = 1L,
		IDD = IDD_PLAYER_DIALOG
	};
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

private:
	CPlayerDlg	m_MainDialog;
	CDVRPlayer*	GetDVRPlayer()
	{
		return m_MainDialog.GetPlayer();
	}
	CDVRSettings& GetDVRSettings()
	{
		return GetDVRPlayer()->GetDVRSettings();
	}
public:
	
	afx_msg void OnDestroy();
protected:
	VARIANT_BOOL Login(LPCTSTR bstrUsername, LPCTSTR bstrPassword, LPCTSTR bstrIP, LONG lPort);
	void Logout(void);
	ULONG SetRenderWindowSize(ULONG lWidth, LONG lHeight);
	ULONG GetRenderWindowSize(LONG* lWidth, LONG* lHeight);
	ULONG GetMediaServer(BSTR* bstrMediaServerIP, LONG* lPort);
	ULONG SetMediaServer(LPCTSTR bstrMediaServerIP, LONG lPort);
	ULONG StartMonitor(LONG lWndNum);
	ULONG StopMonitor(void);
	ULONG SetWndChannel(LONG lWndIndex, LONG lChannelIndex);

	LONG OpenFile(LPCTSTR bstrFile);
	LONG Play(void);
	ULONG Pause(void);
	ULONG Stop(void);

	BSTR CapPic(void);
	BSTR GetCapturePath(void);
	void SetCapturePath(LPCTSTR bstrPath);
public:
	afx_msg void OnMove(int x, int y);
protected:
	ULONG Faster(void);
};

