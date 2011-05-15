// PlayCtrlPanel.cpp : implementation file
//

#include "stdafx.h"
#include "DVRMD_Filter.h"
#include "PlayCtrlPanel.h"
#include "afxdialogex.h"


// CPlayCtrlPanel dialog

IMPLEMENT_DYNAMIC(CPlayCtrlPanel, CDialog)

CPlayCtrlPanel::CPlayCtrlPanel(CWnd* pParent /*=NULL*/)
	: CDialog(CPlayCtrlPanel::IDD, pParent)
{

}

CPlayCtrlPanel::~CPlayCtrlPanel()
{
}

void CPlayCtrlPanel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPlayCtrlPanel, CDialog)
END_MESSAGE_MAP()


// CPlayCtrlPanel message handlers
