#pragma once
#include "StreamParser.h"

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

