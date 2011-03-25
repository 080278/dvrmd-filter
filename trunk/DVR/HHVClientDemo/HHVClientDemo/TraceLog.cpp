// TraceLog.cpp: implementation of the CDVRTraceLog class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TraceLog.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
FILE*	CDVRTrace::m_fileTrace = NULL	;
BOOL	CDVRTrace::m_bInited = FALSE;

CCritSec CDVRTrace::m_csTrace;

CDVRTrace::CDVRTrace()
{
	memset( this, 0x00, sizeof(CDVRTrace) );
}
CDVRTrace::~CDVRTrace(){
	UnInit();
}
void CDVRTrace::Init()
{
	CreateTraceFile( m_fileTrace, "HHVLog.txt" );
	m_bInited = TRUE;
}

void CDVRTrace::UnInit()
{
	if( m_fileTrace != NULL )
		fclose(m_fileTrace ); 
	m_bInited = FALSE;
}

void CDVRTrace::Trace(char* msg)
{
	if( !m_bInited )
	{
		Init();
		m_bInited = TRUE;
	}
	WriteTraceFile( m_fileTrace, msg );
	if( ftell(m_fileTrace) >= MAX_TRACE_FILE_LENGTH )
		UnInit();
}

void CDVRTrace::CreateTraceFile( FILE*& fileTrace, char* shortFileName )
{
	char path[256] = {0x00};
	CUtilities::ExtractAppPath( path);
	strcat( path, "LOG_HHV\\");
	CUtilities::CreateDirectory(path);
	SYSTEMTIME	sysTime;
	GetLocalTime(&sysTime);
	strcat(path, shortFileName);
	fileTrace = fopen( path,"w+b");
}
void CDVRTrace::WriteTraceFile( FILE*& fileTrace, char* msg )
{
	CHAR	buf[1024] = {0x00};
	SYSTEMTIME systime;
	GetLocalTime(&systime);
	sprintf( buf, "%04d-%02d-%02d %02d:%02d:%02d  ",systime.wYear, systime.wMonth, systime.wDay, systime.wHour, systime.wMinute, systime.wSecond);
	strcat( buf, msg );
	fputs( buf, fileTrace );
	fflush( fileTrace );	
}

void TRACE_LOG(LPCTSTR fmt , ... )
{
	CAutoLock_CS lc(&CDVRTrace::m_csTrace);
	va_list argPtr   ;	
	CHAR  msg[1024] = {0x00}  ;	
	va_start( argPtr, fmt );   
	vsprintf( msg, fmt, argPtr );  
	va_end  ( argPtr ); 
	//OutputDebugString( msg );
	CDVRTrace::Trace( msg );
}

void TRACE_CLOSE()
{
	
}