#pragma once

//************************************************************************ 
// 公司: 2012-2015, DM. Co., Ltd.
// 文件名: HeapAnslyze.h
// 作者: 叶树深 
// 版本: 1.0 
// 日期: 2015/10/12
// 功能描述: 分析heap信息
// 其他备注:
// 维护历史:
//************************************************************************ 

#ifdef TEST_MEM_LEAK

#ifndef _CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC
#endif

#include <stdlib.h>
#include <crtdbg.h>

class CMemLeakTest
{
public:
	_CrtMemState m_Begin;
	_CrtMemState m_End;
	_CrtMemState m_Rst;
	CMemLeakTest(){
		_CrtMemCheckpoint(&m_Begin);
	};
	~CMemLeakTest(){
		_CrtMemCheckpoint(&m_End);
		if (_CrtMemDifference(&m_Rst, &m_Begin, &m_End))
		{
			_CrtMemDumpStatistics(&m_Rst);
			_CrtDumpMemoryLeaks();
		}
			
	};
protected:

private:
};


#else

class CMemLeakTest
{
public:
	CMemLeakTest(){};
	~CMemLeakTest(){};
protected:
	
private:
};


#endif 

template<typename KeyNodeT,typename ValueT>
class dict
{
public:
	
	struct Node
	{
		//KeyNodeT	Key;
		typedef std::map<KeyNodeT, ValueT, less<KeyNodeT> > NodeMapT;
		ValueT		Value;
		NodeMapT	SubNodeMap;
	};
	Node m_head;
	typedef vector<KeyNodeT> _KeyT;
	//typedef Node::NodeMapT::iterator iterator;

	ValueT& operator [](const _KeyT & Key)
	{
		iterator itFind;
		Node::NodeMapT * SubMap = &m_head.SubNodeMap;
		for (unsigned int i=0;i<Key.size();i++)
		{
			itFind = SubMap->find(Key[i]);
			if (itFind != m_head.SubNodeMap.end())
			{
				//itFind=itFind->second.
				SubMap = &itFind->second;
				continue;
			}
		}
	}

	ValueT& operator [](const _KeyT Key)
	{

	}
	//find()


	dict(){};
	~dict(){};
protected:
	
private:
};


void GetHeapMemInfo1(HANDLE hHeap, PROCESS_HEAP_ENTRY & CurHeap);

struct _tagMemInfoSet
{
	
};

#define MEMTYPE_USED_BLOCK		1
#define MEMTYPE_RANGE			2
struct _tagMemInfo
{
	unsigned int nType;
	unsigned int nSize;
	vector_pvheap3<PVOID>	StackInfo;
};

struct _tagHeapInfoSet
{
	HANDLE			hHeap;
	unsigned int    nHeapType;
	unsigned int	nTotalSize;
	unsigned int	nTotalHeadSize;
	unsigned int	nUseBlockSize;
	unsigned int	nUseBlockCount;
	unsigned int	nRangeCount;
	unsigned int	nRangeSize;

	unsigned int	nRangeUnUsedCount;
	unsigned int	nNotCommittedSize;

	unsigned int	nNotUsedSize;
	unsigned int	nNotUsedCount;
	
	//unsigned int	nNotUseBlockCount;
	//map<PVOID,_tagMemInfo,less<PVOID>>			meminfo;
	typedef map_pvheap3<unsigned int, unsigned int, less<unsigned int>> MemInfoMapT;
	MemInfoMapT meminfo;

	_tagHeapInfoSet(){
		hHeap = NULL;
		nHeapType = 0;
		nTotalSize = 0;
		nTotalHeadSize = 0;

		nUseBlockCount = 0;
		nUseBlockSize = 0;
		
		nRangeCount = 0;
		nRangeSize = 0;

		nRangeUnUsedCount = 0;
		nNotCommittedSize = 0;

		nNotUsedSize = 0;
		nNotUsedCount = 0;
		//nNotUseBlockCount = 0;
		//nNotUseCommittedSize = 0;
		//nNotUseBlockSize = 0;
	}
	~_tagHeapInfoSet(){}
};

struct _tagHeapInfo
{
	typedef map_pvheap3<HANDLE, _tagHeapInfoSet, less<HANDLE> > HeapInfoMapT;
	HeapInfoMapT heapinfo;

};

extern void GetHeapMemInfo(HANDLE hHeap, PROCESS_HEAP_ENTRY & CurHeap, _tagHeapInfoSet & HeapInfo);
extern void GetHeapInfo(bool bCompact = false, bool bCheck = false, bool bBufferInfo = false);
extern void GetHeapInfo1(bool bCompact = false, bool bCheck = false, bool bBufferInfo = false);
extern void EnableMemLeakCheck();