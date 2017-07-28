// ThreadBaseForKernel.cpp: implementation of the CThreadBaseForKernel class.
// 2006.4.16 叶树深，驱动应用层共享内存
//////////////////////////////////////////////////////////////////////

//线程操作适配器

#include <Ntifs.h>
#include <ntstrsafe.h>
#include "ThreadBaseForKernel.h"
#pragma comment(lib,"Ntoskrnl.lib")



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



CThreadBaseForKernel::CThreadBaseForKernel()
{

}

CThreadBaseForKernel::~CThreadBaseForKernel()
{

}




BOOL CThreadBaseForKernel::SetEvent(HANDLE hEvent)
{
	LONG  PreviousState;
	NTSTATUS status = ZwSetEvent(hEvent,&PreviousState);
	if(NT_SUCCESS(status))
	{
		return TRUE;
	}
	return FALSE;
}

DWORD CThreadBaseForKernel::WaitForSingleObject(HANDLE hHandle, DWORD dwMilliseconds)
{
	LARGE_INTEGER Timeout;
	__int64 nTime=(__int64)((__int64)0-((__int64)(dwMilliseconds))*((__int64)10000));
	Timeout.QuadPart=nTime;
	return ZwWaitForSingleObject(hHandle,FALSE,&Timeout);
}

BOOL CThreadBaseForKernel::CloseHandle(HANDLE hObject)
{
	return ZwClose(hObject);
}


BOOL CThreadBaseForKernel::ReleaseMutex(HANDLE hMutex)
{
	return TRUE;
}

HANDLE CThreadBaseForKernel::OpenFileMapping(DWORD dwDesiredAccess, BOOL bInheritHandle, void *lpName)
{
	return (HANDLE)0;
}

DWORD CThreadBaseForKernel::GetLastError()
{
	return 0;
}

HANDLE CThreadBaseForKernel::CreateThread(LPVOID lpThreadAttributes, DWORD dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId)
{
	return (HANDLE)1;
}

HANDLE CThreadBaseForKernel::CreateFileMapping(HANDLE hFile, LPVOID lpFileMappingAttributes, DWORD flProtect, DWORD dwMaximumSizeHigh, DWORD dwMaximumSizeLow, LPVOID lpName)
{
	HANDLE hSectionHandle=NULL;
	ULONG Allocation=flProtect&0xfffff000;
	if(Allocation==0)
	{
		Allocation=SEC_COMMIT;
	}
	LARGE_INTEGER MaxSize;
	MaxSize.LowPart=dwMaximumSizeLow;
	MaxSize.HighPart=dwMaximumSizeHigh;
	

	NTSTATUS status = ZwCreateSection(
		&hSectionHandle,
		SECTION_ALL_ACCESS,
		(POBJECT_ATTRIBUTES)lpFileMappingAttributes,
		&MaxSize,
		flProtect&0xfff,
		Allocation,
		hFile
    ); 
	if(NT_SUCCESS(status))
	{
		return hSectionHandle;
	}
	return (HANDLE)0;
}

HANDLE CThreadBaseForKernel::OpenMutex(DWORD dwDesiredAccess, BOOL bInheritHandle, LPVOID lpName)
{
	return (HANDLE)0;
}


HANDLE CThreadBaseForKernel::CreateEvent(LPVOID lpEventAttributes, BOOL bManualReset, BOOL bInitialState, LPCSTR lpName)
{
	HANDLE hevent=NULL;
	EVENT_TYPE EventType;
	if(bManualReset)
	{
		EventType=NotificationEvent;
	}
	else
	{
		EventType=SynchronizationEvent;
	}
	NTSTATUS Status= ZwCreateEvent(
		&hevent,
		EVENT_ALL_ACCESS,
		(POBJECT_ATTRIBUTES)lpEventAttributes,
		EventType,
		bInitialState
		);
	DbgPrint("ZwCreateEvent %08x" ,Status) ;
	if(NT_SUCCESS(Status))
	{
		return hevent;
	}
	return (HANDLE)0;
}

HANDLE CThreadBaseForKernel::OpenEvent(DWORD dwDesiredAccess, BOOL bInheritHandle, LPVOID lpName)
{
	return (HANDLE)0;
}

typedef
NTSTATUS
(NTAPI * fpZwResetEvent) (
			  __in HANDLE EventHandle,
			  __out_opt PLONG PreviousState
    );

BOOL CThreadBaseForKernel::ResetEvent(HANDLE hEvent)
{
	LONG  PreviousState;
	fpZwResetEvent  pZwResetEvent=(fpZwResetEvent)GetSysFunction(L"ZwResetEvent");
	if(pZwResetEvent)
	{
		NTSTATUS status = pZwResetEvent(hEvent,&PreviousState);
		if(NT_SUCCESS(status))
		{
			return TRUE;
		}
	}
	return FALSE;
}

/*
void CThreadBaseForKernel::memcpy(void * dstbuf, void *srcbuf, unsigned int nLen)
{
	RtlCopyMemory(dstbuf,srcbuf,nLen);
}*/


typedef NTSTATUS
(NTAPI *
fpZwWaitForMultipleObjects )(
						  __in ULONG Count,
						  __in_ecount(Count) HANDLE Handles[],
						  __in WAIT_TYPE WaitType,
						  __in BOOLEAN Alertable,
						  __in_opt PLARGE_INTEGER Timeout
    );
DWORD CThreadBaseForKernel::WaitForMultipleObjects(DWORD nCount, HANDLE *lpHandles, BOOL bWaitAll, DWORD dwMilliseconds)
{
	WAIT_TYPE WaitType;
	fpZwWaitForMultipleObjects  ZwWaitForMultipleObjects=(fpZwWaitForMultipleObjects)GetSysFunction(L"ZwWaitForMultipleObjects");
	if(ZwWaitForMultipleObjects)
	{
		LARGE_INTEGER Timeout;
		Timeout.QuadPart=dwMilliseconds*(-10000);
		if(bWaitAll)
		{
			WaitType=WaitAll;
		}
		else
		{
			WaitType=WaitAny;
		}
		//STATUS_WAIT_0
		return (DWORD)ZwWaitForMultipleObjects(nCount,lpHandles,WaitType,FALSE,&Timeout);
	}
	return 0xFFFFFFFF;
}

int CThreadBaseForKernel::sprintf(char *pBuf, const char * line,...)
{
	va_list	vl;
	va_start( vl, line );
	RtlStringCchVPrintfA(pBuf,1024,line,vl);
	//vsprintf(pBuf, line, vl );
	va_end( vl);
	return 0;
}

LPVOID CThreadBaseForKernel::MapViewOfFile(HANDLE hFileMappingObject, DWORD dwDesiredAccess, DWORD dwFileOffsetHigh, DWORD dwFileOffsetLow, DWORD dwNumberOfBytesToMap)
{
	LPVOID pRetAddr=NULL;
	LARGE_INTEGER  MaxSize;
	LARGE_INTEGER  SectionOffset;
	SIZE_T  ViewSize=dwNumberOfBytesToMap;

	SectionOffset.HighPart=dwFileOffsetHigh;
	SectionOffset.LowPart=dwFileOffsetLow;
	NTSTATUS Status=  
		ZwMapViewOfSection(
		hFileMappingObject,
		ZwCurrentProcess(), 
		IN OUT &pRetAddr,
		NULL,
		0,
		&SectionOffset  ,
		&ViewSize,
		ViewShare,
		MEM_TOP_DOWN ,
		PAGE_READWRITE
		);
	
	if (!NT_SUCCESS(Status)) 
    { 
        DbgPrint("Map view the file section failed! %08x \n",Status); 
        DbgPrint("BaseAddress %08x ",pRetAddr); 
        if (hFileMappingObject) 
		{
            ZwClose(hFileMappingObject); 
		}
        return 0; 
    } 
	return pRetAddr;
}

HANDLE CThreadBaseForKernel::CreateMutex(LPVOID lpMutexAttributes, BOOL bInitialOwner, LPCSTR lpName)
{
	return (HANDLE)1;
}

SID SeWorldSid={SID_REVISION, 1, SECURITY_WORLD_SID_AUTHORITY, SECURITY_WORLD_RID}; 
SID localSid={SID_REVISION, 1, SECURITY_NT_AUTHORITY, SECURITY_LOCAL_SYSTEM_RID}; 
char szDriverObjName[512];
BOOL CThreadBaseForKernel::BuildAlowingSD(SECURITY_ATTRIBUTES *pObjectAttributes,ACCESS_MASK AccessMask,void * pObjName)
{
	PUNICODE_STRING		pEventString_U=NULL	;
	ULONG buflen = PAGE_SIZE*2; 
	
	PACL dacl=(PACL)ExAllocatePool(PagedPool, buflen);
	//PACL dacl = (PACL)daclbuf; 
	PSECURITY_DESCRIPTOR sd=ExAllocatePool(PagedPool, buflen); 

	//PSECURITY_DESCRIPTOR sd = (PSECURITY_DESCRIPTOR)sdbuf; 
	
	NTSTATUS status = RtlCreateAcl(dacl, PAGE_SIZE, ACL_REVISION); 
	if (!NT_SUCCESS(status)) goto fail; 
	status = RtlAddAccessAllowedAce(dacl, ACL_REVISION, AccessMask, &SeWorldSid); 
	if (!NT_SUCCESS(status)) goto fail;  
	RtlZeroMemory(sd, PAGE_SIZE); 
	status = RtlCreateSecurityDescriptor(sd, SECURITY_DESCRIPTOR_REVISION); 
	if (!NT_SUCCESS(status)) goto fail; 
	status = RtlSetOwnerSecurityDescriptor(sd, &localSid, FALSE); 
	if (!NT_SUCCESS(status)) goto fail; 
	status = RtlSetDaclSecurityDescriptor(sd, TRUE, dacl, FALSE); 
	if (!NT_SUCCESS(status)) goto fail; 
	if (RtlValidSecurityDescriptor(sd)) 
	{ 

		//*pSecurityDescriptor = sd; 
		
	} 

	sprintf(szDriverObjName,"%s%s","\\BaseNamedObjects\\",pObjName);
	ANSI_STRING AnsiName;
	RtlInitAnsiString(&AnsiName,szDriverObjName);
	pEventString_U=(PUNICODE_STRING)ExAllocatePool(PagedPool,sizeof(UNICODE_STRING));
	if(pEventString_U)
	{
		RtlAnsiStringToUnicodeString(pEventString_U,&AnsiName,TRUE);
		
		InitializeObjectAttributes(pObjectAttributes, pEventString_U,OBJ_OPENIF|OBJ_CASE_INSENSITIVE , NULL, sd);
	}
	
	

	return status;
fail:
	ExFreePool(dacl);
	ExFreePool(sd);
	return status; 
}

BOOL CThreadBaseForKernel::SetLowIntegrity(char *pObjName)
{
	return TRUE;
}

PVOID CThreadBaseForKernel::GetSysFunction(PCWSTR pFuncName)
{

	UNICODE_STRING      UniCodeFunctionName   = {0};
	RtlInitUnicodeString( &UniCodeFunctionName, pFuncName);
	return MmGetSystemRoutineAddress(&UniCodeFunctionName );
}

