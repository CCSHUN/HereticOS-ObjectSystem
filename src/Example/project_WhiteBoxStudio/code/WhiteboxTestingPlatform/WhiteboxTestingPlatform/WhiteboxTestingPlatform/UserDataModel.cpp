#include "StdAfx.h"
#include "UserDataModel.h"
#include "WhiteboxTestingPlatform.h"

#define USER_PATH		_T("UserInfo\\UserMap\\")
#define USERPRO_PATH		_T("UserInfo\\UserOwnProject\\")
CUserDataModel::CUserDataModel(void)
{
}

CUserDataModel::~CUserDataModel(void)
{
}

BOOL CUserShareData::UpDataCurUser()
{
	BOOL bRet=theApp.m_WorkSpaceWndManger.m_UserDataModel.UpDataUser(m_CurUser);
	if(bRet)
	{
		BOOL bRet=theApp.m_WorkSpaceWndManger.m_UserDataModel.UpDataUserProject(m_CurUser.szUserName,m_CurUserOwnProjectList);
	}

	return bRet;
}

BOOL CUserShareData::init()
{
	m_UserList.clear();
	BOOL bRet=theApp.m_WorkSpaceWndManger.m_UserDataModel.GetAllUser(m_UserList);
	if(bRet)
	{
		bRet=theApp.m_WorkSpaceWndManger.m_ProjectDataModel.GetProjectNameList(m_AllProjectList);
	}
	return TRUE;
}

BOOL CUserShareData::GetCurUserProject()
{
	return theApp.m_WorkSpaceWndManger.m_UserDataModel.GetUserProject(m_CurUser.szUserName,m_CurUserOwnProjectList);
}

BOOL CUserShareData::GetProjectOwnUser(IN tstring & szProjectName)
{
	return theApp.m_WorkSpaceWndManger.m_UserDataModel.GetProjectOwnUser(szProjectName,m_ProjectUserMap);
}

BOOL CUserShareData::UpDataProjectOwnUser(IN tstring & szProjectName)
{
	return theApp.m_WorkSpaceWndManger.m_UserDataModel.UpDataProjectOwnUser(szProjectName,m_ProjectUserMap);
}


BOOL CUserDataModel::GetUser(tstring & szUserName,_tagUserMapSet & UserSet)
{
	tstring szPath;
	szPath=USER_PATH+szUserName;
	_tagUserMapSet_Wrap lib1;
	lib1.m_szAddr=szPath;
	if(lib1.GetObject())
	{
		UserSet=lib1.m_Data;
		return TRUE;
	}else
	{
		return FALSE;
	}
}


BOOL CUserDataModel::GetProjectOwnUser(IN tstring & szProjectName,OUT _tagProjectOwnUser & ProjectUserMap)
{
	tstring szPath = tstring(_T("WhiteBoxTestProject\\Project_"));
	szPath+=szProjectName+tstring(_T("\\ProjectUser"));
	_tagProjectOwnUser_Wrap ProjectUser;
	//ProjectUser.m_Data=ProjectUserMap;
	ProjectUser.m_szAddr=szPath;
	BOOL bRet= ProjectUser.GetObject();
	ProjectUserMap=ProjectUser.m_Data;

	return bRet;
}

BOOL CUserDataModel::UpDataProjectOwnUser(IN tstring & szProjectName,IN _tagProjectOwnUser & ProjectUserMap)
{
	tstring szPath = tstring(_T("WhiteBoxTestProject\\Project_"));
	szPath+=szProjectName+tstring(_T("\\ProjectUser"));
	_tagProjectOwnUser_Wrap ProjectUser;
	ProjectUser.m_szAddr=szPath;
	ProjectUser.m_Data=ProjectUserMap;
	BOOL bRet=ProjectUser.UpDataObject();
	return bRet;
}

BOOL CUserDataModel::GetAllUser(list<_tagUserMapSet> & UserList)
{
	tstring szPath=USER_PATH;
	CObjectSystemInterface::_tagDirectoryInfo Info;
	CObjectSystemInterface::SYSTEMERROR error;
	tstring szFinder=_T("*");
	if(gpObjectSystem->GetDirectoryInfo(szPath,szFinder,Info,&error)==FALSE)
	{
		return FALSE;
	}
	_tagUserMapSet_Wrap lib1;

	for(unsigned int i=0;i<Info.DirectoryInfoArray.size();i++)
	{
		szPath=USER_PATH+Info.DirectoryInfoArray[i].ObjectName;
		_tagUserMapSet  UserSet;
		if(GetUser(Info.DirectoryInfoArray[i].ObjectName,UserSet))
		{
			UserList.push_back(UserSet);
			//return TRUE;
		}else
		{
			return FALSE;
		}
	}
	return TRUE;
}

BOOL CUserDataModel::GetUserProject(tstring & szUserName,_tagUserOwnProjectTab & OwnProject)
{
	tstring szPath=USERPRO_PATH+szUserName;
	_tagUserOwnProjectTab_Wrap lib1;
	lib1.m_szAddr=szPath;
	if(lib1.GetObject())
	{
		OwnProject=lib1.m_Data;
		return TRUE;
	}
	return FALSE;
}

BOOL CUserDataModel::DeleteUser(tstring & szUserName)
{
	tstring szPath=USER_PATH+szUserName;
	CObjectSystemInterface::SYSTEMERROR Error;
	BOOL bRet=gpObjectSystem->DeleteObject(szPath,&Error);
	if(bRet)
	{
		tstring szPath=USERPRO_PATH+szUserName;
		bRet=gpObjectSystem->DeleteObject(szPath,&Error);
	}
	return TRUE;
}

BOOL CUserDataModel::NewUser(_tagUserMapSet & tagUser)
{
	_tagUserOwnProjectTab tab;
	BOOL bRet=UpDataUser(tagUser);
	if(bRet)
	{
		bRet=UpDataUserProject(tagUser.szUserName,tab);
	}
	return bRet;
}


BOOL CUserDataModel::UpDataUser(_tagUserMapSet & tagUser)
{
	tstring szPath=tstring(USER_PATH);
	szPath+=tagUser.szUserName;
	_tagUserMapSet_Wrap lib1;
	lib1.m_szAddr=szPath;
	lib1.m_Data=tagUser;
	return lib1.UpDataObject();
}

BOOL CUserDataModel::UpDataUserProject(tstring & szUserName,_tagUserOwnProjectTab & OwnProject)
{
	tstring szPath=tstring(USERPRO_PATH);
	szPath+=szUserName;
	_tagUserOwnProjectTab_Wrap lib1;
	lib1.m_szAddr=szPath;
	lib1.m_Data=OwnProject;
	return lib1.UpDataObject();
}


BOOL CUserDataModel::GetAdminUiTree(CViewTree & TreeCtl)
{
	TreeCtl.DeleteAllItems();

	HTREEITEM hRoot = TreeCtl.InsertItem(_T("管理员工作区"), 0, 0);
	TreeCtl.SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);

	TreeIndex * pIndex;
	CUserShareData * pShareData = new CUserShareData;

	pIndex=new TreeIndex;
	pIndex->IndexList.push_back(tstring(ADMIN_USER_WORKSPACE));
	pIndex->szPageName=ADMIN_USER_WORKSPACE;
	pIndex->szPageType=ADDR_MGR;
	pIndex->pSharedObject=pShareData;

	HTREEITEM item=TreeCtl.InsertItem(ADMIN_USER_WORKSPACE, 2, 2, hRoot);

	TreeCtl.SetItemData(item,(DWORD_PTR)pIndex);


	pIndex=new TreeIndex;
	pIndex->IndexList.push_back(tstring(ADMIN_STRUCT_DESIGN_WORKSPACE));
	pIndex->szPageName=ADMIN_STRUCT_DESIGN_WORKSPACE;
	pIndex->szPageType=ADDR_MGR;
	pIndex->pSharedObject=pShareData;

	item=TreeCtl.InsertItem(ADMIN_STRUCT_DESIGN_WORKSPACE, 2, 2, hRoot);

	TreeCtl.SetItemData(item,(DWORD_PTR)pIndex);

	//构造一个共享类 存放共享的数据


	

	TreeCtl.Expand(hRoot, TVE_EXPAND);
	return TRUE;
}