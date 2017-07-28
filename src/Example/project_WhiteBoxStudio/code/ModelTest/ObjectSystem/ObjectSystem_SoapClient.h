#pragma once

#include "ObjectSystem.h"
#include "SoapOperation.h"

class CObjectSystem_SoapClient :public CObjectSystemInterface
{
public:
	CObjectSystem_SoapClient(void);
	~CObjectSystem_SoapClient(void);


	BOOL GetObject(IN tstring & ObjectPath,OUT tstring & Object,IN OUT _tagObjectState & ObjectState,OUT SYSTEMERROR * pError);

	//更新对象到存储
	BOOL UpDataObject(IN tstring & ObjectPath,IN tstring & Object,SYSTEMERROR * pError);

	//获取目录信息
	BOOL GetDirectoryInfo(IN tstring & DirectoryPath,IN tstring & szFinder,OUT _tagDirectoryInfo & DirectoryInfo,OUT SYSTEMERROR * pError);

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

	//
	BOOL ReleaseObjectState(IN tstring & ObjectOrDir,OUT SYSTEMERROR * pError);
	
private:
	CSoapOperation m_SoapOperation;

	tstring m_szUserName;
	tstring m_szConversation;


};
