// CDVRMVSettings.cpp  : Definition of ActiveX Control wrapper class(es) created by Microsoft Visual C++


#include "stdafx.h"
#include "CDVRMVSettings.h"
#import "msxml6.dll"

/////////////////////////////////////////////////////////////////////////////
// CDVRMVSettings

// CDVRMVSettings properties

// CDVRMVSettings operations

#define ERROR_RETURN(x) \
	{\
	HRESULT __hhrr = (x);\
	if (FAILED(__hhrr))\
	{\
		CString csMsg;\
		csMsg.Format(_T("ÔËÐÐ%d = %s³ö´í"), __hhrr, CA2T(#x));\
		AfxMessageBox(csMsg);\
		return false;\
	}\
}

bool CDVRMVSettings::Save(LPCTSTR szXmlPath)
{
	CComVariant bstrPath;
	if (szXmlPath != NULL)
	{
		bstrPath = szXmlPath;
	}
	else
	{
		TCHAR path[_MAX_PATH] = {0X00};
		ExtractFilePath(path);
		_tcscat(path, _T("\\HHitLogin.xml"));
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

		// ´æ´¢MediaServerIP
		MSXML2::IXMLDOMNodePtr spElm = spDoc->createElement(_T("MediaServerIP"));
		spElm->Puttext((LPCTSTR)m_csMediaServerIP);
		spRoot->appendChild(spElm);

		// ´æ´¢MediaServerPort
		spElm = spDoc->createElement(_T("MediaServerPort"));
		spElm->Puttext((LPCTSTR)m_lPort);
		spRoot->appendChild(spElm);

		// ´æ´¢MediaLoginUsername
		spElm = spDoc->createElement(_T("MediaLoginUsername"));
		spElm->Puttext((LPCTSTR)m_csUsername);
		spRoot->appendChild(spElm);

		// ´æ´¢MediaLoginPassword
		spElm = spDoc->createElement(_T("MediaLoginPassword"));
		spElm->Puttext((LPCTSTR)m_csPassword);
		spRoot->appendChild(spElm);

		ERROR_RETURN(spDoc->save(bstrPath));
	}
	catch (CException* e)
	{
		return false;
	}
	return true;
}

bool CDVRMVSettings::Load(LPCTSTR szXmlPath)
{
	CComVariant bstrPath;
	if (szXmlPath != NULL)
	{
		bstrPath = szXmlPath;
	}
	else
	{
		TCHAR path[_MAX_PATH] = {0X00};
		ExtractFilePath(path);
		_tcscat(path, _T("\\HHitLogin.xml"));
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
		VARIANT_BOOL bIsSuccess = spDoc->load(bstrPath);
		if (bIsSuccess == VARIANT_FALSE)
		{
			CString csMsg;
			csMsg.Format(_T("¶ÁÈ¡ÎÄ¼þ%sÊ§°Ü£¡"), bstrPath.bstrVal);
			TRACE((LPCTSTR)csMsg);
			//AfxMessageBox(csMsg);
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
				m_lPort = spRoot->childNodes->Getitem(index)->Gettext().GetBSTR();
			}
			else if (spRoot->childNodes->Getitem(index)->GetnodeName() == _bstr_t(_T("MediaLoginUsername")))
			{
				m_csUsername = spRoot->childNodes->Getitem(index)->Gettext().GetBSTR();
			}
			else if (spRoot->childNodes->Getitem(index)->GetnodeName() == _bstr_t(_T("MediaLoginPassword")))
			{
				m_csPassword = spRoot->childNodes->Getitem(index)->Gettext().GetBSTR();
			}
		}
	}
	catch (CException* e)
	{
		return false;
	}

	return true;
}

BOOL CDVRMVSettings::ExtractFilePath(TCHAR* chPath)
{
	TCHAR path[_MAX_PATH] = {0X00};
	HMODULE hCurModule = NULL;
	::GetModuleFileName(hCurModule,(TCHAR*)path,sizeof(path));
	CString strPath = path;
	INT nPos = strPath.ReverseFind( '\\' );
	_tcsncpy( chPath, strPath, nPos );
	return TRUE;
}