#pragma once



// CTestingTaskView 窗体视图

class CTestingTaskView : public CFormView
{
	DECLARE_DYNCREATE(CTestingTaskView)

protected:
	CTestingTaskView();           // 动态创建所使用的受保护的构造函数
	virtual ~CTestingTaskView();

public:
	enum { IDD = IDD_TESTINGTASKVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};


