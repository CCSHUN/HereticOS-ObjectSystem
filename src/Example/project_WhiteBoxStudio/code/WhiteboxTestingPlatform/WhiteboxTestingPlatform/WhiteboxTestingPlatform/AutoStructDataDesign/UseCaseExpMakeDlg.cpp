// UseCaseExpMakeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AutoStructDataDesign.h"
#include "UseCaseExpMakeDlg.h"


// CUseCaseExpMakeDlg �Ի���

IMPLEMENT_DYNCREATE(CUseCaseExpMakeDlg, CDHtmlDialog)

CUseCaseExpMakeDlg::CUseCaseExpMakeDlg(CWnd* pParent /*=NULL*/)
	: CDHtmlDialog(CUseCaseExpMakeDlg::IDD, CUseCaseExpMakeDlg::IDH, pParent)
	, m_szDriverExp(_T(""))
	, m_szClientExp(_T(""))
	, m_szEvaluateExp(_T(""))
	, m_szSystemConfig(_T(""))
	, m_szUseCaseName(_T("Test001"))
	, m_szExpDesc(_T("˵��"))
{

}

CUseCaseExpMakeDlg::~CUseCaseExpMakeDlg()
{
}

void CUseCaseExpMakeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDHtmlDialog::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO1, m_szDriverExp);
	DDX_CBString(pDX, IDC_COMBO2, m_szClientExp);
	DDX_CBString(pDX, IDC_COMBO3, m_szEvaluateExp);
	DDX_CBString(pDX, IDC_COMBO4, m_szSystemConfig);
	DDX_Text(pDX, IDC_EDIT_USECASENAME, m_szUseCaseName);
	DDX_Control(pDX, IDC_COMBO1, m_DriverCombo);
	DDX_Control(pDX, IDC_COMBO2, m_ClientCombo);
	DDX_Control(pDX, IDC_COMBO3, m_EvaluateCombo);
	DDX_Control(pDX, IDC_COMBO4, m_SystemConfigCombo);
	DDX_Text(pDX, IDC_EDIT_USECASEDESC, m_szExpDesc);
}

BOOL CUseCaseExpMakeDlg::OnInitDialog()
{
	CDHtmlDialog::OnInitDialog();
	map<tstring,_tagFuncDef,less<tstring> >::iterator itFunc=m_pFuncLib->m_FuncLib.begin();
	for(;itFunc!=m_pFuncLib->m_FuncLib.end();itFunc++)
	{
		if(tstring(_T("��������"))==itFunc->second.szFuncType)
		{
			m_DriverCombo.AddString(itFunc->first.c_str());
		}else if(tstring(_T("��������"))==itFunc->second.szFuncType)
		{
			m_ClientCombo.AddString(itFunc->first.c_str());
		}else if(tstring(_T("��������"))==itFunc->second.szFuncType)
		{
			m_EvaluateCombo.AddString(itFunc->first.c_str());
		}else if(tstring(_T("ϵͳ����"))==itFunc->second.szFuncType)
		{
			m_SystemConfigCombo.AddString(itFunc->first.c_str());
		}
	}

	if(m_szTitle==_T("�������"))
	{
		m_DriverCombo.SetCurSel(0);
		m_ClientCombo.SetCurSel(0);
		m_EvaluateCombo.SetCurSel(0);
		m_SystemConfigCombo.SetCurSel(0);
	}else
	{
		if(m_szDriverExp.GetLength())
		{
			m_DriverCombo.SelectString(0,m_szDriverExp);
		}
		if(m_szClientExp.GetLength())
		{
			m_ClientCombo.SelectString(0,m_szClientExp);
		}
		if(m_szEvaluateExp.GetLength())
		{
			m_EvaluateCombo.SelectString(0,m_szEvaluateExp);
		}
		if(m_szSystemConfig.GetLength())
		{
			m_SystemConfigCombo.SelectString(0,m_szSystemConfig);
		}
	}
	
	

	this->SetWindowText(m_szTitle);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

BEGIN_MESSAGE_MAP(CUseCaseExpMakeDlg, CDHtmlDialog)
	ON_BN_CLICKED(IDOK, &CUseCaseExpMakeDlg::OnBnClickedOk)
END_MESSAGE_MAP()

BEGIN_DHTML_EVENT_MAP(CUseCaseExpMakeDlg)
	DHTML_EVENT_ONCLICK(_T("ButtonOK"), OnButtonOK)
	DHTML_EVENT_ONCLICK(_T("ButtonCancel"), OnButtonCancel)
END_DHTML_EVENT_MAP()



// CUseCaseExpMakeDlg ��Ϣ�������

HRESULT CUseCaseExpMakeDlg::OnButtonOK(IHTMLElement* /*pElement*/)
{
	OnOK();
	return S_OK;
}

HRESULT CUseCaseExpMakeDlg::OnButtonCancel(IHTMLElement* /*pElement*/)
{
	OnCancel();
	return S_OK;
}

/*
m_FuncTypeComboCtl.AddString(_T("��������"));
m_FuncTypeComboCtl.AddString(_T("��������"));
m_FuncTypeComboCtl.AddString(_T("��������"));
m_FuncTypeComboCtl.AddString(_T("ϵͳ����"));
*/


void CUseCaseExpMakeDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if((m_szDriverExp.GetLength()==0)
		||(m_szClientExp.GetLength()==0)
		||(m_szEvaluateExp.GetLength()==0)
		||(m_szSystemConfig.GetLength()==0)
		||(m_szUseCaseName.GetLength()==0)
		||(m_szExpDesc.GetLength()==0))
	{
		AfxMessageBox(_T("����ȷ��д����"));
	}else
	{
		OnOK();
	}
}
