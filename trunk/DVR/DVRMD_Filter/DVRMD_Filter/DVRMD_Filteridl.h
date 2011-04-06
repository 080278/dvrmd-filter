

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Mon Apr 04 23:44:09 2011
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


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __DVRMD_Filteridl_h__
#define __DVRMD_Filteridl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DDVRMD_Filter_FWD_DEFINED__
#define ___DDVRMD_Filter_FWD_DEFINED__
typedef interface _DDVRMD_Filter _DDVRMD_Filter;
#endif 	/* ___DDVRMD_Filter_FWD_DEFINED__ */


#ifndef ___DDVRMD_FilterEvents_FWD_DEFINED__
#define ___DDVRMD_FilterEvents_FWD_DEFINED__
typedef interface _DDVRMD_FilterEvents _DDVRMD_FilterEvents;
#endif 	/* ___DDVRMD_FilterEvents_FWD_DEFINED__ */


#ifndef __DVRMD_Filter_FWD_DEFINED__
#define __DVRMD_Filter_FWD_DEFINED__

#ifdef __cplusplus
typedef class DVRMD_Filter DVRMD_Filter;
#else
typedef struct DVRMD_Filter DVRMD_Filter;
#endif /* __cplusplus */

#endif 	/* __DVRMD_Filter_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __DVRMD_FilterLib_LIBRARY_DEFINED__
#define __DVRMD_FilterLib_LIBRARY_DEFINED__

/* library DVRMD_FilterLib */
/* [control][helpstring][helpfile][version][uuid] */ 


EXTERN_C const IID LIBID_DVRMD_FilterLib;

#ifndef ___DDVRMD_Filter_DISPINTERFACE_DEFINED__
#define ___DDVRMD_Filter_DISPINTERFACE_DEFINED__

/* dispinterface _DDVRMD_Filter */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__DDVRMD_Filter;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("EC35B6AB-684F-4FE3-8EAD-4AAABE024EA2")
    _DDVRMD_Filter : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DDVRMD_FilterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DDVRMD_Filter * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DDVRMD_Filter * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DDVRMD_Filter * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DDVRMD_Filter * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DDVRMD_Filter * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DDVRMD_Filter * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DDVRMD_Filter * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DDVRMD_FilterVtbl;

    interface _DDVRMD_Filter
    {
        CONST_VTBL struct _DDVRMD_FilterVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DDVRMD_Filter_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DDVRMD_Filter_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DDVRMD_Filter_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DDVRMD_Filter_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DDVRMD_Filter_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DDVRMD_Filter_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DDVRMD_Filter_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DDVRMD_Filter_DISPINTERFACE_DEFINED__ */


#ifndef ___DDVRMD_FilterEvents_DISPINTERFACE_DEFINED__
#define ___DDVRMD_FilterEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DDVRMD_FilterEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__DDVRMD_FilterEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("67DC81BA-E0EC-4122-AD13-DEF72A4BEC27")
    _DDVRMD_FilterEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DDVRMD_FilterEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DDVRMD_FilterEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DDVRMD_FilterEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DDVRMD_FilterEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DDVRMD_FilterEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DDVRMD_FilterEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DDVRMD_FilterEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DDVRMD_FilterEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DDVRMD_FilterEventsVtbl;

    interface _DDVRMD_FilterEvents
    {
        CONST_VTBL struct _DDVRMD_FilterEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DDVRMD_FilterEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DDVRMD_FilterEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DDVRMD_FilterEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DDVRMD_FilterEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DDVRMD_FilterEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DDVRMD_FilterEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DDVRMD_FilterEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DDVRMD_FilterEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_DVRMD_Filter;

#ifdef __cplusplus

class DECLSPEC_UUID("023D5C5C-2FFE-4054-8CE9-45C492778C52")
DVRMD_Filter;
#endif
#endif /* __DVRMD_FilterLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


