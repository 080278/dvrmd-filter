// SonicIMVPlayerCtrl.cpp : Implementation of CSonicIMVPlayerCtrl
#include "stdafx.h"
#include "SonicIMVPlayerCtrl.h"
#include "OPErrorTypes.h"

// CSonicIMVPlayerCtrl

#define ID_ELAPSED_TIMER (2000)
#define ID_CURSOR_HIDE_TIMER (2001)

LRESULT CSonicIMVPlayerCtrl::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    m_IMVPlayer.SetWindow(m_hWnd);

    #undef SubclassWindow
	HWND hRootWnd = GetAncestor(m_hWnd,GA_ROOT);
	if(::IsWindow(hRootWnd))
		m_msgSniffer.SubclassWindow(hRootWnd);

	if(m_IMVPlayer.State() == PlayerState_Playing)
		SetTimer(ID_ELAPSED_TIMER, 500, NULL);

    return 0;
}

LRESULT CSonicIMVPlayerCtrl::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	m_bFullScreen = VARIANT_FALSE;
    return 0;
}

LRESULT CSonicIMVPlayerCtrl::OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    PAINTSTRUCT ps;
    HDC hdc;

    hdc = BeginPaint(&ps);

    if (m_IMVPlayer.State() != PlayerState_Uninitialized && m_IMVPlayer.State() != PlayerState_Stopped && !m_bDisplayChaning)
    {
        m_IMVPlayer.RepaintVideo();
    }
    else
    {
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(::GetStockObject(BLACK_BRUSH)));
    }

    EndPaint(&ps);

    return 0;
}

LRESULT CSonicIMVPlayerCtrl::OnWindowPosChanging(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
	if(m_bParentChanging)
	{
		WINDOWPOS* pWindowPos = (WINDOWPOS*)lParam;
		if(pWindowPos)
		{
			pWindowPos->flags |= SWP_NOSIZE | SWP_NOMOVE;
			if(m_bFullScreen)
				pWindowPos->flags |= SWP_NOREDRAW;

		}
	}
	 return 0;
}

LRESULT CSonicIMVPlayerCtrl::OnMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	if(!m_bDisplayChaning)
	{
		if(m_IMVPlayer.State() == PlayerState_Paused || m_IMVPlayer.State() == PlayerState_Buffering)
			m_IMVPlayer.RepaintVideo();
	}

	bHandled = FALSE;
	return 0;
}

LRESULT CSonicIMVPlayerCtrl::OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	if(!m_bDisplayChaning)
	{
		RECT rc;
		GetClientRect(&rc);
		m_IMVPlayer.UpdateVideoWindow(&rc);
	}

	return 0;
}

LRESULT CSonicIMVPlayerCtrl::OnEraseBkgnd(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    return 0;
}

void CSonicIMVPlayerCtrl::OnGraphEvent(long eventCode, LONG_PTR param1, LONG_PTR param2)
{
    switch (eventCode)
    {
    case EC_COMPLETE:
    case EC_USERABORT:
		StopInternal(TRUE,TRUE);
        break;
    case EC_ERRORABORT:
        Error(_T("Playback error."));
		
		#if defined(DEBUG) || defined(DEV_RELEASE)
		{
			char debugString[256];
			sprintf_s(debugString,256,"EC_ERRORABORT hr1 = 0x%08x hr2 = 0x%08x\n",param1,param2);
			OutputDebugStringA(debugString);
		}
		#endif

		if(param1 == E_COPP_OUTPUT_PROTECTION_FAILURE)
		{
			// ERROR_GRAPHICS_OPM_VIDEO_OUTPUT_NO_LONGER_EXISTS:
			//The operating system asynchronously destroyed this OPM video output because the operating system's state changed. 
			//This error typically occurs because the monitor PDO associated with this video output was removed,
			//the monitor PDO associated with this video output was stopped, 
			//the video output's session became a non-console session or the video output's desktop became an inactive desktop.

			// For such a case, we simply ignore the opm error and wait display change to re-create opm session.
			if(param2 != ERROR_GRAPHICS_OPM_VIDEO_OUTPUT_NO_LONGER_EXISTS)
			{
				StopInternal(FALSE,TRUE);
				//m_IMVPlayer.CloseSession();
				m_bNeedReInitMVSession = TRUE;
				Fire_HDCPError();
			}
		}
		else
		{
			StopInternal(TRUE,TRUE);
		}

		break;
    }
}

STDMETHODIMP CSonicIMVPlayerCtrl::get_URL(BSTR* pbstrURL)
{
    IMV_TRACE(_T("CSonicIMVPlayerCtrl::get_URL()\n"));

    // make a copy of m_bstrURL pointed to by pstrURL
    *pbstrURL = m_bstrURL.Copy();
    return S_OK;
}

STDMETHODIMP CSonicIMVPlayerCtrl::put_URL(BSTR bstrURL)
{
    IMV_TRACE(_T("CSonicIMVPlayerCtrl::put_URL()\n"));

	m_bNeedReInitMVSession = FALSE;
	HRESULT hr = m_IMVPlayer.Open(bstrURL);
	if(SUCCEEDED(hr))
	{
		put_mute(m_bMute);
		m_bstrURL = bstrURL;
		m_bstrStatus = _T("Open MP4 file succeeded!");
		return S_OK;
	}
	else
	{
		m_bstrURL.Empty();

		if(hr == E_COPP_OUTPUT_PROTECTION_FAILURE)
		{
			m_bstrStatus = _T("HDCP cannot be enabled");
			hr = IMV_FAIL_HDCP;
		}
		else if(hr == E_NO_VALID_KEY)
		{
			m_bstrStatus = _T("There is no license with the file");
			hr = IMV_FAIL_LICENSE;
		}
		else
		{
			m_bstrStatus = _T("This is an invalide MP4 file");
			hr = IMV_FAIL_INVALIDATE_FILE;
		}

		Error(m_bstrStatus);
		return hr;
	}
}

STDMETHODIMP CSonicIMVPlayerCtrl::play(void)
{
    IMV_TRACE(_T("CSonicIMVPlayerCtrl::play()\n"));

	if(m_IMVPlayer.State() == PlayerState_Stopped)
	{
		if(m_bNeedReInitMVSession)
		{
			if(FAILED(m_IMVPlayer.ReInitSession())) 
				return IMV_FAIL_HDCP;

			m_bNeedReInitMVSession = FALSE;
		}

		if(IsWindow())
			SetTimer(ID_ELAPSED_TIMER, 500, NULL);
	}

	return m_IMVPlayer.Play(); 
}

STDMETHODIMP CSonicIMVPlayerCtrl::pause(void)
{
    IMV_TRACE(_T("CSonicIMVPlayerCtrl::pause()\n"));

    return m_IMVPlayer.Pause();
}

STDMETHODIMP CSonicIMVPlayerCtrl::stop(void)
{
    IMV_TRACE(_T("CSonicIMVPlayerCtrl::stop()\n"));

	return StopInternal();
}

HRESULT CSonicIMVPlayerCtrl::StopInternal(BOOL bResetTime /* = TRUE */, BOOL bResetSize /* = FALSE */)
{
	if(m_bFullScreen)
	{
		m_bFullScreen = VARIANT_FALSE;
		if(IsWindow())
		{
			HWND hwndParent;
			m_spInPlaceSite->GetWindow(&hwndParent);
			ModifyStyle(WS_POPUP,WS_CHILD);
			m_bParentChanging = TRUE;
			SetParent(hwndParent);
			m_bParentChanging = FALSE;
		}
	}

	if(IsWindow())
	{
		KillTimer(ID_ELAPSED_TIMER);	
	}

	HRESULT hr = m_IMVPlayer.Stop(bResetTime);

	if(bResetSize)
	{
		RECT rcPos = {0}, rcClip = {0};
		IOleInPlaceObject_SetObjectRects(&rcPos,&rcClip);
	}

	return hr;
}

STDMETHODIMP CSonicIMVPlayerCtrl::get_duration(DOUBLE* pDuration)
{
    IMV_TRACE(_T("CSonicIMVPlayerCtrl::get_duration()\n"));

	CheckPointer(pDuration,E_POINTER);
	*pDuration = 0;
	LONGLONG Duration = 0;
	HRESULT hr = m_IMVPlayer.GetDuration(&Duration);
	CHKHR;
	*pDuration = (double)Duration / UNITS;
	return S_OK;
}

STDMETHODIMP CSonicIMVPlayerCtrl::get_durationString(BSTR* pbstrDuration)
{
    IMV_TRACE(_T("CSonicIMVPlayerCtrl::get_durationString()\n"));

    CheckPointer(pbstrDuration,E_POINTER);

    CComBSTR bstrDuration(L"00:00");
    LONGLONG Duration;
    HRESULT hr = m_IMVPlayer.GetDuration(&Duration);
    if(SUCCEEDED(hr))
    {
        WCHAR wszDuration[9];
        UINT second = Duration / UNITS;
        UINT hour = second / 3600;
        UINT minute = (second - hour*3600) / 60;
        second = second - hour*3600 - minute*60;
        if(hour)
            swprintf_s(wszDuration, 9,TEXT("%.2d:%.2d:%.2d"), hour,minute,second);
        else
            swprintf_s(wszDuration, 9,TEXT("%.2d:%.2d"), minute,second);

        bstrDuration = wszDuration;
    }

    *pbstrDuration = bstrDuration.Detach();

    return hr;
}

STDMETHODIMP CSonicIMVPlayerCtrl::get_currentPosition(DOUBLE* pdCurrentPosition)
{
    IMV_TRACE(_T("CSonicIMVPlayerCtrl::get_currentPosition()\n"));
	 
	CheckPointer(pdCurrentPosition,E_POINTER);
	*pdCurrentPosition = 0;
	LONGLONG CurrentPosition = 0;
	HRESULT hr = m_IMVPlayer.GetCurrentPosition(&CurrentPosition);
	CHKHR;
	*pdCurrentPosition = (double)CurrentPosition / UNITS;
	return S_OK;
}

STDMETHODIMP CSonicIMVPlayerCtrl::get_currentPositionString(BSTR* pbstrCurrentPosition)
{
    IMV_TRACE(_T("CSonicIMVPlayerCtrl::get_currentPositionString()\n"));

    CheckPointer(pbstrCurrentPosition,E_POINTER);

    CComBSTR bstrCurrentPosition(L"00:00");
    LONGLONG CurrentPosition = 0;
    HRESULT hr = m_IMVPlayer.GetCurrentPosition(&CurrentPosition);
    if(SUCCEEDED(hr))
    {
        WCHAR wszCurrentPosition[9];
        UINT second = CurrentPosition / UNITS;
        UINT hour = second / 3600;
        UINT minute = (second - hour*3600) / 60;
        second = second - hour*3600 - minute*60;
        if(hour)
            swprintf_s(wszCurrentPosition, 9,TEXT("%.2d:%.2d:%.2d"), hour,minute,second);
        else
            swprintf_s(wszCurrentPosition, 9,TEXT("%.2d:%.2d"), minute,second);

        bstrCurrentPosition = wszCurrentPosition;
    }

    *pbstrCurrentPosition = bstrCurrentPosition.Detach();

    return hr;
}

STDMETHODIMP CSonicIMVPlayerCtrl::put_currentPosition(DOUBLE dCurrentPosition)
{
    IMV_TRACE(_T("CSonicIMVPlayerCtrl::put_currentPosition()\n"));
	LONGLONG CurrentPosition = (LONGLONG)dCurrentPosition * UNITS;
    return m_IMVPlayer.SetCurrentPosition(CurrentPosition);
}

STDMETHODIMP CSonicIMVPlayerCtrl::fastForward(void)
{
    IMV_TRACE(_T("CSonicIMVPlayerCtrl::fastForward()\n"));
    
	return m_IMVPlayer.SetRate(18.0f);
}

STDMETHODIMP CSonicIMVPlayerCtrl::fastReverse(void)
{
    IMV_TRACE(_T("CSonicIMVPlayerCtrl::fastReverse()\n"));

    return m_IMVPlayer.SetRate(-18.0f);
}

STDMETHODIMP CSonicIMVPlayerCtrl::get_fullScreen(VARIANT_BOOL *pbFullScreen)
{
    IMV_TRACE(_T("CSonicIMVPlayerCtrl::get_fullScreen()\n"));

    CheckPointer(pbFullScreen,E_POINTER);
    *pbFullScreen = m_bFullScreen; 
    return S_OK;
}

STDMETHODIMP CSonicIMVPlayerCtrl::put_fullScreen(VARIANT_BOOL bFullScreen)
{
    IMV_TRACE(_T("CSonicIMVPlayerCtrl::put_fullScreen()\n"));

	if(!IsWindow())
	{
		m_bFullScreen = VARIANT_FALSE;
		return S_OK;
	}

    if(m_bFullScreen == bFullScreen)
        return S_OK;

    m_bFullScreen = bFullScreen;
	
    if(m_bFullScreen)
    {
		HMONITOR hMonitor = MonitorFromWindow(m_hWnd, MONITOR_DEFAULTTONEAREST);
		MONITORINFOEX mi;
		mi.cbSize = sizeof(mi);
		GetMonitorInfo(hMonitor, &mi);

		//SetParent does not modify the WS_CHILD or WS_POPUP window styles of the window whose parent is being changed. 
		//Therefore, if hWndNewParent is NULL, you should also clear the WS_CHILD bit and set the WS_POPUP style after calling SetParent.
		m_bParentChanging = TRUE;
        SetParent(NULL); 
		m_bParentChanging = FALSE;
		ModifyStyle(WS_CHILD,WS_POPUP);
		SetWindowRgn(NULL, TRUE);
		SetWindowPos(
			HWND_TOPMOST, 
			mi.rcMonitor.left, 
			mi.rcMonitor.top, 
			mi.rcMonitor.right-mi.rcMonitor.left, 
			mi.rcMonitor.bottom-mi.rcMonitor.top, 
			SWP_SHOWWINDOW | SWP_NOREDRAW);
		TurnOnCursorHiding();
    }
    else
    {
        // get location in the parent window,
        // as well as some information about the parent
        //
        OLEINPLACEFRAMEINFO frameInfo;
        RECT rcPos, rcClip;
        CComPtr<IOleInPlaceFrame> spInPlaceFrame;
        CComPtr<IOleInPlaceUIWindow> spInPlaceUIWindow;
        frameInfo.cb = sizeof(OLEINPLACEFRAMEINFO);
        HWND hwndParent;
        if (m_spInPlaceSite->GetWindow(&hwndParent) == S_OK)
        {
            m_spInPlaceSite->GetWindowContext(&spInPlaceFrame,
                &spInPlaceUIWindow, &rcPos, &rcClip, &frameInfo);

			//Conversely, if hWndNewParent is not NULL and the window was previously a child of the desktop, 
			//you should clear the WS_POPUP style and set the WS_CHILD style before calling SetParent.
			ModifyStyle(WS_POPUP,WS_CHILD);

			m_bParentChanging = TRUE;
            SetParent(hwndParent);
			m_bParentChanging = FALSE;
           
            SetWindowPos(
                0, 
                rcPos.left, 
                rcPos.top, 
                rcPos.right - rcPos.left, 
                rcPos.bottom - rcPos.top, 
                SWP_SHOWWINDOW | SWP_NOREDRAW);
        }
		TurnOffCursorHiding();
    }

    return S_OK;
}

STDMETHODIMP CSonicIMVPlayerCtrl::get_isAvailable(BSTR bstrItem, VARIANT_BOOL* pIsAvailable)
{
    IMV_TRACE(_T("CSonicIMVPlayerCtrl::get_isAvailable()\n"));

    CheckPointer(bstrItem,E_POINTER);
    CheckPointer(pIsAvailable,E_POINTER);
    CComBSTR bstrTemp(bstrItem);
    bstrTemp.ToLower();
    if(bstrTemp == L"currentposition")
	{
		*pIsAvailable = m_IMVPlayer.CanSeek() ? VARIANT_TRUE : VARIANT_FALSE;
	}
    else if(bstrTemp == L"pause")
    {
		*pIsAvailable = m_IMVPlayer.CanPause() ? VARIANT_TRUE : VARIANT_FALSE;
    }
    else if(bstrTemp == L"play")
    {
		*pIsAvailable = m_IMVPlayer.CanPlay() ? VARIANT_TRUE : VARIANT_FALSE;
    }
    else if(bstrTemp == L"stop")
    {
		*pIsAvailable = m_IMVPlayer.CanStop() ? VARIANT_TRUE : VARIANT_FALSE;
    }
    else if(bstrTemp == L"fastforward")
    {
		*pIsAvailable = m_IMVPlayer.CanFF() ? VARIANT_TRUE : VARIANT_FALSE;
    }
    else if(bstrTemp == L"fastreverse")
    {
		*pIsAvailable = m_IMVPlayer.CanFR() ? VARIANT_TRUE : VARIANT_FALSE;
    }
    else
    {
        *pIsAvailable = VARIANT_FALSE;
    }

    return S_OK;
}

STDMETHODIMP CSonicIMVPlayerCtrl::get_imageSourceHeight(LONG* pHeight)
{
    IMV_TRACE(_T("CSonicIMVPlayerCtrl::get_imageSourceHeight()\n"));

    return m_IMVPlayer.GetVideoImageHeight(pHeight);
}

STDMETHODIMP CSonicIMVPlayerCtrl::get_imageSourceWidth(LONG* pWidth)
{
    IMV_TRACE(_T("CSonicIMVPlayerCtrl::get_imageSourceWidth()\n"));

    return m_IMVPlayer.GetVideoImageWidth(pWidth);
}

STDMETHODIMP CSonicIMVPlayerCtrl::get_mute(VARIANT_BOOL* pfMute)
{
    IMV_TRACE(_T("CSonicIMVPlayerCtrl::get_mute()\n"));

    CheckPointer(pfMute,E_POINTER);
    *pfMute = m_bMute;
    return S_OK;
}

STDMETHODIMP CSonicIMVPlayerCtrl::put_mute(VARIANT_BOOL fMute)
{
    IMV_TRACE(_T("CSonicIMVPlayerCtrl::put_mute()\n"));

    m_bMute = fMute;
    if(fMute)
        m_IMVPlayer.SetVolume(0);
    else
        m_IMVPlayer.SetVolume(m_lVolume);

    return S_OK;
}

STDMETHODIMP CSonicIMVPlayerCtrl::get_volume(LONG* plVolume)
{
    IMV_TRACE(_T("CSonicIMVPlayerCtrl::get_volume()\n"));

    CheckPointer(plVolume,E_POINTER);

    *plVolume = m_lVolume;
    return S_OK;
}

STDMETHODIMP CSonicIMVPlayerCtrl::put_volume(LONG lVolume)
{
    IMV_TRACE(_T("CSonicIMVPlayerCtrl::put_volume()\n"));

    if(lVolume < 0 && lVolume > 100)
        return E_INVALIDARG;

    m_lVolume = lVolume;
    m_IMVPlayer.SetVolume(lVolume);
    return S_OK;
}

STDMETHODIMP CSonicIMVPlayerCtrl::get_playState(LONG* plState)
{
    IMV_TRACE(_T("CSonicIMVPlayerCtrl::get_playState()\n"));

    CheckPointer(plState,E_POINTER);
    *plState = m_IMVPlayer.State();
    return S_OK;
}

// The status property retrieves a value indicating the status of Player.
// This property is a read-only String.
STDMETHODIMP CSonicIMVPlayerCtrl::get_status(BSTR* pbstrStatus)
{
    IMV_TRACE(_T("CSonicIMVPlayerCtrl::get_status()\n"));

    CheckPointer(pbstrStatus,E_POINTER);

    // make a copy of m_bstrStatus pointed to by pstrStatus
    *pbstrStatus = m_bstrStatus.Copy();
    return S_OK;
}

STDMETHODIMP CSonicIMVPlayerCtrl::get_versionInfo(BSTR* pbstrVersionInfo)
{
    IMV_TRACE(_T("CSonicIMVPlayerCtrl::get_versionInfo()\n"));

    CheckPointer(pbstrVersionInfo,E_POINTER);

    // make a copy of m_bstrStatus pointed to by pstrVersion
    *pbstrVersionInfo = m_bStrVersion.Copy();
    return S_OK;
}

STDMETHODIMP CSonicIMVPlayerCtrl::close(void)
{
    IMV_TRACE(_T("CSonicIMVPlayerCtrl::close()\n"));

    m_IMVPlayer.TearDownGraph();
	m_bNeedReInitMVSession = FALSE;
	m_bstrURL.Empty();

    return S_OK;
}

STDMETHODIMP CSonicIMVPlayerCtrl::get_uiMode(BSTR* pbstrMode)
{
    IMV_TRACE(_T("CSonicIMVPlayerCtrl::get_uiMode()\n"));

    CheckPointer(pbstrMode,E_POINTER);

    // make a copy of m_bstruiMode pointed to by pstruiMode
    *pbstrMode = m_bstruiMode.Copy();
    return S_OK;
}

STDMETHODIMP CSonicIMVPlayerCtrl::put_uiMode(BSTR bstrMode)
{
    IMV_TRACE(_T("CSonicIMVPlayerCtrl::put_uiMode()\n"));

    m_bstruiMode = bstrMode;
    return S_OK;
}

STDMETHODIMP CSonicIMVPlayerCtrl::get_controls(ISonicIMVControls **ppControl)
{
    IMV_TRACE(_T("CSonicIMVPlayerCtrl::get_controls()\n"));
	return _InternalQueryInterface(IID_ISonicIMVControls,(void**)ppControl);
}

STDMETHODIMP CSonicIMVPlayerCtrl::get_settings(ISonicIMVSettings** ppSettings)
{
    IMV_TRACE(_T("CSonicIMVPlayerCtrl::get_settings()\n"));
	return _InternalQueryInterface(IID_ISonicIMVSettings,(void**)ppSettings);
}

STDMETHODIMP CSonicIMVPlayerCtrl::get_currentMedia(ISonicIMVMedia** ppMedia)
{
    IMV_TRACE(_T("CSonicIMVPlayerCtrl::get_currentMedia()\n"));
    return _InternalQueryInterface(IID_ISonicIMVMedia,(void**)ppMedia);
}

LRESULT CSonicIMVPlayerCtrl::OnTimer(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	switch (wParam)
	{
	case ID_CURSOR_HIDE_TIMER:
		::ShowCursor(FALSE);
		KillCursorHideTimer();
		break;
	case ID_ELAPSED_TIMER:
		m_IMVPlayer.CheckBufferring();
		break;
	}

	return 0;
}

LRESULT CSonicIMVPlayerCtrl::OnMouseMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	if(m_bFullScreen)
	{
		TurnOffCursorHiding();
		TurnOnCursorHiding();
	}
	return 0;
}

LRESULT CSonicIMVPlayerCtrl::OnLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	if(m_bFullScreen)
	{
		TurnOffCursorHiding();
		TurnOnCursorHiding();
	}
	return 0;
}

LRESULT CSonicIMVPlayerCtrl::OnRButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	if(m_bFullScreen)
	{
		TurnOffCursorHiding();
		TurnOnCursorHiding();
	}
	return 0;
}

void CSonicIMVPlayerCtrl::KillCursorHideTimer()
{
	if (m_idCursorHideTimer)
	{
		// Stop cursor hiding timer.
		KillTimer(ID_CURSOR_HIDE_TIMER);
		m_idCursorHideTimer = 0;
	}
}

void CSonicIMVPlayerCtrl::TurnOnCursorHiding()
{
	if (!m_idCursorHideTimer)
		m_idCursorHideTimer = SetTimer(ID_CURSOR_HIDE_TIMER,2000,(TIMERPROC) NULL);
}

void CSonicIMVPlayerCtrl::TurnOffCursorHiding()
{
	KillCursorHideTimer();

	// Make sure the cursor showed up.
	CURSORINFO info;
	ZeroMemory(&info, sizeof(CURSORINFO));
	info.cbSize = sizeof(CURSORINFO);
	GetCursorInfo(&info);
	if (0 == info.flags)
		::ShowCursor(TRUE);
}
#include "assert.h"
STDMETHODIMP CSonicIMVPlayerCtrl::OpenFile(BSTR bstrMediaFile)
{
	//assert(false);
	return m_IMVPlayer.Open(bstrMediaFile);

}
STDMETHODIMP CSonicIMVPlayerCtrl::Login(BSTR bstrUsername, BSTR bstrPassword, BSTR bstrIP, LONG lPort)
{
	return m_IMVPlayer.Login(bstrUsername, bstrPassword, bstrIP, lPort);

}
STDMETHODIMP CSonicIMVPlayerCtrl::Logout()
{
	return m_IMVPlayer.Logout();

}
STDMETHODIMP CSonicIMVPlayerCtrl::SetMediaServer(BSTR bstrMediaServerIP, LONG lPort)
{
	return m_IMVPlayer.SetMediaServer(bstrMediaServerIP, lPort);

}
STDMETHODIMP CSonicIMVPlayerCtrl::GetMediaServer(BSTR* bstrMediaServerIP, LONG* lPort)
{
	return m_IMVPlayer.GetMediaServer(bstrMediaServerIP, lPort);

}
STDMETHODIMP CSonicIMVPlayerCtrl::StartMonitor(LONG lWndNum)
{
	return m_IMVPlayer.StartMonitor(lWndNum);

}
STDMETHODIMP CSonicIMVPlayerCtrl::StopMonitor()
{
	return m_IMVPlayer.StopMonitor();

}
STDMETHODIMP CSonicIMVPlayerCtrl::CapPic(BSTR* pbstrCapFolder)
{
	return m_IMVPlayer.CapPic(pbstrCapFolder);

}
STDMETHODIMP CSonicIMVPlayerCtrl::GetCapturePath(BSTR* bstrCapFolder)
{
	return m_IMVPlayer.GetCapturePath(bstrCapFolder);

}
STDMETHODIMP CSonicIMVPlayerCtrl::SetCapturePath(BSTR bstrCapFolder)
{
	return m_IMVPlayer.SetCapturePath(bstrCapFolder);

}
STDMETHODIMP CSonicIMVPlayerCtrl::ShowMetaData(VARIANT_BOOL bShow)
{
	return m_IMVPlayer.ShowMetaData(bShow);

}