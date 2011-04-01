// PlayerMgr.cpp: implementation of the CPlayerMgr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PlayerMgr.h"
#include "DvrSDKErr.h"
#include "PlayMp4H_fFunDef.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CPlayerMgr	g_playerMgr;
CPlayerMgr::CPlayerMgr()
{
	m_status = STOP_STATUS;
	memset( m_player, 0x00, sizeof(m_player) );
}

CPlayerMgr::~CPlayerMgr()
{

}

VOID CPlayerMgr::Init(HWND hNotifyWnd)
{
	if( m_status == RUN_STATUS )
		return ;
	LoadPlayMp4Dll();
	memset( m_player, 0x00, sizeof(m_player) );
	m_status = RUN_STATUS;
}
VOID CPlayerMgr::Clearup()
{
	if( m_status == STOP_STATUS )
	{
		TRACE("m_status == STOP_STATUS, 退出CPlayerMgr::UnInit  \r\n\r\n");
		return ;
	}
	for(int i = 0; i < MAX_PLAYER; i++)
	{
		if(m_player[i])
		{
			m_player[i]->Clearup();
			delete m_player[i];
			m_player[i] = NULL;
		}
	}
	m_status = STOP_STATUS;
}

INT CPlayerMgr::StartMonitor(HWND hWnd, HHV_CLIENT_INFO* clientInfo)
{
	//TRACE("进入CPlayerMgr::OpenMonitor, userID = %d, chanNo =%d, transType = %d\r\n", userID, channel, transType);
	
	CPlayer* player = NULL;
	
	DWORD dwLock = m_csLock.Lock(90*1000);
	if( dwLock != WAIT_OBJECT_0 )//不能获得锁
	{
		//TRACE("CPlayerMgr::OpenMonitor中dwLock != WAIT_OBJECT_0 ，退出, userID = %d, chanNo =%d\r\n", userID, channel);
		return HHV_ERROR_ENTER_CSLOCK;
	}
	int index = 0;
	index = GetIdlePlayer( );
	if( index < 0)
	{
		m_csLock.Unlock();
		return index;
	}
	player = new CPlayer();
	if( NULL == player )
	{
		m_csLock.Unlock();
		return HHV_ERROR_POORMEMORY;
	}
	player->Init( NULL, index );
	m_player[index] = player;
	m_csLock.Unlock();
	
	int ret = player->StartMonitor( hWnd, clientInfo);
	if( ret < 0)
	{
		CAutoLock_Mutex lc(&m_csLock);
		delete player;
		m_player[index] = NULL;
		return ret;
	}	
	//TRACE("退出CPlayerMgr::OpenMonitor, userID = %d, chanNo =%d， realHandle = %d\r\n", userID, channel, index);
	
	return index;	
}
INT CPlayerMgr::StopMonitor( int handle )
{	
	TRACE("关闭监视 CPlayerMgr::CloseMonitor 进入 handle = %d\r\n\r\n",handle);
	if( handle >= MAX_PLAYER || handle < 0 )
		return HHV_ERROR_INVALID_PARA;

	DWORD dwLock = m_csLock.Lock(5000);
	if( dwLock != WAIT_OBJECT_0 )//不能获得锁
	{
		return HHV_ERROR_ENTER_CSLOCK;
	}
	CPlayer* player = m_player[handle];
	m_player[handle] = NULL;
	m_csLock.Unlock();
	
	if( player != NULL)
	{
		player->StopMonitor();
		player->Clearup();
		delete player;		
	}
	TRACE("成功退出CPlayerMgr::StopMonitor\r\n\r\n");
	return 0;
}

int	CPlayerMgr::GetIdlePlayer()
{
	for(int i = 0; i < MAX_PLAYER; i++)
	{
		if( m_player[i] == NULL )
			return i;
	}
	return HHV_ERROR_NOIDLEPLAYER;
}

int CPlayerMgr::StartPlayBackByTime(HWND hWnd, SYSTEM_VIDEO_FILE* recdFile,
						 char* ssIP, int ssPort)
{
	CPlayer* player = NULL;
	
	DWORD dwLock = m_csLock.Lock(90*1000);
	if( dwLock != WAIT_OBJECT_0 )//不能获得锁
	{
		//TRACE("CPlayerMgr::OpenMonitor中dwLock != WAIT_OBJECT_0 ，退出, userID = %d, chanNo =%d\r\n", userID, channel);
		return HHV_ERROR_ENTER_CSLOCK;
	}
	int index = 0;
	index = GetIdlePlayer( );
	if( index < 0)
	{
		m_csLock.Unlock();
		return index;
	}
	player = new CPlayer();
	if( NULL == player )
	{
		m_csLock.Unlock();
		return HHV_ERROR_POORMEMORY;
	}
	player->Init( NULL, index );
	m_player[index] = player;
	m_csLock.Unlock();
	
	int ret = player->StartPlayBackByTime(hWnd, recdFile, ssIP, ssPort);
	if( ret < 0)
	{
		CAutoLock_Mutex lc(&m_csLock);
		delete player;
		m_player[index] = NULL;
		return ret;
	}	
	//TRACE("退出CPlayerMgr::OpenMonitor, userID = %d, chanNo =%d， realHandle = %d\r\n", userID, channel, index);
	
	return index;	
}
int CPlayerMgr::StopPlayBackByTime(int handle)
{
	TRACE("关闭回放 CPlayerMgr::StopPlayBackByTime 进入 handle = %d\r\n\r\n",handle);
	if( handle >= MAX_PLAYER || handle < 0 )
		return HHV_ERROR_INVALID_PARA;
	
	DWORD dwLock = m_csLock.Lock(5000);
	if( dwLock != WAIT_OBJECT_0 )//不能获得锁
	{
		return HHV_ERROR_ENTER_CSLOCK;
	}
	CPlayer* player = m_player[handle];
	m_player[handle] = NULL;
	m_csLock.Unlock();
	
	if( player != NULL)
	{
		player->StopPlayBackByTime(handle);
		player->Clearup();
		delete player;		
	}
	TRACE("成功退出CPlayerMgr::StopPlayBackByTime\r\n\r\n");
	return 0;
}
