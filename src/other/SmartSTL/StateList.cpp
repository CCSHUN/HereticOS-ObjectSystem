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


//StateList.cpp
#include "StateList.h"
/*
template<typename _Node, unsigned int nStateCount, int nPrefetchCountLog2, int nPrefetchCountCrcLog2>
TransferListNoHead< _Node, nStateCount, nPrefetchCountLog2, nPrefetchCountCrcLog2>::TransferListNoHead() {
	memset(&m_NodeArray, 0, sizeof(m_NodeArray));
	printf("TransferListNoHeadTransferListNoHeadTransferListNoHeadTransferListNoHeadTransferListNoHeadTransferListNoHeadTransferListNoHeadTransferListNoHeadTransferListNoHeadTransferListNoHeadTransferListNoHeadTransferListNoHead");
#ifdef USING_QUEUE_MODE
	memset(&m_NodeArrayEnd, 0, sizeof(m_NodeArrayEnd));
	for (int i = 0; i<nStateCount; i++)
	{
		m_NodeArray[i].pPrev = (_Node*)&m_NodeArrayEnd[i];
		m_NodeArrayEnd[i].pNext = (_Node*)&m_NodeArray[i];
	}
#endif 
	//memset(&m_PrefetchNode, 0, sizeof(m_PrefetchNode));
	//memset(&m_PrefetchNodeCount, 0, sizeof(m_PrefetchNodeCount));
	//memset(&m_PrefetchNodeCycCount, 0, sizeof(m_PrefetchNodeCount));
};

template<typename _Node, unsigned int nStateCount, int nPrefetchCountLog2, int nPrefetchCountCrcLog2>
TransferListNoHead< _Node, nStateCount, nPrefetchCountLog2, nPrefetchCountCrcLog2>::TransferListNoHead(_Myt & src)
{
	printf("TransferListNoHeadTransferListNoHeadTransferListNoHeadTransferListNoHeadTransferListNoHeadTransferListNoHeadTransferListNoHeadTransferListNoHeadTransferListNoHeadTransferListNoHeadTransferListNoHeadTransferListNoHead");
	memcpy(&m_NodeArray[0], &src.m_NodeArray[0], sizeof(m_NodeArray));
#ifdef USING_QUEUE_MODE
	
	memcpy(&m_NodeArrayEnd[0], &src.m_NodeArrayEnd[0], sizeof(m_NodeArray));
	for (int i = 0; i<nStateCount; i++)
	{
		m_NodeArray[i].pPrev->pNext = (_Node*)&m_NodeArray[i];
		m_NodeArrayEnd[i].pNext->pPrev = (_Node*)&m_NodeArrayEnd[i];
	}
#endif 
};
*/
template<typename _Node, unsigned int nStateCount, int nPrefetchCountLog2, int nPrefetchCountCrcLog2>
void TransferListNoHead< _Node, nStateCount, nPrefetchCountLog2, nPrefetchCountCrcLog2>::DelNode(_Node * pNode)
{
	//用全
	//Error(_T("DelNode pNode=%x,nState=%x  pNext=%x pPrev=%x Head=%x &Head=%x "), pNode, pNode->nState, pNode->pNext, pNode->pPrev, m_NodeArray[pNode->nState], m_NodeArray);
	//if (likely(pNode->pNext))
	{
		pNode->pNext->pPrev = pNode->pPrev;
	}

	//if (unlikely(pNode->pPrev))
	{
		pNode->pPrev->pNext = pNode->pNext;
	}


	//Error(_T("DelNode1 pNode=%x,nState=%x  pNext=%x pPrev=%x Head=%x &Head=%x "), pNode, pNode->nState, pNode->pNext, pNode->pPrev, m_NodeArray[pNode->nState], m_NodeArray);
};

template<typename _Node, unsigned int nStateCount, int nPrefetchCountLog2, int nPrefetchCountCrcLog2>
void TransferListNoHead< _Node, nStateCount, nPrefetchCountLog2, nPrefetchCountCrcLog2>::DelNode_Static(_Node * pNode)
{
	//用全
	//Error(_T("DelNode pNode=%x,nState=%x  pNext=%x pPrev=%x Head=%x &Head=%x "), pNode, pNode->nState, pNode->pNext, pNode->pPrev, m_NodeArray[pNode->nState], m_NodeArray);
	//if (likely(pNode->pNext))
	{
		pNode->pNext->pPrev = pNode->pPrev;
	}

	//if (unlikely(pNode->pPrev))
	{
		pNode->pPrev->pNext = pNode->pNext;
	}


	//Error(_T("DelNode1 pNode=%x,nState=%x  pNext=%x pPrev=%x Head=%x &Head=%x "), pNode, pNode->nState, pNode->pNext, pNode->pPrev, m_NodeArray[pNode->nState], m_NodeArray);
};

template<typename _Node, unsigned int nStateCount, int nPrefetchCountLog2, int nPrefetchCountCrcLog2>
void TransferListNoHead< _Node, nStateCount, nPrefetchCountLog2, nPrefetchCountCrcLog2>::AddNode(unsigned int nState, _Node * pNode)
{
	//Error(_T("AddNode pNode=%x,nState=%x to %x pNext=%x pPrev=%x Head=%x &Head=%x "), pNode, pNode->nState, nState, pNode->pNext, pNode->pPrev, m_NodeArray[pNode->nState], m_NodeArray);


	pNode->pNext = (_Node*)&m_NodeArray[nState];
	pNode->pPrev = m_NodeArray[nState].pPrev;
	m_NodeArray[nState].pPrev = (_Node *)pNode;

	pNode->pPrev->pNext = pNode;
	//Error(_T("AddNode1 pNode=%x,nState=%x to %x pNext=%x pPrev=%x Head=%x &Head=%x "), pNode, pNode->nState, nState, pNode->pNext, pNode->pPrev, m_NodeArray[pNode->nState], m_NodeArray);
};

template<typename _Node, unsigned int nStateCount, int nPrefetchCountLog2, int nPrefetchCountCrcLog2>
void TransferListNoHead< _Node, nStateCount, nPrefetchCountLog2, nPrefetchCountCrcLog2>::MoveNodeToStateList(_Node * pNode, unsigned int nState)
{
	DelNode(pNode);
	AddNode(nState, pNode);

};
/*
template<typename _Node, unsigned int nStateCount, int nPrefetchCountLog2, int nPrefetchCountCrcLog2>
bool TransferListNoHead< _Node, nStateCount, nPrefetchCountLog2, nPrefetchCountCrcLog2>::IsNull(unsigned int nState)
{
	return (m_NodeArray[nState]->pPrev == (_Node*)&m_NodeArrayEnd[nState]) ? true : false;
};
template<typename _Node, unsigned int nStateCount, int nPrefetchCountLog2, int nPrefetchCountCrcLog2>
bool TransferListNoHead< _Node, nStateCount, nPrefetchCountLog2, nPrefetchCountCrcLog2>::IsNull()
{
	return m_bNullConstruct;
};

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
template<typename _Node, unsigned int nStateCount, int nPrefetchCountLog2, int nPrefetchCountCrcLog2>
_Node* TransferListNoHead< _Node, nStateCount, nPrefetchCountLog2, nPrefetchCountCrcLog2>::GetNode(unsigned int nState)
{

#ifdef USING_QUEUE_MODE
	_Node * pNode = m_NodeArrayEnd[nState].pNext;
	if (likely(m_NodeArrayEnd[nState].pNext != (_Node*)&m_NodeArray[nState]))
	{
		//DelNode(pNode);
		//pNode->pNext->pPrev = pNode->pPrev;
		//pNode->pPrev->pNext = pNode->pNext;
		//
		//prefetch0(pNode);

		m_NodeArrayEnd[nState].pNext = pNode->pNext;
		m_NodeArrayEnd[nState].pNext->pPrev = (_Node*)&m_NodeArrayEnd[nState];
		
		//if (unlikely(pNode->pNext == (_Node*)&m_NodeArray[nState]))
		//{
		//	m_NodeArray[nState].pPrev = (_Node*)&m_NodeArrayEnd[nState];
		//}
		//else
		//{
			//prefetch_static(m_NodeArrayEnd[nState].pNext);
			//prefetch_static(m_NodeArrayEnd[nState].pNext->pNext);
		//}
		
		return pNode;
	}

#else
	_Node * pNode = m_NodeArray[nState].pPrev;
	if (likely(m_NodeArray[nState].pPrev != (_Node*)&m_NodeArrayEnd[nState]))
	{
		m_NodeArray[nState]->pPrev = pNode->pPrev;
		m_NodeArray[nState]->pPrev->pNext = (_Node*)&m_NodeArray[nState];
		if (unlikely(pNode->pPrev == (_Node*)&m_NodeArrayEnd[nState]))
		{
			m_NodeArrayEnd[nState].pNext = (_Node*)&m_NodeArray[nState];
		}
		return pNode;
	}
#endif
	
	return NULL;
};