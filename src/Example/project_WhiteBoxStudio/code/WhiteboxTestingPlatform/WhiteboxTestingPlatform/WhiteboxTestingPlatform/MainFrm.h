
// MainFrm.h : CMainFrame 类的接口
//

#pragma once
#include "ProjectView.h"
#include "FileView.h"
#include "ClassView.h"
#include "OutputWnd.h"
#include "PropertiesWnd.h"
#include "PropertiesWnd.h"
#include "SpecifyView.h"
#include "AdminTreeView.h"
#include "MsgTreeView.h"
#include "FloatWnd.h"
#include "AddressNavigate.h"

class CMyMDIFrameWndEx : public CMDIFrameWndEx
{
public:
	CMyMDIFrameWndEx(){};
	~CMyMDIFrameWndEx(){};
protected:
	afx_msg LRESULT OnMoveTabComplete(WPARAM wp, LPARAM lp)
	{
		return 0;
	};
private:
};



class CMainFrame : public CMyMDIFrameWndEx
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// 属性
public:

// 操作
public:
	
	void UpdateTabs();
	CAddressNavigate	m_AddressNavigate;

// 重写
public:
	virtual void OnUpdateFrameTitle(BOOL bAddToTitle);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CMFCMenuBar			m_wndMenuBar;
	//CMFCToolBar			m_wndToolBar;
	//CDialogBar         m_wndToolBar;
	//CMFCStatusBar		m_wndStatusBar;
	//CMFCToolBarImages	m_UserImages;
	//CFileView         m_wndFileView;
	CProjectView         m_wndProjectView;
	//CClassView        m_wndClassView;
	COutputWnd			m_wndOutput;
	//CPropertiesWnd    m_wndProperties;
	CSpecifyView		m_SpecifyManager;
	CAdminTreeView		m_AdminTreeView;
	CMsgTreeView		m_MsgManager;
	CFloatWnd			*m_pFloatWnd;
	

// 生成的消息映射函数
protected:
	BOOL m_bInit;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnWindowManager();
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnApplicationTest(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	afx_msg LRESULT OnMoveTabComplete(WPARAM wp, LPARAM lp);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()

	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);

public:
	afx_msg void OnFileNew();
	void WriteStringToOutputWnd(const CString &sInfo, int nSB_POSITION=-1, BOOL bResetContent=FALSE);
	int CreateNewView();

	void SetObjectStatus(int nDocStatus, const CString &sDec);
};


