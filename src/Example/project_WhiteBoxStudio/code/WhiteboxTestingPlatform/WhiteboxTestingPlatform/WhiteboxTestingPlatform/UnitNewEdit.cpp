// UnitNewEdit.cpp : 实现文件
//

#include "stdafx.h"
#include "WhiteboxTestingPlatform.h"
#include "UnitNewEdit.h"


// CUnitNewEdit 对话框

IMPLEMENT_DYNAMIC(CUnitNewEdit, CDialog)

CUnitNewEdit::CUnitNewEdit(CWnd* pParent /*=NULL*/)
	: CDialog(CUnitNewEdit::IDD, pParent)
	, szPrjName(_T(""))
	, szSysName(_T(""))
	, szModuleName(_T(""))
	, szTesterName(_T(""))
	, szJudgeName(_T(""))
	, szJudgeDate(_T(""))
	, szTestDate(_T(""))
	, szSug(_T(""))
	, fIVT(0)
	, fINVT(0)
	, fBT(0)
	, fRCT(0)
	, fTCCDT(0)
	, nIVT(0)
	, nINVT(0)
	, nBT(0)
	, nRCT(0)
	, nTCCDT(0)
{

}

CUnitNewEdit::~CUnitNewEdit()
{
}

void CUnitNewEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PRJNAME, szPrjName);
	DDX_Text(pDX, IDC_EDIT_SYSNAME, szSysName);
	DDX_Text(pDX, IDC_EDIT_MODULENAME, szModuleName);
	DDX_Text(pDX, IDC_EDIT_TESTER, szTesterName);
	DDX_Text(pDX, IDC_EDIT_JUDGE, szJudgeName);
	DDX_Text(pDX, IDC_EDIT_SUG, szSug);
	DDX_Text(pDX, IDC_EDIT_IVT, fIVT);
	DDX_Text(pDX, IDC_EDIT_INVT, fINVT);
	DDX_Text(pDX, IDC_EDIT_BT, fBT);
	DDX_Text(pDX, IDC_EDIT_RCT, fRCT);
	DDX_Text(pDX, IDC_EDIT_TCCDT, fTCCDT);
	DDX_Text(pDX, IDC_EDIT_IVT2, nIVT);
	DDX_Text(pDX, IDC_EDIT_INVT2, nINVT);
	DDX_Text(pDX, IDC_EDIT_BT2, nBT);
	DDX_Text(pDX, IDC_EDIT_RCT2, nRCT);
	DDX_Text(pDX, IDC_EDIT_TCCDT2, nTCCDT);
	DDX_DateTimeCtrl(pDX, IDC_DATE_TESTDATE, szTestDate);
	DDX_DateTimeCtrl(pDX, IDC_DATE_JUDGEDATE, szJudgeDate);
}


BEGIN_MESSAGE_MAP(CUnitNewEdit, CDialog)
	ON_BN_CLICKED(IDOK, &CUnitNewEdit::OnBnClickedOk)
END_MESSAGE_MAP()


// CUnitNewEdit 消息处理程序

void CUnitNewEdit::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	OnOK();
}
