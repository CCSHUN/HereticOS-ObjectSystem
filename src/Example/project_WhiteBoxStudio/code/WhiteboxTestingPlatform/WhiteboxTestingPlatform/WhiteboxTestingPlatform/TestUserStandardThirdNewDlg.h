#pragma once
#include "afxwin.h"


// CTestUserStandardThirdNewDlg �Ի���

class CTestUserStandardThirdNewDlg : public CDialog
{
	DECLARE_DYNAMIC(CTestUserStandardThirdNewDlg)

public:
	CTestUserStandardThirdNewDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTestUserStandardThirdNewDlg();
	BOOL PreTranslateMessage(MSG* pMsg);

// �Ի�������
	enum { IDD = IDD_TESTUSER_STANDARD_THIRD_NEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedNew();
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

	CString m_ToolType;

	BOOL OnInitDialog();
	CComboBox m_ToolTypeCtl;
};
