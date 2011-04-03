// FilePlaybackSettings.cpp : implementation file
//

#include "stdafx.h"
#include "DVRMD_Filter.h"
#include "FilePlaybackSettings.h"
#include "afxdialogex.h"
#include "PlayerDlg.h"


// CFilePlaybackSettings dialog

IMPLEMENT_DYNAMIC(CFilePlaybackSettingsDlg, CPropertyPage)

CFilePlaybackSettingsDlg::CFilePlaybackSettingsDlg(CPlayerDlg* pMainDlg)
	: CPropertyPage(CFilePlaybackSettingsDlg::IDD)
	, m_pMainDlg(pMainDlg)
{

}

CFilePlaybackSettingsDlg::~CFilePlaybackSettingsDlg()
{
}

void CFilePlaybackSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFilePlaybackSettingsDlg, CPropertyPage)
	ON_BN_CLICKED(IDC_OPENFILE, &CFilePlaybackSettingsDlg::OnBnClickedOpenfile)
END_MESSAGE_MAP()


// CFilePlaybackSettings message handlers


void CFilePlaybackSettingsDlg::OnBnClickedOpenfile()
{
	//CString csMediaFile;
	//GetDlgItem(IDC_MEDIA_FILEPATH)->GetWindowText(csMediaFile);

	m_pMainDlg->PostMessage(WM_COMMAND, IDC_OPENFILE, 0);
}

CString CFilePlaybackSettingsDlg::GetPathName()
{
	return m_csMediaFile;
}

void CFilePlaybackSettingsDlg::SetPathName(LPCTSTR szPath)
{
	m_csMediaFile = szPath;
	if (IsWindow(m_hWnd))
	{
		GetDlgItem(IDC_MEDIA_FILEPATH)->SetWindowText(szPath);
	}
}

BOOL CFilePlaybackSettingsDlg::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	if (!m_csMediaFile.IsEmpty())
	{
		GetDlgItem(IDC_MEDIA_FILEPATH)->SetWindowText(m_csMediaFile);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
