
// stdafx.cpp : 只包括标准包含文件的源文件
// CodeRender.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"




UINT DebugLevel=0xffffffff;

VOID
DebugPrint(
		   __in  ULONG DebugPrintLevel,
		   __in  PCHAR DebugMessage,
		   ...
		   )

{
	char  szMsg[1024];
	size_t len=0;
	va_list ap;

	va_start(ap, DebugMessage);

	if (DebugPrintLevel & DebugLevel)
	{
		//vDbgPrintEx(DPFLTR_IHVVIDEO_ID,DebugPrintLevel,DebugMessage,ap);
		//DbgPrint(DebugMessage, ap);
		memset(szMsg,0,1024);
		sprintf_s(szMsg,128,"l(%x[%d]) ",DebugPrintLevel,GetCurrentProcessId());
		_vsnprintf_s(szMsg+strlen(szMsg),1024-strlen(szMsg),1024-strlen(szMsg),DebugMessage,ap);
		OutputDebugStringA(szMsg);
	}

	va_end(ap);

}