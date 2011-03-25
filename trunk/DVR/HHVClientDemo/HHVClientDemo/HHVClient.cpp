// HHVClient.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "HHVClient.h"
#include "HHVClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHHVClientApp

BEGIN_MESSAGE_MAP(CHHVClientApp, CWinApp)
	//{{AFX_MSG_MAP(CHHVClientApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHHVClientApp construction

CHHVClientApp::CHHVClientApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CHHVClientApp object

CHHVClientApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CHHVClientApp initialization

BOOL CHHVClientApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	//获取当前路径
	GetModuleFileName(NULL,m_szCurPath.GetBuffer(MAX_PATH),MAX_PATH);	
	m_szCurPath.ReleaseBuffer();
	m_szCurPath = m_szCurPath.Left(m_szCurPath.ReverseFind('\\') + 1);
	
	//setting配置文件路径
	CString szSettingPath;		
	szSettingPath = m_szCurPath + "setting.ini";
	
	//语言配置文件路径
	CString szLang;          
	szLang="English";
	DWORD dwSize = 1000;
	GetPrivateProfileString("Setting","Language",_T("Chinese"),szLang.GetBuffer(dwSize),dwSize,szSettingPath); 
	m_szLanguagePath=m_szCurPath + _T("Language\\")+szLang+_T(".ini");
	

	CHHVClientDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

/*********************************************************************
* 函数名称:m_LoadString
* 说明:	根据标识 szID到选定的语言文件中加载字符串
*********************************************************************/
CString CHHVClientApp::m_LoadString(CString szID)
{
	CString szValue;
	DWORD dwSize = 1000;
	GetPrivateProfileString(_T("String"),szID,_T("Not found"),
		szValue.GetBuffer(dwSize),dwSize,m_szLanguagePath);
	szValue.ReleaseBuffer();
	
	szValue.Replace(_T("\\n"),_T("\n"));	//替换回换行符号
	
	return szValue;
}
