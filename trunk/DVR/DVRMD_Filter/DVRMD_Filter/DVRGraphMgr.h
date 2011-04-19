#pragma once

#include "dshow.h"
class CDVRGraphMgr
{
public:
	CDVRGraphMgr(void);
	~CDVRGraphMgr(void);

public:
	int RenderFile(LPCTSTR szFile);

	int Play();
	int Pause();
	int Stop();

	LONGLONG GetDuration();
	LONGLONG GetCurrentPosition();
	HRESULT SetCurrentPosition(LONGLONG lPos);

protected:
	HRESULT BuildGraph();
	void	ReleaseGraph();

	CComPtr<IGraphBuilder>	m_spGraphBuilder;
	CComPtr<IMediaSeeking>  m_spMediaSeeking;
};

