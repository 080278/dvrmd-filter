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


#endif // !defined(AFX_PLAYER_H__B22F676B_7805_4359_8D74_B5A63BA0B5F9__INCLUDED_)
