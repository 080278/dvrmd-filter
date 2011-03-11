// DVRMD_Filter.cpp : Implementation of CDVRMD_FilterApp and DLL registration.

#include "stdafx.h"
#include "DVRMD_Filter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CDVRMD_FilterApp theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0xD040A193, 0xED38, 0x49B2, { 0xAF, 0xDE, 0xD1, 0xE, 0x86, 0xA9, 0xEF, 0xCE } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CDVRMD_FilterApp::InitInstance - DLL initialization

BOOL CDVRMD_FilterApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: Add your own module initialization code here.
	}

	return bInit;
}



// CDVRMD_FilterApp::ExitInstance - DLL termination

int CDVRMD_FilterApp::ExitInstance()
{
	// TODO: Add your own module termination code here.

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
