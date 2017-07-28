#pragma once

#include "ObjectSystem.h"
#include "ObjectSystem_Local.h"
class CObjectSystem_SoapService : public CObjectSystemInterface
{
public:
	CObjectSystem_SoapService(void);
	~CObjectSystem_SoapService(void);
	BOOL GetObject(IN tstring & ObjectPath,OUT tstring & Object,IN OUT _tagObjectState & ObjectState,OUT SYSTEMERROR * pError);

	//更新对象到存储
	BOOL UpDataObject(IN tstring & ObjectPath,IN tstring & Object,SYSTEMERROR * pError);
	BOOL UpDataObject(IN tstring & ObjectPath,IN tstring & Object,IN _tagObjectState & ObjectState,OUT SYSTEMERROR * pError);

	//获取目录信息
	BOOL GetDirectoryInfo(IN tstring & DirectoryPath,IN tstring & szFinder,OUT _tagDirectoryInfo & DirectoryInfo,OUT SYSTEMERROR * pError);
	BOOL GetDirectoryInfo(IN tstring & DirectoryPath,IN tstring & szFinder,OUT _tagDirectoryInfoSoap & DirectoryInfo,OUT SYSTEMERROR * pError);

	//删除对象
	BOOL DeleteObject(IN tstring & ObjectOrDir,SYSTEMERROR * pError);


	BOOL LogonInSystem(IN tstring & szUserName,IN tstring & szPassword);

	//登出
	BOOL LogonOutSystem();

	//////////////////////////////////////////对象锁操作///////////////////////////////////////

	//更新对象锁信息
	BOOL UpDataObjectState(IN tstring & ObjectPath,OUT _tagObjectState & ObjectState,OUT SYSTEMERROR * pError);

	//获取对象锁信息
	BOOL GetObjectState(IN tstring & ObjectPath,OUT _tagObjectState & ObjectState,OUT SYSTEMERROR * pError);

	BOOL GetCurTime(SYSTEMTIME * npTime,SYSTEMTIME * nCurTime);

	BOOL ReleaseObjectState(IN tstring & ObjectOrDir,OUT SYSTEMERROR * pError);

private:
	CObjectSystem_Local m_LocalObjectSystem;
	BOOL GetUser(tstring & szUserName,_tagUserMapSet & UserSet);

};
