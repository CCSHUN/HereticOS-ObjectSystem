// XmlDomOpt.h: interface for the CXmlDomOpt class.
//
//
//��XML�����౻��װΪ��̬lib��, Debug��XmlOptd.lib��Release��XmlOpt.lib
//���ߣ�JZY�� Tianyixin
//�汾��1.10
//ʱ�䣺2007-5-18 9:30
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

//�ڵ�����
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
//                           �ļ�����
//////////////////////////////////////////////////////////////////////////////
	BOOL CreateFile(LPCSTR lpszFilename, LPCSTR lpszEncoding = NULL); //����XML�ĵ�,��ָ�������ʽ
	BOOL CreateExcelFile(LPCSTR lpszFilename, LPCSTR lpszEncoding = NULL); 
	BOOL OpenFile(LPCSTR lpszFilePath);           //��·�����ĵ�
	BOOL SaveFile(LPCTSTR lpszFilePath = NULL);   //�����ĵ� 

///////////////////////////////////////////////////////////////////////////////
//                           ����ڴ�
//////////////////////////////////////////////////////////////////////////////
	void Close();   
	
///////////////////////////////////////////////////////////////////////////
//���°���·���ķ�ʽ����XML�ĵ�
//Author: Tianyixin            
//Date:   2007-4-11
///////////////////////////////////////////////////////////////////////////
public:
	BOOL AddRootNode(CString strname);
	BOOL AddNodeToRoot(CString strname);
	BOOL AddNode(CString strParname,CString strThisname);
	BOOL AddNode(CString strname);
	
	BOOL Remove(CString strname);
	
/*******************���ԡ�ֵ����******************************************/
	CString GetRootName(void);
	BOOL GetAttribute(CString& strattribute, CString strname);	
	BOOL GetValue(CString& strValue OUT, CString strname);	
	BOOL SetAttribute(CString strattribute, CString strname);	
	BOOL SetValue(CString strValue IN, CString strname);	
	BOOL DelAttribute(CString strname IN);
	
///////////////////////////////////////////////////////////////////////////
//���°����ڵ�ķ�ʽ����XML�ĵ�
//Author: JZY             
//Date:   2007-4-14
///////////////////////////////////////////////////////////////////////////
public:
    HDOMNODE GetRootNode();                            //�õ��ĵ����ڵ�
	HDOMNODE GetCurrentNode() {return m_pCurNode;}     //�õ���ǰ�ڵ�
	UINT     GetNodeType(HDOMNODE hNode);              //�õ���ǰ�ڵ�����
	HDOMNODE GetFirstChildNode(HDOMNODE hNode);
	HDOMNODE GetParentNode(HDOMNODE hNode);
	HDOMNODE GetPreviousSiblingNode(HDOMNODE hNode);
	HDOMNODE GetNextSiblingNode(HDOMNODE hNode);			
    HDOMNODE GetNextNode(HDOMNODE hNode, UINT nCode); //�õ���һ���ڵ�
	//nCode = FIRST_CHILD, NEXT_SIBLING, PREVIOUS_SIBLING, ITS_PARENT 

	BOOL     HasChildNode(HDOMNODE hNode);       //�Ƿ����ӽڵ�
	LONG     GetChildNodeNumber(HDOMNODE hNode);  //�õ��ӽڵ���
	BOOL     IsNodeExist(CString strname);        //���ڵ������������ҽڵ��Ƿ����

    BOOL     SetNodeText(HDOMNODE hNode, CString strText);
	BOOL     GetNodeText(HDOMNODE hNode, CString& strText);
    BOOL     GetNodeName(HDOMNODE hNode, CString& strName);//�õ��ڵ�����

	BOOL     SetNodeAttribute(HDOMNODE hNode, CString strAttribute);
	LONG     GetNodeAttributeCount(HDOMNODE hNode);     //�õ�ָ���ڵ����Եĸ���
	BOOL     GetNodeAttributes(HDOMNODE hNode, CString& strAttribute); //�õ�ָ���ڵ��������ԣ�����֮���ԡ�|���ָ�
	BOOL     GetNodeAttribute(HDOMNODE hNode, CString strAttributeName, 
		                      CString& strAttributeValue);  //������������ֵ
	BOOL     GetNodeAttribute(HDOMNODE hNode, int index,    //�����Ե����ֲ���ֵ,��ʼ�±��0��ʼ
                              CString& strAttributeName,    //��������
							  CString& strAttributeValue);  //����ֵ

	//��ָ���ڵ����һ�㰴���Ʋ��ҽڵ�;
	//������������ڵ㣬����ָ��ȡ�ڼ��������ڵ�,��ʼ�±��1��ʼ
    HDOMNODE SelectNode(HDOMNODE hNode, CString strNodeName, int index = 0); 
    //ָ���ڵ��µ���һ���Ƿ����ָ���������ڵ㣬���������ڵ�ĸ���
	int      HasSameNodeName(HDOMNODE hNode, CString strNodeName); 
	                                       
    //������㰴���Ʋ��ҽڵ�
	HDOMNODE SelectNode(CString strName); 	
	int      SelectNodeList(CString strNodeName);//�����ҵ��Ľڵ���
	HDOMNODE GetNodeByIndex(int index); //���ҽڵ��б��ͨ���˺����õ������ڵ�
	

	HDOMNODE InsertRootNode(CString  strRootNodeName);  //������ڵ�
	HDOMNODE InsertNode(HDOMNODE hNode, CString strNodeName); //��ָ���ڵ��²���ڵ�

	BOOL     DeleteAllNodes();       //����ĵ�����
	BOOL     DeleteNode(HDOMNODE hNode); //ɾ���ڵ㼰�����¸��ӽڵ�
	BOOL     EmptyNodeText(HDOMNODE hNode);//���ָ���ڵ������
	BOOL     DeleteNodeAllAttributes(HDOMNODE hNode); //ɾ��ָ���ڵ����������
	BOOL     DeleteNodeAttribute(HDOMNODE hNode, CString strAtrbName); //��������ɾ��ֵ
	BOOL     DeleteNodeAttribute(HDOMNODE hNode, int index);//�����Ե�����ɾ��ֵ
	BOOL	 IsInitialComSuccess();

private:
	HDOMNODE IgnoreCommentNode(HDOMNODE hNode); //����ע�ͽڵ㣬�õ�ע�ͽڵ��µ��������ͽڵ�

protected:
	//ʹ�õĶ�������ָ��
	MSXML2::IXMLDOMDocument2Ptr m_pDoc;
	MSXML2::IXMLDOMNodePtr      m_pRootNode;      //root node
	MSXML2::IXMLDOMNodePtr      m_pCurNode;       //current node
	MSXML2::IXMLDOMNodeListPtr  m_pNodeList; 
	CString	                    m_strFilePath;    //file path
	static BOOL                 m_bInitialCOMLib; //�Ƿ��ڹ��캯���м��ع�COM�⣬�����ع�������Ҫ��m_Ref==0ʱж��COM��
	static int                  m_Ref;            //��������ü���
};

#endif // !defined(AFX_XMLDOMOPT_H__77B9C23B_8F94_4904_B8DB_80EC21E5AF77__INCLUDED_)
