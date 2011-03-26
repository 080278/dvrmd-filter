// Seek.cpp : implementation file
//

#include "stdafx.h"
#include "player.h"
#include "Seek.h"
#include "DVRPlayer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSeek dialog


CSeek::CSeek(CDVRPlayer* pPlayer, CWnd* pParent /*=NULL*/)
	: CDialog(CSeek::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSeek)
	m_nSeekType = 0;
	m_nValue	= 0;
	//}}AFX_DATA_INIT
	m_pParent	= pParent;
	m_pDVRPlayer = pPlayer;
}


void CSeek::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSeek)
	DDX_Radio(pDX, IDC_BYFRAME, m_nSeekType);
	DDX_Text(pDX, IDC_VALUE, m_nValue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSeek, CDialog)
	//{{AFX_MSG_MAP(CSeek)
	ON_BN_CLICKED(IDC_SEEK, OnSeek)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSeek message handlers

void CSeek::OnSeek() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	if(m_nSeekType == 0)
	{
		if(m_nValue >= m_dwMaxFrameNum)
		{
			MessageBox(_T("Input frame number is over!"));
			return;
		}
		NAME(PlayM4_SetCurrentFrameNum)(m_pDVRPlayer->GetPort(), m_nValue);
	}
	else if(m_nSeekType == 1)
	{
		if(m_nValue > m_dwMaxTime)
		{
			MessageBox(_T("Input time is over!"));
			return;
		}
		NAME(PlayM4_SetPlayedTimeEx)(m_pDVRPlayer->GetPort(), m_nValue*1000);
	}
		
}

BOOL CSeek::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_dwMaxTime     = NAME(PlayM4_GetFileTime)(m_pDVRPlayer->GetPort());
	m_dwMaxFrameNum = NAME(PlayM4_GetFileTotalFrames)(m_pDVRPlayer->GetPort());
	CString csRange;
	csRange.Format(_T("Frame number range:%d~%d\r\nTime range(Seconds)£º%d~%d\r\n"), 0, m_dwMaxFrameNum, 0, m_dwMaxTime);
	GetDlgItem(IDC_RANGE)->SetWindowText(csRange);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSeek::OnOK() 
{
	// TODO: Add extra validation here
	if(m_pParent)
	{
		m_pParent->PostMessage(WM_SEEKOK, 0, 0);
	}
	else
	{
		CDialog::OnOK();
	}
}
