 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_S_REPORT_StructInfo.h"

Serialize__S_REPORT::_Myt& Serialize__S_REPORT::operator=(_S_REPORT & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__S_REPORT::GetData()
{
	m_Val.szName=szName; 
	m_Val.nTotalErrorCount=nTotalErrorCount; 
	m_Val.nErrorCount_1=nErrorCount_1; 
	m_Val.nErrorCount_2=nErrorCount_2; 
	m_Val.nErrorCount_3=nErrorCount_3; 
	m_Val.items=items;
}

BOOL Serialize__S_REPORT::Construct(StorageObjectInterface * pOutObject)
{
	szName.init(this,_T("szName"),0,pOutObject); 
	nTotalErrorCount.init(this,_T("nTotalErrorCount"),0,pOutObject); 
	nErrorCount_1.init(this,_T("nErrorCount_1"),0,pOutObject); 
	nErrorCount_2.init(this,_T("nErrorCount_2"),0,pOutObject); 
	nErrorCount_3.init(this,_T("nErrorCount_3"),0,pOutObject); 
	items.init(this,_T("items"),0,pOutObject);
	return TRUE;
}

 void Serialize__S_REPORT::SetData(_S_REPORT & _X)
{
	szName=_X.szName; 
	nTotalErrorCount=_X.nTotalErrorCount; 
	nErrorCount_1=_X.nErrorCount_1; 
	nErrorCount_2=_X.nErrorCount_2; 
	nErrorCount_3=_X.nErrorCount_3; 
	items=_X.items;
}

BOOL Serialize__S_REPORT::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szName")))
	{
		*RetObj=&szName;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("nTotalErrorCount")))
	{
		*RetObj=&nTotalErrorCount;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("nErrorCount_1")))
	{
		*RetObj=&nErrorCount_1;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("nErrorCount_2")))
	{
		*RetObj=&nErrorCount_2;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("nErrorCount_3")))
	{
		*RetObj=&nErrorCount_3;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("items")))
	{
		*RetObj=&items;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__S_REPORT::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_S_REPORT"),this);

	szName.Save(pStorageObject); 
	nTotalErrorCount.Save(pStorageObject); 
	nErrorCount_1.Save(pStorageObject); 
	nErrorCount_2.Save(pStorageObject); 
	nErrorCount_3.Save(pStorageObject); 
	items.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_S_REPORT"),this);
	return TRUE;
}

BOOL Serialize__S_REPORT::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szName); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nTotalErrorCount); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nErrorCount_1); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nErrorCount_2); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nErrorCount_3); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&items);
	return TRUE;
}




