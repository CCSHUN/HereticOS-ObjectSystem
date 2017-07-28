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
	unsigned int bCache:1;		//����ʧ��
	unsigned int bReadFail:1;	//����ʧ��
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

	//�ֵ�

	//���л��������ڴ洢
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

//�洢����ӿ�
class StorageObjectInterface
{
public:
	StorageObjectInterface(){};
	~StorageObjectInterface(){};
	//��ʼ���洢����
	virtual BOOL init(tstring & szFilePath,CharacterType nType=Ansi)
	{
		return TRUE;
	}

	//��������ݽӿ� �õ�ָ����ַ��int������
	virtual BOOL GetObjectVal(IN SerializeRunData * Addr,IN OUT void * pOutData,IN OUT unsigned int & nLen/*IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap*/)
	{
		return FALSE;
	}
	//���д���ݽӿ� ����int�����ݵ�ָ����ַ
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

	//˳��ѹ������ int��
	//template<typename ValType>
	virtual BOOL PushDataVal(IN void * pInData,IN OUT unsigned int & nLen)
	{
		return FALSE;
	}
	//˳��ѹ������ �ַ�����
	virtual BOOL PushDataString(IN LPTSTR pInData,IN OUT unsigned int & nLen)
	{
		return FALSE;
	}

	//˳��ѹ������ ��������
	virtual BOOL PushDataBinary(IN void * pInData,IN OUT unsigned int & nLen)
	{
		return FALSE;
	}

	//���õ�ǰ�ڵ�����
	//˳�򱣴�ڵ㿪ʼ
	virtual BOOL PushNodeCtlBegin(TCHAR * szFieldType,SerializeRunData * CurFieldAddr)
	{
		return FALSE;
	}
	//˳�򱣴�ڵ����
	virtual BOOL PushNodeCtlEnd(TCHAR * szFieldType,SerializeRunData * CurFieldAddr)
	{
		return FALSE;
	}

	//˳�����ؼ���
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
	
	//����˳�����ʱ�������л��ӿ�

	//���ն������õ�һ���洢�ڵ�
	virtual BOOL GetObjectMap(IN OUT vector<SerializeObjectInterface *> & ObjectInterfaceMap)
	{
		return FALSE;
	};

	//�ڵ�ǰ�ڵ���ҿ����ӽڵ�
	virtual BOOL LoadGetCurSerializeObject(FieldAddr & CurFieldAddr, SerializeLoadSaveInterface * * RetObj)
	{
		return FALSE;
	};
	//���ýڵ�����
	virtual BOOL LoadSetData(tstring & Data)
	{
		return FALSE;
	};

	//��ǰ�ڵ��ӽڵ�Load����
	virtual BOOL LoadCurObjectEnd(SerializeLoadSaveInterface * ChildObj)
	{
		return FALSE;
	};


	//��ǰ�ڵ�Load��ʼ
	virtual BOOL LoadObjectBegin(SerializeLoadSaveInterface * Obj)
	{
		return FALSE;
	};

	//��ǰ�ڵ�Load����
	virtual BOOL LoadObjectEnd(SerializeLoadSaveInterface * Obj)
	{
		return FALSE;
	};

	//����˳�򱣴浽���л�����ӿ�
	virtual BOOL Save(StorageObjectInterface * pStorageObject)
	{
		return pStorageObject->LoadObject(this);
	}

	//����˳�򱣴浽���л�����ӿ�
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
