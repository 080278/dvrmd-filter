// DVRPlaySettings.cpp : implementation file
//

#include "stdafx.h"
#include "DVRMD_Filter.h"
#include "PlaySettingsDlg.h"
#include "afxdialogex.h"


// CDVRPlaySettings dialog

IMPLEMENT_DYNAMIC(CPlaySettingsDlg, CPropertyPage)

CPlaySettingsDlg::CPlaySettingsDlg(CDVRPlayer* pPlayer)
	: m_pPlayer(pPlayer)
	, CPropertyPage(CPlaySettingsDlg::IDD)
{

}

CPlaySettingsDlg::~CPlaySettingsDlg()
{
}

void CPlaySettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPlaySettingsDlg, CPropertyPage)
	ON_BN_CLICKED(IDC_LOGIN, &CPlaySettingsDlg::OnBnClickedLogin)
	ON_BN_CLICKED(IDC_LOGOUT, &CPlaySettingsDlg::OnBnClickedLogout)
END_MESSAGE_MAP()


// CDVRPlaySettings message handlers


BOOL CPlaySettingsDlg::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	SetState();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CPlaySettingsDlg::SetState()
{
	BOOL isLogined = m_pPlayer->IsLogined();

	CString csLoginInfo;
	if (isLogined)
	{
		GetDlgItem(IDC_LOGIN)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LOGOUT)->ShowWindow(SW_SHOW);
		csLoginInfo.Format(_T("»¶Ó­ %s"), m_pPlayer->GetDVRSettings().m_csUsername);
	}
	else
	{
		GetDlgItem(IDC_LOGIN)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LOGOUT)->ShowWindow(SW_HIDE);
		csLoginInfo = _T("ÇëµÇÂ¼£¡");
	}

	GetDlgItem(IDC_MEDIASERVER_IP)->EnableWindow(!isLogined);
	GetDlgItem(IDC_MEDIASERVER_PORT)->EnableWindow(!isLogined);
	GetDlgItem(IDC_USERNAME)->EnableWindow(!isLogined);
	GetDlgItem(IDC_PASSWORD)->EnableWindow(!isLogined);

	GetDlgItem(IDC_LOGININFO)->SetWindowText(csLoginInfo);

}
void CPlaySettingsDlg::OnBnClickedLogin()
{
	CString csIP, csPort, csUName, csPwd;
	GetDlgItem(IDC_MEDIASERVER_IP)->GetWindowText(csIP);
	GetDlgItem(IDC_MEDIASERVER_PORT)->GetWindowText(csPort);
	GetDlgItem(IDC_USERNAME)->GetWindowText(csUName);
	GetDlgItem(IDC_PASSWORD)->GetWindowText(csPwd);
	if (!csIP.IsEmpty() && !csPort.IsEmpty() && !csUName.IsEmpty() && !csPwd.IsEmpty())
	{
		m_pPlayer->Login(csUName, csPwd, csIP, _ttoi(csPort));
	}
	SetState();
}


void CPlaySettingsDlg::OnBnClickedLogout()
{
	m_pPlayer->Logout();
	SetState();
}
