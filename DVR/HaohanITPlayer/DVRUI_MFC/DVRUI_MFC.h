
// DVRUI_MFC.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CDVRUI_MFCApp:
// 有关此类的实现，请参阅 DVRUI_MFC.cpp
//
class CMyCommandLineInfo : public CCommandLineInfo
{
public:
        void ParseParam(LPCTSTR lpszParam, BOOL bFlag, BOOL bLast);
};

class CDVRUI_MFCApp : public CWinApp
{
public:
	CDVRUI_MFCApp();

// 重写
public:
	virtual BOOL InitInstance();
	CString csFilePath;//双击打开vs文件，获取当前vs的地址
// 实现

	DECLARE_MESSAGE_MAP()
};

extern CDVRUI_MFCApp theApp;