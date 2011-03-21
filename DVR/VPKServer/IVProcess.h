// IVProcess.h: interface for the CIVProcess class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IVPROCESS_H__C337EFBA_CC53_4471_AB1E_168143C1AE93__INCLUDED_)
#define AFX_IVPROCESS_H__C337EFBA_CC53_4471_AB1E_168143C1AE93__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_YUV_LENGTH		(800*600*3/2)
#define MAX_RGB32_LENGTH	(800*600*4)
#define MAX_META_LENGTH		(10*1024)

#define MAX_PIPE_BUF_LENGTH	(720*576*3/2 + 128)

#pragma pack(1)

struct FRAME_HEADER_VPK
{
    DWORD	SyncFlag;
    __int64 msTime;
	WORD Width;
	WORD Height;
	WORD FramteRate;
	DWORD FrameLength;
	FRAME_HEADER_VPK() 
	{		
		memset( this, 0x00, sizeof(FRAME_HEADER_VPK) );
		SyncFlag = 0xAA8888AA;
	}
};

#pragma pack()

class CIVProcess  
{
public:
	CIVProcess();
	virtual ~CIVProcess();

	int DoIVProcess(int chIndex);
private:
	INT TD_IVProcess();

private:
	HANDLE	m_hPipe;
	BOOL	m_bExit;
	BYTE	m_yuvImage[MAX_YUV_LENGTH];
	BYTE	m_rgbImage[MAX_RGB32_LENGTH];
	BYTE	m_meta[MAX_META_LENGTH];
};

#endif // !defined(AFX_IVPROCESS_H__C337EFBA_CC53_4471_AB1E_168143C1AE93__INCLUDED_)
