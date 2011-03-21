// IVProcess.cpp: implementation of the CIVProcess class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VPKServer.h"
#include "IVProcess.h"
#include "TraceLog.h"
#include "YuvRgbConverter.h"

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
		PIPE_ACCESS_DUPLEX,         //全双工
		PIPE_TYPE_BYTE | PIPE_WAIT | PIPE_READMODE_BYTE,  // 字节流，并且阻塞
		2,                         // 实例个数
		MAX_PIPE_BUF_LENGTH,                           // 流出数据缓冲大小
		MAX_PIPE_BUF_LENGTH,                           // 流入数据缓冲大小
		1000,                         // 超时，毫秒
		NULL                         // 安全信息
		);
    if(m_hPipe== INVALID_HANDLE_VALUE)
	{
		TRACE_LOG( "创建命名管道失败\r\n");
        return -1;
    }
	
	TD_IVProcess();
	return 0;
}


INT CIVProcess::TD_IVProcess()
{
	BOOL bRet = FALSE;
	
	TRACE_LOG("等待客户…… \r\n");
	while (!m_bExit)
	{
		// 检测退出标志
		if( ConnectNamedPipe(m_hPipe, NULL) )
		{
			TRACE_LOG("有客户接入\r\n");
		}
		else//已经连接过，检测是否客户端关闭
		{
			if (GetLastError() ==  ERROR_PIPE_CONNECTED)  // 客户还在连接中
			{
				TRACE_LOG("连接正常…… \r\n");
				bRet = true;
			}
			if (GetLastError() ==  ERROR_NO_DATA)         // 客户已经关闭
			{
				DisconnectNamedPipe(m_hPipe);
				TRACE_LOG("客户已经关闭，等待新客户…… \r\n");
				continue;
			}
		}
		
		DWORD  dwBytesReaded = 0;

		//先读帧头
		FRAME_HEADER_VPK frameHdr;
		bRet = ReadFile(m_hPipe, &frameHdr, sizeof(frameHdr), &dwBytesReaded, NULL);
		if( !bRet || dwBytesReaded != sizeof(FRAME_HEADER_VPK) )
		{
			TRACE_LOG("获取帧头信息失败\r\n\r\n");
			//是否要关闭pipe
			return -1;
		}
		TRACE_LOG("获取帧头信息 width = %d height = %d framelen = %d\r\n\r\n", 
						frameHdr.Width, frameHdr.Height, frameHdr.FrameLength);
		//1、读取YUV420数据
		bRet = ReadFile(m_hPipe, m_yuvImage, frameHdr.FrameLength, &dwBytesReaded, NULL);	
		if( !bRet || dwBytesReaded != frameHdr.FrameLength )
		{
			TRACE_LOG("获取YUV数据失败 error = %d\r\n\r\n", GetLastError());
			//是否要关闭pipe
			return -2;
		}
		TRACE_LOG("获取YUV数据数据 width = %d height = %d dwBytesReaded = %d\r\n\r\n", 
			frameHdr.Width, frameHdr.Height, dwBytesReaded);
		//2、YUV转化为RGB32
		INT width = frameHdr.Width;
		INT height = frameHdr.Height;
		BYTE* y = m_yuvImage ;
		BYTE* v = y + width * height ;
		BYTE* u = v + ( width >> 1 ) * ( height >> 1 ) ;		
		CYuvRgbConverter::yv12_to_rgb32_mmx( m_rgbImage , width , y , v , u , width , width >> 1 , width , -height ) ;
		
		//3、调用分析引擎分析，获得m_meta
		//DoProcess m_rgbImage..................................
		//DoProcess m_rgbImage..................................
//请在这里填充分析引擎
		//DoProcess m_rgbImage..................................
		//DoProcess m_rgbImage..................................

		
		//4、将meta数据及帧头写入客户端
		FRAME_HEADER_VPK metaHdr;
		metaHdr.FrameLength = 12;//测试，假设meta数据长12
		memcpy( m_meta,  "METAMETAMETA", metaHdr.FrameLength );
		DWORD dwBytesWritten = 0;

		//帧头
		bRet = ::WriteFile(m_hPipe, &metaHdr, sizeof(metaHdr), &dwBytesWritten, NULL);
		if( !bRet || dwBytesWritten != sizeof(metaHdr) )
		{
			TRACE_LOG("写输入meta帧头数据失败 error = %d\r\n\r\n", GetLastError() );
			//是否要关闭pipe
			return -3;
		}
		TRACE_LOG("写输入meta头 数据成功 width = %d height = %d dwBytesWritten = %d\r\n\r\n", 
			frameHdr.Width, frameHdr.Height, dwBytesWritten);
		//帧数据
		bRet = ::WriteFile(m_hPipe, m_meta, metaHdr.FrameLength , &dwBytesWritten, NULL);
		if( !bRet || dwBytesWritten != metaHdr.FrameLength  )
		{
			TRACE_LOG("写输入meta数据失败 error = %d\r\n\r\n", GetLastError() );
			//是否要关闭pipe
			return -4;
		}
		TRACE_LOG("写输入meta 数据成功 width = %d height = %d dwBytesWritten = %d\r\n\r\n", 
			frameHdr.Width, frameHdr.Height, dwBytesWritten);
	}
	return 0;
}
