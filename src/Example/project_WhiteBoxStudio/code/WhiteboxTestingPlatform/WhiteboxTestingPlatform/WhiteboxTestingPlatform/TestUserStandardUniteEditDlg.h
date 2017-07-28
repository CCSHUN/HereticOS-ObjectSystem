#pragma once


// CTestUserStandardUniteEditDlg �Ի���

class CTestUserStandardUniteEditDlg : public CDialog
{
	DECLARE_DYNAMIC(CTestUserStandardUniteEditDlg)

public:
	CTestUserStandardUniteEditDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTestUserStandardUniteEditDlg();

// �Ի�������
	enum { IDD = IDD_TESTUSER_STANDARD_UNITE_EDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedAddThirdToUsinglist();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedRemove();

	void UpDataBing(BOOL bToSecond);
	//void OnInitialUpdate();

	BOOL OnInitDialog();

	CStandardSharedData  * m_pShareData;


	CString m_szDesc;
	CString m_szErrorNum;
	CString m_szErrorSuggest;
	CString m_szErrorType;
	CString m_szErrorWarning;
	_tagMachineCheckStandardSet m_CurDataSet;


	CComboBox m_ErrorTypeCtl;
	CComboBox m_ErrorClassCtl;

	CListCtrl m_NoUsingList;
	CListCtrl m_UsingList;
};
