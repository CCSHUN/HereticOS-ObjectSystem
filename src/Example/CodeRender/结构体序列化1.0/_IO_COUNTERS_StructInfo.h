 #pragma once
#include "Serialize.h"

class Serialize__IO_COUNTERS : public Serialize_StructBase<_IO_COUNTERS,Serialize__IO_COUNTERS>
{
	public:
	typedef _IO_COUNTERS _MyObjectType;
 
	Serialize_BaseObject<ULONGLONG> ReadOperationCount; 
	Serialize_BaseObject<ULONGLONG> WriteOperationCount; 
	Serialize_BaseObject<ULONGLONG> OtherOperationCount; 
	Serialize_BaseObject<ULONGLONG> ReadTransferCount; 
	Serialize_BaseObject<ULONGLONG> WriteTransferCount; 
	Serialize_BaseObject<ULONGLONG> OtherTransferCount;

 	Serialize__IO_COUNTERS(){};
	~Serialize__IO_COUNTERS(){};
 	_Myt& operator=(_IO_COUNTERS & _X)
	{
		SetData(_X);
		return *this;
	}
 	void GetData()
	{
		m_Val.ReadOperationCount=ReadOperationCount; 
		m_Val.WriteOperationCount=WriteOperationCount; 
		m_Val.OtherOperationCount=OtherOperationCount; 
		m_Val.ReadTransferCount=ReadTransferCount; 
		m_Val.WriteTransferCount=WriteTransferCount; 
		m_Val.OtherTransferCount=OtherTransferCount;
	}
 	BOOL Construct(StorageObjectInterface * pOutObject)
	{
		ReadOperationCount.init(this,_T("ReadOperationCount"),0,pOutObject); 
		WriteOperationCount.init(this,_T("WriteOperationCount"),0,pOutObject); 
		OtherOperationCount.init(this,_T("OtherOperationCount"),0,pOutObject); 
		ReadTransferCount.init(this,_T("ReadTransferCount"),0,pOutObject); 
		WriteTransferCount.init(this,_T("WriteTransferCount"),0,pOutObject); 
		OtherTransferCount.init(this,_T("OtherTransferCount"),0,pOutObject);
		return TRUE;
	}
 	void SetData(_IO_COUNTERS & _X)
	{
		ReadOperationCount=_X.ReadOperationCount; 
		WriteOperationCount=_X.WriteOperationCount; 
		OtherOperationCount=_X.OtherOperationCount; 
		ReadTransferCount=_X.ReadTransferCount; 
		WriteTransferCount=_X.WriteTransferCount; 
		OtherTransferCount=_X.OtherTransferCount;
	}
 	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
	{
		*RetObj=0;
		if(tstring(CurFieldAddr.pFieldName)==tstring(_T("ReadOperationCount")))
		{
			*RetObj=&ReadOperationCount;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("WriteOperationCount")))
		{
			*RetObj=&WriteOperationCount;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("OtherOperationCount")))
		{
			*RetObj=&OtherOperationCount;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("ReadTransferCount")))
		{
			*RetObj=&ReadTransferCount;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("WriteTransferCount")))
		{
			*RetObj=&WriteTransferCount;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("OtherTransferCount")))
		{
			*RetObj=&OtherTransferCount;
		}
		if(*RetObj) return TRUE;
		return FALSE;
	}
 	BOOL Save(StorageObjectInterface * pStorageObject)
	{
		pStorageObject->PushNodeCtlBegin(_T("_IO_COUNTERS"),this);

		ReadOperationCount.Save(pStorageObject); 
		WriteOperationCount.Save(pStorageObject); 
		OtherOperationCount.Save(pStorageObject); 
		ReadTransferCount.Save(pStorageObject); 
		WriteTransferCount.Save(pStorageObject); 
		OtherTransferCount.Save(pStorageObject);

		pStorageObject->PushNodeCtlEnd(_T("_IO_COUNTERS"),this);
		return TRUE;
	}
 	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
	{

		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&ReadOperationCount); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&WriteOperationCount); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&OtherOperationCount); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&ReadTransferCount); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&WriteTransferCount); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&OtherTransferCount);
		return TRUE;
	}
 

};
