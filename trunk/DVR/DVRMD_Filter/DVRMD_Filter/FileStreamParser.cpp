#include "StdAfx.h"
#include "FileStreamParser.h"


CFileStreamParser::CFileStreamParser(void)
{
	m_hFileStream = NULL;
}


CFileStreamParser::~CFileStreamParser(void)
{
}

void CFileStreamParser::SetFileStreamHandle(HANDLE hFile)
{
	m_hFileStream = hFile;
}

int	CFileStreamParser::ReadCacheData( BYTE* buf, int size )
{
	DWORD dwRead = 0;
	if (ReadFile(m_hFileStream, buf, size, &dwRead, NULL) && dwRead > 0)
	{
		return dwRead;
	}
	return 0;
}

CHttpStreamParser::CHttpStreamParser()
{
	m_hInternetOpen = NULL;
	m_hInternetOpenUrl = NULL;
}
CHttpStreamParser::~CHttpStreamParser()
{
	CloseHttp();
}

BOOL CHttpStreamParser::OpenHttp(LPCTSTR szURL)
{
	CloseHttp();

	m_hInternetOpen = InternetOpen(NULL, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
	if (m_hInternetOpen == NULL)
	{
		return FALSE;
	}

	m_hInternetOpenUrl = InternetOpenUrl(m_hInternetOpen, szURL, NULL, 0, INTERNET_FLAG_TRANSFER_BINARY | INTERNET_FLAG_PRAGMA_NOCACHE, 0);
	if (m_hInternetOpenUrl == NULL)
	{
		return FALSE;
	}

	return TRUE;
}
void CHttpStreamParser::CloseHttp()
{
	if (m_hInternetOpenUrl != NULL)
	{
		::InternetCloseHandle(m_hInternetOpenUrl);
		m_hInternetOpenUrl = NULL;
	}
	if (m_hInternetOpen != NULL)
	{
		::InternetCloseHandle(m_hInternetOpen);
		m_hInternetOpen = NULL;
	}
}

int CHttpStreamParser::ReadCacheData(BYTE* buf, int size)
{
	if (m_hInternetOpenUrl != NULL)
	{
		DWORD dwRead;
		InternetReadFile(m_hInternetOpenUrl, buf, size, &dwRead);
		return dwRead;
	}
	return 0;
}

DWORD CHttpStreamParser::GetFileSize()
{
	if (m_hInternetOpen && m_hInternetOpenUrl)
	{
		DWORD dwContentLength = 0;
		DWORD dwLengthSize = sizeof(dwContentLength);
		if (HttpQueryInfo(m_hInternetOpenUrl, HTTP_QUERY_CONTENT_LENGTH|HTTP_QUERY_FLAG_NUMBER, &dwContentLength, &dwLengthSize, NULL))
		{
			return dwContentLength;
		}
	}
	return 0;
}