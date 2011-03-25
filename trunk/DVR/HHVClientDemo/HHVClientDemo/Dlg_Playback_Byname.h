#if !defined(AFX_DLG_PLAYBACK_BYNAME_H__549EE966_6851_4CA8_B8DE_FCAEA5F16CB2__INCLUDED_)
#define AFX_DLG_PLAYBACK_BYNAME_H__549EE966_6851_4CA8_B8DE_FCAEA5F16CB2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_Playback_Byname.h : header file
#include "TextProgressCtrl.h"
//

/////////////////////////////////////////////////////////////////////////////
// CDlg_Playback_Byname dialog

class CDlg_Playback_Byname : public CDialog
{
// Construction
public:
	CDlg_Playback_Byname(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlg_Playback_Byname)
	enum { IDD = IDD_DLG_PLAYBACK_BYNAME };
	CTextProgressCtrl	m_progress_present;
	CTextProgressCtrl	m_progress_all;
	CSliderCtrl			m_slider_mute;
	CSliderCtrl			m_slider_nowplace;
	CStatic				m_sPlayback_Byname;
	CListCtrl			m_list_find_result;
	CDateTimeCtrl		m_dEndYear;
	CDateTimeCtrl		m_dEndTime;
	CDateTimeCtrl		m_dBeginYear;
	CDateTimeCtrl		m_dBeginTime;
	CComboBox			m_cmb_file_type;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_Playback_Byname)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg_Playback_Byname)
	afx_msg void OnBtnSearchFile();
	afx_msg void OnBtnDownload();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnAllChannel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_PLAYBACK_BYNAME_H__549EE966_6851_4CA8_B8DE_FCAEA5F16CB2__INCLUDED_)
