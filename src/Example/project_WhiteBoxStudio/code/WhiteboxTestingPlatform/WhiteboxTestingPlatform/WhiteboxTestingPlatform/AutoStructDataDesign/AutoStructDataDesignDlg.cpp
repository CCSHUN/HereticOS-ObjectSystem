
// AutoStructDataDesignDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AutoStructDataDesign.h"
#include "AutoStructDataDesignDlg.h"
#include "DlgProxy.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框



// CAutoStructDataDesignDlg 对话框




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
	// 如果该对话框有自动化代理，则
	//  将此代理指向该对话框的后向指针设置为 NULL，以便
	//  此代理知道该对话框已被删除。
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


// CAutoStructDataDesignDlg 消息处理程序

BOOL CAutoStructDataDesignDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_SHOWNORMAL);
	*/

	// TODO: 在此添加额外的初始化代码

	m_FuncPrarmDefListCtl.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_FuncPrarmDefListCtl.InsertColumn(0,_T("参数名称"));
	m_FuncPrarmDefListCtl.InsertColumn(1,_T("参数默认值"));
	m_FuncPrarmDefListCtl.InsertColumn(2,_T("参数说明"));

	m_FuncPrarmDefListCtl.SetColumnWidth(0, 80);
	m_FuncPrarmDefListCtl.SetColumnWidth(1, 120);
	m_FuncPrarmDefListCtl.SetColumnWidth(2, 320);


	m_FuncTypeComboCtl.AddString(_T("驱动用例"));
	m_FuncTypeComboCtl.AddString(_T("场景用例"));
	m_FuncTypeComboCtl.AddString(_T("期望评估"));
	m_FuncTypeComboCtl.AddString(_T("系统配置"));
	m_FuncTypeComboCtl.SelectString(0,_T("驱动用例"));
	LoadToUi();
	

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAutoStructDataDesignDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CAutoStructDataDesignDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 当用户关闭 UI 时，如果控制器仍保持着它的某个
//  对象，则自动化服务器不应退出。这些
//  消息处理程序确保如下情形: 如果代理仍在使用，
//  则将隐藏 UI；但是在关闭对话框时，
//  对话框仍然会保留在那里。

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
	// 如果代理对象仍保留在那里，则自动化
	//  控制器仍会保持此应用程序。
	//  使对话框保留在那里，但将其 UI 隐藏起来。
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
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}

void CAutoStructDataDesignDlg::OnBnClickedAddfunc()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(m_szFuncName.GetLength()==0)
	{
		AfxMessageBox(_T("过程名称非法"));
	}else if(m_pLib->m_FuncLib.m_FuncLib.find(tstring((LPCTSTR)m_szFuncName))!=m_pLib->m_FuncLib.m_FuncLib.end())
	{
		AfxMessageBox(_T("过程已定义,请改变名称"));
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
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(m_pLib->DelFuncByName(tstring((LPCTSTR)m_szFuncName)))
	{
		m_nCurFuncPos=-1;
		m_pLib->m_bNewUpdataExp=TRUE;
		UpDataUi(TRUE);
	}else
	{
		AfxMessageBox(_T("删除表达式失败"));
	}
}

void CAutoStructDataDesignDlg::OnBnClickedAddprrarm()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(m_nCurFuncPos==-1)
	{
		AfxMessageBox(_T("请选定一个过程"));
		return;
	}
	unsigned int nFunID=(unsigned int)m_FuncListCtl.GetItemData(m_nCurFuncPos);

	if(m_pLib->FuncParamIsReDef(nFunID,tstring((LPCTSTR)m_szParamName)))
	{
			AfxMessageBox(_T("参数名重复,请填写其他参数名"));
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
	// TODO: 在此添加控件通知处理程序代码
	POSITION   pos   =   m_FuncPrarmDefListCtl.GetFirstSelectedItemPosition();   
	if  (pos   ==   NULL)   
	{
		AfxMessageBox(_T("请选择要删除的参数"));
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
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	
	POSITION   pos   =   m_FuncPrarmDefListCtl.GetFirstSelectedItemPosition();   
	if  (pos   ==   NULL)   
	{
		AfxMessageBox(_T("请选择要修改的参数"));
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
				AfxMessageBox(_T("表达式名称重定义"));
			}
		}else
		{
			AfxMessageBox(_T("功能表达式参数有错误"));
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
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此处添加消息处理程序代码
}

void CAutoStructDataDesignDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	//OutputDebugString(_T("CAutoStructDataDesignDlg::OnSize"));
	// TODO: 在此处添加消息处理程序代码
}

void CAutoStructDataDesignDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	//OutputDebugString(_T("CAutoStructDataDesignDlg::OnShowWindow"));
	// TODO: 在此处添加消息处理程序代码
	UpDataUi(TRUE);
}

void CAutoStructDataDesignDlg::OnBnClickedEditfunc()
{
	// TODO: 在此添加控件通知处理程序代码
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
				AfxMessageBox(_T("表达式名称重定义"));
			}
			
		}
	}
}

/*
void CAutoStructDataDesignDlg::OnBnClickedCheckM()
{
	// TODO: 在此添加控件通知处理程序代码
}
*/