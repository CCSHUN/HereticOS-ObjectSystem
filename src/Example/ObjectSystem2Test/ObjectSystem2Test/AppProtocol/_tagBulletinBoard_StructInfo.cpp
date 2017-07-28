 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagBulletinBoard_StructInfo.h"

Serialize__tagBulletinBoard::_Myt& Serialize__tagBulletinBoard::operator=(_tagBulletinBoard & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagBulletinBoard::GetData()
{
	m_Val.nMaxFlowerSlotCount=nMaxFlowerSlotCount; 
	m_Val.nGameMode=nGameMode; 
	m_Val.nTransportWaitTime=nTransportWaitTime;
}

BOOL Serialize__tagBulletinBoard::Construct(StorageObjectInterface * pOutObject)
{
	nMaxFlowerSlotCount.init(this,_T("nMaxFlowerSlotCount"),0,pOutObject); 
	nGameMode.init(this,_T("nGameMode"),0,pOutObject); 
	nTransportWaitTime.init(this,_T("nTransportWaitTime"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagBulletinBoard::SetData(_tagBulletinBoard & _X)
{
	nMaxFlowerSlotCount=_X.nMaxFlowerSlotCount; 
	nGameMode=_X.nGameMode; 
	nTransportWaitTime=_X.nTransportWaitTime;
}

BOOL Serialize__tagBulletinBoard::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("nMaxFlowerSlotCount")))
	{
		*RetObj=&nMaxFlowerSlotCount;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("nGameMode")))
	{
		*RetObj=&nGameMode;
	} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("nTransportWaitTime")))
	{
		*RetObj=&nTransportWaitTime;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagBulletinBoard::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagBulletinBoard"),this);

	nMaxFlowerSlotCount.Save(pStorageObject); 
	nGameMode.Save(pStorageObject); 
	nTransportWaitTime.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagBulletinBoard"),this);
	return TRUE;
}

BOOL Serialize__tagBulletinBoard::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nMaxFlowerSlotCount); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nGameMode); 
	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&nTransportWaitTime);
	return TRUE;
}




