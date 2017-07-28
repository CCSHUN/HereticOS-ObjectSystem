// GridCellStat.h: interface for the CGridCellStat class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRIDCELLSTAT_H__85940025_D64C_41E5_8472_A2AD5EF80F09__INCLUDED_)
#define AFX_GRIDCELLSTAT_H__85940025_D64C_41E5_8472_A2AD5EF80F09__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GridCell.h"

class IFL_EXPORT_CLASS CGridCellStat : public CGridCell  
{
	friend class CGridCtrl;
	DECLARE_DYNCREATE(CGridCellStat)
public:
	CGridCellStat();
	virtual ~CGridCellStat();

	CString		GetCellStyle()				{ return  m_sCellType; }
	void 		SetCellStyle(CString sType)	{ m_sCellType = sType; }
	void		SetFloatPrecision(int nPrecision) { m_nPrecision = nPrecision; }
	int			GetFloatPrecision() { return m_nPrecision; }

public:
    virtual BOOL Edit(int nRow, int nCol, CRect rect, CPoint point, UINT nID, UINT nChar);
    virtual void EndEdit();
	virtual BOOL Draw(CDC* pDC, int nRow, int nCol, CRect rect, BOOL bEraseBkgnd = TRUE);

private:
	CString m_sCellType;
	int m_nPrecision;
};

#endif // !defined(AFX_GRIDCELLSTAT_H__85940025_D64C_41E5_8472_A2AD5EF80F09__INCLUDED_)
