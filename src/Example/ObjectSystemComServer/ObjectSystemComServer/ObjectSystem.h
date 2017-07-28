// ObjectSystem.h : CObjectSystem µÄÉùÃ÷

#pragma once
#include "resource.h"       // Ö÷·ûºÅ

#include "ObjectSystemComServer_i.h"




// CObjectSystem

class ATL_NO_VTABLE CObjectSystem :
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CObjectSystem, &CLSID_ObjectSystem>,
	public IDispatchImpl<IObjectSystem, &IID_IObjectSystem, &LIBID_ObjectSystemComServerLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CObjectSystem()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_OBJECTSYSTEM)


BEGIN_COM_MAP(CObjectSystem)
	COM_INTERFACE_ENTRY(IObjectSystem)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:

	STDMETHOD(CallInterface)(BSTR szUserName, BSTR szConversation, int nOpCode, BSTR szCallParameter, BSTR* szRetXml);
};

OBJECT_ENTRY_AUTO(__uuidof(ObjectSystem), CObjectSystem)
