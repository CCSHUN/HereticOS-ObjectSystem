// TestUserStandardUniteView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WhiteboxTestingPlatform.h"
#include "TestUserStandardUniteView.h"
#include "TestUserStandardUniteNewDlg.h"
#include "TestUserStandardUniteEditDlg.h"
#include "ChildFrm.h"
#include "MainFrm.h"
// CTestUserStandardUniteView

IMPLEMENT_DYNCREATE(CTestUserStandardUniteView, CFormView)

CTestUserStandardUniteView::CTestUserStandardUniteView()
	: CFormView(CTestUserStandardUniteView::IDD)
{

}

CTestUserStandardUniteView::~CTestUserStandardUniteView()
{
}

void CTestUserStandardUniteView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_UINTE_STANDARD_LIST, m_UniteStandardList);
	DDX_Text(pDX, IDC_ERROR_NUM, m_szErrorNum);
	DDX_Text(pDX, IDC_ERROR_DESC, m_szDesc);
	DDX_Text(pDX, IDC_ERROR_SUG, m_szErrorSuggest);
	DDX_Text(pDX, IDC_ERROR_TYPE, m_szErrorType);
	DDX_Text(pDX, IDC_ERROR_CLASS, m_szErrorWarning);
}

BEGIN_MESSAGE_MAP(CTestUserStandardUniteView, CFormView)
	ON_WM_CONTEXTMENU()
	ON_BN_CLICKED(IDC_NEW_STANDARD, &CTestUserStandardUniteView::OnBnClickedNewStandard)
	ON_BN_CLICKED(IDC_COMPLATE_STANDARD, &CTestUserStandardUniteView::OnBnClickedComplateStandard)
	ON_BN_CLICKED(IDC_EDIT_STANDARD, &CTestUserStandardUniteView::OnBnClickedEditStandard)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_UINTE_STANDARD_LIST, &CTestUserStandardUniteView::OnLvnItemchangedUinteStandardList)
	ON_NOTIFY(NM_DBLCLK, IDC_UINTE_STANDARD_LIST, &CTestUserStandardUniteView::OnNMDblclkUinteStandardList)
	ON_BN_CLICKED(IDC_DELETE_CUR, &CTestUserStandardUniteView::OnBnClickedDeleteCur)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_UINTE_STANDARD_LIST, &CTestUserStandardUniteView::OnLvnColumnclickListReport)
	ON_COMMAND(ID_OBJ_REGET, OnReGetObject)
	ON_COMMAND(ID_OBJ_RELEASE_LOCK, OnReleaseObjectLock)
	ON_COMMAND(ID_OBJ_GETLOCK, OnGetObjectLock)
	ON_UPDATE_COMMAND_UI(ID_OBJ_REGET, OnCanEdit)
	ON_UPDATE_COMMAND_UI(ID_OBJ_RELEASE_LOCK, OnCanEdit)
	ON_UPDATE_COMMAND_UI(ID_OBJ_GETLOCK, OnCanEdit)
END_MESSAGE_MAP()

void CTestUserStandardUniteView::OnCanEdit(CCmdUI *pCmdUI)
{
	if(theApp.m_WorkSpaceWndManger.m_AccessDataModel.CanEditTest())
	{
		pCmdUI->Enable(TRUE);
		return;
	}

	pCmdUI->Enable(FALSE);
	return;
}

// CTestUserStandardUniteView ���

#ifdef _DEBUG
void CTestUserStandardUniteView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CTestUserStandardUniteView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

void CTestUserStandardUniteView::ProjectChange(BOOL bToTop)
{
	if(bToTop)
	{
		m_pShareData->GetObject();
		UpdataUi();
		((CMainFrame *)AfxGetApp()->GetMainWnd())->WriteStringToOutputWnd(_T("======== ��Ŀ����Զ����ر�׼���� ========\r\n"));
	}else
	{
		m_pShareData->UpdataObject();
		((CMainFrame *)AfxGetApp()->GetMainWnd())->WriteStringToOutputWnd(_T("======== ��Ŀ����Զ������׼���� ========\r\n"));
	}
	
}

void CTestUserStandardUniteView::UpDataObjectUiState()
{
	if((m_pShareData->m_MachineCheckStandardLib.m_nCurError!=CObjectSystemInterface::Error_No)
		)
	{
		return;
	}

	if(m_pShareData->m_MachineCheckStandardLib.m_ObjectState.bLock)
	{
		if(IsCurUserLock(m_pShareData->m_MachineCheckStandardLib))
		{
			//����������
			((CMainFrame *)AfxGetApp()->GetMainWnd())->SetObjectStatus(CFloatWnd::OBJ_STATUS_WRITED,CString(_T("�ѻ�ȡ�����������Ա༭")));
		}else
		{
			//��������������ɫ
			CString szMsg=CString(_T("�����ѱ�["))+CString(m_pShareData->m_MachineCheckStandardLib.m_ObjectState.szLockUser.c_str())+CString(_T("]��������ʱ�޷��༭"));
			((CMainFrame *)AfxGetApp()->GetMainWnd())->SetObjectStatus(CFloatWnd::OBJ_STATUS_READONLY,szMsg);

		}
	}else
	{
		//��ɫ��û���û�����
		((CMainFrame *)AfxGetApp()->GetMainWnd())->SetObjectStatus(CFloatWnd::OBJ_STATUS_OK,CString(_T("������������������������")));
	}
	
}
void CTestUserStandardUniteView::EnableEdit(BOOL bCanEdit)
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
void  CTestUserStandardUniteView::OnReGetObject()
{
	m_pShareData->m_MachineCheckStandardLib.m_ObjectState.szLockUser=theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetLoginName();
	m_pShareData->m_MachineCheckStandardLib.m_ObjectState.bLock=FALSE;
	m_pShareData->m_MachineCheckStandardLib.m_ObjectState.nLockTime=0;
	m_pShareData->m_MachineCheckStandardLib.m_ObjectState.nType=CObjectSystemInterface::Nonmoral;
	m_pShareData->ReGetObject();
	
	EnableEdit(FALSE);

	UpdataUi();
	((CMainFrame *)AfxGetApp()->GetMainWnd())->WriteStringToOutputWnd(_T("======== ���»�ȡ��׼��ˢ�±�׼���� ========\r\n"));
	m_pShareData->m_bIsHopeUpdataUniteUi=FALSE;

	
}
void  CTestUserStandardUniteView::OnReleaseObjectLock()
{
	OnReGetObject();
}
void  CTestUserStandardUniteView::OnGetObjectLock()
{
	//AfxMessageBox(_T("CTestUserStandardUniteView"));
	m_pShareData->m_MachineCheckStandardLib.m_ObjectState.szLockUser=theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetLoginName();
	m_pShareData->m_MachineCheckStandardLib.m_ObjectState.bLock=TRUE;
	m_pShareData->m_MachineCheckStandardLib.m_ObjectState.nLockTime=20*60*1000;
	m_pShareData->m_MachineCheckStandardLib.m_ObjectState.nType=CObjectSystemInterface::Nonmoral;
	if(m_pShareData->ReGetObject())
	{
		if(m_pShareData->m_MachineCheckStandardLib.m_ObjectState.bLock)
		{
			if(m_pShareData->m_MachineCheckStandardLib.m_ObjectState.szLockUser==
				theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetLoginName())
			{
				//���������ɹ�
				EnableEdit(TRUE);
			}else
			{
				//�ѱ������û�����
				EnableEdit(FALSE);
			}
		}else
		{
			//û���û���������
			EnableEdit(FALSE);
		}
		UpdataUi();
	}else
	{
		EnableEdit(FALSE);
	}
	
}

void CTestUserStandardUniteView::OnContextMenu(CWnd* pWnd, CPoint point)
{

	//if (pWnd != pWndTree)
	{
		//AfxMessageBox(_T("12345"));
		//CFormView::OnContextMenu(pWnd, point);
		theApp.GetContextMenuManager()->ShowPopupMenu(IDR_OBJECT_LOCK_MENU, point.x, point.y, this, TRUE);
		return;
	}
}

// CTestUserStandardUniteView ��Ϣ�������
BOOL CTestUserStandardUniteView::UpdataUi()
{
	//tstring szStandardName=((CChildFrame *)GetParentFrame())->m_ProjectIndex.IndexList[0];
	UpDataObjectUiState();
	m_UniteStandardList.DeleteAllItems();
	//_tagMachineCheckStandardSet UniteStandardLib;
	map<tstring,_tagMachineCheckStandardSet,less<tstring> >::iterator it=m_pShareData->m_MachineCheckStandardLib.m_Data.libmap.begin();
	for(;it!=m_pShareData->m_MachineCheckStandardLib.m_Data.libmap.end();it++)
	{
		int Pos=m_UniteStandardList.InsertItem(m_UniteStandardList.GetItemCount(),it->second.szErrorNum.c_str());
		//m_UniteStandardList.SetItemText(Pos,0,it->second.id);
		m_UniteStandardList.SetItemText(Pos,1,it->second.szErrorWarning.c_str());
		m_UniteStandardList.SetItemText(Pos,2,it->second.szErrorType.c_str());
		m_UniteStandardList.SetItemText(Pos,3,it->second.szDesc.c_str());
		m_UniteStandardList.SetItemText(Pos,4,it->second.szErrorSuggest.c_str());
	}

	return TRUE;
}

void CTestUserStandardUniteView::OnInitialUpdate()
{
	//CFormView::OnInitialUpdate();
	CFormView::OnInitialUpdate();

	//m_szCurStandardName=
	m_pShareData=(CStandardSharedData *)(((CChildFrame *)GetParentFrame())->m_ProjectIndex.pSharedObject);
	((CChildFrame *)GetParentFrame())->m_ProjectIndex.pViewInterface=this;
	//m_pShareData->init();
	m_UniteStandardList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_UniteStandardList.InsertColumn(0,_T("�����"));
	m_UniteStandardList.InsertColumn(1,_T("����ȼ�"));
	m_UniteStandardList.InsertColumn(2,_T("��������"));
	m_UniteStandardList.InsertColumn(3,_T("����"));
	m_UniteStandardList.InsertColumn(4,_T("����"));

	m_UniteStandardList.SetColumnWidth(0, 50);
	m_UniteStandardList.SetColumnWidth(1, 80);
	m_UniteStandardList.SetColumnWidth(2, 120);
	m_UniteStandardList.SetColumnWidth(3, 320);
	m_UniteStandardList.SetColumnWidth(4, 320);
	//UpdataUi();
	OnReGetObject();
	
}
void CTestUserStandardUniteView::UpDataBing(BOOL bToSecond)
{
	if(bToSecond)
	{
		//�ӽ��浽����
		UpdateData(TRUE);
		m_CurDataSet.szDesc=m_szDesc;
		m_CurDataSet.szErrorNum=m_szErrorNum;
		m_CurDataSet.szErrorSuggest=m_szErrorSuggest;
		m_CurDataSet.szErrorType=m_szErrorType;
		m_CurDataSet.szErrorWarning=m_szErrorWarning;
	}else
	{
		//�����ݵ�����
		m_szErrorNum=m_CurDataSet.szErrorNum.c_str();
		m_szDesc=m_CurDataSet.szDesc.c_str();
		m_szErrorSuggest=m_CurDataSet.szErrorSuggest.c_str();
		m_szErrorType=m_CurDataSet.szErrorType.c_str();
		m_szErrorWarning=m_CurDataSet.szErrorWarning.c_str();
		UpdateData(FALSE);
	}


}

void CTestUserStandardUniteView::OnBnClickedNewStandard()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CTestUserStandardUniteNewDlg dlg;
	dlg.m_pShareData=m_pShareData;
	if(dlg.DoModal()==IDOK)
	{
		UpdataUi();
	}
}

void CTestUserStandardUniteView::OnBnClickedComplateStandard()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_pShareData->UpdataObject())
	{
		//EnableEdit(FALSE);
		OnReGetObject();
	}
	
}



void CTestUserStandardUniteView::OnBnClickedEditStandard()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������


	if(m_UniteStandardList.GetSelectedCount()<1)
	{
		AfxMessageBox(_T("��ѡ����׼���ٱ༭"));
		return ;
	}
	CTestUserStandardUniteEditDlg dlg;
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
	/*}else
	{
		AfxMessageBox("fail.....");
	}*/
	

}

void CTestUserStandardUniteView::OnLvnItemchangedUinteStandardList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	map<tstring,_tagMachineCheckStandardSet,less<tstring> >::iterator itLib;
	itLib=m_pShareData->m_MachineCheckStandardLib.m_Data.libmap.find(tstring((LPCTSTR)m_UniteStandardList.GetItemText(pNMLV->iItem,0)));
	if(itLib!=m_pShareData->m_MachineCheckStandardLib.m_Data.libmap.end())
	{
		m_CurDataSet=itLib->second;
		UpDataBing(FALSE);
	}
}

void CTestUserStandardUniteView::OnNMDblclkUinteStandardList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	if(m_bCanEdit==FALSE) return;

	map<tstring,_tagMachineCheckStandardSet,less<tstring> >::iterator itLib;
	itLib=m_pShareData->m_MachineCheckStandardLib.m_Data.libmap.find(tstring((LPCTSTR)m_UniteStandardList.GetItemText(pNMItemActivate->iItem,0)));
	if(itLib!=m_pShareData->m_MachineCheckStandardLib.m_Data.libmap.end())
	{
		m_CurDataSet=itLib->second;
		UpDataBing(TRUE);
		CTestUserStandardUniteEditDlg dlg;
		dlg.m_pShareData=m_pShareData;
		dlg.m_CurDataSet=m_CurDataSet;
		if(dlg.DoModal()==IDOK)
		{
			m_UniteStandardList.SetItemText(pNMItemActivate->iItem,1,dlg.m_CurDataSet.szErrorWarning.c_str());
			m_UniteStandardList.SetItemText(pNMItemActivate->iItem,2,dlg.m_CurDataSet.szErrorType.c_str());
			m_UniteStandardList.SetItemText(pNMItemActivate->iItem,3,dlg.m_CurDataSet.szDesc.c_str());
			m_UniteStandardList.SetItemText(pNMItemActivate->iItem,4,dlg.m_CurDataSet.szErrorSuggest.c_str());
			m_CurDataSet=dlg.m_CurDataSet;
			UpDataBing(FALSE);
		}
	}
}

void CTestUserStandardUniteView::OnBnClickedDeleteCur()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_UniteStandardList.GetSelectedCount()<1)
	{
		AfxMessageBox(_T("��ѡ����׼����ɾ��"));
		return ;
	}
	POSITION pos=m_UniteStandardList.GetFirstSelectedItemPosition();
	int item=m_UniteStandardList.GetNextSelectedItem(pos);
	map<tstring,_tagMachineCheckStandardSet,less<tstring> >::iterator itLib;
	itLib=m_pShareData->m_MachineCheckStandardLib.m_Data.libmap.find(tstring((LPCTSTR)m_UniteStandardList.GetItemText(item,0)));
	if(itLib!=m_pShareData->m_MachineCheckStandardLib.m_Data.libmap.end())
	{
		m_pShareData->m_MachineCheckStandardLib.m_Data.libmap.erase(itLib);
		m_pShareData->m_bUniteLibWrited=TRUE;
		m_UniteStandardList.DeleteItem(item);
	}
}

void CTestUserStandardUniteView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
	// TODO: �ڴ����ר�ô����/����û���

	__super::OnActivateView(bActivate, pActivateView, pDeactiveView);
	if(bActivate)
	{
		UpDataObjectUiState();
		if(m_pShareData->m_bIsHopeUpdataUniteUi)
		{
			//m_pShareData->GetObject();
			UpdataUi();
			((CMainFrame *)AfxGetApp()->GetMainWnd())->WriteStringToOutputWnd(_T("======== ҳ�漤���Զ�ˢ�±�׼���� ========\r\n"));
			m_pShareData->m_bIsHopeUpdataUniteUi=FALSE;
		}
		
	}else
	{
		//m_pShareData->UpdataObject();
		//((CMainFrame *)AfxGetApp()->GetMainWnd())->WriteStringToOutputWnd(_T("======== ҳ��ʧȥ�����Զ������׼���� ========\r\n"));
	}

}


void CTestUserStandardUniteView::OnLvnColumnclickListReport(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SetRedraw(FALSE);
	m_UniteStandardList.OnLvnColumnclickList1(pNMHDR, pResult);
	SetRedraw(TRUE);
	m_UniteStandardList.Invalidate();
	m_UniteStandardList.UpdateWindow();
	*pResult = 0;
}