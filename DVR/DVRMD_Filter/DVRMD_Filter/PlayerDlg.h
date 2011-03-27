/////////////////////////////////////////////////////////////////////////////////////
// PlayerDlg.h : header file
/////////////////////////////////////////////////////////////////////////////////////


#if !defined(AFX_PLAYERDLG_H__BC7E7078_7E67_40B3_85A4_591E51BB1A4A__INCLUDED_)
#define AFX_PLAYERDLG_H__BC7E7078_7E67_40B3_85A4_591E51BB1A4A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XColorStatic.h"
#include "XScrollBar.h"
#include "VolumeCtrl.h"
#include "VideoCtrlDlg.h"
#include "WatermarkDlg.h"
#include "DVRPlayer.h"

/////////////////////////////////////////////////////////////////////////////
// CPlayerDlg dialog
/////////////////////////////////////////////////////////////////////////////
class CPlayerDlg : public CDialog
{
private:
	CDVRPlayer	m_DVRPlayer;
// Construction
public:
	CPlayerDlg(CWnd* pParent = NULL);			// standard constructor

public:
	CDVRPlayer* GetPlayer()
	{
		return &m_DVRPlayer;
	}
public:
	BOOL		m_bInited;

	/************************************************************************/
	/* para used to cap pic */
	UINT		m_nCapPicType;					// 0 indicates default bmp, 1 indicates jpeg
	UINT		m_npic_bmp;						// capped bmp  pic number
	UINT		m_npic_jpeg;					// capped jpeg pic number
	CString		m_strCapPicPath;				// capped pic path
	/************************************************************************/

	BOOL		m_bStartDraw;                   // start drawing?
	BOOL		m_bFileEnd;                     // has file played to end?
	BOOL		m_bStreamType;                  // played as stream?
	BOOL		m_bPicQuality;                  // use high picture quality?
	BOOL        m_bDeflash;	                    // set I frame deflashing?
	//BOOL		m_bHighFluid;					// hight fluid motion?
	BOOL		m_bSound;                       // open the sound or not?
	BOOL		m_bOpen;                        // has file opend?
	BOOL		m_bRepeatPlay;                  // play the file rewind?
	BOOL		m_bFullScreen;                  // full screen or not?
	BOOL		m_bConvertAVI;                  // convert to AVI or not?
	
	LONG		m_nSpeed;                       // video play speed
	LONG		m_nWidth;                       // image width
	LONG		m_nHeight;                      // image height
	LONG		m_nPrePlayPos;                  // pre play slider pos
	
	DWORD		m_dwScreenHeight;               // screem height
	DWORD		m_dwScreenWidth;                // screen width	
	CRect		m_rcScreen;						// dlg in which screen now

    DWORD       m_dwSysFormat;
	DWORD		m_dwHeadSize;                   // Hikvision file header length
	DWORD		m_dwMaxFileSize;                // Hikvision file size
	DWORD		m_dwTotalFrames;                // total frames
	DWORD		m_dwDisplaySecond;              // seconds displayed at the statusbar
	DWORD		m_dwDisplayMinute;              // minutes displayed at the statusbar
	DWORD		m_dwDisplayHour;                // hours   displayed at the statusbar
	DWORD		m_dwDlgTopSize;                 // dlg top  space height
	DWORD		m_dwDlgEdge;                    // dlg edge space width 
//	DWORD       m_dwImageSharpenLevel;          // image sharpen level (0 ~6)
	DWORD		m_dwOldDeviceNum;				// old display device sequence

	CRect		m_rcWindow;						// window rect
	CRect		m_rcDraw;						// draw rect
	CRect		m_rcDisplay;                    // mutli display rect
	CPoint		m_StartPoint;                   // start point

	//HANDLE		m_hEventKill;                   // kill inputstream thread event
	//HANDLE		m_hEventInput;                  // inputstream thread event
	//HANDLE		m_hThread;                      // inputstream thread handle
	//HANDLE		m_hStreamFile;                  // input file

	CString     m_strSaveAVIPath;               // saveing avi  file path
	
	CBitmap		m_HikvisionBmp;                 // hikvision bmp
	CBitmap		m_BlackBmp;                     // black bmp
	CBitmap		m_OverlayBmp;                   // overlay bmp
	
//	CMenu*		      m_pMainMenu;              // pointer to the menu
//	CSeek*			  m_pSeek;                  // seek dialog
//	CDisplayRect*     m_pDisplayRegion;         // display region dialog
//	CVideoCtrlDlg*    m_pVideoControl;			// video control dialog
	WINDOWPLACEMENT   m_OldWndpl;               // save dialog window pos
	CWatermarkDlg*     m_pWatermarkDlg;			// watermark dialog
	PBYTE			  m_pQcifTempBuf;			// convert qcif to avi

public:
	BOOL SetDiplayMode(int nID);

	BOOL IsFullScreen()
	{
		return m_bFullScreen;
	}
	
	HANDLE	m_hTestFile;
	//������Ϣ

	BOOL PreTranslateMessage(MSG* lpmsg);       // overload to handle keydown message
	
	void  CutFile();
	void  SetSecretKey();

	CWnd* m_pParentWnd;
	// view operation:
	void  ViewFullScreen();
	void  ViewZoom(UINT nID);
	void  Infomation();
	void  SetDisplay();
	//BOOL  SetDevice(UINT nID);
	void  GetWatermark();
	
	// control operation:
	//void  VideoControl();
	void  Repeat();
	void  Locate();
  
	// option operation:
	void  StreamType();
	
	void  Deflash();
	void  Quality();
	void  HighFluid();
	void  ImageSharpenLevel(UINT nID);
	//void  SetDecodeType(UINT nID);
	
	void  DisplayType(UINT nID);
	void  SelectTimer(UINT nID);
	void  ResetBuf();
	
	void  CapPicType(UINT nID);
	void  CappicPath();
	
	void  ConvertToAVI();

	// help operation:
	void  AppAbout();
	void  AppHelp();
	// open/close file or stream
	BOOL  BrowseFile(CString *strFileName);
	void Play();
	void Pause();
	void Stop();
	void StepBackward();
	void StepForward();
	void Open(LPCTSTR szFile = NULL);
	void Close();
	HRESULT OpenFile(LPCTSTR szFile);
	void CloseFile();

	// set play state
	void  DrawStatus();
	void  SetState();
	void  SetAVIState();
	DWORD GetSpeedModulus(); 
	
	// sort the dialog control
	void  SetWindowSize();
	void  SortControl();
	void  InitWindowSize(DWORD cx, DWORD cy);

	// others
	CRect GetOnPicRect(CRect rcWnd, CRect rcOnWnd, LONG nPicWidth, LONG nPicHeight);	
	void  SetDisplayRegion(RECT);

	/*************************************************************************/
	/*  assistant operation over
	/*************************************************************************/


// Dialog Data
	//{{AFX_DATA(CPlayerDlg)
	enum { IDD = IDD_PLAYER_DIALOG };
	CButtonST		m_ctrlBtnCapPic;
	CButtonST		m_ctrlBtnSound;
	CButtonST		m_ctrlStepBackward;
	CButtonST		m_ctrlStepForward;
	CButtonST		m_ctrlBtnSlow;
	CButtonST		m_ctrlBtnFast;
	CButtonST		m_ctrlBtnGStart;
	CButtonST		m_ctrlBtnGEnd;
	CButtonST		m_ctrlBtnStop;
	CButtonST		m_ctrlBtnPlay;
	CButtonST		m_ctrlBtnPause;
	CStatic			m_ctrlVideoPic;
	CString			m_strPlayStateText;
	CXColorStatic	m_ctrlPlayText;
	//}}AFX_DATA
	CVolumeCtrl		m_SoundSlider;
	CXScrollBar		m_PlaySlider;

	RECT			m_rcOldPicPos;
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlayerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;


	// Generated message map functions
	//{{AFX_MSG(CPlayerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	afx_msg LRESULT WatermarkOk(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT VideoCtrlOK(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT PlayMessage(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT EncChangeMessage(WPARAM wParam, LPARAM lParam);
	afx_msg void OnMenuItem(UINT nID);
	afx_msg void OnButtonItem(UINT nID);
	afx_msg void OnBnClickedOpenfile();
	afx_msg void OnBnClickedShowHideSettings();
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAYERDLG_H__BC7E7078_7E67_40B3_85A4_591E51BB1A4A__INCLUDED_)
