#pragma once
#include "afxcmn.h"
#include "ListCtlStringSort.h"


// CTestUserStandardThirdView ������ͼ

class CTestUserStandardThirdView : public CFormView ,CViewInterfaceForWorkPageManager
{
	DECLARE_DYNCREATE(CTestUserStandardThirdView)

protected:
	CTestUserStandardThirdView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CTestUserStandardThirdView();

public:
	enum { IDD = IDD_TESTUSER_STANDARD_THIRD_VIEW };
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
	afx_msg void OnBnClickedNewStandard();
	

	BOOL UpdataUi();

	void UpDataBing(BOOL bToSecond);
	_tagThirdStandardSet m_CurDataSet;
	CStandardSharedData  * m_pShareData;
	CString m_szUniteStandardErrorNum;		//��е�߶�ͳһ�淶
	CString m_szThirdStandardErrorNum;		//PCLINT����CTester�Ĵ���ID
	CString m_szThirdStandardErrorDesc;
	BOOL m_is_manual_check;					//�Ƿ���Ҫ�˹����
	CString m_szManual_check_MethodSpecify;	//�˹������׼˵����ָ��������Ա�˹����顣
	CString m_szErrorSuggest;
	//BOOL m_is_dealwith;						//�Ƿ���Ҫ����

	CString m_ToolType;						//����"PCLINT", "C++ TESTER"

	afx_msg void OnBnClickedDeleteCur();
	afx_msg void OnBnClickedComplateStandard();

	void ProjectChange(BOOL bToTop);
	BOOL m_is_dealwith;
	CListCtlStringSort m_ThirdStandardList;
	afx_msg void OnBnClickedEditStandard();

	void OnInitialUpdate();
	afx_msg void OnLvnItemchangedReportList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHdnItemdblclickReportList(NMHDR *pNMHDR, LRESULT *pResult);



	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnReGetObject();
	afx_msg void OnReleaseObjectLock();
	afx_msg void OnGetObjectLock();
	afx_msg void OnCanEdit(CCmdUI *pCmdUI);
	void EnableEdit(BOOL bCanEdit);
	void UpDataObjectUiState();
	BOOL m_bCanEdit;

protected:
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
public:
	afx_msg void OnNMDblclkReportList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnColumnclickListReport(NMHDR *pNMHDR, LRESULT *pResult);
};


