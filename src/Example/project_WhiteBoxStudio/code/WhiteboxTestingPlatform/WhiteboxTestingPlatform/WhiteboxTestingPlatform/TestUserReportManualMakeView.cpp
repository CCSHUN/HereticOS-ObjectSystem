// TestUserReportManualMakeView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WhiteboxTestingPlatform.h"
#include "TestUserReportManualMakeView.h"
#include "MainFrm.h"

// CTestUserReportManualMakeView

IMPLEMENT_DYNCREATE(CTestUserReportManualMakeView, CFormView)

CTestUserReportManualMakeView::CTestUserReportManualMakeView()
	: CFormView(CTestUserReportManualMakeView::IDD)
{

}

CTestUserReportManualMakeView::~CTestUserReportManualMakeView()
{
}

void CTestUserReportManualMakeView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_REPORT, m_lstReport);
	DDX_Control(pDX, IDC_COMBO_ERROR_TYPE, m_cmbErrorType);
	DDX_Control(pDX, IDC_COMBO_ERROR_CLASS, m_cmbErrorClass);
}

BEGIN_MESSAGE_MAP(CTestUserReportManualMakeView, CFormView)
	ON_NOTIFY(NM_CLICK, IDC_LIST_REPORT, &CTestUserReportManualMakeView::OnNMClickListReport)
	ON_BN_CLICKED(IDC_COMPLATE_CUR_REPORT, &CTestUserReportManualMakeView::OnBnClickedComplateCurReport)
	ON_BN_CLICKED(IDC_REFRESH, &CTestUserReportManualMakeView::OnBnClickedRefresh)
	ON_CBN_EDITCHANGE(IDC_COMBO_ERROR_TYPE, &CTestUserReportManualMakeView::OnCbnEditchangeComboErrorType)
	ON_CBN_EDITUPDATE(IDC_COMBO_ERROR_TYPE, &CTestUserReportManualMakeView::OnCbnEditupdateComboErrorType)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_REPORT, &CTestUserReportManualMakeView::OnLvnItemchangedListReport)
	ON_BN_CLICKED(IDC_IGNORE_CUR_REPORT, &CTestUserReportManualMakeView::OnBnClickedIgnoreCurReport)
	ON_BN_CLICKED(IDC_LOOKTHIRD, &CTestUserReportManualMakeView::OnBnClickedLookthird)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_REPORT, &CTestUserReportManualMakeView::OnLvnColumnclickListReport)
	ON_BN_CLICKED(IDC_SUBMIT, &CTestUserReportManualMakeView::OnBnClickedSubmit)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_REPORT, &CTestUserReportManualMakeView::OnNMDblclkListReport)
	ON_BN_CLICKED(IDC_DELSELIG, &CTestUserReportManualMakeView::OnBnClickedDelselig)
END_MESSAGE_MAP()


// CTestUserReportManualMakeView ���

#ifdef _DEBUG
void CTestUserReportManualMakeView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CTestUserReportManualMakeView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CTestUserReportManualMakeView ��Ϣ�������
void CTestUserReportManualMakeView::OnNMDblclkListReport(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

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

BOOL CTestUserReportManualMakeView::InitCombo()
{
	_tagMachineCheckStandardTypeLib MachineCheckStandardTypeLib = m_pShareData->m_MachineCheckStandardTypeLib;
	map<tstring,_tagMachineCheckStandardTypeSet,less<tstring> >::iterator it = MachineCheckStandardTypeLib.libmap.begin();
	for (; it!=MachineCheckStandardTypeLib.libmap.end(); it++){
		_tagMachineCheckStandardTypeSet MachineCheckStandardTypeSet = it->second;
		m_cmbErrorType.AddString(MachineCheckStandardTypeSet.name.c_str());
	}

	_tagErrorWarningArray ErrorWarningArray = m_pShareData->m_ErrorWarningArray;
	for (unsigned int i=0; i<ErrorWarningArray.WarningArray.size(); i++){
		m_cmbErrorClass.AddString(ErrorWarningArray.WarningArray[i].szErrorWarningName.c_str());
	}

	return TRUE;
}

void CTestUserReportManualMakeView::OnInitialUpdate()
{
	__super::OnInitialUpdate();

	//get sharedata
	m_pShareData = (CProjectSharedData *)(((CChildFrame *)GetParentFrame())->m_ProjectIndex.pSharedObject);
	((CChildFrame *)GetParentFrame())->m_ProjectIndex.pViewInterface = this;
	m_pShareData->init();

	

	InitCombo();
	InitialListCtrlHeadData();
	InitialListCtrlData();


	TreeIndex CodeViewTreeIndex;
	CodeViewTreeIndex=*m_pShareData->m_pTreeIndex;
	CodeViewTreeIndex.IndexList.push_back(TEST_REPORT_MAKE_WORKSPACE_CODEVIEW);
	CodeViewTreeIndex.szPageName=TEST_REPORT_MAKE_WORKSPACE_CODEVIEW;
	CodeViewTreeIndex.szPageType=ADDR_PROJECT;
	CodeViewTreeIndex.pSharedObject=m_pShareData;
	m_pShareData->m_nReportIndex=0;
	theApp.m_WorkSpaceWndManger.ShowWorkPage(&CodeViewTreeIndex);
	m_pShareData->m_pCodeViewCtl->UpDataUi();
}

void CTestUserReportManualMakeView::InitialListCtrlHeadData()
{
	m_lstReport.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_lstReport.InsertColumn(0,_T("���"));
	m_lstReport.InsertColumn(1,_T("��������"));
	m_lstReport.InsertColumn(2,_T("Դ�ļ�"));
	m_lstReport.InsertColumn(3,_T("�к�"));
	m_lstReport.InsertColumn(4,_T("��������"));
	m_lstReport.InsertColumn(5,_T("ͳһ�淶ID"));
	m_lstReport.InsertColumn(6,_T("�������淶ID"));
	m_lstReport.InsertColumn(7,_T("�������"));

	m_lstReport.InsertColumn(8,_T("����ȼ�"));
	m_lstReport.InsertColumn(9,_T("״̬"));

	m_lstReport.SetColumnWidth(0, 40);
	m_lstReport.SetColumnWidth(1, 100);
	m_lstReport.SetColumnWidth(2, 100);
	m_lstReport.SetColumnWidth(3, 0);
	m_lstReport.SetColumnWidth(4, 100);
	m_lstReport.SetColumnWidth(5, 50);
	m_lstReport.SetColumnWidth(6, 50);
	m_lstReport.SetColumnWidth(7, 0);
	m_lstReport.SetColumnWidth(8, 100);
	m_lstReport.SetColumnWidth(9, 100);
}

void CTestUserReportManualMakeView::InitialListCtrlData()
{
	m_lstReport.DeleteAllItems();

	CString sno, sIndex;
	int nCount = m_pShareData->m_Report.m_Data.items.size(), nIndex=1;
	for (int i=0; i<nCount; i++){
		//if(m_pShareData->m_Report.items[i].szThirdStandardErrorNum == tstring(_T("713"))){
		//	m_pShareData->m_Report.items[i].szThirdStandardErrorNum = tstring(_T("713"));
		//}

		if (m_pShareData->m_Report.m_Data.items[i].szTestState != _T("��Ҫ�˹�����") && 
			m_pShareData->m_Report.m_Data.items[i].szTestState != _T("����")){
			continue;
		}

		sIndex.Format(_T("%d"), nIndex++);
		sno.Format(_T("%d"), i);
		int Pos = m_lstReport.InsertItem(m_lstReport.GetItemCount(), sIndex);

		m_lstReport.SetItemText(Pos, 1, m_pShareData->m_Report.m_Data.items[i].szErrorCodeContent.c_str());
		m_lstReport.SetItemText(Pos, 2, m_pShareData->m_Report.m_Data.items[i].szModule.c_str());
		m_lstReport.SetItemText(Pos, 3, m_pShareData->m_Report.m_Data.items[i].szErrorCodePosition.c_str());
		m_lstReport.SetItemText(Pos, 4, m_pShareData->m_Report.m_Data.items[i].szErrorType.c_str());
		m_lstReport.SetItemText(Pos, 5, m_pShareData->m_Report.m_Data.items[i].szUniteStandardErrorNum.c_str());
		m_lstReport.SetItemText(Pos, 6, m_pShareData->m_Report.m_Data.items[i].szThirdStandardErrorNum.c_str());
		m_lstReport.SetItemText(Pos, 7, sno);
		m_lstReport.SetItemText(Pos, 8, m_pShareData->m_Report.m_Data.items[i].szErrorWarning.c_str());
		m_lstReport.SetItemText(Pos, 9, m_pShareData->m_Report.m_Data.items[i].szTestState.c_str());
	}
}

void CTestUserReportManualMakeView::OnNMClickListReport(NMHDR *pNMHDR, LRESULT *pResult)
{
	

	*pResult = 0;
}

void CTestUserReportManualMakeView::OnBnClickedComplateCurReport()
{
	DoWithCurReportItem(_T("���ͨ��"));
}

void CTestUserReportManualMakeView::OnBnClickedRefresh()
{
	InitialListCtrlData();
}

void CTestUserReportManualMakeView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
	__super::OnActivateView(bActivate, pActivateView, pDeactiveView);

	if(bActivate)
	{
		
		if(m_pShareData->m_bNeedGetReport)
		{
			m_pShareData->GetReportObject();
			m_pShareData->m_bNeedGetReport=FALSE;
		}

		if(m_pShareData->m_bManualReportUpdated)
		{
			InitialListCtrlData();
			((CMainFrame *)AfxGetApp()->GetMainWnd())->WriteStringToOutputWnd(_T("======== ҳ�漤���Զ�ˢ���˹��������� ========\r\n"), SB_BOTTOM);
			m_pShareData->m_bManualReportUpdated = FALSE;
		}
	}
}

void CTestUserReportManualMakeView::OnCbnEditchangeComboErrorType()
{
}

void CTestUserReportManualMakeView::OnCbnEditupdateComboErrorType()
{
}

void CTestUserReportManualMakeView::OnLvnItemchangedListReport(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
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

	pWnd = (CWnd *)GetDlgItem(IDC_ERROR_NUM_UNITE);
	pWnd->SetWindowText(m_lstReport.GetItemText(nItem, 5));

	pWnd = (CWnd *)GetDlgItem(IDC_ERROR_NUM_THIRD);
	pWnd->SetWindowText(m_lstReport.GetItemText(nItem, 6));

	CString sIndex = m_lstReport.GetItemText(nItem, 7);
	CString sDes = m_pShareData->m_Report.m_Data.items[atol_t(sIndex.GetBuffer(0))].szDesc.c_str();
	if (sDes.GetLength() > 0){
		sDes += _T("\r\n");	
	}

	CString sThirdErrorNo = m_lstReport.GetItemText(nItem, 6), sUniteErrorNo;
	_tagThirdStandardlib ThirdStandardlib = m_pShareData->m_ThirdStandardlib;
	map<tstring,_tagThirdStandardSet,less<tstring> >::iterator it = ThirdStandardlib.libmap.find(tstring(sThirdErrorNo.GetBuffer(0)));
	if (it != ThirdStandardlib.libmap.end()){
		ThirdStandardSet ThirdStandardSet =  it->second;
		pWnd = (CWnd *)GetDlgItem(IDC_EDIT_CHECK_MEMO);
		pWnd->SetWindowText(ThirdStandardSet.szManual_check_MethodSpecify.c_str());

		sUniteErrorNo = ThirdStandardSet.szUniteStandardErrorNum.c_str();
	}

	pWnd = (CWnd *)GetDlgItem(IDC_DESCRIPTION);
	pWnd->SetWindowText(m_pShareData->m_Report.m_Data.items[atol_t(sIndex.GetBuffer(0))].szUniteDesc.c_str());
	pWnd = (CWnd *)GetDlgItem(IDC_EDIT_SUGGEST);
	pWnd->SetWindowText(m_pShareData->m_Report.m_Data.items[atol_t(sIndex.GetBuffer(0))].szUniteSuggest.c_str());
	
	m_cmbErrorType.SelectString(0, m_pShareData->m_Report.m_Data.items[atol_t(sIndex.GetBuffer(0))].szErrorType.c_str());
	m_cmbErrorClass.SelectString(0, m_pShareData->m_Report.m_Data.items[atol_t(sIndex.GetBuffer(0))].szErrorWarning.c_str());
	
	*pResult = 0;
}

void CTestUserReportManualMakeView::DoWithCurReportItem(const CString &sItemState)
{
	POSITION pos = m_lstReport.GetFirstSelectedItemPosition();
	if (pos == NULL){
		return;
	}

	CString sDes, sSuggest;
	int nSelectedItem = -1, nCount = 0;
	while ((nSelectedItem = m_lstReport.GetNextSelectedItem(pos)) != -1){
		if (m_lstReport.GetItemText(nSelectedItem, 9) != _T("��Ҫ�˹�����")){
			continue;
		}

		int nIndex = atol_t(m_lstReport.GetItemText(nSelectedItem, 7).GetBuffer(0));
		CWnd *pWnd = (CWnd *)GetDlgItem(IDC_DESCRIPTION);
		pWnd->GetWindowText(sDes);

		pWnd = (CWnd *)GetDlgItem(IDC_EDIT_SUGGEST);
		pWnd->GetWindowText(sSuggest);

		m_pShareData->m_Report.m_Data.items[nIndex].szDesc = sDes.GetBuffer(0);
		m_pShareData->m_Report.m_Data.items[nIndex].szSuggest = sSuggest.GetBuffer(0);
		m_pShareData->m_Report.m_Data.items[nIndex].szTestState = (LPCTSTR)sItemState;
		m_pShareData->m_Report.m_Data.items[nIndex].szTestItemSource=_T("�˹�����");
		m_pShareData->m_Report.m_Data.items[nIndex].szLastEditTime = theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetCurTime();

		if (sItemState == _T("����")){
			m_lstReport.SetItemText(nSelectedItem, 9, _T("����"));
		}else if (sItemState == _T("���ͨ��")){
			m_lstReport.DeleteItem(nSelectedItem);
		}

		nCount++;
	}

	m_pShareData->m_bManualReportSaved = TRUE;

	CString sMemo;
	if (sItemState == _T("����")){
		sMemo.Format(_T("======== ������˹�����, ������%d�� ========\r\n"), nCount);
	}else if (sItemState == _T("���ͨ��")){
		sMemo.Format(_T("======== ������˹�����, �����ͨ��%d�� ========\r\n"), nCount);
	}
	((CMainFrame *)AfxGetApp()->GetMainWnd())->WriteStringToOutputWnd(sMemo, SB_BOTTOM);
}

void CTestUserReportManualMakeView::OnBnClickedIgnoreCurReport()
{
	DoWithCurReportItem(_T("����"));
}



void CTestUserReportManualMakeView::OnLvnColumnclickListReport(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	SetRedraw(FALSE);
	m_lstReport.OnLvnColumnclickList1(pNMHDR, pResult);
	SetRedraw(TRUE);
	m_lstReport.Invalidate();
	m_lstReport.UpdateWindow();
	*pResult = 0;
}

void CTestUserReportManualMakeView::OnBnClickedSubmit()
{
	if (m_pShareData->m_bManualReportSaved){
		m_pShareData->UpdataReportObject();
		m_pShareData->m_bComplateReportUpdated = TRUE;

		m_pShareData->m_bManualReportSaved = FALSE;	
		((CMainFrame *)AfxGetApp()->GetMainWnd())->WriteStringToOutputWnd(_T("======== ���������Ѿ��ύ ========\r\n"), SB_BOTTOM);
	}
}

void CTestUserReportManualMakeView::ProjectChange(BOOL bToTop)
{
	if(bToTop)
	{
		//m_pShareData->GetObject();
		//UpdataUi();
		//((CMainFrame *)AfxGetApp()->GetMainWnd())->WriteStringToOutputWnd(_T("======== ��Ŀ����Զ����ر�׼���� ========\r\n"));
	}else{
		if (m_pShareData->m_bManualReportSaved){
			m_pShareData->m_bComplateReportUpdated = TRUE;

			m_pShareData->m_bManualReportSaved = FALSE;
			m_pShareData->UpdataReportObject();
			((CMainFrame *)AfxGetApp()->GetMainWnd())->WriteStringToOutputWnd(_T("======== ��Ŀ����Զ����汨������ ========\r\n"), SB_BOTTOM);
		}
	}
}



void CTestUserReportManualMakeView::OnBnClickedDelselig()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	POSITION   pos   =   m_lstReport.GetFirstSelectedItemPosition();   
	if  (pos   ==   NULL)   
	{
		AfxMessageBox(_T("��ѡ��Ҫɾ����Ԫ��"));
	}
	else   
	{   
		while(pos)   
		{   
			int   nItem   =   m_lstReport.GetNextSelectedItem(pos);   
			int nIndex = atol_t(m_lstReport.GetItemText(nItem, 7).GetBuffer(0));
			//m_pShareData->m_Report.m_Data.items.iterator it=;
			vector<_S_REPORT_ITEM>::iterator itPos=m_pShareData->m_Report.m_Data.items.begin()+nIndex;

			//m_lstReport.DeleteItem(nItem);
			if(m_pShareData->m_Report.m_Data.items[nIndex].szTestState==_T("����"))
			{
				m_pShareData->m_Report.m_Data.items[nIndex].szTestState=_T("ɾ��");
				m_pShareData->m_bManualReportSaved = TRUE;
			}
			

			//   you   could   do   your   own   processing   on   nItem   here   
		}   
		InitialListCtrlData();
	} 
}


void CTestUserReportManualMakeView::OnBnClickedLookthird()
{
	tstring szAddr=_T("�淶:WhiteBoxTestProject\\")+m_pShareData->m_ProjectConfig.TestReportStandard+_T("\\��������׼����");
	CMainFrame * pMain=(CMainFrame *)theApp.m_pMainWnd;

	pMain->m_AddressNavigate.GotoAddr(szAddr);
}