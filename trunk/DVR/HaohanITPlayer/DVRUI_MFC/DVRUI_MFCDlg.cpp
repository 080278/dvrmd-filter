
// DVRUI_MFCDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DVRUI_MFC.h"
#include "DVRUI_MFCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDVRUI_MFCDlg �Ի���




CDVRUI_MFCDlg::CDVRUI_MFCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDVRUI_MFCDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nPaneCtrlHeight = 30;
}

void CDVRUI_MFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DVRMVPLAYERCTRL1, m_DVRPlayer);
}

BEGIN_MESSAGE_MAP(CDVRUI_MFCDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPENFILE, &CDVRUI_MFCDlg::OnBnClickedOpenfile)
	ON_WM_DESTROY()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CDVRUI_MFCDlg ��Ϣ�������

BOOL CDVRUI_MFCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	RECT rcPlayer, rcDlg;
	GetClientRect(&rcDlg);
	GetDlgItem(IDC_PLAY_WND)->GetWindowRect(&rcPlayer);
	m_nPaneCtrlHeight = rcDlg.bottom - rcPlayer.bottom;
	m_DVRPlayer.MoveWindow(0, 0, rcPlayer.right - rcPlayer.left, rcPlayer.bottom - rcPlayer.top);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CDVRUI_MFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDVRUI_MFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CDVRUI_MFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDVRUI_MFCDlg::OnBnClickedOpenfile()
{
	CFileDialog dlg(TRUE);
	if (dlg.DoModal() == IDOK)
	{
		this->m_DVRPlayer.OpenFile(dlg.GetPathName());
	}
}


void CDVRUI_MFCDlg::OnDestroy()
{
	CDialog::OnDestroy();

}


void CDVRUI_MFCDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	if (m_DVRPlayer.m_hWnd != NULL && ::IsWindow(m_DVRPlayer.m_hWnd))
	{
		m_DVRPlayer.MoveWindow(0, 0, cx, cy-m_nPaneCtrlHeight);
	}
}


BEGIN_EVENTSINK_MAP(CDVRUI_MFCDlg, CDialog)
	ON_EVENT(CDVRUI_MFCDlg, IDC_DVRMVPLAYERCTRL1, 6501, CDVRUI_MFCDlg::DoubleClickDvrmvplayerctrl1, VTS_I2 VTS_I2 VTS_I4 VTS_I4)
	ON_EVENT(CDVRUI_MFCDlg, IDC_DVRMVPLAYERCTRL1, 6502, CDVRUI_MFCDlg::KeyDownDvrmvplayerctrl1, VTS_I2 VTS_I2)
END_EVENTSINK_MAP()


void CDVRUI_MFCDlg::DoubleClickDvrmvplayerctrl1(short nButton, short nShiftState, long fX, long fY)
{
	m_DVRPlayer.put_fullScreen(!m_DVRPlayer.get_fullScreen());
}


void CDVRUI_MFCDlg::KeyDownDvrmvplayerctrl1(short nKeyCode, short nShiftState)
{
	// TODO: Add your message handler code here
	if (nKeyCode == VK_ESCAPE)
	{
		if (m_DVRPlayer.get_fullScreen())
		{
			m_DVRPlayer.put_fullScreen(FALSE);
		}
	}
}
