
// stdafx.cpp : 只包括标准包含文件的源文件
// WhiteboxTestingPlatform.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"
#include "MainFrm.h"

CObjectSystemInterface * gpObjectSystem;




CDebugFunctionModule gDebugTool;
CYDConfig	gConfig;

#include "ObjectSystem_SoapClient.h"
CObjectSystem_SoapClient gSoapObjectSystem;

#include "ObjectSystem_Local.h"
CObjectSystem_Local gobjsys;

CMainFrame * g_pOutWnd;

HINSTANCE ghInstance;

//((CMainFrame *)AfxGetApp()->GetMainWnd())->WriteStringToOutputWnd(szErr1.c_str());

/*
HMODULE AfxLoadSystemLibraryUsingFullPath(const WCHAR *pszLibrary)  
{  
	WCHAR wszLoadPath[MAX_PATH+1];  
	if (::GetSystemDirectoryW(wszLoadPath, _countof(wszLoadPath)) == 0)  
	{  
		return NULL;  
	}  
	if (wszLoadPath[wcslen(wszLoadPath)-1] != L'//')  
	{  
		if (wcscat_s(wszLoadPath, _countof(wszLoadPath), L"//") != 0)  
		{  
			return NULL;  
		}  
	}  
	if (wcscat_s(wszLoadPath, _countof(wszLoadPath), pszLibrary) != 0)  
	{  
		return NULL;  
	}  
	return(::AfxCtxLoadLibraryW(wszLoadPath));  
}
*/
BOOL WndLog( const char * szHead,const char * line,... )
{
	char cpBuf[4096];	
	memset(cpBuf,0,sizeof(cpBuf));
	sprintf_s(cpBuf,2048,"%s tid=%d log:",szHead,GetCurrentThreadId());
	va_list	vl;
	va_start( vl, line );
	unsigned int len=strlen(cpBuf);
	vsprintf_s(cpBuf+len,4090-len, line, vl );
	va_end( vl);
	strcat(cpBuf,"\r\n");
	//OutputDebugStringA(cpBuf);
	CString cpErr=(TCHAR *)CMyString((char *)&cpBuf[0],4096);
	

	if(g_pOutWnd)
	{
		g_pOutWnd->WriteStringToOutputWnd(cpErr);
	}

	return TRUE;
}
BOOL WndLog( const WCHAR * szHead,const WCHAR * line,... )
{
	WCHAR cpBuf[4096];	
	memset(cpBuf,0,sizeof(cpBuf));
	swprintf_s(cpBuf,2048,L"%s tid=%d log:",szHead,GetCurrentThreadId());
	va_list	vl;
	va_start( vl, line );
	unsigned int len=wcslen(cpBuf);
	vswprintf_s(cpBuf+len,4090-len, line, vl );
	va_end( vl);
	wcscat(cpBuf,L"\r\n");
	CString cpErr=(TCHAR *)CMyString((WCHAR *)&cpBuf[0],4096);

	if(g_pOutWnd)
	{
		g_pOutWnd->WriteStringToOutputWnd(cpErr);
	}

	return TRUE;
}