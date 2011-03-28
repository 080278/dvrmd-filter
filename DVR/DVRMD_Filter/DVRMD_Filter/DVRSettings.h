#pragma once

#include <map>

//����DVR��Ϣ
struct HHV_CONN_INFO
{
	HHV_CONN_INFO(){ memset( this, 0x00, sizeof(HHV_CONN_INFO) );	}
	CHAR	ip[48];
	INT		port;
	CHAR	userName[32];	
	CHAR	pwd[32];
};

struct HHV_CLIENT_INFO
{
	HHV_CLIENT_INFO(){ memset( this, 0x00, sizeof(HHV_CLIENT_INFO) );	}
	HHV_CONN_INFO connInfo;
	int channel;//ͨ���ţ���0��ʼ	
	int childstream;	//0-��������1-������
};

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
	HHV_CLIENT_INFO		m_HHVClientInfo;
	CTime				m_StartTime;
	CTime				m_EndTime;

	//Player Settings
	BOOL		m_bHighPictureQuality;
};

