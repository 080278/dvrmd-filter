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

struct CDVRSettings
{
public:
	CDVRSettings(void);
	~CDVRSettings(void);

public:
	bool Save(LPCTSTR szXmlPath = NULL);
	bool Load(LPCTSTR szXmlPath = NULL);

	enum eCapPicType{eJPEG = 0, eBMP};

public:
	//Media Server Settings
	CString		m_csMediaServerIP;			//Media Server IP: e.g. 192.168.123.59
	int			m_lPort;			//Media Server Port: e.g. 2000
	CString		m_csUsername;	//Login Server: Username
	CString		m_csPassword;	// Password

	CTime		m_StartTime;		//Render start time
	CTime		m_EndTime;			//Render end time
	
	//Render Window Settings
	LONG			m_nRenderWidth;
	LONG			m_nRenderHeight;
	int			m_nRenderWndNum;	//Default: 1. 1 , 4, 8, 16
	std::map<int, bool>	m_mapEnableChannel;

	//Player Settings.
	BOOL		m_bHighPictureQuality;	//Quality of the picture: default is FALSE;
	CString		m_csPicCapturePath;	//Capture Picture folder
	eCapPicType	m_eCapturePicType;			//Capture picture type: default is JPEG

};
