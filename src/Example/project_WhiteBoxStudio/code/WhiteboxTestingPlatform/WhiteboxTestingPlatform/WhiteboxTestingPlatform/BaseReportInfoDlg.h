#pragma once


// CBaseReportInfoDlg 对话框

class CBaseReportInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CBaseReportInfoDlg)

public:
	BOOL OnInitDialog();
	CBaseReportInfoDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBaseReportInfoDlg();
	BOOL PreTranslateMessage(MSG* pMsg);
	BOOL m_bNeedUpdata;

// 对话框数据
	enum { IDD = IDD_DEVUSER_REPORT_VIEW_1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeFilename();

public:
	CProjectSharedData *m_pShareData;
	UINT m_iDataIndex;
	tstring m_szUiName;
	void UpdataUi();
};
