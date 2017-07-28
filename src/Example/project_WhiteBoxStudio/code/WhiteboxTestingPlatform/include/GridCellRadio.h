// GridCellRadio.h: interface for the CGridCellRadio class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRIDCELLRADIO_H__1177C30F_C6E5_4096_8183_795D446A0F88__INCLUDED_)
#define AFX_GRIDCELLRADIO_H__1177C30F_C6E5_4096_8183_795D446A0F88__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GridCell.h"

class IFL_EXPORT_CLASS CGridCellRadio : public CGridCell  
{
	friend class CGridCtrl;
	DECLARE_DYNCREATE(CGridCellRadio)

public:
	CGridCellRadio();
	~CGridCellRadio();

public:
	BOOL SetCheck(BOOL bChecked = TRUE);
	BOOL GetCheck();

// Operations
	virtual CSize GetCellExtent(CDC* pDC);
    virtual void OnClick( CPoint PointCellRelative);
    virtual BOOL GetTextRect( LPRECT pRect);

protected:
	CRect GetCheckPlacement();
    virtual BOOL Draw(CDC* pDC, int nRow, int nCol, CRect rect, BOOL bEraseBkgnd = TRUE);

protected:
    BOOL  m_bChecked;
    CRect m_Rect;
};

#endif // !defined(AFX_GRIDCELLRADIO_H__1177C30F_C6E5_4096_8183_795D446A0F88__INCLUDED_)
