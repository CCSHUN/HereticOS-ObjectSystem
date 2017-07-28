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
	
	//���¶��󵽴洢
	BOOL UpDataObject(IN tstring & ObjectPath,IN tstring & Object,SYSTEMERROR * pError);

	BOOL UpDataObject(IN tstring & ObjectPath,IN tstring & Object,IN _tagObjectState & ObjectState,OUT SYSTEMERROR * pError);

	//��ȡĿ¼��Ϣ
	BOOL GetDirectoryInfo(IN tstring & DirectoryPath,IN tstring & szFinder,OUT _tagDirectoryInfo & DirectoryInfo,OUT SYSTEMERROR * pError);

	//��ȡĿ¼��Ϣ
	BOOL GetDirectoryInfo(IN tstring & DirectoryPath,IN tstring & szFinder,OUT _tagDirectoryInfoSoap & DirectoryInfo,OUT SYSTEMERROR * pError);

	//ɾ������
	BOOL DeleteObject(IN tstring & ObjectOrDir,SYSTEMERROR * pError);

	//��ȡ����״̬
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
	//����
	BOOL ClearDirCache(tstring & ObjectOrDirPath);

	//��������
	BOOL ReleaseObjectLock(tstring & ObjectPath);


	
};
