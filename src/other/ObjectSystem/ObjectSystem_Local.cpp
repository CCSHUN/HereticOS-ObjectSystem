#include "stdafx.h"
#include "ObjectSystem_Local.h"

CObjectSystem_Local::CObjectSystem_Local(void)
{
	//m_szRootPath=_T("e:\\ModelTest\\");
}

CObjectSystem_Local::~CObjectSystem_Local(void)
{
}


BOOL CObjectSystem_Local::GetObject(IN tstring & ObjectPath,OUT tstring & Object,IN OUT _tagObjectState & ObjectState,OUT SYSTEMERROR * pError)
{
	map<tstring, PFileContext,less<tstring> >::iterator itObject;
	//if(strstr_t(ObjectPath.c_str(),_T("MachineCheckStandardLib")))
	{
		/*printf("MachineCheckStandardLib");
		for(unsigned int i=0;i<768;i++)
		{
			Object+=_T("1234");
		}
		OutputDebugString(_T("768"));
		return TRUE;*/
	}

	*pError=Error_No;
	itObject=m_FileCacheMap.find(ObjectPath);
	if(itObject!=m_FileCacheMap.end())
	{
		Object=itObject->second->szData;
		if(itObject->second->ObjectState.szLockUser.length()
			&&itObject->second->ObjectState.bLock)
		{
			if(itObject->second->ObjectState.szLockUser==
				ObjectState.szLockUser)
			{
				itObject->second->ObjectState=ObjectState;
				_DebugOutput(_T("GetObject"),_T("对象[%s]锁已更新 Object=%s 请求用户=%s 是否占用=%d"),
					itObject->second->ObjectState.szLockUser.c_str(),
					ObjectPath.c_str(),ObjectState.szLockUser.c_str(),ObjectState.bLock);
			}else
			{
				//对象已锁定 返回对象当前的锁
				ObjectState=itObject->second->ObjectState;
				_DebugOutput(_T("GetObject"),_T("对象[%s]已锁定，只读打开 Object=%s 请求用户=%s 是否占用=%d"),
					itObject->second->ObjectState.szLockUser.c_str(),
					ObjectPath.c_str(),ObjectState.szLockUser.c_str(),ObjectState.bLock);
				*pError=Error_ObjectAlreadyLock;
			}
			
		}else
		{

			//占用对象锁
			itObject->second->ObjectState=ObjectState;
			_DebugOutput(_T("GetObject"),_T("覆盖获取锁 Object=%s 请求用户=%s 是否占用=%d"),
				ObjectPath.c_str(),ObjectState.szLockUser.c_str(),ObjectState.bLock);
		}

	}else
	{
		PFileContext pContext=new _tagFileContext;
		tstring ObjectAddr=gConfig.m_Config.strLocalSystemDirectory+ObjectPath;
		if(pContext->FileOperation.OpenObjectFile_OnlyOpen(ObjectAddr))
		{
			if(pContext->FileOperation.ReadObject(Object))
			{
				pContext->szData=Object;
				/*pContext->ObjectState.bLock=FALSE;
				pContext->ObjectState.nLockTime=0;
				pContext->ObjectState.szLockUser=_T("");
				pContext->ObjectState.nType=CObjectSystemInterface::Nonmoral;*/
				pContext->ObjectState=ObjectState;

				m_FileCacheMap[ObjectPath]=pContext;
				if(Object.length()==0)
				{
					*pError=Error_Sys_OpenFileFail;
					return FALSE;
				}

				
				//if(ObjectState.bLock)
				
				pContext->ObjectState=ObjectState;
				_DebugOutput(_T("GetObject"),_T("覆盖锁 Object=%s 请求用户=%s 是否占用=%d"),
					ObjectPath.c_str(),ObjectState.szLockUser.c_str(),ObjectState.bLock);
				
				
				return TRUE;
			}
			pContext->FileOperation.CloseObject();
		}
		delete pContext;

		*pError=Error_Sys_OpenFileFail;

		return FALSE;
	}

	return TRUE;
}

BOOL CObjectSystem_Local::GetObjectState(IN tstring & ObjectPath,OUT _tagObjectState & ObjectState,OUT SYSTEMERROR * pError)
{
	map<tstring, PFileContext,less<tstring> >::iterator itObject;

	itObject=m_FileCacheMap.find(ObjectPath);
	if(itObject!=m_FileCacheMap.end())
	{
		ObjectState=itObject->second->ObjectState;
	}
	return FALSE;
}

BOOL CObjectSystem_Local::UpDataObject(IN tstring & ObjectPath,IN tstring & Object,IN _tagObjectState & ObjectState,OUT SYSTEMERROR * pError)
{
	map<tstring, PFileContext,less<tstring> >::iterator itObject;
	
	itObject=m_FileCacheMap.find(ObjectPath);
	tstring ObjectAddr=gConfig.m_Config.strLocalSystemDirectory+ObjectPath;
	*pError=Error_No;
	if(itObject!=m_FileCacheMap.end())
	{
		//检查锁
		if(itObject->second->ObjectState.bLock&&itObject->second->ObjectState.szLockUser.length())
		{
			if(itObject->second->ObjectState.szLockUser!=ObjectState.szLockUser)
			{
				_DebugOutput(_T("UpDataObject"),_T("请求 Object=%s 请求用户=%s 对象已经锁定 当前锁定用户=%s"),
					ObjectPath.c_str(),ObjectState.szLockUser.c_str(),
					itObject->second->ObjectState.szLockUser.c_str());
				*pError=Error_ObjectAlreadyLock;
				return FALSE;
			}
		}
		itObject->second->szData=Object;
		
		itObject->second->FileOperation.ClearFile(ObjectAddr);
		if(itObject->second->FileOperation.WriteObject(Object))
		{

			//释放对象锁
			itObject->second->ObjectState.szLockUser.clear();
			itObject->second->ObjectState.bLock=FALSE;
			_DebugOutput(_T("UpDataObject"),_T("释放对象锁 Object=%s 请求用户=%s "),
				ObjectPath.c_str(),ObjectState.szLockUser.c_str());
			return TRUE;
		}
	}
	else
	{
		PFileContext pContext=new _tagFileContext;
		if(pContext->FileOperation.OpenObjectFile(ObjectAddr,TRUE))
		{
			
			if(pContext->FileOperation.WriteObject(Object))
			{
				//保存到cache
				pContext->szData=Object;
				pContext->ObjectState.bLock=FALSE;
				pContext->ObjectState.nLockTime=0;
				pContext->ObjectState.szLockUser=_T("");
				pContext->ObjectState.nType=CObjectSystemInterface::Nonmoral;
				m_FileCacheMap[ObjectPath]=pContext;
				return TRUE;
			}
			pContext->FileOperation.CloseObject();
		}
		delete pContext;
		*pError=Error_Sys_OpenFileFail;
		return FALSE;
	}
	

	return FALSE;
}

//更新对象到存储
BOOL CObjectSystem_Local::UpDataObject(IN tstring & ObjectPath,IN tstring & Object,SYSTEMERROR * pError)
{
	map<tstring, PFileContext,less<tstring> >::iterator itObject;
	
	itObject=m_FileCacheMap.find(ObjectPath);
	tstring ObjectAddr=gConfig.m_Config.strLocalSystemDirectory+ObjectPath;
	if(itObject!=m_FileCacheMap.end())
	{
		itObject->second->szData=Object;
		
		itObject->second->FileOperation.ClearFile(ObjectAddr);
		if(itObject->second->FileOperation.WriteObject(Object))
		{

			//释放对象锁
			/*itObject->second->ObjectState.szLockUser.clear();
			itObject->second->ObjectState.bLock=FALSE;*/
			return TRUE;
		}
	}
	else
	{
		PFileContext pContext=new _tagFileContext;
		if(pContext->FileOperation.OpenObjectFile(ObjectAddr,TRUE))
		{
			
			if(pContext->FileOperation.WriteObject(Object))
			{
				//保存到cache
				pContext->szData=Object;
				m_FileCacheMap[ObjectPath]=pContext;
				return TRUE;
			}
			pContext->FileOperation.CloseObject();
		}
		delete pContext;
		return FALSE;
	}
	

	return FALSE;
}

//获取目录信息
BOOL CObjectSystem_Local::GetDirectoryInfo(IN tstring & DirectoryPath,IN tstring & szFinder,OUT _tagDirectoryInfo & DirectoryInfo,OUT SYSTEMERROR * pError)
{
	tstring ObjectAddr=gConfig.m_Config.strLocalSystemDirectory+DirectoryPath;
	if (ObjectAddr.at(ObjectAddr.length()-1) != '\\')
	{
		ObjectAddr += '\\';
	}

	tstring ObjectAddr1=DirectoryPath;
	if (ObjectAddr1.at(ObjectAddr1.length()-1) != '\\')
	{
		ObjectAddr1 += '\\';
	}

	WIN32_FIND_DATA wfd;
	HANDLE hFind = FindFirstFile((ObjectAddr + szFinder).c_str(),&wfd);
	if (hFind == INVALID_HANDLE_VALUE)
		return FALSE;

	_tagDirectoryInfoSet Set;
	do
	{
		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (stricmp_t(wfd.cFileName,_T(".")) != 0 &&
				stricmp_t(wfd.cFileName,_T("..")) != 0)
			{
				Set.ObjectType= Directory;
				Set.ObjectName=wfd.cFileName;
				DirectoryInfo.DirectoryInfoArray.push_back(Set);
			}
		}
		else
		{
			Set.ObjectType= File;
			Set.ObjectName=wfd.cFileName;
			DirectoryInfo.DirectoryInfoArray.push_back(Set);
		}
	}
	while (FindNextFile(hFind,&wfd));
	FindClose(hFind);

	return TRUE;
}

BOOL CObjectSystem_Local::GetDirectoryInfo(IN tstring & DirectoryPath,IN tstring & szFinder,OUT _tagDirectoryInfoSoap & DirectoryInfo,OUT SYSTEMERROR * pError)
{
	tstring ObjectAddr=gConfig.m_Config.strLocalSystemDirectory+DirectoryPath;
	if (ObjectAddr.at(ObjectAddr.length()-1) != '\\')
	{
		ObjectAddr += '\\';
	}

	tstring ObjectAddr1=DirectoryPath;
	if (ObjectAddr1.at(ObjectAddr1.length()-1) != '\\')
	{
		ObjectAddr1 += '\\';
	}

	WIN32_FIND_DATA wfd;
	HANDLE hFind = FindFirstFile((ObjectAddr + szFinder).c_str(),&wfd);
	if (hFind == INVALID_HANDLE_VALUE)
		return FALSE;

	_tagDirectoryInfoSetSoap Set;
	do
	{
		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (stricmp_t(wfd.cFileName,_T(".")) != 0 &&
				stricmp_t(wfd.cFileName,_T("..")) != 0)
			{
				Set.ObjectType= (unsigned int)Directory;
				Set.ObjectName=wfd.cFileName;
				DirectoryInfo.DirectoryInfoArray.push_back(Set);
			}
		}
		else
		{
			Set.ObjectType= (unsigned int)File;
			Set.ObjectName=wfd.cFileName;
			DirectoryInfo.DirectoryInfoArray.push_back(Set);
		}
	}
	while (FindNextFile(hFind,&wfd));
	FindClose(hFind);

	return TRUE;
}

BOOL CObjectSystem_Local::ReleaseObjectLock(tstring & ObjectPath)
{
	return TRUE;
}
BOOL CObjectSystem_Local::ReleaseObjectState(IN tstring & ObjectOrDir,OUT SYSTEMERROR * pError)
{
	map<tstring, PFileContext,less<tstring> >::iterator itObject=m_FileCacheMap.begin();
	map<tstring, PFileContext,less<tstring> >::iterator itOldObject=itObject;
	for(;itObject!=m_FileCacheMap.end();itObject++)
	{
		if(strstr_t(itObject->first.c_str(),ObjectOrDir.c_str()))
		{
			//清理该cache

			itObject->second->ObjectState.bLock=FALSE;
			itObject->second->ObjectState.nType=CObjectSystemInterface::Nonmoral;
			itObject->second->ObjectState.nLockTime=0;
			itObject->second->ObjectState.szLockUser.clear();
		}
	}
	return TRUE;
}
BOOL CObjectSystem_Local::ClearDirCache(tstring & ObjectOrDirPath)
{
	map<tstring, PFileContext,less<tstring> >::iterator itObject=m_FileCacheMap.begin();
	map<tstring, PFileContext,less<tstring> >::iterator itOldObject=itObject;
	for(;itObject!=m_FileCacheMap.end();itObject++)
	{
		if(strstr_t(itObject->first.c_str(),ObjectOrDirPath.c_str()))
		{
			//清理该cache

			delete itObject->second;
			m_FileCacheMap.erase(itObject);
			if(m_FileCacheMap.size()==0)
			{
				return TRUE;
			}
			itObject=m_FileCacheMap.begin();
		}
	}
	return TRUE;
}
//删除对象
BOOL CObjectSystem_Local::DeleteObject(IN tstring & ObjectOrDir,SYSTEMERROR * pError)
{
	
	ClearDirCache(ObjectOrDir);

	tstring ObjectAddr=gConfig.m_Config.strLocalSystemDirectory+ObjectOrDir;
	CObjectFileOperation del;
	del.DelObjectOrDir(ObjectAddr);

	return TRUE;
}