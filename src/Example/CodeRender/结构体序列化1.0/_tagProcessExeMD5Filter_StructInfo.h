 #pragma once
#include "Serialize.h"

class Serialize__tagProcessExeMD5Filter : public Serialize_StructBase<_tagProcessExeMD5Filter,Serialize__tagProcessExeMD5Filter>
{
	public:
	typedef _tagProcessExeMD5Filter _MyObjectType;
 
	Serialize_BaseObject<tstring> RuleID; 
	Serialize_BaseObject<tstring> FilterRule; 
	Serialize_BaseObject<tstring> ProcessBinMD5;

 	Serialize__tagProcessExeMD5Filter(){};
	~Serialize__tagProcessExeMD5Filter(){};
 	_Myt& operator=(_tagProcessExeMD5Filter & _X)
	{
		SetData(_X);
		return *this;
	}
 	void GetData()
	{
		m_Val.RuleID=RuleID; 
		m_Val.FilterRule=FilterRule; 
		m_Val.ProcessBinMD5=ProcessBinMD5;
	}
 	BOOL Construct(StorageObjectInterface * pOutObject)
	{
		RuleID.init(this,_T("RuleID"),0,pOutObject); 
		FilterRule.init(this,_T("FilterRule"),0,pOutObject); 
		ProcessBinMD5.init(this,_T("ProcessBinMD5"),0,pOutObject);
		return TRUE;
	}
 	void SetData(_tagProcessExeMD5Filter & _X)
	{
		RuleID=_X.RuleID; 
		FilterRule=_X.FilterRule; 
		ProcessBinMD5=_X.ProcessBinMD5;
	}
 	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
	{
		*RetObj=0;
		if(tstring(CurFieldAddr.pFieldName)==tstring(_T("RuleID")))
		{
			*RetObj=&RuleID;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("FilterRule")))
		{
			*RetObj=&FilterRule;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("ProcessBinMD5")))
		{
			*RetObj=&ProcessBinMD5;
		}
		if(*RetObj) return TRUE;
		return FALSE;
	}
 	BOOL Save(StorageObjectInterface * pStorageObject)
	{
		pStorageObject->PushNodeCtlBegin(_T("_tagProcessExeMD5Filter"),this);

		RuleID.Save(pStorageObject); 
		FilterRule.Save(pStorageObject); 
		ProcessBinMD5.Save(pStorageObject);

		pStorageObject->PushNodeCtlEnd(_T("_tagProcessExeMD5Filter"),this);
		return TRUE;
	}
 	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
	{

		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&RuleID); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&FilterRule); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&ProcessBinMD5);
		return TRUE;
	}
 

};
