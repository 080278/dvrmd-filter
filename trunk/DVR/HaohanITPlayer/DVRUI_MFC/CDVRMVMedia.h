// CDVRMVMedia.h  : Declaration of ActiveX Control wrapper class(es) created by Microsoft Visual C++

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CDVRMVMedia

class CDVRMVMedia : public COleDispatchDriver
{
public:
	CDVRMVMedia() {}		// Calls COleDispatchDriver default constructor
	CDVRMVMedia(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CDVRMVMedia(const CDVRMVMedia& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:

	long get_imageSourceWidth()
	{
		long result;
		InvokeHelper(0x97, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	long get_imageSourceHeight()
	{
		long result;
		InvokeHelper(0x98, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	double get_duration()
	{
		double result;
		InvokeHelper(0x99, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
		return result;
	}
	CString get_durationString()
	{
		CString result;
		InvokeHelper(0x9a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}


};
