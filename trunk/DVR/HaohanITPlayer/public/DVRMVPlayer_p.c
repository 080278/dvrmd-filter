

/* this ALWAYS GENERATED file contains the proxy stub code */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Thu Aug 18 15:48:25 2011
 */
/* Compiler settings for public\DVRMVPlayer.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#if !defined(_M_IA64) && !defined(_M_AMD64)


#pragma warning( disable: 4049 )  /* more than 64k source lines */
#if _MSC_VER >= 1200
#pragma warning(push)
#endif

#pragma warning( disable: 4211 )  /* redefine extern to static */
#pragma warning( disable: 4232 )  /* dllimport identity*/
#pragma warning( disable: 4024 )  /* array to pointer mapping*/
#pragma warning( disable: 4152 )  /* function/data pointer conversion in expression */
#pragma warning( disable: 4100 ) /* unreferenced arguments in x86 call */

#pragma optimize("", off ) 

#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 440
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif /* __RPCPROXY_H_VERSION__ */


#include "DVRMVPlayer.h"

#define TYPE_FORMAT_STRING_SIZE   133                               
#define PROC_FORMAT_STRING_SIZE   1931                              
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   1            

typedef struct _DVRMVPlayer_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } DVRMVPlayer_MIDL_TYPE_FORMAT_STRING;

typedef struct _DVRMVPlayer_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } DVRMVPlayer_MIDL_PROC_FORMAT_STRING;

typedef struct _DVRMVPlayer_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } DVRMVPlayer_MIDL_EXPR_FORMAT_STRING;


static const RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const DVRMVPlayer_MIDL_TYPE_FORMAT_STRING DVRMVPlayer__MIDL_TypeFormatString;
extern const DVRMVPlayer_MIDL_PROC_FORMAT_STRING DVRMVPlayer__MIDL_ProcFormatString;
extern const DVRMVPlayer_MIDL_EXPR_FORMAT_STRING DVRMVPlayer__MIDL_ExprFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IDVRMVControls_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IDVRMVControls_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IDVRMVSettings_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IDVRMVSettings_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IDVRMVMedia_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IDVRMVMedia_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IDVRMVPlayer_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IDVRMVPlayer_ProxyInfo;


extern const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ];

#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT40_OR_LATER)
#error You need Windows NT 4.0 or later to run this stub because it uses these features:
#error   -Oif or -Oicf, [wire_marshal] or [user_marshal] attribute, float, double or hyper in -Oif or -Oicf, more than 32 methods in the interface.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will fail with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const DVRMVPlayer_MIDL_PROC_FORMAT_STRING DVRMVPlayer__MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure play */

			0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x7 ),	/* 7 */
/*  8 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 10 */	NdrFcShort( 0x0 ),	/* 0 */
/* 12 */	NdrFcShort( 0x8 ),	/* 8 */
/* 14 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 16 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 18 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 20 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure stop */

/* 22 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 24 */	NdrFcLong( 0x0 ),	/* 0 */
/* 28 */	NdrFcShort( 0x8 ),	/* 8 */
/* 30 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 32 */	NdrFcShort( 0x0 ),	/* 0 */
/* 34 */	NdrFcShort( 0x8 ),	/* 8 */
/* 36 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 38 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 40 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 42 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure pause */

/* 44 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 46 */	NdrFcLong( 0x0 ),	/* 0 */
/* 50 */	NdrFcShort( 0x9 ),	/* 9 */
/* 52 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 54 */	NdrFcShort( 0x0 ),	/* 0 */
/* 56 */	NdrFcShort( 0x8 ),	/* 8 */
/* 58 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 60 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 62 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 64 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure fastForward */

/* 66 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 68 */	NdrFcLong( 0x0 ),	/* 0 */
/* 72 */	NdrFcShort( 0xa ),	/* 10 */
/* 74 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 76 */	NdrFcShort( 0x0 ),	/* 0 */
/* 78 */	NdrFcShort( 0x8 ),	/* 8 */
/* 80 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 82 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 84 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 86 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure fastReverse */

/* 88 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 90 */	NdrFcLong( 0x0 ),	/* 0 */
/* 94 */	NdrFcShort( 0xb ),	/* 11 */
/* 96 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 98 */	NdrFcShort( 0x0 ),	/* 0 */
/* 100 */	NdrFcShort( 0x8 ),	/* 8 */
/* 102 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 104 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 106 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 108 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_currentPosition */

/* 110 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 112 */	NdrFcLong( 0x0 ),	/* 0 */
/* 116 */	NdrFcShort( 0xc ),	/* 12 */
/* 118 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 120 */	NdrFcShort( 0x0 ),	/* 0 */
/* 122 */	NdrFcShort( 0x2c ),	/* 44 */
/* 124 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pdCurrentPosition */

/* 126 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 128 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 130 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 132 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 134 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 136 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_currentPosition */

/* 138 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 140 */	NdrFcLong( 0x0 ),	/* 0 */
/* 144 */	NdrFcShort( 0xd ),	/* 13 */
/* 146 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 148 */	NdrFcShort( 0x10 ),	/* 16 */
/* 150 */	NdrFcShort( 0x8 ),	/* 8 */
/* 152 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter dCurrentPosition */

/* 154 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 156 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 158 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 160 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 162 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 164 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_currentPositionString */

/* 166 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 168 */	NdrFcLong( 0x0 ),	/* 0 */
/* 172 */	NdrFcShort( 0xe ),	/* 14 */
/* 174 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 176 */	NdrFcShort( 0x0 ),	/* 0 */
/* 178 */	NdrFcShort( 0x8 ),	/* 8 */
/* 180 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pbstrCurrentPosition */

/* 182 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 184 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 186 */	NdrFcShort( 0x22 ),	/* Type Offset=34 */

	/* Return value */

/* 188 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 190 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 192 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_isAvailable */

/* 194 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 196 */	NdrFcLong( 0x0 ),	/* 0 */
/* 200 */	NdrFcShort( 0xf ),	/* 15 */
/* 202 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 204 */	NdrFcShort( 0x0 ),	/* 0 */
/* 206 */	NdrFcShort( 0x22 ),	/* 34 */
/* 208 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter bstrItem */

/* 210 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 212 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 214 */	NdrFcShort( 0x30 ),	/* Type Offset=48 */

	/* Parameter pIsAvailable */

/* 216 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 218 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 220 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 222 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 224 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 226 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_mute */

/* 228 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 230 */	NdrFcLong( 0x0 ),	/* 0 */
/* 234 */	NdrFcShort( 0x7 ),	/* 7 */
/* 236 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 238 */	NdrFcShort( 0x0 ),	/* 0 */
/* 240 */	NdrFcShort( 0x22 ),	/* 34 */
/* 242 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pfMute */

/* 244 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 246 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 248 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 250 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 252 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 254 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_mute */

/* 256 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 258 */	NdrFcLong( 0x0 ),	/* 0 */
/* 262 */	NdrFcShort( 0x8 ),	/* 8 */
/* 264 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 266 */	NdrFcShort( 0x6 ),	/* 6 */
/* 268 */	NdrFcShort( 0x8 ),	/* 8 */
/* 270 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter fMute */

/* 272 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 274 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 276 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 278 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 280 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 282 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_volume */

/* 284 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 286 */	NdrFcLong( 0x0 ),	/* 0 */
/* 290 */	NdrFcShort( 0x9 ),	/* 9 */
/* 292 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 294 */	NdrFcShort( 0x0 ),	/* 0 */
/* 296 */	NdrFcShort( 0x24 ),	/* 36 */
/* 298 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter plVolume */

/* 300 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 302 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 304 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 306 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 308 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 310 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_volume */

/* 312 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 314 */	NdrFcLong( 0x0 ),	/* 0 */
/* 318 */	NdrFcShort( 0xa ),	/* 10 */
/* 320 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 322 */	NdrFcShort( 0x8 ),	/* 8 */
/* 324 */	NdrFcShort( 0x8 ),	/* 8 */
/* 326 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter lVolume */

/* 328 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 330 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 332 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 334 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 336 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 338 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_imageSourceWidth */

/* 340 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 342 */	NdrFcLong( 0x0 ),	/* 0 */
/* 346 */	NdrFcShort( 0x7 ),	/* 7 */
/* 348 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 350 */	NdrFcShort( 0x0 ),	/* 0 */
/* 352 */	NdrFcShort( 0x24 ),	/* 36 */
/* 354 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pWidth */

/* 356 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 358 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 360 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 362 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 364 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 366 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_imageSourceHeight */

/* 368 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 370 */	NdrFcLong( 0x0 ),	/* 0 */
/* 374 */	NdrFcShort( 0x8 ),	/* 8 */
/* 376 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 378 */	NdrFcShort( 0x0 ),	/* 0 */
/* 380 */	NdrFcShort( 0x24 ),	/* 36 */
/* 382 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pHeight */

/* 384 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 386 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 388 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 390 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 392 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 394 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_duration */

/* 396 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 398 */	NdrFcLong( 0x0 ),	/* 0 */
/* 402 */	NdrFcShort( 0x9 ),	/* 9 */
/* 404 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 406 */	NdrFcShort( 0x0 ),	/* 0 */
/* 408 */	NdrFcShort( 0x2c ),	/* 44 */
/* 410 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pDuration */

/* 412 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 414 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 416 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 418 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 420 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 422 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_durationString */

/* 424 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 426 */	NdrFcLong( 0x0 ),	/* 0 */
/* 430 */	NdrFcShort( 0xa ),	/* 10 */
/* 432 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 434 */	NdrFcShort( 0x0 ),	/* 0 */
/* 436 */	NdrFcShort( 0x8 ),	/* 8 */
/* 438 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pbstrDuration */

/* 440 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 442 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 444 */	NdrFcShort( 0x22 ),	/* Type Offset=34 */

	/* Return value */

/* 446 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 448 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 450 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_URL */

/* 452 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 454 */	NdrFcLong( 0x0 ),	/* 0 */
/* 458 */	NdrFcShort( 0x7 ),	/* 7 */
/* 460 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 462 */	NdrFcShort( 0x0 ),	/* 0 */
/* 464 */	NdrFcShort( 0x8 ),	/* 8 */
/* 466 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pbstrURL */

/* 468 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 470 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 472 */	NdrFcShort( 0x22 ),	/* Type Offset=34 */

	/* Return value */

/* 474 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 476 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 478 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_URL */

/* 480 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 482 */	NdrFcLong( 0x0 ),	/* 0 */
/* 486 */	NdrFcShort( 0x8 ),	/* 8 */
/* 488 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 490 */	NdrFcShort( 0x0 ),	/* 0 */
/* 492 */	NdrFcShort( 0x8 ),	/* 8 */
/* 494 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter bstrURL */

/* 496 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 498 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 500 */	NdrFcShort( 0x30 ),	/* Type Offset=48 */

	/* Return value */

/* 502 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 504 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 506 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_fullScreen */

/* 508 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 510 */	NdrFcLong( 0x0 ),	/* 0 */
/* 514 */	NdrFcShort( 0x9 ),	/* 9 */
/* 516 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 518 */	NdrFcShort( 0x0 ),	/* 0 */
/* 520 */	NdrFcShort( 0x22 ),	/* 34 */
/* 522 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pbFullScreen */

/* 524 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 526 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 528 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 530 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 532 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 534 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_fullScreen */

/* 536 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 538 */	NdrFcLong( 0x0 ),	/* 0 */
/* 542 */	NdrFcShort( 0xa ),	/* 10 */
/* 544 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 546 */	NdrFcShort( 0x6 ),	/* 6 */
/* 548 */	NdrFcShort( 0x8 ),	/* 8 */
/* 550 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter bFullScreen */

/* 552 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 554 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 556 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 558 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 560 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 562 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_uiMode */

/* 564 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 566 */	NdrFcLong( 0x0 ),	/* 0 */
/* 570 */	NdrFcShort( 0xb ),	/* 11 */
/* 572 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 574 */	NdrFcShort( 0x0 ),	/* 0 */
/* 576 */	NdrFcShort( 0x8 ),	/* 8 */
/* 578 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pbstrMode */

/* 580 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 582 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 584 */	NdrFcShort( 0x22 ),	/* Type Offset=34 */

	/* Return value */

/* 586 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 588 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 590 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_uiMode */

/* 592 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 594 */	NdrFcLong( 0x0 ),	/* 0 */
/* 598 */	NdrFcShort( 0xc ),	/* 12 */
/* 600 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 602 */	NdrFcShort( 0x0 ),	/* 0 */
/* 604 */	NdrFcShort( 0x8 ),	/* 8 */
/* 606 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter bstrMode */

/* 608 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 610 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 612 */	NdrFcShort( 0x30 ),	/* Type Offset=48 */

	/* Return value */

/* 614 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 616 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 618 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_status */

/* 620 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 622 */	NdrFcLong( 0x0 ),	/* 0 */
/* 626 */	NdrFcShort( 0xd ),	/* 13 */
/* 628 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 630 */	NdrFcShort( 0x0 ),	/* 0 */
/* 632 */	NdrFcShort( 0x8 ),	/* 8 */
/* 634 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pbstrStatus */

/* 636 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 638 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 640 */	NdrFcShort( 0x22 ),	/* Type Offset=34 */

	/* Return value */

/* 642 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 644 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 646 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_playState */

/* 648 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 650 */	NdrFcLong( 0x0 ),	/* 0 */
/* 654 */	NdrFcShort( 0xe ),	/* 14 */
/* 656 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 658 */	NdrFcShort( 0x0 ),	/* 0 */
/* 660 */	NdrFcShort( 0x24 ),	/* 36 */
/* 662 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter plState */

/* 664 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 666 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 668 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 670 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 672 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 674 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_versionInfo */

/* 676 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 678 */	NdrFcLong( 0x0 ),	/* 0 */
/* 682 */	NdrFcShort( 0xf ),	/* 15 */
/* 684 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 686 */	NdrFcShort( 0x0 ),	/* 0 */
/* 688 */	NdrFcShort( 0x8 ),	/* 8 */
/* 690 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pbstrVersionInfo */

/* 692 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 694 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 696 */	NdrFcShort( 0x22 ),	/* Type Offset=34 */

	/* Return value */

/* 698 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 700 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 702 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure close */

/* 704 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 706 */	NdrFcLong( 0x0 ),	/* 0 */
/* 710 */	NdrFcShort( 0x10 ),	/* 16 */
/* 712 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 714 */	NdrFcShort( 0x0 ),	/* 0 */
/* 716 */	NdrFcShort( 0x8 ),	/* 8 */
/* 718 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 720 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 722 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 724 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_controls */

/* 726 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 728 */	NdrFcLong( 0x0 ),	/* 0 */
/* 732 */	NdrFcShort( 0x11 ),	/* 17 */
/* 734 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 736 */	NdrFcShort( 0x0 ),	/* 0 */
/* 738 */	NdrFcShort( 0x8 ),	/* 8 */
/* 740 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter ppControl */

/* 742 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 744 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 746 */	NdrFcShort( 0x42 ),	/* Type Offset=66 */

	/* Return value */

/* 748 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 750 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 752 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure play */

/* 754 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 756 */	NdrFcLong( 0x0 ),	/* 0 */
/* 760 */	NdrFcShort( 0x12 ),	/* 18 */
/* 762 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 764 */	NdrFcShort( 0x0 ),	/* 0 */
/* 766 */	NdrFcShort( 0x8 ),	/* 8 */
/* 768 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 770 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 772 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 774 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure stop */

/* 776 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 778 */	NdrFcLong( 0x0 ),	/* 0 */
/* 782 */	NdrFcShort( 0x13 ),	/* 19 */
/* 784 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 786 */	NdrFcShort( 0x0 ),	/* 0 */
/* 788 */	NdrFcShort( 0x8 ),	/* 8 */
/* 790 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 792 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 794 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 796 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure pause */

/* 798 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 800 */	NdrFcLong( 0x0 ),	/* 0 */
/* 804 */	NdrFcShort( 0x14 ),	/* 20 */
/* 806 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 808 */	NdrFcShort( 0x0 ),	/* 0 */
/* 810 */	NdrFcShort( 0x8 ),	/* 8 */
/* 812 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 814 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 816 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 818 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure fastForward */

/* 820 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 822 */	NdrFcLong( 0x0 ),	/* 0 */
/* 826 */	NdrFcShort( 0x15 ),	/* 21 */
/* 828 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 830 */	NdrFcShort( 0x0 ),	/* 0 */
/* 832 */	NdrFcShort( 0x8 ),	/* 8 */
/* 834 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 836 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 838 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 840 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure fastReverse */

/* 842 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 844 */	NdrFcLong( 0x0 ),	/* 0 */
/* 848 */	NdrFcShort( 0x16 ),	/* 22 */
/* 850 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 852 */	NdrFcShort( 0x0 ),	/* 0 */
/* 854 */	NdrFcShort( 0x8 ),	/* 8 */
/* 856 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 858 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 860 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 862 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_currentPosition */

/* 864 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 866 */	NdrFcLong( 0x0 ),	/* 0 */
/* 870 */	NdrFcShort( 0x17 ),	/* 23 */
/* 872 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 874 */	NdrFcShort( 0x0 ),	/* 0 */
/* 876 */	NdrFcShort( 0x2c ),	/* 44 */
/* 878 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pdCurrentPosition */

/* 880 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 882 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 884 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 886 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 888 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 890 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_currentPosition */

/* 892 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 894 */	NdrFcLong( 0x0 ),	/* 0 */
/* 898 */	NdrFcShort( 0x18 ),	/* 24 */
/* 900 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 902 */	NdrFcShort( 0x10 ),	/* 16 */
/* 904 */	NdrFcShort( 0x8 ),	/* 8 */
/* 906 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter dCurrentPosition */

/* 908 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 910 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 912 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 914 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 916 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 918 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_currentPositionString */

/* 920 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 922 */	NdrFcLong( 0x0 ),	/* 0 */
/* 926 */	NdrFcShort( 0x19 ),	/* 25 */
/* 928 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 930 */	NdrFcShort( 0x0 ),	/* 0 */
/* 932 */	NdrFcShort( 0x8 ),	/* 8 */
/* 934 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pbstrCurrentPosition */

/* 936 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 938 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 940 */	NdrFcShort( 0x22 ),	/* Type Offset=34 */

	/* Return value */

/* 942 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 944 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 946 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_isAvailable */

/* 948 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 950 */	NdrFcLong( 0x0 ),	/* 0 */
/* 954 */	NdrFcShort( 0x1a ),	/* 26 */
/* 956 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 958 */	NdrFcShort( 0x0 ),	/* 0 */
/* 960 */	NdrFcShort( 0x22 ),	/* 34 */
/* 962 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter bstrItem */

/* 964 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 966 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 968 */	NdrFcShort( 0x30 ),	/* Type Offset=48 */

	/* Parameter pIsAvailable */

/* 970 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 972 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 974 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 976 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 978 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 980 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_settings */

/* 982 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 984 */	NdrFcLong( 0x0 ),	/* 0 */
/* 988 */	NdrFcShort( 0x1b ),	/* 27 */
/* 990 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 992 */	NdrFcShort( 0x0 ),	/* 0 */
/* 994 */	NdrFcShort( 0x8 ),	/* 8 */
/* 996 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter ppSettings */

/* 998 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1000 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1002 */	NdrFcShort( 0x58 ),	/* Type Offset=88 */

	/* Return value */

/* 1004 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1006 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1008 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_mute */

/* 1010 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1012 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1016 */	NdrFcShort( 0x1c ),	/* 28 */
/* 1018 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1020 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1022 */	NdrFcShort( 0x22 ),	/* 34 */
/* 1024 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pfMute */

/* 1026 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1028 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1030 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 1032 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1034 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1036 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_mute */

/* 1038 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1040 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1044 */	NdrFcShort( 0x1d ),	/* 29 */
/* 1046 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1048 */	NdrFcShort( 0x6 ),	/* 6 */
/* 1050 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1052 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter fMute */

/* 1054 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1056 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1058 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 1060 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1062 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1064 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_volume */

/* 1066 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1068 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1072 */	NdrFcShort( 0x1e ),	/* 30 */
/* 1074 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1076 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1078 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1080 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter plVolume */

/* 1082 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1084 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1086 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1088 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1090 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1092 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_volume */

/* 1094 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1096 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1100 */	NdrFcShort( 0x1f ),	/* 31 */
/* 1102 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1104 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1106 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1108 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter lVolume */

/* 1110 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1112 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1114 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1116 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1118 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1120 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_currentMedia */

/* 1122 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1124 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1128 */	NdrFcShort( 0x20 ),	/* 32 */
/* 1130 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1132 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1134 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1136 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter ppMedia */

/* 1138 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1140 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1142 */	NdrFcShort( 0x6e ),	/* Type Offset=110 */

	/* Return value */

/* 1144 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1146 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1148 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_imageSourceWidth */

/* 1150 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1152 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1156 */	NdrFcShort( 0x21 ),	/* 33 */
/* 1158 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1160 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1162 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1164 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pWidth */

/* 1166 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1168 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1170 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1172 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1174 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1176 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_imageSourceHeight */

/* 1178 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1180 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1184 */	NdrFcShort( 0x22 ),	/* 34 */
/* 1186 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1188 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1190 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1192 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pHeight */

/* 1194 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1196 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1198 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1200 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1202 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1204 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_duration */

/* 1206 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1208 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1212 */	NdrFcShort( 0x23 ),	/* 35 */
/* 1214 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1216 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1218 */	NdrFcShort( 0x2c ),	/* 44 */
/* 1220 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pDuration */

/* 1222 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1224 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1226 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 1228 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1230 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1232 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_durationString */

/* 1234 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1236 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1240 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1242 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1244 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1246 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1248 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pbstrDuration */

/* 1250 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1252 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1254 */	NdrFcShort( 0x22 ),	/* Type Offset=34 */

	/* Return value */

/* 1256 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1258 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1260 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure OpenFile */

/* 1262 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1264 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1268 */	NdrFcShort( 0x25 ),	/* 37 */
/* 1270 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1272 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1274 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1276 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter bstrMediaFile */

/* 1278 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1280 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1282 */	NdrFcShort( 0x30 ),	/* Type Offset=48 */

	/* Return value */

/* 1284 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1286 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1288 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Login */

/* 1290 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1292 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1296 */	NdrFcShort( 0x26 ),	/* 38 */
/* 1298 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 1300 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1302 */	NdrFcShort( 0x22 ),	/* 34 */
/* 1304 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x6,		/* 6 */

	/* Parameter bstrUsername */

/* 1306 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1308 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1310 */	NdrFcShort( 0x30 ),	/* Type Offset=48 */

	/* Parameter bstrPassword */

/* 1312 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1314 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1316 */	NdrFcShort( 0x30 ),	/* Type Offset=48 */

	/* Parameter bstrIP */

/* 1318 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1320 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1322 */	NdrFcShort( 0x30 ),	/* Type Offset=48 */

	/* Parameter lPort */

/* 1324 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1326 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1328 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pRet */

/* 1330 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1332 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1334 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 1336 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1338 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 1340 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Logout */

/* 1342 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1344 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1348 */	NdrFcShort( 0x27 ),	/* 39 */
/* 1350 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1352 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1354 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1356 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 1358 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1360 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1362 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetMediaServer */

/* 1364 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1366 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1370 */	NdrFcShort( 0x28 ),	/* 40 */
/* 1372 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1374 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1376 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1378 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter bstrMediaServerIP */

/* 1380 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1382 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1384 */	NdrFcShort( 0x30 ),	/* Type Offset=48 */

	/* Parameter lPort */

/* 1386 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1388 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1390 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1392 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1394 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1396 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetMediaServer */

/* 1398 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1400 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1404 */	NdrFcShort( 0x29 ),	/* 41 */
/* 1406 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1408 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1410 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1412 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x3,		/* 3 */

	/* Parameter bstrMediaServerIP */

/* 1414 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1416 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1418 */	NdrFcShort( 0x22 ),	/* Type Offset=34 */

	/* Parameter lPort */

/* 1420 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1422 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1424 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1426 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1428 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1430 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure StartMonitor */

/* 1432 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1434 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1438 */	NdrFcShort( 0x2a ),	/* 42 */
/* 1440 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1442 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1444 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1446 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter lWndNum */

/* 1448 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1450 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1452 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1454 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1456 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1458 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure StopMonitor */

/* 1460 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1462 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1466 */	NdrFcShort( 0x2b ),	/* 43 */
/* 1468 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1470 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1472 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1474 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 1476 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1478 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1480 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure CapPic */

/* 1482 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1484 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1488 */	NdrFcShort( 0x2c ),	/* 44 */
/* 1490 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1492 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1494 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1496 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pCapPicPath */

/* 1498 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1500 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1502 */	NdrFcShort( 0x22 ),	/* Type Offset=34 */

	/* Return value */

/* 1504 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1506 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1508 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetCapturePath */

/* 1510 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1512 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1516 */	NdrFcShort( 0x2d ),	/* 45 */
/* 1518 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1520 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1522 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1524 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pbstrCapFolder */

/* 1526 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1528 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1530 */	NdrFcShort( 0x22 ),	/* Type Offset=34 */

	/* Return value */

/* 1532 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1534 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1536 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetCapturePath */

/* 1538 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1540 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1544 */	NdrFcShort( 0x2e ),	/* 46 */
/* 1546 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1548 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1550 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1552 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter bstrCapFolder */

/* 1554 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1556 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1558 */	NdrFcShort( 0x30 ),	/* Type Offset=48 */

	/* Return value */

/* 1560 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1562 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1564 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ShowMetaData */

/* 1566 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1568 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1572 */	NdrFcShort( 0x2f ),	/* 47 */
/* 1574 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1576 */	NdrFcShort( 0x6 ),	/* 6 */
/* 1578 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1580 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter bShow */

/* 1582 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1584 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1586 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 1588 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1590 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1592 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetWndChannel */

/* 1594 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1596 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1600 */	NdrFcShort( 0x30 ),	/* 48 */
/* 1602 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1604 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1606 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1608 */	0x4,		/* Oi2 Flags:  has return, */
			0x3,		/* 3 */

	/* Parameter lWndIndex */

/* 1610 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1612 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1614 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter lChannelIndex */

/* 1616 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1618 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1620 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1622 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1624 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1626 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetFullScreen */

/* 1628 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1630 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1634 */	NdrFcShort( 0x31 ),	/* 49 */
/* 1636 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1638 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1640 */	NdrFcShort( 0x22 ),	/* 34 */
/* 1642 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pbFullScreen */

/* 1644 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1646 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1648 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 1650 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1652 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1654 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetFullScreen */

/* 1656 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1658 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1662 */	NdrFcShort( 0x32 ),	/* 50 */
/* 1664 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1666 */	NdrFcShort( 0x6 ),	/* 6 */
/* 1668 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1670 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter bFullScreen */

/* 1672 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1674 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1676 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 1678 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1680 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1682 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure AddFileToPlayList */

/* 1684 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1686 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1690 */	NdrFcShort( 0x33 ),	/* 51 */
/* 1692 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1694 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1696 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1698 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter bstrFile */

/* 1700 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1702 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1704 */	NdrFcShort( 0x30 ),	/* Type Offset=48 */

	/* Return value */

/* 1706 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1708 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1710 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ClosePlayList */

/* 1712 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1714 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1718 */	NdrFcShort( 0x34 ),	/* 52 */
/* 1720 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1722 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1724 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1726 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 1728 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1730 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1732 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure PlayNextFile */

/* 1734 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1736 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1740 */	NdrFcShort( 0x35 ),	/* 53 */
/* 1742 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1744 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1746 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1748 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 1750 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1752 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1754 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure StartPlayback */

/* 1756 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1758 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1762 */	NdrFcShort( 0x36 ),	/* 54 */
/* 1764 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 1766 */	NdrFcShort( 0x28 ),	/* 40 */
/* 1768 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1770 */	0x4,		/* Oi2 Flags:  has return, */
			0x4,		/* 4 */

	/* Parameter lStartTime */

/* 1772 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1774 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1776 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Parameter lEndTime */

/* 1778 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1780 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1782 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Parameter lChannel */

/* 1784 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1786 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1788 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1790 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1792 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 1794 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure StopPlayback */

/* 1796 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1798 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1802 */	NdrFcShort( 0x37 ),	/* 55 */
/* 1804 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1806 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1808 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1810 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 1812 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1814 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1816 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetDuration */

/* 1818 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1820 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1824 */	NdrFcShort( 0x38 ),	/* 56 */
/* 1826 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1828 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1830 */	NdrFcShort( 0x2c ),	/* 44 */
/* 1832 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pDuration */

/* 1834 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1836 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1838 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 1840 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1842 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1844 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetCurrentPosition */

/* 1846 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1848 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1852 */	NdrFcShort( 0x39 ),	/* 57 */
/* 1854 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1856 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1858 */	NdrFcShort( 0x2c ),	/* 44 */
/* 1860 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pdCurrentPosition */

/* 1862 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1864 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1866 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 1868 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1870 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1872 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetDurationString */

/* 1874 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1876 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1880 */	NdrFcShort( 0x3a ),	/* 58 */
/* 1882 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1884 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1886 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1888 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pbstrDuration */

/* 1890 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1892 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1894 */	NdrFcShort( 0x22 ),	/* Type Offset=34 */

	/* Return value */

/* 1896 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1898 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1900 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetCurrentPositionString */

/* 1902 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1904 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1908 */	NdrFcShort( 0x3b ),	/* 59 */
/* 1910 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1912 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1914 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1916 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pbstrCurrentPosition */

/* 1918 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1920 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1922 */	NdrFcShort( 0x22 ),	/* Type Offset=34 */

	/* Return value */

/* 1924 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1926 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1928 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const DVRMVPlayer_MIDL_TYPE_FORMAT_STRING DVRMVPlayer__MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/*  4 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/*  6 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/*  8 */	NdrFcShort( 0x1a ),	/* Offset= 26 (34) */
/* 10 */	
			0x13, 0x0,	/* FC_OP */
/* 12 */	NdrFcShort( 0xc ),	/* Offset= 12 (24) */
/* 14 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 16 */	NdrFcShort( 0x2 ),	/* 2 */
/* 18 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 20 */	NdrFcShort( 0xfffc ),	/* -4 */
/* 22 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 24 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 26 */	NdrFcShort( 0x8 ),	/* 8 */
/* 28 */	NdrFcShort( 0xfff2 ),	/* Offset= -14 (14) */
/* 30 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 32 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 34 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 36 */	NdrFcShort( 0x0 ),	/* 0 */
/* 38 */	NdrFcShort( 0x4 ),	/* 4 */
/* 40 */	NdrFcShort( 0x0 ),	/* 0 */
/* 42 */	NdrFcShort( 0xffe0 ),	/* Offset= -32 (10) */
/* 44 */	
			0x12, 0x0,	/* FC_UP */
/* 46 */	NdrFcShort( 0xffea ),	/* Offset= -22 (24) */
/* 48 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 50 */	NdrFcShort( 0x0 ),	/* 0 */
/* 52 */	NdrFcShort( 0x4 ),	/* 4 */
/* 54 */	NdrFcShort( 0x0 ),	/* 0 */
/* 56 */	NdrFcShort( 0xfff4 ),	/* Offset= -12 (44) */
/* 58 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 60 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 62 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 64 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 66 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 68 */	NdrFcShort( 0x2 ),	/* Offset= 2 (70) */
/* 70 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 72 */	NdrFcLong( 0x583c0343 ),	/* 1480328003 */
/* 76 */	NdrFcShort( 0x5d2 ),	/* 1490 */
/* 78 */	NdrFcShort( 0x4c3a ),	/* 19514 */
/* 80 */	0x92,		/* 146 */
			0x82,		/* 130 */
/* 82 */	0xfc,		/* 252 */
			0x14,		/* 20 */
/* 84 */	0xc8,		/* 200 */
			0x39,		/* 57 */
/* 86 */	0x6e,		/* 110 */
			0x4e,		/* 78 */
/* 88 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 90 */	NdrFcShort( 0x2 ),	/* Offset= 2 (92) */
/* 92 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 94 */	NdrFcLong( 0x7d45535f ),	/* 2101695327 */
/* 98 */	NdrFcShort( 0x3ece ),	/* 16078 */
/* 100 */	NdrFcShort( 0x4bd7 ),	/* 19415 */
/* 102 */	0xa8,		/* 168 */
			0x68,		/* 104 */
/* 104 */	0xc1,		/* 193 */
			0xb2,		/* 178 */
/* 106 */	0xa8,		/* 168 */
			0x12,		/* 18 */
/* 108 */	0x8a,		/* 138 */
			0x76,		/* 118 */
/* 110 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 112 */	NdrFcShort( 0x2 ),	/* Offset= 2 (114) */
/* 114 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 116 */	NdrFcLong( 0x842d4d89 ),	/* -2077405815 */
/* 120 */	NdrFcShort( 0xdb49 ),	/* -9399 */
/* 122 */	NdrFcShort( 0x43d9 ),	/* 17369 */
/* 124 */	0x8a,		/* 138 */
			0xa6,		/* 166 */
/* 126 */	0x44,		/* 68 */
			0xd4,		/* 212 */
/* 128 */	0x48,		/* 72 */
			0x3f,		/* 63 */
/* 130 */	0xbf,		/* 191 */
			0xc3,		/* 195 */

			0x0
        }
    };

static const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ] = 
        {
            
            {
            BSTR_UserSize
            ,BSTR_UserMarshal
            ,BSTR_UserUnmarshal
            ,BSTR_UserFree
            }

        };



/* Standard interface: __MIDL_itf_DVRMVPlayer_0000_0000, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}} */


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IDispatch, ver. 0.0,
   GUID={0x00020400,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IDVRMVControls, ver. 0.0,
   GUID={0x583C0343,0x05D2,0x4c3a,{0x92,0x82,0xFC,0x14,0xC8,0x39,0x6E,0x4E}} */

#pragma code_seg(".orpc")
static const unsigned short IDVRMVControls_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0,
    22,
    44,
    66,
    88,
    110,
    138,
    166,
    194
    };

static const MIDL_STUBLESS_PROXY_INFO IDVRMVControls_ProxyInfo =
    {
    &Object_StubDesc,
    DVRMVPlayer__MIDL_ProcFormatString.Format,
    &IDVRMVControls_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IDVRMVControls_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    DVRMVPlayer__MIDL_ProcFormatString.Format,
    &IDVRMVControls_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(16) _IDVRMVControlsProxyVtbl = 
{
    &IDVRMVControls_ProxyInfo,
    &IID_IDVRMVControls,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IDVRMVControls::play */ ,
    (void *) (INT_PTR) -1 /* IDVRMVControls::stop */ ,
    (void *) (INT_PTR) -1 /* IDVRMVControls::pause */ ,
    (void *) (INT_PTR) -1 /* IDVRMVControls::fastForward */ ,
    (void *) (INT_PTR) -1 /* IDVRMVControls::fastReverse */ ,
    (void *) (INT_PTR) -1 /* IDVRMVControls::get_currentPosition */ ,
    (void *) (INT_PTR) -1 /* IDVRMVControls::put_currentPosition */ ,
    (void *) (INT_PTR) -1 /* IDVRMVControls::get_currentPositionString */ ,
    (void *) (INT_PTR) -1 /* IDVRMVControls::get_isAvailable */
};


static const PRPC_STUB_FUNCTION IDVRMVControls_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IDVRMVControlsStubVtbl =
{
    &IID_IDVRMVControls,
    &IDVRMVControls_ServerInfo,
    16,
    &IDVRMVControls_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IDVRMVSettings, ver. 0.0,
   GUID={0x7D45535F,0x3ECE,0x4bd7,{0xA8,0x68,0xC1,0xB2,0xA8,0x12,0x8A,0x76}} */

#pragma code_seg(".orpc")
static const unsigned short IDVRMVSettings_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    228,
    256,
    284,
    312
    };

static const MIDL_STUBLESS_PROXY_INFO IDVRMVSettings_ProxyInfo =
    {
    &Object_StubDesc,
    DVRMVPlayer__MIDL_ProcFormatString.Format,
    &IDVRMVSettings_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IDVRMVSettings_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    DVRMVPlayer__MIDL_ProcFormatString.Format,
    &IDVRMVSettings_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(11) _IDVRMVSettingsProxyVtbl = 
{
    &IDVRMVSettings_ProxyInfo,
    &IID_IDVRMVSettings,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IDVRMVSettings::get_mute */ ,
    (void *) (INT_PTR) -1 /* IDVRMVSettings::put_mute */ ,
    (void *) (INT_PTR) -1 /* IDVRMVSettings::get_volume */ ,
    (void *) (INT_PTR) -1 /* IDVRMVSettings::put_volume */
};


static const PRPC_STUB_FUNCTION IDVRMVSettings_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IDVRMVSettingsStubVtbl =
{
    &IID_IDVRMVSettings,
    &IDVRMVSettings_ServerInfo,
    11,
    &IDVRMVSettings_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IDVRMVMedia, ver. 0.0,
   GUID={0x842D4D89,0xDB49,0x43d9,{0x8A,0xA6,0x44,0xD4,0x48,0x3F,0xBF,0xC3}} */

#pragma code_seg(".orpc")
static const unsigned short IDVRMVMedia_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    340,
    368,
    396,
    424
    };

static const MIDL_STUBLESS_PROXY_INFO IDVRMVMedia_ProxyInfo =
    {
    &Object_StubDesc,
    DVRMVPlayer__MIDL_ProcFormatString.Format,
    &IDVRMVMedia_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IDVRMVMedia_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    DVRMVPlayer__MIDL_ProcFormatString.Format,
    &IDVRMVMedia_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(11) _IDVRMVMediaProxyVtbl = 
{
    &IDVRMVMedia_ProxyInfo,
    &IID_IDVRMVMedia,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IDVRMVMedia::get_imageSourceWidth */ ,
    (void *) (INT_PTR) -1 /* IDVRMVMedia::get_imageSourceHeight */ ,
    (void *) (INT_PTR) -1 /* IDVRMVMedia::get_duration */ ,
    (void *) (INT_PTR) -1 /* IDVRMVMedia::get_durationString */
};


static const PRPC_STUB_FUNCTION IDVRMVMedia_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IDVRMVMediaStubVtbl =
{
    &IID_IDVRMVMedia,
    &IDVRMVMedia_ServerInfo,
    11,
    &IDVRMVMedia_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IDVRMVPlayer, ver. 0.0,
   GUID={0x1EF48C0B,0x67B9,0x489D,{0x92,0xF4,0x0C,0x14,0x53,0xF6,0x13,0xE8}} */

#pragma code_seg(".orpc")
static const unsigned short IDVRMVPlayer_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    452,
    480,
    508,
    536,
    564,
    592,
    620,
    648,
    676,
    704,
    726,
    754,
    776,
    798,
    820,
    842,
    864,
    892,
    920,
    948,
    982,
    1010,
    1038,
    1066,
    1094,
    1122,
    1150,
    1178,
    1206,
    1234,
    1262,
    1290,
    1342,
    1364,
    1398,
    1432,
    1460,
    1482,
    1510,
    1538,
    1566,
    1594,
    1628,
    1656,
    1684,
    1712,
    1734,
    1756,
    1796,
    1818,
    1846,
    1874,
    1902
    };

static const MIDL_STUBLESS_PROXY_INFO IDVRMVPlayer_ProxyInfo =
    {
    &Object_StubDesc,
    DVRMVPlayer__MIDL_ProcFormatString.Format,
    &IDVRMVPlayer_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IDVRMVPlayer_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    DVRMVPlayer__MIDL_ProcFormatString.Format,
    &IDVRMVPlayer_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(60) _IDVRMVPlayerProxyVtbl = 
{
    &IDVRMVPlayer_ProxyInfo,
    &IID_IDVRMVPlayer,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IDVRMVPlayer::get_URL */ ,
    (void *) (INT_PTR) -1 /* IDVRMVPlayer::put_URL */ ,
    (void *) (INT_PTR) -1 /* IDVRMVPlayer::get_fullScreen */ ,
    (void *) (INT_PTR) -1 /* IDVRMVPlayer::put_fullScreen */ ,
    (void *) (INT_PTR) -1 /* IDVRMVPlayer::get_uiMode */ ,
    (void *) (INT_PTR) -1 /* IDVRMVPlayer::put_uiMode */ ,
    (void *) (INT_PTR) -1 /* IDVRMVPlayer::get_status */ ,
    (void *) (INT_PTR) -1 /* IDVRMVPlayer::get_playState */ ,
    (void *) (INT_PTR) -1 /* IDVRMVPlayer::get_versionInfo */ ,
    (void *) (INT_PTR) -1 /* IDVRMVPlayer::close */ ,
    (void *) (INT_PTR) -1 /* IDVRMVPlayer::get_controls */ ,
    (void *) (INT_PTR) -1 /* IDVRMVPlayer::play */ ,
    (void *) (INT_PTR) -1 /* IDVRMVPlayer::stop */ ,
    (void *) (INT_PTR) -1 /* IDVRMVPlayer::pause */ ,
    (void *) (INT_PTR) -1 /* IDVRMVPlayer::fastForward */ ,
    (void *) (INT_PTR) -1 /* IDVRMVPlayer::fastReverse */ ,
    (void *) (INT_PTR) -1 /* IDVRMVPlayer::get_currentPosition */ ,
    (void *) (INT_PTR) -1 /* IDVRMVPlayer::put_currentPosition */ ,
    (void *) (INT_PTR) -1 /* IDVRMVPlayer::get_currentPositionString */ ,
    (void *) (INT_PTR) -1 /* IDVRMVPlayer::get_isAvailable */ ,
    (void *) (INT_PTR) -1 /* IDVRMVPlayer::get_settings */ ,
    (void *) (INT_PTR) -1 /* IDVRMVPlayer::get_mute */ ,
    (void *) (INT_PTR) -1 /* IDVRMVPlayer::put_mute */ ,
    (void *) (INT_PTR) -1 /* IDVRMVPlayer::get_volume */ ,
    (void *) (INT_PTR) -1 /* IDVRMVPlayer::put_volume */ ,
    (void *) (INT_PTR) -1 /* IDVRMVPlayer::get_currentMedia */ ,
    (void *) (INT_PTR) -1 /* IDVRMVPlayer::get_imageSourceWidth */ ,
    (void *) (INT_PTR) -1 /* IDVRMVPlayer::get_imageSourceHeight */ ,
    (void *) (INT_PTR) -1 /* IDVRMVPlayer::get_duration */ ,
    (void *) (INT_PTR) -1 /* IDVRMVPlayer::get_durationString */ ,
    (void *) (INT_PTR) -1 /* IDVRMVPlayer::OpenFile */ ,
    (void *) (INT_PTR) -1 /* IDVRMVPlayer::Login */ ,
    (void *) (INT_PTR) -1 /* IDVRMVPlayer::Logout */ ,
    (void *) (INT_PTR) -1 /* IDVRMVPlayer::SetMediaServer */ ,
    (void *) (INT_PTR) -1 /* IDVRMVPlayer::GetMediaServer */ ,
    (void *) (INT_PTR) -1 /* IDVRMVPlayer::StartMonitor */ ,
    (void *) (INT_PTR) -1 /* IDVRMVPlayer::StopMonitor */ ,
    (void *) (INT_PTR) -1 /* IDVRMVPlayer::CapPic */ ,
    (void *) (INT_PTR) -1 /* IDVRMVPlayer::GetCapturePath */ ,
    (void *) (INT_PTR) -1 /* IDVRMVPlayer::SetCapturePath */ ,
    (void *) (INT_PTR) -1 /* IDVRMVPlayer::ShowMetaData */ ,
    (void *) (INT_PTR) -1 /* IDVRMVPlayer::SetWndChannel */ ,
    (void *) (INT_PTR) -1 /* IDVRMVPlayer::GetFullScreen */ ,
    (void *) (INT_PTR) -1 /* IDVRMVPlayer::SetFullScreen */ ,
    (void *) (INT_PTR) -1 /* IDVRMVPlayer::AddFileToPlayList */ ,
    (void *) (INT_PTR) -1 /* IDVRMVPlayer::ClosePlayList */ ,
    (void *) (INT_PTR) -1 /* IDVRMVPlayer::PlayNextFile */ ,
    (void *) (INT_PTR) -1 /* IDVRMVPlayer::StartPlayback */ ,
    (void *) (INT_PTR) -1 /* IDVRMVPlayer::StopPlayback */ ,
    (void *) (INT_PTR) -1 /* IDVRMVPlayer::GetDuration */ ,
    (void *) (INT_PTR) -1 /* IDVRMVPlayer::GetCurrentPosition */ ,
    (void *) (INT_PTR) -1 /* IDVRMVPlayer::GetDurationString */ ,
    (void *) (INT_PTR) -1 /* IDVRMVPlayer::GetCurrentPositionString */
};


static const PRPC_STUB_FUNCTION IDVRMVPlayer_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IDVRMVPlayerStubVtbl =
{
    &IID_IDVRMVPlayer,
    &IDVRMVPlayer_ServerInfo,
    60,
    &IDVRMVPlayer_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    DVRMVPlayer__MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x20000, /* Ndr library version */
    0,
    0x700022b, /* MIDL Version 7.0.555 */
    0,
    UserMarshalRoutines,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0
    };

const CInterfaceProxyVtbl * const _DVRMVPlayer_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IDVRMVPlayerProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IDVRMVControlsProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IDVRMVSettingsProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IDVRMVMediaProxyVtbl,
    0
};

const CInterfaceStubVtbl * const _DVRMVPlayer_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IDVRMVPlayerStubVtbl,
    ( CInterfaceStubVtbl *) &_IDVRMVControlsStubVtbl,
    ( CInterfaceStubVtbl *) &_IDVRMVSettingsStubVtbl,
    ( CInterfaceStubVtbl *) &_IDVRMVMediaStubVtbl,
    0
};

PCInterfaceName const _DVRMVPlayer_InterfaceNamesList[] = 
{
    "IDVRMVPlayer",
    "IDVRMVControls",
    "IDVRMVSettings",
    "IDVRMVMedia",
    0
};

const IID *  const _DVRMVPlayer_BaseIIDList[] = 
{
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    0
};


#define _DVRMVPlayer_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _DVRMVPlayer, pIID, n)

int __stdcall _DVRMVPlayer_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( _DVRMVPlayer, 4, 2 )
    IID_BS_LOOKUP_NEXT_TEST( _DVRMVPlayer, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( _DVRMVPlayer, 4, *pIndex )
    
}

const ExtendedProxyFileInfo DVRMVPlayer_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _DVRMVPlayer_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _DVRMVPlayer_StubVtblList,
    (const PCInterfaceName * ) & _DVRMVPlayer_InterfaceNamesList,
    (const IID ** ) & _DVRMVPlayer_BaseIIDList,
    & _DVRMVPlayer_IID_Lookup, 
    4,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
#pragma optimize("", on )
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* !defined(_M_IA64) && !defined(_M_AMD64)*/

