// HHVClientDlg.h : header file
//

#if !defined(AFX_HHVCLIENTDLG_H__D462295A_F6CB_4762_B198_B67042058881__INCLUDED_)
#define AFX_HHVCLIENTDLG_H__D462295A_F6CB_4762_B198_B67042058881__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "./HWndManager.h"

#include "Dlg_Playback_Download.h"

/////////////////////////////////////////////////////////////////////////////
// CHHVClientDlg dialog

class CHHVClientDlg : public CDialog
{
// Construction
public:
	CHHVClientDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CHHVClientDlg)
	enum { IDD = IDD_HHVCLIENT_DIALOG };
	CString	m_strIP;
	int		m_nPort;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHHVClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

	CHWndManager	m_HwdMgr;

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CHHVClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnStaticHwnd();
	afx_msg void OnBtnRealplay();
	afx_msg void OnBtnRealstop();
	afx_msg void OnBtnPlaybackDownload();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HHVCLIENTDLG_H__D462295A_F6CB_4762_B198_B67042058881__INCLUDED_)
