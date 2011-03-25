#if !defined(AFX_DLG_PLAYBACK_DOWNLOAD_BYTIME_H__086A5B12_0518_4591_A15C_3CD0E90D1107__INCLUDED_)
#define AFX_DLG_PLAYBACK_DOWNLOAD_BYTIME_H__086A5B12_0518_4591_A15C_3CD0E90D1107__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_Playback_Download_Bytime.h : header file
#include "TextProgressCtrl.h"
#include "struct_TCPServ.h"

/////////////////////////////////////////////////////////////////////////////
// CDlg_Playback_Download_Bytime dialog

class CDlg_Playback_Download_Bytime : public CDialog
{
// Construction
public:
	CDlg_Playback_Download_Bytime(CWnd* pParent = NULL);   // standard constructor

	DATE_INFO	Playback_BeginTime_DateInfo;
	TIME_INFO	Playback_BeginTime_TimeInfo;

	DATE_INFO	Playback_EndTime_DateInfo;
	TIME_INFO	Playback_EndTime_TimeInfo;
	
	LONG        m_lPlayback_Bytime_Handle;

// Dialog Data
	//{{AFX_DATA(CDlg_Playback_Download_Bytime)
	enum { IDD = IDD_DLG_PLAYBACK_BYTIME };
	CSliderCtrl	m_slider_playback_bytime;
	CSliderCtrl	m_slider_mute_bytime;
	CTextProgressCtrl	m_progress_present;
	CDateTimeCtrl	m_dEndYear_Bytime;
	CDateTimeCtrl	m_dEndTime_Bytime;
	CDateTimeCtrl	m_dBeginYear_Bytime;
	CDateTimeCtrl	m_dBeginTime_Bytime;
	CComboBox	m_cmb_channel;
	CStatic	m_sPlayback_Bytime;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_Playback_Download_Bytime)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg_Playback_Download_Bytime)
	afx_msg void OnBtnDownloadBytime();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnPlaybackPlayBytime();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_PLAYBACK_DOWNLOAD_BYTIME_H__086A5B12_0518_4591_A15C_3CD0E90D1107__INCLUDED_)
