#pragma once



// CWorkSheetView 窗体视图

class CWorkSheetView : public CFormView
{
	DECLARE_DYNCREATE(CWorkSheetView)

protected:
	CWorkSheetView();           // 动态创建所使用的受保护的构造函数
	virtual ~CWorkSheetView();

public:
	enum { IDD = IDD_WORKSHEETVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};


