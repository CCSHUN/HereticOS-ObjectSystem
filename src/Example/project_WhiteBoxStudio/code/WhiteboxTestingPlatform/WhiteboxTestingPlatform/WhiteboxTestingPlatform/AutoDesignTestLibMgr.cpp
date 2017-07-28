// AutoDesignTestLibMgr.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WhiteboxTestingPlatform.h"
#include "AutoDesignTestLibMgr.h"


// CAutoDesignTestLibMgr �Ի���

IMPLEMENT_DYNAMIC(CAutoDesignTestLibMgr, CDialog)

CAutoDesignTestLibMgr::CAutoDesignTestLibMgr(CWnd* pParent /*=NULL*/)
	: CDialog(CAutoDesignTestLibMgr::IDD, pParent)
	, m_szTestLibName(_T(""))
	, m_szFromLibName(_T(""))
	, m_bIsCopyLib(FALSE)
{

}

CAutoDesignTestLibMgr::~CAutoDesignTestLibMgr()
{
}

void CAutoDesignTestLibMgr::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_szTestLibName);
	DDX_Control(pDX, IDC_COMBO1, m_LibCombo);
	DDX_Control(pDX, IDC_LIST_TESTLIB, m_TestLibList);
	DDX_CBString(pDX, IDC_COMBO1, m_szFromLibName);
	DDX_Check(pDX, IDC_CHECK_ISCOPYLIB, m_bIsCopyLib);
}


BEGIN_MESSAGE_MAP(CAutoDesignTestLibMgr, CDialog)
	ON_BN_CLICKED(IDC_NEWTESTLIB, &CAutoDesignTestLibMgr::OnBnClickedNewtestlib)
	ON_BN_CLICKED(IDC_DELLIB, &CAutoDesignTestLibMgr::OnBnClickedDellib)
	ON_BN_CLICKED(IDC_BUTTON_LOADLIB, &CAutoDesignTestLibMgr::OnBnClickedButtonLoadlib)
	ON_BN_CLICKED(IDC_CHECK_ISCOPYLIB, &CAutoDesignTestLibMgr::OnBnClickedCheckIscopylib)
END_MESSAGE_MAP()


// CAutoDesignTestLibMgr ��Ϣ�������
BOOL CAutoDesignTestLibMgr::UpDataUi(BOOL bToUi)
{
	m_TestLibList.DeleteAllItems();
	m_LibCombo.ResetContent();
	
	//m_FuncPrarmDefListCtl.SetColumnWidth(1, 120);
	//m_FuncPrarmDefListCtl.SetColumnWidth(2, 320);
	map<tstring ,int,less<tstring>> lib;
	if(m_pLib->EnumLib(lib))
	{
		map<tstring ,int,less<tstring>>::iterator itLib=lib.begin();
		for(;itLib!=lib.end();itLib++)
		{
			int nItem=m_TestLibList.InsertItem(m_TestLibList.GetItemCount(),
				itLib->first.c_str());
			m_LibCombo.AddString(itLib->first.c_str());
		}
	}

	//m_LibCombo.AddString(itLib->first.c_str());


	m_LibCombo.SetCurSel(0);

	return TRUE;
}
BOOL CAutoDesignTestLibMgr::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_TestLibList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_TestLibList.InsertColumn(0,_T("������"));
	//m_TestLibList.InsertColumn(1,_T("����Ĭ��ֵ"));
	//m_FuncPrarmDefListCtl.InsertColumn(2,_T("����˵��"));

	m_TestLibList.SetColumnWidth(0, 180);

	OnBnClickedCheckIscopylib();
	UpDataUi(TRUE);
	return TRUE;
}

void CAutoDesignTestLibMgr::OnBnClickedNewtestlib()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(m_szTestLibName.GetLength()==0)
	{
		AfxMessageBox(_T("����д������"));
		return ;
	}
	if(m_pLib->m_LibMgr.find(tstring((LPCTSTR)m_szTestLibName))!=m_pLib->m_LibMgr.end())
	{
		AfxMessageBox(_T("�������ظ�"));
		return ;
	}
	if (m_pLib->NewLib(tstring((LPCTSTR)m_szTestLibName),m_bIsCopyLib==TRUE?tstring((LPCTSTR)m_szFromLibName):tstring(_T(""))))
	{
		UpDataUi(TRUE);
	}
}

void CAutoDesignTestLibMgr::OnBnClickedDellib()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	POSITION   pos   =   m_TestLibList.GetFirstSelectedItemPosition();   
	if  (pos   ==   NULL)   
	{
		AfxMessageBox(_T("��ѡ��Ҫɾ���Ĳ���"));
		return;
	}
	else   
	{  
		while(pos)   
		{   
			int   nItem   =   m_TestLibList.GetNextSelectedItem(pos);   
			tstring szLibName=(LPCTSTR)m_TestLibList.GetItemText(nItem,0);
			//tstring szCurFunName=(LPCTSTR)m_FuncListCtl.GetItemDataPtr(m_nCurFuncPos);
			//m_TestLibList.Set
			m_pLib->DelLib(szLibName);
			//m_pLib->m_bNewUpdataExp=TRUE;

			//   you   could   do   your   own   processing   on   nItem   here   
		}   
		UpDataUi(TRUE);
	}  
}

void CAutoDesignTestLibMgr::OnBnClickedButtonLoadlib()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	POSITION   pos   =   m_TestLibList.GetFirstSelectedItemPosition();   
	if  (pos   ==   NULL)   
	{
		AfxMessageBox(_T("��ѡ��Ҫ���صĿ�"));
		return;
	}
	int   nItem   =   m_TestLibList.GetNextSelectedItem(pos);   
	tstring szLibName=(LPCTSTR)m_TestLibList.GetItemText(nItem,0);

	if(m_pLib->Load(szLibName))
	{
		m_pLib->m_bNewUpdataExp=TRUE;
		tstring szTitle=tstring(_T("�׺�ϵͳ����ƽ̨-"))+szLibName;
		theApp.GetMainWnd()->SetWindowText(szTitle.c_str());
	}else
	{
		AfxMessageBox(_T("����ʧ��"));
	}
	
}

void CAutoDesignTestLibMgr::OnBnClickedCheckIscopylib()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(m_bIsCopyLib)
	{
		m_LibCombo.EnableWindow(TRUE);
	}else
	{
		m_LibCombo.EnableWindow(FALSE);
	}
}
