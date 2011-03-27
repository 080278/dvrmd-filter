#pragma once

#include <map>

class CDVRSettings
{
public:
	CDVRSettings(void);
	~CDVRSettings(void);

public:
	//Settings of the DVR ActiveX Player.

	//Display settings
	HWND		m_hParentWnd;	//Main Frame window
	HWND		m_hRenderWnd;
	RECT		m_rcRenderArea;
	
	//Media Server Settings.
	TCHAR		m_MediaServerIP[16];
	int			m_Port;
	CTime		m_StartTime;
	CTime		m_EndTime;

	//Player Settings
	BOOL		m_bHighPictureQuality;
};

