// CodeViewDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "WhiteboxTestingPlatform.h"
#include "CodeViewDlg.h"
#include "TemplateTool.h"

// CCodeViewDlg 对话框

IMPLEMENT_DYNAMIC(CCodeViewDlg, CDialog)

CCodeViewDlg::CCodeViewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCodeViewDlg::IDD, pParent)
{
	m_bNeedUpdata=FALSE;
	m_iDataIndex=-1;
}

CCodeViewDlg::~CCodeViewDlg()
{
}

void CCodeViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCodeViewDlg, CDialog)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

BOOL CCodeViewDlg::OnInitDialog()
{
	BOOL bRet=CDialog::OnInitDialog();
	bRet=m_CodeHtmlView.CreateFromStatic(IDC_STATIC,this);
	m_CodeHtmlView.init(this);
	return bRet;
}


void CCodeViewDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	m_bNeedUpdata=bShow;
	__super::OnShowWindow( bShow,  nStatus);
	UpdataUi();

}

void CCodeViewDlg::UpdataUi()
{
	if(m_bNeedUpdata==FALSE ||m_iDataIndex==-1) return;
	tstring szCode=_T("BEGIN_MESSAGE_MAP(CCodeViewDlg, CDialog)\r\nEND_MESSAGE_MAP()\r\n\r\nBOOL CCodeViewDlg::OnInitDialog()")
	_T("{\r\n\tBOOL bRet=CDialog::OnInitDialog();\r\n\tbRet<=m_CodeHtmlView.CreateFromStatic(IDC_STATIC,this);")
	_T("\r\n\tm_CodeHtmlView.init(this);\r\n\treturn bRet;\r\n}\r\n");
	//tstring szFile=_T("e:/svn/project/project_WhiteBoxStudio/code/WhiteboxTestingPlatform/WhiteboxTestingPlatform/WhiteboxTestingPlatform/DevUserReportView.cpp");
	if((m_pShareData==NULL)
		||(m_pShareData->m_Report.m_Data.items.size()<=m_iDataIndex))
	{
		return;
	}

	TCHAR szCodeFile[512];TCHAR szCodeLine[128];
	tstring szFile=m_pShareData->GetSubProjectCodePath().c_str();
	if(szFile.length()==0) return;

	if (szFile.at(szFile.length()-1) != '\\')
	{
		szFile += '\\';
	}

	TCHAR *pszCodePos=(TCHAR *)m_pShareData->m_Report.m_Data.items[m_iDataIndex].szErrorCodePosition.c_str();
	TCHAR * pLinePos=strrchr_t(pszCodePos,'(');
	if(pLinePos==NULL)
	{
		return;
	}
	strcpy_t(szCodeFile,pszCodePos);
	szCodeFile[pLinePos-pszCodePos]=0;
	szFile+=szCodeFile;
	pLinePos++;
	strcpy_t(szCodeLine,pLinePos);
	szCodeLine[strlen_t(szCodeLine)-1]=0;
	

	CString szLine=szCodeLine;

	map<tstring,CString,less<tstring> >::iterator itCode=m_CodeMap.find(szFile);
	if(itCode!=m_CodeMap.end())
	{
		m_CodeHtmlView.ShowCode(itCode->second,szLine);
	}else
	{
		
		if(CTemplateTool::FileToString(szFile,
			szCode))
		{
			
			m_CodeHtmlView.ShowCode(CString(szCode.c_str()),szLine);
			m_CodeMap[szFile]=CString(szCode.c_str());
		}else
		{
			WndLog(_T("代码定位器"),_T("打开本地代码文件失败,请配置本地代码路径 CodePath=%s"),
				szFile.c_str());
		}
	}
	

}

BOOL CCodeViewDlg::PreTranslateMessage(MSG* pMsg)
{
	switch(pMsg->message)
	{
	case WM_KEYDOWN:
		if(pMsg->wParam==VK_RETURN)
		{
			/*UpdateData(TRUE);
			GotoAddr(tstring(m_szAddress.GetBuffer(0)));
			return TRUE;*/
		}
		return GetDlgItem(IDC_STATIC)->PreTranslateMessage(pMsg);
		//pMsg->wParam;
	default:
		return CDialog::PreTranslateMessage(pMsg);

	}
	return CDialog::PreTranslateMessage(pMsg);
}

// CCodeViewDlg 消息处理程序
