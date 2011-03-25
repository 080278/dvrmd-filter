#if !defined(AFX_PLAYER_H__A25350EB_6B96_4CFB_BBE7_5654197142F7__INCLUDED_)
#define AFX_PLAYER_H__A25350EB_6B96_4CFB_BBE7_5654197142F7__INCLUDED_

#include "./ComSocket.h"
#include "./StreamParser.h"
#include "./RealStreamParser.h"
#include "./PlayStreamParser.h"
#include "./struct_TCPServ.h"

#define SYN_READ_STREAM
#define WAIT_THREAD_EXIT_MAX_TIME    (5*1000)

//错误类型定义
#define SDK_ERROR       1
#define CLIENT_ERROR    2
#define SERVER_ERROR    3

//连接DVR信息
struct HHV_CONN_INFO
{
	HHV_CONN_INFO(){ memset( this, 0x00, sizeof(HHV_CONN_INFO) );	}
	CHAR	ip[48];
	INT		port;
	CHAR	userName[32];	
	CHAR	pwd[32];
};

struct HHV_CLIENT_INFO
{
	HHV_CLIENT_INFO(){ memset( this, 0x00, sizeof(HHV_CLIENT_INFO) );	}
	HHV_CONN_INFO connInfo;
	int channel;//通道号，从0开始	
	int childstream;	//0-主码流；1-次码流
};

class CPlayer  
{
public:
	CPlayer();
	virtual ~CPlayer();
	
	VOID Init(HWND hNotifyWnd, int index_MTManager);
	VOID Clearup();
	
	INT StartMonitor(HWND hWnd, HHV_CLIENT_INFO* clientInfo);
	VOID StopMonitor( );

	int  StartPlayBackByTime(HWND hWnd, SYSTEM_VIDEO_FILE* recdFile,char* ssIP, int ssPort);
	void StopPlayBackByTime(int realHandle);

private:
	INT MonitorStartCmdMT(SOCKET sk, HHV_CLIENT_INFO* clientInfo, 
		char* streamHeader, int& size);

	int PlayStartCmdByTime( SOCKET sk, SYSTEM_VIDEO_FILE* recdFile,
							char* streamHeader, int& size,
							SPlayBackByTimeResponseInfo&  rspBody );
private:
	static UINT __stdcall DecoderRoutine(void * dat);
	INT InputData();

	static void CALLBACK MP4SDKDrawFun(long nPort,HDC hDc,LONG nUser);
private:
	CComSocket m_comSocket;
	
	BOOL m_exit;
	
	CHAR m_buffer[MAX_FRAME_LENGTH];
	CHAR m_meta[10*1024];

	INT  m_PlayHandle;

	INT  m_index;

	HANDLE m_Thread ;

	HHV_CLIENT_INFO m_clientInfo;

	HANDLE m_hExitEvent;

	HWND m_hNotifyWnd ;

	CHAR m_streamHeader[4*1024];

	int            m_playbacklen;  //回放的文件长度
	int            m_pos;        //现在位置 ==   已经接受到的文件大小
	
	CRealStreamParser m_streamParser;
	CPlayStreamParser m_streamParser_PlayBack;

	FRAME_HEADER m_frameHeader;

	INT InputData_Frame();//按帧读取填充
	INT InputData_Frame_PlayBack();//按帧读取填充

	int m_playType;

};

#endif // !defined(AFX_PLAYER_H__A25350EB_6B96_4CFB_BBE7_5654197142F7__INCLUDED_)
