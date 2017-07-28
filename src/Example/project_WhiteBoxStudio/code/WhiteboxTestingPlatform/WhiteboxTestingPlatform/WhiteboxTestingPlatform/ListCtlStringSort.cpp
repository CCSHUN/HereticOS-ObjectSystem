// ListCtlStringSort.cpp : 实现文件
//

#include "stdafx.h"
#include "WhiteboxTestingPlatform.h"
#include "ListCtlStringSort.h"


// CListCtlStringSort

IMPLEMENT_DYNAMIC(CListCtlStringSort, CListCtrl)

CListCtlStringSort::CListCtlStringSort()
{
	sort = 0;
	SubItem = 0;
}

CListCtlStringSort::~CListCtlStringSort()
{
}


/*
BOOL CListCtlStringSort::PreTranslateMessage(MSG* pMsg)
{
	switch(pMsg->message)
	{
	case WM_NOTIFY:
		if(pMsg->lParam==LVN_COLUMNCLICK)
		{
			//UpdateData(TRUE);
			//GotoAddr(tstring(m_szAddress.GetBuffer(0)));
			return TRUE;
		}
		//pMsg->wParam;
	default:
		return CListCtrl::PreTranslateMessage(pMsg);

	}
	return CListCtrl::PreTranslateMessage(pMsg);
}*/
/*
BOOL CListCtlStringSort::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	if(wParam==LVN_COLUMNCLICK)
	{
		AfxMessageBox(_T(""));
	}
	if(lParam==LVN_COLUMNCLICK)
	{
		AfxMessageBox(_T("1"));
	}
	//
	return 0;
}*/
void CListCtlStringSort::OnLvnColumnclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{

	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	int Length = GetItemCount();

	vector<CString> ItemData;

	ItemData.resize(Length);
	for (int i = 0; i < Length; i++)
	
	{
		ItemData[i] = GetItemText(i,pNMLV->iSubItem);
		SetItemData(i,(DWORD_PTR)&ItemData[i]);//设置排序关键字
	}

	if (SubItem != pNMLV->iSubItem)
	{
			sort = 0;
			SubItem = pNMLV->iSubItem;
	}
	else
	{
		if (sort == 0)
		{
				sort = 1;
		}
		else
		{
				sort = 0;
		}
	}
	SortItems(MyCompareProc,(DWORD_PTR)&sort);//排序
		
	*pResult = 0;
}
BEGIN_MESSAGE_MAP(CListCtlStringSort, CListCtrl)
END_MESSAGE_MAP()



// CListCtlStringSort 消息处理程序


