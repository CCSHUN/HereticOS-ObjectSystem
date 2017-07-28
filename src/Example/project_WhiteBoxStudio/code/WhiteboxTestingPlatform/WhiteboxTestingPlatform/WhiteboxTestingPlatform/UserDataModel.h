#pragma once


#define USER_TYPE_TESTER	_T("测试")
#define USER_TYPE_DEVELOP	_T("研发")
#define USER_TYPE_ADMIN		_T("管理员")
class CUserDataModel
{
public:
	CUserDataModel(void);
	~CUserDataModel(void);
	BOOL GetAdminUiTree(CViewTree & TreeCtl);

	BOOL GetAllUser(list<_tagUserMapSet> & UserList);
	BOOL GetUser(tstring & szUserName,_tagUserMapSet & UserSet);
	BOOL GetUserProject(tstring & szUserName,_tagUserOwnProjectTab & OwnProject);
	BOOL DeleteUser(tstring & szUserName);
	BOOL NewUser(_tagUserMapSet & tagUser);
	BOOL UpDataUser(_tagUserMapSet & tagUser);
	BOOL UpDataUserProject(tstring & szUserName,_tagUserOwnProjectTab & OwnProject);

	//项目拥有用户
	BOOL GetProjectOwnUser(IN tstring & szProjectName,OUT _tagProjectOwnUser & ProjectUserMap);
	BOOL UpDataProjectOwnUser(IN tstring & szProjectName,IN _tagProjectOwnUser & ProjectUserMap);

};


class CUserShareData : public CUiSharedData
{
public:
	list<_tagUserMapSet>	m_UserList;
	_tagUserMapSet			m_CurUser;
	_tagUserOwnProjectTab	m_CurUserOwnProjectList;
	_tagProjectOwnUser		m_ProjectUserMap;


	map<tstring,tstring,less<tstring> >	m_AllProjectList;

	BOOL	m_bEdited;		//编辑过数据
	BOOL	init();
	BOOL	UpDataCurUser();
	BOOL	GetCurUserProject();

	BOOL GetProjectOwnUser(IN tstring & szProjectName);
	BOOL UpDataProjectOwnUser(IN tstring & szProjectName);

	CUserShareData(){};
	~CUserShareData(){};
protected:
	
private:
};