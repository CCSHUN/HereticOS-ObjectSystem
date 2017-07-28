 #pragma once
#include "Serialize.h"

class Serialize__tagSystemInfoAuditRule : public Serialize_StructBase<_tagSystemInfoAuditRule,Serialize__tagSystemInfoAuditRule>
{
	public:
	typedef _tagSystemInfoAuditRule _MyObjectType;
 
	Serialize_BaseObject<tstring> RuleID; 
	Serialize_BaseObject<tstring> InfoAuditType; 
	Serialize_BaseObject<int> InfoUploadCycle; 
	Serialize_BaseObject<int> DifferentialValveCycle;

 	Serialize__tagSystemInfoAuditRule(){};
	~Serialize__tagSystemInfoAuditRule(){};
 	_Myt& operator=(_tagSystemInfoAuditRule & _X)
	{
		SetData(_X);
		return *this;
	}
 	void GetData()
	{
		m_Val.RuleID=RuleID; 
		m_Val.InfoAuditType=InfoAuditType; 
		m_Val.InfoUploadCycle=InfoUploadCycle; 
		m_Val.DifferentialValveCycle=DifferentialValveCycle;
	}
 	BOOL Construct(StorageObjectInterface * pOutObject)
	{
		RuleID.init(this,_T("RuleID"),0,pOutObject); 
		InfoAuditType.init(this,_T("InfoAuditType"),0,pOutObject); 
		InfoUploadCycle.init(this,_T("InfoUploadCycle"),0,pOutObject); 
		DifferentialValveCycle.init(this,_T("DifferentialValveCycle"),0,pOutObject);
		return TRUE;
	}
 	void SetData(_tagSystemInfoAuditRule & _X)
	{
		RuleID=_X.RuleID; 
		InfoAuditType=_X.InfoAuditType; 
		InfoUploadCycle=_X.InfoUploadCycle; 
		DifferentialValveCycle=_X.DifferentialValveCycle;
	}
 	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
	{
		*RetObj=0;
		if(tstring(CurFieldAddr.pFieldName)==tstring(_T("RuleID")))
		{
			*RetObj=&RuleID;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("InfoAuditType")))
		{
			*RetObj=&InfoAuditType;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("InfoUploadCycle")))
		{
			*RetObj=&InfoUploadCycle;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("DifferentialValveCycle")))
		{
			*RetObj=&DifferentialValveCycle;
		}
		if(*RetObj) return TRUE;
		return FALSE;
	}
 	BOOL Save(StorageObjectInterface * pStorageObject)
	{
		pStorageObject->PushNodeCtlBegin(_T("_tagSystemInfoAuditRule"),this);

		RuleID.Save(pStorageObject); 
		InfoAuditType.Save(pStorageObject); 
		InfoUploadCycle.Save(pStorageObject); 
		DifferentialValveCycle.Save(pStorageObject);

		pStorageObject->PushNodeCtlEnd(_T("_tagSystemInfoAuditRule"),this);
		return TRUE;
	}
 	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
	{

		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&RuleID); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&InfoAuditType); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&InfoUploadCycle); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&DifferentialValveCycle);
		return TRUE;
	}
 

};
