#pragma once
#include "afxcmn.h"



// CReportView ������ͼ

class CReportView : public CFormView
{
	DECLARE_DYNCREATE(CReportView)

protected:
	CReportView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CReportView();

public:
	enum { IDD = IDD_REPORTVIEW };
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
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_lstReport;
	afx_msg void OnLvnItemchangedListReport(NMHDR *pNMHDR, LRESULT *pResult);
};


