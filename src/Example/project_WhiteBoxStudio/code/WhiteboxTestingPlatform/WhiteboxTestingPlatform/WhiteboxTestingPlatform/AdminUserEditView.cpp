// AdminUserEditView.cpp : 实现文件
//

#include "stdafx.h"
#include "WhiteboxTestingPlatform.h"
#include "AdminUserEditView.h"
#include "AdminUserAddEditDlg.h"

// CAdminUserEditView

IMPLEMENT_DYNCREATE(CAdminUserEditView, CFormView)

CAdminUserEditView::CAdminUserEditView()
	: CFormView(CAdminUserEditView::IDD)
{

}

CAdminUserEditView::~CAdminUserEditView()
{
}

void CAdminUserEditView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_USER, m_UserListCtl);
	DDX_Control(pDX, IDC_LIST_USERPROJECT, m_UserProjectListBox);
	DDX_Control(pDX, IDC_LIST_NOUSING_USERPROJECT, m_UserNoUsingProjectListBox);
}

BEGIN_MESSAGE_MAP(CAdminUserEditView, CFormView)
	ON_BN_CLICKED(IDC_OK, &CAdminUserEditView::OnBnClickedOk)
	ON_BN_CLICKED(IDC_EDITUSER, &CAdminUserEditView::OnBnClickedEdituser)
	ON_BN_CLICKED(IDC_ADDUSER, &CAdminUserEditView::OnBnClickedAdduser)
	ON_BN_CLICKED(IDC_DELSELUSER, &CAdminUserEditView::OnBnClickedDelseluser)
	ON_BN_CLICKED(IDC_ADDPRO, &CAdminUserEditView::OnBnClickedAddpro)
	ON_BN_CLICKED(IDC_REMOVEPRO, &CAdminUserEditView::OnBnClickedRemovepro)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_USER, &CAdminUserEditView::OnLvnItemchangedListUser)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_USER, &CAdminUserEditView::OnNMDblclkListUser)
END_MESSAGE_MAP()


// CAdminUserEditView 诊断

#ifdef _DEBUG
void CAdminUserEditView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAdminUserEditView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAdminUserEditView 消息处理程序

void CAdminUserEditView::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	
}

void CAdminUserEditView::OnBnClickedEdituser()
{
	// TODO: 在此添加控件通知处理程序代码
	CAdminUserAddEditDlg dlg;
	dlg.m_pShareData=m_pShareData;
	dlg.m_bEdit=TRUE;
	if(dlg.DoModal()==IDOK)
	{
		m_pShareData->m_CurUser=dlg.m_CurUser;
		m_pShareData->m_bEdited=TRUE;
		//m_pShareData->m_CurUserOwnProjectList.OwnProjectArray.clear();
		//m_pShareData->m_UserList.push_back(m_pShareData->m_CurUser);
		m_pShareData->UpDataCurUser();
		m_pShareData->init();
		UpdataUi();
		//m_UserListCtl->
	}
}

void CAdminUserEditView::OnBnClickedAdduser()
{
	// TODO: 在此添加控件通知处理程序代码
	CAdminUserAddEditDlg dlg;
	dlg.m_pShareData=m_pShareData;
	if(dlg.DoModal()==IDOK)
	{
		m_pShareData->m_CurUser=dlg.m_CurUser;
		m_pShareData->m_bEdited=TRUE;
		m_pShareData->m_CurUserOwnProjectList.OwnProjectArray.clear();
		m_pShareData->m_UserList.push_back(m_pShareData->m_CurUser);
		m_pShareData->UpDataCurUser();
		UpdataUi();
		//m_UserListCtl->
	}

}

BOOL CAdminUserEditView::UpdataUi()
{
	m_UserListCtl.DeleteAllItems();
	//_tagMachineCheckStandardSet UniteStandardLib;
	list<_tagUserMapSet>::iterator it=m_pShareData->m_UserList.begin();
	for(;it!=m_pShareData->m_UserList.end();it++)
	{
		int Pos=m_UserListCtl.InsertItem(m_UserListCtl.GetItemCount(),it->szUserName.c_str());
		//m_UniteStandardList.SetItemText(Pos,0,it->second.id);
		//m_ThirdStandardList.SetItemText(Pos,0,it->second.szThirdStandardErrorNum.c_str());
		m_UserListCtl.SetItemText(Pos,1,it->szUserType.c_str());

		//m_UserListCtl.SetItemText(Pos,2,it->second.is_dealwith==0?_T("关注"):_T("不关注"));
		//m_UserListCtl.SetItemText(Pos,3,it->second.is_manual_check==0?_T("不需要复查"):_T("需要复查"));
		//m_ThirdStandardList.SetItemText(Pos,4,it->second.ToolType.c_str());
		//m_ThirdStandardList.SetItemText(Pos,5,it->second.szThirdStandardErrorDesc.c_str());
		//m_ThirdStandardList.SetItemText(Pos,6,it->second.szErrorSuggest.c_str());
		//m_ThirdStandardList.SetItemText(Pos,7,it->second.szManual_check_MethodSpecify.c_str());

	}
	tstring szUserName=m_pShareData->m_CurUser.szUserName;
	if(szUserName.length())
	{
		m_UserProjectListBox.ResetContent();
		m_UserNoUsingProjectListBox.ResetContent();
		list<_tagUserMapSet>::iterator it=m_pShareData->m_UserList.begin();

		for(;it!=m_pShareData->m_UserList.end();it++)
		{
			if(it->szUserName==szUserName)
			{
				//m_pShareData->m_CurUser=*it;
				if(m_pShareData->GetCurUserProject())
				{
					map<tstring,_tagUserProjectSet,less<tstring> >::iterator itPos=m_pShareData->m_CurUserOwnProjectList.OwnProjectArray.begin();
					for(;itPos!=m_pShareData->m_CurUserOwnProjectList.OwnProjectArray.end();itPos++)
					{
						m_UserProjectListBox.AddString(itPos->first.c_str());
					}
					map<tstring,tstring,less<tstring> >::iterator itAllProject=m_pShareData->m_AllProjectList.begin();
					for(;itAllProject!=m_pShareData->m_AllProjectList.end();itAllProject++)
					{
						if(m_pShareData->m_CurUserOwnProjectList.OwnProjectArray.find(itAllProject->first)
							==m_pShareData->m_CurUserOwnProjectList.OwnProjectArray.end())
						{
							m_UserNoUsingProjectListBox.AddString(itAllProject->first.c_str());
						}
					}
				}
			}

		}
	}
	
	return TRUE;
}
void CAdminUserEditView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	m_pShareData=(CUserShareData *)(((CChildFrame *)GetParentFrame())->m_ProjectIndex.pSharedObject);
	((CChildFrame *)GetParentFrame())->m_ProjectIndex.pViewInterface=this;
	m_pShareData->m_bEdited=FALSE;
	m_pShareData->init();


	m_UserListCtl.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_UserListCtl.InsertColumn(0,_T("用户名"));
	m_UserListCtl.InsertColumn(1,_T("用户类型"));


	m_UserListCtl.SetColumnWidth(0, 100);
	m_UserListCtl.SetColumnWidth(1, 100);


	UpdataUi();
}
void CAdminUserEditView::OnBnClickedDelseluser()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CAdminUserEditView::OnBnClickedAddpro()
{
	// TODO: 在此添加控件通知处理程序代码
	//int nCurProject=m_UserNoUsingProjectListBox.GetCurSel();
	//m_UserNoUsingProjectListBox.getIt
	int pos=m_UserNoUsingProjectListBox.GetCurSel();
	if(pos==-1)
	{
		return;
	}
	int len=m_UserNoUsingProjectListBox.GetTextLen(pos);
	TCHAR * pText=new TCHAR[len+2];
	m_UserNoUsingProjectListBox.GetText(pos,pText);
	_tagUserProjectSet ProjectSet;
	ProjectSet.szProjectName=tstring(pText);
	ProjectSet.szUserName=tstring(m_pShareData->m_CurUser.szUserName);
	


	m_pShareData->GetProjectOwnUser(ProjectSet.szProjectName);
	_tagProjectOwnUserSet User;
	User.szUserName=m_pShareData->m_CurUser.szUserName;
	User.szUserType=m_pShareData->m_CurUser.szUserType;
	m_pShareData->m_ProjectUserMap.OwnUserMap[ProjectSet.szUserName]=User;
	if(m_pShareData->UpDataProjectOwnUser(ProjectSet.szProjectName))
	{
		m_pShareData->m_CurUserOwnProjectList.OwnProjectArray[ProjectSet.szProjectName]=ProjectSet;
		m_pShareData->m_bEdited=TRUE;
		m_pShareData->UpDataCurUser();
	}

	
	UpdataUi();
}

void CAdminUserEditView::OnBnClickedRemovepro()
{
	// TODO: 在此添加控件通知处理程序代码
	int pos=m_UserProjectListBox.GetCurSel();
	if(pos==-1)
	{
		return;
	}
	int len=m_UserProjectListBox.GetTextLen(pos);
	TCHAR * pText=new TCHAR[len+2];
	m_UserProjectListBox.GetText(pos,pText);
	_tagUserProjectSet ProjectSet;
	ProjectSet.szProjectName=tstring(pText);
	ProjectSet.szUserName=tstring(m_pShareData->m_CurUser.szUserName);
	//=ProjectSet;

	m_pShareData->GetProjectOwnUser(ProjectSet.szProjectName);
	_tagProjectOwnUserSet User;
	User.szUserName=m_pShareData->m_CurUser.szUserName;
	User.szUserType=m_pShareData->m_CurUser.szUserType;
	m_pShareData->m_ProjectUserMap.OwnUserMap.erase(User.szUserName);
	if(m_pShareData->UpDataProjectOwnUser(ProjectSet.szProjectName))
	{
		m_pShareData->m_CurUserOwnProjectList.OwnProjectArray.erase(ProjectSet.szProjectName);
		m_pShareData->m_bEdited=TRUE;
		m_pShareData->UpDataCurUser();
	}
	UpdataUi();
}

void CAdminUserEditView::OnLvnItemchangedListUser(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if(m_pShareData->m_bEdited)
	{
		m_pShareData->UpDataCurUser();
	}
	m_UserProjectListBox.ResetContent();
	m_UserNoUsingProjectListBox.ResetContent();

	list<_tagUserMapSet>::iterator it=m_pShareData->m_UserList.begin();
	tstring szUserName=m_UserListCtl.GetItemText(pNMLV->iItem,0);
	for(;it!=m_pShareData->m_UserList.end();it++)
	{
		if(it->szUserName==szUserName)
		{
			m_pShareData->m_CurUser=*it;
			if(m_pShareData->GetCurUserProject())
			{
				map<tstring,_tagUserProjectSet,less<tstring> >::iterator itPos=m_pShareData->m_CurUserOwnProjectList.OwnProjectArray.begin();
				for(;itPos!=m_pShareData->m_CurUserOwnProjectList.OwnProjectArray.end();itPos++)
				{
					m_UserProjectListBox.AddString(itPos->first.c_str());
				}
				map<tstring,tstring,less<tstring> >::iterator itAllProject=m_pShareData->m_AllProjectList.begin();
				for(;itAllProject!=m_pShareData->m_AllProjectList.end();itAllProject++)
				{
					if(m_pShareData->m_CurUserOwnProjectList.OwnProjectArray.find(itAllProject->first)
						==m_pShareData->m_CurUserOwnProjectList.OwnProjectArray.end())
					{
						m_UserNoUsingProjectListBox.AddString(itAllProject->first.c_str());
					}
				}
			}
		}
		
	}


	*pResult = 0;
}

void CAdminUserEditView::OnNMDblclkListUser(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	OnLvnItemchangedListUser(pNMHDR,pResult);
	OnBnClickedEdituser();

	*pResult = 0;
}
