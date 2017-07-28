
// CodeRenderDlg.cpp : 实现文件
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


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CCodeRenderDlg 对话框




CCodeRenderDlg::CCodeRenderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCodeRenderDlg::IDD, pParent)
	, m_szCode(_T("妈妈"))
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


// CCodeRenderDlg 消息处理程序

BOOL CCodeRenderDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCodeRenderDlg::OnPaint()
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

	"ROOT<类声明>=类声明",
	"逗号分隔符<逗号分隔符>=WORD(,)",
	"类声明<类声明>=类声明1|类声明2|类声明3",
	"类声明1<类声明>=NULL<类模板声明>|类头关键词+类名+NULL<继承类表>+包<类声明包开始,类声明包结束,类声明体>",
	"类声明包开始<类声明包开始>=WORD({)",
	"类声明包结束<类声明包结束>=WORD(})+WORD(;)",
	"类头关键词<类头关键词>=WORD(class)",
	"类声明2<类声明>=NULL_FALSE",
	"类声明3<类声明>=NULL_FALSE",

	"类模板声明<类模板声明>=类模板声明1|类模板声明2",
	"类模板声明1<类模板声明>=模板关键词+包<模板声明参数包开始,模板声明参数包结束,模板声明参数表>",
	"模板关键词<模板关键词>=WORD(template)",
	"类模板声明2<类模板声明>=NULL_FALSE",
	"模板声明参数包开始<模板声明参数包开始>=word(<)",
	"模板声明参数包结束<模板声明参数包结束>=word(>)",
	"模板声明参数表<模板声明参数表>=N<模板声明参数声明,逗号分隔符>",
	"模板声明参数声明<模板声明参数声明>=WORD(typename)+模板参数名",
	"模板参数名<模板参数名>=词型",

	"类头关键字<类头关键字>=word(class)",
	"类名<类名>=词型",

	"继承类表<继承类表>=WORD(:)+N<继承类表参数,逗号分隔符>",
	"继承类表参数<继承类表参数>=word(public)+词型+word(,)",
	"继承类表参数结束<继承类表参数结束>=word(public)+词型",

	"类声明包开始<类声明包开始>=word({)",
	"类声明包结束<类声明包结束>=word(})+word(;)",

	"类声明体<类声明体>=N<类声明体内容,NULL_TRUE>",
	"类声明体内容1<类声明体内容>=word(public)+word(:)",
	"类声明体内容2<类声明体内容>=word(protected)+word(:)",
	"类声明体内容3<类声明体内容>=word(private)+word(:)",
	"类声明体内容4<类声明体内容>=类声明体内容1|类声明体内容2|类声明体内容3",

	"类声明体内容5<类声明体内容>=函数声明|函数定义",
	"类声明体内容6<类声明体内容>=变量声明|变量声明表",
	"类声明体内容7<类声明体内容>=NULL_FALSE",
	"类声明体内容8<类声明体内容>=NULL_FALSE",

	"类声明体内容<类声明体内容>=类声明体内容1|类声明体内容2|类声明体内容3|类声明体内容4|类声明体内容5|类声明体内容6|类声明体内容7|类声明体内容8",

	"函数定义<函数定义>=NULL_FALSE",
	"函数声明<函数声明>=函数声明1|无返回参数函数声明",
	"函数声明1<函数声明>=函数返回型别+NULL<函数调用约定>+函数名+包<函数声明包开始,函数声明包结束,函数声明参数表>|空参数声明",
	"空参数声明<函数参数声明>=WORD(()+WORD())+WORD(;)",
	"无返回参数函数声明<函数声明>=NULL<函数调用约定>|函数名+空参数声明",


	"函数返回型别<函数返回型别>=词型",
	"函数调用约定<函数调用约定>=word(_stdcall)|word(__stdcall)",
	"函数名<函数名>=词型",
	"函数声明包开始<函数声明包开始>=WORD(()",
	"函数声明包结束<函数声明包结束>=WORD())+WORD(;)",
	"函数声明参数表<函数参数声明>=N<函数声明参数声明,逗号分隔符>",
	"函数声明参数声明<函数声明参数声明>=参数类型+参数名称",
	"参数类型<参数类型>=词型",
	"参数名称<参数名称>=词型",

	"变量声明<变量声明>=变量类型+变量名称+word(;)",
	"变量类型<变量类型>=词型",
	"变量名称<变量声明>=词型",

	"变量声明表<变量声明表>=N<变量声明表单元变量声明,逗号分隔符>+word(;)",
	"变量声明表单元变量声明<变量声明表单元变量声明>=变量类型+变量名称",
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
	// TODO: 在此添加控件通知处理程序代码

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
				sprintf(szMsg,"解析结束");
				m_szLog+=szMsg;
				OutputDebugStringA(szMsg);
				UpdateData(FALSE);
				return;
			case TT_WORD:
				sprintf(szMsg,"名称型 :%s\r\n",tag.GetStrValue().c_str());
				m_szLog+=szMsg;
				break;
			case TT_INTEGER:
				sprintf(szMsg,"整型 :%d\r\n",tag.GetIntNumValue());
				m_szLog+=szMsg;
				break;
			case TT_REAL:
				sprintf(szMsg,"浮点型 :%f\r\n",tag.GetDoubleNumValue());
				m_szLog+=szMsg;
				break;
			case TT_STRING:
				sprintf(szMsg,"字符串型 :%s\r\n",tag.GetStrValue().c_str());
				m_szLog+=szMsg;
				break;
			case TT_CHAR:
				sprintf(szMsg,"字符型 :%s\r\n",tag.GetStrValue().c_str());
				m_szLog+=szMsg;
				break;
			case TT_EOL:
				sprintf(szMsg,"换行 \r\n");
				m_szLog+=szMsg;
				break;
			default:
				sprintf(szMsg,"未知类型 %s\r\n",tag.GetStrValue().c_str());
				m_szLog+=szMsg;
				break;
			}
			nType=tag.NextToken();
		}*/
	
	UpdateData(FALSE);
}
