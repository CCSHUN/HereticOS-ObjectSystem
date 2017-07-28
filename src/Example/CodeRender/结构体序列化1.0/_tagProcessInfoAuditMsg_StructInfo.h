 #pragma once
#include "Serialize.h"

class Serialize__tagProcessInfoAuditMsg : public Serialize_StructBase<_tagProcessInfoAuditMsg,Serialize__tagProcessInfoAuditMsg>
{
	public:
	typedef _tagProcessInfoAuditMsg _MyObjectType;
 
	Serialize_BaseObject<__int64> Processid; 
	Serialize_BaseObject<tstring> ProcessName; 
	Serialize_BaseObject<__int64> HandleCount; 
	Serialize_BaseObject<__int64> OtherOperationCount; 
	Serialize_BaseObject<__int64> OtherTransferCount; 
	Serialize_BaseObject<__int64> ReadOperationCount; 
	Serialize_BaseObject<__int64> ReadTransferCount; 
	Serialize_BaseObject<__int64> WriteOperationCount; 
	Serialize_BaseObject<__int64> WriteTransferCount; 
	Serialize_BaseObject<__int64> PageFaultCount; 
	Serialize_BaseObject<__int64> PagefileUsage; 
	Serialize_BaseObject<__int64> PeakPagefileUsage; 
	Serialize_BaseObject<__int64> PeakWorkingSetSize; 
	Serialize_BaseObject<__int64> QuotaNonPagedPoolUsage; 
	Serialize_BaseObject<__int64> QuotaPagedPoolUsage; 
	Serialize_BaseObject<__int64> QuotaPeakNonPagedPoolUsage; 
	Serialize_BaseObject<__int64> QuotaPeakPagedPoolUsage; 
	Serialize_BaseObject<__int64> WorkingSetSize; 
	Serialize_BaseObject<tstring> CreationTime; 
	Serialize_BaseObject<tstring> ExitTime; 
	Serialize_BaseObject<tstring> KernelTime; 
	Serialize_BaseObject<tstring> UserTime;

 	Serialize__tagProcessInfoAuditMsg(){};
	~Serialize__tagProcessInfoAuditMsg(){};
 	_Myt& operator=(_tagProcessInfoAuditMsg & _X)
	{
		SetData(_X);
		return *this;
	}
 	void GetData()
	{
		m_Val.Processid=Processid; 
		m_Val.ProcessName=ProcessName; 
		m_Val.HandleCount=HandleCount; 
		m_Val.OtherOperationCount=OtherOperationCount; 
		m_Val.OtherTransferCount=OtherTransferCount; 
		m_Val.ReadOperationCount=ReadOperationCount; 
		m_Val.ReadTransferCount=ReadTransferCount; 
		m_Val.WriteOperationCount=WriteOperationCount; 
		m_Val.WriteTransferCount=WriteTransferCount; 
		m_Val.PageFaultCount=PageFaultCount; 
		m_Val.PagefileUsage=PagefileUsage; 
		m_Val.PeakPagefileUsage=PeakPagefileUsage; 
		m_Val.PeakWorkingSetSize=PeakWorkingSetSize; 
		m_Val.QuotaNonPagedPoolUsage=QuotaNonPagedPoolUsage; 
		m_Val.QuotaPagedPoolUsage=QuotaPagedPoolUsage; 
		m_Val.QuotaPeakNonPagedPoolUsage=QuotaPeakNonPagedPoolUsage; 
		m_Val.QuotaPeakPagedPoolUsage=QuotaPeakPagedPoolUsage; 
		m_Val.WorkingSetSize=WorkingSetSize; 
		m_Val.CreationTime=CreationTime; 
		m_Val.ExitTime=ExitTime; 
		m_Val.KernelTime=KernelTime; 
		m_Val.UserTime=UserTime;
	}
 	BOOL Construct(StorageObjectInterface * pOutObject)
	{
		Processid.init(this,_T("Processid"),0,pOutObject); 
		ProcessName.init(this,_T("ProcessName"),0,pOutObject); 
		HandleCount.init(this,_T("HandleCount"),0,pOutObject); 
		OtherOperationCount.init(this,_T("OtherOperationCount"),0,pOutObject); 
		OtherTransferCount.init(this,_T("OtherTransferCount"),0,pOutObject); 
		ReadOperationCount.init(this,_T("ReadOperationCount"),0,pOutObject); 
		ReadTransferCount.init(this,_T("ReadTransferCount"),0,pOutObject); 
		WriteOperationCount.init(this,_T("WriteOperationCount"),0,pOutObject); 
		WriteTransferCount.init(this,_T("WriteTransferCount"),0,pOutObject); 
		PageFaultCount.init(this,_T("PageFaultCount"),0,pOutObject); 
		PagefileUsage.init(this,_T("PagefileUsage"),0,pOutObject); 
		PeakPagefileUsage.init(this,_T("PeakPagefileUsage"),0,pOutObject); 
		PeakWorkingSetSize.init(this,_T("PeakWorkingSetSize"),0,pOutObject); 
		QuotaNonPagedPoolUsage.init(this,_T("QuotaNonPagedPoolUsage"),0,pOutObject); 
		QuotaPagedPoolUsage.init(this,_T("QuotaPagedPoolUsage"),0,pOutObject); 
		QuotaPeakNonPagedPoolUsage.init(this,_T("QuotaPeakNonPagedPoolUsage"),0,pOutObject); 
		QuotaPeakPagedPoolUsage.init(this,_T("QuotaPeakPagedPoolUsage"),0,pOutObject); 
		WorkingSetSize.init(this,_T("WorkingSetSize"),0,pOutObject); 
		CreationTime.init(this,_T("CreationTime"),0,pOutObject); 
		ExitTime.init(this,_T("ExitTime"),0,pOutObject); 
		KernelTime.init(this,_T("KernelTime"),0,pOutObject); 
		UserTime.init(this,_T("UserTime"),0,pOutObject);
		return TRUE;
	}
 	void SetData(_tagProcessInfoAuditMsg & _X)
	{
		Processid=_X.Processid; 
		ProcessName=_X.ProcessName; 
		HandleCount=_X.HandleCount; 
		OtherOperationCount=_X.OtherOperationCount; 
		OtherTransferCount=_X.OtherTransferCount; 
		ReadOperationCount=_X.ReadOperationCount; 
		ReadTransferCount=_X.ReadTransferCount; 
		WriteOperationCount=_X.WriteOperationCount; 
		WriteTransferCount=_X.WriteTransferCount; 
		PageFaultCount=_X.PageFaultCount; 
		PagefileUsage=_X.PagefileUsage; 
		PeakPagefileUsage=_X.PeakPagefileUsage; 
		PeakWorkingSetSize=_X.PeakWorkingSetSize; 
		QuotaNonPagedPoolUsage=_X.QuotaNonPagedPoolUsage; 
		QuotaPagedPoolUsage=_X.QuotaPagedPoolUsage; 
		QuotaPeakNonPagedPoolUsage=_X.QuotaPeakNonPagedPoolUsage; 
		QuotaPeakPagedPoolUsage=_X.QuotaPeakPagedPoolUsage; 
		WorkingSetSize=_X.WorkingSetSize; 
		CreationTime=_X.CreationTime; 
		ExitTime=_X.ExitTime; 
		KernelTime=_X.KernelTime; 
		UserTime=_X.UserTime;
	}
 	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
	{
		*RetObj=0;
		if(tstring(CurFieldAddr.pFieldName)==tstring(_T("Processid")))
		{
			*RetObj=&Processid;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("ProcessName")))
		{
			*RetObj=&ProcessName;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("HandleCount")))
		{
			*RetObj=&HandleCount;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("OtherOperationCount")))
		{
			*RetObj=&OtherOperationCount;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("OtherTransferCount")))
		{
			*RetObj=&OtherTransferCount;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("ReadOperationCount")))
		{
			*RetObj=&ReadOperationCount;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("ReadTransferCount")))
		{
			*RetObj=&ReadTransferCount;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("WriteOperationCount")))
		{
			*RetObj=&WriteOperationCount;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("WriteTransferCount")))
		{
			*RetObj=&WriteTransferCount;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("PageFaultCount")))
		{
			*RetObj=&PageFaultCount;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("PagefileUsage")))
		{
			*RetObj=&PagefileUsage;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("PeakPagefileUsage")))
		{
			*RetObj=&PeakPagefileUsage;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("PeakWorkingSetSize")))
		{
			*RetObj=&PeakWorkingSetSize;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("QuotaNonPagedPoolUsage")))
		{
			*RetObj=&QuotaNonPagedPoolUsage;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("QuotaPagedPoolUsage")))
		{
			*RetObj=&QuotaPagedPoolUsage;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("QuotaPeakNonPagedPoolUsage")))
		{
			*RetObj=&QuotaPeakNonPagedPoolUsage;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("QuotaPeakPagedPoolUsage")))
		{
			*RetObj=&QuotaPeakPagedPoolUsage;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("WorkingSetSize")))
		{
			*RetObj=&WorkingSetSize;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("CreationTime")))
		{
			*RetObj=&CreationTime;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("ExitTime")))
		{
			*RetObj=&ExitTime;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("KernelTime")))
		{
			*RetObj=&KernelTime;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("UserTime")))
		{
			*RetObj=&UserTime;
		}
		if(*RetObj) return TRUE;
		return FALSE;
	}
 	BOOL Save(StorageObjectInterface * pStorageObject)
	{
		pStorageObject->PushNodeCtlBegin(_T("_tagProcessInfoAuditMsg"),this);

		Processid.Save(pStorageObject); 
		ProcessName.Save(pStorageObject); 
		HandleCount.Save(pStorageObject); 
		OtherOperationCount.Save(pStorageObject); 
		OtherTransferCount.Save(pStorageObject); 
		ReadOperationCount.Save(pStorageObject); 
		ReadTransferCount.Save(pStorageObject); 
		WriteOperationCount.Save(pStorageObject); 
		WriteTransferCount.Save(pStorageObject); 
		PageFaultCount.Save(pStorageObject); 
		PagefileUsage.Save(pStorageObject); 
		PeakPagefileUsage.Save(pStorageObject); 
		PeakWorkingSetSize.Save(pStorageObject); 
		QuotaNonPagedPoolUsage.Save(pStorageObject); 
		QuotaPagedPoolUsage.Save(pStorageObject); 
		QuotaPeakNonPagedPoolUsage.Save(pStorageObject); 
		QuotaPeakPagedPoolUsage.Save(pStorageObject); 
		WorkingSetSize.Save(pStorageObject); 
		CreationTime.Save(pStorageObject); 
		ExitTime.Save(pStorageObject); 
		KernelTime.Save(pStorageObject); 
		UserTime.Save(pStorageObject);

		pStorageObject->PushNodeCtlEnd(_T("_tagProcessInfoAuditMsg"),this);
		return TRUE;
	}
 	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
	{

		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&Processid); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&ProcessName); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&HandleCount); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&OtherOperationCount); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&OtherTransferCount); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&ReadOperationCount); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&ReadTransferCount); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&WriteOperationCount); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&WriteTransferCount); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&PageFaultCount); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&PagefileUsage); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&PeakPagefileUsage); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&PeakWorkingSetSize); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&QuotaNonPagedPoolUsage); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&QuotaPagedPoolUsage); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&QuotaPeakNonPagedPoolUsage); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&QuotaPeakPagedPoolUsage); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&WorkingSetSize); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&CreationTime); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&ExitTime); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&KernelTime); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&UserTime);
		return TRUE;
	}
 

};
