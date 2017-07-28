 #pragma once
#include "Serialize.h"

class Serialize__PROCESS_MEMORY_COUNTERS : public Serialize_StructBase<_PROCESS_MEMORY_COUNTERS,Serialize__PROCESS_MEMORY_COUNTERS>
{
	public:
	typedef _PROCESS_MEMORY_COUNTERS _MyObjectType;
 
	Serialize_BaseObject<DWORD> cb; 
	Serialize_BaseObject<DWORD> PageFaultCount; 
	Serialize_BaseObject<SIZE_T> PeakWorkingSetSize; 
	Serialize_BaseObject<SIZE_T> WorkingSetSize; 
	Serialize_BaseObject<SIZE_T> QuotaPeakPagedPoolUsage; 
	Serialize_BaseObject<SIZE_T> QuotaPagedPoolUsage; 
	Serialize_BaseObject<SIZE_T> QuotaPeakNonPagedPoolUsage; 
	Serialize_BaseObject<SIZE_T> QuotaNonPagedPoolUsage; 
	Serialize_BaseObject<SIZE_T> PagefileUsage; 
	Serialize_BaseObject<SIZE_T> PeakPagefileUsage;

 	Serialize__PROCESS_MEMORY_COUNTERS(){};
	~Serialize__PROCESS_MEMORY_COUNTERS(){};
 	_Myt& operator=(_PROCESS_MEMORY_COUNTERS & _X)
	{
		SetData(_X);
		return *this;
	}
 	void GetData()
	{
		m_Val.cb=cb; 
		m_Val.PageFaultCount=PageFaultCount; 
		m_Val.PeakWorkingSetSize=PeakWorkingSetSize; 
		m_Val.WorkingSetSize=WorkingSetSize; 
		m_Val.QuotaPeakPagedPoolUsage=QuotaPeakPagedPoolUsage; 
		m_Val.QuotaPagedPoolUsage=QuotaPagedPoolUsage; 
		m_Val.QuotaPeakNonPagedPoolUsage=QuotaPeakNonPagedPoolUsage; 
		m_Val.QuotaNonPagedPoolUsage=QuotaNonPagedPoolUsage; 
		m_Val.PagefileUsage=PagefileUsage; 
		m_Val.PeakPagefileUsage=PeakPagefileUsage;
	}
 	BOOL Construct(StorageObjectInterface * pOutObject)
	{
		cb.init(this,_T("cb"),0,pOutObject); 
		PageFaultCount.init(this,_T("PageFaultCount"),0,pOutObject); 
		PeakWorkingSetSize.init(this,_T("PeakWorkingSetSize"),0,pOutObject); 
		WorkingSetSize.init(this,_T("WorkingSetSize"),0,pOutObject); 
		QuotaPeakPagedPoolUsage.init(this,_T("QuotaPeakPagedPoolUsage"),0,pOutObject); 
		QuotaPagedPoolUsage.init(this,_T("QuotaPagedPoolUsage"),0,pOutObject); 
		QuotaPeakNonPagedPoolUsage.init(this,_T("QuotaPeakNonPagedPoolUsage"),0,pOutObject); 
		QuotaNonPagedPoolUsage.init(this,_T("QuotaNonPagedPoolUsage"),0,pOutObject); 
		PagefileUsage.init(this,_T("PagefileUsage"),0,pOutObject); 
		PeakPagefileUsage.init(this,_T("PeakPagefileUsage"),0,pOutObject);
		return TRUE;
	}
 	void SetData(_PROCESS_MEMORY_COUNTERS & _X)
	{
		cb=_X.cb; 
		PageFaultCount=_X.PageFaultCount; 
		PeakWorkingSetSize=_X.PeakWorkingSetSize; 
		WorkingSetSize=_X.WorkingSetSize; 
		QuotaPeakPagedPoolUsage=_X.QuotaPeakPagedPoolUsage; 
		QuotaPagedPoolUsage=_X.QuotaPagedPoolUsage; 
		QuotaPeakNonPagedPoolUsage=_X.QuotaPeakNonPagedPoolUsage; 
		QuotaNonPagedPoolUsage=_X.QuotaNonPagedPoolUsage; 
		PagefileUsage=_X.PagefileUsage; 
		PeakPagefileUsage=_X.PeakPagefileUsage;
	}
 	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
	{
		*RetObj=0;
		if(tstring(CurFieldAddr.pFieldName)==tstring(_T("cb")))
		{
			*RetObj=&cb;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("PageFaultCount")))
		{
			*RetObj=&PageFaultCount;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("PeakWorkingSetSize")))
		{
			*RetObj=&PeakWorkingSetSize;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("WorkingSetSize")))
		{
			*RetObj=&WorkingSetSize;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("QuotaPeakPagedPoolUsage")))
		{
			*RetObj=&QuotaPeakPagedPoolUsage;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("QuotaPagedPoolUsage")))
		{
			*RetObj=&QuotaPagedPoolUsage;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("QuotaPeakNonPagedPoolUsage")))
		{
			*RetObj=&QuotaPeakNonPagedPoolUsage;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("QuotaNonPagedPoolUsage")))
		{
			*RetObj=&QuotaNonPagedPoolUsage;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("PagefileUsage")))
		{
			*RetObj=&PagefileUsage;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("PeakPagefileUsage")))
		{
			*RetObj=&PeakPagefileUsage;
		}
		if(*RetObj) return TRUE;
		return FALSE;
	}
 	BOOL Save(StorageObjectInterface * pStorageObject)
	{
		pStorageObject->PushNodeCtlBegin(_T("_PROCESS_MEMORY_COUNTERS"),this);

		cb.Save(pStorageObject); 
		PageFaultCount.Save(pStorageObject); 
		PeakWorkingSetSize.Save(pStorageObject); 
		WorkingSetSize.Save(pStorageObject); 
		QuotaPeakPagedPoolUsage.Save(pStorageObject); 
		QuotaPagedPoolUsage.Save(pStorageObject); 
		QuotaPeakNonPagedPoolUsage.Save(pStorageObject); 
		QuotaNonPagedPoolUsage.Save(pStorageObject); 
		PagefileUsage.Save(pStorageObject); 
		PeakPagefileUsage.Save(pStorageObject);

		pStorageObject->PushNodeCtlEnd(_T("_PROCESS_MEMORY_COUNTERS"),this);
		return TRUE;
	}
 	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
	{

		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&cb); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&PageFaultCount); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&PeakWorkingSetSize); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&WorkingSetSize); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&QuotaPeakPagedPoolUsage); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&QuotaPagedPoolUsage); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&QuotaPeakNonPagedPoolUsage); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&QuotaNonPagedPoolUsage); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&PagefileUsage); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&PeakPagefileUsage);
		return TRUE;
	}
 

};
