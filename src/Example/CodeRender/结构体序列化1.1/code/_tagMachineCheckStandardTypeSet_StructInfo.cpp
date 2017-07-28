 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagMachineCheckStandardTypeSet_StructInfo.h"

Serialize__tagMachineCheckStandardTypeSet::_Myt& Serialize__tagMachineCheckStandardTypeSet::operator=(_tagMachineCheckStandardTypeSet & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagMachineCheckStandardTypeSet::GetData()
{
	m_Val.id=id; 
	m_Val.name=name; 
	m_Val.min_range=min_range; 
	m_Val.max_range=max_range; 
	m_Val.parent_id=parent_id;
}

BOOL Serialize__tagMachineCheckStandardTypeSet::Construct(StorageObjectInterface * pOutObject)
{
	id.init(this,_T("id"),0,pOutObject); 
	name.init(this,_T("name"),0,pOutObject); 
	min_range.init(this,_T("min_range"),0,pOutObject); 
	max_range.init(this,_T("max_range"),0,pOutObject); 
	parent_id.init(this,_T("parent_id"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagMachineCheckStandardTypeSet::SetData(_tagMachineCheckStandardTypeSet & _X)
{
	id=_X.id; 
	name=_X.name; 
	min_range=_X.min_range; 
	max_range=_X.max_range; 
	parent_id=_X.parent_id;
}

BOOL Serialize__tagMachineCheckStandardTypeSet::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("id")))
	{
		*RetObj=&id;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("name")))
	{
		*RetObj=&name;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("min_range")))
	{
		*RetObj=&min_range;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("max_range")))
	{
		*RetObj=&max_range;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("parent_id")))
	{
		*RetObj=&parent_id;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagMachineCheckStandardTypeSet::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagMachineCheckStandardTypeSet"),this);

	id.Save(pStorageObject); 
	name.Save(pStorageObject); 
	min_range.Save(pStorageObject); 
	max_range.Save(pStorageObject); 
	parent_id.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagMachineCheckStandardTypeSet"),this);
	return TRUE;
}

BOOL Serialize__tagMachineCheckStandardTypeSet::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&id); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&name); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&min_range); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&max_range); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&parent_id);
	return TRUE;
}




