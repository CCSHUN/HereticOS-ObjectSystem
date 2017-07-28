#pragma once
#include "afxcmn.h"
#include "afxwin.h"



// CAdminUserEditView 窗体视图

class CAdminUserEditView : public CFormView,CViewInterfaceForWorkPageManager
{
	DECLARE_DYNCREATE(CAdminUserEditView)

protected:
	CAdminUserEditView();           // 动态创建所使用的受保护的构造函数
	virtual ~CAdminUserEditView();

public:
	BOOL UpdataUi();
	void OnInitialUpdate();

	enum { IDD = IDD_ADMINUSER_USEREDIT_VIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	CUserShareData  * m_pShareData;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedEdituser();
	afx_msg void OnBnClickedAdduser();
	CListCtrl m_UserListCtl;
	CListBox m_UserProjectListBox;
	CListBox m_UserNoUsingProjectListBox;
	afx_msg void OnBnClickedDelseluser();
	afx_msg void OnBnClickedAddpro();
	afx_msg void OnBnClickedRemovepro();
	afx_msg void OnLvnItemchangedListUser(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListUser(NMHDR *pNMHDR, LRESULT *pResult);
};


