// AddressNavigate.cpp : 实现文件
//

#include "stdafx.h"
#include "WhiteboxTestingPlatform.h"
#include "AddressNavigate.h"


// CAddressNavigate 对话框

IMPLEMENT_DYNAMIC(CAddressNavigate, CDialog)

CAddressNavigate::CAddressNavigate(CWnd* pParent /*=NULL*/)
	: CDialog(CAddressNavigate::IDD, pParent)
	, m_szAddress(_T(""))
	, m_szAddrType(_T(""))
{

}

CAddressNavigate::~CAddressNavigate()
{
}

BOOL CAddressNavigate::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{

	AfxMessageBox(_T(""));
	return TRUE;
}
BOOL CAddressNavigate::UpDataSize()
{
	RECT rect,rectPar;
	GetWindowRect(&rect);
	GetParent()->GetWindowRect(&rectPar);
	RECT rect1;
	m_AddrEditCtl.GetWindowRect(&rect1);
	//rect1.right=rect.right-260;
	rect1.left=rect1.left-rect.left;
	rect1.top=rect1.top-rect.top;
	rect1.bottom=rect1.bottom-rect.top;

	RECT pos={100,0,250,30};
	rect1.right=rectPar.right-250;
	rect1.right=rect1.right-rect.left;
	m_AddrEditCtl.MoveWindow(&rect1,TRUE);
	return TRUE;
}

BOOL CAddressNavigate::GotoAddr(tstring & szAddr)
{
	UpdateData(TRUE);
	tstring szAddrNoType;
	
	m_szAddrType=_T("未知");

	if(strstr_t(szAddr.c_str(),ADDR_PROJECT)==szAddr.c_str())
	{
		szAddrNoType=szAddr.c_str()+strlen_t(ADDR_PROJECT);
		theApp.m_WorkSpaceWndManger.m_ProjectDataModel.
			GoProjectPage(szAddrNoType);
		//m_AddrTypeCtl.SelectString(0,ADDR_PROJECT);
		m_szAddrType=ADDR_PROJECT;
	}else if(strstr_t(szAddr.c_str(),ADDR_STAREND)==szAddr.c_str())
	{
		szAddrNoType=szAddr.c_str()+strlen_t(ADDR_STAREND);
		theApp.m_WorkSpaceWndManger.m_StandardDataModel.
			GoProjectPage(szAddrNoType);
		//m_AddrTypeCtl.SelectString(0,ADDR_STAREND);
		m_szAddrType=ADDR_STAREND;
	}else if(strstr_t(szAddr.c_str(),ADDR_MESSAGE)==szAddr.c_str())
	{

	}else if(strstr_t(szAddr.c_str(),ADDR_SEARCH)==szAddr.c_str())
	{

	}else if(strstr_t(szAddr.c_str(),ADDR_MGR)==szAddr.c_str())
	{

	}else
	{
		AfxMessageBox(_T("无效地址引用"));
		return FALSE;
	}

	m_szAddress=szAddr.c_str();
	UpdateData(FALSE);
	return TRUE;

}
void CAddressNavigate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ADDR, m_AddrEditCtl);
	DDX_Text(pDX, IDC_ADDR, m_szAddress);
	DDX_Control(pDX, IDC_COMBO_ADDRTYPE, m_AddrTypeCtl);
	DDX_CBString(pDX, IDC_COMBO_ADDRTYPE, m_szAddrType);
}

BOOL CAddressNavigate::SetAddr(tstring & szAddrType,tstring & szAddrNoType)
{
	m_szAddrType=szAddrType.c_str();

	if(m_szAddrType==ADDR_PROJECT)
	{
		m_szAddress=ADDR_PROJECT;
	}else if(m_szAddrType==ADDR_STAREND)
	{
		m_szAddress=ADDR_STAREND;
	}else if(m_szAddrType==ADDR_MESSAGE)
	{
		m_szAddress=ADDR_MESSAGE;
	}else if(m_szAddrType==ADDR_SEARCH)
	{
		m_szAddress=ADDR_SEARCH;
	}else if(m_szAddrType==ADDR_MGR)
	{
		m_szAddress=ADDR_MGR;
	}else
	{
		m_szAddress=_T("");
	}

	m_szAddress+=szAddrNoType.c_str();
	UpdateData(FALSE);
	return TRUE;
}
BOOL CAddressNavigate::PreTranslateMessage(MSG* pMsg)
{
	switch(pMsg->message)
	{
	case WM_KEYDOWN:
		if(pMsg->wParam==VK_RETURN)
		{
			UpdateData(TRUE);
			GotoAddr(tstring(m_szAddress.GetBuffer(0)));
			return TRUE;
		}
		//pMsg->wParam;
	default:
		return CDialog::PreTranslateMessage(pMsg);

	}
	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CAddressNavigate::OnInitDialog()
{
	CDialog::OnInitDialog();
	UpDataSize();
	m_AddrTypeCtl.AddString(ADDR_PROJECT);
	m_AddrTypeCtl.AddString(ADDR_STAREND);
	m_AddrTypeCtl.AddString(ADDR_SEARCH);
	m_AddrTypeCtl.AddString(ADDR_MESSAGE);
	m_AddrTypeCtl.AddString(ADDR_MGR);
	return TRUE;
}

BEGIN_MESSAGE_MAP(CAddressNavigate, CDialog)
	ON_WM_COPYDATA()
END_MESSAGE_MAP()


// CAddressNavigate 消息处理程序
