#pragma once

#include <map>

//连接DVR信息
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
	int channel;//通道号，从0开始	
	int childstream;	//0-主码流；1-次码流
};

class CDVRSettings
{
public:
	CDVRSettings(void);
	~CDVRSettings(void);

	enum eCapPicType{eJPEG = 0, eBMP};

public:
	//Media Server Settings
	TCHAR		m_szIP[48];		//Media Server IP: e.g. 192.168.123.59
	int			m_lPort;		//Media Server Port: e.g. 2000
	TCHAR		m_szUsername[64];
	TCHAR		m_szPassword[64];

	CTime		m_StartTime;
	CTime		m_EndTime;
	
	//Player Settings.
	BOOL		m_bHighPictureQuality;
	TCHAR		m_szPicCapturePath[MAX_PATH];
	eCapPicType	m_eCapturePicType;
};

