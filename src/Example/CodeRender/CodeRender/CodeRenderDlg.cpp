
// CodeRenderDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CodeRender.h"
#include "CodeRenderDlg.h"
#include "Tokenizer.h"
#include <string>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CCodeRenderDlg �Ի���




CCodeRenderDlg::CCodeRenderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCodeRenderDlg::IDD, pParent)
	, m_szCode(_T("����"))
	, m_szLog(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCodeRenderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_szCode);
	DDX_Text(pDX, IDC_EDIT1, m_szLog);
}

BEGIN_MESSAGE_MAP(CCodeRenderDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_TEST, &CCodeRenderDlg::OnBnClickedTest)
END_MESSAGE_MAP()


// CCodeRenderDlg ��Ϣ�������

BOOL CCodeRenderDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CCodeRenderDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCodeRenderDlg::OnPaint()
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
HCURSOR CCodeRenderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//#include "ObjExpression.h"
#include "MakeCodeObj.h" 

/*
class asdf
{
public:
	asdf();
	int sasddas(int basdf,char asd);
	int sasdsf34ddas435(int basdf435,char asd67,string sad);
	~asdf();
protected:
	
private:
};*/
//template
char * g_hpprule[]=
{
	"NULL_FALSE<NULL_FALSE>=NULL_FALSE",
	"NULL_TRUE<NULL_TRUE>=NULL_TRUE",

	"ROOT<������>=������",
	"���ŷָ���<���ŷָ���>=WORD(,)",
	"������<������>=������1|������2|������3",
	"������1<������>=NULL<��ģ������>|��ͷ�ؼ���+����+NULL<�̳����>+��<����������ʼ,������������,��������>",
	"����������ʼ<����������ʼ>=WORD({)",
	"������������<������������>=WORD(})+WORD(;)",
	"��ͷ�ؼ���<��ͷ�ؼ���>=WORD(class)",
	"������2<������>=NULL_FALSE",
	"������3<������>=NULL_FALSE",

	"��ģ������<��ģ������>=��ģ������1|��ģ������2",
	"��ģ������1<��ģ������>=ģ��ؼ���+��<ģ��������������ʼ,ģ����������������,ģ������������>",
	"ģ��ؼ���<ģ��ؼ���>=WORD(template)",
	"��ģ������2<��ģ������>=NULL_FALSE",
	"ģ��������������ʼ<ģ��������������ʼ>=word(<)",
	"ģ����������������<ģ����������������>=word(>)",
	"ģ������������<ģ������������>=N<ģ��������������,���ŷָ���>",
	"ģ��������������<ģ��������������>=WORD(typename)+ģ�������",
	"ģ�������<ģ�������>=����",

	"��ͷ�ؼ���<��ͷ�ؼ���>=word(class)",
	"����<����>=����",

	"�̳����<�̳����>=WORD(:)+N<�̳�������,���ŷָ���>",
	"�̳�������<�̳�������>=word(public)+����+word(,)",
	"�̳�����������<�̳�����������>=word(public)+����",

	"����������ʼ<����������ʼ>=word({)",
	"������������<������������>=word(})+word(;)",

	"��������<��������>=N<������������,NULL_TRUE>",
	"������������1<������������>=word(public)+word(:)",
	"������������2<������������>=word(protected)+word(:)",
	"������������3<������������>=word(private)+word(:)",
	"������������4<������������>=������������1|������������2|������������3",

	"������������5<������������>=��������|��������",
	"������������6<������������>=��������|����������",
	"������������7<������������>=NULL_FALSE",
	"������������8<������������>=NULL_FALSE",

	"������������<������������>=������������1|������������2|������������3|������������4|������������5|������������6|������������7|������������8",

	"��������<��������>=NULL_FALSE",
	"��������<��������>=��������1|�޷��ز�����������",
	"��������1<��������>=���������ͱ�+NULL<��������Լ��>+������+��<������������ʼ,��������������,��������������>|�ղ�������",
	"�ղ�������<������������>=WORD(()+WORD())+WORD(;)",
	"�޷��ز�����������<��������>=NULL<��������Լ��>|������+�ղ�������",


	"���������ͱ�<���������ͱ�>=����",
	"��������Լ��<��������Լ��>=word(_stdcall)|word(__stdcall)",
	"������<������>=����",
	"������������ʼ<������������ʼ>=WORD(()",
	"��������������<��������������>=WORD())+WORD(;)",
	"��������������<������������>=N<����������������,���ŷָ���>",
	"����������������<����������������>=��������+��������",
	"��������<��������>=����",
	"��������<��������>=����",

	"��������<��������>=��������+��������+word(;)",
	"��������<��������>=����",
	"��������<��������>=����",

	"����������<����������>=N<����������Ԫ��������,���ŷָ���>+word(;)",
	"����������Ԫ��������<����������Ԫ��������>=��������+��������",
	NULL
};



//template < typename a, typename b >
/*
template < typename a, typename b >
class codetest
{
public:
	int codetestd(int ss,char * pss);
protected:
	
private:
};*/

class asdsa
{
public:
	int as;
	virtual int sasdasdas(unsigned int s, char * p)
	{
		return 1;
	}
	virtual int sasdasdas1(unsigned int s, char * p)
	{
		return 2;
	}
	virtual int sasdasdas2(unsigned int s, char * p)
	{
		return 22;
	}
protected:
	
private:
};

class asdsa1
{
public:
	int as;
	virtual int sasdasdas(unsigned int s, char * p)
	{
		return 4;
	}
	virtual int sasdasdas1(unsigned int s, char * p)
	{
		return 5;
	}
	virtual int sasdasdas2(unsigned int s, char * p)
	{
		return 33;
	}
protected:

private:
};

class asdsa2 :public asdsa1
{
public:
	int as;
	virtual int sasdasdas(unsigned int s, char * p)
	{
		return 44;
	}
	virtual int sasdasdas1(unsigned int s, char * p)
	{
		return 54;
	}
	virtual int sasdasdas2(unsigned int s, char * p)
	{
		return 334;
	}
protected:

private:
};


class asd1:public asdsa,public asdsa1,public asdsa2
{
public:
	int as1;
	virtual int sasdasdas(unsigned int s, char * p)
	{
		return 5;
	}
	virtual int sasdasdas1(unsigned int s, char * p)
	{
		return 6;
	}
protected:
	
private:
};
#define GETPARENTCLASS(ParType,subType,subpoint) (ParType *)(subpoint-(subType *)((ParType *) 0))

void CCodeRenderDlg::OnBnClickedTest()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	asdsa p11;
	asd1 asd;
	asd1 * p=(asd1 *)&p11;
	p->sasdasdas1(1,0);
	asdsa* p1=(asdsa*)&asd;
	p1->sasdasdas1(1,0);
	asd.sasdasdas1(1,0);
	
	p1->sasdasdas2(1,0);
	//asd.sasdasdas2(1,0);
	
	asdsa1* p2=(asdsa1*)&asd;
	p2->sasdasdas2(1,0);
	//asd.sasdasdas2(1,0);

	CObjExpression obj;
	UpdateData(TRUE);
	m_szLog.Empty();
	
	obj.AddExpression("d:\\1.txt","d:\\");
	//obj.AddExpression(g_hpprule);
	//obj.ParseDestString(m_szCode.GetBuffer(m_szCode.GetLength()));
	CMakeCodeObj Make;
	Make.BindObjExpressionMgr(&obj);
	//OutputDebugStringA(codetree.c_str());

	vector<string> code;
	Make.MakeCode(code);


	for (unsigned int i=0;i<code.size();i++)
	{

		OutputDebugStringA(code[i].c_str());
	}
	
	/*
	CTokenizer tag(string(m_szCode.GetBuffer(m_szCode.GetLength())));
		int nType=tag.NextToken();
		char szMsg[512];
		for(;nType!=TT_EOF;)
		{
			switch (nType)
			{
			case TT_EOF:
				sprintf(szMsg,"��������");
				m_szLog+=szMsg;
				OutputDebugStringA(szMsg);
				UpdateData(FALSE);
				return;
			case TT_WORD:
				sprintf(szMsg,"������ :%s\r\n",tag.GetStrValue().c_str());
				m_szLog+=szMsg;
				break;
			case TT_INTEGER:
				sprintf(szMsg,"���� :%d\r\n",tag.GetIntNumValue());
				m_szLog+=szMsg;
				break;
			case TT_REAL:
				sprintf(szMsg,"������ :%f\r\n",tag.GetDoubleNumValue());
				m_szLog+=szMsg;
				break;
			case TT_STRING:
				sprintf(szMsg,"�ַ����� :%s\r\n",tag.GetStrValue().c_str());
				m_szLog+=szMsg;
				break;
			case TT_CHAR:
				sprintf(szMsg,"�ַ��� :%s\r\n",tag.GetStrValue().c_str());
				m_szLog+=szMsg;
				break;
			case TT_EOL:
				sprintf(szMsg,"���� \r\n");
				m_szLog+=szMsg;
				break;
			default:
				sprintf(szMsg,"δ֪���� %s\r\n",tag.GetStrValue().c_str());
				m_szLog+=szMsg;
				break;
			}
			nType=tag.NextToken();
		}*/
	
	UpdateData(FALSE);
}
