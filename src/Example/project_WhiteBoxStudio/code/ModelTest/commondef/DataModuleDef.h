#pragma once
#include "ObjectSystem.h"

#define IN

#define OUT

//typedef string tstring;

struct _tagDirectoryInfoSetSoap
{
	tstring					ObjectName;		//������
	unsigned int			ObjectType;		//��������
	tstring					OtherInfo;		//����������Ϣ
};

struct _tagDirectoryInfoSoap
{
	vector<_tagDirectoryInfoSetSoap> DirectoryInfoArray;
};

//soap ������Э�鶨��Ķ���

struct _tagObjectStateSoap 
{
	BOOL	bLock;			//�����Ƿ�����
	unsigned int	nType;	//��������
	tstring szLockUser;		//��ǰ��ȡ�����û�
	unsigned int nLockTime;	//����ʱ��
};



typedef struct _tagstrParameter
{
	SER_TO_X<tstring,Base64ZipString> szVar;
}strParameter,*PstrParameter;

typedef struct _tagCallParameter
{
	tstring					szPassword;
	BOOL					bCallSuccess;
	tstring 				ObjectPath;
	SER_TO_X<tstring,Base64ZipString> 				Object;
	_tagObjectStateSoap		tagObjectState;
	unsigned int			nError;
	tstring					szFinder;
	_tagDirectoryInfoSoap	DirectoryInfo;
	map<tstring,_tagstrParameter,less<tstring> > strPar;
}CallParameter,*PCallParameter;

#include "..\ObjectSerDef\_tagstrParameter_StructInfo.h"
//typedef  ObjectTypeWrap<_tagstrParameter,Serialize__tagstrParameter> _tagstrParameter_Wrap; 
MAKESTRUCTINFO(_tagstrParameter)

#include "..\ObjectSerDef\_tagObjectStateSoap_StructInfo.h"
MAKESTRUCTINFO(_tagObjectStateSoap)

#include "..\ObjectSerDef\_tagDirectoryInfoSetSoap_StructInfo.h"
MAKESTRUCTINFO(_tagDirectoryInfoSetSoap)

#include "..\ObjectSerDef\_tagDirectoryInfoSoap_StructInfo.h"
MAKESTRUCTINFO(_tagDirectoryInfoSoap)

#include "..\ObjectSerDef\_tagCallParameter_StructInfo.h"
MAKESTRUCTINFO(_tagCallParameter)

typedef struct _tagYDConfig
{
	tstring strRuleVer;
	//�����ڲ������Ӽ���õ�����ip
	tstring strNetDomainName;
	int		nNetDomainPort;

	tstring strWSDLUrl;
	tstring strRunDirectory;
	tstring strLocalSystemDirectory;
	int		nSoapTimeout;
	int		nCheckCycle;
	tstring szDebugLevel;			//�� �� �� ��
}YDConfig;

#include "..\ObjectSerDef\_tagYDConfig_StructInfo.h"
MAKESTRUCTINFO(_tagYDConfig)




typedef struct _tagUserMapSet
{
	tstring szUserName;
	tstring szPassword;
	tstring szUserType;			//�û����� �ݶ�Ϊ������Ա���з���Ա������Ա
	tstring szChildUserType;	//��ʱ���ã��Ժ�λϸ�ֺ���չ
	tstring szChildUserType1;	//��ʱ���ã��Ժ�λϸ�ֺ���չ
}UserMapSet,*PUserMapSet;
//�����û�����չ�����ҵ�����
//�ͻ��˻�ȡ�����ַ UserInfo\UserMap\xxxx   //xxxxΪ�û���


typedef struct _tagUserProjectSet
{
	tstring szUserName;
	tstring szProjectName;
}UserProjectSet,*PUserProjectSet;

typedef struct _tagUserOwnProjectTab
{
	map<tstring,_tagUserProjectSet,less<tstring> > OwnProjectArray; //����Ŀ����������
}UserOwnProjectTab,*PUserOwnProjectTab;


typedef struct _tagProjectOwnUserSet
{
	tstring szUserName;
	tstring szUserType;
}ProjectOwnUserSet,*PProjectOwnUserSet;

typedef struct _tagProjectOwnUser
{
	map<tstring,_tagProjectOwnUserSet,less<tstring> > OwnUserMap; //����Ŀ����������
}ProjectOwnUser,*PProjectOwnUser;

//�û�ӵ�е���Ŀ�б�
//��ַ UserInfo\UserOwnProject\xxxx  //xxxxΪ�û���

//��Ŀ�����ֶΣ�����
typedef struct _tagConfigInfo
{
	map<tstring,tstring,less<tstring> > m_CfgArray;
}ConfigInfo,*PConfigInfo;

typedef struct _tagProjectConfig
{
	tstring WorksheetStandard;	//���õĹ�������׼
	SER_TO_X<tstring,HexString>  CheckCfgStandard;	//���õļ�������ļ���׼
	tstring TestReportStandard; //���Ա���淶��׼��
}ProjectConfig,*PProjectConfig;

typedef struct _tagProjectState
{
	tstring szProjectState;					//������״̬ �����½���ĿΪ"�½�"����ɱ����Ϊ"�������ύ"���з����������Ϊ"�з����ύ" ����Ա"�鵵"
	
}ProjectState,*PProjectState;



//�׺в���Ŀ¼
//CodeTest\

//�û�Ŀ¼�ṹ
//UserInfo\
//		|---UserMap\        //����û���Ϣ
//				|----xxxx   //xxxxΪ�û���
//		|---UserOwnProject\	//����û���ע����Ŀ�б���Ϣ
//				|----xxxx   //xxxxΪ�û���
//		|---UserMsg\		//����û����ܵ�����Ϣ
//				|----xxxx   //xxxxΪ�û���
//					 |----PrivateMsg\ //���˽����Ϣ��Ϣ
//								|----xxxx\ //�����xxxx�û�����Ϣ��¼
//										|----2013-05-27#tickcount#Msg	//��Ϣ��
//										|----MsgInfo��//�������û���ص�������Ϣ
//					 |----SystemMsg\	//���ϵͳ��Ϣ
//								|----2013-05-27#tickcount#Msg	//��Ϣ��
//								|----MsgInfo��//�������û���ص�������Ϣ
//					 |----GroupMsgIndex		//���������������


//UserInfo\UserOwnProject\xxxx  //xxxxΪ�û���

//��Ŀ û�ж�Ӧ���ݽṹ��ֻ��Ŀ¼�ṹ
// WhiteBoxTestProject\  ������Ŀ������ݽṹ���ڴ�Ŀ¼��
//				|----------------Project_XXXX\    ÿ����Ŀһ��Ŀ¼��XXXXΪ��Ŀ����
//										|-------Directory_XXXXXX
//													|-------Directory_XXXXXX
//																|-------ChildTest_XXXX\		ÿ�β�����Ŀ����
//																				|----------Worksheet		��Ŀ����������XML
//																				|----------CheckCfg		��Ŀ��鹤�����ö���XML����Ӧ�ṹ_tagProjectConfig		
//																				|----------TestReport		��Ŀ���Ա������XML
//																				|----------ProjectState	��Ŀ״̬����
//																				|----------ProjectConfig	��Ŀȫ��������Ϣ��Ϊ������չ���淶����
//																				|-------Directory_XXXXXX
//																								|-------ChildTest_XXXX\		ÿ�β�����Ŀ����
//																												|----------Worksheet		��Ŀ����������XML
//																												|----------CheckCfg		��Ŀ��鹤�����ö���XML����Ӧ�ṹ_tagProjectConfig		
//																												|----------TestReport		��Ŀ���Ա������XML
//																												|----------ProjectState	��Ŀ״̬����
//																												|----------ProjectConfig	��Ŀȫ��������Ϣ��Ϊ������չ���淶����
//										|-------Directory_XXXXXX
//													|-------Directory_XXXXXX
//																|-------ChildTest_XXXX\		ÿ�β�����Ŀ����
//																				|----------Worksheet		��Ŀ����������XML
//																				|----------CheckCfg		��Ŀ��鹤�����ö���XML����Ӧ�ṹ_tagProjectConfig		
//																				|----------TestReport		��Ŀ���Ա������XML
//																				|----------ProjectState	��Ŀ״̬����
//																				|----------ProjectConfig	��Ŀȫ��������Ϣ��Ϊ������չ���淶����
//										|-------GroupMsg\
//													|----2013-05-27#count#Msg	//��Ϣ��
//													|----MsgInfo��//��������������ص�������Ϣ
//										|-------ProjectUser						��Ŀ�û��б�
//				|----------------Project_XXXX\    ÿ����Ŀһ��Ŀ¼��XXXXΪ��Ŀ����
//										|-------Directory_XXXXXX
//													|-------Directory_XXXXXX
//																|-------ChildTest_XXXX\		ÿ�β�����Ŀ����
//																				|----------Worksheet		��Ŀ����������XML
//																				|----------CheckCfg		��Ŀ��鹤�����ö���XML����Ӧ�ṹ_tagProjectConfig		
//																				|----------TestReport		��Ŀ���Ա������XML
//																				|----------ProjectState	��Ŀ״̬����
//																				|----------ProjectConfig	��Ŀȫ��������Ϣ��Ϊ������չ���淶����
//										|-------Directory_XXXXXX
//													|-------Directory_XXXXXX
//																|-------ChildTest_XXXX\		ÿ�β�����Ŀ����
//																				|----------Worksheet		��Ŀ����������XML
//																				|----------CheckCfg		��Ŀ��鹤�����ö���XML����Ӧ�ṹ_tagProjectConfig		
//																				|----------TestReport		��Ŀ���Ա������XML
//																				|----------ProjectState	��Ŀ״̬����
//																				|----------ProjectConfig	��Ŀȫ��������Ϣ��Ϊ������չ���淶����
//										|-------GroupMsg\
//													|----2013-05-27#count#Msg	//��Ϣ��
//													|----MsgInfo��//��������������ص�������Ϣ
//										|-------ProjectUser						��Ŀ�û��б�


// WhiteBoxTestStandard\ ��Ű׺в��Ա�׼���ݿ�
//		|----------------MachineCheckStandard\		��е�߶��淶
//								|-------MachineCheckStandard_XXXXXX\							XXXXX�ǹ淶���� (ͳһ�淶VER1.0)
//												|-------MachineCheckStandardSpecify				ͳһ�淶��׼˵����
//												|-------MachineCheckStandardLib					��е�߶��淶-���� XML����Ӧ�ṹMachineCheckStandardLib���ļ���Ӧ���а汾�ֶΣ�ʹ��ʱ�ڽ�������ʾ�汾��Ϣ
//												|-------MachineCheckStandard-Rule-diff			��е�߶��淶-���� ����˵����ÿһ�ΰ汾�ύ��Ҫ˵���ύ�ˣ����ڣ��������ݵȣ���ר�������������ʱ�������ù��ܲ���Ҫ
//												|-------MachineCheckStandardTypeLib				е�߶��淶-�������� XML����Ӧ�ṹMachineCheckStandardTypeLib
//												|-------ThirdStandardlib						е�߶��淶-�������� XML����Ӧ�ṹThirdStandardlib
//												|-------ErrorWarningDefine						е�߶��淶-�������� XML����Ӧ�ṹThirdStandardlib


//WhiteBoxTestProjectConfigTemplate\ �����Ŀ����ģ�����ݶ���
//					|-------------------CheckToolType_XXXXXX\									XXXXΪ��������
//													|---------ProjectConfigTemplate_XXXXX		XXXXΪģ����������

//ͳһ�淶����˵����
typedef struct _tagMachineCheckStandardSpecify{
	tstring szMachineCheckStandardSpecify;			//�淶˵����
}MachineCheckStandardSpecify,*PMachineCheckStandardSpecify;

//�������ͣ��μ��ĵ�<<YD-����.���߼��淶.xls>>�ġ��������Ͷ��塱ҳ��
typedef struct _tagMachineCheckStandardTypeSet {
	tstring id;
	tstring name;								//�������ƣ���Ϊ��������࣬�����硰�淶�����⡱�������硰�﷨��ʽ���⡱��
	unsigned long min_range;					//��������������ı�ŷ�Χ
	unsigned long max_range;
	tstring parent_id;							//����Ǵ��࣬����ֶ�Ϊ0������Ϊ�����ID
} MachineCheckStandardTypeSet, *PMachineCheckStandardTypeSet;

typedef struct _tagErrorWarningSet
{
	SER_TO_X<tstring,HexString> szErrorWarningName;	
	SER_TO_X<tstring,HexString> szErrorWarningDesc;

}ErrorWarningSet,*PErrorWarningSet;


//��е�߶�ͳһ�淶
typedef struct _tagMachineCheckStandardSet {
	tstring szErrorNum;
	tstring szErrorType;			//��������
	SER_TO_X<tstring,HexString> szDesc;					//��������
	tstring szErrorWarning;			//���󾯸����� ���飬���棬���ش���
	tstring szErrorTypeId;				//�����ԽṹMachineCheckStandardTypeSet
	SER_TO_X<tstring,HexString> szErrorSuggest;
	
} MachineCheckStandardSet, *PMachineCheckStandardSet;

//��������е�߶��淶ӳ�� ͨ��rule_id������ͳһ��е�߶��淶
typedef struct _tagThirdStandardSet {
	tstring szUniteStandardErrorNum;		//��е�߶�ͳһ�淶
	tstring szThirdStandardErrorNum;		//PCLINT����CTester�Ĵ���ID
	SER_TO_X<tstring,HexString> szThirdStandardErrorDesc;
	SER_TO_X<tstring,HexString> szErrorSuggest;					//����
	BOOL is_manual_check;					//�Ƿ���Ҫ�˹����
	SER_TO_X<tstring,HexString> szManual_check_MethodSpecify;	//�˹������׼˵����ָ��������Ա�˹����顣
	BOOL is_dealwith;						//�Ƿ���Ҫ����

	tstring ToolType;						//����"PCLINT", "C++ TESTER"
} ThirdStandardSet, *PThirdStandardSet;


//�������Ͷ���

typedef struct _tagErrorWarningArray
{
	vector<_tagErrorWarningSet> WarningArray;

}ErrorWarningArray,*PErrorWarningArray;

//ͳһ��е�߶� "��������" �淶��
typedef struct _tagMachineCheckStandardTypeLib
{
	map<tstring,_tagMachineCheckStandardTypeSet,less<tstring> > libmap;
}MachineCheckStandardTypeLib,*PMachineCheckStandardTypeLib;

//ͳһ��е�߶��淶��
typedef struct _tagMachineCheckStandardLib
{
	map<tstring,_tagMachineCheckStandardSet,less<tstring> > libmap;
}MachineCheckStandardLib,*PMachineCheckStandardLib;

//��������е�߶��淶ӳ��� ͨ��rule_id������ͳһ��е�߶��淶
typedef struct _tagThirdStandardlib
{
	map<tstring,_tagThirdStandardSet,less<tstring> > libmap;
}ThirdStandardlib,*PThirdStandardlib;

//���Թ������ṹ���ýṹ���������Թ����ж���ʹ��
typedef struct _S_WORKSHEET {
	tstring szProjectNo;
	tstring szModuleNo;
	tstring szWorksheetNo;		
	tstring szApplyDate;
	tstring szApplyMan;
	tstring szResponsiblePerson;
	tstring szDefaultDispatchUser;
	tstring szCheckRange;
	int nCheckType;					//1 Ϊ������飻2 Ϊȫ�����
	tstring szPreWorksheetNo;	
	tstring szSVNCodePath;
	tstring szSourceList;

	tstring szSuggest;
	int nCheckResult;				//0 Ϊ�ɹ���1 Ϊ�쳣��ֹ
	tstring szFailReason;
	tstring szSignatureMan;
	tstring szSignatureDate;
} WORKSHEET, *PWORKSHEET;

typedef struct _tagReportLog
{
	tstring	szUserName;
	__int64 tmDate;		//����
	SER_TO_X<tstring,HexString> szReport_log;
}ReportLog,*PReportLog;

//���Ա���ṹ
typedef struct _S_REPORT_ITEM {
	tstring szTestState;										//���Լ�¼״̬ "���ͨ��" "��Ҫ�˹�����" "��Ҫ��ʵ�淶" "����"
	tstring szTestItemSource;									//������Դ,"�Զ�����" "�˹�����" "�˹����"	
	tstring szTestToolType;										//��������
	tstring szUniteStandardErrorNum;							//��е�߶�ͳһ�淶
	tstring szThirdStandardErrorNum;							//PCLINT����CTester�Ĵ���ID
	SER_TO_X<tstring,Base64ZipString> szErrorCodeContent;				//������������е�����
	SER_TO_X<tstring,Base64ZipString> szErrorCodePosition;								//����������ڵ��ļ������к�
	SER_TO_X<tstring,Base64ZipString> szModule;						//�����Դ�ļ����ļ���
	SER_TO_X<tstring,Base64ZipString> szSuggest;						//����
	SER_TO_X<tstring,Base64ZipString> szDesc;							//����ļ�Ҫ����

	SER_TO_X<tstring,Base64ZipString> szUniteSuggest;					//ͳһ�淶����
	SER_TO_X<tstring,Base64ZipString> szUniteDesc;					//ͳһ�淶����ļ�Ҫ����

	SER_TO_X<tstring,Base64ZipString> szThirdSuggest;					//����������
	SER_TO_X<tstring,Base64ZipString> szThirdDesc;					//����������ļ�Ҫ����

	tstring szErrorType;										//��������
	tstring szErrorWarning;										//���󾯸����� ���飬���棬���ش���

	tstring szCreateTime;										//����ʱ��
	tstring szLastEditTime;										//�������ʱ��

	//�з�������Ϣ
	tstring szDevelopState;										//�������״̬ �����ύ��Ϊ���� �з������Ϊ�޸�������δ����
	vector<_tagReportLog>	szReport_log;						//���⽻����¼
	tstring szProcessUser;										//���⴦���ˣ�Ĭ�ϴ������ڹ�����������
} REPORT_ITEM, *PREPORT_ITEM;


typedef struct _S_REPORT {
	tstring szName;						//��������
	unsigned long nTotalErrorCount;		//��������
	unsigned long nErrorCount_1;			//���ش�������
	unsigned long nErrorCount_2;			//�еȴ�������
	unsigned long nErrorCount_3;			//һ���������
	vector<_S_REPORT_ITEM> items;
} REPORT, *PREPORT;


typedef struct _tagUnitReportSet
{
	int		nID;
	tstring szState;

	tstring szPrjName;
	tstring szSysName;
	tstring szModuleName;
	tstring szTesterName;
	tstring szJudgeName;
	tstring szTestDate;
	tstring szJudgeDate;
	tstring szSug;

	int		nIVT;
	int		nINVT;
	int		nBT;
	int		nRCT;
	int		nTCCDT;

	double fIVT;
	double fINVT;
	double fBT;
	double fRCT;
	double fTCCDT;
}UnitReportSet,*PUnitReportSet;

typedef struct _tagUnitReport
{
	tstring szID;					//���β���ID
	tstring szInheritID;			//�̳е��ϴβ���ID
	vector<_tagUnitReportSet> UnitReportArray;
}UnitReport,*PUnitReport;

//��Ŀ����
typedef struct _S_PROJECT_CONFIG {
	tstring config_content;					//��׼����
} PROJECT_CONFIG, *PPROJECT_CONFIG;



//PCLint ����
typedef struct  _tagPCLintReportItem
{
	tstring filename;
	tstring errorno;
	int rowno;
	tstring msgtxt;
}PCLintReportItem, *PPCLintReportItem;

#include "..\ObjectSerDef\_tagErrorWarningSet_StructInfo.h"
MAKESTRUCTINFO(_tagErrorWarningSet)

#include "..\ObjectSerDef\_tagUnitReportSet_StructInfo.h"
MAKESTRUCTINFO(_tagUnitReportSet)

#include "..\ObjectSerDef\_tagUnitReport_StructInfo.h"
MAKESTRUCTINFO(_tagUnitReport)
/*
class _tagErrorWarningSet_Wrap
{
public:
	_tagErrorWarningSet	m_Data;
	tstring		m_szAddr;
	CObjectSystemInterface::_tagObjectState m_ObjectState;

	CObjectSystemInterface::SYSTEMERROR m_nCurError;
	_tagErrorWarningSet_Wrap(){};
	~_tagErrorWarningSet_Wrap(){};
	BOOL GetObject()
	{
		tstring Object;
		BOOL bRet=gpObjectSystem->GetObject(m_szAddr,Object,m_ObjectState,&m_nCurError);
		if(bRet)
		{
			SerTCHARXmlBufferToObject(_tagErrorWarningSet,m_Data,(Object.c_str()));
		}
		return bRet;

	}

	BOOL UpDataObject()
	{
		tstring Object;
		SerObjectToXmlBuffer(_tagErrorWarningSet,m_Data,Object);
		return gpObjectSystem->UpDataObject(m_szAddr,Object,&m_nCurError);
	}

	BOOL GetDirectoryInfo(CObjectSystemInterface::_tagDirectoryInfo & DirectoryInfo)
	{
		return gpObjectSystem->GetDirectoryInfo(m_szAddr,DirectoryInfo,&m_nCurError);
	}
	BOOL DeleteObject()
	{
		return gpObjectSystem->DeleteObject(m_szAddr,&m_nCurError);
	}
};
*/


#include "..\ObjectSerDef\_tagErrorWarningArray_StructInfo.h"
MAKESTRUCTINFO(_tagErrorWarningArray)

/*
class _tagErrorWarningArray_Wrap
{
public:
	_tagErrorWarningArray	m_Data;
	tstring		m_szAddr;
	CObjectSystemInterface::_tagObjectState m_ObjectState;

	CObjectSystemInterface::SYSTEMERROR m_nCurError;
	_tagErrorWarningArray_Wrap(){};
	~_tagErrorWarningArray_Wrap(){};
	BOOL GetObject()
	{
		tstring Object;
		BOOL bRet=gpObjectSystem->GetObject(m_szAddr,Object,m_ObjectState,&m_nCurError);
		if(bRet)
		{
			SerTCHARXmlBufferToObject(_tagErrorWarningArray,m_Data,(Object.c_str()));
		}
		return bRet;

	}

	BOOL UpDataObject()
	{
		tstring Object;
		SerObjectToXmlBuffer(_tagErrorWarningArray,m_Data,Object);
		return gpObjectSystem->UpDataObject(m_szAddr,Object,&m_nCurError);
	}

	BOOL GetDirectoryInfo(CObjectSystemInterface::_tagDirectoryInfo & DirectoryInfo)
	{
		return gpObjectSystem->GetDirectoryInfo(m_szAddr,DirectoryInfo,&m_nCurError);
	}
	BOOL DeleteObject()
	{
		return gpObjectSystem->DeleteObject(m_szAddr,&m_nCurError);
	}
};*/

// �����Զ������ɷֲ�ʽ����
#include "..\ObjectSerDef\_tagPCLintReportItem_StructInfo.h"
MAKESTRUCTINFO(_tagPCLintReportItem)

//MAKESTRUCTINFO(ObjectType)
#include "..\ObjectSerDef\_tagUserMapSet_StructInfo.h"
MAKESTRUCTINFO(_tagUserMapSet)
#include "..\ObjectSerDef\_tagUserProjectSet_StructInfo.h"
MAKESTRUCTINFO(_tagUserProjectSet)
#include "..\ObjectSerDef\_tagProjectOwnUserSet_StructInfo.h"
MAKESTRUCTINFO(_tagProjectOwnUserSet)
#include "..\ObjectSerDef\_tagProjectOwnUser_StructInfo.h"
MAKESTRUCTINFO(_tagProjectOwnUser)



#include "..\ObjectSerDef\_tagUserOwnProjectTab_StructInfo.h"
MAKESTRUCTINFO(_tagUserOwnProjectTab)
#include "..\ObjectSerDef\_tagProjectConfig_StructInfo.h"
MAKESTRUCTINFO(_tagProjectConfig)

#include "..\ObjectSerDef\_tagProjectState_StructInfo.h"
MAKESTRUCTINFO(_tagProjectState)
#include "..\ObjectSerDef\_tagMachineCheckStandardSpecify_StructInfo.h"
MAKESTRUCTINFO(_tagMachineCheckStandardSpecify)
#include "..\ObjectSerDef\_tagMachineCheckStandardTypeSet_StructInfo.h"
MAKESTRUCTINFO(_tagMachineCheckStandardTypeSet)


#include "..\ObjectSerDef\_tagMachineCheckStandardSet_StructInfo.h"
MAKESTRUCTINFO(_tagMachineCheckStandardSet)
#include "..\ObjectSerDef\_tagThirdStandardSet_StructInfo.h"
MAKESTRUCTINFO(_tagThirdStandardSet)



#include "..\ObjectSerDef\_tagMachineCheckStandardTypeLib_StructInfo.h"
MAKESTRUCTINFO(_tagMachineCheckStandardTypeLib)


#include "..\ObjectSerDef\_tagMachineCheckStandardLib_StructInfo.h"
MAKESTRUCTINFO(_tagMachineCheckStandardLib)


#include "..\ObjectSerDef\_tagThirdStandardlib_StructInfo.h"
MAKESTRUCTINFO(_tagThirdStandardlib)


#include "..\ObjectSerDef\_S_WORKSHEET_StructInfo.h"
MAKESTRUCTINFO(_S_WORKSHEET)

#include "..\ObjectSerDef\_tagReportLog_StructInfo.h"
MAKESTRUCTINFO(_tagReportLog)
#include "..\ObjectSerDef\_S_REPORT_ITEM_StructInfo.h"
MAKESTRUCTINFO(_S_REPORT_ITEM)
#include "..\ObjectSerDef\_S_REPORT_StructInfo.h"
MAKESTRUCTINFO(_S_REPORT)






#include "..\ObjectSerDef\_S_PROJECT_CONFIG_StructInfo.h"
MAKESTRUCTINFO(_S_PROJECT_CONFIG)



/*
class _tagUserMapSet_Wrap
{
public:
	typedef _tagUserMapSet  ObjectType;
	ObjectType	m_Data;
	tstring		m_szAddr;
	CObjectSystem::_tagObjectState m_ObjectState;

	CObjectSystem::SYSTEMERROR m_nCurError;
	_tagUserMapSet_Wrap(){};
	~_tagUserMapSet_Wrap(){};
	BOOL GetObject()
	{
		tstring Object;
		BOOL bRet=gpObjectSystem->GetObject(m_szAddr,Object,m_ObjectState,&m_nCurError);
		if(bRet)
		{
			SerTCHARXmlBufferToObject(_tagUserMapSet,m_Data,(Object.c_str()));
		}
		return bRet;

	}

	BOOL UpDataObject()
	{
		tstring Object;
		SerObjectToAnsiXmlBuffer(_tagUserMapSet,m_Data,Object);
		return gpObjectSystem->UpDataObject(m_szAddr,Object,&m_nCurError);
	}

	BOOL GetDirectoryInfo(CObjectSystem::_tagDirectoryInfo & DirectoryInfo)
	{
		return gpObjectSystem->GetDirectoryInfo(m_szAddr,DirectoryInfo,&m_nCurError);
	}
	BOOL DeleteObject()
	{
		return gpObjectSystem->DeleteObject(m_szAddr,&m_nCurError);
	}
};
*/



typedef struct _tagTestHexString
{
	SER_TO_X<tstring,HexString>	Test;	
}TestHexString,*PTestHexString;


#include "..\ObjectSerDef\_tagTestHexString_StructInfo.h"
MAKESTRUCTINFO(_tagTestHexString)






typedef struct _tagReportOutput_Summary
{
	unsigned int	nCurPos;
	SER_TO_X<tstring,XmlString>		szDesc;
	unsigned int	nErrorTotal;		
	unsigned int	nComplateTotal;
	unsigned int	nManaualTotal;
	unsigned int	nIgnoreTotal;
	tstring			szErrorType;
	tstring			szWaringType;
	tstring			szUniteNum;
}ReportOutput_Summary;


typedef struct _tagReportOutput_Detailed
{
	SER_TO_X<tstring,XmlString>	szDetailed;
}ReportOutput_Detailed;

typedef struct _tagReportOutput_Overall
{
	unsigned int nDescTotal;		//������������
	unsigned int nErrorTotal;		//
	unsigned int nComplateTotal;
	unsigned int nManaualTotal;
	unsigned int nIgnoreTotal;
}ReportOutput_Overall;

typedef struct _tagReportOutput
{
	//���屨��overall
	_tagReportOutput_Overall	Overall;
	//ժҪSummary
	vector<_tagReportOutput_Summary>	Summary;
	//��ϸ����detailed
	vector<_tagReportOutput_Detailed>	Detailed;
}ReportOutput,*PReportOutput;


#include "..\ObjectSerDef\_tagReportOutput_Overall_StructInfo.h"
MAKESTRUCTINFO(_tagReportOutput_Overall)
#include "..\ObjectSerDef\_tagReportOutput_Summary_StructInfo.h"
MAKESTRUCTINFO(_tagReportOutput_Summary)
#include "..\ObjectSerDef\_tagReportOutput_Detailed_StructInfo.h"
MAKESTRUCTINFO(_tagReportOutput_Detailed)

#include "..\ObjectSerDef\_tagReportOutput_StructInfo.h"
MAKESTRUCTINFO(_tagReportOutput)




//////////////////////////////////////////��Ϣϵͳ//////////////////////////////////////////
//����
typedef struct _tagMsgData
{
	tstring szType;			//�������͡�bin�ļ���jpgͼƬ��gif������midi���֣���Ƶ����Ƶ html
	tstring szData;	
}MsgData,*PMsgData;

typedef struct _tagMsgBody
{
	tstring szSenderUser;
	tstring szSendDate;			//��������
	tstring szTitle;			//���ͱ���
	vector<tstring>				szRecvUserList;			//�����û��б�
	vector<_tagMsgData>			tagMsgAppend;			//����
	_tagMsgData					szMsgData;				//��Ϣ����
}MsgBody,*PMsgBody;

typedef struct _tagUserMsgInfo
{
	tstring szBeginMsgTime;					//��ʼ��Ϣʱ��
	tstring szEndMsgTime;					//�����Ϣʱ��
	unsigned int nMsgNum;					//��Ϣ��
	vector<tstring>		szNewMsgIndex;		//����Ϣ����
}UserMsgInfo,*PUserMsgInfo;

#include "..\ObjectSerDef\_tagMsgData_StructInfo.h"
MAKESTRUCTINFO(_tagMsgData)
#include "..\ObjectSerDef\_tagMsgBody_StructInfo.h"
MAKESTRUCTINFO(_tagMsgBody)
#include "..\ObjectSerDef\_tagUserMsgInfo_StructInfo.h"
MAKESTRUCTINFO(_tagUserMsgInfo)
