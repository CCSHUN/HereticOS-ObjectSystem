#pragma once


//���ߺ�
#define HasLock(obj)  (obj.m_ObjectState.szLockUser==theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetLoginName())
#define IsCurUserLock(obj)	((obj.m_ObjectState.bLock)&&(obj.m_ObjectState.szLockUser==theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetLoginName()))
#define IsCurUserAndUiLock(obj,uiName)	 ((obj.m_ObjectState.bLock)&&(obj.m_ObjectState.szLockUser==theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetLoginName()+uiName))

#define LOGIN_TYPE_LOCAL				_T("���ض���洢ϵͳ")
#define LOGIN_TYPE_NET_SOAPSERVICE		_T("�������洢ϵͳ Soap Web Services ��ʽ")

class CAccessControl_Local
{
public:
	CAccessControl_Local(void);
	~CAccessControl_Local(void);
	BOOL LonginSystem(tstring & szLonginType,tstring & szUserName,tstring & szPassword);
	BOOL UpDataAccessControl();

	tstring GetLoginName() const;
	tstring GetLoginUserType() const;

	//����༭������Ϣ
	BOOL CanEditTest();
	//����༭�з�����
	//BOOL CanEditDevReport();
	//���������Ŀ���紴����Ŀ����Ŀ�鵵����Ŀ�������̵�
	BOOL CanMangerProject();

	BOOL CanEditProject(tstring & szProjectName);

	BOOL CanEditProject(_tagProjectState & tProjectState);

	BOOL GetCurTime(SYSTEMTIME & tm);
	tstring &	 GetCurTime();
private:
	tstring					m_szUserName;
	_tagUserMapSet			m_CurUser;
	_tagUserOwnProjectTab	m_CurUserOwnProjectList;
	SYSTEMTIME				m_ServerTime;
	__int64					m_BeginTickCount;
	tstring m_szCurTime;

};
