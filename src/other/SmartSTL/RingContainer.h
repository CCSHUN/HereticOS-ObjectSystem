#pragma once
//************************************************************************ 
// ��˾: 2012-2015, DM. Co., Ltd.
// �ļ���: RingContainer.h
// ����: Ҷ���� 
// �汾: 1.0 
// ����: 2016/01/30
// ��������: ����������������ȷ�������Ķ�����pushend popbegin,Ӧ����fifo io�ĳ���
// ������ע:
// ά����ʷ:
//************************************************************************ 
//#include "MetaProgram.h"
//__declspec(align(64))

template<typename ObjectT,unsigned int nCount>
class __declspec(align(64)) RingContainer
{
public:
	enum RingState
	{
		RingState_Non = 0,
		RingState_Ready=1,
		RingState_Pending = 2,
		RingState_Complate=3
	};

	struct RingObject
	{
		volatile RingState		ringstate;
		volatile ObjectT		m_Object;
		volatile RingObject *	m_pNextObject;
	};
	volatile RingObject m_ObjectArray[nCount];
	volatile RingObject * m_ReadyBeginPos;
	volatile RingObject * m_ReadyEndPos;
	volatile RingObject * m_PendingBegin;
	volatile LONG m_nComplateCount;
	volatile LONG m_nSubmitCount;
	volatile LONG m_nReadyCount;
	volatile LONG m_nErrorCount;
	volatile LONG m_nErrorCount1;
	volatile LONG m_nErrorCount2;
	volatile UINT m_nLastError;

	void init()
	{
		for (unsigned int i = 0; i < nCount; i++)
		{
			m_ObjectArray[i].ringstate = RingState_Complate;
			if (i == (nCount - 1))
			{
				m_ObjectArray[i].m_pNextObject = &m_ObjectArray[0];
				break;
			}
			m_ObjectArray[i].m_pNextObject = &m_ObjectArray[i+1];
		}
		m_PendingBegin=m_ReadyBeginPos= m_ReadyEndPos= &m_ObjectArray[0];
		
		
	}
	
	RingObject * ReadyObject()
	{
		RingObject * pRetObject;
		if (m_ReadyEndPos->ringstate != RingState_Complate)
		{
			return NULL;
		}
		pRetObject = (RingObject *)InterlockedExchangePointer((volatile PVOID *)&m_ReadyEndPos, (PVOID)m_ReadyEndPos->m_pNextObject);
		InterlockedExchange((volatile LONG *)&pRetObject->ringstate, RingState_Ready);
		InterlockedIncrement(&m_nReadyCount);
		return pRetObject;
	}

	//�������NULL��û�л����ܹ������������
	RingObject * ReadyObject(ObjectT & object)
	{
		RingObject * pRetObject = ReadyObject();
		if (pRetObject)
		{
			pRetObject->m_Object = object;
		}
		return pRetObject;
	}

	//�Ӿ�������ȡ��һ��������FIFO�Ķ����������NULL��û�о������¶���
	RingObject * GetReadyObject()
	{
		RingObject * pRetObject;
		if (m_ReadyBeginPos->ringstate != RingState_Ready)
		{
			return NULL;
		}
		//InterlockedExchange(&m_ReadyBeginPos->ringstate, RingState_Ready);
		pRetObject=(RingObject *)InterlockedExchangePointer((volatile PVOID *)&m_ReadyBeginPos, (PVOID)m_ReadyBeginPos->m_pNextObject);
		
		//if (m_PendingBegin == NULL) m_PendingBegin = pRetObject;
		
		return pRetObject;
	}
	void PendingObject(RingObject * pObject)
	{
		InterlockedExchange((volatile LONG *)&pObject->ringstate, RingState_Pending);
		InterlockedIncrement(&m_nSubmitCount);
	}
	RingObject * GetFirstPendingObject()
	{
		return (RingObject *)(m_PendingBegin->ringstate== RingState_Pending? m_PendingBegin:NULL);
	}
	RingObject * ComplateFirstPendingObject(unsigned int nComplateCount)
	{
		InterlockedExchange((volatile LONG*)&m_PendingBegin->ringstate, RingState_Complate);
		RingObject * pRetObject = (RingObject *)InterlockedExchangePointer((volatile PVOID *)&m_PendingBegin, (PVOID)m_PendingBegin->m_pNextObject);
		//InterlockedAdd(&m_nComplateCount, nComplateCount);
		InterlockedIncrement(&m_nComplateCount);
		return pRetObject;
	}
	void ComplateEndObject()
	{
		InterlockedExchange((volatile LONG*)&m_ReadyBeginPos->ringstate, RingState_Complate);
		InterlockedIncrement(&m_nComplateCount);
		//InterlockedDecrement(&m_nReadyCount);
		//InterlockedDecrement(&m_nSubmitCount);
	}
	void Error(int nErr=1)
	{
		InterlockedAdd(&m_nErrorCount, nErr);
	}
	void Error1(int nErr = 1)
	{
		InterlockedAdd(&m_nErrorCount1, nErr);
	}
	void Error2(int nErr = 1)
	{
		InterlockedAdd(&m_nErrorCount2, nErr);
	}
	void SetLastError(UINT nError)
	{
		m_nLastError = nError;
	}
	//���һ������ʹ���ܽ��ܾ�������
	void ComplateObject(RingObject * object)
	{
		InterlockedExchange((volatile LONG*)&object->ringstate, RingState_Complate);
		InterlockedIncrement(&m_nComplateCount);
		//InterlockedDecrement(&m_nReadyCount);
		//InterlockedDecrement(&m_nSubmitCount);
	}

	RingContainer(){
		m_nSubmitCount = m_nReadyCount = m_nComplateCount = m_nErrorCount = m_nErrorCount1 = m_nErrorCount2 = 0;

		init();
	};
	~RingContainer(){};
protected:
	
private:
};

