// DevUserReportDlg1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WhiteboxTestingPlatform.h"
#include "BaseReportInfoDlg.h"


// CDevUserReportDlg1 �Ի���

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

	//����б༭�õ��������飬������Ϊ�༭�õ���������
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
		tstring szSuggest=_T("[ͳһ�淶����]\r\n")+m_pShareData->m_Report.m_Data.items[m_iDataIndex].szUniteDesc+_T("\r\n\r\n");
		szSuggest+=_T("[ͳһ�淶��ϸ�����뽨��]\r\n")+m_pShareData->m_Report.m_Data.items[m_iDataIndex].szUniteSuggest+_T("\r\n\r\n");
		szSuggest+=_T("[�������淶����]\r\n")+m_pShareData->m_Report.m_Data.items[m_iDataIndex].szThirdDesc+_T("\r\n\r\n");
		szSuggest+=_T("[�������淶��ϸ�����뽨��]\r\n")+m_pShareData->m_Report.m_Data.items[m_iDataIndex].szThirdSuggest+_T("\r\n\r\n");

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


// CDevUserReportDlg1 ��Ϣ�������

void CBaseReportInfoDlg::OnEnChangeFilename()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
