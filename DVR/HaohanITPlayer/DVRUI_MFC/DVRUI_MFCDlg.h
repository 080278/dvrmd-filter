
// DVRUI_MFCDlg.h : 头文件
//

#pragma once
#include "CDVRMVPlayer.h"
#include "CDVRMVSettings.h"


// CDVRUI_MFCDlg 对话框
class CDVRUI_MFCDlg : public CDialog
{
// 构造
public:
	CDVRUI_MFCDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DVRUI_MFC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CDVRMVPlayer m_DVRPlayer;
	afx_msg void OnBnClickedOpenfile();
	afx_msg void OnDestroy();

private:
	int m_nPaneCtrlHeight;
	bool m_Pause;
	CSliderCtrl   *pSlidCtrl;
	float m_Duration;
	int clickCount;

private:
	CDVRMVSettings m_Settings;

protected:
	void SetChannelState();
	void InitServerInfoBox();//初始化登录界面
	void SetFileState(bool b);
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_EVENTSINK_MAP()
	void DoubleClickDvrmvplayerctrl1(short nButton, short nShiftState, long fX, long fY);
	void KeyDownDvrmvplayerctrl1(short nKeyCode, short nShiftState);
	afx_msg void OnBnClickedPlayNext();
	afx_msg void OnBnClickedButtonLogin();
	afx_msg void OnBnClickedButtonStartMonitor();
	afx_msg void OnBnClickedButtonStopMonitor();
	afx_msg void OnBnClickedButtonChannel();
	afx_msg void OnBnClickedButtonStartPlayback();
	afx_msg void OnBnClickedButtonStopPlayback();
	afx_msg void OnBnClickedButtonVsPlayPause();
	afx_msg void OnBnClickedButtonVsStop();
	afx_msg void OnBnClickedButtonVsReverse();
	afx_msg void OnBnClickedButtonVsForward();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	int ServerPort;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
