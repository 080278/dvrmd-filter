
// DVRUI_MFCDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DVRUI_MFC.h"
#include "DVRUI_MFCDlg.h"
#include "afxdialogex.h"
#include "CDVRMVSettings.h"

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
	, ServerPort(20000)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nPaneCtrlHeight = 30;
}

void CDVRUI_MFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DVRMVPLAYERCTRL1, m_DVRPlayer);
	DDX_Text(pDX, IDC_EDIT_SERVERPORT, ServerPort);
}

BEGIN_MESSAGE_MAP(CDVRUI_MFCDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPENFILE, &CDVRUI_MFCDlg::OnBnClickedOpenfile)
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_PLAY_NEXT, &CDVRUI_MFCDlg::OnBnClickedPlayNext)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CDVRUI_MFCDlg::OnBnClickedButtonLogin)
	ON_BN_CLICKED(IDC_BUTTON_START_MONITOR, &CDVRUI_MFCDlg::OnBnClickedButtonStartMonitor)
	ON_BN_CLICKED(IDC_BUTTON_STOP_MONITOR, &CDVRUI_MFCDlg::OnBnClickedButtonStopMonitor)
	ON_BN_CLICKED(IDC_BUTTON_CHANNEL, &CDVRUI_MFCDlg::OnBnClickedButtonChannel)
	ON_BN_CLICKED(IDC_BUTTON_SERVER_PLAY, &CDVRUI_MFCDlg::OnBnClickedButtonStartPlayback)
	ON_BN_CLICKED(IDC_BUTTON_SERVER_STOP, &CDVRUI_MFCDlg::OnBnClickedButtonStopPlayback)
	ON_BN_CLICKED(IDC_BUTTON_VS_PLAY_PAUSE, &CDVRUI_MFCDlg::OnBnClickedButtonVsPlayPause)
	ON_BN_CLICKED(IDC_BUTTON_VS_STOP, &CDVRUI_MFCDlg::OnBnClickedButtonVsStop)
	ON_BN_CLICKED(IDC_BUTTON_VS_REVERSE, &CDVRUI_MFCDlg::OnBnClickedButtonVsReverse)
	ON_BN_CLICKED(IDC_BUTTON_VS_FORWARD, &CDVRUI_MFCDlg::OnBnClickedButtonVsForward)
	ON_WM_CTLCOLOR()
//	ON_WM_VSCROLL()
ON_WM_HSCROLL()
ON_WM_TIMER()
END_MESSAGE_MAP()


// CDVRUI_MFCDlg 消息处理程序

BOOL CDVRUI_MFCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_Settings.Load();
	InitServerInfoBox();
	SetFileState(false);
	clickCount = 0;

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
	if(theApp.csFilePath.GetLength() > 0)
	{
		m_DVRPlayer.OpenFile(theApp.csFilePath);
	}
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
	CFileDialog dlg(TRUE,
		_T("mpg"),
		NULL, 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("DVR File(*.vs)|*.vs|File(*.mp4;*.264)|*.mp4;*.264|All Files(*.*)|*.*||"), this);
	if (dlg.DoModal() == IDOK)
	{
		m_DVRPlayer.ShowMetaData(TRUE);
		this->m_DVRPlayer.OpenFile(dlg.GetPathName());
		pSlidCtrl=(CSliderCtrl*)GetDlgItem(IDC_SLIDER_PLAY_CONTROL);
		m_Duration = m_DVRPlayer.get_duration();//获得文件总长度
		SetTimer(PLAY_FILE_TIMER, 500, NULL);
		SetFileState(true);
		m_Pause = true;
	}
}


void CDVRUI_MFCDlg::OnDestroy()
{
	CDialog::OnDestroy();
	KillTimer(PLAY_FILE_TIMER);
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


void CDVRUI_MFCDlg::OnBnClickedPlayNext()
{
	m_DVRPlayer.PlayNextFile();
}


void CDVRUI_MFCDlg::OnBnClickedButtonLogin()
{
	CString csLoginInfo;
	CString csIP, csPort, csUName, csPwd;
	GetDlgItem(IDC_IPADDRESS_SERVERIP)->GetWindowText(csIP);
	GetDlgItem(IDC_EDIT_SERVERPORT)->GetWindowText(csPort);
	GetDlgItem(IDC_EDIT_USERNAME)->GetWindowText(csUName);
	GetDlgItem(IDC_EDIT_PASSWORD)->GetWindowText(csPwd);
	if (!csIP.IsEmpty() && !csPort.IsEmpty() && !csUName.IsEmpty() && !csPwd.IsEmpty())
	{
		BOOL b = m_DVRPlayer.Login(csUName, csPwd, csIP, _ttoi(csPort));
		if(b)
		{
			csLoginInfo = _T("登录服务器成功！");
			m_Settings.m_csMediaServerIP = csIP;
			m_Settings.m_lPort = csPort;
			m_Settings.m_csUsername = csUName;
			m_Settings.m_csPassword = csPwd;
			m_Settings.Save();
		}
		else
			csLoginInfo = _T("登录服务器失败！");
		GetDlgItem(IDC_STATIC_LOINGINFO)->SetWindowText(csLoginInfo);
	}
}


void CDVRUI_MFCDlg::OnBnClickedButtonStartMonitor()
{
	CString csWndNum;
	CWnd* pWnd = GetDlgItem(IDC_COMBO_SPILTMODEL);
	pWnd->GetWindowText(csWndNum);
	if (csWndNum.IsEmpty())
		m_Settings.m_nRenderWndNum = 1;
	else
		m_Settings.m_nRenderWndNum = _ttoi(csWndNum);
	m_DVRPlayer.StartMonitor(m_Settings.m_nRenderWndNum);
	SetChannelState();
	SetFileState(false);
}


void CDVRUI_MFCDlg::OnBnClickedButtonStopMonitor()
{
	m_DVRPlayer.StopMonitor();
}


void CDVRUI_MFCDlg::OnBnClickedButtonChannel()
{
	CComboBox* pWndComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_WIND_NUMBER);
	CComboBox* pChannelComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_CHANNEL);
	if (pWndComboBox && 
		pWndComboBox->GetCurSel() != CB_ERR	&& 
		pChannelComboBox &&
		pChannelComboBox->GetCurSel() != CB_ERR)
	{
		CString csWndIndex, csChannelIndex;
		pWndComboBox->GetWindowText(csWndIndex);
		pChannelComboBox->GetWindowText(csChannelIndex);
		m_DVRPlayer.SetWndChannel(_ttoi(csWndIndex), _ttoi(csChannelIndex));
	}
	SetFileState(false);
}


void CDVRUI_MFCDlg::SetChannelState()
{
	CComboBox* pWndComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_WIND_NUMBER);
	
	pWndComboBox->ResetContent();

	for (int i = 0; i < m_Settings.m_nRenderWndNum; ++i)
	{
		CString csNum;
		csNum.Format(_T("%d"), i);
		pWndComboBox->AddString(csNum);
	}
}


void CDVRUI_MFCDlg::OnBnClickedButtonStartPlayback()
{
	time_t start_long_time;
	time_t stop_long_time; 

	CDateTimeCtrl* pStartDate = (CDateTimeCtrl*)GetDlgItem(IDC_START_DATE);
	CDateTimeCtrl* pStartTime = (CDateTimeCtrl*)GetDlgItem(IDC_START_TIME);
	CDateTimeCtrl* pEndDate = (CDateTimeCtrl*)GetDlgItem(IDC_END_DATE);
	CDateTimeCtrl* pEndTime = (CDateTimeCtrl*)GetDlgItem(IDC_END_TIME);

	CComboBox* pChangeChannelComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_CHANGE_CHANNEL);

	CTime start_time, stop_time;
	CTime start_date, stop_date;

	pStartDate->GetTime(start_date);

	pStartTime->GetTime(start_time);

	CTime startT(start_date.GetYear(), start_date.GetMonth(), start_date.GetDay(), start_time.GetHour(), start_time.GetMinute(), start_time.GetSecond()); 

	start_long_time = startT.GetTime();

	pEndDate->GetTime(stop_date);

	pEndTime->GetTime(stop_time);

	CTime stopT(stop_date.GetYear(), stop_date.GetMonth(), stop_date.GetDay(), stop_time.GetHour(), stop_time.GetMinute(), stop_time.GetSecond()); 

	stop_long_time = stopT.GetTime();

	CString csChannel;
	if (pChangeChannelComboBox && 
		pChangeChannelComboBox->GetCurSel() != CB_ERR)
	{
		pChangeChannelComboBox->GetWindowText(csChannel);;
	}
	if(csChannel.IsEmpty())
		csChannel = "0";
	m_DVRPlayer.StartPlayback(start_long_time, stop_long_time, _ttoi(csChannel));
	KillTimer(PLAY_FILE_TIMER);
	CString csMsg;
	csMsg.Format(_T(""));
	GetDlgItem(IDC_PLAYTIME)->SetWindowText(csMsg);
	SetFileState(false);
}


void CDVRUI_MFCDlg::OnBnClickedButtonStopPlayback()
{
	m_DVRPlayer.StopPlayback();
}


void CDVRUI_MFCDlg::InitServerInfoBox()
{
	GetDlgItem(IDC_IPADDRESS_SERVERIP)->SetWindowText(m_Settings.m_csMediaServerIP);
	GetDlgItem(IDC_EDIT_SERVERPORT)->SetWindowText(m_Settings.m_lPort);
	GetDlgItem(IDC_EDIT_USERNAME)->SetWindowText(m_Settings.m_csUsername);
	GetDlgItem(IDC_EDIT_PASSWORD)->SetWindowText(m_Settings.m_csPassword);
}


void CDVRUI_MFCDlg::OnBnClickedButtonVsPlayPause()
{
	if(m_Pause)
	{
		m_DVRPlayer.pause();
		GetDlgItem(IDC_BUTTON_VS_PLAY_PAUSE)->SetWindowTextW(_T("播放"));
		m_Pause = false;
		GetDlgItem(IDC_BUTTON_VS_FORWARD)->EnableWindow(false);
		GetDlgItem(IDC_BUTTON_VS_REVERSE)->EnableWindow(false);
		GetDlgItem(IDC_SLIDER_PLAY_CONTROL)->EnableWindow(false);
	}
	else
	{
		m_DVRPlayer.play();
		GetDlgItem(IDC_BUTTON_VS_PLAY_PAUSE)->SetWindowTextW(_T("暂停"));
		m_Pause = true;
		GetDlgItem(IDC_BUTTON_VS_FORWARD)->EnableWindow(true);
		GetDlgItem(IDC_BUTTON_VS_REVERSE)->EnableWindow(true);
		GetDlgItem(IDC_SLIDER_PLAY_CONTROL)->EnableWindow(true);
	}
}


void CDVRUI_MFCDlg::OnBnClickedButtonVsStop()
{
	m_DVRPlayer.stop();
	GetDlgItem(IDC_BUTTON_VS_PLAY_PAUSE)->SetWindowTextW(_T("播放"));
	m_Pause = false;
	GetDlgItem(IDC_BUTTON_VS_FORWARD)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_VS_REVERSE)->EnableWindow(false);
	GetDlgItem(IDC_SLIDER_PLAY_CONTROL)->EnableWindow(false);
}


void CDVRUI_MFCDlg::OnBnClickedButtonVsReverse()
{
	clickCount--;
	m_DVRPlayer.fastReverse();
	GetDlgItem(IDC_BUTTON_VS_PLAY_PAUSE)->SetWindowTextW(_T("播放"));
	m_Pause = false;
	if(clickCount >= 4)
	{
		GetDlgItem(IDC_BUTTON_VS_REVERSE)->EnableWindow(false);
	}
	else
		GetDlgItem(IDC_BUTTON_VS_FORWARD)->EnableWindow(true);
}


void CDVRUI_MFCDlg::OnBnClickedButtonVsForward()
{
	clickCount++;
	m_DVRPlayer.fastForward();
	GetDlgItem(IDC_BUTTON_VS_PLAY_PAUSE)->SetWindowTextW(_T("播放"));
	m_Pause = false;
	if(clickCount >= 4)
	{
		GetDlgItem(IDC_BUTTON_VS_FORWARD)->EnableWindow(false);
	}
	else
		GetDlgItem(IDC_BUTTON_VS_REVERSE)->EnableWindow(true);
}

void CDVRUI_MFCDlg::SetFileState(bool b)
{
	GetDlgItem(IDC_BUTTON_VS_PLAY_PAUSE)->EnableWindow(b);
	GetDlgItem(IDC_BUTTON_VS_STOP)->EnableWindow(b);
	GetDlgItem(IDC_BUTTON_VS_REVERSE)->EnableWindow(b);
	GetDlgItem(IDC_BUTTON_VS_FORWARD)->EnableWindow(b);	
	GetDlgItem(IDC_SLIDER_PLAY_CONTROL)->EnableWindow(b);
	GetDlgItem(IDC_COMBO_WIND_NUMBER)->EnableWindow(!b);
	GetDlgItem(IDC_COMBO_CHANNEL)->EnableWindow(!b);
	GetDlgItem(IDC_BUTTON_CHANNEL)->EnableWindow(!b);
}

HBRUSH CDVRUI_MFCDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if(GetDlgItem(IDC_STATIC_LOINGINFO)->m_hWnd == pWnd->m_hWnd)
	{
		pDC->SetTextColor(RGB(255,0,0)); 
	}
	return hbr;
}

void CDVRUI_MFCDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CSliderCtrl   *pSlidCtrl=(CSliderCtrl*)GetDlgItem(IDC_SLIDER_PLAY_CONTROL);  
   
	int m_nCur=pSlidCtrl->GetPos();//取得当前位置值

	float pos = m_nCur / 100.00f;

	m_DVRPlayer.SetPosition(pos);
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CDVRUI_MFCDlg::OnTimer(UINT_PTR nIDEvent)
{
	switch(nIDEvent)
    {
      case PLAY_FILE_TIMER:
      {   
          CString csMsg;
		  csMsg.Format(_T("%s/%s"), m_DVRPlayer.get_currentPositionString(), m_DVRPlayer.get_durationString());
		  GetDlgItem(IDC_PLAYTIME)->SetWindowText(csMsg);

		  int currentPosition = m_DVRPlayer.get_currentPosition();
		  int pos = currentPosition / m_Duration * 100;
		  pSlidCtrl->SetPos(pos);
          break;
      }
      default:
		  KillTimer(nIDEvent);
          break;
    } 

	CDialog::OnTimer(nIDEvent);
}
