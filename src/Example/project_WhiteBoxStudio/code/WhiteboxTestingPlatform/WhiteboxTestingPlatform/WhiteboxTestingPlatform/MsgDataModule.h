#pragma once

class CMsgDataModule
{
public:
	BOOL GetMsgUiTree(CViewTree & TreeCtl);
	BOOL GetUserMsg(tstring & szUserName,tstring & szDstUserName,tstring & szFinder,OUT vector<_tagMsgBody> & Body);
	BOOL GetSystemMsg(tstring & szUserName,tstring & szFinder,OUT vector<_tagMsgBody> & Body);
	BOOL GetProjectMsg(tstring & szProjectName,tstring & szFinder,OUT vector<_tagMsgBody> & Body);
	BOOL SendUserMsg(tstring & szUserName,tstring & szDstUserName,_tagMsgBody & msg);
	BOOL SendProjectMsg(tstring & szUserName,tstring & szDstProjectName,_tagMsgBody & msg);
	BOOL SendSystemMsg(tstring & szDstUserName,_tagMsgBody & msg);
	CMsgDataModule(void);
	~CMsgDataModule(void);
private:
	BOOL GetMsgUserList(IN tstring & szUserName,IN OUT CViewTree & TreeCtl,IN HTREEITEM hItem );
	BOOL GetUserProjectList(IN tstring & szUserName,IN OUT CViewTree & TreeCtl,IN HTREEITEM hItem );
	BOOL GetMsgInfo(tstring & szMsgInfoAdd,_tagUserMsgInfo & tagUserMsgInfo);
	BOOL GetMsgByPath(tstring & szPath,tstring & szFinder,vector<_tagMsgBody> & Msg);
	BOOL SendMsgByPath(tstring & szPath,tstring & szMsgName,_tagMsgBody & Msg);

	map<tstring,void * ,less<tstring> > m_IndexMap;
	map<tstring,void * ,less<tstring> > m_TreeIndexMap;
};


class CMsgShareData :public CUiSharedData
{
public:

	vector<_tagMsgBody> m_MsgArray;
	_tagUserMsgInfo		m_CurUserMsgInfo;

	CMsgShareData()
	{
		m_bGet=FALSE;
		
	};
	~CMsgShareData(){};
	BOOL init();
	BOOL SendMessage(tstring & szMsgBoby);
protected:
	BOOL m_bGet;

private:
};