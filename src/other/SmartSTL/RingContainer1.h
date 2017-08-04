#pragma once
//************************************************************************ 
// 公司: 2012-2015, DM. Co., Ltd.
// 文件名: RingContainer.h
// 作者: 叶树深 
// 版本: 1.0 
// 日期: 2016/01/30
// 功能描述: 环形容器，用于在确定数量的对象中pushend popbegin,应用于fifo io的场景
// 其他备注:
// 维护历史:
//************************************************************************ 
//#include "MetaProgram.h"
//__declspec(align(64))
#include "MetaProgram.h"
template<typename ObjectT,unsigned int nCountMask>
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
	};
	volatile RingObject m_ObjectArray[nCountMask+1];
	volatile LONGLONG m_ReadyBeginPos;
	volatile LONGLONG m_ReadyEndPos;
	volatile LONGLONG m_PendingBegin;
	volatile LONGLONG m_nComplateCount;
	volatile LONGLONG m_nSubmitCount;
	volatile LONGLONG m_nReadyCount;
	volatile LONGLONG m_nErrorCount;
	volatile LONGLONG m_nErrorCount1;
	volatile LONGLONG m_nErrorCount2;
	volatile UINT m_nLastError;
	//ULONGLONG m_nCountMask;

	void init()
	{
		//ULONGLONG nCount = TTL::power<2, nCountMask>::nRet;
		for (unsigned int i = 0; i < nCountMask+1; i++)
		{
			m_ObjectArray[i].ringstate = RingState_Complate;
		}
		m_PendingBegin=m_ReadyBeginPos= m_ReadyEndPos= 0;
		
		
	}
	
	RingObject * ReadyObject()
	{
		RingObject * pRetObject;
		if (m_ObjectArray[m_ReadyEndPos&nCountMask].ringstate != RingState_Complate)
		{
			return NULL;
		}
		pRetObject =(RingObject *)&m_ObjectArray[InterlockedExchangeAdd64(&m_ReadyEndPos,1)&nCountMask];
		InterlockedExchange((volatile LONG *)&pRetObject->ringstate, RingState_Ready);
		InterlockedIncrement64(&m_nReadyCount);
		return pRetObject;
	}

	//如果返回NULL则，没有缓存能够就绪进入队列
	RingObject * ReadyObject(ObjectT & object)
	{
		RingObject * pRetObject = ReadyObject();
		if (pRetObject)
		{
			pRetObject->m_Object = object;
		}
		return pRetObject;
	}

	//从就绪队列取出一个就绪的FIFO的对象，如果返回NULL则没有就绪的新对象
	RingObject * GetReadyObject()
	{
		RingObject * pRetObject;
		if (m_ObjectArray[m_ReadyBeginPos&nCountMask].ringstate != RingState_Ready)
		{
			return NULL;
		}
		//InterlockedExchange(&m_ReadyBeginPos->ringstate, RingState_Ready);
		//pRetObject=(RingObject *)InterlockedExchangePointer((volatile PVOID *)&m_ReadyBeginPos, (PVOID)m_ReadyBeginPos->m_pNextObject);
		pRetObject = (RingObject *)&m_ObjectArray[InterlockedExchangeAdd64(&m_ReadyBeginPos, 1)&nCountMask];

		//if (m_PendingBegin == NULL) m_PendingBegin = pRetObject;
		
		return pRetObject;
	}
	void PendingObject(RingObject * pObject)
	{
		InterlockedExchange((volatile LONG *)&pObject->ringstate, RingState_Pending);
		InterlockedIncrement64(&m_nSubmitCount);
	}
	RingObject * GetFirstPendingObject()
	{
		return (RingObject *)(m_ObjectArray[m_PendingBegin&nCountMask].ringstate== RingState_Pending? &m_ObjectArray[m_PendingBegin&nCountMask] :NULL);
	}
	RingObject * ComplateFirstPendingObject(unsigned int nComplateCount)
	{
		InterlockedExchange((volatile LONG*)&m_ObjectArray[m_PendingBegin&nCountMask].ringstate, RingState_Complate);
		RingObject * pRetObject = (RingObject *)&m_ObjectArray[InterlockedExchangeAdd64(&m_PendingBegin, 1)&nCountMask];
		//RingObject * pRetObject = (RingObject *)InterlockedExchangePointer((volatile PVOID *)&m_PendingBegin, (PVOID)m_PendingBegin->m_pNextObject);
		//InterlockedAdd(&m_nComplateCount, nComplateCount);
		InterlockedIncrement64(&m_nComplateCount);
		return pRetObject;
	}
	void ComplateEndObject()
	{
		InterlockedExchange((volatile LONG*)&m_ObjectArray[m_ReadyBeginPos&nCountMask].ringstate, RingState_Complate);
		InterlockedIncrement64(&m_nComplateCount);
		//InterlockedDecrement(&m_nReadyCount);
		//InterlockedDecrement(&m_nSubmitCount);
	}
	void Error(int nErr=1)
	{
		InterlockedAdd64(&m_nErrorCount, nErr);
	}
	void Error1(int nErr = 1)
	{
		InterlockedAdd64(&m_nErrorCount1, nErr);
	}
	void Error2(int nErr = 1)
	{
		InterlockedAdd64(&m_nErrorCount2, nErr);
	}
	void SetLastError(UINT nError)
	{
		m_nLastError = nError;
	}
	//完成一个缓存使其能接受就绪对象
	void ComplateObject(RingObject * object)
	{
		InterlockedExchange((volatile LONG*)&object->ringstate, RingState_Complate);
		InterlockedIncrement64(&m_nComplateCount);
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

