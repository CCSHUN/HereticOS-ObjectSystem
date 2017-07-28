// TestUserStandardUniteNewDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "WhiteboxTestingPlatform.h"
#include "TestUserStandardUniteNewDlg.h"


// CTestUserStandardUniteNewDlg 对话框

IMPLEMENT_DYNAMIC(CTestUserStandardUniteNewDlg, CDialog)

CTestUserStandardUniteNewDlg::CTestUserStandardUniteNewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestUserStandardUniteNewDlg::IDD, pParent)
	, m_szErrorNum (_T(""))
{
	//UpDataBing(FALSE);
}

CTestUserStandardUniteNewDlg::~CTestUserStandardUniteNewDlg()
{
}

BOOL CTestUserStandardUniteNewDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN ||pMsg->wParam == VK_ESCAPE))     
	{     
		return ::TranslateMessage(pMsg);     
	}    

	return CDialog::PreTranslateMessage(pMsg);
}

void CTestUserStandardUniteNewDlg::UpDataBing(BOOL bToSecond)
{
	if(bToSecond)
	{
		UpdateData(TRUE);
		m_CurDataSet.szDesc=m_szDesc;
		m_CurDataSet.szErrorNum=m_szErrorNum;
		m_CurDataSet.szErrorSuggest=m_szErrorSuggest;
		m_CurDataSet.szErrorType=m_szErrorType;
		m_CurDataSet.szErrorWarning=m_szErrorWarning;
	}else
	{
		m_szErrorNum=m_CurDataSet.szErrorNum.c_str();
		m_szDesc=m_CurDataSet.szDesc.c_str();
		m_szErrorSuggest=m_CurDataSet.szErrorSuggest.c_str();
		m_szErrorType=m_CurDataSet.szErrorType.c_str();
		m_szErrorWarning=m_CurDataSet.szErrorWarning.c_str();
		UpdateData(FALSE);
	}

}
void CTestUserStandardUniteNewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ERROR_NUM, m_szErrorNum);
	DDX_Text(pDX, IDC_ERROR_DESC, m_szDesc);
	DDX_Text(pDX, IDC_ERROR_SUG, m_szErrorSuggest);
	DDX_CBString(pDX, IDC_COMBO_ERROR_TYPE, m_szErrorType);
	DDX_CBString(pDX, IDC_COMBO_ERROR_CLASS1, m_szErrorWarning);
	DDX_Control(pDX, IDC_COMBO_ERROR_TYPE, m_ErrorTypeCtl);
	DDX_Control(pDX, IDC_COMBO_ERROR_CLASS1, m_ErrorClassCtl);
	DDX_Control(pDX, IDC_LIST_NOUSING, m_NoUsingList);
	DDX_Control(pDX, IDC_LIST_USING, m_UsingList);
}


BEGIN_MESSAGE_MAP(CTestUserStandardUniteNewDlg, CDialog)
	ON_BN_CLICKED(IDC_ADD_THIRD_TO_USINGLIST, &CTestUserStandardUniteNewDlg::OnBnClickedAddThirdToUsinglist)
	ON_BN_CLICKED(IDC_CANCEL, &CTestUserStandardUniteNewDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_OK, &CTestUserStandardUniteNewDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_REMOVE, &CTestUserStandardUniteNewDlg::OnBnClickedRemove)
END_MESSAGE_MAP()


// CTestUserStandardUniteNewDlg 消息处理程序

void CTestUserStandardUniteNewDlg::OnBnClickedAddThirdToUsinglist()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(FALSE);
	if(m_NoUsingList.GetSelectedCount()<1)
	{
		AfxMessageBox(_T("请选定没有引用的第三方标准"));
		return;
	}
	POSITION pos=m_NoUsingList.GetFirstSelectedItemPosition();
	int item=m_NoUsingList.GetNextSelectedItem(pos);
	map<tstring,_tagThirdStandardSet,less<tstring> >::iterator itLib;
	itLib=m_pShareData->m_ThirdStandardLib.m_Data.libmap.find(tstring((LPCTSTR)m_NoUsingList.GetItemText(item,0)));
	if(itLib!=m_pShareData->m_ThirdStandardLib.m_Data.libmap.end())
	{
		//itLib->second.szUniteStandardErrorNum=m_szErrorNum;
		int Pos=m_UsingList.InsertItem(m_NoUsingList.GetItemCount(),itLib->second.szThirdStandardErrorNum.c_str());
		//m_UniteStandardList.SetItemText(Pos,0,it->second.id);
		//m_ThirdStandardList.SetItemText(Pos,0,it->second.szThirdStandardErrorNum.c_str());
		//m_NoUsingList.SetItemText(Pos,1,itLib->second.szUniteStandardErrorNum.c_str());

		//m_NoUsingList.SetItemText(Pos,2,itLib->second.is_dealwith==0?_T("关注"):_T("不关注"));
		m_UsingList.SetItemText(Pos,1,itLib->second.is_manual_check==0?_T("不需要复查"):_T("需要复查"));
		m_UsingList.SetItemText(Pos,2,itLib->second.ToolType.c_str());
		m_UsingList.SetItemText(Pos,3,itLib->second.szThirdStandardErrorDesc.c_str());
		m_NoUsingList.DeleteItem(item);
	}
	
}

void CTestUserStandardUniteNewDlg::OnBnClickedRemove()
{
	// TODO: 在此添加控件通知处理程序代码
	
	if(m_UsingList.GetSelectedCount()<1)
	{
		AfxMessageBox(_T("请选定没有引用的第三方标准"));
		return;
	}
	POSITION pos=m_UsingList.GetFirstSelectedItemPosition();
	int item=m_UsingList.GetNextSelectedItem(pos);
	map<tstring,_tagThirdStandardSet,less<tstring> >::iterator itLib;
	itLib=m_pShareData->m_ThirdStandardLib.m_Data.libmap.find(tstring((LPCTSTR)m_UsingList.GetItemText(item,0)));
	if(itLib!=m_pShareData->m_ThirdStandardLib.m_Data.libmap.end())
	{
		//itLib->second.szUniteStandardErrorNum=m_szErrorNum;
		int Pos=m_NoUsingList.InsertItem(m_NoUsingList.GetItemCount(),itLib->second.szThirdStandardErrorNum.c_str());
		//m_UniteStandardList.SetItemText(Pos,0,it->second.id);
		//m_ThirdStandardList.SetItemText(Pos,0,it->second.szThirdStandardErrorNum.c_str());
		//m_NoUsingList.SetItemText(Pos,1,itLib->second.szUniteStandardErrorNum.c_str());

		//m_NoUsingList.SetItemText(Pos,2,itLib->second.is_dealwith==0?_T("关注"):_T("不关注"));
		m_NoUsingList.SetItemText(Pos,1,itLib->second.is_manual_check==0?_T("不需要复查"):_T("需要复查"));
		m_NoUsingList.SetItemText(Pos,2,itLib->second.ToolType.c_str());
		m_NoUsingList.SetItemText(Pos,3,itLib->second.szThirdStandardErrorDesc.c_str());
		m_UsingList.DeleteItem(item);
	}
}


void CTestUserStandardUniteNewDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}

void CTestUserStandardUniteNewDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	
	//UpdateData(TRUE);
	UpDataBing(TRUE);
	if(m_pShareData->m_MachineCheckStandardLib.m_Data.libmap.find(m_CurDataSet.szErrorNum)==m_pShareData->m_MachineCheckStandardLib.m_Data.libmap.end())
	{
		//
		for (int iitem=0;iitem<m_UsingList.GetItemCount();iitem++)
		{
			
			map<tstring,_tagThirdStandardSet,less<tstring> >::iterator itLib;
			tstring szThirdNum=(LPCTSTR)m_UsingList.GetItemText(iitem,0);
			itLib=m_pShareData->m_ThirdStandardLib.m_Data.libmap.find(szThirdNum);
			if(itLib!=m_pShareData->m_ThirdStandardLib.m_Data.libmap.end())
			{
				itLib->second.szUniteStandardErrorNum=m_szErrorNum;
				m_pShareData->m_bThirdLibWrited=TRUE;
				m_pShareData->m_bIsHopeUpdataThirdUi=TRUE;
			}
			//iitem=m_UsingList.GetNextItem(iitem,TVGN_NEXT);

		}

		m_pShareData->m_MachineCheckStandardLib.m_Data.libmap[m_CurDataSet.szErrorNum]=m_CurDataSet;
		m_pShareData->m_bUniteLibWrited=TRUE;
		CDialog::OnOK();
	}else
	{
		AfxMessageBox(_T("新建的标准已经存在请重新输入"));
	}

}
BOOL CTestUserStandardUniteNewDlg::OnInitDialog()
{
	BOOL bRet=CDialog::OnInitDialog();

	map<tstring,_tagMachineCheckStandardTypeSet,less<tstring> >::iterator itTypeLib=m_pShareData->m_MachineCheckStandardTypeLib.m_Data.libmap.begin();
	for(;itTypeLib!=m_pShareData->m_MachineCheckStandardTypeLib.m_Data.libmap.end();itTypeLib++)
	{
		m_ErrorTypeCtl.AddString(itTypeLib->second.name.c_str());
	}
	m_ErrorTypeCtl.SetCurSel(0);

	for(unsigned int i=0;i<m_pShareData->m_ErrorWarningArray.m_Data.WarningArray.size();i++)
	{
		m_ErrorClassCtl.AddString(m_pShareData->m_ErrorWarningArray.m_Data.WarningArray[i].szErrorWarningName.c_str());
	}
	m_ErrorClassCtl.SetCurSel(0);

	m_NoUsingList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_NoUsingList.InsertColumn(0,_T("错误号"));
	m_NoUsingList.InsertColumn(1,_T("是否复查"));
	m_NoUsingList.InsertColumn(2,_T("检查工具"));
	m_NoUsingList.InsertColumn(3,_T("描述"));

	m_NoUsingList.SetColumnWidth(0, 100);
	m_NoUsingList.SetColumnWidth(1, 100);
	m_NoUsingList.SetColumnWidth(2, 100);
	m_NoUsingList.SetColumnWidth(3, 400);

	m_UsingList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_UsingList.InsertColumn(0,_T("错误号"));
	m_UsingList.InsertColumn(1,_T("是否复查"));
	m_UsingList.InsertColumn(2,_T("检查工具"));
	m_UsingList.InsertColumn(3,_T("描述"));

	m_UsingList.SetColumnWidth(0, 100);
	m_UsingList.SetColumnWidth(1, 100);
	m_UsingList.SetColumnWidth(2, 100);
	m_UsingList.SetColumnWidth(3, 400);

	map<tstring,_tagThirdStandardSet,less<tstring> >::iterator itLib=m_pShareData->m_ThirdStandardLib.m_Data.libmap.begin();
	for(;itLib!=m_pShareData->m_ThirdStandardLib.m_Data.libmap.end();itLib++)
	{
		if(itLib->second.szUniteStandardErrorNum==tstring(_T("未关联")))
		{
			int Pos=m_NoUsingList.InsertItem(m_NoUsingList.GetItemCount(),itLib->second.szThirdStandardErrorNum.c_str());
			//m_UniteStandardList.SetItemText(Pos,0,it->second.id);
			//m_ThirdStandardList.SetItemText(Pos,0,it->second.szThirdStandardErrorNum.c_str());
			//m_NoUsingList.SetItemText(Pos,1,itLib->second.szUniteStandardErrorNum.c_str());

			//m_NoUsingList.SetItemText(Pos,2,itLib->second.is_dealwith==0?_T("关注"):_T("不关注"));
			m_NoUsingList.SetItemText(Pos,1,itLib->second.is_manual_check==0?_T("不需要复查"):_T("需要复查"));
			m_NoUsingList.SetItemText(Pos,2,itLib->second.ToolType.c_str());
			m_NoUsingList.SetItemText(Pos,3,itLib->second.szThirdStandardErrorDesc.c_str());
		}
	}
	return bRet;
	
}
