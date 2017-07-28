#pragma once

#include "StandardDataModel.h"
#include "afxwin.h"
#include "afxcmn.h"
// CTestUserStandardUniteNewDlg �Ի���

class CTestUserStandardUniteNewDlg : public CDialog
{
	void UpDataBing(BOOL bToSecond=TRUE);

	DECLARE_DYNAMIC(CTestUserStandardUniteNewDlg)

public:
	CTestUserStandardUniteNewDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTestUserStandardUniteNewDlg();
	BOOL PreTranslateMessage(MSG* pMsg);

// �Ի�������
	enum { IDD = IDD_TESTUSER_STANDARD_UNITE_NEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	_tagMachineCheckStandardSet m_CurDataSet;
	CStandardSharedData  * m_pShareData;
	afx_msg void OnBnClickedAddThirdToUsinglist();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();


	//BOOL SetCur

	CString m_szDesc;
	CString m_szErrorNum;
	CString m_szErrorSuggest;
	CString m_szErrorType;
	CString m_szErrorWarning;
	CComboBox m_ErrorTypeCtl;
	CComboBox m_ErrorClassCtl;
	afx_msg void OnBnClickedRemove();

	BOOL OnInitDialog();
	CListCtrl m_NoUsingList;
	CListCtrl m_UsingList;
};
