// AutoStructDesignView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WhiteboxTestingPlatform.h"
#include "AutoStructDesignView.h"


// CAutoStructDesignView

IMPLEMENT_DYNCREATE(CAutoStructDesignView, CFormView)

CAutoStructDesignView::CAutoStructDesignView()
	: CFormView(CAutoStructDesignView::IDD)
	, m_szTemplateName(_T(""))
	, m_szTemplateDesc(_T(""))
	, m_PrarmDesc(_T(""))
	, m_PrarmName(_T(""))
{

}

CAutoStructDesignView::~CAutoStructDesignView()
{
}

void CAutoStructDesignView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TYPE_TYPE, m_TypeLibTree);
	DDX_Control(pDX, IDC_TEMPLATE_LIST, m_TemplateListCtl);
	DDX_Text(pDX, IDC_PARAMNAME, m_szTemplateName);
	DDX_Text(pDX, IDC_DESC, m_szTemplateDesc);
	DDX_Control(pDX, IDC_PRARM_LIST, m_PrarmListCtl);
	DDX_Control(pDX, IDC_COMBO_PRARMTYPE, m_PrarmTypeCombo);
	DDX_Text(pDX, IDC_DESC2, m_PrarmDesc);
	DDX_Text(pDX, IDC_PARAMNAME2, m_PrarmName);
}

BEGIN_MESSAGE_MAP(CAutoStructDesignView, CFormView)
	ON_BN_CLICKED(IDC_AddToTypeLib, &CAutoStructDesignView::OnBnClickedAddtotypelib)
	ON_BN_CLICKED(IDC_AddTemplate, &CAutoStructDesignView::OnBnClickedAddtemplate)
	ON_BN_CLICKED(IDC_DelTemplate, &CAutoStructDesignView::OnBnClickedDeltemplate)
	ON_BN_CLICKED(IDC_UpData, &CAutoStructDesignView::OnBnClickedUpdata)
	ON_BN_CLICKED(IDC_AddTemplate3, &CAutoStructDesignView::OnBnClickedAddtemplate3)
	ON_BN_CLICKED(IDC_DelTemplate2, &CAutoStructDesignView::OnBnClickedDeltemplate2)
	ON_BN_CLICKED(IDC_UpData2, &CAutoStructDesignView::OnBnClickedUpdata2)
	ON_BN_CLICKED(IDC_SAVE, &CAutoStructDesignView::OnBnClickedSave)
	//ON_CBN_SELCHANGE(IDC_COMBO_PRARMTYPE2, &CAutoStructDesignView::OnCbnSelchangeComboPrarmtype2)
END_MESSAGE_MAP()


// CAutoStructDesignView ���

#ifdef _DEBUG
void CAutoStructDesignView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAutoStructDesignView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAutoStructDesignView ��Ϣ�������
void CAutoStructDesignView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	((CChildFrame *)GetParentFrame())->m_ProjectIndex.pViewInterface=this;
}
void CAutoStructDesignView::OnBnClickedAddtotypelib()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CAutoStructDesignView::OnBnClickedAddtemplate()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CAutoStructDesignView::OnBnClickedDeltemplate()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CAutoStructDesignView::OnBnClickedUpdata()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CAutoStructDesignView::OnBnClickedAddtemplate3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CAutoStructDesignView::OnBnClickedDeltemplate2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CAutoStructDesignView::OnBnClickedUpdata2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CAutoStructDesignView::OnBnClickedSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

