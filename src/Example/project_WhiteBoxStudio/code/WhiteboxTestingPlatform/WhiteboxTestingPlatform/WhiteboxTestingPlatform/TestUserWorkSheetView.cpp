// TestUserWorkSheetView.cpp : 实现文件
//

#include "stdafx.h"
#include "WhiteboxTestingPlatform.h"
#include "TestUserWorkSheetView.h"


// CTestUserWorkSheetView

IMPLEMENT_DYNCREATE(CTestUserWorkSheetView, CFormView)

CTestUserWorkSheetView::CTestUserWorkSheetView()
	: CFormView(CTestUserWorkSheetView::IDD)
{

}

CTestUserWorkSheetView::~CTestUserWorkSheetView()
{
}

void CTestUserWorkSheetView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CHECKRANGE, m_cmbCheckRange);
	DDX_Control(pDX, IDC_DATE_APPLY, m_dateApply);
	DDX_Control(pDX, IDC_DATE_CHECK, m_dateCheck);
	DDX_Control(pDX, IDC_COMBO_APPLY, m_cmbApply);
}

BEGIN_MESSAGE_MAP(CTestUserWorkSheetView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CTestUserWorkSheetView::OnBnClickedButtonSave)
END_MESSAGE_MAP()


// CTestUserWorkSheetView 诊断

#ifdef _DEBUG
void CTestUserWorkSheetView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CTestUserWorkSheetView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CTestUserWorkSheetView 消息处理程序

void CTestUserWorkSheetView::OnInitialUpdate()
{
	__super::OnInitialUpdate();

	m_pShareData = (CProjectSharedData *)(((CChildFrame *)GetParentFrame())->m_ProjectIndex.pSharedObject);
	((CChildFrame *)GetParentFrame())->m_ProjectIndex.pViewInterface = this;
	m_pShareData->init();

	InitDevList();
	InitComboBoxData();
	GetWorkSheetData();
}

void CTestUserWorkSheetView::InitComboBoxData()
{
	m_cmbCheckRange.AddString(_T("代码规范检查"));
	m_cmbCheckRange.AddString(_T("用例代码覆盖度检查"));
	m_cmbCheckRange.AddString(_T("模块内功能逻辑性错误检查"));
	m_cmbCheckRange.AddString(_T("模块内性能优化检查"));
	m_cmbCheckRange.AddString(_T("代码在整个系统层面问题分析检查"));
	m_cmbCheckRange.AddString(_T("代码在整个系统层面性能优化检查"));
	m_cmbCheckRange.SetCurSel(0);
}

void CTestUserWorkSheetView::SetCtrlDate(CDateTimeCtrl &ctrlDate, const CString &sDate)
{
	if (sDate.GetLength() < 10){
		return;
	}

	CString sApplyDate = sDate;
	CString year, month, day;
	year = sApplyDate.Left(4);
	sApplyDate = sApplyDate.Right(sApplyDate.GetLength()-sApplyDate.Find(_T("-"))-1);
	month = sApplyDate.Left (sApplyDate.Find (_T("-")));
	day = sApplyDate.Right(sApplyDate.GetLength()-sApplyDate.Find(_T("-"))-1);

	int y = atoi_t(year.GetBuffer(0));
	int m = atoi_t(month.GetBuffer(0));
	int d = atoi_t(day.GetBuffer(0));
	CTime timeApplyDate(y, m, d, 0, 0, 0);
	ctrlDate.SetTime(&timeApplyDate);	
}

BOOL CTestUserWorkSheetView::InitDevList()
{
	_tagProjectOwnUser ProjectUserMap;
	tstring sProjectName = m_pShareData->GetProjectName().c_str() + strlen_t(_T("Project_"));
	if (!theApp.m_WorkSpaceWndManger.m_UserDataModel.GetProjectOwnUser(sProjectName, ProjectUserMap)){
		return FALSE;
	}

	map<tstring,_tagProjectOwnUserSet,less<tstring> >::iterator itPos = ProjectUserMap.OwnUserMap.begin();
	for(; itPos!=ProjectUserMap.OwnUserMap.end(); itPos++)
	{
		_tagProjectOwnUserSet ProjectOwnUserSet = itPos->second;
		if (ProjectOwnUserSet.szUserType != USER_TYPE_DEVELOP){
			continue;
		}

		m_cmbApply.AddString(ProjectOwnUserSet.szUserName.c_str());
	}
	return TRUE;
}

void CTestUserWorkSheetView::GetWorkSheetData()
{
	((CWnd *)GetDlgItem(IDC_EDIT_PROJECTNO))->SetWindowText(m_pShareData->m_WorkSheet.szProjectNo.c_str());
	((CWnd *)GetDlgItem(IDC_EDIT_WORKNO))->SetWindowText(m_pShareData->m_WorkSheet.szWorksheetNo.c_str());
	((CWnd *)GetDlgItem(IDC_EDIT_MODULENO))->SetWindowText(m_pShareData->m_WorkSheet.szModuleNo.c_str());
	//((CWnd *)GetDlgItem(IDC_EDIT_APPLY))->SetWindowText(m_pShareData->m_WorkSheet.szApplyMan.c_str());
	//((CWnd *)GetDlgItem(IDC_EDIT_CHECKMAN_LIST))->SetWindowText(m_pShareData->m_WorkSheet.szResponsiblePerson.c_str());
	((CWnd *)GetDlgItem(IDC_EDIT_PREWORKNO))->SetWindowText(m_pShareData->m_WorkSheet.szPreWorksheetNo.c_str());
	((CWnd *)GetDlgItem(IDC_EDIT_SVNPATH))->SetWindowText(m_pShareData->m_WorkSheet.szSVNCodePath.c_str());
	((CWnd *)GetDlgItem(IDC_EDIT_SOURCELIST))->SetWindowText(m_pShareData->m_WorkSheet.szSourceList.c_str());

	m_cmbApply.SetCurSel(0);
	m_cmbApply.SelectString(0, m_pShareData->m_WorkSheet.szApplyMan.c_str());

	m_cmbCheckRange.SelectString(0, m_pShareData->m_WorkSheet.szCheckRange.c_str());

	SetCtrlDate(m_dateApply, m_pShareData->m_WorkSheet.szApplyDate.c_str());

	CheckRadioButton(IDC_RADIO_CHECKTYPE_ADD, IDC_RADIO_CHECKTYPE_ALL, m_pShareData->m_WorkSheet.nCheckType); 

	((CWnd *)GetDlgItem(IDC_EDIT_SUGGEST))->SetWindowText(m_pShareData->m_WorkSheet.szSuggest.c_str());
	((CWnd *)GetDlgItem(IDC_EDIT_CHECKRESULT_DES))->SetWindowText(m_pShareData->m_WorkSheet.szFailReason.c_str());
	((CWnd *)GetDlgItem(IDC_EDIT_CHECKMAN))->SetWindowText(m_pShareData->m_WorkSheet.szSignatureMan.c_str());

	CheckRadioButton(IDC_RADIO_CHECKRESULT_SUCC, IDC_RADIO_CHECKRESULT_FAIL, m_pShareData->m_WorkSheet.nCheckResult); 
	SetCtrlDate(m_dateCheck, m_pShareData->m_WorkSheet.szSignatureDate.c_str());
}

void CTestUserWorkSheetView::OnBnClickedButtonSave()
{
	CString sText;
	((CWnd *)GetDlgItem(IDC_EDIT_PROJECTNO))->GetWindowText(sText);
	m_pShareData->m_WorkSheet.szProjectNo = (LPCTSTR)sText;
	((CWnd *)GetDlgItem(IDC_EDIT_WORKNO))->GetWindowText(sText);
	m_pShareData->m_WorkSheet.szWorksheetNo = (LPCTSTR)sText;
	((CWnd *)GetDlgItem(IDC_EDIT_MODULENO))->GetWindowText(sText);
	m_pShareData->m_WorkSheet.szModuleNo = (LPCTSTR)sText;
	m_cmbApply.GetWindowText(sText);
	m_pShareData->m_WorkSheet.szApplyMan = (LPCTSTR)sText;
	//((CWnd *)GetDlgItem(IDC_EDIT_CHECKMAN_LIST))->GetWindowText(sText);
	//m_pShareData->m_WorkSheet.szResponsiblePerson = (LPCTSTR)sText;
	((CWnd *)GetDlgItem(IDC_EDIT_PREWORKNO))->GetWindowText(sText);
	m_pShareData->m_WorkSheet.szPreWorksheetNo = (LPCTSTR)sText;
	((CWnd *)GetDlgItem(IDC_EDIT_SVNPATH))->GetWindowText(sText);
	m_pShareData->m_WorkSheet.szSVNCodePath = (LPCTSTR)sText;
	((CWnd *)GetDlgItem(IDC_EDIT_SOURCELIST))->GetWindowText(sText);
	m_pShareData->m_WorkSheet.szSourceList = (LPCTSTR)sText;

	m_cmbCheckRange.GetWindowText(sText);
	m_pShareData->m_WorkSheet.szCheckRange = (LPCTSTR)sText;

	m_pShareData->m_WorkSheet.nCheckType = GetCheckedRadioButton(IDC_RADIO_CHECKTYPE_ADD, IDC_RADIO_CHECKTYPE_ALL);

	CTime timeApply;
	DWORD dwResult = m_dateApply.GetTime(timeApply);
	if (dwResult == GDT_VALID){
		m_pShareData->m_WorkSheet.szApplyDate = timeApply.Format(_T("%Y-%m-%d"));	
	}

	((CWnd *)GetDlgItem(IDC_EDIT_SUGGEST))->GetWindowText(sText);
	m_pShareData->m_WorkSheet.szSuggest = (LPCTSTR)sText;
	((CWnd *)GetDlgItem(IDC_EDIT_CHECKRESULT_DES))->GetWindowText(sText);
	m_pShareData->m_WorkSheet.szFailReason = (LPCTSTR)sText;
	((CWnd *)GetDlgItem(IDC_EDIT_CHECKMAN))->GetWindowText(sText);
	m_pShareData->m_WorkSheet.szSignatureMan = (LPCTSTR)sText;

	m_pShareData->m_WorkSheet.nCheckResult = GetCheckedRadioButton(IDC_RADIO_CHECKRESULT_SUCC, IDC_RADIO_CHECKRESULT_FAIL);

	CTime timeCheck;
	dwResult = m_dateCheck.GetTime(timeCheck);
	if (dwResult == GDT_VALID){
		m_pShareData->m_WorkSheet.szSignatureDate = timeCheck.Format(_T("%Y-%m-%d"));	
	}

	m_pShareData->UpdataWorkSheetObject();
}
