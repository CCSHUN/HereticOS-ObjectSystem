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
#include "SystemContainer.h"
#include "tool.hpp"
//2005.4.16 �ڴ������
#include "yssmemory_os.hpp"
#include "StateList.h"

//#define printf_d printf
#define printf_d 

#define MEMMGR_TYPE_DEF			0
#define MEMMGR_TYPE_1			1
#define MEMMGR_TYPE_STATICGC	2
#define MEMMGR_TYPE_STATICGC_TMP	3
#define MEMMGR_TYPE_OS			4
#define MEMMGR_TYPE_OS_VM		5		
#define MEMMGR_TYPE_BITMAP			6
#define MEMMGR_TYPE_FREELIST		7

#define MEM_DBG
class MemPoolDbg
{
public:

	__int64 m_nAllocCount;
	__int64 m_nFreeCount;
	__int64 m_nAllocSize;
	__int64 m_nFreeSize;
	__int64 m_nCurAllocSize;
	__int64 m_nCurAllocCount;

	__int64 m_nGcAllocCount;
	__int64 m_nGcAllocSize;
	TCHAR szInfo[512];
	MemPoolDbg() {
		m_nAllocCount=m_nFreeCount=m_nAllocSize=m_nFreeSize=m_nCurAllocSize=m_nCurAllocCount=0;
	};
	~MemPoolDbg() {};
	void DbgNewMem(size_t nSize)
	{
		m_nAllocCount++;
		m_nCurAllocCount++;
		m_nCurAllocSize += nSize;
		m_nAllocSize += nSize;
	}
	void DbgDelMem(size_t nSize)
	{
		m_nFreeCount++;
		m_nCurAllocCount--;
		m_nCurAllocSize -= nSize;
		m_nFreeSize += nSize;
	}

	void DbgGcNewMem(size_t nSize)
	{
		m_nGcAllocCount++;
		m_nGcAllocSize += nSize;
	}
	void DbgGcDelMem(size_t nSize)
	{
		m_nGcAllocCount--;
		m_nGcAllocSize -= nSize;
	}

	TCHAR * PrintMemPoolInfo(TCHAR *szHead=_T("MemPool"))
	{
		sprintf_t(szInfo,_T("%s CurAlloc(%llu %lluKB) GcAlloc(%llu %lluKB) Alloc(%llu %lluKB)  Free(%llu %lluKB)\n"), szHead,
			m_nCurAllocCount, m_nCurAllocSize / 1024,
			m_nGcAllocCount, m_nGcAllocSize / 1024,
			m_nAllocCount, m_nAllocSize / 1024,
			m_nFreeCount, m_nFreeSize/1024);
		return &szInfo[0];
	}

private:

};




extern unsigned int g_hTlsForHeap;

//�����ڴ�������ָ�������ڴ涯̬�ض����������ڴ���䳡��
template<typename PointInterfaceT>
class MemoryMgr : public MemoryMgrInterface<PointInterfaceT>
{
public:
	//�ڴ�ͷβ��־
#define YSSFLAG_BEGIN 'SSEY'
#define YSSFLAG_END 'DNEY'

#define DEFMEMSIZE	 128*1024*4
#define TOTALBUFLEN(allocsize) ((allocsize)+sizeof(_tagMemHead)+sizeof(unsigned int))
	//��ȡ������ڴ��ַ
#define GetBufFromRealMem(pMemHead) ((__int64)(pMemHead)+sizeof(_tagMemHead))
	//��ȡ�ڴ����ṹ�ӷ����ڴ��ַ
#define GetRealMemFromBuf(buf) ((_tagMemHead *)(((__int64)buf)-sizeof(_tagMemHead)))

	//�������
#define GetPrevMem(pMem) ((_tagMemHead *)(((__int64)m_pMemBuf)+pMem->PrevOffset))
#define GetNextMem(pMem) ((_tagMemHead *)(((__int64)m_pMemBuf)+pMem->NextOffset))

	//��ȡ�ڴ�ƫ�Ƶ�ַ
#define GetPointOffset(pMem) (((__int64)pMem)-((__int64)m_pMemBuf))
	//ȡ������־
#define GetEndFlag_Mem(pMem) ((unsigned int *)((__int64)(pMem)+(pMem)->nLen-sizeof(unsigned int)))
#define GetEndFlag_Buf(pBuf) ((unsigned int *)((__int64)GetRealMemFromBuf(pBuf)+GetRealMemFromBuf(pBuf)->nLen-sizeof(unsigned int)))

	MemoryMgr()
	{

		//{0,0,0};
		//if(m_pMemBuf) YSS_DELETE_MEM(m_pMemBuf);
		NewGc();
	};

	~MemoryMgr(){};
	unsigned char * m_pMemBuf;

	//
	__int64 m_nLen;
	//�ѷ�������
	__int64 m_nTotalUsed;
	//�Ƿ�ϣ������
	//bool m_bHopeReArrange;

	__int64 m_nNewCount;

	//
	struct _tagMemHead
	{
		unsigned int nFlag;	//��ʼ��־
		typename PointInterfaceT::PointIndexType PrevOffset;//ǰһ���ڴ��ƫ��
		typename PointInterfaceT::PointIndexType NextOffset;//ǰһ���ڴ��ƫ��
		__int64 nLen;
	};

	_tagMemHead * m_pLastMem;	//���һ���ڴ�


	void * NewGc()
	{
		m_nLen=DEFMEMSIZE;
		m_pMemBuf=(unsigned char *)YSS_MALLC_MEM(m_nLen);
		m_pLastMem=(_tagMemHead*)m_pMemBuf;
		m_pLastMem->nFlag=0;
		m_pLastMem->nLen=0;
		m_pLastMem->PrevOffset=0;
		m_pLastMem->NextOffset=0;
		m_nNewCount=0;
		return this;
	}
	//�õ���ʵ��ַ
	void * MapGetAddr(IN PointInterfaceT * pMem)
	{
		return (void *)((__int64)m_pMemBuf+pMem->m_nIndex);
	}

	//������ָ��ת��Ϊ����ָ��
	bool GetVPFromRealAddr(IN OUT PointInterfaceT * pMem, IN void * pAddr)
	{
		pMem->m_nIndex=(__int64)pAddr-(__int64)m_pMemBuf;
		return true;
	}

	void * NewMemory(__int64 nLen) 
	{  
		return NewMem(nLen);
	};

	bool DelMemory(void * pMem, __int64 nLen) {
		DelMem((void *)pMem);
		m_nNewCount--;

		return false;
	}

	bool NewVirtualMemory(IN OUT PointInterfaceT & pMem, __int64  nLen)
	{
		char * pBuf=(char *)NewMem(nLen);
		pMem.m_nIndex=(__int64)pBuf-(__int64)m_pMemBuf;
		m_nNewCount++;
#ifdef _DBG
		YSS_ASSERT(m_nTotalUsed>GetPointOffset(m_pLastMem));
		YSS_ASSERT(GetPointOffset(m_pLastMem)>m_nLen);
		YSS_ASSERT(!CheckMem());
#endif
		//printf("NewMemory %d\r\n",pMem.m_nIndex);
		return pBuf==NULL? false : true;
	}

	bool DelVirtualMemory(PointInterfaceT & pMem)
	{
		void * pBuf=MapGetAddr(&pMem);
		//printf("addr=%08x\r\n",pBuf);
		//printf("DelMemory %d\r\n",pMem.m_nIndex);
#ifdef _DBG
		YSS_ASSERT(m_nTotalUsed>GetPointOffset(m_pLastMem));
		YSS_ASSERT(!CheckMem());
		//((_tagMemHead *)pBuf)->nFlag='leDY';

		//����ڴ����Ƿ�����

#endif

		DelMem((void *)pBuf);

		m_nNewCount--;
#ifdef _DBG
		
		YSS_ASSERT(m_nTotalUsed>GetPointOffset(m_pLastMem));
		YSS_ASSERT(GetPointOffset(m_pLastMem)>m_nLen);
		YSS_ASSERT(!CheckMem());
		((_tagMemHead *)pBuf)->nFlag='leDY';

		//����ڴ����Ƿ�����
		
#endif

		pMem.m_nIndex=-1;
		 
		return true;

	}
	bool TestInfo()
	{
		int nf=GetPointOffset(m_pLastMem);
		printf("m_nTotalUsed=%d m_nLen=%d endoffset=%d nBlockNum=%d \r\n",
			(int)m_nTotalUsed,(int)m_nLen,
			(int)nf,(int)m_nNewCount);
#ifdef _DBG
		YSS_ASSERT(m_nTotalUsed>GetPointOffset(m_pLastMem));
#endif
		/*_tagMemHead * pPos=(_tagMemHead *)m_pMemBuf;
		for(int i=1;pPos!=m_pLastMem;)
		{
			int nPos=GetPointOffset(pPos);
			printf("%d,%d,0x%08x\r\n",i,nPos,(unsigned int)pPos);
			pPos=GetNextMem(pPos);
			i++;
			if(i>32)
			{
				return false;
			}
		}*/
		return true;
	}
protected:

private:
	bool CheckMem()
	{
		_tagMemHead * pPos=m_pLastMem;
		int nTotal=0;
		for(;(void *)pPos!=(void *)m_pMemBuf;)
		{
			pPos=(_tagMemHead *)((__int64)m_pMemBuf+pPos->PrevOffset);
			if(pPos->nLen) nTotal++;
		}
		return nTotal==m_nNewCount?true:false;
	}
	//�ڴ�������
	bool ReArrange(__int64 nNeedSize)
	{
		__int64 nLastPos=GetPointOffset(m_pLastMem);
		__int64 nNewLen=m_nLen*2+nNeedSize+DEFMEMSIZE;
		unsigned char * pNewMem=(unsigned char *)YSS_MALLC_MEM(nNewLen);
		_tagMemHead * pPos=GetPrevMem(m_pLastMem);
		_tagMemHead * pPrevNewPos=(_tagMemHead *)pNewMem;
		printf("ReArrange m_nTotalUsed=%d m_nLen=%d to %d \r\n",m_nTotalUsed,m_nLen,nNewLen);
		memcpy(pNewMem,m_pMemBuf,m_nLen);

		m_pLastMem=(_tagMemHead *)(pNewMem+nLastPos);

		YSS_DELETE_MEM(m_pMemBuf);
		m_pMemBuf=pNewMem;
		m_nLen=nNewLen;
		return true;
	}

	//��ʼ���ڴ�
	bool InitMem(IN _tagMemHead * pMem,unsigned int nAllocLen)
	{
		pMem->nLen=TOTALBUFLEN(nAllocLen);
		pMem->nFlag=YSSFLAG_BEGIN;
		*(unsigned int *)((__int64)pMem+pMem->nLen-sizeof(unsigned int))=YSSFLAG_END;
		return true;
	}

	//��õ�ǰ�ڵ���ǰһ���ڵ�֮�����Ƭ�ߴ�
	__int64 GetCurMemLastScrapLen(IN _tagMemHead * pMem,OUT _tagMemHead ** pOutMem)
	{
		_tagMemHead* PrevPos=GetPrevMem(pMem);
		*pOutMem=(_tagMemHead*)((__int64)PrevPos+PrevPos->nLen);
		__int64 nRetLen=((__int64) pMem)-((__int64)PrevPos+PrevPos->nLen);
		return nRetLen;
	}
	//Ѱ�ҵ�ǰ�ڵ��ڴ�֮ǰ����Ҫ��Ŀ�϶�ռ�
	bool GetMemFromScrap(OUT _tagMemHead ** pMem,__int64 nAllocSize)
	{
		_tagMemHead * pPos=m_pLastMem;
		for(;(void *)pPos!=(void *)m_pMemBuf;)
		{
			_tagMemHead * pOutMem=NULL;
			if(GetCurMemLastScrapLen(pPos,&pOutMem)>=TOTALBUFLEN(nAllocSize))
			{
				*pMem=pOutMem;
				bool bRet=InitMem(*pMem,nAllocSize);
				_tagMemHead* PrevPos=GetPrevMem(pPos);
				//���뵽�ڴ�����
				PointInterfaceT::PointIndexType nPos = GetPointOffset(pPos);
				PointInterfaceT::PointIndexType nOut = GetPointOffset(pOutMem);
				PointInterfaceT::PointIndexType nPrevPos = GetPointOffset(PrevPos);

				
				pOutMem->PrevOffset=nPrevPos;
				pOutMem->NextOffset=nPos;
				pPos->PrevOffset=nOut;
				PrevPos->NextOffset=nOut;

				//�ܼ��ѷ���;
				m_nTotalUsed+=(*pMem)->nLen;

				return bRet;
			}
			pPos=(_tagMemHead *)((__int64)m_pMemBuf+pPos->PrevOffset);
		}
		return false;
	}
	//��ĩβ�����ڴ�
	bool GetMemFromLastMem(OUT _tagMemHead ** pMem,__int64 nAllocSize)
	{
		if(
			(m_nLen-(((__int64)m_pLastMem)-((__int64)m_pMemBuf)))
			>(TOTALBUFLEN(nAllocSize)*2)
			)
		{
			*pMem=m_pLastMem;
			bool bRet=InitMem(*pMem,nAllocSize);
			(*pMem)->NextOffset=GetPointOffset(m_pLastMem)+(*pMem)->nLen;

			//���뵽�ڴ�����
			_tagMemHead* NextPos=GetNextMem(m_pLastMem);
			

			NextPos->PrevOffset=GetPointOffset(m_pLastMem);
			NextPos->NextOffset=0;

			m_pLastMem=NextPos;
			m_nTotalUsed+=(*pMem)->nLen;
			return true;
		}

		return false;
	}
	void * NewMem(__int64 nLen)
	{
		_tagMemHead * pMem=0;
		bool bRet=false;
		if(nLen==196616)
		{
			printf("a");
		}
		//��poolĩβ�����ڴ�
		bRet=GetMemFromLastMem(&pMem,nLen);
		if(bRet==false)
		{
			//��pool�е���Ƭ�з����ڴ�
			bRet=GetMemFromScrap(&pMem,nLen);
			if(bRet==false)
			{
				//�����ڴ���Ƭ������ڴ棬���������pool��û�и�����ڴ棬�����ڴ�󿽱����µ�pool�ٷ���
				bRet=ReArrange(nLen);
				if(bRet)
				{
					//�ݹ����
					return NewMem(nLen);
				}
			}
		}

		if(bRet)
		{
			return (void *)GetBufFromRealMem(pMem);
		}else
		{
			YSS_ASSERT(1);
		}
		return 0;
	}

	bool DelMem(void * pBuf)
	{
		YSS_ASSERT(pBuf==NULL)
		_tagMemHead * pMem=GetRealMemFromBuf(pBuf);
		YSS_ASSERT(pMem->nFlag!=YSSFLAG_BEGIN)
		YSS_ASSERT(*GetEndFlag_Mem(pMem)!=YSSFLAG_END)
		/*if(pMem==GetPrevMem(m_pLastMem))
		{
			m_nTotalUsed-=pMem->nLen;
			_tagMemHead * pOld=pMem;
			//printf("enddel %08x-%d\r\n",(unsigned int)m_pLastMem,m_pLastMem->PrevOffset);
			m_pLastMem=GetPrevMem(m_pLastMem);
			//�����Ƿ���Ҫ����
			_tagMemHead * pPrev=GetPrevMem(m_pLastMem);//->NextOffset
			if(pPrev!=m_pLastMem)
			{
				typename PointInterface::PointIndexType nPrev=GetPointOffset(pPrev);
				if((GetPointOffset(m_pLastMem)-nPrev)>pPrev->nLen)
				{
					m_pLastMem=(_tagMemHead * )((BYTE*)pPrev+pPrev->nLen);
					m_pLastMem->PrevOffset=nPrev;
				}
			}
			m_pLastMem->NextOffset=0;

			pOld->nLen=0;/ *pOld->PrevOffset=0;* /pOld->nFlag='leDY';pOld->NextOffset=0;
			//printf("del pMem==m_pLastMem ");
			//TestInfo();
		}else*/
		{
			_tagMemHead * pOld=pMem;
			m_nTotalUsed-=pMem->nLen;

			_tagMemHead * pNext=GetNextMem(pMem);
			_tagMemHead * pPrev=GetPrevMem(pMem);
			//unsigned int nNextPos=GetPointOffset(pNext);
			unsigned int nPrvPos=GetPointOffset(pPrev);
			//printf("PrevOffset=%d NextPrevOffset=%d PrevMemPos=%d NextMemPos=%d %08x\r\n",pMem->PrevOffset,GetNextMem(pMem)->PrevOffset,
			//	nPrvPos,nNextPos,(unsigned int)pNext);

			//if(pPrev==pOld)
			//{
				//�׽ڵ�
				//ɾ�����ڵ�
				//pNext->PrevOffset=pMem->PrevOffset;//GetPointOffset(GetPrevMem(pMem));
				//pOld->nLen=0;pOld->PrevOffset=0;pOld->nFlag='leDY';pOld->NextOffset=0;
				//return true;
			//}
			if(pNext==m_pLastMem)
			{
				//����β�ڵ�
				//m_pLastMem=pMem;
				//GetNextMem(pMem)->PrevOffset=pMem->PrevOffset;//GetPointOffset(GetPrevMem(pMem));
				//����β����
				pOld->nLen=0;pOld->PrevOffset=0;pOld->nFlag='leDY';pOld->NextOffset=0;

				m_pLastMem=(_tagMemHead *)((BYTE*)pPrev+pPrev->nLen);//=GetPointOffset(pMem);

				m_pLastMem->PrevOffset=nPrvPos;
				m_pLastMem->nLen=0;
				m_pLastMem->NextOffset=0;

				pPrev->NextOffset=GetPointOffset(m_pLastMem);


			}else
			{
				//ɾ�����ڵ�
				pNext->PrevOffset=pMem->PrevOffset;//GetPointOffset(GetPrevMem(pMem));
				pPrev->NextOffset=pMem->NextOffset;
				pOld->nLen=0;pOld->PrevOffset=0;pOld->nFlag='leDY';pOld->NextOffset=0;
			}

				

			
			//printf("del pMem!=m_pLastMem ");
			//TestInfo();
		}
		return true;

	}
	__int64 m_CurMaxIndex;
};


typedef __int64 IndexType;
extern MemoryMgrInterface< PointInterfaceForMemoryMgr<IndexType> > * g_pMemoryMgr[];


//ʵ�����д���С�ڴ棬��̬һ�η���õĳ��ϣ�����string�����ȵȣ�����һ���ͷţ������������ٶȣ�
//�����ʺ����д�����ʱ���󷴸����������ĳ��ϣ���Ϊ�ڴ����ڼ䲻���ͷţ������ڴ�ռ�ù���
//�ŵ㣺 ռ���ڴ���С�������ٶ�=�������������ٶȣ�0�����ٶ�
//ȱ�㣺 ��Ҫ�ں��ʵ�ʱ����������GC��������Ӧ����ʱ����ʱ��
template<typename PointInterfaceT, typename ContainerT, int nGrowSize, int nGrowCount>
class MemoryMgr_StaticGC : 
	public MemoryMgrInterface<PointInterfaceT>,
	public MemPoolDbg,
	public CSystemContainerObjectBase<MemoryMgr_StaticGC<PointInterfaceT, ContainerT, nGrowSize, nGrowCount>, ContainerT>
{
public:
	struct BlockCtl
	{
		void * pBlock;
		unsigned int nCurLen;
		unsigned int nMaxLen;
	};
	BlockCtl m_MemBlock[nGrowCount];
	unsigned int m_nCurrentBlockCount;

public:
	typedef MemoryMgr_StaticGC<PointInterfaceT, ContainerT,  nGrowSize,  nGrowCount > _Myt;
	/*
	static _Myt & GetInstance()
	{
		static _Myt _self;
		return _self;
	}
	*/

private:
	
	bool GrowHeap(unsigned int nLen)
	{
		if (m_nCurrentBlockCount == (nGrowCount-1))
		{
			YSS_ASSERT(TRUE);
			return false;
		}
		//��0���ߵ�ǰheap������
		

		if (m_MemBlock[m_nCurrentBlockCount].pBlock == NULL)
		{
			m_MemBlock[m_nCurrentBlockCount].pBlock = ContainerT::SystemMemPoolT::GetInstance().NewMemory(max(nLen, nGrowSize));
			m_MemBlock[m_nCurrentBlockCount].nCurLen = 0;
			m_MemBlock[m_nCurrentBlockCount].nMaxLen = max(nLen, nGrowSize);
#ifdef MEM_DBG
			
			DbgGcNewMem(max(nLen, nGrowSize));
#endif
		}
		else
		{
			m_nCurrentBlockCount++;
			if (m_MemBlock[m_nCurrentBlockCount].pBlock == NULL) return GrowHeap(nLen);
			if (nLen > nGrowSize)
			{
				ContainerT::SystemMemPoolT::GetInstance().DelMemory(m_MemBlock[m_nCurrentBlockCount].pBlock, m_MemBlock[m_nCurrentBlockCount].nMaxLen);
				m_MemBlock[m_nCurrentBlockCount].pBlock = ContainerT::SystemMemPoolT::GetInstance().NewMemory(max(nLen, nGrowSize));
#ifdef MEM_DBG
				DbgGcDelMem(m_MemBlock[m_nCurrentBlockCount].nMaxLen);
				DbgGcNewMem(max(nLen, nGrowSize));
#endif
			}
			m_MemBlock[m_nCurrentBlockCount].nCurLen = 0;
			m_MemBlock[m_nCurrentBlockCount].nMaxLen = max(nLen, nGrowSize);
		}
		

		return true;
	}
	void * NewMem(__int64 nLen)
	{
#ifdef MEM_DBG
		if (m_nCurrentBlockCount >= nGrowCount) YSS_ASSERT(TRUE);
#endif 
		//if (nLen > nGrowSize) GrowHeap(nLen);
		//if (m_MemBlock[m_nCurrentBlockCount].pBlock==NULL) GrowHeap();
		if (m_MemBlock[m_nCurrentBlockCount].nCurLen + nLen>m_MemBlock[m_nCurrentBlockCount].nMaxLen) GrowHeap(nLen);
		void * pMem = (void*)((char *)m_MemBlock[m_nCurrentBlockCount].pBlock + m_MemBlock[m_nCurrentBlockCount].nCurLen);
#ifdef MEM_DBG
		if (pMem == NULL)
		{
			YSS_ASSERT(TRUE);
		}
		DbgNewMem(nLen);
#endif
		m_MemBlock[m_nCurrentBlockCount].nCurLen += nLen;
		return pMem;
	}

public:
	MemoryMgr_StaticGC(){ 
		memset(&m_MemBlock, 0, sizeof(m_MemBlock));
		m_nCurrentBlockCount = 0; 
	};
	~MemoryMgr_StaticGC(){};
	//GCȫ�ֳ�ʼ�������ڴ�
	void * NewGc()
	{
		return this;
	}
	//ȫ��GCģʽʱ�ͷ�gc�ڴ�
	void DelGc(bool bRealClear)
	{
		
		for (unsigned int i=0;m_MemBlock[i].pBlock!=NULL;i++)
		{
			if (bRealClear)
			{
				ContainerT::SystemMemPoolT::GetInstance().DelMemory(m_MemBlock[i].pBlock, m_MemBlock[i].nMaxLen);
				m_MemBlock[i].pBlock = 0;
			}
			m_MemBlock[0].nCurLen = 0;
		}
		m_nCurrentBlockCount = 0;
		
		return;
	}


	//��pool�з�����ͨ�ڴ�
	void * NewMemory(__int64 nLen) {
		return NewMem(nLen);
	};
	bool DelMemory(void * pMem, __int64 nLen) {
#ifdef MEM_DBG
		DbgDelMem(nLen);
#endif
		return FALSE;//g_pMemoryMgr[nParentMemMgr].DelMemory(pMem);
	};

protected:


};



//  VS2013��֧�ֳ������ʽ
//	constexpr size_t  FlagBitSize=2;

//�����һЩ���������ڼ��ټ���
#define FlagBitSize				2												//��־λ����������Ϊ2��N�η�
#define FlagBitSizeLog2			(TTL::log<FlagBitSize,2>::nRet)					//ȡ���λ�ߴ��2Ϊ�׵Ķ���
#define FlagBitSizeMask			((0x1<<FlagBitSize)-1)
#define FlagBitSizeLog2Mask		(FlagBitSizeLog2-1)

#define TypeNodeCount			((sizeof(size_t)<<3)>>FlagBitSizeLog2)			//size_t���������ɵĽڵ�����
#define TypeNodeCountLog2		(TTL::log<TypeNodeCount, 2>::nRet)
#define TypeNodeCountMask		(TypeNodeCount-1)
#define TypeNodeCountLog2Mask	(TypeNodeCountLog2-1)

#define TreeNodeCount			(TTL::power<2, nBitTreeNodeLog2>::nRet)			//һ���ڵ��Ҷ������
#define TreeNodeCountLog2		(nBitTreeNodeLog2)
#define TreeNodeCountMask		(TreeNodeCount-1)
#define TreeNodeCountLog2Mask	(TreeNodeCountLog2-1)
#define TreeNodeFlagMask		((1<<(FlagBitSize<<TreeNodeCountLog2))-1)

#define BlockSize				(TTL::power<2,nBlockSizeLog2>::nRet)			//�����ڴ�Ĵ�С
#define BlockSizeLog2			(nBlockSizeLog2)
#define BlockSizeMask			(BlockSize-1)
#define BlockSizeLog2Mask		(BlockSizeLog2-1)

#define BlockCount				(TTL::power<TreeNodeCount, nBitTreeDepth>::nRet)
#define BlockCountLog2			(nBitTreeDepth)	
#define BlockCountMask			(BlockCount-1)	
#define BlockCountLog2Mask		(BlockCountLog2-1)

#define LevelNodeCount(_nLevel)		(0x1<<m_LevelPower(_nLevel))
#define LowNodeIDFromID(_nDepth,_nID)		(_nID<<m_LevelPower(_nDepth))
//Node

//#define LevelFromLowID

//��x��y�η���<<�� x^y=2^(log2(x)*y) �˱�Ϊһ����Χ��yԤ����(log2(N)*y)  
//nBitTreeDepthΪy�ķ�Χ nBitTreeNodeLog2Ϊ����log2(N),ʹ��ʱ��y�����������õ�(log2(N)*y)
template<u_char nBitTreeDepth, u_char nBitTreeNodeLog2>
class PowerTab
{
public:
	u_char m_LevelTab[nBitTreeDepth+1];
	PowerTab(){
		for (u_char i = 0; i <= nBitTreeDepth; i++)
		{
			//BitTreeNodeCount��(nBitTreeDepth-i)�η��������ǰ��ڵ���
			m_LevelTab[i] = (nBitTreeNodeLog2*(nBitTreeDepth-i));
		}
	};
	~PowerTab(){
	};

	size_t operator ()(size_t nDepth)
	{
		return m_LevelTab[nDepth];
	}
protected:
	
private:
};

class MemoryCheck
{
public:
	
	std::map<u_char *, int, std::less<u_char*>> m_AddressMap;
	unsigned int m_nCheckCount;
	MemoryCheck(){ m_nCheckCount = 0; };
	~MemoryCheck(){};

	void NewCheck(u_char* pBuf,size_t nLen)
	{
		if (m_AddressMap.find(pBuf) != m_AddressMap.end())
		{
			
			YSS_ASSERT(1);
		}
		else
		{
			
			m_AddressMap[pBuf] = nLen;
			m_nCheckCount++;
		}
	}
	void DelCheck(u_char* pBuf, size_t nLen)
	{
		if (m_AddressMap.find(pBuf) == m_AddressMap.end())
		{
			YSS_ASSERT(1);
		}
		else
		{
			if (nLen != m_AddressMap[pBuf])
			{
				YSS_ASSERT(1);
			}
			m_AddressMap.erase(pBuf);// = 1;
			m_nCheckCount--;
		}
	}
protected:
	
private:
};
//λͼ�㷨�ʺ��ڽ���ڴ���Ƭ��ɵ��ڴ�������ܲ����������Լ�С�ڴ��ǽϴ��ͷ�ռ�ռ�ã�ʹ���ڴ��������½������⡣
//nBlockSizeLog2����С���С,2��nBlockSizeLog2�η� 
//nBitTreeDepth�����
//nBitTreeNodeLog2��2Ϊ�׽ڵ������Ķ���������3
//��ڵ�����Ϊ2��3�η�8����СΪ1��
//cache���ڲ���nGrowLevel
//>>��������<<���˷� &Maskȡ����
//�ŵ㣺��С�ڴ�����ٶ������ȶ������ڴ�����ٶ���Ի���죩��С�ڴ�����ٶ���ϵͳ�Ķ���֮һ���ͷ��ٽϿ죬��ϵͳ�����ٶȵ�5��������ڴ���Ƭ��ɵĴ��ڴ治�׷�������⣬����Ҫ��������GC,
//ȱ�㣺ռ���ڴ�϶࣬������nBlockSizeLog2��Ӧ�ó��ϲ��ϴ��ʱ����ʱ���������ͷŵ�Ԥ������ڴ�

#ifndef intel_cpp



template<typename PointInterfaceT, typename ParentMemMgr,unsigned int nBlockSizeLog2, unsigned int nBitTreeDepth, unsigned int nBitTreeNodeLog2, unsigned int nCacheLevel >
class MemoryMgr_BitMap : public MemoryMgrInterface<PointInterfaceT>
{
public:
	typedef MemoryMgr_BitMap<PointInterfaceT, ParentMemMgr, nBlockSizeLog2, nBitTreeDepth, nBitTreeNodeLog2, nCacheLevel> _Myt;
	static _Myt & GetInstance()
	{
		static _Myt _self;
		return _self;
	}

private:

	//BYTE m_BitMap[nBitTreeDepth][(power<power<2, nBitTreeNodeLog2>::nRet, nBitTreeDepth>::nRet / 4) + 1];
#define STATE_BIT_NULL			0x0		//δ��ʼ��
#define STATE_BIT_DIRTY			0x1		//��
#define STATE_BIT_FULL			0x2		//��
#define STATE_BIT_TOMEDIA		0x3		//����������ý�飨����̻������磩


	//size_t m_SizeLevelTab[nBitTreeDepth];
	PowerTab<nBitTreeDepth, nBitTreeNodeLog2> m_LevelPower;
	//�ڵ����ߴ�

	//�ֲ�����bitmap��
	size_t* m_pBitMapLevel[nBitTreeDepth + 1];
	//bitmap�ڴ�� �ڵ���* size_t���ɵĽڵ���
	size_t m_BitMap[(((TTL::TotalTreeNodeCount<nBitTreeDepth, nBitTreeNodeLog2>::nRet)>>TypeNodeCountLog2) + (2 * (nBitTreeDepth+1)))];
	//�ڴ��ָ���
	u_char * m_pBlockMemArray[BlockCount];
	u_char * m_pBaseMem;

	size_t m_nLastCanUsedNodeID;
	size_t m_nLastCanUsedNodeChildCount;

	size_t m_nLastCanUsedDepth;
	size_t m_nLastCanUsedLen;
	size_t m_nTotalCompareNodeCount;
	size_t m_nTotalMemFromNear;
	size_t m_nTotalMemCount;

	size_t m_nCurLen;
	bool m_bSetFull;
	size_t m_nCurNodeBit;

	bool m_bOverSetLast; bool m_bOverSetLastFull;


	//ID��0��ʼ����
//#define GetBitAddress(nDepth,nParentId,nChildId) (BYTE*)(&((&((m_pBitMapLevel[nDepth])[(nParentId<<nBitTreeNodeLog2)>>2]))[nChildId>>2]))
//#define SetBit(nDepth,nParentId,nChildId,nBitVal) ((*(GetBitAddress(nDepth,nParentId,nChildId)))&=nBitVal<<((nChildId&0x3)<<1));
//#define GetBit(nDepth,nParentId,nChildId,nBitVal) nBitVal=((*(GetBitAddress(nDepth,nParentId,nChildId)))>>((nChildId&0x3)<<1))&0x3;

	//Ѱַ����
	/*
	
	inline size_t * GetBitAddress(unsigned int nDepth, size_t nParentId, size_t nChildId)
	{
		size_t nOffset = (nParentId << TreeNodeCountLog2);
		nOffset = nOffset >> TypeNodeCountLog2;
		size_t * pAddr = (size_t*)(&((&((m_pBitMapLevel[nDepth])[nOffset]))[nChildId >> TypeNodeCountLog2]));
		return pAddr;
	}

	inline void SetBit(unsigned int nDepth, size_t nParentId, size_t nChildId, size_t nBitVal)
	{
		size_t* pDst = GetBitAddress(nDepth, nParentId, nChildId);
		size_t  nOffset = ((nChildId & FlagBitSizeMask) << FlagBitSizeLog2);
		nOffset += (nParentId & TypeNodeCountLog2Mask) << FlagBitSizeLog2;
		size_t  nDstVal = nBitVal << nOffset;
		size_t  nDstValMask = ~(FlagBitSizeMask << nOffset);
		*pDst &= nDstValMask;
		*pDst |= nDstVal;
		return ;
	}

	
	inline size_t  GetBit(unsigned int nDepth, size_t nParentId, size_t nChildId)
	{
		size_t * pDst = GetBitAddress(nDepth, nParentId, nChildId);
		size_t  nOffset = ((nChildId & FlagBitSizeMask) << FlagBitSizeLog2);
		nOffset += (nParentId & TypeNodeCountLog2Mask) << FlagBitSizeLog2;
		size_t  nDstVal = (*pDst >> nOffset) & FlagBitSizeMask;
		return nDstVal;
	}
	*/

	inline size_t * GetBitAddress(unsigned int nDepth, size_t nID)
	{
		size_t nOffset = nID >> TypeNodeCountLog2;
		size_t * pAddr = (size_t*)&((m_pBitMapLevel[nDepth])[nOffset]);
		return pAddr;
	}

	inline void SetBit(unsigned int nDepth, size_t nID, size_t nBitVal)
	{
		size_t* pDst = GetBitAddress(nDepth, nID);
		size_t nChildId = nID&TreeNodeCountMask;
		//size_t nSizeOffset = (nID >> TypeNodeCountLog2) << FlagBitSizeLog2;
		size_t nBitOffset = (nID&TypeNodeCountMask) << FlagBitSizeLog2;

		size_t  nDstVal = nBitVal << nBitOffset;
		size_t  nDstValMask = ~(FlagBitSizeMask << nBitOffset);
		pDst[0] &= nDstValMask;
		pDst[0] |= nDstVal;
		return;
	}


	inline size_t  GetBit(unsigned int nDepth, size_t nID)
	{
		/*if ((nDepth == 0x9) && (nID == 16))
		{
			printf("aaa");
		}*/
		size_t* pDst = GetBitAddress(nDepth, nID);
		size_t nChildId = nID&TreeNodeCountMask;

		//
		//size_t nSizeOffset = (nID >> TypeNodeCountLog2) << FlagBitSizeLog2;
		/*size_t val = FlagBitSizeLog2;
		size_t nSizeOffset = (nID << FlagBitSizeLog2);
		val = TypeNodeCountLog2;
		nSizeOffset = nSizeOffset >> TypeNodeCountLog2;*/

		size_t nBitOffset = (nID&TypeNodeCountMask) << FlagBitSizeLog2;

		size_t  nDstVal = ((pDst[0] >> nBitOffset) & FlagBitSizeMask);
		return nDstVal;
	}
	//ͨ���ܽ��ӽڵ�����״̬���������ڵ�����״̬�������Ƿ����óɹ�

	//��Ҫ�ȽϵĴ���
	#define		CanMaskCount			((TreeNodeCount>TypeNodeCount) ? TypeNodeCount : TreeNodeCount)
	#define		CompareCount			(((TreeNodeCount - 1) >> TypeNodeCountLog2) + 1)
	#define		CompareCountI			((TreeNodeCount - 1) >> TypeNodeCountLog2)

	//CompareNode<(((((TTL::power<2, nBitTreeNodeLog2>::nRet - 1 >> nRet + 1 - 1, nState, nStateMask>

	template<int i, size_t nStateMask>
	struct CompareNode
	{
		template<typename CallFunc>
		inline static bool ForNode(size_t * pDst, size_t nCurID, size_t & NodeBit, CallFunc & Call)
		{
			size_t nChildId = (nCurID + (i << TypeNodeCountLog2))&TreeNodeCountMask;
			//��ID���Ա��λ������������������
			size_t nSizeOffset = (nChildId >> TypeNodeCountLog2); //>> TypeNodeCountLog2;
			//
			size_t nBitOffset = (nCurID &TypeNodeCountMask) << FlagBitSizeLog2;
			NodeBit = ((pDst[nSizeOffset] >> nBitOffset) & TreeNodeFlagMask);
			if (NodeBit != nStateMask)
			{
				Call(NodeBit);
				return false;
			}
			//β�ݹ�ɱ������Ż��⿪
			return CompareNode<(i - 1), nStateMask>::ForNode(pDst, nCurID, NodeBit, Call);
		}
	};
	template<size_t nStateMask>
	struct CompareNode<-1, nStateMask>
	{
		template<typename CallFunc>
		inline static bool ForNode(size_t * pDst, size_t nCurID, size_t & NodeBit, CallFunc & Call)
		{
			return true;
		}
	};

	template<unsigned int nCompareCount,unsigned int nState, size_t nStateMask>
	bool IfSet(unsigned int nDepth, size_t nID, size_t * & pDst)
	{
		size_t nCurID = nID << TreeNodeCountLog2;
		if(pDst==NULL) pDst = GetBitAddress(nDepth + 1, nCurID);
		size_t nChildId = 0;
		size_t  nBitOffset = 0;
		//size_t  nSizeOffset = 0; 
		
			for (unsigned int i = 0; i < nCompareCount; i++)
			{
				size_t nChildId = (nCurID + (i << TypeNodeCountLog2))&TreeNodeCountMask;
				//��ID���Ա��λ������������������
				size_t nSizeOffset = (nChildId >> TypeNodeCountLog2); //>> TypeNodeCountLog2;
				//
				nBitOffset = (nCurID &TypeNodeCountMask) << FlagBitSizeLog2;
				//size_t nDiff = ((pDst[nSizeOffset] >> nBitOffset) & TreeNodeFlagMask) ^ nStateMask;
				m_nCurNodeBit = ((pDst[nSizeOffset] >> nBitOffset) & TreeNodeFlagMask);
				if (m_nCurNodeBit != nStateMask)
				{
					//m_nLastCanUsedNodeChildCount = 0;
					//m_nLastCanUsedNodeChildCount = NodeBit ^ (TTL::MakeBitMask<CanMaskCount, FlagBitSize, STATE_BIT_NULL>::nRet);
					//while (nDiff) { nDiff = nDiff >> FlagBitSize, m_nLastCanUsedNodeChildCount++; };

					return false;
				}

			}
		
		/*
		if (CompareNode<CompareCountI, nState, nStateMask>::ForNode(pDst, nCurID) == false)
		{
			return false;
		}
		*/
		
		SetBit(nDepth, nID, nState);
		return true;
	};
	struct NodeContext
	{
		u_char * pDstBit;
		unsigned int nSizeOffset;
		unsigned int nBitOffset;
	};
	bool GetCanUsedNode(unsigned int nDepth, size_t nID, OUT size_t & nCanId, size_t * & pDst)
	{
		nCanId = 0;
		bool bFindCanUsed = false;
		////return true;
		//size_t  NodeBit,nOldNodeBit;
		size_t nCurID = nID << TreeNodeCountLog2;
		if (pDst==NULL) pDst = GetBitAddress(nDepth + 1, nCurID);
		CompareNode<CompareCountI,
			TTL::MakeBitMask<CanMaskCount, FlagBitSize, STATE_BIT_FULL>::nRet
		>::ForNode(pDst, nCurID, m_nCurNodeBit,
		[=, &nCanId, &bFindCanUsed](size_t & nCurNodeBit) {
			//����ȫ����
			unsigned int i = 0;

			while (i < CanMaskCount)
			{
				size_t nBit = (nCurNodeBit&FlagBitSizeMask);
				if (nBit == STATE_BIT_NULL)
				{
					nCanId = i;
					bFindCanUsed = true;
					return;
				}
				else if (nBit == STATE_BIT_DIRTY)
				{
					nCanId = i;
					bFindCanUsed = true;
					return;
				}
				nCurNodeBit = nCurNodeBit >> FlagBitSize;
				i++;
			};
			bFindCanUsed = false;
			return;
		});
		
		/*if (nCanId == 0)
		{
			return false;
		}*/
		return bFindCanUsed;
	}
	

	bool NullSet(unsigned int nDepth, size_t nID, size_t * & pDst)
	{
		/*
		m_nLastCanUsedNodeChildCount = 0;
		TTL::_Switch<CompareCount,
			typename TTL::_Case<_default, _IfSet0,
			typename TTL::_NullCase>
			//>
		 >::RetType ste;
		*/// 
		//ste(nDepth, nID);
		//printf("%s", typeid(int).name());
		//m_nLastCanUsedNodeChildCount = 0;
		//size_t NodeBit;
		return IfSet< CompareCount, STATE_BIT_NULL,
			TTL::MakeBitMask<CanMaskCount,
			FlagBitSize, STATE_BIT_NULL>::nRet>(nDepth, nID, pDst);
		return true;
	}
	//�ж�������״̬
	bool FullSet(unsigned int nDepth, size_t nID,size_t * & pDst)
	{
		m_nLastCanUsedNodeChildCount = 0;
		//size_t NodeBit;
		if (IfSet< CompareCount, STATE_BIT_FULL,
			TTL::MakeBitMask<CanMaskCount,
			FlagBitSize, STATE_BIT_FULL>::nRet>(nDepth, nID,pDst) == false)
		{
			
			
			
			return false;
		}
		return true;
	}

	
	//��pool�з�����ͨ�ڴ�
	/*
	*/
	unsigned int NNNN = 0;
	void * NewMem(unsigned int nDepth, size_t nID) {
		
		//��⵱ǰ�ڵ��Ƿ�ɷ���
		//if (nDepth>)
		
		size_t nFlag = GetBit(nDepth, nID);
		if (nFlag == STATE_BIT_FULL) return NULL;
		
		unsigned int nCurDepthMaxAllocSize = LevelNodeCount(nDepth) << BlockSizeLog2;//(0x1 << (nBitTreeDepth - nDepth)) << BlockSizeLog2;
		unsigned int nCurDepthChildMaxAllocSize = (nDepth == nBitTreeDepth) ? nCurDepthMaxAllocSize : (nCurDepthMaxAllocSize >> TreeNodeCountLog2);
		if ((m_nCurLen <= nCurDepthMaxAllocSize))
		{
			if ((m_nCurLen>nCurDepthChildMaxAllocSize))
			{
				if (nFlag == STATE_BIT_NULL)
				{
					//���ڴ�ռ��ģʽ
					if ((nDepth == 7) && (nID == 35))
					{
						//NNNN++;
						//printf("%u\r\n", NNNN);
					}
					if (NNNN == 0x8)
					{
						//printf("%u 1\r\n", NNNN);
					}
					SetBit(nDepth, nID, STATE_BIT_FULL);
					size_t nCurParentId = LowNodeIDFromID(nDepth,nID);
					//�����ڴ���Ƭ��ɵĶ������
					//m_nLastCanUsedDepth = 0;
					//m_nLastCanUsedNodeID = 0;
					//m_nLastCanUsedLen = BlockSize;
					m_bOverSetLastFull = true;
					m_bSetFull = true;
					//m_bOverSetLast = true;
					//printf_d("new bigmem level=%u id=%u memid=%u(newb) \r\n", nDepth, nID, nCurParentId);

					return m_pBlockMemArray[nCurParentId];

				}
				//���㹻����
				return NULL;
			}
			else
			{
				if (nDepth == nBitTreeDepth)
				{
					//С�ڴ�ռ��ģʽ����ʱ��������������Ҫ�Ż�ΪSTATE_BIT_DIRTY
					
					SetBit(nDepth, nID, STATE_BIT_FULL);
					m_bSetFull = true;
					//printf_d("new rootmem level=%u id=%u memid=%u(new) \r\n", nDepth, nID, nID);
					


					return m_pBlockMemArray[nID];
				}
				else
				{
					size_t nChildId = 0;
					size_t * pDstVal = NULL;
					if (GetCanUsedNode(nDepth, nID, nChildId, pDstVal))
					{
						for (; nChildId < TreeNodeCount; nChildId++)
						{
							//nFlag = GetBit(nDepth + 1, nParentId, nChildId);
							//if (Flag != STATE_BIT_FULL)
							m_nTotalCompareNodeCount++;
							void * pMem = NewMem(nDepth + 1, (nID << TreeNodeCountLog2) + nChildId);
							if (pMem)
							{
								//���õ�ǰ�ڵ�״̬
								//
								if (FullSet(nDepth, nID,pDstVal) == false)
								//if (GetCanUsedNode(nDepth, nID, nChildId, pDstVal))
								{
									if ((m_bOverSetLast == false) && (nDepth != 0)/*&&(m_nLastCanUsedNodeChildCount)*/)
									{
										if (m_nLastCanUsedDepth == 0)
										{

											//m_nLastCanUsedDepth = 0;
											//m_nLastCanUsedNodeID = 0;
											m_nLastCanUsedDepth = nDepth - 1;
											m_nLastCanUsedNodeID = nID >> TreeNodeCountLog2;
											//m_nLastCanUsedDepth = nDepth;
											//m_nLastCanUsedNodeID = nID;
											m_nLastCanUsedLen = (m_bOverSetLastFull == true) ? BlockSize : m_nCurLen;

											m_bOverSetLast = true;
										}
									}
									SetBit(nDepth, nID, STATE_BIT_DIRTY);
									m_bSetFull = false;
								}
								else
								{
									m_bSetFull = true;
									//SetBit(nDepth, nID, STATE_BIT_FULL);
									if ((m_bOverSetLast == false) && (nDepth != 0))
									{
										//m_bOverSetLastFull = true;
										m_nLastCanUsedDepth = 0;
										m_nLastCanUsedNodeID = 0;
										m_bOverSetLast = true;
									}

								}
								//��ǰ�ڵ����ɹ�
								return pMem;
							}
						}
					}
					
				}
				
			}
			
		}

		return NULL;
	};
	
	bool DelMem(unsigned int nDepth, size_t nID,bool bFirstSet)
	{
		//��FULL�ڵ��ΪNULL��֮��������ΪFULL���ΪDIRTY���������FULL����ֹ���ݡ�
		if (bFirstSet)
		{
			size_t nFlag = GetBit(nDepth, nID);
			if (nFlag == STATE_BIT_FULL)
			{
				SetBit(nDepth, nID, STATE_BIT_DIRTY);
				//�������ϻ���
				//return true;
			}
			else if (nFlag == STATE_BIT_DIRTY)
			{
				//����Ƿ�Ҫ��գ������Ҫ�������ϵݹ�
				size_t * pDst=NULL;
				if (NullSet(nDepth, nID, pDst) == false)
				{
					//ֹͣ����
					
					return true;
				}
			}

			
		}
		else
		{
			SetBit(nDepth, nID, STATE_BIT_NULL);
			bFirstSet = true;
			//printf_d("del mem level=%u id=%u memid=%u(del) \r\n", nDepth, nID, LowNodeIDFromID(nDepth, nID));
			
		}

		if (nDepth == 0)
		{
			return true;
		}

		return DelMem(nDepth - 1, nID >> TreeNodeCountLog2, bFirstSet);
		
	}
	bool DelMem(void * pMem, __int64 nLen) {
		size_t nOffset = (size_t)((u_char*)pMem - m_pBlockMemArray[0]);// >> (TTL::log(sizeof(size_t), 2));
		//nOffset = nOffset ;
		size_t nCurID = nOffset >> BlockSizeLog2; //ȡģ
		size_t nChildId = nCurID & TreeNodeCountMask;//ȡ��
		//size_t nParentId = nCurID >> TreeNodeCountLog2;
		unsigned int nSize = nLen >> BlockSizeLog2;
		if ((nLen&BlockSizeMask)==0)
		{
			nSize--;
		}
		unsigned int nDepth = nBitTreeDepth;
		for (; nSize!=0;)
		{
			nDepth--;
			nSize = nSize >> TreeNodeCountLog2;
			nCurID = nCurID >> TreeNodeCountLog2;
		}
		return DelMem(nDepth, nCurID, FALSE);
	};

	
	void DumpMemInfo(unsigned int nDepth,size_t nID)
	{
		unsigned int nFlag = GetBit(nDepth, nID);
		//if (nDepth == nBitTreeDepth)
		
		nFlag = GetBit(nDepth, nID);
		if (nFlag == STATE_BIT_FULL)
		{
			printf("Mem  Depth=%d,nId=%d nFlag=%d size=%u\r\n", nDepth, nID, nFlag, (LevelNodeCount(nDepth) << BlockSizeLog2));
			return;
		}
		else if (nFlag == STATE_BIT_DIRTY)
		{
			for (unsigned int i = 0; i < TreeNodeCount; i++)
			{
				DumpMemInfo(nDepth + 1, ((nID << TreeNodeCountLog2) + i));
			}
		}
		// null ������
	}


public:
	MemoryMgr_BitMap(){
		//��ʼ��bitmap;
		memset(&m_pBitMapLevel[0], 0, sizeof(m_pBitMapLevel));
		memset(&m_BitMap[0], 0, sizeof(m_BitMap));
		//memset(&m_pBlockMemArray[0], 0, sizeof(m_pBlockMemArray));
		m_pBaseMem = (u_char*)ParentMemMgr::GetInstance().NewMemory(BlockSize * (BlockCount+2));
		for (unsigned int i=0;i<BlockCount;i++)
		{
			m_pBlockMemArray[i] = (u_char *)(m_pBaseMem+((i + 1)*BlockSize));
		}
		size_t * pCurBitMap = &m_BitMap[0];
		size_t nCurPos = 0;
		size_t nNeedCount = 1; //((pow(TreeNodeCount, i) >> TypeNodeCountLog2)) + 1;
		size_t nNeedSize = 0;
		for (size_t i = 0; i <= nBitTreeDepth; i++)
		{
			m_pBitMapLevel[i] = pCurBitMap;
			nNeedSize = (nNeedCount >> TypeNodeCountLog2) + 1;
			nCurPos += nNeedSize+1; //2��i�η�+1���߽���

			nNeedCount = nNeedCount << TreeNodeCountLog2;// ((pow(TreeNodeCount, i) >> TypeNodeCountLog2)) + 1;

			m_pBitMapLevel[i][nNeedSize] = 'YESS';

			pCurBitMap = &m_BitMap[nCurPos];
			
		}
		m_nLastCanUsedLen = 0;
		m_nLastCanUsedNodeID = 0;
		m_nLastCanUsedDepth = 0;
		m_nTotalCompareNodeCount = 0;
		m_nTotalMemFromNear = 0;
		m_nTotalMemCount = 0;
		m_bOverSetLast = false;
	};
	~MemoryMgr_BitMap(){};
	//GCȫ�ֳ�ʼ�������ڴ�
	void * NewGc()
	{
		return this;
	}
	//ȫ��GCģʽʱ�ͷ�gc�ڴ�
	void DelGc(bool bRealClear)
	{
		return;
	}

	void ReArrange()
	{
		return;
	}
	bool TestInfo()
	{
		printf("MemoryMgr_OS TreeNodeCount = %d %x TotalTreeNodeCount=%u BlockCount=%u BlockSize=%u \r\n"\
			"m_nTotalCompareNodeCount=%I64d m_nTotalMemFromNear=%u m_nTotalMemCount=%u\r\n", 
			TreeNodeCount, TreeNodeCountMask, TTL::TotalTreeNodeCount<nBitTreeDepth, nBitTreeNodeLog2>::nRet,
			BlockCount, BlockSize, (__int64)m_nTotalCompareNodeCount, (unsigned int)m_nTotalMemFromNear, (unsigned int)m_nTotalMemCount);

		printf("DumpMemInfo %x %x %x %x\r\n", 
			m_pBitMapLevel[nBitTreeDepth][0],
			m_pBitMapLevel[nBitTreeDepth][1],
			m_pBitMapLevel[nBitTreeDepth][2],
			m_pBitMapLevel[nBitTreeDepth-1][0]);
		DumpMemInfo(0, 0);

		printf("\r\b=======================End==========================\r\n", TreeNodeCount);
		//����ʹ����
		return true;
	}


	//��pool�з�����ͨ�ڴ�
	MemoryCheck mc;
	void * NewMemory(__int64 nLen) {
		unsigned int nCurDepthMaxAllocSize = LevelNodeCount(0) << BlockSizeLog2;
		if (nLen > nCurDepthMaxAllocSize)
		{
			YSS_ASSERT(true);
		}
		size_t nUsedDepth = 0;
		size_t nUsedId = 0;
		
		if (m_bOverSetLast&&m_nLastCanUsedDepth)
		{
			//�Ż�С�ڴ����
			if (m_nLastCanUsedLen >= nLen)
			{
				nUsedDepth = m_nLastCanUsedDepth;
				nUsedId = m_nLastCanUsedNodeID;
				m_nTotalMemFromNear++;
			}
		}
		m_nTotalMemCount++;

		m_bOverSetLast = false;
		m_bSetFull = false;
		m_bOverSetLastFull = false;
		m_nCurLen = nLen;
		void * pMem = NewMem(nUsedDepth, nUsedId);
		

		size_t nOldUsedDepth=nUsedDepth, nOldUsedId = nUsedId;
		bool bOldSetFull = m_bSetFull;

		size_t * pDstVal = NULL;
		while (m_bSetFull && (nUsedDepth != 0)) {
			nUsedDepth--;
			nUsedId = nUsedId >> TreeNodeCountLog2;
			pDstVal = NULL;
			m_bSetFull = FullSet(nUsedDepth, nUsedId, pDstVal);
			m_nLastCanUsedLen = BlockSize;
		};
		//mc.NewCheck((u_char*)pMem,nLen);
		printf_d("New pMem=%x Len=%u %u %u %s %s\r\n",
			pMem, (unsigned int)nLen,
			(unsigned int)nOldUsedDepth, (unsigned int)nOldUsedId, 
			nOldUsedDepth == 0 ? "" : "fast",
			bOldSetFull==true?"reset":"");
		if (pMem == NULL)
		{
			pDstVal = NULL;
			bool bOk = FullSet(nUsedDepth, nUsedId, pDstVal);
			YSS_ASSERT(true);
		}
		return pMem;
	};
	bool DelMemory(void * pMem, __int64 nLen) {
		printf_d("Del pMem=%x Len=%u\r\n", pMem, nLen);
		//mc.DelCheck((u_char*)pMem,nLen);
		return DelMem(pMem,nLen);
	};
};

#endif // !intel_cpp



//freelistÿһ���ڴ��С����Ϊ��һ������С*2,����Ϊ�����ڴ����������ʱ����ʹ�ã�����ʱ�����пɿ��ٷ����ͷ��ڴ棬������Ҫ�㸴�Ӷȵ�Tree List����֮����� cache�ߴ����BlockSize*nListMaxCount
//nLevelΪ�ּ���
//nListMaxCountΪfreelist�������ɻ����ڴ������
//nBlockSize������ڵ���4*sizeof(char *)
//nLevel=3 nBlockSizeLog2=8�����
//256(Level0) 512(Level1) 1024(Level2) 2048(Level3)
//�ŵ㣺 Ԥ�Ⱥ�ӵ�������ڴ�����ٶȣ������Ż�����ϵͳ�ڴ����,�ر��ʺ�����ʱ������ڴ����
//ȱ��: ��Ҫ����gc�����ͷ�cache����Ҫ����nBlockSizeLog2��Ӧ�ó��ϣ��ڴ�ռ�ýϴ�
template<typename PointInterfaceT, unsigned int nBlockSizeLog2, unsigned int nLevel, unsigned int nListMaxCount, typename ContainerT>
class MemoryMgr_FreeList : public MemoryMgrInterface<PointInterfaceT>,
	public MemPoolDbg,
	public CSystemContainerObjectBase<MemoryMgr_FreeList<PointInterfaceT, nBlockSizeLog2, nLevel, nListMaxCount, ContainerT>, ContainerT>
{
private:
	PowerTab<nLevel, 1> m_LevelPower;
	
	struct MemNode :public TransferList<MemNode, 1>::_NodeBase
	{
		void* pMemBlock;
		size_t nLen;
	};

	TransferList<MemNode, 1> m_FreeListArray[nLevel];
	size_t m_nCurListCount;

	void * NewMem(__int64 nLen) {

		//size_t nParentId = nCurID >> TreeNodeCountLog2;
		size_t nSize = nLen >> BlockSizeLog2;
		size_t nUseLen = BlockSize;
		if ((nLen&BlockSizeMask) == 0)
		{
			nSize--;
		}
		unsigned int nDepth = 0;
		for (; nSize != 0;)
		{
			nDepth++;
			nSize = nSize >> 1;
			nUseLen = nUseLen << 1;
		}
		if (nDepth > nLevel)
		{
			YSS_ASSERT(1);
			return ContainerT::SystemMemPoolT::GetInstance().NewMemory(nUseLen);
		}
		volatile MemNode  * pNode = m_FreeListArray[nDepth].GetNode(0);
#ifdef MEM_DBG
		DbgNewMem(nLen);
#endif
		if (pNode )
		{
			//m_nCurListCount -= LevelNodeCount(nLevel - nDepth);
			return pNode->pMemBlock;
		}
		else
		{
#ifdef MEM_DBG
			DbgGcNewMem(nUseLen);
#endif
			return ContainerT::SystemMemPoolT::GetInstance().NewMemory(nUseLen);
		}
	};
	bool DelMem(void * pMem, __int64 nLen) {
		unsigned int nSize = nLen >> BlockSizeLog2;
		if ((nLen&BlockSizeMask) == 0)
		{
			nSize--;
		}
		unsigned int nDepth = 0;
		for (; nSize != 0;)
		{
			nDepth++;
			nSize = nSize >> 1;
		}
		if ((m_nCurListCount < nListMaxCount) && (nDepth <= nLevel))
		{
			MemNode  * pNode = (MemNode  *)pMem;
			pNode->pMemBlock = pMem;
			pNode->nLen = nLen;
			m_FreeListArray[nDepth].AddNode(0,pNode);
			//m_nCurListCount += LevelNodeCount(nLevel - nDepth);
		}
		else
		{
			return ContainerT::SystemMemPoolT::GetInstance().DelMemory(pMem,nLen);
		}
#ifdef MEM_DBG
		DbgDelMem(nLen);
#endif
		return true;
	};
	//�����ͷ�FreeList
	void Clean()
	{
		
		for (unsigned int i = 0; i<nLevel;i++)
		{
			do
			{
				volatile MemNode  * pNode = m_FreeListArray[i].GetNode(0);
				if (pNode)
				{
#ifdef MEM_DBG
					DbgGcDelMem(pNode->nLen);
#endif
					ContainerT::SystemMemPoolT::GetInstance().DelMemory(pNode->pMemBlock,pNode->nLen);
				}
				else
				{
					break;
				}
			} while (true);
			
		}
		return;
	}
public:
	MemoryMgr_FreeList(){
		m_nCurListCount = 0;
	};
	~MemoryMgr_FreeList(){

	};
	typedef MemoryMgr_FreeList<PointInterfaceT, nBlockSizeLog2, nLevel, nListMaxCount, ContainerT> _Myt;
	/*
	static _Myt & GetInstance()
	{
		static _Myt _self;
		return _self;
	}*/
	
	//GCȫ�ֳ�ʼ�������ڴ�
	void * NewGc()
	{
		return this;
	}
	//ȫ��GCģʽʱ�ͷ�gc�ڴ�
	void DelGc(bool bRealClear)
	{
		Clean();
		return;
	}

	void ReArrange()
	{
		Clean();
		return;
	}
	bool TestInfo()
	{
		
		printf("MemoryMgr_FreeList sizeof(MemNode)=%u UsedCount = %u BlockSize=%u nLevel=%u\r\n",
			(int)sizeof(MemNode),m_nCurListCount, BlockSize, nLevel);
		

		//����ʹ����
		return true;
	}


	//��pool�з�����ͨ�ڴ�
	void * NewMemory(__int64 nLen) {
		return NewMem(nLen);
	};
	bool DelMemory(void * pMem, __int64 nLen) {
		return DelMem(pMem,nLen);
	};
};


template<typename _MemPoolT>
class GCContainer
{
public:
	//Խ��Ĺ�����Խ�߱�����Ȩ��
	unsigned int m_nManagerLevel;
	GCContainer() { m_nManagerLevel = 0; };
	~GCContainer() {};

	typedef GCContainer<_MemPoolT> _Myt;
	static _Myt & GetInstance()
	{
		static _Myt _self;
		return _self;
	}
	void RegistManager(unsigned int nManagerLevel)
	{
		m_nManagerLevel = nManagerLevel>m_nManagerLevel? nManagerLevel: m_nManagerLevel;
	}
	void ReleaseGC(unsigned int nManagerLevel,BOOL bRealFree=FALSE)
	{
		if (nManagerLevel >= m_nManagerLevel)
		{
			_MemPoolT::GetInstance().DelGc(bRealFree);
		}
	}
private:

};




