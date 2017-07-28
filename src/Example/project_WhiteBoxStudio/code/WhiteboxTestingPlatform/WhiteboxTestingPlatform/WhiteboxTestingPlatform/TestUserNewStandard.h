#pragma once


// CTestUserNewStandard 对话框

class CTestUserNewStandard : public CDialog
{
	DECLARE_DYNAMIC(CTestUserNewStandard)

public:
	CTestUserNewStandard(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTestUserNewStandard();
	BOOL PreTranslateMessage(MSG* pMsg);

// 对话框数据
	enum { IDD = IDD_TESTUSER_STANDARD_NEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CString m_szStandardName;
};
