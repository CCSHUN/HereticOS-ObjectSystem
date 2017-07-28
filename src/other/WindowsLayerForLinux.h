#pragma once
//WindowsLayerForLinux.h
#ifdef _LINUX_
#include "time.h"
#include "unistd.h"
#include "pthread.h"
//#include "atomic.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/syscall.h>
#include <sched.h>
#include <typeinfo> 


typedef unsigned long long ULONG_PTR, *PULONG_PTR;
typedef ULONG_PTR KAFFINITY;
typedef unsigned int DWORD;
typedef unsigned int BOOL;
typedef void * HANDLE;
typedef void * PVOID;
typedef unsigned short WORD;
typedef unsigned int UINT;
typedef unsigned long long LONGLONG;
typedef long long __int64;
typedef wchar_t WCHAR;
typedef unsigned char BYTE;
typedef void VOID;
#define OUT 
#define IN
#define INFINITE 0xFFFFFFFF
//#define NULL 0

#ifdef _UNICODE
typedef WCHAR TCHAR;
#define _T(x)      L##x
#else
typedef char            TCHAR;
#define _T(x)      x
#endif

#define WINAPI
#define FALSE 0
#define TRUE 1

/*
返回计算之前的值
type __sync_fetch_and_add (type *ptr, type value, ...)
type __sync_fetch_and_sub (type *ptr, type value, ...)
type __sync_fetch_and_or (type *ptr, type value, ...)
type __sync_fetch_and_and (type *ptr, type value, ...)
type __sync_fetch_and_xor (type *ptr, type value, ...)
type __sync_fetch_and_nand (type *ptr, type value, ...)

之后的值
type __sync_add_and_fetch (type *ptr, type value, ...)
type __sync_sub_and_fetch (type *ptr, type value, ...)
type __sync_or_and_fetch (type *ptr, type value, ...)
type __sync_and_and_fetch (type *ptr, type value, ...)
type __sync_xor_and_fetch (type *ptr, type value, ...)
type __sync_nand_and_fetch (type *ptr, type value, ...)
*/

#define InterlockedAdd64(x,y) __sync_fetch_and_add((x),(y))
#define InterlockedDec64(x,y) __sync_fetch_and_sub((x),(y))

typedef DWORD (* PTHREAD_START_ROUTINE)(
	void* lpThreadParameter
	);

typedef PTHREAD_START_ROUTINE LPTHREAD_START_ROUTINE;

struct ThreadWarpContext
{
	PTHREAD_START_ROUTINE pWin32ThreadProc;
	void* lpThreadParameter;
};

void* ThreadProcWarp(void  * pParameter)
{
	ThreadWarpContext * pContext = (ThreadWarpContext *)pParameter;
	pContext->pWin32ThreadProc(pContext->lpThreadParameter);
	delete pContext;
	pthread_exit(0);
	return NULL;
}


HANDLE
CreateThread(
	void * lpThreadAttributes,
	unsigned int dwStackSize,
	LPTHREAD_START_ROUTINE lpStartAddress,
	void * lpParameter,
	DWORD dwCreationFlags,
	DWORD* lpThreadId
)
{
	pthread_t id;
	ThreadWarpContext * pThreadContext = new ThreadWarpContext;
	pThreadContext->lpThreadParameter = lpParameter;
	pThreadContext->pWin32ThreadProc = lpStartAddress;

	if (pthread_create(&id,NULL, ThreadProcWarp, pThreadContext) != 0)
	{
		return NULL;
	}
	if(lpThreadId) *lpThreadId = id;
	return (HANDLE)id;
};

typedef struct _GROUP_AFFINITY {
	KAFFINITY Mask;
	WORD   Group;
	WORD   Reserved[3];
} GROUP_AFFINITY, *PGROUP_AFFINITY;

#include "CpuTypeInfo.h"
BOOL
SetThreadGroupAffinity(
	 HANDLE hThread,
	 GROUP_AFFINITY * GroupAffinity,
	 PGROUP_AFFINITY PreviousGroupAffinity
)
{
	printf("SetThreadGroupAffinity1 Handle %p Mask(%x)\r\n", hThread , GroupAffinity->Mask);
	cpu_set_t mask;
	CPU_ZERO(&mask);
	KAFFINITY Win32Mask = GroupAffinity->Mask;
	for (int i = 0;Win32Mask != 0;i++)
	{
		if ((Win32Mask & 1))
		{
//#ifdef CPU_TYPE
			int nCore = g_CpuInfoTab[CPU_TYPE][GroupAffinity->Group][i];
//#else
//		int nCore = i;
//#endif
			CPU_SET(nCore, &mask);
			printf("CPU CPU_TYPE(%d) i=%d nCore=%d is set mask(%x)\n", CPU_TYPE, i, nCore, mask);
		}
		Win32Mask = Win32Mask >> 1;
	}

	pthread_setaffinity_np((pthread_t)hThread, sizeof(cpu_set_t), &mask);


	CPU_ZERO(&mask);
	if (pthread_getaffinity_np((pthread_t)hThread, sizeof(mask), &mask) < 0) {
		fprintf(stderr, "get thread affinity failed\n");
	}
	int num = sysconf(_SC_NPROCESSORS_CONF);

	for (int j = 0; j < num; j++) {
		if (CPU_ISSET(j, &mask)) {
			printf("cputotal(%d) thread %p is running in processor %d mask(%x-%x)\n",
				num, (pthread_t)pthread_self(), j, GroupAffinity->Mask, mask);
		}
	}

	return TRUE;
};

BOOL
SetCurrentThreadGroupAffinity(
	GROUP_AFFINITY * GroupAffinity,
	PGROUP_AFFINITY PreviousGroupAffinity
)
{
	pthread_t hThread= pthread_self();
	
	cpu_set_t mask;
	CPU_ZERO(&mask);
	KAFFINITY Win32Mask = GroupAffinity->Mask;
	//CPU_SET(0, &cpuset);
	for (int i=0;Win32Mask!=0;i++)
	{
		if ((Win32Mask & 1))
		{
//#ifdef CPU_TYPE
			int nCore = g_CpuInfoTab[CPU_TYPE][GroupAffinity->Group][i];
//#else
//			int nCore = i;
//#endif
			CPU_SET(nCore, &mask);
			printf("CPU CPU_TYPE(%d) i=%d nCore=%d is set mask(%x)\n", CPU_TYPE, i, nCore, mask);
		}
		Win32Mask = Win32Mask >> 1;
	}
	//Error("SetCurrentThreadGroupAffinity Handle %p Mask(%x-%x)\n", hThread, GroupAffinity->Mask, mask);

	pthread_setaffinity_np(hThread, sizeof(cpu_set_t), &mask);

	CPU_ZERO(&mask);
	if (pthread_getaffinity_np(pthread_self(), sizeof(mask), &mask) < 0) {
		fprintf(stderr, "get thread affinity failed\n");
	}

	int num = sysconf(_SC_NPROCESSORS_CONF);
	for (int j = 0; j < num; j++) {
		if (CPU_ISSET(j, &mask)) {
			printf("cputotal(%d) thread %p is running in processor %d Mask(%x-%x)\n",
				num, (pthread_t)pthread_self(), j, GroupAffinity->Mask, mask);
		}
	}

	return TRUE;
};

void Sleep(DWORD nTick)
{
	unsigned long nUs = nTick * 1000;
	usleep(nUs);
};


DWORD
WINAPI
GetCurrentThreadId(
) 
{
	//Error(_T("GetCurrentThreadId %lu %lu\r\n"), (long int)syscall(__NR_gettid), pthread_self());
	return (DWORD)syscall(__NR_gettid);
};

HANDLE GetCurrentThread()
{
	//Error(_T("GetCurrentThread %lu \r\n"), pthread_self());
	return (HANDLE)pthread_self();
}

BOOL
WINAPI
IsBadReadPtr(
	VOID *lp,
	size_t ucb
) {

	return FALSE;
};

BOOL
WINAPI
SwitchToThread(
) 
{
	sleep(0);
};

unsigned long GetTickCount()
{
	struct timespec ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);

	return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
	return 0;
}

__int64 GetTickCount64()
{
	struct timespec ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);

	return ((__int64)(ts.tv_sec * 1000) + (__int64)(ts.tv_nsec / 1000000));
	return 0;
}

int vsprintf_s(
	char*       const _Buffer,
	size_t      const _BufferCount,
	char const* const _Format,
	va_list           _ArgList
)
{
	return vsprintf(_Buffer, _Format, _ArgList);
}

int  vswprintf_s(
	wchar_t*       const _Buffer,
	size_t         const _BufferCount,
	wchar_t const* const _Format,
	va_list              _ArgList
)
{
	return vswprintf(_Buffer, _BufferCount,_Format, _ArgList);
}

char*  gets_s(char*   _Buffer, size_t _Size)
{
	//return gets(_Buffer);
	return fgets(_Buffer, _Size, stdin);
}
char*   strcpy_s(
	char*       _Destination,
	size_t     _SizeInBytes,
	char const* _Source
)
{
	return strcpy(_Destination, _Source);
}

char*  strcat_s(
	char*       _Destination,
	size_t     _SizeInBytes,
	char const* _Source
)
{
	return strcat(_Destination, _Source);
}


#endif