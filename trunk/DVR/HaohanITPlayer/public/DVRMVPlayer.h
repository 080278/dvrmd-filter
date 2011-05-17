

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Tue May 17 23:26:48 2011
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

#ifndef __DVRMVPlayer_h__
#define __DVRMVPlayer_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IDVRMVControls_FWD_DEFINED__
#define __IDVRMVControls_FWD_DEFINED__
typedef interface IDVRMVControls IDVRMVControls;
#endif 	/* __IDVRMVControls_FWD_DEFINED__ */


#ifndef __IDVRMVSettings_FWD_DEFINED__
#define __IDVRMVSettings_FWD_DEFINED__
typedef interface IDVRMVSettings IDVRMVSettings;
#endif 	/* __IDVRMVSettings_FWD_DEFINED__ */


#ifndef __IDVRMVMedia_FWD_DEFINED__
#define __IDVRMVMedia_FWD_DEFINED__
typedef interface IDVRMVMedia IDVRMVMedia;
#endif 	/* __IDVRMVMedia_FWD_DEFINED__ */


#ifndef __IDVRMVPlayer_FWD_DEFINED__
#define __IDVRMVPlayer_FWD_DEFINED__
typedef interface IDVRMVPlayer IDVRMVPlayer;
#endif 	/* __IDVRMVPlayer_FWD_DEFINED__ */


#ifndef ___IDVRMVPlayerCtrlEvents_FWD_DEFINED__
#define ___IDVRMVPlayerCtrlEvents_FWD_DEFINED__
typedef interface _IDVRMVPlayerCtrlEvents _IDVRMVPlayerCtrlEvents;
#endif 	/* ___IDVRMVPlayerCtrlEvents_FWD_DEFINED__ */


#ifndef __DVRMVPlayerCtrl_FWD_DEFINED__
#define __DVRMVPlayerCtrl_FWD_DEFINED__

#ifdef __cplusplus
typedef class DVRMVPlayerCtrl DVRMVPlayerCtrl;
#else
typedef struct DVRMVPlayerCtrl DVRMVPlayerCtrl;
#endif /* __cplusplus */

#endif 	/* __DVRMVPlayerCtrl_FWD_DEFINED__ */


#ifndef __DVRMVPlayerProp_FWD_DEFINED__
#define __DVRMVPlayerProp_FWD_DEFINED__

#ifdef __cplusplus
typedef class DVRMVPlayerProp DVRMVPlayerProp;
#else
typedef struct DVRMVPlayerProp DVRMVPlayerProp;
#endif /* __cplusplus */

#endif 	/* __DVRMVPlayerProp_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_DVRMVPlayer_0000_0000 */
/* [local] */ 

//=========================================================================
//
// Sonic Playback Engine On Intel Media Vault Platform 
// Copyright (C) Haohanit.  All Rights Reserved.
//
//=========================================================================
typedef /* [public][helpstring] */ 
enum IMVResult
    {	IMV_SUCCESSFUL	= 0,
	IMV_FAIL_HDCP	= -1,
	IMV_FAIL_LICENSE	= -2,
	IMV_FAIL_INVALIDATE_FILE	= -3
    } 	IMVResult;



extern RPC_IF_HANDLE __MIDL_itf_DVRMVPlayer_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_DVRMVPlayer_0000_0000_v0_0_s_ifspec;

#ifndef __IDVRMVControls_INTERFACE_DEFINED__
#define __IDVRMVControls_INTERFACE_DEFINED__

/* interface IDVRMVControls */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IDVRMVControls;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("583C0343-05D2-4c3a-9282-FC14C8396E4E")
    IDVRMVControls : public IDispatch
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

    typedef struct IDVRMVControlsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDVRMVControls * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDVRMVControls * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDVRMVControls * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDVRMVControls * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDVRMVControls * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDVRMVControls * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDVRMVControls * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *play )( 
            IDVRMVControls * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *stop )( 
            IDVRMVControls * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *pause )( 
            IDVRMVControls * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *fastForward )( 
            IDVRMVControls * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *fastReverse )( 
            IDVRMVControls * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_currentPosition )( 
            IDVRMVControls * This,
            /* [retval][out] */ DOUBLE *pdCurrentPosition);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_currentPosition )( 
            IDVRMVControls * This,
            /* [in] */ DOUBLE dCurrentPosition);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_currentPositionString )( 
            IDVRMVControls * This,
            /* [retval][out] */ BSTR *pbstrCurrentPosition);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_isAvailable )( 
            IDVRMVControls * This,
            /* [in] */ BSTR bstrItem,
            /* [retval][out] */ VARIANT_BOOL *pIsAvailable);
        
        END_INTERFACE
    } IDVRMVControlsVtbl;

    interface IDVRMVControls
    {
        CONST_VTBL struct IDVRMVControlsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDVRMVControls_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDVRMVControls_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDVRMVControls_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDVRMVControls_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IDVRMVControls_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IDVRMVControls_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IDVRMVControls_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IDVRMVControls_play(This)	\
    ( (This)->lpVtbl -> play(This) ) 

#define IDVRMVControls_stop(This)	\
    ( (This)->lpVtbl -> stop(This) ) 

#define IDVRMVControls_pause(This)	\
    ( (This)->lpVtbl -> pause(This) ) 

#define IDVRMVControls_fastForward(This)	\
    ( (This)->lpVtbl -> fastForward(This) ) 

#define IDVRMVControls_fastReverse(This)	\
    ( (This)->lpVtbl -> fastReverse(This) ) 

#define IDVRMVControls_get_currentPosition(This,pdCurrentPosition)	\
    ( (This)->lpVtbl -> get_currentPosition(This,pdCurrentPosition) ) 

#define IDVRMVControls_put_currentPosition(This,dCurrentPosition)	\
    ( (This)->lpVtbl -> put_currentPosition(This,dCurrentPosition) ) 

#define IDVRMVControls_get_currentPositionString(This,pbstrCurrentPosition)	\
    ( (This)->lpVtbl -> get_currentPositionString(This,pbstrCurrentPosition) ) 

#define IDVRMVControls_get_isAvailable(This,bstrItem,pIsAvailable)	\
    ( (This)->lpVtbl -> get_isAvailable(This,bstrItem,pIsAvailable) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDVRMVControls_INTERFACE_DEFINED__ */


#ifndef __IDVRMVSettings_INTERFACE_DEFINED__
#define __IDVRMVSettings_INTERFACE_DEFINED__

/* interface IDVRMVSettings */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IDVRMVSettings;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7D45535F-3ECE-4bd7-A868-C1B2A8128A76")
    IDVRMVSettings : public IDispatch
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

    typedef struct IDVRMVSettingsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDVRMVSettings * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDVRMVSettings * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDVRMVSettings * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDVRMVSettings * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDVRMVSettings * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDVRMVSettings * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDVRMVSettings * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_mute )( 
            IDVRMVSettings * This,
            /* [retval][out] */ VARIANT_BOOL *pfMute);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_mute )( 
            IDVRMVSettings * This,
            /* [in] */ VARIANT_BOOL fMute);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_volume )( 
            IDVRMVSettings * This,
            /* [retval][out] */ LONG *plVolume);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_volume )( 
            IDVRMVSettings * This,
            /* [in] */ LONG lVolume);
        
        END_INTERFACE
    } IDVRMVSettingsVtbl;

    interface IDVRMVSettings
    {
        CONST_VTBL struct IDVRMVSettingsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDVRMVSettings_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDVRMVSettings_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDVRMVSettings_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDVRMVSettings_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IDVRMVSettings_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IDVRMVSettings_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IDVRMVSettings_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IDVRMVSettings_get_mute(This,pfMute)	\
    ( (This)->lpVtbl -> get_mute(This,pfMute) ) 

#define IDVRMVSettings_put_mute(This,fMute)	\
    ( (This)->lpVtbl -> put_mute(This,fMute) ) 

#define IDVRMVSettings_get_volume(This,plVolume)	\
    ( (This)->lpVtbl -> get_volume(This,plVolume) ) 

#define IDVRMVSettings_put_volume(This,lVolume)	\
    ( (This)->lpVtbl -> put_volume(This,lVolume) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDVRMVSettings_INTERFACE_DEFINED__ */


#ifndef __IDVRMVMedia_INTERFACE_DEFINED__
#define __IDVRMVMedia_INTERFACE_DEFINED__

/* interface IDVRMVMedia */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IDVRMVMedia;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("842D4D89-DB49-43d9-8AA6-44D4483FBFC3")
    IDVRMVMedia : public IDispatch
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

    typedef struct IDVRMVMediaVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDVRMVMedia * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDVRMVMedia * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDVRMVMedia * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDVRMVMedia * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDVRMVMedia * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDVRMVMedia * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDVRMVMedia * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_imageSourceWidth )( 
            IDVRMVMedia * This,
            /* [retval][out] */ LONG *pWidth);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_imageSourceHeight )( 
            IDVRMVMedia * This,
            /* [retval][out] */ LONG *pHeight);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_duration )( 
            IDVRMVMedia * This,
            /* [retval][out] */ DOUBLE *pDuration);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_durationString )( 
            IDVRMVMedia * This,
            /* [retval][out] */ BSTR *pbstrDuration);
        
        END_INTERFACE
    } IDVRMVMediaVtbl;

    interface IDVRMVMedia
    {
        CONST_VTBL struct IDVRMVMediaVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDVRMVMedia_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDVRMVMedia_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDVRMVMedia_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDVRMVMedia_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IDVRMVMedia_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IDVRMVMedia_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IDVRMVMedia_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IDVRMVMedia_get_imageSourceWidth(This,pWidth)	\
    ( (This)->lpVtbl -> get_imageSourceWidth(This,pWidth) ) 

#define IDVRMVMedia_get_imageSourceHeight(This,pHeight)	\
    ( (This)->lpVtbl -> get_imageSourceHeight(This,pHeight) ) 

#define IDVRMVMedia_get_duration(This,pDuration)	\
    ( (This)->lpVtbl -> get_duration(This,pDuration) ) 

#define IDVRMVMedia_get_durationString(This,pbstrDuration)	\
    ( (This)->lpVtbl -> get_durationString(This,pbstrDuration) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDVRMVMedia_INTERFACE_DEFINED__ */


#ifndef __IDVRMVPlayer_INTERFACE_DEFINED__
#define __IDVRMVPlayer_INTERFACE_DEFINED__

/* interface IDVRMVPlayer */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IDVRMVPlayer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1EF48C0B-67B9-489D-92F4-0C1453F613E8")
    IDVRMVPlayer : public IDispatch
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
            /* [retval][out] */ IDVRMVControls **ppControl) = 0;
        
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
            /* [retval][out] */ IDVRMVSettings **ppSettings) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_mute( 
            /* [retval][out] */ VARIANT_BOOL *pfMute) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_mute( 
            /* [in] */ VARIANT_BOOL fMute) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_volume( 
            /* [retval][out] */ LONG *plVolume) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_volume( 
            /* [in] */ LONG lVolume) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_currentMedia( 
            /* [retval][out] */ IDVRMVMedia **ppMedia) = 0;
        
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

    typedef struct IDVRMVPlayerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDVRMVPlayer * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDVRMVPlayer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDVRMVPlayer * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDVRMVPlayer * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDVRMVPlayer * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDVRMVPlayer * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDVRMVPlayer * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_URL )( 
            IDVRMVPlayer * This,
            /* [retval][out] */ BSTR *pbstrURL);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_URL )( 
            IDVRMVPlayer * This,
            /* [in] */ BSTR bstrURL);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_fullScreen )( 
            IDVRMVPlayer * This,
            /* [retval][out] */ VARIANT_BOOL *pbFullScreen);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_fullScreen )( 
            IDVRMVPlayer * This,
            /* [in] */ VARIANT_BOOL bFullScreen);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_uiMode )( 
            IDVRMVPlayer * This,
            /* [retval][out] */ BSTR *pbstrMode);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_uiMode )( 
            IDVRMVPlayer * This,
            /* [in] */ BSTR bstrMode);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_status )( 
            IDVRMVPlayer * This,
            /* [retval][out] */ BSTR *pbstrStatus);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_playState )( 
            IDVRMVPlayer * This,
            /* [retval][out] */ LONG *plState);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_versionInfo )( 
            IDVRMVPlayer * This,
            /* [retval][out] */ BSTR *pbstrVersionInfo);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *close )( 
            IDVRMVPlayer * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_controls )( 
            IDVRMVPlayer * This,
            /* [retval][out] */ IDVRMVControls **ppControl);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *play )( 
            IDVRMVPlayer * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *stop )( 
            IDVRMVPlayer * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *pause )( 
            IDVRMVPlayer * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *fastForward )( 
            IDVRMVPlayer * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *fastReverse )( 
            IDVRMVPlayer * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_currentPosition )( 
            IDVRMVPlayer * This,
            /* [retval][out] */ DOUBLE *pdCurrentPosition);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_currentPosition )( 
            IDVRMVPlayer * This,
            /* [in] */ DOUBLE dCurrentPosition);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_currentPositionString )( 
            IDVRMVPlayer * This,
            /* [retval][out] */ BSTR *pbstrCurrentPosition);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_isAvailable )( 
            IDVRMVPlayer * This,
            /* [in] */ BSTR bstrItem,
            /* [retval][out] */ VARIANT_BOOL *pIsAvailable);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_settings )( 
            IDVRMVPlayer * This,
            /* [retval][out] */ IDVRMVSettings **ppSettings);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_mute )( 
            IDVRMVPlayer * This,
            /* [retval][out] */ VARIANT_BOOL *pfMute);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_mute )( 
            IDVRMVPlayer * This,
            /* [in] */ VARIANT_BOOL fMute);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_volume )( 
            IDVRMVPlayer * This,
            /* [retval][out] */ LONG *plVolume);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_volume )( 
            IDVRMVPlayer * This,
            /* [in] */ LONG lVolume);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_currentMedia )( 
            IDVRMVPlayer * This,
            /* [retval][out] */ IDVRMVMedia **ppMedia);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_imageSourceWidth )( 
            IDVRMVPlayer * This,
            /* [retval][out] */ LONG *pWidth);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_imageSourceHeight )( 
            IDVRMVPlayer * This,
            /* [retval][out] */ LONG *pHeight);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_duration )( 
            IDVRMVPlayer * This,
            /* [retval][out] */ DOUBLE *pDuration);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_durationString )( 
            IDVRMVPlayer * This,
            /* [retval][out] */ BSTR *pbstrDuration);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OpenFile )( 
            IDVRMVPlayer * This,
            /* [in] */ BSTR bstrMediaFile);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Login )( 
            IDVRMVPlayer * This,
            /* [in] */ BSTR bstrUsername,
            /* [in] */ BSTR bstrPassword,
            /* [in] */ BSTR bstrIP,
            /* [in] */ LONG lPort);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Logout )( 
            IDVRMVPlayer * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetMediaServer )( 
            IDVRMVPlayer * This,
            /* [in] */ BSTR bstrMediaServerIP,
            /* [in] */ LONG lPort);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetMediaServer )( 
            IDVRMVPlayer * This,
            /* [out] */ BSTR *bstrMediaServerIP,
            /* [out] */ LONG *lPort);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StartMonitor )( 
            IDVRMVPlayer * This,
            /* [in] */ LONG lWndNum);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StopMonitor )( 
            IDVRMVPlayer * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CapPic )( 
            IDVRMVPlayer * This,
            /* [out] */ BSTR *pCapPicPath);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCapturePath )( 
            IDVRMVPlayer * This,
            /* [out] */ BSTR *pbstrCapFolder);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetCapturePath )( 
            IDVRMVPlayer * This,
            /* [in] */ BSTR bstrCapFolder);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ShowMetaData )( 
            IDVRMVPlayer * This,
            /* [in] */ VARIANT_BOOL bShow);
        
        END_INTERFACE
    } IDVRMVPlayerVtbl;

    interface IDVRMVPlayer
    {
        CONST_VTBL struct IDVRMVPlayerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDVRMVPlayer_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDVRMVPlayer_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDVRMVPlayer_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDVRMVPlayer_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IDVRMVPlayer_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IDVRMVPlayer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IDVRMVPlayer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IDVRMVPlayer_get_URL(This,pbstrURL)	\
    ( (This)->lpVtbl -> get_URL(This,pbstrURL) ) 

#define IDVRMVPlayer_put_URL(This,bstrURL)	\
    ( (This)->lpVtbl -> put_URL(This,bstrURL) ) 

#define IDVRMVPlayer_get_fullScreen(This,pbFullScreen)	\
    ( (This)->lpVtbl -> get_fullScreen(This,pbFullScreen) ) 

#define IDVRMVPlayer_put_fullScreen(This,bFullScreen)	\
    ( (This)->lpVtbl -> put_fullScreen(This,bFullScreen) ) 

#define IDVRMVPlayer_get_uiMode(This,pbstrMode)	\
    ( (This)->lpVtbl -> get_uiMode(This,pbstrMode) ) 

#define IDVRMVPlayer_put_uiMode(This,bstrMode)	\
    ( (This)->lpVtbl -> put_uiMode(This,bstrMode) ) 

#define IDVRMVPlayer_get_status(This,pbstrStatus)	\
    ( (This)->lpVtbl -> get_status(This,pbstrStatus) ) 

#define IDVRMVPlayer_get_playState(This,plState)	\
    ( (This)->lpVtbl -> get_playState(This,plState) ) 

#define IDVRMVPlayer_get_versionInfo(This,pbstrVersionInfo)	\
    ( (This)->lpVtbl -> get_versionInfo(This,pbstrVersionInfo) ) 

#define IDVRMVPlayer_close(This)	\
    ( (This)->lpVtbl -> close(This) ) 

#define IDVRMVPlayer_get_controls(This,ppControl)	\
    ( (This)->lpVtbl -> get_controls(This,ppControl) ) 

#define IDVRMVPlayer_play(This)	\
    ( (This)->lpVtbl -> play(This) ) 

#define IDVRMVPlayer_stop(This)	\
    ( (This)->lpVtbl -> stop(This) ) 

#define IDVRMVPlayer_pause(This)	\
    ( (This)->lpVtbl -> pause(This) ) 

#define IDVRMVPlayer_fastForward(This)	\
    ( (This)->lpVtbl -> fastForward(This) ) 

#define IDVRMVPlayer_fastReverse(This)	\
    ( (This)->lpVtbl -> fastReverse(This) ) 

#define IDVRMVPlayer_get_currentPosition(This,pdCurrentPosition)	\
    ( (This)->lpVtbl -> get_currentPosition(This,pdCurrentPosition) ) 

#define IDVRMVPlayer_put_currentPosition(This,dCurrentPosition)	\
    ( (This)->lpVtbl -> put_currentPosition(This,dCurrentPosition) ) 

#define IDVRMVPlayer_get_currentPositionString(This,pbstrCurrentPosition)	\
    ( (This)->lpVtbl -> get_currentPositionString(This,pbstrCurrentPosition) ) 

#define IDVRMVPlayer_get_isAvailable(This,bstrItem,pIsAvailable)	\
    ( (This)->lpVtbl -> get_isAvailable(This,bstrItem,pIsAvailable) ) 

#define IDVRMVPlayer_get_settings(This,ppSettings)	\
    ( (This)->lpVtbl -> get_settings(This,ppSettings) ) 

#define IDVRMVPlayer_get_mute(This,pfMute)	\
    ( (This)->lpVtbl -> get_mute(This,pfMute) ) 

#define IDVRMVPlayer_put_mute(This,fMute)	\
    ( (This)->lpVtbl -> put_mute(This,fMute) ) 

#define IDVRMVPlayer_get_volume(This,plVolume)	\
    ( (This)->lpVtbl -> get_volume(This,plVolume) ) 

#define IDVRMVPlayer_put_volume(This,lVolume)	\
    ( (This)->lpVtbl -> put_volume(This,lVolume) ) 

#define IDVRMVPlayer_get_currentMedia(This,ppMedia)	\
    ( (This)->lpVtbl -> get_currentMedia(This,ppMedia) ) 

#define IDVRMVPlayer_get_imageSourceWidth(This,pWidth)	\
    ( (This)->lpVtbl -> get_imageSourceWidth(This,pWidth) ) 

#define IDVRMVPlayer_get_imageSourceHeight(This,pHeight)	\
    ( (This)->lpVtbl -> get_imageSourceHeight(This,pHeight) ) 

#define IDVRMVPlayer_get_duration(This,pDuration)	\
    ( (This)->lpVtbl -> get_duration(This,pDuration) ) 

#define IDVRMVPlayer_get_durationString(This,pbstrDuration)	\
    ( (This)->lpVtbl -> get_durationString(This,pbstrDuration) ) 

#define IDVRMVPlayer_OpenFile(This,bstrMediaFile)	\
    ( (This)->lpVtbl -> OpenFile(This,bstrMediaFile) ) 

#define IDVRMVPlayer_Login(This,bstrUsername,bstrPassword,bstrIP,lPort)	\
    ( (This)->lpVtbl -> Login(This,bstrUsername,bstrPassword,bstrIP,lPort) ) 

#define IDVRMVPlayer_Logout(This)	\
    ( (This)->lpVtbl -> Logout(This) ) 

#define IDVRMVPlayer_SetMediaServer(This,bstrMediaServerIP,lPort)	\
    ( (This)->lpVtbl -> SetMediaServer(This,bstrMediaServerIP,lPort) ) 

#define IDVRMVPlayer_GetMediaServer(This,bstrMediaServerIP,lPort)	\
    ( (This)->lpVtbl -> GetMediaServer(This,bstrMediaServerIP,lPort) ) 

#define IDVRMVPlayer_StartMonitor(This,lWndNum)	\
    ( (This)->lpVtbl -> StartMonitor(This,lWndNum) ) 

#define IDVRMVPlayer_StopMonitor(This)	\
    ( (This)->lpVtbl -> StopMonitor(This) ) 

#define IDVRMVPlayer_CapPic(This,pCapPicPath)	\
    ( (This)->lpVtbl -> CapPic(This,pCapPicPath) ) 

#define IDVRMVPlayer_GetCapturePath(This,pbstrCapFolder)	\
    ( (This)->lpVtbl -> GetCapturePath(This,pbstrCapFolder) ) 

#define IDVRMVPlayer_SetCapturePath(This,bstrCapFolder)	\
    ( (This)->lpVtbl -> SetCapturePath(This,bstrCapFolder) ) 

#define IDVRMVPlayer_ShowMetaData(This,bShow)	\
    ( (This)->lpVtbl -> ShowMetaData(This,bShow) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDVRMVPlayer_INTERFACE_DEFINED__ */



#ifndef __DVRMVPlayerLib_LIBRARY_DEFINED__
#define __DVRMVPlayerLib_LIBRARY_DEFINED__

/* library DVRMVPlayerLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_DVRMVPlayerLib;

#ifndef ___IDVRMVPlayerCtrlEvents_DISPINTERFACE_DEFINED__
#define ___IDVRMVPlayerCtrlEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IDVRMVPlayerCtrlEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IDVRMVPlayerCtrlEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("3492600D-3F55-4EDE-9901-F767D18C3497")
    _IDVRMVPlayerCtrlEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IDVRMVPlayerCtrlEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IDVRMVPlayerCtrlEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IDVRMVPlayerCtrlEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IDVRMVPlayerCtrlEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IDVRMVPlayerCtrlEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IDVRMVPlayerCtrlEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IDVRMVPlayerCtrlEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IDVRMVPlayerCtrlEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IDVRMVPlayerCtrlEventsVtbl;

    interface _IDVRMVPlayerCtrlEvents
    {
        CONST_VTBL struct _IDVRMVPlayerCtrlEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IDVRMVPlayerCtrlEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IDVRMVPlayerCtrlEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IDVRMVPlayerCtrlEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IDVRMVPlayerCtrlEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _IDVRMVPlayerCtrlEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _IDVRMVPlayerCtrlEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _IDVRMVPlayerCtrlEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IDVRMVPlayerCtrlEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_DVRMVPlayerCtrl;

#ifdef __cplusplus

class DECLSPEC_UUID("023D5C5C-2FFE-4054-8CE9-45C492778C52")
DVRMVPlayerCtrl;
#endif

EXTERN_C const CLSID CLSID_DVRMVPlayerProp;

#ifdef __cplusplus

class DECLSPEC_UUID("D9D9CCA7-2BE1-4E1D-8D88-E7F4CBB3E34B")
DVRMVPlayerProp;
#endif
#endif /* __DVRMVPlayerLib_LIBRARY_DEFINED__ */

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


