// TestUserStandardThirdNewDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "WhiteboxTestingPlatform.h"
#include "TestUserStandardThirdNewDlg.h"


// CTestUserStandardThirdNewDlg 对话框

IMPLEMENT_DYNAMIC(CTestUserStandardThirdNewDlg, CDialog)

CTestUserStandardThirdNewDlg::CTestUserStandardThirdNewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestUserStandardThirdNewDlg::IDD, pParent)
	, m_ToolType(_T(""))
{

}
BOOL CTestUserStandardThirdNewDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN ||pMsg->wParam == VK_ESCAPE))     
	{     
		return ::TranslateMessage(pMsg);     
	}    

	return CDialog::PreTranslateMessage(pMsg);
}

CTestUserStandardThirdNewDlg::~CTestUserStandardThirdNewDlg()
{
}

void CTestUserStandardThirdNewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_ERROR_NOCHECK, m_is_dealwith);
	DDX_Check(pDX, IDC_ERROR_MANUAL, m_is_manual_check);
	DDX_Text(pDX, IDC_ERROR_NUM, m_szThirdStandardErrorNum);
	DDX_Text(pDX, IDC_ERROR_CHECKSUG, m_szManual_check_MethodSpecify);
	//DDX_Text(pDX, IDC_ERROR_UNITENUM, m_szUniteStandardErrorNum);
	//DDX_Text(pDX, IDC_ERROR_TOOLTYPE, m_ToolType);
	DDX_Text(pDX, IDC_ERROR_DESC, m_szThirdStandardErrorDesc);
	DDX_Text(pDX, IDC_ERROR_SUG, m_szErrorSuggest);
	DDX_CBString(pDX, IDC_COMBO_TOOLTYPE, m_ToolType);
	DDX_Control(pDX, IDC_COMBO_TOOLTYPE, m_ToolTypeCtl);
}


BEGIN_MESSAGE_MAP(CTestUserStandardThirdNewDlg, CDialog)
	ON_BN_CLICKED(IDC_NEW, &CTestUserStandardThirdNewDlg::OnBnClickedNew)
	ON_BN_CLICKED(IDC_CANCEL, &CTestUserStandardThirdNewDlg::OnBnClickedCancel)

END_MESSAGE_MAP()


void CTestUserStandardThirdNewDlg::UpDataBing(BOOL bToSecond)
{
	if(bToSecond)
	{
		UpdateData(TRUE);
		m_CurDataSet.is_dealwith=m_is_dealwith;
		m_CurDataSet.is_manual_check=m_is_manual_check;
		m_CurDataSet.szManual_check_MethodSpecify=m_szManual_check_MethodSpecify;
		m_CurDataSet.szThirdStandardErrorDesc=m_szThirdStandardErrorDesc;
		m_CurDataSet.szThirdStandardErrorNum=m_szThirdStandardErrorNum;
		m_CurDataSet.ToolType=m_ToolType;
		m_CurDataSet.szUniteStandardErrorNum=m_szUniteStandardErrorNum;
		m_CurDataSet.szErrorSuggest=m_szErrorSuggest;
	}else
	{
		m_is_dealwith=m_CurDataSet.is_dealwith;
		m_is_manual_check=m_CurDataSet.is_manual_check;
		m_szManual_check_MethodSpecify=m_CurDataSet.szManual_check_MethodSpecify.c_str();
		m_szThirdStandardErrorDesc=m_CurDataSet.szThirdStandardErrorDesc.c_str();
		m_szThirdStandardErrorNum=m_CurDataSet.szThirdStandardErrorNum.c_str();
		m_ToolType=m_CurDataSet.ToolType.c_str();
		m_szUniteStandardErrorNum=m_CurDataSet.szUniteStandardErrorNum.c_str();
		m_szErrorSuggest=m_CurDataSet.szErrorSuggest.c_str();
		UpdateData(FALSE);
	}
}

BOOL CTestUserStandardThirdNewDlg::OnInitDialog()
{
	BOOL bRet=CDialog::OnInitDialog();
	//UpDataBing(FALSE);
	m_ToolTypeCtl.AddString(_T("C++Test"));
	m_ToolTypeCtl.AddString(_T("PC-Lint"));
	m_ToolTypeCtl.SelectString(0,_T("PC-Lint"));
	

	return bRet;
}

// CTestUserStandardThirdNewDlg 消息处理程序

void CTestUserStandardThirdNewDlg::OnBnClickedNew()
{
	// TODO: 在此添加控件通知处理程序代码
	UpDataBing(TRUE);
	if(m_pShareData->m_ThirdStandardLib.m_Data.libmap.find(m_CurDataSet.szThirdStandardErrorNum)==m_pShareData->m_ThirdStandardLib.m_Data.libmap.end())
	{
		m_CurDataSet.szUniteStandardErrorNum=_T("未关联");
		m_pShareData->m_ThirdStandardLib.m_Data.libmap[m_CurDataSet.szThirdStandardErrorNum]=m_CurDataSet;
		m_pShareData->m_bThirdLibWrited=TRUE;
		CDialog::OnOK();
	}else
	{
		AfxMessageBox(_T("新建的标准已经存在请重新输入"));
	}
}

void CTestUserStandardThirdNewDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}
