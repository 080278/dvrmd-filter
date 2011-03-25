#if !defined(AFX_DLG_PLAYBACK_DOWNLOAD_H__7E1F940E_E30F_4271_A3C4_558491553844__INCLUDED_)
#define AFX_DLG_PLAYBACK_DOWNLOAD_H__7E1F940E_E30F_4271_A3C4_558491553844__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_Playback_Download.h : header file

#include "TabSheet.h"
#include "Dlg_Playback_Byname.h"
#include "Dlg_Playback_Download_Bytime.h"
//

/////////////////////////////////////////////////////////////////////////////
// CDlg_Playback_Download dialog

class CDlg_Playback_Download : public CDialog
{
// Construction
public:
	CDlg_Playback_Download(CWnd* pParent = NULL);   // standard constructor

	//定义属性页中的各个对话框
	CDlg_Playback_Byname				playback_byname_dlg;
	CDlg_Playback_Download_Bytime		playback_bytime_dlg;

// Dialog Data
	//{{AFX_DATA(CDlg_Playback_Download)
	enum { IDD = IDD_DLG_PLAYBACK_DOWNLOAD };
		// NOTE: the ClassWizard will add data members here
		CTabSheet	m_sheet_playback;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_Playback_Download)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg_Playback_Download)
	afx_msg void OnBtnPlaybackClose();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_PLAYBACK_DOWNLOAD_H__7E1F940E_E30F_4271_A3C4_558491553844__INCLUDED_)
