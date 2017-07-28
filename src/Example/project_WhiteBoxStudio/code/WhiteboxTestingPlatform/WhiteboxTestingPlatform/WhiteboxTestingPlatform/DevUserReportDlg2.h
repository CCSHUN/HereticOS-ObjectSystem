#pragma once


// CDevUserReportDlg2 对话框
#include "QuestionResponse.h"

class CDevUserReportDlg2 : public CDialog,CQuestionResponseReversedCall
{
	DECLARE_DYNAMIC(CDevUserReportDlg2)

public:
	CDevUserReportDlg2(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDevUserReportDlg2();
	CQuestionResponse m_QuestionResponseView;
	void UpdataUi();
	void OnHtmlUiPostEdit(CString & szHtmlObject);
	BOOL GetQuestionResponseDataByTemplate(IN __int64 nPostTime,IN tstring & szUserName,IN tstring & szMsgBaboy,OUT tstring & szUiCode);

	BOOL PreTranslateMessage(MSG* pMsg);
	void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	void OnShowWindow(BOOL bShow, UINT nStatus);

	BOOL m_bNeedUpdata;
	

// 对话框数据
	enum { IDD = IDD_DEVUSER_REPORT_VIEW_2 };

protected:
	tstring m_szQuestionResponseTemplate;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboDevstate();
	afx_msg void OnEnChangeEditFeedbackAdd();
	afx_msg void OnEnChangeEditFeedback();
	afx_msg void OnBnClickedAdd();

public:
	CProjectSharedData *m_pShareData;
	UINT m_iDataIndex;
	tstring m_szUiName;
	
};
