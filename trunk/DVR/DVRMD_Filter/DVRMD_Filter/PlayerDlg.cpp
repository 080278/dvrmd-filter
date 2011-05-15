////////////////////////////////////////////////////////////////////////////////
//File:PlayerDlg.cpp 
/////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "PlayerDlg.h"
#include "Player.h"
#include "vkey.h"
#include "CConvertAVI.h"
#include "watermarkinfo.h"
#include <stdio.h>

#define GET_YEAR(_time_)      (((_time_)>>26) + 2000) 
#define GET_MONTH(_time_)     (((_time_)>>22) & 15)   
#define GET_DAY(_time_)       (((_time_)>>17) & 31)   
#define GET_HOUR(_time_)      (((_time_)>>12) & 31)   
#define GET_MINUTE(_time_)    (((_time_)>>6)  & 63)
#define GET_SECOND(_time_)    (((_time_)>>0)  & 63)   
void RunInfo(TCHAR *szFormat, ...)
{	
	TCHAR szInfo[512];
	va_list	ArgumentList;

	va_start(ArgumentList, szFormat); 
	_vstprintf(szInfo, szFormat, ArgumentList);
	va_end(ArgumentList);
	OutputDebugString(szInfo);
}

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// class used to convert file to avi
//CConvertAVI g_classAVI;

/************************************************************************/				

UINT	PLAY_TIMER			= 1;			 // TIMER ID;
//UINT	m_lPort				= 0;			 // uesed port;can be from 0 to 15;
/************************************************************************/

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
/////////////////////////////////////////////////////////////////////////////
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
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	// display the version information
	CString strVer;

	DWORD dwVer	   = NAME(PlayM4_GetSdkVersion)();
	DWORD dwVersion = dwVer & 0x0000ffff;
	DWORD dwBuild   = (dwVer >> 16) & 0x0000ffff;
#ifdef _FOR_HIKPLAYM4_DLL_
	strVer.Format(_T("HikPlayer ver is %.1f\n\rHikPlayM4.dll ver is %04x build is %04x"), APP_VERSION, dwVersion, dwBuild);
#else
	strVer.Format(_T("Player ver is %.1f\n\rPlayM4.dll ver is %04x build is %04x"), APP_VERSION, dwVersion, dwBuild);
#endif
	GetDlgItem(IDC_VER)->SetWindowText(strVer);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlayerDlg dialog

CPlayerDlg::CPlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPlayerDlg::IDD, pParent)
	, m_DVRSettingsPage1(GetPlayer())
	, m_DVRSettingsPage2(this)
	, m_DVRSettingsPage3(GetPlayer())
	, m_DVRSettingsPage4(this)
{
	//{{AFX_DATA_INIT(CPlayerDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon	                  =	AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bInited				  = FALSE;
}

void CPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPlayerDlg)
	DDX_Control(pDX, IDC_CAPPIC, m_ctrlBtnCapPic);
	DDX_Control(pDX, IDC_SOUND, m_ctrlBtnSound);
	DDX_Control(pDX, IDC_STEPBACK, m_ctrlStepBackward);
	DDX_Control(pDX, IDC_STEP, m_ctrlStepForward);
	DDX_Control(pDX, IDC_SLOW, m_ctrlBtnSlow);
	DDX_Control(pDX, IDC_FAST, m_ctrlBtnFast);
	DDX_Control(pDX, IDC_GOTOSTART, m_ctrlBtnGStart);
	DDX_Control(pDX, IDC_GOTOEND, m_ctrlBtnGEnd);
	DDX_Control(pDX, IDC_STOP, m_ctrlBtnStop);
	DDX_Control(pDX, IDC_PLAY, m_ctrlBtnPlay);
	DDX_Control(pDX, IDC_PAUSE, m_ctrlBtnPause);
	DDX_Control(pDX, IDC_SHOW, m_ctrlVideoPic);
	DDX_Control(pDX, IDC_SOUND_SLIDER, m_SoundSlider);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPlayerDlg, CDialog)
	//{{AFX_MSG_MAP(CPlayerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_KEYDOWN()
	ON_WM_HSCROLL()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_WM_DROPFILES()
	ON_WM_MOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_GETMINMAXINFO()
	ON_WM_DESTROY()
	ON_WM_WINDOWPOSCHANGED()
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(IDM_VIEW_FULLSCREEN, IDM_BYTIME, OnMenuItem)
	ON_COMMAND_RANGE(IDC_PLAY, IDC_SOUND, OnButtonItem)
	ON_MESSAGE(WM_FILE_END, PlayMessage)
	ON_MESSAGE(WM_ENC_CHANGE,EncChangeMessage)
	ON_BN_CLICKED(IDC_OPENFILE, OnBnClickedOpenfile)
	ON_BN_CLICKED(IDC_SHOWHIDE_SETTINGS, OnBnClickedShowHideSettings)

	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_RENDER_MODE, &CPlayerDlg::OnClickedRenderMode)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlayerDlg message handlers

BOOL CPlayerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_CtrlPanel.Create(IDD_CTRL_PANEL, this);

	m_pOldParentWnd = NULL;
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_dwScreenWidth  = GetSystemMetrics(SM_CXSCREEN);
	m_dwScreenHeight = GetSystemMetrics(SM_CYSCREEN);

	m_rcScreen.left  = 0;
	m_rcScreen.right = m_dwScreenWidth;
	m_rcScreen.top   = 0;
	m_rcScreen.bottom= m_dwScreenHeight;


	// Init Play Slider
	VERIFY(m_PlaySlider.CreateFromStatic(
		SBS_HORZ|WS_CHILD|SS_LEFT|SS_NOTIFY|WS_VISIBLE,
		this, IDC_PLAY_RECT_SLIDER, IDC_PLAY_SLIDER));

	m_PlaySlider.SetScrollRange(0, PLAYER_SLIDER_MAX);
	m_PlaySlider.EnableThumbColor(FALSE);
	m_PlaySlider.EnableThumbGripper(TRUE);
	m_PlaySlider.EnableChannelColor(FALSE);

	// Init Sound Slider
#ifdef _WAVE_ADJ
	m_SoundSlider.SetRangeMin(MIN_WAVE_COEF);
	m_SoundSlider.SetRangeMax(MAX_WAVE_COEF);
#else
	m_SoundSlider.SetRangeMin(0);
	m_SoundSlider.SetRangeMax(0xffff-1);
#endif

	m_SoundSlider.SetLineSize(1);
	m_SoundSlider.SetPageSize(5);

	// 	

	// Init the parameters
	m_StartPoint.x		 =	0;
	m_StartPoint.y		 =	0;
	m_dwTotalFrames		 =	0;
	m_dwDisplayHour		 =	0;
	m_dwDisplayMinute	 =	0;
	m_dwDisplaySecond	 =	0;
//	m_dwImageSharpenLevel=  0;
	m_nPrePlayPos		 =  0;
	m_dwOldDeviceNum     =  0;

	m_npic_bmp			 =	0;
	m_npic_jpeg			 =	0;
	m_nCapPicType		 =	0;
	m_strCapPicPath		 =  _T("");

	m_bStartDraw         =	FALSE;
	m_bSound			 =	FALSE;
	m_bOpen			     =	FALSE;
	m_bFullScreen		 =	FALSE;
	m_bRepeatPlay		 =	FALSE;
	m_bStreamType		 =	FALSE;
	m_bConvertAVI		 =  FALSE;
	m_bPicQuality	     =  TRUE;
	m_bDeflash			 =  TRUE;
//#ifdef _HIGH_FRUID
//	m_bHighFluid		 =  TRUE;
//#else
//	m_bHighFluid		 =  FALSE;
//#endif

	//m_ctrlPlayText.ShowText(m_strPlayStateText);

	m_pQcifTempBuf		 =  NULL;

	// Init state text control
	//m_ctrlPlayText.SetTextColor(RGB(255,255,255), FALSE);
	//m_ctrlPlayText.SetBackgroundColor(RGB(0,0,0), FALSE);
	//m_ctrlPlayText.SetBold(TRUE, FALSE);

	//GetPlayer()->GetDVRSettings().m_nRenderWidth	= 352;
	//GetPlayer()->GetDVRSettings().m_nRenderWidth   = 288;

	RECT rcPos;
	m_ctrlVideoPic.GetWindowRect(&rcPos);
	rcPos.right = rcPos.left + GetPlayer()->GetDVRSettings().m_nRenderWidth;
	rcPos.bottom = rcPos.top + GetPlayer()->GetDVRSettings().m_nRenderHeight;
	InitWindowSize();
	GetPlayer()->Init(m_ctrlVideoPic.GetSafeHwnd(), &rcPos, m_hWnd); 
	// init the sub dialogs

	// bitmap
	m_BlackBmp.LoadBitmap(IDB_BLACK);
	m_OverlayBmp.LoadBitmap(IDB_OVERLAY);
	SetWindowText(_T("Player"));

	SetState();

	UpdateData(FALSE);
	SortControl();

	m_bInited = TRUE;

	m_DVRSettingsSheet.SetTitle(_T("DVR 配置"));

	m_DVRSettingsSheet.AddPage(&m_DVRSettingsPage1);
	m_DVRSettingsSheet.AddPage(&m_DVRSettingsPage2);
	m_DVRSettingsSheet.AddPage(&m_DVRSettingsPage3);
	m_DVRSettingsSheet.AddPage(&m_DVRSettingsPage4);

	m_DVRSettingsSheet.Create(this);

	//::SetWindowLong(m_DVRSettingsSheet.m_hWnd, GWL_STYLE, WS_VISIBLE);//GetWindowLong(m_DVRSettingsSheet.m_hWnd, GWL_STYLE) - WS_CAPTION);

	RECT rcSheet; 
	GetDlgItem(IDC_SHEET_POS)->GetWindowRect(&rcSheet);
	////ClientToScreen(&rcSheet);
	ScreenToClient(&rcSheet);
	m_DVRSettingsSheet.SetWindowPos(NULL, rcSheet.left, rcSheet.top, 0, 0, SWP_NOZORDER | SWP_NOSIZE);

	m_DVRSettingsSheet.ShowWindow(SW_HIDE);

	//m_CtrlPanel.ShowWindow(SW_SHOW);
	//m_CtrlPanel.SetWindowPos(&CWnd::wndTopMost, 0, 0, GetPlayer()->GetDVRSettings().m_nRenderWidth, 100, SWP_SHOWWINDOW);

	return TRUE;  // return TRUE  unless you set the focus to a control
}


void CPlayerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		//CAboutDlg dlgAbout;
		//dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPlayerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		//	SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		//int cxIcon = GetSystemMetrics(SM_CXICON);
		//int cyIcon = GetSystemMetrics(SM_CYICON);
		//CRect rect;
		//GetClientRect(&rect);
		//int x = (rect.Width() - cxIcon + 1) / 2;
		//int y = (rect.Height() - cyIcon + 1) / 2;

		//// Draw the icon
		//dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
	//UpdateWindow();
	//GetPlayer()->RefreshPlay();
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPlayerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//////////////////////////////////////////////////////////////////////////////
//Function: called when u drag a file to the playing window
//////////////////////////////////////////////////////////////////////////////
void CPlayerDlg::OnDropFiles(HDROP hDropInfo) 
{
	// TODO: Add your message handler code here and/or call default

	DWORD nFileNameSize = DragQueryFile(hDropInfo, 0, NULL, 0);
	TCHAR * sFileName	= new TCHAR[nFileNameSize + 1];
	DragQueryFile(hDropInfo, 0, sFileName, nFileNameSize + 1);

	Open();
	SetState();

	delete []sFileName;
	CDialog::OnDropFiles(hDropInfo);
}


//////////////////////////////////////////////////////////////////////////////
//Function: overload to handle keydown message
//////////////////////////////////////////////////////////////////////////////
BOOL CPlayerDlg::PreTranslateMessage(MSG* lpmsg)
{

	switch (lpmsg->message)
	{
	case WM_KEYDOWN:
		OnKeyDown(lpmsg->wParam, LOWORD(lpmsg ->lParam), HIWORD(lpmsg->lParam));
		return TRUE;

	default:
		break;
	} 

	return CDialog::PreTranslateMessage(lpmsg); 
}


//////////////////////////////////////////////////////////////////////////////
//Function: hot key
//////////////////////////////////////////////////////////////////////////////
void CPlayerDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	TRACE(_T("OnKeyDown"));
	if(nChar == VK_F2) 
		ViewFullScreen();
	else if (nChar == VK_ESCAPE && this->m_bFullScreen)
	{
		ViewFullScreen();
	}

	if(GetKeyState(VK_CONTROL) & 0xFF00)
	{
		switch(nChar)
		{
		case VK_C:
			if(!m_bFullScreen)
			{
				//nMenuState = //m_pMainMenu->GetMenuState(IDM_FILE_CLOSE, MF_BYCOMMAND);
				//if(nMenuState != MF_GRAYED)
				{
					Close();
					SetState();
				}
			}
			break;

		case VK_O:
			if(!m_bFullScreen)
			{
				//nMenuState = //m_pMainMenu->GetMenuState(IDM_FILE_OPEN, MF_BYCOMMAND);
				//if(nMenuState != MF_GRAYED)		
				{
					CString csFile;
					if(BrowseFile(&csFile))
					{
						Open(csFile);
						SetState();
					}
				}
			}
			break;

		case VK_LEFT:
			m_DVRPlayer.GotoStart();
			break;

		case VK_RIGHT:
			m_DVRPlayer.GotoEnd();
			break;

		case VK_ONE:
			if(m_DVRPlayer.GetPlayState() != CDVRPlayer::eState_Stop)
			{
				ViewZoom(IDM_VIEW_ZOOM_50);
			}
			break;

		case VK_TWO:
			if(m_DVRPlayer.GetPlayState() != CDVRPlayer::eState_Stop)
			{
				ViewZoom(IDM_VIEW_ZOOM_100);
			}
			break;

		case VK_THREE:
			if(m_DVRPlayer.GetPlayState() != CDVRPlayer::eState_Stop)
			{
				ViewZoom(IDM_VIEW_ZOOM_200);
			}
			break;

		default:
			break;
		}
	}

	else
	{
		switch(nChar)
		{
		case VK_ESCAPE:
			if(m_bFullScreen)
			{
				ViewFullScreen();
			}
			break;

		case VK_SPACE:
			if(m_DVRPlayer.GetPlayState() == CDVRPlayer::eState_Play)
			{
				Pause();
				SetState();
			}
			else if(m_DVRPlayer.GetPlayState() == CDVRPlayer::eState_Pause || m_DVRPlayer.GetPlayState() == CDVRPlayer::eState_Stop)
			{
				Play();
				SetState();
			}
			break;

		case VK_LEFT:
			if(m_DVRPlayer.GetPlayState() != CDVRPlayer::eState_Stop)
			{
				StepBackward();
				SetState();
			}
			break;

		case VK_RIGHT:
			if(m_DVRPlayer.GetPlayState() != CDVRPlayer::eState_Stop)
			{
				StepForward();
				SetState();
			}
			break;

		case VK_UP:
			//m_DVRPlayer.AdjustSound(TRUE);
			break;

		case VK_DOWN:
			//m_DVRPlayer.AdjustSound(FALSE);
			break;

		case VK_DOT:
			if(m_DVRPlayer.GetPlayState() != CDVRPlayer::eState_Close)
			{
				if(m_bFullScreen)
				{
					ViewFullScreen();
				}

				Stop();
				SetState();
			}
			break;

		default:
			break;
		}
	}

	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

///////////////////////////////////////////////////////////////////////////
//Function: Voluem and progress.
///////////////////////////////////////////////////////////////////////////
void CPlayerDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	DWORD nTime;
	int   nPlayPos;
	switch(GetWindowLong(pScrollBar->m_hWnd, GWL_ID))
	{
		/////////////////////////////////////////////////////////////////
		//progress slider
	case IDC_PLAY_SLIDER:
		if(m_bStreamType)
		{
			break;
		}
		nPlayPos = m_PlaySlider.GetScrollPos();
		if( abs(nPlayPos - m_nPrePlayPos) < 3 )
		{
			break;
		}

#ifdef _FILE_POS
		GetPlayer()->SetPosition((float)nPlayPos/(float)PLAYER_SLIDER_MAX);
		//NAME(PlayM4_SetPlayPos)(m_lPort, );
#else
		nTime = nPlayPos * 1000 / PLAYER_SLIDER_MAX * GetPlayer()->GetDuration();
		//NAME(PlayM4_SetPlayedTimeEx)(m_lPort,nTime);
		GetPlayer()->SetPosition(nTime);
#endif
		//		DrawStatus();
		break;

		///////////////////////////////////////////////////////////////
		//sound slider;
	case IDC_SOUND_SLIDER:
//#ifdef _WAVE_ADJ
//		NAME(PlayM4_AdjustWaveAudio)(m_lPort, m_SoundSlider.GetPos());
//#else
		GetPlayer()->SetVolume( WORD(m_SoundSlider.GetPos()));
		////NAME(PlayM4_SetVolume)(m_lPort, WORD(m_SoundSlider.GetPos()));
//#endif
		break;

	default:
		break;
	}

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

/////////////////////////////////////////////////////////////////////
//Called when u double click the left button
/////////////////////////////////////////////////////////////////////
void CPlayerDlg::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CPoint dpoint;
	CRect  vwrect;
	GetCursorPos(&dpoint);	

	m_ctrlVideoPic.GetWindowRect(&vwrect);
	if( ( m_DVRPlayer.GetPlayState() == CDVRPlayer::eState_Play || m_DVRPlayer.GetPlayState() == CDVRPlayer::eState_Pause))
	{
		TRACE(_T("DoubleClick"));
		ViewFullScreen();
	}

	CDialog::OnLButtonDblClk(nFlags, point);
}


/////////////////////////////////////////////////////////////////////
//Timer funtion
/////////////////////////////////////////////////////////////////////
void CPlayerDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent==PLAY_TIMER)
	{
		DrawStatus();
	}
	CDialog::OnTimer(nIDEvent);
}




/////////////////////////////////////////////////////////////////////
//Adjust control allign function
/////////////////////////////////////////////////////////////////////
void CPlayerDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	// TODO: Add your message handler code here
	TRACE(_T("OnSize"));
	//if(m_ctrlVideoPic.GetSafeHwnd())
	//{
	//	//SortControl();
	//}
}


/////////////////////////////////////////////////////////////////////
// Function: Limit the window size.
/////////////////////////////////////////////////////////////////////
void CPlayerDlg::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	// TODO: Add your message handler code here and/or call default
	//lpMMI->ptMinTrackSize.x = WIDTH/2 + m_dwDlgEdge * 2;				// width
	//lpMMI->ptMinTrackSize.y = PANNEL_HEIGHT + m_dwDlgTopSize ;			// height

	CDialog::OnGetMinMaxInfo(lpMMI);
}


///////////////////////////////////////////////////////////////////////////
//Function:Redraw the image when move window.
///////////////////////////////////////////////////////////////////////////
void CPlayerDlg::OnMove(int x, int y) 
{
	CDialog::OnMove(x, y);

	if (::IsWindow(m_DVRSettingsSheet.m_hWnd) && m_DVRSettingsSheet.IsWindowVisible())
	{
		RECT rcSheet;
		GetDlgItem(IDC_SHEET_POS)->GetWindowRect(&rcSheet);
		m_DVRSettingsSheet.MoveWindow(&rcSheet);
	}

	if (!m_bInited)
	{
		return;
	}
	TRACE(_T("OnMove"));
	// TODO: Add your message handler code here
	//NAME(PlayM4_RefreshPlay)(m_lPort);
	GetPlayer()->RefreshPlay();

	GetWindowRect(&m_rcWindow);
	DWORD dwNewDeviceNum;

	if(m_rcWindow.left < 0)
	{
		return;
	}

	if( (DWORD)m_rcWindow.right + (DWORD)m_rcWindow.left > 2 * m_dwScreenWidth )
	{
		if( (DWORD)m_rcWindow.top + (DWORD)m_rcWindow.bottom > 2 * m_dwScreenHeight)
		{
			dwNewDeviceNum = 3;
			m_rcScreen.left  = m_dwScreenWidth;
			m_rcScreen.right = m_dwScreenWidth  * 2;
			m_rcScreen.top   = m_dwScreenHeight;
			m_rcScreen.bottom= m_dwScreenHeight * 2;
		}
		else
		{
			dwNewDeviceNum = 1;
			m_rcScreen.left  = m_dwScreenWidth;
			m_rcScreen.right = m_dwScreenWidth  * 2;
			m_rcScreen.top   = 0;
			m_rcScreen.bottom= m_dwScreenHeight;
		}
	}
	else
	{
		if( (DWORD)m_rcWindow.top + (DWORD)m_rcWindow.bottom > 2 * m_dwScreenHeight)
		{
			dwNewDeviceNum = 2;
			m_rcScreen.left  = 0;
			m_rcScreen.right = m_dwScreenWidth;
			m_rcScreen.top   = m_dwScreenHeight;
			m_rcScreen.bottom= m_dwScreenHeight * 2;
		}
		else
		{
			dwNewDeviceNum = 0;
			m_rcScreen.left  = 0;
			m_rcScreen.right = m_dwScreenWidth;
			m_rcScreen.top   = 0;
			m_rcScreen.bottom= m_dwScreenHeight;
		}
	}

	//if(dwNewDeviceNum != m_dwOldDeviceNum)
	//{
	//	//if(SetDevice(IDM_DEVICE0 + dwNewDeviceNum))
	//	{
	//		m_dwOldDeviceNum = dwNewDeviceNum;
	//	}
	//}
}



///////////////////////////////////////////////////////////////////////////
//Function: Called when u click the left mouse button
///////////////////////////////////////////////////////////////////////////
void CPlayerDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//	CRect rcShow;
	//	m_ctrlVideoPic.GetWindowRect(rcShow);
	//	ScreenToClient(rcShow);
	//
	//	if(rcShow.PtInRect(point))
	//	{
	//		m_StartPoint = point;
	//		m_bStartDraw = TRUE;
	//		InvalidateRect(m_rcDraw, TRUE);
	//		ZeroMemory(&m_rcDraw, sizeof(m_rcDraw));
	//	}

	CDialog::OnLButtonDown(nFlags, point);
}

void CPlayerDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//	if(m_bStartDraw)
	//	{
	//		if(m_StartPoint != point)
	//		{
	//
	//			CRect rcShow;
	//			m_ctrlVideoPic.GetWindowRect(rcShow);
	//			ScreenToClient(rcShow);
	//			
	//			if( rcShow.PtInRect(point) && (point.x >= m_StartPoint.x) && (point.y >= m_StartPoint.y))
	//			{
	//				m_rcDraw.left   = m_StartPoint.x;
	//				m_rcDraw.top    = m_StartPoint.y;
	//				m_rcDraw.right  = point.x;
	//				m_rcDraw.bottom = point.y;
	//				
	//				CDC* pDC = GetDC();
	//				pDC->DrawFocusRect(m_rcDraw);
	//				ReleaseDC(pDC);
	//			
	//				LONG nPicWidth  = 352;
	//				LONG nPicHeight = 288;
	//				NAME(PlayM4_GetPictureSize)(m_lPort, &nPicWidth, &nPicHeight);
	//				m_rcDisplay = GetOnPicRect(rcShow, m_rcDraw, nPicWidth, nPicHeight);
	//
	//				if(m_pDisplayRegion->m_hWnd)
	//					m_pDisplayRegion->PostMessage(WM_DISPLAY_RECT, 0, (long)(&m_rcDisplay));
	//			}
	//
	//		}
	//		m_bStartDraw = FALSE;
	//	}

	CDialog::OnLButtonUp(nFlags, point);
}


//////////////////////////////////////////////////////////////////////
//Function: Close.
//////////////////////////////////////////////////////////////////////
void CPlayerDlg::OnClose() 
{
	CDialog::OnClose();
}


/*************************************************************************/
/*************************************************************************/
/*************************************************************************/
/*  user defined message handle begin
/*************************************************************************/
/*************************************************************************/
/*************************************************************************/

// Function: process the received WM_FILE_END message.
// Para: wParam channel No. lParam reserved；
LRESULT CPlayerDlg::PlayMessage(WPARAM /*wParam*/, LPARAM lParam)
{
	//	if(m_bFullScreen)
	//		ViewFullScreen();

	//remove the same message.
	MSG msgVal;
	while(PeekMessage(&msgVal, m_hWnd, WM_FILE_END, WM_FILE_END, PM_REMOVE));

	if(m_bRepeatPlay)
	{
		TRACE(_T("wptest:Process message %d\n"), lParam);
		m_DVRPlayer.GotoStart();
	}

	if(m_bConvertAVI)
	{  
		Stop();
		SetState();
	}
	return 0;
}

// when enc changed got this message
LRESULT CPlayerDlg::EncChangeMessage(WPARAM /*wParam*/, LPARAM /*lParam*/)
{
	OutputDebugString(_T("Get Message/n!"));
	MSG msgVal;
	while(PeekMessage(&msgVal,m_hWnd,WM_ENC_CHANGE,WM_ENC_CHANGE,PM_REMOVE));

	if(m_bFullScreen)
	{
		ViewFullScreen();
	}

	SetWindowSize();

//	if(m_pDisplayRegion)
	//{
	//	if(m_pDisplayRegion->m_bValid)
	//	{
	//		m_pDisplayRegion->SetResolution(m_nHeight, m_nWidth);
	//		m_pDisplayRegion->InitShow();

	//		if(GetPlayer()->GetPlayState() == State_Pause)
	//		{
	//			StepForward();
	//			//NAME(PlayM4_OneByOne)(m_lPort);
	//		}
	//	}
	//}

	Sleep(1);
	return 0;
}

LRESULT CPlayerDlg::VideoCtrlOK(WPARAM /*wParam*/, LPARAM /*lParam*/)
{
	//m_pVideoControl->DestroyWindow();
	if(m_DVRPlayer.GetPlayState() == CDVRPlayer::eState_Pause || m_DVRPlayer.GetPlayState() == CDVRPlayer::eState_Play)
	{
		////m_pMainMenu->EnableMenuItem(IDM_VIDEO_CONTROL, MF_ENABLED);
	}
	return 0;
}

//
//// when u click the OK button on the display dialog, got this message
//LRESULT CPlayerDlg::DisplayOk(WPARAM wParam, LPARAM /*lParam*/)
//{
//	if (wParam == 0) 
//	{
//		m_ctrlBtnCapPic.EnableWindow(TRUE);
//		m_ctrlBtnSound.EnableWindow(TRUE);	
//		m_ctrlBtnSlow.EnableWindow(TRUE);
//		m_ctrlBtnFast.EnableWindow(TRUE);
//		m_ctrlBtnGStart.EnableWindow(TRUE);
//		m_ctrlBtnGEnd.EnableWindow(TRUE);
//		m_ctrlBtnStop.EnableWindow(TRUE);
//		m_ctrlBtnPlay.EnableWindow(TRUE);
//		m_ctrlBtnPause.EnableWindow(TRUE);	
//		m_ctrlStepBackward.EnableWindow(TRUE);
//		m_ctrlStepForward.EnableWindow(TRUE);
//		////m_pMainMenu->EnableMenuItem(2, MF_ENABLED|MF_BYPOSITION);
//		Play();
//		SetState();
//	}
//	if (wParam == 1) 
//	{
//		Pause();
//		SetState();
//	}
//	return 0;
//}
/*************************************************************************/
/*************************************************************************/
/*************************************************************************/
/*  user defined message handle over
/*************************************************************************/
/*************************************************************************/
/*************************************************************************/

void CALLBACK DecryptWatermark(LONG nPort, BYTE* pData, DWORD dwDataLen, DWORD dwUser)
{
	UNREFERENCED_PARAMETER(nPort);

	char* pBuf = (char*)pData;
	CDVRPlayer::m_strWaterMark.global_time = *(DWORD*)pBuf;
	pBuf += sizeof(DWORD);
	CDVRPlayer::m_strWaterMark.device_sn = *(DWORD*)pBuf;
	pBuf += sizeof(DWORD);
	for(int i = 0; i < 6; i ++)
	{
		CDVRPlayer::m_strWaterMark.mac_addr[i] = *(unsigned char*)pBuf;
		pBuf += sizeof(unsigned char);
	}

	CDVRPlayer::m_strWaterMark.device_type = *(unsigned char*)pBuf;
	pBuf += sizeof(unsigned char);
	CDVRPlayer::m_strWaterMark.device_info = *(unsigned char*)pBuf;
	pBuf += sizeof(unsigned char);
	CDVRPlayer::m_strWaterMark.channel_num = *(unsigned char*)pBuf;
	pBuf += sizeof(unsigned char);
}

// Functon:Watermark call back function.
void CALLBACK funCheckWatermark(long /*nPort*/, WATERMARK_INFO *pFrameType, DWORD /*nUser*/)
{
	//	CPlayerDlg* pOwner = (CPlayerDlg*)nUser;

	char* pBuf = (char*)pFrameType->pDataBuf;
	CDVRPlayer::m_strWaterMark.global_time = *(DWORD*)pBuf;
	pBuf += sizeof(DWORD);
	CDVRPlayer::m_strWaterMark.device_sn = *(DWORD*)pBuf;
	pBuf += sizeof(DWORD);
	for(int i = 0; i < 6; i ++)
	{
		CDVRPlayer::m_strWaterMark.mac_addr[i] = *(unsigned char*)pBuf;
		pBuf += sizeof(unsigned char);
	}

	CDVRPlayer::m_strWaterMark.device_type = *(unsigned char*)pBuf;
	pBuf += sizeof(unsigned char);
	CDVRPlayer::m_strWaterMark.device_info = *(unsigned char*)pBuf;
	pBuf += sizeof(unsigned char);
	CDVRPlayer::m_strWaterMark.channel_num = *(unsigned char*)pBuf;
	pBuf += sizeof(unsigned char);
}

/*************************************************************************/
/*************************************************************************/
/*************************************************************************/
/*  callback function begin
/*************************************************************************/
/*************************************************************************/
/*************************************************************************/	

// Function:The call back funtion for capture image!
void CALLBACK DisplayCBFun(long /*nPort*/,\
	char * pBuf,long /*nSize*/,\
	long /*nWidth*/,long /*nHeight*/,\
	long /*nStamp*/,long /*nType*/,long /*nReceaved*/)
{
	UNREFERENCED_PARAMETER(pBuf);
}

// Funtion:The source buffer call back funtion.
void CALLBACK SourceBufFun(long nPort,DWORD nBufSize,DWORD dwUser,void*pContext)
{
	UNREFERENCED_PARAMETER(pContext);

	CPlayerDlg* pOwner = (CPlayerDlg*)dwUser;

	if( (pOwner->GetPlayer()->GetPlayState() == CDVRPlayer::eState_Close) || (pOwner->GetPlayer()->GetPlayState() == CDVRPlayer::eState_Stop) )
	{
		return ;
	}
	NAME(PlayM4_ResetSourceBufFlag)(nPort);
	if(pOwner->m_bFileEnd)
	{

		PostMessage(pOwner->m_hWnd, WM_FILE_END, pOwner->GetPlayer()->GetPort(), 0);
		pOwner->m_bFileEnd = FALSE;
	}
	else
	{
		SetEvent(pOwner->GetPlayer()->m_hEventInput);
	}
}

// Functon:File reference call back function.
void CALLBACK FileRefDone(DWORD /*nReserved*/,DWORD nUser)
{
	CPlayerDlg* pOwner = (CPlayerDlg*)nUser;
	pOwner->GetPlayer()->CanStepBackword(true);
	//	pOwner->//m_pMainMenu->EnableMenuItem(IDM_CUT_FILE,MF_ENABLED);
	//pOwner->//m_pMainMenu->EnableMenuItem(IDM_SEEK,MF_ENABLED);
	TRACE(_T("File reference created!\n"));

	//	DWORD dwIndex = 0;
	//	NAME(PlayM4_GetRefValue)(m_lPort, NULL, &dwIndex);
	//	BYTE* pIndex = new BYTE[dwIndex];
	//	NAME(PlayM4_GetRefValue)(m_lPort, pIndex, &dwIndex);
	//	HANDLE hFile = CreateFile("D:\\new.idx", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	//	DWORD dw;
	//	WriteFile(hFile, pIndex, dwIndex, &dw, NULL);
}

// Functon:File Verify call back function.
/*
void CALLBACK VerifyFun(long nPort, FRAME_POS * pFilePos, DWORD bIsVideo,  DWORD nUser)
{
//	TRACE(_T("File have been changed at: pos = 0x%X; time(s) = %d, frameNum = %d; IsVideo = %d\n",
//		pFilePos->nFilePos, pFilePos->nFrameTime/1000, pFilePos->nFrameNum, bIsVideo);
CString abstime;
CString str;
if (pFilePos->pErrorTime )
{
abstime.Format(_T("%02d-%02d-%02d %02d:%02d:%02d",pFilePos->pErrorTime->wYear, pFilePos->pErrorTime->wMonth,
pFilePos->pErrorTime->wDay, pFilePos->pErrorTime->wHour, pFilePos->pErrorTime->wMinute, pFilePos->pErrorTime->wSecond);
}
str.Format(_T("file error at pos=0x%X, time(s) =%d,frameNum=%d,isVideo=%d, \
errorframe at%d,lostframe=%d,lostdata=%d,time=%s\n",	\
pFilePos->nFilePos, pFilePos->nFrameTime/1000, pFilePos->nFrameNum, bIsVideo,	\
pFilePos->nErrorFrameNum, pFilePos->nErrorLostFrameNum, pFilePos->nErrorFrameSize, abstime);
TRACE(str); 
}
*/

// Functon:Wave data call back function.
void CALLBACK WaveCBFun(long /*nPort*/, char * pAudioBuf, long /*nSize*/, long /*nStamp*/, long /*nType*/, long /*nUser*/)
{
	UNREFERENCED_PARAMETER(pAudioBuf);
	//TRACE(_T("Wave data, nPort = %d, nSize = %d, nStamp = %d, nType = %d\n", nPort, nSize, nStamp, nType);
}
/*************************************************************************/
/*************************************************************************/
/*************************************************************************/
/*  callback function begin
/*************************************************************************/
/*************************************************************************/
/*************************************************************************/

void CALLBACK EncChange(LONG lPort, LONG dwUser)
{
	CPlayerDlg* pOwner = (CPlayerDlg*)dwUser;
	pOwner->SetWindowSize();
}

///////////////////////////////////////////////////////////////////////
// Function: input stream thread.
////////////////////////////////////////////////////////////////////////
#define BUF_SIZE 3008
DWORD WINAPI InputStreamThread( LPVOID lpParameter)
{
	//CPlayerDlg* pOwner = (CPlayerDlg*)lpParameter;
	CDVRPlayer* pThis = (CDVRPlayer*)lpParameter;
	HANDLE hMulEvents[2];
	hMulEvents[0] = pThis->m_hEventKill;
	hMulEvents[1] = pThis->m_hEventInput;
	BYTE pBuf[BUF_SIZE];
	DWORD nRealRead;
	BOOL bBufFull = FALSE;
	DWORD dwSize = BUF_SIZE;
	unsigned char chType;
	DWORD	dwDataLen = 0;

	while (WAIT_OBJECT_0 != WaitForMultipleObjects(2, hMulEvents, FALSE, INFINITE))
	{	
		if(!bBufFull)
		{
			// TRACE(_T("Read file and put it input into the stream buffer.\n");
			if(TRUE)//pOwner->m_dwSysFormat != SYSTEM_RTP)
			{
				if(!(ReadFile(pThis->m_hStreamFile, pBuf, dwSize, &nRealRead, NULL) && (nRealRead == dwSize)))
				{
					//File end;
					//pOwner->m_bFileEnd = TRUE;
					bBufFull = FALSE;
					ResetEvent(pThis->m_hEventInput);
				}
				dwDataLen = nRealRead;
			}
			else
			{
				//先读出4字节rtp包长

				if (!(ReadFile(pThis->m_hStreamFile, pBuf, 4, &nRealRead, NULL) && (nRealRead == 4)))
				{
					//File end;
					//pOwner->m_bFileEnd = TRUE;
					bBufFull = FALSE;
					ResetEvent(pThis->m_hEventInput);
				}

				dwSize = pBuf[0] + (pBuf[1] << 8) + (pBuf[2] << 16) + (pBuf[3] << 24);

				if (!(ReadFile(pThis->m_hStreamFile, pBuf, dwSize, &nRealRead, NULL) && (nRealRead == dwSize)))
				{
					//File end;
					//pOwner->m_bFileEnd = TRUE;
					bBufFull = FALSE;
					ResetEvent(pThis->m_hEventInput);
				}

				dwDataLen = nRealRead;
			}

			while ( !NAME(PlayM4_InputData)(pThis->GetPort(), pBuf, dwDataLen) )
			{
				if ( PlayM4_GetLastError(pThis->GetPort()) == PLAYM4_BUF_OVER )
				{
					Sleep(10);
					continue;
				}

				bBufFull = TRUE;
				ResetEvent(pThis->m_hEventInput);
				break;
			}
		}
	}

	return 1;
}



/*************************************************************************/
/*************************************************************************/
/*************************************************************************/
/*  assistant operation begin
/*************************************************************************/
/*************************************************************************/
/*************************************************************************/
// open/close file or stream
// browse file and get the file path
BOOL CPlayerDlg::BrowseFile(CString *strFileName)
{
#ifdef _FOR_HIKPLAYM4_DLL_
	CFileDialog dlg(TRUE, 
		_T("mpg"),
		NULL, 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("Hikvision File(*.mp4;*.264)|*.mp4;*.264|All Files(*.*)|*.*||"), this);
#else
	CFileDialog dlg(TRUE, 
		_T("mpg"),
		NULL, 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("File(*.mp4;*.264)|*.mp4;*.264|DVR File(*.vs)|*.vs|All Files(*.*)|*.*||"), this);
#endif

	if(dlg.DoModal() == IDCANCEL)
	{
		return FALSE;
	}
	*strFileName = dlg.GetPathName();

	return TRUE;
}

// set play state
// Funtion: Draw the status .
void CPlayerDlg::DrawStatus()
{
	if (IsFullScreen())
	{
		return;
	}
	DWORD nCurrentTime = GetPlayer()->GetCurrentPosition();
	DWORD nDuration	= GetPlayer()->GetDuration();

	if (nDuration <= 0) return;
	m_PlaySlider.SetScrollPos(PLAYER_SLIDER_MAX * nCurrentTime / nDuration);

	CString csPlayTime;
	csPlayTime.Format(_T("%.2d:%.2d:%.2d / %.2d:%.2d:%.2d"), nCurrentTime/3600, nCurrentTime/60, nCurrentTime%60, nDuration/3600, nDuration/60, nDuration%60);
	GetDlgItem(IDC_PLAY_TIMEINFO)->SetWindowText(csPlayTime);
//
//	//TRACE(_T("hytest: play position = %f!\n", NAME(PlayM4_GetPlayPos)(m_lPort));
//
//	//TRACE(_T("Get time is:%d\n",nCurrentTime);			
//	DWORD nHour   = (nCurrentTime / 3600) % 24;
//	DWORD nMinute = (nCurrentTime % 3600) / 60;
//	DWORD nSecond = nCurrentTime % 60;
//	int nPos = 0;
//	if(m_bStreamType)
//	{
//		DWORD nFilePos = SetFilePointer(GetPlayer()->m_hStreamFile, 0, 0, FILE_CURRENT);
//		nPos = nFilePos * PLAYER_SLIDER_MAX / m_dwMaxFileSize;
//	}
//	else
//	{
//#ifdef _FILE_POS
//		float fPos = NAME(PlayM4_GetPlayPos)(m_lPort);
//		nPos = int(fPos * PLAYER_SLIDER_MAX);
//
//#else
//		nPos = nCurrentTime * PLAYER_SLIDER_MAX / GetPlayer()->GetDuration();
//
//#endif
//	}
//
//	DWORD nCurrentFrame = GetPlayer()->GetCurrentFrameNum();//NAME(PlayM4_GetCurrentFrameNum)(m_lPort);
//
//	TRACE(_T("nCurrentFrame %d----------nCurrentTime %d--------------\n", nCurrentFrame, nCurrentTime);
//	if(m_nSpeed > 0)
//	{
//		m_strPlayStateText.Format(_T("speed X %d            %d/%d  %02d:%02d:%02d/%02d:%02d:%02d"), GetSpeedModulus(), nCurrentFrame, m_dwTotalFrames, nHour, nMinute, nSecond, m_dwDisplayHour,m_dwDisplayMinute,m_dwDisplaySecond);
//	}
//	else if(m_nSpeed == 0)
//	{
//		m_strPlayStateText.Format(_T("speed normal          %d/%d  %02d:%02d:%02d/%02d:%02d:%02d"), nCurrentFrame, m_dwTotalFrames, nHour, nMinute, nSecond, m_dwDisplayHour,m_dwDisplayMinute,m_dwDisplaySecond);
//	}
//	else
//	{
//		m_strPlayStateText.Format(_T("speed / %d            %d/%d  %02d:%02d:%02d/%02d:%02d:%02d"), GetSpeedModulus(), nCurrentFrame, m_dwTotalFrames, nHour, nMinute, nSecond, m_dwDisplayHour,m_dwDisplayMinute,m_dwDisplaySecond);
//	}
//
//	if(m_bConvertAVI)
//	{
//		m_strPlayStateText.Format(_T("Converting……        %d/%d  %02d:%02d:%02d/%02d:%02d:%02d"), nCurrentFrame, m_dwTotalFrames, nHour, nMinute, nSecond, m_dwDisplayHour, m_dwDisplayMinute, m_dwDisplaySecond);     
//	}
//
//	m_ctrlPlayText.ShowText(m_strPlayStateText);
//
//
//
//	//adjust the slider.
//	//	INT nAdjust = (m_nPrePlayPos < nPos) ? 1 : 0;
//	int nScrollPos = 0;
//	if (m_dwTotalFrames != 1)
//	{
//		nScrollPos = nCurrentFrame * PLAYER_SLIDER_MAX / (m_dwTotalFrames - 1);
//	}
//	else
//	{
//		nScrollPos = 1;
//	}
//
//	if (m_nPrePlayPos == nScrollPos)
//	{
//		return;
//	}
//	m_PlaySlider.SetScrollPos(nScrollPos);
//	m_nPrePlayPos = nScrollPos;
//
	// test
	// TRACE(_T("Current frame rate:%d\n",NAME(PlayM4_GetCurrentFrameRate)(m_lPort));
	// TRACE(_T("Current time use ms:%d\n",NAME(PlayM4_GetPlayedTimeEx)(m_lPort));

}

// set state
void CPlayerDlg::SetState()
{
	if (GetPlayer()->IsMonitoring())
	{
		m_ctrlBtnCapPic.SetIcon(IDI_CAPPIC_AT, IDI_CAPPIC_ENABLE);
		m_ctrlBtnCapPic.EnableWindow(TRUE);
		return;
	}

	switch(m_DVRPlayer.GetPlayState())
	{
	case CDVRPlayer::eState_Close:

		// button state

		m_ctrlBtnPlay.SetIcon(IDI_PLAY_DISABLE);
		m_ctrlBtnPlay.EnableWindow(FALSE);
		m_ctrlBtnPlay.ShowWindow(SW_SHOW);
		m_ctrlBtnPlay.SetCheck(0);

		m_ctrlBtnPause.SetIcon(IDI_PAUSE_DISABLE);
		m_ctrlBtnPause.EnableWindow(FALSE);
		m_ctrlBtnPause.ShowWindow(SW_HIDE);
		m_ctrlBtnPause.SetCheck(0);

		m_ctrlBtnStop.SetIcon(IDI_STOP_DISABLE);
		m_ctrlBtnStop.EnableWindow(FALSE);
		m_ctrlBtnStop.SetCheck(0);


		m_ctrlBtnSlow.SetIcon(IDI_FASTBACKWARD_DISABLE);
		m_ctrlBtnSlow.EnableWindow(FALSE);

		m_ctrlBtnFast.SetIcon(IDI_FASTFORWARD_DISABLE);
		m_ctrlBtnFast.EnableWindow(FALSE);

		m_ctrlBtnGEnd.SetIcon(IDI_GOTOEND_DISABLE);
		m_ctrlBtnGEnd.EnableWindow(FALSE);

		m_ctrlBtnGStart.SetIcon(IDI_GOTOSTART_DISABLE);
		m_ctrlBtnGStart.EnableWindow(FALSE);

		m_ctrlStepBackward.SetIcon(IDI_STEPBACKWARD_DISABLE);
		m_ctrlStepBackward.EnableWindow(FALSE);

		m_ctrlStepForward.SetIcon(IDI_STEPFORWARD_DISABLE);
		m_ctrlStepForward.EnableWindow(FALSE);

		m_ctrlBtnSound.SetIcon(IDI_SOUND_DISABLE);
		m_ctrlBtnSound.EnableWindow(FALSE);

		m_ctrlBtnCapPic.SetIcon(IDI_CAPPIC_DISABLE);
		m_ctrlBtnCapPic.EnableWindow(FALSE);


		// scroll state	
		m_PlaySlider.SetScrollPos(0);
		m_PlaySlider.EnableWindow(FALSE);

#ifdef _WAVE_ADJ
		m_SoundSlider.SetPos(0);
#else
		m_SoundSlider.SetPos(0xffff>>1);
#endif
		m_SoundSlider.EnableWindow(FALSE);
		//m_ctrlVideoPic.SetBitmap(m_BlackBmp);

		InitWindowSize();

		break;

	case CDVRPlayer::eState_Play:
		m_ctrlBtnPlay.SetIcon(IDI_PLAY_CHECK);
		m_ctrlBtnPlay.EnableWindow(TRUE);
		m_ctrlBtnPlay.ShowWindow(SW_HIDE);
		m_ctrlBtnPlay.SetCheck(1);

		m_ctrlBtnPause.SetIcon(IDI_PAUSE_ENABLE);
		m_ctrlBtnPause.EnableWindow(TRUE);
		m_ctrlBtnPause.ShowWindow(SW_SHOW);
		m_ctrlBtnPause.SetCheck(0);

		m_ctrlBtnStop.SetIcon(IDI_STOP_ENABLE);
		m_ctrlBtnStop.EnableWindow(TRUE);
		m_ctrlBtnStop.SetCheck(0);

		if(m_bStreamType)
		{
			m_ctrlBtnGStart.SetIcon(IDI_GOTOSTART_DISABLE);
			m_ctrlBtnGStart.EnableWindow(FALSE);

			m_ctrlBtnGEnd.SetIcon(IDI_GOTOEND_DISABLE);
			m_ctrlBtnGEnd.EnableWindow(FALSE);

			m_ctrlStepBackward.SetIcon(IDI_STEPBACKWARD_DISABLE);
			m_ctrlStepBackward.EnableWindow(FALSE);
		}
		else
		{
			m_ctrlBtnGStart.SetIcon(IDI_GOTOSTART_ENABLE);
			m_ctrlBtnGStart.EnableWindow(TRUE);

			m_ctrlBtnGEnd.SetIcon(IDI_GOTOEND_ENABLE);
			m_ctrlBtnGEnd.EnableWindow(TRUE);

			m_ctrlStepBackward.SetIcon(IDI_STEPBACKWARD_ENABLE);
			m_ctrlStepBackward.EnableWindow(TRUE);
		}


		m_ctrlBtnSlow.SetIcon(IDI_FASTBACKWARD_ENABLE);
		m_ctrlBtnSlow.EnableWindow(TRUE);

		m_ctrlBtnFast.SetIcon(IDI_FASTFORWARD_ENABLE);
		m_ctrlBtnFast.EnableWindow(TRUE);

		m_ctrlStepForward.SetIcon(IDI_STEPFORWARD_ENABLE);
		m_ctrlStepForward.EnableWindow(TRUE);

		m_ctrlBtnCapPic.SetIcon(IDI_CAPPIC_AT, IDI_CAPPIC_ENABLE);
		m_ctrlBtnCapPic.EnableWindow(TRUE);

		m_ctrlBtnSound.EnableWindow(TRUE);
		if(m_bSound)
		{
			m_ctrlBtnSound.SetIcon(IDI_SOUND_ENABLE);
		}
		else
		{
			m_ctrlBtnSound.SetIcon(IDI_SOUND_DISABLE);
		}

		// scroll state			
		if(m_bStreamType)
		{
			m_PlaySlider.EnableWindow(FALSE);
		}
		else
		{
			m_PlaySlider.EnableWindow(TRUE);
		}
		m_PlaySlider.RedrawWindow();
		m_SoundSlider.EnableWindow(TRUE);

		//if((HBITMAP)m_OverlayBmp != m_ctrlVideoPic.GetBitmap())
		//{
		//	m_ctrlVideoPic.SetBitmap(m_OverlayBmp);
		//}

		break;

	case CDVRPlayer::eState_Pause:
	case CDVRPlayer::eState_Step:
		m_ctrlBtnPlay.SetIcon(IDI_PLAY_ENABLE);
		m_ctrlBtnPlay.EnableWindow(TRUE);
		m_ctrlBtnPlay.ShowWindow(SW_SHOW);
		m_ctrlBtnPlay.SetCheck(0);

		m_ctrlBtnPause.SetIcon(IDI_PAUSE_CHECK);
		m_ctrlBtnPause.EnableWindow(TRUE);
		m_ctrlBtnPause.ShowWindow(SW_HIDE);
		m_ctrlBtnPause.SetCheck(1);

		m_ctrlBtnStop.SetIcon(IDI_STOP_ENABLE);
		m_ctrlBtnStop.EnableWindow(TRUE);
		m_ctrlBtnStop.SetCheck(0);

		if(m_bStreamType)
		{
			m_ctrlBtnGStart.SetIcon(IDI_GOTOSTART_DISABLE);
			m_ctrlBtnGStart.EnableWindow(FALSE);

			m_ctrlBtnGEnd.SetIcon(IDI_GOTOEND_DISABLE);
			m_ctrlBtnGEnd.EnableWindow(FALSE);

			m_ctrlStepBackward.SetIcon(IDI_STEPBACKWARD_DISABLE);
			m_ctrlStepBackward.EnableWindow(FALSE);
		}
		else
		{
			m_ctrlBtnGStart.SetIcon(IDI_GOTOSTART_ENABLE);
			m_ctrlBtnGStart.EnableWindow(TRUE);

			m_ctrlBtnGEnd.SetIcon(IDI_GOTOEND_ENABLE);
			m_ctrlBtnGEnd.EnableWindow(TRUE);

			m_ctrlStepBackward.SetIcon(IDI_STEPBACKWARD_ENABLE);
			m_ctrlStepBackward.EnableWindow(TRUE);
		}

		m_ctrlBtnSlow.SetIcon(IDI_FASTBACKWARD_ENABLE);
		m_ctrlBtnSlow.EnableWindow(TRUE);

		m_ctrlBtnFast.SetIcon(IDI_FASTFORWARD_ENABLE);
		m_ctrlBtnFast.EnableWindow(TRUE);

		m_ctrlStepForward.SetIcon(IDI_STEPFORWARD_ENABLE);
		m_ctrlStepForward.EnableWindow(TRUE);

		m_ctrlBtnCapPic.SetIcon(IDI_CAPPIC_AT, IDI_CAPPIC_ENABLE);
		m_ctrlBtnCapPic.EnableWindow(TRUE);

		break;

	case CDVRPlayer::eState_Stop:
		m_ctrlBtnPlay.SetIcon(IDI_PLAY_ENABLE);
		m_ctrlBtnPlay.EnableWindow(TRUE);
		m_ctrlBtnPlay.ShowWindow(SW_SHOW);
		m_ctrlBtnPlay.SetCheck(0);

		m_ctrlBtnPause.SetIcon(IDI_PAUSE_ENABLE);
		m_ctrlBtnPause.EnableWindow(TRUE);
		m_ctrlBtnPause.ShowWindow(SW_HIDE);
		m_ctrlBtnPause.SetCheck(0);

		m_ctrlBtnStop.SetIcon(IDI_STOP_CHECK);
		m_ctrlBtnStop.EnableWindow(TRUE);
		m_ctrlBtnStop.SetCheck(1);

		m_ctrlBtnGStart.SetIcon(IDI_GOTOSTART_DISABLE);
		m_ctrlBtnGStart.EnableWindow(FALSE);

		m_ctrlBtnSlow.SetIcon(IDI_FASTBACKWARD_ENABLE);
		m_ctrlBtnSlow.EnableWindow(TRUE);

		m_ctrlBtnFast.SetIcon(IDI_FASTFORWARD_ENABLE);
		m_ctrlBtnFast.EnableWindow(TRUE);

		m_ctrlBtnGEnd.SetIcon(IDI_GOTOEND_DISABLE);
		m_ctrlBtnGEnd.EnableWindow(FALSE);

		m_ctrlStepBackward.SetIcon(IDI_STEPBACKWARD_DISABLE);
		m_ctrlStepBackward.EnableWindow(FALSE);

		m_ctrlStepForward.SetIcon(IDI_STEPFORWARD_DISABLE);
		m_ctrlStepForward.EnableWindow(FALSE);

		m_ctrlBtnCapPic.SetIcon(IDI_CAPPIC_DISABLE);
		m_ctrlBtnCapPic.EnableWindow(FALSE);

		// scroll state
		m_PlaySlider.SetScrollPos(0);
		m_PlaySlider.EnableWindow(FALSE);

#ifdef _WAVE_ADJ
		m_SoundSlider.SetPos(0);
#else
		m_SoundSlider.SetPos(0xffff>>1);
#endif
		m_SoundSlider.EnableWindow(FALSE);

		//m_ctrlVideoPic.SetBitmap(m_BlackBmp);

		break;

	default:
		break;
	}

	// Hide the buttons.
	m_ctrlBtnGEnd.ShowWindow(SW_HIDE);
	m_ctrlBtnGStart.ShowWindow(SW_HIDE);
	m_ctrlStepBackward.ShowWindow(SW_HIDE);
	m_ctrlStepForward.ShowWindow(SW_HIDE);
	m_ctrlBtnSound.ShowWindow(SW_HIDE);
	GetDlgItem(IDC_INTER2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_INTER3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_SOUND_SLIDER)->ShowWindow(SW_HIDE);
		
	SortControl();

	UpdateData(FALSE);
	GetPlayer()->RefreshPlay();
}

// set avi state
void CPlayerDlg::SetAVIState()
{
	// button state

	m_ctrlBtnPlay.SetIcon(IDI_PLAY_DISABLE);
	m_ctrlBtnPlay.EnableWindow(FALSE);
	m_ctrlBtnPlay.SetCheck(0);

	m_ctrlBtnPause.SetIcon(IDI_PAUSE_DISABLE);
	m_ctrlBtnPause.EnableWindow(FALSE);
	m_ctrlBtnPause.SetCheck(0);

	m_ctrlBtnStop.SetIcon(IDI_STOP_ENABLE);
	m_ctrlBtnStop.EnableWindow(TRUE);
	m_ctrlBtnStop.SetCheck(0);

	m_ctrlBtnGStart.SetIcon(IDI_GOTOSTART_DISABLE);
	m_ctrlBtnGStart.EnableWindow(FALSE);

	m_ctrlBtnSlow.SetIcon(IDI_FASTBACKWARD_DISABLE);
	m_ctrlBtnSlow.EnableWindow(FALSE);

	m_ctrlBtnFast.SetIcon(IDI_FASTFORWARD_DISABLE);
	m_ctrlBtnFast.EnableWindow(FALSE);

	m_ctrlBtnGEnd.SetIcon(IDI_GOTOEND_DISABLE);
	m_ctrlBtnGEnd.EnableWindow(FALSE);

	m_ctrlStepBackward.SetIcon(IDI_STEPBACKWARD_DISABLE);
	m_ctrlStepBackward.EnableWindow(FALSE);

	m_ctrlStepForward.SetIcon(IDI_STEPFORWARD_DISABLE);
	m_ctrlStepForward.EnableWindow(FALSE);

	m_ctrlBtnCapPic.SetIcon(IDI_CAPPIC_DISABLE);
	m_ctrlBtnCapPic.EnableWindow(FALSE);

	m_ctrlBtnSound.SetIcon(IDI_SOUND_DISABLE);
	m_ctrlBtnSound.EnableWindow(FALSE);

	// scroll state	
	m_PlaySlider.SetScrollPos(0);
	m_PlaySlider.EnableWindow(FALSE);


	//if((HBITMAP)m_OverlayBmp != m_ctrlVideoPic.GetBitmap())
	//{
	//	m_ctrlVideoPic.SetBitmap(m_OverlayBmp);
	//}
}

// get speed modulus to show int the static text control
DWORD CPlayerDlg::GetSpeedModulus()
{
	DWORD dwValue = 0;
	switch(m_nSpeed)
	{
	case 1:
	case -1:
		dwValue = 2;
		break;

	case 2:
	case -2:
		dwValue = 4;
		break;

	case 3:
	case -3:
		dwValue = 8;
		break;

	case 4:
	case -4:
		dwValue = 16;
		break;

	default:
		break;
	}

	return dwValue;
}

// resize the dialog
void CPlayerDlg::SetWindowSize()
{
	return;
	CRect rcWin, rcClient;
	GetWindowRect(&rcWin);
	GetClientRect(&rcClient);
	m_dwDlgEdge = (rcWin.Width() - rcClient.Width()) >> 1;
	ClientToScreen(&rcClient);
	m_dwDlgTopSize = rcClient.top - rcWin.top;

	TRACE(_T("init window size!\n"));
	GetPlayer()->GetPictureSize(&GetPlayer()->GetDVRSettings().m_nRenderWidth, &GetPlayer()->GetDVRSettings().m_nRenderHeight);
//	m_pDisplayRegion->SetResolution(m_nHeight, m_nWidth);
	TRACE(_T("get window size ok\n"));

	if (GetPlayer()->GetDVRSettings().m_nRenderWidth == 704 && (GetPlayer()->GetDVRSettings().m_nRenderHeight == 288 || GetPlayer()->GetDVRSettings().m_nRenderHeight == 240))
	{
		GetPlayer()->GetDVRSettings().m_nRenderHeight <<= 1;
	}

	DWORD nWindowHeight = GetPlayer()->GetDVRSettings().m_nRenderHeight + PANNEL_HEIGHT + m_dwDlgTopSize + m_dwDlgEdge + 10;
	DWORD nWindowWidth  = GetPlayer()->GetDVRSettings().m_nRenderWidth + (m_dwDlgEdge << 1);

	nWindowHeight = min(nWindowHeight, m_dwScreenHeight);
	nWindowWidth  = min(nWindowWidth,  m_dwScreenWidth);
	if (nWindowWidth < 200)
	{
		nWindowHeight += 20;
	}
	MoveWindow(
		(m_dwScreenWidth  -nWindowWidth)  / 2 + m_rcScreen.left,
		(m_dwScreenHeight -nWindowHeight) / 2 + m_rcScreen.top,
		nWindowWidth,
		nWindowHeight,
		TRUE);
	TRACE(_T("exit window size\n"));

}

// Funtion: sort the controls
void CPlayerDlg::SortControl()
{
	TRACE(_T("init SORT\n"));

	CRect rcClient, rcVideo;

	GetClientRect(&rcClient);
	m_ctrlVideoPic.GetClientRect(&rcVideo);
	
	DWORD x=LEFT_EDGE+10,y=rcVideo.bottom+STATE_HEIGHT;

	x=LEFT_EDGE;

	//BUTTON
	m_ctrlBtnSlow.MoveWindow(x,y,BUTTON_SIZE,BUTTON_SIZE,TRUE);
	x+=BUTTON_SIZE;
	m_ctrlBtnPlay.SetWindowPos(&CWnd::wndTop, x, y, BUTTON_SIZE,BUTTON_SIZE, SWP_SHOWWINDOW);//MoveWindow(x,y,BUTTON_SIZE,BUTTON_SIZE,TRUE);
	m_ctrlBtnPause.MoveWindow(x,y,BUTTON_SIZE,BUTTON_SIZE,TRUE);
	x+=BUTTON_SIZE;
	m_ctrlBtnStop.MoveWindow(x,y,BUTTON_SIZE,BUTTON_SIZE,TRUE);
	x+=BUTTON_SIZE;
	m_ctrlBtnFast.MoveWindow(x,y,BUTTON_SIZE,BUTTON_SIZE,TRUE);
	x+=BUTTON_SIZE;
	x+=INTERVAL;
	GetDlgItem(IDC_INTER1)->MoveWindow(x,y,INTERVAL_SIZE,BUTTON_SIZE,TRUE);
	x+=INTERVAL_SIZE;
	x+=INTERVAL;
	m_ctrlBtnCapPic.MoveWindow(x,y,BUTTON_SIZE,BUTTON_SIZE,TRUE);
	x+=BUTTON_SIZE;


	//m_ctrlBtnGStart.MoveWindow(x,y,BUTTON_SIZE,BUTTON_SIZE,TRUE);
	//x+=BUTTON_SIZE;
	//m_ctrlBtnGEnd.MoveWindow(x,y,BUTTON_SIZE,BUTTON_SIZE,TRUE);
	//x+=BUTTON_SIZE;

	//x+=INTERVAL;
	//GetDlgItem(IDC_INTER2)->MoveWindow(x,y,INTERVAL_SIZE,BUTTON_SIZE,TRUE);
	//x+=INTERVAL_SIZE;
	//x+=INTERVAL;

	//m_ctrlStepBackward.MoveWindow(x,y,BUTTON_SIZE,BUTTON_SIZE,TRUE);
	//x+=BUTTON_SIZE;

	//m_ctrlStepForward.MoveWindow(x,y,BUTTON_SIZE,BUTTON_SIZE,TRUE);
	//x+=BUTTON_SIZE;

	x+=INTERVAL;
	GetDlgItem(IDC_INTER3)->MoveWindow(x,y,INTERVAL_SIZE,BUTTON_SIZE,TRUE);
	x+=INTERVAL_SIZE;
	x+=INTERVAL;



	////SOUND
	//x=rcClient.right-SOUND_SLIDER_WIDTH;
	//m_SoundSlider.MoveWindow(x,y+BUTTON_SIZE-SOUND_SLIDER_HEIGHT,SOUND_SLIDER_WIDTH,SOUND_SLIDER_HEIGHT,TRUE);
	//x-=BUTTON_SIZE;

	//m_ctrlBtnSound.MoveWindow(x,y,BUTTON_SIZE,BUTTON_SIZE,TRUE);

	//y-=BUTTON_SIZE+BUTTON_UP;
	////PLAY SLIDER
	//x=0;
	CRect rcCtrl;
	CWnd* pWndTI = GetDlgItem(IDC_PLAY_TIMEINFO);
	pWndTI->GetClientRect(&rcCtrl);
	pWndTI->MoveWindow(rcVideo.right-rcCtrl.Width(), y - rcCtrl.Height(), rcCtrl.Width(), rcCtrl.Height());
	GetDlgItem(IDC_PLAY_RECT_SLIDER)->MoveWindow(x,y,rcClient.Width(),PLAY_SLIDER_HEIGHT,TRUE);
	m_PlaySlider.MoveWindowEx(x,y+4,rcVideo.Width()-x,PLAY_SLIDER_HEIGHT,TRUE);

	CRect rcOpenFileBtn, rcSHBtn;
	GetDlgItem(IDC_OPENFILE)->GetWindowRect(rcOpenFileBtn);
	GetDlgItem(IDC_SHOWHIDE_SETTINGS)->GetClientRect(rcSHBtn);
	GetDlgItem(IDC_RENDER_MODE)->MoveWindow(rcVideo.right-rcSHBtn.Width()-INTERVAL-rcOpenFileBtn.Width()-INTERVAL-rcOpenFileBtn.Width(), y+BUTTON_SIZE, rcOpenFileBtn.Width(), rcOpenFileBtn.Height());
	GetDlgItem(IDC_OPENFILE)->MoveWindow(rcVideo.right-rcSHBtn.Width()-INTERVAL-rcOpenFileBtn.Width(), y+BUTTON_SIZE, rcOpenFileBtn.Width(), rcOpenFileBtn.Height());
	GetDlgItem(IDC_SHOWHIDE_SETTINGS)->MoveWindow(rcVideo.right-rcSHBtn.Width(),  y+BUTTON_SIZE, rcSHBtn.Width(), rcSHBtn.Height());
	//y-=PLAY_SLIDER_UP;

	//pic show
	//m_ctrlVideoPic.MoveWindow(0,0,rcClient.Width(),y,TRUE);

	GetPlayer()->RefreshPlay();
	//NAME(PlayM4_RefreshPlay)(m_lPort);

	// redraw whole the dialog rect except the video show rect
	CRect rect;
	rect.left   = rcClient.left;
	rect.top    = rcVideo.bottom;
	rect.right  = rcClient.right;
	rect.bottom = rcClient.bottom;
	InvalidateRect(&rect);
	TRACE(_T("exit SORT\n"));
}


// Funtion: Init window size.
void CPlayerDlg::InitWindowSize(DWORD cx,DWORD cy)
{
	TRACE(_T("init window\n"));
	CRect rcWin, rcClient;
	GetWindowRect(&rcWin);
	GetClientRect(&rcClient);
	m_dwDlgEdge = (rcWin.Width() - rcClient.Width()) >> 1;
	ClientToScreen(&rcClient);
	m_dwDlgTopSize = rcClient.top - rcWin.top;

	DWORD nWindowWidth  = cx + (m_dwDlgEdge << 1);
	DWORD nWindowHeight = cy + PANNEL_HEIGHT + m_dwDlgTopSize + m_dwDlgEdge + 10;

	nWindowHeight = min(nWindowHeight, m_dwScreenHeight);
	nWindowWidth  = min(nWindowWidth,  m_dwScreenWidth);

	//MoveWindow(
	//	(m_dwScreenWidth  - nWindowWidth)/2 + m_rcScreen.left,
	//	(m_dwScreenHeight - nWindowHeight)/2+ m_rcScreen.top,
	//	nWindowWidth,
	//	nWindowHeight,
	//	TRUE);
	RECT rcRender;
	m_ctrlVideoPic.GetClientRect(&rcRender);
	m_ctrlVideoPic.SetBitmap(m_BlackBmp);
	rcRender.right = rcRender.left + cx;
	rcRender.bottom = rcRender.top + cy;

	m_ctrlVideoPic.MoveWindow(&rcRender);
	//m_ctrlVideoPic.SetWindowPos(&CWnd::wndNoTopMost, 0, 0, cx, cy, SWP_NOMOVE | SWP_NOZORDER);
	SortControl();

	//for the small picture size.The menu will be high. 
	GetWindowRect(&rcWin);
	GetClientRect(&rcClient);
	m_dwDlgEdge = (rcWin.Width() - rcClient.Width()) >> 1;
	ClientToScreen(&rcClient);
	DWORD nTopSize = rcClient.top - rcWin.top;
	if(nTopSize != m_dwDlgTopSize)
	{
		TRACE(_T("re init window!!!!!!\n"));
		m_dwDlgTopSize = nTopSize;
		nWindowHeight  = cy + PANNEL_HEIGHT + m_dwDlgTopSize + m_dwDlgEdge + 10;
		nWindowWidth   = cx + (m_dwDlgEdge << 1);

		nWindowHeight = min(nWindowHeight, m_dwScreenHeight);
		nWindowWidth  = min(nWindowWidth,  m_dwScreenWidth);

		//MoveWindow(
		//	(m_dwScreenWidth  - nWindowWidth)  / 2 + m_rcScreen.left,
		//	(m_dwScreenHeight - nWindowHeight) / 2 + m_rcScreen.top,
		//	nWindowWidth,
		//	nWindowHeight,
		//	TRUE);
		SortControl();
	}
}


// others
// geton pic rect
CRect CPlayerDlg::GetOnPicRect(CRect rcWnd, CRect rcOnWnd, LONG nPicWidth, LONG nPicHeight)
{
	CRect rcOnPic;
	//LONG nScaleX=rcWnd.Width()
	long nWndX = rcOnWnd.left - rcWnd.left;
	long nWndY = rcOnWnd.top  - rcWnd.top;
	if(nWndX < 0)
	{
		nWndX = 0;
	}

	if(nWndY < 0)
	{
		nWndY = 0;
	}

	rcOnPic.left   = nWndX * nPicWidth  / rcWnd.Width();
	rcOnPic.top    = nWndY * nPicHeight / rcWnd.Height();
	rcOnPic.right  = rcOnPic.left + rcOnWnd.Width()  * nPicWidth/rcWnd.Width();
	rcOnPic.bottom = rcOnPic.top  + rcOnWnd.Height() * nPicHeight/rcWnd.Height();

	if(rcOnPic.right > nPicWidth)
	{
		rcOnPic.right = nPicWidth;
	}

	if(rcOnPic.bottom > nPicHeight)
	{
		rcOnPic.bottom = nPicHeight;
	}

	return rcOnPic;
}

void CPlayerDlg::SetDisplayRegion(RECT Rect)
{
	GetPlayer()->SetDisplayRegion(GetDlgItem(IDC_SHOW)->m_hWnd, &Rect);
	UpdateWindow();
}

// view operation:
void CPlayerDlg::ViewFullScreen() 
{
	// TODO: Add your command handler code here
	m_bFullScreen = !m_bFullScreen;

	if(m_bFullScreen)
	{
		if (m_pOldParentWnd == NULL)
		{
			m_pOldParentWnd = GetParent();
			SetParent(NULL);
		}
		//Save the pre info;
		GetWindowPlacement(&m_OldWndpl);
		//Remove WS_SIZEBOX windows style. or not the window can't be full-creen.
		ModifyStyle(WS_SIZEBOX, 0, 0);

		CRect WindowRect, ClientRect;
		RECT  m_FullScreenRect;

		GetWindowRect(&WindowRect);
		GetClientRect(&ClientRect);
		ClientToScreen(&ClientRect);

		//get the dest window rect.
		m_FullScreenRect.left   = WindowRect.left   - ClientRect.left + m_rcScreen.left;
		m_FullScreenRect.top    = WindowRect.top    - ClientRect.top  + m_rcScreen.top;
		m_FullScreenRect.right  = WindowRect.right  - ClientRect.right + m_rcScreen.right;
		m_FullScreenRect.bottom = WindowRect.bottom - ClientRect.bottom + m_rcScreen.bottom;
		//Move the main window to the dest rect.
		WINDOWPLACEMENT wndpl;
		wndpl.length  = sizeof(WINDOWPLACEMENT);
		wndpl.flags   = 0;
		wndpl.showCmd = SW_SHOWNORMAL;
		wndpl.rcNormalPosition = m_FullScreenRect;
		SetWindowPlacement(&wndpl);
		::SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0,  m_FullScreenRect.right-m_FullScreenRect.left , m_FullScreenRect.bottom-m_FullScreenRect.top, SWP_SHOWWINDOW);
		//Move the view winow to full-screen.
		RECT rc;
		GetClientRect(&rc);
		m_ctrlVideoPic.GetClientRect(&m_rcOldPicPos);
		m_ctrlVideoPic.MoveWindow(&rc,TRUE);
		GetPlayer()->GetDVRSettings().m_nRenderWidth = rc.right - rc.left;
		GetPlayer()->GetDVRSettings().m_nRenderHeight = rc.bottom - rc.top;

		//Remove WS_VISIBLE window style.
		m_ctrlBtnPlay.ModifyStyle(WS_VISIBLE, 0, 0);
		m_ctrlBtnPause.ModifyStyle(WS_VISIBLE, 0, 0);
		m_ctrlBtnStop.ModifyStyle(WS_VISIBLE, 0, 0);
		m_ctrlBtnFast.ModifyStyle(WS_VISIBLE, 0, 0);
		m_ctrlBtnGEnd.ModifyStyle(WS_VISIBLE, 0, 0);
		m_ctrlBtnSlow.ModifyStyle(WS_VISIBLE, 0, 0);
		m_ctrlBtnGStart.ModifyStyle(WS_VISIBLE, 0, 0);
		m_ctrlStepBackward.ModifyStyle(WS_VISIBLE, 0, 0);
		m_ctrlStepForward.ModifyStyle(WS_VISIBLE, 0, 0);
		m_ctrlBtnCapPic.ModifyStyle(WS_VISIBLE, 0, 0);
		m_ctrlBtnSound.ModifyStyle(WS_VISIBLE, 0, 0);

		GetDlgItem(IDC_INTER1)->ModifyStyle(WS_VISIBLE, 0, 0);
		GetDlgItem(IDC_INTER2)->ModifyStyle(WS_VISIBLE, 0, 0);
		GetDlgItem(IDC_INTER3)->ModifyStyle(WS_VISIBLE, 0, 0);

		m_SoundSlider.ModifyStyle(WS_VISIBLE,0,0);
		m_PlaySlider.ModifyStyle(WS_VISIBLE,0,0);

		GetDlgItem(IDC_OPENFILE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_SHOWHIDE_SETTINGS)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_PLAY_TIMEINFO)->ShowWindow(SW_HIDE);
	}
	else
	{
		if (m_pOldParentWnd != NULL)
		{
			SetParent(m_pOldParentWnd);
			m_pOldParentWnd = NULL;
		}
		//Visible the control.
		m_ctrlBtnPlay.ModifyStyle(0, WS_VISIBLE, 0);
		m_ctrlBtnPause.ModifyStyle(0, WS_VISIBLE, 0);
		m_ctrlBtnStop.ModifyStyle(0, WS_VISIBLE, 0);
		m_ctrlBtnFast.ModifyStyle(0, WS_VISIBLE, 0);
		m_ctrlBtnGEnd.ModifyStyle(0, WS_VISIBLE, 0);
		m_ctrlBtnSlow.ModifyStyle(0, WS_VISIBLE, 0);
		m_ctrlBtnGStart.ModifyStyle(0, WS_VISIBLE, 0);
		m_ctrlStepForward.ModifyStyle(0, WS_VISIBLE, 0);
		m_ctrlStepBackward.ModifyStyle(0, WS_VISIBLE, 0);
		m_ctrlBtnCapPic.ModifyStyle(0, WS_VISIBLE, 0);			
		m_ctrlBtnSound.ModifyStyle(0, WS_VISIBLE, 0);

		GetDlgItem(IDC_INTER1)->ModifyStyle(0, WS_VISIBLE, 0);
		GetDlgItem(IDC_INTER2)->ModifyStyle(0, WS_VISIBLE, 0);
		GetDlgItem(IDC_INTER3)->ModifyStyle(0, WS_VISIBLE, 0);

		m_PlaySlider.ModifyStyle(0,WS_VISIBLE,0);
		m_SoundSlider.ModifyStyle(0,WS_VISIBLE,0);

		SetWindowPlacement(&m_OldWndpl);
		m_ctrlVideoPic.MoveWindow(&m_rcOldPicPos,TRUE);
		GetPlayer()->GetDVRSettings().m_nRenderWidth = m_rcOldPicPos.right - m_rcOldPicPos.left;
		GetPlayer()->GetDVRSettings().m_nRenderHeight = m_rcOldPicPos.bottom - m_rcOldPicPos.top;


		GetDlgItem(IDC_OPENFILE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_SHOWHIDE_SETTINGS)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_PLAY_TIMEINFO)->ShowWindow(SW_SHOW);

		SetState();
		RedrawWindow();
	}


	GetPlayer()->RefreshPlay();
	//NAME(PlayM4_RefreshPlay)(m_lPort);
}

void  CPlayerDlg::InitWindowSize()
{
	if(m_bFullScreen)
	{
		ViewFullScreen();
	}
	else
	{
		InitWindowSize(GetPlayer()->GetDVRSettings().m_nRenderWidth, GetPlayer()->GetDVRSettings().m_nRenderHeight);
	}
}
void CPlayerDlg::ViewZoom(UINT nID)
{
	if(m_bFullScreen)
	{
		ViewFullScreen();
	}


	int nItem = nID - IDM_VIEW_ZOOM_100;

	switch(nItem)
	{
	case 0:
		InitWindowSize(GetPlayer()->GetDVRSettings().m_nRenderWidth, GetPlayer()->GetDVRSettings().m_nRenderHeight);
		break;

	case -1:
		InitWindowSize(GetPlayer()->GetDVRSettings().m_nRenderWidth >> 1, GetPlayer()->GetDVRSettings().m_nRenderHeight >> 1);
		break;

	case 1:
		InitWindowSize(GetPlayer()->GetDVRSettings().m_nRenderWidth << 1, GetPlayer()->GetDVRSettings().m_nRenderHeight << 1);
		break;

	default:
		break;
	}
	////m_pMainMenu->CheckMenuItem(nID, MF_CHECKED);
}

void CPlayerDlg::Repeat() 
{
	// TODO: Add your command handler code here

	m_bRepeatPlay = !m_bRepeatPlay;
	UINT nFlag = m_bRepeatPlay ? MF_CHECKED : MF_UNCHECKED;
	////m_pMainMenu->CheckMenuItem(IDM_REPEAT, nFlag);
}

//void CPlayerDlg::Locate() 
//{
//	// TODO: Add your command handler code here
//
//	//m_pSeek->Create(IDD_SEEK);
//	////m_pMainMenu->EnableMenuItem(IDM_SEEK,MF_GRAYED | MF_DISABLED);
//}

// option operation:
void CPlayerDlg::StreamType() 
{
	// TODO: Add your command handler code here

	m_bStreamType = !m_bStreamType;
	UINT nFlag = m_bStreamType ? MF_CHECKED : MF_UNCHECKED;
	////m_pMainMenu->CheckMenuItem(IDM_STREAM_TYPE, nFlag);
}

void CPlayerDlg::Deflash() 
{
	// TODO: Add your command handler code here

	m_bDeflash = !m_bDeflash;
	UINT nFlag = m_bDeflash ? MF_CHECKED : MF_UNCHECKED;
	////m_pMainMenu->CheckMenuItem(IDM_DEFLASH, nFlag);

	GetPlayer()->RefreshPlay();
	//NAME(PlayM4_SetDeflash)(m_lPort, m_bDeflash);
}

void CPlayerDlg::Quality() 
{
	// TODO: Add your command handler code here

	m_bPicQuality = !m_bPicQuality;
	UINT nFlag = m_bPicQuality ? MF_CHECKED : MF_UNCHECKED;
	////m_pMainMenu->CheckMenuItem(IDM_QUALITY, nFlag);
	GetPlayer()->SetPictureQuality(m_bPicQuality);
	//NAME(PlayM4_SetPicQuality)(m_lPort, m_bPicQuality);
}

void CPlayerDlg::DisplayType(UINT nID)
{
	GetPlayer()->SetDisplayType(nID == IDM_DISNORMAL ? DISPLAY_NORMAL : DISPLAY_QUARTER);
}

void CPlayerDlg::SelectTimer(UINT nID)
{
	GetPlayer()->SetTimerType(nID - IDM_TIMERNULL);
}

void CPlayerDlg::ResetBuf() 
{
	// TODO: Add your command handler code here
	// Only test the interface. 
	GetPlayer()->ResetBuf();
}

void CPlayerDlg::CapPicType(UINT nID)
{
	if(nID == IDM_CAP_BMP)
	{
		m_nCapPicType = 0;
	}
	else
	{
		m_nCapPicType = 1;
	}
}

void CPlayerDlg::CappicPath() 
{
	TCHAR	     szDir[MAX_PATH];
	BROWSEINFO   bi;
	ITEMIDLIST  *pidl;

	bi.hwndOwner	  = this->m_hWnd;
	bi.pidlRoot		  = NULL;
	bi.pszDisplayName = szDir;
	bi.lpszTitle	  = _T("请选择目录");
	bi.ulFlags		  = BIF_RETURNONLYFSDIRS;
	bi.lpfn			  = NULL;
	bi.lParam		  = 0;
	bi.iImage		  = 0;

	pidl = SHBrowseForFolder(&bi);
	if(NULL == pidl)
	{
		return;
	}

	if(!SHGetPathFromIDList(pidl, szDir)) 
	{
		return;
	}

	m_strCapPicPath.Format(_T("%s"),szDir);
}

void CPlayerDlg::ConvertToAVI() 
{
	// TODO: Add your command handler code here	
	int ReturnValue;
	CString str, m_csInfo;

	str.Format(_T("Convert  to AVI File will be Failed to Play the MPEG4 File\n\n"));
	m_csInfo += str;
	str.Format(_T("The Converted AVI File can't be Larger than 2G!\n\n"));
	m_csInfo += str;
	str.Format(_T("Playing the Converted AVI File must Install the Divx!\n\n"));
	m_csInfo += str;
	str.Format(_T("if Continued,Click OK Button!\n"));
	m_csInfo += str;
	ReturnValue = MessageBox((LPCTSTR)m_csInfo, NULL, MB_YESNO); 


	if(ReturnValue == IDYES)
	{
		Close();

		m_bConvertAVI = TRUE;
		str.Format(_T("AVI Movie Files (*.avi)|*.avi||"));

		CFileDialog Filedlg(FALSE, _T("*.avi"), _T("*.avi"), OFN_LONGNAMES|OFN_CREATEPROMPT|OFN_OVERWRITEPROMPT, str, this);

		if(Filedlg.DoModal() == IDOK)
		{
			CString csFile;
			if(BrowseFile(&csFile))
			{
				Open(csFile);

				if(m_bConvertAVI)
				{
					SetAVIState();
				}
				else
				{
					SetState();
				}
				SortControl();
			}
			else
			{
				m_bConvertAVI = FALSE;
				SetState();
			}
		}
		else
		{
			m_bConvertAVI = FALSE;
			SetState();
		}
	}
}

/*************************************************************************/
/*************************************************************************/
/*************************************************************************/
/* when you click the menu item, you come here
/*************************************************************************/
/*************************************************************************/
/*************************************************************************/
void CPlayerDlg::OnMenuItem(UINT nID)
{
	CString csFile;
	switch(nID)
	{
	case IDM_FILE_OPEN:
		if(BrowseFile(&csFile)) 
		{
			Close();
			Open(csFile);
			if (IsWindow(m_DVRSettingsSheet.m_hWnd))
				m_DVRSettingsPage4.SetPathName(csFile);
			SetTimer(PLAY_TIMER, 500, NULL);
			SetState();
		}
		break;

	case IDM_FILE_CLOSE:
		Close();
		SetState();
		break;

	case IDM_APP_EXIT:
		SendMessage(WM_CLOSE);
		break;

	case IDM_VIEW_FULLSCREEN:
		ViewFullScreen();
		break;

	case IDM_VIEW_ZOOM_50:
	case IDM_VIEW_ZOOM_100:
	case IDM_VIEW_ZOOM_200:
		ViewZoom(nID);
		break;

	case IDM_PLAY_PAUSE:
		if(GetPlayer()->GetPlayState() == CDVRPlayer::eState_Play)
		{
			Pause();
			SetState();
		}
		else if(GetPlayer()->GetPlayState() == CDVRPlayer::eState_Pause || GetPlayer()->GetPlayState() == CDVRPlayer::eState_Stop)
		{
			Play();
			SetState();
		}
		break;

	case IDM_STOP:
		if(GetPlayer()->GetPlayState() != CDVRPlayer::eState_Close)
		{
			Stop();
			SetState();
		}
		break;

	case IDM_STEPFORWARD:
		if(GetPlayer()->GetPlayState() != CDVRPlayer::eState_Stop)
		{
			StepForward();
			SetState();
		}
		break;

	case IDM_STEPBACKWARD:
		if(GetPlayer()->GetPlayState() != CDVRPlayer::eState_Stop)
		{
			StepBackward();
			SetState();
		}
		break;

	case IDM_GOTOSTART:
		GetPlayer()->GotoStart();
		break;

	case IDM_GOTOEND:
		GetPlayer()->GotoEnd();
		break;

	case IDM_REPEAT:
		Repeat();
		break;

	case IDM_STREAM_TYPE:
		StreamType();
		break;

	case IDM_DEFLASH:
		Deflash();
		break;

	case IDM_QUALITY:
		Quality();
		break;

	case IDM_THROW0:
	case IDM_THROW1:                      
	case IDM_THROW2:
		GetPlayer()->ThrowB(nID);
		break;

	case IDM_DISNORMAL:                   
	case IDM_DISQUARTER:
		DisplayType(nID);
		break;

	case IDM_TIMER1:
	case IDM_TIMER2:
	case IDM_TIMERNULL:
		SelectTimer(nID);
		break;

	case IDM_RESET_BUF:
		ResetBuf();
		break;

	case IDM_CAP_BMP:
	case IDM_CAP_JPEG:
		CapPicType(nID);
		break;

	case IDM_CAPPIC_PATH:
		CappicPath();
		break;

	default:
		break;
	}
}

void CPlayerDlg::OnButtonItem(UINT nID)
{
	switch(nID)
	{
	case IDC_PLAY:
		Play();
		break;

	case IDC_PAUSE:
		Pause();
		break;

	case IDC_STOP:
		Stop();
		break;

	case IDC_GOTOSTART:
		m_DVRPlayer.GotoStart();
		break;

	case IDC_SLOW:
		Play();
		m_DVRPlayer.Slow();
		break;

	case IDC_FAST:
		Play();
		m_DVRPlayer.Fast();
		break;

	case IDC_GOTOEND:
		m_DVRPlayer.GotoEnd();
		break;

	case IDC_STEP:
		StepForward();
		break;

	case IDC_STEPBACK:
		StepBackward();
		break;

	case IDC_CAPPIC:
		m_DVRPlayer.Cappic();
		break;

	case IDC_SOUND:
		//m_DVRPlayer.Sound();
		break;

	default:
		break;
	}

	SetState();
}

void CPlayerDlg::OnDestroy() 
{
	CDialog::OnDestroy();


	m_DVRSettingsSheet.DestroyWindow();

	GetPlayer()->Destory();
	if(m_pQcifTempBuf)
	{
		delete []m_pQcifTempBuf;
		m_pQcifTempBuf = NULL;
	}
}

void CPlayerDlg::OnBnClickedOpenfile()
{
	OnMenuItem(IDM_FILE_OPEN);
}

void CPlayerDlg::Play()
{
	if (GetPlayer()->GetPlayState() != CDVRPlayer::eState_Play)
	{
		GetPlayer()->Play();
		m_ctrlVideoPic.SetWindowPos(&CWnd::wndBottom, 0,0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		SetTimer(PLAY_TIMER, 500, NULL);
	}
}

void CPlayerDlg::Pause()
{
	GetPlayer()->Pause();
}

void CPlayerDlg::Stop()
{
	if (GetPlayer()->GetPlayState() != CDVRPlayer::eState_Stop)
	{
		KillTimer(PLAY_TIMER);
		GetPlayer()->Stop();
	}
}

void CPlayerDlg::StepBackward()
{
	if (GetPlayer()->CanStepBackword())
	{
		GetPlayer()->StepBackward();
	}
}
void CPlayerDlg::StepForward()
{
	GetPlayer()->StepForward();
}

void CPlayerDlg::Open(LPCTSTR szFile)
{
	GetPlayer()->Open(szFile);
	//GetPlayer()->GetPictureSize(&GetPlayer()->GetDVRSettings().m_nRenderWidth, &GetPlayer()->GetDVRSettings().m_nRenderHeight);
	InitWindowSize(GetPlayer()->GetDVRSettings().m_nRenderWidth, GetPlayer()->GetDVRSettings().m_nRenderHeight);
}

void CPlayerDlg::Close()
{
	GetPlayer()->Close();

	//m_nWidth = 352;
	//m_nHeight = 288;
	//m_HikvisionBmp.LoadBitmap(IDB_HIKVISION);
	//m_ctrlVideoPic.SetBitmap(m_BlackBmp);
	//m_ctrlVideoPic.ShowWindow(SW_SHOW);
	SetWindowText(_T("Player"));
	m_ctrlVideoPic.Invalidate();
}

HRESULT CPlayerDlg::OpenFile(LPCTSTR szFile)
{
	HANDLE hFile = ::CreateFile(szFile, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		::CloseHandle(hFile);
		Close();
		Open(szFile);
		SetTimer(PLAY_TIMER, 500, NULL);
		SetState();
		return S_OK;
	}
	return E_FAIL;
}

void CPlayerDlg::OnBnClickedShowHideSettings()
{
	m_DVRSettingsSheet.ShowWindow(m_DVRSettingsSheet.IsWindowVisible()?SW_HIDE:SW_SHOW);
	//m_DVRSettingsSheet.DoModal();
}


BOOL CPlayerDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	if (IsFullScreen())
	{
		return 1;
	}
	return CDialog::OnEraseBkgnd(pDC);
}

bool CPlayerDlg::StartMonitor()
{
	BOOL bRet = GetPlayer()->StartMonitor();

	SetState();
	return bRet;
}
void CPlayerDlg::StopMonitor()
{
	GetPlayer()->StopMonitor();
	SetState();
}

void CPlayerDlg::OnClickedRenderMode()
{
	CDVRSettings::GetInstance()->m_bDrawMetaDataOnRender = !CDVRSettings::GetInstance()->m_bDrawMetaDataOnRender;
}
