#pragma once


// CBaseReportInfoDlg �Ի���

class CBaseReportInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CBaseReportInfoDlg)

public:
	BOOL OnInitDialog();
	CBaseReportInfoDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBaseReportInfoDlg();
	BOOL PreTranslateMessage(MSG* pMsg);
	BOOL m_bNeedUpdata;

// �Ի�������
	enum { IDD = IDD_DEVUSER_REPORT_VIEW_1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeFilename();

public:
	CProjectSharedData *m_pShareData;
	UINT m_iDataIndex;
	tstring m_szUiName;
	void UpdataUi();
};
