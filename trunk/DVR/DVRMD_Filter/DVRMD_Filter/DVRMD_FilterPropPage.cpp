// DVRMD_FilterPropPage.cpp : Implementation of the CDVRMD_FilterPropPage property page class.

#include "stdafx.h"
#include "DVRMD_Filter.h"
#include "DVRMD_FilterPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CDVRMD_FilterPropPage, COlePropertyPage)



// Message map

BEGIN_MESSAGE_MAP(CDVRMD_FilterPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CDVRMD_FilterPropPage, "DVRMD_FILTER.DVRMD_FilterPropPage.1",
	0x410847a0, 0x65ac, 0x462c, 0x9f, 0x89, 0x5a, 0xf, 0x5b, 0x39, 0x6b, 0xaa)



// CDVRMD_FilterPropPage::CDVRMD_FilterPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CDVRMD_FilterPropPage

BOOL CDVRMD_FilterPropPage::CDVRMD_FilterPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_DVRMD_FILTER_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CDVRMD_FilterPropPage::CDVRMD_FilterPropPage - Constructor

CDVRMD_FilterPropPage::CDVRMD_FilterPropPage() :
	COlePropertyPage(IDD, IDS_DVRMD_FILTER_PPG_CAPTION)
{
}



// CDVRMD_FilterPropPage::DoDataExchange - Moves data between page and properties

void CDVRMD_FilterPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CDVRMD_FilterPropPage message handlers
