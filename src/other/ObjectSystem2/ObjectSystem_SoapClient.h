#pragma once

#include "ObjectSystem.h"
#include "SoapOperation.h"

class CObjectSystem_SoapClient :public CObjectSystemInterface
{
public:
	CObjectSystem_SoapClient(void);
	~CObjectSystem_SoapClient(void);


	BOOL GetObject(IN tstring & ObjectPath,OUT tstring & Object,IN OUT ObjectSystem::_tagObjectState & ObjectState,OUT ObjectSystem::SYSTEMERROR * pError);

	//���¶��󵽴洢
	BOOL UpDataObject(IN tstring & ObjectPath,IN tstring & Object, ObjectSystem::SYSTEMERROR * pError);

	//��ȡĿ¼��Ϣ
	BOOL GetDirectoryInfo(IN tstring & DirectoryPath,IN tstring & szFinder,OUT ObjectSystem::_tagDirectoryInfo & DirectoryInfo,OUT ObjectSystem::SYSTEMERROR * pError);

	//ɾ������
	BOOL DeleteObject(IN tstring & ObjectOrDir, ObjectSystem::SYSTEMERROR * pError);


	BOOL LogonInSystem(IN tstring & szUserName,IN tstring & szPassword);

	//�ǳ�
	BOOL LogonOutSystem();

	//////////////////////////////////////////����������///////////////////////////////////////

	//���¶�������Ϣ
	BOOL UpDataObjectState(IN tstring & ObjectPath,OUT ObjectSystem::_tagObjectState & ObjectState,OUT ObjectSystem::SYSTEMERROR * pError);

	//��ȡ��������Ϣ
	BOOL GetObjectState(IN tstring & ObjectPath,OUT ObjectSystem::_tagObjectState & ObjectState,OUT ObjectSystem::SYSTEMERROR * pError);

	BOOL GetCurTime(SYSTEMTIME * npTime,SYSTEMTIME * nCurTime);

	//
	BOOL ReleaseObjectState(IN tstring & ObjectOrDir,OUT ObjectSystem::SYSTEMERROR * pError);
	
private:
	CSoapOperation m_SoapOperation;

	tstring m_szUserName;
	tstring m_szConversation;


};
