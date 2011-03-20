
// DVRMDFrameDlg.h : header file
//

#pragma once
#include "dvrmd_filterctrl1.h"


// CDVRMDFrameDlg dialog
class CDVRMDFrameDlg : public CDialog
{
// Construction
public:
	CDVRMDFrameDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_DVRMDFRAME_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CDvrmd_filterctrl1 m_DVRPlayer;
	afx_msg void OnDestroy();
};
