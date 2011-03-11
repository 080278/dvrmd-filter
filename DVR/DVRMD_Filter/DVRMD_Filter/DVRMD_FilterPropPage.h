#pragma once

// DVRMD_FilterPropPage.h : Declaration of the CDVRMD_FilterPropPage property page class.


// CDVRMD_FilterPropPage : See DVRMD_FilterPropPage.cpp for implementation.

class CDVRMD_FilterPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CDVRMD_FilterPropPage)
	DECLARE_OLECREATE_EX(CDVRMD_FilterPropPage)

// Constructor
public:
	CDVRMD_FilterPropPage();

// Dialog Data
	enum { IDD = IDD_PROPPAGE_DVRMD_FILTER };

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	DECLARE_MESSAGE_MAP()
};

