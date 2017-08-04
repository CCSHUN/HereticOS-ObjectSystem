#pragma once
//************************************************************************ 
// 公司: 2012-2015, DM. Co., Ltd.
// 文件名: stlallocator.h
// 作者: 叶树深 
// 版本: 1.0 
// 日期: 2015/10/27
// 功能描述: stl allocator封装
// 其他备注:
// 维护历史:
//************************************************************************ 

#include "yssmemory.hpp"


struct _tagTLSHeapInfo
{
	unsigned int nConCount[8];
	MemoryMgr_OS<PointInterfaceForMemoryMgr<IndexType>, 0,0> m_Heap;
};

template<class T, typename MemMgrType>
class yss_allocator : public std::allocator<T>
{

public:
	template<class RebindT>
	struct rebind
	{
		typedef yss_allocator<RebindT, MemMgrType> other;
	};

	//HANDLE m_Heap;

	yss_allocator() {

		//m_Heap = (HANDLE)&g_pMemoryMgr[nMemMgrType];
		
	}

	yss_allocator(yss_allocator<T, MemMgrType> const& _X) {
		//m_Heap = _X.m_Heap;
	}


	yss_allocator<T, MemMgrType>& operator=(yss_allocator<T, MemMgrType> const& _X)
	{
		//m_Heap = _X.m_Heap;
		return (*this);
	}

	


	//_Container_proxy 用这个构造。
	template<class Other>
	yss_allocator(yss_allocator<Other, MemMgrType> const& _X)
	{
		//m_Heap = g_ShareHeap->gYss_share_allocator_Heap;
		//m_Heap = _X.m_Heap;
	}

	


	pointer allocate(size_type count)
	{
		//HANDLE gHead = ::GetProcessHeap();
		//int n = sizeof(T);
		
		//HeapLock(m_Heap);
		pointer ret = (pointer)MemMgrType::GetInstance().NewMemory(count*sizeof(T));
		//HeapUnlock(m_Heap);
		//g_pMemoryMgr[nMemMgrType].
		if (ret == NULL)
		{
			*(char *)0 = 0;
		}

		return (pointer)ret;
	}

	void deallocate(pointer ptr, size_type count)
	{
		//HANDLE gHead = ::GetProcessHeap();


		MemMgrType::GetInstance().DelMemory(ptr, count*sizeof(T));
		//HeapLock(m_Heap);
		//::HeapFree(m_Heap, HEAP_GENERATE_EXCEPTIONS | HEAP_ZERO_MEMORY, (LPVOID)ptr);
		//HeapUnlock(m_Heap);
		return;
	}
};

template<class T, int nHeapIndex>
class yss_allocator_tls : public std::allocator<T>
{

public:
	template<class RebindT>
	struct rebind
	{
		typedef yss_allocator_tls<RebindT, nHeapIndex> other;
	};

	//HANDLE m_Heap;

	yss_allocator_tls() {

		//m_Heap = (HANDLE)&g_pMemoryMgr[nMemMgrType];
		//_tagTLSHeapInfo * pInfo=::
		//_tagTLSHeapInfo * pInfo = (_tagTLSHeapInfo *)::TlsGetValue(g_hTlsForHeap);
		//pInfo->nConCount[0]++;
	}

	yss_allocator_tls(yss_allocator_tls<T, nHeapIndex> const& _X) {
		//m_Heap = _X.m_Heap;
		_tagTLSHeapInfo * pInfo = (_tagTLSHeapInfo *)::TlsGetValue(g_hTlsForHeap);
		pInfo->nConCount[1]++;
	}


	yss_allocator_tls<T, nHeapIndex>& operator=(yss_allocator_tls<T, nHeapIndex> const& _X)
	{
		//m_Heap = _X.m_Heap;
		_tagTLSHeapInfo * pInfo = (_tagTLSHeapInfo *)::TlsGetValue(g_hTlsForHeap);
		pInfo->nConCount[2]++;
		return (*this);
	}



	//_Container_proxy 用这个构造。
	template<class Other>
	yss_allocator_tls(yss_allocator_tls<Other, nHeapIndex> const& _X)
	{
		//m_Heap = g_ShareHeap->gYss_share_allocator_Heap;
		//m_Heap = _X.m_Heap;
		_tagTLSHeapInfo * pInfo = (_tagTLSHeapInfo *)::TlsGetValue(g_hTlsForHeap);
		pInfo->nConCount[3]++;
	}




	pointer allocate(size_type count)
	{
		//HANDLE gHead = ::GetProcessHeap();
		//int n = sizeof(T);
		
		//HeapLock(m_Heap);
		_tagTLSHeapInfo * pInfo = (_tagTLSHeapInfo *)::TlsGetValue(g_hTlsForHeap);
		pointer ret = (pointer)pInfo->m_Heap.NewMemory(count*sizeof(T));
		pInfo->nConCount[4]++;
		//HeapUnlock(m_Heap);
		//g_pMemoryMgr[nMemMgrType].
		if (ret == NULL)
		{
			*(char *)0 = 0;
		}

		return (pointer)ret;
	}

	void deallocate(pointer ptr, size_type count)
	{
		//HANDLE gHead = ::GetProcessHeap();
		_tagTLSHeapInfo * pInfo = (_tagTLSHeapInfo *)::TlsGetValue(g_hTlsForHeap);
		pInfo->m_Heap.DelMemory(ptr, count*sizeof(T));
		pInfo->nConCount[5]++;
		//HeapLock(m_Heap);
		//::HeapFree(m_Heap, HEAP_GENERATE_EXCEPTIONS | HEAP_ZERO_MEMORY, (LPVOID)ptr);
		//HeapUnlock(m_Heap);
		return;
	}
};
