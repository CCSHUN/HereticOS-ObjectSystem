 #pragma once
#include "Serialize.h"

class Serialize__tagSafeLevelInfo : public Serialize_StructBase<_tagSafeLevelInfo,Serialize__tagSafeLevelInfo>
{
	public:
	typedef _tagSafeLevelInfo _MyObjectType;
 
	Serialize__tagSafeLevelInfoAttributes MyObjectAttributes; 
	Serialize_BaseObject<tstring> priSafeLevelId; 
	Serialize_BaseObject<tstring> safelevelCnName; 
	Serialize_BaseObject<int> statusCode; 
	Serialize_BaseObject<int> levelNumber; 
	Serialize_BaseObject<tstring> safelevelCode; 
	Serialize_BaseObject<tstring> deptId; 
	Serialize_BaseObject<tstring> orderC0de;

 	Serialize__tagSafeLevelInfo(){};
	~Serialize__tagSafeLevelInfo(){};
 	_Myt& operator=(_tagSafeLevelInfo & _X)
	{
		SetData(_X);
		return *this;
	}
 	void GetData()
	{
		m_Val.MyObjectAttributes=MyObjectAttributes; 
		m_Val.priSafeLevelId=priSafeLevelId; 
		m_Val.safelevelCnName=safelevelCnName; 
		m_Val.statusCode=statusCode; 
		m_Val.levelNumber=levelNumber; 
		m_Val.safelevelCode=safelevelCode; 
		m_Val.deptId=deptId; 
		m_Val.orderC0de=orderC0de;
	}
 	BOOL Construct(StorageObjectInterface * pOutObject)
	{
		MyObjectAttributes.init(this,_T("MyObjectAttributes"),0,pOutObject); 
		priSafeLevelId.init(this,_T("priSafeLevelId"),0,pOutObject); 
		safelevelCnName.init(this,_T("safelevelCnName"),0,pOutObject); 
		statusCode.init(this,_T("statusCode"),0,pOutObject); 
		levelNumber.init(this,_T("levelNumber"),0,pOutObject); 
		safelevelCode.init(this,_T("safelevelCode"),0,pOutObject); 
		deptId.init(this,_T("deptId"),0,pOutObject); 
		orderC0de.init(this,_T("orderC0de"),0,pOutObject);
		return TRUE;
	}
 	void SetData(_tagSafeLevelInfo & _X)
	{
		MyObjectAttributes=_X.MyObjectAttributes; 
		priSafeLevelId=_X.priSafeLevelId; 
		safelevelCnName=_X.safelevelCnName; 
		statusCode=_X.statusCode; 
		levelNumber=_X.levelNumber; 
		safelevelCode=_X.safelevelCode; 
		deptId=_X.deptId; 
		orderC0de=_X.orderC0de;
	}
 	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
	{
		*RetObj=0;
		if(tstring(CurFieldAddr.pFieldName)==tstring(_T("MyObjectAttributes")))
		{
			*RetObj=&MyObjectAttributes;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("priSafeLevelId")))
		{
			*RetObj=&priSafeLevelId;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("safelevelCnName")))
		{
			*RetObj=&safelevelCnName;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("statusCode")))
		{
			*RetObj=&statusCode;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("levelNumber")))
		{
			*RetObj=&levelNumber;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("safelevelCode")))
		{
			*RetObj=&safelevelCode;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("deptId")))
		{
			*RetObj=&deptId;
		} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("orderC0de")))
		{
			*RetObj=&orderC0de;
		}
		if(*RetObj) return TRUE;
		return FALSE;
	}
 	BOOL Save(StorageObjectInterface * pStorageObject)
	{
		pStorageObject->PushNodeCtlBegin(_T("_tagSafeLevelInfo"),this);

		MyObjectAttributes.Save(pStorageObject); 
		priSafeLevelId.Save(pStorageObject); 
		safelevelCnName.Save(pStorageObject); 
		statusCode.Save(pStorageObject); 
		levelNumber.Save(pStorageObject); 
		safelevelCode.Save(pStorageObject); 
		deptId.Save(pStorageObject); 
		orderC0de.Save(pStorageObject);

		pStorageObject->PushNodeCtlEnd(_T("_tagSafeLevelInfo"),this);
		return TRUE;
	}
 	BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
	{

		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&MyObjectAttributes); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&priSafeLevelId); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&safelevelCnName); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&statusCode); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&levelNumber); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&safelevelCode); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&deptId); 
		ObjectInterfaceMap.push_back((SerializeObjectInterface *)&orderC0de);
		return TRUE;
	}
 

};
