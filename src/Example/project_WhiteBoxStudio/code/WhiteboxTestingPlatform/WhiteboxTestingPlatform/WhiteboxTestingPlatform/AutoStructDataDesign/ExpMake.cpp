// ExpMake.cpp : 实现文件
//

#include "stdafx.h"
#include "AutoStructDataDesign.h"
#include "ExpMake.h"


// CExpMake 对话框

IMPLEMENT_DYNAMIC(CExpMake, CDialog)

CExpMake::CExpMake(CWnd* pParent /*=NULL*/)
	: CDialog(CExpMake::IDD, pParent)
	, m_szParamVal(_T(""))
	, m_szRunfmt(_T("%sClientSimulate.exe"))
	, m_szExpDesc(_T(""))
{
	m_nCurExpPos=-1;
}

CExpMake::~CExpMake()
{
}

void CExpMake::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_EXP, m_ExpListCtl);
	DDX_Control(pDX, IDC_LIST_PRARM2, m_ExpParamValList);
	DDX_Text(pDX, IDC_EDIT_PARAMNAME3, m_szParamVal);
	DDX_Text(pDX, IDC_EDIT1, m_szRunfmt);
	DDX_Text(pDX, IDC_STATIC_DESC, m_szExpDesc);
}


BEGIN_MESSAGE_MAP(CExpMake, CDialog)

	ON_BN_CLICKED(IDC_ADDCASEEXP, &CExpMake::OnBnClickedAddcaseexp)
	ON_BN_CLICKED(IDC_DELCASEEXP, &CExpMake::OnBnClickedDelcaseexp)
	ON_BN_CLICKED(IDC_UPDATA_PARAM2, &CExpMake::OnBnClickedUpdataParam2)
	ON_BN_CLICKED(IDC_RunSel, &CExpMake::OnBnClickedRunsel)
	ON_BN_CLICKED(IDC_RunAll, &CExpMake::OnBnClickedRunall)

	ON_LBN_SELCHANGE(IDC_LIST_EXP, &CExpMake::OnLbnSelchangeListExp)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_PRARM2, &CExpMake::OnLvnItemchangedListPrarm2)
	ON_WM_SHOWWINDOW()
	ON_LBN_DBLCLK(IDC_LIST_EXP, &CExpMake::OnLbnDblclkListExp)
END_MESSAGE_MAP()



BOOL CExpMake::OnInitDialog()
{
	CDialog::OnInitDialog();



	m_ExpParamValList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_ExpParamValList.InsertColumn(0,_T("表达式名"));
	m_ExpParamValList.InsertColumn(1,_T("参数名"));
	m_ExpParamValList.InsertColumn(2,_T("参数值"));
	m_ExpParamValList.InsertColumn(3,_T("默认参数值"));
	m_ExpParamValList.InsertColumn(4,_T("参数说明"));

	m_ExpParamValList.SetColumnWidth(0, 80);
	m_ExpParamValList.SetColumnWidth(1, 80);
	m_ExpParamValList.SetColumnWidth(2, 160);
	m_ExpParamValList.SetColumnWidth(3, 160);
	m_ExpParamValList.SetColumnWidth(4, 160);


	UpDataUi(TRUE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
// CExpMake 消息处理程序

BOOL CExpMake::UpDataUi(BOOL ToUi)
{
	m_ExpListCtl.ResetContent();

	m_ExpParamValList.DeleteAllItems();
	m_pLib->UpdataLib();

	map<tstring,_tagExp,less<tstring>>::iterator itExp=m_pLib->m_ExpLib.m_ExpLib.begin();

	for(;itExp!=m_pLib->m_ExpLib.m_ExpLib.end();itExp++)
	{
		m_ExpListCtl.SetItemData(m_ExpListCtl.AddString(m_pLib->GetExpDefString(itExp->second,m_pLib->m_FuncLib).c_str())
			,(DWORD_PTR)itExp->second.nExpID);
	}

	if(m_nCurExpPos!=-1)
	{
		m_ExpListCtl.SetCurSel(m_nCurExpPos);
		OnLbnSelchangeListExp();
	}

	return TRUE;
}

#include "UseCaseExpMakeDlg.h"

void CExpMake::OnBnClickedAddcaseexp()
{
	// TODO: 在此添加控件通知处理程序代码
	CUseCaseExpMakeDlg dlg;
	dlg.m_szTitle=_T("添加用例");
	dlg.m_pFuncLib=&m_pLib->m_FuncLib;
	if (dlg.DoModal()==IDOK)
	{
		_tagExp tExp;
		tExp.szExpName=dlg.m_szUseCaseName;
		tExp.szExpDesc=dlg.m_szExpDesc;
		tExp.FuncIDArray.push_back(m_pLib->GetFuncIDByName(tstring((LPCTSTR)dlg.m_szDriverExp)));
		tExp.FuncIDArray.push_back(m_pLib->GetFuncIDByName(tstring((LPCTSTR)dlg.m_szClientExp)));
		tExp.FuncIDArray.push_back(m_pLib->GetFuncIDByName(tstring((LPCTSTR)dlg.m_szEvaluateExp)));
		tExp.FuncIDArray.push_back(m_pLib->GetFuncIDByName(tstring((LPCTSTR)dlg.m_szSystemConfig)));

		vector<_tagParamDef> DefaultVal;

		if(m_pLib->GetDefaultVal(tstring((LPCTSTR)dlg.m_szDriverExp),DefaultVal,m_pLib->m_FuncLib))
		{
			tExp.m_ExpValMap[m_pLib->GetFuncIDByName(tstring((LPCTSTR)dlg.m_szDriverExp))]=DefaultVal;
		}

		DefaultVal.clear();
		if(m_pLib->GetDefaultVal(tstring((LPCTSTR)dlg.m_szClientExp),DefaultVal,m_pLib->m_FuncLib))
		{
			tExp.m_ExpValMap[m_pLib->GetFuncIDByName(tstring((LPCTSTR)dlg.m_szClientExp))]=DefaultVal;
		}

		DefaultVal.clear();
		if(m_pLib->GetDefaultVal(tstring((LPCTSTR)dlg.m_szEvaluateExp),DefaultVal,m_pLib->m_FuncLib))
		{
			tExp.m_ExpValMap[m_pLib->GetFuncIDByName(tstring((LPCTSTR)dlg.m_szEvaluateExp))]=DefaultVal;
		}

		DefaultVal.clear();
		if(m_pLib->GetDefaultVal(tstring((LPCTSTR)dlg.m_szSystemConfig),DefaultVal,m_pLib->m_FuncLib))
		{
			tExp.m_ExpValMap[m_pLib->GetFuncIDByName(tstring((LPCTSTR)dlg.m_szSystemConfig))]=DefaultVal;
		}

		//m_pLib->m_ExpLib.m_ExpLib[tExp.szExpName]=tExp;
		if(m_pLib->AddNewExp(tExp))
		{
			m_pLib->m_bNewUpdataExp=TRUE;
			UpDataUi(TRUE);
		}else
		{
			AfxMessageBox(_T("用例名重复，请重建用例"));
		}
		
	}
}

void CExpMake::OnBnClickedDelcaseexp()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(m_nCurExpPos==-1)
	{
		AfxMessageBox(_T("请选定一个用例"));
		return;
	}else
	{
		unsigned int nExpID=(unsigned int)m_ExpListCtl.GetItemData(m_nCurExpPos);
		m_pLib->DelExpByID(nExpID);
		m_pLib->m_bNewUpdataExp=TRUE;
		m_nCurExpPos=-1;
		UpDataUi(TRUE);
	}
}

//修改参数值
void CExpMake::OnBnClickedUpdataParam2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(m_szParamVal.GetLength()==0)
	{
		AfxMessageBox(_T("请填写一个有效参数值"));
		return;
	}
	if(m_ExpParamValList.GetSelectedCount()<1)
	{
		AfxMessageBox(_T("请选定要修改的用例参数"));
		return;
	}
	POSITION pos=m_ExpParamValList.GetFirstSelectedItemPosition();
	int item=m_ExpParamValList.GetNextSelectedItem(pos);

	unsigned int nExpID=(unsigned int )m_ExpListCtl.GetItemData(m_nCurExpPos);
	tstring szExpName=m_pLib->GetExpNameByID(nExpID);
	tstring szFuncName=m_ExpParamValList.GetItemText(item,0);
	tstring szParName=m_ExpParamValList.GetItemText(item,1);

	IDType nFuncid=m_pLib->GetFuncIDByName(szFuncName);
	_tagExp exp;
	if(m_pLib->GetExp(nExpID,exp))
	{
		vector<_tagParamDef> & ParArray=exp.m_ExpValMap[nFuncid];
		for(unsigned int i=0;i<ParArray.size();i++)
		{
			if(ParArray[i].szParamName==szParName)
			{
				ParArray[i].szLastEditParamVal=(LPCTSTR)m_szParamVal;
				m_ExpParamValList.SetItemText(item,2,(LPCTSTR)m_szParamVal);
				m_pLib->m_bNewUpdataExp=TRUE;
				m_pLib->UpDataExpPar(nExpID,nFuncid,ParArray[i]);
				break;
			}
		}
	}
	

}

void CExpMake::OnBnClickedRunsel()
{
	// TODO: 在此添加控件通知处理程序代码


	UpdateData(TRUE);
	if(m_nCurExpPos==-1)
	{
		AfxMessageBox(_T("请选定一个用例"));
		return;
	}else
	{
		
		unsigned int nExpID=(unsigned int)m_ExpListCtl.GetItemData(m_nCurExpPos);
		_tagExp exp;
		m_pLib->GetExp(nExpID,exp);
		_tagTestParam Par;
		if(m_pLib->GetTestParamFromExp(exp.szExpName,Par,m_pLib->m_ExpLib))
		{
			TCHAR szFile[MAX_PATH];
			::GetModuleFileName(NULL,szFile,MAX_PATH);
			TCHAR * pFileName=strrchr_t(szFile,'\\');
			pFileName++;
			pFileName[0]=0;
			tstring szPath=szFile;
			strcpy_t(pFileName,exp.szExpName.c_str());

			SerObjectToAnsiXmlFile(_tagTestParam,Par,tstring(szFile));
			TCHAR szCmd[2048];
			sprintf_s_t(szCmd,1023,(LPCTSTR)m_szRunfmt,szPath.c_str());
			OutputDebugString(szCmd);
			//::WinExec((LPCSTR)szCmd,SW_SHOW);
			::ShellExecute(NULL,_T("open"),szCmd,szFile,NULL,SW_SHOWNORMAL);
		}
	}

	//SerObjectToAnsiXmlFile(_)
}
#include "ExecAllTestUseCase.h"
void CExpMake::OnBnClickedRunall()
{
	// TODO: 在此添加控件通知处理程序代码
	//m_pLib->SaveToXml();
	ExecAllTestUseCase(this);
}

void CExpMake::OnLbnSelchangeListExp()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nCurExpPos=m_ExpListCtl.GetCurSel();
	if(m_nCurExpPos==-1) return;

	//tstring szExpName=(LPCTSTR)m_ExpListCtl.GetItemDataPtr(m_nCurExpPos);
	m_ExpParamValList.DeleteAllItems();
	unsigned int nExpID=(unsigned int)m_ExpListCtl.GetItemData(m_nCurExpPos);
	_tagExp tExp;
	m_pLib->GetExp(nExpID,tExp);

	//_tagExp & tExp=m_pLib->m_ExpLib.m_ExpLib[szExpName];
	for(unsigned int i=0;i<tExp.FuncIDArray.size();i++)
	{
		vector<_tagParamDef> & tPar=tExp.m_ExpValMap[tExp.FuncIDArray[i]];
		for(unsigned int j=0;j<tPar.size();j++)
		{
			int nItem=m_ExpParamValList.InsertItem(m_ExpParamValList.GetItemCount(),
				m_pLib->GetFuncNameByFuncID(tExp.FuncIDArray[i]).c_str());
			m_ExpParamValList.SetItemText(nItem,1,tPar[j].szParamName.c_str());
			if(tPar[j].szLastEditParamVal.length())
			{
				m_ExpParamValList.SetItemText(nItem,2,tPar[j].szLastEditParamVal.c_str());
			}else
			{
				m_ExpParamValList.SetItemText(nItem,2,tPar[j].szDefaultParam.c_str());
			}
			m_ExpParamValList.SetItemText(nItem,3,tPar[j].szDefaultParam.c_str());
			m_ExpParamValList.SetItemText(nItem,4,tPar[j].szParamDesc.c_str());
			//m_ExpParamValList.SetItemData(nItem,i);
		}

	}

}

void CExpMake::OnLvnItemchangedListPrarm2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	if(m_nCurExpPos==-1) return;
	//tstring szExpName=(LPCTSTR)m_ExpListCtl.GetItemDataPtr(m_nCurExpPos);


	m_szParamVal=m_ExpParamValList.GetItemText(pNMLV->iItem,2);
	UpdateData(FALSE);
	/*
	_tagExp & tExp=m_ExpLib.m_ExpLib[szExpName];
	for(unsigned int i=0;i<tExp.szFuncArray.size();i++)
	{
		if(tExp.szFuncArray[i]
			==tstring(m_ExpParamValList.GetItemText(pNMLV->iItem,0)))
		{
			m_szParamVal=tstring(m_ExpParamValList.GetItemText(pNMLV->iItem,2));
			UpdateData(FALSE);
			break;
		}

	}
	*/
}

void CExpMake::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	UpDataUi(TRUE);
	// TODO: 在此处添加消息处理程序代码
}

void CExpMake::OnLbnDblclkListExp()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nCurExpPos=m_ExpListCtl.GetCurSel();
	if(m_nCurExpPos==-1) return;

	unsigned int nExpID=(unsigned int)m_ExpListCtl.GetItemData(m_nCurExpPos);
	tstring szExpName=m_pLib->GetExpNameByID(nExpID);
	CUseCaseExpMakeDlg dlg;
	dlg.m_szTitle=_T("修改用例");
	dlg.m_szUseCaseName=szExpName.c_str();
	
	dlg.m_pFuncLib=&m_pLib->m_FuncLib;
	_tagExp exp;
	if(m_pLib->GetExp(nExpID,exp))
	{
		dlg.m_szExpDesc=exp.szExpDesc.c_str();
		for(unsigned int n=0;n<exp.FuncIDArray.size();n++)
		{
			tstring szFuncName=m_pLib->GetFuncNameByFuncID(exp.FuncIDArray[n]);
			_tagFuncDef Func;
			if(m_pLib->GetFuncByFuncID(exp.FuncIDArray[n],Func))
			{
				if(tstring(_T("驱动用例"))==Func.szFuncType)
				{
					dlg.m_szDriverExp=szFuncName.c_str();
				}else if(tstring(_T("场景用例"))==Func.szFuncType)
				{
					dlg.m_szClientExp=szFuncName.c_str();
				}else if(tstring(_T("期望评估"))==Func.szFuncType)
				{
					dlg.m_szEvaluateExp=szFuncName.c_str();
				}else if(tstring(_T("系统配置"))==Func.szFuncType)
				{
					dlg.m_szSystemConfig=szFuncName.c_str();
				}
			}
			
		}

		if (dlg.DoModal()==IDOK)
		{
			exp.szExpName=dlg.m_szUseCaseName;
			exp.szExpDesc=dlg.m_szExpDesc;
			BOOL bFixOK=TRUE;
			if(m_pLib->FixExpFunc(tstring((LPCTSTR)dlg.m_szDriverExp),tstring(_T("驱动用例")),exp)==FALSE)
			{
				bFixOK=FALSE;
			}else if(m_pLib->FixExpFunc(tstring((LPCTSTR)dlg.m_szClientExp),tstring(_T("场景用例")),exp)==FALSE)
			{
				bFixOK=FALSE;
			}else if(m_pLib->FixExpFunc(tstring((LPCTSTR)dlg.m_szEvaluateExp),tstring(_T("期望评估")),exp)==FALSE)
			{
				bFixOK=FALSE;
			}else if(m_pLib->FixExpFunc(tstring((LPCTSTR)dlg.m_szSystemConfig),tstring(_T("系统配置")),exp)==FALSE)
			{
				bFixOK=FALSE;
			}

			if(bFixOK==FALSE)
			{
				AfxMessageBox(_T("表达式混合失败"));
			}
			if(m_pLib->UpDataExp(nExpID,exp))
			{
				UpDataUi(TRUE);
			}else
			{
				AfxMessageBox(_T("修改表达式失败"));
			}
		}

	}
	
}
