#pragma once



// CTestingTaskView ������ͼ

class CTestingTaskView : public CFormView
{
	DECLARE_DYNCREATE(CTestingTaskView)

protected:
	CTestingTaskView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};


