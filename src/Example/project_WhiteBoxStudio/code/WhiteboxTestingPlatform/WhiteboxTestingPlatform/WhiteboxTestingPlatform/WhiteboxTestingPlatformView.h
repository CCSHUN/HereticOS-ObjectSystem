
// WhiteboxTestingPlatformView.h : CWhiteboxTestingPlatformView 类的接口
//


#pragma once


class CWhiteboxTestingPlatformView : public CFormView
{
protected: // 仅从序列化创建
	CWhiteboxTestingPlatformView();
	DECLARE_DYNCREATE(CWhiteboxTestingPlatformView)

public:
	enum{ IDD = IDD_WHITEBOXTESTINGPLATFORM_FORM };

// 属性
public:
	CWhiteboxTestingPlatformDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CWhiteboxTestingPlatformView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileNew();
};

#ifndef _DEBUG  // WhiteboxTestingPlatformView.cpp 中的调试版本
inline CWhiteboxTestingPlatformDoc* CWhiteboxTestingPlatformView::GetDocument() const
   { return reinterpret_cast<CWhiteboxTestingPlatformDoc*>(m_pDocument); }
#endif

