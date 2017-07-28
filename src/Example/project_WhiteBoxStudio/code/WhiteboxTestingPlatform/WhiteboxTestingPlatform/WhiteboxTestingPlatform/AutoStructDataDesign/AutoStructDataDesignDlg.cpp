
// AutoStructDataDesignDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AutoStructDataDesign.h"
#include "AutoStructDataDesignDlg.h"
#include "DlgProxy.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���



// CAutoStructDataDesignDlg �Ի���




IMPLEMENT_DYNAMIC(CAutoStructDataDesignDlg, CDialog);

CAutoStructDataDesignDlg::CAutoStructDataDesignDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAutoStructDataDesignDlg::IDD, pParent)
	, m_szFuncName(_T(""))
	, m_szFuncDesc(_T(""))
	, m_szParamName(_T(""))
	, m_szParamDesc(_T(""))
	, m_szFuncType(_T(""))
	, m_szDefaultParamVal(_T(""))
	
	, m_szRefMacroName(_T(""))
{
	m_nCurFuncPos=-1;
	
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;
}

CAutoStructDataDesignDlg::~CAutoStructDataDesignDlg()
{
	// ����öԻ������Զ���������
	//  ���˴���ָ��öԻ���ĺ���ָ������Ϊ NULL���Ա�
	//  �˴���֪���öԻ����ѱ�ɾ����
	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;
}

void CAutoStructDataDesignDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST_FUNC, m_FuncListCtl);
	DDX_Control(pDX, IDC_LIST_PRARMDEF, m_FuncPrarmDefListCtl);

	DDX_Text(pDX, IDC_EDIT_PARAMNAME2, m_szFuncName);
	DDX_Control(pDX, IDC_COMBO1, m_FuncTypeComboCtl);
	DDX_Text(pDX, IDC_EDIT_FUNCDESC, m_szFuncDesc);
	DDX_Text(pDX, IDC_EDIT_PARAMNAME, m_szParamName);
	DDX_Text(pDX, IDC_EDIT_DESC, m_szParamDesc);

	DDX_CBString(pDX, IDC_COMBO1, m_szFuncType);
	DDX_Text(pDX, IDC_EDIT_DEFAULTPARAM, m_szDefaultParamVal);

	//DDX_CBString(pDX, IDC_COMBO_MACRO, m_szRefMacroName);
}

BEGIN_MESSAGE_MAP(CAutoStructDataDesignDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDCANCEL, &CAutoStructDataDesignDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_ADDFUNC, &CAutoStructDataDesignDlg::OnBnClickedAddfunc)
	ON_BN_CLICKED(IDC_DELFUNC, &CAutoStructDataDesignDlg::OnBnClickedDelfunc)
	ON_BN_CLICKED(IDC_ADDPRRARM, &CAutoStructDataDesignDlg::OnBnClickedAddprrarm)
	ON_BN_CLICKED(IDC_DELPARAM, &CAutoStructDataDesignDlg::OnBnClickedDelparam)
	ON_BN_CLICKED(IDC_UPDATA_PARAMDEF, &CAutoStructDataDesignDlg::OnBnClickedUpdataParamdef)

	ON_LBN_SELCHANGE(IDC_LIST_FUNC, &CAutoStructDataDesignDlg::OnLbnSelchangeListFunc)

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_PRARMDEF, &CAutoStructDataDesignDlg::OnLvnItemchangedListPrarmdef)

	ON_WM_ACTIVATE()
	ON_WM_SIZE()
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_EDITFUNC, &CAutoStructDataDesignDlg::OnBnClickedEditfunc)
	//ON_BN_CLICKED(IDC_CHECK_M, &CAutoStructDataDesignDlg::OnBnClickedCheckM)
END_MESSAGE_MAP()


// CAutoStructDataDesignDlg ��Ϣ�������

BOOL CAutoStructDataDesignDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	/*
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_SHOWNORMAL);
	*/

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	m_FuncPrarmDefListCtl.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_FuncPrarmDefListCtl.InsertColumn(0,_T("��������"));
	m_FuncPrarmDefListCtl.InsertColumn(1,_T("����Ĭ��ֵ"));
	m_FuncPrarmDefListCtl.InsertColumn(2,_T("����˵��"));

	m_FuncPrarmDefListCtl.SetColumnWidth(0, 80);
	m_FuncPrarmDefListCtl.SetColumnWidth(1, 120);
	m_FuncPrarmDefListCtl.SetColumnWidth(2, 320);


	m_FuncTypeComboCtl.AddString(_T("��������"));
	m_FuncTypeComboCtl.AddString(_T("��������"));
	m_FuncTypeComboCtl.AddString(_T("��������"));
	m_FuncTypeComboCtl.AddString(_T("ϵͳ����"));
	m_FuncTypeComboCtl.SelectString(0,_T("��������"));
	LoadToUi();
	

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CAutoStructDataDesignDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	//if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	//{
		//CAboutDlg dlgAbout;
		//dlgAbout.DoModal();
	//}
	//else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CAutoStructDataDesignDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CAutoStructDataDesignDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// ���û��ر� UI ʱ������������Ա���������ĳ��
//  �������Զ�����������Ӧ�˳�����Щ
//  ��Ϣ�������ȷ����������: �����������ʹ�ã�
//  ������ UI�������ڹرնԻ���ʱ��
//  �Ի�����Ȼ�ᱣ�������

void CAutoStructDataDesignDlg::OnClose()
{
	if (CanExit())
	{
		//SaveToXml();
		CDialog::OnClose();
	}
}

void CAutoStructDataDesignDlg::OnOK()
{
	if (CanExit())
		CDialog::OnOK();
}

void CAutoStructDataDesignDlg::OnCancel()
{
	if (CanExit())
		CDialog::OnCancel();
}

BOOL CAutoStructDataDesignDlg::CanExit()
{
	// �����������Ա�����������Զ���
	//  �������Իᱣ�ִ�Ӧ�ó���
	//  ʹ�Ի���������������� UI ����������
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}

BOOL CAutoStructDataDesignDlg::UpDataUi(BOOL ToUi)
{

	m_FuncListCtl.ResetContent();
	m_FuncPrarmDefListCtl.DeleteAllItems();


	map<tstring,_tagFuncDef,less<tstring> >::iterator itFunc=m_pLib->m_FuncLib.m_FuncLib.begin();

	for(;itFunc!=m_pLib->m_FuncLib.m_FuncLib.end();itFunc++)
	{
		m_FuncListCtl.SetItemData(m_FuncListCtl.AddString(m_pLib->GetFuncDefStringFromFuncID(itFunc->second.nFuncID,m_pLib->m_FuncLib).c_str())
			,(DWORD_PTR)itFunc->second.nFuncID);
	}


	if(m_nCurFuncPos!=-1)
	{
		m_FuncListCtl.SetCurSel(m_nCurFuncPos);
		OnLbnSelchangeListFunc();
	}

	return TRUE;
}

BOOL CAutoStructDataDesignDlg::LoadToUi()
{
	//m_pLib->Load();
	UpDataUi(TRUE);

	return TRUE;
}
/*
BOOL CAutoStructDataDesignDlg::SaveToXml()
{
	m_pLib->SaveToXml();

	//SerObjectToAnsiXmlFile(_tagTestParam,Param,szFile);
	return TRUE;
}*/

void CAutoStructDataDesignDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}

void CAutoStructDataDesignDlg::OnBnClickedAddfunc()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(m_szFuncName.GetLength()==0)
	{
		AfxMessageBox(_T("�������ƷǷ�"));
	}else if(m_pLib->m_FuncLib.m_FuncLib.find(tstring((LPCTSTR)m_szFuncName))!=m_pLib->m_FuncLib.m_FuncLib.end())
	{
		AfxMessageBox(_T("�����Ѷ���,��ı�����"));
	}else
	{
		_tagFuncDef func;
		func.szFuncDesc=(LPCTSTR)m_szFuncDesc;
		func.szFuncName=(LPCTSTR)m_szFuncName;
		func.szFuncType=(LPCTSTR)m_szFuncType;
		m_pLib->AddNewFunc(func);
		m_pLib->m_bNewUpdataExp=TRUE;
		m_nCurFuncPos=-1;
		//LoadToUi();
		UpDataUi(TRUE);
	}
}

void CAutoStructDataDesignDlg::OnBnClickedDelfunc()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(m_pLib->DelFuncByName(tstring((LPCTSTR)m_szFuncName)))
	{
		m_nCurFuncPos=-1;
		m_pLib->m_bNewUpdataExp=TRUE;
		UpDataUi(TRUE);
	}else
	{
		AfxMessageBox(_T("ɾ�����ʽʧ��"));
	}
}

void CAutoStructDataDesignDlg::OnBnClickedAddprrarm()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(m_nCurFuncPos==-1)
	{
		AfxMessageBox(_T("��ѡ��һ������"));
		return;
	}
	unsigned int nFunID=(unsigned int)m_FuncListCtl.GetItemData(m_nCurFuncPos);

	if(m_pLib->FuncParamIsReDef(nFunID,tstring((LPCTSTR)m_szParamName)))
	{
			AfxMessageBox(_T("�������ظ�,����д����������"));
			return;
	}

	_tagParamDef Param;
	Param.szParamDesc=(LPCTSTR)m_szParamDesc;
	Param.szParamName=(LPCTSTR)m_szParamName;
	Param.szDefaultParam=(LPCTSTR)m_szDefaultParamVal;
	m_pLib->AddNewFuncParam(nFunID,Param);
	//m_pLib->m_FuncLib.m_FuncLib[szFunName].m_ParamDefArray.push_back(Param);
	m_pLib->m_bNewUpdataExp=TRUE;
	//m_FuncPrarmDefListCtl.

	int Pos=m_FuncPrarmDefListCtl.InsertItem(m_FuncPrarmDefListCtl.GetItemCount(),m_szParamName);
	m_FuncPrarmDefListCtl.SetItemText(Pos,1,m_szDefaultParamVal);
	m_FuncPrarmDefListCtl.SetItemText(Pos,2,m_szParamDesc);
	UpDataUi(TRUE);


	//if(m_FuncLib.m_FuncLib.find(szFunName)!=)
}

void CAutoStructDataDesignDlg::OnBnClickedDelparam()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	POSITION   pos   =   m_FuncPrarmDefListCtl.GetFirstSelectedItemPosition();   
	if  (pos   ==   NULL)   
	{
		AfxMessageBox(_T("��ѡ��Ҫɾ���Ĳ���"));
		return;
	}
	else   
	{  
		while(pos)   
		{   
			int   nItem   =   m_FuncPrarmDefListCtl.GetNextSelectedItem(pos);   
			tstring szParamName=(LPCTSTR)m_FuncPrarmDefListCtl.GetItemText(nItem,0);
			IDType nFuncID=(unsigned int )m_FuncListCtl.GetItemData(m_nCurFuncPos);

			m_pLib->DelFuncParam(nFuncID,szParamName);

			/*vector<_tagParamDef> & ParamArray=m_pLib->m_FuncLib.m_FuncLib[szCurFunName].m_ParamDefArray;
			vector<_tagParamDef>::iterator itPar=ParamArray.begin();
			for(;itPar!=ParamArray.end();itPar++)
			{
				if(itPar->szParamName==szParamName)
				{
					ParamArray.erase(itPar);
					break;
				}
			}*/
			m_pLib->m_bNewUpdataExp=TRUE;

			//   you   could   do   your   own   processing   on   nItem   here   
		}   
		UpDataUi(TRUE);
	}  
}

void CAutoStructDataDesignDlg::OnBnClickedUpdataParamdef()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	
	POSITION   pos   =   m_FuncPrarmDefListCtl.GetFirstSelectedItemPosition();   
	if  (pos   ==   NULL)   
	{
		AfxMessageBox(_T("��ѡ��Ҫ�޸ĵĲ���"));
		return;
	}else
	{
		int   nItem   =   m_FuncPrarmDefListCtl.GetNextSelectedItem(pos);   
		tstring szParamName=(LPCTSTR)m_FuncPrarmDefListCtl.GetItemText(nItem,0);
		IDType nFuncID=(unsigned int)m_FuncListCtl.GetItemData(m_nCurFuncPos);
		IDType nParamID=(unsigned int)m_FuncPrarmDefListCtl.GetItemData(nItem);
		_tagParamDef Param;
		if(m_pLib->GetFuncParamByParName(nFuncID,szParamName,Param))
		{
			Param.szDefaultParam=(LPCTSTR)m_szDefaultParamVal;
			Param.szParamName=(LPCTSTR)m_szParamName;
			Param.szParamDesc=(LPCTSTR)m_szParamDesc;

			if(m_pLib->UpdataFuncParam(nFuncID,Param))
			{

				m_pLib->m_bNewUpdataExp=TRUE;
				m_FuncPrarmDefListCtl.SetItemText(nItem,0,m_szParamName);
				m_FuncPrarmDefListCtl.SetItemText(nItem,1,m_szDefaultParamVal);
				m_FuncPrarmDefListCtl.SetItemText(nItem,2,m_szParamDesc);
				UpDataUi(TRUE);
			}else
			{
				AfxMessageBox(_T("���ʽ�����ض���"));
			}
		}else
		{
			AfxMessageBox(_T("���ܱ��ʽ�����д���"));
		}
		
		/*vector<_tagParamDef> & ParamArray=m_pLib->m_FuncLib.m_FuncLib[szCurFunName].m_ParamDefArray;
		vector<_tagParamDef>::iterator itPar=ParamArray.begin();
		for(;itPar!=ParamArray.end();itPar++)
		{
			if(itPar->szParamName==szParamName)
			{
				//itPar->szParamName=(LPCTSTR)m_szParamName;
				itPar->szParamDesc=(LPCTSTR)m_szParamDesc;
				itPar->szDefaultParam=(LPCTSTR)m_szDefaultParamVal;
				break;
			}
		}*/
		
	}
	
}


void CAutoStructDataDesignDlg::OnLbnSelchangeListFunc()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_nCurFuncPos=m_FuncListCtl.GetCurSel();
	if(m_nCurFuncPos==-1) return;
	IDType nFuncID=(unsigned int)m_FuncListCtl.GetItemData(m_nCurFuncPos);
	m_szFuncName=m_pLib->GetFuncNameByFuncID(nFuncID).c_str();
	m_szFuncDesc=m_pLib->m_FuncLib.m_FuncLib[tstring((LPCTSTR)m_szFuncName)].szFuncDesc.c_str();
	m_szFuncType=m_pLib->m_FuncLib.m_FuncLib[tstring((LPCTSTR)m_szFuncName)].szFuncType.c_str();
	//m_FuncTypeComboCtl.SelectString(0,szFuncType.c_str());
	UpdateData(FALSE);

	m_FuncPrarmDefListCtl.DeleteAllItems();
	for(unsigned int i=0;i<m_pLib->m_FuncLib.m_FuncLib[tstring((LPCTSTR)m_szFuncName)].m_ParamDefArray.size();i++)
	{
		int nItem=m_FuncPrarmDefListCtl.InsertItem(m_FuncPrarmDefListCtl.GetItemCount(),
			m_pLib->m_FuncLib.m_FuncLib[tstring((LPCTSTR)m_szFuncName)].m_ParamDefArray[i].szParamName.c_str());
		m_FuncPrarmDefListCtl.SetItemText(nItem,2,m_pLib->m_FuncLib.m_FuncLib[tstring((LPCTSTR)m_szFuncName)].m_ParamDefArray[i].szParamDesc.c_str());
		m_FuncPrarmDefListCtl.SetItemText(nItem,1,m_pLib->m_FuncLib.m_FuncLib[tstring((LPCTSTR)m_szFuncName)].m_ParamDefArray[i].szDefaultParam.c_str());
		m_FuncPrarmDefListCtl.SetItemData(nItem,m_pLib->m_FuncLib.m_FuncLib[tstring((LPCTSTR)m_szFuncName)].m_ParamDefArray[i].nParamID);
	}
}



void CAutoStructDataDesignDlg::OnLvnItemchangedListPrarmdef(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	if(m_nCurFuncPos==-1) return;
	//tstring szFuncName=(LPCTSTR)m_FuncListCtl.GetItemDataPtr(m_nCurFuncPos);

	m_szParamName=m_FuncPrarmDefListCtl.GetItemText(pNMLV->iItem,0);
	m_szDefaultParamVal=m_FuncPrarmDefListCtl.GetItemText(pNMLV->iItem,1);
	m_szParamDesc=m_FuncPrarmDefListCtl.GetItemText(pNMLV->iItem,2);
	UpdateData(FALSE);

	/*
	for(unsigned int i=0;i<m_FuncLib.m_FuncLib[tstring((LPCTSTR)szFuncName)].m_ParamDefArray.size();i++)
	{
		if(m_FuncLib.m_FuncLib[tstring((LPCTSTR)szFuncName)].m_ParamDefArray[i].szParamName
			==tstring(m_FuncPrarmDefListCtl.GetItemText(pNMLV->iItem,0)))
		{
			m_szParamName=tstring(m_FuncPrarmDefListCtl.GetItemText(pNMLV->iItem,0));
			m_szDefaultParamVal=tstring(m_FuncPrarmDefListCtl.GetItemText(pNMLV->iItem,1));
			m_szParamDesc=tstring(m_FuncPrarmDefListCtl.GetItemText(pNMLV->iItem,2));
			UpdateData(FALSE);
			break;
		}
		
	}
	*/
}


void CAutoStructDataDesignDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialog::OnActivate(nState, pWndOther, bMinimized);
	//OutputDebugString(_T("CAutoStructDataDesignDlg::OnActivate"));
	// TODO: �ڴ˴������Ϣ����������
}

void CAutoStructDataDesignDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	//OutputDebugString(_T("CAutoStructDataDesignDlg::OnSize"));
	// TODO: �ڴ˴������Ϣ����������
}

void CAutoStructDataDesignDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	//OutputDebugString(_T("CAutoStructDataDesignDlg::OnShowWindow"));
	// TODO: �ڴ˴������Ϣ����������
	UpDataUi(TRUE);
}

void CAutoStructDataDesignDlg::OnBnClickedEditfunc()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	IDType nFuncID=(unsigned int)m_FuncListCtl.GetItemData(m_nCurFuncPos);
	if(nFuncID)
	{
		_tagFuncDef Func;
		
		if(m_pLib->GetFuncByFuncID(nFuncID,Func))
		{
			Func.szFuncName=m_szFuncName;
			Func.szFuncType=m_szFuncType;
			Func.szFuncDesc=m_szFuncDesc;
			if(m_pLib->UpDataFuncByID(nFuncID,Func))
			{
				m_pLib->m_bNewUpdataExp=TRUE;
				UpDataUi(TRUE);
			}else
			{
				AfxMessageBox(_T("���ʽ�����ض���"));
			}
			
		}
	}
}

/*
void CAutoStructDataDesignDlg::OnBnClickedCheckM()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
*/