//SerializeInterface.h
#pragma once

typedef struct _tagFieldAddr
{
	TCHAR * pFieldName;
	//FieldFieldAttributes	FieldAttributes;
	unsigned int nIndex;
	_tagFieldAddr * pChild;
}FieldAddr,*PFieldAddr;

typedef struct _tagRunState
{
	unsigned int bCache:1;		//加载失败
	unsigned int bReadFail:1;	//加载失败
}RunState,*PRunState;



class SerializeRunData
{
public:
	SerializeRunData(){};
	~SerializeRunData(){};
	SerializeRunData * m_pParent;
	TCHAR * m_pFieldName;
	unsigned int m_nIndex;
	//BOOL bCache;
	RunState runstate;

	//兄弟

	//序列化容器用于存储
	//vector<FieldAddr > m_MeAddr;
	/*
	BOOL GetAddress(vector<FieldAddr > &Addr)
		{
			SerializeRunData * pCur=this;
			FieldAddr CurAddr;
			for(;pCur!=NULL;pCur=pCur->m_pParent)
			{
				CurAddr.nIndex=pCur->m_nIndex;
				CurAddr.pFieldName=pCur->m_pFieldName;
				Addr.push_back(CurAddr);
			}
			return TRUE;
		}*/
	
protected:
private:
};

class SerializeObjectInterface ;

class SerializeLoadSaveInterface;

//存储对象接口
class StorageObjectInterface
{
public:
	StorageObjectInterface(){};
	~StorageObjectInterface(){};
	//初始化存储对象
	virtual BOOL init(tstring & szFilePath,CharacterType nType=Ansi)
	{
		return TRUE;
	}

	//随机读数据接口 得到指定地址的int型数据
	virtual BOOL GetObjectVal(IN SerializeRunData * Addr,IN OUT void * pOutData,IN OUT unsigned int & nLen/*IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap*/)
	{
		return FALSE;
	}
	//随机写数据接口 保存int型数据到指定地址
	virtual BOOL SetObjectVal(IN SerializeRunData * Addr,IN void * pInData,IN OUT unsigned int & nLen)
	{
		return FALSE;
	}

	virtual BOOL GetBinaryObject(IN SerializeRunData * Addr,IN OUT void * pOutData,IN OUT unsigned int & nLen)
	{
		return FALSE;
	}

	virtual BOOL SetBinaryObject(IN SerializeRunData * Addr,IN void * pInData,IN OUT unsigned int & nLen)
	{
		return FALSE;
	}

	virtual BOOL GetStringObject(IN SerializeRunData * Addr,IN OUT void * pOutData,IN OUT unsigned int & nLen)
	{
		return FALSE;
	}

	virtual BOOL GetStringObject(IN SerializeRunData * Addr,tstring & pOutData)
	{
		return FALSE;
	}

	virtual BOOL SetStringObject(IN SerializeRunData * Addr,IN void * pInData,IN OUT unsigned int & nLen)
	{
		return FALSE;
	}

	virtual BOOL SetStringObject(IN SerializeRunData * Addr,IN tstring & pInData)
	{
		return FALSE;
	}

	//顺序压入数据 int型
	//template<typename ValType>
	virtual BOOL PushDataVal(IN void * pInData,IN OUT unsigned int & nLen)
	{
		return FALSE;
	}
	//顺序压入数据 字符串型
	virtual BOOL PushDataString(IN LPTSTR pInData,IN OUT unsigned int & nLen)
	{
		return FALSE;
	}

	//顺序压入数据 二进制型
	virtual BOOL PushDataBinary(IN void * pInData,IN OUT unsigned int & nLen)
	{
		return FALSE;
	}

	//设置当前节点属性
	//顺序保存节点开始
	virtual BOOL PushNodeCtlBegin(TCHAR * szFieldType,SerializeRunData * CurFieldAddr)
	{
		return FALSE;
	}
	//顺序保存节点结束
	virtual BOOL PushNodeCtlEnd(TCHAR * szFieldType,SerializeRunData * CurFieldAddr)
	{
		return FALSE;
	}

	//顺序化主控加载
	virtual BOOL LoadObject(SerializeLoadSaveInterface * pObj)
	{
		return FALSE;
	}
protected:
	
private:
};



class SerializeLoadSaveInterface
{
public:
	SerializeLoadSaveInterface(){};
	~SerializeLoadSaveInterface(){};
	
	//主动顺序加载时主动序列化接口

	//按照对象树得到一个存储节点
	virtual BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
	{
		return FALSE;
	};

	//在当前节点查找可用子节点
	virtual BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
	{
		return FALSE;
	};
	//设置节点数据
	virtual BOOL LoadSetData(tstring & Data)
	{
		return FALSE;
	};

	//当前节点子节点Load结束
	virtual BOOL LoadCurObjectEnd(SerializeLoadSaveInterface * ChildObj)
	{
		return FALSE;
	};


	//当前节点Load开始
	virtual BOOL LoadObjectBegin(SerializeLoadSaveInterface * Obj)
	{
		return FALSE;
	};

	//当前节点Load结束
	virtual BOOL LoadObjectEnd(SerializeLoadSaveInterface * Obj)
	{
		return FALSE;
	};

	//主动顺序保存到序列化对象接口
	virtual BOOL Save(StorageObjectInterface * pStorageObject)
	{
		return pStorageObject->LoadObject(this);
	}

	//主动顺序保存到序列化对象接口
	virtual BOOL Load(StorageObjectInterface * pStorageObject)
	{
		return FALSE;
	}
};

class SerializeObjectInterface :
	public SerializeRunData,
	public SerializeLoadSaveInterface
{
public:
	SerializeObjectInterface(){};
	~SerializeObjectInterface(){};
protected:

private:
};
