#pragma once

#include "ObjectSystem.h"
#include "ObjectSystem_Local.h"
class CObjectSystem_SoapService : public CObjectSystemInterface
{
public:
	CObjectSystem_SoapService(void);
	~CObjectSystem_SoapService(void);
	BOOL GetObject(IN tstring & ObjectPath,OUT tstring & Object,IN OUT _tagObjectState & ObjectState,OUT SYSTEMERROR * pError);

	//���¶��󵽴洢
	BOOL UpDataObject(IN tstring & ObjectPath,IN tstring & Object,SYSTEMERROR * pError);
	BOOL UpDataObject(IN tstring & ObjectPath,IN tstring & Object,IN _tagObjectState & ObjectState,OUT SYSTEMERROR * pError);

	//��ȡĿ¼��Ϣ
	BOOL GetDirectoryInfo(IN tstring & DirectoryPath,IN tstring & szFinder,OUT _tagDirectoryInfo & DirectoryInfo,OUT SYSTEMERROR * pError);
	BOOL GetDirectoryInfo(IN tstring & DirectoryPath,IN tstring & szFinder,OUT _tagDirectoryInfoSoap & DirectoryInfo,OUT SYSTEMERROR * pError);

	//ɾ������
	BOOL DeleteObject(IN tstring & ObjectOrDir,SYSTEMERROR * pError);


	BOOL LogonInSystem(IN tstring & szUserName,IN tstring & szPassword);

	//�ǳ�
	BOOL LogonOutSystem();

	//////////////////////////////////////////����������///////////////////////////////////////

	//���¶�������Ϣ
	BOOL UpDataObjectState(IN tstring & ObjectPath,OUT _tagObjectState & ObjectState,OUT SYSTEMERROR * pError);

	//��ȡ��������Ϣ
	BOOL GetObjectState(IN tstring & ObjectPath,OUT _tagObjectState & ObjectState,OUT SYSTEMERROR * pError);

	BOOL GetCurTime(SYSTEMTIME * npTime,SYSTEMTIME * nCurTime);

	BOOL ReleaseObjectState(IN tstring & ObjectOrDir,OUT SYSTEMERROR * pError);

private:
	CObjectSystem_Local m_LocalObjectSystem;
	BOOL GetUser(tstring & szUserName,_tagUserMapSet & UserSet);

};
