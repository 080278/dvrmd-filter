

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


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


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __SonicIMVPlayer_h__
#define __SonicIMVPlayer_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ISonicIMVControls_FWD_DEFINED__
#define __ISonicIMVControls_FWD_DEFINED__
typedef interface ISonicIMVControls ISonicIMVControls;
#endif 	/* __ISonicIMVControls_FWD_DEFINED__ */


#ifndef __ISonicIMVSettings_FWD_DEFINED__
#define __ISonicIMVSettings_FWD_DEFINED__
typedef interface ISonicIMVSettings ISonicIMVSettings;
#endif 	/* __ISonicIMVSettings_FWD_DEFINED__ */


#ifndef __ISonicIMVMedia_FWD_DEFINED__
#define __ISonicIMVMedia_FWD_DEFINED__
typedef interface ISonicIMVMedia ISonicIMVMedia;
#endif 	/* __ISonicIMVMedia_FWD_DEFINED__ */


#ifndef __ISonicIMVPlayer_FWD_DEFINED__
#define __ISonicIMVPlayer_FWD_DEFINED__
typedef interface ISonicIMVPlayer ISonicIMVPlayer;
#endif 	/* __ISonicIMVPlayer_FWD_DEFINED__ */


#ifndef ___ISonicIMVPlayerCtrlEvents_FWD_DEFINED__
#define ___ISonicIMVPlayerCtrlEvents_FWD_DEFINED__
typedef interface _ISonicIMVPlayerCtrlEvents _ISonicIMVPlayerCtrlEvents;
#endif 	/* ___ISonicIMVPlayerCtrlEvents_FWD_DEFINED__ */


#ifndef __SonicIMVPlayerCtrl_FWD_DEFINED__
#define __SonicIMVPlayerCtrl_FWD_DEFINED__

#ifdef __cplusplus
typedef class SonicIMVPlayerCtrl SonicIMVPlayerCtrl;
#else
typedef struct SonicIMVPlayerCtrl SonicIMVPlayerCtrl;
#endif /* __cplusplus */

#endif 	/* __SonicIMVPlayerCtrl_FWD_DEFINED__ */


#ifndef __SonicIMVPlayerProp_FWD_DEFINED__
#define __SonicIMVPlayerProp_FWD_DEFINED__

#ifdef __cplusplus
typedef class SonicIMVPlayerProp SonicIMVPlayerProp;
#else
typedef struct SonicIMVPlayerProp SonicIMVPlayerProp;
#endif /* __cplusplus */

#endif 	/* __SonicIMVPlayerProp_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_SonicIMVPlayer_0000_0000 */
/* [local] */ 

//=========================================================================
//
// Sonic Playback Engine On Intel Media Vault Platform 
// Copyright (C) Sonic Solution.  All Rights Reserved.
//
//=========================================================================
typedef /* [public][helpstring] */ 
enum IMVResult
    {	IMV_SUCCESSFUL	= 0,
	IMV_FAIL_HDCP	= -1,
	IMV_FAIL_LICENSE	= -2,
	IMV_FAIL_INVALIDATE_FILE	= -3
    } 	IMVResult;



extern RPC_IF_HANDLE __MIDL_itf_SonicIMVPlayer_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_SonicIMVPlayer_0000_0000_v0_0_s_ifspec;

#ifndef __ISonicIMVControls_INTERFACE_DEFINED__
#define __ISonicIMVControls_INTERFACE_DEFINED__

/* interface ISonicIMVControls */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ISonicIMVControls;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("583C0343-05D2-4c3a-9282-FC14C8396E4E")
    ISonicIMVControls : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE play( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE stop( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE pause( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE fastForward( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE fastReverse( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_currentPosition( 
            /* [retval][out] */ DOUBLE *pdCurrentPosition) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_currentPosition( 
            /* [in] */ DOUBLE dCurrentPosition) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_currentPositionString( 
            /* [retval][out] */ BSTR *pbstrCurrentPosition) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_isAvailable( 
            /* [in] */ BSTR bstrItem,
            /* [retval][out] */ VARIANT_BOOL *pIsAvailable) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISonicIMVControlsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISonicIMVControls * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISonicIMVControls * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISonicIMVControls * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ISonicIMVControls * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ISonicIMVControls * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ISonicIMVControls * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ISonicIMVControls * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *play )( 
            ISonicIMVControls * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *stop )( 
            ISonicIMVControls * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *pause )( 
            ISonicIMVControls * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *fastForward )( 
            ISonicIMVControls * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *fastReverse )( 
            ISonicIMVControls * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_currentPosition )( 
            ISonicIMVControls * This,
            /* [retval][out] */ DOUBLE *pdCurrentPosition);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_currentPosition )( 
            ISonicIMVControls * This,
            /* [in] */ DOUBLE dCurrentPosition);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_currentPositionString )( 
            ISonicIMVControls * This,
            /* [retval][out] */ BSTR *pbstrCurrentPosition);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_isAvailable )( 
            ISonicIMVControls * This,
            /* [in] */ BSTR bstrItem,
            /* [retval][out] */ VARIANT_BOOL *pIsAvailable);
        
        END_INTERFACE
    } ISonicIMVControlsVtbl;

    interface ISonicIMVControls
    {
        CONST_VTBL struct ISonicIMVControlsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISonicIMVControls_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISonicIMVControls_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISonicIMVControls_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISonicIMVControls_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ISonicIMVControls_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ISonicIMVControls_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ISonicIMVControls_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ISonicIMVControls_play(This)	\
    ( (This)->lpVtbl -> play(This) ) 

#define ISonicIMVControls_stop(This)	\
    ( (This)->lpVtbl -> stop(This) ) 

#define ISonicIMVControls_pause(This)	\
    ( (This)->lpVtbl -> pause(This) ) 

#define ISonicIMVControls_fastForward(This)	\
    ( (This)->lpVtbl -> fastForward(This) ) 

#define ISonicIMVControls_fastReverse(This)	\
    ( (This)->lpVtbl -> fastReverse(This) ) 

#define ISonicIMVControls_get_currentPosition(This,pdCurrentPosition)	\
    ( (This)->lpVtbl -> get_currentPosition(This,pdCurrentPosition) ) 

#define ISonicIMVControls_put_currentPosition(This,dCurrentPosition)	\
    ( (This)->lpVtbl -> put_currentPosition(This,dCurrentPosition) ) 

#define ISonicIMVControls_get_currentPositionString(This,pbstrCurrentPosition)	\
    ( (This)->lpVtbl -> get_currentPositionString(This,pbstrCurrentPosition) ) 

#define ISonicIMVControls_get_isAvailable(This,bstrItem,pIsAvailable)	\
    ( (This)->lpVtbl -> get_isAvailable(This,bstrItem,pIsAvailable) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISonicIMVControls_INTERFACE_DEFINED__ */


#ifndef __ISonicIMVSettings_INTERFACE_DEFINED__
#define __ISonicIMVSettings_INTERFACE_DEFINED__

/* interface ISonicIMVSettings */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ISonicIMVSettings;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7D45535F-3ECE-4bd7-A868-C1B2A8128A76")
    ISonicIMVSettings : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_mute( 
            /* [retval][out] */ VARIANT_BOOL *pfMute) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_mute( 
            /* [in] */ VARIANT_BOOL fMute) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_volume( 
            /* [retval][out] */ LONG *plVolume) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_volume( 
            /* [in] */ LONG lVolume) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISonicIMVSettingsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISonicIMVSettings * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISonicIMVSettings * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISonicIMVSettings * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ISonicIMVSettings * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ISonicIMVSettings * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ISonicIMVSettings * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ISonicIMVSettings * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_mute )( 
            ISonicIMVSettings * This,
            /* [retval][out] */ VARIANT_BOOL *pfMute);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_mute )( 
            ISonicIMVSettings * This,
            /* [in] */ VARIANT_BOOL fMute);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_volume )( 
            ISonicIMVSettings * This,
            /* [retval][out] */ LONG *plVolume);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_volume )( 
            ISonicIMVSettings * This,
            /* [in] */ LONG lVolume);
        
        END_INTERFACE
    } ISonicIMVSettingsVtbl;

    interface ISonicIMVSettings
    {
        CONST_VTBL struct ISonicIMVSettingsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISonicIMVSettings_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISonicIMVSettings_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISonicIMVSettings_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISonicIMVSettings_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ISonicIMVSettings_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ISonicIMVSettings_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ISonicIMVSettings_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ISonicIMVSettings_get_mute(This,pfMute)	\
    ( (This)->lpVtbl -> get_mute(This,pfMute) ) 

#define ISonicIMVSettings_put_mute(This,fMute)	\
    ( (This)->lpVtbl -> put_mute(This,fMute) ) 

#define ISonicIMVSettings_get_volume(This,plVolume)	\
    ( (This)->lpVtbl -> get_volume(This,plVolume) ) 

#define ISonicIMVSettings_put_volume(This,lVolume)	\
    ( (This)->lpVtbl -> put_volume(This,lVolume) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISonicIMVSettings_INTERFACE_DEFINED__ */


#ifndef __ISonicIMVMedia_INTERFACE_DEFINED__
#define __ISonicIMVMedia_INTERFACE_DEFINED__

/* interface ISonicIMVMedia */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ISonicIMVMedia;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("842D4D89-DB49-43d9-8AA6-44D4483FBFC3")
    ISonicIMVMedia : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_imageSourceWidth( 
            /* [retval][out] */ LONG *pWidth) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_imageSourceHeight( 
            /* [retval][out] */ LONG *pHeight) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_duration( 
            /* [retval][out] */ DOUBLE *pDuration) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_durationString( 
            /* [retval][out] */ BSTR *pbstrDuration) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISonicIMVMediaVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISonicIMVMedia * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISonicIMVMedia * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISonicIMVMedia * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ISonicIMVMedia * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ISonicIMVMedia * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ISonicIMVMedia * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ISonicIMVMedia * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_imageSourceWidth )( 
            ISonicIMVMedia * This,
            /* [retval][out] */ LONG *pWidth);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_imageSourceHeight )( 
            ISonicIMVMedia * This,
            /* [retval][out] */ LONG *pHeight);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_duration )( 
            ISonicIMVMedia * This,
            /* [retval][out] */ DOUBLE *pDuration);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_durationString )( 
            ISonicIMVMedia * This,
            /* [retval][out] */ BSTR *pbstrDuration);
        
        END_INTERFACE
    } ISonicIMVMediaVtbl;

    interface ISonicIMVMedia
    {
        CONST_VTBL struct ISonicIMVMediaVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISonicIMVMedia_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISonicIMVMedia_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISonicIMVMedia_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISonicIMVMedia_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ISonicIMVMedia_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ISonicIMVMedia_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ISonicIMVMedia_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ISonicIMVMedia_get_imageSourceWidth(This,pWidth)	\
    ( (This)->lpVtbl -> get_imageSourceWidth(This,pWidth) ) 

#define ISonicIMVMedia_get_imageSourceHeight(This,pHeight)	\
    ( (This)->lpVtbl -> get_imageSourceHeight(This,pHeight) ) 

#define ISonicIMVMedia_get_duration(This,pDuration)	\
    ( (This)->lpVtbl -> get_duration(This,pDuration) ) 

#define ISonicIMVMedia_get_durationString(This,pbstrDuration)	\
    ( (This)->lpVtbl -> get_durationString(This,pbstrDuration) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISonicIMVMedia_INTERFACE_DEFINED__ */


#ifndef __ISonicIMVPlayer_INTERFACE_DEFINED__
#define __ISonicIMVPlayer_INTERFACE_DEFINED__

/* interface ISonicIMVPlayer */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ISonicIMVPlayer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1EF48C0B-67B9-489D-92F4-0C1453F613E8")
    ISonicIMVPlayer : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_URL( 
            /* [retval][out] */ BSTR *pbstrURL) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_URL( 
            /* [in] */ BSTR bstrURL) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_fullScreen( 
            /* [retval][out] */ VARIANT_BOOL *pbFullScreen) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_fullScreen( 
            /* [in] */ VARIANT_BOOL bFullScreen) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_uiMode( 
            /* [retval][out] */ BSTR *pbstrMode) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_uiMode( 
            /* [in] */ BSTR bstrMode) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_status( 
            /* [retval][out] */ BSTR *pbstrStatus) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_playState( 
            /* [retval][out] */ LONG *plState) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_versionInfo( 
            /* [retval][out] */ BSTR *pbstrVersionInfo) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE close( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_controls( 
            /* [retval][out] */ ISonicIMVControls **ppControl) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE play( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE stop( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE pause( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE fastForward( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE fastReverse( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_currentPosition( 
            /* [retval][out] */ DOUBLE *pdCurrentPosition) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_currentPosition( 
            /* [in] */ DOUBLE dCurrentPosition) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_currentPositionString( 
            /* [retval][out] */ BSTR *pbstrCurrentPosition) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_isAvailable( 
            /* [in] */ BSTR bstrItem,
            /* [retval][out] */ VARIANT_BOOL *pIsAvailable) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_settings( 
            /* [retval][out] */ ISonicIMVSettings **ppSettings) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_mute( 
            /* [retval][out] */ VARIANT_BOOL *pfMute) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_mute( 
            /* [in] */ VARIANT_BOOL fMute) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_volume( 
            /* [retval][out] */ LONG *plVolume) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_volume( 
            /* [in] */ LONG lVolume) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_currentMedia( 
            /* [retval][out] */ ISonicIMVMedia **ppMedia) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_imageSourceWidth( 
            /* [retval][out] */ LONG *pWidth) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_imageSourceHeight( 
            /* [retval][out] */ LONG *pHeight) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_duration( 
            /* [retval][out] */ DOUBLE *pDuration) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_durationString( 
            /* [retval][out] */ BSTR *pbstrDuration) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OpenFile( 
            /* [in] */ BSTR bstrMediaFile) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Login( 
            /* [in] */ BSTR bstrUsername,
            /* [in] */ BSTR bstrPassword,
            /* [in] */ BSTR bstrIP,
            /* [in] */ LONG lPort) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Logout( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetMediaServer( 
            /* [in] */ BSTR bstrMediaServerIP,
            /* [in] */ LONG lPort) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetMediaServer( 
            /* [out] */ BSTR *bstrMediaServerIP,
            /* [out] */ LONG *lPort) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StartMonitor( 
            /* [in] */ LONG lWndNum) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StopMonitor( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CapPic( 
            /* [out] */ BSTR *pCapPicPath) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCapturePath( 
            /* [out] */ BSTR *pbstrCapFolder) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetCapturePath( 
            /* [in] */ BSTR bstrCapFolder) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ShowMetaData( 
            /* [in] */ VARIANT_BOOL bShow) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISonicIMVPlayerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISonicIMVPlayer * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISonicIMVPlayer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISonicIMVPlayer * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ISonicIMVPlayer * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ISonicIMVPlayer * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ISonicIMVPlayer * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ISonicIMVPlayer * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_URL )( 
            ISonicIMVPlayer * This,
            /* [retval][out] */ BSTR *pbstrURL);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_URL )( 
            ISonicIMVPlayer * This,
            /* [in] */ BSTR bstrURL);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_fullScreen )( 
            ISonicIMVPlayer * This,
            /* [retval][out] */ VARIANT_BOOL *pbFullScreen);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_fullScreen )( 
            ISonicIMVPlayer * This,
            /* [in] */ VARIANT_BOOL bFullScreen);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_uiMode )( 
            ISonicIMVPlayer * This,
            /* [retval][out] */ BSTR *pbstrMode);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_uiMode )( 
            ISonicIMVPlayer * This,
            /* [in] */ BSTR bstrMode);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_status )( 
            ISonicIMVPlayer * This,
            /* [retval][out] */ BSTR *pbstrStatus);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_playState )( 
            ISonicIMVPlayer * This,
            /* [retval][out] */ LONG *plState);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_versionInfo )( 
            ISonicIMVPlayer * This,
            /* [retval][out] */ BSTR *pbstrVersionInfo);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *close )( 
            ISonicIMVPlayer * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_controls )( 
            ISonicIMVPlayer * This,
            /* [retval][out] */ ISonicIMVControls **ppControl);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *play )( 
            ISonicIMVPlayer * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *stop )( 
            ISonicIMVPlayer * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *pause )( 
            ISonicIMVPlayer * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *fastForward )( 
            ISonicIMVPlayer * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *fastReverse )( 
            ISonicIMVPlayer * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_currentPosition )( 
            ISonicIMVPlayer * This,
            /* [retval][out] */ DOUBLE *pdCurrentPosition);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_currentPosition )( 
            ISonicIMVPlayer * This,
            /* [in] */ DOUBLE dCurrentPosition);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_currentPositionString )( 
            ISonicIMVPlayer * This,
            /* [retval][out] */ BSTR *pbstrCurrentPosition);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_isAvailable )( 
            ISonicIMVPlayer * This,
            /* [in] */ BSTR bstrItem,
            /* [retval][out] */ VARIANT_BOOL *pIsAvailable);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_settings )( 
            ISonicIMVPlayer * This,
            /* [retval][out] */ ISonicIMVSettings **ppSettings);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_mute )( 
            ISonicIMVPlayer * This,
            /* [retval][out] */ VARIANT_BOOL *pfMute);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_mute )( 
            ISonicIMVPlayer * This,
            /* [in] */ VARIANT_BOOL fMute);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_volume )( 
            ISonicIMVPlayer * This,
            /* [retval][out] */ LONG *plVolume);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_volume )( 
            ISonicIMVPlayer * This,
            /* [in] */ LONG lVolume);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_currentMedia )( 
            ISonicIMVPlayer * This,
            /* [retval][out] */ ISonicIMVMedia **ppMedia);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_imageSourceWidth )( 
            ISonicIMVPlayer * This,
            /* [retval][out] */ LONG *pWidth);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_imageSourceHeight )( 
            ISonicIMVPlayer * This,
            /* [retval][out] */ LONG *pHeight);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_duration )( 
            ISonicIMVPlayer * This,
            /* [retval][out] */ DOUBLE *pDuration);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_durationString )( 
            ISonicIMVPlayer * This,
            /* [retval][out] */ BSTR *pbstrDuration);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OpenFile )( 
            ISonicIMVPlayer * This,
            /* [in] */ BSTR bstrMediaFile);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Login )( 
            ISonicIMVPlayer * This,
            /* [in] */ BSTR bstrUsername,
            /* [in] */ BSTR bstrPassword,
            /* [in] */ BSTR bstrIP,
            /* [in] */ LONG lPort);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Logout )( 
            ISonicIMVPlayer * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetMediaServer )( 
            ISonicIMVPlayer * This,
            /* [in] */ BSTR bstrMediaServerIP,
            /* [in] */ LONG lPort);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetMediaServer )( 
            ISonicIMVPlayer * This,
            /* [out] */ BSTR *bstrMediaServerIP,
            /* [out] */ LONG *lPort);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StartMonitor )( 
            ISonicIMVPlayer * This,
            /* [in] */ LONG lWndNum);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StopMonitor )( 
            ISonicIMVPlayer * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CapPic )( 
            ISonicIMVPlayer * This,
            /* [out] */ BSTR *pCapPicPath);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCapturePath )( 
            ISonicIMVPlayer * This,
            /* [out] */ BSTR *pbstrCapFolder);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetCapturePath )( 
            ISonicIMVPlayer * This,
            /* [in] */ BSTR bstrCapFolder);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ShowMetaData )( 
            ISonicIMVPlayer * This,
            /* [in] */ VARIANT_BOOL bShow);
        
        END_INTERFACE
    } ISonicIMVPlayerVtbl;

    interface ISonicIMVPlayer
    {
        CONST_VTBL struct ISonicIMVPlayerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISonicIMVPlayer_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISonicIMVPlayer_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISonicIMVPlayer_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISonicIMVPlayer_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ISonicIMVPlayer_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ISonicIMVPlayer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ISonicIMVPlayer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ISonicIMVPlayer_get_URL(This,pbstrURL)	\
    ( (This)->lpVtbl -> get_URL(This,pbstrURL) ) 

#define ISonicIMVPlayer_put_URL(This,bstrURL)	\
    ( (This)->lpVtbl -> put_URL(This,bstrURL) ) 

#define ISonicIMVPlayer_get_fullScreen(This,pbFullScreen)	\
    ( (This)->lpVtbl -> get_fullScreen(This,pbFullScreen) ) 

#define ISonicIMVPlayer_put_fullScreen(This,bFullScreen)	\
    ( (This)->lpVtbl -> put_fullScreen(This,bFullScreen) ) 

#define ISonicIMVPlayer_get_uiMode(This,pbstrMode)	\
    ( (This)->lpVtbl -> get_uiMode(This,pbstrMode) ) 

#define ISonicIMVPlayer_put_uiMode(This,bstrMode)	\
    ( (This)->lpVtbl -> put_uiMode(This,bstrMode) ) 

#define ISonicIMVPlayer_get_status(This,pbstrStatus)	\
    ( (This)->lpVtbl -> get_status(This,pbstrStatus) ) 

#define ISonicIMVPlayer_get_playState(This,plState)	\
    ( (This)->lpVtbl -> get_playState(This,plState) ) 

#define ISonicIMVPlayer_get_versionInfo(This,pbstrVersionInfo)	\
    ( (This)->lpVtbl -> get_versionInfo(This,pbstrVersionInfo) ) 

#define ISonicIMVPlayer_close(This)	\
    ( (This)->lpVtbl -> close(This) ) 

#define ISonicIMVPlayer_get_controls(This,ppControl)	\
    ( (This)->lpVtbl -> get_controls(This,ppControl) ) 

#define ISonicIMVPlayer_play(This)	\
    ( (This)->lpVtbl -> play(This) ) 

#define ISonicIMVPlayer_stop(This)	\
    ( (This)->lpVtbl -> stop(This) ) 

#define ISonicIMVPlayer_pause(This)	\
    ( (This)->lpVtbl -> pause(This) ) 

#define ISonicIMVPlayer_fastForward(This)	\
    ( (This)->lpVtbl -> fastForward(This) ) 

#define ISonicIMVPlayer_fastReverse(This)	\
    ( (This)->lpVtbl -> fastReverse(This) ) 

#define ISonicIMVPlayer_get_currentPosition(This,pdCurrentPosition)	\
    ( (This)->lpVtbl -> get_currentPosition(This,pdCurrentPosition) ) 

#define ISonicIMVPlayer_put_currentPosition(This,dCurrentPosition)	\
    ( (This)->lpVtbl -> put_currentPosition(This,dCurrentPosition) ) 

#define ISonicIMVPlayer_get_currentPositionString(This,pbstrCurrentPosition)	\
    ( (This)->lpVtbl -> get_currentPositionString(This,pbstrCurrentPosition) ) 

#define ISonicIMVPlayer_get_isAvailable(This,bstrItem,pIsAvailable)	\
    ( (This)->lpVtbl -> get_isAvailable(This,bstrItem,pIsAvailable) ) 

#define ISonicIMVPlayer_get_settings(This,ppSettings)	\
    ( (This)->lpVtbl -> get_settings(This,ppSettings) ) 

#define ISonicIMVPlayer_get_mute(This,pfMute)	\
    ( (This)->lpVtbl -> get_mute(This,pfMute) ) 

#define ISonicIMVPlayer_put_mute(This,fMute)	\
    ( (This)->lpVtbl -> put_mute(This,fMute) ) 

#define ISonicIMVPlayer_get_volume(This,plVolume)	\
    ( (This)->lpVtbl -> get_volume(This,plVolume) ) 

#define ISonicIMVPlayer_put_volume(This,lVolume)	\
    ( (This)->lpVtbl -> put_volume(This,lVolume) ) 

#define ISonicIMVPlayer_get_currentMedia(This,ppMedia)	\
    ( (This)->lpVtbl -> get_currentMedia(This,ppMedia) ) 

#define ISonicIMVPlayer_get_imageSourceWidth(This,pWidth)	\
    ( (This)->lpVtbl -> get_imageSourceWidth(This,pWidth) ) 

#define ISonicIMVPlayer_get_imageSourceHeight(This,pHeight)	\
    ( (This)->lpVtbl -> get_imageSourceHeight(This,pHeight) ) 

#define ISonicIMVPlayer_get_duration(This,pDuration)	\
    ( (This)->lpVtbl -> get_duration(This,pDuration) ) 

#define ISonicIMVPlayer_get_durationString(This,pbstrDuration)	\
    ( (This)->lpVtbl -> get_durationString(This,pbstrDuration) ) 

#define ISonicIMVPlayer_OpenFile(This,bstrMediaFile)	\
    ( (This)->lpVtbl -> OpenFile(This,bstrMediaFile) ) 

#define ISonicIMVPlayer_Login(This,bstrUsername,bstrPassword,bstrIP,lPort)	\
    ( (This)->lpVtbl -> Login(This,bstrUsername,bstrPassword,bstrIP,lPort) ) 

#define ISonicIMVPlayer_Logout(This)	\
    ( (This)->lpVtbl -> Logout(This) ) 

#define ISonicIMVPlayer_SetMediaServer(This,bstrMediaServerIP,lPort)	\
    ( (This)->lpVtbl -> SetMediaServer(This,bstrMediaServerIP,lPort) ) 

#define ISonicIMVPlayer_GetMediaServer(This,bstrMediaServerIP,lPort)	\
    ( (This)->lpVtbl -> GetMediaServer(This,bstrMediaServerIP,lPort) ) 

#define ISonicIMVPlayer_StartMonitor(This,lWndNum)	\
    ( (This)->lpVtbl -> StartMonitor(This,lWndNum) ) 

#define ISonicIMVPlayer_StopMonitor(This)	\
    ( (This)->lpVtbl -> StopMonitor(This) ) 

#define ISonicIMVPlayer_CapPic(This,pCapPicPath)	\
    ( (This)->lpVtbl -> CapPic(This,pCapPicPath) ) 

#define ISonicIMVPlayer_GetCapturePath(This,pbstrCapFolder)	\
    ( (This)->lpVtbl -> GetCapturePath(This,pbstrCapFolder) ) 

#define ISonicIMVPlayer_SetCapturePath(This,bstrCapFolder)	\
    ( (This)->lpVtbl -> SetCapturePath(This,bstrCapFolder) ) 

#define ISonicIMVPlayer_ShowMetaData(This,bShow)	\
    ( (This)->lpVtbl -> ShowMetaData(This,bShow) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISonicIMVPlayer_INTERFACE_DEFINED__ */



#ifndef __SonicIMVPlayerLib_LIBRARY_DEFINED__
#define __SonicIMVPlayerLib_LIBRARY_DEFINED__

/* library SonicIMVPlayerLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_SonicIMVPlayerLib;

#ifndef ___ISonicIMVPlayerCtrlEvents_DISPINTERFACE_DEFINED__
#define ___ISonicIMVPlayerCtrlEvents_DISPINTERFACE_DEFINED__

/* dispinterface _ISonicIMVPlayerCtrlEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__ISonicIMVPlayerCtrlEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("3492600D-3F55-4EDE-9901-F767D18C3497")
    _ISonicIMVPlayerCtrlEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _ISonicIMVPlayerCtrlEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _ISonicIMVPlayerCtrlEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _ISonicIMVPlayerCtrlEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _ISonicIMVPlayerCtrlEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _ISonicIMVPlayerCtrlEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _ISonicIMVPlayerCtrlEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _ISonicIMVPlayerCtrlEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _ISonicIMVPlayerCtrlEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _ISonicIMVPlayerCtrlEventsVtbl;

    interface _ISonicIMVPlayerCtrlEvents
    {
        CONST_VTBL struct _ISonicIMVPlayerCtrlEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _ISonicIMVPlayerCtrlEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _ISonicIMVPlayerCtrlEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _ISonicIMVPlayerCtrlEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _ISonicIMVPlayerCtrlEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _ISonicIMVPlayerCtrlEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _ISonicIMVPlayerCtrlEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _ISonicIMVPlayerCtrlEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___ISonicIMVPlayerCtrlEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_SonicIMVPlayerCtrl;

#ifdef __cplusplus

class DECLSPEC_UUID("023D5C5C-2FFE-4054-8CE9-45C492778C52")
SonicIMVPlayerCtrl;
#endif

EXTERN_C const CLSID CLSID_SonicIMVPlayerProp;

#ifdef __cplusplus

class DECLSPEC_UUID("D9D9CCA7-2BE1-4E1D-8D88-E7F4CBB3E34B")
SonicIMVPlayerProp;
#endif
#endif /* __SonicIMVPlayerLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


