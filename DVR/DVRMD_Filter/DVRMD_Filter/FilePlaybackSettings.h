#pragma once


// CFilePlaybackSettings dialog
class CPlayerDlg;

class CFilePlaybackSettingsDlg : public CPropertyPage
{
	DECLARE_DYNAMIC(CFilePlaybackSettingsDlg)

public:
	CFilePlaybackSettingsDlg(CPlayerDlg* pMainDlg);
	virtual ~CFilePlaybackSettingsDlg();

// Dialog Data
	enum { IDD = IDD_FILE_SETTINGS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOpenfile();

	CString GetPathName();
	void	SetPathName(LPCTSTR szPath);

protected:
	CString m_csMediaFile;
	CPlayerDlg*	m_pMainDlg;
public:
	virtual BOOL OnInitDialog();
};
