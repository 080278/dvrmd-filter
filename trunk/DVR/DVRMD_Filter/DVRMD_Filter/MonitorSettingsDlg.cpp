// MonitorSettingsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DVRMD_Filter.h"
#include "MonitorSettingsDlg.h"
#include "afxdialogex.h"
#include "PlayerDlg.h"

#define MAX_CHANNEL_NUM		16

// CMonitorSettingsDlg dialog

IMPLEMENT_DYNAMIC(CMonitorSettingsDlg, CPropertyPage)

CMonitorSettingsDlg::CMonitorSettingsDlg(CPlayerDlg* pPlayer)
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
	ON_BN_CLICKED(IDC_CHANGE_CHANNEL, &CMonitorSettingsDlg::OnBnClickedChangeChannel)
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
	CWnd* pWnd = GetDlgItem(IDC_COMBO_WINNUM);
	pWnd->GetWindowText(csWndNum);
	if (csWndNum.IsEmpty())
		m_pPlayer->GetPlayer()->GetDVRSettings().m_nRenderWndNum = 1;
	else
		m_pPlayer->GetPlayer()->GetDVRSettings().m_nRenderWndNum = _ttoi(csWndNum);

	m_pPlayer->StartMonitor();
	SetState();
}


BOOL CMonitorSettingsDlg::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	CComboBox* pChannelComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_CHANNEL);
	pChannelComboBox->ResetContent();
	for (int i = 0; i < MAX_CHANNEL_NUM; ++i)
	{
		CString csNum;
		csNum.Format(_T("%d"), i);
		pChannelComboBox->AddString(csNum);
	}

	if (m_pPlayer->GetPlayer()->GetDVRSettings().m_nRenderWndNum > 0)
	{
		CString csWndNum;
		csWndNum.Format(_T("%d"), m_pPlayer->GetPlayer()->GetDVRSettings().m_nRenderWndNum);
		CComboBox* pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_WINNUM);
		pComboBox->SelectString(-1, csWndNum);
		//GetDlgItem(IDC_COMBO_WINNUM)->SetWindowText(csWndNum);
	}
	SetState();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CMonitorSettingsDlg::SetState()
{
	CComboBox* pWndComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_WININDEX);

	pWndComboBox->ResetContent();

	for (int i = 0; i < m_pPlayer->GetPlayer()->GetDVRSettings().m_nRenderWndNum; ++i)
	{
		CString csNum;
		csNum.Format(_T("%d"), i);
		pWndComboBox->AddString(csNum);
	}
}

void CMonitorSettingsDlg::OnBnClickedChangeChannel()
{
	CComboBox* pWndComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_WININDEX);
	CComboBox* pChannelComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_CHANNEL);
	if (pWndComboBox && 
		pWndComboBox->GetCurSel() != CB_ERR	&& 
		pChannelComboBox &&
		pChannelComboBox->GetCurSel() != CB_ERR)
	{
		CString csWndIndex, csChannelIndex;
		pWndComboBox->GetWindowText(csWndIndex);
		pChannelComboBox->GetWindowText(csChannelIndex);
		m_pPlayer->GetPlayer()->SetWndChannel(_ttoi(csWndIndex), _ttoi(csChannelIndex));
	}
}