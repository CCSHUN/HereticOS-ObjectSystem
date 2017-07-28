#pragma once


#include "CodeViewDlg.h"
// CCodeView ������ͼ

class CCodeView : public CFormView, public CViewInterfaceForWorkPageManager
{
	DECLARE_DYNCREATE(CCodeView)

protected:
	CCodeView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CCodeView();

public:
	CCodeViewDlg m_CodeViewCtl;
	CProjectSharedData *m_pShareData;
	virtual void OnInitialUpdate();
	void ProjectChange(BOOL bToTop);
	void UpDataUi();

	enum { IDD = IDD_CODEVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};


