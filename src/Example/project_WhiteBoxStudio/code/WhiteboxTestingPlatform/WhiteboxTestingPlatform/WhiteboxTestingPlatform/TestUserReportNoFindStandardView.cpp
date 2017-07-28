// TestUserReportNoFindStandardView.cpp : 实现文件
//

#include "stdafx.h"
#include "WhiteboxTestingPlatform.h"
#include "TestUserReportNoFindStandardView.h"
#include "Report.h"
#include "myworkthread.h"
#include "MainFrm.h"

IMPLEMENT_DYNCREATE(CTestUserReportNoFindStandardView, CFormView)

CTestUserReportNoFindStandardView::CTestUserReportNoFindStandardView()
	: CFormView(CTestUserReportNoFindStandardView::IDD)
{

}

CTestUserReportNoFindStandardView::~CTestUserReportNoFindStandardView()
{
}

void CTestUserReportNoFindStandardView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_REPORT, m_lstReport);
}

BEGIN_MESSAGE_MAP(CTestUserReportNoFindStandardView, CFormView)
	ON_NOTIFY(NM_CLICK, IDC_LIST_REPORT, &CTestUserReportNoFindStandardView::OnNMClickListReport)
	ON_BN_CLICKED(IDC_REBUILD_CUR, &CTestUserReportNoFindStandardView::OnBnClickedRebuildCur)
	ON_BN_CLICKED(IDC_REFRESH, &CTestUserReportNoFindStandardView::OnBnClickedRefresh)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_REPORT, &CTestUserReportNoFindStandardView::OnLvnItemchangedListReport)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_REPORT, &CTestUserReportNoFindStandardView::OnLvnColumnclickListReport)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_REPORT, &CTestUserReportNoFindStandardView::OnNMDblclkListReport)
	ON_BN_CLICKED(IDC_EDIT_THIRD, &CTestUserReportNoFindStandardView::OnBnClickedEditThird)
END_MESSAGE_MAP()


void CTestUserReportNoFindStandardView::OnNMDblclkListReport(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	int nItem = pNMItemActivate->iItem;
	if (nItem == -1){
		return;
	}

	int nIndex = atol_t(m_lstReport.GetItemText(nItem, 7).GetBuffer(0));
	m_pShareData->m_nReportIndex = nIndex;
	//m_CodeViewDlg.m_pShareData = m_dataDlg1.m_pShareData = m_dataDlg2.m_pShareData = m_pShareData;
	/*m_CodeViewDlg.m_szUiName = m_dataDlg1.m_szUiName = m_dataDlg2.m_szUiName = _T("#Dev");

	m_tabData.SetCurSelFromID(IDD_CODEVIEW_DLG);
	m_CodeViewDlg.UpdataUi();*/
	
	TreeIndex CodeViewTreeIndex;
	CodeViewTreeIndex=*m_pShareData->m_pTreeIndex;
	CodeViewTreeIndex.IndexList.push_back(TEST_REPORT_MAKE_WORKSPACE_CODEVIEW);
	CodeViewTreeIndex.szPageName=TEST_REPORT_MAKE_WORKSPACE_CODEVIEW;
	CodeViewTreeIndex.szPageType=ADDR_PROJECT;
	CodeViewTreeIndex.pSharedObject=m_pShareData;
	theApp.m_WorkSpaceWndManger.ShowWorkPage(&CodeViewTreeIndex);

	m_pShareData->m_pCodeViewCtl->UpDataUi();

	*pResult = 0;
}

void CTestUserReportNoFindStandardView::OnLvnColumnclickListReport(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	SetRedraw(FALSE);
	m_lstReport.OnLvnColumnclickList1(pNMHDR, pResult);
	SetRedraw(TRUE);
	m_lstReport.Invalidate();
	m_lstReport.UpdateWindow();
	*pResult = 0;
}

// CTestUserReportNoFindStandardView 诊断

#ifdef _DEBUG
void CTestUserReportNoFindStandardView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CTestUserReportNoFindStandardView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

void CTestUserReportNoFindStandardView::InitialListCtrlHeadData()
{
	m_lstReport.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_lstReport.InsertColumn(0,_T("编号"));
	m_lstReport.InsertColumn(1,_T("错误描述"));
	m_lstReport.InsertColumn(2,_T("源文件"));
	m_lstReport.InsertColumn(3,_T("行号"));
	m_lstReport.InsertColumn(4,_T("建议"));
	m_lstReport.InsertColumn(5,_T("统一规范ID"));
	m_lstReport.InsertColumn(6,_T("第三方规范ID"));
	m_lstReport.InsertColumn(7,_T("描述"));
	

	m_lstReport.SetColumnWidth(0, 40);
	m_lstReport.SetColumnWidth(1, 100);
	m_lstReport.SetColumnWidth(2, 100);
	m_lstReport.SetColumnWidth(3, 100);
	m_lstReport.SetColumnWidth(4, 0);
	m_lstReport.SetColumnWidth(5, 100);
	m_lstReport.SetColumnWidth(6, 100);
	m_lstReport.SetColumnWidth(7, 0);
	
}

void CTestUserReportNoFindStandardView::InitialListCtrlData()
{
	m_lstReport.DeleteAllItems();

	CString sno;
	int nCount = m_pShareData->m_Report.m_Data.items.size(), nIndex=1;
	for (int i=0; i<nCount; i++){
		if (m_pShareData->m_Report.m_Data.items[i].szTestState != _T("需要充实规范")){
			continue;
		}

		sno.Format(_T("%d"), nIndex++);
		int Pos = m_lstReport.InsertItem(m_lstReport.GetItemCount(), sno);

		m_lstReport.SetItemText(Pos, 1, m_pShareData->m_Report.m_Data.items[i].szErrorCodeContent.c_str());
		m_lstReport.SetItemText(Pos, 2, m_pShareData->m_Report.m_Data.items[i].szModule.c_str());
		m_lstReport.SetItemText(Pos, 3, m_pShareData->m_Report.m_Data.items[i].szErrorCodePosition.c_str());
		m_lstReport.SetItemText(Pos, 4, m_pShareData->m_Report.m_Data.items[i].szSuggest.c_str());
		m_lstReport.SetItemText(Pos, 5, m_pShareData->m_Report.m_Data.items[i].szUniteStandardErrorNum.c_str());
		m_lstReport.SetItemText(Pos, 6, m_pShareData->m_Report.m_Data.items[i].szThirdStandardErrorNum.c_str());
		m_lstReport.SetItemText(Pos, 7, m_pShareData->m_Report.m_Data.items[i].szDesc.c_str());
		
	}
}

// CTestUserReportNoFindStandardView 消息处理程序

void CTestUserReportNoFindStandardView::OnInitialUpdate()
{
	__super::OnInitialUpdate();

	//get sharedata
	m_pShareData = (CProjectSharedData *)(((CChildFrame *)GetParentFrame())->m_ProjectIndex.pSharedObject);
	((CChildFrame *)GetParentFrame())->m_ProjectIndex.pViewInterface = this;
	m_pShareData->init();

	InitialListCtrlHeadData();
	InitialListCtrlData();
}

void CTestUserReportNoFindStandardView::OnNMClickListReport(NMHDR *pNMHDR, LRESULT *pResult)
{
	

	*pResult = 0;
}

void CTestUserReportNoFindStandardView::OnBnClickedRebuildCur()
{
	if (g_nBuildCount <= 0){
		g_nBuildCount++;

		CReport *pReport = new CReport;
		pReport->m_pShareData = (CProjectSharedData *)m_pShareData;
		pReport->SetBuildType(CReport::BUILD_TYPE);
		AddTaskToWorkThread(pReport);	
	}else{
		::MessageBox(NULL, _T("正在进行BUILD，请不要重复BUILD"), _T("信息"), MB_OK|MB_ICONINFORMATION);
	}

}

void CTestUserReportNoFindStandardView::OnBnClickedRefresh()
{
	InitialListCtrlData();
}

void CTestUserReportNoFindStandardView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
	__super::OnActivateView(bActivate, pActivateView, pDeactiveView);

	if(bActivate)
	{
		if(m_pShareData->m_bNeedGetReport)
		{
			m_pShareData->GetReportObject();
			m_pShareData->m_bNeedGetReport=FALSE;
		}
		if(m_pShareData->m_bNofindReportUpdated)
		{
			InitialListCtrlData();
			((CMainFrame *)AfxGetApp()->GetMainWnd())->WriteStringToOutputWnd(_T("======== 页面激活自动刷新标准补齐数据 ========\r\n"), SB_BOTTOM);
			m_pShareData->m_bNofindReportUpdated = FALSE;
		}
	}
}

void CTestUserReportNoFindStandardView::OnLvnItemchangedListReport(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	//*pResult = 0;
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	int nItem = pNMItemActivate->iItem;
	if (nItem == -1){
		return;
	}

	CString szErrorCodeContent, szErrorCodePosition, szModule, szSummary;
	szErrorCodeContent = m_lstReport.GetItemText(nItem, 1);
	CWnd *pWnd = (CWnd *)GetDlgItem(IDC_ERROR_DESCRIPTION);
	pWnd->SetWindowText(m_lstReport.GetItemText(nItem, 1));

	pWnd = (CWnd *)GetDlgItem(IDC_FILENAME);
	pWnd->SetWindowText(m_lstReport.GetItemText(nItem, 2));

	pWnd = (CWnd *)GetDlgItem(IDC_LINE_NUM);
	pWnd->SetWindowText(m_lstReport.GetItemText(nItem, 3));

	pWnd = (CWnd *)GetDlgItem(IDC_ERROR_NUM_THIRD);
	pWnd->SetWindowText(m_lstReport.GetItemText(nItem, 6));

	*pResult = 0;
}

void CTestUserReportNoFindStandardView::OnBnClickedEditThird()
{
	// TODO: 在此添加控件通知处理程序代码
	//规范:WhiteBoxTestProject\YD应用程序检查标准\第三方标准管理
	tstring szAddr=_T("规范:WhiteBoxTestProject\\")+m_pShareData->m_ProjectConfig.TestReportStandard+_T("\\第三方标准管理");
	CMainFrame * pMain=(CMainFrame *)theApp.m_pMainWnd;
	
	pMain->m_AddressNavigate.GotoAddr(szAddr);

}
