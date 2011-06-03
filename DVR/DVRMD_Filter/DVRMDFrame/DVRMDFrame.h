
// DVRMDFrame.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CDVRMDFrameApp:
// See DVRMDFrame.cpp for the implementation of this class
//
class CMyCommandLineInfo : public CCommandLineInfo
{
public:
        void ParseParam(LPCTSTR lpszParam, BOOL bFlag, BOOL bLast);
};

class CDVRMDFrameApp : public CWinAppEx
{
public:
	CDVRMDFrameApp();

// Overrides
	public:
	virtual BOOL InitInstance();

	CString csFilePath;//双击打开vs文件，获取当前vs的地址
// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CDVRMDFrameApp theApp;