// Player.h : main header file for the PLAYER application
//

#if !defined(AFX_PLAYER_H__B22F676B_7805_4359_8D74_B5A63BA0B5F9__INCLUDED_)
#define AFX_PLAYER_H__B22F676B_7805_4359_8D74_B5A63BA0B5F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#ifdef _FOR_HIKPLAYM4_DLL_
	//#define NAME(x) Hik_##x
	//#include "hikplaympeg4.h"
#define NAME(x) x
	#include "PlayM4.h"
#else
	#define NAME(x) x
	//#include "plaympeg4.h"
	#include "PlayM4.h"
#endif

#include "./ComSocket.h"
#include "./StreamParser.h"
#include "./RealStreamParser.h"
#include "./PlayStreamParser.h"
#include "./NetDef.h"
#include "DVRSettings.h"

#define SYN_READ_STREAM
#define WAIT_THREAD_EXIT_MAX_TIME    (5*1000)

//错误类型定义
#define SDK_ERROR       1
#define CLIENT_ERROR    2
#define SERVER_ERROR    3

class CPlayer  
{
public:
	CPlayer();
	virtual ~CPlayer();
	
	VOID Init(HWND hNotifyWnd, int index_MTManager);
	VOID Clearup();
	
	INT StartMonitor(HWND hWnd, HHV_CLIENT_INFO* clientInfo);
	VOID StopMonitor( );

	int  StartPlayBackByTime(HWND hWnd, SYSTEM_VIDEO_FILE* recdFile,char* ssIP, int ssPort);
	void StopPlayBackByTime(int realHandle);

private:
	INT MonitorStartCmdMT(SOCKET sk, HHV_CLIENT_INFO* clientInfo, 
		char* streamHeader, int& size);

	int PlayStartCmdByTime( SOCKET sk, SYSTEM_VIDEO_FILE* recdFile,
							char* streamHeader, int& size,
							SPlayBackByTimeResponseInfo&  rspBody );
private:
	static UINT __stdcall DecoderRoutine(void * dat);
	INT InputData();

	static void CALLBACK MP4SDKDrawFun(long nPort,HDC hDc,LONG nUser);
private:
	CComSocket m_comSocket;
	
	BOOL m_exit;
	
	CHAR m_buffer[MAX_FRAME_LENGTH];
	CHAR m_meta[10*1024];

	INT  m_PlayHandle;

	INT  m_index;

	HANDLE m_Thread ;

	HHV_CLIENT_INFO m_clientInfo;

	HANDLE m_hExitEvent;

	HWND m_hNotifyWnd ;

	CHAR m_streamHeader[4*1024];

	int            m_playbacklen;  //回放的文件长度
	int            m_pos;        //现在位置 ==   已经接受到的文件大小
	
	CRealStreamParser m_streamParser;
	CPlayStreamParser m_streamParser_PlayBack;

	FRAME_HEADER m_frameHeader;

	INT InputData_Frame();//按帧读取填充
	INT InputData_Frame_PlayBack();//按帧读取填充

	int m_playType;

};
#endif // !defined(AFX_PLAYER_H__B22F676B_7805_4359_8D74_B5A63BA0B5F9__INCLUDED_)
