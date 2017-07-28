////////////////////////////////////////////////////////////////////////////
// GridCellBase.h : header file
//
// MFC Grid Control - Grid cell base class header file
//
// Written by Chris Maunder <cmaunder@mail.com>
// Copyright (c) 1998-2002. All Rights Reserved.
//
// This code may be used in compiled form in any way you desire. This
// file may be redistributed unmodified by any means PROVIDING it is 
// not sold for profit without the authors written consent, and 
// providing that this notice and the authors name and all copyright 
// notices remains intact. 
//
// An email letting me know how you are using it would be nice as well. 
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability for any damage/loss of business that
// this product may cause.
//
// For use with CGridCtrl v2.22+
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRIDCELLBASE_H__519FA702_722C_11D1_ABBA_00A0243D1382__INCLUDED_)
#define AFX_GRIDCELLBASE_H__519FA702_722C_11D1_ABBA_00A0243D1382__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//鼠标光标的类型
#define CURSOR_TYPE_NORMAL				0X1				//普通类型
#define CURSOR_TYPE_EXCEL				0X2				//EXCEL类型
#define CURSOR_TYPE_EXCEL_STYLEBRUSH	0X3				//格式刷

class CGridCtrl;

// Cell states
#define GVIS_FOCUSED				0x0001
#define GVIS_SELECTED				0x0002
#define GVIS_DROPHILITED			0x0004
#define GVIS_READONLY				0x0008
#define GVIS_FIXED					0x0010
#define GVIS_FIXEDROW				0x0020
#define GVIS_FIXEDCOL				0x0040
#define GVIS_MODIFIED				0x0080

//add by zhangxin : date 2007-08-21
//单元格的行列是否可插入, 是否可删除, 这些属性只设置在行的第一个单元格和列的第一个单元格
#define GVIS_ROW_INSERTED			0x0100
#define GVIS_ROW_DELETED			0x0200
#define GVIS_COL_INSERTED			0x0400
#define GVIS_COL_DELETED			0x0800
//end add

//动态数据行如果没有数据不删除(用在输入格式文件时)
#define GVIS_ROW_NODYMICDATA_NODELETE 0x1000			

//打印时单元格不输出文本
#define GVIS_CELL_PRINT_NOOUTPUT_TEXT	0x2000			

// End of Cell states

// 单元格边框
#define GVDT_NONE				0x0000
#define GVDT_LEFT				0x0001
#define GVDT_TOP				0x0002
#define GVDT_RIGHT				0x0004
#define GVDT_BOTTOM				0x0008
#define GVDT_TOPLEFT			(GVDT_TOP|GVDT_LEFT)
#define GVDT_TOPRIGHT			(GVDT_TOP|GVDT_RIGHT)
#define GVDT_BOTLEFT			(GVDT_LEFT|GVDT_BOTTOM)
#define GVDT_BOTRIGHT			(GVDT_RIGHT|GVDT_BOTTOM)
#define GVDT_ALL				(GVDT_TOP|GVDT_LEFT|GVDT_RIGHT|GVDT_BOTTOM)

//add by zhangxin : date 2007-09-14
//在编辑单元格公式时, 标记参与运算的单元格
#define GVDT_MATHMARK_TOP		0x0010
#define GVDT_MATHMARK_LEFT		0x0020
#define GVDT_MATHMARK_RIGHT		0x0040
#define GVDT_MATHMARK_BOTTOM	0x0080
#define GVDT_MATHMARK_TOPLEFT	(GVDT_MATHMARK_TOP | GVDT_MATHMARK_LEFT)
#define GVDT_MATHMARK_TOPRIGHT	(GVDT_MATHMARK_TOP | GVDT_MATHMARK_RIGHT)
#define GVDT_MATHMARK_BOTLEFT	(GVDT_MATHMARK_LEFT | GVDT_MATHMARK_BOTTOM)
#define GVDT_MATHMARK_BOTRIGHT	(GVDT_MATHMARK_RIGHT | GVDT_MATHMARK_BOTTOM)
#define GVDT_MATHMARK_ALL		(GVDT_MATHMARK_TOP | GVDT_MATHMARK_LEFT | GVDT_MATHMARK_RIGHT | GVDT_MATHMARK_BOTTOM)
//end add

//add by zhangxin : date 2007-10-15
//选区的边框, 暂时没有使用
#define GVDT_SELECTION_TOP				0x0100
#define GVDT_SELECTION_LEFT				0x0200
#define GVDT_SELECTION_RIGHT			0x0400
#define GVDT_SELECTION_BOTTOM			0x0800
//end add 

//add by zhangxin : date 2007-10-17
//格式刷源区域的边框
#define GVDT_CELL_STYLEBRUSH_TOP		0x1000
#define GVDT_CELL_STYLEBRUSH_LEFT		0x2000
#define GVDT_CELL_STYLEBRUSH_RIGHT		0x4000
#define GVDT_CELL_STYLEBRUSH_BOTTOM		0x8000
//end add 

//add by zhangxin : date 2007-10-30
//当从格式文件中导入公式时, 如果单元格中有数据时, 则这时该公式不计算, 并且单元格右上角加标记
#define GVDT_CELL_INIT_NOTCALMATH		0x10000
//当单元格有注释时, 在右上角做标记             
#define GVDT_CELL_RAMARK				0x20000
//end add 

//End of 单元格边框



//公式标记单元格线框的颜色
#define COLOR_MATHMARK_1		RGB(255, 0, 0)
#define COLOR_MATHMARK_2		RGB(0, 255, 0)
#define COLOR_MATHMARK_3		RGB(0, 0, 255)
#define COLOR_MATHMARK_4		RGB(255, 50, 50)
#define COLOR_MATHMARK_5		RGB(50, 255, 50)
#define COLOR_MATHMARK_6		RGB(150, 255, 150)
#define COLOR_MATHMARK_7		RGB(255, 150, 150)
#define COLOR_MATHMARK_8		RGB(50, 50, 255)
#define COLOR_MATHMARK_9		RGB(150, 150, 255)
#define COLOR_MATHMARK_10		RGB(255, 255, 0)
#define COLOR_MATHMARK_11		RGB(255, 255, 50)
#define COLOR_MATHMARK_12		RGB(255, 255, 150)
#define COLOR_MATHMARK_13		RGB(255, 0, 255)
#define COLOR_MATHMARK_14		RGB(255, 50, 255)
#define COLOR_MATHMARK_15		RGB(255, 15, 255)
#define COLOR_MATHMARK_16		RGB(0, 255, 255)

#define COLOR_NONE				RGB(255,255,255)
#define COLOR_DEFAULT			RGB(192,192,192)
#define COLOR_BLACK				RGB(0,0,0)
#define COLOR_SELECTED			RGB(169,178,202)

// Cell data mask
#define GVIF_TEXT               LVIF_TEXT
#define GVIF_IMAGE              LVIF_IMAGE
#define GVIF_PARAM              LVIF_PARAM
#define GVIF_STATE              LVIF_STATE
#define GVIF_BKCLR              (GVIF_STATE<<1)
#define GVIF_FGCLR              (GVIF_STATE<<2)
#define GVIF_FORMAT             (GVIF_STATE<<3)
#define GVIF_FONT               (GVIF_STATE<<4)
#define GVIF_MARGIN             (GVIF_STATE<<5)
#define GVIF_ALL                (GVIF_TEXT|GVIF_IMAGE|GVIF_PARAM|GVIF_STATE|GVIF_BKCLR|GVIF_FGCLR| \
                                 GVIF_FORMAT|GVIF_FONT|GVIF_MARGIN)

// Used for Get/SetItem calls.
typedef struct _GV_ITEM {
    int      row,col;     // Row and Column of item
    UINT     mask;        // Mask for use in getting/setting cell data
    UINT     nState;      // cell state (focus/hilighted etc)
    DWORD    nFormat;     // Format of cell
    int      iImage;      // index of the list view item抯 icon
    COLORREF crBkClr;     // Background colour (or CLR_DEFAULT)
    COLORREF crFgClr;     // Forground colour (or CLR_DEFAULT)
    LPARAM   lParam;      // 32-bit value to associate with item
    LOGFONT  lfFont;      // Cell font
    UINT     nMargin;     // Internal cell margin
    CString  strText;     // Text in cell
} GV_ITEM;

#define MAX_MATHMARK_COUNT	16
extern COLORREF gMathMarkColor[MAX_MATHMARK_COUNT];

// Each cell contains one of these. Fields "row" and "column" are not stored since we
// will usually have acces to them in other ways, and they are an extra 8 bytes per
// cell that is probably unnecessary.

class IFL_EXPORT_CLASS CGridCellBase : public CObject
{
    friend class CGridCtrl;
    DECLARE_DYNAMIC(CGridCellBase)

// Construction/Destruction
public:
    CGridCellBase();
    virtual ~CGridCellBase();

// Attributes
public:
    virtual void SetName(LPCTSTR /* szText */)              = 0 ;
    virtual void SetMemo(LPCTSTR /* szText */)              = 0 ;
    virtual void SetText(LPCTSTR /* szText */)              = 0 ;
    virtual void SetImage(int /* nImage */)                 = 0 ;
    virtual void SetData(LPARAM /* lParam */)               = 0 ;
    virtual void SetState(DWORD nState)                     { m_nState = nState; }
    virtual void SetFormat(DWORD /* nFormat */)             = 0 ;
    virtual void SetTextClr(COLORREF /* clr */)             = 0 ;
    virtual void SetBackClr(COLORREF /* clr */)             = 0 ;
    virtual void SetFont(const LOGFONT* /* plf */)          = 0 ;
    virtual void SetMargin( UINT /* nMargin */)             = 0 ;
    virtual void SetGrid(CGridCtrl* /* pGrid */)            = 0 ;
    virtual void SetCoords( int /* nRow */, int /* nCol */) = 0 ;

    virtual LPCTSTR    GetName() 	   const				= 0 ;
    virtual LPCTSTR    GetMemo() 	   const				= 0 ;
    virtual LPCTSTR    GetText()       const                = 0 ;
    virtual LPCTSTR    GetTipText()    const                { return GetText(); } // may override TitleTip return
    virtual int        GetImage()      const                = 0 ;
    virtual LPARAM     GetData()       const                = 0 ;
    virtual DWORD      GetState()      const                { return m_nState;  }
    virtual DWORD      GetFormat()     const                = 0 ;
    virtual COLORREF   GetTextClr()    const                = 0 ;
    virtual COLORREF   GetBackClr()    const                = 0 ;
    virtual LOGFONT  * GetFont()       const                = 0 ;
    virtual CFont    * GetFontObject() const                = 0 ;
    virtual CGridCtrl* GetGrid()       const                = 0 ;
    virtual CWnd     * GetEditWnd()    const                = 0 ;
    virtual UINT       GetMargin()     const                = 0 ;

    virtual CGridCellBase* GetDefaultCell() const;

    virtual BOOL IsDefaultFont()       const                = 0 ;
    virtual BOOL IsEditing()           const                = 0 ;
    virtual BOOL IsFocused()           const                { return (m_nState & GVIS_FOCUSED);  }
    virtual BOOL IsFixed()             const                { return (m_nState & GVIS_FIXED);    }
    virtual BOOL IsFixedCol()          const                { return (m_nState & GVIS_FIXEDCOL); }
    virtual BOOL IsFixedRow()          const                { return (m_nState & GVIS_FIXEDROW); }
    virtual BOOL IsSelected()          const                { return (m_nState & GVIS_SELECTED); }
    virtual BOOL IsReadOnly()          const                { return (m_nState & GVIS_READONLY); }
    virtual BOOL IsModified()          const                { return (m_nState & GVIS_MODIFIED); }
    virtual BOOL IsDropHighlighted()   const                { return (m_nState & GVIS_DROPHILITED); }

	//add by zhangxin : date 2007-08-21
    virtual BOOL IsRowInserted()	   const                { return (m_nState & GVIS_ROW_INSERTED); }
    virtual BOOL IsRowDeleted()		   const                { return (m_nState & GVIS_ROW_DELETED); }
    virtual BOOL IsColInserted()	   const                { return (m_nState & GVIS_COL_INSERTED); }
    virtual BOOL IsColDeleted()		   const                { return (m_nState & GVIS_COL_DELETED); }
	//end by

	// qy 2006-8-16
	// 处理合并需要的变量
	virtual BOOL	IsHide() const				{ return m_bHide;}
	virtual int		GetHideRow() const			{ return m_nRowhide; }
	virtual int		GetHideCol() const			{ return m_nColhide; }
	virtual int		GetHideTopLeftRow() const	{ return m_nTopleftRow; }
	virtual int		GetHideTopLeftCol() const	{ return m_nTopleftCol; }

	virtual void	SetHide(BOOL bHide)			{ m_bHide = bHide;}
	virtual void	SetHideRow(int rowHide) 	{ m_nRowhide = rowHide; }
	virtual void	SetHideCol(int colHide) 	{ m_nColhide = colHide; }
	virtual void	SetHideTopLeftRow(int tl_row)	{ m_nTopleftRow = tl_row; }
	virtual void	SetHideTopLeftCol(int tl_col)	{ m_nTopleftCol = tl_col; }

	// 边框
	virtual	void	SetLineState(UINT nState)	{ m_nLineState = nState; }
    virtual UINT	GetLineState() const        { return m_nLineState;  }
	// end

// Operators
public:
    virtual void operator=(const CGridCellBase& cell);

// Operations
public:
    virtual void	Reset();

    virtual BOOL	Draw(CDC* pDC, int nRow, int nCol, CRect rect, BOOL bEraseBkgnd = TRUE);
    virtual void	DrawText(CDC* pDC,LPCSTR lpstr,int count,LPRECT rect,UINT fmt);
	void			DrawPrintText(CDC* pDC,LPCSTR lpstr,int count,LPRECT lprect,UINT fmt);

	virtual BOOL	GetTextRect( LPRECT pRect);    // i/o:  i=dims of cell rect; o=dims of text rect
    virtual BOOL	GetTipTextRect( LPRECT pRect) { return GetTextRect( pRect); }  // may override for btns, etc.
    virtual CSize	GetTextExtent(LPCTSTR str, CDC* pDC = NULL);
    virtual CSize	GetCellExtent(CDC* pDC);

    // Editing
    virtual			BOOL Edit( int /* nRow */, int /* nCol */, CRect /* rect */, CPoint /* point */, 
								UINT /* nID */, UINT /* nChar */) { ASSERT( FALSE); return FALSE;}
	virtual BOOL	ValidateEdit(LPCTSTR str);
    virtual void	EndEdit() {}

    // EFW - Added to print cells properly
    virtual BOOL	PrintCell(CDC* pDC, int nRow, int &nCol, CRect rect, struct PRINT_POS_INFO_ *pPrintInfo);

    // add additional protected grid members required of cells
    LRESULT			SendMessageToParent(int nRow, int nCol, int nMessage);

protected:
    virtual void OnEndEdit();
    virtual void OnMouseEnter();
    virtual void OnMouseOver();
    virtual void OnMouseLeave();
    virtual void OnClick( CPoint PointCellRelative);
    virtual void OnClickDown( CPoint PointCellRelative);
    virtual void OnRClick( CPoint PointCellRelative);
    virtual void OnDblClick( CPoint PointCellRelative);
    virtual BOOL OnSetCursor();

protected:
    DWORD		m_nState;      // Cell state (selected/focus etc)

	//add by zhangxin : 2005.11.20
protected:
    BOOL		m_bHide;						//	单元格是否被合并(需要隐藏)
	int			m_nColhide;						//	水平需要隐藏的单元格;只针对TOPLEFT赋值.即列数
	int			m_nRowhide;						//	垂直需要隐藏的单元格;只针对TOPLEFT赋值,即行数
	int			m_nTopleftRow,m_nTopleftCol;	//	被隐藏的单元格需要输入最左上的行和列值
	UINT		m_nLineState;					//  边框的线条样式
	int		    m_nPrintLines;	//控制打印的边线状态: GVL_BOTH, GVL_HORZ, GVL_VERT, GVL_NONE

	//end add

	//add by zhangxin : 2007-03-29
	CString		m_sName;						//单元格的名字
	CString     m_sMemo;						//单元格的批注
	//end

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRIDCELLBASE_H__519FA702_722C_11D1_ABBA_00A0243D1382__INCLUDED_)
