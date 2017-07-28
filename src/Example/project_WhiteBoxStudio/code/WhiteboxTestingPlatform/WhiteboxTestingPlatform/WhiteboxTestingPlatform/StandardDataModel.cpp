#include "StdAfx.h"
#include "StandardDataModel.h"
#include "WhiteboxTestingPlatform.h"
CStandardDataModel::CStandardDataModel(void)
{
}

CStandardDataModel::~CStandardDataModel(void)
{
}
#define UNITE_STANDARD_NAME _T("MachineCheckStandardLib")
#define THIRD_STANDARD_NAME _T("ThirdStandardlib")
#define STANDARD_ERROR_TYPE_ADDR			_T("MachineCheckStandardTypeLib")
#define STANDARD_ERRORWARNING_ADDR			_T("ErrorWarningDefine")


BOOL CStandardDataModel::NewStandard(tstring szStandardName)
{
	tstring szPath=tstring(_T("WhiteBoxTestStandard\\MachineCheckStandard\\MachineCheckStandard_"))+szStandardName+tstring(_T("\\"));
	_tagMachineCheckStandardLib_Wrap		MachineCheckStandardLib;
	_tagThirdStandardlib_Wrap				ThirdStandardlib;
	_tagMachineCheckStandardTypeLib_Wrap	MachineCheckStandardTypeLib;
	_tagErrorWarningArray_Wrap				ErrorWarningArray;

	MachineCheckStandardLib.m_szAddr=szPath+UNITE_STANDARD_NAME;
	BOOL bOk=MachineCheckStandardLib.UpDataObject();
	if(bOk==FALSE) return FALSE;
	ThirdStandardlib.m_szAddr=szPath+THIRD_STANDARD_NAME;
	ThirdStandardlib.UpDataObject();
	if(bOk==FALSE) return FALSE;
	MachineCheckStandardTypeLib.m_szAddr=szPath+STANDARD_ERROR_TYPE_ADDR;
	MachineCheckStandardTypeLib.UpDataObject();
	if(bOk==FALSE) return FALSE;

	ErrorWarningArray.m_szAddr=szPath+STANDARD_ERRORWARNING_ADDR;
	ErrorWarningArray.UpDataObject();
	if(bOk==FALSE) return FALSE;


	return TRUE;
}
BOOL CStandardDataModel::DelStandard(tstring szStandardName)
{
	tstring szPath=tstring(_T("WhiteBoxTestStandard\\MachineCheckStandard\\MachineCheckStandard_"))+szStandardName;
	CObjectSystemInterface::SYSTEMERROR Error;
	return gpObjectSystem->DeleteObject(szPath,&Error);
}

BOOL CStandardDataModel::GoProjectPage(tstring & szAddr)
{
	TreeIndex * pindex;
	//CProjectSharedData * pShareData;
	if(m_TreeIndexMap.find(tstring(szAddr))!=m_TreeIndexMap.end())
	{
		pindex=(TreeIndex *)m_TreeIndexMap[tstring(szAddr)];
	}else
	{
		AfxMessageBox(_T("地址不可用"));
		return FALSE;
	}
	theApp.m_WorkSpaceWndManger.ShowWorkPage(pindex);
	return TRUE;
}

BOOL CStandardDataModel::GetStandardTree(CViewTree & TreeCtl)
{

	TreeCtl.DeleteAllItems();

	HTREEITEM hRoot = TreeCtl.InsertItem(_T("所有标准"), 0, 0);
	TreeCtl.SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);
	

	//MachineCheckStandard_
	tstring szPath=tstring(_T("WhiteBoxTestStandard\\MachineCheckStandard\\"));
	CObjectSystemInterface::_tagDirectoryInfo Info;
	CObjectSystemInterface::SYSTEMERROR error;
	tstring szFinder=_T("*");
	if(gpObjectSystem->GetDirectoryInfo(szPath,szFinder,Info,&error)==FALSE)
	{
		return FALSE;
	}


	HTREEITEM item;

	TreeIndex * pIndex;

	
	HTREEITEM hSrcSub ;

	for(unsigned int i=0;i<Info.DirectoryInfoArray.size();i++)
	{
		const TCHAR * szStandardName=Info.DirectoryInfoArray[i].ObjectName.c_str()+strlen_t(_T("MachineCheckStandard_"));
		CStandardSharedData * pShareData;
		//=new CStandardSharedData;
		if(m_IndexMap.find(tstring(szStandardName))!=m_IndexMap.end())
		{
			pShareData=(CStandardSharedData *)m_IndexMap[tstring(szStandardName)];
		}else
		{
			pShareData=new CStandardSharedData;
			m_IndexMap[tstring(szStandardName)]=(void *)pShareData;
		}
		pShareData->m_szStandardName=szStandardName;

		hSrcSub = TreeCtl.InsertItem(szStandardName, 0, 0, hRoot);
		pIndex=new TreeIndex;
		pIndex->IndexList.push_back(tstring(szStandardName));
		pIndex->szPageName=TEST_STANDARD_WORKSPACE;
		pIndex->szPageType=ADDR_STAREND;
		pIndex->pSharedObject=pShareData;

		TreeCtl.SetItemData(hSrcSub,(DWORD_PTR)pIndex);
		//构造一个共享类 存放共享的数据
		

		item=TreeCtl.InsertItem(TEST_STANDARD_UNITE_WORKSPACE, 2, 2, hSrcSub);

		pIndex=new TreeIndex;
		pIndex->IndexList.push_back(tstring(szStandardName));
		pIndex->IndexList.push_back(tstring(TEST_STANDARD_UNITE_WORKSPACE));
		pIndex->szPageName=TEST_STANDARD_UNITE_WORKSPACE;
		pIndex->szPageType=ADDR_STAREND;
		pIndex->pSharedObject=pShareData;
		TreeCtl.SetItemData(item,(DWORD_PTR)pIndex);
		{
			tstring szAddr=theApp.m_WorkSpaceWndManger.m_ProjectDataModel.GetProjectWholePath(pIndex);
			if(szAddr[szAddr.length()-1]=='\\')
			{
				//szAddr[szAddr.length()-1]=0;
				szAddr.erase(szAddr.length()-1);
			}

			m_TreeIndexMap[szAddr]=pIndex;
		}

		item=TreeCtl.InsertItem(TEST_STANDARD_THIRD_WORKSPACE, 2, 2, hSrcSub);

		pIndex=new TreeIndex;
		pIndex->IndexList.push_back(tstring(szStandardName));
		pIndex->IndexList.push_back(tstring(TEST_STANDARD_THIRD_WORKSPACE));
		pIndex->szPageName=TEST_STANDARD_THIRD_WORKSPACE;
		pIndex->szPageType=ADDR_STAREND;
		pIndex->pSharedObject=pShareData;
		TreeCtl.SetItemData(item,(DWORD_PTR)pIndex);
		{
			tstring szAddr=theApp.m_WorkSpaceWndManger.m_ProjectDataModel.GetProjectWholePath(pIndex);
			if(szAddr[szAddr.length()-1]=='\\')
			{
				//szAddr[szAddr.length()-1]=0;
				szAddr.erase(szAddr.length()-1);
			}

			m_TreeIndexMap[szAddr]=pIndex;
		}

		item=TreeCtl.InsertItem(TEST_STANDARD_ERROR_TYPE_WORKSPACE, 2, 2, hSrcSub);
		pIndex=new TreeIndex;
		pIndex->IndexList.push_back(tstring(szStandardName));
		pIndex->IndexList.push_back(tstring(TEST_STANDARD_ERROR_TYPE_WORKSPACE));
		pIndex->szPageName=TEST_STANDARD_ERROR_TYPE_WORKSPACE;
		pIndex->szPageType=ADDR_STAREND;
		pIndex->pSharedObject=pShareData;
		TreeCtl.SetItemData(item,(DWORD_PTR)pIndex);
		{
			tstring szAddr=theApp.m_WorkSpaceWndManger.m_ProjectDataModel.GetProjectWholePath(pIndex);
			if(szAddr[szAddr.length()-1]=='\\')
			{
				//szAddr[szAddr.length()-1]=0;
				szAddr.erase(szAddr.length()-1);
			}

			m_TreeIndexMap[szAddr]=pIndex;
		}
		//TreeCtl.Expand(hSrcSub, TVE_EXPAND);
	}
	

	TreeCtl.Expand(hRoot, TVE_EXPAND);

	return TRUE;
}

BOOL CStandardDataModel::GetUniteStandardByName(IN tstring & szStandardName,OUT _tagMachineCheckStandardLib & MachineCheckStandardLib)
{
	tstring szPath=tstring(_T("WhiteBoxTestStandard\\MachineCheckStandard\\"));
	szPath+=_T("MachineCheckStandard_");
	szPath+=szStandardName;szPath+=_T("\\");
	_tagMachineCheckStandardLib_Wrap lib;
	lib.m_szAddr=szPath+UNITE_STANDARD_NAME;
	if(lib.GetObject())
	{
		MachineCheckStandardLib=lib.m_Data;
		return TRUE;
	}
	return FALSE;
}

BOOL CStandardDataModel::GetUniteStandardByName(IN tstring & szStandardName,OUT _tagMachineCheckStandardLib_Wrap & MachineCheckStandardLib)
{
	tstring szPath=tstring(_T("WhiteBoxTestStandard\\MachineCheckStandard\\"));
	szPath+=_T("MachineCheckStandard_");
	szPath+=szStandardName;szPath+=_T("\\");
	MachineCheckStandardLib.m_szAddr=szPath+UNITE_STANDARD_NAME;
	if(MachineCheckStandardLib.GetObject())
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CStandardDataModel::UpDataUniteStandardByName(IN tstring & szStandardName,IN _tagMachineCheckStandardLib & MachineCheckStandardLib)
{
	tstring szPath=tstring(_T("WhiteBoxTestStandard\\MachineCheckStandard\\"));
	szPath+=_T("MachineCheckStandard_");
	szPath+=szStandardName;szPath+=_T("\\");
	_tagMachineCheckStandardLib_Wrap lib;
	lib.m_szAddr=szPath+UNITE_STANDARD_NAME;
	lib.m_Data=MachineCheckStandardLib;
	return lib.UpDataObject();
}

BOOL CStandardDataModel::UpDataUniteStandardByName(IN tstring & szStandardName,IN _tagMachineCheckStandardLib_Wrap & MachineCheckStandardLib)
{
	tstring szPath=tstring(_T("WhiteBoxTestStandard\\MachineCheckStandard\\"));
	szPath+=_T("MachineCheckStandard_");
	szPath+=szStandardName;szPath+=_T("\\");
	MachineCheckStandardLib.m_szAddr=szPath+UNITE_STANDARD_NAME;
	return MachineCheckStandardLib.UpDataObject();
}

BOOL CStandardDataModel::GetThirdStandardByName(IN tstring & szStandardName,OUT _tagThirdStandardlib & ThirdStandardLib)
{

	tstring szPath=tstring(_T("WhiteBoxTestStandard\\MachineCheckStandard\\"));
	szPath+=_T("MachineCheckStandard_");
	szPath+=szStandardName;szPath+=_T("\\");
	_tagThirdStandardlib_Wrap lib1;
	lib1.m_szAddr=szPath+THIRD_STANDARD_NAME;
	if(lib1.GetObject())
	{
		ThirdStandardLib=lib1.m_Data;
		return TRUE;
	}
	return FALSE;
}

BOOL CStandardDataModel::GetThirdStandardByName(IN tstring & szStandardName,OUT _tagThirdStandardlib_Wrap & ThirdStandardLib)
{

	tstring szPath=tstring(_T("WhiteBoxTestStandard\\MachineCheckStandard\\"));
	szPath+=_T("MachineCheckStandard_");
	szPath+=szStandardName;szPath+=_T("\\");
	ThirdStandardLib.m_szAddr=szPath+THIRD_STANDARD_NAME;
	if(ThirdStandardLib.GetObject())
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CStandardDataModel::GetStandardErrorTypeNameLib(IN tstring & szStandardName,OUT _tagMachineCheckStandardTypeLib & lib)
{
	tstring szPath=tstring(_T("WhiteBoxTestStandard\\MachineCheckStandard\\"));
	szPath+=_T("MachineCheckStandard_");
	szPath+=szStandardName;szPath+=_T("\\");
	_tagMachineCheckStandardTypeLib_Wrap lib1;
	lib1.m_szAddr=szPath+STANDARD_ERROR_TYPE_ADDR;
	if(lib1.GetObject())
	{
		lib=lib1.m_Data;
		return TRUE;
	}
	return FALSE;
}

BOOL CStandardDataModel::GetStandardErrorTypeNameLib(IN tstring & szStandardName,OUT _tagMachineCheckStandardTypeLib_Wrap & lib)
{
	tstring szPath=tstring(_T("WhiteBoxTestStandard\\MachineCheckStandard\\"));
	szPath+=_T("MachineCheckStandard_");
	szPath+=szStandardName;szPath+=_T("\\");
	lib.m_szAddr=szPath+STANDARD_ERROR_TYPE_ADDR;
	if(lib.GetObject())
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CStandardDataModel::UpdataStandardErrorTypeNameLib(IN tstring & szStandardName,OUT _tagMachineCheckStandardTypeLib & lib)
{
	tstring szPath=tstring(_T("WhiteBoxTestStandard\\MachineCheckStandard\\"));
	szPath+=_T("MachineCheckStandard_");
	szPath+=szStandardName;szPath+=_T("\\");
	_tagMachineCheckStandardTypeLib_Wrap lib1;
	lib1.m_szAddr=szPath+STANDARD_ERROR_TYPE_ADDR;
	lib1.m_Data=lib;
	return lib1.UpDataObject();
}

BOOL CStandardDataModel::UpdataStandardErrorTypeNameLib(IN tstring & szStandardName,OUT _tagMachineCheckStandardTypeLib_Wrap & lib)
{
	tstring szPath=tstring(_T("WhiteBoxTestStandard\\MachineCheckStandard\\"));
	szPath+=_T("MachineCheckStandard_");
	szPath+=szStandardName;szPath+=_T("\\");
	lib.m_szAddr=szPath+STANDARD_ERROR_TYPE_ADDR;
	return lib.UpDataObject();
}

BOOL CStandardDataModel::GetStandardErrorWarningNameArray(IN tstring & szStandardName,OUT _tagErrorWarningArray & lib)
{
	tstring szPath=tstring(_T("WhiteBoxTestStandard\\MachineCheckStandard\\"));
	szPath+=_T("MachineCheckStandard_");
	szPath+=szStandardName;szPath+=_T("\\");
	_tagErrorWarningArray_Wrap lib1;
	lib1.m_szAddr=szPath+STANDARD_ERRORWARNING_ADDR;
	if(lib1.GetObject())
	{
		lib=lib1.m_Data;
		return TRUE;
	}
	return FALSE;
}
BOOL CStandardDataModel::GetStandardErrorWarningNameArray(IN tstring & szStandardName,OUT _tagErrorWarningArray_Wrap & lib)
{
	tstring szPath=tstring(_T("WhiteBoxTestStandard\\MachineCheckStandard\\"));
	szPath+=_T("MachineCheckStandard_");
	szPath+=szStandardName;szPath+=_T("\\");
	lib.m_szAddr=szPath+STANDARD_ERRORWARNING_ADDR;
	if(lib.GetObject())
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CStandardDataModel::UpdataStandardErrorWarningNameArray(IN tstring & szStandardName,OUT _tagErrorWarningArray & lib)
{
	tstring szPath=tstring(_T("WhiteBoxTestStandard\\MachineCheckStandard\\"));
	szPath+=_T("MachineCheckStandard_");
	szPath+=szStandardName;szPath+=_T("\\");
	_tagErrorWarningArray_Wrap lib1;
	lib1.m_szAddr=szPath+STANDARD_ERRORWARNING_ADDR;
	lib1.m_Data=lib;
	return lib1.UpDataObject();
}

BOOL CStandardDataModel::UpdataStandardErrorWarningNameArray(IN tstring & szStandardName,OUT _tagErrorWarningArray_Wrap & lib)
{
	tstring szPath=tstring(_T("WhiteBoxTestStandard\\MachineCheckStandard\\"));
	szPath+=_T("MachineCheckStandard_");
	szPath+=szStandardName;szPath+=_T("\\");
	lib.m_szAddr=szPath+STANDARD_ERRORWARNING_ADDR;
	return lib.UpDataObject();
}

BOOL CStandardDataModel::UpDataThirdStandardByName(IN tstring & szStandardName,IN _tagThirdStandardlib & ThirdStandardLib)
{
	tstring szPath=tstring(_T("WhiteBoxTestStandard\\MachineCheckStandard\\"));
	szPath+=_T("MachineCheckStandard_");
	szPath+=szStandardName;szPath+=_T("\\");
	_tagThirdStandardlib_Wrap lib1;
	lib1.m_szAddr=szPath+THIRD_STANDARD_NAME;
	lib1.m_Data=ThirdStandardLib;
	return lib1.UpDataObject();
}

BOOL CStandardDataModel::UpDataThirdStandardByName(IN tstring & szStandardName,IN _tagThirdStandardlib_Wrap & ThirdStandardLib)
{
	tstring szPath=tstring(_T("WhiteBoxTestStandard\\MachineCheckStandard\\"));
	szPath+=_T("MachineCheckStandard_");
	szPath+=szStandardName;szPath+=_T("\\");
	ThirdStandardLib.m_szAddr=szPath+THIRD_STANDARD_NAME;
	return ThirdStandardLib.UpDataObject();
}

BOOL CStandardDataModel::GetStandardByName(IN tstring & szStandardName,OUT _tagMachineCheckStandardLib & MachineCheckStandardLib,OUT _tagThirdStandardlib & ThirdStandardLib)
{
	BOOL bRet=GetUniteStandardByName(szStandardName,MachineCheckStandardLib);
	if(bRet)
	{
		bRet=GetThirdStandardByName(szStandardName,ThirdStandardLib);
	}
	return bRet;
}

BOOL CStandardDataModel::UpDataStandardByName(IN tstring & szStandardName,IN _tagMachineCheckStandardLib & MachineCheckStandardLib,IN _tagThirdStandardlib & ThirdStandardLib)
{
	BOOL bRet=UpDataUniteStandardByName(szStandardName,MachineCheckStandardLib);
	if(bRet)
	{
		bRet=UpDataThirdStandardByName(szStandardName,ThirdStandardLib);
	}
	return bRet;
}

BOOL CStandardDataModel::GetAllStandardNameArray(OUT vector<tstring> & NameList)
{
	tstring szPath=tstring(_T("WhiteBoxTestStandard\\MachineCheckStandard\\"));
	CObjectSystemInterface::_tagDirectoryInfo Info;
	CObjectSystemInterface::SYSTEMERROR error;
	tstring szFinder=_T("*");
	if(gpObjectSystem->GetDirectoryInfo(szPath,szFinder,Info,&error)==FALSE)
	{
		return FALSE;
	}

	for(unsigned int i=0;i<Info.DirectoryInfoArray.size();i++)
	{
		const TCHAR * szStandardName=Info.DirectoryInfoArray[i].ObjectName.c_str()+strlen_t(_T("MachineCheckStandard_"));
		if(szStandardName)
		{
			NameList.push_back(tstring(szStandardName));
		}
	}
	return TRUE;
}

BOOL CStandardSharedData::ReGetObject()
{
	m_bGet=FALSE;
	return GetObject();
}

BOOL CStandardSharedData::GetObject()
{
	if(m_bGet==FALSE)
	{
		if(theApp.m_WorkSpaceWndManger.m_StandardDataModel.GetStandardErrorWarningNameArray(m_szStandardName,m_ErrorWarningArray))
		{
			if(theApp.m_WorkSpaceWndManger.m_StandardDataModel.GetStandardErrorTypeNameLib(m_szStandardName,m_MachineCheckStandardTypeLib))
			{
				if(theApp.m_WorkSpaceWndManger.m_StandardDataModel.GetThirdStandardByName(m_szStandardName,m_ThirdStandardLib))
				{
					if(theApp.m_WorkSpaceWndManger.m_StandardDataModel.GetUniteStandardByName(m_szStandardName,m_MachineCheckStandardLib))
					{
						if(theApp.m_WorkSpaceWndManger.m_StandardDataModel.GetStandardErrorWarningNameArray(m_szStandardName,m_ErrorWarningArray))
						{
							m_bGet=TRUE;
							return TRUE;
						}
					}
				}
			}
		}
		
	}
	return FALSE;
}
BOOL CStandardSharedData::UpdataObject()
{
	//return theApp.m_WorkSpaceWndManger.m_StandardDataModel.UpDataStandardByName(m_szStandardName,m_MachineCheckStandardLib,m_ThirdStandardLib);
	BOOL bRet=FALSE;
	m_bGet=FALSE;
	if(m_bUniteLibWrited)
	{
		bRet=theApp.m_WorkSpaceWndManger.m_StandardDataModel.UpDataUniteStandardByName(m_szStandardName,m_MachineCheckStandardLib);
		if(bRet==TRUE)
		{
			m_bUniteLibWrited=FALSE;
		}else
		{
			return bRet;
		}
	}

	if(m_bThirdLibWrited)
	{
		bRet=theApp.m_WorkSpaceWndManger.m_StandardDataModel.UpDataThirdStandardByName(m_szStandardName,m_ThirdStandardLib);
		if(bRet==TRUE)
		{
			m_bThirdLibWrited=FALSE;
		}else
		{
			return bRet;
		}
	}

	if(m_bErrorTypeLibWrited)
	{
		bRet=theApp.m_WorkSpaceWndManger.m_StandardDataModel.UpdataStandardErrorTypeNameLib(m_szStandardName,m_MachineCheckStandardTypeLib);
		if(bRet==TRUE)
		{
			m_bThirdLibWrited=FALSE;
		}else
		{
			return bRet;
		}
	}

	if(m_bErrorWarningLibWrited)
	{
		bRet=theApp.m_WorkSpaceWndManger.m_StandardDataModel.UpdataStandardErrorWarningNameArray(m_szStandardName,m_ErrorWarningArray);
		if(bRet==TRUE)
		{
			m_bThirdLibWrited=FALSE;
		}else
		{
			return bRet;
		}
	}

	return bRet;

}

BOOL CStandardSharedData::init()
{
	if(m_bGet==FALSE)
	{
		//初始化对象锁
		m_MachineCheckStandardLib.m_ObjectState.szLockUser=theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetLoginName();
		m_MachineCheckStandardLib.m_ObjectState.bLock=FALSE;
		m_MachineCheckStandardLib.m_ObjectState.nLockTime=20*60*1000;
		m_MachineCheckStandardLib.m_ObjectState.nType=CObjectSystemInterface::Nonmoral;

		m_ThirdStandardLib.m_ObjectState.szLockUser=theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetLoginName();
		m_ThirdStandardLib.m_ObjectState.bLock=FALSE;
		m_ThirdStandardLib.m_ObjectState.nLockTime=20*60*1000;
		m_ThirdStandardLib.m_ObjectState.nType=CObjectSystemInterface::Nonmoral;

		m_MachineCheckStandardTypeLib.m_ObjectState.szLockUser=theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetLoginName();
		m_MachineCheckStandardTypeLib.m_ObjectState.bLock=FALSE;
		m_MachineCheckStandardTypeLib.m_ObjectState.nLockTime=5*60*1000;
		m_MachineCheckStandardTypeLib.m_ObjectState.nType=CObjectSystemInterface::Nonmoral;

		m_ErrorWarningArray.m_ObjectState.szLockUser=theApp.m_WorkSpaceWndManger.m_AccessDataModel.GetLoginName();
		m_ErrorWarningArray.m_ObjectState.bLock=FALSE;
		m_ErrorWarningArray.m_ObjectState.nLockTime=5*60*1000;
		m_ErrorWarningArray.m_ObjectState.nType=CObjectSystemInterface::Nonmoral;

		if(GetObject())
		{
			m_bGet=TRUE;
			return TRUE;
		}
	}
	return FALSE;
}