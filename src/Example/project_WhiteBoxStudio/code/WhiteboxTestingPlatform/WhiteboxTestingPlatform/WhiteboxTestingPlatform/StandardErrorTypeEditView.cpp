// StandardErrorTypeEditView.cpp : 实现文件
//

#include "stdafx.h"
#include "WhiteboxTestingPlatform.h"
#include "StandardErrorTypeEditView.h"


// CStandardErrorTypeEditView

IMPLEMENT_DYNCREATE(CStandardErrorTypeEditView, CFormView)

CStandardErrorTypeEditView::CStandardErrorTypeEditView()
	: CFormView(CStandardErrorTypeEditView::IDD)
	, m_szErrorType(_T(""))
	, m_szErrorWraning(_T(""))
{

}

CStandardErrorTypeEditView::~CStandardErrorTypeEditView()
{
}

void CStandardErrorTypeEditView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ERROR_TYPE_LIST, m_StandardErrorTypeList);
	DDX_Control(pDX, IDC_ERROR_CLASS_LIST, m_StandardErrorClassList);
	DDX_Text(pDX, IDC_ERRORTYPE, m_szErrorType);
	DDX_Text(pDX, IDC_ERRORWRANING, m_szErrorWraning);
}

BEGIN_MESSAGE_MAP(CStandardErrorTypeEditView, CFormView)
	ON_WM_CONTEXTMENU()
	ON_BN_CLICKED(IDOK, &CStandardErrorTypeEditView::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CStandardErrorTypeEditView::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_ERRORTYPE_DELETE, &CStandardErrorTypeEditView::OnBnClickedErrortypeDelete)
	ON_BN_CLICKED(IDC_ERRCLASS_DELETE, &CStandardErrorTypeEditView::OnBnClickedErrclassDelete)
	ON_BN_CLICKED(IDC_ERRTYPE_ADD, &CStandardErrorTypeEditView::OnBnClickedErrtypeAdd)
	ON_BN_CLICKED(IDC_ERRCLASS_ADD, &CStandardErrorTypeEditView::OnBnClickedErrclassAdd)
	ON_COMMAND(ID_OBJ_REGET, OnReGetObject)
	ON_COMMAND(ID_OBJ_RELEASE_LOCK, OnReleaseObjectLock)
	ON_COMMAND(ID_OBJ_GETLOCK, OnGetObjectLock)
	ON_UPDATE_COMMAND_UI(ID_OBJ_REGET, OnCanEdit)
	ON_UPDATE_COMMAND_UI(ID_OBJ_RELEASE_LOCK, OnCanEdit)
	ON_UPDATE_COMMAND_UI(ID_OBJ_GETLOCK, OnCanEdit)
END_MESSAGE_MAP()

void CStandardErrorTypeEditView::OnCanEdit(CCmdUI *pCmdUI)
{
	if(theApp.m_WorkSpaceWndManger.m_AccessDataModel.CanEditTest())
	{
		pCmdUI->Enable(TRUE);
		return;
	}

	pCmdUI->Enable(FALSE);
	return;
}


// CStandardErrorTypeEditView 诊断

#ifdef _DEBUG
void CStandardErrorTypeEditView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CStandardErrorTypeEditView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


void CStandardErrorTypeEditView::UpDataObjectUiState()
{
	if((m_pShareData->m_MachineCheckStandardTypeLib.m_nCurError!=CObjectSystemInterface::Error_No)
		||(m_pShareData->m_ErrorWarningArray.m_nCurError!=CObjectSystemInterface::Error_No))
	{
		return;
	}
	if(m_pShareData->m_MachineCheckStandardTypeLib.m_ObjectState.bLock)
	{
		if(IsCurUserLock(m_pShareData->m_MachineCheckStandardTypeLib))
		{
			//被本人锁定
			((CMainFrame *)AfxGetApp()->GetMainWnd())->SetObjectStatus(CFloatWnd::OBJ_STATUS_WRITED,CString(_T("已获取对象锁定可以编辑")));
		}else
		{
			//被别人锁定　红色
			CString szMsg=CString(_T("对象已被["))+CString(m_pShareData->m_MachineCheckStandardTypeLib.m_ObjectState.szLockUser.c_str())+CString(_T("]锁定，暂时无法编辑"));
			((CMainFrame *)AfxGetApp()->GetMainWnd())->SetObjectStatus(CFloatWnd::OBJ_STATUS_READONLY,szMsg);

		}
	}else
	{
		//灰色，没有用户锁定
		((CMainFrame *)AfxGetApp()->GetMainWnd())->SetObjectStatus(CFloatWnd::OBJ_STATUS_OK,CString(_T("对象无人锁定，可申请锁定")));
	}

}
void CStandardErrorTypeEditView::EnableEdit(BOOL bCanEdit)
{
	m_bCanEdit=bCanEdit;
	if(m_bCanEdit)
	{
		GetDlgItem(IDC_ERRCLASS_DELETE)->EnableWindow(TRUE);
		GetDlgItem(IDC_ERRCLASS_ADD)->EnableWindow(TRUE);
		GetDlgItem(IDC_ERRORTYPE_DELETE)->EnableWindow(TRUE);
		GetDlgItem(IDC_ERRTYPE_ADD)->EnableWindow(TRUE);
		GetDlgItem(IDOK)->EnableWindow(TRUE);
	}else
	{
		GetDlgItem(IDC_ERRCLASS_DELETE)->EnableWindow(FALSE);
		GetDlgItem(IDC_ERRCLASS_ADD)->EnableWindow(FALSE);
		GetDlgItem(IDC_ERRORTYPE_DELETE)->EnableWindow(FALSE);
		GetDlgItem(IDC_ERRTYPE_ADD)->EnableWindow(FALSE);
		GetDlgItem(IDOK)->EnableWindow(FALSE);
	}
}
void  CStandardErrorTypeEditView::OnReGetObject()
{
	m_pShareData->m_MachineCheckStandardTypeLib.m_ObjectState.szLockUser=theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetLoginName();
	m_pShareData->m_MachineCheckStandardTypeLib.m_ObjectState.bLock=FALSE;
	m_pShareData->m_MachineCheckStandardTypeLib.m_ObjectState.nLockTime=0;
	m_pShareData->m_MachineCheckStandardTypeLib.m_ObjectState.nType=CObjectSystemInterface::Nonmoral;

	m_pShareData->m_ErrorWarningArray.m_ObjectState.szLockUser=theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetLoginName();
	m_pShareData->m_ErrorWarningArray.m_ObjectState.bLock=FALSE;
	m_pShareData->m_ErrorWarningArray.m_ObjectState.nLockTime=0;
	m_pShareData->m_ErrorWarningArray.m_ObjectState.nType=CObjectSystemInterface::Nonmoral;

	m_pShareData->ReGetObject();

	EnableEdit(FALSE);

	UpdataUi();
	((CMainFrame *)AfxGetApp()->GetMainWnd())->WriteStringToOutputWnd(_T("======== 重新获取标准　刷新标准数据 ========\r\n"));
	m_pShareData->m_bIsHopeUpdataUniteUi=FALSE;


}
void  CStandardErrorTypeEditView::OnReleaseObjectLock()
{
	OnReGetObject();
}
void  CStandardErrorTypeEditView::OnGetObjectLock()
{
	//AfxMessageBox(_T("CTestUserStandardUniteView"));
	m_pShareData->m_MachineCheckStandardTypeLib.m_ObjectState.szLockUser=theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetLoginName();
	m_pShareData->m_MachineCheckStandardTypeLib.m_ObjectState.bLock=TRUE;
	m_pShareData->m_MachineCheckStandardTypeLib.m_ObjectState.nLockTime=20*60*1000;
	m_pShareData->m_MachineCheckStandardTypeLib.m_ObjectState.nType=CObjectSystemInterface::Nonmoral;

	m_pShareData->m_ErrorWarningArray.m_ObjectState.szLockUser=theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetLoginName();
	m_pShareData->m_ErrorWarningArray.m_ObjectState.bLock=TRUE;
	m_pShareData->m_ErrorWarningArray.m_ObjectState.nLockTime=20*60*1000;
	m_pShareData->m_ErrorWarningArray.m_ObjectState.nType=CObjectSystemInterface::Nonmoral;

	if(m_pShareData->ReGetObject())
	{
		if(m_pShareData->m_MachineCheckStandardTypeLib.m_ObjectState.bLock)
		{
			if(m_pShareData->m_MachineCheckStandardTypeLib.m_ObjectState.szLockUser==
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

void CStandardErrorTypeEditView::OnContextMenu(CWnd* pWnd, CPoint point)
{

	//if (pWnd != pWndTree)
	{
		//AfxMessageBox(_T("12345"));
		//CFormView::OnContextMenu(pWnd, point);
		theApp.GetContextMenuManager()->ShowPopupMenu(IDR_OBJECT_LOCK_MENU, point.x, point.y, this, TRUE);
		return;
	}
}


// CStandardErrorTypeEditView 消息处理程序

void CStandardErrorTypeEditView::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_pShareData->UpdataObject())
	{
		OnReGetObject();
	}
}

void CStandardErrorTypeEditView::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CStandardErrorTypeEditView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
	// TODO: 在此添加专用代码和/或调用基类

	CFormView::OnActivateView(bActivate, pActivateView, pDeactiveView);
	if(bActivate)
	{
		UpDataObjectUiState();
	}
}

void CStandardErrorTypeEditView::OnBnClickedErrortypeDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	int pos=m_StandardErrorTypeList.GetCurSel();
	int len=m_StandardErrorTypeList.GetTextLen(pos);
	TCHAR * pText=new TCHAR[len+2];
	m_StandardErrorTypeList.GetText(pos,pText);
	map<tstring,_tagMachineCheckStandardTypeSet,less<tstring> >::iterator itErrorType=m_pShareData->m_MachineCheckStandardTypeLib.m_Data.libmap.find(tstring(pText));
	if(itErrorType!=m_pShareData->m_MachineCheckStandardTypeLib.m_Data.libmap.end())
	{
		m_pShareData->m_MachineCheckStandardTypeLib.m_Data.libmap.erase(itErrorType);
		m_pShareData->m_bErrorTypeLibWrited=TRUE;
	}
	delete pText;

	m_StandardErrorTypeList.DeleteString(pos);
}

void CStandardErrorTypeEditView::OnBnClickedErrclassDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	int pos=m_StandardErrorClassList.GetCurSel();
	int len=m_StandardErrorClassList.GetTextLen(pos);
	TCHAR * pText=new TCHAR[len+2];
	m_StandardErrorClassList.GetText(pos,pText);
	vector<_tagErrorWarningSet>::iterator it=m_pShareData->m_ErrorWarningArray.m_Data.WarningArray.begin();
	for(;it!=m_pShareData->m_ErrorWarningArray.m_Data.WarningArray.end();it++)
	{
		if(it->szErrorWarningName==tstring(pText))
		{
			m_pShareData->m_ErrorWarningArray.m_Data.WarningArray.erase(it);
			m_pShareData->m_bErrorWarningLibWrited=TRUE;
			break;
		}
	}
	
	delete  pText;

	m_StandardErrorClassList.DeleteString(pos);
}

void CStandardErrorTypeEditView::OnBnClickedErrtypeAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_StandardErrorTypeList.AddString(m_szErrorType);
	_tagMachineCheckStandardTypeSet Set;
	Set.name=m_szErrorType;
	m_pShareData->m_MachineCheckStandardTypeLib.m_Data.libmap[Set.name]=Set;
	m_pShareData->m_bErrorTypeLibWrited=TRUE;
}

/*
void CStandardErrorTypeEditView::ProjectChange(BOOL bToTop)
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

}*/

// CTestUserStandardUniteView 消息处理程序
BOOL CStandardErrorTypeEditView::UpdataUi()
{
	
	UpDataObjectUiState();
	m_StandardErrorTypeList.ResetContent();
	map<tstring,_tagMachineCheckStandardTypeSet,less<tstring> >::iterator itErrorType=m_pShareData->m_MachineCheckStandardTypeLib.m_Data.libmap.begin();
	for(;itErrorType!=m_pShareData->m_MachineCheckStandardTypeLib.m_Data.libmap.end();itErrorType++)
	{
		m_StandardErrorTypeList.AddString(itErrorType->second.name.c_str());
	}

	//vector<_tagErrorWarningSet>::iterator itWarning=m_pShareData->m_ErrorWarningArray.
	m_StandardErrorClassList.ResetContent();
	for (unsigned int i=0;i<m_pShareData->m_ErrorWarningArray.m_Data.WarningArray.size();i++)
	{
		m_StandardErrorClassList.AddString(m_pShareData->m_ErrorWarningArray.m_Data.WarningArray[i].szErrorWarningName.c_str());
	}
	return TRUE;
}

void CStandardErrorTypeEditView::OnInitialUpdate()
{
	//CFormView::OnInitialUpdate();
	CFormView::OnInitialUpdate();

	//m_szCurStandardName=
	m_pShareData=(CStandardSharedData *)(((CChildFrame *)GetParentFrame())->m_ProjectIndex.pSharedObject);
	((CChildFrame *)GetParentFrame())->m_ProjectIndex.pViewInterface=this;
	//m_pShareData->init();
	
	UpdataUi();

	OnReGetObject();

}
void CStandardErrorTypeEditView::UpDataBing(BOOL bToSecond)
{
	if(bToSecond)
	{
		//从界面到数据
		UpdateData(TRUE);
		
		/*m_CurDataSet.szDesc=m_szDesc;
		m_CurDataSet.szErrorNum=m_szErrorNum;
		m_CurDataSet.szErrorSuggest=m_szErrorSuggest;
		m_CurDataSet.szErrorType=m_szErrorType;
		m_CurDataSet.szErrorWarning=m_szErrorWarning;*/
	}else
	{
		//从数据到界面
		/*m_szErrorNum=m_CurDataSet.szErrorNum.c_str();
		m_szDesc=m_CurDataSet.szDesc.c_str();
		m_szErrorSuggest=m_CurDataSet.szErrorSuggest.c_str();
		m_szErrorType=m_CurDataSet.szErrorType.c_str();
		m_szErrorWarning=m_CurDataSet.szErrorWarning.c_str();*/
		UpdateData(FALSE);
	}


}


void CStandardErrorTypeEditView::OnBnClickedErrclassAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_StandardErrorClassList.AddString(m_szErrorWraning);
	_tagErrorWarningSet Set;
	Set.szErrorWarningName=m_szErrorWraning;
	m_pShareData->m_ErrorWarningArray.m_Data.WarningArray.push_back(Set);
	m_pShareData->m_bErrorWarningLibWrited=TRUE;
	//m_.libmap[_T("1234")]=Set;
}
