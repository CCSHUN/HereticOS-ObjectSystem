 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagUnitReport_StructInfo.h"

Serialize__tagUnitReport::_Myt& Serialize__tagUnitReport::operator=(_tagUnitReport & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagUnitReport::GetData()
{
	m_Val.szID=szID; 
	m_Val.szInheritID=szInheritID; 
	m_Val.UnitReportArray=UnitReportArray;
}

BOOL Serialize__tagUnitReport::Construct(StorageObjectInterface * pOutObject)
{
	szID.init(this,_T("szID"),0,pOutObject); 
	szInheritID.init(this,_T("szInheritID"),0,pOutObject); 
	UnitReportArray.init(this,_T("UnitReportArray"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagUnitReport::SetData(_tagUnitReport & _X)
{
	szID=_X.szID; 
	szInheritID=_X.szInheritID; 
	UnitReportArray=_X.UnitReportArray;
}

BOOL Serialize__tagUnitReport::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szID")))
	{
		*RetObj=&szID;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szInheritID")))
	{
		*RetObj=&szInheritID;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("UnitReportArray")))
	{
		*RetObj=&UnitReportArray;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagUnitReport::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagUnitReport"),this);

	szID.Save(pStorageObject); 
	szInheritID.Save(pStorageObject); 
	UnitReportArray.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagUnitReport"),this);
	return TRUE;
}

BOOL Serialize__tagUnitReport::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szID); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szInheritID); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&UnitReportArray);
	return TRUE;
}




