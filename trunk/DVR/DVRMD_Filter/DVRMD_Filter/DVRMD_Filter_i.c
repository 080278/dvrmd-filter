

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Thu Mar 31 21:43:13 2011
 */
/* Compiler settings for DVRMD_Filter.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
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

MIDL_DEFINE_GUID(IID, LIBID_DVRMD_FilterLib,0xD040A193,0xED38,0x49B2,0xAF,0xDE,0xD1,0x0E,0x86,0xA9,0xEF,0xCE);


MIDL_DEFINE_GUID(IID, DIID__DDVRMD_Filter,0xEC35B6AB,0x684F,0x4FE3,0x8E,0xAD,0x4A,0xAA,0xBE,0x02,0x4E,0xA2);


MIDL_DEFINE_GUID(IID, DIID__DDVRMD_FilterEvents,0x67DC81BA,0xE0EC,0x4122,0xAD,0x13,0xDE,0xF7,0x2A,0x4B,0xEC,0x27);


MIDL_DEFINE_GUID(CLSID, CLSID_DVRMD_Filter,0x023D5C5C,0x2FFE,0x4054,0x8C,0xE9,0x45,0xC4,0x92,0x77,0x8C,0x52);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



