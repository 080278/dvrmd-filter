// CDVRMVSettings.h  : Declaration of ActiveX Control wrapper class(es) created by Microsoft Visual C++

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CDVRMVSettings

class CDVRMVSettings : public COleDispatchDriver
{
public:
	CDVRMVSettings() {}		// Calls COleDispatchDriver default constructor
	CDVRMVSettings(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CDVRMVSettings(const CDVRMVSettings& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:

	BOOL get_mute()
	{
		BOOL result;
		InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_mute(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x65, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_volume()
	{
		long result;
		InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_volume(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x66, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}

//连接DVR信息

public:
	bool Save(LPCTSTR szXmlPath = NULL);
	bool Load(LPCTSTR szXmlPath = NULL);
	BOOL ExtractFilePath(TCHAR* chPath);

public:
	//Media Server Settings
	CString		m_csMediaServerIP;			//Media Server IP: e.g. 192.168.123.59
	CString			m_lPort;			//Media Server Port: e.g. 2000
	CString		m_csUsername;	//Login Server: Username
	CString		m_csPassword;	// Password

	int			m_nRenderWndNum;	//Default: 1. 1 , 4, 8, 16

};
