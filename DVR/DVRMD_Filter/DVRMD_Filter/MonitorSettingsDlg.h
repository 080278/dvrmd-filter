#pragma once

class CPlayerDlg;
// CMonitorSettingsDlg dialog

class CMonitorSettingsDlg : public CPropertyPage
{
	DECLARE_DYNAMIC(CMonitorSettingsDlg)

public:
	CMonitorSettingsDlg(CPlayerDlg* pPlayer);
	virtual ~CMonitorSettingsDlg();

// Dialog Data
	enum { IDD = IDD_MONITOR_SETTINGS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

protected:
	CPlayerDlg* m_pPlayer;
public:
	afx_msg void OnBnClickedWatchEnd();
	afx_msg void OnBnClickedWatchStart();
	virtual BOOL OnInitDialog();

protected:
	void SetState();
public:
	afx_msg void OnBnClickedChangeChannel();
};
