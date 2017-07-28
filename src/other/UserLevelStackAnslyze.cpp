#include "stdafx.h"
//#include "exceptiondumphelp.h"
#include "BaseFunctionTool.h" 
#include "TextIoSystem.h"
#include "Psapi.h"
#include "Petool.h"
#include "Tlhelp32.h"
#include "SymLoader.h"
#include "dbghelp.h"
#include "UserLevelStackAnslyze.h"

#define DumpPath _T("c:\\IeStackAnslyze\\dump")
#define SymPath _T("c:\\IeStackAnslyze\\sym")
#define SymOutPath _T("c:\\IeStackAnslyze\\OutSymInfo")

int filter(unsigned int code, struct _EXCEPTION_POINTERS *ep) 
{ 
	ErrorPrinterT<PrinterProxyOutputDebugString> Error;
	Error(_T("filter code= %x ep addr=0x%08x,code=%x"),code,
		ep->ExceptionRecord->ExceptionAddress,ep->ExceptionRecord->ExceptionCode);
	MyUnhandledExceptionFilter(ep);
	return EXCEPTION_EXECUTE_HANDLER; 
} 

BOOL AddrCanRead(IN  VOID  *pAddress,
				 IN SIZE_T  Length
				 )
{
	BOOL bRet=TRUE;
	return !IsBadReadPtr(pAddress,Length);
	/*__try
	{
		if(IsBadReadPtr(pAddress,Length))
		
		__leave;
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{

		bRet = FALSE;
	}
*/

	return bRet;
}

CSymLoader gSymLoad;

void GetAddressInfo(PVOID pAddress,tstring &szInfo,ErrorPrinter & ErrorLog)
{
#define ModuleMaxSize 8192
	HMODULE ModuleArray[ModuleMaxSize]={NULL};
	TCHAR szModuleName[MAX_PATH]={0};
	szInfo=_T("null");
	DWORD nNeed=0;
	HANDLE hProcess= GetCurrentProcess();
	if(hProcess)
	{

		if(EnumProcessModules(hProcess,&ModuleArray[0],ModuleMaxSize*sizeof(HMODULE),&nNeed))
		{
			for(unsigned int i=0;i*sizeof(HMODULE)<nNeed;i++)
			{
				_MODULEINFO Info;
				if(GetModuleFileName(ModuleArray[i],&szModuleName[0],sizeof(TCHAR)*MAX_PATH))
				{
					if(GetModuleInformation(hProcess,ModuleArray[i],&Info,sizeof(_MODULEINFO)))
					{
						if((pAddress>Info.lpBaseOfDll)&&(pAddress<=((char*)Info.lpBaseOfDll+Info.SizeOfImage)))
						{
							char * pOffsetAddress=(char *)((char *)pAddress-(char*)Info.lpBaseOfDll);
							//TCHAR szFullPath[MAX_PATH]={0};
							//GetModule
							szInfo=_T("null");
							 
							gSymLoad.GetAddressInfo(tstring(szModuleName),(DWORD64)pAddress,Info.lpBaseOfDll,(DWORD64)Info.SizeOfImage,szInfo);
							//ErrorLog(_T("%s"),szInfo.c_str());
							ErrorLog(szInfo,_T("(%s.0x%p sym-(%s) SecOffset.0x%p PEFile.0x%p)"),szModuleName,pOffsetAddress,
								szInfo.c_str(),
								(ULONG)Rva2Raw(Info.lpBaseOfDll,(ULONG)pOffsetAddress),
								(ULONG)Rva2SecOffset(Info.lpBaseOfDll,(ULONG)pOffsetAddress));
							/*ErrorLog(_T("(%s.0x%08x,base=0x%08x,calladdr=0x%08x,SecOffset=0x%x,len=%x)"),szModuleName,
								((char *)pAddress-(char*)Info.lpBaseOfDll),Info.lpBaseOfDll,
								pAddress,(ULONG)Rva2SecOffset(Info.lpBaseOfDll,(ULONG)pOffsetAddress),Info.SizeOfImage);*/
							return;
						}
						memset(szModuleName,0,sizeof(TCHAR)*MAX_PATH);
						memset(&Info,0,sizeof(_MODULEINFO));
					}else
					{
						ErrorLog(_T("GetModuleInformation Err(%d)"),GetLastError());
					}
				}else
				{
					ErrorLog(_T("GetModuleBaseName Err(%d)"),GetLastError());
				}
				
			}
		}else
		{
			ErrorLog(_T("EnumProcessModules Err(%d)"),GetLastError());
		}
	}else
	{
		ErrorLog(_T("GetCurrentProcess Err(%d)"),GetLastError());
	}
	
}
//2011.12.27 叶树深 SSDT 调用线程栈分析

BOOL	StackAnslyze(ULONG Ebp,ULONG Eip,char * pFlag,BOOL bKnlMode)
{
	//ANSI_STRING szCallStackAnslyzeReport;
	


	return TRUE;
};


void UserLevelThreadStackAnslyze32(HANDLE hThread,TCHAR * pCallInfo, ErrorPrinter & ErrorLog)
{
	ULONG ThreadEbp=0;
	if(hThread==NULL)
	{
#ifndef _AMD64_ 
		__asm
		{
			mov eax,ebp
			mov ThreadEbp,eax
		}
#endif
	}else
	{
		_CONTEXT cpuContext;
		cpuContext.ContextFlags=CONTEXT_FULL;
		SuspendThread(hThread);
		GetThreadContext(hThread,&cpuContext);
		ResumeThread(hThread);
		ThreadEbp=cpuContext.Ebp;
	}
	
	ErrorLog(_T("UserLevelThreadStackAnslyze32 hThread=%x Ebp=%x begin"),hThread,ThreadEbp);
	

	tstring szCallStackAnslyzeReport=pCallInfo;
	tstring szCallStackAnslyzeReportTmp;

	unsigned int CurStack=0;
	unsigned int CallAddr=0;
	unsigned int i=0;

	try
	{
		//DbgPrint("SSDTCallStackAnslyze in ...\n");
		CurStack=ThreadEbp;


		for(i=0;i<64;i++)
		{
			//ProbeForRead((((ULONG*)CurStack)+1),4,4);
			if(AddrCanRead((((ULONG*)CurStack)+1),4)==FALSE)
			{
				szCallStackAnslyzeReport+=_T("CallAddrEnd\r\n");
				break;
			}

			if(AddrCanRead(((ULONG*)CurStack),4)==FALSE)
			{
				szCallStackAnslyzeReport+=_T("StackEnd\r\n");
				break;
			}

			CallAddr=*(((ULONG*)CurStack)+1);

			tstring szInfo;
			GetAddressInfo((LPVOID)CallAddr,szInfo,ErrorLog);
			ErrorLog(szCallStackAnslyzeReportTmp,_T("(Stack(0x%08x) -- %s -- CallAddr(0x%08x))\r\n"),
				CurStack,szInfo.c_str(),CallAddr);

			szCallStackAnslyzeReport+=szCallStackAnslyzeReportTmp;

			//ProbeForRead((((ULONG*)CurStack)),4,4);


			CurStack=*((ULONG*)CurStack);
			/*if((i+1)%5==0)
			{
				ErrorLog(szCallStackAnslyzeReportTmp,_T("Line(%d) End\\r\n"),((i+1)/5),)
				szCallStackAnslyzeReport+=_T(" ");
				ErrorLog(szCallStackAnslyzeReport.c_str());

				szCallStackAnslyzeReport=pCallInfo;
				

			}*/
		}
		szCallStackAnslyzeReport+=_T("Ended \r\n\r\n\r\n");
	}
	catch(...)
	{
		ErrorLog(szCallStackAnslyzeReport.c_str());
		ErrorLog(_T("SSDTCallStackAnslyze Fail ...\n"));
		return ;
	}


	ErrorLog(szCallStackAnslyzeReport.c_str());
	return;
}




typedef BOOL (WINAPI * pMiniDumpWriteDump)(IN HANDLE hProcess,IN DWORD ProcessId,IN HANDLE hFile,IN MINIDUMP_TYPE DumpType,
										   IN CONST PMINIDUMP_EXCEPTION_INFORMATION ExceptionParam, OPTIONAL
										   IN CONST PMINIDUMP_USER_STREAM_INFORMATION UserStreamParam, OPTIONAL
										   IN CONST PMINIDUMP_CALLBACK_INFORMATION CallbackParam OPTIONAL
										   );
tstring  gszDumpFilePath;
tstring  gszDumpName;



LONG WINAPI MyUnhandledExceptionFilter(_EXCEPTION_POINTERS* pExceptionInfo)
{
	BOOL bMiniDumpSuccessful; 
	DWORD dwBufferSize = MAX_PATH; 
	HANDLE hDumpFile=NULL; 
	SYSTEMTIME stLocalTime; 
	MINIDUMP_EXCEPTION_INFORMATION ExpParam; 
	ErrorPrinter_OutputDebugString ErrorLog;

	

	TCHAR  strPath[511];
	GetModuleFileName(NULL,strPath,MAX_PATH);

	//dll path
	TCHAR dbgdllpath[512];
	strcpy_s_t(dbgdllpath,512,strPath);
	TCHAR * pName = strrchr_t(dbgdllpath, '\\') + 1;
	if (gszDumpName.length() == 0)
	{
		gszDumpName = pName;
	}
	if (gszDumpFilePath.length() == 0) {
		TCHAR tmp = pName[0];
		*pName = 0;
		gszDumpFilePath = dbgdllpath;
		*pName = tmp;
	}
	strcpy_s_t(pName, MAX_PATH,_T("dbghelp.dll"));
	

	//dump file name
	tstring szFullPath;
	GetLocalTime( &stLocalTime );
	
	
	ErrorLog(szFullPath,_T("%s%s-%04d%02d%02d-%02d%02d%02d-%ld-%ld.dmp"),
		gszDumpFilePath.c_str(),gszDumpName.c_str(),
		stLocalTime.wYear, stLocalTime.wMonth, stLocalTime.wDay, 
		stLocalTime.wHour, stLocalTime.wMinute, stLocalTime.wSecond, 
		GetCurrentProcessId(), GetCurrentThreadId());

	ErrorLog(_T("MyUnhandledExceptionFilter Begin %s "),szFullPath.c_str());

	hDumpFile = CreateFile(szFullPath.c_str(), GENERIC_READ|GENERIC_WRITE, 
		FILE_SHARE_WRITE|FILE_SHARE_READ, 0, CREATE_ALWAYS, 0, 0); 
	if(hDumpFile==NULL)
	{
		ErrorLog(_T("创建内存转储文件失败err=%d,(%s)"),GetLastError(),szFullPath.c_str());
	}
	ExpParam.ThreadId = GetCurrentThreadId(); 
	ExpParam.ExceptionPointers = pExceptionInfo; 
	ExpParam.ClientPointers = TRUE; 

	HMODULE hDll=NULL;
	hDll=::LoadLibrary(_T("dbghelp.dll"));
	if (hDll == NULL)
	{
		hDll = ::LoadLibrary(dbgdllpath);
	}
	if (hDll == NULL)
	{
		return -1;
	}
	pMiniDumpWriteDump MyMiniDumpWriteDump = (pMiniDumpWriteDump)::GetProcAddress(hDll,"MiniDumpWriteDump");
	if (MyMiniDumpWriteDump==NULL)
	{
		ErrorLog(_T("MyMiniDumpWriteDump Null")); 
	}
	//MiniDumpWithFullMemory  MiniDumpWithDataSegs
	bMiniDumpSuccessful = (*MyMiniDumpWriteDump)(GetCurrentProcess(), GetCurrentProcessId(), 
		hDumpFile, MiniDumpWithFullMemory, &ExpParam, NULL, NULL); 
	CloseHandle(hDumpFile);
	//return EXCEPTION_CONTINUE_EXECUTION;
	//return EXCEPTION_CONTINUE_SEARCH; 
	//return EXCEPTION_EXECUTE_HANDLER;
	ErrorLog(_T("MyUnhandledExceptionFilter End %s "),szFullPath.c_str());
	return EXCEPTION_EXECUTE_HANDLER;
}

void MakeDump()
{
	__try
	{

		//SetUnhandledExceptionFilter(MyUnhandledExceptionFilter);
		*(char *)0=0;
		__leave;

	}
	__except (MyUnhandledExceptionFilter(GetExceptionInformation()))
	{

		//ErrorLog(_T("DumpCurProcess End... %s %s"),pszDumpFilePath,pszDumpName);
	}
}

void SetupExceptionDump()
{
	SetUnhandledExceptionFilter(MyUnhandledExceptionFilter);
}
void DumpCurProcess(TCHAR * pszDumpFilePath,TCHAR * pszDumpName)
{
	gszDumpFilePath=pszDumpFilePath;//_T("\\SystemRoot\\");
	gszDumpName=pszDumpName;
	ErrorPrinter_OutputDebugString ErrorLog;
	MakeDump();
	ErrorLog(_T("DumpCurProcess End... %s %s"),pszDumpFilePath,pszDumpName);

}

#define USEStackAnslyze 1

#ifdef USEStackAnslyze
void UserLevelStackAnslyze32(unsigned int Ebp,TCHAR * pCallInfo, ErrorPrinter & ErrorLog,BOOL bDump)
{
	DWORD pid = 0;
	HANDLE hThreadSnap, hThread;
	THREADENTRY32 te32;

	pid = GetCurrentProcessId();


	hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, pid);
	if (hThreadSnap == INVALID_HANDLE_VALUE)
	{
		ErrorLog(_T("CreateToolhelp32Snapshot  Err=%d Fail ...\n"),GetLastError());
		return ;
	}
	ErrorLog(_T("***************(%s) StackAnslyze Begin....***************\r\n"),pCallInfo);
	tstring szSvr;
	ErrorLog(szSvr,_T("SRV*%s*http://msdl.microsoft.com/download/symbols"),SymPath);
	gSymLoad.Init(szSvr,ErrorLog,tstring(SymOutPath));

	te32.dwSize = sizeof(THREADENTRY32);

	if (Thread32First(hThreadSnap, &te32)) {
		do {
			if (te32.th32OwnerProcessID != pid)
				continue;

			tstring szHead;
			ErrorLog(szHead,_T("thread(%d):"),te32.th32ThreadID);

			if (te32.th32ThreadID == GetCurrentThreadId())
			{
				UserLevelThreadStackAnslyze32(NULL,(TCHAR *)szHead.c_str(),ErrorLog);
				continue;
			}

			hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, te32.th32ThreadID);
			if (hThread == NULL)
			{
				ErrorLog(_T("OpenThread te32.th32ThreadID(%d) Err=%d Fail ...\n"),te32.th32ThreadID,GetLastError());
				continue;
			}
			ErrorLog(szHead,_T("thread(id=%d hThread=%x):"),te32.th32ThreadID,hThread);
			UserLevelThreadStackAnslyze32(hThread,(TCHAR *)szHead.c_str(),ErrorLog);


			CloseHandle(hThread);
		}while(Thread32Next(hThreadSnap, &te32));
	}

	CloseHandle(hThreadSnap);

	ErrorLog(_T("***************(%s) StackAnslyze End....***************\r\n"),pCallInfo);
	if(bDump)
	{
		DumpCurProcess(DumpPath,pCallInfo);
	}
	gSymLoad.Close();
	
	return ;
}

#else
void UserLevelStackAnslyze32(unsigned int Ebp,TCHAR * pCallInfo, ErrorPrinter & ErrorLog,BOOL bDump=TRUE)
{
	return;
}
#endif

void UserLevelStackAnslyze64(unsigned int rbp,TCHAR * pCallInfo, ErrorPrinter & ErrorLog)
{
	return;
}