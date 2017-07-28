// DevUserReportDlg1.cpp : 实现文件
//

#include "stdafx.h"
#include "WhiteboxTestingPlatform.h"
#include "BaseReportInfoDlg.h"


// CDevUserReportDlg1 对话框

IMPLEMENT_DYNAMIC(CBaseReportInfoDlg, CDialog)

CBaseReportInfoDlg::CBaseReportInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBaseReportInfoDlg::IDD, pParent)
{

}

CBaseReportInfoDlg::~CBaseReportInfoDlg()
{
}

BOOL CBaseReportInfoDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN ||pMsg->wParam == VK_ESCAPE))     
	{     
		return ::TranslateMessage(pMsg);     
	}    

	return CDialog::PreTranslateMessage(pMsg);
}
void CBaseReportInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

void CBaseReportInfoDlg::UpdataUi()
{
	CWnd *pWnd = (CWnd *)GetDlgItem(IDC_ERROR_DESCRIPTION);
	pWnd->SetWindowText(m_pShareData->m_Report.m_Data.items[m_iDataIndex].szErrorCodeContent.c_str());

	pWnd = (CWnd *)GetDlgItem(IDC_FILENAME);
	pWnd->SetWindowText(m_pShareData->m_Report.m_Data.items[m_iDataIndex].szModule.c_str());

	pWnd = (CWnd *)GetDlgItem(IDC_LINE_NUM);
	pWnd->SetWindowText(m_pShareData->m_Report.m_Data.items[m_iDataIndex].szErrorCodePosition.c_str());

	/*pWnd = (CWnd *)GetDlgItem(IDC_EDIT_SUGGEST);
	pWnd->SetWindowText(m_lstReport.GetItemText(nItem, 4));*/

	/*pWnd = (CWnd *)GetDlgItem(IDC_ERROR_NUM_UNITE);
	pWnd->SetWindowText(m_lstReport.GetItemText(nItem, 5));

	pWnd = (CWnd *)GetDlgItem(IDC_ERROR_NUM_THIRD);
	pWnd->SetWindowText(m_lstReport.GetItemText(nItem, 6));*/

	/*pWnd = (CWnd *)GetDlgItem(IDC_ERROR_TYPE);
	pWnd->SetWindowText(m_pShareData->m_Report.m_Data.items[m_iDataIndex].szErrorType.c_str());
	pWnd = (CWnd *)GetDlgItem(IDC_ERROR_CLASS);
	pWnd->SetWindowText(m_pShareData->m_Report.m_Data.items[m_iDataIndex].szErrorWarning.c_str());
*/

	//如果有编辑好的描述建议，则设置为编辑好的描述建议
	if(m_pShareData->m_Report.m_Data.items[m_iDataIndex].szDesc.length())
	{
		pWnd = (CWnd *)GetDlgItem(IDC_DESCRIPTION);
		pWnd->SetWindowText(m_pShareData->m_Report.m_Data.items[m_iDataIndex].szDesc.c_str());
	}else
	{
		pWnd = (CWnd *)GetDlgItem(IDC_DESCRIPTION);
		pWnd->SetWindowText(m_pShareData->m_Report.m_Data.items[m_iDataIndex].szUniteDesc.c_str());
	}

	if(m_pShareData->m_Report.m_Data.items[m_iDataIndex].szSuggest.length())
	{
		pWnd = (CWnd *)GetDlgItem(IDC_EDIT_SUGGEST);
		pWnd->SetWindowText(m_pShareData->m_Report.m_Data.items[m_iDataIndex].szSuggest.c_str());
	}else
	{
		pWnd = (CWnd *)GetDlgItem(IDC_EDIT_SUGGEST);
		tstring szSuggest=_T("[统一规范描述]\r\n")+m_pShareData->m_Report.m_Data.items[m_iDataIndex].szUniteDesc+_T("\r\n\r\n");
		szSuggest+=_T("[统一规范详细描述与建议]\r\n")+m_pShareData->m_Report.m_Data.items[m_iDataIndex].szUniteSuggest+_T("\r\n\r\n");
		szSuggest+=_T("[第三方规范描述]\r\n")+m_pShareData->m_Report.m_Data.items[m_iDataIndex].szThirdDesc+_T("\r\n\r\n");
		szSuggest+=_T("[第三方规范详细描述与建议]\r\n")+m_pShareData->m_Report.m_Data.items[m_iDataIndex].szThirdSuggest+_T("\r\n\r\n");

		pWnd->SetWindowText(szSuggest.c_str());
	}
}
BOOL CBaseReportInfoDlg::OnInitDialog()
{
	BOOL bRet=CDialog::OnInitDialog();
	return bRet;
}

BEGIN_MESSAGE_MAP(CBaseReportInfoDlg, CDialog)
	ON_EN_CHANGE(IDC_FILENAME, &CBaseReportInfoDlg::OnEnChangeFilename)
END_MESSAGE_MAP()


// CDevUserReportDlg1 消息处理程序

void CBaseReportInfoDlg::OnEnChangeFilename()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
