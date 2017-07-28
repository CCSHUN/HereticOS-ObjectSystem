#include "StdAfx.h"
#include "DebugFunctionModule.h"


#include <dbghelp.h>
#pragma comment(lib, "dbghelp.lib")

CDebugFunctionModule::CDebugFunctionModule(void)
{
}

CDebugFunctionModule::~CDebugFunctionModule(void)
{
}



typedef BOOL (WINAPI * pMiniDumpWriteDump)(IN HANDLE hProcess,IN DWORD ProcessId,IN HANDLE hFile,IN MINIDUMP_TYPE DumpType,
										   IN CONST PMINIDUMP_EXCEPTION_INFORMATION ExceptionParam, OPTIONAL
										   IN CONST PMINIDUMP_USER_STREAM_INFORMATION UserStreamParam, OPTIONAL
										   IN CONST PMINIDUMP_CALLBACK_INFORMATION CallbackParam OPTIONAL
										   );

LONG WINAPI MyUnhandledExceptionFilter(_EXCEPTION_POINTERS* pExceptionInfo)
{
	BOOL bMiniDumpSuccessful; 
	DWORD dwBufferSize = MAX_PATH; 
	HANDLE hDumpFile=NULL; 
	SYSTEMTIME stLocalTime; 
	MINIDUMP_EXCEPTION_INFORMATION ExpParam; 

	TCHAR  strPath[511];
	GetModuleFileName(NULL,strPath,MAX_PATH);

	//dll path
	TCHAR dbgdllpath[512];
	strcpy_t(dbgdllpath,strPath);
	//_DebugOutput(_T("debugtool"),_T("debugtool Dump path=%s"),dbgdllpath);
	strcpy_t(strrchr_t(dbgdllpath,'\\')+1,_T("dbghelp.dll"));
	//_DebugOutput(_T("debugtool"),_T("debugtool Dump path=%s"),dbgdllpath);

	HMODULE dll=::LoadLibrary(dbgdllpath);
	_DebugOutput(_T("debugtool"),_T("debugtool Dump path=%s hDll=%x "),dbgdllpath,dll);
	pMiniDumpWriteDump MyMiniDumpWriteDump = (pMiniDumpWriteDump)::GetProcAddress(dll,"MiniDumpWriteDump");

	//dump file name
	TCHAR dumppath[1024];
	//strcpy(dumppath+3,strrchr(strPath,'\\')+1);
	strcpy_t(dumppath,strPath);
	//dumppath[0]='c';dumppath[1]=':';dumppath[2]='\\';
	GetLocalTime( &stLocalTime );
	TCHAR * pPos=strrchr_t(dumppath,'.');
	sprintf_s_t(pPos,512*sizeof(TCHAR)-(pPos-dumppath),_T("-%04d%02d%02d-%02d%02d%02d-%ld-%ld.dmp"),
		stLocalTime.wYear, stLocalTime.wMonth, stLocalTime.wDay, 
		stLocalTime.wHour, stLocalTime.wMinute, stLocalTime.wSecond, 
		GetCurrentProcessId(), GetCurrentThreadId());
	_DebugOutput(_T("debugtool"),_T("debugtool Dump path=%s"),dbgdllpath);

	hDumpFile = CreateFile(dumppath, GENERIC_READ|GENERIC_WRITE, 
		FILE_SHARE_WRITE|FILE_SHARE_READ, 0, CREATE_ALWAYS, 0, 0); 
	if(hDumpFile==INVALID_HANDLE_VALUE)
	{
		_DebugOutput(_T("debugtool"),_T("创建内存转储文件失败 file=%s  nError=%d"),dumppath,GetLastError());
		return EXCEPTION_CONTINUE_SEARCH; 
	}
	ExpParam.ThreadId = GetCurrentThreadId(); 
	ExpParam.ExceptionPointers = pExceptionInfo; 
	ExpParam.ClientPointers = TRUE; 

	
	if (MyMiniDumpWriteDump==NULL)
	{
		_DebugOutput("debugtool","MyMiniDumpWriteDump Null");
		_DebugOutput(_T("debugtool"),dumppath);
		return EXCEPTION_CONTINUE_SEARCH; 
	}

	bMiniDumpSuccessful = (*MyMiniDumpWriteDump)(GetCurrentProcess(), GetCurrentProcessId(), 
		hDumpFile, MiniDumpWithDataSegs, &ExpParam, NULL, NULL); 
	//CloseHandle(hDumpFile);
	return EXCEPTION_CONTINUE_SEARCH; 
}

BOOL CDebugFunctionModule::Log( const char * szHead,const char * line,... )
{
	char cpBuf[4096];	
	memset(cpBuf,0,sizeof(cpBuf));
	sprintf_s(cpBuf,2048,"%s tid=%d log:",szHead,GetCurrentThreadId());
	va_list	vl;
	va_start( vl, line );
	unsigned int len=strlen(cpBuf);
	vsprintf_s(cpBuf+len,4090-len, line, vl );
	va_end( vl);
	strcat(cpBuf,"\n");
	OutputDebugStringA(cpBuf);
	return TRUE;
}
BOOL CDebugFunctionModule::Log( const WCHAR * szHead,const WCHAR * line,... )
{
	WCHAR cpBuf[4096];	
	memset(cpBuf,0,sizeof(cpBuf));
	swprintf_s(cpBuf,2048,L"%s tid=%d log:",szHead,GetCurrentThreadId());
	va_list	vl;
	va_start( vl, line );
	unsigned int len=wcslen(cpBuf);
	vswprintf_s(cpBuf+len,4090-len, line, vl );
	va_end( vl);
	wcscat(cpBuf,L"\n");
	OutputDebugStringW(cpBuf);
	return TRUE;
}

BOOL CDebugFunctionModule::init(CModuleMgrInterface * pMgr)
{
	SetUnhandledExceptionFilter(MyUnhandledExceptionFilter);
	//*((int *)0)=1;
	return TRUE;
}
BOOL CDebugFunctionModule::close()
{
	return TRUE;
}