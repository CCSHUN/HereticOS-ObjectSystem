// XmlDomOpt.h: interface for the CXmlDomOpt class.
//
//
//该XML解析类被封装为静态lib库, Debug版XmlOptd.lib，Release版XmlOpt.lib
//作者：JZY， Tianyixin
//版本：1.10
//时间：2007-5-18 9:30
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XMLDOMOPT_H__77B9C23B_8F94_4904_B8DB_80EC21E5AF77__INCLUDED_)
#define AFX_XMLDOMOPT_H__77B9C23B_8F94_4904_B8DB_80EC21E5AF77__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "afxdisp.h"

#import "msxml6.dll"

typedef MSXML2::IXMLDOMNodePtr HDOMNODE;

#define  ITS_PARENT        0x0101
#define  FIRST_CHILD       0x0102
#define  NEXT_SIBLING      0x0103
#define  PREVIOUS_SIBLING  0x0104

//节点类型
#define ELEMENT            1
#define ATTRIBUTE          2
#define XMLTEXT            3
#define CDATA              4
#define ENTITY_REFERENCE   5
#define ENTITY             6
#define PI                 7     //processing instruction
#define COMMENT            8
#define DOCUMENT           9
#define DOCUMENT_TYPE      10
#define DOCUMENT_FRAGMENT  11
#define NOTATION           12


#define RELEASE(x)	\
	if( x != NULL )		\
	{					\
		x.Release();	\
		x = NULL;		\
	}

class CXmlDomOpt  
{
public:
	CXmlDomOpt();
	virtual ~CXmlDomOpt();

///////////////////////////////////////////////////////////////////////////////
//                           文件操作
//////////////////////////////////////////////////////////////////////////////
	BOOL CreateFile(LPCSTR lpszFilename, LPCSTR lpszEncoding = NULL); //创建XML文档,并指定编码格式
	BOOL CreateExcelFile(LPCSTR lpszFilename, LPCSTR lpszEncoding = NULL); 
	BOOL OpenFile(LPCSTR lpszFilePath);           //按路径打开文档
	BOOL SaveFile(LPCTSTR lpszFilePath = NULL);   //保存文档 

///////////////////////////////////////////////////////////////////////////////
//                           清空内存
//////////////////////////////////////////////////////////////////////////////
	void Close();   
	
///////////////////////////////////////////////////////////////////////////
//以下按树路径的方式操作XML文档
//Author: Tianyixin            
//Date:   2007-4-11
///////////////////////////////////////////////////////////////////////////
public:
	BOOL AddRootNode(CString strname);
	BOOL AddNodeToRoot(CString strname);
	BOOL AddNode(CString strParname,CString strThisname);
	BOOL AddNode(CString strname);
	
	BOOL Remove(CString strname);
	
/*******************属性、值操作******************************************/
	CString GetRootName(void);
	BOOL GetAttribute(CString& strattribute, CString strname);	
	BOOL GetValue(CString& strValue OUT, CString strname);	
	BOOL SetAttribute(CString strattribute, CString strname);	
	BOOL SetValue(CString strValue IN, CString strname);	
	BOOL DelAttribute(CString strname IN);
	
///////////////////////////////////////////////////////////////////////////
//以下按树节点的方式操作XML文档
//Author: JZY             
//Date:   2007-4-14
///////////////////////////////////////////////////////////////////////////
public:
    HDOMNODE GetRootNode();                            //得到文档根节点
	HDOMNODE GetCurrentNode() {return m_pCurNode;}     //得到当前节点
	UINT     GetNodeType(HDOMNODE hNode);              //得到当前节点类型
	HDOMNODE GetFirstChildNode(HDOMNODE hNode);
	HDOMNODE GetParentNode(HDOMNODE hNode);
	HDOMNODE GetPreviousSiblingNode(HDOMNODE hNode);
	HDOMNODE GetNextSiblingNode(HDOMNODE hNode);			
    HDOMNODE GetNextNode(HDOMNODE hNode, UINT nCode); //得到下一个节点
	//nCode = FIRST_CHILD, NEXT_SIBLING, PREVIOUS_SIBLING, ITS_PARENT 

	BOOL     HasChildNode(HDOMNODE hNode);       //是否有子节点
	LONG     GetChildNodeNumber(HDOMNODE hNode);  //得到子节点数
	BOOL     IsNodeExist(CString strname);        //按节点名在任意层查找节点是否存在

    BOOL     SetNodeText(HDOMNODE hNode, CString strText);
	BOOL     GetNodeText(HDOMNODE hNode, CString& strText);
    BOOL     GetNodeName(HDOMNODE hNode, CString& strName);//得到节点名称

	BOOL     SetNodeAttribute(HDOMNODE hNode, CString strAttribute);
	LONG     GetNodeAttributeCount(HDOMNODE hNode);     //得到指定节点属性的个数
	BOOL     GetNodeAttributes(HDOMNODE hNode, CString& strAttribute); //得到指定节点所有属性，属性之间以“|”分隔
	BOOL     GetNodeAttribute(HDOMNODE hNode, CString strAttributeName, 
		                      CString& strAttributeValue);  //按属性名查找值
	BOOL     GetNodeAttribute(HDOMNODE hNode, int index,    //按属性的数字查找值,起始下标从0开始
                              CString& strAttributeName,    //属性名称
							  CString& strAttributeValue);  //属性值

	//在指定节点的下一层按名称查找节点;
	//如果存在重名节点，可以指定取第几个重名节点,起始下标从1开始
    HDOMNODE SelectNode(HDOMNODE hNode, CString strNodeName, int index = 0); 
    //指定节点下的下一层是否存在指定的重名节点，返回重名节点的个数
	int      HasSameNodeName(HDOMNODE hNode, CString strNodeName); 
	                                       
    //在任意层按名称查找节点
	HDOMNODE SelectNode(CString strName); 	
	int      SelectNodeList(CString strNodeName);//返回找到的节点数
	HDOMNODE GetNodeByIndex(int index); //查找节点列表后，通过此函数得到各个节点
	

	HDOMNODE InsertRootNode(CString  strRootNodeName);  //插入根节点
	HDOMNODE InsertNode(HDOMNODE hNode, CString strNodeName); //在指定节点下插入节点

	BOOL     DeleteAllNodes();       //清空文档内容
	BOOL     DeleteNode(HDOMNODE hNode); //删除节点及其以下个子节点
	BOOL     EmptyNodeText(HDOMNODE hNode);//清空指定节点的内容
	BOOL     DeleteNodeAllAttributes(HDOMNODE hNode); //删除指定节点的所有属性
	BOOL     DeleteNodeAttribute(HDOMNODE hNode, CString strAtrbName); //按属性名删除值
	BOOL     DeleteNodeAttribute(HDOMNODE hNode, int index);//按属性的数字删除值
	BOOL	 IsInitialComSuccess();

private:
	HDOMNODE IgnoreCommentNode(HDOMNODE hNode); //忽视注释节点，得到注释节点下的其它类型节点

protected:
	//使用的都是智能指针
	MSXML2::IXMLDOMDocument2Ptr m_pDoc;
	MSXML2::IXMLDOMNodePtr      m_pRootNode;      //root node
	MSXML2::IXMLDOMNodePtr      m_pCurNode;       //current node
	MSXML2::IXMLDOMNodeListPtr  m_pNodeList; 
	CString	                    m_strFilePath;    //file path
	static BOOL                 m_bInitialCOMLib; //是否在构造函数中加载过COM库，若加载过，则需要在m_Ref==0时卸载COM库
	static int                  m_Ref;            //对象的引用计数
};

#endif // !defined(AFX_XMLDOMOPT_H__77B9C23B_8F94_4904_B8DB_80EC21E5AF77__INCLUDED_)
