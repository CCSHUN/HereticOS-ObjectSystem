#ifdef WIN32
#include "windows.h"
#else
#include <ntddk.h>
#include "windef.h"
#include "image.h"
#endif



#define SIZE_OF_NT_SIGNATURE sizeof(DWORD)
//PE文件头
#define PEFHDROFFSET(a) ((PIMAGE_FILE_HEADER)((BYTE*)a+ ((PIMAGE_DOS_HEADER)a)->e_lfanew +SIZE_OF_NT_SIGNATURE))
//可选头
#define OPTHDROFFSET(a) ((PIMAGE_OPTIONAL_HEADER)((LPBYTE)PEFHDROFFSET(a)+sizeof(IMAGE_FILE_HEADER)))
//段头
#define SECTIONHDROFFSET(a) (PIMAGE_SECTION_HEADER)((LPBYTE)OPTHDROFFSET(a)+sizeof(IMAGE_OPTIONAL_HEADER))
//SECHDROFFSET

int NumOfSections(PVOID lpFile)
{
	return ((PIMAGE_FILE_HEADER)(PEFHDROFFSET(lpFile)))->NumberOfSections;
}

int Mystrcmp(char * pStr,char * pStr1)
{
	UINT i=0;
	for(i=0;(pStr[i]!=0)&&(pStr1[i]!=0);i++)
	{
		if(pStr[i]>pStr1[i]) return 1;

		if(pStr[i]<pStr1[i]) return -1;
	}

	if((pStr[i]==0)&&(pStr1[i]==0)) return 0;

	if(pStr[i]==0) return -1;

	if(pStr1[i]==0) return 1;

	return 2;
}

void * MyGetProcAddressFromRav(BYTE * pRvaBuf,char * pFuncName)
{
	PIMAGE_DOS_HEADER pDosHeader;
	PIMAGE_OPTIONAL_HEADER32 pOpHeader=(PIMAGE_OPTIONAL_HEADER32)OPTHDROFFSET(pRvaBuf);
	PIMAGE_EXPORT_DIRECTORY pExportTable=(PIMAGE_EXPORT_DIRECTORY)(pRvaBuf+pOpHeader->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
	USHORT ord=0;
	char * pCurFuncName=NULL;
	UINT i=0;
	if(pOpHeader->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size==0) return NULL;
	for(i=0;i<pExportTable->NumberOfNames;i++)
	{
		ord=((USHORT *)(pRvaBuf+pExportTable->AddressOfNameOrdinals))[i];
		pCurFuncName=(char *)(pRvaBuf+((DWORD*)(pRvaBuf+pExportTable->AddressOfNames))[i]);
		if(Mystrcmp(pCurFuncName,pFuncName)==0)
		{
			return ((DWORD *)(pRvaBuf+pExportTable->AddressOfFunctions))[ord]+pRvaBuf;
		}
	}

	return NULL;
}

PVOID MyGetEntryPointAddress(BYTE * pRvaBuf)
{
	PIMAGE_DOS_HEADER pDosHeader;
	PIMAGE_OPTIONAL_HEADER32 pOpHeader=(PIMAGE_OPTIONAL_HEADER32)OPTHDROFFSET(pRvaBuf);
	
	return (PVOID)pOpHeader->AddressOfEntryPoint;
}


//************************************************************************      
// 函数名称: Alig     
// 函数说明：返回一个边界对齐的地址     
// 作 成 者：叶树深    
// 作成日期：2015/05/11     
// 返 回 值:      
// 参    数:      
//************************************************************************  
#define AligU(n, dwFactor) Alig(n, dwFactor, TRUE)
#define AligD(n, dwFactor) Alig(n, dwFactor, FALSE)
ULONG Alig(ULONG n, ULONG dwFactor, BOOL bUp/* 是否是向上对齐 */)
{
	CONST ULONG r = n % dwFactor;
	if ( 0 == r )
	{
		return n;
	}

	n -= r;
	if ( bUp )
	{
		n += dwFactor;
	}

	return n;
}

//************************************************************************      
// 函数名称: Rva2Raw     
// 函数说明：返回虚拟地址偏移对应 PE文件的偏移     
// 作 成 者：叶树深    
// 作成日期：2015/05/11     
// 返 回 值:      
// 参    数:      
//************************************************************************  
ULONG WINAPI Rva2Raw(PVOID pMem, ULONG dwRva)
{
	PIMAGE_DOS_HEADER pDosH = (PIMAGE_DOS_HEADER)pMem;
	PIMAGE_NT_HEADERS pNtH = (PIMAGE_NT_HEADERS)((UINT_PTR)pDosH + pDosH->e_lfanew);
	PIMAGE_SECTION_HEADER pSectH = IMAGE_FIRST_SECTION(pNtH);
	ULONG dwRaw = (ULONG)-1;
	ULONG dwNumOfSect = pNtH->FileHeader.NumberOfSections;

	if ( dwRva < pSectH->VirtualAddress )
	{
		return dwRva;
	}

	while ( dwNumOfSect-- )
	{
		ULONG b = pSectH->VirtualAddress;
		ULONG e = AligU(b + pSectH->Misc.VirtualSize, pNtH->OptionalHeader.SectionAlignment);

		if ( dwRva >= b && dwRva < e )
		{
			dwRaw = dwRva - pSectH->VirtualAddress + pSectH->PointerToRawData;
			break;
		}

		pSectH++;
	}

	return dwRaw;
}


//************************************************************************      
// 函数名称: Rva2SecOffset     
// 函数说明：返回虚拟地址偏移对应 段内偏移     
// 作 成 者：叶树深    
// 作成日期：2015/05/11     
// 返 回 值:      
// 参    数:      
//************************************************************************  
ULONG WINAPI Rva2SecOffset(PVOID pMem, ULONG dwRva)
{
	PIMAGE_DOS_HEADER pDosH = (PIMAGE_DOS_HEADER)pMem;
	PIMAGE_NT_HEADERS pNtH = (PIMAGE_NT_HEADERS)((UINT_PTR)pDosH + pDosH->e_lfanew);
	PIMAGE_SECTION_HEADER pSectH = IMAGE_FIRST_SECTION(pNtH);
	ULONG dwRaw = (ULONG)-1;
	ULONG dwNumOfSect = pNtH->FileHeader.NumberOfSections;

	if ( dwRva < pSectH->VirtualAddress )
	{
		return dwRva;
	}

	while ( dwNumOfSect-- )
	{
		ULONG b = pSectH->VirtualAddress;
		ULONG e = AligU(b + pSectH->Misc.VirtualSize, pNtH->OptionalHeader.SectionAlignment);

		if ( dwRva >= b && dwRva < e )
		{
			dwRaw = dwRva - pSectH->VirtualAddress;
			break;
		}

		pSectH++;
	}

	return dwRaw;
}
