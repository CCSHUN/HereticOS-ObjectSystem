#pragma once

#include "ObjectSystem.h"
#include "SoapOperation.h"

class CObjectSystem_SoapClient :public CObjectSystemInterface
{
public:
	CObjectSystem_SoapClient(void);
	~CObjectSystem_SoapClient(void);


	BOOL GetObject(IN tstring & ObjectPath,OUT tstring & Object,IN OUT _tagObjectState & ObjectState,OUT SYSTEMERROR * pError);

	//���¶��󵽴洢
	BOOL UpDataObject(IN tstring & ObjectPath,IN tstring & Object,SYSTEMERROR * pError);

	//��ȡĿ¼��Ϣ
	BOOL GetDirectoryInfo(IN tstring & DirectoryPath,IN tstring & szFinder,OUT _tagDirectoryInfo & DirectoryInfo,OUT SYSTEMERROR * pError);

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

	//
	BOOL ReleaseObjectState(IN tstring & ObjectOrDir,OUT SYSTEMERROR * pError);
	
private:
	CSoapOperation m_SoapOperation;

	tstring m_szUserName;
	tstring m_szConversation;


};
