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


//2002.6 叶树深 字符串基本功能库
#pragma warning(disable:4996)


#ifdef _LINUX_
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <wchar.h>
#include "WindowsLayerForLinux.h"
#define ALIGNED(_align) __attribute__((aligned(_align)))
#define CACHE_ALIGN_HEAD 
#define CACHE_ALIGN_END ALIGNED(__CACHE_LINE__)

#include <unistd.h>

#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)
#define LocalThreadObject thread_local
#define PRAGMA(x) _Pragma(x)
#define OPTIMIZE_OFF \
_Pragma("GCC push_options")\
_Pragma("GCC optimize (\"O0\")")\

#define OPTIMIZE_OFF_END _Pragma("GCC pop_options")

//#define prefetch(x)  //prefetch3(x)
//#define prefetch0(x)  prefetch0
//#define prefetch1(x)  __builtin_prefetch(x,0,2)
//#define prefetch2(x)  __builtin_prefetch(x,0,3)
//#define prefetch(x)  __builtin_prefetch(x,0,3)

static inline void prefetch0(const volatile void *p)
{
	asm volatile ("prefetcht0 %[p]" : : [p] "m" (*(const volatile char *)p));
}

static inline void prefetch1(const volatile void *p)
{
	asm volatile ("prefetcht1 %[p]" : : [p] "m" (*(const volatile char *)p));
}

static inline void prefetch2(const volatile void *p)
{
	asm volatile ("prefetcht2 %[p]" : : [p] "m" (*(const volatile char *)p));
}

static inline void prefetch_static(const volatile void *p)
{
	asm volatile ("prefetchnta %[p]" : : [p] "m" (*(const volatile char *)p));
}
#define prefetch_object_array(_obj, _op) for (int _prefetch_object_pos = 0; _prefetch_object_pos < sizeof(_obj); _prefetch_object_pos += __CACHE_LINE__) { _op((void*)((((char *)(&_obj[0]))) + _prefetch_object_pos)); };
#define prefetch_object(_obj, _op) for (int _prefetch_object_pos = 0; _prefetch_object_pos < sizeof(_obj); _prefetch_object_pos += __CACHE_LINE__) { _op((void*)((((char *)(&_obj))) + _prefetch_object_pos)); };

//__thread
#else
//#include "stdafx.h"
#include "windows.h"
#define ALIGNED(_align) __declspec(align(_align))
#define CACHE_ALIGN_HEAD ALIGNED(__CACHE_LINE__)
#define CACHE_ALIGN_END 
#include <tchar.h>
#include "stdio.h"
#include "stdlib.h"
#include <string.h>
#define likely(x)  x
#define unlikely(x)  x
//#define LocalThreadObject __declspec(thread)
#define LocalThreadObject thread_local static
#define PRAGMA(x) __pragma(x)

#define OPTIMIZE_OFF PRAGMA("optimize(\"\", off)")


#define OPTIMIZE_OFF_END PRAGMA("optimize(\"\", on)")

#define prefetch(x)
#define prefetch0(x)  
#define prefetch1(x)  
#define prefetch2(x)  
#define prefetch3(x)  
#define prefetch_static(x)
#define prefetch_object(_obj, _op)
#define prefetch_object_array(_obj, _op)
#endif




#include <map>
#include <string>
#include <vector>
#include <list>
#include <unordered_map>
using namespace std;





#ifdef _UNICODE
#define sprintf_t swprintf 

#define gets_t _getws
#define gets_s_t _getws_s 
#define printf_t wprintf
#define sprintf_s_t swprintf_s
#define fopen_t _wfopen
#define strcpy_t wcscpy
#define strcpy_s_t wcscpy_s
#define strcat_t wcscat
#define strcat_s_t wcscat_s

#define strlen_t wcslen 
#define atoi_t	_wtoi
#define atoi64_t	_wtoi64
#define itoa_t		_itow
#define i64toa_t		_i64tow
#define ui64toa_t		_ui64tow
#define sscanf_t		swscanf
#define sscanf_s_t		swscanf_s
#define strlwr_s_t		_wcslwr_s
#define strupr_s_t		_wcsupr_s
#define scanf_t			wscanf
#define scanf_s_t		wscanf_s

#define strstr_t			wcsstr
#define strrchr_t			wcsrchr
#define stricmp_t		wcsicmp
#define atol_t			_wtol
#define strcmp_t	wcscmp
#define vsprintf_s_t vswprintf_s
#define strchr_t   wcschr

#define fopen_t _wfopen
#define fgets_t _wfgets
#ifdef _LINUX_
#define popen_t	_wpopen
#else
#define popen_t	_wpopen
#endif

#else
#define sprintf_t sprintf 

#define printf_t printf
#define gets_t gets
#define gets_s_t gets_s
#define sscanf_t		sscanf
#define sscanf_s_t		sscanf_s
#define scanf_t			scanf
#define scanf_s_t		scanf_s

#define sprintf_s_t sprintf_s
#define strcpy_t strcpy
#define strcpy_s_t strcpy_s
#define strcat_t strcat
#define strcat_s_t strcat_s

#define strlen_t strlen
#define atoi_t	atoi
#define atoi64_t	_atoi64
#define itoa_t		_itoa
#define i64toa_t		_i64toa
#define ui64toa_t		_ui64toa
#define strstr_t		strstr
#define strrchr_t			strrchr
#define stricmp_t	stricmp
#define atol_t			atol
#define strcmp_t	strcmp
#define vsprintf_s_t vsprintf_s
#define fopen_t fopen
#define strchr_t   strchr

#define fopen_t fopen

#define strlwr_s_t		_strlwr_s
#define strupr_s_t		_strupr_s

#ifdef _LINUX_
#define popen_t	popen
#define fgets_t fgets
#define pclose pclose
#else
#define popen_t	_popen
#define fgets_t _fgets
#define pclose _pclose
#endif


#endif

#include "./SmartSTL/stlallocator.h"
typedef MemoryMgr_OS<PointInterfaceForMemoryMgr<IndexType>, 0> MemoryMgr_Heap;
typedef MemoryMgr_OS_VirtualMem<PointInterfaceForMemoryMgr<IndexType>, 0> MemoryMgr_OSVm;
//class Container_DefaultT;

#include "./SmartSTL/SystemContainer.h"

typedef SystemContainer<MemoryMgr_Heap,int, int,int> Container_BaseT;


typedef MemoryMgr_OS<PointInterfaceForMemoryMgr<IndexType>, 1> MemoryMgr_Heap1;
typedef MemoryMgr_OS_VirtualMem<PointInterfaceForMemoryMgr<IndexType>, 1> MemoryMgr_OSVm1;
typedef MemoryMgr_FreeList<PointInterfaceForMemoryMgr<IndexType>, 6, 18, 4096, Container_BaseT> MemoryMgr_FreeList1T;
typedef MemoryMgr_FreeList<PointInterfaceForMemoryMgr<IndexType>, 6, 18, 4096, Container_BaseT> MemoryMgr_FreeList2T;
typedef MemoryMgr_StaticGC<PointInterfaceForMemoryMgr<IndexType>, Container_BaseT, 4 * 1024 * 1024, 256> MemoryMgr__StaticGC;
typedef MemoryMgr_StaticGC<PointInterfaceForMemoryMgr<IndexType>, Container_BaseT, 4 * 1024 * 1024, 512> MemoryMgr__StaticGC_Tmp;

typedef SystemContainer<MemoryMgr_Heap, MemoryMgr_FreeList1T, MemoryMgr__StaticGC, MemoryMgr__StaticGC_Tmp> Container_DefaultT;

template < class _Kty, class _Ty, class _Pr = less<_Kty> >
using map_gc = map<_Kty, _Ty, _Pr, yss_allocator<_Ty, MemoryMgr__StaticGC>  >;

template < class _Kty, class _Ty, class _Pr = less<_Kty> >
using map_freelist = map<_Kty, _Ty, _Pr, yss_allocator<_Ty, MemoryMgr_FreeList1T>  >;

template<class _Ty >
using vector_gc = vector<_Ty, yss_allocator<_Ty, MemoryMgr__StaticGC>>;

template<class _Ty >
using vector_freelist = vector<_Ty, yss_allocator<_Ty, MemoryMgr_FreeList1T>>;

template<class _Alloc, class _Elem = TCHAR, class _Traits = char_traits<_Elem>>
using tstring_pool = std::basic_string<_Elem, std::char_traits<_Elem>, _Alloc  >;
//MEMMGR_TYPE_FREELIST
//MEMMGR_TYPE_STATICGC
//MEMMGR_TYPE_STATICGC_TMP
typedef tstring_pool<yss_allocator<wchar_t, MemoryMgr_FreeList2T >, wchar_t> wstring_tmp;
typedef tstring_pool<yss_allocator<char, MemoryMgr_FreeList2T >, char  > string_tmp;
typedef tstring_pool<yss_allocator<TCHAR, MemoryMgr_FreeList2T >> tstring_tmp;
//typedef tstring tstring_tmp;
typedef tstring_pool<yss_allocator<TCHAR, MemoryMgr_FreeList2T >> tstring;

//typedef std::basic_string<TCHAR, std::char_traits<TCHAR>  > tstring;
//typedef std::basic_string<TCHAR, std::char_traits<TCHAR>  > tstring_tmp;
/*
template<class _Alloc, class _Elem , class _Traits >
template<typename Pool1T>
tstring_pool<_Alloc, _Elem, _Traits> &  tstring_pool<_Alloc, _Elem, _Traits>::operator =(tstring_pool<Pool1T, _Elem, _Traits> & str)
{
	*this = str.c_str();
	return *this;
}
*/

#ifdef _DLL_SHARE_OBJECT

#include <memory>  
#include ".\sharemem\ShareObject.h"

//内存池数量
#define HEAP_COUNT	5
struct  ShareHeap
{
	HANDLE gYss_share_allocator_Heap[HEAP_COUNT];
	HANDLE gYss_share_allocator_ProcessHeap;
};


extern  CShareObject<ShareHeap> g_ShareHeap;
extern  ShareHeap * g_pShareHeap;
extern BOOL YssAllocatorHeapCreate(HANDLE hHeap);

template<class T, int nHeapIndex>
class yss_share_allocator : public std::allocator<T>
{

public:
	template<class RebindT>
	struct rebind
	{
		typedef yss_share_allocator<RebindT, nHeapIndex> other;
	};

	HANDLE m_Heap;

	yss_share_allocator() {

		m_Heap = g_ShareHeap->gYss_share_allocator_Heap[nHeapIndex];
	}

	yss_share_allocator(yss_share_allocator<T, nHeapIndex> const& _X) {
		m_Heap = _X.m_Heap;
	}

	
	yss_share_allocator<T, nHeapIndex>& operator=(yss_share_allocator<T, nHeapIndex> const& _X)
	{
		m_Heap = _X.m_Heap;
		return (*this);
	}

	/*bool operator ==(yss_share_allocator<T> const& _X)
	{
		m_Heap == _X.m_Heap;
		return (m_Heap == _X.m_Heap)?true:false;
	}
	
	template<class Other>
	yss_share_allocator()
	{
	if (gYss_share_allocator_Heap == NULL)
	{
	YssAllocatorHeapCreate(NULL);
	}

	m_Heap = gYss_share_allocator_Heap;
	}
	*/

	
	//_Container_proxy 用这个构造。
	template<class Other>
	yss_share_allocator(yss_share_allocator<Other, nHeapIndex> const& _X)
	{
		//m_Heap = g_ShareHeap->gYss_share_allocator_Heap;
		m_Heap = _X.m_Heap;
	}

	/*
	template<class Other>
	yss_share_allocator<Other>& operator = (yss_share_allocator<Other> const& _X)
	{
	//m_Heap = _X.m_Heap;
	return (*this);
	}
	*/
	

	pointer allocate(size_type count)
	{
		//HANDLE gHead = ::GetProcessHeap();
		//int n = sizeof(T);
		if (m_Heap == NULL)
		{
			*(char *)0=0;
		}
		//HeapLock(m_Heap);
		pointer ret=(pointer)::HeapAlloc(m_Heap, HEAP_GENERATE_EXCEPTIONS | HEAP_ZERO_MEMORY, count*sizeof(T));
		//HeapUnlock(m_Heap);
		if (ret == NULL)
		{
			*(char *)0 = 0;
		}

		return (pointer) ret;
	}

	void deallocate(pointer ptr, size_type count)
	{
		//HANDLE gHead = ::GetProcessHeap();
		if (m_Heap == NULL)
		{
			*(char *)0=0;
		}
		//HeapLock(m_Heap);
		::HeapFree(m_Heap, HEAP_GENERATE_EXCEPTIONS | HEAP_ZERO_MEMORY, (LPVOID)ptr);
		//HeapUnlock(m_Heap);
		return;
	}
};

#define HEAP_ADDR_SHARE	0
#define HEAP_ADDR_PVHEAP	1
#define HEAP_ADDR_PVHEAP1	2
#define HEAP_ADDR_PVHEAP2	3
#define HEAP_ADDR_PVHEAP3	4


typedef basic_string<char, char_traits<char>, yss_share_allocator<char, HEAP_ADDR_SHARE> > string_share;
typedef basic_string<wchar_t, char_traits<wchar_t>, yss_share_allocator<wchar_t, HEAP_ADDR_SHARE> > wstring_share;


typedef basic_string<char, char_traits<char>, yss_share_allocator<char, HEAP_ADDR_PVHEAP> > string_pvheap;
typedef basic_string<wchar_t, char_traits<wchar_t>, yss_share_allocator<wchar_t, HEAP_ADDR_PVHEAP> > wstring_pvheap;

typedef basic_string<char, char_traits<char>, yss_share_allocator<char, HEAP_ADDR_PVHEAP1> > string_pvheap1;
typedef basic_string<wchar_t, char_traits<wchar_t>, yss_share_allocator<wchar_t, HEAP_ADDR_PVHEAP1> > wstring_pvheap1;

typedef basic_string<char, char_traits<char>, yss_share_allocator<char, HEAP_ADDR_PVHEAP2> > string_pvheap2;
typedef basic_string<wchar_t, char_traits<wchar_t>, yss_share_allocator<wchar_t, HEAP_ADDR_PVHEAP2> > wstring_pvheap2;

typedef basic_string<char, char_traits<char>, yss_share_allocator<char, HEAP_ADDR_PVHEAP3> > string_pvheap3;
typedef basic_string<wchar_t, char_traits<wchar_t>, yss_share_allocator<wchar_t, HEAP_ADDR_PVHEAP3> > wstring_pvheap3;


#ifdef _UNICODE
typedef wstring_share tstring_share;
typedef wstring_pvheap tstring_pvheap;
typedef wstring_pvheap1 tstring_pvheap1;
typedef wstring_pvheap2 tstring_pvheap2;
typedef wstring_pvheap3 tstring_pvheap3;


#else

typedef string_share tstring_share;
typedef string_pvheap tstring_pvheap;
typedef string_pvheap1 tstring_pvheap1;
typedef string_pvheap2 tstring_pvheap2;
typedef string_pvheap3 tstring_pvheap3;

#endif

/*

template<class _Ty >
struct vector_share_rebind
{
	typedef vector<_Ty, yss_share_allocator<_Ty>> other;
};*/

#ifndef USE_STLVEC
template<class _Ty >
using vector_share = vector<_Ty, yss_share_allocator<_Ty, HEAP_ADDR_SHARE>>;


template<class _Ty >
using vector_pvheap = vector<_Ty, yss_share_allocator<_Ty, HEAP_ADDR_PVHEAP>>;

template<class _Ty >
using vector_pvheap1 = vector<_Ty, yss_share_allocator<_Ty, HEAP_ADDR_PVHEAP1>>;

template<class _Ty >
using vector_pvheap2 = vector<_Ty, yss_share_allocator<_Ty, HEAP_ADDR_PVHEAP2>>;

template<class _Ty >
using vector_pvheap3 = vector<_Ty, yss_share_allocator<_Ty, HEAP_ADDR_PVHEAP3>>;


template<class _Kty, class _Ty, class _Hasher = hash<_Kty>,class _Keyeq = equal_to<_Kty> >
using unordered_map_pvheap = unordered_map<_Kty, _Ty, _Hasher, _Keyeq, yss_share_allocator<pair<const _Kty, _Ty>, HEAP_ADDR_PVHEAP> >;


/*
	template<class _Kty,
class _Ty,
class _Hasher = hash<_Kty>,
class _Keyeq = equal_to<_Kty>,
class _Alloc = allocator<pair<const _Kty, _Ty> > >
class unordered_map*/


#else

template<class _Ty >
using vector_share = vector<_Ty>;

#endif


template < class _Kty, class _Ty, class _Pr = less<_Kty> >
using map_share = map<_Kty, _Ty, _Pr, yss_share_allocator<_Ty, HEAP_ADDR_SHARE>  >;

template < class _Kty, class _Ty, class _Pr = less<_Kty> >
using map_pvheap = map<_Kty, _Ty, _Pr, yss_share_allocator<_Ty, HEAP_ADDR_PVHEAP>  >;

template < class _Kty, class _Ty, class _Pr = less<_Kty> >
using map_pvheap1 = map<_Kty, _Ty, _Pr, yss_share_allocator<_Ty, HEAP_ADDR_PVHEAP1>  >;

template < class _Kty, class _Ty, class _Pr = less<_Kty> >
using map_pvheap2 = map<_Kty, _Ty, _Pr, yss_share_allocator<_Ty, HEAP_ADDR_PVHEAP2>  >;

template < class _Kty, class _Ty, class _Pr = less<_Kty> >
using map_pvheap3 = map<_Kty, _Ty, _Pr, yss_share_allocator<_Ty, HEAP_ADDR_PVHEAP3>  >;




#endif







class CMyString
{
public:
	typedef enum
	{
		Ansi,
		Unicode,
	}StringType;

	StringType m_type;
	void * m_pStr;

	StringType m_reftype;
	void * m_refStr;
	size_t m_nRefBufLen;

	CMyString()
	{
		m_pStr=NULL;
		
	};
	~CMyString()
	{
		if(m_pStr)
		{
			delete m_pStr;
		}
	}
	CMyString(char * pStr,size_t nRefBufLen)
	{
		m_refStr=pStr;
		m_reftype=Ansi;
		m_nRefBufLen=nRefBufLen;
		m_pStr=NULL;
	}
	CMyString(wchar_t * pStr,size_t nRefBufLen)
	{
		m_refStr= (void*)pStr;
		m_reftype=Unicode;
		m_nRefBufLen=nRefBufLen;
		m_pStr=NULL;
	}

	CMyString(const char * pStr)
	{
		m_refStr = (void*)pStr;
		m_reftype = Ansi;
		m_nRefBufLen = strlen(pStr);
		m_pStr = NULL;
	}

	CMyString(const wchar_t * pStr )
	{
		m_refStr = (void*)pStr;
		m_reftype = Unicode;
		m_nRefBufLen = wcslen(pStr)*2;
		m_pStr = NULL;
	}
	CMyString( char * pStr)
	{
		m_refStr = (void*)pStr;
		m_reftype = Ansi;
		m_nRefBufLen = strlen(pStr);
		m_pStr = NULL;
	}

	CMyString( wchar_t * pStr)
	{
		m_refStr = (void*)pStr;
		m_reftype = Unicode;
		m_nRefBufLen = wcslen(pStr) * 2;
		m_pStr = NULL;
	}

	CMyString(CMyString & pStr)
	{
		m_refStr=pStr.m_refStr;
		m_reftype=pStr.m_reftype;
		m_nRefBufLen=pStr.m_nRefBufLen;
		m_pStr=NULL;
	}

	template<typename StringT>
	CMyString(StringT & szAnsiString)
	{
		m_refStr=(void *)szAnsiString.c_str();
		m_reftype=Ansi;
		m_nRefBufLen=szAnsiString.length();
		m_pStr=NULL;
	}

	
	/*CMyString & freeme()
	{
		if(m_pStr)
		{
			delete m_pStr;
			m_pStr=NULL;
		}
		return *this;
	}*/
	operator char *()
	{
		if(m_reftype==Ansi)
		{
			return (char *)m_refStr;
		}
		else
		{
			if(m_pStr)
			{
				return (char *) m_pStr;
			}
			else
			{
				m_pStr=new BYTE[m_nRefBufLen+2];
				memset(m_pStr,0,m_nRefBufLen+2);
				m_type=Ansi;
				setlocale(LC_CTYPE,"");
				m_nRefBufLen=wcstombs((char *)m_pStr,(wchar_t *)m_refStr,m_nRefBufLen);

				return (char *) m_pStr;
			}
		}
	}
	operator wchar_t *()
	{
		if(m_reftype==Unicode)
		{
			return (wchar_t *)m_refStr;
		}
		else
		{
			if(m_pStr)
			{
				return (wchar_t *) m_pStr;
			}
			else
			{
				m_pStr=new BYTE[m_nRefBufLen*2+2];
				memset(m_pStr,0,m_nRefBufLen*2+2);
				m_type=Unicode;
				
				m_nRefBufLen=mbstowcs((wchar_t *)m_pStr,(char *)m_refStr,m_nRefBufLen)*sizeof(wchar_t);
				return (wchar_t *) m_pStr;
			}
		}
	}

	operator string  ()
	{
		return string((char *)this);
	}
	operator wstring ()
	{
		return wstring((wchar_t *)this);
	}
protected:

private:
};


template<typename ValType>
ValType AtoVal(TCHAR * pszVal,unsigned int nBit,ValType)
{
	__int64 RstVal=0;
	__int64 CurVal=0;
	for(int pos=0;pszVal[pos];pos++)
	{
		if(pszVal[pos]>='0'&&pszVal[pos]<='9')
		{
			CurVal=pszVal[pos]-'0';
		}else if((pszVal[pos]|0x20)>='a'&&(pszVal[pos]|0x20)<='z')
		{
			CurVal=(pszVal[pos]|0x20)-'a'+10;
		}

		RstVal=RstVal*nBit+CurVal;
	}
	return *((ValType*)((BYTE*)&RstVal));
}

static void EncodeHex(BYTE * pData,unsigned int nLen,tstring & szOut)
{
	TCHAR *pHexTab=_T("0123456789ABCDEF");
	TCHAR * pOut=new TCHAR[nLen*2+1];
	for(unsigned int i=0;i<nLen;i++)
	{
		pOut[2*i]=pHexTab[((pData[i]&0xf0)>>4)];
		pOut[2*i+1]=pHexTab[pData[i]&0xf];
		pOut[2*i+2]=0;
	}
	szOut=pOut;
	delete [] pOut;
}

static BOOL DecodeHex(TCHAR * pData,BYTE * pOutData,IN unsigned int  nOutDataLen)
{
	BYTE nLow,nHigh;
	unsigned int nCount=nOutDataLen;
	for(unsigned int i=0;pData[i]!=0;i+=2)
	{
		if((pData[i]>='0')&&(pData[i]<='9'))
		{
			nHigh=pData[i]-'0';
		}else if(((pData[i]|0x20)>='a')&&((pData[i]|0x20)<='z'))
		{
			nHigh=(pData[i]|0x20)-'a'+10;
		}else
		{
			return FALSE;
		}

		if((pData[i+1]>='0')&&(pData[i+1]<='9'))
		{
			nLow=pData[i+1]-'0';
		}else if(((pData[i+1]|0x20)>='a')&&((pData[i+1]|0x20)<='z'))
		{
			nLow=(pData[i+1]|0x20)-'a'+10;
		}else
		{
			return FALSE;
		}

		pOutData[i/2]=nLow|((nHigh&0xf)<<4);
		if(2*nCount<i)
		{
			return FALSE;
		}
	}
	return TRUE;
}
#ifdef ZIP
#include "Base64.h"
#define ZLIB_WINAPI

#include ".\zlib/include/zlib.h"  
class CBase64Zip
{
private:
	CBase64Zip(){};
	~CBase64Zip(){};

public:
	template<typename StringT>
	static BOOL Base64ZipCompress(IN unsigned char * pBuf,IN unsigned long nLen,OUT StringT & szOutData)
	{
		BOOL bOk = FALSE;
		unsigned long bufLen = nLen + 4096;
		unsigned char * buf = (unsigned char *)MemoryMgr__StaticGC_Tmp::GetInstance().NewMemory(bufLen + 64);
		memcpy(buf, "yesszip#", 8);
		*((uLongf *)(buf + 8)) = nLen;
		if (compress(buf + 8 + sizeof(uLongf), &bufLen, pBuf, nLen) == Z_OK)
		{
			//Base64<StringT::value_type>::GetInstance(). base;
			bufLen += 8 + sizeof(uLongf);
			int buf1len = bufLen * 2;
			/*
			StringT::value_type * buf1 = new StringT::value_type[buf1len];
			std::auto_ptr< StringT::value_type> mem1(buf1);
			base.Base64EnCode(buf, bufLen, buf1, buf1len);
			szOutData = buf1;
			*/
			szOutData.reserve(buf1len);
			Base64<StringT::value_type>::GetInstance().Base64EnCode(buf, bufLen, szOutData);
			bOk = TRUE; 
			
		}
		return bOk;
	};

	template<typename StringT, typename VectorT>
	static BOOL Base64ZipUnCompress(IN StringT & inBuf,OUT VectorT & OutBuf)
	{
		//uLongf
		//uncompress(strDst, &dstLen, buf, bufLen);  
		//Base64<StringT::value_type> base;
		//unsigned char * pDstBuf = new unsigned char[inBuf.length() * sizeof(StringT::value_type) * 2];
		BOOL bRet = FALSE;
		int nDstLen = inBuf.length() << (sizeof(StringT::value_type) - 1) << 1;
		unsigned char * pDstBuf = (unsigned char *)MemoryMgr__StaticGC_Tmp::GetInstance().NewMemory(nDstLen);
		//std::auto_ptr<unsigned char> mem(pDstBuf);
		
		Base64<StringT::value_type>::GetInstance().Base64DeCode(inBuf.c_str(), inBuf.length(), pDstBuf, nDstLen);
		do
		{
			if (memcmp(pDstBuf, "yesszip#", 8) == 0)
			{
				uLongf nZipDstLen = *((uLongf *)(pDstBuf + 8));
				if (nZipDstLen>256 * 1024 * 1024)
				{
					//内存超大了
					bRet= FALSE;
					break;
				}

				OutBuf.resize(nZipDstLen + 4096);
				int ret = uncompress(&OutBuf[0], &nZipDstLen, pDstBuf + 8 + sizeof(uLongf), nDstLen - 8 - sizeof(uLongf));
				if (ret == Z_OK)
				{
					bRet= TRUE;
					break;
				}
			}
		} while (false);
		//MemoryMgr__StaticGC::GetInstance().DelMemory(pDstBuf, nDstLen);
		return bRet;
	};
	template<typename BufferT, typename VectorT>
	static BOOL Base64ZipUnCompress(IN BufferT * inBuf,unsigned int nLen, OUT VectorT & OutBuf)
	{
		BOOL bRet = FALSE;
		int nDstLen = nLen << (sizeof(BufferT) - 1) << 1;
		unsigned char * pDstBuf = (unsigned char *)MemoryMgr__StaticGC_Tmp::GetInstance().NewMemory(nDstLen);

		Base64<BufferT>::GetInstance().Base64DeCode(inBuf, nLen, pDstBuf, nDstLen);
		do
		{
			if (memcmp(pDstBuf, "yesszip#", 8) == 0)
			{
				uLongf nZipDstLen = *((uLongf *)(pDstBuf + 8));
				if (nZipDstLen>256 * 1024 * 1024)
				{
					//内存超大了
					bRet = FALSE;
					break;
				}

				OutBuf.resize(nZipDstLen + 4096);
				//unsigned char pZipDstBuf=new unsigned char[nDstLen+4096];
				//std::auto_ptr<unsigned char> mem(pZipDstBuf);
				int ret = uncompress(&OutBuf[0], &nZipDstLen, pDstBuf + 8 + sizeof(uLongf), nDstLen - 8 - sizeof(uLongf));
				if (ret == Z_OK)
				{
					bRet = TRUE;;
					break;
				}
			}
		} while (false);
		//MemoryMgr__StaticGC::GetInstance().DelMemory(pDstBuf, nDstLen);
		return bRet;
	};
	/*
	template<typename StringT>
	static BOOL Base64ZipUnCompress(IN StringT & inBuf,OUT vector<unsigned char> & OutBuf)
	{
		string inbuf1 = (char *)CMyString((WCHAR *)inBuf.c_str(), inBuf.length() * 2);
		return Base64ZipUnCompress(inbuf1, OutBuf);
	};
	*/
private:
};


#endif


#define TimeUsedBegin(TimeName) DWORD TimeName=GetTickCount();
#define TimeUsedEnd(TimeName) TimeName=GetTickCount()-TimeName;


class CXmlString
{
public:
	CXmlString(){};
	template<typename StringT, typename String1T>
	static BOOL GetXMLStringFromtstring(OUT StringT & XmlString,IN String1T &SrcString ) {
		WCHAR * pSrcString = (WCHAR *)CMyString((TCHAR *)SrcString.c_str(), SrcString.length() * sizeof(TCHAR));
		XmlString.clear();
		for (unsigned int i = 0; pSrcString[i] != 0; i++)
		{
			switch (pSrcString[i])
			{
			case '<':
				XmlString += _T("&lt;");
				break;
			case  '>':
				XmlString += _T("&gt;");
				break;
			case '&':
				XmlString += _T("&amp;");
				break;
			case '\'':
				XmlString += _T("&apos;");
				break;
			case '\"':
				XmlString += _T("&quot;");
				break;
			case '\n':
				XmlString += _T("&#10;");
				break;
			default:
				XmlString += pSrcString[i];
				break;
			}
		}
		return TRUE;
	};
	template<typename StringT, typename String1T>
	static BOOL GetStringFromXMLString(OUT StringT & String,IN String1T & XMLString ) {
		TCHAR * pSrcString = (TCHAR *)CMyString(XMLString);
		String.clear();
		for (unsigned int i = 0; pSrcString[i] != 0; i++)
		{
			if (strstr_t(pSrcString + i, _T("&lt;")) == pSrcString + i)
			{
				String += _T("<");
			}
			else if (strstr_t(pSrcString + i, _T("&gt;")) == pSrcString + i)
			{
				String += _T(">");
			}
			else if (strstr_t(pSrcString + i, _T("&amp;")) == pSrcString + i)
			{
				String += _T("&");
			}
			else if (strstr_t(pSrcString + i, _T("&apos;")) == pSrcString + i)
			{
				String += _T("\'");
			}
			else if (strstr_t(pSrcString + i, _T("&quot;")) == pSrcString + i)
			{
				String += _T("\"");
			}
			else if (strstr_t(pSrcString + i, _T("&#10;")) == pSrcString + i)
			{
				String += _T("\n");
			}
			else
			{
				String += pSrcString[i];
			}

		}
		return TRUE;
	}
	;

	~CXmlString(){};
protected:

private:
};

template<typename _T>
bool shellget(TCHAR * szCmd, _T & RetVal)
{
	FILE   *pPipe;

	if ((pPipe = popen_t(szCmd, _T("r"))) == NULL)
	{
		printf_t(_T("popen_t szCmd (%s) fail...\n"), szCmd);
		return false;
	}
	int nReadLen = 0;
	for (;;)
	{
		if (!fgets_t(&RetVal[nReadLen], sizeof(RetVal)- nReadLen *sizeof(TCHAR), pPipe)) break;
		nReadLen =strlen_t(RetVal);
		if (nReadLen * sizeof(TCHAR) >= sizeof(RetVal)) break;
	}
	
	if (feof(pPipe))
	{

		printf_t(_T("szCmd (%s) Process returned %d  nReadLen=%d \n"), szCmd, pclose(pPipe), nReadLen);
		return true;

	}else
	{
		printf_t(_T("szCmd (%s) nReadLen=%d Error: Failed to read the pipe to the end.\n%s \n"), szCmd, nReadLen, &RetVal[0]);
		return false;
	}
}