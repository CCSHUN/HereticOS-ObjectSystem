// ThreadBaseForKernel.h: interface for the CThreadBaseForKernel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_THREADBASEFORKERNEL_H__8A3D8E07_46F9_459B_9783_A19EAB90E1AA__INCLUDED_)
#define AFX_THREADBASEFORKERNEL_H__8A3D8E07_46F9_459B_9783_A19EAB90E1AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000




#define BOOL unsigned int
//#define FALSE 0
//#define TRUE 1
//#define HANDLE void *
//#define LPVOID void *
#define SECURITY_ATTRIBUTES OBJECT_ATTRIBUTES
//#define DWORD unsigned int
#define CThreadBase CThreadBaseForKernel
//#define LPCSTR LPVOID
//#define LPTHREAD_START_ROUTINE LPVOID
//#define LPDWORD unsigned int *
#define NULL 0
#define INFINITE            0xFFFFFFFF
#define DWORD unsigned int
#define PVOID void *

#define LPVOID void * 
#define LPDWORD DWORD * 

#define LPTHREAD_START_ROUTINE	 void * 
#define WAIT_TIMEOUT            STATUS_TIMEOUT
#define WAIT_OBJECT_0			STATUS_WAIT_0 
#define WAIT_OBJECT_1			STATUS_WAIT_1
#define FILE_MAP_ALL_ACCESS		SECTION_ALL_ACCESS
#define INVALID_HANDLE_VALUE	0
#define MUTEX_ALL_ACCESS		0





class CThreadBaseForKernel  
{
public:
	static PVOID GetSysFunction(PCWSTR pFuncName);
	static BOOL SetLowIntegrity(char *pObjName);
	static BOOL BuildAlowingSD(SECURITY_ATTRIBUTES *pObjectAttributes,ACCESS_MASK AccessMask,void * pObjName);
	static HANDLE CreateMutex(LPVOID lpMutexAttributes,BOOL bInitialOwner,LPCSTR lpName);
	static LPVOID MapViewOfFile(HANDLE hFileMappingObject,DWORD dwDesiredAccess,DWORD dwFileOffsetHigh,DWORD dwFileOffsetLow,DWORD dwNumberOfBytesToMap);
	static int sprintf(char *pBuf, const char * line, ...);
	static DWORD WaitForMultipleObjects(DWORD nCount,HANDLE *lpHandles,BOOL bWaitAll,DWORD dwMilliseconds);
	//static void memcpy(void * dstbuf,void * srcbuf,unsigned int nLen);
	static BOOL ResetEvent(HANDLE hEvent);
	static HANDLE OpenEvent(DWORD dwDesiredAccess,BOOL bInheritHandle,LPVOID lpName);
	static HANDLE CreateEvent(LPVOID lpEventAttributes,BOOL bManualReset,BOOL bInitialState,LPCSTR lpName);
	static BOOL ReleaseMutex(HANDLE hMutex);
	static HANDLE OpenMutex(DWORD dwDesiredAccess,BOOL bInheritHandle,LPVOID lpName);
	static HANDLE CreateFileMapping(HANDLE hFile,LPVOID lpFileMappingAttributes,DWORD flProtect,DWORD dwMaximumSizeHigh,DWORD dwMaximumSizeLow,LPVOID lpName);
	static HANDLE CreateThread(LPVOID lpThreadAttributes, DWORD dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId);
	static DWORD GetLastError();
	static HANDLE OpenFileMapping(DWORD dwDesiredAccess,BOOL bInheritHandle,void * lpName);
	static BOOL Log( const char * line,...)
	{
		return TRUE;
	};
	static BOOL CloseHandle(HANDLE hObject);
	static DWORD WaitForSingleObject(HANDLE hHandle,DWORD dwMilliseconds);
	static BOOL SetEvent(HANDLE hEvent);
	CThreadBaseForKernel();
	~CThreadBaseForKernel();
};


#endif // !defined(AFX_THREADBASEFORKERNEL_H__8A3D8E07_46F9_459B_9783_A19EAB90E1AA__INCLUDED_)

