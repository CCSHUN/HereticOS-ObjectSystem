#pragma once
//#include "windows.h"
#include "TextIoSystem.h"

extern void UserLevelStackAnslyze32(unsigned int Ebp, TCHAR * pCallInfo, ErrorPrinter & ErrorLog, BOOL bDump=TRUE);
extern void UserLevelStackAnslyze64(__int64 rbp, TCHAR * pCallInfo, ErrorPrinter & ErrorLog);
extern void SetupExceptionDump();
extern LONG WINAPI MyUnhandledExceptionFilter(_EXCEPTION_POINTERS* pExceptionInfo);

extern int filter(unsigned int code, struct _EXCEPTION_POINTERS *ep);