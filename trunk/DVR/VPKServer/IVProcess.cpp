// IVProcess.cpp: implementation of the CIVProcess class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VPKServer.h"
#include "IVProcess.h"
#include "TraceLog.h"
#include "YuvRgbConverter.h"
#include "Engine.h"
#include <string>
using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIVProcess::CIVProcess()
{
	m_hPipe = INVALID_HANDLE_VALUE;
	m_bExit = FALSE;
}

CIVProcess::~CIVProcess()
{

}

int CIVProcess::DoIVProcess(int chIndex)
{	
	char pname[128] = {0x00};
	sprintf(pname,"\\\\.\\pipe\\pipe_source_%d",chIndex);
	
	m_hPipe = ::CreateNamedPipe(pname, 
		PIPE_ACCESS_DUPLEX,         //ȫ˫��
		PIPE_TYPE_BYTE | PIPE_WAIT | PIPE_READMODE_BYTE,  // �ֽ�������������
		2,                         // ʵ������
		MAX_PIPE_BUF_LENGTH,                           // �������ݻ����С
		MAX_PIPE_BUF_LENGTH,                           // �������ݻ����С
		1000,                         // ��ʱ������
		NULL                         // ��ȫ��Ϣ
		);
    if(m_hPipe== INVALID_HANDLE_VALUE)
	{
		TRACE_LOG( "���������ܵ�ʧ��\r\n");
        return -1;
    }
	
	TD_IVProcess();
	return 0;
}


INT CIVProcess::TD_IVProcess()
{
	BOOL bRet = FALSE;
	
	TRACE_LOG("�ȴ��ͻ����� \r\n");
	while (!m_bExit)
	{
		// ����˳���־
		if( ConnectNamedPipe(m_hPipe, NULL) )
		{
			TRACE_LOG("�пͻ�����\r\n");
		}
		else//�Ѿ����ӹ�������Ƿ�ͻ��˹ر�
		{
			if (GetLastError() ==  ERROR_PIPE_CONNECTED)  // �ͻ�����������
			{
				TRACE_LOG("������������ \r\n");
				bRet = true;
			}
			if (GetLastError() ==  ERROR_NO_DATA)         // �ͻ��Ѿ��ر�
			{
				DisconnectNamedPipe(m_hPipe);
				TRACE_LOG("�ͻ��Ѿ��رգ��ȴ��¿ͻ����� \r\n");
				continue;
			}
		}
		
		DWORD  dwBytesReaded = 0;

		//�ȶ�֡ͷ
		FRAME_HEADER_VPK frameHdr;
		bRet = ReadFile(m_hPipe, &frameHdr, sizeof(frameHdr), &dwBytesReaded, NULL);
		if( !bRet || dwBytesReaded != sizeof(FRAME_HEADER_VPK) )
		{
			TRACE_LOG("��ȡ֡ͷ��Ϣʧ��\r\n\r\n");
			//�Ƿ�Ҫ�ر�pipe
			return -1;
		}
		TRACE_LOG("��ȡ֡ͷ��Ϣ width = %d height = %d framelen = %d\r\n\r\n", 
						frameHdr.Width, frameHdr.Height, frameHdr.FrameLength);
		//1����ȡYUV420����
		bRet = ReadFile(m_hPipe, m_yuvImage, frameHdr.FrameLength, &dwBytesReaded, NULL);	
		if( !bRet || dwBytesReaded != frameHdr.FrameLength )
		{
			TRACE_LOG("��ȡYUV����ʧ�� error = %d\r\n\r\n", GetLastError());
			//�Ƿ�Ҫ�ر�pipe
			return -2;
		}
		TRACE_LOG("��ȡYUV�������� width = %d height = %d dwBytesReaded = %d\r\n\r\n", 
			frameHdr.Width, frameHdr.Height, dwBytesReaded);
		//2��YUVת��ΪRGB32
		INT width = frameHdr.Width;
		INT height = frameHdr.Height;
		BYTE* y = m_yuvImage ;
		BYTE* v = y + width * height ;
		BYTE* u = v + ( width >> 1 ) * ( height >> 1 ) ;		
		CYuvRgbConverter::yv12_to_rgb32_mmx( m_rgbImage , width , y , v , u , width , width >> 1 , width , -height ) ;
		
		//3�����÷���������������m_meta
		//������������������
		HHV::Attributes attr;

		attr["simulation.frame_rate"]="10";    // the frame rate used
		attr["simulation.event_interval"]="3"; // generate event intervals in seconds
		HHV::Engine *vapi_engine=HHV::GetProcessingEngineInstance("Simulation", attr);

		//�������rgbImage������д��IplImage�ڣ�������������
#pragma message("Fix me: Please verify/debug below code!!!")
		IplImage *img = cvCreateImage(cvSize(width,height), IPL_DEPTH_8U, 3);
		img->imageData = (char*)m_rgbImage;
		img->imageDataOrigin = (char*)m_rgbImage;

		vector<HHV::Event> events_in;
		vapi_engine->Process(img, frameHdr.msTime, events_in);

		vector<HHV::VideoEvent> events_out;
		vapi_engine->GetVideoEvents(events_out);
		if (events_out.size()>0) {
			for (vector<HHV::VideoEvent>::size_type i=0; i < events_out.size(); i++)
			TRACE_LOG("%d: %s\n", i, events_out[i].event_name.c_str());
		}

		const IplImage *outimg= vapi_engine->GetProcessedImage();  // this contains the image with overlayed meta-data.
		HHV::FrameMetaDataList meta;
		vapi_engine->GetDisplayData(frameHdr.msTime, meta);  // meta contains the meta data that needs to be stored to dvr.

		cvReleaseImage(&img);

		
		//4����meta���ݼ�֡ͷд��ͻ���
		FRAME_HEADER_VPK metaHdr;
		metaHdr.FrameLength = 0;

		BYTE* pPos = m_meta;
		for (HHV::FrameMetaDataList::iterator it = meta.begin(); it != meta.end(); ++it)
		{
			VERIFY(pPos-m_meta <= MAX_META_LENGTH);
			std::auto_ptr<byte>	buf(it->ToMemory());
			memcpy(pPos, buf.get(), it->memsize());
			pPos += it->memsize();
		}

		metaHdr.FrameLength = pPos - m_meta;

		DWORD dwBytesWritten = 0;

		//֡ͷ
		bRet = ::WriteFile(m_hPipe, &metaHdr, sizeof(metaHdr), &dwBytesWritten, NULL);
		if( !bRet || dwBytesWritten != sizeof(metaHdr) )
		{
			TRACE_LOG("д����meta֡ͷ����ʧ�� error = %d\r\n\r\n", GetLastError() );
			//�Ƿ�Ҫ�ر�pipe
			return -3;
		}
		TRACE_LOG("д����metaͷ ���ݳɹ� width = %d height = %d dwBytesWritten = %d\r\n\r\n", 
			frameHdr.Width, frameHdr.Height, dwBytesWritten);
		//֡����
		bRet = ::WriteFile(m_hPipe, m_meta, metaHdr.FrameLength , &dwBytesWritten, NULL);
		if( !bRet || dwBytesWritten != metaHdr.FrameLength  )
		{
			TRACE_LOG("д����meta����ʧ�� error = %d\r\n\r\n", GetLastError() );
			//�Ƿ�Ҫ�ر�pipe
			return -4;
		}
		TRACE_LOG("д����meta ���ݳɹ� width = %d height = %d dwBytesWritten = %d\r\n\r\n", 
			frameHdr.Width, frameHdr.Height, dwBytesWritten);
	}
	return 0;
}
