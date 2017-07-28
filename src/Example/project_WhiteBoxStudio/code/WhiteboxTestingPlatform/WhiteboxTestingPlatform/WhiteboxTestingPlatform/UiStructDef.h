#pragma once



//UI共享数据引用 存放ui间需要共享的数据
class CUiSharedData
{
public:
	CUiSharedData(){};
	~CUiSharedData(){};
	virtual BOOL GetObject(){ return TRUE;};
	virtual BOOL UpdataObject(){ return TRUE;};
protected:

private:
};

//管理器器操作目标View的接口

class CViewInterfaceForWorkPageManager
{
public:
	CViewInterfaceForWorkPageManager(){};
	~CViewInterfaceForWorkPageManager(){};
	//virtual void HitPage(); //点击标签激活时
	virtual	void ProjectChange(BOOL bToTop){};		//项目改变，需要切换项目tab时 

	//要求跟新数据到界面时
	virtual void UpDataUi(){};
protected:

private:
};


typedef struct _tagTreeIndex
{
	vector<tstring> IndexList;
	tstring szPageName;
	tstring szPageType;
	BOOL bProjectActive;					//项目当前是否活动
	CUiSharedData *  pSharedObject;			//用于构造共享数据，在树构造期间分配管理不同界面之间的数据共享

	//CWnd * pFrameWnd;
	//CWnd * pViewWnd;
	CViewInterfaceForWorkPageManager * pViewInterface;
}TreeIndex,*PTreeIndex;


typedef struct _tagWorkUiContext
{
	TreeIndex index;
	void * pContext;				//CChildFrame
	
}WorkUiContext,*PWorkUiContext;


#include "ChildFrm.h"
class CMyView : public CFormView,CViewInterfaceForWorkPageManager
{
public:
	CMyView();
	~CMyView();
	void OnInitialUpdate()
	{
		CFormView::OnInitialUpdate();
		((CChildFrame *)GetParentFrame())->m_ProjectIndex.pViewInterface=this;
	}
protected:
	
private:
};