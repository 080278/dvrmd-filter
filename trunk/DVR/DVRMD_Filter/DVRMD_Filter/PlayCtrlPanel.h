#pragma once


// CPlayCtrlPanel dialog

class CPlayCtrlPanel : public CDialog
{
	DECLARE_DYNAMIC(CPlayCtrlPanel)

public:
	CPlayCtrlPanel(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPlayCtrlPanel();

// Dialog Data
	enum { IDD = IDD_CTRL_PANEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
