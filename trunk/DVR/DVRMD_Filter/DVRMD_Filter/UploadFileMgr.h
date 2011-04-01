// UploadFileMgr.h: interface for the CUploadFileMgr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UPLOADFILEMGR_H__D22E8AC3_154A_4DE8_8DCB_41AE907E778A__INCLUDED_)
#define AFX_UPLOADFILEMGR_H__D22E8AC3_154A_4DE8_8DCB_41AE907E778A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "UploadFile.h"

#include "Sync_Locks.h"
#include "Utilities.h"

#define MAX_UPLOADFILE_NUM	36

class CUploadFileMgr  
{
public:
	CUploadFileMgr();
	virtual ~CUploadFileMgr();

	static CUploadFileMgr* GetInstance();
	INT UploadCfgFile(int userID, TCHAR* dvrIP, 
		int dvrPort,const TCHAR* imageName );

private:
	int	GetIdleIndex();
private:
	CUploadFile* m_UploadFile[MAX_UPLOADFILE_NUM];
	
	CMutex m_csLock;
	
	int m_status;

	static CUploadFileMgr g_UploadFileMgr;
};

//extern CUploadFileMgr g_UploadFileMgr;

#endif // !defined(AFX_UPLOADFILEMGR_H__D22E8AC3_154A_4DE8_8DCB_41AE907E778A__INCLUDED_)
