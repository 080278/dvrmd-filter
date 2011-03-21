// VPKServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "VPKServer.h"
#include <process.h>
#include "IVProcess.h"
#include "TraceLog.h"

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

CIVProcess	g_ivPorcess;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		TRACE_LOG("Fatal Error: MFC initialization failed");
		return -1;
	}

	LPWSTR *szArglist = NULL;
	int nArgs = 0;;
	int i = 0;
	szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
	if( NULL == szArglist )
	{
		//TRACE_LOG(L"CommandLineToArgvW failed\n");
		MessageBox(NULL, "ͨ���������ʧ��\r\n\r\n","��ʾ", MB_OK);
		return 0;
	}
	if( nArgs != 2 )
	{
		MessageBox(NULL, "ͨ����������ȷ\r\n\r\n", "��ʾ", MB_OK);
		return 0;
	}
	CString strChIndex = szArglist[1];
	int chIndex = atoi(strChIndex.GetBuffer(0) );

	TRACE_LOG( "ͨ����������Ϊ %d \r\n\r\n", chIndex );

	g_ivPorcess.DoIVProcess(chIndex);

	return 0;
}


