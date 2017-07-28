r0006l22t24// TestUserReportComplateView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WhiteboxTestingPlatform.h"
#include "TestUserReportComplateView.h"
#include "MainFrm.h"
#include "NewPost.h"

// CTestUserReportComplateView

IMPLEMENT_DYNCREATE(CTestUserReportComplateView, CFormView)

CTestUserReportComplateView::CTestUserReportComplateView()
: CFormView(CTestUserReportComplateView::IDD)
{

}

CTestUserReportComplateView::~CTestUserReportComplateView()
{
}

void CTestUserReportComplateView::InitTab()
{

	m_tabData.AddPage(_T("������Ϣ"),&m_dataDlg1,IDD_DEVUSER_REPORT_VIEW_1);
	//m_tabData.AddPage(_T("��������"),&m_dataDlg2,IDD_DEVUSER_REPORT_VIEW_2);
	m_tabData.AddPage(_T("���ⶨλ"),&m_CodeViewDlg,IDD_CODEVIEW_DLG);
	m_tabData.Show();

}

void CTestUserReportComplateView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_REPORT, m_lstReport);
	DDX_Control(pDX, IDC_TAB_DATA, m_tabData);
}

BEGIN_MESSAGE_MAP(CTestUserReportComplateView, CFormView)
	ON_BN_CLICKED(IDC_REFRESH, &CTestUserReportComplateView::OnBnClickedRefresh)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_REPORT, &CTestUserReportComplateView::OnNMCustomdrawListReport)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_REPORT, &CTestUserReportComplateView::OnLvnItemchangedListReport)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_REPORT, &CTestUserReportComplateView::OnLvnColumnclickListReport)

	ON_BN_CLICKED(IDC_LOOKTHIRD, &CTestUserReportComplateView::OnBnClickedLookthird)
	ON_BN_CLICKED(IDC_SUBMIT, &CTestUserReportComplateView::OnBnClickedSubmit)
	ON_BN_CLICKED(IDC_MAKE_SUMMARY, &CTestUserReportComplateView::OnBnClickedMakeSummary)
	ON_BN_CLICKED(IDC_SENDPOST, &CTestUserReportComplateView::OnBnClickedSendpost)

	ON_COMMAND(ID_OBJ_REGET, OnReGetObject)
	ON_COMMAND(ID_OBJ_RELEASE_LOCK, OnReleaseObjectLock)
	ON_COMMAND(ID_OBJ_GETLOCK, OnGetObjectLock)
	ON_WM_CONTEXTMENU()
	ON_BN_CLICKED(IDC_COMPLATE_REPORT, &CTestUserReportComplateView::OnBnClickedComplateReport)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_REPORT, &CTestUserReportComplateView::OnNMDblclkListReport)
	ON_BN_CLICKED(IDC_EDITREPORT, &CTestUserReportComplateView::OnBnClickedEditreport)
	ON_BN_CLICKED(IDC_DELREPORT, &CTestUserReportComplateView::OnBnClickedDelreport)
END_MESSAGE_MAP()


// CTestUserReportComplateView ���

#ifdef _DEBUG
void CTestUserReportComplateView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CTestUserReportComplateView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

void CTestUserReportComplateView::OnLvnColumnclickListReport(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	SetRedraw(FALSE);
	m_lstReport.OnLvnColumnclickList1(pNMHDR, pResult);
	SetRedraw(TRUE);
	m_lstReport.Invalidate();
	m_lstReport.UpdateWindow();
	*pResult = 0;
}


void CTestUserReportComplateView::InitialListCtrlHeadData()
{
	m_lstReport.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_lstReport.InsertColumn(0,_T("���"));
	m_lstReport.InsertColumn(1,_T("����"));
	m_lstReport.InsertColumn(2,_T("Դ�ļ�"));
	m_lstReport.InsertColumn(3,_T("�к�"));
	m_lstReport.InsertColumn(4,_T("����"));
	m_lstReport.InsertColumn(5,_T("UID"));
	m_lstReport.InsertColumn(6,_T("TID"));
	m_lstReport.InsertColumn(7,_T("�������"));
	m_lstReport.InsertColumn(8,_T("����ȼ�"));
	m_lstReport.InsertColumn(9,_T("��Դ"));

	m_lstReport.SetColumnWidth(0, 40);
	m_lstReport.SetColumnWidth(1, 200);
	m_lstReport.SetColumnWidth(2, 100);
	m_lstReport.SetColumnWidth(3, 100);
	m_lstReport.SetColumnWidth(4, 0);
	m_lstReport.SetColumnWidth(5, 50);
	m_lstReport.SetColumnWidth(6, 50);
	m_lstReport.SetColumnWidth(7, 0);
	m_lstReport.SetColumnWidth(8, 100);
	m_lstReport.SetColumnWidth(9, 100);
}

void CTestUserReportComplateView::InitialListCtrlData()
{
	m_lstReport.DeleteAllItems();

	CString sno, sIndex;
	int nCount = m_pShareData->m_Report.m_Data.items.size(), nIndex=1;
	for (int i=0; i<nCount; i++){
		if (m_pShareData->m_Report.m_Data.items[i].szTestState != _T("���ͨ��")){
			continue;
		}

		sno.Format(_T("%d"), i);
		sIndex.Format(_T("%d"), nIndex++);
		int Pos = m_lstReport.InsertItem(m_lstReport.GetItemCount(), sIndex);

		m_lstReport.SetItemText(Pos, 1, m_pShareData->m_Report.m_Data.items[i].szUniteDesc.c_str());
		m_lstReport.SetItemText(Pos, 2, m_pShareData->m_Report.m_Data.items[i].szModule.c_str());
		m_lstReport.SetItemText(Pos, 3, m_pShareData->m_Report.m_Data.items[i].szErrorCodePosition.c_str());
		m_lstReport.SetItemText(Pos, 4, m_pShareData->m_Report.m_Data.items[i].szSuggest.c_str());
		m_lstReport.SetItemText(Pos, 5, m_pShareData->m_Report.m_Data.items[i].szUniteStandardErrorNum.c_str());
		m_lstReport.SetItemText(Pos, 6, m_pShareData->m_Report.m_Data.items[i].szThirdStandardErrorNum.c_str());
		m_lstReport.SetItemText(Pos, 7, sno);
		m_lstReport.SetItemText(Pos, 8, m_pShareData->m_Report.m_Data.items[i].szErrorWarning.c_str());
		m_lstReport.SetItemText(Pos, 9, m_pShareData->m_Report.m_Data.items[i].szTestItemSource.c_str());
	}
}

// CTestUserReportComplateView ��Ϣ�������

void CTestUserReportComplateView::OnInitialUpdate()
{
	__super::OnInitialUpdate();

	//get sharedata
	m_pShareData = (CProjectSharedData *)(((CChildFrame *)GetParentFrame())->m_ProjectIndex.pSharedObject);
	((CChildFrame *)GetParentFrame())->m_ProjectIndex.pViewInterface = this;
	//m_pShareData->init();

	this->OnReGetObject();

	InitialListCtrlHeadData();
	InitialListCtrlData();
	InitTab();
}

void CTestUserReportComplateView::OnBnClickedRefresh()
{
	InitialListCtrlData();
}

void CTestUserReportComplateView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
	__super::OnActivateView(bActivate, pActivateView, pDeactiveView);

	if(bActivate)
	{
		UpDataObjectUiState();
		if(m_pShareData->m_bNeedGetReport)
		{
			m_pShareData->GetReportObject();
			m_pShareData->m_bNeedGetReport=FALSE;
		}

		if(m_pShareData->m_bComplateReportUpdated)
		{
			InitialListCtrlData();
			((CMainFrame *)AfxGetApp()->GetMainWnd())->WriteStringToOutputWnd(_T("======== ҳ�漤���Զ�ˢ����������� ========\r\n"), SB_BOTTOM);
			m_pShareData->m_bComplateReportUpdated = FALSE;
		}
	}
}

void CTestUserReportComplateView::OnNMCustomdrawListReport(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = CDRF_DODEFAULT;
	NMLVCUSTOMDRAW * lplvdr=(NMLVCUSTOMDRAW*)pNMHDR;
	NMCUSTOMDRAW &nmcd = lplvdr->nmcd;
	switch(lplvdr->nmcd.dwDrawStage)//�ж�״̬
	{
	case CDDS_PREPAINT:
		{
			*pResult = CDRF_NOTIFYITEMDRAW;
			break;
		}
	case CDDS_ITEMPREPAINT://���Ϊ��ITEM֮ǰ��Ҫ������ɫ�ĸı�
		{
			int nItem = static_cast<int>(lplvdr->nmcd.dwItemSpec);
			CString sIndex = m_lstReport.GetItemText(nItem, 7);
			if (m_pShareData->m_Report.m_Data.items[atol_t(sIndex.GetBuffer(0))].szErrorWarning.find(_T("����")) != -1){
				lplvdr->clrTextBk = RGB(255, 0, 0);
				*pResult = CDRF_NOTIFYSUBITEMDRAW;	
			}
			if (m_pShareData->m_Report.m_Data.items[atol_t(sIndex.GetBuffer(0))].szErrorWarning.find(_T("����")) != -1){
				lplvdr->clrTextBk = RGB(255, 0xd7, 0);
				*pResult = CDRF_NOTIFYSUBITEMDRAW;	
			}
		}
		break;
	}
}

void  CTestUserReportComplateView::OnReGetObject()
{
	m_pShareData->m_Report.m_ObjectState.szLockUser=theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetLoginName()+_T("#TEST");
	m_pShareData->m_Report.m_ObjectState.bLock=FALSE;
	m_pShareData->m_Report.m_ObjectState.nLockTime=0;
	m_pShareData->m_Report.m_ObjectState.nType=CObjectSystemInterface::Nonmoral;
	m_pShareData->ReGetObject();

	EnableEdit(FALSE);

	UpdataUi();
	((CMainFrame *)AfxGetApp()->GetMainWnd())->WriteStringToOutputWnd(_T("======== ���»�ȡ����ˢ�±������� ========\r\n"));
}

void  CTestUserReportComplateView::OnReleaseObjectLock()
{
	OnReGetObject();
	EnableEdit(FALSE);

	UpdataUi();
}

void  CTestUserReportComplateView::OnGetObjectLock()
{
	m_pShareData->m_Report.m_ObjectState.szLockUser=theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetLoginName()+_T("#TEST");
	m_pShareData->m_Report.m_ObjectState.bLock=TRUE;
	m_pShareData->m_Report.m_ObjectState.nLockTime=20*60*1000;
	m_pShareData->m_Report.m_ObjectState.nType=CObjectSystemInterface::Nonmoral;

	m_pShareData->m_ProjectState.m_ObjectState.szLockUser=theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetLoginName()+_T("#TEST");
	m_pShareData->m_ProjectState.m_ObjectState.bLock=TRUE;
	m_pShareData->m_ProjectState.m_ObjectState.nLockTime=20*60*1000;
	m_pShareData->m_ProjectState.m_ObjectState.nType=CObjectSystemInterface::Nonmoral;

	if(m_pShareData->ReGetObject())
	{
		if(m_pShareData->m_Report.m_ObjectState.bLock)
		{
			if(m_pShareData->m_Report.m_ObjectState.szLockUser==
				theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetLoginName()+_T("#TEST"))
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

void CTestUserReportComplateView::EnableEdit(BOOL bCanEdit)
{
	m_bCanEdit=bCanEdit;
	GetDlgItem(IDC_SUBMIT)->EnableWindow(m_bCanEdit);
	GetDlgItem(IDC_SENDPOST)->EnableWindow(m_bCanEdit);
	GetDlgItem(IDC_EDITREPORT)->EnableWindow(m_bCanEdit);
	GetDlgItem(IDC_DELREPORT)->EnableWindow(FALSE);
	if(m_pShareData->m_ProjectState.m_Data.szProjectState!=PROJECT_STATE_NEW_OVER)
	{
		GetDlgItem(IDC_COMPLATE_REPORT)->EnableWindow(m_bCanEdit);
	}

	if(theApp.m_WorkSpaceWndManger.m_AccessDataModel.CanMangerProject())
	{
		GetDlgItem(IDC_DELREPORT)->EnableWindow(m_bCanEdit);
	}
	
}

void CTestUserReportComplateView::UpDataObjectUiState()
{
	if(m_pShareData->m_Report.m_ObjectState.bLock)
	{
		if(m_pShareData->m_Report.m_ObjectState.szLockUser==
			theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetLoginName()+_T("#TEST"))
		{
			//����������
			((CMainFrame *)AfxGetApp()->GetMainWnd())->SetObjectStatus(CFloatWnd::OBJ_STATUS_WRITED,CString(_T("�ѻ�ȡ�����������Ա༭")));
		}else
		{
			//��������������ɫ
			CString szMsg=CString(_T("�����ѱ�["))+CString(m_pShareData->m_Report.m_ObjectState.szLockUser.c_str())+CString(_T("]��������ʱ�޷��༭"));
			((CMainFrame *)AfxGetApp()->GetMainWnd())->SetObjectStatus(CFloatWnd::OBJ_STATUS_READONLY,szMsg);

		}
	}else
	{
		//��ɫ��û���û�����
		((CMainFrame *)AfxGetApp()->GetMainWnd())->SetObjectStatus(CFloatWnd::OBJ_STATUS_OK,CString(_T("������������������������")));
	}
}

BOOL CTestUserReportComplateView::UpdataUi()
{
	UpDataObjectUiState();
	InitialListCtrlData();

	return TRUE;
}


void CTestUserReportComplateView::OnNMDblclkListReport(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	int nItem = pNMItemActivate->iItem;
	if (nItem == -1){
		return;
	}

	int nIndex = atol_t(m_lstReport.GetItemText(nItem, 7).GetBuffer(0));
	m_CodeViewDlg.m_iDataIndex = m_dataDlg1.m_iDataIndex = m_dataDlg2.m_iDataIndex = nIndex;
	m_CodeViewDlg.m_pShareData = m_dataDlg1.m_pShareData = m_dataDlg2.m_pShareData = m_pShareData;
	m_CodeViewDlg.m_szUiName = m_dataDlg1.m_szUiName = m_dataDlg2.m_szUiName = _T("#Dev");

	m_tabData.SetCurSelFromID(IDD_CODEVIEW_DLG);
	m_CodeViewDlg.UpdataUi();
	*pResult = 0;
}

void CTestUserReportComplateView::OnLvnItemchangedListReport(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	int nItem = pNMItemActivate->iItem;
	if (nItem == -1){
		return;
	}

	int nIndex = atol_t(m_lstReport.GetItemText(nItem, 7).GetBuffer(0));
	CWnd *pWnd=NULL;

/*
	CWnd *pWnd = (CWnd *)GetDlgItem(IDC_ERROR_DESCRIPTION);
	pWnd->SetWindowText(m_pShareData->m_Report.m_Data.items[nIndex].szErrorCodeContent.c_str());

	pWnd = (CWnd *)GetDlgItem(IDC_FILENAME);
	pWnd->SetWindowText(m_lstReport.GetItemText(nItem, 2));

	pWnd = (CWnd *)GetDlgItem(IDC_LINE_NUM);
	pWnd->SetWindowText(m_lstReport.GetItemText(nItem, 3));

	pWnd = (CWnd *)GetDlgItem(IDC_EDIT_SUGGEST);
	pWnd->SetWindowText(m_lstReport.GetItemText(nItem, 4));*/

	pWnd = (CWnd *)GetDlgItem(IDC_ERROR_NUM_UNITE);
	pWnd->SetWindowText(m_lstReport.GetItemText(nItem, 5));

	pWnd = (CWnd *)GetDlgItem(IDC_ERROR_NUM_THIRD);
	pWnd->SetWindowText(m_lstReport.GetItemText(nItem, 6));

	pWnd = (CWnd *)GetDlgItem(IDC_ERROR_TYPE);
	pWnd->SetWindowText(m_pShareData->m_Report.m_Data.items[nIndex].szErrorType.c_str());
	pWnd = (CWnd *)GetDlgItem(IDC_ERROR_CLASS);
	pWnd->SetWindowText(m_pShareData->m_Report.m_Data.items[nIndex].szErrorWarning.c_str());

	//����б༭�õ��������飬������Ϊ�༭�õ���������
	m_CodeViewDlg.m_iDataIndex = m_dataDlg1.m_iDataIndex = m_dataDlg2.m_iDataIndex = nIndex;
	m_CodeViewDlg.m_pShareData = m_dataDlg1.m_pShareData = m_dataDlg2.m_pShareData = m_pShareData;
	m_CodeViewDlg.m_szUiName = m_dataDlg1.m_szUiName = m_dataDlg2.m_szUiName = _T("#TEST");


	if((pNMItemActivate->uOldState==0)&&(pNMItemActivate->uNewState==3))
	{
		int nTab=m_tabData.GetCurSel();
		m_dataDlg1.UpdataUi();
		m_CodeViewDlg.UpdataUi();

	}
}

void CTestUserReportComplateView::OnBnClickedLookthird()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CTestUserReportComplateView::OnBnClickedSubmit()
{
	m_pShareData->UpdataReportObject();
	((CMainFrame *)AfxGetApp()->GetMainWnd())->WriteStringToOutputWnd(_T("======== ���������Ѿ��ύ ========\r\n"), SB_BOTTOM);
	OnReleaseObjectLock();
}


#include <vector>
typedef struct _tagReportStat
{
	unsigned int nTotal;
	unsigned int nComplateTotal;
	unsigned int nManaualTotal;
	unsigned int nignoreTotal;
	vector<_S_REPORT_ITEM> vec;
}ReportStat;


//#define TELEPLATE_FILE_VAL_MAP_BEGIN(name) ma

#include "TemplateTool.h"



/*
BOOL MakeFileByTemplateFile(IN CTemplateTool::TemplateMap & ValMap,IN tstring & szTemplateFileName,OUT tstring & szOutFileName)
{
	CStdioFile fTemplatefile;
	if (!fTemplatefile.Open(theApp.GetAppPath()+szTemplateFileName.c_str(), CFile::modeRead)){
		return FALSE;
	}

	CStdioFile fOutfile;
	if(strstr_t(szOutFileName.c_str(),_T("\\")))
	{
		if (!fOutfile.Open(szOutFileName.c_str(), CFile::modeCreate | CFile::modeReadWrite)){
			return FALSE;
		}
	}else
	{
		if (!fOutfile.Open(theApp.GetAppPath()+szOutFileName.c_str(), CFile::modeCreate | CFile::modeReadWrite)){
			return FALSE;
		}
	}
	

	CString szTemplate1;
	tstring szTemplate;
	tstring szOutFile;
	for(;;)
	{
		if(fTemplatefile.ReadString(szTemplate1))
		{
			szTemplate+=(LPCTSTR)szTemplate1;
			szTemplate+=_T("\r\n");
		}else
		{
			break;
		}
	}
	
	if(CTemplateTool::MakeStringByTemplateString(ValMap,szTemplate,szOutFile))
	{
		fOutfile.WriteString(szOutFile.c_str());
		fTemplatefile.Close();
		fOutfile.Close();
		return TRUE;
	}
	fTemplatefile.Close();
	fOutfile.Close();
	return FALSE;
}*/

unsigned int GetStringTotalLine(tstring & szDst)
{
	unsigned int nRetNum=0;
	TCHAR * pPos=(TCHAR *)szDst.c_str();
	for(;;)
	{
		pPos=strstr_t(pPos,_T("\n"));
		if(pPos)
		{
			nRetNum++;
			pPos++;
		}else
		{
			break;
		}
	}
	return nRetNum;
}
BOOL MakeExeclRowData(unsigned int nRow,unsigned int nCol,unsigned int nLen,unsigned int nHig,tstring & szStyleId,IN tstring & szData,OUT tstring & szOutExeclRow)
{
	TCHAR szRow[16];
	TCHAR szCol[16];
	TCHAR szLen[16];
	TCHAR szHight[16];


	itoa_t(nRow,szRow,10);
	itoa_t(nCol,szCol,10);
	itoa_t(nLen,szLen,10);
	itoa_t(nHig,szHight,10);
	szOutExeclRow.clear();

	szOutExeclRow+=_T("<Row ss:Index=\"")+tstring(szRow);
	szOutExeclRow+=_T("\" ss:AutoFitHeight=\"0\">\r\n\t<Cell ss:Index=\"")+tstring(szCol);
	szOutExeclRow+=_T("\" ss:MergeAcross=\"")+tstring(szLen);
	szOutExeclRow+=_T("\" ss:MergeDown=\"")+tstring(szHight);
	szOutExeclRow+=_T("\" ss:StyleID=\"")+tstring(szStyleId);
	szOutExeclRow+=_T("\"><Data ss:Type=\"String\">")+tstring(szData);
	szOutExeclRow+=_T("</Data></Cell>\r\n</Row>\r\n");
	return TRUE;
}
void MakeSummary(_S_REPORT_Wrap & m_Report)
{

	_tagReportOutput OutputReport;
	map<tstring, _tagReportStat, less<tstring> > g_mapReportStat;

	//��������������
	map<tstring, _tagReportStat, less<tstring> >::iterator itFind;

	map<tstring,tstring,less<tstring> >  ValMap;
	
	tstring szExecl,szExeclTemp;
	unsigned int nRow=1;

	memset(&OutputReport.Overall,0,sizeof(OutputReport.Overall));

	for (unsigned int i=0;i<m_Report.m_Data.items.size();i++)
	{
		if(m_Report.m_Data.items[i].szUniteDesc.length()==0)
		{
			continue;
		}

		OutputReport.Overall.nErrorTotal++;

		if (m_Report.m_Data.items[i].szTestState == _T("���ͨ��"))
		{
			OutputReport.Overall.nComplateTotal+=1;
		}else if (m_Report.m_Data.items[i].szTestState == _T("��Ҫ�˹�����"))
		{
			OutputReport.Overall.nManaualTotal+=1;

		}else if (m_Report.m_Data.items[i].szTestState == _T("����"))
		{
			OutputReport.Overall.nIgnoreTotal+=1;
		}else
		{
			continue;
		}


		itFind=g_mapReportStat.find(m_Report.m_Data.items[i].szUniteDesc);

		if(itFind!=g_mapReportStat.end())
		{
			g_mapReportStat[m_Report.m_Data.items[i].szUniteDesc].nTotal+=1;
			g_mapReportStat[m_Report.m_Data.items[i].szUniteDesc].vec.push_back(m_Report.m_Data.items[i]);
			if (m_Report.m_Data.items[i].szTestState == _T("���ͨ��"))
			{
				g_mapReportStat[m_Report.m_Data.items[i].szUniteDesc].nComplateTotal+=1;
			}else if (m_Report.m_Data.items[i].szTestState == _T("��Ҫ�˹�����"))
			{
				g_mapReportStat[m_Report.m_Data.items[i].szUniteDesc].nManaualTotal+=1;

			}else if (m_Report.m_Data.items[i].szTestState == _T("����"))
			{
				g_mapReportStat[m_Report.m_Data.items[i].szUniteDesc].nignoreTotal+=1;
			}
		}else
		{
			_tagReportStat Set;
			Set.nTotal=1;
			Set.nComplateTotal=0;
			Set.nignoreTotal=0;
			Set.nManaualTotal=0;

			if (m_Report.m_Data.items[i].szTestState == _T("���ͨ��"))
			{
				Set.nComplateTotal=1;
			}else if (m_Report.m_Data.items[i].szTestState == _T("��Ҫ�˹�����"))
			{
				Set.nManaualTotal=1;

			}else if (m_Report.m_Data.items[i].szTestState == _T("����"))
			{
				Set.nignoreTotal=1;
			}

			Set.vec.push_back(m_Report.m_Data.items[i]);
			g_mapReportStat[m_Report.m_Data.items[i].szUniteDesc]=Set;
		}
	}

	OutputReport.Overall.nDescTotal=g_mapReportStat.size();

	TCHAR szOverall[512];
	tstring szOverall1;
	sprintf_s_t(szOverall,512,_T("�ܼ�������:%d\n�ܼ�����������:%d\n�ܼ���ȷ��������:%d\n")
		_T("��Ҫ�˹�����������:%d\n����������:%d\n"),OutputReport.Overall.nErrorTotal,OutputReport.Overall.nDescTotal,
		OutputReport.Overall.nComplateTotal,OutputReport.Overall.nManaualTotal,
		OutputReport.Overall.nIgnoreTotal);

	CXmlString::GetXMLStringFromtstring(szOverall1,tstring(szOverall));
	if(MakeExeclRowData(nRow,1,10,GetStringTotalLine(tstring(szOverall)),tstring(_T("s69")),szOverall1,szExeclTemp))
	{
		szExecl+=szExeclTemp;
		nRow+=GetStringTotalLine(tstring(szOverall))+3;
	}


	//���屨��

	//return;

	map<tstring, _tagReportStat, less<tstring> >::iterator itPos=g_mapReportStat.begin();
	unsigned int i=0;
	

	tstring szSummary,szSummary1;
	for(;itPos!=g_mapReportStat.end();itPos++)
	{
		i++;
		TCHAR szTotal[16];
		TCHAR szComplateTotal[16];
		TCHAR szManaualTotal[16];
		TCHAR szignoreTotal[16];
		TCHAR szi[16];

		itoa_t(itPos->second.nTotal,szTotal,10);
		itoa_t(itPos->second.nComplateTotal,szComplateTotal,10);
		itoa_t(itPos->second.nManaualTotal,szManaualTotal,10);
		itoa_t(itPos->second.nignoreTotal,szignoreTotal,10);
		itoa_t(i,szi,10);

		szSummary=_T("��(")+tstring(szi)+_T(")��\n��������: ")+itPos->first+_T("\n�ܼ�����: ")+szTotal+_T("\n����ܼ�����: ")+szComplateTotal
			+_T("\n��Ҫ�˹������ܼ�����: ")+szManaualTotal+_T("\n�����ܼ�����: ")+szignoreTotal+_T("\n")
			+_T("��������: ")+itPos->second.vec[0].szErrorType+_T("\n����ȼ�: ")+itPos->second.vec[0].szErrorWarning+_T("\n")
			+_T("ͳһ�淶���: ")+itPos->second.vec[0].szUniteStandardErrorNum+_T("\n");

		CXmlString::GetXMLStringFromtstring(szSummary1,szSummary);
		if(MakeExeclRowData(nRow,1,10,GetStringTotalLine(szSummary),tstring(_T("s70")),szSummary1,szExeclTemp))
		{
			szExecl+=szExeclTemp;
		}
		nRow+=GetStringTotalLine(szSummary)+3;
	}

	

	itPos=g_mapReportStat.begin();
	i=0;
	tstring szDetailed,szDetailed1;
	for(;itPos!=g_mapReportStat.end();itPos++)
	{
		i++;
		TCHAR szTotal[16];
		TCHAR szComplateTotal[16];
		TCHAR szManaualTotal[16];
		TCHAR szignoreTotal[16];
		TCHAR szi[16];

		itoa_t(itPos->second.nTotal,szTotal,10);
		itoa_t(itPos->second.nComplateTotal,szComplateTotal,10);
		itoa_t(itPos->second.nManaualTotal,szManaualTotal,10);
		itoa_t(itPos->second.nignoreTotal,szignoreTotal,10);
		itoa_t(i,szi,10);

		
		szDetailed=_T("��(")+tstring(szi)+_T(")��\n��������: ")+itPos->first+_T("\n�ܼ�����: ")+szTotal+_T("\n����ܼ�����: ")+szComplateTotal
			+_T("\n��Ҫ�˹������ܼ�����: ")+szManaualTotal+_T("\n�����ܼ�����: ")+szignoreTotal+_T("\n")
			+_T("��������: ")+itPos->second.vec[0].szErrorType+_T("\n����ȼ�: ")+itPos->second.vec[0].szErrorWarning+_T("\n")+
			_T("ͳһ�淶���: ")+itPos->second.vec[0].szUniteStandardErrorNum+_T("\n")+
			_T("��ϸ����: \n")+_T("[ͳһ�淶����: ]\n")+itPos->second.vec[0].szUniteDesc+_T("\n[ͳһ�淶��ϸ����������:]\n")+itPos->second.vec[0].szUniteSuggest+
			_T("\n[�������淶����: ]\n")+itPos->second.vec[0].szThirdDesc+_T("\n[�������淶��ϸ����������: ]\n")+itPos->second.vec[0].szThirdSuggest+_T("\n\n");
		for(unsigned int i=0;i<itPos->second.vec.size();i++)
		{
			szDetailed+=_T("����״̬: ")+itPos->second.vec[i].szTestState+
				_T("  �������淶���: ")+itPos->second.vec[i].szThirdStandardErrorNum+
				_T("  ����λ��: ")+itPos->second.vec[i].szErrorCodePosition+
				_T("\n��������:\t")+itPos->second.vec[i].szErrorCodeContent+_T("\n\n");
			if(i>150)
			{
				break;
			}
		}
		//_tagReportOutput_Detailed Detailed;
		//Detailed.szDetailed=szDetailed;
		//OutputReport.Detailed.push_back(Detailed);
		CXmlString::GetXMLStringFromtstring(szDetailed1,szDetailed);
		if(MakeExeclRowData(nRow,1,10,GetStringTotalLine(szDetailed),tstring(_T("s70")),szDetailed1,szExeclTemp))
		{
			szExecl+=szExeclTemp;
			nRow+=GetStringTotalLine(szDetailed)+3;
		}
		
	}

	ValMap[tstring(_T("####{0000-1111-2222-3333-4444}####"))]=szExecl;

	CTemplateTool::MakeFileByTemplateFile(ValMap,
		tstring(theApp.GetAppPath().GetBuffer(0))+tstring(_T("Execlģ���ļ�")),tstring(theApp.GetAppPath().GetBuffer(0))+tstring(_T("���屨��.xml")));

}

void CTestUserReportComplateView::OnBnClickedMakeSummary()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	MakeSummary(m_pShareData->m_Report);
}

void CTestUserReportComplateView::OnBnClickedSendpost()
{
	CNewPost NewPost;
	NewPost.m_szTitle=_T("��������");
	if (NewPost.DoModal() != IDOK){
		return;
	}

	REPORT_ITEM post;
	post.szUniteDesc = NewPost.m_sSubject;
	post.szUniteSuggest = NewPost.m_sContent;
	post.szModule = NewPost.m_sPosition;
	tstring szTestItemSource=_T("�˹����-")+theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetLoginName();
	post.szTestItemSource = szTestItemSource;
	post.szTestState = _T("���ͨ��");
	post.szCreateTime = post.szLastEditTime = theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetCurTime();
	m_pShareData->m_Report.m_Data.items.push_back(post);

	//add to grid
	InitialListCtrlData();
}

void CTestUserReportComplateView::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_OBJECT_LOCK_MENU, point.x, point.y, this, TRUE);
	return;
}

void CTestUserReportComplateView::OnBnClickedComplateReport()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_pShareData->m_ProjectState.m_Data.szProjectState=PROJECT_STATE_TEST_OVER;
	m_pShareData->UpdataReportObject();
	m_pShareData->UpdataProjectState();
	((CMainFrame *)AfxGetApp()->GetMainWnd())->WriteStringToOutputWnd(_T("======== ��������� ========\r\n"), SB_BOTTOM);
	OnReleaseObjectLock();
}

void CTestUserReportComplateView::OnBnClickedEditreport()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CNewPost EditPost;
	POSITION pos=m_lstReport.GetFirstSelectedItemPosition();
	if  (pos   ==   NULL)   
	{
		AfxMessageBox(_T("��ѡ��Ҫ�༭��Ԫ��"));
		return;
	}
	int   nItem   =   m_lstReport.GetNextSelectedItem(pos);  
	int nIndex = atol_t(m_lstReport.GetItemText(nItem, 7).GetBuffer(0));
	
	if(strstr_t(m_pShareData->m_Report.m_Data.items[nIndex].szTestItemSource.c_str(),_T("�˹����-"))&&
		strstr_t(m_pShareData->m_Report.m_Data.items[nIndex].szTestItemSource.c_str(),
		theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetLoginName().c_str())
		)
	{
		EditPost.m_sSubject=m_pShareData->m_Report.m_Data.items[nIndex].szUniteDesc.c_str();
		EditPost.m_sContent=m_pShareData->m_Report.m_Data.items[nIndex].szUniteSuggest.c_str();
		EditPost.m_sPosition=m_pShareData->m_Report.m_Data.items[nIndex].szModule.c_str();
		//EditPost.SetWindowText(_T("�༭����"));
		EditPost.m_szTitle=_T("�༭����");
		if (EditPost.DoModal() != IDOK){
			return;
		}

		REPORT_ITEM post;
		m_pShareData->m_Report.m_Data.items[nIndex].szUniteDesc = EditPost.m_sSubject;
		m_pShareData->m_Report.m_Data.items[nIndex].szUniteSuggest = EditPost.m_sContent;
		m_pShareData->m_Report.m_Data.items[nIndex].szModule = EditPost.m_sPosition;
		tstring szTestItemSource=_T("�˹����-")+theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetLoginName();
		m_pShareData->m_Report.m_Data.items[nIndex].szTestItemSource = szTestItemSource;
		m_pShareData->m_Report.m_Data.items[nIndex].szTestState = _T("���ͨ��");
		m_pShareData->m_Report.m_Data.items[nIndex].szLastEditTime = post.szLastEditTime = theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetCurTime();

		m_lstReport.SetItemText(nItem,1,EditPost.m_sSubject);
		m_lstReport.SetItemText(nItem,2,EditPost.m_sPosition);
		m_lstReport.SetItemText(nItem,9,szTestItemSource.c_str());

		//m_pShareData->m_Report.m_Data.items.push_back(post);
	}else
	{
		AfxMessageBox(_T("�Ƿ��༭,ֻ����༭�Լ��ύ������"));
	}
	
}

void CTestUserReportComplateView::OnBnClickedDelreport()
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
			//m_pShareData->m_Report.m_Data.items.erase(itPos);
			m_pShareData->m_Report.m_Data.items[nIndex].szTestState=_T("ɾ��");
			

			//   you   could   do   your   own   processing   on   nItem   here   
		}   
		InitialListCtrlData();
	}  
}
