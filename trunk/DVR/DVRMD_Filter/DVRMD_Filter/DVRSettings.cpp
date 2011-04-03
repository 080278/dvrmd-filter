#include "StdAfx.h"
#include "DVRSettings.h"


CDVRSettings::CDVRSettings(void)
	: m_lPort(-1)
	, m_bHighPictureQuality(FALSE)
	, m_eCapturePicType(eJPEG)
	, m_nRenderWndNum(1)
{
}


CDVRSettings::~CDVRSettings(void)
{
}
