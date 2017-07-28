
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


#pragma once
//作者：叶树深 2010.6.10
//map容器序列化抽象

//template<typename FirstSerializeObject,typename SecondSerializeObject>
class Serialize_MapContainerSet : public SerializeObjectInterface
{
public:
	typedef Serialize_MapContainerSet _Myt;
	Serialize_BaseObject<tstring>	m_Key;
	SerializeObjectInterface	*	m_pVal;
	map<tstring,SerializeObjectInterface *,less<tstring> >  m_InterfaceArray;

	Serialize_MapContainerSet()
	{

	};

	~Serialize_MapContainerSet()
	{

	};

	BOOL init(SerializeRunData * pParent,TCHAR * pFieldName,unsigned int nIndex,StorageObjectInterface * pOutObject)
	{
		runstate.bCache=0;
		m_pParent=pParent;
		m_pFieldName=pFieldName;
		m_nIndex=nIndex;

		m_Key.init(this,_T("key"),0,pOutObject);
		//m_pVal->init(this,_T("value"),0,pOutObject);

		return TRUE;
	}



	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
	{
		*RetObj=0;
		//tstring szKey=tstring(m_pFieldName)+tstring("_Key");
		//tstring szVal=tstring(m_pFieldName)+tstring("_Val");
		if(tstring(CurFieldAddr.pFieldName)==tstring(_T("key")))
		{
			*RetObj=&m_Key;
		}else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("value")))
		{
			map<tstring,SerializeObjectInterface *,less<tstring> >::iterator itMap=m_InterfaceArray.find((tstring)m_Key);
			if(itMap!=m_InterfaceArray.end())
			{
				m_pVal=itMap->second;
				//m_pVal->m_pFieldName=_T("value");
				*RetObj=m_pVal;
				return TRUE;
			}
			
		}
		if(*RetObj) return TRUE;

		return FALSE;
	};

	BOOL LoadSetData(tstring & Data)
	{
		return FALSE;
	};

	BOOL Load(StorageObjectInterface * pStorageObject)
	{
		return pStorageObject->LoadObject(this);
	}

	BOOL Save(StorageObjectInterface * pInnerStorageObject,StorageObjectInterface * pStorageObject)
	{
		m_pFieldName=_T("key_value");
		pInnerStorageObject->PushNodeCtlBegin(_T("Serialize_MapContainerSet"),this);

		m_Key.Save(pStorageObject);
		//保存头
		//m_pFieldName=_T("value");
		//pInnerStorageObject->PushNodeCtlBegin(_T("object"),this);

		TCHAR * pOldFieldName=m_pVal->m_pFieldName;
		m_pVal->m_pFieldName=_T("value");
		m_pVal->Save(pStorageObject);
		m_pVal->m_pFieldName=pOldFieldName;
		//pInnerStorageObject->PushNodeCtlEnd(_T("object"),this);

		m_pFieldName=_T("key_value");
		pInnerStorageObject->PushNodeCtlEnd(_T("Serialize_MapContainerSet"),this);
		return TRUE;
	};
};

template<typename SerializeObjectType,typename MapFunctionType>
class ObjectMapContainer
{
public:
	typedef ObjectMapContainer<SerializeObjectType, MapFunctionType> _Myt;
	typedef typename SerializeObjectType::_MyObjectType ObjectType;
	ObjectType m_Object;
	
	_Myt& operator=(ObjectType & _X)
	{
		m_Object=_X;
		return *this;
	}

	operator ObjectType &()
	{
		return m_Object;
	}

	ObjectMapContainer(){};
	~ObjectMapContainer(){};
protected:
	
private:
};

template<typename SerializeObjectType,typename MapFunctionType>
class Serialize_ObjectMapContainer : 
	public SerializeObjectInterface,
	public StorageObjectInterface
	//public SerializeObjectType
{
public:
	typedef Serialize_ObjectMapContainer<SerializeObjectType,MapFunctionType> _Myt;
	typedef typename SerializeObjectType::_MyObjectType _MyObjectType;
	SerializeObjectType m_Val;
	StorageObjectInterface * m_pOutObject;
	//map<tstring,MapFunctionType,less<tstring> > m_ObjectInterfaceArray;
	vector<SerializeObjectInterface *> m_ObjectInterfaceArray;
	MapFunctionType m_TmpObjectInterface;

	Serialize_ObjectMapContainer()
	{

	};

	Serialize_ObjectMapContainer(StorageObjectInterface * pOutObject)
	{
		m_pOutObject=pOutObject;
	};

	~Serialize_ObjectMapContainer()
	{

	};

	BOOL init(SerializeRunData * pParent,TCHAR * pFieldName,unsigned int nIndex,StorageObjectInterface * pOutObject,unsigned int nNum=0)
	{
		runstate.bCache=0;
		m_pParent=pParent;
		m_pFieldName=pFieldName;
		m_nIndex=nIndex;

		m_pOutObject=pOutObject;
		/*
		Meminfo.init(this,"Meminfo",0);
				IOInfo.init(this,"IOInfo",0);*/
		m_Val.init(pParent,_T(""),0,pOutObject);

		m_Val.GetObjectMap(m_ObjectInterfaceArray);
		for(unsigned int i=0;i<m_ObjectInterfaceArray.size();i++)
		{
			m_TmpObjectInterface.m_InterfaceArray[m_ObjectInterfaceArray[i]->m_pFieldName]=m_ObjectInterfaceArray[i];
		}
		

		return TRUE;
		
	}

	

	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
	{
		* RetObj=&m_TmpObjectInterface;
		return TRUE;
	};

	BOOL LoadCurObjectEnd(SerializeLoadSaveInterface * ChildObj)
	{
		return TRUE;
	};


	//当前节点Load开始
	BOOL LoadObjectBegin(SerializeLoadSaveInterface * Obj)
	{
		return FALSE;
	};

	//当前节点Load结束
	BOOL LoadObjectEnd(SerializeLoadSaveInterface * Obj)
	{
		return FALSE;
	};

	BOOL Load(StorageObjectInterface * pStorageObject)
	{																					
		return pStorageObject->LoadObject(this);
	}

	operator _MyObjectType &()
	{
		return m_Val;
	}
	SerializeObjectType& operator=( _MyObjectType & _X) 
	{
		runstate.bCache=1;
		m_Val=_X;

		return m_Val;
	}
	
	BOOL LoadSetData(tstring & Data)
	{
		
		//CMyString szData((TCHAR *)Data.c_str(),Data.length()*sizeof(TCHAR));
		//m_Val=AtoVal((TCHAR *)Data.c_str(),10,ObjectType());
			//atoi((char *)szData);
		//runstate.bCache=1;
		return TRUE;
	};

	

	BOOL Save(StorageObjectInterface * pStorageObject)
	{
		MapFunctionType MapFunction;
		m_pOutObject=pStorageObject;
		pStorageObject->PushNodeCtlBegin(_T("MapContainer"),this);

		MapFunction.init(this,"key_value",0,pStorageObject);
		for(unsigned int i=0;i<m_ObjectInterfaceArray.size();i++)
		{
			MapFunction.m_Key=tstring(m_ObjectInterfaceArray[i]->m_pFieldName);
			MapFunction.m_pVal=m_ObjectInterfaceArray[i];
			MapFunction.Save((StorageObjectInterface *)this,pStorageObject);
		}
		pStorageObject->PushNodeCtlEnd(_T("MapContainer"),this);

		return TRUE;
	}



	//存储对象接口
	BOOL init(tstring & szFilePath,CharacterType nType=Ansi)
	{
		return m_pOutObject->init(szFilePath,nType);
	}

	BOOL LoadObject(SerializeLoadSaveInterface * pObj)
	{
		return m_pOutObject->LoadObject(pObj);
	}
	

	BOOL GetObjectInt(IN SerializeRunData * Addr,IN OUT void * pOutData,IN OUT unsigned int & nLen)
	{
		return m_pOutObject->GetObjectInt(Addr, pOutData,nLen);
	}

	BOOL SetObjectInt(IN SerializeRunData * Addr,IN void * pInData,IN OUT unsigned int & nLen)
	{
		return m_pOutObject->SetObjectInt(Addr,pInData, nLen);
	}

	BOOL GetBinaryObject(IN SerializeRunData * Addr,IN OUT void * pOutData,IN OUT unsigned int & nLen)
	{
		return m_pOutObject->GetBinaryObject(Addr,pOutData,nLen);
	}

	BOOL SetBinaryObject(IN SerializeRunData * Addr,IN void * pInData,IN OUT unsigned int & nLen)
	{
		return m_pOutObject->SetBinaryObject( Addr, pInData,nLen);
	}

	BOOL GetStringObject(IN SerializeRunData * Addr,IN OUT void * pOutData,IN OUT unsigned int & nLen)
	{
		return m_pOutObject->GetStringObject( Addr, pOutData, nLen);
	}

	BOOL SetStringObject(IN SerializeRunData * Addr,IN void * pInData,IN OUT unsigned int & nLen)
	{
		return m_pOutObject->SetStringObject( Addr, pInData, nLen);
	}

	BOOL PushDataVal(IN void * pInData,IN OUT unsigned int & nLen)
	{
		return m_pOutObject->PushDataVal( pInData,nLen);

	}

	BOOL PushDataBinary(IN void * pInData,IN OUT unsigned int & nLen)
	{
		return m_pOutObject->PushDataBinary(pInData,nLen);//return WriteFile(m_hFile,(BYTE *)szRst.c_str(),szRst.length()*sizeof(TCHAR),&nRetLen,NULL);
	}

	BOOL PushDataString(IN LPTSTR pInData,IN OUT unsigned int & nLen)
	{
		return m_pOutObject->PushDataString(pInData,nLen);
	}

	//顺序保存节点开始
	/*
	void GetFormatTab(tstring & szTab)
		{
			for(unsigned int i=0;i<m_nCurDepth;i++)
			{
				szTab+=_T("\t");
			}
		}*/
	
	BOOL PushNodeCtlBegin(TCHAR * szFieldType,SerializeRunData * CurFieldAddr)
	{
		return m_pOutObject->PushNodeCtlBegin(szFieldType, CurFieldAddr);
	}
	//顺序保存节点结束
	BOOL PushNodeCtlEnd(TCHAR * szFieldType,SerializeRunData * CurFieldAddr)
	{
		return m_pOutObject->PushNodeCtlEnd(szFieldType, CurFieldAddr);
	}

};
