
// ChildFrm.h : CChildFrame ��Ľӿ�
//

#pragma once



class CChildFrame : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// ����
public:
	TreeIndex m_ProjectIndex;

// ����
public:
	

// ��д
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// ���ɵ���Ϣӳ�亯��
	BOOL CanShowOnMDITabs();
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnMoveTabComplete(WPARAM wp, LPARAM lp);
};
