#include "StdAfx.h"
#include "DVRSettings.h"
#import "msxml4.dll"

#define ERROR_RETURN(x) \
	if (FAILED(x))\
	{\
		CString csMsg;\
		csMsg.Format(_T("运行%s出错"), ##x);\
		AfxMessageBox(csMsg);\
		return false;\
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
}


CDVRSettings::~CDVRSettings(void)
{
	::CoUninitialize();
}

bool CDVRSettings::Save(LPCTSTR szXmlPath)
{
	CComVariant bstrPath = _T("DVRSettings.xml");
	if (szXmlPath != NULL)
	{
		bstrPath = szXmlPath;
	}

	try
	{
		MSXML2::IXMLDOMDocumentPtr spDoc;
		MSXML2::IXMLDOMNodePtr spRoot;

		ERROR_RETURN(spDoc.CreateInstance(__uuidof(MSXML2::DOMDocument40)));
		CComVariant	nodeType = NODE_ELEMENT;

		spRoot = spDoc->createNode(nodeType, _T("DVRSettings"), _T(""));

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

		spDoc->appendChild(spRoot);
		ERROR_RETURN(spDoc->save(bstrPath));
	}
	catch (CMemoryException* e)
	{
		return false;
	}
	catch (CException* e)
	{
		return false;
	}
	return true;
}
bool CDVRSettings::Load(LPCTSTR szXmlPath)
{
	CComVariant bstrPath = _T("DVRSettings.xml");
	if (szXmlPath != NULL)
	{
		bstrPath = szXmlPath;
	}

	try
	{
		MSXML2::IXMLDOMDocumentPtr spDoc;
		MSXML2::IXMLDOMNodePtr spRoot;

		ERROR_RETURN(spDoc.CreateInstance(__uuidof(MSXML2::DOMDocument40)));

		VARIANT_BOOL bIsSuccess = spDoc->load(bstrPath);
		if (bIsSuccess == VARIANT_FALSE)
		{
			CString csMsg;
			csMsg.Format(_T("读取文件%s失败！"), bstrPath);
			AfxMessageBox(csMsg);
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
			//else if
		}
	}
	catch (CException* e)
	{
		return false;
	}

	return true;
}