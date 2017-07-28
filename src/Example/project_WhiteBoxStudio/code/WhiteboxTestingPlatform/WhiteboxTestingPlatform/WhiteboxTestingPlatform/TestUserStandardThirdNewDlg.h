#pragma once
#include "afxwin.h"


// CTestUserStandardThirdNewDlg 对话框

class CTestUserStandardThirdNewDlg : public CDialog
{
	DECLARE_DYNAMIC(CTestUserStandardThirdNewDlg)

public:
	CTestUserStandardThirdNewDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTestUserStandardThirdNewDlg();
	BOOL PreTranslateMessage(MSG* pMsg);

// 对话框数据
	enum { IDD = IDD_TESTUSER_STANDARD_THIRD_NEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedNew();
	afx_msg void OnBnClickedCancel();

	void UpDataBing(BOOL bToSecond);
	_tagThirdStandardSet m_CurDataSet;
	CStandardSharedData  * m_pShareData;
	CString m_szUniteStandardErrorNum;		//机械走读统一规范
	CString m_szThirdStandardErrorNum;		//PCLINT或者CTester的错误ID
	CString m_szThirdStandardErrorDesc;
	BOOL m_is_manual_check;					//是否需要人工检查
	CString m_szManual_check_MethodSpecify;	//人工复查标准说明，指导测试人员人工复查。
	CString m_szErrorSuggest;
	//BOOL m_is_dealwith;						//是否需要处理

	//CString m_ToolType;						//类似"PCLINT", "C++ TESTER"
	BOOL m_is_dealwith;

	CString m_ToolType;

	BOOL OnInitDialog();
	CComboBox m_ToolTypeCtl;
};
