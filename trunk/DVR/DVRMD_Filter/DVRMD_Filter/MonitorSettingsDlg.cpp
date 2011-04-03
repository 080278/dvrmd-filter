// MonitorSettingsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DVRMD_Filter.h"
#include "MonitorSettingsDlg.h"
#include "afxdialogex.h"
#include "DVRPlayer.h"


// CMonitorSettingsDlg dialog

IMPLEMENT_DYNAMIC(CMonitorSettingsDlg, CPropertyPage)

CMonitorSettingsDlg::CMonitorSettingsDlg(CDVRPlayer* pPlayer)
	: CPropertyPage(CMonitorSettingsDlg::IDD)
	, m_pPlayer(pPlayer)
{

}

CMonitorSettingsDlg::~CMonitorSettingsDlg()
{
}

void CMonitorSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMonitorSettingsDlg, CPropertyPage)
	ON_BN_CLICKED(IDC_WATCH_END, &CMonitorSettingsDlg::OnBnClickedWatchEnd)
	ON_BN_CLICKED(IDC_WATCH_START, &CMonitorSettingsDlg::OnBnClickedWatchStart)
END_MESSAGE_MAP()


// CMonitorSettingsDlg message handlers


void CMonitorSettingsDlg::OnBnClickedWatchEnd()
{

	m_pPlayer->StopMonitor();
	SetState();
}


void CMonitorSettingsDlg::OnBnClickedWatchStart()
{
	CString csWndNum;
	GetDlgItem(IDC_COMBO_WINNUM)->GetWindowText(csWndNum);
	if (csWndNum.IsEmpty())
		m_pPlayer->GetDVRSettings().m_nRenderWndNum = 1;
	else
		m_pPlayer->GetDVRSettings().m_nRenderWndNum = _ttoi(csWndNum);

	m_pPlayer->StartMonitor();
	SetState();
}


BOOL CMonitorSettingsDlg::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	SetState();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CMonitorSettingsDlg::SetState()
{

}