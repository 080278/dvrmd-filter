// UploadFileMgr.cpp: implementation of the CUploadFileMgr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "HHVClient.h"
#include "UploadFileMgr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CUploadFileMgr CUploadFileMgr::g_UploadFileMgr;

CUploadFileMgr::CUploadFileMgr()
{

}

CUploadFileMgr::~CUploadFileMgr()
{

}

CUploadFileMgr* CUploadFileMgr::GetInstance()
{
	return &g_UploadFileMgr;
}

INT CUploadFileMgr::UploadCfgFile(int userID, TCHAR* dvrIP, 
								  int dvrPort,const TCHAR* imageName )
{
	CUploadFile* pUploadFile = NULL;
	
	DWORD dwLock = m_csLock.Lock(90*1000);
	if( dwLock != WAIT_OBJECT_0 )//���ܻ����
	{
		return HHV_ERROR_ENTER_CSLOCK;
	}
	int index = 0;
	index = GetIdleIndex( );
	if( index < 0)
	{
		m_csLock.Unlock();
		return index;
	}
	pUploadFile = new CUploadFile();
	if( NULL == pUploadFile )
	{
		m_csLock.Unlock();
		return HHV_ERROR_POORMEMORY;
	}
	m_UploadFile[index] = pUploadFile;
	m_csLock.Unlock();
	
	int ret = pUploadFile->UploadCfgFile(index, userID, dvrIP, dvrPort, imageName);
	if( ret < 0)
	{
		CAutoLock_Mutex lc(&m_csLock);
		delete pUploadFile;
		m_UploadFile[index] = NULL;
		return ret;
	}	
	return index;	
}

int	CUploadFileMgr::GetIdleIndex()
{
	for(int i = 0; i < MAX_UPLOADFILE_NUM; i++)
	{
		if( m_UploadFile[i] == NULL )
			return i;
	}
	return HHV_ERROR_NOIDLEPLAYER;
}