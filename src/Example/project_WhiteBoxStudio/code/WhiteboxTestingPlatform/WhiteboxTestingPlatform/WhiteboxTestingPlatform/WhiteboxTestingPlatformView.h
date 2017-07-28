
// WhiteboxTestingPlatformView.h : CWhiteboxTestingPlatformView ��Ľӿ�
//


#pragma once


class CWhiteboxTestingPlatformView : public CFormView
{
protected: // �������л�����
	CWhiteboxTestingPlatformView();
	DECLARE_DYNCREATE(CWhiteboxTestingPlatformView)

public:
	enum{ IDD = IDD_WHITEBOXTESTINGPLATFORM_FORM };

// ����
public:
	CWhiteboxTestingPlatformDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CWhiteboxTestingPlatformView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileNew();
};

#ifndef _DEBUG  // WhiteboxTestingPlatformView.cpp �еĵ��԰汾
inline CWhiteboxTestingPlatformDoc* CWhiteboxTestingPlatformView::GetDocument() const
   { return reinterpret_cast<CWhiteboxTestingPlatformDoc*>(m_pDocument); }
#endif

