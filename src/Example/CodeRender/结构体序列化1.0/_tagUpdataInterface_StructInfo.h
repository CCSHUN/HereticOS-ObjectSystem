 #pragma once
#include "Serialize.h"

class Serialize__tagUpdataInterface : public Serialize_StructBase<_tagUpdataInterface,Serialize__tagUpdataInterface>
{
	public:
	typedef _tagUpdataInterface _MyObjectType;
 
	Serialize_BaseObject<tstring> Ver; 
	Serialize_vector< Serialize_BaseObject<tstring>> UpadataInterfaceList;

 	Serialize__tagUpdataInterface(){};
	~Serialize__tagUpdataInterface(){};
 	_Myt& operator=(_tagUpdataInterface & _X)
	{
		SetData(_X);
		return *this;
	}
 	void GetData()
	{
		m_Val.Ver=Ver; 
		m_Val.UpadataInterfaceList=UpadataInterfaceList;
	}
 	BOOL Construct(StorageObjectInterface * pOutObject)
	{
		Ver.init(this,_T("Ver"),0,pOutObject); 
		UpadataInterfaceList.init(this,_T("UpadataInterfaceList"),0,pOutObject);
		return TRUE;
	}
 	void SetData(_tagUpdataInterface & _X)
	{
		Ver=_X.Ver; 
		UpadataInterfaceList=_X.UpadataInterfaceList;
	}
 	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
	{
		*RetObj=0;
		if(tstring(CurFieldAddr.pFieldName)==tstring(_T("Ver")))
		{
			*RetObj=&Ver;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("UpadataInterfaceList")))
		{
			*RetObj=&UpadataInterfaceList;
		}
		if(*RetObj) return TRUE;
		return FALSE;
	}
 	BOOL Save(StorageObjectInterface * pStorageObject)
	{
		pStorageObject->PushNodeCtlBegin(_T("_tagUpdataInterface"),this);

		Ver.Save(pStorageObject); 
		UpadataInterfaceList.Save(pStorageObject);

		pStorageObject->PushNodeCtlEnd(_T("_tagUpdataInterface"),this);
		return TRUE;
	}
 	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
	{

		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&Ver); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&UpadataInterfaceList);
		return TRUE;
	}
 

};
