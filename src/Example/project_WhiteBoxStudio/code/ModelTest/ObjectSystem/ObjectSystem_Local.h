#pragma once

#include "ObjectSystem.h"
#include "ObjectFileOperation.h"

class CObjectSystem_Local: public CObjectSystemInterface
{
public:
	
	CObjectSystem_Local(void);
	~CObjectSystem_Local(void);
	//tstring m_szRootPath;

	

	BOOL GetObject(IN tstring & ObjectPath,OUT tstring & Object,IN OUT _tagObjectState & ObjectState,OUT SYSTEMERROR * pError);
	
	//更新对象到存储
	BOOL UpDataObject(IN tstring & ObjectPath,IN tstring & Object,SYSTEMERROR * pError);

	BOOL UpDataObject(IN tstring & ObjectPath,IN tstring & Object,IN _tagObjectState & ObjectState,OUT SYSTEMERROR * pError);

	//获取目录信息
	BOOL GetDirectoryInfo(IN tstring & DirectoryPath,IN tstring & szFinder,OUT _tagDirectoryInfo & DirectoryInfo,OUT SYSTEMERROR * pError);

	//获取目录信息
	BOOL GetDirectoryInfo(IN tstring & DirectoryPath,IN tstring & szFinder,OUT _tagDirectoryInfoSoap & DirectoryInfo,OUT SYSTEMERROR * pError);

	//删除对象
	BOOL DeleteObject(IN tstring & ObjectOrDir,SYSTEMERROR * pError);

	//获取对象状态
	BOOL GetObjectState(IN tstring & ObjectPath,OUT _tagObjectState & ObjectState,OUT SYSTEMERROR * pError);
	

	BOOL ReleaseObjectState(IN tstring & ObjectOrDir,OUT SYSTEMERROR * pError);

private:

	typedef struct _tagFileContext
	{ 
		CObjectFileOperation	FileOperation;
		tstring					szData;
		__int64					nLastAccessTime;
		_tagObjectState			ObjectState;
	}FileContext,*PFileContext;

	map<tstring, PFileContext,less<tstring> > m_FileCacheMap;
	//清理
	BOOL ClearDirCache(tstring & ObjectOrDirPath);

	//解锁对象
	BOOL ReleaseObjectLock(tstring & ObjectPath);


	
};
