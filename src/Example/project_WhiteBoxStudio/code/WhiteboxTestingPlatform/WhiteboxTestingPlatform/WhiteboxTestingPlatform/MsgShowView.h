#pragma once



// CMsgShowView ������ͼ

class CMsgShowView : public CFormView
{
	DECLARE_DYNCREATE(CMsgShowView)

protected:
	CMsgShowView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CMsgShowView();

public:
	enum { IDD = IDD_MSGSHOW_VIEW };
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


