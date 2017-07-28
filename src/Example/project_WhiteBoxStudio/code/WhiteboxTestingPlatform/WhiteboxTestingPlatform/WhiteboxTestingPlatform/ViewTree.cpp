
#include "stdafx.h"
#include "ViewTree.h"
#include "WhiteboxTestingPlatform.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define NODE_NAME_CONFIG		_T("配置")
#define NODE_NAME_REPORT		_T("报表")

/////////////////////////////////////////////////////////////////////////////
// CViewTree

typedef struct _S_TREELIST_ITEMDATA{
	int id;
	char level;
}TREELIST_ITEMDATA, *PTREELIST_ITEMDATA;

CViewTree::CViewTree()
{
}

CViewTree::~CViewTree()
{
}

BEGIN_MESSAGE_MAP(CViewTree, CTreeCtrl)
	ON_NOTIFY_REFLECT(NM_CLICK, &CViewTree::OnNMClick)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewTree 消息处理程序

BOOL CViewTree::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	BOOL bRes = CTreeCtrl::OnNotify(wParam, lParam, pResult);

	NMHDR* pNMHDR = (NMHDR*)lParam;
	ASSERT(pNMHDR != NULL);

	if (pNMHDR && pNMHDR->code == TTN_SHOW && GetToolTips() != NULL)
	{
		GetToolTips()->SetWindowPos(&wndTop, -1, -1, -1, -1, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
	}

	return bRes;
}

void CViewTree::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	/************************** 通过识别控件中鼠标位置获取当前选择项 ***********************************/ 
	// 获取当前选择的项
	CTreeCtrl* pTreeCtrl = this;
	CPoint ptCurSel(0, 0);
	TVHITTESTINFO HitTestInfo;

	// 通过鼠标在客户区中的位置
	GetCursorPos(&ptCurSel); 
	pTreeCtrl->ScreenToClient(&ptCurSel);   
	// 获取当前选择的是哪一项
	HitTestInfo.pt = ptCurSel;   
	HTREEITEM hSelect = pTreeCtrl->HitTest(&HitTestInfo);

	/*if(hSelect != NULL)
	{
		CString strItem = pTreeCtrl->GetItemText(hSelect);
		//CString strItem=(LPTSTR)pTreeCtrl->GetItemData(hSelect);
		if(!strItem.CompareNoCase(NODE_NAME_CONFIG)){
			theApp.CreateNewView(theApp.m_pTestingTaskConfigDocTpl);
		}else if(!strItem.CompareNoCase(NODE_NAME_REPORT)){
			theApp.CreateNewView(theApp.m_pReportDocTpl);
		}
	}*/
	//if(m_TreeType==_T("项目视图"))
	//{
	TreeIndex * pindex;
	if(hSelect)
	{
		pindex=(TreeIndex *)pTreeCtrl->GetItemData(hSelect);
		if(pindex)
		{
			tstring szAddr=_T("");
			CMainFrame * pMain=(CMainFrame *)theApp.m_pMainWnd;
			szAddr=theApp.m_WorkSpaceWndManger.m_ProjectDataModel.GetProjectWholePath(pindex);
			if(szAddr[szAddr.length()-1]=='\\')
			{
				szAddr[szAddr.length()-1]=0;
			}
			pMain->m_AddressNavigate.SetAddr(pindex->szPageType,szAddr);

			if(theApp.m_WorkSpaceWndManger.ShowWorkPage(pindex))
			{
				
				szAddr=theApp.m_WorkSpaceWndManger.m_ProjectDataModel.GetProjectWholePath(pindex);
				if(szAddr[szAddr.length()-1]=='\\')
				{
					szAddr[szAddr.length()-1]=0;
				}
				pMain->m_AddressNavigate.SetAddr(pindex->szPageType,szAddr);
			}else
			{
				//pMain->m_AddressNavigate.SetAddr(pindex->szPageType,szAddr);
			}

			
			

			// 设置该项为选中状态 
			pTreeCtrl->SelectItem(hSelect);
		}
	}
	/*}else if(m_TreeType==_T("标准视图"))
	{

	}*/
	
	
	

	
	/*********************************** END *********************************************/ 



	/****************************以下方法获取的是上一次处于选中状态的项 ***************************
	//首先将点击的对象选中 
	CTreeCtrl* pTreeCtrl = this;
	HTREEITEM hSelect = pTreeCtrl->GetSelectedItem(); 
	HTREEITEM hLight = pTreeCtrl->GetDropHilightItem(); 
	if((hLight != NULL) && (hSelect != hLight)) ;
	//hSelect = hLight; 
	if(hSelect   ==   NULL) 
	return; 
	pTreeCtrl->SelectItem(hSelect); 

	//编辑当前选中对象名称
	pTreeCtrl->EditLabel(hSelect);
	if( NULL != hSelect )
	{
	CString strItem = pTreeCtrl->GetItemText(hSelect);

	if(strItem == _T("控制器"))
	{
	pTreeCtrl->SetItemText(hSelect, _T("改变了控制器名称"));
	}

	pTreeCtrl->SetItemText(hSelect, strItem);
	::AfxMessageBox( strItem);  
	}
	*************************************END ********************************/

	*pResult = 0;
}
