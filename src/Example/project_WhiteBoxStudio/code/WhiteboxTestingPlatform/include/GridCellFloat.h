// GridCellFloat.h: interface for the CGridCellFloat class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRIDCELLFLOAT_H__A651FE31_AA3E_4D90_B436_5449AA90391C__INCLUDED_)
#define AFX_GRIDCELLFLOAT_H__A651FE31_AA3E_4D90_B436_5449AA90391C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GridCell.h"

class IFL_EXPORT_CLASS CGridCellFloat : public CGridCell  
{
    friend class CGridCtrl;
    DECLARE_DYNCREATE(CGridCellFloat)
public:
	CGridCellFloat();
	virtual ~CGridCellFloat();

public:
	void SetFloatPrecision(int nPrecision) { m_nPrecision = nPrecision; }
	int  GetFloatPrecision() { return m_nPrecision; }
	virtual BOOL Draw(CDC* pDC, int nRow, int nCol, CRect rect, BOOL bEraseBkgnd = TRUE);

private:
	int m_nPrecision;
};

#endif // !defined(AFX_GRIDCELLFLOAT_H__A651FE31_AA3E_4D90_B436_5449AA90391C__INCLUDED_)
