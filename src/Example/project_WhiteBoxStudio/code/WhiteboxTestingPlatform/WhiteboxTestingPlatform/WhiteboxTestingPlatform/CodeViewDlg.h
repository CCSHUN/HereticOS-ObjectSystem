#pragma once

#include "CodeHtmlView.h"
// CCodeViewDlg �Ի���

class CCodeViewDlg : public CDialog,CCodeHtmlViewReversedCall
{
	DECLARE_DYNAMIC(CCodeViewDlg)

public:
	map<tstring,CString,less<tstring> > m_CodeMap;
	CProjectSharedData *m_pShareData;
	UINT m_iDataIndex;
	tstring m_szUiName;
	BOOL m_bNeedUpdata;

	CCodeViewDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCodeViewDlg();
	
	BOOL OnInitDialog();
	void UpdataUi();

	BOOL PreTranslateMessage(MSG* pMsg);
	void OnShowWindow(BOOL bShow, UINT nStatus);

// �Ի�������
	enum { IDD = IDD_CODEVIEW_DLG };

protected:
	
	CCodeHtmlView m_CodeHtmlView;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
