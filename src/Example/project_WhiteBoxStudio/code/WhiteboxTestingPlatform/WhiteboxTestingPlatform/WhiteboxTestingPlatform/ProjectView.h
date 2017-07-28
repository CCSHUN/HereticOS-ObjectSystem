#pragma once

#include "ViewTree.h"

class CProjectViewToolBar : public CMFCToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CProjectView : public CDockablePane
{
	DECLARE_DYNAMIC(CProjectView)

public:
	CProjectView();
	virtual ~CProjectView();

public:
	void AdjustLayout();

protected:
	void FillFileView();

protected:
	DECLARE_MESSAGE_MAP()

protected:
	CViewTree m_wndFileView;
	CImageList m_FileViewImages;
	//CProjectViewToolBar m_wndToolBar;

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnBuildReport();
	afx_msg void OnReBuildReport();
	afx_msg void OnCreateTestingProject();
	afx_msg void OnCreateDirectory();
	afx_msg void OnCreateSubTestingProject();
	afx_msg void OnProjectDel();
	afx_msg void OnGetNodePath();
	afx_msg void OnFileOpen();
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnStopbuildReport();
	afx_msg void OnReGetProjectTree();

	afx_msg void OnMangerProject();

public:
	afx_msg void OnUpdateCreateProject(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCreateSubProject(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCreateDirectory(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBuildReport(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRebuildReport(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCanStopbuild(CCmdUI *pCmdUI);
	afx_msg void OnProjectTreeCanReGet(CCmdUI *pCmdUI);
	afx_msg void OnProjectMangerCanEdit(CCmdUI *pCmdUI);

	afx_msg void OnCanDel(CCmdUI *pCmdUI);
	afx_msg void CProjectView::UnLockProject();
	afx_msg void CProjectView::OnCanUnLockSubProject(CCmdUI *pCmdUI);
};


