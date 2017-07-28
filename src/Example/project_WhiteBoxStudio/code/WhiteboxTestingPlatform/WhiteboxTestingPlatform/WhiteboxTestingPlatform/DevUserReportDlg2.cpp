// DevUserReportDlg2.cpp : 实现文件
//

#include "stdafx.h"
#include "WhiteboxTestingPlatform.h"
#include "DevUserReportDlg2.h"
#include "TemplateTool.h"

// CDevUserReportDlg2 对话框

IMPLEMENT_DYNAMIC(CDevUserReportDlg2, CDialog)

CDevUserReportDlg2::CDevUserReportDlg2(CWnd* pParent /*=NULL*/)
	: CDialog(CDevUserReportDlg2::IDD, pParent)
{
	m_iDataIndex=-1;
	m_bNeedUpdata=FALSE;

}

void CDevUserReportDlg2::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	__super::OnActivate(nState,  pWndOther, bMinimized);

}

void CDevUserReportDlg2::OnShowWindow(BOOL bShow, UINT nStatus)
{
	m_bNeedUpdata=bShow;
	__super::OnShowWindow( bShow,  nStatus);
	UpdataUi();

}
BOOL CDevUserReportDlg2::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN ||pMsg->wParam == VK_ESCAPE))     
	{     
		return ::TranslateMessage(pMsg);     
	}    
	
	return CDialog::PreTranslateMessage(pMsg);
}


BOOL CDevUserReportDlg2::GetQuestionResponseDataByTemplate(IN __int64 nPostTime,IN tstring & szUserName,IN tstring & szMsgBaboy,OUT tstring & szUiCode)
{
	SYSTEMTIME tm;
	theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetCurTime(tm);
	TCHAR szTime[64];
	sprintf_s_t(szTime,32,_T("发表时间:　%d-%02d-%02d %02d:%02d:%02d"),
		tm.wYear,tm.wMonth,tm.wDay,
		tm.wHour,tm.wMinute,tm.wSecond);
	CTemplateTool::TemplateMap map;
	//tstring(_T("QuestResponseSetTemplate.txt"))
	map[tstring(_T("###PostTime###"))]=szTime;
	map[tstring(_T("###UserInfo###"))]=szUserName;
	map[tstring(_T("###PostData###"))]=szMsgBaboy;
	if(m_szQuestionResponseTemplate.size()==0)
	{
		CTemplateTool::FileToString(tstring(_T("ui\\template\\QuestResponseSetTemplate.txt")),m_szQuestionResponseTemplate);
	}
	tstring szTemplate=m_szQuestionResponseTemplate;
	return CTemplateTool::MakeStringByTemplateString(map, szTemplate, szUiCode);
}


void CDevUserReportDlg2::OnHtmlUiPostEdit(CString & szHtmlObject)
{
	//AfxMessageBox(szHtmlObject);
	if(m_iDataIndex==-1)
	{
		AfxMessageBox(_T("请先选定问题记录"));
		return;
	}
	if(IsCurUserAndUiLock(m_pShareData->m_Report,m_szUiName))
	{
		_tagReportLog LogSet;
		LogSet.szReport_log=szHtmlObject;
		LogSet.szUserName=theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetLoginName();
		LogSet.tmDate=CTime::GetCurrentTime().GetTime();
		m_pShareData->m_Report.m_Data.items[m_iDataIndex].szReport_log.push_back(LogSet);
		m_pShareData->m_Report.m_Data.items[m_iDataIndex].szLastEditTime=theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetCurTime();
		tstring szUiCode;
		GetQuestionResponseDataByTemplate(LogSet.tmDate,LogSet.szUserName,LogSet.szReport_log,szUiCode);
		m_QuestionResponseView.InsertHtmlObject(CString(szUiCode.c_str()));
	}else
	{
		AfxMessageBox(_T("请先申请编辑权限"));
		return;
	}
	
}

void CDevUserReportDlg2::UpdataUi()
{
	if(m_bNeedUpdata==FALSE) return;
	m_QuestionResponseView.EmptyHtmlObject();
	for(unsigned int i=0;i<m_pShareData->m_Report.m_Data.items[m_iDataIndex].szReport_log.size();i++)
	{
		tstring szMsg=m_pShareData->m_Report.m_Data.items[m_iDataIndex].szReport_log[i].szReport_log;
		//m_QuestionResponseView.InsertHtmlObject(CString(szMsg.c_str()));
		tstring szUiCode;
		GetQuestionResponseDataByTemplate(m_pShareData->m_Report.m_Data.items[m_iDataIndex].szReport_log[i].tmDate,
			m_pShareData->m_Report.m_Data.items[m_iDataIndex].szReport_log[i].szUserName,
			m_pShareData->m_Report.m_Data.items[m_iDataIndex].szReport_log[i].szReport_log,
			szUiCode);
		m_QuestionResponseView.InsertHtmlObject(CString(szUiCode.c_str()));
	}
}
BOOL CDevUserReportDlg2::OnInitDialog()
{
	BOOL bRet=CDialog::OnInitDialog();
	bRet=m_QuestionResponseView.CreateFromStatic(IDC_STATIC,this);
	m_QuestionResponseView.init(this);
	return bRet;
}
CDevUserReportDlg2::~CDevUserReportDlg2()
{
}

void CDevUserReportDlg2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDevUserReportDlg2, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_DEVSTATE, &CDevUserReportDlg2::OnCbnSelchangeComboDevstate)
	ON_EN_CHANGE(IDC_EDIT_FEEDBACK_ADD, &CDevUserReportDlg2::OnEnChangeEditFeedbackAdd)
	ON_EN_CHANGE(IDC_EDIT_FEEDBACK, &CDevUserReportDlg2::OnEnChangeEditFeedback)
	ON_BN_CLICKED(IDC_ADD, &CDevUserReportDlg2::OnBnClickedAdd)
	ON_WM_ACTIVATE()
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CDevUserReportDlg2 消息处理程序

void CDevUserReportDlg2::OnCbnSelchangeComboDevstate()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CDevUserReportDlg2::OnEnChangeEditFeedbackAdd()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CDevUserReportDlg2::OnEnChangeEditFeedback()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CDevUserReportDlg2::OnBnClickedAdd()
{
	// TODO: 在此添加控件通知处理程序代码
}
