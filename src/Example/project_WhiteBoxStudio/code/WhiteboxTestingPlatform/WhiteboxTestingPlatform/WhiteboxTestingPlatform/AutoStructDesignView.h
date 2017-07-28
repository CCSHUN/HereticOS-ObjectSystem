#pragma once
#include "afxcmn.h"
#include "afxwin.h"
//#include "resource.h"

// CAutoStructDesignView ������ͼ

class CAutoStructDesignView : public CFormView,CViewInterfaceForWorkPageManager
{
	DECLARE_DYNCREATE(CAutoStructDesignView)
	void OnInitialUpdate();
protected:
	CAutoStructDesignView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CAutoStructDesignView();

public:
	enum { IDD = IDD_STRCUTDATA_DESIGN_VIEW };
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
	afx_msg void OnBnClickedAddtotypelib();
	afx_msg void OnBnClickedAddtemplate();
	afx_msg void OnBnClickedDeltemplate();
	afx_msg void OnBnClickedUpdata();
	afx_msg void OnBnClickedAddtemplate3();
	afx_msg void OnBnClickedDeltemplate2();
	afx_msg void OnBnClickedUpdata2();
	CTreeCtrl m_TypeLibTree;
	CListBox m_TemplateListCtl;
	CString m_szTemplateName;
	CString m_szTemplateDesc;
	CListBox m_PrarmListCtl;
	CComboBox m_PrarmTypeCombo;
	CString m_PrarmDesc;
	CString m_PrarmName;
	afx_msg void OnBnClickedSave();
};


