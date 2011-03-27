#pragma once

#include "PlayM4.h"
#include "watermarkinfo.h"

static UINT	WM_FILE_END			= WM_USER +33;	 // User message. Be posted when the file is end.
static UINT	WM_ENC_CHANGE		= WM_USER +100;  // User message. Be posted when the image size is changed.

void CALLBACK EncChange(LONG lPort, LONG dwUser);
void CALLBACK DecCBFun(long nPort,char * pBuf,long nSize,
	FRAME_INFO * pFrameInfo, 
	long nReserved1,long /*nReserved2*/);
//文件头标
// 海康格式封装
#define HKM4_FILE_CODE		0x484B4D34	// "HKM4" 海康文件层，M卡老版本非标准MPEG4
#define HKH4_FILE_CODE		0x484B4834	// "HKH4" 海康H.264
#define HSM4_FILE_CODE		0x48534D34	// "HSM4" 海康系统层，标准MPEG4

// MPEG2-PS
#define PSM4_FILE_CODE		0x50534D34	// "PSM4" PS系统层，标准MPEG4
#define PSH4_FILE_CODE		0x50534834	// "PSH4" PS系统层，标准H264

// MPEG2-TS
#define TSM4_FILE_CODE		0x54534D34	// "PSM4" TS系统层，标准MPEG4
#define TSH4_FILE_CODE		0x54534834	// "PSH4" TS系统层，标准H264

// RTP
#define RTM4_FILE_CODE		0x52544D34	// "RTM4" RTP封装标准MPEG4
#define RTH4_FILE_CODE		0x52544834	// "RTH4" RTP封装标准H264

// 系统封装格式	
#define SYSTEM_NULL			0x0				// 没有系统层，纯音频流或视频流	
#define SYSTEM_HIK          0x1				//add 20071218
#define SYSTEM_MPEG2_PS     0x2				//add 20071218
#define SYSTEM_MPEG2_TS     0x3				//add 20071218
#define SYSTEM_RTP          0x4				//add 20071218

// 视频编码类型
#define VIDEO_NULL          0x0 // 没有视频
#define VIDEO_H264          0x1 // 标准H.264和海康H.264都可以用这个定义
#define VIDEO_MPEG4         0x3 // 标准MPEG4

// 音频编码类型
#define AUDIO_NULL          0x0000 // 没有音频
#define AUDIO_ADPCM         0x1000 // ADPCM 
#define AUDIO_MPEG          0x2000 // MPEG 系列音频，解码器能自适应各种MPEG音频
// G系列音频
#define AUDIO_G711_U		0x7110
#define AUDIO_G711_A		0x7111
#define AUDIO_G722_1		0x7221
#define AUDIO_G723_1        0x7231
#define AUDIO_G726          0x7260
#define AUDIO_G729          0x7290

#ifndef HIK_RTP_STREAM_TYPE_DEFINITION
#define HIK_RTP_STREAM_TYPE_DEFINITION

//RTP 负载类型，与TS/PS解析系统定义相同
/* 输入流类型声明 */
#define HIK_STD_STREAM_TYPE_RTP_NULL    0x00    /* 没有RTP流      */
#define HIK_STD_STREAM_TYPE_RTP_STM     0x91    /* 未定义的其他流 */
#define HIK_STD_STREAM_TYPE_RTP_G711    0x71    /* G711 音频流    */
#define HIK_STD_STREAM_TYPE_RTP_G722    0x72    /* G722 音频流    */
#define HIK_STD_STREAM_TYPE_RTP_G723    0x73    /* G723 音频流    */
#define HIK_STD_STREAM_TYPE_RTP_G726    0x76    /* G726 音频流    */
#define HIK_STD_STREAM_TYPE_RTP_G727    0x77    /* G727 音频流    */
#define HIK_STD_STREAM_TYPE_RTP_G728    0x78    /* G728 音频流    */
#define HIK_STD_STREAM_TYPE_RTP_G729    0x79    /* G729 音频流    */

#define HIK_STD_STREAM_TYPE_RTP_M1V     0x01    /* mpeg1 视频流   */
#define HIK_STD_STREAM_TYPE_RTP_M2V     0x02    /* mpeg2 视频流   */
#define HIK_STD_STREAM_TYPE_RTP_M1A     0x03    /* mpeg1 音频流   */
#define HIK_STD_STREAM_TYPE_RTP_M2A     0x04    /* mpeg2 音频流   */
#define HIK_STD_STREAM_TYPE_RTP_M4V     0x10    /* MPEG4视频流    */
#define HIK_STD_STREAM_TYPE_RTP_264     0x1b    /* H.264视频流	  */

#endif

#define HIK_STD_STREAM_TYPE_MPG2_TS		7    	/* TS流           */
#define HIK_STD_STREAM_TYPE_MPG2_PS     8       /* PS流           */

enum _VIDEO_PLAY_STATE 
{ 
	State_Close  = 0,
	State_Play   = 1,
	State_Pause  = 2,
	State_Stop   = 3,
	State_Step   = 4
};

class CDVRPlayer
{
public:
	CDVRPlayer(void);
	~CDVRPlayer(void);

public:
	bool Init(HWND hPlayWnd, RECT* rcDisplayRegion, HWND hParentWnd, int lPort = -1);	//Init method of the Player.
	void Destory();

	bool SetDisplayRegion(HWND hPlayWnd, RECT* rcDisplayRegion);
	bool SetDisplayType(LONG lType);//ISPLAY_NORMAL, DISPLAY_QUARTER (1/4)
	LONG GetDisplayType();
	bool SetTimerType(DWORD dwTimerType = TIMER_1);	//TIMER_1: When playing file
											//TIMER_2: When preview 
	DWORD GetTimerType();
	// play / pause / stop
	void  Play();
	void  Pause();
	void  Stop();
	BOOL  SetPosition(DWORD dwTime);	// Set play position: microsecond
	DWORD GetCurrentPosition();			// Get play position: microsecond.
	DWORD GetCurrentFrameNum();		
	DWORD GetDuration(){return m_dwMaxFileTime;}
	bool  SetVolume(WORD wVolume);

	// gotostart / slow / fast / gotoend
	void  GotoStart();
	void  Slow();
	void  Fast();
	void  AdjustSpeed(int nSpeed);
	void  GotoEnd();

	// stepback / stepfore / cap picture
	bool  CanStepBackword(){return m_bFileRefCreated;}
	void  CanStepBackword(bool canStepBack){m_bFileRefCreated = canStepBack;}
	void  StepBackward();
	void  StepForward();
	void  SetPictureQuality(BOOL bHighQuality)
	{
		m_bPicQuality = bHighQuality;
	}
	void  SetDeflash(bool bDeflash)
	{
		m_bDeflash = bDeflash;
	}
	bool  GetPictureSize(LONG* plWidth, LONG* plHeight);
	void  GetPic(PBYTE pImage, DWORD nBufSize);
	void  Cappic();
	enum eCapPicType{eJPEG, eBMP};
	void  SetCapturePicType(eCapPicType eType)
	{
		m_nCapPicType = eType;
	}
	void SetCapturePath(LPCTSTR szFolder)
	{
		m_strCapPicPath = szFolder;
	}

	// close or open sound
	void  Sound();
	// adjust sound
	//void  AdjustSound(BOOL bFlag);

	_VIDEO_PLAY_STATE GetPlayState()
	{
		return m_enumState;
	}

	void ThrowB(UINT nID);
	void TestCapability(DWORD nDeviceNum);
	void RefreshPlay();
	LONG GetPort(){return m_lPort;}
	void ResetBuf();
	char* MyErrorToString(DWORD error);
public:
	// file operation:
	void  Open(LPCTSTR szFile = NULL);
	void  Close();
	void  OpenFile();
	void  CloseFile();
	void  OpenStream();
	void  CloseStream();
	static WATERMARK_VER1_INFO m_strWaterMark;

	HANDLE		m_hEventKill;                   // kill inputstream thread event
	HANDLE		m_hEventInput;                  // inputstream thread event
	HANDLE		m_hThread;                      // inputstream thread handle
	HANDLE		m_hStreamFile;                  // input file

private:
	// callback function

	//OnDrawFun
	// Draw the meta data on the screen.
	static void CALLBACK OnDrawFun(long nPort, HDC hDC, LONG nUser);
private:
	_VIDEO_PLAY_STATE m_enumState;              // now the play state
	LONG	m_lPort;
	CString m_strPlayFileName;

	BOOL		m_bStreamType;							//Stream or File

	HWND		m_hRenderWnd;						//Play Area window
	HWND		m_hParentWnd;					//Main Frame Window
	RECT		m_rcDisplayRegion;				//Play Area.
	LONG		m_nSpeed;                       // video play speed
	LONG		m_nWidth;                       // image width
	LONG		m_nHeight;                      // image height

	BOOL		m_bHighFluid;					// hight fluid motion
	DWORD		m_dwMaxFileTime;				// Media File duration.
	bool		m_bFileRefCreated;				// Back seek Index is created.
	eCapPicType m_nCapPicType;
	CString		m_strCapPicPath;				//Capture path;
	UINT		m_npic_bmp;						// capped bmp  pic number
	UINT		m_npic_jpeg;					// capped jpeg pic number
	BOOL		m_bPicQuality;
	BOOL		m_bDeflash;
	BOOL		m_bOpen; 

	DWORD		m_dwDisplayHour;
	DWORD		m_dwDisplayMinute;
	DWORD		m_dwDisplaySecond;
	DWORD		m_dwTotalFrames;
	BOOL		m_bFileEnd;
	DWORD		m_dwMaxFileSize;
	DWORD		m_dwHeadSize;
};