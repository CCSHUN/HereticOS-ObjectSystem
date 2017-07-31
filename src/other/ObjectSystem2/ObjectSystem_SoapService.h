#pragma once

#include "ObjectSystem.h"
#include "ObjectSystem_Local.h"

template<typename ConfigT, typename FileSystemT>
class CObjectSystem_SoapService : public CObjectSystemInterface
{
public:
	CObjectSystem_SoapService(void);
	~CObjectSystem_SoapService(void);
	BOOL GetObject(IN tstring & ObjectPath,OUT tstring & Object,IN OUT ObjectSystem::_tagObjectState & ObjectState,OUT ObjectSystem::SYSTEMERROR * pError);

	//���¶��󵽴洢
	BOOL UpDataObject(IN tstring & ObjectPath,IN tstring & Object, ObjectSystem::SYSTEMERROR * pError);
	BOOL UpDataObject(IN tstring & ObjectPath,IN tstring & Object,IN _tagObjectState & ObjectState,OUT ObjectSystem::SYSTEMERROR * pError);

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

	BOOL ReleaseObjectState(IN tstring & ObjectOrDir,OUT ObjectSystem::SYSTEMERROR * pError);

private:
	CObjectSystem_Local< ConfigT, FileSystemT> m_LocalObjectSystem;
	BOOL GetUser(tstring & szUserName,_tagUserMapSet & UserSet);

};
