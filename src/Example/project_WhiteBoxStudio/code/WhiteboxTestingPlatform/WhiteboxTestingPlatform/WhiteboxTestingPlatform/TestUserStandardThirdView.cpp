// TestUserStandardThirdView.cpp : 实现文件
//

#include "stdafx.h"
#include "WhiteboxTestingPlatform.h"
#include "TestUserStandardThirdView.h"
#include "ChildFrm.h"
#include "MainFrm.h"
#include "TestUserStandardThirdEditDlg.h"
#include "TestUserStandardThirdNewDlg.h"

// CTestUserStandardThirdView

IMPLEMENT_DYNCREATE(CTestUserStandardThirdView, CFormView)

CTestUserStandardThirdView::CTestUserStandardThirdView()
	: CFormView(CTestUserStandardThirdView::IDD)
	, m_is_dealwith(FALSE)
{

}

CTestUserStandardThirdView::~CTestUserStandardThirdView()
{

}

void CTestUserStandardThirdView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_ERROR_NOCHECK, m_is_dealwith);
	DDX_Check(pDX, IDC_ERROR_MANUAL, m_is_manual_check);
	DDX_Text(pDX, IDC_ERROR_NUM, m_szThirdStandardErrorNum);
	DDX_Text(pDX, IDC_ERROR_CHECKSUG, m_szManual_check_MethodSpecify);
	DDX_Text(pDX, IDC_ERROR_UNITENUM, m_szUniteStandardErrorNum);
	//DDX_Text(pDX, IDC_ERROR_SUG, m_);
	DDX_Text(pDX, IDC_ERROR_TOOLTYPE, m_ToolType);
	DDX_Text(pDX, IDC_ERROR_DESC, m_szThirdStandardErrorDesc);
	DDX_Text(pDX, IDC_ERROR_SUG, m_szErrorSuggest);
	DDX_Control(pDX, IDC_REPORT_LIST, m_ThirdStandardList);
}

BEGIN_MESSAGE_MAP(CTestUserStandardThirdView, CFormView)
	ON_WM_CONTEXTMENU()
	ON_BN_CLICKED(IDC_NEW_STANDARD, &CTestUserStandardThirdView::OnBnClickedNewStandard)
	ON_BN_CLICKED(IDC_DELETE_CUR, &CTestUserStandardThirdView::OnBnClickedDeleteCur)
	ON_BN_CLICKED(IDC_COMPLATE_STANDARD, &CTestUserStandardThirdView::OnBnClickedComplateStandard)
	ON_BN_CLICKED(IDC_EDIT_STANDARD, &CTestUserStandardThirdView::OnBnClickedEditStandard)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_REPORT_LIST, &CTestUserStandardThirdView::OnLvnItemchangedReportList)
	ON_NOTIFY(HDN_ITEMDBLCLICK, 0, &CTestUserStandardThirdView::OnHdnItemdblclickReportList)
	ON_NOTIFY(NM_DBLCLK, IDC_REPORT_LIST, &CTestUserStandardThirdView::OnNMDblclkReportList)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_REPORT_LIST, &CTestUserStandardThirdView::OnLvnColumnclickListReport)
	ON_COMMAND(ID_OBJ_REGET, OnReGetObject)
	ON_COMMAND(ID_OBJ_RELEASE_LOCK, OnReleaseObjectLock)
	ON_COMMAND(ID_OBJ_GETLOCK, OnGetObjectLock)
	ON_UPDATE_COMMAND_UI(ID_OBJ_REGET, OnCanEdit)
	ON_UPDATE_COMMAND_UI(ID_OBJ_RELEASE_LOCK, OnCanEdit)
	ON_UPDATE_COMMAND_UI(ID_OBJ_GETLOCK, OnCanEdit)
END_MESSAGE_MAP()

void CTestUserStandardThirdView::OnCanEdit(CCmdUI *pCmdUI)
{
	if(theApp.m_WorkSpaceWndManger.m_AccessDataModel.CanEditTest())
	{
		pCmdUI->Enable(TRUE);
		return;
	}

	pCmdUI->Enable(FALSE);
	return;
}



void CTestUserStandardThirdView::UpDataBing(BOOL bToSecond)
{
	if(bToSecond)
	{
		UpdateData(TRUE);
		m_CurDataSet.is_dealwith=m_is_dealwith;
		m_CurDataSet.is_manual_check=m_is_manual_check;
		m_CurDataSet.szManual_check_MethodSpecify=m_szManual_check_MethodSpecify;
		m_CurDataSet.szThirdStandardErrorDesc=m_szThirdStandardErrorDesc;
		m_CurDataSet.szThirdStandardErrorNum=m_szThirdStandardErrorNum;
		m_CurDataSet.ToolType=m_ToolType;
		m_CurDataSet.szUniteStandardErrorNum=m_szUniteStandardErrorNum;
		m_CurDataSet.szErrorSuggest=m_szErrorSuggest;
	}else
	{
		m_is_dealwith=m_CurDataSet.is_dealwith;
		m_is_manual_check=m_CurDataSet.is_manual_check;
		m_szManual_check_MethodSpecify=m_CurDataSet.szManual_check_MethodSpecify.c_str();
		m_szThirdStandardErrorDesc=m_CurDataSet.szThirdStandardErrorDesc.c_str();
		m_szThirdStandardErrorNum=m_CurDataSet.szThirdStandardErrorNum.c_str();
		m_ToolType=m_CurDataSet.ToolType.c_str();
		m_szUniteStandardErrorNum=m_CurDataSet.szUniteStandardErrorNum.c_str();
		m_szErrorSuggest=m_CurDataSet.szErrorSuggest.c_str();
		UpdateData(FALSE);
	}
}


// CTestUserStandardThirdView 诊断

#ifdef _DEBUG
void CTestUserStandardThirdView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CTestUserStandardThirdView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

void CTestUserStandardThirdView::ProjectChange(BOOL bToTop)
{
	if(bToTop)
	{
		m_pShareData->GetObject();
		UpdataUi();
		((CMainFrame *)AfxGetApp()->GetMainWnd())->WriteStringToOutputWnd(_T("======== 项目变更自动加载标准数据 ========\r\n"));
	}else
	{
		m_pShareData->UpdataObject();
		((CMainFrame *)AfxGetApp()->GetMainWnd())->WriteStringToOutputWnd(_T("======== 项目变更自动保存标准数据 ========\r\n"));
	}

}

void CTestUserStandardThirdView::UpDataObjectUiState()
{
	if((m_pShareData->m_ThirdStandardLib.m_nCurError!=CObjectSystemInterface::Error_No)
		)
	{
		return;
	}
	if(m_pShareData->m_ThirdStandardLib.m_ObjectState.bLock)
	{
		if(IsCurUserLock(m_pShareData->m_ThirdStandardLib))
		{
			//被本人锁定
			((CMainFrame *)AfxGetApp()->GetMainWnd())->SetObjectStatus(CFloatWnd::OBJ_STATUS_WRITED,CString(_T("已获取对象锁定可以编辑")));
		}else
		{
			//被别人锁定　红色
			CString szMsg=CString(_T("对象已被["))+CString(m_pShareData->m_ThirdStandardLib.m_ObjectState.szLockUser.c_str())+CString(_T("]锁定，暂时无法编辑"));
			((CMainFrame *)AfxGetApp()->GetMainWnd())->SetObjectStatus(CFloatWnd::OBJ_STATUS_READONLY,szMsg);

		}
	}else
	{
		//灰色，没有用户锁定
		((CMainFrame *)AfxGetApp()->GetMainWnd())->SetObjectStatus(CFloatWnd::OBJ_STATUS_OK,CString(_T("对象无人锁定，可申请锁定")));
	}

}
void CTestUserStandardThirdView::EnableEdit(BOOL bCanEdit)
{
	m_bCanEdit=bCanEdit;
	if(m_bCanEdit)
	{
		GetDlgItem(IDC_NEW_STANDARD)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_STANDARD)->EnableWindow(TRUE);
		GetDlgItem(IDC_DELETE_CUR)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMPLATE_STANDARD)->EnableWindow(TRUE);
	}else
	{
		GetDlgItem(IDC_NEW_STANDARD)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_STANDARD)->EnableWindow(FALSE);
		GetDlgItem(IDC_DELETE_CUR)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMPLATE_STANDARD)->EnableWindow(FALSE);
	}
}
void  CTestUserStandardThirdView::OnReGetObject()
{
	m_pShareData->m_ThirdStandardLib.m_ObjectState.szLockUser=theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetLoginName();
	m_pShareData->m_ThirdStandardLib.m_ObjectState.bLock=FALSE;
	m_pShareData->m_ThirdStandardLib.m_ObjectState.nLockTime=0;
	m_pShareData->m_ThirdStandardLib.m_ObjectState.nType=CObjectSystemInterface::Nonmoral;
	m_pShareData->ReGetObject();

	EnableEdit(FALSE);

	UpdataUi();
	((CMainFrame *)AfxGetApp()->GetMainWnd())->WriteStringToOutputWnd(_T("======== 重新获取标准　刷新标准数据 ========\r\n"));
	m_pShareData->m_bIsHopeUpdataUniteUi=FALSE;


}
void  CTestUserStandardThirdView::OnReleaseObjectLock()
{
	OnReGetObject();
}
void  CTestUserStandardThirdView::OnGetObjectLock()
{
	//AfxMessageBox(_T("CTestUserStandardUniteView"));
	m_pShareData->m_ThirdStandardLib.m_ObjectState.szLockUser=theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetLoginName();
	m_pShareData->m_ThirdStandardLib.m_ObjectState.bLock=TRUE;
	m_pShareData->m_ThirdStandardLib.m_ObjectState.nLockTime=20*60*1000;
	m_pShareData->m_ThirdStandardLib.m_ObjectState.nType=CObjectSystemInterface::Nonmoral;
	if(m_pShareData->ReGetObject())
	{
		if(m_pShareData->m_ThirdStandardLib.m_ObjectState.bLock)
		{
			if(m_pShareData->m_ThirdStandardLib.m_ObjectState.szLockUser==
				theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetLoginName())
			{
				//申请锁定成功
				EnableEdit(TRUE);
			}else
			{
				//已被其它用户锁定
				EnableEdit(FALSE);
			}
		}else
		{
			//没有用户锁定对象
			EnableEdit(FALSE);
		}
		UpdataUi();
	}else
	{
		EnableEdit(FALSE);
	}

}

void CTestUserStandardThirdView::OnContextMenu(CWnd* pWnd, CPoint point)
{

	//if (pWnd != pWndTree)
	{
		//AfxMessageBox(_T("12345"));
		//CFormView::OnContextMenu(pWnd, point);
		theApp.GetContextMenuManager()->ShowPopupMenu(IDR_OBJECT_LOCK_MENU, point.x, point.y, this, TRUE);
		return;
	}
}
void CTestUserStandardThirdView::OnInitialUpdate()
{
	//CFormView::OnInitialUpdate();
	CFormView::OnInitialUpdate();

	//m_szCurStandardName=
	m_pShareData=(CStandardSharedData *)(((CChildFrame *)GetParentFrame())->m_ProjectIndex.pSharedObject);
	((CChildFrame *)GetParentFrame())->m_ProjectIndex.pViewInterface=this;
	//m_pShareData->init();
	m_ThirdStandardList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_ThirdStandardList.InsertColumn(0,_T("错误号"));
	m_ThirdStandardList.InsertColumn(1,_T("统一规范错误号"));
	m_ThirdStandardList.InsertColumn(2,_T("是否关注"));
	m_ThirdStandardList.InsertColumn(3,_T("是否复查"));
	m_ThirdStandardList.InsertColumn(4,_T("检查工具"));

	m_ThirdStandardList.SetColumnWidth(0, 100);
	m_ThirdStandardList.SetColumnWidth(1, 100);
	m_ThirdStandardList.SetColumnWidth(2, 100);
	m_ThirdStandardList.SetColumnWidth(3, 100);
	m_ThirdStandardList.SetColumnWidth(4, 100);
	//UpdataUi();
	OnReGetObject();

	//((CMainFrame *)AfxGetApp()->GetMainWnd())->SetObjectStatus(CFloatWnd::DOC_STATUS_READONLY, _T("当前文档处于只读状态"));

}


BOOL CTestUserStandardThirdView::UpdataUi()
{
	//tstring szStandardName=((CChildFrame *)GetParentFrame())->m_ProjectIndex.IndexList[0];
	UpDataObjectUiState();
	m_ThirdStandardList.DeleteAllItems();
	//_tagMachineCheckStandardSet UniteStandardLib;
	map<tstring,_tagThirdStandardSet,less<tstring> >::iterator it=m_pShareData->m_ThirdStandardLib.m_Data.libmap.begin();
	for(;it!=m_pShareData->m_ThirdStandardLib.m_Data.libmap.end();it++)
	{
		int Pos=m_ThirdStandardList.InsertItem(m_ThirdStandardList.GetItemCount(),it->second.szThirdStandardErrorNum.c_str());
		//m_UniteStandardList.SetItemText(Pos,0,it->second.id);
		//m_ThirdStandardList.SetItemText(Pos,0,it->second.szThirdStandardErrorNum.c_str());
		m_ThirdStandardList.SetItemText(Pos,1,it->second.szUniteStandardErrorNum.c_str());
		
		m_ThirdStandardList.SetItemText(Pos,2,it->second.is_dealwith==0?_T("关注"):_T("不关注"));
		m_ThirdStandardList.SetItemText(Pos,3,it->second.is_manual_check==0?_T("不需要复查"):_T("需要复查"));
		m_ThirdStandardList.SetItemText(Pos,4,it->second.ToolType.c_str());
		//m_ThirdStandardList.SetItemText(Pos,5,it->second.szThirdStandardErrorDesc.c_str());
		//m_ThirdStandardList.SetItemText(Pos,6,it->second.szErrorSuggest.c_str());
		//m_ThirdStandardList.SetItemText(Pos,7,it->second.szManual_check_MethodSpecify.c_str());
		
	}

	return TRUE;
}

// CTestUserStandardThirdView 消息处理程序

void CTestUserStandardThirdView::OnBnClickedNewStandard()
{
	// TODO: 在此添加控件通知处理程序代码
	CTestUserStandardThirdNewDlg dlg;
	dlg.m_pShareData=m_pShareData;
	if(dlg.DoModal()==IDOK)
	{
		UpdataUi();
	}
}


void CTestUserStandardThirdView::OnBnClickedDeleteCur()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_ThirdStandardList.GetSelectedCount()<1)
	{
		AfxMessageBox(_T("请选定标准后再删除"));
		return ;
	}
	POSITION pos=m_ThirdStandardList.GetFirstSelectedItemPosition();
	int item=m_ThirdStandardList.GetNextSelectedItem(pos);
	map<tstring,_tagThirdStandardSet,less<tstring> >::iterator itLib;
	itLib=m_pShareData->m_ThirdStandardLib.m_Data.libmap.find(tstring((LPCTSTR)m_ThirdStandardList.GetItemText(item,0)));
	if(itLib!=m_pShareData->m_ThirdStandardLib.m_Data.libmap.end())
	{
		m_pShareData->m_ThirdStandardLib.m_Data.libmap.erase(itLib);
		m_pShareData->m_bThirdLibWrited=TRUE;
		m_ThirdStandardList.DeleteItem(item);
	}

}

void CTestUserStandardThirdView::OnBnClickedComplateStandard()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_pShareData->UpdataObject())
	{
		//EnableEdit(FALSE);
		OnReGetObject();
	}
}

void CTestUserStandardThirdView::OnBnClickedEditStandard()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_ThirdStandardList.GetSelectedCount()<1)
	{
		AfxMessageBox(_T("请选定标准后再编辑"));
		return ;
	}
	CTestUserStandardThirdEditDlg dlg;
	dlg.m_pShareData=m_pShareData;
	/*POSITION pos=m_UniteStandardList.GetFirstSelectedItemPosition();
	int item=m_UniteStandardList.GetNextSelectedItem(pos);
	map<tstring,_tagMachineCheckStandardSet,less<tstring> >::iterator itLib;
	itLib=m_pShareData->m_MachineCheckStandardLib.libmap.find(tstring((LPTSTR)m_UniteStandardList.GetItemText(item,0)));
	if(itLib!=m_pShareData->m_MachineCheckStandardLib.libmap.end())
	{*/
		//if(pos==)
	UpDataBing(FALSE);
	dlg.m_CurDataSet=m_CurDataSet;
	if(dlg.DoModal()==IDOK)
	{

	}
}

void CTestUserStandardThirdView::OnLvnItemchangedReportList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	map<tstring,_tagThirdStandardSet,less<tstring> >::iterator itLib;
	itLib=m_pShareData->m_ThirdStandardLib.m_Data.libmap.find(tstring((LPCTSTR)m_ThirdStandardList.GetItemText(pNMLV->iItem,0)));
	if(itLib!=m_pShareData->m_ThirdStandardLib.m_Data.libmap.end())
	{
		m_CurDataSet=itLib->second;
		UpDataBing(FALSE);
	}
}

void CTestUserStandardThirdView::OnHdnItemdblclickReportList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	
}



void CTestUserStandardThirdView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
	// TODO: 在此添加专用代码和/或调用基类

	__super::OnActivateView(bActivate, pActivateView, pDeactiveView);
	if(bActivate)
	{
		UpDataObjectUiState();
		if(m_pShareData->m_bIsHopeUpdataThirdUi)
		{
			//m_pShareData->GetObject();
			UpdataUi();
			((CMainFrame *)AfxGetApp()->GetMainWnd())->WriteStringToOutputWnd(_T("======== 第三方标准管理器 页面激活自动刷新标准数据 ========\r\n"));
			m_pShareData->m_bIsHopeUpdataThirdUi=FALSE;
		}

	}else
	{
		//m_pShareData->UpdataObject();
		//((CMainFrame *)AfxGetApp()->GetMainWnd())->WriteStringToOutputWnd(_T("======== 页面失去焦点自动保存标准数据 ========\r\n"));
	}
}

void CTestUserStandardThirdView::OnNMDblclkReportList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	if(m_bCanEdit==FALSE) return;

	map<tstring,_tagThirdStandardSet,less<tstring> >::iterator itLib;
	itLib=m_pShareData->m_ThirdStandardLib.m_Data.libmap.find(tstring((LPCTSTR)m_ThirdStandardList.GetItemText(pNMItemActivate->iItem,0)));
	if(itLib!=m_pShareData->m_ThirdStandardLib.m_Data.libmap.end())
	{
		m_CurDataSet=itLib->second;
		UpDataBing(TRUE);
		CTestUserStandardThirdEditDlg dlg;
		dlg.m_pShareData=m_pShareData;
		dlg.m_CurDataSet=m_CurDataSet;
		if(dlg.DoModal()==IDOK)
		{

			m_ThirdStandardList.SetItemText(pNMItemActivate->iItem,0,dlg.m_CurDataSet.szThirdStandardErrorNum.c_str());
			//m_UniteStandardList.SetItemText(Pos,0,it->second.id);
			//m_ThirdStandardList.SetItemText(Pos,0,it->second.szThirdStandardErrorNum.c_str());
			m_ThirdStandardList.SetItemText(pNMItemActivate->iItem,1,dlg.m_CurDataSet.szUniteStandardErrorNum.c_str());

			m_ThirdStandardList.SetItemText(pNMItemActivate->iItem,2,dlg.m_CurDataSet.is_dealwith==0?_T("关注"):_T("不关注"));
			m_ThirdStandardList.SetItemText(pNMItemActivate->iItem,3,dlg.m_CurDataSet.is_manual_check==0?_T("不需要复查"):_T("需要复查"));
			m_ThirdStandardList.SetItemText(pNMItemActivate->iItem,4,dlg.m_CurDataSet.ToolType.c_str());

			m_CurDataSet=dlg.m_CurDataSet;
			UpDataBing(FALSE);
		}
	}
}


void CTestUserStandardThirdView::OnLvnColumnclickListReport(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	SetRedraw(FALSE);
	m_ThirdStandardList.OnLvnColumnclickList1(pNMHDR, pResult);
	SetRedraw(TRUE);
	m_ThirdStandardList.Invalidate();
	m_ThirdStandardList.UpdateWindow();
	*pResult = 0;
}

