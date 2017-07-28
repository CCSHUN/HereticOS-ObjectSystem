 #include "stdafx.h"
#include "CommonTypeDef.h"
#include "_tagTestHexString_StructInfo.h"

Serialize__tagTestHexString::_Myt& Serialize__tagTestHexString::operator=(_tagTestHexString & _X)
{
	SetData(_X);
	return *this;
}

void Serialize__tagTestHexString::GetData()
{
	m_Val.Test=Test;
}

BOOL Serialize__tagTestHexString::Construct(StorageObjectInterface * pOutObject)
{
	Test.init(this,_T("Test"),0,pOutObject);
	return TRUE;
}

 void Serialize__tagTestHexString::SetData(_tagTestHexString & _X)
{
	Test=_X.Test;
}

BOOL Serialize__tagTestHexString::LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
{
	*RetObj=0;
	if(tstring(CurFieldAddr.pFieldName)==tstring(_T("Test")))
	{
		*RetObj=&Test;
	}
	if(*RetObj) return TRUE;
	return FALSE;
}

BOOL Serialize__tagTestHexString::Save(StorageObjectInterface * pStorageObject)
{
	pStorageObject->PushNodeCtlBegin(_T("_tagTestHexString"),this);

	Test.Save(pStorageObject);

	pStorageObject->PushNodeCtlEnd(_T("_tagTestHexString"),this);
	return TRUE;
}

BOOL Serialize__tagTestHexString::GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
{

	ObjectInterfaceMap.push_back((SerializeObjectInterface *)&Test);
	return TRUE;
}




