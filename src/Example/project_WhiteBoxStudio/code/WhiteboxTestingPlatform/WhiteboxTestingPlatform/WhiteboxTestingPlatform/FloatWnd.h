#pragma once
#include "afxwin.h"
#include "resource.h"

// CFloatWnd 对话框

typedef struct gifImage{
 
   WORD logX;
   WORD logY;
   WORD width;
   WORD height;
 
   struct flag{
      BYTE d:3;
      BYTE c:1;
      BYTE b:3;
      BYTE a:1;
   }Flag;
}GifImage,*PGifImage;

class ImageEx;

class CFloatWnd : public CDialog
{
	DECLARE_DYNAMIC(CFloatWnd)

public:
	CFloatWnd(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFloatWnd();

// 对话框数据
	enum { IDD = IDD_FLOATWND };

	enum { OBJ_STATUS_WRITED, OBJ_STATUS_READONLY, OBJ_STATUS_OK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnNcHitTest(CPoint point);
	void OnUpdateTransparent(int iTransparent);

	void SetPicture(const CString &sPicFile);
	CString GetPicture() { return m_sPicFile; }

private:
	BOOL DrawPicture(CDC* pDC, CRect rect);
	void DrawGIF(CDC *pDC);

private:
	CFont m_font;
	COLORREF m_colorBk;
	CString m_sDec;
	CString		m_sPicFile;
	IPicture	*m_pPic;   
	HGLOBAL		m_hGlobal;
	IStream		*m_pStm;  
public:
	afx_msg void OnPaint();

	ImageEx			*m_image;

	void SetStatus(int nDocStatus, const CString &sDec);
	CStatic m_staticTip;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
