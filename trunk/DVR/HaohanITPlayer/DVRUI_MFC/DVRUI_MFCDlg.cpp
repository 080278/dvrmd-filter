
// DVRUI_MFCDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DVRUI_MFC.h"
#include "DVRUI_MFCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDVRUI_MFCDlg 对话框




CDVRUI_MFCDlg::CDVRUI_MFCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDVRUI_MFCDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nPaneCtrlHeight = 30;
}

void CDVRUI_MFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DVRMVPLAYERCTRL1, m_DVRPlayer);
}

BEGIN_MESSAGE_MAP(CDVRUI_MFCDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPENFILE, &CDVRUI_MFCDlg::OnBnClickedOpenfile)
	ON_WM_DESTROY()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CDVRUI_MFCDlg 消息处理程序

BOOL CDVRUI_MFCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	RECT rcPlayer, rcDlg;
	GetClientRect(&rcDlg);
	GetDlgItem(IDC_PLAY_WND)->GetWindowRect(&rcPlayer);
	m_nPaneCtrlHeight = rcDlg.bottom - rcPlayer.bottom;
	m_DVRPlayer.MoveWindow(0, 0, rcPlayer.right - rcPlayer.left, rcPlayer.bottom - rcPlayer.top);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDVRUI_MFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDVRUI_MFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDVRUI_MFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDVRUI_MFCDlg::OnBnClickedOpenfile()
{
	CFileDialog dlg(TRUE);
	if (dlg.DoModal() == IDOK)
	{
		this->m_DVRPlayer.OpenFile(dlg.GetPathName());
	}
}


void CDVRUI_MFCDlg::OnDestroy()
{
	CDialog::OnDestroy();

}


void CDVRUI_MFCDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	if (m_DVRPlayer.m_hWnd != NULL && ::IsWindow(m_DVRPlayer.m_hWnd))
	{
		m_DVRPlayer.MoveWindow(0, 0, cx, cy-m_nPaneCtrlHeight);
	}
}


BEGIN_EVENTSINK_MAP(CDVRUI_MFCDlg, CDialog)
	ON_EVENT(CDVRUI_MFCDlg, IDC_DVRMVPLAYERCTRL1, 6501, CDVRUI_MFCDlg::DoubleClickDvrmvplayerctrl1, VTS_I2 VTS_I2 VTS_I4 VTS_I4)
	ON_EVENT(CDVRUI_MFCDlg, IDC_DVRMVPLAYERCTRL1, 6502, CDVRUI_MFCDlg::KeyDownDvrmvplayerctrl1, VTS_I2 VTS_I2)
END_EVENTSINK_MAP()


void CDVRUI_MFCDlg::DoubleClickDvrmvplayerctrl1(short nButton, short nShiftState, long fX, long fY)
{
	m_DVRPlayer.put_fullScreen(!m_DVRPlayer.get_fullScreen());
}


void CDVRUI_MFCDlg::KeyDownDvrmvplayerctrl1(short nKeyCode, short nShiftState)
{
	// TODO: Add your message handler code here
	if (nKeyCode == VK_ESCAPE)
	{
		if (m_DVRPlayer.get_fullScreen())
		{
			m_DVRPlayer.put_fullScreen(FALSE);
		}
	}
}
