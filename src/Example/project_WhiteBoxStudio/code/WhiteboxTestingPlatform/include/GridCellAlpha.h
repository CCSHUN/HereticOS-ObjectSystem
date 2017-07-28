// GridCellAlpha.h: interface for the CGridCellAlpha class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRIDCELLALPHA_H__5DE5162F_45BD_48B4_A4D3_E1C97D66EC5F__INCLUDED_)
#define AFX_GRIDCELLALPHA_H__5DE5162F_45BD_48B4_A4D3_E1C97D66EC5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GridCell.h"

class IFL_EXPORT_CLASS CGridCellAlpha : public CGridCell  
{
    friend class CGridCtrl;
    DECLARE_DYNCREATE(CGridCellAlpha)
public:
	CGridCellAlpha();
	virtual ~CGridCellAlpha();

public:
	void SetCharsLength(int nLength) { m_nLength = nLength; }
	int  GetCharsLength() { return m_nLength; }

protected:
	virtual BOOL Draw(CDC* pDC, int nRow, int nCol, CRect rect, BOOL bEraseBkgnd = TRUE);

private:
	int m_nLength;
};

#endif // !defined(AFX_GRIDCELLALPHA_H__5DE5162F_45BD_48B4_A4D3_E1C97D66EC5F__INCLUDED_)
