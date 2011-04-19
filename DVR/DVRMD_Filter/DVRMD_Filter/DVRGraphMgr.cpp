#include "StdAfx.h"
#include "DVRGraphMgr.h"


CDVRGraphMgr::CDVRGraphMgr(void)
{
}


CDVRGraphMgr::~CDVRGraphMgr(void)
{
}

HRESULT CDVRGraphMgr::BuildGraph()
{
	ReleaseGraph();

	m_spGraphBuilder.CoCreateInstance(CLSID_FilterGraph);

	return S_OK;
}
void CDVRGraphMgr::ReleaseGraph()
{
	m_spGraphBuilder.Release();
}
int CDVRGraphMgr::RenderFile(LPCTSTR szFile)
{
	//m_spGraphBuilder->AddSourceFilter(szFile, )

	return 0;
}