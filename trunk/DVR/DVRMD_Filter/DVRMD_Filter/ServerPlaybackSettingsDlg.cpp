// ServerPlaybackSettingsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DVRMD_Filter.h"
#include "ServerPlaybackSettingsDlg.h"
#include "afxdialogex.h"
#include "NetDef.h"
#include "DVRPlayer.h"


// CServerPlaybackSettingsDlg dialog

IMPLEMENT_DYNAMIC(CServerPlaybackSettingsDlg, CPropertyPage)

CServerPlaybackSettingsDlg::CServerPlaybackSettingsDlg(CDVRPlayer* pPlayer)
	: CPropertyPage(CServerPlaybackSettingsDlg::IDD)
	, m_pDVRPlayer(pPlayer)
{

}

CServerPlaybackSettingsDlg::~CServerPlaybackSettingsDlg()
{
}

void CServerPlaybackSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CServerPlaybackSettingsDlg, CPropertyPage)
	ON_BN_CLICKED(IDC_PLAYBACK, &CServerPlaybackSettingsDlg::OnBnClickedPlayback)
END_MESSAGE_MAP()


// CServerPlaybackSettingsDlg message handlers


void CServerPlaybackSettingsDlg::OnBnClickedPlayback()
{
	DATE_INFO	startDate, endDate;
	TIME_INFO	startTime, endTime;

	CDateTimeCtrl* pStartDate = (CDateTimeCtrl*)GetDlgItem(IDC_START_DATE);
	CDateTimeCtrl* pStartTime = (CDateTimeCtrl*)GetDlgItem(IDC_START_TIME);
	CDateTimeCtrl* pEndDate = (CDateTimeCtrl*)GetDlgItem(IDC_END_DATE);
	CDateTimeCtrl* pEndTime = (CDateTimeCtrl*)GetDlgItem(IDC_END_TIME);

	CTime tm;
	pStartDate->GetTime(tm);
	startDate.year = tm.GetYear();
	startDate.month = tm.GetMonth();
	startDate.date = tm.GetDay();
	pStartTime->GetTime(tm);
	startTime.hour = tm.GetHour();
	startTime.minute =tm.GetMinute();
	startTime.second = tm.GetSecond();

	pEndDate->GetTime(tm);
	endDate.year = tm.GetYear();
	endDate.month = tm.GetMonth();
	endDate.date = tm.GetDay();
	pEndTime->GetTime(tm);
	endTime.hour = tm.GetHour();
	endTime.minute =tm.GetMinute();
	endTime.second = tm.GetSecond();

	SYSTEM_VIDEO_FILE sysFile;
	memcpy( &sysFile.start_date, &startDate, sizeof(DATE_INFO) );
	memcpy( &sysFile.start_time, &startTime, sizeof(TIME_INFO) );
	memcpy( &sysFile.end_date, &endDate, sizeof(DATE_INFO) );
	memcpy( &sysFile.end_time, &endTime, sizeof(TIME_INFO) );

	m_pDVRPlayer->StartPlayback(sysFile);
}
