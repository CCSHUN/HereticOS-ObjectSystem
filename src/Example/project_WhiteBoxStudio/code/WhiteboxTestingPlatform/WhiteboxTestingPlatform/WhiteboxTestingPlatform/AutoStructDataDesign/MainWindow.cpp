// MainWindow.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AutoStructDataDesign.h"
#include "MainWindow.h"


// CMainWindow �Ի���

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
	m_MainTab.AddPage(_T("�����"),&m_LibMgr,IDD_TESTLIBMGR);
	m_MainTab.AddPage(_T("���ܱ��ʽ"),&m_FuncPage,IDD_AUTOSTRUCTDATADESIGN_DIALOG);
	m_MainTab.AddPage(_T("��������"),&m_ExpMakePage,IDD_ExpMake);
	
	m_MainTab.Show();
	return TRUE;
}

BEGIN_MESSAGE_MAP(CMainWindow, CDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_SAVE, &CMainWindow::OnBnClickedSave)
END_MESSAGE_MAP()


// CMainWindow ��Ϣ�������

void CMainWindow::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_Lib.Save();
	CDialog::OnClose();
}

void CMainWindow::OnBnClickedSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_Lib.Save();
}
