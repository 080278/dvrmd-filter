#ifndef _STRUCT_TCPSERV_H
#define _STRUCT_TCPSERV_H

#define NET_CHARACTER_LENGTH	32 

#include "winsock2.h"

#include "GUID.h"

typedef  unsigned char			U8  ;
typedef  unsigned short			U16 ;
typedef  unsigned int			U32 ;
typedef  unsigned __int64		U64 ;

#define DVRNameLen 80

#define _DVRIPLen  48

#define _DVRSerialNumLen 64

#define  VIDEO_USER_TYPE	1
//视频用户_需要当前时刻之前的固定长度的视频数据
#define  VIDEO_USER_NeedData_BeforeCurrentTime_TYPE		2 

#define NAME_LENGTH_LOCAL           64 //本地机器上使用的文件名长度
#define NAME_LENGTH_NET             32 //网络传输使用的文件名长度
#define NAME_LENGTH_NET64           80 //
#define DESCRIPTION_LENGTH_NET      128//描述长度
//#define RECV_BLOCK_SIZE             1024//下载文件时每次接收的数据块的大小
//#define RECV_BLOCK_SIZE_2           (128*1024)//下载文件时每次接收的数据块的大小


#define SYSTEM_COMMAND_BASE                       0x1000
//支持回放
#define SYSTEM_VIDEO_OPEN_REQUEST		         ( SYSTEM_COMMAND_BASE + 73  )
#define SYSTEM_VIDEO_CLOSE_REQUEST	   	         ( SYSTEM_COMMAND_BASE + 77  )
#define SYSTEM_VIDEO_READ_REQUEST	             ( SYSTEM_COMMAND_BASE + 78  )
#define SYSTEM_VIDEO_SEEK_REQUEST                ( SYSTEM_COMMAND_BASE + 81  )

#define SYSTEM_SS_REQUEST_ACCEPT                 ( SYSTEM_COMMAND_BASE + 84  )
#define SYSTEM_SS_UPDATE_OK                      ( SYSTEM_COMMAND_BASE + 86  )
#define SYSTEM_SS_UPDATE_FAIL                    ( SYSTEM_COMMAND_BASE + 87  )

//无文件回放
#define SYSTEM_SS_NoFilePlayBack				( SYSTEM_COMMAND_BASE + 93  )

#define SYSTEM_VIDEOCHANNEL_WORKSATUTUS_REQUEST		( SYSTEM_COMMAND_BASE + 88 )
#define SYSTEM_DVR_VIDEOCHANNEL_WORKSATUTUS_REQUEST		( SYSTEM_COMMAND_BASE + 89 )
#define SYSTEM_ALL_VIDEOCHANNEL_WORKSATUTUS_REQUEST		( SYSTEM_COMMAND_BASE + 90 )

// 按时间回放录像
#define SYSTEM_VIDEO_Playback_ByTime_REQUEST	( SYSTEM_COMMAND_BASE + 91 )

//请求视频监视
#define SYSTEM_MONITOR_START_DIRECT              ( SYSTEM_COMMAND_BASE + 44  )
#define SYSTEM_MONITOR_STOP						 ( SYSTEM_COMMAND_BASE + 46  )
#define SYSTEM_VS_REQUEST_ACCEPT                 ( SYSTEM_COMMAND_BASE + 47  )
#define SYSTEM_VS_REQUEST_REJECT                 ( SYSTEM_COMMAND_BASE + 48  )

// 监视, 并且需要当前时刻之前的固定长度的视频数据
#define SYSTEM_MONITOR_START_NeedData_BeforeCurrentTime	 ( SYSTEM_COMMAND_BASE + 51 )

#pragma pack(1)

struct DATE_INFO
{
	U16 year  ;
	U8 month ;
	U8 date  ;
	
	void h2n() { year = htons(year); }
	void n2h() { h2n(); }
};

struct TIME_INFO
{
	U8 hour   ;
	U8 minute ;
	U8 second ;
	U8 reserved ;
};

struct TIME_PHASEEX
{
    TIME_INFO 	start ;
    TIME_INFO 	end ;
    U8        	active ;
} ;

struct COMMAND_HEADER
{
	unsigned char CmdType	;
	unsigned short CmdPara	;
	unsigned int command  ;
	unsigned int size	;
	void	h2n() { command = htonl(command); size = htonl(size); CmdPara = htons(CmdPara); }
	void	n2h() { command = ntohl(command); size = ntohl(size); CmdPara = ntohs(CmdPara); }
} ;

//CS返回的录像文件记录
struct SYSTEM_VIDEO_FILE
{
    SYSTEM_VIDEO_FILE()
    { memset( this, 0x00, sizeof(SYSTEM_VIDEO_FILE) ); }
    int           video;  //文件标签
	SGUID		  dvrCode;
	int           channel;
    char	      DevName[NAME_LENGTH_NET];//设备名字
    U8            has_audio  ;
    U16           video_type ;    //0:手动；1：告警；2：定时
    U16           video_quality   ;
	
    DWORD         filelen_low;//文件长度
    DWORD         filelen_hi; //文件长度
    U8            frame_rate;
    U8            video_format;
    U8            resolution;
    char          IP[32] ;
    short         Port;
	
    DATE_INFO     start_date ;
    TIME_INFO     start_time ;
    DATE_INFO     end_date   ;
    TIME_INFO     end_time   ;
	
    void h2n()
    {
		video = htonl( video );
		channel = htonl( channel );
		video_type = htons( video_type );
		video_quality = htons( video_quality );
		start_date.year = htons( start_date.year );
		end_date.year = htons( end_date.year );
		filelen_low = htonl( filelen_low );
		filelen_hi = htonl( filelen_hi );
		Port = htons( Port );
    }
    void n2h()
    {
        h2n();
    }
} ;

/*
 *	 增加字段 FileName 表示需要下载或回放的文件的名字
 */
struct FILE_OPEN_REQUEST_MSG
{
    unsigned char CmdType	;
	unsigned short CmdPara	;
	DWORD		command ;
    DWORD		size	;
	SGUID		dvrID;
	UINT		channel;
    DWORD		video   ; 	
	DATE_INFO   StartDate;
	TIME_INFO   StartTime;
	DATE_INFO   EndDate;
	TIME_INFO   EndTime;

	//	 需要下载或回放的文件的名字
	char		FileName[100];	
};       

typedef struct
{
    unsigned char CmdType	;
	unsigned short CmdPara	;
	DWORD   command ;
    DWORD   size  ;        
    DWORD   reason  ;    
}FILE_OPEN_RESPONSE_MSG ;     

typedef struct
{
    unsigned char CmdType	;
	unsigned short CmdPara	;
	DWORD   command ;
    DWORD   size  ;        
    DWORD   hpos    ;    
    DWORD   lpos    ;
}FILE_SEEK_REQUEST_MSG ;

//struct NET_DATA_PACKET_I64
//{
//	U8	    CmdType;
//	U16	    CmdPara;
//	U32     command  ;
//	U32     size ;
//	U32     position  ;
//} ;


//struct NET_DATA_PACKET_SEEK_I64
//{
//	U8	    CmdType;
//	U16	    CmdPara;
//	U32     command;
//	U32     size ;
//	U32     Pos_high;
//	U32	    Pos_low;
//} ; 


typedef struct
{
    unsigned char CmdType	;
	unsigned short CmdPara	;
	DWORD   command ;
    DWORD   size  ;          
}FILE_SEEK_RESPONSE_MSG ;       

typedef struct 
{
	unsigned char CmdType	;
	unsigned short CmdPara	;
	DWORD   command ;
    DWORD   size  ;        
	DWORD	length;	
}FILE_READ_REQUEST_MSG;  

typedef struct 
{
	unsigned char CmdType	;
	unsigned short CmdPara	;
	DWORD   command ;
    DWORD   size  ;        
	DWORD	Data;	
}FILE_READ_RESPONSE_MSG;  


/*	
 *	按时间回放请求
 */
struct Playback_ByTime_REQUEST_MSG
{
    COMMAND_HEADER header;
	SGUID		dvrID;
	UINT		channel;
	DATE_INFO   StartDate;
	TIME_INFO   StartTime;
	DATE_INFO   EndDate;
	TIME_INFO   EndTime;

	VOID h2n() 
	{
		header.h2n();
		channel = htonl(channel);
		StartDate.h2n();
		EndDate.h2n();
	}

	VOID n2h() 
	{
		header.n2h();
		channel = ntohl(channel);
		StartDate.n2h();
		EndDate.n2h();
	}
};  


// 按时间回放的回应信息
struct SPlayBackByTimeResponseInfo
{
	int nPlayBackLength;
	int nAudio;
	int nVideotype;
	int nQuality;
	int nFrameRate;
	int nVideoFormat;
	int nResolution;
	
	DATE_INFO   StartDate;
	TIME_INFO   StartTime;
	DATE_INFO   EndDate;
	TIME_INFO   EndTime;

	int nFileHeadSize;

	void n2h()
	{
		nPlayBackLength = ntohl(nPlayBackLength);
		nFileHeadSize = ntohl(nFileHeadSize);
		nAudio = ntohl(nAudio);
		nVideotype = ntohl(nVideotype);
		nQuality = ntohl(nQuality);
		nFrameRate = ntohl(nFrameRate);
		nVideoFormat = ntohl(nVideoFormat);
		nResolution = ntohl(nResolution);
		StartDate.n2h();
		EndDate.n2h();
	}
	
	void h2n()
	{
		nPlayBackLength = htonl(nPlayBackLength);
		nFileHeadSize = htonl(nFileHeadSize);
		nAudio = htonl(nAudio);
		nVideotype = htonl(nVideotype);
		nQuality = htonl(nQuality);
		nFrameRate = htonl(nFrameRate);
		nVideoFormat = htonl(nVideoFormat);
		nResolution = htonl(nResolution);
		StartDate.h2n();
		EndDate.h2n();
	}
};

/*	
 *	功能: 开始监视, 依据虚拟视频通道编号
 */
struct SStart_Monitor_ByVirtualVChnIndex
{
	COMMAND_HEADER	header;
	int channel;
	int childstream;
    int transType;	//client------VS之间流传输协议
	
	SStart_Monitor_ByVirtualVChnIndex()
	{
		memset( this, 0x00, sizeof(SStart_Monitor_ByVirtualVChnIndex) );
	}
	
	void h2n() 
	{ 
		header.h2n(); 
		channel = htonl(channel); 
		childstream = htonl(childstream);
		transType = htonl(transType);
	}
	
	void n2h() 
	{ 
		header.n2h(); 
		channel = ntohl(channel); 
		childstream = ntohl(childstream);
		transType = ntohl(transType);
	}
};

//增加字段 DVRType	DVRSubType
//增加字段: DVR的MFR类型，主要由于有些DVR厂商的DVR只有一套SDK，只是调用时，传入不同的类型值
//增加字段: nDVRMaxLinkNum(DVR最大连接限制)、nVSMaxLinkNum(VS最大连接限制)
//增加字段: proxyip proxyport SerialNum
typedef struct Client_Start_Monitor_Direct
{
	COMMAND_HEADER	header;
	char dvrIP[_DVRIPLen];
	int	 dvrPort;
	char userName[32];
	char pwd[32];
	int channel;
	int childstream;
	int	udp_port;//用户的UDP接收端口
	int dvrtype;
    int dvrsubtype;
	////DVR的MFR类型，主要由于有些DVR厂商的DVR只有一套SDK，只是调用时，传入不同的类型值
	unsigned int u32DVRMFRType;	
    int transType;	//client------VS之间流传输协议
	unsigned int u32DVRMaxLinkNum; 
	unsigned int u32VSMaxLinkNum; 
	char sSerialNum[_DVRSerialNumLen]; 
	char sProxyIP[32];
	int nProxyPort; 
	
	Client_Start_Monitor_Direct() { memset( this, 0x00, sizeof(Client_Start_Monitor_Direct) ); }
	
	void h2n() 
	{ 
		header.h2n(); 

		dvrPort = htonl(dvrPort); 
		channel = htonl(channel); 
		childstream = htonl(childstream);
		udp_port = htonl(udp_port);
		dvrtype = htonl(dvrtype); 
		dvrsubtype = htonl(dvrsubtype);
		transType = htonl(transType);
		u32DVRMFRType = htonl(u32DVRMFRType); 
		u32DVRMaxLinkNum = htonl(u32DVRMaxLinkNum); 
		u32VSMaxLinkNum = htonl(u32VSMaxLinkNum); 
		nProxyPort = htonl(nProxyPort); 
	}
	
	void n2h() 
	{ 
		h2n();
	}
}CLIENT_START_MONITOR_DIRECT;

typedef struct
{
	COMMAND_HEADER	header;
	int				dvrID;
	int				channel;
}CLIENT_STOP_MONITOR;


struct CLIENT_START_MONITOR_RESPONSE
{
	COMMAND_HEADER	header;
	INT				reason;
	char            mcast_IP[32];
    unsigned short  mcast_port;
    int             streamheadsize;//流头大小
	
	void          h2n()
    {
		header.h2n();
		reason = htonl( reason );
		mcast_port = htons( mcast_port );
		streamheadsize = htonl(streamheadsize);
    }
	
    void          n2h()
    {
        h2n();
    }

};


//1. 增加属性: MaxNumOfConnect, 最大连接限制
//功能: VS的信息, 其是VS信息链的组成单元
struct SVSChainUnit
{
	char VSIP[16];
	int  nVSTCPPort;
	int nMaxNumOfConnect; //最大连接限制 
	
	void h2n()
    {
		nVSTCPPort = htonl( nVSTCPPort );
		nMaxNumOfConnect = htonl( nMaxNumOfConnect ); 
    }
	
    void n2h()
    {
        nVSTCPPort = ntohl( nVSTCPPort );
		nMaxNumOfConnect = ntohl( nMaxNumOfConnect ); 
    }
};

#pragma pack()

#endif // _STRUCT_TCPSERV_H
