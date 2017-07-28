// FloatWnd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WhiteboxTestingPlatform.h"
#include "FloatWnd.h"
#include "resource.h"
#include <math.h>
#include "ImageEx.h"

// CFloatWnd �Ի���

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


// CFloatWnd ��Ϣ�������

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
	
	//����WS_EX_LAYERED��չ����
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
	// �쳣: OCX ����ҳӦ���� FALSE
}

LRESULT CFloatWnd::OnNcHitTest(CPoint point)
{
	//UINT nHitTest = CDialog::OnNcHitTest(point);

	//if (nHitTest == HTCLIENT && ::GetAsyncKeyState(MK_LBUTTON) < 0) 
	//	nHitTest = HTCAPTION;		// ������������£�GetAsyncKeyState�����ķ���ֵС��0

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
		//ȡ��SetLayeredWindowAttributes����ָ�� 
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

		dc.FillSolidRect(rect,m_colorBk);   //����Ϊ��ɫ����   
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
	//HINSTANCE handle = ::AfxGetResourceHandle();			//���Ȼ����Դ��� 
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
	//BYTE* lpBy = (BYTE*)LoadResource(handle,hrsrc);			//���ͼ����׵�ַ
	//BYTE* pByte[20];										//��������gifÿ��ͼ��ĵ�ַ
	//DWORD nu[20];											//��������ÿ��ͼ��Ĵ�С
	// 
	//int num = 0;											//���������м���ͼ��
	//DWORD firstLocation = 0;								//��һ��ͼ���λ�ã������滻
	// 
	//for(DWORD j=0; j<word; j++){
	//	if(lpBy[j]==0x2c) {									//ͼ��ͷ
	//	    if(lpBy[j-1]==0x00) {						//ȷ���Ƿ�ͼ��ͷ
	//			if(num==0){
	//				firstLocation = j;			//�õ���һ��ͼ��λ��
	//			}

	//			PGifImage nowImage = (PGifImage)&lpBy[j+1];

	//			if(nowImage->Flag.a == 0) {			//aΪ0ʱָͼ�󲻴��ھֲ���ɫ��
	//				DWORD number = 1+sizeof(GifImage);

	//				while(lpBy[j+number]!=0){
	//					number = number+(DWORD)lpBy[j+number]+1;
	//				}							//���ͼ���С

	//				number++;					//�����һ��0x00����

	//				pByte[num] = new BYTE[number];

	//				//��ͼ�󴢴�������
	//				for(DWORD n=0;n<number;n++){
	//					*(BYTE*)(pByte[num]+n) = lpBy[j+n];
	//				}							

	//				nu[num] = number;
	//				j = j+number-1;				//����ͼ��
	//				num++;
 //
	//			}else{
	//				//��aΪ1ʱ��Ҫ���Ͼֲ���ɫ��Ĵ�С��������aΪ0ʱһ��
	//				int number = 1+sizeof(GifImage)+3*(int)floor(pow((float)2, (int)nowImage->Flag.d));

	//				//���ͼ���С
	//				while(lpBy[j+number] != 0){
	//					number = number+(DWORD)lpBy[j+number]+1;
	//				}                        
 //
	//				number++;                //�����һ��0x00����
	//				pByte[num] = new BYTE[number];

	//				//��ͼ�󴢴�������
	//				for(int n=0; n<number; n++){
	//					*(BYTE*)(pByte[num]+n) = lpBy[j+n];

	//				}                        

	//				nu[num] = number;
	//				j = j+number-1;            //����ͼ��
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
	//		//�޸�ҳ��ı������ԣ��Խ���д����
	//		for(DWORD n=0;n<nu[m];n++){
	//			lpBy[firstLocation+n] = *(BYTE*)(pByte[m]+n);
	//		}

	//		VirtualProtect(lpBy,word,DDD,NULL);

	//		//��ΪIPicture�����ͼ����������ʽ���ܹ���������������һ�κ���
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

	//		pDC->HIMETRICtoDP(&sz);    //ʱOLE��ʽ�Ĵ�Сת��Ϊ������С
	//		CRect rect;
	//		m_picture->Render(*pDC,0,0,sz.cx,sz.cy,0,b,a,-b,&rect);
	//		Sleep(0);                  //ֹͣһ��ʱ�䡣
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
	////����brushΪϣ���ı�����ɫ
	//CBrush backBrush(RGB(255, 0, 0));

	////����ɵ�brush
	//CBrush* pOldBrush = pDC->SelectObject(&backBrush);
	//CRect rect;
	//GetWindowRect(&rect);

	////����Ҫ������
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
		//dc.FillSolidRect(rect,RGB(255,0,0));   //����Ϊ��ɫ����  
  //  }

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}
