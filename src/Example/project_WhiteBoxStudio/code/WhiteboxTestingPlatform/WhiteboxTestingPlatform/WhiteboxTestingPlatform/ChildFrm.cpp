
// ChildFrm.cpp : CChildFrame ���ʵ��
//

#include "stdafx.h"
#include "WhiteboxTestingPlatform.h"

#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWndEx)
	ON_REGISTERED_MESSAGE(AFX_WM_ON_MOVETABCOMPLETE, &CChildFrame::OnMoveTabComplete)
END_MESSAGE_MAP()

// CChildFrame ����/����

CChildFrame::CChildFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
}

CChildFrame::~CChildFrame()
{
}

LRESULT CChildFrame::OnMoveTabComplete(WPARAM wp, LPARAM lp)
{
	return 0;
};
BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ��������ʽ
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;
	cs.style = cs.style&(~(WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE|WS_SYSMENU));

	return TRUE;
}

BOOL CChildFrame::CanShowOnMDITabs()
{
	return theApp.m_WorkSpaceWndManger.CanTab(m_ProjectIndex);
}

// CChildFrame ���

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CChildFrame ��Ϣ�������
