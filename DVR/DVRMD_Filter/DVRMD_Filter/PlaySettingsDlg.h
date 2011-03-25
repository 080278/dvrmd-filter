#pragma once


// CDVRPlaySettings dialog

class CPlaySettingsDlg : public CPropertyPage
{
	DECLARE_DYNAMIC(CPlaySettingsDlg)

public:
	CPlaySettingsDlg();
	virtual ~CPlaySettingsDlg();

// Dialog Data
	enum { IDD = IDD_DVR_PLAY_SETTINGS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
