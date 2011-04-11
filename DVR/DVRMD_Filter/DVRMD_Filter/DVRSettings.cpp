#include "StdAfx.h"
#include "DVRSettings.h"
#import "msxml6.dll"
#include "./CommClass.h"

#define ERROR_RETURN(x) \
	{\
	HRESULT __hhrr = (x);\
	if (FAILED(__hhrr))\
	{\
		CString csMsg;\
		csMsg.Format(_T("运行%d = %s出错"), __hhrr, CA2T(#x));\
		AfxMessageBox(csMsg);\
		return false;\
	}\
}

CDVRSettings::CDVRSettings(void)
	: m_lPort(-1)
	, m_bHighPictureQuality(FALSE)
	, m_eCapturePicType(eJPEG)
	, m_nRenderWndNum(1)
	, m_nRenderWidth(352)
	, m_nRenderHeight(288)
{
	::CoInitialize(NULL);
	Load();
}


CDVRSettings::~CDVRSettings(void)
{
	Save();
	::CoUninitialize();
}

bool CDVRSettings::Save(LPCTSTR szXmlPath)
{
	CComVariant bstrPath;
	if (szXmlPath != NULL)
	{
		bstrPath = szXmlPath;
	}
	else
	{
		TCHAR path[_MAX_PATH] = {0X00};
		CCommClass::ExtractFilePath( path );
		_tcscat(path, _T("\\DVRSettings.xml"));
		bstrPath = path;
	}

	try
	{
		MSXML2::IXMLDOMDocumentPtr spDoc;
		MSXML2::IXMLDOMNodePtr spRoot;

		HRESULT hr = spDoc.CreateInstance(__uuidof(MSXML2::DOMDocument40));
		if (FAILED(hr))
		{
			hr = spDoc.CreateInstance(__uuidof(MSXML2::DOMDocument60));
		}
		CComVariant	nodeType = NODE_ELEMENT;

		spRoot = spDoc->createNode(nodeType, _T("DVRSettings"), _T(""));
		spDoc->appendChild(spRoot);

		// 存储MediaServerIP
		MSXML2::IXMLDOMNodePtr spElm = spDoc->createElement(_T("MediaServerIP"));
		spElm->Puttext((LPCTSTR)m_csMediaServerIP);
		spRoot->appendChild(spElm);

		// 存储MediaServerPort
		spElm = spDoc->createElement(_T("MediaServerPort"));
		CString csPort;
		csPort.Format(_T("%d"), m_lPort);
		spElm->Puttext((LPCTSTR)csPort);
		spRoot->appendChild(spElm);

		// ...

		ERROR_RETURN(spDoc->save(bstrPath));
	}
	catch (CException* e)
	{
		return false;
	}
	return true;
}
bool CDVRSettings::Load(LPCTSTR szXmlPath)
{
	CComVariant bstrPath;
	if (szXmlPath != NULL)
	{
		bstrPath = szXmlPath;
	}
	else
	{
		TCHAR path[_MAX_PATH] = {0X00};
		CCommClass::ExtractFilePath( path );
		_tcscat(path, _T("\\DVRSettings.xml"));
		bstrPath = path;
	}

	try
	{
		MSXML2::IXMLDOMDocumentPtr spDoc;
		MSXML2::IXMLDOMNodePtr spRoot;

		//ERROR_RETURN(spDoc.CreateInstance(__uuidof(MSXML2::DOMDocument40)));
		HRESULT hr = spDoc.CreateInstance(__uuidof(MSXML2::DOMDocument40));
		if (FAILED(hr))
		{
			hr = spDoc.CreateInstance(__uuidof(MSXML2::DOMDocument60));
		}
		VARIANT_BOOL bIsSuccess = spDoc->load(bstrPath);
		if (bIsSuccess == VARIANT_FALSE)
		{
			CString csMsg;
			csMsg.Format(_T("读取文件%s失败！"), bstrPath.bstrVal);
			AfxMessageBox(csMsg);
			return false;
		}

		spRoot = spDoc->documentElement;
		for (long index = 0; index <spRoot->childNodes->Getlength(); ++index)
		{
			if (spRoot->childNodes->Getitem(index)->GetnodeName() == _bstr_t(_T("MediaServerIP")))
			{
				m_csMediaServerIP = spRoot->childNodes->Getitem(index)->Gettext().GetBSTR();
			}
			else if (spRoot->childNodes->Getitem(index)->GetnodeName() == _bstr_t(_T("MediaServerPort")))
			{
				m_lPort = _ttoi(spRoot->childNodes->Getitem(index)->Gettext());
			}
			//else if(...)
		}
	}
	catch (CException* e)
	{
		return false;
	}

	return true;
}