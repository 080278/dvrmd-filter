
// DVRUI_MFCDlg.h : ͷ�ļ�
//

#pragma once
#include "dvrmvplayerctrl1.h"


// CDVRUI_MFCDlg �Ի���
class CDVRUI_MFCDlg : public CDialog
{
// ����
public:
	CDVRUI_MFCDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DVRUI_MFC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CDvrmvplayerctrl1 m_DVRPlayer;
	afx_msg void OnBnClickedOpenfile();
	afx_msg void OnDestroy();

private:
	int m_nPaneCtrlHeight;
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_EVENTSINK_MAP()
	void DoubleClickDvrmvplayerctrl1(short nButton, short nShiftState, long fX, long fY);
	void KeyDownDvrmvplayerctrl1(short nKeyCode, short nShiftState);
};
