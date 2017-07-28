#pragma once
#include "afxwin.h"


// CAddressNavigate �Ի���
#define ADDR_PROJECT _T("��Ŀ:")
#define ADDR_STAREND _T("�淶:")
#define ADDR_MESSAGE _T("��Ϣ:")
#define ADDR_SEARCH _T("����:")
#define ADDR_MGR _T("����:")

class CAddressNavigate : public CDialog
{
	DECLARE_DYNAMIC(CAddressNavigate)

public:
	BOOL UpDataSize();
	BOOL GotoAddr(tstring & szAddr);
	CAddressNavigate(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAddressNavigate();
	BOOL SetAddr(tstring & szAddrType,tstring & szAddrNoType);
	BOOL PreTranslateMessage(MSG* pMsg);
	BOOL OnInitDialog();
	BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);

// �Ի�������
	enum { IDD = IDD_ADDR_NAVIGATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_AddrEditCtl;
	CString m_szAddress;
	CComboBox m_AddrTypeCtl;
	CString m_szAddrType;
};
