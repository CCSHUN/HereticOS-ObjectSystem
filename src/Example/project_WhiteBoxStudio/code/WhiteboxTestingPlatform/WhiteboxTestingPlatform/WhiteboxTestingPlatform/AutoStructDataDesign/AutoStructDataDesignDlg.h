
// AutoStructDataDesignDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "TestConfig.h"
#include "TestLibDataMode.h"
class CAutoStructDataDesignDlgAutoProxy;


// CAutoStructDataDesignDlg �Ի���
class CAutoStructDataDesignDlg : public CDialog
{
	DECLARE_DYNAMIC(CAutoStructDataDesignDlg);
	friend class CAutoStructDataDesignDlgAutoProxy;

// ����
public:
	CAutoStructDataDesignDlg(CWnd* pParent = NULL);	// ��׼���캯��
	virtual ~CAutoStructDataDesignDlg();

// �Ի�������
	enum { IDD = IDD_AUTOSTRUCTDATADESIGN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	BOOL LoadToUi();
	//BOOL SaveToXml();
	BOOL UpDataUi(BOOL ToUi);


// ʵ��
protected:
	CAutoStructDataDesignDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedAddfunc();
	afx_msg void OnBnClickedDelfunc();
	afx_msg void OnBnClickedAddprrarm();
	afx_msg void OnBnClickedDelparam();
	afx_msg void OnBnClickedUpdataParamdef();
	
	CListBox m_FuncListCtl;
	CListCtrl m_FuncPrarmDefListCtl;
	
	CString m_szFuncName;
	CComboBox m_FuncTypeComboCtl;
	CString m_szFuncDesc;
	CString m_szParamName;
	CString m_szParamDesc;
	
	afx_msg void OnLbnSelchangeListFunc();
	
	afx_msg void OnLvnItemchangedListPrarmdef(NMHDR *pNMHDR, LRESULT *pResult);

	
	CString m_szFuncType;

	TestLibDataMode * m_pLib;


	int m_nCurFuncPos;
	CString m_szDefaultParamVal;
	
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedEditfunc();
	//afx_msg void OnBnClickedCheckM();
	//CString m_szRefMacroName;
};
