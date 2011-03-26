// Info.cpp : implementation file
//

#include "stdafx.h"
#include "player.h"
#include "Info.h"
#include "DVRPlayer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInfo dialog


CInfo::CInfo(CDVRPlayer* pPlayer, CWnd* pParent /*=NULL*/)
	: CDialog(CInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInfo)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_dwRows = 0;
	m_bInit = FALSE;
	m_strTemp  = _T("");
	m_pDVRPlayer = pPlayer;
}


void CInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInfo)
	DDX_Control(pDX, IDC_LIST_INFO, m_ctrlListInfo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInfo, CDialog)
	//{{AFX_MSG_MAP(CInfo)
	ON_BN_CLICKED(IDC_REFRESH, OnRefresh)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInfo message handlers

void CInfo::OnRefresh() 
{
	// TODO: Add your control notification handler code here
	int nRows = m_dwRows;

		//invalid after play()
	BOOL bOverlay=NAME(PlayM4_GetOverlayMode)(m_pDVRPlayer->GetPort());
	if(!m_bInit)
	{
		m_strTemp.Format(_T("Is OVERLAY Surface"));
		m_ctrlListInfo.InsertItem(LVIF_TEXT|LVIF_STATE, nRows, m_strTemp, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED, 0, 0);
	}

	if(bOverlay)
	{
		m_strTemp.Format(_T("yes   The color key:0x%X"),NAME(PlayM4_GetColorKey)(m_pDVRPlayer->GetPort()));
	}
	else
	{
		m_strTemp.Format(_T("No"));
	}

	m_ctrlListInfo.SetItemText(nRows,1,m_strTemp);
	nRows ++;

	if(!m_bInit)
	{
		m_strTemp.Format(_T("Max display buffers(frame)"));
		m_ctrlListInfo.InsertItem(LVIF_TEXT|LVIF_STATE, nRows, m_strTemp, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED, 0, 0);
	}

	m_strTemp.Format(_T("%d"),NAME(PlayM4_GetDisplayBuf)(m_pDVRPlayer->GetPort()));
	m_ctrlListInfo.SetItemText(nRows,1,m_strTemp);
	nRows ++;

	if(!m_bInit)
	{
		m_strTemp.Format(_T("Volume"));
		m_ctrlListInfo.InsertItem(LVIF_TEXT|LVIF_STATE, nRows, m_strTemp, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED, 0, 0);
	}
	m_strTemp.Format(_T("%x"),NAME(PlayM4_GetVolume)(m_pDVRPlayer->GetPort()));
	m_ctrlListInfo.SetItemText(nRows,1,m_strTemp);
	nRows ++;

	if(!m_bInit)
	{
		m_strTemp.Format(_T("Image qulity"));
		m_ctrlListInfo.InsertItem(LVIF_TEXT|LVIF_STATE, nRows, m_strTemp, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED, 0, 0);
	}

	BOOL bHiQuality=FALSE;
	NAME(PlayM4_GetPictureQuality)(m_pDVRPlayer->GetPort(),&bHiQuality);
	if(bHiQuality)
	{
		m_strTemp=_T("High");
	}
	else
	{
		m_strTemp=_T("Low");
	}
	m_ctrlListInfo.SetItemText(nRows,1,m_strTemp);
	nRows ++;

	if(!m_bInit)
	{
		m_strTemp.Format(_T("TIMER"));
		m_ctrlListInfo.InsertItem(LVIF_TEXT|LVIF_STATE, nRows, m_strTemp, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED, 0, 0);
	}
	DWORD nTimer;
	NAME(PlayM4_GetTimerType)(m_pDVRPlayer->GetPort(),&nTimer,NULL);
	if(nTimer==TIMER_1)
	{
		m_strTemp=_T("TIMER_1");
	}
	else
	{
		m_strTemp=_T("TIMER_2");
	}
	m_ctrlListInfo.SetItemText(nRows,1,m_strTemp);
	nRows ++;

	DWORD nVideoRender =NAME(PlayM4_GetBufferValue)(m_pDVRPlayer->GetPort(),BUF_VIDEO_RENDER);
	DWORD nAudioRender =NAME(PlayM4_GetBufferValue)(m_pDVRPlayer->GetPort(),BUF_AUDIO_RENDER);
	DWORD nVideoSource =NAME(PlayM4_GetBufferValue)(m_pDVRPlayer->GetPort(),BUF_VIDEO_SRC);
	DWORD nAudioSource =NAME(PlayM4_GetBufferValue)(m_pDVRPlayer->GetPort(),BUF_AUDIO_SRC);
	
	if(!m_bInit)
	{
		m_strTemp.Format(_T("Video render frames"));
		m_ctrlListInfo.InsertItem(LVIF_TEXT|LVIF_STATE, nRows, m_strTemp, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED, 0, 0);
	}
	m_strTemp.Format(_T("%d"),nVideoRender);
	m_ctrlListInfo.SetItemText(nRows,1,m_strTemp);
	nRows ++;

	if(!m_bInit)
	{
		m_strTemp.Format(_T("Audio render frames"));
		m_ctrlListInfo.InsertItem(LVIF_TEXT|LVIF_STATE, nRows, m_strTemp, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED, 0, 0);
	}
	m_strTemp.Format(_T("%d"),nAudioRender);
	m_ctrlListInfo.SetItemText(nRows,1,m_strTemp);
	nRows ++;

	if(!m_bInit)
	{
		m_strTemp.Format(_T("Video Source size"));
		m_ctrlListInfo.InsertItem(LVIF_TEXT|LVIF_STATE, nRows, m_strTemp, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED, 0, 0);
	}
	m_strTemp.Format(_T("%d"),nVideoSource);
	m_ctrlListInfo.SetItemText(nRows,1,m_strTemp);
	nRows ++;

	if(!m_bInit)
	{
		m_strTemp.Format(_T("Audio Source size"));
		m_ctrlListInfo.InsertItem(LVIF_TEXT|LVIF_STATE, nRows, m_strTemp, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED, 0, 0);
	}
	m_strTemp.Format(_T("%d"),nAudioSource);
	m_ctrlListInfo.SetItemText(nRows,1,m_strTemp);
	nRows ++;
}

BOOL CInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//m_ListCtrl
	m_ctrlListInfo.InsertColumn(0, _T("Description"), LVCFMT_LEFT, 200);
	m_ctrlListInfo.InsertColumn(1, _T("value"), LVCFMT_LEFT, 150);			
	m_ctrlListInfo.SetExtendedStyle(LVS_EX_FULLROWSELECT);


#if (WINVER > 0x0400)
	//If only one adapter ,the return value is 0;
	DWORD nVal=NAME(PlayM4_GetDDrawDeviceTotalNums)();
	if(nVal>=1)
	{
		m_strTemp.Format(_T("Video adaper numbers"));
		m_ctrlListInfo.InsertItem(LVIF_TEXT|LVIF_STATE, m_dwRows, m_strTemp, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED, 0, 0);
		m_strTemp.Format(_T("%d"), nVal);
		m_ctrlListInfo.SetItemText(m_dwRows,1,m_strTemp);
		m_dwRows ++;

		for(DWORD nCount=1;nCount<=nVal;nCount++) 
		{
			DWORD nNameLen = 50;
			char pDriverDesp[50];
			char pDriverName[50];
			ZeroMemory(pDriverDesp, nNameLen);
			ZeroMemory(pDriverName, nNameLen);
			HMONITOR hMonitor;
			NAME(PlayM4_GetDDrawDeviceInfo)(nCount,pDriverDesp,nNameLen,pDriverName,nNameLen,&hMonitor);
			m_strTemp.Format(_T("----Adatper<%d>"), nCount-1);
			m_ctrlListInfo.InsertItem(LVIF_TEXT|LVIF_STATE, m_dwRows, m_strTemp, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED, 0, 0);
			m_ctrlListInfo.SetItemText(m_dwRows,1,CA2T(pDriverDesp));
			m_dwRows ++;

			m_strTemp.Format(_T("----Driver<%d>"), nCount-1);
			m_ctrlListInfo.InsertItem(LVIF_TEXT|LVIF_STATE, m_dwRows, m_strTemp, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED, 0, 0);
			m_ctrlListInfo.SetItemText(m_dwRows,1,CA2T(pDriverName));
			m_dwRows ++;
		}
	}
	else
	{
		m_strTemp.Format(_T("Only one video adapter"));
		m_ctrlListInfo.InsertItem(LVIF_TEXT|LVIF_STATE, m_dwRows, m_strTemp, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED, 0, 0);
		m_ctrlListInfo.SetItemText(m_dwRows,1,_T("none"));
		m_dwRows ++;
	}
#endif

	OnRefresh();

	m_bInit = TRUE;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
