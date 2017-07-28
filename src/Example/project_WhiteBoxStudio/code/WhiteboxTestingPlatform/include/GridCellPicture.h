// GridCellPicture.h: interface for the CGridCellPicture class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRIDCELLPICTURE_H__F2127448_F797_48EF_9F6F_550F3CD74C7D__INCLUDED_)
#define AFX_GRIDCELLPICTURE_H__F2127448_F797_48EF_9F6F_550F3CD74C7D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GridCell.h"

class IFL_EXPORT_CLASS CGridCellPicture : public CGridCell  
{
    friend class CGridCtrl;
    DECLARE_DYNCREATE(CGridCellPicture)

public:
	CGridCellPicture();
	virtual ~CGridCellPicture();

public:
	void SetPicture(const CString &sPicFile);
	CString GetPicture() { return m_sPicFile; }

protected:
	CRect	GetCheckPlacement();
	virtual BOOL	Draw(CDC* pDC, int nRow, int nCol, CRect rect, BOOL bEraseBkgnd = TRUE);
	virtual BOOL	PrintCell(CDC* pDC, int nRow, int &nCol, CRect rect, struct PRINT_POS_INFO_ *pPrintInfo);

private:
	BOOL DrawPicture(CDC* pDC, int nRow, int nCol, CRect rect);
	BOOL PrintPicture(CDC* pDC, int nRow, int nCol, CRect rect);

private:
	CString		m_sPicFile;
	IPicture	*m_pPic;   
	HGLOBAL		m_hGlobal;
	IStream		*m_pStm;  
};

#endif // !defined(AFX_GRIDCELLPICTURE_H__F2127448_F797_48EF_9F6F_550F3CD74C7D__INCLUDED_)
