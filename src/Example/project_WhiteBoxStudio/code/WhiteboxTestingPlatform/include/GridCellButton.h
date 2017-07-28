// GridCellButton.h: interface for the CGridCellButton class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRIDCELLBUTTON_H__DF8FE693_BF4A_4AC6_B75A_9F5A9141E3C8__INCLUDED_)
#define AFX_GRIDCELLBUTTON_H__DF8FE693_BF4A_4AC6_B75A_9F5A9141E3C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GridCell.h"

class IFL_EXPORT_CLASS CGridCellButton : public CGridCell  
{
    friend class CGridCtrl;
    DECLARE_DYNCREATE(CGridCellButton)

public:
	CGridCellButton();
	virtual ~CGridCellButton();

public:
 	virtual CSize	GetCellExtent(CDC* pDC);
    virtual void	OnClick(CPoint PointCellRelative);
	virtual void	OnClickDown(CPoint PointCellRelative);
	virtual void	OnMouseLeave();
    virtual BOOL	GetTextRect( LPRECT pRect);
	virtual BOOL	Edit(int nRow, int nCol, CRect rect, CPoint point, UINT nID, UINT nChar){ return FALSE; }
public:
	//设置名字
	void	SetButtonText(const CString &sText){ m_sText = sText; }
	CString GetButtonText() { return m_sText; }

	//设置消息ID 
	void	SetMessageID(UINT nMessageID){ m_nMessageID = nMessageID; }
	UINT	GetMessageID() { return m_nMessageID; }

	//设置按钮可用，不可用
	void	SetDisabled(BOOL bDisabled = TRUE);
	BOOL	GetIsDisabled();
	void	SetVisibled(BOOL bVisibled = TRUE);
	BOOL	GetIsVisibled();

protected:
	CRect	GetCheckPlacement();
	virtual BOOL Draw(CDC* pDC, int nRow, int nCol, CRect rect, BOOL bEraseBkgnd = TRUE);
private:
    BOOL  m_bChecked;
    CRect m_Rect;
	CString m_sText;
	UINT m_nMessageID;
	BOOL m_bVisibled;
	//按钮可用，不可用的状态变量
	BOOL  m_bDisabled;
};

#endif // !defined(AFX_GRIDCELLBUTTON_H__DF8FE693_BF4A_4AC6_B75A_9F5A9141E3C8__INCLUDED_)
