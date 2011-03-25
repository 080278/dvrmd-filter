// Dlg_Playback_Download_Bytime.cpp : implementation file
//

#include "stdafx.h"
#include "HHVClient.h"
#include "Dlg_Playback_Download_Bytime.h"
#include "PlayerMgr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_Playback_Download_Bytime dialog


CDlg_Playback_Download_Bytime::CDlg_Playback_Download_Bytime(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_Playback_Download_Bytime::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg_Playback_Download_Bytime)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlg_Playback_Download_Bytime::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_Playback_Download_Bytime)
	DDX_Control(pDX, IDC_SLIDER_PLAYBACK_BYTIME, m_slider_playback_bytime);
	DDX_Control(pDX, IDC_SLIDER_MUTE_BYTIME, m_slider_mute_bytime);
	DDX_Control(pDX, IDC_PROGRESS_PRESENT, m_progress_present);
	DDX_Control(pDX, IDC_DTP_ENDYEAR_BYTIME, m_dEndYear_Bytime);
	DDX_Control(pDX, IDC_DTP_ENDTIMER_BYTIME, m_dEndTime_Bytime);
	DDX_Control(pDX, IDC_DTP_BEGINYEAR_BYTIME, m_dBeginYear_Bytime);
	DDX_Control(pDX, IDC_DTP_BEGINTIMER_BYTIME, m_dBeginTime_Bytime);
	DDX_Control(pDX, IDC_CMB_SEARCH_CHANNELNO, m_cmb_channel);
	DDX_Control(pDX, IDC_STATIC_PLAYBACK_BYTIME, m_sPlayback_Bytime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_Playback_Download_Bytime, CDialog)
	//{{AFX_MSG_MAP(CDlg_Playback_Download_Bytime)
	ON_BN_CLICKED(IDC_BTN_DOWNLOAD_BYTIME, OnBtnDownloadBytime)
	ON_BN_CLICKED(IDC_BTN_PLAYBACK_PLAY_BYTIME, OnBtnPlaybackPlayBytime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_Playback_Download_Bytime message handlers

void CDlg_Playback_Download_Bytime::OnBtnDownloadBytime() 
{
	// TODO: Add your control notification handler code here
	
}

BOOL CDlg_Playback_Download_Bytime::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//加入通道号
	CString cmbstr;
	for(int i = 0;i < 16; i++)	
	{
		cmbstr.Format("%d",i+1);
		m_cmb_channel.AddString(cmbstr);
	}
	m_cmb_channel.SetCurSel(0);
	//channel_no = 1;
	
	m_dBeginYear_Bytime.SetFormat("yyy-MM-dd");
	m_dEndYear_Bytime.SetFormat("yyy-MM-dd");   
	m_dBeginTime_Bytime.SetFormat("HH:mm:ss"); 
	m_dEndTime_Bytime.SetFormat("HH:mm:ss"); 
	
	CTime        PlayStart;   
	PlayStart = CTime::GetCurrentTime(   );  
	PlayStart -= CTimeSpan(1, 0, 0, 0);   
	m_dBeginYear_Bytime.SetTime(&PlayStart);
	
	//设置滚动条的位置
	m_slider_playback_bytime.SetRange(0,100);
	m_slider_playback_bytime.SetPos(0);
	m_slider_mute_bytime.SetRange(0,100);
	m_slider_mute_bytime.SetPos(100);
	m_progress_present.SetRange(0,100);
	m_progress_present.SetPos(0);
	
	return TRUE; 
}

void CDlg_Playback_Download_Bytime::OnBtnPlaybackPlayBytime() 
{
	BeginWaitCursor();
	
	CString str;
	GetDlgItem(IDC_BTN_PLAYBACK_PLAY_BYTIME)->GetWindowText(str);
	if(  theApp.m_LoadString( _T(" IDS_PLAYBACK_PLAY "))  == str )
	{
		CTime begin_year,begin_time,end_year,end_time;	
		m_dBeginYear_Bytime.GetTime( begin_year );
		m_dBeginTime_Bytime.GetTime( begin_time );
		m_dEndYear_Bytime.GetTime( end_year );
		m_dEndTime_Bytime.GetTime( end_time );
		
		Playback_BeginTime_DateInfo.year = begin_year.GetYear();
		Playback_BeginTime_DateInfo.month = begin_year.GetMonth();
		Playback_BeginTime_DateInfo.date = begin_year.GetDay();
		Playback_BeginTime_TimeInfo.hour = begin_time.GetHour();
		Playback_BeginTime_TimeInfo.minute = begin_time.GetMinute();
		Playback_BeginTime_TimeInfo.second = begin_time.GetSecond();
		
		Playback_EndTime_DateInfo.year = end_year.GetYear();
		Playback_EndTime_DateInfo.month = end_year.GetMonth();
		Playback_EndTime_DateInfo.date = end_year.GetDay();
		Playback_EndTime_TimeInfo.hour = end_time.GetHour();
		Playback_EndTime_TimeInfo.minute = end_time.GetMinute();
		Playback_EndTime_TimeInfo.second = end_time.GetSecond();
		
		ASSERT(m_sPlayback_Bytime.GetSafeHwnd());
		
		HWND hWnd = m_sPlayback_Bytime.GetSafeHwnd();
		//HHV_CLIENT_INFO	 hhvInfo;
		//strcpy( hhvInfo.connInfo.ip, "192.168.123.59" );
		//hhvInfo.connInfo.port = 20000;
		//hhvInfo.channel = i;
		SYSTEM_VIDEO_FILE	sysFile;
		memcpy( &sysFile.start_date, &Playback_BeginTime_DateInfo, sizeof(DATE_INFO) );
		memcpy( &sysFile.start_time, &Playback_BeginTime_TimeInfo, sizeof(TIME_INFO) );
		memcpy( &sysFile.end_date, &Playback_EndTime_DateInfo, sizeof(DATE_INFO) );
		memcpy( &sysFile.end_time, &Playback_EndTime_TimeInfo, sizeof(TIME_INFO) );		

		int ret = g_playerMgr.StartPlayBackByTime(hWnd, &sysFile, "192.168.123.59", 20000);
		if( ret < 0 )
		{
			MessageBox("监视出错");
		}	
	
	}
	EndWaitCursor();	
}
