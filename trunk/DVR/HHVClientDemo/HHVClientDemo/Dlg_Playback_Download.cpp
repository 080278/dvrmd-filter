// Dlg_Playback_Download.cpp : implementation file
//

#include "stdafx.h"
#include "HHVClient.h"
#include "Dlg_Playback_Download.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_Playback_Download dialog


CDlg_Playback_Download::CDlg_Playback_Download(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_Playback_Download::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg_Playback_Download)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlg_Playback_Download::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_Playback_Download)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_TAB_PLAYBACK_DOWNLOAD, m_sheet_playback);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_Playback_Download, CDialog)
	//{{AFX_MSG_MAP(CDlg_Playback_Download)
	ON_BN_CLICKED(IDC_BTN_PLAYBACK_CLOSE, OnBtnPlaybackClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_Playback_Download message handlers

void CDlg_Playback_Download::OnBtnPlaybackClose() 
{
	// TODO: Add your control notification handler code here
	
}

BOOL CDlg_Playback_Download::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//在属性页中加入对话框
	CString str[2];
	str[0]="按时间回放";
	str[1]="按文件名回放";
	
	m_sheet_playback.AddPage( str[0], &playback_bytime_dlg, IDD_DLG_PLAYBACK_BYTIME);
	m_sheet_playback.AddPage( str[1], &playback_byname_dlg, IDD_DLG_PLAYBACK_BYNAME);
	
	m_sheet_playback.Show();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
