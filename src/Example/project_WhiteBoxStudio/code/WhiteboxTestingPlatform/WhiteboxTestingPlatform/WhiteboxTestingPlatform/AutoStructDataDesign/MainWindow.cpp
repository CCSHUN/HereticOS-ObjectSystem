// MainWindow.cpp : 实现文件
//

#include "stdafx.h"
#include "AutoStructDataDesign.h"
#include "MainWindow.h"


// CMainWindow 对话框

IMPLEMENT_DYNAMIC(CMainWindow, CDialog)

CMainWindow::CMainWindow(CWnd* pParent /*=NULL*/)
	: CDialog(CMainWindow::IDD, pParent)
{

}

CMainWindow::~CMainWindow()
{
}

void CMainWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_MainTab);
}

BOOL CMainWindow::OnInitDialog()
{
	CDialog::OnInitDialog();
	//m_Lib.Load();
	m_FuncPage.m_pLib=&m_Lib;
	m_ExpMakePage.m_pLib=&m_Lib;
	m_LibMgr.m_pLib=&m_Lib;
	m_MainTab.AddPage(_T("库管理"),&m_LibMgr,IDD_TESTLIBMGR);
	m_MainTab.AddPage(_T("功能表达式"),&m_FuncPage,IDD_AUTOSTRUCTDATADESIGN_DIALOG);
	m_MainTab.AddPage(_T("测试用例"),&m_ExpMakePage,IDD_ExpMake);
	
	m_MainTab.Show();
	return TRUE;
}

BEGIN_MESSAGE_MAP(CMainWindow, CDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_SAVE, &CMainWindow::OnBnClickedSave)
END_MESSAGE_MAP()


// CMainWindow 消息处理程序

void CMainWindow::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_Lib.Save();
	CDialog::OnClose();
}

void CMainWindow::OnBnClickedSave()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Lib.Save();
}
