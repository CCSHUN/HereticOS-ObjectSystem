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
#include "Base64.h"



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
#define ZLIB_WINAPI

#include ".\zlib/include/zlib.h"  
//#pragma comment(lib,"./zlib/lib/zdll.lib")

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
		Base64 base;
		int buf1len=bufLen*2;
		unsigned char * buf1=new unsigned char[buf1len];
		std::auto_ptr<unsigned char> mem1(buf1);
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
		Base64 base;
		bufLen+=8+sizeof(uLongf);
		int buf1len=bufLen*2;
		unsigned char * buf1=new unsigned char[buf1len];
		std::auto_ptr<unsigned char> mem1(buf1);
		base.Base64EnCode(buf,bufLen,buf1,buf1len);
		bOk=TRUE;
		szOutData=(WCHAR *)CMyString((char *)buf1,buf1len+2);
	}
	return bOk;
}
  
BOOL CBase64Zip::Base64ZipUnCompress(IN string & inBuf,OUT vector<unsigned char> & OutBuf)
{
	//uLongf
	//uncompress(strDst, &dstLen, buf, bufLen);  
	Base64 base;
	unsigned char * pDstBuf=new unsigned char[inBuf.length()*2];
	std::auto_ptr<unsigned char> mem(pDstBuf);
	int nDstLen=inBuf.length()*2;
	base.Base64DeCode((unsigned char *)inBuf.c_str(),inBuf.length(),pDstBuf,nDstLen);
	if(memcmp(pDstBuf,"yesszip#",8)==0)
	{
		uLongf nZipDstLen=*((uLongf *)(pDstBuf+8));
		if(nZipDstLen>256*1024*1024)
		{
			//ÄÚ´æ³¬´óÁË
			return FALSE;
		}

		OutBuf.resize(nZipDstLen+4096);
		//unsigned char pZipDstBuf=new unsigned char[nDstLen+4096];
		//std::auto_ptr<unsigned char> mem(pZipDstBuf);
		int ret=uncompress(&OutBuf[0],&nZipDstLen,pDstBuf+8+sizeof(uLongf),nDstLen-8-sizeof(uLongf));
		if(ret==Z_OK)
		{
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CBase64Zip::Base64ZipUnCompress(IN wstring & inBuf,OUT vector<unsigned char> & OutBuf)
{
	string inbuf1=(char *)CMyString((WCHAR *)inBuf.c_str(),inBuf.length()*2);
	return Base64ZipUnCompress(inbuf1,OutBuf);
}

#endif


BOOL CXmlString::GetXMLStringFromtstring(OUT tstring & XmlString,IN tstring &SrcString )
{
	WCHAR * pSrcString=(WCHAR *)CMyString((TCHAR *)SrcString.c_str(),SrcString.length()*sizeof(TCHAR));
	XmlString.clear();
	for(unsigned int i=0;pSrcString[i]!=0;i++)
	{
		switch(pSrcString[i])
		{
		case '<':
			XmlString+=_T("&lt;");
			break;
		case  '>':
			XmlString+=_T("&gt;");
			break;
		case '&':
			XmlString+=_T("&amp;");
			break;
		case '\'':
			XmlString+=_T("&apos;");
			break;
		case '\"':
			XmlString+=_T("&quot;");
			break;
		case '\n':
			XmlString+=_T("&#10;");
			break;
		default:
			XmlString+=pSrcString[i];
			break;
		}
	}
	return TRUE;
}

BOOL CXmlString::GetStringFromXMLString(OUT tstring & String,IN tstring &XMLString )
{
	TCHAR * pSrcString=(TCHAR *)CMyString((TCHAR *)XMLString.c_str(),XMLString.length()*sizeof(TCHAR));
	String.clear();
	for(unsigned int i=0;pSrcString[i]!=0;i++)
	{
		if(strstr_t(pSrcString+i,_T("&lt;"))==pSrcString+i)
		{
			String+=_T("<");
		}else if(strstr_t(pSrcString+i,_T("&gt;"))==pSrcString+i)
		{
			String+=_T(">");
		}else if(strstr_t(pSrcString+i,_T("&amp;"))==pSrcString+i)
		{
			String+=_T("&");
		}else if(strstr_t(pSrcString+i,_T("&apos;"))==pSrcString+i)
		{
			String+=_T("\'");
		}else if(strstr_t(pSrcString+i,_T("&quot;"))==pSrcString+i)
		{
			String+=_T("\"");
		}else if(strstr_t(pSrcString+i,_T("&#10;"))==pSrcString+i)
		{
			String+=_T("\n");
		}else 
		{
			String+=pSrcString[i];
		}
		
	}
	return TRUE;
}

