
#include "stdafx.h"
#include "ViewTree.h"
#include "WhiteboxTestingPlatform.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define NODE_NAME_CONFIG		_T("����")
#define NODE_NAME_REPORT		_T("����")

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
// CViewTree ��Ϣ�������

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
	/************************** ͨ��ʶ��ؼ������λ�û�ȡ��ǰѡ���� ***********************************/ 
	// ��ȡ��ǰѡ�����
	CTreeCtrl* pTreeCtrl = this;
	CPoint ptCurSel(0, 0);
	TVHITTESTINFO HitTestInfo;

	// ͨ������ڿͻ����е�λ��
	GetCursorPos(&ptCurSel); 
	pTreeCtrl->ScreenToClient(&ptCurSel);   
	// ��ȡ��ǰѡ�������һ��
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
	//if(m_TreeType==_T("��Ŀ��ͼ"))
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

			
			

			// ���ø���Ϊѡ��״̬ 
			pTreeCtrl->SelectItem(hSelect);
		}
	}
	/*}else if(m_TreeType==_T("��׼��ͼ"))
	{

	}*/
	
	
	

	
	/*********************************** END *********************************************/ 



	/****************************���·�����ȡ������һ�δ���ѡ��״̬���� ***************************
	//���Ƚ�����Ķ���ѡ�� 
	CTreeCtrl* pTreeCtrl = this;
	HTREEITEM hSelect = pTreeCtrl->GetSelectedItem(); 
	HTREEITEM hLight = pTreeCtrl->GetDropHilightItem(); 
	if((hLight != NULL) && (hSelect != hLight)) ;
	//hSelect = hLight; 
	if(hSelect   ==   NULL) 
	return; 
	pTreeCtrl->SelectItem(hSelect); 

	//�༭��ǰѡ�ж�������
	pTreeCtrl->EditLabel(hSelect);
	if( NULL != hSelect )
	{
	CString strItem = pTreeCtrl->GetItemText(hSelect);

	if(strItem == _T("������"))
	{
	pTreeCtrl->SetItemText(hSelect, _T("�ı��˿���������"));
	}

	pTreeCtrl->SetItemText(hSelect, strItem);
	::AfxMessageBox( strItem);  
	}
	*************************************END ********************************/

	*pResult = 0;
}
