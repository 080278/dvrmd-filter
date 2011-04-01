#pragma once

//#include <map>

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

struct CDVRSettings
{
public:
	CDVRSettings(void);
	~CDVRSettings(void);

	enum eCapPicType{eJPEG = 0, eBMP};

public:
	//Media Server Settings
	CString		m_csMediaServerIP;			//Media Server IP: e.g. 192.168.123.59
	int			m_lPort;			//Media Server Port: e.g. 2000
	CString		m_csUsername;	//Login Server: Username
	CString		m_csPassword;	// Password

	CTime		m_StartTime;		//Render start time
	CTime		m_EndTime;			//Render end time
	
	//Player Settings.
	BOOL		m_bHighPictureQuality;	//Quality of the picture: default is FALSE;
	CString		m_csPicCapturePath;	//Capture Picture folder
	eCapPicType	m_eCapturePicType;			//Capture picture type: default is JPEG
};

