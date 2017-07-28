
// DlgProxy.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AutoStructDataDesign.h"
#include "DlgProxy.h"
#include "AutoStructDataDesignDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAutoStructDataDesignDlgAutoProxy

IMPLEMENT_DYNCREATE(CAutoStructDataDesignDlgAutoProxy, CCmdTarget)

CAutoStructDataDesignDlgAutoProxy::CAutoStructDataDesignDlgAutoProxy()
{
	EnableAutomation();
	
	// ΪʹӦ�ó������Զ��������ڻ״̬ʱһֱ���� 
	//	���У����캯������ AfxOleLockApp��
	AfxOleLockApp();

	// ͨ��Ӧ�ó����������ָ��
	//  �����ʶԻ������ô�����ڲ�ָ��
	//  ָ��Ի��򣬲����öԻ���ĺ���ָ��ָ��
	//  �ô���
	ASSERT_VALID(AfxGetApp()->m_pMainWnd);
	if (AfxGetApp()->m_pMainWnd)
	{
		ASSERT_KINDOF(CAutoStructDataDesignDlg, AfxGetApp()->m_pMainWnd);
		if (AfxGetApp()->m_pMainWnd->IsKindOf(RUNTIME_CLASS(CAutoStructDataDesignDlg)))
		{
			m_pDialog = reinterpret_cast<CAutoStructDataDesignDlg*>(AfxGetApp()->m_pMainWnd);
			m_pDialog->m_pAutoProxy = this;
		}
	}
}

CAutoStructDataDesignDlgAutoProxy::~CAutoStructDataDesignDlgAutoProxy()
{
	// Ϊ������ OLE �Զ����������ж������ֹӦ�ó���
	// 	������������ AfxOleUnlockApp��
	//  ���������������⣬�⻹���������Ի���
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CAutoStructDataDesignDlgAutoProxy::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease�����ཫ�Զ�
	// ɾ���ö����ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CAutoStructDataDesignDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CAutoStructDataDesignDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// ע��: ��������˶� IID_IAutoStructDataDesign ��֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡��� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {63A4B192-BE39-4A4A-8715-08899BC5F756}
static const IID IID_IAutoStructDataDesign =
{ 0x63A4B192, 0xBE39, 0x4A4A, { 0x87, 0x15, 0x8, 0x89, 0x9B, 0xC5, 0xF7, 0x56 } };

BEGIN_INTERFACE_MAP(CAutoStructDataDesignDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CAutoStructDataDesignDlgAutoProxy, IID_IAutoStructDataDesign, Dispatch)
END_INTERFACE_MAP()

// IMPLEMENT_OLECREATE2 ���ڴ���Ŀ�� StdAfx.h �ж���
// {33378D5A-5F55-4986-9FC9-704A62084595}
IMPLEMENT_OLECREATE2(CAutoStructDataDesignDlgAutoProxy, "AutoStructDataDesign.Application", 0x33378d5a, 0x5f55, 0x4986, 0x9f, 0xc9, 0x70, 0x4a, 0x62, 0x8, 0x45, 0x95)


// CAutoStructDataDesignDlgAutoProxy ��Ϣ�������
