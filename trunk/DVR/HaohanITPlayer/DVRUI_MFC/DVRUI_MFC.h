
// DVRUI_MFC.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDVRUI_MFCApp:
// �йش����ʵ�֣������ DVRUI_MFC.cpp
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

// ��д
public:
	virtual BOOL InitInstance();
	CString csFilePath;//˫����vs�ļ�����ȡ��ǰvs�ĵ�ַ
// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CDVRUI_MFCApp theApp;