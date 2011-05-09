// SonicIMVPlayerCtrl.h : Declaration of the CSonicIMVPlayerCtrl
#pragma once
#include "resource.h"       // main symbols
#include <atlctl.h>
#include "SonicIMVPlayer.h"
#include "_ISonicIMVPlayerCtrlEvents_CP.h"
#include "IMVDShowPlayer.h"
#include "SonicIMVPlayerIds.h"

// CSonicIMVPlayerCtrl
class ATL_NO_VTABLE CSonicIMVPlayerCtrl :
    public CComObjectRootEx<CComSingleThreadModel>,
    public CComCoClass<CSonicIMVPlayerCtrl, &CLSID_SonicIMVPlayerCtrl>,
    public CComControl<CSonicIMVPlayerCtrl>,
    public IDispatchImpl<ISonicIMVPlayer, &IID_ISonicIMVPlayer, &LIBID_SonicIMVPlayerLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
    public IDispatchImpl<ISonicIMVControls, &IID_ISonicIMVControls, &LIBID_SonicIMVPlayerLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
    public IDispatchImpl<ISonicIMVSettings, &IID_ISonicIMVSettings, &LIBID_SonicIMVPlayerLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
    public IDispatchImpl<ISonicIMVMedia, &IID_ISonicIMVMedia, &LIBID_SonicIMVPlayerLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
    public IProvideClassInfo2Impl<&CLSID_SonicIMVPlayerCtrl, &__uuidof(_ISonicIMVPlayerCtrlEvents), &LIBID_SonicIMVPlayerLib>,
    public IPersistStreamInitImpl<CSonicIMVPlayerCtrl>,
    public IPersistStorageImpl<CSonicIMVPlayerCtrl>,
    public IPersistPropertyBagImpl<CSonicIMVPlayerCtrl>,
    public IQuickActivateImpl<CSonicIMVPlayerCtrl>,
    public IOleControlImpl<CSonicIMVPlayerCtrl>,
    public IOleObjectImpl<CSonicIMVPlayerCtrl>,
    public IObjectSafetyImpl<CSonicIMVPlayerCtrl, INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
    public IOleInPlaceActiveObjectImpl<CSonicIMVPlayerCtrl>,
    public IViewObjectExImpl<CSonicIMVPlayerCtrl>,
    public IOleInPlaceObjectWindowlessImpl<CSonicIMVPlayerCtrl>,
    public IDataObjectImpl<CSonicIMVPlayerCtrl>,
    public ISupportErrorInfo,
    public IConnectionPointContainerImpl<CSonicIMVPlayerCtrl>,
    public CProxy_ISonicIMVPlayerCtrlEvents<CSonicIMVPlayerCtrl>,	
    public ISpecifyPropertyPagesImpl<CSonicIMVPlayerCtrl>,
    public IGraphEventCallback
{
public:

    CSonicIMVPlayerCtrl():m_msgSniffer(this, 1)
    {
        m_bParentChanging = FALSE;
        m_bFullScreen = VARIANT_FALSE;
        m_bMute = VARIANT_FALSE;
        m_lVolume = 50;
        m_bStrVersion = _T("1.0.0.0082");
        m_idCursorHideTimer = 0;
		m_bDisplayChaning = FALSE;
		m_bNeedReInitMVSession = FALSE;
    }

    DECLARE_WND_CLASS_EX(_T("SonicIMVPlayerCtrl"), CS_DBLCLKS|CS_OWNDC, COLOR_WINDOW)

	static LPCTSTR GetWndCaption() 
	{
		return _T("EVRVideo");
    }

    static DWORD GetWndExStyle(DWORD dwExStyle)
    {
        return WS_EX_TOOLWINDOW;
    }

	STDMETHOD(OnWindowMessage)(UINT msg, WPARAM wParam, LPARAM lParam, LRESULT *plResult)
	{
// 		CHAR debugString[MAX_PATH];
// 		sprintf_s(debugString,256,"IOleInPlaceObjectWindowless::OnWindowMessage  : msg=%02x \n",msg);
// 		OutputDebugStringA(debugString); 
		return S_FALSE;
	}

	inline HRESULT IOleObject_SetClientSite(IOleClientSite *pClientSite)
	{
		HRESULT hr = CComControlBase::IOleObject_SetClientSite(pClientSite);
		if(FAILED(hr))
			return hr;

		if (m_spClientSite == NULL)
			return S_OK;

		if (!m_bNegotiatedWnd)
		{
			if (!m_bWindowOnly)
				// Try for windowless site
				hr = m_spClientSite->QueryInterface(__uuidof(IOleInPlaceSiteWindowless), (void **)&m_spInPlaceSite);

			if (m_spInPlaceSite)
			{
				m_bInPlaceSiteEx = TRUE;
				// CanWindowlessActivate returns S_OK or S_FALSE
				if ( m_spInPlaceSite->CanWindowlessActivate() == S_OK )
				{
					m_bWndLess = TRUE;
					m_bWasOnceWindowless = TRUE;
				}
				else
				{
					m_bWndLess = FALSE;
				}
			}
			else
			{
				m_spClientSite->QueryInterface(__uuidof(IOleInPlaceSiteEx), (void **)&m_spInPlaceSite);
				if (m_spInPlaceSite)
					m_bInPlaceSiteEx = TRUE;
				else
					hr = m_spClientSite->QueryInterface(__uuidof(IOleInPlaceSite), (void **)&m_spInPlaceSite);
			}
		}

		ATLASSUME(m_spInPlaceSite);
		if (!m_spInPlaceSite)
			return E_FAIL;

		m_bNegotiatedWnd = TRUE;

		HWND hwndParent;
		if (m_spInPlaceSite->GetWindow(&hwndParent) == S_OK)
		{
			RECT rcPos = {0, 0, 0, 0};
			HWND h = CreateControlWindow(hwndParent, rcPos);
			ATLASSERT(h != NULL);	// will assert if creation failed
			ATLASSERT(h == m_hWndCD);
			if(h == NULL)
				return E_FAIL;
		}

		return S_OK;
	}

	inline HRESULT IOleInPlaceObject_InPlaceDeactivate(void)
	{
		CComPtr<IOleInPlaceObject> pIPO;
		ControlQueryInterface(__uuidof(IOleInPlaceObject), (void**)&pIPO);
		ATLENSURE(pIPO != NULL);

		if (!m_bInPlaceActive)
			return S_OK;
		pIPO->UIDeactivate();

		m_bInPlaceActive = FALSE;

		if (m_spInPlaceSite)
			m_spInPlaceSite->OnInPlaceDeactivate();

		return S_OK;
	}

	inline HRESULT InPlaceActivate(LONG iVerb, const RECT* /*prcPosRect*/)
	{
		HRESULT hr;

		if (!m_spInPlaceSite)
			return E_FAIL;

		if (!m_bInPlaceActive)
		{
			BOOL bNoRedraw = FALSE;
			if (m_bWndLess)
				m_spInPlaceSite->OnInPlaceActivateEx(&bNoRedraw, ACTIVATE_WINDOWLESS);
			else
			{
				if (m_bInPlaceSiteEx)
					m_spInPlaceSite->OnInPlaceActivateEx(&bNoRedraw, 0);
				else
				{
					hr = m_spInPlaceSite->CanInPlaceActivate();
					// CanInPlaceActivate returns S_FALSE or S_OK
					if (FAILED(hr))
						return hr;
					if ( hr != S_OK )
					{
						// CanInPlaceActivate returned S_FALSE.
						return( E_FAIL );
					}
					m_spInPlaceSite->OnInPlaceActivate();
				}
			}
			m_bInPlaceActive = TRUE;
		}

		m_spClientSite->ShowObject();

		return S_OK;
	}

	inline HRESULT IOleInPlaceObject_SetObjectRects(LPCRECT prcPos,LPCRECT prcClip)
	{
		if(m_bFullScreen)
			return S_OK;

		//workaround for CNMM-335: Playback window is a little large over below the write line 
		if(m_IMVPlayer.State() == PlayerState_Uninitialized && !IsRectEmpty(prcPos))
			return S_OK;

		return CComControlBase::IOleInPlaceObject_SetObjectRects(prcPos, prcClip);
	}

    DECLARE_OLEMISC_STATUS(OLEMISC_RECOMPOSEONRESIZE |
    OLEMISC_CANTLINKINSIDE |
    OLEMISC_INSIDEOUT |
    OLEMISC_ACTIVATEWHENVISIBLE |
    OLEMISC_SETCLIENTSITEFIRST
    )

    DECLARE_REGISTRY_RESOURCEID(IDR_SONICIMVPLAYERCTRL)

    BEGIN_COM_MAP(CSonicIMVPlayerCtrl)
        COM_INTERFACE_ENTRY(ISonicIMVPlayer)
        COM_INTERFACE_ENTRY(ISonicIMVControls)
        COM_INTERFACE_ENTRY(ISonicIMVSettings)
        COM_INTERFACE_ENTRY(ISonicIMVMedia)
        COM_INTERFACE_ENTRY2(IDispatch, ISonicIMVPlayer)
        COM_INTERFACE_ENTRY(IViewObjectEx)
        COM_INTERFACE_ENTRY(IViewObject2)
        COM_INTERFACE_ENTRY(IViewObject)
        COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
        COM_INTERFACE_ENTRY(IOleInPlaceObject)
        COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
        COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
        COM_INTERFACE_ENTRY(IOleControl)
        COM_INTERFACE_ENTRY(IOleObject)
        COM_INTERFACE_ENTRY(IObjectSafety)
        COM_INTERFACE_ENTRY(IPersistStreamInit)
        COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
        COM_INTERFACE_ENTRY(ISupportErrorInfo)
        COM_INTERFACE_ENTRY(IConnectionPointContainer)
        COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
        COM_INTERFACE_ENTRY(IQuickActivate)
        COM_INTERFACE_ENTRY(IPersistStorage)
        COM_INTERFACE_ENTRY(IPersistPropertyBag)
        COM_INTERFACE_ENTRY(IDataObject)
        COM_INTERFACE_ENTRY(IProvideClassInfo)
        COM_INTERFACE_ENTRY(IProvideClassInfo2)
    END_COM_MAP()

    BEGIN_PROP_MAP(CSonicIMVPlayerCtrl)
		// Example entries
		// PROP_ENTRY("Property Description", dispid, clsid)
		// PROP_PAGE(CLSID_StockColorPage)
		PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
		PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
		PROP_PAGE(CLSID_SonicIMVPlayerProp)
		PROP_ENTRY_EX("URL", DISPID_IMVPLAYER_URL, CLSID_NULL, IID_ISonicIMVPlayer)
		PROP_ENTRY_EX("uiMode", DISPID_IMVPLAYER_UIMODE, CLSID_NULL, IID_ISonicIMVPlayer)
		PROP_ENTRY_EX("mute", DISPID_IMVSETTINGS_MUTE, CLSID_NULL, IID_ISonicIMVSettings)
    END_PROP_MAP()

    BEGIN_CONNECTION_POINT_MAP(CSonicIMVPlayerCtrl)
        CONNECTION_POINT_ENTRY(__uuidof(_ISonicIMVPlayerCtrlEvents))
    END_CONNECTION_POINT_MAP()

    BEGIN_MSG_MAP(CSonicIMVPlayerCtrl)
        MESSAGE_HANDLER(WM_CREATE, OnCreate)
        MESSAGE_HANDLER(WM_PAINT, OnPaint)
		MESSAGE_HANDLER(WM_WINDOWPOSCHANGING , OnWindowPosChanging)
        MESSAGE_HANDLER(WM_SIZE , OnSize)
        MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
        MESSAGE_HANDLER(WM_GRAPH_EVENT, GraphEventNotify)
        MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
        MESSAGE_HANDLER(WM_KEYDOWN, OnKeyDown)
        MESSAGE_HANDLER(WM_CHAR, OnChar)
        MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDblClk)
		MESSAGE_HANDLER(WM_TIMER, OnTimer)
		MESSAGE_HANDLER(WM_LBUTTONDOWN,OnLButtonDown)
		MESSAGE_HANDLER(WM_RBUTTONDOWN,OnRButtonDown)
		MESSAGE_HANDLER(WM_MOUSEMOVE,OnMouseMove)
		
		// Declare an alternate message map, 
		// identified by '1' that handle the message of our root parent
		ALT_MSG_MAP(1)
		MESSAGE_HANDLER(WM_POWERBROADCAST,OnPowerBroadcast)
		MESSAGE_HANDLER(WM_DISPLAYCHANGE, OnDisplayChange)
		MESSAGE_HANDLER(WM_MOVE, OnMove)
    END_MSG_MAP()
    // Handler prototypes:
    //  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    //  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
    //  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
    LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnWindowPosChanged(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/);
	LRESULT OnWindowPosChanging(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/);
    LRESULT OnEraseBkgnd(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnTimer(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled);
	LRESULT OnMouseMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnRButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	
    LRESULT GraphEventNotify(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        m_IMVPlayer.HandleGraphEvent((IGraphEventCallback*)this);
        return 0;
    }

    LRESULT OnKeyDown(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
        short nKeyCode = (short)wParam;
		// A bit field with the least significant bits corresponding to the SHIFT key (bit 0), 
		// the CTRL key (bit 1), and the ALT key (bit 2). 
        short nShiftState = ((GetKeyState(VK_SHIFT)&0x8000) >> 15) |
			                ((GetKeyState(VK_CONTROL)&0x8000) >> 14) |
							((GetKeyState(VK_MENU)&0x8000) >> 13);

        Fire_KeyDown(nKeyCode, nShiftState);
        return 0;
    }

    LRESULT OnChar(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
        short nKeyAscii = (short)wParam;
		
		// workaroud: translate Ctrl+p to p
		if(wParam == 16)
			nKeyAscii = 'p';

        Fire_KeyPress(nKeyAscii);
        return 0;
    }

    LRESULT OnLButtonDblClk(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
    {
		//nButton is a bit field with bits corresponding to
		//the left button (bit 0),right button (bit 1), and middle button (bit 2). 
		//These bits correspond to the values 1, 2, and 4, respectively. 
		//Only one of the bits is set, indicating the button that caused the event.
		short nButton = 1;

		//nShiftState is a bit field with the least significant bits corresponding to 
		//the SHIFT key (bit 0), the CTRL key (bit 1), and the ALT key (bit 2). 
		//These bits correspond to the values 1, 2, and 4, respectively. 
		//The shift argument indicates the state of these keys. 
		//Some, all, or none of the bits can be set, indicating that some, all, or none of the keys are pressed.
		short nShiftState = ((GetKeyState(VK_SHIFT)&0x8000) >> 15) |
			((GetKeyState(VK_CONTROL)&0x8000) >> 14) |
			((GetKeyState(VK_MENU)&0x8000) >> 13);

		//The x coordinate of the mouse pointer relative to the upper left-hand corner of the control.
		long fX = GET_X_LPARAM(lParam);
		//The y coordinate of the mouse pointer relative to the upper left-hand corner of the control.
		long fY = GET_X_LPARAM(lParam);
        Fire_DoubleClick(nButton,nShiftState,fX,fY);
        return 0;
    }

	LRESULT OnDisplayChange(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		if(m_bDisplayChaning)
		{
			bHandled = TRUE;
			return 1;
		}

		if(m_IMVPlayer.State() != PlayerState_Uninitialized)
		{
			if(m_bFullScreen)
			{
				HMONITOR hMonitor = MonitorFromWindow(m_hWnd, MONITOR_DEFAULTTONEAREST);
				MONITORINFOEX mi;
				mi.cbSize = sizeof(mi);
				GetMonitorInfo(hMonitor, &mi);
				SetWindowPos(
					HWND_TOPMOST, 
					mi.rcMonitor.left, 
					mi.rcMonitor.top, 
					mi.rcMonitor.right-mi.rcMonitor.left, 
					mi.rcMonitor.bottom-mi.rcMonitor.top, 
					SWP_SHOWWINDOW | SWP_NOREDRAW);
			}

			m_bDisplayChaning = TRUE;
			m_bNeedReInitMVSession = FAILED(m_IMVPlayer.HandleDeviceChanged());
			m_bDisplayChaning = FALSE;
			if(m_bNeedReInitMVSession)
			{				
				RECT rcPos = {0}, rcClip = {0};
				IOleInPlaceObject_SetObjectRects(&rcPos,&rcClip);
				Fire_HDCPError();
			}
		}
		
		bHandled = FALSE;
		return 1;
	}

	LRESULT OnPowerBroadcast(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
	{
		if(m_IMVPlayer.State() != PlayerState_Uninitialized)
		{
			if(wParam == PBT_APMSUSPEND)
			{
				StopInternal(FALSE,TRUE);
				m_IMVPlayer.CloseSession();
				m_bNeedReInitMVSession = TRUE;
			}
		}

		bHandled = FALSE;
		return 1;
	}

    void OnGraphEvent(long eventCode, LONG_PTR param1, LONG_PTR param2);

    // ISupportsErrorInfo
    STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
    {
        static const IID* arr[] =
        {
            &IID_ISonicIMVPlayer,
        };

        for (int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
        {
            if (InlineIsEqualGUID(*arr[i], riid))
                return S_OK;
        }
        return S_FALSE;
    }

    // IViewObjectEx
    DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

public:
    HRESULT OnDraw(ATL_DRAWINFO& di)
    {
		RECT& rc = *(RECT*)di.prcBounds;
		HDC hdc  = di.hdcDraw;

		FillRect(hdc, &rc, (HBRUSH)(::GetStockObject(BLACK_BRUSH)));

		return S_OK;
    }

    DECLARE_PROTECT_FINAL_CONSTRUCT()

    HRESULT FinalConstruct()
    {
#ifdef ANTI_DEBUG	
		if(IsDebuggerPresent())
		{
			const char *pMsg = "Debugger detected. Debugging RoxioNow is not allowed. Exiting...";
			::MessageBoxA(NULL, pMsg, "Error",MB_OK | MB_ICONSTOP);
			ExitProcess(-1);
		}
#endif //ANTI_DEBUG

        return S_OK;
    }

    void FinalRelease()
    {
    }

private:
    CIMVDShowPlayer m_IMVPlayer;
    CComBSTR m_bstrURL;
    CComBSTR m_bstruiMode;
    CComBSTR m_bstrStatus;
    CComBSTR m_bStrVersion; // "X.0.0.YYYY": X represents the major version number and YYYY represents the build number.
    BOOL m_bParentChanging;
	VARIANT_BOOL m_bFullScreen;
    VARIANT_BOOL m_bMute;
    LONG m_lVolume;
	CContainedWindow m_msgSniffer;
	BOOL m_bDisplayChaning;
	BOOL m_bNeedReInitMVSession;
	UINT_PTR m_idCursorHideTimer;	
	void KillCursorHideTimer();
	void TurnOnCursorHiding();
	void TurnOffCursorHiding();
	HRESULT StopInternal(BOOL bResetTime = TRUE, BOOL bResetSize = FALSE);

public:
	//ISonicIMVPlayer
    STDMETHOD(get_URL)(BSTR* pbstrURL);
    STDMETHOD(put_URL)(BSTR bstrURL);
    STDMETHOD(get_fullScreen)(VARIANT_BOOL *pbFullScreen);
    STDMETHOD(put_fullScreen)(VARIANT_BOOL bFullScreen);
    STDMETHOD(get_uiMode)(BSTR* pbstrMode);
    STDMETHOD(put_uiMode)(BSTR bstrMode);
    STDMETHOD(get_status)(BSTR* pbstrStatus);
    STDMETHOD(get_versionInfo)(BSTR* pbstrVersionInfo);
    STDMETHOD(get_playState)(LONG* plState);
    STDMETHOD(close)(void);
    STDMETHOD(get_controls)(ISonicIMVControls **ppControl);
    STDMETHOD(get_settings)(ISonicIMVSettings** ppSettings);
    STDMETHOD(get_currentMedia)(ISonicIMVMedia** ppMedia);

	//ISonicIMVControls
    STDMETHOD(get_isAvailable)(BSTR bstrItem, VARIANT_BOOL* pIsAvailable);
    STDMETHOD(play)(void);
    STDMETHOD(pause)(void);
    STDMETHOD(stop)(void);
    STDMETHOD(fastForward)(void);
    STDMETHOD(fastReverse)(void);
    STDMETHOD(get_currentPosition)(DOUBLE* pdCurrentPosition);
    STDMETHOD(put_currentPosition)(DOUBLE dCurrentPosition);
    STDMETHOD(get_currentPositionString)(BSTR* pbstrCurrentPosition);

	//ISonicIMVSettings
    STDMETHOD(get_mute)(VARIANT_BOOL* pfMute);
    STDMETHOD(put_mute)(VARIANT_BOOL fMute);
    STDMETHOD(get_volume)(LONG* plVolume);
    STDMETHOD(put_volume)(LONG lVolume);

	//ISonicIMVMedia
    STDMETHOD(get_imageSourceHeight)(LONG* pHeight);
    STDMETHOD(get_imageSourceWidth)(LONG* pWidth);
    STDMETHOD(get_duration)(DOUBLE* pDuration);
    STDMETHOD(get_durationString)(BSTR* pbstrDuration);

	//DVR Interfaces
	STDMETHOD(OpenFile)(BSTR bstrMediaFile);
	STDMETHOD(Login)(BSTR bstrUsername, BSTR bstrPassword, BSTR bstrIP, LONG lPort);
	STDMETHOD(Logout)();
	STDMETHOD(SetMediaServer)(BSTR bstrMediaServerIP, LONG lPort);
	STDMETHOD(GetMediaServer)(BSTR* bstrMediaServerIP, LONG* lPort);
	STDMETHOD(StartMonitor)(LONG lWndNum);
	STDMETHOD(StopMonitor)();
	STDMETHOD(CapPic)(BSTR* pbstrCapFolder);
	STDMETHOD(GetCapturePath)(BSTR* bstrCapFolder);
	STDMETHOD(SetCapturePath)(BSTR bstrCapFolder);
	STDMETHOD(ShowMetaData)(VARIANT_BOOL bShow);
};

OBJECT_ENTRY_AUTO(__uuidof(SonicIMVPlayerCtrl), CSonicIMVPlayerCtrl)
