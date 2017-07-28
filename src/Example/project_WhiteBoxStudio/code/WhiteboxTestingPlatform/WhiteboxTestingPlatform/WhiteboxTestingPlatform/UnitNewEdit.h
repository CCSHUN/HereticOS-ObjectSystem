#pragma once
#include "afxwin.h"


// CUnitNewEdit 对话框

class CUnitNewEdit : public CDialog
{
	DECLARE_DYNAMIC(CUnitNewEdit)

public:
	CUnitNewEdit(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUnitNewEdit();

// 对话框数据
	enum { IDD = IDD_UNITADDEDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString m_szTitle;

	CString szPrjName;
	CString szSysName;
	CString szModuleName;
	CString szTesterName;
	CString szJudgeName;
	CString szSug;
	double fIVT;
	double fINVT;
	double fBT;
	double fRCT;
	double fTCCDT;
	int nIVT;
	int nINVT;
	int nBT;
	int nRCT;
	int nTCCDT;
	CString szTestDate;
	CString szJudgeDate;
};
