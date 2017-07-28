#pragma once
#include "afxwin.h"

#ifdef _WIN32_WCE
#error "Windows CE ��֧�� CDHtmlDialog��"
#endif 


// CUseCaseExpMakeDlg �Ի���

class CUseCaseExpMakeDlg : public CDHtmlDialog
{
	DECLARE_DYNCREATE(CUseCaseExpMakeDlg)

public:
	//BOOL OnInitDialog();

	CUseCaseExpMakeDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUseCaseExpMakeDlg();
// ��д
	HRESULT OnButtonOK(IHTMLElement *pElement);
	HRESULT OnButtonCancel(IHTMLElement *pElement);

// �Ի�������
	enum { IDD = IDD_NEWEXPDLG, IDH = IDR_HTML_USECASEEXPMAKEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	DECLARE_DHTML_EVENT_MAP()
public:
	afx_msg void OnBnClickedOk();
	_tagFuncLib	*	m_pFuncLib;

	CString m_szDriverExp;
	CString m_szClientExp;
	CString m_szEvaluateExp;
	CString m_szSystemConfig;
	CString m_szUseCaseName;
	CString m_szTitle;
	CComboBox m_DriverCombo;
	CComboBox m_ClientCombo;
	CComboBox m_EvaluateCombo;
	CComboBox m_SystemConfigCombo;
	CString m_szExpDesc;
};
