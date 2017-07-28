#pragma once

#include "ViewTree.h"

class CSpecifyViewToolBar : public CMFCToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CSpecifyView : public CDockablePane
{
	DECLARE_DYNAMIC(CSpecifyView)

public:
	CSpecifyView();
	virtual ~CSpecifyView();

protected:
	DECLARE_MESSAGE_MAP()

public:
	void AdjustLayout();

protected:
	void FillFileView();

protected:
	CViewTree m_wndFileView;
	CImageList m_FileViewImages;
	//CSpecifyViewToolBar m_wndToolBar;

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnFileOpen();
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnNewStandard();
	afx_msg void OnUpdataStandard();
	afx_msg void OnDeleteStandard();
	afx_msg void OnReGetStandard();
	void OnCanCreateDel(CCmdUI *pCmdUI);
};


