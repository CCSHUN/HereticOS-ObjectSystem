#pragma once


// CTestUserNewStandard �Ի���

class CTestUserNewStandard : public CDialog
{
	DECLARE_DYNAMIC(CTestUserNewStandard)

public:
	CTestUserNewStandard(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTestUserNewStandard();
	BOOL PreTranslateMessage(MSG* pMsg);

// �Ի�������
	enum { IDD = IDD_TESTUSER_STANDARD_NEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CString m_szStandardName;
};
