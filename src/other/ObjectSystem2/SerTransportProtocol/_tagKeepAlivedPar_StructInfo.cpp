 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagKeepAlivedPar_StructInfo.h"

Serialize__tagKeepAlivedPar::_Myt& Serialize__tagKeepAlivedPar::operator=(_tagKeepAlivedPar & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagKeepAlivedPar::GetData()
{
	m_Val.nCyc=nCyc; 
	m_Val.nWndPos=nWndPos; 
	m_Val.nWndLen=nWndLen;
}

BOOL Serialize__tagKeepAlivedPar::Construct(StorageObjectInterface * pOutObject)
{
	nCyc.init(this,_T("nCyc"),0,pOutObject); 
	nWndPos.init(this,_T("nWndPos"),0,pOutObject); 
	nWndLen.init(this,_T("nWndLen"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagKeepAlivedPar::SetData(_tagKeepAlivedPar & _X)
{
	nCyc=_X.nCyc; 
	nWndPos=_X.nWndPos; 
	nWndLen=_X.nWndLen;
}

BOOL Serialize__tagKeepAlivedPar::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("nCyc")))
	{
		*RetObj=&nCyc;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("nWndPos")))
	{
		*RetObj=&nWndPos;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("nWndLen")))
	{
		*RetObj=&nWndLen;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagKeepAlivedPar::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagKeepAlivedPar"),this);

	nCyc.Save(pStorageObject); 
	nWndPos.Save(pStorageObject); 
	nWndLen.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagKeepAlivedPar"),this);
	return TRUE;
}

BOOL Serialize__tagKeepAlivedPar::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nCyc); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nWndPos); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nWndLen);
	return TRUE;
}




