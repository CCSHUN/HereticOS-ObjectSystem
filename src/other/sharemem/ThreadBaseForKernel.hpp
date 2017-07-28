// ThreadBaseForKernel.h: interface for the CThreadBaseForKernel class.
// 2006.4.16 叶树深，驱动应用层共享内存
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_THREADBASEFORKERNEL_H__8A3D8E07_46F9_459B_9783_A19EAB90E1AA__INCLUDED_)
#define AFX_THREADBASEFORKERNEL_H__8A3D8E07_46F9_459B_9783_A19EAB90E1AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define BOOL unsigned int
#define FALSE 0
#define TRUE 1
#define HANDLE unsigned int
//#define LPVOID void *
#define SECURITY_ATTRIBUTES OBJECT_ATTRIBUTES
#define DWORD unsigned int
#define CThreadBase CThreadBaseForKernel
#define LPCSTR LPVOID
#define LPTHREAD_START_ROUTINE LPVOID
#define LPDWORD unsigned int *
#define NULL 0
#define INFINITE            0xFFFFFFFF


#define PVOID			void *
#define LPVOID			void * 
#define LPDWORD			DWORD * 


#define LPTHREAD_START_ROUTINE void * 
#define WAIT_TIMEOUT            STATUS_TIMEOUT
#define WAIT_OBJECT_0			STATUS_WAIT_0 
#define WAIT_OBJECT_1			STATUS_WAIT_1
#define FILE_MAP_ALL_ACCESS		SECTION_ALL_ACCESS
#define INVALID_HANDLE_VALUE	0
#define MUTEX_ALL_ACCESS		0
	




#endif // !defined(AFX_THREADBASEFORKERNEL_H__8A3D8E07_46F9_459B_9783_A19EAB90E1AA__INCLUDED_)

