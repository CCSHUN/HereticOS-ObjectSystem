#pragma once
//mylisp输入输出系统
#include "BaseFunctionTool.h"

#include "AutoLock.h"
#include "stdio.h"
#include <stdarg.h>

class PrinterProxyInterface
{
public:
	PrinterProxyInterface(){};
	~PrinterProxyInterface(){};
	virtual void Output(const TCHAR * pMsg){};
	virtual void Input(const TCHAR * pMsg){};
	virtual const TCHAR * GetInput(tstring & szInput){return NULL;};
	virtual const TCHAR * GetOutput(tstring & szOutput){return NULL;};
protected:

private:
};

class PrinterProxyConsole :public PrinterProxyInterface
{
public:
	PrinterProxyConsole(){};
	~PrinterProxyConsole(){};
	void Output(const TCHAR * pMsg)
	{
		printf_t(pMsg);
	}
	const TCHAR * GetInput(tstring & szInput)
	{
		TCHAR szMsg[64*1024];
		gets_s_t(szMsg,64*1024);
		szInput=szMsg;
		return szInput.c_str();
	}
protected:

private:
};




class PrinterProxyOutputFile :public PrinterProxyInterface
{
public:
	FILE* m_fp;

	PrinterProxyOutputFile(){
		m_fp=NULL;
	};

	~PrinterProxyOutputFile(){
		if(m_fp)
		{
			DWORD nEnd={0};
			fwrite(&nEnd,4,1,m_fp); 
			fclose(m_fp);
			m_fp=NULL;
		}
	};


	void operator()(TCHAR * pszFilePath){
		m_fp=fopen_t(pszFilePath,_T("w+b"));
		if(sizeof(TCHAR)==2)
		{
			unsigned short nHead=0xfeff;
			fwrite(&nHead,2,1,m_fp); 
		}
		
	};

	void Output(const TCHAR * pMsg)
	{
		if(m_fp)
		{
			
			fwrite(pMsg,(strlen_t(pMsg)),sizeof(TCHAR),m_fp); 
			fflush(m_fp);
		}
		
	}
	const TCHAR * GetInput(tstring & szInput)
	{
		TCHAR szMsg[64*1024];
		gets_s_t(szMsg,64*1024);
		szInput=szMsg;
		return szInput.c_str();
	}
protected:

private:
};

#ifndef _LINUX_
class PrinterProxyCom :public PrinterProxyInterface
{
public:
	PrinterProxyCom(){};
	~PrinterProxyCom(){};
	list<tstring> m_OutputQueue;
	list<tstring> m_InputQueue;
	CCriticalSectionStack m_InputLock;
	CCriticalSectionStack m_OutputLock;
	void Output(const TCHAR * pMsg)
	{
		CAutoStackLock lk(&m_OutputLock,_T("PrinterProxyCom::Output"));
		m_OutputQueue.push_back(tstring(pMsg));
	}
	void Input(const TCHAR * pMsg){
		CAutoStackLock lk(&m_InputLock,_T("PrinterProxyCom::Input"));
		m_InputQueue.push_back(tstring(pMsg));
	}
	BOOL WaitInputer()
	{
		CAutoStackLock lk;
		for(;;)
		{
			lk.Lock(&m_InputLock,NULL);
			if(m_InputQueue.size()) return TRUE;
			lk.UnLock();
			Sleep(200);
		}
		return FALSE;
	}
	const TCHAR * GetInput(tstring & szInput){ 
		if(WaitInputer())
		{
			CAutoStackLock lk(&m_InputLock,_T("PrinterProxyCom::GetInput"));
			szInput=m_InputQueue.front();
			m_InputQueue.pop_front();
			return szInput.c_str(); 
		}
		return NULL;
	}
	const TCHAR * GetOutput(tstring & szOutput){
		CAutoStackLock lk(&m_OutputLock,_T("PrinterProxyCom::GetOutput"));
		if(m_OutputQueue.size())
		{
			szOutput=m_OutputQueue.front();
			m_OutputQueue.pop_front();
			return szOutput.c_str();
		}
		return NULL;
	}
protected:

private:
};


class PrinterProxyOutputDebugString :public PrinterProxyInterface
{
public:
	PrinterProxyOutputDebugString() {};
	~PrinterProxyOutputDebugString() {};
	void Output(const TCHAR * pMsg)
	{
		OutputDebugString(pMsg);
	}
	const TCHAR * GetInput(tstring & szInput)
	{
		TCHAR szMsg[64 * 1024];
		gets_s_t(szMsg, 64 * 1024);
		szInput = szMsg;
		return szInput.c_str();
	}
protected:

private:
};
#endif

class ErrorPrinter
{
public:
	PrinterProxyInterface * m_pIo;
#define LogBugLen 4096*16

	enum ErrorType
	{
		ErrorType_Fail=0x1,
		ErrorType_OK=0x2,
		ErrorType_Info=0x4,
		ErrorType_Log1=0x8,
		ErrorType_Log2=0x10,
		ErrorType_Log3=0x20,
		ErrorType_Log4=0x40,
		ErrorType_Log5=0x80,
		ErrorType_Log6=0x100,
		ErrorType_Log7=0x200,
		ErrorType_Log8=0x400,

		ErrorType_DebugOut=0x800,
	};
	__int64 m_AllowType;
	map<tstring,__int64,less<tstring>> m_AllowTypeInfo;
	ErrorPrinter(){
		m_pIo=NULL;
		m_AllowTypeInfo[tstring(_T("Fail"))]=ErrorType_Fail;
		m_AllowTypeInfo[tstring(_T("GetValOK"))]=ErrorType_OK;
		m_AllowTypeInfo[tstring(_T("GetValAll"))]=ErrorType_Fail|ErrorType_OK;
		m_AllowTypeInfo[tstring(_T("执行错误"))]=ErrorType_Fail;

		m_AllowTypeInfo[tstring(_T("求值成功"))]=ErrorType_OK;
		m_AllowTypeInfo[tstring(_T("所有求值过程"))]=ErrorType_Fail|ErrorType_OK;
		m_AllowTypeInfo[tstring(_T("日志1"))]=ErrorType_Log1;
		m_AllowTypeInfo[tstring(_T("日志2"))]=ErrorType_Log2;

		m_AllowTypeInfo[tstring(_T("日志3"))]=ErrorType_Log3;
		m_AllowTypeInfo[tstring(_T("日志4"))]=ErrorType_Log4;
		m_AllowTypeInfo[tstring(_T("日志5"))]=ErrorType_Log5;
		m_AllowTypeInfo[tstring(_T("日志6"))]=ErrorType_Log6;

		m_AllowTypeInfo[tstring(_T("日志7"))]=ErrorType_Log7;
		m_AllowTypeInfo[tstring(_T("日志8"))]=ErrorType_Log8;

		m_AllowType=m_AllowTypeInfo[tstring(_T("执行错误"))]|ErrorType_DebugOut;
	};
	~ErrorPrinter(){};
	void SetIo(PrinterProxyInterface * InOutPrinterProxy)
	{
		m_pIo=InOutPrinterProxy;
	}

	void operator()(ErrorType  nType,const TCHAR * line,... )
	{
		if((nType&m_AllowType)&&(m_pIo!=NULL)&&(!IsBadReadPtr(m_pIo,sizeof(PrinterProxyInterface))))
		{
			TCHAR cpBuf[LogBugLen];	
			memset(cpBuf,0,sizeof(cpBuf));
			//sprintf_s(cpBuf,2048,"log:",GetCurrentThreadId());
			va_list	vl;
			va_start( vl, line );
			size_t len=strlen_t(cpBuf);
			vsprintf_s_t(cpBuf+len,LogBugLen-len-6, line, vl );
			va_end( vl);
			strcat_s_t(cpBuf, LogBugLen,_T("\r\n"));
			//printf(cpBuf);

			m_pIo->Output(cpBuf);
			return ;
		}
	}
	void operator()(const TCHAR * line,... )
	{
		if((m_pIo!=NULL)&&(!IsBadReadPtr(m_pIo,sizeof(PrinterProxyInterface))))
		{
			TCHAR cpBuf[LogBugLen];	
			memset(cpBuf,0,sizeof(cpBuf));
			//sprintf_s(cpBuf,2048,"log:",GetCurrentThreadId());
			va_list	vl;
			va_start( vl, line );
			size_t len=strlen_t(cpBuf);
			vsprintf_s_t(cpBuf+len,LogBugLen-len-6, line, vl );
			va_end( vl);
			strcat_s_t(cpBuf, LogBugLen,_T("\r\n"));
			//printf(cpBuf);

			m_pIo->Output(cpBuf);
			return ;
		}
	}
	void operator()(tstring & szDst)
	{
		if ((m_pIo != NULL) && (!IsBadReadPtr(m_pIo, sizeof(PrinterProxyInterface))))
		{
			m_pIo->Output(szDst.c_str());
			return;
		}
	}

	template<typename T>
	void operator()(basic_string<char, char_traits<char>, T> & szDst, const char * fmt, ...)
	{
		char cpBuf[LogBugLen];	
		memset(cpBuf,0,sizeof(cpBuf));
		//swprintf_s(cpBuf,2048,L"%s tid=%d log:",szHead,GetCurrentThreadId());
		va_list	vl;
		va_start( vl, fmt );
		size_t len=strlen(cpBuf);
		vsprintf_s(cpBuf+len,LogBugLen-len, fmt, vl );
		va_end( vl);
		//strcat_t(cpBuf,_T("\r\n"));
		szDst=cpBuf;
		return ;
	}
	template<typename T>
	void operator()(basic_string<wchar_t, char_traits<wchar_t>, T> & szDst, const WCHAR * fmt, ...)
	{
		WCHAR cpBuf[LogBugLen];
		memset(cpBuf, 0, sizeof(cpBuf));
		//swprintf_s(cpBuf,2048,L"%s tid=%d log:",szHead,GetCurrentThreadId());
		va_list	vl;
		va_start(vl, fmt);
		size_t len = wcslen(cpBuf);
		vswprintf_s(cpBuf + len, LogBugLen - len, fmt, vl);
		va_end(vl);
		//strcat_t(cpBuf,_T("\r\n"));
		szDst = cpBuf;
		return;
	}
	

	//格式化追加到szDst
	void cat(string & szDst, const char * fmt, ...)
	{
		char cpBuf[LogBugLen];
		memset(cpBuf, 0, sizeof(cpBuf));
		//swprintf_s(cpBuf,2048,L"%s tid=%d log:",szHead,GetCurrentThreadId());
		va_list	vl;
		va_start(vl, fmt);
		size_t len = strlen(cpBuf);
		vsprintf_s(cpBuf + len, LogBugLen - len, fmt, vl);
		va_end(vl);
		//strcat_t(cpBuf,_T("\r\n"));
		szDst += cpBuf;
		return;
	}
	//格式化追加到szDst
	void cat(wstring & szDst, const WCHAR * fmt, ...)
	{
		WCHAR cpBuf[LogBugLen];
		memset(cpBuf, 0, sizeof(cpBuf));
		//swprintf_s(cpBuf,2048,L"%s tid=%d log:",szHead,GetCurrentThreadId());
		va_list	vl;
		va_start(vl, fmt);
		size_t len = wcslen(cpBuf);
		vswprintf_s(cpBuf + len, LogBugLen - len, fmt, vl);
		va_end(vl);
		//strcat_t(cpBuf,_T("\r\n"));
		szDst += cpBuf;
		return;
	}

	bool OpenLog(tstring & szLogName)
	{
		map<tstring,__int64,less<tstring>>::iterator itType=m_AllowTypeInfo.find(szLogName);
		if(itType!=m_AllowTypeInfo.end())
		{
			m_AllowType|=itType->second;
			return true;
		}
		return false;
	}
	bool CloseLog(tstring & szLogName)
	{
		map<tstring,__int64,less<tstring>>::iterator itType=m_AllowTypeInfo.find(szLogName);
		if(itType!=m_AllowTypeInfo.end())
		{
			m_AllowType&=(~itType->second);
			return true;
		}
		return false;
	}
};

template<typename IOType>
class ErrorPrinterT :
	public ErrorPrinter
{
public:
	IOType m_Io;
	ErrorPrinterT(){
		SetIo(&m_Io);
	};
	template<typename T>
	ErrorPrinterT(T & Par){
		m_Io(Par);
		SetIo(&m_Io);
	};

	template<typename T>
	ErrorPrinterT(T  Par){
		m_Io(Par);
		SetIo(&m_Io);
	};

	~ErrorPrinterT(){};
protected:
	
private:
};

#ifndef _LINUX_
typedef  ErrorPrinterT<PrinterProxyOutputDebugString> ErrorPrinter_OutputDebugString;
#endif

typedef  ErrorPrinterT<PrinterProxyOutputFile> ErrorPrinter_OutputFile;
typedef  ErrorPrinterT<PrinterProxyConsole> ErrorPrinter_Console;