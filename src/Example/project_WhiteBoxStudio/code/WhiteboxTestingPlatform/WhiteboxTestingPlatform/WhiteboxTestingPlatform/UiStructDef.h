#pragma once



//UI������������ ���ui����Ҫ���������
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

//������������Ŀ��View�Ľӿ�

class CViewInterfaceForWorkPageManager
{
public:
	CViewInterfaceForWorkPageManager(){};
	~CViewInterfaceForWorkPageManager(){};
	//virtual void HitPage(); //�����ǩ����ʱ
	virtual	void ProjectChange(BOOL bToTop){};		//��Ŀ�ı䣬��Ҫ�л���Ŀtabʱ 

	//Ҫ��������ݵ�����ʱ
	virtual void UpDataUi(){};
protected:

private:
};


typedef struct _tagTreeIndex
{
	vector<tstring> IndexList;
	tstring szPageName;
	tstring szPageType;
	BOOL bProjectActive;					//��Ŀ��ǰ�Ƿ�
	CUiSharedData *  pSharedObject;			//���ڹ��칲�����ݣ����������ڼ�������ͬ����֮������ݹ���

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