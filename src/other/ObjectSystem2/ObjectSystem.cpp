///////////////////////////////////////////////////////////////////////////////////
//	Copyright 2017 shushen,ye
//	Licensed under the Apache License, Version 2.0 (the "License");
//	you may not use this file except in compliance with the License.
//	You may obtain a copy of the License at
//	http://www.apache.org/licenses/LICENSE-2.0
//	Unless required by applicable law or agreed to in writing, software
//	distributed under the License is distributed on an "AS IS" BASIS,
//	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//	See the License for the specific language governing permissions and
//	limitations under the License.
///////////////////////////////////////////////////////////////////////////////////

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