#pragma once
#include "afxwin.h"


// CAddressNavigate 对话框
#define ADDR_PROJECT _T("项目:")
#define ADDR_STAREND _T("规范:")
#define ADDR_MESSAGE _T("消息:")
#define ADDR_SEARCH _T("搜索:")
#define ADDR_MGR _T("管理:")

class CAddressNavigate : public CDialog
{
	DECLARE_DYNAMIC(CAddressNavigate)

public:
	BOOL UpDataSize();
	BOOL GotoAddr(tstring & szAddr);
	CAddressNavigate(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAddressNavigate();
	BOOL SetAddr(tstring & szAddrType,tstring & szAddrNoType);
	BOOL PreTranslateMessage(MSG* pMsg);
	BOOL OnInitDialog();
	BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);

// 对话框数据
	enum { IDD = IDD_ADDR_NAVIGATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_AddrEditCtl;
	CString m_szAddress;
	CComboBox m_AddrTypeCtl;
	CString m_szAddrType;
};
