#pragma once


// CServerPlaybackSettingsDlg dialog
class CDVRPlayer;

class CServerPlaybackSettingsDlg : public CPropertyPage
{
	DECLARE_DYNAMIC(CServerPlaybackSettingsDlg)

public:
	CServerPlaybackSettingsDlg(CDVRPlayer* pPlayer);
	virtual ~CServerPlaybackSettingsDlg();

// Dialog Data
	enum { IDD = IDD_PLAYBACK_SETTINGS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedPlayback();

	virtual BOOL OnInitDialog();

private:
	CDVRPlayer*		m_pDVRPlayer;
};
