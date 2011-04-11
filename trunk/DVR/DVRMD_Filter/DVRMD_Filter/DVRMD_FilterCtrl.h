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
		dispidEnableChannel = 13L,
		dispidIsChannelEnable = 12L,
		dispidHighPictureQuality = 11,
		dispidCapturePicPath = 10,
		dispidCapturePicType = 9,
		dispidRenderWndNum = 8,
		dispidLogout = 7L,
		dispidLogin = 6L,
		dispidMediaServerPort = 5,
		dispidMediaServerIP = 4,
		dispidRenderHeight = 3,
		dispidRenderWidth = 2,
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
	LONG OpenFile(LPCTSTR bstrFile);

	ULONG GetRenderWidth(void);
	void SetRenderWidth(ULONG newVal);
	ULONG GetRenderHeight(void);
	void SetRenderHeight(ULONG newVal);
	BSTR GetMediaServerIP(void);
	void SetMediaServerIP(LPCTSTR newVal);
	LONG GetMediaServerPort(void);
	void SetMediaServerPort(LONG newVal);
	VARIANT_BOOL Login(LPCTSTR bstrUsername, LPCTSTR bstrPassword, LPCTSTR bstrIP, LONG lPort);
	void Logout(void);
	ULONG GetRenderWndNum(void);
	void SetRenderWndNum(ULONG newVal);
	ULONG GetCapturePicType(void);
	void SetCapturePicType(ULONG newVal);
	BSTR GetCapturePicPath(void);
	void SetCapturePicPath(LPCTSTR newVal);
	VARIANT_BOOL GetHighPictureQuality(void);
	void SetHighPictureQuality(VARIANT_BOOL newVal);
	VARIANT_BOOL IsChannelEnable(ULONG lChannel);
	ULONG EnableChannel(ULONG lChannel, VARIANT_BOOL bEnable);
};

