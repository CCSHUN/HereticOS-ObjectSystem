
// DlgProxy.h: ͷ�ļ�
//

#pragma once

class CAutoStructDataDesignDlg;


// CAutoStructDataDesignDlgAutoProxy ����Ŀ��

class CAutoStructDataDesignDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CAutoStructDataDesignDlgAutoProxy)

	CAutoStructDataDesignDlgAutoProxy();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��

// ����
public:
	CAutoStructDataDesignDlg* m_pDialog;

// ����
public:

// ��д
	public:
	virtual void OnFinalRelease();

// ʵ��
protected:
	virtual ~CAutoStructDataDesignDlgAutoProxy();

	// ���ɵ���Ϣӳ�亯��

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CAutoStructDataDesignDlgAutoProxy)

	// ���ɵ� OLE ����ӳ�亯��

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

