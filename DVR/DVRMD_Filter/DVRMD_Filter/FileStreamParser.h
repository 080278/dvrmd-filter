#pragma once
#include "StreamParser.h"
#include <WinInet.h>

class CFileStreamParser : public CStreamParser
{
public:
	CFileStreamParser(void);
	virtual ~CFileStreamParser(void);

	void SetFileStreamHandle(HANDLE hFile);
public:
	virtual int	ReadCacheData( BYTE* buf, int size );

protected:
	HANDLE m_hFileStream;
};

class CHttpStreamParser : public CStreamParser
{
public:
	CHttpStreamParser();
	virtual ~CHttpStreamParser();

	BOOL OpenHttp(LPCTSTR szURL);
	BOOL IsOpen(){return m_hInternetOpen != NULL && m_hInternetOpenUrl != NULL;}
	void CloseHttp();

	DWORD GetFileSize();
public:
	virtual int ReadCacheData(BYTE* buf, int size);

protected:
	HINTERNET	m_hInternetOpen;
	HINTERNET	m_hInternetOpenUrl;
};
