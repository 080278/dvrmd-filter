// HHVClient.h : main header file for the HHVCLIENT application
//

#if !defined(AFX_HHVCLIENT_H__8E20CCE0_5ABD_48E5_8CB3_08E784419AD9__INCLUDED_)
#define AFX_HHVCLIENT_H__8E20CCE0_5ABD_48E5_8CB3_08E784419AD9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CHHVClientApp:
// See HHVClient.cpp for the implementation of this class
//

class CHHVClientApp : public CWinApp
{
public:
	CHHVClientApp();

	CString m_LoadString(CString szID);

	CString			m_szCurPath;				//保存当前路径
	CString			m_szLanguagePath;			//保存语言文件的路径

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHHVClientApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CHHVClientApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CHHVClientApp theApp;
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HHVCLIENT_H__8E20CCE0_5ABD_48E5_8CB3_08E784419AD9__INCLUDED_)
