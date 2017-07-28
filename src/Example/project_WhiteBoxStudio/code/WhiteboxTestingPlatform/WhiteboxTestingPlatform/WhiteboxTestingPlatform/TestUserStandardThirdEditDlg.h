#pragma once


// CTestUserStandardThirdEditDlg �Ի���

class CTestUserStandardThirdEditDlg : public CDialog
{
	DECLARE_DYNAMIC(CTestUserStandardThirdEditDlg)

public:
	CTestUserStandardThirdEditDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTestUserStandardThirdEditDlg();
	BOOL PreTranslateMessage(MSG* pMsg);

// �Ի�������
	enum { IDD = IDD_TESTUSER_STANDARD_THIRD_EDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();


	void UpDataBing(BOOL bToSecond);
	_tagThirdStandardSet m_CurDataSet;
	CStandardSharedData  * m_pShareData;
	CString m_szUniteStandardErrorNum;		//��е�߶�ͳһ�淶
	CString m_szThirdStandardErrorNum;		//PCLINT����CTester�Ĵ���ID
	CString m_szThirdStandardErrorDesc;
	BOOL m_is_manual_check;					//�Ƿ���Ҫ�˹����
	CString m_szManual_check_MethodSpecify;	//�˹������׼˵����ָ��������Ա�˹����顣
	CString m_szErrorSuggest;
	//BOOL m_is_dealwith;						//�Ƿ���Ҫ����

	//CString m_ToolType;						//����"PCLINT", "C++ TESTER"
	BOOL m_is_dealwith;

	afx_msg void OnBnClickedOk();

	BOOL OnInitDialog();

	CString m_ToolType;

	CComboBox m_ToolTypeCtl;
};
