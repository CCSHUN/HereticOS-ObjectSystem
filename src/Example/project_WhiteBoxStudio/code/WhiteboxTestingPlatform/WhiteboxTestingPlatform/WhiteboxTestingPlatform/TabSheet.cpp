// TabSheet.cpp : implementation file
//

#include "stdafx.h"
#include "TabSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabSheet

CTabSheet::CTabSheet()
{
    m_nNumOfPages = 0;
	m_nCurrentPage = 0;
}

CTabSheet::~CTabSheet()
{
}


BEGIN_MESSAGE_MAP(CTabSheet, CTabCtrl)
	//{{AFX_MSG_MAP(CTabSheet)
	ON_WM_LBUTTONDOWN()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabSheet message handlers

void CTabSheet::Show()
{
	int i=0;
	for(i=0; i < m_nNumOfPages; i++ )
	{
		m_pPages[i]->Create( m_IDD[i], this );
		InsertItem( i, m_Title[i] );
	}

	m_pPages[0]->ShowWindow(SW_SHOW);
	for( i=1; i < m_nNumOfPages; i++)
	{
		m_pPages[i]->ShowWindow(SW_HIDE);
	}
	SetRect();
}

void CTabSheet::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CTabCtrl::OnLButtonDown(nFlags, point);
	if(m_nCurrentPage != GetCurFocus())
	{
		//AfxMessageBox("");
		m_pPages[m_nCurrentPage]->ShowWindow(SW_HIDE);
		m_nCurrentPage=GetCurFocus();
		m_pPages[m_nCurrentPage]->ShowWindow(SW_SHOW);
	}
	else
	{
		//AfxMessageBox("");
	}
}

int CTabSheet::GetCurSel()
{
	return CTabCtrl::GetCurSel();
}

int CTabSheet::SetCurSel(int nItem)
{
	if( nItem < 0 || nItem >= m_nNumOfPages)
		return -1;

	int ret = m_nCurrentPage;

	if(m_nCurrentPage != nItem )
	{
		m_pPages[m_nCurrentPage]->ShowWindow(SW_HIDE);
		m_nCurrentPage = nItem;
		m_pPages[m_nCurrentPage]->ShowWindow(SW_SHOW);
		CTabCtrl::SetCurSel(nItem);
	}

	return ret;
}
int CTabSheet::SetCurSelFromID(int nID)
{
	int i=0;
	for(i=0;i<MAXPAGE&&m_IDD[i]!=nID;)
	{
		if(i==MAXPAGE)
		{
			return -1;
		}
		i++;
	}
	int nItem=i;
	if( nItem < 0 || nItem >= m_nNumOfPages)
		return -1;

	int ret = m_nCurrentPage;

	if(m_nCurrentPage != nItem )
	{
		m_pPages[m_nCurrentPage]->ShowWindow(SW_HIDE);
		m_nCurrentPage = nItem;
		m_pPages[m_nCurrentPage]->ShowWindow(SW_SHOW);
		CTabCtrl::SetCurSel(nItem);
	}

	return ret;
}

void CTabSheet::SetRect()
{
	CRect tabRect, itemRect;
	int nX, nY, nXc, nYc;

	GetClientRect(&tabRect);
	GetItemRect(0, &itemRect);

	if(itemRect.right-itemRect.left>itemRect.bottom-itemRect.top)
	{
		if(tabRect.bottom-itemRect.bottom>itemRect.top-tabRect.top)
		{
			//ио
			nX=itemRect.left;
			nY=itemRect.bottom+1;
			nXc=tabRect.right-itemRect.left-2;
			nYc=tabRect.bottom-nY-1;
		}
		else
		{
			//об
			nX=itemRect.left;
			nY=tabRect.top+1;
			nXc=tabRect.right-itemRect.left-2;
			nYc=itemRect.top-nY-1;
		}
		
	}
	else
	{
		if(tabRect.right-itemRect.right>itemRect.left-tabRect.left)
		{
			//вС
			nX=itemRect.right;
			nY=itemRect.top;
			nXc=tabRect.right-itemRect.right-2;
			nYc=tabRect.bottom-nY-1;
		}
		else
		{
			//ср
			nX=tabRect.left;
			nY=tabRect.top+1;
			nXc=itemRect.left-2;
			nYc=tabRect.bottom-nY-1;
		}
	}

	m_pPages[0]->SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_SHOWWINDOW);
	for( int nCount=1; nCount < m_nNumOfPages; nCount++ )
		m_pPages[nCount]->SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_HIDEWINDOW);
}

void CTabSheet::OnSize(UINT nType, int cx, int cy) 
{
	CTabCtrl::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	switch(nType)
	{
	case SIZE_MAXIMIZED:
		break;
	case SIZE_MINIMIZED:
		break;
	case SIZE_RESTORED:
		{
			/*
			RECT rect;
						this->GetClientRect(&rect);
						if(m_EditCtl.GetSafeHwnd())
						{
							m_EditCtl.SetWindowPos(&wndTop,0,0,rect.right-rect.left,rect.bottom-rect.top,SWP_NOREDRAW);
						}*/
			SetRect();
		}
		break;
	case SIZE_MAXHIDE:
		break;
	case SIZE_MAXSHOW:
		break;
	}
}
BOOL CTabSheet::AddPage(LPCTSTR title, CDialog *pDialog, UINT ID)
{
	if( MAXPAGE == m_nNumOfPages )
		return FALSE;

	m_nNumOfPages++;

	m_pPages[m_nNumOfPages-1] = pDialog;
	m_IDD[m_nNumOfPages-1] = ID;
	m_Title[m_nNumOfPages-1] = title;

	return TRUE;
}
