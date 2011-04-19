#include "StdAfx.h"
#include "atlimage.h"
#include "Player.h"
#include "DVRPlayer.h"

//#define TEST_PERFORMANCE

#ifdef TEST_PERFORMANCE
#include "FreeProfiler.h"

FreeProfilerImport("FreeProfiler\\Configuration\\FreeProfilerConfig.xml");

#endif
int ScaleFrameMetaDataList::g_ScaleIndex = 0;

ScaleFrameMetaDataList::ScaleFrameMetaDataList()
	: m_bScaling(false)
{
	CString csEvent;
	csEvent.Format(_T("ScaleEvent_%d"), g_ScaleIndex);
	m_hEvent[eScaleEvent] = ::CreateEvent(NULL, TRUE, FALSE, csEvent);
	csEvent.Format(_T("ExitScaleThread_%d"), g_ScaleIndex);
	m_hEvent[eExitEvent] = ::CreateEvent(NULL, TRUE, FALSE, csEvent);
	++g_ScaleIndex;

	m_hThread = (HANDLE)::_beginthreadex(NULL, 0, ScaleCallBack, this, 0, NULL);
	memset(&m_lWndWidth, 0, sizeof(m_lWndWidth));
	memset(&m_lWndHeight, 0, sizeof(m_lWndHeight));
}

ScaleFrameMetaDataList::~ScaleFrameMetaDataList()
{
	::SetEvent(m_hEvent[eExitEvent]);
	::WaitForSingleObject(m_hThread, 10000);
	::CloseHandle(m_hThread);
	::CloseHandle(m_hEvent[eScaleEvent]);
	::CloseHandle(m_hEvent[eExitEvent]);
}
void ScaleFrameMetaDataList::GetScaledFrameMetaDataList(HHV::FrameMetaDataList& dstFrame, HHV::FrameMetaData& attrs, const HHV::FrameMetaDataList& srcFrame, LONG lWndWidth, LONG lWndHeight)
{
	if (!m_bScaling)
	{
		m_TmpLock.Lock();
		m_TmpMetaDataList = srcFrame;
		m_lWndWidth = lWndWidth;
		m_lWndHeight = lWndHeight;
		SetEvent(m_hEvent[eScaleEvent]);
		m_TmpLock.Unlock();
	}
	m_ScaleLock.Lock();
	dstFrame = m_FrameMetaDataList;
	attrs = m_Attributes;
	m_ScaleLock.Unlock();
}

unsigned ScaleFrameMetaDataList::ScaleCallBack(void* pParam)
{
	ScaleFrameMetaDataList* pThis = (ScaleFrameMetaDataList*)pParam;
	BOOL bExit = FALSE;
	while(!bExit)
	{
		DWORD dwEventIndex = ::WaitForMultipleObjects(sizeof(pThis->m_hEvent)/sizeof(HANDLE), pThis->m_hEvent, FALSE, 1000);
		switch(dwEventIndex)
		{
		case WAIT_TIMEOUT:
			break;
		case WAIT_OBJECT_0+eScaleEvent:
			{
				pThis->m_TmpLock.Lock();
				HHV::FrameMetaDataList frame = pThis->m_TmpMetaDataList;
				HHV::FrameMetaData attributes;
				LONG lWndWidth = pThis->m_lWndWidth;
				LONG lWndHeight = pThis->m_lWndHeight;
				pThis->m_TmpLock.Unlock();
				if (frame.size() > 0)
				{
					for (HHV::FrameMetaDataList::iterator it = frame.begin(); it != frame.end(); ++it)
					{
						ScaleAttributes(attributes, it->attributes, lWndWidth, lWndHeight);
						ScaleFrameMetaData(*it, lWndWidth, lWndHeight);
					}
				}
				pThis->m_ScaleLock.Lock();
				pThis->m_FrameMetaDataList = frame;
				pThis->m_Attributes = attributes;
				pThis->m_ScaleLock.Unlock();
				ResetEvent(pThis->m_hEvent[eScaleEvent]);
			}
			break;
		case WAIT_OBJECT_0+eExitEvent:
			bExit = TRUE;
			break;
		}
	}
	::_endthreadex(0);
	return 0;
}

void ScaleFrameMetaDataList::ScaleAttributes(HHV::FrameMetaData& attributes, HHV::Attributes& attrs, LONG lWndWidth, LONG lWndHeight)
{
#ifdef TEST_PERFORMANCE
	FreeProfilerRecordCodeBlock(0x7, "")
#endif
	
	HHV::Attributes::const_iterator it = attrs.find("NumberOfRegion");
	if (it != attrs.end() && !it->first.empty())
	{
		int nNumberOfRegion = atoi(it->second.c_str());
		std::vector<int> imgSize = ToArray(attrs, "region.imagesize");
		if (imgSize.size() == 2)
		{
			float xScale = (float)lWndWidth/imgSize[0];
			float yScale = (float)lWndHeight/imgSize[1];
			for (int i = 1; i <= nNumberOfRegion; ++i)
			{
				std::string shape = ShapeType(attrs, i);
				if (shape == "rectangle" || shape == "line")
				{
					HHV::ObjectType ot = ToObjectType(attrs, i);
					ScaleObjectType(ot, xScale, yScale);
					attributes.displayData.gui_object_list.push_back(ot);
				}
				else if (shape == "polygon")
				{
					HHV::PolygonM pm = ToPolygon(attrs, i);
					ScalePolygonM(pm, xScale, yScale);
					attributes.displayData.polygon_list.push_back(pm);
				}
				//else if (shape == "line")
				//{
				//	CvPoint imgSize = ImageSize(attrs, i);
				//	if (imgSize.x >0 && imgSize.y > 0 )
				//	{
				//		DrawPolyLine(graphics, ToPolyLine(attrs, i), lWndWidht, lWndHeight, imgSize.x, imgSize.y);
				//	}
				//}
			}
		}
	}
}

void ScaleFrameMetaDataList::ScaleFrameDisplayData(HHV::FrameDisplayData& fdd,  LONG lWndWidth, LONG lWndHeight)
{
	float xScale = (float)lWndWidth/fdd.image_width;
	float yScale = (float)lWndHeight/fdd.image_height;

	for (HHV::DisplayObjectMetaList::iterator it = fdd.disp_obj_list.begin(); it != fdd.disp_obj_list.end(); ++it)
	{
		ScaleDisplayObjectMeta(*it, xScale, yScale);
	}
	
	for (HHV::PolyLines::iterator it = fdd.line_list.begin(); it != fdd.line_list.end(); ++it)
	{
		ScalePolyLine(*it, xScale, yScale);
	}

	for (HHV::Texts::iterator it = fdd.text_list.begin(); it != fdd.text_list.end(); ++it)
	{
		ScaleTextMeta(*it, xScale, yScale);
	}

	for (HHV::Polygons::iterator it = fdd.polygon_list.begin(); it != fdd.polygon_list.end(); ++it)
	{
		ScalePolygonM(*it, xScale, yScale);
	}

	for (HHV::GUIObjects::iterator it = fdd.gui_object_list.begin(); it != fdd.gui_object_list.end(); ++it)
	{
		ScaleObjectType(*it, xScale, yScale);
	}
}
void ScaleFrameMetaDataList::ScaleDisplayObjectMeta(HHV::DisplayObjectMeta& dom, float xScale, float yScale)
{
	ScaleObjectType(dom.obj, xScale, yScale);
	ScalePolyLine(dom.track, xScale, yScale);
}
void ScaleFrameMetaDataList::ScalePolyLine(HHV::PolyLine& line, float xScale, float yScale)
{
	line.thickness = line.thickness*xScale;
	for (HHV::Points::iterator it = line.lines.begin(); it != line.lines.end(); ++it)
	{
		it->x = it->x * xScale;
		it->y = it->y * yScale;
	}
}
void ScaleFrameMetaDataList::ScaleTextMeta(HHV::TextMeta& txt, float xScale, float yScale)
{
	txt.size *= xScale;
	txt.x *= xScale;
	txt.y *= yScale;
}
void ScaleFrameMetaDataList::ScalePolygonM(HHV::PolygonM& pg, float xScale, float yScale)
{
	pg.style.thickness *= xScale;
	for (HHV::Points::iterator it = pg.points.begin(); it != pg.points.end(); ++it)
	{
		it->x *= xScale;
		it->y *= yScale;
	}
}
void ScaleFrameMetaDataList::ScaleObjectType(HHV::ObjectType& ot, float xScale, float yScale)
{
	ot.style.thickness *= xScale;
	switch(ot.type)
	{
	case 0:
	case 1:
		ot.x0 *= xScale;
		ot.y0 *= yScale;
		ot.x1 *= xScale;
		ot.y1 *= yScale;
		break;
	case 2:
		ot.x0 *= xScale;
		ot.y0 *= yScale;
		ot.x1 *= xScale;
		ot.y1 *= yScale;
		ot.x2 *= xScale;
		ot.y2 *= yScale;
		ot.x3 *= xScale;
		ot.y3 *= yScale;
		break;
	default:
		break;
	}
}

std::string ScaleFrameMetaDataList::ToString(LPCSTR prefix, int num)
{
	CStringA csRet;
	csRet.Format("%s.%d", prefix, num);
	return (LPCSTR)csRet;
}

std::vector<int> ScaleFrameMetaDataList::ToArray(const HHV::Attributes& attrs, LPCSTR prefix, int index)
{
	std::vector<int> ary;
	HHV::Attributes::const_iterator it = attrs.find((index == -1) ? prefix : ToString(prefix, index));
	if (it != attrs.end())
	{
		int nStartPos = 0;
		int nPos = it->second.find(',', nStartPos);
		while (nPos != std::string::npos)
		{
			ary.push_back(atoi(it->second.substr(nStartPos, nPos).c_str()));
			nStartPos = nPos+1;
			nPos = it->second.find(',', nStartPos);
		}
		if (nStartPos != 0)
		{
			ary.push_back(atoi(it->second.substr(nStartPos, it->second.length()-nStartPos).c_str()));
		}
	}
	return ary;
}
std::string ScaleFrameMetaDataList::ShapeType(const HHV::Attributes& attrs, int index)
{
	HHV::Attributes::const_iterator it = attrs.find(ToString("shape-type", index));
	if (it != attrs.end())
	{
		return it->second;
	}
	return "";
}
HHV::PolyLine ScaleFrameMetaDataList::ToPolyLine(const HHV::Attributes& attrs, int index)
{
	return HHV::PolyLine();
}
HHV::ObjectType ScaleFrameMetaDataList::ToObjectType(const HHV::Attributes& attrs, int index)
{
	HHV::ObjectType obj;

	std::string shape = ShapeType(attrs, index);
	obj.style.bFill = false;
	obj.type = -1;
	obj.style.alpha = 100;
	obj.style.color.r = 0;
	obj.style.color.g = 0;
	obj.style.color.b = 0;
	obj.style.thickness = 2;

	if (shape == "line")
	{
		std::vector<int> ary = ToArray(attrs, "coordinate", index);
		if (ary.size() >= 4)
		{
			obj.type = 0;
			obj.x0 = ary[0];
			obj.y0 = ary[1];
			obj.x1 = ary[2];
			obj.y1 = ary[3];	
		}
	}
	else if (shape == "rectangle")
	{
		std::vector<int> ary = ToArray(attrs, "coordinate", index);
		if (ary.size() >= 4)
		{
			obj.type = 1;
			obj.x0 = ary[0];
			obj.y0 = ary[1];
			obj.x1 = ary[2];
			obj.y1 = ary[3];
			//obj.x2 = ary[4];
			//obj.y2 = ary[5];
			//obj.x3 = ary[6];
			//obj.y3 = ary[7];
		}
	}

	return obj;
}
HHV::PolygonM ScaleFrameMetaDataList::ToPolygon(const HHV::Attributes& attrs, int index)
{
	HHV::PolygonM pm;
	pm.style.bFill = false;
	pm.style.bFlash = false;
	pm.style.alpha = 100;
	pm.style.thickness = 2;
	pm.style.color.r = 0;
	pm.style.color.g = 0;
	pm.style.color.b = 0;

	std::vector<int> ary = ToArray(attrs, "coordinate", index);
	if (0 == (ary.size() & 1))
	{
		for (int i = 0; i < ary.size(); i += 2)
		{
			pm.points.push_back(cvPoint(ary[i], ary[i+1]));
		}
	}

	return pm;
}
WATERMARK_VER1_INFO CDVRPlayer::m_strWaterMark;

// metaData scale


CDVRPlayer::CDVRPlayer(void)
{
	m_lPort = -1;
	m_UserID = -1;

	Gdiplus::GdiplusStartupInput gdiplusStartupInput;

	// Initialize GDI+.
	Gdiplus::GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);

	WSADATA wsaD;
	WORD wVersion = MAKEWORD(2, 2);
	if ( WSAStartup( wVersion, &wsaD ) != 0 )
	{
		::MessageBox(m_hParentWnd, _T("Socket Lib Load Failure!"), _T("tips"), MB_OK );
	}
}


CDVRPlayer::~CDVRPlayer(void)
{
	Gdiplus::GdiplusShutdown(m_gdiplusToken);
	m_gdiplusToken = NULL;

	m_spDVRLoginMgr->Clearup();
	m_spDVRLoginMgr.reset(NULL);
	WSACleanup();
}

bool CDVRPlayer::Init(HWND hRenderWnd, RECT* rcDisplayRegion, HWND hParentWnd, int lPort)
{
	m_enumState = CDVRPlayer::eState_Close;
	m_lPort = lPort;
	m_hRenderWnd = hRenderWnd;
	m_rcDisplayRegion = *rcDisplayRegion;
	m_dwMaxFileTime = 0;
	m_bFileRefCreated = false;
	//m_DVRSettings.m_eCapturePicType = CDVRSettings::eBMP;
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
	m_nPlayType = -1;
	m_nPlaybackIndex = -1;
	m_bDrawMetaData = TRUE;

	if (m_lPort == -1)
		NAME(PlayM4_GetPort)(&m_lPort);

	m_spDVRLoginMgr.reset(new CLoginDvrMgr);
	m_spDVRLoginMgr->Startup();

	return true;
}

void CDVRPlayer::Destory()
{
	if (m_nPlayType == 0)
	{
		DestoryPlayFile();
	}
	else if (m_nPlayType == 1)
	{
		DestoryMonitor();
	}

	m_nPlayType = -1;
	m_MonitorHandler.clear();
}

BOOL CDVRPlayer::InitForPlayFile()
{
	Destory();
	m_nPlayType = 0;
#if (WINVER > 0x0400)
	// If do not support multi monitor,may not call!
	HMONITOR hMonitor;
	char chDriverDesp[50];
	char chDriverName[50];

	NAME(PlayM4_InitDDrawDevice)();
	DWORD nVal=NAME(PlayM4_GetDDrawDeviceTotalNums)();
	if(nVal > 1)
	{
		nVal = min<DWORD>(nVal, MAX_DISPLAY_DEVICE);
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

	// set the capture picture call back function;
	//	NAME(PlayM4_SetDisplayCallBack)(m_lPort, DisplayCBFun);
	// set the wave audio call back function;
	//	NAME(PlayM4_SetAudioCallBack)(m_lPort, WaveCBFun, (long)this);

	NAME(PlayM4_SetDDrawDevice)(m_lPort, 0);
	// Test adapter Capability;
	NAME(PlayM4_SetVolume)(m_lPort, 0);

	NAME(PlayM4_RegisterDrawFun)(m_lPort, OnDrawFun, (LONG)this);

	return TRUE;
}

void CDVRPlayer::DestoryPlayFile()
{
	Close();

	NAME(PlayM4_RealeseDDraw)();
	NAME(PlayM4_ReleaseDDrawDevice)();
	NAME(PlayM4_FreePort)(m_lPort);

	m_lPort = -1;
	m_enumState = CDVRPlayer::eState_Close;
}
BOOL CDVRPlayer::InitForMonitor()
{
	Destory();

	m_nPlayType = 1;

	m_spHWndMgr.reset(new CHWndManager);
	m_spPlayerMgr.reset(new CPlayerMgr);

	m_spHWndMgr->InitSplit(m_hRenderWnd);
	int splitMode = SPLIT_1;	//1;3;4;6;9;16;25;36
	switch (GetDVRSettings().m_nRenderWndNum)
	{
	case 3:
		splitMode = SPLIT_3;
		break;
	case 4:
		splitMode = SPLIT_4;
		break;
	case 6:
		splitMode = SPLIT_6;
		break;
	case 9:
		splitMode = SPLIT_9;
		break;
	case 16:
		splitMode = SPLIT_16;
		break;
	case  25:
		splitMode = SPLIT_25;
		break;
	case  36:
		splitMode = SPLIT_36;
		break;
	default:
		splitMode = SPLIT_1;
	}
	m_spHWndMgr->SetSplitMode(m_lPort, splitMode);
	m_spPlayerMgr->Init(NULL);
	//m_spDVRLoginMgr->Startup();

	return TRUE;
}

void CDVRPlayer::DestoryMonitor()
{
	if (IsMonitoring())
	{
		StopMonitor();
	}
	m_spPlayerMgr->Clearup();
	m_spHWndMgr.reset(NULL);
	m_spPlayerMgr.reset(NULL);
}
BOOL CDVRPlayer::Login()
{
	if (m_DVRSettings.m_csUsername.GetLength() > 0 && 
		m_DVRSettings.m_csPassword.GetLength() > 0 &&
		m_DVRSettings.m_csMediaServerIP.GetLength() > 0 &&
		m_DVRSettings.m_lPort != -1)
	{
		return Login(m_DVRSettings.m_csUsername, m_DVRSettings.m_csPassword, m_DVRSettings.m_csMediaServerIP, m_DVRSettings.m_lPort);
	}

	return FALSE;
}
BOOL CDVRPlayer::Login(LPCTSTR szUsername, LPCTSTR szPwd, LPCTSTR szIP, int nPort)
{
	m_UserID = m_spDVRLoginMgr->Login(szUsername, szPwd, szIP, nPort);
	if (m_UserID >= 0)
	{
		m_DVRSettings.m_csUsername = szUsername;
		m_DVRSettings.m_csPassword = szPwd;
		m_DVRSettings.m_csMediaServerIP = szIP;
		m_DVRSettings.m_lPort = nPort;

		return TRUE;
	}
	return FALSE;
}
void CDVRPlayer::Logout()
{
	if (m_UserID >= 0)
	{
		m_spDVRLoginMgr->Logout(m_UserID);
		m_UserID = -1;
	}
}

BOOL CDVRPlayer::StartMonitor()
{
	if (InitForMonitor())
	{
		if (!IsLogined())
		{
			::MessageBox(m_hParentWnd, _T("请先登录服务器！"), _T("错误"), MB_OK);
			return FALSE;
		}

		for (int i = 0; i < GetDVRSettings().m_nRenderWndNum; ++i)
		{
			HWND hWnd = m_spHWndMgr->GetHWnd(i);
			HHV_CLIENT_INFO	 hhvInfo;
			strcpy( hhvInfo.connInfo.ip, CT2A(GetDVRSettings().m_csMediaServerIP));
			hhvInfo.connInfo.port = GetDVRSettings().m_lPort;
			hhvInfo.channel = i;
			int ret = m_spPlayerMgr->StartMonitor( hWnd, &hhvInfo );
			if( ret < 0 )
			{
				CString csErr;
				csErr.Format(_T("监视出错.IP:%s Port:%d 通道:%d, "), GetDVRSettings().m_csMediaServerIP, GetDVRSettings().m_lPort, i);
				MessageBox(m_hParentWnd, csErr, _T("错误"), MB_OK);
			}
			else
			{
				m_MonitorHandler[i] = ret;
			}
		}
	}

	if (!m_MonitorHandler.empty())
	{
		GetPictureSize(&m_nWidth, &m_nHeight);
	}
	return !m_MonitorHandler.empty();
}

BOOL CDVRPlayer::SetWndChannel(int nWndIndex, int nChannel)
{
	if (nWndIndex < GetDVRSettings().m_nRenderWndNum && nWndIndex >= 0 && nChannel >= 0 && nChannel < 16)
	{
		std::map<int, int>::iterator it = m_MonitorHandler.find(nWndIndex);
		if (it != m_MonitorHandler.end())
		{
			m_spPlayerMgr->StopMonitor(it->second);
			m_MonitorHandler.erase(it);
		}
		HWND hWnd = m_spHWndMgr->GetHWnd(nWndIndex);
		HHV_CLIENT_INFO	 hhvInfo;
		strcpy( hhvInfo.connInfo.ip, CT2A(GetDVRSettings().m_csMediaServerIP));
		hhvInfo.connInfo.port = GetDVRSettings().m_lPort;
		hhvInfo.channel = nChannel;
		int ret = m_spPlayerMgr->StartMonitor( hWnd, &hhvInfo );
		if( ret < 0 )
		{
			CString csErr;
			csErr.Format(_T("监视出错.IP:%s Port:%d 通道:%d, "), GetDVRSettings().m_csMediaServerIP, GetDVRSettings().m_lPort, nChannel);
			MessageBox(m_hParentWnd, csErr, _T("错误"), MB_OK);
		}
		else
		{
			m_MonitorHandler[nWndIndex] = ret;
		}

		return ret >= 0;
	}
	return FALSE;
}
void CDVRPlayer::StopMonitor()
{
	for (std::map<int, int>::iterator it = m_MonitorHandler.begin(); it != m_MonitorHandler.end(); ++it)
	{
		m_spPlayerMgr->StopMonitor(it->second);
	}

	m_MonitorHandler.clear();
}

BOOL CDVRPlayer::IsMonitoring()
{
	return !m_MonitorHandler.empty();
}

BOOL CDVRPlayer::StartPlayback(SYSTEM_VIDEO_FILE& sysFile)
{
	if (IsLogined())
	{
		if (m_spPlayerMgr.get() == NULL)
		{
			InitForMonitor();
		}
		m_nPlaybackIndex = m_spPlayerMgr->StartPlayBackByTime(m_hRenderWnd, &sysFile, CT2A(m_DVRSettings.m_csMediaServerIP), m_DVRSettings.m_lPort);
		if (m_nPlaybackIndex < 0)
		{
			::MessageBox(m_hParentWnd, _T("监视出错"), _T("Error"), MB_OK);
		}
		return m_nPlaybackIndex >= 0;
	}
	else
	{
		::MessageBox(m_hParentWnd, _T("请先登录服务器！"), _T("错误"), MB_OK);
	}

	return FALSE;
}

void CDVRPlayer::EndPlayback()
{
	if (IsLogined() && m_nPlaybackIndex >= 0)
	{
		m_spPlayerMgr->StopPlayBackByTime(m_nPlaybackIndex);

		m_nPlaybackIndex = -1;
	}
}

//	Draw the Meta Data
void CDVRPlayer::OnDrawFun(long nPort, HDC hDC, LONG nUser)
{
#ifdef TEST_PERFORMANCE
	FreeProfilerRecordCodeBlock(0x1, "OnDrawFun")
#endif
#ifdef _DEBUG
		DWORD dwBegin = GetTickCount();
#endif // _DEBUG
	CDVRPlayer* pThis = (CDVRPlayer*)nUser;
	if (!pThis || !pThis->m_bDrawMetaData)
	{
		return;
	}
	int renderWndWidth = pThis->GetDVRSettings().m_nRenderWidth;
	int renderWndHeight = pThis->GetDVRSettings().m_nRenderHeight;

	HHV::FrameMetaDataList metaDataList;
	if (pThis->GetFrameMetaDataList(metaDataList) > 0)
	{
		HHV::FrameMetaDataList scaledMetaData;
		HHV::FrameMetaData	attributes;
		pThis->m_ScaleMetaData.GetScaledFrameMetaDataList(scaledMetaData, attributes, metaDataList, pThis->GetDVRSettings().m_nRenderWidth, pThis->GetDVRSettings().m_nRenderHeight);
		Gdiplus::Graphics graphics(hDC);
		DrawFrameMetaData(graphics, attributes, pThis->GetDVRSettings().m_nRenderWidth, pThis->GetDVRSettings().m_nRenderHeight);
		for (HHV::FrameMetaDataList::iterator itFrame = scaledMetaData.begin(); itFrame != scaledMetaData.end(); ++itFrame)
		{
			DrawFrameMetaData(graphics, *itFrame, pThis->GetDVRSettings().m_nRenderWidth, pThis->GetDVRSettings().m_nRenderHeight);
		}
	}
#ifdef _DEBUG
	DWORD dwEnd = GetTickCount();
	TRACE3("\n**********OnDrawFun: (%d) (%d, %d) ************\n",dwEnd - dwBegin, dwBegin, dwEnd);
#endif
}
#define INT_SCALE(x, scale)	(x)
// Draw Function




void CDVRPlayer::DrawFrameMetaData(Gdiplus::Graphics& graphics, const HHV::FrameMetaData& frame, const LONG& lWndWidth, const LONG& lWndHeight)
{
#ifdef TEST_PERFORMANCE
	FreeProfilerRecordCodeBlock(0x6, "")
#endif
#ifdef _DEBUG
	TRACE2("Frame Image: width(%d), height(%d)\n", frame.displayData.image_width, frame.displayData.image_height);
	TRACE(_T("Frame Attributes:"));
	DWORD dwBegin = GetTickCount();
#endif
	//DrawAttributes(graphics, frame.attributes, lWndWidth, lWndHeight);

	//for (HHV::Attributes::const_iterator it = frame.attributes.begin(); it != frame.attributes.end(); ++it)
	//{
	//	TRACE(_T("Attr Key(%s), Value(%s)\n"), (LPTSTR)CA2T(it->first.c_str()), (LPTSTR)CA2T(it->second.c_str()));
	//}
	for (HHV::DisplayObjectMetaList::const_iterator itDspObj = frame.displayData.disp_obj_list.begin(); 
		itDspObj != frame.displayData.disp_obj_list.end(); 
		++itDspObj)
	{
		TRACE1("Draw DisplayObjectMeta: id=%s\n", (LPTSTR)CA2T(itDspObj->id.c_str()));
		DrawDisplayObjectMeta(graphics, *itDspObj, lWndWidth, lWndHeight, frame.displayData.image_width, frame.displayData.image_height);
	}

	for (HHV::PolyLines::const_iterator itLine = frame.displayData.line_list.begin(); 
		itLine != frame.displayData.line_list.end(); 
		++itLine)
	{
		DrawPolyLine(graphics, *itLine, lWndWidth, lWndHeight, frame.displayData.image_width, frame.displayData.image_height);
	}

	for (HHV::Texts::const_iterator itTxt = frame.displayData.text_list.begin();
		itTxt != frame.displayData.text_list.end();
		++itTxt)
	{
		DrawTextMeta(graphics, *itTxt, lWndWidth, lWndHeight, frame.displayData.image_width, frame.displayData.image_height);
	}

	for (HHV::Polygons::const_iterator itPolygon = frame.displayData.polygon_list.begin();
		itPolygon != frame.displayData.polygon_list.end();
		++itPolygon)
	{
		DrawPolygon(graphics, *itPolygon, lWndWidth, lWndHeight, frame.displayData.image_width, frame.displayData.image_height);
	}

	for (HHV::GUIObjects::const_iterator itGUIObj = frame.displayData.gui_object_list.begin();
		itGUIObj != frame.displayData.gui_object_list.end();
		++itGUIObj)
	{
		DrawObjectType(graphics, *itGUIObj, lWndWidth, lWndHeight, frame.displayData.image_width, frame.displayData.image_height);
	}
#ifdef _DEBUG
	DWORD dwEnd = GetTickCount();
	TRACE1("\nDrawFrameMetaData: %d\n", dwEnd-dwBegin);
#endif
}
void CDVRPlayer::DrawPolyLine(Gdiplus::Graphics& graphics, const HHV::PolyLine& line, const LONG& lWndWidth, const LONG& lWndHeight, const LONG& nImgWidth, const LONG& nImgHeight)
{
#ifdef TEST_PERFORMANCE
	FreeProfilerRecordCodeBlock(0x5, "")
#endif
	if (line.lines.size() > 1)
	{
		Gdiplus::Pen gPlusPen(Gdiplus::Color(line.color.r, line.color.g, line.color.b), line.thickness);
		Gdiplus::SolidBrush gPlusBrush(Gdiplus::Color(line.color.r, line.color.g, line.color.b));

		Gdiplus::Point* ptLines = new Gdiplus::Point[line.lines.size()];
		int i = 0;
		for (HHV::Points::const_iterator itPt = line.lines.begin();
			itPt != line.lines.end();
			++itPt, ++i)
		{
			ptLines[i].X = INT_SCALE(itPt->x, lWndWidth/nImgWidth);
			ptLines[i].Y = INT_SCALE(itPt->y, lWndHeight/nImgHeight);
		}

		switch(line.end_style)
		{
		case 1:
			gPlusPen.SetCustomEndCap(&Gdiplus::AdjustableArrowCap(line.arrow_length, line.arrow_width, FALSE));
			break;
		case 2:
			gPlusPen.SetCustomEndCap(&Gdiplus::AdjustableArrowCap(line.arrow_length, line.arrow_width, TRUE));
			break;
		case 0:
		default:
			break;
		}
		graphics.DrawLines(&gPlusPen, ptLines, line.lines.size());

		delete[] ptLines;
	}
}

void CDVRPlayer::DrawTextMeta(Gdiplus::Graphics& graphics, const HHV::TextMeta& txt, const LONG& lWndWidth, const LONG& lWndHeight, const LONG& nImgWidth, const LONG& nImgHeight)
{
#ifdef TEST_PERFORMANCE
	FreeProfilerRecordCodeBlock(0x4, "")
#endif
	Gdiplus::Font gPlusFont(L"黑体", INT_SCALE(txt.size, lWndWidth/nImgWidth), Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
	Gdiplus::SolidBrush gPlushBrush(Gdiplus::Color(txt.color.r, txt.color.g, txt.color.b));
	int nTxtLen = txt.text.length();
	WCHAR* pBuf = new WCHAR[nTxtLen+1];
	memset(pBuf, 0, sizeof(WCHAR)*(nTxtLen+1));
	::MultiByteToWideChar(CP_ACP, 0, txt.text.c_str(), -1, pBuf, nTxtLen+1);
	graphics.DrawString(pBuf, nTxtLen, &gPlusFont, Gdiplus::PointF(INT_SCALE(txt.x, lWndWidth/nImgWidth), INT_SCALE(txt.y, lWndHeight/nImgHeight)), &gPlushBrush);
	delete[] pBuf;
}
void CDVRPlayer::DrawPolygon(Gdiplus::Graphics& graphics, const HHV::PolygonM& polygon, const LONG& lWndWidth, const LONG& lWndHeight, const LONG& nImgWidth, const LONG& nImgHeight)
{
#ifdef TEST_PERFORMANCE
	FreeProfilerRecordCodeBlock(0x3, "")
#endif
	const HHV::DrawingStyle& style = polygon.style;

	Gdiplus::Pen gPlusPen(Gdiplus::Color(style.alpha*255/100, style.color.r, style.color.g, style.color.b), style.thickness);

	Gdiplus::Point* ptPolygons = new Gdiplus::Point[polygon.points.size()];
	for (int i = 0; i < polygon.points.size(); ++i)
	{
		ptPolygons[i].X = INT_SCALE(polygon.points[i].x, lWndWidth/nImgWidth);
		ptPolygons[i].Y = INT_SCALE(polygon.points[i].y, lWndHeight/nImgHeight);
	}
	if (polygon.style.bFill)
	{
		Gdiplus::SolidBrush gPlusBrush(Gdiplus::Color(style.alpha*255/100, style.fill_color.r, style.fill_color.g, style.fill_color.b));
		graphics.FillPolygon(&gPlusBrush, ptPolygons, polygon.points.size());
	}
	
	graphics.DrawPolygon(&gPlusPen, ptPolygons, polygon.points.size());
	delete[] ptPolygons;
}
void CDVRPlayer::DrawObjectType(Gdiplus::Graphics& graphics, const HHV::ObjectType& obj, const LONG& lWndWidth, const LONG& lWndHeight, const LONG& nImgWidth, const LONG& nImgHeight)
{
#ifdef TEST_PERFORMANCE
	FreeProfilerRecordCodeBlock(0x2, "")
#endif
	const HHV::DrawingStyle& style = obj.style;

	Gdiplus::Pen gPlusPen(Gdiplus::Color(style.alpha*255/100, style.color.r, style.color.g, style.color.b), style.thickness);

	switch(obj.type)
	{
	case 0:		//line_segment
		graphics.DrawLine(&gPlusPen, INT_SCALE(obj.x0, lWndWidth/nImgWidth), INT_SCALE(obj.y0, lWndHeight/nImgHeight), INT_SCALE(obj.x1, lWndWidth/nImgWidth), INT_SCALE(obj.y1, lWndHeight/nImgHeight));
		break;
	case 1:		//rectangle
		if (style.bFill)
		{
			Gdiplus::SolidBrush gPlusBrush(Gdiplus::Color(style.alpha*255/100, style.fill_color.r, style.fill_color.g, style.fill_color.b));
			graphics.FillRectangle(&gPlusBrush, INT_SCALE(obj.x0 + obj.style.thickness/2, lWndWidth/nImgWidth), INT_SCALE(obj.y0 + obj.style.thickness/2, lWndHeight/nImgHeight), 
				INT_SCALE(obj.x1 - obj.x0 - obj.style.thickness, lWndWidth/nImgWidth), INT_SCALE(obj.y1 - obj.y0 - obj.style.thickness, lWndHeight/nImgHeight));
		}

		graphics.DrawRectangle(&gPlusPen, INT_SCALE(obj.x0, lWndWidth/nImgWidth), INT_SCALE(obj.y0, lWndHeight/nImgHeight), 
			INT_SCALE(obj.x1 - obj.x0, lWndWidth/nImgWidth), INT_SCALE(obj.y1 - obj.y0, lWndHeight/nImgHeight));
		break;
	case 2:		//ellipse
		if (style.bFill)
		{
			Gdiplus::SolidBrush gPlusBrush(Gdiplus::Color(style.alpha*255/100, style.fill_color.r, style.fill_color.g, style.fill_color.b));

			graphics.FillEllipse(&gPlusBrush, INT_SCALE((obj.x0 + obj.style.thickness/2), lWndWidth/nImgWidth), INT_SCALE((obj.y0 + obj.style.thickness/2), lWndHeight/nImgHeight), 
				INT_SCALE((obj.x1 - obj.x0 - obj.style.thickness), lWndWidth/nImgWidth), INT_SCALE((obj.y1 - obj.y0 - obj.style.thickness), lWndHeight/nImgHeight));
		}

		graphics.DrawEllipse(&gPlusPen, INT_SCALE(obj.x0, lWndWidth/nImgWidth), INT_SCALE(obj.y0, lWndHeight/nImgHeight), 
			INT_SCALE(obj.x1 - obj.x0, lWndWidth/nImgWidth), INT_SCALE(obj.y1 - obj.y0, lWndHeight/nImgHeight));
		break;
	case -1:	//no display
	default:
		//
		break;
	}
}

//// 将传入engine的Region信息写入meta
//if(meta.size()==0)
//{
//	// 没有meta数据时，添加一个空的FrameMetaData
//	HHV::FrameMetaData data;
//	meta.push_back(data);
//}
//
//// 找到Region数量
//string s = m_attributes["NumberOfRegion"]; 
//int iNumberOfRegion = atoi(s.c_str());
//meta[0].attributes["NumberOfRegion"] = m_attributes["NumberOfRegion"];
//
//// 循环写入各个Region的信息
//for(int i=1;i<=iNumberOfRegion;i++)
//{
//	CString strNo;
//	strNo.Format(".%d", i);
//	meta[0].attributes[(const char *)("regionName" + strNo)] = m_attributes[(const char *)("regionName" + strNo)];
//	meta[0].attributes[(const char *)("region-types" + strNo)] = m_attributes[(const char *)("region-types" + strNo)];
//	meta[0].attributes[(const char *)("security-level" + strNo)] = m_attributes[(const char *)("security-level" + strNo)];
//	meta[0].attributes[(const char *)("shape-type" + strNo)] = m_attributes[(const char *)("shape-type" + strNo)];
//	meta[0].attributes[(const char *)("coordinate" + strNo)] = m_attributes[(const char *)("coordinate" + strNo)];
//	meta[0].attributes[(const char *)("object" + strNo)] = m_attributes[(const char *)("object" + strNo)];
//}

int CDVRPlayer::GetFrameMetaDataList(HHV::FrameMetaDataList& metaDataList)
{
	HHV::FrameMetaData fmd1;
	fmd1.attributes["NumberOfRegion"] = "2";
	fmd1.attributes["regionName.1"] = "regionName1";
	fmd1.attributes["region-types.1"] = "Monitoring";
	fmd1.attributes["security-level.1"] = "serious";
	fmd1.attributes["shape-type.1"] = "rectangle";
	fmd1.attributes["coordinate.1"] = "5,5,300,270";
	fmd1.attributes["object.1"] = "Object";
	fmd1.attributes["region.imagesize"] = "352,288";
	fmd1.attributes["regionName.2"] = "regionName2";
	fmd1.attributes["region-types.2"] = "Effective";
	fmd1.attributes["security-level.2"] = "serious";
	fmd1.attributes["shape-type.2"] = "rectangle";
	fmd1.attributes["coordinate.2"] = "0,0,350,280";
	fmd1.attributes["object.2"] = "Human";


	//fmd1.displayData.image_width = 376;
	//fmd1.displayData.image_height = 258;

	//HHV::DisplayObjectMeta dom1;
	//dom1.id = "0001";
	//dom1.obj.type = 0;
	//dom1.obj.style.color.r = 200;
	//dom1.obj.style.color.g = 100;
	//dom1.obj.style.color.b = 0;
	//dom1.obj.style.bFill = true;//GetTickCount() % 10 > 5;
	//dom1.obj.style.thickness = 10;
	//dom1.obj.style.fill_color.r = 0;
	//dom1.obj.style.fill_color.g = 255;
	//dom1.obj.style.fill_color.b = 0;
	//dom1.obj.style.alpha = 50;
	//dom1.obj.x0 = 10;
	//dom1.obj.y0 = 20;
	//dom1.obj.x1 = 110;
	//dom1.obj.y1 = 100;
	//dom1.obj.x2 = 150;
	//dom1.obj.y2 = 30;
	//dom1.obj.x3 = 300;
	//dom1.obj.y3 = 100;

	//dom1.track.color.r = 100;
	//dom1.track.color.g = 200;
	//dom1.track.color.b = 255;
	//dom1.track.thickness = 2;
	//dom1.track.end_style = 2; // 0 no style; 1: arrow solid, 2: arrow line
	//dom1.track.arrow_width = 4;
	//dom1.track.arrow_length = 5;
	//dom1.track.lines.push_back(cvPoint(150, 20));
	//dom1.track.lines.push_back(cvPoint(110, 40));
	//dom1.track.lines.push_back(cvPoint(250, 60));
	//dom1.track.lines.push_back(cvPoint(315, 80));
	//dom1.track.lines.push_back(cvPoint(150, 100));

	//HHV::PolygonM pg;
	//pg.style.color.r = 0;
	//pg.style.color.g = 255;
	//pg.style.color.b = 0;
	//pg.style.alpha = 50;
	//pg.style.bFill = true;
	//pg.style.fill_color.r = 255;
	//pg.style.fill_color.g = 255;
	//pg.style.fill_color.b = 0; 
	//pg.style.thickness = 5;
	//pg.points.push_back(cvPoint(50, 200));
	//pg.points.push_back(cvPoint(200, 200));
	//pg.points.push_back(cvPoint(200, 250));
	//pg.points.push_back(cvPoint(50, 250));

	//HHV::TextMeta txt;
	//txt.color = pg.style.color;
	//txt.size = 30;
	//txt.text = "你好，这是测试用的MetaData！";
	//txt.x = 200;
	//txt.y = 100;

	//fmd1.displayData.disp_obj_list.push_back(dom1);
	//fmd1.displayData.polygon_list.push_back(pg);
	//pg.style.bFill = false;
	//pg.points.clear();
	//pg.points.push_back(cvPoint(250, 200));
	//pg.points.push_back(cvPoint(300, 200));
	//pg.points.push_back(cvPoint(300, 250));
	//pg.points.push_back(cvPoint(50, 250));
	//fmd1.displayData.polygon_list.push_back(pg);

	//fmd1.displayData.text_list.push_back(txt);


	metaDataList.push_back(fmd1);
	return (int)metaDataList.size();
}
void CDVRPlayer::RefreshPlay()
{
	NAME(PlayM4_RefreshPlay)(m_lPort);
	NAME(PlayM4_RefreshPlayEx)(m_lPort, 0);
}
// play / pause / stop
void CDVRPlayer::Play()
{
	if(m_enumState == CDVRPlayer::eState_Play)
	{
		return;
	}
	
	if(m_enumState == CDVRPlayer::eState_Pause)
	{
//		DWORD nPreSpeed = m_nSpeed;

		NAME(PlayM4_Pause)(m_lPort, FALSE);

		m_enumState = CDVRPlayer::eState_Play;

		// when u called this api, the speed is adjust to normal speed, so we must resume it.
//		NAME(PlayM4_Play)(m_lPort, m_ctrlVideoPic.GetSafeHwnd());
//		m_nSpeed = 0;
//		ThrowB(IDM_THROW0);
//		AdjustSpeed(nPreSpeed);
	}
	else if (m_enumState == CDVRPlayer::eState_Stop && m_bStreamType)
	{
		Open();
	}
	else if(m_enumState == CDVRPlayer::eState_Step)
	{
		NAME(PlayM4_Play)(m_lPort, m_hRenderWnd);
		m_nSpeed = 0;
		ThrowB(IDM_THROW0);

		m_enumState = CDVRPlayer::eState_Play;
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
			m_enumState = CDVRPlayer::eState_Play;

			//SetTimer(PLAY_TIMER, 500, NULL);

			NAME(PlayM4_RefreshPlay)(m_lPort);
		}

		//m_bSound = NAME(PlayM4_PlaySound)(m_lPort);	
	}
}

void CDVRPlayer::Pause()
{
	if(m_enumState == CDVRPlayer::eState_Play)
	{
		NAME(PlayM4_Pause)(m_lPort, TRUE);
		m_enumState = CDVRPlayer::eState_Pause;
	}
}

void CDVRPlayer::Stop()
{
	if(m_enumState == CDVRPlayer::eState_Stop)
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
	m_enumState = CDVRPlayer::eState_Stop;
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

	TRACE(_T("hytest: play position = %f!\n"), NAME(PlayM4_GetPlayPos)(m_lPort));

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
			//TRACE(_T("FrameNum is :%d\n",nEndFrame);
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
		m_enumState = CDVRPlayer::eState_Step;
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
	m_enumState = CDVRPlayer::eState_Step;

}

bool CDVRPlayer::GetPictureSize(LONG* plWidth, LONG* plHeight)
{
	return NAME(PlayM4_GetPictureSize)(m_lPort, plWidth, plHeight) == TRUE;
}

CString CDVRPlayer::GetPic(PBYTE pImage, DWORD nBufSize)
{
	CString sFilePath;
	CFile	clsFile;

	DWORD   pImageSize	= 0;
	
	if(m_DVRSettings.m_eCapturePicType == CDVRSettings::eJPEG)
	{
		if( !NAME(PlayM4_GetJPEG)(m_lPort, pImage, nBufSize, &pImageSize) )
		{
			return CString();
		}

		if(m_DVRSettings.m_csPicCapturePath.Compare(_T("")))
		{
			sFilePath.Format(_T("%s\\capture%02d.jpeg"), m_DVRSettings.m_csPicCapturePath, m_npic_jpeg);
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
			return CString();
		}

		if(m_DVRSettings.m_csPicCapturePath.Compare(_T("")))
		{
			sFilePath.Format(_T("%s\\capture%02d.bmp"), m_DVRSettings.m_csPicCapturePath, m_npic_bmp);
		}
		else
		{
			sFilePath.Format(_T("C:\\capture%02d.bmp"), m_npic_bmp);
		}
	}
	
	if(!clsFile.Open(sFilePath,CFile::modeCreate|CFile::modeWrite))
	{
		return CString();
	}

	try							
	{
		clsFile.Write(pImage, pImageSize);
		clsFile.Close();
		CImage m_image;
		CImage m_imgDest;
		HRESULT hr = m_image.Load((LPCTSTR)sFilePath);
		if (S_OK == hr)
		{
			if(DeleteFile((LPCTSTR)sFilePath))
			{
				m_imgDest.Create(352, 288, 24);
				HDC hdc = m_imgDest.GetDC();
				SetStretchBltMode(hdc, COLORONCOLOR);
				m_image.StretchBlt(hdc, 0, 0, 352, 288);
				m_imgDest.Save((LPCTSTR)sFilePath);
				m_imgDest.ReleaseDC();	
			}
		}

		if(m_DVRSettings.m_eCapturePicType == CDVRSettings::eJPEG)
		{
			m_npic_jpeg++;
		}
		else
		{
			m_npic_bmp++;
		}
	}
	catch (CFileException* e) 
	{
		e->ReportError();
		e->Delete();
	}

	return sFilePath;
}


CString CDVRPlayer::Cappic() 
{
	// TODO: Add your control notification handler code here
	PBYTE	pImage		= NULL;
	DWORD   nBufSize	= m_nWidth * m_nHeight * 5;  // 保证足够大即可(不会小于一幅bmp或者jpeg图像大小)
	CString picPath; 

	try
	{
		pImage = new BYTE[nBufSize];
		if(NULL == pImage)
		{
			//throw 0;
			return CString();
		}
		
		picPath = GetPic(pImage, nBufSize);
	}
	catch(...)
	{
		return CString();
	}

	if(pImage != NULL)
	{
		delete []pImage;
		pImage = NULL;
	}
	return picPath;
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
	InitForPlayFile();

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

	// If you want to change the display buffer. Do hear!
	//	NAME(PlayM4_SetDisplayBuf)(m_lPort,50);
	//	NAME(PlayM4_SetDisplayBufAddtionalLen)(m_lPort, 6);

	Play();
	//	PlayM4_SetPlayedTimeEx(m_lPort, 3000000);
	// 	BOOL b = NAME(PlayM4_SetDisplayType)(m_lPort, 3);
	//	PlayM4_SetCurrentFrameNum(m_lPort, 10000);
	//	PlayM4_SetPlayPos(m_lPort, 1.2);
	// 	DWORD dw = PlayM4_GetLastError(m_lPort);
	//::SetWindowText(m_hParentWnd, (LPCTSTR) m_strPlayFileName);
}

// close file
void CDVRPlayer::CloseFile()
{
	Stop();
	NAME(PlayM4_CloseFile)(m_lPort);

	m_bOpen = FALSE;
	m_bFileRefCreated =	FALSE;	
}

// Function: Open the file by stream type and play it
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
	TCHAR szError[50];

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
		_stprintf(szError, _T("Open stream failed(%s)"), MyErrorToString(NAME(PlayM4_GetLastError)(m_lPort)));
		MessageBox(csError);
		delete []pBuf;
		pBuf = NULL;
		throw 0;
	}
	PlayM4_SyncToAudio(m_lPort, FALSE);
#else defined MIX_INPUT	

	if(!NAME(PlayM4_OpenStream)(m_lPort, pBuf, sizeof(stInfo),  6*1000*1024))
	{
		_stprintf(szError, _T("Open stream failed(%s)"), MyErrorToString(NAME(PlayM4_GetLastError)(m_lPort)));
		MessageBox(NULL, szError, _T("Error"), MB_OK);
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
				TRACE(_T("GetExitCode option error!-decodethread\n"));
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
	if (GetPlayState() != CDVRPlayer::eState_Step && GetPlayState() != CDVRPlayer::eState_Pause) 
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
	return NAME(PlayM4_SetDisplayType)(m_lPort, lType) == TRUE;
}
LONG CDVRPlayer::GetDisplayType()
{
	return NAME(PlayM4_GetDisplayType)(m_lPort);
}

bool CDVRPlayer::SetTimerType(DWORD dwTimerType)
{
	return NAME(PlayM4_SetTimerType)(m_lPort, dwTimerType, 0) == TRUE;
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

//Error Information
LPCTSTR CDVRPlayer::MyErrorToString(DWORD error)
{
	switch(error)
	{
	case 0:
		return _T("No error.\0");
	case 1:
		return _T("The parameter that user inputted is invalid.\0");
	case 2:
		return _T("The order of the function to be called is incorrect.\0");
	case 3:
		return _T("Failure when creating system multimedia clock.\0");
	case 4:
		return _T("Failure when decoding video data.\0");
	case 5:
		return _T("Failure when decoding audio data.\0");
	case 6:
		return _T("Failure when allocating memory.\0");
	case 7:
		return _T("File open failed when calling API Hik_PlayM4_OpenFile.\0");
	case 8:
		return _T("Failure when creating thread or event.\0");
	case 9:
		return _T("Failure when creating directdraw object.\0");
	case 10:
		return _T("Failure when creating off-screen surface.\0");
	case 11:
		return _T("The input source buffer has overflowed when calling API Hik_PlayM4_InputData.\0");
	case 12:
		return _T("Failure when creating audio device.\0");
	case 13:
		return _T("Failure when setting audio volume.\0");
	case 14:
		return _T("The function only supports playing a file.\0");
	case 15:
		return _T("The function only supports playing a stream.\0");
	case 16:
		return _T("Neither MMX nor SSE arithmetic is supported by system.\0");
	case 17:
		return _T("Unknown file header.\0");
	case 18:
		return _T("The version of video decoder and video encoder is not compatible.\0");
	case 19:
		return _T("Failure when initializing decoder.\0");
	case 20:
		return _T("The file data is unknown. No I-frame found.\0");
	case 21:
		return _T("Failure when initializing multimedia clock.\0");
	case 22:
		return _T("Failure when blitting overlay.\0");
	case 23:
		return _T("Failure when updating overlay or offscreen surface.\0");
	case 24:
		return _T("Open file error, streamtype is multi.\0");
	case 25:
		return _T("Openfile error, streamtype is video.\0");
	case 26:
		return _T("JPEG compression error when capturing jpeg file.\0");
	case 27:
		return _T("Version of this file not supported when extracting h264 video data.\0");
	case 28:
		return _T("Failure when extracting video data.\0");
	default:
		return _T("Unrecognized error value.\0");
	}
}
