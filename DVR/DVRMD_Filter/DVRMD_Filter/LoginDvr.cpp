// UserLogin.cpp: implementation of the CLoginDvr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LoginDvr.h"
//#include "TraceLog.h"
#include "Player.h"
#include "DvrSDKErr.h"
//#include "struct_TCPServ.h"
#include "./NetDef.h"
#include "CommClass.h"
#include "UploadFileMgr.h"

//#define SUYUAN_NO_CHECK_DVR_ONLINE	1

int g_connectTimeOut = 10*1000;

extern HWND			g_hWnd;
VOID __stdcall TimerProc(HWND hwnd,UINT uMsg,UINT_PTR idEvent,DWORD dwTime);

CLoginDvr::CLoginDvr(TCHAR* pdvrIP, int pdvrPort, TCHAR* puserName, TCHAR* puserPwd, int nIndex)
{
	strcpy( m_loginInfo.dvrIP, CT2A(pdvrIP));
	m_loginInfo.dvrPort = pdvrPort;

	TRACE("CLoginDvr::CLoginDvr��pdvrIP = %s, pdvrPort = %d, puserName =%s, puserPwd = %s \r\n", pdvrIP, pdvrPort, puserName, puserPwd);
	strcpy( m_loginInfo.userName, CT2A(puserName) );
	strcpy( m_loginInfo.userPwd, CT2A(puserPwd) );
	m_index = nIndex;
	m_loginInfo.index = nIndex;
	m_loginInfo.logined = STATUS_UNLOGINED;
}

CLoginDvr::~CLoginDvr()
{
	Clearup();
}

void CLoginDvr::Startup()
{

}
void CLoginDvr::Clearup()
{

}

//return the index handle
int	CLoginDvr::Login(TCHAR* userName, TCHAR* pwd, TCHAR* addr, int port)
{
	LOGIN_STRUCT* login = &m_loginInfo;
	int index = m_index;

	//2010-03-19 added
	m_csLock.Lock();
	if( login->hSocket != INVALID_SOCKET )//�ȹر�socket
	{
		TRACE("��¼ʱ�ȹر�ԭsocket index = %d IP = %s SOCKET = %d\r\n\r\n",login->index, login->dvrIP, login->hSocket );
		closesocket( login->hSocket );
		login->hSocket = INVALID_SOCKET;
	}
	login->logined = STATUS_UNLOGINED;
	
	int ret = LoginDvr_T(userName, pwd, addr, port, login);//���ص�¼�ɹ�SOCKET 
	
	if( ret < 0 )
	{
		m_csLock.Unlock();
		return ret;
	}

	login->hSocket = (SOCKET)ret;
	
	//��¼�ɹ�
	login->logined = STATUS_LOGINED;//��¼��¼״̬
	
	m_csLock.Unlock();

	return login->index;
}

/* �ǳ�ʱ��ɾ��ռλ��ֻ�ر�socket
 *	
 */
int	CLoginDvr::Logout( )
{	
	LOGIN_STRUCT* login = &m_loginInfo;

	m_csLock.Lock();
	
	closesocket( login->hSocket );//ֻ�ر�socket
	login->hSocket = INVALID_SOCKET;
	login->logined = STATUS_UNLOGINED;
	login->loginID = -1;
	m_csLock.Unlock();
	return 0;
}

//����Ƿ�����,�淢������
int CLoginDvr::CheckOnlineStatus( int index)
{
	LOGIN_STRUCT* login = &m_loginInfo;
	
	CAutoLock_CS		lc(&m_csLock);
	if( login->logined == STATUS_UNLOGINED )
	{
//		TRACE("CLoginDvr::CheckOnlineStatus()��login->logined == STATUS_UNLOGINED�� �˳�--------------checkonline------2 \r\n");
		return 0;
	}
	int ret = -1;
	//ret = CInterfaceCmd::CheckSocketStatus( login->hSocket );
	if( ret < 0 )
	{
		Logout( );
		NotifyLogoutMessage(m_index, CA2T(login->dvrIP));
	}
	
	return ret;
}

int	CLoginDvr::LoginDvr_T(TCHAR* userName,  TCHAR* pwd, TCHAR* addr, int port,LOGIN_STRUCT* login )
{
	SOCKET sk = CreateSocket( 0, 30 );

	if( sk == INVALID_SOCKET )
	{
		TRACE("����Socketʧ�� CLoginDvr::Login IP = %s port = %d\r\n\r\n", addr, port);
		return HHV_ERROR_CREATESOCKET;
	}
	if( Connect(sk, CT2A(addr), port,g_connectTimeOut ) == SOCKET_ERROR )
	{
		int err = GetLastError();
		TRACE("����DVRʧ�� CLoginDvr::Login IP = %s port = %d SOCKET = %d, err=%d\r\n\r\n", addr, port, sk, err);
		closesocket(sk);
		return HHV_ERROR_CONNECT;
	}
	
	int ret = LoginDvrCmd( sk, userName, pwd, login );
	if( ret < 0 )
	{
		TRACE("��¼�����ʧ�� CLoginDvr::Login IP = %s port = %d userName = %s pwd = %s\r\n\r\n", addr, port, userName, pwd);
		closesocket( sk );
		return ret;
	}
	return (int)sk;
}

int CLoginDvr::MakeKeyFrame(LONG index, LONG lChannel)
{
	TRACE("����CLoginDvr::MakeKeyFrame��\r\n" );
	LOGIN_STRUCT* login = &m_loginInfo;
	if( login == NULL )
		return HHV_ERROR_NOLOGIN;

	m_csLock.Lock();
	//int ret = CInterfaceCmd::GenerateIFrame( login->hSocket, login->loginID, lChannel );
	//TRACE("�˳�CLoginDvr::MakeKeyFrame��ret = %d\r\n", ret );
	m_csLock.Unlock();
	//return ret;
	return 0;
}

void CLoginDvr::NotifyLogoutMessage( int index, TCHAR* dvrIP)
{
	TRACE("CLoginDvr::NotifyLogoutMessage  \r\n");
	
//	UINT uMsg = WM_DLDVR_LOGOUT_NOTIFY;
//	UINT wParam = index; 
//	UINT lParam = 0;//����
//	
//	if( g_Config.hNotifyWnd != NULL)
//	{
//		::PostMessage( g_Config.hNotifyWnd, uMsg, wParam, lParam );	
//	}
//
//	NET_DLDVR_EXCEPTION	ext;
//	ext.Msg = uMsg;
//	ext.wParam = wParam;
//	ext.lPara = lParam;
//	if( g_Config.funCallBack != NULL )
//	{
//		TRACE("NotifyLogoutMessage �е���g_Config.funCallBack�� index = %d IP = %s \r\n\r\n", index, dvrIP);
//
//		g_Config.funCallBack( EXCEPTION_NOTIFY, dvrIP, (char*)&ext, sizeof(NET_DLDVR_EXCEPTION) );			
//	}
//
//	SEGMENT_LOGIN_STRUCT	login;	
//	long userID = -1;
//	for( int i =0; i< MAX_LOGIN_DVR; i++)
//	{
//		int ret = g_LoginDvrMgr.GetSegmentLoginInfoByUserID( i, login );
//		if( ret < 0 )
//			continue;
//		if( strcmp( dvrIP, login.dvrIP ) == 0)
//		{
//			userID = i;
//			break;
//		}
//	}
//	if( g_Config.funCallBackEx != NULL )
//	{
//		g_Config.funCallBackEx( EXCEPTION_NOTIFY, userID, (char*)&ext, sizeof(NET_DLDVR_EXCEPTION) );			
//	}
//
//	for( i = 0; i < MAX_PLAYER; i++)
//	{
//		if( g_Config.funCallBack_Index[i] != NULL)
//		{
//			g_Config.funCallBack_Index[i](  EXCEPTION_NOTIFY, dvrIP, (char*)&ext, sizeof(NET_DLDVR_EXCEPTION) );		
//		}
//		
//		if( g_Config.funCallBackEx_Index[i] != NULL )
//		{
//			g_Config.funCallBackEx_Index[i]( EXCEPTION_NOTIFY, userID, (char*)&ext, sizeof(NET_DLDVR_EXCEPTION)) ;			
//		}
//	}

}

int CLoginDvr::ShutDownDVR( int userID )
{
	//int ret = 0;
	//	LOGIN_STRUCT* login = &m_loginInfo;	
	//	CAutoLock_CS lc(&m_csLock);
	//	
	//	ret = CInterfaceCmd::ShutDownDvr(login->hSocket, login->loginID, NULL );
	//	OnNetDisconnected_T( ret );
	//	return ret;
	return 0;
}

int CLoginDvr::StartDVRRecord( int userID, int channel )
{
	int ret = 0;
	LOGIN_STRUCT* login = &m_loginInfo;	
	CAutoLock_CS lc(&m_csLock);

	SRecordStart_Msg_Direct msg;
	memset( &msg, 0x00, sizeof(SRecordStart_Msg_Direct) );
	msg.header.command = SYSTEM_START_RECORD_Direct;
	msg.Channel = channel;
	
	msg.h2n();

	if(send(login->hSocket, (char*)&msg, sizeof(msg), 0 ) <= 0 )
	{
		return HHV_ERROR_SEND;
    }


	return 0;
}

int CLoginDvr::StopDVRRecord( int userID, int channel )
{
	int ret = 0;
	LOGIN_STRUCT* login = &m_loginInfo;	
	CAutoLock_CS lc(&m_csLock);
	
	SRecordStop_Msg_Direct oSRecStop;
	memset( &oSRecStop, 0x00, sizeof(SRecordStop_Msg_Direct) );

	oSRecStop.header.command = SYSTEM_STOP_RECORD_Direct;
	
	oSRecStop.Channel = channel;
	
	oSRecStop.h2n();

	if(send(login->hSocket, (char*)&oSRecStop, sizeof(oSRecStop), 0 ) <= 0 )
	{
		return HHV_ERROR_SEND;
    }

	return 0;
}

//int CLoginDvr::GetDvrWorkState( int userID, NET_DLDVR_WORKSTATE* workState )
//{
	//int ret = 0;
	//	LOGIN_STRUCT* login = &m_loginInfo;	
	//	CAutoLock_CS lc(&m_csLock);
	//	
	//	ret = CInterfaceCmd::GetDvrState( login->hSocket, login->loginID, workState, NULL);
	//
	//	OnNetDisconnected_T( ret );
	////	TRACE("��ȷ�˳�CDVRCfg::GetDvrWorkState, ret=%d\r\n",ret);
	//	return ret;
//	return 0;
//}

int CLoginDvr::GetDvrVersion(long userID, char *buf)
{
	//int ret = 0;
	//	LOGIN_STRUCT* login = &m_loginInfo;	
	//	CAutoLock_CS lc(&m_csLock);
	//	
	//	ret = CInterfaceCmd::GetDvrVersion(login->hSocket, login->loginID, buf, NULL );
	//	OnNetDisconnected_T( ret );
	//	
	//	return ret;
	return 0;
}

//int CLoginDvr::GetDvrDiskState( int userID, NET_DLDVR_DVRDISKSTATE* diskState )
//{
	//int ret = 0;
	//	LOGIN_STRUCT* login = &m_loginInfo;	
	//	CAutoLock_CS lc(&m_csLock);
	//	
	//	ret = CInterfaceCmd::GetDvrDiskState( login->hSocket, login->loginID, diskState, NULL);
	//
	//	OnNetDisconnected_T( ret );
	//	return ret;
//	return 0;
//}

int CLoginDvr::FindFileByTime(int userID, int channel, UINT startTime, UINT stopTime,  WORD MaxCount, char *buf)
{
	//LOGIN_STRUCT* login = &m_loginInfo;	
	//	CAutoLock_CS lc(&m_csLock);
	//	
	//	int ret = 0;
	//	
	//	ret = CInterfaceCmd::FindFileByTime( login->hSocket, login->loginID, channel, startTime, stopTime, MaxCount, buf, NULL );
	//	
	//
	//	OnNetDisconnected_T( ret );
	//	TRACE("CDVRCfg::FindFileOpen�е���CInterfaceCmd::FindFileOpen ret= %d���˳�FindFileOpen\r\n", ret);
	//	return ret;

	return 0;
	
}

int CLoginDvr::LoginDvrCmd( SOCKET sk, TCHAR* strUser,TCHAR* strPass, LOGIN_STRUCT* login )
{
    NET_LOGIN_MESSAGE			msg ;
	NET_LOGIN_RESPONSE			res;
	memset(&msg, 0x00, sizeof(msg));
	memset(&res, 0x00, sizeof(res));
	
	msg.header.command  = SYSTEM_LOGIN_REQUEST;
	msg.header.length = sizeof(msg) - sizeof(msg.header);
	strcpy( msg.UserName, CT2A(strUser));
	strcpy( msg.PassWord, CT2A(strPass));
	
	msg.h2n();
	
	if(send(sk, (char*)&msg, sizeof(msg), 0 ) <= 0 )
	{
        //Application->MessageBoxA( "��½����1, ���͵�½����ʧ��!",
		//	GetString("ID_MESSAGE_ERROR").c_str(), MB_ICONWARNING );
		return HHV_ERROR_SEND;
    }
	
	if(recv(sk, (char*)&res, sizeof(res), 0 ) <= 0 )
    {
        //Application->MessageBoxA( "��½����2, �ղ�����������Ӧ,����������Ƿ��!",
		//	GetString("ID_MESSAGE_ERROR").c_str(), MB_ICONWARNING );
		return HHV_ERROR_RECV ;
    }
	
	res.n2h();
	
	if ( res.header.command != SYSTEM_REQUEST_ACCEPT )
	{
		switch ( res.reason )
		{
			
		case USER_INVALID_USERNAME:
		case USER_INVALID_PASSWORD:
		case USER_GROUP_NOTALLOCATE:
			//Application->MessageBoxA( GetString("ID_COMMCLASS_TEXT_C9").c_str(),
			//	GetString("ID_MESSAGE_ERROR").c_str(), MB_ICONWARNING );
			
			return HHV_ERROR_INVALID_USERNAMEORPWD;
			
		case USER_ADMINI_ONLINE:
			//Application->MessageBoxA( GetString("ID_COMMCLASS_TEXT_C10").c_str(),
			//	GetString("ID_MESSAGE_ERROR").c_str(), MB_ICONWARNING );
			return HHV_ERROR_ADMINI_ONLINE;
			
			break;
        case DataBase_ERROR:
            //Application->MessageBoxA( GetString("ID_COMMCLASS_TEXT_C16").c_str(),
			//	GetString("ID_MESSAGE_ERROR").c_str(), MB_ICONWARNING );
			return HHV_ERROR_DataBase_ERROR;
			break;
        default:
            //Application->MessageBoxA( GetString("ID_COMMCLASS_TEXT_C17").c_str(),
			//	GetString("ID_MESSAGE_ERROR").c_str(), MB_ICONWARNING );
			return HHV_ERROR_USER_NORESON;
			break;
		}
	}

    //nCSVersion = res.CSVersion; //CS�汾��Ϣ               
	//csSameNameID = res.csSameNameID;//�û�ID

	return 0;
}  

bool CLoginDvr::IsSame( TCHAR* dvrIP, int dvrPort )
{
	if( strcmp(m_loginInfo.dvrIP, CT2A(dvrIP)) == 0 && 
		m_loginInfo.dvrPort == dvrPort )
		return true;
	return false;
}


INT CLoginDvr::UploadCfgFile(const TCHAR* imageName )
{
	int ret = 0;
	LOGIN_STRUCT* login = &m_loginInfo;	
	CAutoLock_CS lc(&m_csLock);

	return g_UploadFileMgr.UploadCfgFile(login->loginID, CA2T(login->dvrIP), login->dvrPort,
										imageName);
}

