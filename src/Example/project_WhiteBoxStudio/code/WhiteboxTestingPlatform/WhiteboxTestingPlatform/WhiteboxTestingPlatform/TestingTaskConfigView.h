#pragma once
#include "afxwin.h"



// CTestingTaskConfigView ������ͼ

class CTestingTaskConfigView : public CFormView, public CViewInterfaceForWorkPageManager
{
	DECLARE_DYNCREATE(CTestingTaskConfigView)

protected:
	CTestingTaskConfigView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CTestingTaskConfigView();

public:
	enum { IDD = IDD_TESTINGTASKCONFIGVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileNew();

	void ProjectChange();
	virtual void OnInitialUpdate();
	CComboBox m_cmbSpecifyName;
	CString m_sCMDParam;
	CString m_sProjectName;
	CProjectSharedData *m_pShareData;
	CString m_sStandardParam;
	afx_msg void OnEnChangeEditStandardparam();
	afx_msg void OnBnClickedButton1();
	CString m_sPrivateParam;
	CEdit m_StandardParamCtl;
};


