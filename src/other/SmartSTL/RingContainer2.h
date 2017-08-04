#pragma once
//************************************************************************ 
// ¹«Ë¾: 2012-2015, DM. Co., Ltd.
// ÎÄ¼þÃû: RingContainer.h
// ×÷Õß: Ò¶Ê÷Éî 
// °æ±¾: 1.0 
// ÈÕÆÚ: 2016/01/30
// ¹¦ÄÜÃèÊö: »·ÐÎÈÝÆ÷£¬ÓÃÓÚÔÚÈ·¶¨ÊýÁ¿µÄ¶ÔÏóÖÐpushend popbegin,Ó¦ÓÃÓÚfifo ioµÄ³¡¾°
// ÆäËû±¸×¢:
// Î¬»¤ÀúÊ·:
//************************************************************************ 
#include "MetaProgram.h"
//__declspec(align(64))
//#include "MetaProgram.h"
//#define KernlMode
enum RingState
{
	//RingState_Non = 0,
	RingState_Ready = 0,
	RingState_Complate = 1,
	RingState_Pending = 2

};


struct CACHE_ALIGN_HEAD _tagTransformTable
{
	RingState src;
	RingState dst;
}CACHE_ALIGN_END;

static _tagTransformTable gTransformTable[] = {
	//{ RingState_Non ,RingState_Non },
	{ RingState_Ready ,RingState_Pending },
	{ RingState_Complate ,RingState_Ready },
	{ RingState_Pending,RingState_Complate  }
	
	
};


template<typename ObjectT,unsigned int nCountMask,unsigned int nStateCount>
class CACHE_ALIGN_HEAD RingContainer
{
public:
	
	struct CACHE_ALIGN_HEAD RingObject
	{
		volatile RingState		ringstate;
		volatile ObjectT		m_pObject;
	}CACHE_ALIGN_END;

	struct CACHE_ALIGN_HEAD StateContext
	{
		volatile ObjectT	 m_pReserveHead;
		volatile LONGLONG m_RingHead;
		volatile LONGLONG m_nOpCount;
	}CACHE_ALIGN_END;

	volatile StateContext  m_StateArray[nStateCount];
	volatile RingObject m_ObjectArray[nCountMask + 1];
#ifndef _LINUX_
	KSPIN_LOCK m_QueueLock;
#endif

	volatile LONGLONG m_nErrorCount;
	volatile LONGLONG m_nErrorCount1;
	volatile LONGLONG m_nErrorCount2;
	volatile LONGLONG m_nSendMiss;
	volatile UINT m_nLastError;
	volatile UINT m_nLastComplate;
	//ULONGLONG m_nCountMask;
	_tagTransformTable * m_TransformTable;

	void ErrorLog(int nErr = 1)
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


	void init(_tagTransformTable * pTransformTable = gTransformTable)
	{
		m_TransformTable = pTransformTable;
		for (unsigned int i = 0; i < (nCountMask + 1); i++)
		{
			
			m_ObjectArray[i].ringstate = m_TransformTable[((i*nStateCount) / ((nCountMask + 1)))].src;
			*(ObjectT*)&m_ObjectArray[i].m_pObject = ObjectT();
			m_StateArray[(m_ObjectArray[i].ringstate + 1) % nStateCount].m_RingHead = (i+1)&nCountMask;
		}
		for (int s=0;s<nStateCount;s++)
		{
			*(ObjectT*)&m_StateArray[s].m_pReserveHead = ObjectT();
			
			m_StateArray[s].m_nOpCount = 0;
		}
		
		m_nLastComplate=m_nSendMiss=m_nErrorCount = m_nErrorCount1 = m_nErrorCount2 = 0;
#ifdef KernlMode
		KeInitializeSpinLock(&m_QueueLock);
#else
#endif

	}
	RingObject & operator [] (RingState state)
	{
		RingObject * pRetObject = NULL;
		pRetObject = (RingObject *)&m_ObjectArray[m_StateArray[state].m_RingHead&nCountMask];
			
		return *pRetObject;
	}
	RingObject * Get(RingState state)
	{
		RingObject * pRetObject = NULL;
		if (m_ObjectArray[m_StateArray[state].m_RingHead&nCountMask].ringstate == state)
		{
			//pRetObject = (RingObject *)&m_ObjectArray[InterlockedExchangeAdd64(&m_StateArray[state].m_RingHead, 1)&nCountMask];
			pRetObject = (RingObject *)&m_ObjectArray[m_StateArray[state].m_RingHead&nCountMask];
			m_StateArray[state].m_RingHead++;
		}
		return pRetObject;
	}

	void Complate(RingObject * pObject)
	{
		pObject->ringstate = m_TransformTable[pObject->ringstate].dst;
		m_StateArray[pObject->ringstate].m_nOpCount++;
		//InterlockedExchange((volatile LONG*)&pObject->ringstate, m_TransformTable[pObject->ringstate].dst);
		//InterlockedIncrement64(&m_StateArray[pObject->ringstate].m_nOpCount);
	}

	RingObject * TryDo(RingState state, const ObjectT & object)
	{
		RingObject * pObject = Get(state);
		if (pObject)
		{
			pObject->m_pObject = object;
			Complate(pObject);
		}
		return pObject;
	}
	RingObject * TryDo(RingState state)
	{
		RingObject * pObject = Get(state);
		if (pObject)
		{
			Complate(pObject);
		}
		return pObject;
	}
	

	RingObject * Do(RingState state, ObjectT & object, ObjectT * pReserveObject)
	{
		RingObject * pObject = TryDo(state, object);
		if(pObject==NULL)
		{
			//KIRQL oldirql;
			//KeAcquireSpinLock(&m_QueueLock, &oldirql);
			*pReserveObject = m_StateArray[state].m_pReserveHead;
			m_StateArray[state].m_pReserveHead = object;
			//KeReleaseSpinLock(&m_QueueLock, oldirql);
		}
		return pObject;
	}

	
	template<typename NextObjectFunction>
	void FixReserve(RingState state, NextObjectFunction NextObjectFunc)
	{
		//KIRQL oldirql;
		if (m_StateArray[state].m_pReserveHead)
		{
			RingObject * pCanUsedObject = Get(state);
			if (pCanUsedObject)
			{
				//KeAcquireSpinLock(&m_QueueLock, &oldirql);
				for (; pCanUsedObject;)
				{
					if (m_StateArray[state].m_pReserveHead == NULL)
					{
						pCanUsedObject->m_pObject = NULL;
						Complate(pCanUsedObject);
						break;
					}
					Error2();
					ObjectT pObject = NextObjectFunc(m_StateArray[state].m_pReserveHead);
					pCanUsedObject->m_pObject = m_StateArray[state].m_pReserveHead;
					m_StateArray[state].m_pReserveHead = pObject;
					Complate(pCanUsedObject);
					pCanUsedObject = Get(state);
				}
				//KeReleaseSpinLock(&m_QueueLock, oldirql);
			}
		}
		
		
	}
	

	RingContainer(){
		m_nErrorCount = m_nErrorCount1 = m_nErrorCount2 = 0;

		init();
	};
	~RingContainer(){};
protected:
	
private:
}CACHE_ALIGN_END;

