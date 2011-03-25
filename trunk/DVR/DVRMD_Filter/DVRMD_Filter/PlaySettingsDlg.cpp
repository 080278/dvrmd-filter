// DVRPlaySettings.cpp : implementation file
//

#include "stdafx.h"
#include "DVRMD_Filter.h"
#include "PlaySettingsDlg.h"
#include "afxdialogex.h"


// CDVRPlaySettings dialog

IMPLEMENT_DYNAMIC(CPlaySettingsDlg, CPropertyPage)

CPlaySettingsDlg::CPlaySettingsDlg()
	: CPropertyPage(CPlaySettingsDlg::IDD)
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
END_MESSAGE_MAP()


// CDVRPlaySettings message handlers
