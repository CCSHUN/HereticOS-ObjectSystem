#ifndef __PETOOL_H_VERSION__
#define __PETOOL_H_VERSION__ 

void * MyGetEntryPointAddress(BYTE * pRvaBuf);
void * MyGetProcAddressFromRav(BYTE * pRvaBuf,char * pFuncName);
extern "C" ULONG WINAPI Rva2Raw(PVOID pMem, ULONG dwRva);
extern "C" ULONG WINAPI Rva2SecOffset(PVOID pMem, ULONG dwRva);

#endif