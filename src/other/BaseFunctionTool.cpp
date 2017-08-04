///////////////////////////////////////////////////////////////////////////////////
//	Copyright 2017 shushen,ye
//	Licensed under the Apache License, Version 2.0 (the "License");
//	you may not use this file except in compliance with the License.
//	You may obtain a copy of the License at
//	http://www.apache.org/licenses/LICENSE-2.0
//	Unless required by applicable law or agreed to in writing, software
//	distributed under the License is distributed on an "AS IS" BASIS,
//	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//	See the License for the specific language governing permissions and
//	limitations under the License.
///////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BaseFunctionTool.h"




#ifdef _DLL_SHARE_OBJECT

#include ".\TextIoSystem.h"
#include ".\sharemem\ShareObject.h"
//#include ".\AutoLock.h"


#ifdef _DEBUG

#ifndef Error
static ErrorPrinter_OutputDebugString g_Error;
#define Error g_Error

#endif

//#define  Error()


#else
//static ErrorPrinter_OutputDebugString Error;
#define  Error()


#endif

CShareObject<ShareHeap> g_ShareHeap;
ShareHeap * g_pShareHeap = NULL;
BOOL bShareHeapInitOk = YssAllocatorHeapCreate(NULL);

BOOL YssAllocatorHeapCreate(HANDLE hHeap)
{
	if (g_ShareHeap.IsValid()==FALSE)
	{
		if (g_ShareHeap.init(_T("YssShare"),TRUE,FALSE))
		{
			if (g_ShareHeap->gYss_share_allocator_Heap[0] == NULL)
			{
				g_ShareHeap.Lock();

				ErrorPrinter_OutputDebugString err;
				tstring szLog=_T("YssAllocatorHeapCreate init ");
				for (unsigned int i = 0; i<HEAP_COUNT;i++)
				{
					g_ShareHeap->gYss_share_allocator_Heap[i] = HeapCreate(HEAP_GENERATE_EXCEPTIONS, 0, 0);
					ULONG  HeapFragValue = 2;

					if (!HeapSetInformation(g_ShareHeap->gYss_share_allocator_Heap[i],
						HeapCompatibilityInformation,
						&HeapFragValue,
						sizeof(HeapFragValue))
						)
					{
						Error(_T("HeapSetInformation Fail ERR=(%d)\n"), GetLastError());
					}
					err.cat(szLog, _T("%u:0x%08x "), i, g_ShareHeap->gYss_share_allocator_Heap[i]);
				}
				
				
				g_ShareHeap->gYss_share_allocator_ProcessHeap = ::GetProcessHeap();
				err.cat(szLog, _T("g:0x%08x "), g_ShareHeap->gYss_share_allocator_ProcessHeap);
				Error(_T("%s"), szLog.c_str());
				g_pShareHeap = (ShareHeap *)g_ShareHeap;
				g_ShareHeap.UnLock();
			}
			else
			{
				g_pShareHeap = (ShareHeap *)g_ShareHeap;
			}
		}
	}

	if (hHeap) {
		g_ShareHeap->gYss_share_allocator_Heap[0] = hHeap;
		return TRUE;
	}
	
	
	return TRUE;
}




#endif


char * szLocaleString=setlocale(LC_CTYPE, "");

#ifdef ZIP
//#define _CRT_NONSTDC_NO_DEPRECATE
//#define _CRT_SECURE_NO_DEPRECATE

//#pragma comment(lib,"./zlib/lib/zdll.lib")

/*
BOOL CBase64Zip::Base64ZipCompress(IN unsigned char * pBuf,IN unsigned long nLen,OUT string & szOutData)
{
	BOOL bOk=FALSE;
	unsigned long bufLen=nLen+4096;
	unsigned char * buf=new unsigned char[bufLen+64];
	memcpy(buf,"yesszip#",8);
	*((uLongf *)(buf+8))=nLen;
	std::auto_ptr<unsigned char> mem(buf);
	if(compress(buf+8+sizeof(uLongf), &bufLen, pBuf, nLen)== Z_OK)
	{
		Base64<char> base;
		bufLen += 8 + sizeof(uLongf);
		int buf1len=bufLen*2;
		char * buf1=new char[buf1len];
		std::auto_ptr< char> mem1(buf1);
		base.Base64EnCode(buf,bufLen,buf1,buf1len);
		bOk=TRUE;
		szOutData=(char *)buf1;
	}
	return bOk;
}


BOOL CBase64Zip::Base64ZipCompress(IN unsigned char * pBuf,IN unsigned long nLen,OUT wstring & szOutData)
{
	BOOL bOk=FALSE;
	unsigned long bufLen=nLen+4096;
	unsigned char * buf=new unsigned char[bufLen+64];
	memcpy(buf,"yesszip#",8);
	*((uLongf *)(buf+8))=nLen;
	std::auto_ptr<unsigned char> mem(buf);
	if(compress(buf+8+sizeof(uLongf), &bufLen, pBuf, nLen)== Z_OK)
	{
		Base64<WCHAR> base;
		bufLen+=8+sizeof(uLongf);
		int buf1len=bufLen*2;
		WCHAR * buf1=new WCHAR[buf1len];
		std::auto_ptr<WCHAR> mem1(buf1);
		base.Base64EnCode(buf,bufLen,buf1,buf1len);
		bOk=TRUE;
		szOutData= buf1;
	}
	return bOk;
}
 */

#endif

