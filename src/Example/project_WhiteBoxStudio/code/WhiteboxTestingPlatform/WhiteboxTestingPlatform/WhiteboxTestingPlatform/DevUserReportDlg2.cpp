// DevUserReportDlg2.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WhiteboxTestingPlatform.h"
#include "DevUserReportDlg2.h"
#include "TemplateTool.h"

// CDevUserReportDlg2 �Ի���

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
	sprintf_s_t(szTime,32,_T("����ʱ��:��%d-%02d-%02d %02d:%02d:%02d"),
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
		AfxMessageBox(_T("����ѡ�������¼"));
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
		AfxMessageBox(_T("��������༭Ȩ��"));
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


// CDevUserReportDlg2 ��Ϣ�������

void CDevUserReportDlg2::OnCbnSelchangeComboDevstate()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CDevUserReportDlg2::OnEnChangeEditFeedbackAdd()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

void CDevUserReportDlg2::OnEnChangeEditFeedback()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

void CDevUserReportDlg2::OnBnClickedAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
