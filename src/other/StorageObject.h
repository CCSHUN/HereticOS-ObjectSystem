///////////////////////////////////////////////////////////////////////////////////
//	Copyright 2017 shushen,ye
//	Licensed under the Apache License, Version 2.0 (the "License");
//	you may not use this file except in compliance with the License.
//	You may obtain a copy of the License at
//	http://www.apache.org/licenses/LICENSE-2.0
//	Unless required by applicable law or agreed to in writing, software
//	distributed under the License is distributed on an "AS IS" BASIS,
//	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//	See the License for the specific language governing permissions and
//	limitations under the License.
///////////////////////////////////////////////////////////////////////////////////


//作者：叶树深 2010.6.10
//XML序列化存储对象

#pragma once

typedef enum
{
	ToBuffer,
	ToFile,
}StorageObjectType;


#include "XmlRender.h"
class XMLStorageObject : public StorageObjectInterface
{
public:
	XMLStorageObject()
	{
		m_szFile=_T("");
		m_hFile=0;
		m_pxml=0;
		m_ObjectCurSaveType=ObjectVal;
	};
	~XMLStorageObject()
	{
		if(m_pxml)
		{
			delete m_pxml;
		}
		if(m_hFile)
		{
			CloseHandle(m_hFile);
		}
	};
	tstring m_szFile;
	HANDLE m_hFile;
	CXmlRender * m_pxml;
	//序列化保存时暂存的当前深度
	unsigned int m_nCurDepth;
	BOOL m_bLastIsValue;
	BOOL m_bSave;
	CharacterType m_StringType;
	tstring m_XmlBuffer;
	StorageObjectType m_StorageObjectType;


	//当前节点数据
	typedef struct _tagXmlNodeInfo
	{
		tstring m_CurNodeName;
		tstring m_CurNodeAttributes;
		tstring m_CurNodeVal;
	}XmlNodeInfo;
	typedef enum
	{
		ObjectAttributes,
		ObjectVal,
	}ObjectCurSaveType;
	ObjectCurSaveType m_ObjectCurSaveType;
	list<XmlNodeInfo> m_XmlNodeInfoList;
	
	BOOL ReCreateFile()
	{
		if(m_hFile)
		{
			CloseHandle(m_hFile);
		}
		m_hFile = ::CreateFile(m_szFile.c_str(), GENERIC_READ|GENERIC_WRITE,
			FILE_SHARE_READ|FILE_SHARE_WRITE, NULL,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if(m_hFile==INVALID_HANDLE_VALUE)
		{
			return FALSE;
		}
		BYTE nHead[4]={0};
		DWORD nRetLen=0;
		switch(m_StringType)
		{
		case Ansi:

			break;
		case Unicode:
			nHead[0]=0xFF;nHead[1]=0xFE;
			WriteFile(m_hFile,&nHead,2,&nRetLen,NULL);
			break;
		case UTF8:
			//nHead=0xfeff;
			nHead[0] = 0xEF;
			nHead[1] = 0xBB;
			nHead[2] = 0xBF;
			WriteFile(m_hFile,&nHead,3,&nRetLen,NULL);
			break;

		default:
			break;
		}
		return TRUE;
	}

	template<typename StringType>
	BOOL WriteString(StringType * pStr,unsigned int nBufLen)
	{
		CMyString szOut(pStr,nBufLen);
		
		list<XmlNodeInfo>::iterator itBack=m_XmlNodeInfoList.end();
		itBack--;
		switch(m_ObjectCurSaveType)
		{
		case ObjectAttributes:
			itBack->m_CurNodeAttributes+=tstring(_T("=\""))+tstring((TCHAR*)szOut)+tstring(_T("\""));
			break;
		case ObjectVal:
			itBack->m_CurNodeVal+=tstring((TCHAR*)szOut);
			break;
		default:
			break;
		}
		
		return TRUE;
	}
	BOOL SaveXmlBuf()
	{
		//CMyString szOut(m_XmlBuffer,nBufLen);
		CMyString szOut((TCHAR *)m_XmlBuffer.c_str(),m_XmlBuffer.length()*sizeof(TCHAR));
		void * pBuf=NULL;
		DWORD nRetLen=0;
		switch(m_StringType)
		{
		case Ansi:
			pBuf=(char *)szOut;	
			break;
		case Unicode:
			pBuf=(WCHAR *)szOut;
			break;
		case UTF8:
			pBuf=(char *)szOut;	
			break;
		default:
			break;
		}
		switch(m_StorageObjectType)
		{
		case ToBuffer:
			//m_XmlBuffer+=tstring((TCHAR *)szOut);
			break;
		case ToFile:
			return WriteFile(m_hFile,pBuf,szOut.m_nRefBufLen,&nRetLen,NULL);
			break;
		default:
			return FALSE;
			break;
		}
		return TRUE;
	}
	BOOL init(tstring & szObject,StorageObjectType ObjectType,CharacterType nType=Ansi)
	{
		BOOL bRet=FALSE;
		m_bSave=FALSE;
		//m_szFile=szObject;
		m_nCurDepth=0;
		m_bLastIsValue=FALSE;
		m_StringType=nType;

		if(m_hFile)
		{
			CloseHandle(m_hFile);
		}
		
		int encodeing=XMLFILE_ENCODING_UNICODE;
		switch(nType)
		{
		case Ansi:
			encodeing=XMLFILE_ENCODING_ASNI;
			break;
		case Unicode:
			encodeing=XMLFILE_ENCODING_UNICODE;
			break;
		case UTF8:
			encodeing=XMLFILE_ENCODING_UTF8;
			break;
		default:
			return FALSE;
			break;
		}
		m_StorageObjectType=ObjectType;

		if(m_pxml) delete m_pxml;
		m_pxml=new CXmlRender;

		switch(m_StorageObjectType)
		{
		case ToBuffer:
			{
				CMyString szBuf((TCHAR *)szObject.c_str(),szObject.length()*sizeof(TCHAR));
				void * pXmlBuf=(char *)szBuf;
				if(szBuf.m_nRefBufLen)
				{
					if(m_pxml->LoadFromMem((BYTE *)pXmlBuf,
						szBuf.m_nRefBufLen,
						XMLFILE_ENCODING_ASNI)==false)
					{
						return FALSE;
					}
				}else
				{
					return FALSE;
				}

				
			}
			

			break;
		case ToFile:
			{
				m_szFile=szObject;
				m_hFile = ::CreateFile(m_szFile.c_str(), GENERIC_READ|GENERIC_WRITE,
					FILE_SHARE_READ|FILE_SHARE_WRITE, NULL,
					OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
				if(m_hFile==INVALID_HANDLE_VALUE)
				{
					//新建文件
					bRet=ReCreateFile();
					if(bRet==FALSE)
					{
						m_hFile=0;
						return FALSE;
					}
				}else
				{
					//打开文件

					if(m_pxml->LoadFromFile(m_szFile.c_str(),encodeing)==false)
					{
						CloseHandle(m_hFile);
						m_hFile=0;
						return FALSE;
					}
				}
			}
			break;
		default:
			return FALSE;
			break;
		}
		

		bRet=TRUE;
		return bRet;
	}
	BOOL LoadObject(SerializeLoadSaveInterface * pObj)
	{
		FieldAddr ChildAddr;
		CXmlNode node=m_pxml->GetRoot();
		if(node.IsValid())
		{
			return EnumXmlNode(pObj,&m_pxml->GetRoot(),&ChildAddr,&ChildAddr);
		}else
		{
			return FALSE;
		}
		
	}
	BOOL EnumXmlNode(SerializeLoadSaveInterface * pObj,CXmlNode * pNote,FieldAddr * pParent,FieldAddr * pHead)
	{
		LPCTSTR pstrName = NULL;
		LPCTSTR pstrValue = NULL;
		LPCTSTR pstrTotalNum = NULL;
		map<tstring,unsigned int,less<tstring> > FeildPos;
		FieldAddr ChildAddr;
		pParent->pChild=&ChildAddr;
		pObj->LoadObjectBegin(pObj);
		for(CXmlNode node = pNote->GetChild() ; node.IsValid(); node = node.GetSibling() ) 
		{

			ChildAddr.pFieldName =(TCHAR *) node.GetName();
			
			pstrValue = node.GetValue();
			if(ChildAddr.pFieldName)
			{
				map<tstring,unsigned int,less<tstring> >::iterator itMap=FeildPos.find(tstring(ChildAddr.pFieldName));
				if(itMap!=FeildPos.end())
				{
					itMap->second+=1;
					ChildAddr.nIndex=itMap->second;
				}else
				{
					FeildPos[tstring(ChildAddr.pFieldName)]=0;
					ChildAddr.nIndex=0;
				}
			}else
			{
				return FALSE;
			}


			SerializeLoadSaveInterface * pGetObj=0;
			if(tstring(_T("szReport_log"))==tstring(ChildAddr.pFieldName))
			{
				printf("asdasd");
			}

			if(pObj->LoadGetCurSerializeObject(ChildAddr,&pGetObj))
			{
				//int nstrValuelen=strlen(pstrValue);
				
				if(node.HasChildren()==false)
				{
					//最终值型不需要begin end控制
					if(pGetObj->LoadSetData(tstring(pstrValue))==FALSE)
					{
						return FALSE;
					}

				}

			}else
			{
				return FALSE;
			}

			if(node.GetChild().IsValid()) // 如果有子节点
			{

				if(EnumXmlNode( pGetObj,&node,&ChildAddr,pHead)==FALSE)
				{
					return FALSE;
				}
			}
			pObj->LoadCurObjectEnd(pGetObj);
		}
		pObj->LoadObjectEnd(pObj);
		return TRUE;
	}

	BOOL GetObjectInt(IN SerializeRunData * Addr,IN OUT void * pOutData,IN OUT unsigned int & nLen)
	{
		return TRUE;
	}
	BOOL SetObjectInt(IN SerializeRunData * Addr,IN void * pInData,IN OUT unsigned int & nLen)
	{
		return TRUE;
	}

	BOOL GetBinaryObject(IN SerializeRunData * Addr,IN OUT void * pOutData,IN OUT unsigned int & nLen)
	{
		memset(pOutData,0,nLen);
		return TRUE;
	}

	BOOL SetBinaryObject(IN SerializeRunData * Addr,IN void * pInData,IN OUT unsigned int & nLen)
	{
		return TRUE;
	}

	BOOL GetStringObject(IN SerializeRunData * Addr,IN OUT void * pOutData,IN OUT unsigned int & nLen)
	{
		memset(pOutData,0,nLen);
		return TRUE;
	}

	BOOL SetStringObject(IN SerializeRunData * Addr,IN void * pInData,IN OUT unsigned int & nLen)
	{
		return TRUE;
	}

	BOOL PushDataVal(IN void * pInData,IN OUT unsigned int & nLen)
	{
		char cpBuf[32] = {0};
		if(nLen==4)
		{
			_itoa_s(*(unsigned int *)pInData,cpBuf,10);
		}else if(nLen==8)
		{
			_ui64toa_s(*(unsigned __int64 *)pInData,cpBuf,32,10);
		}else if(nLen==2)
		{
			_itoa_s(*(USHORT *)pInData,cpBuf,10);
		}else
		{
			return FALSE;
		}

		DWORD nRetLen=0;
		m_bLastIsValue=TRUE;

		return WriteString((char *)cpBuf,strlen(cpBuf));

	}

	BOOL PushDataBinary(IN void * pInData,IN OUT unsigned int & nLen)
	{
		tstring szRst;
		DWORD nRetLen=0;
		EncodeHex((BYTE *)pInData,nLen,szRst);
		m_bLastIsValue=TRUE;
		return WriteString((TCHAR*)szRst.c_str(),szRst.length()*sizeof(TCHAR));
		//return WriteFile(m_hFile,(BYTE *)szRst.c_str(),szRst.length()*sizeof(TCHAR),&nRetLen,NULL);
	}

	BOOL PushDataString(IN LPTSTR pInData,IN OUT unsigned int & nLen)
	{
		DWORD nRetLen=0;
		m_bLastIsValue=TRUE;
		//return WriteFile(m_hFile,pInData,nLen,&nRetLen,NULL);	
		return WriteString((TCHAR*)pInData,nLen);
	}

	//顺序保存节点开始
	void GetFormatTab(tstring & szTab)
	{
		for(unsigned int i=0;i<m_nCurDepth;i++)
		{
			szTab+=_T("\t");
		}
	}
	BOOL PushNodeCtlBegin(TCHAR * szFieldType,SerializeRunData * CurFieldAddr)
	{
		DWORD nRetLen=0;
		if(m_bSave==FALSE)
		{
			//第一次保存先清空下文件
			switch(m_StorageObjectType)
			{
			case ToBuffer:
				m_XmlBuffer.clear();
				break;
			case ToFile:
				ReCreateFile();
				break;
			default:
				break;
			}
			
			m_bSave=TRUE;
		}
		m_nCurDepth++;
		/*
		tstring  szData=_T("\r\n");
				GetFormatTab(szData);
				szData+=tstring(_T("<"))+tstring(CurFieldAddr->m_pFieldName)+tstring(_T(" type=\""))+tstring(szFieldType)+tstring(_T("\" >"));
			
				return WriteString((TCHAR*)szData.c_str(),szData.length()*sizeof(TCHAR));
		*/
		if(m_ObjectCurSaveType==ObjectVal)
		{
			if(tstring(CurFieldAddr->m_pFieldName)==tstring(_T("MyObjectAttributes")))
			{
				m_ObjectCurSaveType=ObjectAttributes;
			}else
			{
				m_ObjectCurSaveType=ObjectVal;
				XmlNodeInfo node;
				node.m_CurNodeName=CurFieldAddr->m_pFieldName;
				m_XmlNodeInfoList.push_back(node);
			}

		}else if(m_ObjectCurSaveType==ObjectAttributes)
		{
			list<XmlNodeInfo>::iterator itBack=m_XmlNodeInfoList.end();
			itBack--;
			itBack->m_CurNodeAttributes+=tstring(_T(" "))+tstring(CurFieldAddr->m_pFieldName);
		}
		
		
		return FALSE;
	}
	//顺序保存节点结束
	BOOL PushNodeCtlEnd(TCHAR * szFieldType,SerializeRunData * CurFieldAddr)
	{
		DWORD nRetLen=0;
		m_nCurDepth--;
		tstring  szEndData;
		if(!m_bLastIsValue)
		{
			szEndData=_T("\n");
			GetFormatTab(szEndData);
		}
		tstring  szBeginData=_T("\n");
		GetFormatTab(szBeginData);

		m_bLastIsValue=FALSE;
		/*
		szData+=tstring(_T("</"))+tstring(CurFieldAddr->m_pFieldName)+tstring(_T(">"));
		
		
				return WriteString((TCHAR*)szData.c_str(),szData.length()*sizeof(TCHAR));*/
		if(tstring(CurFieldAddr->m_pFieldName)==tstring(_T("MyObjectAttributes")))
		{
			m_ObjectCurSaveType=ObjectVal;
			//
		}else
		{
			//保存数据
			list<XmlNodeInfo>::iterator itBack=m_XmlNodeInfoList.end();
			itBack--;
			if(itBack==m_XmlNodeInfoList.end()) return FALSE;
			if(m_nCurDepth==0)
			{
				m_XmlBuffer+=
					tstring(_T("<"))+itBack->m_CurNodeName;
				
				if(itBack->m_CurNodeAttributes.length())
				{
					m_XmlBuffer+=tstring(_T(" "));
				}
					m_XmlBuffer+=itBack->m_CurNodeAttributes+tstring(_T(">"))+itBack->m_CurNodeVal+
					szEndData+tstring(_T("</"))+itBack->m_CurNodeName+tstring(_T(">"));
				SaveXmlBuf();
			}else
			{
				if(m_ObjectCurSaveType==ObjectVal)
				{
					list<XmlNodeInfo>::iterator itBackFrout=itBack;
					itBackFrout--;
					itBackFrout->m_CurNodeVal+=szBeginData+
						tstring(_T("<"))+itBack->m_CurNodeName;
					
					if(itBack->m_CurNodeAttributes.length())
					{
						itBackFrout->m_CurNodeVal+=tstring(_T(" "));
					}
					itBackFrout->m_CurNodeVal+=itBack->m_CurNodeAttributes+tstring(_T(">"))+itBack->m_CurNodeVal+
						szEndData+tstring(_T("</"))+itBack->m_CurNodeName+tstring(_T(">"));

					m_XmlNodeInfoList.pop_back();
				}

			}


		}
		return TRUE;
	}
};

class StorageObjectToIni: public StorageObjectInterface
{
public:
	StorageObjectToIni(){};
	~StorageObjectToIni(){};
	tstring m_szFile;
	BOOL init(TCHAR * pszStorageObject)
	{
		m_szFile=tstring(pszStorageObject);
		return TRUE;
	}

	BOOL GetAddr(IN SerializeRunData * pAddr,tstring & szAddr)
	{
		TCHAR szNode[128];
		SerializeRunData * pCurAddr=pAddr;
		for(;pCurAddr!=NULL;pCurAddr=pCurAddr->m_pParent)
		{

			sprintf_s_t(szNode,128,_T("%s_%d_"),pCurAddr->m_pFieldName,pCurAddr->m_nIndex);
			tstring strNode=tstring(szNode);
			szAddr.insert(szAddr.begin(),strNode.begin(),strNode.end());
		}
		if(szAddr.length())
		{
			szAddr.erase(--szAddr.end());
		}
		return TRUE;
	}

	BOOL GetObjectVal(IN SerializeRunData * Addr,IN OUT void * pOutData,IN OUT unsigned int & nLen)
	{
		tstring szPath;
		if(GetAddr(Addr,szPath))
		{
			*(int *)pOutData= GetPrivateProfileInt(_T("Test"),szPath.c_str(),-1,m_szFile.c_str());
			return TRUE;
		}

		return FALSE;
	}
	BOOL SetObjectVal(IN SerializeRunData * Addr,IN void * pInData,IN OUT unsigned int & nLen)
	{
		tstring szPath;
		char cpBuf[16] = {0};
		if(GetAddr(Addr,szPath))
		{
			_ltoa(*(int *)pInData,cpBuf,10);
			CMyString szData(cpBuf,16);
			return WritePrivateProfileString(_T("Test"),szPath.c_str(),(TCHAR*)szData,m_szFile.c_str());
		}
		return FALSE;
	}
};