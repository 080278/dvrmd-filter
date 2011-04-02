// ServerPlaybackSettingsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DVRMD_Filter.h"
#include "ServerPlaybackSettingsDlg.h"
#include "afxdialogex.h"


// CServerPlaybackSettingsDlg dialog

IMPLEMENT_DYNAMIC(CServerPlaybackSettingsDlg, CPropertyPage)

CServerPlaybackSettingsDlg::CServerPlaybackSettingsDlg()
	: CPropertyPage(CServerPlaybackSettingsDlg::IDD)
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
END_MESSAGE_MAP()


// CServerPlaybackSettingsDlg message handlers
