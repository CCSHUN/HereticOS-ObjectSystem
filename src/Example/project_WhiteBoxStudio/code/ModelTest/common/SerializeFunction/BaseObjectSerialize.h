#pragma once



//stl容器序列化
template<typename SerializeObjectType>
class Serialize_vector : public vector<SerializeObjectType>,
	public SerializeObjectInterface
{
public:
	typedef Serialize_vector<SerializeObjectType> _Myt;
	typedef vector<SerializeObjectType> _Myt1;
	typedef vector<typename SerializeObjectType::_MyObjectType>	_MyObjectType;

	StorageObjectInterface * m_pOutObject;
	vector<typename SerializeObjectType::_MyObjectType> m_Val;
	Serialize_vector()
	{

	};

	~Serialize_vector()
	{

	};

	SerializeObjectType & operator[](size_type _Pos)
	{
		if(_Pos>=this->size())
		{
			return *(SerializeObjectType *)NULL;
		}
		return ((_Myt1*)this)->at(_Pos);
	}

	operator _MyObjectType &()
	{
		if(runstate.bCache)
		{
			
		}else
		{
			
			m_Val.clear();
			for(_Myt::iterator itPos=this->begin();itPos!=this->end();itPos++)
			{
				m_Val.insert(m_Val.end(),(SerializeObjectType::_MyObjectType)*itPos);
			}
			

			runstate.bCache=1;
		}
		return m_Val;
	}
	
	

	_Myt& operator=(_MyObjectType & _X) 
	{
		runstate.bCache=0;
		this->clear();
		this->resize(_X.size());
		SerializeObjectType SerializeObject;
		SerializeObject.init(this,this->m_pFieldName,0,m_pOutObject);
		for(unsigned int i=0;i<this->size();i++)
		{
			//cb.init(this,"cb",0,pOutObject);
			SerializeObject.m_nIndex=i;
			this->at(i)=SerializeObject;
			this->at(i)=_X[i];
		}

		return *this;
	}
	
	
	BOOL init(SerializeRunData * pParent,TCHAR * pFieldName,unsigned int nIndex,StorageObjectInterface * pOutObject)
	{
		runstate.bCache=0;
		m_pParent=pParent;
		m_pFieldName=pFieldName;
		m_nIndex=nIndex;
		clear();

		m_pOutObject=pOutObject;
		/*
		Meminfo.init(this,"Meminfo",0);
				IOInfo.init(this,"IOInfo",0);*/
		return TRUE;
		
	}

	

	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
	{
		if(this->size()<=CurFieldAddr.nIndex)
		{
			SerializeObjectType SerializeObject;
			//SerializeObject.init(this,m_pFieldName,0,m_pOutObject);
			unsigned int nNeedSize=CurFieldAddr.nIndex-this->size()+1;
			for(unsigned int i=0;i<nNeedSize;i++)
			{
				SerializeObject.m_nIndex=i;
				this->push_back(SerializeObject);
				this->back().init(this,m_pFieldName,i,m_pOutObject);
			}
		}
		* RetObj=&(*this)[CurFieldAddr.nIndex];
		return TRUE;
	};
	BOOL LoadSetData(tstring & Data)
	{
		//unsigned int nLen=Data.size()
		if(Data.at(0)==_T('\n'))
		{
			//空数组返回成功,继续下个字段
			return TRUE;
		}
		return FALSE;
	};

	BOOL LoadObjectEnd(SerializeLoadSaveInterface * Obj)
	{
		/*for(unsigned int i=0;i<this->size();i++)
		{
			this->at(i).init(this,m_pFieldName,i,m_pOutObject);
		}*/
		return FALSE;
	};

	BOOL Load(StorageObjectInterface * pStorageObject)
	{
		return pStorageObject->LoadObject(this);
	}

	BOOL Save(StorageObjectInterface * pStorageObject)
	{
		unsigned int nRetLen=4;
		pStorageObject->PushNodeCtlBegin(_T("vector"),this);
		//pStorageObject->PushDataInt(&m_Val,nRetLen);
		for(_Myt::iterator itPos=this->begin();itPos!=this->end();itPos++)
		{
			itPos->Save(pStorageObject);
		}
		pStorageObject->PushNodeCtlEnd(_T("vector"),this);
		return TRUE;
	}

};


template<typename SerializeObjectType>
class Serialize_list : public list<SerializeObjectType>,
	public SerializeObjectInterface
{
public:
	typedef Serialize_list<SerializeObjectType> _Myt;
	typedef list<SerializeObjectType> _Myt1;
	typedef list<typename SerializeObjectType::_MyObjectType>	_MyObjectType;

	StorageObjectInterface * m_pOutObject;
	_MyObjectType m_Val;
	Serialize_list()
	{

	};

	~Serialize_list()
	{

	};



	operator _MyObjectType &()
	{
		if(runstate.bCache)
		{
			
		}else
		{
			
			m_Val.clear();
			for(_Myt::iterator itPos=this->begin();itPos!=this->end();itPos++)
			{
				m_Val.insert(m_Val.end(),(SerializeObjectType::_MyObjectType)*itPos);
			}
			

			runstate.bCache=1;
		}
		return m_Val;
	}
	
	

	_Myt& operator=(_MyObjectType & _X) 
	{
		runstate.bCache=0;
		this->clear();
		//this->resize(_X.size());
		SerializeObjectType SerializeObject;
		SerializeObject.init(this,this->m_pFieldName,0,m_pOutObject);
		_MyObjectType::iterator itPos=_X.begin();
		for(unsigned int i=0;itPos!=_X.end();itPos++)
		{
			//cb.init(this,"cb",0,pOutObject);
			//SerializeObject.m_nIndex=i;
			//this->at(i)=SerializeObject;
			//this->at(i)=_X[i];
			SerializeObject.m_nIndex=i;
			SerializeObject=*itPos;
			this->push_back(SerializeObject);
			i++;
		}

		return *this;
	}
	
	
	BOOL init(SerializeRunData * pParent,TCHAR * pFieldName,unsigned int nIndex,StorageObjectInterface * pOutObject)
	{
		runstate.bCache=0;
		m_pParent=pParent;
		m_pFieldName=pFieldName;
		m_nIndex=nIndex;
		clear();

		m_pOutObject=pOutObject;
		/*
		Meminfo.init(this,"Meminfo",0);
				IOInfo.init(this,"IOInfo",0);*/
		return TRUE;
		
	}

	

	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
	{
		
		SerializeObjectType SerializeObject;
		SerializeObject.m_nIndex=this->size()+1;
		this->push_back(SerializeObject);
		this->back().init(this,m_pFieldName,this->size(),m_pOutObject);
		* RetObj=&this->back();

		return TRUE;
	};
	BOOL LoadSetData(tstring & Data)
	{
		//unsigned int nLen=Data.size()
		if(Data.at(0)==_T('\n'))
		{
			//空数组返回成功,继续下个字段
			return TRUE;
		}
		return FALSE;
	};

	BOOL LoadObjectEnd(SerializeLoadSaveInterface * Obj)
	{
		/*for(unsigned int i=0;i<this->size();i++)
		{
			this->at(i).init(this,m_pFieldName,i,m_pOutObject);
		}*/
		return FALSE;
	};

	BOOL Load(StorageObjectInterface * pStorageObject)
	{
		return pStorageObject->LoadObject(this);
	}

	BOOL Save(StorageObjectInterface * pStorageObject)
	{
		unsigned int nRetLen=4;
		pStorageObject->PushNodeCtlBegin(_T("list"),this);
		//pStorageObject->PushDataInt(&m_Val,nRetLen);
		for(_Myt::iterator itPos=this->begin();itPos!=this->end();itPos++)
		{
			itPos->Save(pStorageObject);
		}
		pStorageObject->PushNodeCtlEnd(_T("list"),this);
		return TRUE;
	}

};




template<typename FirstSerializeObject,typename SecondSerializeObject>
class Serialize_Set : public SerializeObjectInterface
{
public:
	typedef Serialize_Set<FirstSerializeObject, SecondSerializeObject> _Myt;
	FirstSerializeObject	m_Key;
	SecondSerializeObject	m_Val;

	Serialize_Set()
	{

	};

	~Serialize_Set()
	{

	};

	

	
	BOOL init(SerializeRunData * pParent,TCHAR * pFieldName,unsigned int nIndex,StorageObjectInterface * pOutObject)
	{
		runstate.bCache=0;
		m_pParent=pParent;
		m_pFieldName=pFieldName;
		m_nIndex=nIndex;
		
		m_Key.init(this,_T("Key"),0,pOutObject);
		m_Val.init(this,_T("Val"),0,pOutObject);

		return TRUE;
	}



	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
	{
		*RetObj=0;
		//tstring szKey=tstring(m_pFieldName)+tstring("_Key");
		//tstring szVal=tstring(m_pFieldName)+tstring("_Val");
		if(tstring(CurFieldAddr.pFieldName)==tstring(_T("Key")))
		{
			*RetObj=&m_Key;
		}else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("Val")))
		{
			*RetObj=&m_Val;
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

	BOOL Save(StorageObjectInterface * pStorageObject)
	{
		pStorageObject->PushNodeCtlBegin(_T("Serialize_Set"),this);

		m_Key.Save(pStorageObject);
		m_Val.Save(pStorageObject);

		pStorageObject->PushNodeCtlEnd(_T("Serialize_Set"),this);
		return TRUE;
	};
};


template<typename SerializeObjectKeyType,typename SerializeObjectType,typename Key_CompareType>
class Serialize_map : public map<typename SerializeObjectKeyType::_MyObjectType,Serialize_Set<SerializeObjectKeyType,SerializeObjectType>,Key_CompareType >,
	public SerializeObjectInterface
{
public:
	
	typedef typename SerializeObjectKeyType::_MyObjectType _MyObjectKeyType;
	typedef map<_MyObjectKeyType,Serialize_Set<SerializeObjectKeyType,SerializeObjectType>,Key_CompareType > _Myt;
	
	typedef map<_MyObjectKeyType,typename SerializeObjectType::_MyObjectType,Key_CompareType > _MyValueType;
	typedef _MyValueType _MyObjectType;

	Serialize_Set<SerializeObjectKeyType,SerializeObjectType>  * m_pTempSet;
	StorageObjectInterface * m_pOutObject;
	map<_MyObjectKeyType,typename SerializeObjectType::_MyObjectType,Key_CompareType > m_Val;
	tstring m_szFieldName;
	Serialize_map()
	{
		m_pTempSet=NULL;
	};

	~Serialize_map()
	{

	};

	
	SerializeObjectType & operator[](_MyObjectKeyType & Key)
	{
		_Myt::iterator itSet=this->find(Key);
		
		if(itSet!=this->end())
		{
			return itSet->second.m_Val;
		}else
		{
			Serialize_Set<SerializeObjectKeyType,SerializeObjectType> TempSet;
			TempSet.init(this,(TCHAR *)m_szFieldName.c_str(),0,m_pOutObject);
			(*(_Myt*)this)[Key]=TempSet;
			(*(_Myt*)this)[Key].init(this,(TCHAR *)m_szFieldName.c_str(),0,m_pOutObject);
			(*(_Myt*)this)[Key].m_Key=Key;
			//(*this)[Key].m_Val=itMap->second;
			return (*this)[Key].m_Val;
		}
	}

	SerializeObjectType & operator[](_MyObjectKeyType  Key)
	{
		_Myt::iterator itSet=this->find(Key);

		if(itSet!=this->end())
		{
			return itSet->second.m_Val;
		}else
		{
			Serialize_Set<SerializeObjectKeyType,SerializeObjectType> TempSet;
			//TempSet.init(this,(TCHAR *)m_szFieldName.c_str(),0,m_pOutObject);
			(*(_Myt*)this)[Key]=TempSet;
			(*(_Myt*)this)[Key].init(this,(TCHAR *)m_szFieldName.c_str(),0,m_pOutObject);
			(*(_Myt*)this)[Key].m_Key=Key;
			//(*this)[Key].m_Val=itMap->second;
			return (*(_Myt*)this)[Key].m_Val;
		}
	}
	
	operator _MyValueType &()
	{
		if(runstate.bCache)
		{
			
		}else
		{
			
			m_Val.clear();
			for(_Myt::iterator itPos=this->begin();itPos!=this->end();itPos++)
			{
				//m_Val.insert(m_Val.end(),(ObjectType)*itPos);
				m_Val[itPos->first]=(typename SerializeObjectType::_MyObjectType)itPos->second.m_Val;
			}
			

			runstate.bCache=1;
		}
		return m_Val;
	}
	
	

	_Myt& operator=(_MyValueType & _X) 
	{
		runstate.bCache=0;
		
		this->clear();
		Serialize_Set<SerializeObjectKeyType,SerializeObjectType> SerializeObject;
		SerializeObject.init(this,(TCHAR *)m_szFieldName.c_str(),0,m_pOutObject);
		_MyValueType::iterator itMap=_X.begin();
		for(int i=0;itMap!=_X.end();itMap++)
		{
			//cb.init(this,"cb",0,pOutObject);
			//SerializeObject=_X[itMap->first];
			(*(_Myt*)this)[itMap->first]=SerializeObject;
			(*(_Myt*)this)[itMap->first].init(this,(TCHAR *)m_szFieldName.c_str(),i,m_pOutObject);
			(*(_Myt*)this)[itMap->first].m_Key=itMap->first;
			(*(_Myt*)this)[itMap->first].m_Val=itMap->second;
			//(*this)[itMap->first]=_X[itMap->first];
			i++;
		}

		return *this;
	}
	
	
	BOOL init(SerializeRunData * pParent,TCHAR * pFieldName,unsigned int nIndex,StorageObjectInterface * pOutObject)
	{
		runstate.bCache=0;
		m_pParent=pParent;
		m_pFieldName=pFieldName;
		m_nIndex=nIndex;

		clear();

		m_pOutObject=pOutObject;
		m_szFieldName=tstring(m_pFieldName)+tstring(_T("_MapSet"));
		//m_TempSet.init(this,(TCHAR *)m_szFieldName.c_str(),0,pOutObject);
	
		/*
		Meminfo.init(this,"Meminfo",0);
				IOInfo.init(this,"IOInfo",0);*/
		return TRUE;
		
	}

	

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

	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
	{
		if(m_pTempSet) delete m_pTempSet;
		m_pTempSet=new Serialize_Set<SerializeObjectKeyType,SerializeObjectType>;

		m_pTempSet->m_nIndex=this->size();
		m_pTempSet->init(this,(TCHAR *)m_szFieldName.c_str(),0,m_pOutObject);
		/*
		* RetObj=NULL;
				if(tstring(CurFieldAddr.pFieldName)==tstring(_T("Key")))
				{
					*RetObj=&m_TempSet.m_Key;
				} else if(tstring(CurFieldAddr.pFieldName)==tstring(_T("Val")))
				{
					*RetObj=&m_TempSet.m_Val;
				}*/
		
		//m_TempSet.m_Key.init()
		* RetObj=m_pTempSet;
		return TRUE;
	};
	BOOL LoadSetData(tstring & Data)
	{
		return TRUE;
	};

	BOOL LoadCurObjectEnd(SerializeLoadSaveInterface * ChildObj)
	{
		Serialize_Set<SerializeObjectKeyType,SerializeObjectType> * pObj=(Serialize_Set<SerializeObjectKeyType,SerializeObjectType>*)ChildObj;
		(*(_Myt*)this)[pObj->m_Key]=*pObj;
		return TRUE;
	};

	BOOL Load(StorageObjectInterface * pStorageObject)
	{
		return pStorageObject->LoadObject(this);
	}

	BOOL Save(StorageObjectInterface * pStorageObject)
	{
		unsigned int nRetLen=4;
		pStorageObject->PushNodeCtlBegin(_T("map"),this);
		//pStorageObject->PushDataInt(&m_Val,nRetLen);
		for(_Myt::iterator itPos=this->begin();itPos!=this->end();itPos++)
		{
			//itPos->first->Save(pStorageObject);
			itPos->second.Save(pStorageObject);
		}
		pStorageObject->PushNodeCtlEnd(_T("map"),this);
		return TRUE;
	}

};

template<typename ObjectType>
class Serialize_BaseObject : public SerializeObjectInterface
{
public:
	typedef Serialize_BaseObject<ObjectType> _Myt;
	typedef ObjectType _MyObjectType;
	ObjectType m_Val;
	StorageObjectInterface * m_pOutObject;
	Serialize_BaseObject()
	{

	};

	~Serialize_BaseObject()
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
		return TRUE;
		
	}

	

	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
	{
		return FALSE;
	};

	BOOL Load(StorageObjectInterface * pStorageObject)
	{																					
		return pStorageObject->LoadObject(this);
	}

	operator _MyObjectType()
	{
		if(runstate.bCache)
		{
			
		}else
		{
			/*
			m_Val.Meminfo=Meminfo;
						m_Val.IOInfo=IOInfo;*/
			//vector<FieldAddr > Addr;
			unsigned int nLen=sizeof(_MyObjectType);
			m_pOutObject->GetObjectVal(this,&m_Val,nLen);
			

			runstate.bCache=1;
		}
		return m_Val;
	}
	_Myt& operator=( _MyObjectType _X) 
	{
		runstate.bCache=1;
		vector<FieldAddr > Addr;

		unsigned int nLen=sizeof(_MyObjectType);
		m_Val=_X;
		m_pOutObject->SetObjectVal(this,&m_Val,nLen);
		
		//清除缓存
		for(SerializeRunData * pPos=m_pParent;pPos!=NULL;pPos=pPos->m_pParent)
		{
			pPos->runstate.bCache=0;
		}

		return *this;
	}
	/*
	_Myt& operator=(ObjectType & _X) 
		{
			runstate.bCache=1;
			//vector<FieldAddr > Addr;
	
			unsigned int nLen=sizeof(ObjectType);
			m_Val=_X;
			m_pOutObject->SetObjectVal(this,&m_Val,nLen);
			
			//清除缓存
			for(SerializeRunData * pPos=m_pParent;pPos!=NULL;pPos=pPos->m_pParent)
			{
				pPos->runstate.bCache=0;
			}
			/ *
			Meminfo=_X.Meminfo;
					IOInfo=_X.IOInfo;* /
			
	
			return *this;
		}*/
	

	
	BOOL LoadSetData(tstring & Data)
	{
		
		CMyString szData((TCHAR *)Data.c_str(),Data.length()*sizeof(TCHAR));
		m_Val=AtoVal((TCHAR *)Data.c_str(),10,ObjectType());
			//atoi((char *)szData);
		runstate.bCache=1;
		return TRUE;
	};

	

	BOOL Save(StorageObjectInterface * pStorageObject)
	{
		unsigned int nRetLen=sizeof(_MyObjectType);
		pStorageObject->PushNodeCtlBegin(_T("VAL"),this);
		pStorageObject->PushDataVal(&m_Val,nRetLen);
		pStorageObject->PushNodeCtlEnd(_T("VAL"),this);
		return TRUE;
	}

};

template<>
class Serialize_BaseObject<double> : public SerializeObjectInterface
{
public:
	typedef Serialize_BaseObject<double> _Myt;
	typedef double _MyObjectType;
	double m_Val;
	StorageObjectInterface * m_pOutObject;
	Serialize_BaseObject()
	{

	};

	~Serialize_BaseObject()
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
		return TRUE;
		
	}



	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
	{
		return FALSE;
	};

	BOOL Load(StorageObjectInterface * pStorageObject)
	{																					
		return pStorageObject->LoadObject(this);
	}

	operator _MyObjectType()
	{
		if(runstate.bCache)
		{
			
		}else
		{
			unsigned int nLen=sizeof(_MyObjectType);
			m_pOutObject->GetObjectVal(this,&m_Val,nLen);
			

			runstate.bCache=1;
		}
		return m_Val;
	}
	_Myt& operator=( _MyObjectType _X) 
	{
		runstate.bCache=1;

		unsigned int nLen=sizeof(_MyObjectType);
		m_Val=_X;
		m_pOutObject->SetObjectVal(this,&m_Val,nLen);
		
		//清除缓存
		for(SerializeRunData * pPos=m_pParent;pPos!=NULL;pPos=pPos->m_pParent)
		{
			pPos->runstate.bCache=0;
		}

		return *this;
	}
	
	

	
	BOOL LoadSetData(tstring & Data)
	{
		CMyString szData((TCHAR *)Data.c_str(),Data.length()*sizeof(TCHAR));
		m_Val=atof((char *)szData);
		runstate.bCache=1;
		return TRUE;
	};

	

	BOOL Save(StorageObjectInterface * pStorageObject)
	{
		TCHAR szOut[64];
		sprintf_s_t(szOut,_T("%f"),m_Val);
		unsigned int nRetLen=strlen_t(szOut)*sizeof(TCHAR);
		pStorageObject->PushNodeCtlBegin(_T("float"),this);
		pStorageObject->PushDataString(szOut,nRetLen);
		pStorageObject->PushNodeCtlEnd(_T("float"),this);
		return TRUE;
	}

};


template<>
class Serialize_BaseObject<tstring> : public SerializeObjectInterface
{
public:
	typedef Serialize_BaseObject<tstring> _Myt;
	typedef tstring _MyObjectType;
	tstring m_Val;
	StorageObjectInterface * m_pOutObject;
	Serialize_BaseObject()
	{

	};

	~Serialize_BaseObject()
	{

	};

	BOOL init(SerializeRunData * pParent,TCHAR * pFieldName,unsigned int nIndex,StorageObjectInterface * pOutObject,unsigned int nNum=0)
	{
		runstate.bCache=0;
		m_pParent=pParent;
		m_pFieldName=pFieldName;
		m_nIndex=nIndex;
		m_Val.c_str();

		m_pOutObject=pOutObject;
		/*
		Meminfo.init(this,"Meminfo",0);
				IOInfo.init(this,"IOInfo",0);*/
		return TRUE;
		
	}

	

	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
	{
		return FALSE;
	};

	BOOL Load(StorageObjectInterface * pStorageObject)
	{																					
		return pStorageObject->LoadObject(this);
	}

	operator _MyObjectType &()
	{
		if(runstate.bCache)
		{
			
		}else
		{
			/*
			m_Val.Meminfo=Meminfo;
						m_Val.IOInfo=IOInfo;*/
			//vector<FieldAddr > Addr;
			//unsigned int nLen=sizeof(tstring);
			m_pOutObject->GetStringObject(this,m_Val);
			

			runstate.bCache=1;
		}
		return m_Val;
	}
	_Myt& operator=( _MyObjectType & _X) 
	{
		runstate.bCache=1;
		vector<FieldAddr > Addr;

		unsigned int nLen=sizeof(_MyObjectType);
		m_Val=_X;
		m_pOutObject->SetStringObject(this,m_Val);
		
		//清除缓存
		for(SerializeRunData * pPos=m_pParent;pPos!=NULL;pPos=pPos->m_pParent)
		{
			pPos->runstate.bCache=0;
		}

		return *this;
	}

	_Myt& operator=(const  _MyObjectType & _X) 
	{
		runstate.bCache=1;
		vector<FieldAddr > Addr;

		unsigned int nLen=sizeof(_MyObjectType);
		m_Val=_X;
		m_pOutObject->SetStringObject(this,m_Val);

		//清除缓存
		for(SerializeRunData * pPos=m_pParent;pPos!=NULL;pPos=pPos->m_pParent)
		{
			pPos->runstate.bCache=0;
		}

		return *this;
	}
	
	
	BOOL LoadSetData(tstring & Data)
	{
		m_Val=Data;
		runstate.bCache=1;
		return TRUE;
	};

	

	BOOL Save(StorageObjectInterface * pStorageObject)
	{
		unsigned int nRetLen=m_Val.length()*sizeof(TCHAR);
		pStorageObject->PushNodeCtlBegin(_T("string"),this);
		pStorageObject->PushDataString((LPTSTR)m_Val.c_str(),nRetLen);
		pStorageObject->PushNodeCtlEnd(_T("string"),this);
		return TRUE;
	}

};

template<>
class Serialize_BaseObject<CAutoVal> : public SerializeObjectInterface
{
public:
	typedef Serialize_BaseObject<CAutoVal> _Myt;
	typedef CAutoVal _MyObjectType;
	CAutoVal m_Val;
	StorageObjectInterface * m_pOutObject;
	Serialize_BaseObject()
	{

	};

	~Serialize_BaseObject()
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
		return TRUE;
		
	}

	

	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
	{
		return FALSE;
	};

	BOOL Load(StorageObjectInterface * pStorageObject)
	{																					
		return pStorageObject->LoadObject(this);
	}

	operator _MyObjectType &()
	{
		if(runstate.bCache)
		{
			
		}else
		{
			/*
			m_Val.Meminfo=Meminfo;
						m_Val.IOInfo=IOInfo;*/
			//vector<FieldAddr > Addr;
			//unsigned int nLen=sizeof(tstring);
			m_pOutObject->GetStringObject(this,m_Val);
			

			runstate.bCache=1;
		}
		return m_Val;
	}
	_Myt& operator=( _MyObjectType & _X) 
	{
		runstate.bCache=1;
		vector<FieldAddr > Addr;

		unsigned int nLen=sizeof(_MyObjectType);
		m_Val=_X;
		m_pOutObject->SetStringObject(this,m_Val);
		
		//清除缓存
		for(SerializeRunData * pPos=m_pParent;pPos!=NULL;pPos=pPos->m_pParent)
		{
			pPos->runstate.bCache=0;
		}

		return *this;
	}

	_Myt& operator=(const  _MyObjectType & _X) 
	{
		runstate.bCache=1;
		vector<FieldAddr > Addr;

		unsigned int nLen=sizeof(_MyObjectType);
		m_Val=_X;
		m_pOutObject->SetStringObject(this,(tstring)m_Val);

		//清除缓存
		for(SerializeRunData * pPos=m_pParent;pPos!=NULL;pPos=pPos->m_pParent)
		{
			pPos->runstate.bCache=0;
		}

		return *this;
	}
	
	
	BOOL LoadSetData(tstring & Data)
	{
		m_Val=Data;
		runstate.bCache=1;
		return TRUE;
	};

	

	BOOL Save(StorageObjectInterface * pStorageObject)
	{
		unsigned int nRetLen=((tstring&)m_Val).length()*sizeof(TCHAR);
		pStorageObject->PushNodeCtlBegin(_T("CAutoVal"),this);
		pStorageObject->PushDataString((LPTSTR)((tstring&)m_Val).c_str(),nRetLen);
		pStorageObject->PushNodeCtlEnd(_T("CAutoVal"),this);
		return TRUE;
	}

};


//HEXSER<DWORD>	Test;
template<typename ValType,SerDstType DstType>
class SER_TO_X 
{
public:
	typedef SER_TO_X<ValType,DstType> _Myt;
	ValType m_Val;
	SER_TO_X()
	{

	};

	~SER_TO_X()
	{

	};


	operator ValType &()
	{
		return m_Val;
	}
	
	_Myt& operator=( ValType  _X) 
	{

		m_Val=_X;

		return *this;
	}

};


template<typename ValType,SerDstType DstType>
class Serialize_BaseObject<SER_TO_X<ValType,DstType>> : public SerializeObjectInterface
{
public:
	typedef Serialize_BaseObject<SER_TO_X<ValType,DstType>> _Myt;
	typedef SER_TO_X<ValType,DstType> _MyObjectType;
	SER_TO_X<ValType,DstType> m_Val;
	StorageObjectInterface * m_pOutObject;
	Serialize_BaseObject()
	{

	};

	~Serialize_BaseObject()
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
		return TRUE;
		
	}


	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
	{
		return FALSE;
	};

	BOOL Load(StorageObjectInterface * pStorageObject)
	{																					
		return pStorageObject->LoadObject(this);
	}

	operator _MyObjectType &()
	{
		if(runstate.bCache)
		{
			
		}else
		{
			/*
			m_Val.Meminfo=Meminfo;
						m_Val.IOInfo=IOInfo;*/
			//vector<FieldAddr > Addr;
			unsigned int nLen=sizeof(double);
			tstring szRst;
			m_pOutObject->GetStringObject(this,szRst);
			

			runstate.bCache=1;
		}
		return m_Val;
	}
	_Myt& operator=( _MyObjectType _X) 
	{
		runstate.bCache=1;

		m_Val=_X;
		tstring szRst;
		m_pOutObject->SetStringObject(this,szRst);
		
		//清除缓存
		for(SerializeRunData * pPos=m_pParent;pPos!=NULL;pPos=pPos->m_pParent)
		{
			pPos->runstate.bCache=0;
		}

		return *this;
	}
	
	
	BOOL LoadSetData(tstring & Data)
	{
		//m_Val=atof(Data.c_str());
		//TCHAR szOut[64];
		//BOOL bRst=DecodeHex((TCHAR *)Data.c_str(),(BYTE *)&m_Val.m_Val,sizeof(ValType));
		BOOL bRet=SetMe(Data);
		if(bRet) runstate.bCache=1;
		return bRet;
	};

	

	BOOL Save(StorageObjectInterface * pStorageObject)
	{
		tstring szOut;
		//EncodeHex((BYTE *)&m_Val.m_Val,sizeof(ValType),szOut);
		GetMe(szOut);
		
		unsigned int nRetLen=szOut.length()*sizeof(TCHAR);
		pStorageObject->PushNodeCtlBegin(_T("VAL"),this);
		pStorageObject->PushDataString((LPTSTR)szOut.c_str(),nRetLen);
		pStorageObject->PushNodeCtlEnd(_T("VAL"),this);
		return TRUE;
		
		return FALSE;
	}
private:
	unsigned int GetType()
	{
		unsigned int r=0;
		switch(DstType)
		{
		case DecString:
			r=10;
			break;
		case HexString:
			r=16;
			break;
		case BinString:
			r=2;
			break;
		case Base64String:
			r=64;
		default:
			return FALSE;
		}
		return r;
	}
	BOOL SetMe(IN tstring & Val)
	{
		
		if(DstType==Base64String)
		{

		}else
		{
			unsigned int r=GetType();
			if(r<33)
			{
				switch(sizeof(ValType))
				{
				case 4:
					//m_Val=atoi_t(Val.c_str());
					//break;
				case 8 :
					//m_Val=atoi64_t(Val.c_str());
					//break;
					m_Val=AtoVal((TCHAR *)Val.c_str(),r,ValType());
					break;
				default:
					return FALSE;
				}
			}
		}
		return TRUE;
	}
	BOOL GetMe(OUT tstring & Val)
	{
		unsigned int r=GetType();
		TCHAR szVal[64];
		if(r<33)
		{
			switch(sizeof(ValType))
			{
			case 4:
				Val=itoa_t((int)m_Val,szVal,r);
				break;
			case 8 :
				Val=i64toa_t((__int64)m_Val,szVal,r);
				break;
			default:
				return FALSE;
			}
		}
		return TRUE;
	}
};


template<SerDstType DstType>
class SER_TO_X<tstring,DstType> :public tstring
{
public:
	typedef SER_TO_X<tstring,DstType> _Myt;
	//tstring m_Val;
	SER_TO_X()
	{

	};

	~SER_TO_X()
	{

	};


	/*operator tstring &()
	{
		return (tstring)*this;
	}*/

	_Myt& operator=( tstring & _X) 
	{

		*((tstring*)this)=_X;

		return *this;
	}

	_Myt& operator=(const tstring & _X) 
	{

		*((tstring*)this)=_X;

		return *this;
	}

	_Myt& operator=( LPCTSTR _X) 
	{

		*((tstring*)this)=_X;

		return *this;
	}

	_Myt& operator=( LPTSTR _X) 
	{

		*((tstring*)this)=_X;

		return *this;
	}

};

template<SerDstType DstType>
class Serialize_BaseObject<SER_TO_X<tstring,DstType>> : public SerializeObjectInterface
{
public:
	typedef Serialize_BaseObject<SER_TO_X<tstring,DstType>> _Myt;
	typedef SER_TO_X<tstring,DstType> _MyObjectType;
	SER_TO_X<tstring,DstType> m_Val;
	StorageObjectInterface * m_pOutObject;
	Serialize_BaseObject()
	{

	};

	~Serialize_BaseObject()
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
		return TRUE;
		
	}


	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
	{
		return FALSE;
	};

	BOOL Load(StorageObjectInterface * pStorageObject)
	{																					
		return pStorageObject->LoadObject(this);
	}

	operator _MyObjectType &()
	{
		if(runstate.bCache)
		{
			
		}else
		{
			/*
			m_Val.Meminfo=Meminfo;
						m_Val.IOInfo=IOInfo;*/
			//vector<FieldAddr > Addr;
			//unsigned int nLen=sizeof(double);
			tstring szRst;
			m_pOutObject->GetStringObject(this,szRst);
			

			runstate.bCache=1;
		}
		return m_Val;
	}
	_Myt& operator=( _MyObjectType _X) 
	{
		runstate.bCache=1;

		m_Val=_X;
		tstring szRst;
		m_pOutObject->SetStringObject(this,szRst);
		
		//清除缓存
		for(SerializeRunData * pPos=m_pParent;pPos!=NULL;pPos=pPos->m_pParent)
		{
			pPos->runstate.bCache=0;
		}

		return *this;
	}
	
	
	BOOL LoadSetData(tstring & Data)
	{
		//m_Val=atof(Data.c_str());
		//TCHAR szOut[64];
		//BOOL bRst=DecodeHex((TCHAR *)Data.c_str(),(BYTE *)&m_Val.m_Val,sizeof(ValType));
		BOOL bRet=SetMe(Data);
		if(bRet) runstate.bCache=1;
		return bRet;
	};

	

	BOOL Save(StorageObjectInterface * pStorageObject)
	{
		tstring szOut;
		//EncodeHex((BYTE *)&m_Val.m_Val,sizeof(ValType),szOut);
		GetMe(szOut);
		
		unsigned int nRetLen=szOut.length()*sizeof(TCHAR);
		pStorageObject->PushNodeCtlBegin(_T("VAL"),this);
		pStorageObject->PushDataString((LPTSTR)szOut.c_str(),nRetLen);
		pStorageObject->PushNodeCtlEnd(_T("VAL"),this);
		return TRUE;
		
		return FALSE;
	}
private:
	unsigned int GetType()
	{
		unsigned int r=0;
		switch(DstType)
		{
		case DecString:
			r=10;
			break;
		case HexString:
			r=16;
			break;
		case BinString:
			r=2;
			break;
		case Base64String:
			r=64;
		default:
			return FALSE;
		}
		return r;
	}
	BOOL SetMe(IN tstring & Val)
	{
		switch(DstType)
		{
		case DecString:
			//r=10;
			break;
		case HexString:
			{
				if(Val==_T("NULL"))
				{
					m_Val.clear();
				}else
				{
					unsigned int nLen=Val.length()*sizeof(TCHAR);
					BYTE * pBuffer=new BYTE[nLen];
					memset(pBuffer,0,nLen);
					DecodeHex((TCHAR*)Val.c_str(),pBuffer,nLen);
					m_Val=(TCHAR *)pBuffer;
					delete pBuffer;
				}
			}
			//r=16;
			break;
		case BinString:
			//r=2;
			break;
		case Base64String:
			break;
		case Base64ZipString:
			{
				if(Val==_T("NULL"))
				{
					m_Val.clear();
				}else
				{
					unsigned int nLen=Val.length()*sizeof(TCHAR);
					vector<unsigned char> Buf;
					if(CBase64Zip::Base64ZipUnCompress(Val,Buf))
					{
						m_Val=(TCHAR *)(&Buf[0]);
					}
				}
			}
			
			break;
		case XmlString:
			{
				if(Val==_T("NULL"))
				{
					m_Val.clear();
				}else
				{
					CXmlString::GetStringFromXMLString(m_Val,Val);
				}
			}

			break;
			//r=64;
		default:
			return FALSE;
		}
		
		/*if(DstType==Base64String)
		{

		}else
		{
			unsigned int r=GetType();
			if(r<33)
			{
				switch(sizeof(ValType))
				{
				case 4:
					//m_Val=atoi_t(Val.c_str());
					//break;
				case 8 :
					//m_Val=atoi64_t(Val.c_str());
					//break;
					m_Val=AtoVal((TCHAR *)Val.c_str(),r,ValType());
					break;
				default:
					return FALSE;
				}
			}
		}*/
		return TRUE;
	}
	BOOL GetMe(OUT tstring & Val)
	{
		switch(DstType)
		{
		case DecString:
			//r=10;
			break;
		case HexString:
			{
				if(m_Val.length()==0)
				{
					Val=_T("NULL");
				}else
				{
					EncodeHex((BYTE *)m_Val.c_str(),m_Val.length()*sizeof(TCHAR),Val);
				}
			}
			//r=16;
			break;
		case BinString:
			//r=2;
			break;
		case Base64String:
			//r=64;r
			break;
		case Base64ZipString:
			{
				if(m_Val.length()==0)
				{
					Val=_T("NULL");
				}else
				{
					CBase64Zip::Base64ZipCompress((unsigned char *)m_Val.c_str(),m_Val.length()*sizeof(TCHAR),Val);
				}
			}
			break;
		case XmlString:
			{
				if(m_Val.length()==0)
				{
					Val=_T("NULL");
				}else
				{
					CXmlString::GetXMLStringFromtstring(Val,m_Val);
				}
			}
			break;
		default:
			return FALSE;
		}
		return TRUE;
	}
};


template<typename SerializeObjectType,int Num>
class Serialize_BaseObjectBinaryArray : public SerializeObjectInterface
{
public:
	typedef Serialize_BaseObjectBinaryArray<SerializeObjectType,Num> _Myt;
	SerializeObjectType m_Val[Num];
	StorageObjectInterface * m_pOutObject;
	Serialize_BaseObjectBinaryArray()
	{

	};

	~Serialize_BaseObjectBinaryArray()
	{

	};

	BOOL init(SerializeRunData * pParent,TCHAR * pFieldName,unsigned int nIndex,StorageObjectInterface * pOutObject,unsigned int nNum=0)
	{
		runstate.bCache=0;
		m_pParent=pParent;
		m_pFieldName=pFieldName;
		m_nIndex=nIndex;


		m_pOutObject=pOutObject;
		
		return TRUE;
		
	}

	

	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
	{
		return FALSE;
	};

	BOOL Load(StorageObjectInterface * pStorageObject)
	{																					
		return pStorageObject->LoadObject(this);
	}

	operator SerializeObjectType *()
	{
		if(runstate.bCache)
		{
			
		}else
		{
			/*
			m_Val.Meminfo=Meminfo;
						m_Val.IOInfo=IOInfo;*/
			//vector<FieldAddr > Addr;
			unsigned int nLen=sizeof(m_Val);
			m_pOutObject->GetBinaryObject(this,&m_Val,nLen);
			

			runstate.bCache=1;
		}
		return &m_Val[0];
	}
	
	_Myt& operator=(SerializeObjectType (&Val)[Num]) 
	{
		runstate.bCache=1;
		//vector<FieldAddr > Addr;

		unsigned int nLen=sizeof(m_Val);
		memcpy(m_Val,Val,nLen);
		m_pOutObject->SetBinaryObject(this,&m_Val,nLen);
		
		//清除缓存
		for(SerializeRunData * pPos=m_pParent;pPos!=NULL;pPos=pPos->m_pParent)
		{
			pPos->runstate.bCache=0;
		}
		/*
		Meminfo=_X.Meminfo;
				IOInfo=_X.IOInfo;*/
		

		return *this;
	}

	
	BOOL LoadSetData(tstring & Data)
	{
		BOOL bRst=DecodeHex((TCHAR *)Data.c_str(),(BYTE *)&m_Val[0],sizeof(m_Val));
		if(bRst)
		{
			runstate.bCache=1;
		}
		return bRst;
	};

	

	BOOL Save(StorageObjectInterface * pStorageObject)
	{
		unsigned int nRetLen=sizeof(m_Val);
		TCHAR szFieldType[16];
		sprintf_s_t(szFieldType,16,"CHAR_ARRAY_%d",Num);
		pStorageObject->PushNodeCtlBegin(szFieldType,this);
		pStorageObject->PushDataBinary(&m_Val,nRetLen);
		pStorageObject->PushNodeCtlEnd(szFieldType,this);
		return TRUE;
	}
};



template<typename SerializeObjectType,int Num>
class Serialize_BaseObjectStringArray : public SerializeObjectInterface
{
public:
	typedef Serialize_BaseObjectStringArray<SerializeObjectType,Num> _Myt;
	SerializeObjectType m_Val[Num];
	StorageObjectInterface * m_pOutObject;
	Serialize_BaseObjectStringArray()
	{

	};

	~Serialize_BaseObjectStringArray()
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
		return TRUE;
		
	}

	
	BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
	{
		return FALSE;
	};

	BOOL Load(StorageObjectInterface * pStorageObject)
	{																					
		return pStorageObject->LoadObject(this);
	}

	operator SerializeObjectType *()
	{
		if(runstate.bCache)
		{
			
		}else
		{
			
			unsigned int nLen=sizeof(m_Val);
			m_pOutObject->GetStringObject(this,&m_Val,nLen);
			

			runstate.bCache=1;
		}
		return &m_Val[0];
	}
	
	_Myt& operator=(SerializeObjectType (&Val)[Num]) 
	{
		runstate.bCache=1;
		//vector<FieldAddr > Addr;
		
		unsigned int nLen=sizeof(m_Val);
		memcpy(m_Val,Val,nLen);
		m_pOutObject->SetStringObject(this,&m_Val,nLen);
		
		//清除缓存
		for(SerializeRunData * pPos=m_pParent;pPos!=NULL;pPos=pPos->m_pParent)
		{
			pPos->runstate.bCache=0;
		}
		

		return *this;
	}

	
	BOOL LoadSetData(tstring & Data)
	{
		unsigned int nLen=min(sizeof(m_Val)-1,Data.length()*sizeof(TCHAR));
		memset(m_Val,0,sizeof(m_Val));
		memcpy(m_Val,Data.c_str(),nLen);
		runstate.bCache=1;
		
		return TRUE;
	};

	

	BOOL Save(StorageObjectInterface * pStorageObject)
	{
		unsigned int nRetLen=strlen_t(m_Val)*sizeof(TCHAR);
		TCHAR szFieldType[16];
		sprintf_s_t(szFieldType,16,"CHAR_ARRAY_%d",Num);
		pStorageObject->PushNodeCtlBegin(szFieldType,this);
		pStorageObject->PushDataString((LPTSTR)&m_Val,nRetLen);
		pStorageObject->PushNodeCtlEnd(szFieldType,this);
		return TRUE;
	}
};



//typedef Serialize_BaseObject<DWORD> Serialize_DWORD;




template<typename ObjectType,typename SerializeStructType>
class Serialize_StructBase : public SerializeObjectInterface
{
public:
	typedef SerializeStructType _Myt;
	//typedef typename SerializeStructType::_MyObjectType _MyObjectType1;
	ObjectType m_Val;
	Serialize_StructBase(){};
	~Serialize_StructBase(){};
	
	operator ObjectType &()
	{
		if(runstate.bCache)
		{

		}else
		{
			((SerializeStructType*)this)->GetData();
			runstate.bCache=1;
		}
		return m_Val;
	}

	

	BOOL init(SerializeRunData * pParent,TCHAR * pFieldName,unsigned int nIndex,StorageObjectInterface * pOutObject,unsigned int nNum=0)
	{
		runstate.bCache=0;
		m_pParent=pParent;
		m_pFieldName=pFieldName;
		m_nIndex=nIndex;

		
		((SerializeStructType*)this)->Construct(pOutObject);

		return TRUE;
	}

	

	BOOL LoadSetData(tstring & Data)
	{
		return FALSE;
	};

	BOOL Load(StorageObjectInterface * pStorageObject)
	{
		return pStorageObject->LoadObject(this);
	}


protected:
	
private:
};
