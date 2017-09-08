#pragma once

//2017 内存池使用新的C++14 thread local实做
#include "../BaseFunctionTool.h"
#include "../SmartSTL/thread_static.h"
#include "StateList.h"


#ifndef _LINUX_
void DisplayError(TCHAR* pszAPI, DWORD dwError)
{
	LPVOID lpvMessageBuffer;

	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, dwError,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpvMessageBuffer, 0, NULL);

	//... now display this string
	_tprintf(TEXT("ERROR: API        = %s\n"), pszAPI);
	_tprintf(TEXT("       error code = %d\n"), dwError);
	_tprintf(TEXT("       message    = %s\n"), lpvMessageBuffer);

	// Free the buffer allocated by the system
	LocalFree(lpvMessageBuffer);

	//ExitProcess(GetLastError());
}

void Privilege(TCHAR* pszPrivilege, BOOL bEnable)
{
	HANDLE           hToken;
	TOKEN_PRIVILEGES tp;
	BOOL             status;
	DWORD            error;

	// open process token
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
		DisplayError(TEXT("OpenProcessToken"), GetLastError());

	// get the luid
	if (!LookupPrivilegeValue(NULL, pszPrivilege, &tp.Privileges[0].Luid))
		DisplayError(TEXT("LookupPrivilegeValue"), GetLastError());

	tp.PrivilegeCount = 1;

	// enable or disable privilege
	if (bEnable)
		tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	else
		tp.Privileges[0].Attributes = 0;

	// enable or disable privilege
	status = AdjustTokenPrivileges(hToken, FALSE, &tp, 0, (PTOKEN_PRIVILEGES)NULL, 0);

	// It is possible for AdjustTokenPrivileges to return TRUE and still not succeed.
	// So always check for the last error value.
	error = GetLastError();
	if (!status || (error != ERROR_SUCCESS))
		DisplayError(TEXT("AdjustTokenPrivileges"), GetLastError());

	// close the handle
	if (!CloseHandle(hToken))
		DisplayError(TEXT("CloseHandle"), GetLastError());
}

/*
To enable the lock pages in memory option
On the Start menu, click Run. In the Open box, type gpedit.msc.
On the Local Group Policy Editor console, expand Computer Configuration, and then expand Windows Settings.
Expand Security Settings, and then expand Local Policies.
Select the User Rights Assignment folder.
The policies will be displayed in the details pane.
In the pane, double-click Lock pages in memory.
In the Local Security Setting – Lock pages in memory dialog box, click Add User or Group.
In the Select Users, Service Accounts, or Groups dialog box, add an account with privileges to run sqlservr.exe.
Log out and then log back in for this change to take effect.
*/
#define SE_LOCK_MEMORYPRIVILEGE             TEXT("SeLockMemoryPrivilege")
char * AllocLargePageCount(unsigned int nCount, unsigned int nNode = 0, BOOL bLarge = TRUE)
{
	Privilege(TEXT("SeLockMemoryPrivilege"), TRUE);
	SIZE_T sizeOfLargePage = GetLargePageMinimum();

	if (0 == sizeOfLargePage)
	{
		Error(_T("error in GetLargePageMinium \n"));
		return NULL;
	}


	DWORD nFlag = MEM_RESERVE | MEM_COMMIT;
	if (bLarge) nFlag |= MEM_LARGE_PAGES;

	UCHAR NodeNumber;
	if (!GetNumaProcessorNode(nNode, &NodeNumber))
	{
		Error(_T("GetNumaProcessorNode failed: %d\n"), GetLastError());
		return NULL;
	}
	Error((_T("GetNumaProcessorNode ok: %d NodeNumber=%u sizeOfLargePage %d %d\n")),
		GetLastError(), NodeNumber, sizeOfLargePage, sizeOfLargePage * nCount);
	PVOID pAddr = VirtualAllocExNuma(
		GetCurrentProcess(),
		NULL,
		sizeOfLargePage * nCount,
		nFlag,
		PAGE_READWRITE, NodeNumber);

	//PVOID pAddr = VirtualAlloc(NULL, sizeOfLargePage * nCount, nFlag, PAGE_READWRITE);
	if (NULL == pAddr)
	{
		Error(_T("error in VirtualAlloc err=%x\n"), GetLastError());
		return NULL;
	}
	//char szBuffer[] = "hello world!\r\n";
	//size_t nBuffer = _countof(szBuffer);

	//Error("sizeOfLargePage is %u %u %u\r\n", sizeOfLargePage, _countof(szBuffer), sizeof(szBuffer));
	// memcpy_s(pAddr, _countof(szBuffer), szBuffer, _countof(szBuffer)); //_countof参数只能是数组，返回字符数 
	//memcpy(pAddr, szBuffer, sizeof(szBuffer));
	//Error("%s", pAddr);

	//VirtualFree(pAddr, 0, MEM_DECOMMIT | MEM_RELEASE);

	return (char *)pAddr;
}

char * AllocLargePage(size_t nSize, char * pszName = NULL, unsigned int nNode = 0, BOOL bLarge = TRUE, size_t nPageSize = 2048 * 1024)
{
	Privilege(TEXT("SeLockMemoryPrivilege"), TRUE);
	SIZE_T sizeOfLargePage = GetLargePageMinimum();
	unsigned int nCount = (nSize / sizeOfLargePage) + ((nSize>sizeOfLargePage) ? 1 : 0);
	if (0 == sizeOfLargePage)
	{
		Error(_T("error in GetLargePageMinium \n"));
		return NULL;
	}


	DWORD nFlag = MEM_RESERVE | MEM_COMMIT;
	if (bLarge) nFlag |= MEM_LARGE_PAGES;

	UCHAR NodeNumber;
	if (!GetNumaProcessorNode(nNode, &NodeNumber))
	{
		Error(_T("GetNumaProcessorNode failed: %d\n"), GetLastError());
		return NULL;
	}
	Error((_T("GetNumaProcessorNode ok: %d NodeNumber=%u PageSize=%d count=%d size=%d %d\n")),
		GetLastError(), NodeNumber, sizeOfLargePage, nCount, nSize, sizeOfLargePage * nCount);
	PVOID pAddr = VirtualAllocExNuma(
		GetCurrentProcess(),
		NULL,
		sizeOfLargePage * nCount,
		nFlag,
		PAGE_READWRITE, NodeNumber);

	//PVOID pAddr = VirtualAlloc(NULL, sizeOfLargePage * nCount, nFlag, PAGE_READWRITE);
	if (NULL == pAddr)
	{
		Error(_T("error in VirtualAlloc err=%x\n"), GetLastError());
		return NULL;
	}
	//char szBuffer[] = "hello world!\r\n";
	//size_t nBuffer = _countof(szBuffer);

	//Error("sizeOfLargePage is %u %u %u\r\n", sizeOfLargePage, _countof(szBuffer), sizeof(szBuffer));
	// memcpy_s(pAddr, _countof(szBuffer), szBuffer, _countof(szBuffer)); //_countof参数只能是数组，返回字符数 
	//memcpy(pAddr, szBuffer, sizeof(szBuffer));
	//Error("%s", pAddr);

	//VirtualFree(pAddr, 0, MEM_DECOMMIT | MEM_RELEASE);

	return (char *)pAddr;
}
void FreeLargePage(void * pAddr, __int64 nLen=0)
{
	VirtualFree(pAddr, 0, MEM_DECOMMIT | MEM_RELEASE);
}
#else

#include <fcntl.h> 
#include <sys/mman.h> 

thread_local static unsigned int g_nAllocLargePageIndex = 0;
thread_local static LONGLONG g_nCurrentCore = -1;
LONGLONG g_nCurrentMaxCore = 0;

char * AllocLargePage(size_t nSize, char * pszName = NULL, unsigned int nNode = 0, BOOL bLarge = TRUE, size_t nPageSize=2048*1024)
{
	int fd;
	void * addr;

	/* create a file in hugetlb fs */
	char szPath[256];
	if (pszName)
	{
		sprintf(szPath, "/mnt/huge/%s", pszName);
	}
	else
	{
		if (g_nCurrentCore == -1)
		{
			g_nCurrentCore = (int)(unsigned int)InterlockedAdd64(&g_nCurrentMaxCore, (unsigned int)1);
		}
		sprintf(szPath, "/mnt/huge/NoName-%d-%d", g_nCurrentCore,g_nAllocLargePageIndex);
		g_nAllocLargePageIndex++;
	}

	fd = open(szPath, O_CREAT | O_RDWR);
	if (fd < 0) {
		Error(_T("AllocLargePage open Err: %s\n"), szPath);
		return NULL;
	}
	size_t sizeOfLargePage = nPageSize;//getpagesize();
	unsigned int nCount = (nSize / sizeOfLargePage) + 1;
	Error(_T("AllocLargePage %s PageSize=%d count=%d size=%d %d\n"), szPath, sizeOfLargePage, nCount, nSize, nCount*sizeOfLargePage);
	TCHAR szLargePageInfo[1024] = {0};
	if (shellget(_T("cat /proc/meminfo | grep Huge"), szLargePageInfo))
	{
		Error(_T("LargePageInfo:\n%s\n"), szLargePageInfo);
	}
	/* map the file into address space of current application process */
	addr = mmap(0, nCount*sizeOfLargePage, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (addr == MAP_FAILED) {
		Error(_T("AllocLargePage map Err: %s\n"), szPath);
		close(fd);
		unlink(szPath);
		return NULL;
	}
	return (char*)addr;
	/* from now on, you can store application data on huage pages via addr */

	//munmap(addr, MAP_LENGTH);
	//close(fd);
	//unlink("/mnt/huge/test");
}
void FreeLargePage(void * pAddr,__int64 nLen = 0)
{
	//VirtualFree(pAddr, 0, MEM_DECOMMIT | MEM_RELEASE);
}

#endif


template<typename ParentMemoryMgrT>
class MemoryMgr_LargePage
{
public:
	
	ParentMemoryMgrT * m_pParentMemoryMgr;
	void SetParentMemoryMgr(ParentMemoryMgrT * pParentMemoryMgr)
	{
		m_pParentMemoryMgr = pParentMemoryMgr;
	}


public:
	MemoryMgr_LargePage() {
		
	};
	~MemoryMgr_LargePage() {};
	//GC全局初始化分配内存
	void * NewGc()
	{
		return this;
	}
	//全局GC模式时释放gc内存
	void DelGc(bool bRealClear)
	{
		
		return;
	}


	//从pool中分配普通内存
	void * NewMemory(__int64 nLen) {
		return (void *)AllocLargePage(nLen);
	};
	bool DelMemory(void * pMem, __int64 nLen) {
		FreeLargePage(pMem, nLen);
		return FALSE;//g_pMemoryMgr[nParentMemMgr].DelMemory(pMem);
	};

protected:


};


