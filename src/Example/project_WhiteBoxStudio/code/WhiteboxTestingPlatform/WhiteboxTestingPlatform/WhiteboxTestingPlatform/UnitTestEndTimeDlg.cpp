// UnitTestEndTimeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WhiteboxTestingPlatform.h"
#include "UnitTestEndTimeDlg.h"


// CUnitTestEndTimeDlg �Ի���

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


// CUnitTestEndTimeDlg ��Ϣ�������

void CUnitTestEndTimeDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(FALSE);
	OnOK();
}
