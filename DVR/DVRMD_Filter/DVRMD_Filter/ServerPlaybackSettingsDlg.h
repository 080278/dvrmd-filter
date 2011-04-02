#pragma once


// CServerPlaybackSettingsDlg dialog

class CServerPlaybackSettingsDlg : public CPropertyPage
{
	DECLARE_DYNAMIC(CServerPlaybackSettingsDlg)

public:
	CServerPlaybackSettingsDlg();
	virtual ~CServerPlaybackSettingsDlg();

// Dialog Data
	enum { IDD = IDD_PLAYBACK_SETTINGS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
