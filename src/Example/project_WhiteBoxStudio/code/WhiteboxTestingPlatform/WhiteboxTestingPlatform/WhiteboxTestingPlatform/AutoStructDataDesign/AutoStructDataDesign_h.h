

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Fri Nov 22 16:22:22 2013
 */
/* Compiler settings for .\AutoStructDataDesign.idl:
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


#ifndef __AutoStructDataDesign_h_h__
#define __AutoStructDataDesign_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IAutoStructDataDesign_FWD_DEFINED__
#define __IAutoStructDataDesign_FWD_DEFINED__
typedef interface IAutoStructDataDesign IAutoStructDataDesign;
#endif 	/* __IAutoStructDataDesign_FWD_DEFINED__ */


#ifndef __AutoStructDataDesign_FWD_DEFINED__
#define __AutoStructDataDesign_FWD_DEFINED__

#ifdef __cplusplus
typedef class AutoStructDataDesign AutoStructDataDesign;
#else
typedef struct AutoStructDataDesign AutoStructDataDesign;
#endif /* __cplusplus */

#endif 	/* __AutoStructDataDesign_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __AutoStructDataDesign_LIBRARY_DEFINED__
#define __AutoStructDataDesign_LIBRARY_DEFINED__

/* library AutoStructDataDesign */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_AutoStructDataDesign;

#ifndef __IAutoStructDataDesign_DISPINTERFACE_DEFINED__
#define __IAutoStructDataDesign_DISPINTERFACE_DEFINED__

/* dispinterface IAutoStructDataDesign */
/* [uuid] */ 


EXTERN_C const IID DIID_IAutoStructDataDesign;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("63A4B192-BE39-4A4A-8715-08899BC5F756")
    IAutoStructDataDesign : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IAutoStructDataDesignVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAutoStructDataDesign * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAutoStructDataDesign * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAutoStructDataDesign * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IAutoStructDataDesign * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IAutoStructDataDesign * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IAutoStructDataDesign * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IAutoStructDataDesign * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IAutoStructDataDesignVtbl;

    interface IAutoStructDataDesign
    {
        CONST_VTBL struct IAutoStructDataDesignVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAutoStructDataDesign_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAutoStructDataDesign_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAutoStructDataDesign_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAutoStructDataDesign_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IAutoStructDataDesign_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IAutoStructDataDesign_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IAutoStructDataDesign_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IAutoStructDataDesign_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_AutoStructDataDesign;

#ifdef __cplusplus

class DECLSPEC_UUID("33378D5A-5F55-4986-9FC9-704A62084595")
AutoStructDataDesign;
#endif
#endif /* __AutoStructDataDesign_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


