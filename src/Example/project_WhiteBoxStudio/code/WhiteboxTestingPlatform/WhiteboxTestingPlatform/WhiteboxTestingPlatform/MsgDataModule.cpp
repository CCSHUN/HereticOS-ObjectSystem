#include "StdAfx.h"
#include "MsgDataModule.h"
#include "WhiteboxTestingPlatform.h"

CMsgDataModule::CMsgDataModule(void)
{
}

CMsgDataModule::~CMsgDataModule(void)
{
}


BOOL CMsgDataModule::GetMsgByPath(tstring & szPath,tstring & szFinder,vector<_tagMsgBody> & Msg)
{
	CObjectSystemInterface::_tagDirectoryInfo Info;
	CObjectSystemInterface::SYSTEMERROR error;
	if(gpObjectSystem->GetDirectoryInfo(szPath,szFinder,Info,&error)==FALSE)
	{
		return FALSE;
	}
	//tstring szMsgPath;
	_tagMsgBody_Wrap MsgBoby;
	for(unsigned int n=0;n<Info.DirectoryInfoArray.size();n++)
	{
		MsgBoby.m_szAddr=szPath+Info.DirectoryInfoArray[n].ObjectName;
		if(MsgBoby.GetObject())
		{
			Msg.push_back(MsgBoby.m_Data);
		}
		else
		{
			return FALSE;
		}
	}
	return TRUE;
	//_ta
}

BOOL CMsgDataModule::SendMsgByPath(tstring & szSendUser,tstring & szPath,_tagMsgBody & Msg)
{
	CObjectSystemInterface::_tagDirectoryInfo Info;
	//CObjectSystemInterface::SYSTEMERROR error;
	
	_tagMsgBody_Wrap MsgBoby;
	_tagUserMsgInfo_Wrap MsgInfo;
	//for(unsigned int n=0;n<Msg.szRecvUserList.size();n++)
	{
		
		//30秒自动解锁
		MsgInfo.m_szAddr=szPath+tstring(_T("\\MsgInfo"));
		MsgInfo.m_ObjectState.szLockUser=szSendUser;
		MsgInfo.m_ObjectState.bLock=TRUE;
		MsgInfo.m_ObjectState.nType=CObjectSystemInterface::AutoProlong;
		MsgInfo.m_ObjectState.nLockTime=6*1000;
		BOOL bSendOk=FALSE;
		for(unsigned int i=0;i<20;i++)
		{
			if(MsgInfo.GetObject())
			{
				//增加新消息,增加消息总数
				if(MsgInfo.m_ObjectState.szLockUser!=szSendUser)
				{
					::Sleep(500);
					continue;
				}else
				{
					//更新消息元信息
					_tagUserMsgInfo Info=MsgInfo.m_Data;
					Info.nMsgNum++;
					TCHAR	szMsgNum[32];
					tstring szMsgName=theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetCurTime()
						+_T("#");
					szMsgName+=itoa_t(GetTickCount(),szMsgNum,10);
					szMsgName+=itoa_t(Info.nMsgNum,szMsgNum,10);
					Info.szNewMsgIndex.push_back(szMsgName);
					MsgInfo.m_Data=Info;

					if(MsgInfo.UpDataObject())
					{
						//保存消息体
						MsgBoby.m_szAddr=szPath+szMsgName;
						if(MsgBoby.UpDataObject())
						{
							bSendOk=TRUE;
						}

						break;

					}
					
				}
				
			}
			else
			{
				//return FALSE;
				break;
			}
		}

		_DebugOutput(_T("CMsgDataModule::SendMsgByPath"),_T("SendTo %s %s"),szPath.c_str(),bSendOk?_T("成功"):_T("失败"));
		
	}
	return TRUE;
	//_ta
}

//用户目录结构
//UserInfo\
//		|---UserMap\        //存放用户信息
//				|----xxxx   //xxxx为用户名
//		|---UserOwnProject\	//存放用户关注的项目列表信息
//				|----xxxx   //xxxx为用户名
//		|---UserMsg\		//存放用户接受到的消息
//				|----xxxx   //xxxx为用户名
//					 |----PrivateMsg\ //存放私人消息信息
//								|----xxxx\ //存放与xxxx用户的消息记录
//										|----2013-05-27#tickcount#Msg	//消息体
//										|----MsgInfo　//存放与该用户相关的总体信息
//					 |----SystemMsg\	//存放系统消息
//								|----2013-05-27#tickcount#Msg	//消息体
//								|----MsgInfo　//存放与该用户相关的总体信息
//					 |----GroupMsgIndex		//参与的讨论组索引
//项目 没有对应数据结构，只有目录结构
// WhiteBoxTestProject\  所有项目相关数据结构放在此目录下
//		|----------------Project_XXXX\    每个项目一个目录，XXXX为项目名称
//								|-------ChildTest_XXXX\		每次测试项目名称
//                                            |----------Worksheet		项目工作单对象XML
//											  |----------CheckCfg		项目检查工具配置对象XML，对应结构_tagProjectConfig		
//											  |----------TestReport		项目测试报告对象XML
//											  |----------ProjectState	项目状态对象
//											  |----------ProjectConfig	项目全局配置信息，为将来扩展做规范定义
//								|-------GroupMsg\
//											  |----2013-05-27#tickcount#Msg	//消息体
//											  |----MsgInfo　//存放与该讨论组相关的总体信息
//								|-------ProjectUser						项目用户列表

BOOL CMsgDataModule::GetUserMsg(tstring & szUserName,tstring & szDstUserName,tstring & szFinder,OUT vector<_tagMsgBody> & Body)
{
	tstring szMsgPath=tstring(_T("UserInfo\\UserMsg\\"))+szUserName+tstring(_T("\\PrivateMsg\\"))+szDstUserName+tstring(_T("\\"));
	return GetMsgByPath(szMsgPath,szFinder,Body);
}

BOOL CMsgDataModule::GetSystemMsg(tstring & szUserName,tstring & szFinder,OUT vector<_tagMsgBody> & Body)
{
	tstring szMsgPath=tstring(_T("UserInfo\\UserMsg\\"))+szUserName+tstring(_T("\\SystemMsg\\"));
	return GetMsgByPath(szMsgPath,szFinder,Body);
}

BOOL CMsgDataModule::GetProjectMsg(tstring & szProjectName,tstring & szFinder,OUT vector<_tagMsgBody> & Body)
{
	tstring szMsgPath=tstring(_T("WhiteBoxTestProject\\Project_"))+szProjectName+tstring(_T("\\GroupMsg\\"));
	return GetMsgByPath(szMsgPath,szFinder,Body);
}

BOOL CMsgDataModule::SendUserMsg(tstring & szUserName,tstring & szDstUserName,_tagMsgBody & msg)
{
	tstring szMsgPath=tstring(_T("UserInfo\\UserMsg\\"))+szUserName+tstring(_T("\\PrivateMsg\\"))+szDstUserName+tstring(_T("\\"));

	return SendMsgByPath(szUserName,szMsgPath,msg);
}

BOOL CMsgDataModule::SendProjectMsg(tstring & szUserName,tstring & szDstProjectName,_tagMsgBody & msg)
{
	tstring szMsgPath=tstring(_T("WhiteBoxTestProject\\Project_"))+szDstProjectName+tstring(_T("\\GroupMsg\\"));
	return SendMsgByPath(szUserName,szMsgPath,msg);
}

BOOL CMsgDataModule::SendSystemMsg(tstring & szDstUserName,_tagMsgBody & msg)
{
	tstring szMsgPath=tstring(_T("UserInfo\\UserMsg\\"))+szDstUserName+tstring(_T("\\SystemMsg\\"));
	return SendMsgByPath(szDstUserName,szMsgPath,msg);
}
BOOL CMsgShareData::SendMessage(tstring & szMsgBoby)
{
	return TRUE;
}

BOOL CMsgDataModule::GetMsgUserList(IN tstring & szUserName,IN OUT CViewTree & TreeCtl,IN HTREEITEM hItem )
{
	tstring szMsgDir=tstring(_T("UserInfo\\UserMsg\\"))+szUserName+tstring(_T("\\PrivateMsg"));
	CObjectSystemInterface::_tagDirectoryInfo Info;
	CObjectSystemInterface::SYSTEMERROR error;
	tstring szFinder=_T("*");
	if(gpObjectSystem->GetDirectoryInfo(szMsgDir,szFinder,Info,&error)==FALSE)
	{
		return FALSE;
	}
	//tstring szMsgPath;
	CMsgShareData * pShareData;
	_tagMsgBody_Wrap MsgBoby;
	for(unsigned int n=0;n<Info.DirectoryInfoArray.size();n++)
	{
		if(Info.DirectoryInfoArray[n].ObjectType==CObjectSystemInterface::Directory)
		{
			//UserList.push_back(Info.DirectoryInfoArray[n].ObjectName);
			//CStandardSharedData * pShareData;
			//=new CStandardSharedData;
			tstring szMsgPath=szMsgDir+_T("\\")+Info.DirectoryInfoArray[n].ObjectName;
			if(m_IndexMap.find(tstring(szMsgPath))!=m_IndexMap.end())
			{
				pShareData=(CMsgShareData *)m_IndexMap[tstring(szMsgPath)];
			}else
			{
				pShareData=new CMsgShareData;
				m_IndexMap[tstring(szMsgPath)]=(void *)pShareData;
			}
			//pShareData->m_szStandardName=szMsgPath;

			HTREEITEM hSrcSub = TreeCtl.InsertItem(Info.DirectoryInfoArray[n].ObjectName.c_str(), 2, 2, hItem);
			TreeIndex * pIndex=new TreeIndex;
			pIndex->IndexList.push_back(szMsgDir);
			pIndex->IndexList.push_back(Info.DirectoryInfoArray[n].ObjectName);
			pIndex->szPageName=Info.DirectoryInfoArray[n].ObjectName;
			pIndex->szPageType=ADDR_MESSAGE;
			pIndex->pSharedObject=pShareData;

			TreeCtl.SetItemData(hSrcSub,(DWORD_PTR)pIndex);
			//构造一个共享类 存放共享的数据

			{
				tstring szAddr=theApp.m_WorkSpaceWndManger.m_ProjectDataModel.GetProjectWholePath(pIndex);
				if(szAddr[szAddr.length()-1]=='\\')
				{
					//szAddr[szAddr.length()-1]=0;
					szAddr.erase(szAddr.length()-1);
				}

				m_TreeIndexMap[szAddr]=pIndex;
			}
		}
	}
	return TRUE;
}


BOOL CMsgDataModule::GetUserProjectList(IN tstring & szUserName,IN OUT CViewTree & TreeCtl,IN HTREEITEM hItem )
{
	return TRUE;
}
BOOL CMsgDataModule::GetMsgInfo(tstring & szMsgInfoAdd,_tagUserMsgInfo & tagUserMsgInfo)
{
	return TRUE;
}


BOOL CMsgDataModule::GetMsgUiTree(CViewTree & TreeCtl)
{
	TreeCtl.DeleteAllItems();

	HTREEITEM hRoot = TreeCtl.InsertItem(MSG_WORKSPACE, 0, 0);
	TreeCtl.SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);
	GetMsgUserList(theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetLoginName(),TreeCtl,hRoot);
	return TRUE;
}