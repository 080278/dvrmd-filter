#include "StdAfx.h"
#include "DVRSettings.h"


CDVRSettings::CDVRSettings(void)
	: m_lPort(-1)
	, m_bHighPictureQuality(FALSE)
	, m_eCapturePicType(eJPEG)
	, m_nRenderWndNum(1)
	, m_nRenderWidth(640)
	, m_nRenderHeight(480)
{
}


CDVRSettings::~CDVRSettings(void)
{
}
