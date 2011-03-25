// HHVClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HHVClient.h"
#include "HHVClientDlg.h"
#include "winsock2.h"
#include "PlayerMgr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHHVClientDlg dialog

CHHVClientDlg::CHHVClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHHVClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHHVClientDlg)
	m_strIP = _T("192.168.123.59");
	m_nPort = 20000;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHHVClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHHVClientDlg)
	DDX_Text(pDX, IDC_EDT_IP, m_strIP);
	DDX_Text(pDX, IDC_EDT_PORT, m_nPort);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHHVClientDlg, CDialog)
	//{{AFX_MSG_MAP(CHHVClientDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_STATIC_HWND, OnStaticHwnd)
	ON_BN_CLICKED(IDC_BTN_REALPLAY, OnBtnRealplay)
	ON_BN_CLICKED(IDC_BTN_REALSTOP, OnBtnRealstop)
	ON_BN_CLICKED(IDC_BTN_PLAYBACK_DOWNLOAD, OnBtnPlaybackDownload)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHHVClientDlg message handlers

BOOL CHHVClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	WSADATA wsaD;
	DWORD wVersion = MAKEWORD(2, 2);
	if ( WSAStartup( wVersion, &wsaD ) != 0 )
	{
		::MessageBox(NULL, "Socket Lib Load Failure!", "tips", MB_OK );
		return FALSE;
	}
	
	// TODO: Add extra initialization here
	//初始化16分割窗体
	HWND hParentWnd = GetDlgItem(IDC_STATIC_HWND)->m_hWnd;
	m_HwdMgr.InitSplit(hParentWnd);
	m_HwdMgr.SetSplitMode(0, SPLIT_16);

	g_playerMgr.Init(NULL);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CHHVClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CHHVClientDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CHHVClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CHHVClientDlg::OnStaticHwnd() 
{
	POINT pos;
	GetCursorPos(&pos);
	
	POINT	ptClient;
	ptClient.x = pos.x;
	ptClient.y = pos.y;
	ScreenToClient(&ptClient);
	
	m_HwdMgr.SelectChannel(ptClient);
	
}

int chCount = 4;
void CHHVClientDlg::OnBtnRealplay() 
{
	UpdateData(TRUE);
	int i = 0;
	for( ; i < chCount; ++i )
	{
		HWND hWnd = m_HwdMgr.GetHWnd(i);
		HHV_CLIENT_INFO	 hhvInfo;
		strcpy( hhvInfo.connInfo.ip, (LPCTSTR)m_strIP );
		hhvInfo.connInfo.port = m_nPort;
		hhvInfo.channel = i;
		int ret = g_playerMgr.StartMonitor( hWnd, &hhvInfo );
		if( ret < 0 )
		{
			MessageBox("监视出错");
		}
	}
	for( i = 0; i < chCount; ++i )
	{
		HWND hWnd = m_HwdMgr.GetHWnd(i + 4);
		HHV_CLIENT_INFO	 hhvInfo;
		strcpy( hhvInfo.connInfo.ip, "192.168.123.59" );
		hhvInfo.connInfo.port = 20000;
		hhvInfo.channel = i;
		int ret = g_playerMgr.StartMonitor( hWnd, &hhvInfo );
		if( ret < 0 )
		{
			MessageBox("监视出错");
		}
	}

	for( i = 0; i < chCount; ++i )
	{
		HWND hWnd = m_HwdMgr.GetHWnd(i + 8);
		HHV_CLIENT_INFO	 hhvInfo;
		strcpy( hhvInfo.connInfo.ip, "192.168.123.59" );
		hhvInfo.connInfo.port = 20000;
		hhvInfo.channel = i;
		int ret = g_playerMgr.StartMonitor( hWnd, &hhvInfo );
		if( ret < 0 )
		{
			MessageBox("监视出错");
		}
	}

	for( i = 0; i < chCount; ++i )
	{
		HWND hWnd = m_HwdMgr.GetHWnd(i + 12);
		HHV_CLIENT_INFO	 hhvInfo;
		strcpy( hhvInfo.connInfo.ip, "192.168.123.59" );
		hhvInfo.connInfo.port = 20000;
		hhvInfo.channel = i;
		int ret = g_playerMgr.StartMonitor( hWnd, &hhvInfo );
		if( ret < 0 )
		{
			MessageBox("监视出错");
		}
	}
}

int handleCount = 16;
void CHHVClientDlg::OnBtnRealstop() 
{
	for( int i = 0; i < handleCount; ++i )
	{
		int ret = g_playerMgr.StopMonitor( i );
		if( ret < 0 )
		{
			MessageBox("监视出错");
		}	
	}
	
}

void CHHVClientDlg::OnBtnPlaybackDownload() 
{
	CDlg_Playback_Download playback_download_dlg;
	playback_download_dlg.DoModal();	
}
