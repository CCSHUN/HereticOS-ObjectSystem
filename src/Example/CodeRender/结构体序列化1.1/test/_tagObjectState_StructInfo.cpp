 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagObjectState_StructInfo.h"

Serialize__tagObjectState::_Myt& Serialize__tagObjectState::operator=(_tagObjectState & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagObjectState::GetData()
{
	m_Val.bLock=bLock; 
	m_Val.nType=nType; 
	m_Val.szLockUser=szLockUser; 
	m_Val.nLockTime=nLockTime;
}

BOOL Serialize__tagObjectState::Construct(StorageObjectInterface * pOutObject)
{
	bLock.init(this,_T("bLock"),0,pOutObject); 
	nType.init(this,_T("nType"),0,pOutObject); 
	szLockUser.init(this,_T("szLockUser"),0,pOutObject); 
	nLockTime.init(this,_T("nLockTime"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagObjectState::SetData(_tagObjectState & _X)
{
	bLock=_X.bLock; 
	nType=_X.nType; 
	szLockUser=_X.szLockUser; 
	nLockTime=_X.nLockTime;
}

BOOL Serialize__tagObjectState::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("bLock")))
	{
		*RetObj=&bLock;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("nType")))
	{
		*RetObj=&nType;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("szLockUser")))
	{
		*RetObj=&szLockUser;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("nLockTime")))
	{
		*RetObj=&nLockTime;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagObjectState::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagObjectState"),this);

	bLock.Save(pStorageObject); 
	nType.Save(pStorageObject); 
	szLockUser.Save(pStorageObject); 
	nLockTime.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagObjectState"),this);
	return TRUE;
}

BOOL Serialize__tagObjectState::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&bLock); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nType); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&szLockUser); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nLockTime);
	return TRUE;
}




