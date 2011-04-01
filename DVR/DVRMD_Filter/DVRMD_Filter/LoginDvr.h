#ifndef _LOGINDVR_H
#define _LOGINDVR_H

#pragma warning(disable:4786)

#include "winsock2.h"
#include "Sync_Locks.h"

#define STATUS_LOGINED		1
#define STATUS_UNLOGINED	0

#define MAX_USERNAME_LEN	64
#define MAX_IPADDR_LEN		48	

struct LOGIN_STRUCT
{
	char				userName[MAX_USERNAME_LEN];
	char				userPwd[MAX_USERNAME_LEN];
	char				dvrIP[MAX_IPADDR_LEN];
	unsigned short		dvrPort;
	int					loginID;
	int					index;
	SOCKET				hSocket;
	int					logined;//状态记录，已经登录成功

	BYTE				onlineHeartbeatFailCount;

	LOGIN_STRUCT()
	{
		hSocket	= INVALID_SOCKET;
		index = -1;
		memset(userName, 0x00, MAX_USERNAME_LEN);
		memset(userPwd, 0x00, MAX_USERNAME_LEN);
		memset(dvrIP, 0x00, MAX_IPADDR_LEN);
		dvrPort = 0;
		loginID = -1;
		onlineHeartbeatFailCount = 0;
	}
};


#define		STOP_STATUS	0
#define		RUN_STATUS	1

class CLoginDvr
{
public:
	CLoginDvr(LPCTSTR dvrIP, int dvrPort, LPCTSTR userName, LPCTSTR userPwd, int index );
	virtual ~CLoginDvr();

	void	Startup();
	void	Clearup();

	int		Login(LPCTSTR userName,  LPCTSTR pwd, LPCTSTR addr, int port );
	int		Logout( );

	int		ReLogin( int index );

	int		CheckOnlineStatus( int index);

	int		MakeKeyFrame(LONG lUserID, LONG lChannel);
	
	int		ShutDownDVR( int userID );


	int PanelKey( int userID, int keyIndex );
	int StartDVRRecord( int userID, int channel );
	int StopDVRRecord( int userID, int channel );	
	
	int GetDvrVersion(long lUserID, LPTSTR buf);

	bool IsSame(LPCTSTR dvrIP, int dvrPort);
	
	int FindFileByTime(int userID, int channel, UINT startTime, UINT stopTime, WORD MaxCount, char *buf);

	INT UploadCfgFile(LPCTSTR imageName );
private:
	int				CheckUserID_T(int handle);
	int				GetFreeIndex_T();	
	int				LoginDvr_T(LPCTSTR userName,  LPCTSTR pwd, LPCTSTR addr, int port, LOGIN_STRUCT* login);
	void			OnNetDisconnected_T(int retvalue );

	int				LoginDvrCmd(SOCKET sk, LPCTSTR strUser, LPCTSTR strPass, LOGIN_STRUCT* login);
private:
	bool			m_bExit;
	HANDLE			m_hEventThreadExit;
	HANDLE			m_hCreateWindowEvent;

	int				m_index;
	int				m_timerID;
public:
	LOGIN_STRUCT	m_loginInfo;
private:
	CCritSec		m_csLock;
	
private:
	void			NotifyLogoutMessage(int index, TCHAR* dvrIP);
private:
	char			userName[MAX_USERNAME_LEN];
	char			userPwd[MAX_USERNAME_LEN];
	char			dvrIP[MAX_IPADDR_LEN];
	unsigned short	dvrPort;
};
/***********************************************************************************************/
#endif