// Dlg_Playback_Byname.cpp : implementation file
//

#include "stdafx.h"
#include "HHVClient.h"
#include "Dlg_Playback_Byname.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_Playback_Byname dialog


CDlg_Playback_Byname::CDlg_Playback_Byname(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_Playback_Byname::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg_Playback_Byname)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlg_Playback_Byname::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_Playback_Byname)
	DDX_Control(pDX, IDC_PROGRESS_PRESENT, m_progress_present);
	DDX_Control(pDX, IDC_PROGRESS_ALL, m_progress_all);
	DDX_Control(pDX, IDC_SLIDER_MUTE, m_slider_mute);
	DDX_Control(pDX, IDC_SLIDER_NOWPLACE, m_slider_nowplace);
	DDX_Control(pDX, IDC_STATIC_PLAYBACK_BYNAME, m_sPlayback_Byname);
	DDX_Control(pDX, IDC_LIST_FIND_RESULT, m_list_find_result);
	DDX_Control(pDX, IDC_DATETIMEPICKER_ENDYEAR, m_dEndYear);
	DDX_Control(pDX, IDC_DATETIMEPICKER_ENDTIMER, m_dEndTime);
	DDX_Control(pDX, IDC_DATETIMEPICKER_BEGINYEAR, m_dBeginYear);
	DDX_Control(pDX, IDC_DATETIMEPICKER_BEGINTIMER, m_dBeginTime);
	DDX_Control(pDX, IDC_COMBO_FILE_TYPE, m_cmb_file_type);
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_Playback_Byname, CDialog)
	//{{AFX_MSG_MAP(CDlg_Playback_Byname)
	ON_BN_CLICKED(IDC_BTN_SEARCH_FILE, OnBtnSearchFile)
	ON_BN_CLICKED(IDC_BTN_DOWNLOAD, OnBtnDownload)
	ON_BN_CLICKED(IDC_BTN_ALL_CHANNEL, OnBtnAllChannel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_Playback_Byname message handlers

void CDlg_Playback_Byname::OnBtnSearchFile() 
{
	BeginWaitCursor();
	UpdateData(TRUE);
	
	BOOL AllChannelNoCheck;
	AllChannelNoCheck = TRUE;
	
	//判断是否所有的通道都没有选中
	int i = 0;
	for(; i < 16; i++)
	{
		if( IsDlgButtonChecked(IDC_CHK_CHAN1 + i))
		{
            AllChannelNoCheck = FALSE;
		}
	}//for
	
	if( AllChannelNoCheck )
	{		
		MessageBox( theApp.m_LoadString( _T(" IDS_SELECT_CHANNEL ")) );
		return;
	}
	
	m_list_find_result.DeleteAllItems();
	
	DWORD dwFileType;
	dwFileType = m_cmb_file_type.GetCurSel(); 
	
	if(5 == dwFileType)
	{
		dwFileType = 0xff;
	}
	
	DWORD channel = 0x00000001;
	for(i = 0; i < 16; i++)
	{
		if( IsDlgButtonChecked(IDC_CHK_CHAN1 + i))
		{
            channel |= 0x00000001<<i;
		}
	}//for
	
	CTime begin_year,begin_time,end_year,end_time;
	
	m_dBeginYear.GetTime( begin_year );
	m_dBeginTime.GetTime( begin_time );
	m_dEndYear.GetTime( end_year );
	m_dEndTime.GetTime( end_time );
}

void CDlg_Playback_Byname::OnBtnDownload() 
{
	// TODO: Add your control notification handler code here
	
}

BOOL CDlg_Playback_Byname::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//选则文件类型
	m_cmb_file_type.AddString( theApp.m_LoadString( _T(" IDS_TIMING_VEDIO_BYNAME ")) );
	m_cmb_file_type.AddString( theApp.m_LoadString( _T(" IDS_MOBILE_DETECTION_BYNAME ")) );
	m_cmb_file_type.AddString( theApp.m_LoadString( _T(" IDS_ALARM_TRIGGER_BYNAME ")) );
	m_cmb_file_type.AddString( theApp.m_LoadString( _T(" IDS_ORDER_TRIGGER_BYNAME ")) );
	m_cmb_file_type.AddString( theApp.m_LoadString( _T(" IDS_MANUAL_VIDEO_BYNAME ")) );
	m_cmb_file_type.AddString( theApp.m_LoadString( _T(" IDS_ALL_TYPE_BYNAME ")) );
	m_cmb_file_type.SetCurSel(5);
	
	//查询结果列表项
	m_list_find_result.InsertColumn(0, theApp.m_LoadString( _T(" IDS_NO_BYNAME ")) , LVCFMT_LEFT, 40);
	m_list_find_result.InsertColumn(1, theApp.m_LoadString( _T(" IDS_CHANNEL_BYNAME ")) , LVCFMT_LEFT, 60);
	m_list_find_result.InsertColumn(2, theApp.m_LoadString( _T(" IDS_FILENAME_BYNAME ")) , LVCFMT_LEFT, 140);
	m_list_find_result.InsertColumn(3, theApp.m_LoadString( _T(" IDS_BEGIN_TIME_BYNAME ")) , LVCFMT_LEFT, 150);
	m_list_find_result.InsertColumn(4, theApp.m_LoadString( _T(" IDS_END_TIME_BYNAME ")) , LVCFMT_LEFT, 150);
	m_list_find_result.InsertColumn(5, theApp.m_LoadString( _T(" IDS_FILE_SIZE_BYNAME ")) , LVCFMT_LEFT, 95);
	
	DWORD dwStyle = ListView_GetExtendedListViewStyle(m_list_find_result.GetSafeHwnd());	
	dwStyle |= LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT;
	ListView_SetExtendedListViewStyle (m_list_find_result.GetSafeHwnd(),dwStyle);
	
	
	m_dBeginYear.SetFormat("yyy-MM-dd");
	m_dEndYear.SetFormat("yyy-MM-dd");   
	m_dBeginTime.SetFormat("HH:mm:ss"); 
	m_dEndTime.SetFormat("HH:mm:ss"); 
	
	CTime        PlayStart;   
	PlayStart = CTime::GetCurrentTime(   );  
	PlayStart -= CTimeSpan(1, 0, 0, 0);   
	m_dBeginYear.SetTime(&PlayStart);
	
	//设置滚动条的位置
	m_slider_nowplace.SetRange(0,100);
	m_slider_nowplace.SetPos(0);
	m_slider_mute.SetRange(0,100);
	m_slider_mute.SetPos(100);
	m_progress_present.SetRange(0,100);
	m_progress_present.SetPos(0);
	m_progress_all.SetRange(0,100);
	m_progress_all.SetPos(0);
	
	
	//Contral_bRet = FALSE;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlg_Playback_Byname::OnBtnAllChannel() 
{
	int count = 0;
	int i = 0;
	
	for(i = 0; i < 16; i++)
	{
		if(IsDlgButtonChecked(IDC_CHK_CHAN1 + i)) count++;
	}
	
	if( count < 16 )
	{
		for( i = 0; i < 16; i++)
		{
			((CButton*)GetDlgItem(IDC_CHK_CHAN1+i))->SetCheck(1);	
		}
	}
	else
	{
		for( i = 0; i < 16; i++)
		{
			((CButton*)GetDlgItem(IDC_CHK_CHAN1+i))->SetCheck(0);	
		}
	}	
}
