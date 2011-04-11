#pragma once

#include "DVRPlayer.h"
// CDVRPlaySettings dialog

class CPlaySettingsDlg : public CPropertyPage
{
	DECLARE_DYNAMIC(CPlaySettingsDlg)

public:
	CPlaySettingsDlg(CDVRPlayer* pPlayer);
	virtual ~CPlaySettingsDlg();

// Dialog Data
	enum { IDD = IDD_MEDIASERVER_SETTINGS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	CDVRPlayer*	m_pPlayer;
	void SetState();
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedLogin();
	afx_msg void OnBnClickedLogout();
};
