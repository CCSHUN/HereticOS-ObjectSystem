// FloatWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "WhiteboxTestingPlatform.h"
#include "FloatWnd.h"
#include "resource.h"
#include <math.h>
#include "ImageEx.h"

// CFloatWnd 对话框

IMPLEMENT_DYNAMIC(CFloatWnd, CDialog)

CFloatWnd::CFloatWnd(CWnd* pParent /*=NULL*/)
	: CDialog(CFloatWnd::IDD, pParent)
{
	m_sPicFile = "";
	m_pPic = NULL;
	m_pStm = NULL;
	m_hGlobal = NULL;

	m_image = NULL;
	m_colorBk = RGB(20, 148, 20);
}

CFloatWnd::~CFloatWnd()
{
	if(m_pPic)
	{
		m_pPic->Release();
		m_pPic = NULL;

		if(m_pStm)
		{
			m_pStm->Release();
			m_pStm = NULL;
		}

		if(m_hGlobal)
		{
			::GlobalFree(m_hGlobal);
			m_hGlobal = NULL;
		}
	}

	delete m_image;
}

void CFloatWnd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_TIP2, m_staticTip);
}


BEGIN_MESSAGE_MAP(CFloatWnd, CDialog)
	ON_WM_NCHITTEST()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CFloatWnd 消息处理程序

BOOL CFloatWnd::OnInitDialog()
{
	CDialog::OnInitDialog();

	//CBitmap m_Bitmap;
	//HBITMAP hBitmap = m_Logo.GetBitmap();
	//ASSERT(hBitmap);

	//m_Bitmap.Attach(hBitmap);
	//BITMAP bmp;
	//m_Bitmap.GetBitmap(&bmp);

	//int nX = bmp.bmWidth;
	//int nY = bmp.bmHeight;

	//MoveWindow(0,0,nX,nY);	
	//m_Logo.MoveWindow(0,0,nX,nY);
	//CenterWindow();
	::SetWindowPos(m_hWnd,HWND_TOPMOST,1000,0,0,0,/*SWP_NOMOVE | */SWP_NOSIZE);

	//m_Bitmap.Detach();
	
	//加入WS_EX_LAYERED扩展属性
	//SetWindowLong(m_hWnd,GWL_EXSTYLE,GetWindowLong(this->GetSafeHwnd(),GWL_EXSTYLE)^0x80000);
	
	//OnUpdateTransparent(255);

	m_image = new ImageEx(theApp.GetAppPath() + L"LockGIF\\locked.gif");
	m_image->InitAnimation(m_hWnd, CPoint(3, 3));

	LOGFONT LogFont;
	GetFont()->GetLogFont(&LogFont);//
	//LogFont.lfHeight+=LogFont.lfHeight;
	//LogFont.lfWidth+=LogFont.lfWidth;
	m_font.CreateFontIndirect(&LogFont);
	//GetDlgItem(IDC_STATIC_HEAD)->SetFont(&m_font);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

LRESULT CFloatWnd::OnNcHitTest(CPoint point)
{
	//UINT nHitTest = CDialog::OnNcHitTest(point);

	//if (nHitTest == HTCLIENT && ::GetAsyncKeyState(MK_LBUTTON) < 0) 
	//	nHitTest = HTCAPTION;		// 如果鼠标左键按下，GetAsyncKeyState函数的返回值小于0

	//	

	//return (LRESULT)nHitTest;

	return 0;
}
void CFloatWnd::OnUpdateTransparent(int iTransparent)
{
	HINSTANCE hInst = LoadLibrary(_T("User32.DLL"));
	if(hInst)
	{
		typedef BOOL (WINAPI *SLWA)(HWND,COLORREF,BYTE,DWORD);
		SLWA pFun = NULL;
		//取得SetLayeredWindowAttributes函数指针 
		pFun = (SLWA)GetProcAddress(hInst,"SetLayeredWindowAttributes");
		if(pFun)
		{
			pFun(m_hWnd,0,iTransparent,2);
		}
		FreeLibrary(hInst); 
	}
}

BOOL CFloatWnd::DrawPicture(CDC* pDC, CRect rect)
{
	if (m_sPicFile.IsEmpty() || m_pPic == NULL)
	{
		return FALSE;
	}

	OLE_XSIZE_HIMETRIC   hmWidth;       
	OLE_YSIZE_HIMETRIC   hmHeight;       
	m_pPic->get_Width(&hmWidth);       
	m_pPic->get_Height(&hmHeight);       

	m_pPic->Render(*pDC, 0, 0, (DWORD)rect.Width(), (DWORD)rect.Height(),
			                0, hmHeight, hmWidth, -hmHeight, NULL);     

	return TRUE;
}

void CFloatWnd::SetPicture(const CString &sPicFile) 
{ 
	m_sPicFile = sPicFile; 

	if(m_pPic)
	{
		m_pPic->Release();
		m_pPic = NULL;

		if(m_pStm)
		{
			m_pStm->Release();
			m_pStm = NULL;
		}

		if(m_hGlobal)
		{
			::GlobalFree(m_hGlobal);
			m_hGlobal = NULL;
		}
	}

	if (m_sPicFile.IsEmpty())
	{
		return;
	}

	CFileStatus   fstatus;       
	CFile   file;       
	LONG   cb;    
	if(file.Open(m_sPicFile, CFile::modeRead))       
	{       
		file.GetStatus(m_sPicFile, fstatus);
		cb = (LONG)fstatus.m_size;
		if (cb <= 0)
		{
			file.Close();
			return;
		}

		m_hGlobal = GlobalAlloc(GMEM_MOVEABLE, cb);       
		LPVOID pvData = NULL;       
		if(m_hGlobal != NULL)       
		{       
			if((pvData = GlobalLock(m_hGlobal)) != NULL)       
			{       
				file.Read(pvData, cb);       
				GlobalUnlock(m_hGlobal);       
				CreateStreamOnHGlobal(m_hGlobal, TRUE, &m_pStm);    
				if (m_pStm == NULL)
				{
					file.Close();
					::GlobalFree(m_hGlobal);
					m_hGlobal = NULL;
					return;
				}
			}   
			else
			{
				file.Close();
				::GlobalFree(m_hGlobal);
				m_hGlobal = NULL;
				return;
			}
		}     
		else
		{
			file.Close();
			return;
		}
	}  
	else
	{
		DWORD dw = GetLastError();
		return;
	}

	if(FAILED(OleLoadPicture(m_pStm, (LONG)fstatus.m_size, TRUE, IID_IPicture, (LPVOID*)&m_pPic)))     
	{     
		file.Close();
		m_pStm->Release();
		::GlobalFree(m_hGlobal);
		m_pPic = NULL;
		m_pStm = NULL;
		m_hGlobal = NULL;
	}
	else
	{
		file.Close();
	}

	return;	
}
void CFloatWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	//CRect rect;
	//GetWindowRect(rect);
	//DrawPicture(&dc, rect);
	//DrawGIF(&dc);

	//if   (IsIconic()){
	//	;
	//}else{   
		CRect   rect;   
		GetClientRect(rect);  

		CFont *pFont = (CFont *)dc.SelectObject(&m_font);

		dc.FillSolidRect(rect,m_colorBk);   //设置为绿色背景   
		rect.left += 30;
		rect.top -= 5;
		dc.SetTextColor(RGB(255, 255, 255));
		dc.DrawText(m_sDec, m_sDec.GetLength(), rect, DT_LEFT | DT_SINGLELINE | DT_VCENTER);
		dc.SelectObject(pFont);

		CDialog::OnPaint();   
	//}  
}

void CFloatWnd::DrawGIF(CDC *pDC)
{
	//HINSTANCE handle = ::AfxGetResourceHandle();			//首先获得资源句柄 
	//HRSRC hrsrc= ::FindResource(handle, MAKEINTRESOURCE(IDR_GIF1),_T("GIF"));
	//DWORD word = ::SizeofResource(handle,hrsrc);


	//CFileStatus   fstatus;       
	//CFile   file;       
	//LONG   cb;    
	//if(file.Open(m_sPicFile, CFile::modeRead))       
	//{       
	//	file.GetStatus(m_sPicFile, fstatus);
	//	cb = (LONG)fstatus.m_size;
	//	if (cb <= 0)
	//	{
	//		file.Close();
	//		return;
	//	}
	//}
	// 
	//BYTE* lpBy = (BYTE*)LoadResource(handle,hrsrc);			//获得图象的首地址
	//BYTE* pByte[20];										//用来储存gif每幅图象的地址
	//DWORD nu[20];											//用来储存每幅图象的大小
	// 
	//int num = 0;											//用来计算有几副图象
	//DWORD firstLocation = 0;								//第一副图象的位置，用来替换
	// 
	//for(DWORD j=0; j<word; j++){
	//	if(lpBy[j]==0x2c) {									//图象开头
	//	    if(lpBy[j-1]==0x00) {						//确认是否图象开头
	//			if(num==0){
	//				firstLocation = j;			//得到第一副图象位置
	//			}

	//			PGifImage nowImage = (PGifImage)&lpBy[j+1];

	//			if(nowImage->Flag.a == 0) {			//a为0时指图象不存在局部调色板
	//				DWORD number = 1+sizeof(GifImage);

	//				while(lpBy[j+number]!=0){
	//					number = number+(DWORD)lpBy[j+number]+1;
	//				}							//算得图象大小

	//				number++;					//把最后一个0x00加上

	//				pByte[num] = new BYTE[number];

	//				//将图象储存起来。
	//				for(DWORD n=0;n<number;n++){
	//					*(BYTE*)(pByte[num]+n) = lpBy[j+n];
	//				}							

	//				nu[num] = number;
	//				j = j+number-1;				//跳过图象
	//				num++;
 //
	//			}else{
	//				//当a为1时需要加上局部调色板的大小，其他与a为0时一样
	//				int number = 1+sizeof(GifImage)+3*(int)floor(pow((float)2, (int)nowImage->Flag.d));

	//				//算得图象大小
	//				while(lpBy[j+number] != 0){
	//					number = number+(DWORD)lpBy[j+number]+1;
	//				}                        
 //
	//				number++;                //把最后一个0x00加上
	//				pByte[num] = new BYTE[number];

	//				//将图象储存起来。
	//				for(int n=0; n<number; n++){
	//					*(BYTE*)(pByte[num]+n) = lpBy[j+n];

	//				}                        

	//				nu[num] = number;
	//				j = j+number-1;            //跳过图象
	//				num++;

	//			}
	//		}
	//	}
	//}
 //
	//int working= 1;
	//while(working) {
 //   	for(int m=0;m<num;m++) {
 //           CBrush brush(RGB(255,255,255));
 //           pDC->FillRect(CRect(0,0,500,500),&brush);
	//		DWORD DDD;
	//		VirtualProtect(lpBy,word,PAGE_READWRITE,&DDD);
 //
	//		//修改页面的保护属性，以进行写操作
	//		for(DWORD n=0;n<nu[m];n++){
	//			lpBy[firstLocation+n] = *(BYTE*)(pByte[m]+n);
	//		}

	//		VirtualProtect(lpBy,word,DDD,NULL);

	//		//因为IPicture必须把图象存成流的形式才能工作，所以有下面一段函数
	//		CMemFile file(lpBy,word);
	//		CArchive ar(&file,CArchive::load|CArchive::bNoFlushOnDelete);
	//		CArchiveStream arcstream(&ar);

	//		CComQIPtr<IPicture> m_picture;

	//		HRESULT hr = OleLoadPicture((LPSTREAM)&arcstream,0,false,
	//		  IID_IPicture,(void**)&m_picture);

	//		long a,b;
	//		m_picture->get_Width(&a);
	//		m_picture->get_Height(&b);
	//		CSize sz(a,b);

	//		pDC->HIMETRICtoDP(&sz);    //时OLE格式的大小转化为正常大小
	//		CRect rect;
	//		m_picture->Render(*pDC,0,0,sz.cx,sz.cy,0,b,a,-b,&rect);
	//		Sleep(0);                  //停止一段时间。
	//	}

	//	working= 0;
	//}
}

void CFloatWnd::SetStatus(int nDocStatus, const CString &sDec)
{
	if(m_image){
		m_image->Destroy();
		delete m_image;
		m_image = NULL;
	}

	CString sImageName = _T("unlocked.gif");
	if(nDocStatus == OBJ_STATUS_WRITED){
		sImageName = _T("unlocked.gif");
		m_colorBk = RGB(20, 148, 20);
	}else if(nDocStatus == OBJ_STATUS_READONLY){
		sImageName = _T("locked.gif");
		m_colorBk = RGB(148, 20, 20);
	}else if(nDocStatus == OBJ_STATUS_OK){
		sImageName = _T("ok.gif");
		m_colorBk = RGB(111, 111, 111);
	}

	m_image = new ImageEx(theApp.GetAppPath() + _T("LockGIF\\") + sImageName);
	m_image->InitAnimation(m_hWnd, CPoint(3, 3));

	m_sDec = sDec;
	Invalidate();
	//m_staticTip.SetWindowText(sDec);
}

BOOL CFloatWnd::OnEraseBkgnd(CDC* pDC)
{
	////设置brush为希望的背景颜色
	//CBrush backBrush(RGB(255, 0, 0));

	////保存旧的brush
	//CBrush* pOldBrush = pDC->SelectObject(&backBrush);
	//CRect rect;
	//GetWindowRect(&rect);

	////画需要的区域
	//pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY);
	//pDC->SelectObject(pOldBrush);

	return CDialog::OnEraseBkgnd(pDC);
}

HBRUSH CFloatWnd::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

  //  if(nCtlColor == CTLCOLOR_STATIC)
  //  {
  //      pDC->SetTextColor(RGB(255, 255, 255));
  //      pDC->SetBkColor(RGB(255, 0, 0));

		//CRect   rect;   
		//GetClientRect(rect);   
		//dc.FillSolidRect(rect,RGB(255,0,0));   //设置为绿色背景  
  //  }

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
