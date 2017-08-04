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
#include "tool.hpp"
//2005.4.16 内存分配器




#ifdef RealPoint

//分配构造对象
#define YSS_NEW(Type,pPoint) pPoint=new Type();

#define YSS_DELETE(Type,pPoint) delete pPoint;pPoint=NULL;

#else
#define YSS_MALLOC(nSize,pPoint) NewVirtualMemory(pPoint,nSize);

#define YSS_NEW(Type,pPoint) YSS_MALLOC(sizeof(Type),pPoint);\
	Yss_Construct<Type>((Type *)(pPoint));\

#define YSS_FREE(pPoint)  DelVirtualMemory(pPoint);

#define YSS_DELETE(Type,pPoint) Yss_Destroy<Type>((Type *)(pPoint));\
	YSS_FREE(pPoint);\

#endif

//分配删除内存
#define YSS_MALLC_MEM(size) ((void *)(new char[(size)]))
#define YSS_DELETE_MEM(pMem) (delete [] pMem)


//调用构造函数
template<class T>
class Yss_Construct
{
public:
	Yss_Construct(T* pData){new (pData) T();};
	~Yss_Construct(){};
};

template<class T>
class Yss_Destroy
{
public:
	Yss_Destroy(T * pData){pData->~T();};
	~Yss_Destroy(){};
protected:

private:
};

template<typename PointInterfaceT>
class MemoryMgrInterface
{
public:
	MemoryMgrInterface(){};
	virtual ~MemoryMgrInterface(){};

	template<typename T>
	MemoryMgrInterface(T& _X)
	{
		//this->__vfptr = _X.__vfptr;
	};
	template<typename T>
	void operator =(T& _X)
	{
		this->vptr = _X.vptr;
	}
	template<typename T>
	void operator =(T _X)
	{
		this->vptr = _X.vptr;
	}
	//GC全局初始化分配内存
	virtual void * NewGc()
	{
		return NULL;
	}
	//全局GC模式时释放gc内存
	virtual void DelGc(bool bRealClear)
	{
		return;
	}
	//GC内存重整
	virtual void ReArrange()
	{
		return;
	}

	//分组GC
	virtual void * NewGc(unsigned int nGroupID)
	{
		return NULL;
	}
	//分组GC
	virtual void DelGc(unsigned int nGroupID, bool bRealClear)
	{
		return ;
	}


	//从pool中分配智能指针型内存
	virtual bool NewVirtualMemory(IN OUT PointInterfaceT & pMem, __int64  nLen){ YSS_ASSERT(TRUE); return false; };
	virtual bool DelVirtualMemory(PointInterfaceT & pMem) { YSS_ASSERT(TRUE); return false; };

	//从pool中分配普通内存
	virtual void * NewMemory( __int64 nLen) { YSS_ASSERT(TRUE); return NULL; };
	virtual bool DelMemory(void * pMem, __int64 nLen) { YSS_ASSERT(TRUE); return false; };

	//测试接口
	virtual bool TestInfo(){ return true; };

	//得到真实指针
	virtual void * MapGetAddr(IN PointInterfaceT * pMem) { YSS_ASSERT(TRUE); return NULL; };

	//将物理指针转化为智能指针
	virtual bool GetVPFromRealAddr(IN OUT PointInterfaceT * pMem, IN void * pAddr){ YSS_ASSERT(TRUE); return false; };

protected:
	
private:
};


template<typename _IndexType>
class PointInterfaceForMemoryMgr
{
public:
	PointInterfaceForMemoryMgr(){};
	~PointInterfaceForMemoryMgr(){};
	typedef  _IndexType PointIndexType;
	PointIndexType m_nIndex;
protected:

private:
};



typedef __int64 IndexType;
extern MemoryMgrInterface< PointInterfaceForMemoryMgr<IndexType> > * g_pMemoryMgr[];

//封装OS提供的内存分配接口
template<typename PointInterfaceT, int nMemMgrName,size_t nInitSize=0>
class MemoryMgr_OS : public MemoryMgrInterface<PointInterfaceT>
{
public:
	HANDLE m_hHeap;
	MemoryMgr_OS(){ m_hHeap = NULL; };
public:
	typedef MemoryMgr_OS<PointInterfaceT, nMemMgrName, nInitSize> _Myt;
	static _Myt & GetInstance()
	{
		static _Myt _self;
		return _self;
	}
	//GC全局初始化分配内存
	
	void * NewGc()
	{
		m_hHeap = HeapCreate(HEAP_GENERATE_EXCEPTIONS, nInitSize, 0);
		if (m_hHeap == INVALID_HANDLE_VALUE)
		{
			m_hHeap = HeapCreate(HEAP_GENERATE_EXCEPTIONS, 0, 0);
		}
		ULONG  HeapFragValue = 2;

		if (!HeapSetInformation(m_hHeap,
			HeapCompatibilityInformation,
			&HeapFragValue,
			sizeof(HeapFragValue))
			)
		{
			//Error(_T("HeapSetInformation Fail ERR=(%d)\n"), GetLastError());
			//return NULL;
		}
		return this;
	}
	//全局GC模式时释放gc内存
	void DelGc(bool bRealClear)
	{
		
		if (m_hHeap)
		{
			HeapDestroy(m_hHeap);
		}
		
		return;
	}
	~MemoryMgr_OS(){ DelGc(TRUE); };


	//从pool中分配普通内存
	void * NewMemory(__int64 nLen) {
		if (m_hHeap == NULL)
		{
			//*(char *)0 = 0;
			NewGc();
		}
		//HeapLock(m_Heap);
		void * pMem = ::HeapAlloc(m_hHeap, HEAP_GENERATE_EXCEPTIONS | HEAP_ZERO_MEMORY, nLen);
		//HeapUnlock(m_Heap);
		if (pMem == NULL)
		{
			*(char *)0 = 0;
		}
		return pMem;
	};
	bool TestInfo()
	{
		printf("MemoryMgr_OS m_hHeap = %x\r\n", m_hHeap);
		return true;
	}
	bool DelMemory(void * pMem, __int64 nLen) {
		::HeapFree(m_hHeap, HEAP_GENERATE_EXCEPTIONS | HEAP_ZERO_MEMORY, (LPVOID)pMem);
		return true;
	};

protected:

private:
};


//封装OS提供的内存分配接口
template<typename PointInterfaceT>
class MemoryMgr_OS_TLS_Proxy : public MemoryMgrInterface<PointInterfaceT>
{
public:
	HANDLE m_hHeap;
	MemoryMgr_OS_TLS_Proxy(){ m_hHeap = NULL; };

	//GC全局初始化分配内存

	void * NewGc()
	{
		m_hHeap = HeapCreate(HEAP_GENERATE_EXCEPTIONS, nInitSize, 0);
		if (m_hHeap == INVALID_HANDLE_VALUE)
		{
			m_hHeap = HeapCreate(HEAP_GENERATE_EXCEPTIONS, 0, 0);
		}
		ULONG  HeapFragValue = 2;

		if (!HeapSetInformation(m_hHeap,
			HeapCompatibilityInformation,
			&HeapFragValue,
			sizeof(HeapFragValue))
			)
		{
			//Error(_T("HeapSetInformation Fail ERR=(%d)\n"), GetLastError());
			//return NULL;
		}
		return this;
	}
	//全局GC模式时释放gc内存
	void DelGc(bool bRealClear)
	{

		if (m_hHeap)
		{
			HeapDestroy(m_hHeap);
		}

		return;
	}
	~MemoryMgr_OS_TLS_Proxy(){ DelGc(TRUE); };


	//从pool中分配普通内存
	void * NewMemory(__int64 nLen) {
		if (m_hHeap == NULL)
		{
			//*(char *)0 = 0;
			NewGc();
		}
		//HeapLock(m_Heap);
		void * pMem = ::HeapAlloc(m_hHeap, HEAP_GENERATE_EXCEPTIONS | HEAP_ZERO_MEMORY, nLen);
		//HeapUnlock(m_Heap);
		if (pMem == NULL)
		{
			*(char *)0 = 0;
		}
		return pMem;
	};
	bool TestInfo()
	{
		printf("MemoryMgr_OS m_hHeap = %x\r\n", m_hHeap);
		return true;
	}
	bool DelMemory(void * pMem, __int64 nLen) {
		::HeapFree(m_hHeap, HEAP_GENERATE_EXCEPTIONS | HEAP_ZERO_MEMORY, (LPVOID)pMem);
		return true;
	};

protected:

private:
};


template<typename PointInterfaceT, int nMemMgrName >
class MemoryMgr_OS_VirtualMem : public MemoryMgrInterface<PointInterfaceT>
{
public:
	unsigned int m_nMemConut;
	MemoryMgr_OS_VirtualMem(){ m_nMemConut = 0; };

public:
	typedef MemoryMgr_OS_VirtualMem<PointInterfaceT, nMemMgrName> _Myt;
	static _Myt & GetInstance()
	{
		static _Myt _self;
		return _self;
	}
	//GC全局初始化分配内存

	void * NewGc()
	{
		return NULL;
	}
	//全局GC模式时释放gc内存
	void DelGc(bool bRealClear)
	{

		return;
	}
	~MemoryMgr_OS_VirtualMem(){ DelGc(TRUE); };


	//从pool中分配普通内存
#define MemG
	void * NewMemory(__int64 nLen) {
		//HeapLock(m_Heap);
		void * pMem = ::VirtualAlloc(NULL, nLen, MEM_COMMIT|MEM_RESERVE, PAGE_READWRITE);
		m_nMemConut++;
		return pMem;
	};
	bool TestInfo()
	{
		printf("MemoryMgr_OS_VirtualMem m_hHeap\r\n");
		return true;
	}
	bool DelMemory(void * pMem, __int64 nLen) {
		//::VirtualFree(pMem, nLen, MEM_DECOMMIT);
		::VirtualFree(pMem, 0, MEM_RELEASE);
		return true;
	};

protected:

private:
};









