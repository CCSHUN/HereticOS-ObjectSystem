#pragma once
#include "BaseFunctionTool.h"
#include "TextIoSystem.h"

#define LoadSymMaxWaitTime 10000
class CSymLoader
{
public:
	CSymLoader(void);
	~CSymLoader(void);
	BOOL Init(tstring & szSvrPath,ErrorPrinter & ErrorLog,tstring & szOutPath=tstring(_T("")));
	BOOL Close();
	BOOL GetDllSymInfo(TCHAR * pDll,TCHAR * pOutPath,BOOL bWait=TRUE,DWORD nWaitTime=10000);
	BOOL GetAddressInfo(DWORD64 pAddress,OUT tstring & szInfo);
	BOOL GetAddressInfo(tstring & szModuleName,DWORD64 pAddress,VOID * pModuleBaseAddress,DWORD64 nSizeOfImage,OUT tstring & szInfo,unsigned int nMaxWait=LoadSymMaxWaitTime);
	BOOL AsynLoadSym(tstring & szModuleName,VOID * pModuleBaseAddress,DWORD64 nSizeOfImage);
};
