#pragma once


// CUnitTestEndTimeDlg 对话框

class CUnitTestEndTimeDlg : public CDialog
{
	DECLARE_DYNAMIC(CUnitTestEndTimeDlg)

public:
	CUnitTestEndTimeDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUnitTestEndTimeDlg();

// 对话框数据
	enum { IDD = IDD_UNIT_ENDTime };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString m_szEndTime;
};
