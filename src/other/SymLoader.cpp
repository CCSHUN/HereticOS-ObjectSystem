//************************************************************************ 
// 公司: 2012-2015, DM. Co., Ltd.
// 文件名: SymLoader.cpp
// 作者: 叶树深 
// 版本: 1.0 
// 日期: 2015/05/12
// 功能描述: 加载符号，通过进程内地址查找可能有效的符号
// 其他备注:
// 维护历史:
//************************************************************************ 

#include "StdAfx.h"
#include "SymLoader.h"
#define DBGHELP_TRANSLATE_TCHAR
#include "dbghelp.h"
#pragma comment(lib,"Dbghelp.lib")
#include "Psapi.h"
#pragma comment(lib,"Psapi.lib")
#include "atlbase.h"
#include <objbase.h>
/*
SYMFLAG_CLR_TOKEN
0x00040000
The symbol is a CLR token.

SYMFLAG_CONSTANT
0x00000100
The symbol is a constant.

SYMFLAG_EXPORT
0x00000200
The symbol is from the export table.

SYMFLAG_FORWARDER
0x00000400
The symbol is a forwarder.

SYMFLAG_FRAMEREL
0x00000020
Offsets are frame relative.

SYMFLAG_FUNCTION
0x00000800
The symbol is a known function.

SYMFLAG_ILREL
0x00010000
The symbol address is an offset relative to the beginning of the intermediate language block. This applies to managed code only.

SYMFLAG_LOCAL
0x00000080
The symbol is a local variable.

SYMFLAG_METADATA
0x00020000
The symbol is managed metadata.

SYMFLAG_PARAMETER
0x00000040
The symbol is a parameter.

SYMFLAG_REGISTER
0x00000008
The symbol is a register. The Register member is used.

SYMFLAG_REGREL
0x00000010
Offsets are register relative.

SYMFLAG_SLOT
0x00008000
The symbol is a managed code slot. 

SYMFLAG_THUNK
0x00002000
The symbol is a thunk. 

SYMFLAG_TLSREL
0x00004000
The symbol is an offset into the TLS data area. 

SYMFLAG_VALUEPRESENT
0x00000001
The Value member is used.

SYMFLAG_VIRTUAL
*/
typedef struct _tagSymTypeInfo
{
	ULONG nFlag;
	TCHAR * pTypeInfo;
}SymTypeInfo,*PSymTypeInfo;

typedef struct _tagSymNameSet
{
	 SYMBOL_INFO	InfoSet;
	 __int64		nBeginAddress;
	 __int64		nEndAddress;
}SymNameSet,*PSymNameSet;

enum SymLibStatus
{
	NoFind,
	LoadOk,
};
typedef struct _tagSymNameArray
{
	map<tstring,_tagSymNameSet,less<tstring>> NameArray;
	tstring szVerInfo;
	__int64 nBeginAddress;
	__int64	nEndAddress;
	SymLibStatus	LibStatus;
	tstring szError;
}SymNameArray,*PSymNameArray;

typedef struct _tagSymModuleMap
{
	map<tstring,_tagSymNameArray,less<tstring> > ModuleArray;
}SymModuleMap,*PSymModuleMap;


SymTypeInfo gSymTypeInfo[]={
	SYMFLAG_CLR_TOKEN,_T("CLR token."),
	SYMFLAG_CONSTANT,_T("constant."),
	SYMFLAG_EXPORT,_T("export sym."),
	SYMFLAG_FORWARDER,_T("forwarder."),
	SYMFLAG_FRAMEREL,_T("frame relative."),
	SYMFLAG_FUNCTION,_T("function."),
	SYMFLAG_ILREL,_T("managed code only."),
	SYMFLAG_LOCAL,_T("local variable."),
	SYMFLAG_METADATA,_T("managed metadata."),
	SYMFLAG_PARAMETER,_T("parameter."),
	SYMFLAG_REGISTER,_T("Register member is used."),
	SYMFLAG_REGREL,_T("register relative."),
	SYMFLAG_SLOT,_T("managed code slot. "),
	SYMFLAG_THUNK,_T("thunk. "),
	SYMFLAG_TLSREL,_T("TLS data area. "),
	SYMFLAG_VALUEPRESENT,_T("Value member is used"),
	SYMFLAG_VIRTUAL,_T("VIRTUAL"),
	NULL
};

enum SymCommand
{
	LoadSym,
};

typedef struct _tagSymCommandPar
{
	SymCommand	SymCommandId;
	tstring		szModuleFullPath;
	VOID *		pModuleBaseAddress;
	__int64		nSizeOfImage;
}SymCommandPar,*PSymCommandPar;

typedef struct _tagSymGContext
{
	_tagSymModuleMap gSymInfoMap;
	_tagSymNameArray TmpArray;		//给枚举函数填充使用
	CCriticalSectionStack gSymLock;
	list<SymCommandPar> gSymEventQueue;
	CCriticalSectionStack gSymEventQueueLock;
	ErrorPrinter_OutputDebugString  ErrorLog;
	HANDLE Event[2];
	HANDLE hThread;
	wstring szSvrPath;
	wstring szOutPath;
}SymGContext,*PSymGContext;


//_tagSymGContext::gbInit=0;
BOOL gbSymInit=FALSE;
_tagSymGContext gSymContext;


CSymLoader::CSymLoader(void)
{
}

CSymLoader::~CSymLoader(void)
{
}

BOOL CALLBACK SymEnumSymbolsProc(PSYMBOL_INFO pSymInfo, ULONG SymbolSize, PVOID UserContext)
{
	//	if(strstr(pSymInfo->Name, "IEParseDisplayNameWithBCW"))
	//	if(strstr(pSymInfo->Name, "LoadBrowserHelperObjects"))
	_tagSymGContext * pContext=(_tagSymGContext * )UserContext;
	_tagSymNameSet Set;
	Set.InfoSet=*pSymInfo;
	Set.nBeginAddress=pSymInfo->Address;
	CMyString  szName(wstring(&pSymInfo->Name[0]));
	pContext->TmpArray.NameArray[tstring((TCHAR*)szName)]=Set;
	if(
		(wcsstr(&pSymInfo->Name[0],L"_LoadBrowserHelperObjects"))||
		(wcsstr(&pSymInfo->Name[0],L"DMWP"))
		)
	{
		pContext->ErrorLog(_T("sym--(%s)-%p-%x"),&pSymInfo->Name[0],pSymInfo->Address,pSymInfo->Flags); 
	}
	

	return TRUE;
}
BOOL ReBuildSym(_tagSymNameArray & NameArray,DWORD nFlag,ErrorPrinter & ErrorLog)
{
	map<__int64,tstring,less<__int64> > SortMap;
	map<tstring,_tagSymNameSet,less<tstring>>::iterator itName=NameArray.NameArray.begin();
	for(;itName!=NameArray.NameArray.end();itName++)
	{
		if((itName->second.InfoSet.Flags&nFlag)||(nFlag==0))
		{
			SortMap[itName->second.InfoSet.Address]=itName->first;
		}
		
	}
	

	ErrorLog(_T("ReBuildSym count(%d) BaseAddr=%p Size=%I64d Begin ..."),SortMap.size(),(PVOID)NameArray.nBeginAddress,
		NameArray.nEndAddress-NameArray.nBeginAddress);
	if(SortMap.size())
	{
		map<__int64,tstring,less<__int64> >::iterator itSort=SortMap.begin();
		map<__int64,tstring,less<__int64> >::iterator itNext=itSort;itNext++; 
		for(;itSort!=SortMap.end();itSort++)
		{
			itName=NameArray.NameArray.find(itSort->second);
			if(itNext!=SortMap.end())
			{
				itName->second.nEndAddress=
					(NameArray.NameArray[itNext->second].nBeginAddress-1);
				itNext++;
			}else
			{

				itName->second.nEndAddress=NameArray.nEndAddress;
			}

			ErrorLog(_T("sym--( %s ) offiset=%I64d BeginAddr= %p,EndAddr= %p, nFlag= %x,Index=( %d ), TypeIndex=( %d ), ..."),
				itSort->second.c_str(),
				(__int64)itName->second.nBeginAddress-NameArray.nBeginAddress,
				(PVOID)itName->second.nBeginAddress,
				(PVOID)itName->second.nEndAddress,
				itName->second.InfoSet.Flags,
				itName->second.InfoSet.Index,
				itName->second.InfoSet.TypeIndex);

		}
		
	}
	ErrorLog(_T("ReBuildSym count(%d) End ..."),SortMap.size());
	return TRUE;

}
DWORD CALLBACK SymThread(LPVOID lpParam)
{
	// COM环境,多线程MTA公寓
	HRESULT bRet=::CoInitializeEx(NULL,COINIT_MULTITHREADED );
	_tagSymGContext * pContext=(_tagSymGContext * )lpParam;

	
	DWORD nWaitObj=0;
	HANDLE hProcess = GetCurrentProcess();
	

	hProcess = GetCurrentProcess();
	

	if(SymInitialize(hProcess, (TCHAR*)pContext->szSvrPath.c_str(), TRUE)==FALSE)
	{
		pContext->ErrorLog(L"SymInitialize Err(%d) (%s) Fail ...",GetLastError(),pContext->szSvrPath.c_str());
		return 0;
	}
	DWORD nOption=SymGetOptions();
	//SymSetOptions(0);
	pContext->ErrorLog(_T("SymThread pid(%d) nOption(%x) (%s) begin ..."),GetCurrentThreadId(),nOption,pContext->szSvrPath.c_str());
	SymSetOptions(2);

	do 
	{
		nWaitObj=::WaitForMultipleObjects(2,
			&pContext->Event[0],
			FALSE,INFINITE);
		if(nWaitObj==WAIT_OBJECT_0)
		{
			pContext->ErrorLog(_T("SymThread (%d) End ..."),GetCurrentThreadId());
			SymCleanup(hProcess);
			return 0;
		}else if(nWaitObj==WAIT_OBJECT_0+1)
		{
			SymCommandPar Par;
			BOOL bHasCommand=TRUE;

			
			for(;;)
			{
				
				CAutoStackLock lk;
				lk.Lock(&pContext->gSymEventQueueLock,NULL);
				if(pContext->gSymEventQueue.size()==0)
				{
					bHasCommand=FALSE;
				}else
				{
					Par=pContext->gSymEventQueue.front();
					
				}
				lk.UnLock();

				
					
				
				if(bHasCommand)
				{
					pContext->ErrorLog(_T("SymThread Begin Load (%s) (BaseAddr=%p)  ..."),Par.szModuleFullPath.c_str(),Par.pModuleBaseAddress);

					BOOL bLoad=FALSE;
					DWORD64 nLoad= SymLoadModuleEx(hProcess, NULL, Par.szModuleFullPath.c_str(), NULL, (DWORD64)Par.pModuleBaseAddress, 0,0,0);
					if(nLoad==0)
					{
						
						if(GetLastError()==ERROR_SUCCESS)
						{
							pContext->ErrorLog(_T("SymThread Already  Load (%s) (BaseAddr=%p)  ..."),Par.szModuleFullPath.c_str(),Par.pModuleBaseAddress);
							bLoad=TRUE; 
							
						}else
						{
							pContext->ErrorLog(_T("SymThread Load Fail(%d) (%s) (BaseAddr=%p)  ..."),
								GetLastError(),Par.szModuleFullPath.c_str(),Par.pModuleBaseAddress);
 
							bLoad=FALSE;
							lk.Lock(&pContext->gSymEventQueueLock,NULL);
							pContext->gSymEventQueue.pop_front();
							lk.UnLock();
							continue;
						}
						
						
					}else
					{
						bLoad=TRUE;
					}

					//枚举符号
					BOOL bAdd=FALSE;
					if(bLoad)
					{
						map<tstring,_tagSymNameArray,less<tstring> >::iterator itModule=
											pContext->gSymInfoMap.ModuleArray.find(Par.szModuleFullPath);
						
						if((itModule!=pContext->gSymInfoMap.ModuleArray.end())
							&&(itModule->second.LibStatus==NoFind))
							
						{
							bAdd=TRUE;
						}else if(itModule==pContext->gSymInfoMap.ModuleArray.end())
						{
							bAdd=TRUE;
						}

						if(bAdd)
						{
							CAutoStackLock lkSym;
							lkSym.Lock(&pContext->gSymLock,NULL);
							pContext->TmpArray.NameArray.clear();
							pContext->TmpArray.nBeginAddress=(__int64)Par.pModuleBaseAddress,
							pContext->TmpArray.nEndAddress=(__int64)Par.pModuleBaseAddress+Par.nSizeOfImage;
							pContext->TmpArray.szError.clear();pContext->TmpArray.szVerInfo.clear();
							if(SymEnumSymbols(hProcess, (ULONG64)Par.pModuleBaseAddress, NULL, SymEnumSymbolsProc, pContext))
							{
								pContext->TmpArray.LibStatus=LoadOk;
								if(pContext->szOutPath.length())
								{
									tstring szSymPath;
									TCHAR * pFileName=strrchr_t((TCHAR*)Par.szModuleFullPath.c_str(),'\\');
									if (pFileName) {
										pFileName++;
									}else{
										pFileName=(TCHAR*)Par.szModuleFullPath.c_str();
									}
									pContext->ErrorLog(szSymPath,_T("%s\\%s.txt"),pContext->szOutPath.c_str(),pFileName);
									ErrorPrinter_OutputFile fout((TCHAR *)szSymPath.c_str());
									ReBuildSym(pContext->TmpArray,0,fout);
								}else
								{
									ReBuildSym(pContext->TmpArray,0,pContext->ErrorLog);
								}
								
							}else
							{
								pContext->TmpArray.LibStatus=NoFind;
								pContext->ErrorLog(_T("SymThread SymEnumSymbols Error(%d) (%s) (BaseAddr=%p)  ..."),
									GetLastError(),Par.szModuleFullPath.c_str(),Par.pModuleBaseAddress);
							}
							
							
							pContext->gSymInfoMap.ModuleArray[Par.szModuleFullPath]=pContext->TmpArray;
							pContext->ErrorLog(_T("SymThread Add Sym (%s) (BaseAddr=%p)  ..."),Par.szModuleFullPath.c_str(),Par.pModuleBaseAddress);
							lkSym.UnLock();
						}
						
					}  

					pContext->ErrorLog(_T("SymThread Load bAdd=%d (%s) (%s) (BaseAddr=%p)  ..."),
						bAdd,((bLoad==TRUE)?_T("成功"):_T("失败")),Par.szModuleFullPath.c_str(),Par.pModuleBaseAddress);
					
					lk.Lock(&pContext->gSymEventQueueLock,NULL);
					pContext->gSymEventQueue.pop_front();
					lk.UnLock();
					
					
					//dwload = SymLoadModule64(hHandle, NULL, FullName, NULL, moduleBase, 0);
				}else
				{
					break;
				}
			}
			//SymCleanup(hProcess);

			

			
			//pIeMonContext->m_pWebBrowser2->Quit();


		}
	} while (TRUE);
	pContext->ErrorLog(_T("IeMonThread (%d) FakeEnd ..."),GetCurrentThreadId());


	return 0;
}

//

BOOL InitSymThread()
{
	//PIeMonContext * pContext=new IeMonContext;
	
	gSymContext.Event[0]=CreateEvent(NULL,TRUE,FALSE,NULL);
	gSymContext.Event[1]=CreateEvent(NULL,FALSE,FALSE,NULL);
	gSymContext.hThread=CreateThread(NULL, 0, SymThread, 
		&gSymContext, 0, NULL);
	return TRUE;
}

//************************************************************************      
// 函数名称: Init     
// 函数说明：初始化符号系统     
// 作 成 者：叶树深    
// 作成日期：2015/05/12     
// 返 回 值:      
// 参    数:      
//************************************************************************  
//"SRV*C:\\mnesym*http://msdl.microsoft.com/download/symbols"
BOOL CSymLoader::Init(tstring & szSvrPath,ErrorPrinter & ErrorLog,tstring & szOutPath)
{
	CAutoStackLock lk(&gSymContext.gSymLock);
	if(gbSymInit==FALSE)
	{
		gSymContext.szSvrPath=szSvrPath;
		gSymContext.szOutPath=szOutPath;
		gSymContext.ErrorLog.SetIo(ErrorLog.m_pIo);
		InitSymThread();
		gbSymInit=TRUE;
	}
	return TRUE;
}


//************************************************************************      
// 函数名称: AsynLoadSym     
// 函数说明：     
// 作 成 者：叶树深    
// 作成日期：2015/05/12     
// 返 回 值:      
// 参    数:      
//************************************************************************  
BOOL CSymLoader::AsynLoadSym(tstring & szModuleName,VOID * pModuleBaseAddress,DWORD64 nSizeOfImage)
{
	CAutoStackLock lk(&gSymContext.gSymEventQueueLock);
	//std::find(gSymContext.gSymEventQueue.begin(),gSymContext.gSymEventQueue.end(),szModuleName)
	list<_tagSymCommandPar>::iterator itPar=gSymContext.gSymEventQueue.begin();
	for(;itPar!=gSymContext.gSymEventQueue.end();itPar++)
	{
		if((itPar->SymCommandId==LoadSym)&&(itPar->szModuleFullPath==szModuleName))
		{
			return TRUE;
		}
	}

	_tagSymCommandPar Par;
	Par.pModuleBaseAddress=pModuleBaseAddress;
	Par.SymCommandId=LoadSym;
	Par.szModuleFullPath=szModuleName;
	Par.nSizeOfImage=nSizeOfImage;
	gSymContext.gSymEventQueue.push_back(Par);
	::SetEvent(gSymContext.Event[1]);
	gSymContext.ErrorLog(_T("AsynLoadSym %d %s %p"),gSymContext.gSymEventQueue.size(),
		szModuleName.c_str(),pModuleBaseAddress);
	return TRUE;

}
BOOL CSymLoader::Close()
{
	if(gbSymInit)
	{
		::SetEvent(gSymContext.Event[0]); 
		if(WaitForSingleObject(gSymContext.hThread,5000)==WAIT_OBJECT_0)
		{
			gSymContext.ErrorLog(_T("CSymLoader 线程退出"));
		}
		else
		{
			gSymContext.ErrorLog(_T("CSymLoader 线程异常，强制终止"));
			SymCleanup(GetCurrentProcess());
			::TerminateThread(gSymContext.hThread,0);
		}
		gbSymInit=FALSE;
	}
	return TRUE;
}


//************************************************************************      
// 函数名称: GetAddressInfo     
// 函数说明：     
// 作 成 者：叶树深    
// 作成日期：2015/05/12     
// 返 回 值:      
// 参    数:      
//************************************************************************  
BOOL CSymLoader::GetAddressInfo(DWORD64 pAddress,OUT tstring & szInfo)
{
	CAutoStackLock lk(&gSymContext.gSymLock);
	map<tstring,_tagSymNameArray,less<tstring> >::iterator itModule=gSymContext.gSymInfoMap.ModuleArray.begin();
	for(;itModule!=gSymContext.gSymInfoMap.ModuleArray.end();itModule++)
	{
		if(
			(((__int64)pAddress)<itModule->second.nEndAddress)
			&&(((__int64)pAddress)>itModule->second.nBeginAddress)
			&&(itModule->second.LibStatus==LoadOk)
			)
		{
			map<tstring,_tagSymNameSet,less<tstring>>::iterator itName=itModule->second.NameArray.begin();
			for(;itName!=itModule->second.NameArray.end();itName++)
			{
				if(
					(((__int64)pAddress)<itName->second.nEndAddress)
					&&(((__int64)pAddress)>itName->second.nBeginAddress)
					)
				{
					gSymContext.ErrorLog(szInfo,_T("%s.%p"),
						itName->first.c_str(),((__int64)pAddress-itName->second.nBeginAddress));
					return TRUE;
				}

			}
		}
	}
	return FALSE;
}

//************************************************************************      
// 函数名称: GetDllSymInfo     
// 函数说明：导出dll符号信息     
// 作 成 者：叶树深    
// 作成日期：2015/05/14     
// 返 回 值:      
// 参    数:      
//************************************************************************  
BOOL CSymLoader::GetDllSymInfo(TCHAR * pDll,TCHAR * pOutPath,BOOL bWait,DWORD nWaitTime)
{
	ErrorPrinter_OutputDebugString OutputerError;
	HMODULE hM=::LoadLibrary(pDll);
	TCHAR szModuleName[MAX_PATH]={0};
	BOOL bRet=FALSE;
	if(hM)
	{
		_MODULEINFO info;
		if(GetModuleInformation(GetCurrentProcess(),hM,&info,sizeof(_MODULEINFO)))
		{
			tstring szSvr;
			OutputerError(szSvr,_T("SRV*%s*http://msdl.microsoft.com/download/symbols"),pOutPath);
			Init(szSvr,OutputerError,tstring(pOutPath));
			if(GetModuleFileName(hM,&szModuleName[0],sizeof(TCHAR)*MAX_PATH))
			{
				AsynLoadSym(tstring(szModuleName),info.lpBaseOfDll,info.SizeOfImage);
				for(unsigned int nWait=0;nWait<nWaitTime;)
				{
					{
						CAutoStackLock lk(&gSymContext.gSymLock);
						if(gSymContext.gSymInfoMap.ModuleArray.find(tstring(szModuleName))!=gSymContext.gSymInfoMap.ModuleArray.end())
						{
							bRet=TRUE;
							break;
						}
					}
					Sleep(100);
					nWait+=100;
					if(nWait>nWaitTime)
						break;
				}
			}
		}
	}
	Close();
	return bRet;
}



//************************************************************************      
// 函数名称: GetAddressInfo     
// 函数说明：     
// 作 成 者：叶树深    
// 作成日期：2015/05/12     
// 返 回 值:      
// 参    数:      
//************************************************************************  
BOOL CSymLoader::GetAddressInfo(tstring & szModuleName,DWORD64 pAddress,VOID * pModuleBaseAddress, DWORD64 nSizeOfImage,OUT tstring & szInfo,unsigned int nMaxWait)
{
	unsigned int nWait=0;
	BOOL bWait=FALSE;
	do 
	{
		{
			bWait=FALSE;
			CAutoStackLock lk(&gSymContext.gSymLock);
			map<tstring,_tagSymNameArray,less<tstring> >::iterator itModule=gSymContext.gSymInfoMap.ModuleArray.find(szModuleName);
			if(itModule!=gSymContext.gSymInfoMap.ModuleArray.end())
			{
				if(itModule->second.LibStatus==LoadOk)
				{
					map<tstring,_tagSymNameSet,less<tstring>>::iterator itName=itModule->second.NameArray.begin();
					for(;itName!=itModule->second.NameArray.end();itName++)
					{
						if(
							(((__int64)pAddress)<itName->second.nEndAddress)
							&&(((__int64)pAddress)>itName->second.nBeginAddress)
							)
						{
							gSymContext.ErrorLog(szInfo,_T("%s.%p"),
								itName->first.c_str(),((__int64)pAddress-itName->second.nBeginAddress));
							return TRUE;
						}

					}

					gSymContext.ErrorLog(szInfo,_T("GetAddressInfo  NoFind  %s %p"),
						szModuleName.c_str(),pAddress);
					return FALSE;
				}else
				{
					gSymContext.ErrorLog(_T("Sym Load Fail(%d)(%s)"),
						itModule->second.LibStatus,itModule->second.szError.c_str());
					return FALSE;
				}
			}else
			{
				bWait=TRUE;
			}
		}
		if(nWait>=nMaxWait)
		{
			break;
		}

		if(bWait)
		{
			AsynLoadSym(szModuleName,pModuleBaseAddress,nSizeOfImage);
			Sleep(1000);
			nWait+=1000;
		}
		
	} while (TRUE);
	gSymContext.ErrorLog(_T("GetAddressInfo WaitTime Over (%s) (%p)"),szModuleName.c_str(),pModuleBaseAddress );
	return FALSE;

}
