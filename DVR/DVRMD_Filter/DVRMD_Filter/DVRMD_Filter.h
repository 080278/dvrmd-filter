#pragma once

// DVRMD_Filter.h : main header file for DVRMD_Filter.DLL

#if !defined( __AFXCTL_H__ )
#error "include 'afxctl.h' before including this file"
#endif

#include "resource.h"       // main symbols
//#include "../DVRMDPlayer/Player.h"


// CDVRMD_FilterApp : See DVRMD_Filter.cpp for implementation.

class CDVRMD_FilterApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();

	//CPlayerApp	m_playerApp;
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

