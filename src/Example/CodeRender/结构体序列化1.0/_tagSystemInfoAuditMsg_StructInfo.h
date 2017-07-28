 #pragma once
#include "Serialize.h"

class Serialize__tagSystemInfoAuditMsg : public Serialize_StructBase<_tagSystemInfoAuditMsg,Serialize__tagSystemInfoAuditMsg>
{
	public:
	typedef _tagSystemInfoAuditMsg _MyObjectType;
 
	Serialize_BaseObject<__int64> CommitLimit; 
	Serialize_BaseObject<__int64> CommitPeak; 
	Serialize_BaseObject<__int64> CommitTotal; 
	Serialize_BaseObject<__int64> HandleCount; 
	Serialize_BaseObject<__int64> KernelNonpaged; 
	Serialize_BaseObject<__int64> KernelPaged; 
	Serialize_BaseObject<__int64> KernelTotal; 
	Serialize_BaseObject<__int64> PageSize; 
	Serialize_BaseObject<__int64> PhysicalAvailable; 
	Serialize_BaseObject<__int64> PhysicalTotal; 
	Serialize_BaseObject<__int64> ProcessCount; 
	Serialize_BaseObject<__int64> SystemCache; 
	Serialize_BaseObject<__int64> ThreadCount;

 	Serialize__tagSystemInfoAuditMsg(){};
	~Serialize__tagSystemInfoAuditMsg(){};
 	_Myt& operator=(_tagSystemInfoAuditMsg & _X)
	{
		SetData(_X);
		return *this;
	}
 	void GetData()
	{
		m_Val.CommitLimit=CommitLimit; 
		m_Val.CommitPeak=CommitPeak; 
		m_Val.CommitTotal=CommitTotal; 
		m_Val.HandleCount=HandleCount; 
		m_Val.KernelNonpaged=KernelNonpaged; 
		m_Val.KernelPaged=KernelPaged; 
		m_Val.KernelTotal=KernelTotal; 
		m_Val.PageSize=PageSize; 
		m_Val.PhysicalAvailable=PhysicalAvailable; 
		m_Val.PhysicalTotal=PhysicalTotal; 
		m_Val.ProcessCount=ProcessCount; 
		m_Val.SystemCache=SystemCache; 
		m_Val.ThreadCount=ThreadCount;
	}
 	BOOL Construct(StorageObjectInterface * pOutObject)
	{
		CommitLimit.init(this,_T("CommitLimit"),0,pOutObject); 
		CommitPeak.init(this,_T("CommitPeak"),0,pOutObject); 
		CommitTotal.init(this,_T("CommitTotal"),0,pOutObject); 
		HandleCount.init(this,_T("HandleCount"),0,pOutObject); 
		KernelNonpaged.init(this,_T("KernelNonpaged"),0,pOutObject); 
		KernelPaged.init(this,_T("KernelPaged"),0,pOutObject); 
		KernelTotal.init(this,_T("KernelTotal"),0,pOutObject); 
		PageSize.init(this,_T("PageSize"),0,pOutObject); 
		PhysicalAvailable.init(this,_T("PhysicalAvailable"),0,pOutObject); 
		PhysicalTotal.init(this,_T("PhysicalTotal"),0,pOutObject); 
		ProcessCount.init(this,_T("ProcessCount"),0,pOutObject); 
		SystemCache.init(this,_T("SystemCache"),0,pOutObject); 
		ThreadCount.init(this,_T("ThreadCount"),0,pOutObject);
		return TRUE;
	}
 	void SetData(_tagSystemInfoAuditMsg & _X)
	{
		CommitLimit=_X.CommitLimit; 
		CommitPeak=_X.CommitPeak; 
		CommitTotal=_X.CommitTotal; 
		HandleCount=_X.HandleCount; 
		KernelNonpaged=_X.KernelNonpaged; 
		KernelPaged=_X.KernelPaged; 
		KernelTotal=_X.KernelTotal; 
		PageSize=_X.PageSize; 
		PhysicalAvailable=_X.PhysicalAvailable; 
		PhysicalTotal=_X.PhysicalTotal; 
		ProcessCount=_X.ProcessCount; 
		SystemCache=_X.SystemCache; 
		ThreadCount=_X.ThreadCount;
	}
 	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
	{
		*RetObj=0;
		if(tstring(CurFieldAddr.pFieldName)==tstring(_T("CommitLimit")))
		{
			*RetObj=&CommitLimit;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("CommitPeak")))
		{
			*RetObj=&CommitPeak;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("CommitTotal")))
		{
			*RetObj=&CommitTotal;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("HandleCount")))
		{
			*RetObj=&HandleCount;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("KernelNonpaged")))
		{
			*RetObj=&KernelNonpaged;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("KernelPaged")))
		{
			*RetObj=&KernelPaged;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("KernelTotal")))
		{
			*RetObj=&KernelTotal;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("PageSize")))
		{
			*RetObj=&PageSize;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("PhysicalAvailable")))
		{
			*RetObj=&PhysicalAvailable;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("PhysicalTotal")))
		{
			*RetObj=&PhysicalTotal;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("ProcessCount")))
		{
			*RetObj=&ProcessCount;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("SystemCache")))
		{
			*RetObj=&SystemCache;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("ThreadCount")))
		{
			*RetObj=&ThreadCount;
		}
		if(*RetObj) return TRUE;
		return FALSE;
	}
 	BOOL Save(StorageObjectInterface * pStorageObject)
	{
		pStorageObject->PushNodeCtlBegin(_T("_tagSystemInfoAuditMsg"),this);

		CommitLimit.Save(pStorageObject); 
		CommitPeak.Save(pStorageObject); 
		CommitTotal.Save(pStorageObject); 
		HandleCount.Save(pStorageObject); 
		KernelNonpaged.Save(pStorageObject); 
		KernelPaged.Save(pStorageObject); 
		KernelTotal.Save(pStorageObject); 
		PageSize.Save(pStorageObject); 
		PhysicalAvailable.Save(pStorageObject); 
		PhysicalTotal.Save(pStorageObject); 
		ProcessCount.Save(pStorageObject); 
		SystemCache.Save(pStorageObject); 
		ThreadCount.Save(pStorageObject);

		pStorageObject->PushNodeCtlEnd(_T("_tagSystemInfoAuditMsg"),this);
		return TRUE;
	}
 	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
	{

		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&CommitLimit); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&CommitPeak); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&CommitTotal); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&HandleCount); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&KernelNonpaged); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&KernelPaged); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&KernelTotal); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&PageSize); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&PhysicalAvailable); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&PhysicalTotal); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&ProcessCount); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&SystemCache); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&ThreadCount);
		return TRUE;
	}
 

};
