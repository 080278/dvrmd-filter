

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Mon May 09 21:14:21 2011
 */
/* Compiler settings for public\SonicIMVPlayer.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_ISonicIMVControls,0x583C0343,0x05D2,0x4c3a,0x92,0x82,0xFC,0x14,0xC8,0x39,0x6E,0x4E);


MIDL_DEFINE_GUID(IID, IID_ISonicIMVSettings,0x7D45535F,0x3ECE,0x4bd7,0xA8,0x68,0xC1,0xB2,0xA8,0x12,0x8A,0x76);


MIDL_DEFINE_GUID(IID, IID_ISonicIMVMedia,0x842D4D89,0xDB49,0x43d9,0x8A,0xA6,0x44,0xD4,0x48,0x3F,0xBF,0xC3);


MIDL_DEFINE_GUID(IID, IID_ISonicIMVPlayer,0x1EF48C0B,0x67B9,0x489D,0x92,0xF4,0x0C,0x14,0x53,0xF6,0x13,0xE8);


MIDL_DEFINE_GUID(IID, LIBID_SonicIMVPlayerLib,0x84EFD30E,0xAE3F,0x4E2E,0xBF,0x00,0x68,0x1B,0xF7,0x5C,0x9A,0x34);


MIDL_DEFINE_GUID(IID, DIID__ISonicIMVPlayerCtrlEvents,0x3492600D,0x3F55,0x4EDE,0x99,0x01,0xF7,0x67,0xD1,0x8C,0x34,0x97);


MIDL_DEFINE_GUID(CLSID, CLSID_SonicIMVPlayerCtrl,0x023D5C5C,0x2FFE,0x4054,0x8C,0xE9,0x45,0xC4,0x92,0x77,0x8C,0x52);


MIDL_DEFINE_GUID(CLSID, CLSID_SonicIMVPlayerProp,0xD9D9CCA7,0x2BE1,0x4E1D,0x8D,0x88,0xE7,0xF4,0xCB,0xB3,0xE3,0x4B);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



