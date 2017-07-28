#include "StdAfx.h"
#include "ObjectSystem.h"

/*
template<class ValType,class SerType>
ObjectTypeWrap<ValType,SerType>::ObjectTypeWrap()
{
	m_ObjectState.bLock=FALSE;
	m_ObjectState.nLockTime=0;
	m_ObjectState.nType=CObjectSystemInterface::Nonmoral;
	m_ObjectState.szLockUser=_T("");
}

template<class ValType,class SerType>
virtual ObjectTypeWrap<ValType,SerType>::~ObjectTypeWrap(){};

template<class ValType,class SerType>
BOOL ObjectTypeWrap<ValType,SerType>::GetObject()
{
	tstring Object;
	BOOL bRet=gpObjectSystem->GetObject(m_szAddr,Object,m_ObjectState,&m_nCurError);
	if(bRet)
	{
		SerTCHARXmlBufferToObjectEx(ValType,SerType,m_Data,(Object.c_str()));
	}
	return bRet;

}
template<class ValType,class SerType>
BOOL ObjectTypeWrap<ValType,SerType>::UpDataObject()
{
	tstring Object;
	SerObjectToXmlBufferEx(ValType,SerType,m_Data,Object);
	return gpObjectSystem->UpDataObject(m_szAddr,Object,&m_nCurError);
}

template<class ValType,class SerType>
BOOL ObjectTypeWrap<ValType,SerType>::GetDirectoryInfo(CObjectSystemInterface::_tagDirectoryInfo & DirectoryInfo)
{
	return gpObjectSystem->GetDirectoryInfo(m_szAddr,m_szFinder,DirectoryInfo,&m_nCurError);
}

template<class ValType,class SerType>
BOOL ObjectTypeWrap<ValType,SerType>::DeleteObject()
{
	return gpObjectSystem->DeleteObject(m_szAddr,&m_nCurError);
}*/