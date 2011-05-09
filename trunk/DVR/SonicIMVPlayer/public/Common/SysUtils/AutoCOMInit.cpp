//-----------------------------------------------------------------------------
// AutoCOMInit.cpp
// Copyright (c) 2003 - 2004, Sonic Solutions.  All rights reserved.
//-----------------------------------------------------------------------------

#if !defined (__unix__)

#include "AutoCOMInit.h"

AutoCOMInit::AutoCOMInit(bool inIsThread /* = true */) :
	mIsThread(inIsThread)
{
	if(mIsThread)
		::CoInitialize(0);
}

AutoCOMInit::~AutoCOMInit()
{
	if(mIsThread)
		::CoUninitialize();
}

#endif // __unix__
