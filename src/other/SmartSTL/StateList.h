#pragma once

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
//************************************************************************ 
// 文件名: StateList.h
// 作者: 叶树深 
// 版本: 1.0 
// 日期: 2015/11/16
// 功能描述: 
// 其他备注:
// 维护历史:
//************************************************************************ 

#define _CONSTEXP_


#include "MetaProgram.h"



#ifndef _LINUX_
//状态列表
template<typename _Node,unsigned int nStateCount>
class TransferListSafe
{
public:
	struct _NodeBase  
	{ 
		unsigned int nState;
		_Node * pNext;
		_Node * pPrev;
	};
	volatile _Node * m_NodeArray[nStateCount];
#ifdef USING_QUEUE_MODE
	volatile _Node * m_NodeArrayEnd[nStateCount];
#endif 
	TransferListSafe(){
		memset(&m_NodeArray, 0, sizeof(m_NodeArray));
#ifdef USING_QUEUE_MODE
		memset(&m_NodeArrayEnd, 0, sizeof(m_NodeArrayEnd));
#endif 
	};
	~TransferListSafe(){};


	
public:
	inline void DelNode(volatile _Node * pNode)
	{
		//脱链
		if (pNode->pNext)
		{
			InterlockedExchangePointer((PVOID*)&pNode->pNext->pPrev, (PVOID)pNode->pPrev);
		}

		if (pNode->pPrev)
		{
			InterlockedExchangePointer((PVOID*)&pNode->pPrev->pNext, (PVOID)pNode->pNext);
		}

		//设置当前运行链表
		if (m_NodeArray[pNode->nState] == pNode)
		{
			(pNode->pNext == NULL) ? InterlockedExchangePointer((PVOID*)&m_NodeArray[pNode->nState], (PVOID)pNode->pPrev) : InterlockedExchangePointer((PVOID*)&m_NodeArray[pNode->nState], (PVOID)pNode->pNext);
		}

		

#ifdef USING_QUEUE_MODE
		if (m_NodeArrayEnd[pNode->nState] == pNode)
		{
			//(pNode->pPrev == NULL) ? m_NodeArrayEnd[pNode->nState] = pNode->pNext : m_NodeArray[pNode->nState] = pNode->pPrev;
			(pNode->pPrev == NULL) ? InterlockedExchangePointer((PVOID*)&m_NodeArrayEnd[pNode->nState], (PVOID)pNode->pNext) : InterlockedExchangePointer((PVOID*)&m_NodeArrayEnd[pNode->nState], (PVOID)pNode->pPrev);
		}
#endif 
	}

	inline void AddNode(volatile unsigned int nState, volatile _Node * pNode)
	{
		InterlockedExchange(&pNode->nState, nState);

		if (m_NodeArray[nState]){
			InterlockedExchangePointer((PVOID*)&pNode->pNext, NULL);
			InterlockedExchangePointer((PVOID*)&pNode->pPrev, (PVOID)m_NodeArray[nState]);
			InterlockedExchangePointer((PVOID*)&(m_NodeArray[nState]->pNext), (PVOID)pNode);
			InterlockedExchangePointer((PVOID*)&m_NodeArray[nState], (PVOID)pNode);
		}
		else
		{
			InterlockedExchangePointer((PVOID*)&m_NodeArray[nState], (PVOID)pNode);
			InterlockedExchangePointer((PVOID*)&(m_NodeArray[nState]->pNext), NULL);
			InterlockedExchangePointer((PVOID*)&(m_NodeArray[nState]->pPrev), NULL);
		}
	}

	inline void MoveNodeToStateList(volatile _Node * pNode, volatile unsigned int nState)
	{
		DelNode(pNode);
		AddNode(nState, pNode);
	}
	bool IsNull(volatile unsigned int nState)
	{
		return (m_NodeArray[nState]) == NULL ? true : false;
	}
	volatile _Node * GetNode(volatile unsigned int nState)
	{
#ifdef USING_QUEUE_MODE
		volatile _Node * pNode = m_NodeArrayEnd[nState];
#else
		volatile _Node * pNode = m_NodeArray[nState];
#endif
		if(pNode) DelNode(pNode);
		return  pNode;
	}

protected:
	

};
#endif

template<typename _Node>
class _NodeList
{
public:
	_NodeList(){ pNext = NULL; pPrev = NULL; }
	~_NodeList(){ }

	_Node * pNext;
	_Node * pPrev;

	/*
	
	inline void DelNode(volatile _Node * pNode)
	{
		//脱链
		if (pNode->pNext)
		{
			pNode->pNext->pPrev = pNode->pPrev;
		}

		if (pNode->pPrev)
		{
			pNode->pPrev->pNext = pNode->pNext;
		}
	}

	static void AddNode(volatile _Node * pDstNode, volatile _Node * pNode)
	{
		//pNode->nState = nState;
		//pNode->pNext = NULL;
		pNode->pPrev = (_Node *)pDstNode;
		pDstNode->pNext = (_Node *)pNode;
		pDstNode->pPrev = NULL;
	}

	

	inline void DelNode()
	{
		//脱链
		if (pNext)
		{
			pNext->pPrev = pPrev;
		}

		if (pPrev)
		{
			pPrev->pNext = pNext;
		}
	}

	*/

};

//#define USING_QUEUE_MODE 1

template<typename _Node, unsigned int nStateCount,int nPrefetchCountLog2=6, int nPrefetchCountCrcLog2=4>
class TransferList
{
public:
	struct _NodeBase :public _NodeList<_Node>
	{
#ifdef STATELIST_UNUSING_STATE

#else
		unsigned int nState;
#endif
	};

	_Node * m_NodeArray[nStateCount];

#ifdef USING_QUEUE_MODE
	_Node * m_NodeArrayEnd[nStateCount];
#endif 
	_Node * m_PrefetchNode[nStateCount];
	unsigned int m_PrefetchNodeCount[nStateCount];
	unsigned int m_PrefetchNodeCycCount[nStateCount];
	TransferList(){
		memset(&m_NodeArray, 0, sizeof(m_NodeArray));
#ifdef USING_QUEUE_MODE
		memset(&m_NodeArrayEnd, 0, sizeof(m_NodeArrayEnd));
#endif 
		memset(&m_PrefetchNode, 0, sizeof(m_PrefetchNode));
		memset(&m_PrefetchNodeCount, 0, sizeof(m_PrefetchNodeCount));
		memset(&m_PrefetchNodeCycCount, 0, sizeof(m_PrefetchNodeCount));
	};
	~TransferList(){};



public:
	_Node * operator[](unsigned int nIndex)
	{
		return (_Node *)m_NodeArray[nIndex];
	}
#ifndef STATELIST_UNUSING_STATE
	inline void DelNode(_Node * pNode)
	{
		//脱链
		//Error(_T("DelNode pNode=%x,nState=%x  pNext=%x pPrev=%x Head=%x &Head=%x "), pNode, pNode->nState, pNode->pNext, pNode->pPrev, m_NodeArray[pNode->nState], m_NodeArray);
		if (likely(pNode->pNext))
		{
			pNode->pNext->pPrev=pNode->pPrev;
		}

		if (likely(pNode->pPrev))
		{
			pNode->pPrev->pNext=pNode->pNext;
		}

		//设置当前运行链表
		if (unlikely(m_NodeArray[pNode->nState] == pNode))
		{
			m_NodeArray[pNode->nState] = pNode->pPrev;
			//(pNode->pNext == NULL) ? m_NodeArray[pNode->nState]=pNode->pPrev : m_NodeArray[pNode->nState]=pNode->pNext;
		}


#ifdef USING_QUEUE_MODE
		if (unlikely(m_NodeArrayEnd[pNode->nState] == pNode))
		{
			m_NodeArrayEnd[pNode->nState] = pNode->pNext;
			//(pNode->pPrev == NULL) ? m_NodeArrayEnd[pNode->nState] = pNode->pNext : m_NodeArrayEnd[pNode->nState] = pNode->pPrev;
		}
#endif 
		//Error(_T("DelNode1 pNode=%x,nState=%x  pNext=%x pPrev=%x Head=%x &Head=%x "), pNode, pNode->nState, pNode->pNext, pNode->pPrev, m_NodeArray[pNode->nState], m_NodeArray);
	}
#else

	inline void DelNode(_Node * pNode,unsigned int nState)
	{
		//脱链
		//Error(_T("DelNode pNode=%x,nState=%x  pNext=%x pPrev=%x Head=%x &Head=%x "), pNode, pNode->nState, pNode->pNext, pNode->pPrev, m_NodeArray[pNode->nState], m_NodeArray);
		if (likely(pNode->pNext))
		{
			pNode->pNext->pPrev = pNode->pPrev;
		}

		if (unlikely(pNode->pPrev))
		{
			pNode->pPrev->pNext = pNode->pNext;
		}

		//设置当前运行链表
		if (unlikely(m_NodeArray[nState] == pNode))
		{
			m_NodeArray[nState] = pNode->pPrev;
			//(pNode->pNext == NULL) ? m_NodeArray[pNode->nState]=pNode->pPrev : m_NodeArray[pNode->nState]=pNode->pNext;
		}


#ifdef USING_QUEUE_MODE
		if (unlikely(m_NodeArrayEnd[nState] == pNode))
		{
			m_NodeArrayEnd[nState] = pNode->pNext;
			//(pNode->pPrev == NULL) ? m_NodeArrayEnd[pNode->nState] = pNode->pNext : m_NodeArrayEnd[pNode->nState] = pNode->pPrev;
		}
#endif 
		//Error(_T("DelNode1 pNode=%x,nState=%x  pNext=%x pPrev=%x Head=%x &Head=%x "), pNode, pNode->nState, pNode->pNext, pNode->pPrev, m_NodeArray[pNode->nState], m_NodeArray);
	}
#endif

	inline void AddNode(unsigned int nState, _Node * pNode)
	{
		//Error(_T("AddNode pNode=%x,nState=%x to %x pNext=%x pPrev=%x Head=%x &Head=%x "), pNode, pNode->nState, nState, pNode->pNext, pNode->pPrev, m_NodeArray[pNode->nState], m_NodeArray);
#ifndef STATELIST_UNUSING_STATE
		pNode->nState = nState;
#endif // !STATELIST_UNUSING_STATE

		

		if (likely(m_NodeArray[nState])){
			pNode->pNext= NULL;
			pNode->pPrev = (_Node *)m_NodeArray[nState];
			m_NodeArray[nState]->pNext = (_Node *)pNode;
			m_NodeArray[nState]=pNode;
		}
		else
		{
			m_NodeArray[nState]=pNode;
			m_NodeArray[nState]->pNext=NULL;
			m_NodeArray[nState]->pPrev= NULL;

#ifdef USING_QUEUE_MODE
			m_NodeArrayEnd[nState] = pNode;
#endif

		}
		//Error(_T("AddNode1 pNode=%x,nState=%x to %x pNext=%x pPrev=%x Head=%x &Head=%x "), pNode, pNode->nState, nState, pNode->pNext, pNode->pPrev, m_NodeArray[pNode->nState], m_NodeArray);
	}

	inline void MoveNodeToStateList(_Node * pNode,unsigned int nState)
	{
		//Error(_T("Move pNode=%x,nState=%x to %x pNext=%x pPrev=%x"), pNode, pNode->nState, nState, pNode->pNext, pNode->pPrev);
#ifndef STATELIST_UNUSING_STATE
		DelNode(pNode);
#else
		DelNode(pNode, nState);
#endif 
		//Error(_T("Move pNode1=%x,nState=%x to %x pNext=%x pPrev=%x"), pNode, pNode->nState, nState, pNode->pNext, pNode->pPrev);
		AddNode(nState, pNode);


		//Error(_T("Move over pNode=%x,nState=%x to %x pNext=%x pPrev=%x"), pNode, pNode->nState, nState, pNode->pNext, pNode->pPrev);
	}
	bool IsNull(unsigned int nState)
	{
		return (m_NodeArray[nState]) == NULL ? true : false;
	}
	inline void PrefetchNode(unsigned int nState)
	{
		m_PrefetchNodeCycCount[nState]++;
		if (likely(m_PrefetchNode[nState]))
		{

		}
		if (unlikely((m_PrefetchNodeCycCount[nState] > TTL_CEXP::power(2, nPrefetchCountLog2))))
		{
			prefetch3(m_PrefetchNode[nState]);
		}
	}
	_Node * GetNode(unsigned int nState)
	{

#ifdef USING_QUEUE_MODE
		_Node * pNode = m_NodeArrayEnd[nState];
		if (likely(pNode)) {
			m_NodeArrayEnd[nState] = pNode->pNext;
			if (likely(pNode->pNext)) 
			{
				prefetch(pNode->pNext);
				pNode->pNext->pPrev = NULL;
			}
			else
			{
				m_NodeArray[nState] = NULL;
			}
			//PrefetchNode(nState);

		}
#else
		_Node * pNode = m_NodeArray[nState];
		
		if (likely(pNode))
		{
			m_NodeArray[nState] = pNode->pPrev;
			if (likely(pNode->pPrev))
			{
				prefetch(pNode->pPrev);
				pNode->pPrev->pNext = NULL;
			}
			PrefetchNode(nState);
		}
#endif
		
		
		return  pNode;
	}



protected:


};


template<typename _Node, unsigned int nStateCount, int nPrefetchCountLog2 = 6, int nPrefetchCountCrcLog2 = 4>
class TransferListNoHead
{
public:
	struct _NodeBase :public _NodeList<_Node>
	{

	};
	typedef TransferListNoHead<_Node, nStateCount, nPrefetchCountLog2, nPrefetchCountCrcLog2> _Myt;
	_NodeBase  m_NodeArray[nStateCount];

#ifdef USING_QUEUE_MODE
	_NodeBase  m_NodeArrayEnd[nStateCount];
#endif 
	//unsigned int m_PrefetchNodeCount[nStateCount];
	//unsigned int m_PrefetchNodeCycCount[nStateCount];
	void Init()
	{
		memset(&m_NodeArray, 0, sizeof(m_NodeArray));
		//printf("TransferListNoHeadTransferListNoHeadTransferListNoHeadTransferListNoHeadTransferListNoHeadTransferListNoHeadTransferListNoHeadTransferListNoHeadTransferListNoHeadTransferListNoHeadTransferListNoHeadTransferListNoHead");
#ifdef USING_QUEUE_MODE
		memset(&m_NodeArrayEnd, 0, sizeof(m_NodeArrayEnd));
		for (int i = 0; i<nStateCount; i++)
		{
			m_NodeArray[i].pPrev = (_Node*)&m_NodeArrayEnd[i];
			m_NodeArrayEnd[i].pNext = (_Node*)&m_NodeArray[i];
		}
#endif 
		//for (int _prefetch_object_pos = 0; _prefetch_object_pos < sizeof(m_NodeArray); _prefetch_object_pos += __CACHE_LINE__) { prefetch_static((void*)((((char *)(&m_NodeArray))) + _prefetch_object_pos)); };
		//prefetch_object(m_NodeArray, prefetch_static);
		//prefetch_object(m_NodeArrayEnd, prefetch_static);
	}
	bool m_bNullConstruct;
	TransferListNoHead() {
		m_bNullConstruct = false;
		Init();
		//memset(&m_PrefetchNode, 0, sizeof(m_PrefetchNode));
		//memset(&m_PrefetchNodeCount, 0, sizeof(m_PrefetchNodeCount));
		//memset(&m_PrefetchNodeCycCount, 0, sizeof(m_PrefetchNodeCount));
	};;
	bool IsNull(unsigned int nState) const 
	{
		return (m_NodeArray[nState]->pPrev == (_Node*)&m_NodeArrayEnd[nState]) ? true : false;
	};
	bool IsNull() const
	{
		return m_bNullConstruct;
	};
	void Clone(const _Myt & src)
	{
		if (src.IsNull())
		{
			Init();
		}
		else
		{
			memcpy(&m_NodeArray[0], &src.m_NodeArray[0], sizeof(m_NodeArray));
#ifdef USING_QUEUE_MODE

			memcpy(&m_NodeArrayEnd[0], &src.m_NodeArrayEnd[0], sizeof(m_NodeArray));
			for (int i = 0; i<nStateCount; i++)
			{
				m_NodeArray[i].pPrev->pNext = (_Node*)&m_NodeArray[i];
				m_NodeArrayEnd[i].pNext->pPrev = (_Node*)&m_NodeArrayEnd[i];
			}
#endif 
		}
		
	}
	TransferListNoHead(const _Myt & src) {
		//printf("TransferListNoHeadTransferListNoHeadTransferListNoHeadTransferListNoHeadTransferListNoHeadTransferListNoHeadTransferListNoHeadTransferListNoHeadTransferListNoHeadTransferListNoHeadTransferListNoHeadTransferListNoHead");
		Clone(src);
	};
	
	_Myt & operator =(const _Myt & src) {
		//printf("TransferListNoHeadTransferListNoHeadTransferListNoHeadTransferListNoHeadTransferListNoHeadTransferListNoHeadTransferListNoHeadTransferListNoHeadTransferListNoHeadTransferListNoHeadTransferListNoHeadTransferListNoHead");
		Clone(src);
		return *this;
	};
	
	
	~TransferListNoHead() {};

	

public:
	_Node * operator[](unsigned int nIndex)
	{
		return (_Node *)m_NodeArray[nIndex].pPrev;
	};


	inline void DelNode( _Node * pNode);
	static void DelNode_Static(_Node * pNode);
	inline void AddNode(unsigned int nState, _Node * pNode);

	inline void MoveNodeToStateList(_Node * pNode, unsigned int nState);
	
	/*
	inline void PrefetchNode(unsigned int nState)
	{
		m_PrefetchNodeCycCount[nState]++;
		if (likely(m_PrefetchNode[nState]))
		{

		}
		if (unlikely((m_PrefetchNodeCycCount[nState] > TTL_CEXP::power(2, nPrefetchCountLog2))))
		{
			prefetch3(m_PrefetchNode[nState]);
		}
	}
	*/
	_Node * GetNode(unsigned int nState);



protected:


};

//#undef _CONSTEXP_