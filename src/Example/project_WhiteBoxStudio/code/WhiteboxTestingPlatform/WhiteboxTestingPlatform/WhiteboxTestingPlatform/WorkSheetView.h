#pragma once



// CWorkSheetView ������ͼ

class CWorkSheetView : public CFormView
{
	DECLARE_DYNCREATE(CWorkSheetView)

protected:
	CWorkSheetView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};


