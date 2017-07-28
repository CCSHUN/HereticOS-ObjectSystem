// TestUserStandardThirdEditDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "WhiteboxTestingPlatform.h"
#include "TestUserStandardThirdEditDlg.h"


// CTestUserStandardThirdEditDlg 对话框

IMPLEMENT_DYNAMIC(CTestUserStandardThirdEditDlg, CDialog)

CTestUserStandardThirdEditDlg::CTestUserStandardThirdEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestUserStandardThirdEditDlg::IDD, pParent)
{

}

CTestUserStandardThirdEditDlg::~CTestUserStandardThirdEditDlg()
{
}

BOOL CTestUserStandardThirdEditDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN ||pMsg->wParam == VK_ESCAPE))     
	{     
		return ::TranslateMessage(pMsg);     
	}    

	return CDialog::PreTranslateMessage(pMsg);
}
void CTestUserStandardThirdEditDlg::DoDataExchange(CDataExchange* pDX)
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


BEGIN_MESSAGE_MAP(CTestUserStandardThirdEditDlg, CDialog)
	ON_BN_CLICKED(IDC_CANCEL, &CTestUserStandardThirdEditDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_OK, &CTestUserStandardThirdEditDlg::OnBnClickedOk)
END_MESSAGE_MAP()

void CTestUserStandardThirdEditDlg::UpDataBing(BOOL bToSecond)
{
	if(bToSecond)
	{
		//界面到数据
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
		//数据到界面
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

// CTestUserStandardThirdEditDlg 消息处理程序


BOOL CTestUserStandardThirdEditDlg::OnInitDialog()
{
	BOOL bRet=CDialog::OnInitDialog();
	m_ToolTypeCtl.AddString(_T("C++Test"));
	m_ToolTypeCtl.AddString(_T("PC-Lint"));

	UpDataBing(FALSE);

	
	//m_ToolTypeCtl.SelectString(0,"PC-Lint");

	return bRet;
}

void CTestUserStandardThirdEditDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}

void CTestUserStandardThirdEditDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpDataBing(TRUE);
	m_pShareData->m_ThirdStandardLib.m_Data.libmap[m_CurDataSet.szThirdStandardErrorNum]=m_CurDataSet;
	m_pShareData->m_bThirdLibWrited=TRUE;
	CDialog::OnOK();
}
