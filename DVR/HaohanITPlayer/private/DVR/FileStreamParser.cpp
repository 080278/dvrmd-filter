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