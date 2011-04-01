#include "StdAfx.h"
#include "Player.h"
#include "DVRPlayer.h"

WATERMARK_VER1_INFO CDVRPlayer::m_strWaterMark;

CDVRPlayer::CDVRPlayer(void)
{
	m_lPort = -1;
}


CDVRPlayer::~CDVRPlayer(void)
{
}

bool CDVRPlayer::Init(HWND hRenderWnd, RECT* rcDisplayRegion, HWND hParentWnd, int lPort)
{
	m_enumState = State_Close;
	m_lPort = lPort;
	m_hRenderWnd = hRenderWnd;
	m_rcDisplayRegion = *rcDisplayRegion;
	m_dwMaxFileTime = 0;
	m_bFileRefCreated = false;
	m_nCapPicType = CDVRSettings::eBMP;
	m_npic_jpeg = 0;
	m_npic_bmp = 0;
	m_hParentWnd = hParentWnd;
	m_bPicQuality = FALSE;
	m_bDeflash = FALSE;
	m_bOpen = FALSE;
	m_dwDisplayHour = 0;
	m_dwDisplayMinute = 0;
	m_dwDisplaySecond = 0;
	m_dwTotalFrames = 0;
	m_bFileEnd = FALSE;
	m_dwMaxFileSize = 0;
	m_hStreamFile = NULL;
	m_dwHeadSize = NULL;
	m_hEventKill = NULL; 
	m_hEventInput = NULL;
	m_hThread = NULL;    
	m_hStreamFile = NULL;
	m_bStreamType = FALSE;

	#if (WINVER > 0x0400)
	// If do not support multi monitor,may not call!
	HMONITOR hMonitor;
	char chDriverDesp[50];
	char chDriverName[50];

	NAME(PlayM4_InitDDrawDevice)();
	DWORD nVal=NAME(PlayM4_GetDDrawDeviceTotalNums)();
	if(nVal > 1)
	{
		nVal = min(nVal, MAX_DISPLAY_DEVICE);
		for(DWORD nCount = 0; nCount < nVal; nCount++) 
		{
			ZeroMemory(chDriverDesp, 50);
			NAME(PlayM4_GetDDrawDeviceInfo)(nCount, chDriverDesp, 50, chDriverName, 50, &hMonitor);
			////m_pMainMenu->GetSubMenu(1)->InsertMenu(IDM_TEMP_DEVICE, MF_BYCOMMAND, IDM_DEVICE0 + nCount + 1, chDriverDesp);
		}
	}
	else
	{
		ZeroMemory(chDriverDesp, 50);
		NAME(PlayM4_GetDDrawDeviceInfo)(0, chDriverDesp, 50, chDriverName, 50, &hMonitor);
		////m_pMainMenu->GetSubMenu(1)->InsertMenu(IDM_TEMP_DEVICE, MF_BYCOMMAND, IDM_DEVICE0, chDriverDesp);
	}

	TestCapability(0);
#endif

	if (m_lPort == -1)
		NAME(PlayM4_GetPort)(&m_lPort);

	// set the capture picture call back function;
	//	NAME(PlayM4_SetDisplayCallBack)(m_lPort, DisplayCBFun);
	// set the wave audio call back funtion;
	//	NAME(PlayM4_SetAudioCallBack)(m_lPort, WaveCBFun, (long)this);

	NAME(PlayM4_SetDDrawDevice)(m_lPort, 0);
	// Test adapter Capability;
	NAME(PlayM4_SetVolume)(m_lPort, 0);

	NAME(PlayM4_RegisterDrawFun)(m_lPort, OnDrawFun, (LONG)this);
	return true;
}

void CDVRPlayer::OnDrawFun(long nPort, HDC hDC, LONG nUser)
{
	CDVRPlayer* pThis = (CDVRPlayer*)nUser;
	
}

void CDVRPlayer::RefreshPlay()
{
	NAME(PlayM4_RefreshPlay)(m_lPort);
	NAME(PlayM4_RefreshPlayEx)(m_lPort, 0);
}

void CDVRPlayer::Destory()
{
	NAME(PlayM4_Stop)(m_lPort);
	NAME(PlayM4_CloseFile)(m_lPort);
	NAME(PlayM4_RealeseDDraw)();

	NAME(PlayM4_FreePort)(m_lPort);

	NAME(PlayM4_ReleaseDDrawDevice)();

	m_enumState = State_Close;
}

// play / pause / stop
void CDVRPlayer::Play()
{
	if(m_enumState == State_Play)
	{
		return;
	}
	
	if(m_enumState == State_Pause)
	{
//		DWORD nPreSpeed = m_nSpeed;

		NAME(PlayM4_Pause)(m_lPort, FALSE);

		m_enumState = State_Play;

		// when u called this api, the speed is adjust to normal speed, so we must resume it.
//		NAME(PlayM4_Play)(m_lPort, m_ctrlVideoPic.GetSafeHwnd());
//		m_nSpeed = 0;
//		ThrowB(IDM_THROW0);
//		AdjustSpeed(nPreSpeed);
	}
	else if (m_enumState == State_Stop && m_bStreamType)
	{
		Open();
	}
	else if(m_enumState == State_Step)
	{
		NAME(PlayM4_Play)(m_lPort, m_hRenderWnd);
		m_nSpeed = 0;
		ThrowB(IDM_THROW0);

		m_enumState = State_Play;
	}
	else
	{
		ZeroMemory(&m_strWaterMark, sizeof(WATERMARK_VER1_INFO));
		NAME(PlayM4_SetCheckWatermarkCallBack)(m_lPort, funCheckWatermark, (DWORD)this);
		
		m_nSpeed = 0;
		ThrowB(IDM_THROW0);

		//if(m_bConvertAVI)
		//{
		//	NAME(PlayM4_SetDecCallBackMend)(m_lPort, DecCBFun, DWORD(this));
		//	m_bFileRefCreated = FALSE;
		//}

		if(m_bStreamType)
		{
//			NAME(PlayM4_ResetSourceBuffer)(m_lPort);
			SetEvent(m_hEventInput);
		}

		if(NAME(PlayM4_Play)(m_lPort, m_hRenderWnd))
		{
			m_enumState = State_Play;

			//SetTimer(PLAY_TIMER, 500, NULL);

			NAME(PlayM4_RefreshPlay)(m_lPort);
		}

		//m_bSound = NAME(PlayM4_PlaySound)(m_lPort);	
	}
}

void CDVRPlayer::Pause()
{
	if(m_enumState == State_Play)
	{
		NAME(PlayM4_Pause)(m_lPort, TRUE);
		m_enumState = State_Pause;
	}
}

void CDVRPlayer::Stop()
{
	if(m_enumState == State_Stop)
	{
		return;
	}

	//// stop sound
	//if(NAME(PlayM4_StopSound)())
	//{
	//	m_bSound = FALSE;
	//	m_ctrlBtnSound.SetIcon(IDI_SOUND_DISABLE);
	//}
	
	// stop video
	if(NAME(PlayM4_Stop)(m_lPort))	
	{
		//m_strPlayStateText = "Stop";
		//m_ctrlPlayText.ShowText(m_strPlayStateText);
	
		if(m_bStreamType)
		{
			ResetEvent(m_hEventInput);
		}
	}	

	ZeroMemory(&m_strWaterMark, sizeof(WATERMARK_VER1_INFO));
	m_enumState = State_Stop;
}

// gotostart / slow / fast / gotoend
void CDVRPlayer::GotoStart() 
{
	// TODO: Add your control notification handler code here

	if(m_bFileRefCreated)
	{
		NAME(PlayM4_SetPlayedTimeEx)(m_lPort, 0);
	}
	else
	{
		NAME(PlayM4_SetPlayPos)(m_lPort, 0);
	}
}

BOOL CDVRPlayer::SetPosition(DWORD dwTime)
{
	return NAME(PlayM4_SetPlayedTimeEx)(m_lPort, dwTime);
}

DWORD CDVRPlayer::GetCurrentPosition()
{
	DWORD nCurrentTime = NAME(PlayM4_GetPlayedTime)(m_lPort);

	TRACE("hytest: play position = %f!\n", NAME(PlayM4_GetPlayPos)(m_lPort));

	return nCurrentTime;
}

DWORD CDVRPlayer::GetCurrentFrameNum()
{
	return NAME(PlayM4_GetCurrentFrameNum)(m_lPort);
}

BOOL CDVRPlayer::SetVolume(WORD wVolume)
{
#ifdef _WAVE_ADJ
	NAME(PlayM4_AdjustWaveAudio)(m_lPort, wVolume);
#else
	return NAME(PlayM4_SetVolume)(m_lPort, wVolume);
#endif
}
void CDVRPlayer::GotoEnd() 
{
	// TODO: Add your control notification handler code here
	
	if(m_bFileRefCreated)
	{
		//Note: May create many WM_FILE_END message. The best way is to synchronize the option;
		
//		int nEndFrame = m_dwTotalFrames;
//		int nCurFrame = NAME(PlayM4_GetCurrentFrameNum)(m_lPort);
		while( !NAME(PlayM4_SetPlayedTimeEx)(m_lPort, m_dwMaxFileTime * 1000 ) )
		{
			//TRACE("FrameNum is :%d\n",nEndFrame);
//			if(nEndFrame <= int(max(0, m_dwTotalFrames - 3)))
//			{
//				NAME(PlayM4_SetCurrentFrameNum)(m_lPort, nCurFrame);
//				break;
//			}
		}
	}
	else
	{
		NAME(PlayM4_SetPlayPos)(m_lPort, 1);
	}

}

void CDVRPlayer::Fast() 
{
	// TODO: Add your control notification handler code here

	// Throw B-Frame ,improve the performance;
	
	if(NAME(PlayM4_Fast)(m_lPort))
	{
		m_nSpeed ++;
		if(m_nSpeed > 0)
		{
			ThrowB(IDM_THROW2);	
		}
	}	
}

void CDVRPlayer::Slow() 
{
	// TODO: Add your control notification handler code here
	
	if(NAME(PlayM4_Slow)(m_lPort))
	{
		m_nSpeed --;
		if(m_nSpeed <= 0)
		{
			ThrowB(IDM_THROW0);
		}
	}
}

void CDVRPlayer::AdjustSpeed(int nSpeed)
{
	int nCyc = 0;
	while(m_nSpeed != nSpeed)
	{
		if(nSpeed > m_nSpeed)
		{
			Fast();	
		}
		else if(nSpeed < m_nSpeed)
		{
			Slow();
		}

		nCyc ++;
		if(nCyc >= 10)
		{
			break;
		}
	}
}

// stepback / stepfore / cap picture
void CDVRPlayer::StepBackward() 
{
	// TODO: Add your control notification handler code here
	if(m_bFileRefCreated)
	{
		NAME(PlayM4_OneByOneBack)(m_lPort);
		m_enumState = State_Step;
	}
}

void CDVRPlayer::StepForward() 
{
	// TODO: Add your control notification handler code here
	
	// you can do it like the followed too.
	// DWORD nCurrentFrame = NAME(PlayM4_GetCurrentFrameNum)(m_lPort);
	// NAME(PlayM4_SetCurrentFrameNum)(m_lPort,nCurrentFrame+1);
	ThrowB(IDM_THROW0);          // when step forward one by one, don't throw B frame;
	NAME(PlayM4_OneByOne)(m_lPort);
	m_enumState = State_Step;

}

bool CDVRPlayer::GetPictureSize(LONG* plWidth, LONG* plHeight)
{
	return NAME(PlayM4_GetPictureSize)(m_lPort, plWidth, plHeight);
}

void CDVRPlayer::GetPic(PBYTE pImage, DWORD nBufSize)
{
	CString sFilePath;
	CFile	clsFile;

	DWORD   pImageSize	= 0;
	
	if(m_nCapPicType == 1)
	{
		if( !NAME(PlayM4_GetJPEG)(m_lPort, pImage, nBufSize, &pImageSize) )
		{
			return;
		}

		if(m_strCapPicPath.Compare(_T("")))
		{
			sFilePath.Format(_T("%s\\capture%02d.jpeg"), m_strCapPicPath, m_npic_jpeg);
		}
		else
		{
			sFilePath.Format(_T("C:\\capture%02d.jpeg"), m_npic_jpeg);
		}
	}
	else
	{
		if( !NAME(PlayM4_GetBMP)(m_lPort, pImage, nBufSize, &pImageSize) )
		{
			return;
		}

		if(m_strCapPicPath.Compare(_T("")))
		{
			sFilePath.Format(_T("%s\\capture%02d.bmp"), m_strCapPicPath, m_npic_bmp);
		}
		else
		{
			sFilePath.Format(_T("C:\\capture%02d.bmp"), m_npic_bmp);
		}
	}
	
	if(!clsFile.Open(sFilePath,CFile::modeCreate|CFile::modeWrite))
	{
		return;
	}

	try							
	{
		clsFile.Write(pImage, pImageSize);
		clsFile.Close();

		if(m_nCapPicType == 0)
		{
			m_npic_bmp++;
		}
		else
		{
			m_npic_jpeg++;
		}
	}
	catch (CFileException* e) 
	{
		e->ReportError();
		e->Delete();
	}
}


void CDVRPlayer::Cappic() 
{
	// TODO: Add your control notification handler code here
	PBYTE	pImage		= NULL;
	DWORD   nBufSize	= m_nWidth * m_nHeight * 5;  // 保证足够大即可(不会小于一幅bmp或者jpeg图像大小)

	try
	{
		pImage = new BYTE[nBufSize];
		if(NULL == pImage)
		{
			throw 0;
		}
		
		GetPic(pImage, nBufSize);
	}
	catch(...)
	{
	}

	if(pImage != NULL)
	{
		delete []pImage;
		pImage = NULL;
	}
}

// close or open sound
//void CDVRPlayer::Sound() 
//{
//	// TODO: Add your control notification handler code here
//	if(false)
//	{
//		if(NAME(PlayM4_StopSound)())
//		{
//		}
//	}
//	else
//	{
//		if(NAME(PlayM4_PlaySound)(m_lPort))
//		{
//		}
//	}
//}
//
//// adjust sound
//void  CDVRPlayer::AdjustSound(BOOL bFlag)
//{
//	int nSoundPos = m_SoundSlider.GetPos();	
//
//	if(bFlag)
//	{
//#ifdef _WAVE_ADJ
//		nSoundPos += (MAX_WAVE_COEF - MIN_WAVE_COEF)/0xf;
//		nSoundPos = min(nSoundPos, MAX_WAVE_COEF);
//#else
//		nSoundPos += 0xffff/0xf;
//		nSoundPos = min(nSoundPos, 0xffff-1);
//#endif
//	}
//	else
//	{
//#ifdef _WAVE_ADJ
//		nSoundPos -= (MAX_WAVE_COEF - MIN_WAVE_COEF)/0xf;
//		nSoundPos = max(nSoundPos, MIN_WAVE_COEF);
//#else
//		nSoundPos -= 0xffff/0xf;
//		nSoundPos = max(nSoundPos, 0);
//#endif
//	}
//
//#ifdef _WAVE_ADJ
//		NAME(PlayM4_AdjustWaveAudio)(m_lPort, nSoundPos);
//#else
//		NAME(PlayM4_SetVolume)(m_lPort, WORD(nSoundPos));
//#endif
//
//	m_SoundSlider.SetPos(nSoundPos);
//}
// file operation:
void CDVRPlayer::Open(LPCTSTR szFile) 
{
	Close();
//	SetState();
	if (szFile != NULL)
		m_strPlayFileName = szFile;

	if (m_lPort == -1)
	{
		PlayM4_GetPort(&m_lPort);
	}

	try
	{
		NAME(PlayM4_SetEncChangeMsg)(m_lPort, m_hParentWnd, WM_ENC_CHANGE);
		NAME(PlayM4_SetEncTypeChangeCallBack(m_lPort, EncChange, (long)this));

		if(m_bStreamType)
		{
			OpenStream();
		}
		else
		{
			OpenFile();
		}

		NAME(PlayM4_SetPicQuality)(m_lPort, m_bPicQuality);
		NAME(PlayM4_SetDeflash)(m_lPort, m_bDeflash);
		//		NAME(PlayM4_SetPlayMode)(m_lPort, m_bHighFluid);

		m_bOpen = TRUE;

		NAME(PlayM4_GetPictureSize)(m_lPort, &m_nWidth, &m_nHeight);
		NAME(PlayM4_SetVolume)(m_lPort,0);
		////m_pMainMenu->ModifyMenu(IDM_SETDISPLAY, MF_BYCOMMAND, IDM_SETDISPLAY, "Multi Display");
		// if video format is HCIF, then double the height
		if( (m_nWidth == WIDTH*2) && (m_nHeight <= HEIGHT_PAL) )
		{
			m_nHeight *= 2;
		}

	}
	catch(...)
	{
		Close();
	}
}


void CDVRPlayer::Close() 
{
	// TODO: Add your command handler code here
	if(m_bOpen)
	{
		if(m_bStreamType)
		{
			CloseStream();
		}
		else
		{
			CloseFile();	
		}



		m_nWidth = 352;
		m_nHeight = 288;



	}
}

void CDVRPlayer::ThrowB(UINT nID)
{
	NAME(PlayM4_ThrowBFrameNum)(m_lPort, nID - IDM_THROW0);

	for(int i = IDM_THROW0; i <= IDM_THROW2; i++ )
	{
		//m_pMainMenu->CheckMenuItem(i, MF_UNCHECKED);
	}
	//m_pMainMenu->CheckMenuItem(nID, MF_CHECKED);
}

// Funtion: test the capability of your system.
void CDVRPlayer::TestCapability(DWORD nDeviceNum)
{
	CString csCap=_T("");
#if (WINVER > 0x0400)
	int nFlag=NAME(PlayM4_GetCapsEx)(nDeviceNum);
#else
	int nFlag=NAME(PlayM4_GetCaps());
#endif

	if(!(nFlag&SUPPORT_SSE))
	{
		csCap+=_T("Don't support SSE instruction set;\r\n");
	}

	if(!(nFlag&SUPPORT_DDRAW))
	{
		csCap+=_T("Create DirectDraw faild;\r\n");
	}

	if(!(nFlag&SUPPORT_BLT))
	{
		csCap+=_T("Error when blitting overlay or offscreen;Error when blitting overlay or offscreen;\r\n");
	}

	if(!(nFlag&SUPPORT_BLTFOURCC))
	{
		csCap+=_T("Don't support color-space conversions;\r\n");
	}

	if(!(nFlag&SUPPORT_BLTSHRINKX))
	{
		csCap+=_T("Don't support arbitrary shrinking of a surface along the x-axis\r\n");
	}

	if(!(nFlag&SUPPORT_BLTSHRINKY))
	{
		csCap+=_T("Don't supports arbitrary shrinking of a surface along the y-axis (vertically);\r\n");
	}

	if(!(nFlag&SUPPORT_BLTSTRETCHX))
	{
		csCap+=_T("Don't supports arbitrary stretching of a surface along the x-axis;\r\n");
	}

	if(!(nFlag&SUPPORT_BLTSTRETCHY))
	{
		csCap+=_T("Don't supports arbitrary stretching of a surface along the y-axis;\r\n");
	}

	if(csCap.GetLength()>0)
	{
		csCap+=_T("If your video adapter chip is made by nVidia,please update the new driver!\r\n");
		MessageBox(NULL, csCap,_T("Warning"),MB_OK);
	}
}

// open file and play
void CDVRPlayer::OpenFile()
{
	CString strError;

	NAME(PlayM4_SetFileEndMsg)(m_lPort, m_hParentWnd, WM_FILE_END);

	NAME(PlayM4_SetFileRefCallBack)(m_lPort, FileRefDone, (DWORD)this);
	//	NAME(PlayM4_SetVerifyCallBack)(m_lPort, 0, 0xffffffff, VerifyFun, (DWORD) this); // verify the whole file;
	//	NAME(PlayM4_SetDecCallBackMend)(m_lPort, DecCBFun, (long)this);	
	NAME(PlayM4_SetDecCallBackEx)(m_lPort, DecCBFun, NULL, 0);	

	//	BOOL bRelt = PlayM4_SetDecodeFrameType(m_lPort, 0);
	char szFilename[MAX_PATH];
	strcpy(szFilename, CT2A((LPCTSTR)m_strPlayFileName));

	if(!NAME(PlayM4_OpenFile)(m_lPort, szFilename))
	{
		m_strPlayFileName = _T("");
		strError.Format(_T("Open file failed(%s)"), MyErrorToString(NAME(PlayM4_GetLastError)(m_lPort)));
		MessageBox(m_hParentWnd, strError, _T("Error"), MB_OK);
		throw 0;
	}

	//	HANDLE hFile = CreateFile("D:\\F009-100726-142016.hik.idx", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	//	DWORD dwIndex = GetFileSize(hFile, NULL);
	//	BYTE* pIndex = new BYTE[dwIndex];
	//	DWORD dw;
	//	ReadFile(hFile, pIndex, dwIndex, &dw, NULL);
	//	NAME(PlayM4_SetRefValue)(m_lPort, pIndex, dwIndex);

	//	PlayM4_SetSecretKey(m_lPort, 1, "tyco_oem_ver", 12 * 8);

	NAME(PlayM4_SyncToAudio)(m_lPort, TRUE);

	// try overlay mode!
	//	NAME(PlayM4_SetOverlayMode)(m_lPort, TRUE, RGB(255,0,255));
	// try flip overlay mode
	//	NAME(PlayM4_SetOverlayFlipMode)(m_lPort, TRUE);

	m_dwMaxFileTime = NAME(PlayM4_GetFileTime)(m_lPort);
	if(!m_dwMaxFileTime)
	{
		// 		strError.Format(_T("File seconds is zero");
		// 		MessageBox(strError);
		// 		throw 0;
		m_dwMaxFileTime = 1;
	}

	m_dwDisplayHour		= m_dwMaxFileTime/3600;
	m_dwDisplayMinute   = (m_dwMaxFileTime % 3600) / 60;
	m_dwDisplaySecond   = m_dwMaxFileTime % 60;
	m_dwTotalFrames		= NAME(PlayM4_GetFileTotalFrames)(m_lPort);

	//if(m_bConvertAVI)
	//{
	//	AVI_CONVERT_PARA strParam;
	//	long dwHeight, dwWidth;
	//	NAME(PlayM4_GetPictureSize)(m_lPort, &dwWidth, &dwHeight);
	//	strParam.dwFrameWidth  = MOD16(dwWidth);
	//	strParam.dwFrameHeight = MOD16(dwHeight);
	//	strParam.dwFrameSize   = strParam.dwFrameWidth * strParam.dwFrameHeight *3/2;
	//	strParam.dwTotalFrames = m_dwTotalFrames;

	//	BOOL bInitAVI = g_classAVI.InitResource(&strParam, m_strSaveAVIPath);
	//	if(!bInitAVI)
	//	{
	//		strError.Format(_T("Init AVI Resource failed!"));
	//		MessageBox(strError);
	//		g_classAVI.ReleaseResource();
	//		m_bConvertAVI = FALSE;
	//	}
	//}

	// If you want to change the display buffer. Do hear!
	//	NAME(PlayM4_SetDisplayBuf)(m_lPort,50);
	//	NAME(PlayM4_SetDisplayBufAddtionalLen)(m_lPort, 6);

	Play();
	//	PlayM4_SetPlayedTimeEx(m_lPort, 3000000);
	// 	BOOL b = NAME(PlayM4_SetDisplayType)(m_lPort, 3);
	//	PlayM4_SetCurrentFrameNum(m_lPort, 10000);
	//	PlayM4_SetPlayPos(m_lPort, 1.2);
	// 	DWORD dw = PlayM4_GetLastError(m_lPort);
	::SetWindowText(m_hParentWnd, (LPCTSTR) m_strPlayFileName);
}

// close file
void CDVRPlayer::CloseFile()
{
	Stop();
	NAME(PlayM4_CloseFile)(m_lPort);
	//	NAME(PlayM4_FreePort)(m_lPort);
	////m_pMainMenu->GetSubMenu(3)->EnableMenuItem(10, MF_ENABLED|MF_BYPOSITION);
	//Destory();
	m_bOpen = FALSE;
	m_bFileRefCreated =	FALSE;	
}

// Funtion: Open the file by stream type and play it
void CDVRPlayer::OpenStream()
{
	m_dwDisplayHour		= 0;
	m_dwDisplayMinute   = 0;
	m_dwDisplaySecond   = 0;
	m_dwTotalFrames     = 0;
	m_bFileEnd          = FALSE;
	HIK_MEDIAINFO		stInfo;
	ZeroMemory(&stInfo,sizeof(HIK_MEDIAINFO));

	m_hStreamFile = CreateFile(m_strPlayFileName,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if(m_hStreamFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, _T("Open file failed"), _T("Error"), MB_OK);
		throw 0;
	}
	m_dwMaxFileSize = ::GetFileSize(m_hStreamFile, NULL);
	//	NAME(PlayM4_SetSourceBufCallBack)(m_lPort, 6000000, SourceBufFun, (DWORD)this, NULL);
	NAME(PlayM4_SetStreamOpenMode)(m_lPort, STREAME_FILE);
	m_dwHeadSize = NAME(PlayM4_GetFileHeadLength)();
	PBYTE pBuf = NULL;
	char csError[50];

	pBuf = new BYTE[m_dwHeadSize];
	if(!pBuf)
	{
		MessageBox(NULL, _T("Alloc memory failed"), _T("Error"), MB_OK);
		throw 0;
	}
	DWORD nRealRead;
	SetFilePointer(m_hStreamFile, 0, 0, FILE_BEGIN);
	ReadFile(m_hStreamFile, pBuf, m_dwHeadSize, &nRealRead, NULL);
	if(nRealRead != m_dwHeadSize)
	{
		MessageBox(NULL, _T("File is too small"), _T("Error"), MB_OK);
		delete []pBuf;
		pBuf = NULL;
		throw 0;
	}

	unsigned int g_strFileHdr[10] = { 0x484B4834, 0xd6d0b3fe, 0x20040308, 0x0, 0x10011001, 0x00101001, 0x3e80, 0x01200160, 0x1011, 0x4 };

	//	NAME(PlayM4_OpenStream)(m_lPort, g_strFileHdr, 40,  6*1000*1024)
#ifdef SPLIT_INPUT
	if(!NAME(PlayM4_OpenStreamEx)(m_lPort, (BYTE*)&stInfo, m_dwHeadSize, 6*1000*1024))
	{
		sprintf(csError, "Open stream failed(%s)", MyErrorToString(NAME(PlayM4_GetLastError)(m_lPort)));
		MessageBox(csError);
		delete []pBuf;
		pBuf = NULL;
		throw 0;
	}
	PlayM4_SyncToAudio(m_lPort, FALSE);
#else defined MIX_INPUT	

	if(!NAME(PlayM4_OpenStream)(m_lPort, pBuf, sizeof(stInfo),  6*1000*1024))
	{
		sprintf(csError, "Open stream failed(%s)", MyErrorToString(NAME(PlayM4_GetLastError)(m_lPort)));
		MessageBox(NULL, CA2T(csError), _T("Error"), MB_OK);
		delete []pBuf;
		pBuf = NULL;
		throw 0;
	}
	NAME(PlayM4_SyncToAudio)(m_lPort, FALSE);
#endif

	delete []pBuf;
	pBuf = NULL;

	DWORD dw;
	m_hThread	  = NULL;
	m_hEventInput = NULL;
	m_hEventKill  = NULL;

	m_hThread	  =	CreateThread(NULL,0, LPTHREAD_START_ROUTINE (InputStreamThread),this,0,&dw);
	m_hEventInput =	CreateEvent(NULL,TRUE,FALSE,NULL);
	m_hEventKill  =	CreateEvent(NULL,FALSE,FALSE,NULL);
	if( !(m_hThread&&m_hEventInput&&m_hEventKill) )
	{
		MessageBox(NULL, _T("Create thread failed"), _T("Error"), MB_OK);
		throw 0;
	}

	// try overlay mode!
	//	NAME(PlayM4_SetOverlayMode)(m_lPort, TRUE, RGB(255,0,255));
	// try flip overlay mode
	//	NAME(PlayM4_SetOverlayFlipMode)(m_lPort, TRUE);

	Play();
}


// Function:Close the stream.
void CDVRPlayer::CloseStream()
{
	Stop();
	NAME(PlayM4_CloseStream)(m_lPort);
	if(m_hStreamFile)
	{
		CloseHandle(m_hStreamFile);
		m_hStreamFile = NULL;
	}

	if(m_hThread)
	{
		SetEvent(m_hEventKill);
		DWORD dwStatus;
		for(int i = 0; i < 5; i++)
		{
			if(!::GetExitCodeThread(m_hThread, &dwStatus)|| (i == 4) )
			{
				TerminateThread(m_hThread, 0);
				TRACE("GetExitCode option error!-decodethread\n");
			}
			else
			{
				if(dwStatus == STILL_ACTIVE)
				{
					SetEvent(m_hEventKill);
					Sleep(2);
				}
				else
				{
					break;
				}
			}
		}
		CloseHandle(m_hThread);
		m_hThread = NULL;
	}

	if(m_hEventInput)
	{
		CloseHandle(m_hEventInput);
		m_hEventInput = NULL;
	}

	if(m_hEventKill)
	{
		CloseHandle(m_hEventKill);
		m_hEventKill = NULL;
	}

	Destory();
	m_bOpen = FALSE;
	m_bFileRefCreated =	FALSE;		
}

bool CDVRPlayer::SetDisplayRegion(HWND hRenderWnd, RECT* rcDisplayRegion)
{
	if (GetPlayState() != State_Step && GetPlayState() != State_Pause) 
	{
		return false;
	}

	NAME(PlayM4_SetDisplayRegion)(m_lPort, 0, rcDisplayRegion, hRenderWnd, TRUE);

	NAME(PlayM4_RefreshPlayEx)(m_lPort, 0);

	m_hRenderWnd = hRenderWnd;
	m_rcDisplayRegion = *rcDisplayRegion;
	return true;
}

bool CDVRPlayer::SetDisplayType(LONG lType)
{
	return NAME(PlayM4_SetDisplayType)(m_lPort, lType);
}
LONG CDVRPlayer::GetDisplayType()
{
	return NAME(PlayM4_GetDisplayType)(m_lPort);
}

bool CDVRPlayer::SetTimerType(DWORD dwTimerType)
{
	return NAME(PlayM4_SetTimerType)(m_lPort, dwTimerType, 0);
}

DWORD CDVRPlayer::GetTimerType()
{
	DWORD dwTimerType;
	NAME(PlayM4_GetTimerType)(m_lPort, &dwTimerType, 0);
	return dwTimerType;
}

void CDVRPlayer::ResetBuf()
{
	NAME(PlayM4_ResetBuffer)(m_lPort, BUF_VIDEO_RENDER);
	NAME(PlayM4_ResetBuffer)(m_lPort, BUF_AUDIO_RENDER);
	NAME(PlayM4_ResetBuffer)(m_lPort, BUF_VIDEO_SRC);
	NAME(PlayM4_ResetBuffer)(m_lPort, BUF_AUDIO_SRC);
}

//错误信息
char* CDVRPlayer::MyErrorToString(DWORD error)
{
	switch(error)
	{
	case 0:
		return "No error.\0";
	case 1:
		return "The parameter that user inputted is invalid.\0";
	case 2:
		return "The order of the function to be called is incorrect.\0";
	case 3:
		return "Failure when creating system multimedia clock.\0";
	case 4:
		return "Failure when decoding video data.\0";
	case 5:
		return "Failure when decoding audio data.\0";
	case 6:
		return "Failure when allocating memory.\0";
	case 7:
		return "File open failed when calling API Hik_PlayM4_OpenFile.\0";
	case 8:
		return "Failure when creating thread or event.\0";
	case 9:
		return "Failure when creating directdraw object.\0";
	case 10:
		return "Failure when creating off-screen surface.\0";
	case 11:
		return "The input source buffer has overflowed when calling API Hik_PlayM4_InputData.\0";
	case 12:
		return "Failure when creating audio device.\0";
	case 13:
		return "Failure when setting audio volume.\0";
	case 14:
		return "The function only supports playing a file.\0";
	case 15:
		return "The function only supports playing a stream.\0";
	case 16:
		return "Neither MMX nor SSE arithmetic is supported by system.\0";
	case 17:
		return "Unknown file header.\0";
	case 18:
		return "The version of video decoder and video encoder is not compatible.\0";
	case 19:
		return "Failure when initializing decoder.\0";
	case 20:
		return "The file data is unknown. No I-frame found.\0";
	case 21:
		return "Failure when initializing multimedia clock.\0";
	case 22:
		return "Failure when blitting overlay.\0";
	case 23:
		return "Failure when updating overlay or offscreen surface.\0";
	case 24:
		return "Open file error, streamtype is multi.\0";
	case 25:
		return "Openfile error, streamtype is video.\0";
	case 26:
		return "JPEG compression error when capturing jpeg file.\0";
	case 27:
		return "Version of this file not supported when extracting h264 video data.\0";
	case 28:
		return "Failure when extracting video data.\0";
	default:
		return "Unrecognized error value.\0";
	}
}
