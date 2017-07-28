#pragma once
#include "afxwin.h"


// CSubProjectManger 对话框

class CSubProjectManger : public CDialog
{
	DECLARE_DYNAMIC(CSubProjectManger)

public:
	CSubProjectManger(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSubProjectManger();

// 对话框数据
	enum { IDD = IDD_SUBPROJECTMANGERDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CProjectSharedData * m_pShareData;
	BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	CComboBox m_ProjectStateComboCtl;
	CString m_szProjectState;
};
