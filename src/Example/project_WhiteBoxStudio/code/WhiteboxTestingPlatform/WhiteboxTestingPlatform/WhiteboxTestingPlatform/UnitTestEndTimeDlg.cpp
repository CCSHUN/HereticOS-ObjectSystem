// UnitTestEndTimeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "WhiteboxTestingPlatform.h"
#include "UnitTestEndTimeDlg.h"


// CUnitTestEndTimeDlg 对话框

IMPLEMENT_DYNAMIC(CUnitTestEndTimeDlg, CDialog)

CUnitTestEndTimeDlg::CUnitTestEndTimeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUnitTestEndTimeDlg::IDD, pParent)
	, m_szEndTime(_T(""))
{

}

CUnitTestEndTimeDlg::~CUnitTestEndTimeDlg()
{
}

void CUnitTestEndTimeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_szEndTime);
}


BEGIN_MESSAGE_MAP(CUnitTestEndTimeDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CUnitTestEndTimeDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CUnitTestEndTimeDlg 消息处理程序

void CUnitTestEndTimeDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(FALSE);
	OnOK();
}
