

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Tue Jul 02 17:21:44 2013
 */
/* Compiler settings for .\ObjectSystemComServer.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

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

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __ObjectSystemComServer_i_h__
#define __ObjectSystemComServer_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IObjectSystem_FWD_DEFINED__
#define __IObjectSystem_FWD_DEFINED__
typedef interface IObjectSystem IObjectSystem;
#endif 	/* __IObjectSystem_FWD_DEFINED__ */


#ifndef __ObjectSystem_FWD_DEFINED__
#define __ObjectSystem_FWD_DEFINED__

#ifdef __cplusplus
typedef class ObjectSystem ObjectSystem;
#else
typedef struct ObjectSystem ObjectSystem;
#endif /* __cplusplus */

#endif 	/* __ObjectSystem_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IObjectSystem_INTERFACE_DEFINED__
#define __IObjectSystem_INTERFACE_DEFINED__

/* interface IObjectSystem */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IObjectSystem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EE8C24CA-76D4-46AC-9AA9-A5F6D581962A")
    IObjectSystem : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CallInterface( 
            /* [in] */ BSTR szUserName,
            /* [in] */ BSTR szConversation,
            /* [in] */ int nOpCode,
            /* [in] */ BSTR szCallParameter,
            /* [retval][out] */ BSTR *szRetXml) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IObjectSystemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IObjectSystem * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IObjectSystem * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IObjectSystem * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IObjectSystem * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IObjectSystem * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IObjectSystem * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IObjectSystem * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CallInterface )( 
            IObjectSystem * This,
            /* [in] */ BSTR szUserName,
            /* [in] */ BSTR szConversation,
            /* [in] */ int nOpCode,
            /* [in] */ BSTR szCallParameter,
            /* [retval][out] */ BSTR *szRetXml);
        
        END_INTERFACE
    } IObjectSystemVtbl;

    interface IObjectSystem
    {
        CONST_VTBL struct IObjectSystemVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IObjectSystem_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IObjectSystem_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IObjectSystem_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IObjectSystem_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IObjectSystem_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IObjectSystem_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IObjectSystem_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IObjectSystem_CallInterface(This,szUserName,szConversation,nOpCode,szCallParameter,szRetXml)	\
    ( (This)->lpVtbl -> CallInterface(This,szUserName,szConversation,nOpCode,szCallParameter,szRetXml) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IObjectSystem_INTERFACE_DEFINED__ */



#ifndef __ObjectSystemComServerLib_LIBRARY_DEFINED__
#define __ObjectSystemComServerLib_LIBRARY_DEFINED__

/* library ObjectSystemComServerLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_ObjectSystemComServerLib;

EXTERN_C const CLSID CLSID_ObjectSystem;

#ifdef __cplusplus

class DECLSPEC_UUID("81AF9FBD-95AF-4FA2-8B07-2844B3599891")
ObjectSystem;
#endif
#endif /* __ObjectSystemComServerLib_LIBRARY_DEFINED__ */

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


