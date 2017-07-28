#pragma once
#include "ObjectSystem.h"

#define IN

#define OUT

//typedef string tstring;

struct _tagDirectoryInfoSetSoap
{
	tstring					ObjectName;		//对象名
	unsigned int			ObjectType;		//对象类型
	tstring					OtherInfo;		//对象其他信息
};

struct _tagDirectoryInfoSoap
{
	vector<_tagDirectoryInfoSetSoap> DirectoryInfoArray;
};

//soap 对象传输协议定义的对象

struct _tagObjectStateSoap 
{
	BOOL	bLock;			//对象是否被锁。
	unsigned int	nType;	//锁的类型
	tstring szLockUser;		//当前获取锁的用户
	unsigned int nLockTime;	//锁定时间
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
	//域用于测试连接计算得到本地ip
	tstring strNetDomainName;
	int		nNetDomainPort;

	tstring strWSDLUrl;
	tstring strRunDirectory;
	tstring strLocalSystemDirectory;
	int		nSoapTimeout;
	int		nCheckCycle;
	tstring szDebugLevel;			//高 中 低 关
}YDConfig;

#include "..\ObjectSerDef\_tagYDConfig_StructInfo.h"
MAKESTRUCTINFO(_tagYDConfig)




typedef struct _tagUserMapSet
{
	tstring szUserName;
	tstring szPassword;
	tstring szUserType;			//用户类型 暂定为测试人员，研发人员，管理员
	tstring szChildUserType;	//暂时不用，以后定位细分后扩展
	tstring szChildUserType1;	//暂时不用，以后定位细分后扩展
}UserMapSet,*PUserMapSet;
//根据用户类型展开相关业务界面
//客户端获取对象地址 UserInfo\UserMap\xxxx   //xxxx为用户名


typedef struct _tagUserProjectSet
{
	tstring szUserName;
	tstring szProjectName;
}UserProjectSet,*PUserProjectSet;

typedef struct _tagUserOwnProjectTab
{
	map<tstring,_tagUserProjectSet,less<tstring> > OwnProjectArray; //用项目名称做索引
}UserOwnProjectTab,*PUserOwnProjectTab;


typedef struct _tagProjectOwnUserSet
{
	tstring szUserName;
	tstring szUserType;
}ProjectOwnUserSet,*PProjectOwnUserSet;

typedef struct _tagProjectOwnUser
{
	map<tstring,_tagProjectOwnUserSet,less<tstring> > OwnUserMap; //用项目名称做索引
}ProjectOwnUser,*PProjectOwnUser;

//用户拥有的项目列表
//地址 UserInfo\UserOwnProject\xxxx  //xxxx为用户名

//项目配置字段，备用
typedef struct _tagConfigInfo
{
	map<tstring,tstring,less<tstring> > m_CfgArray;
}ConfigInfo,*PConfigInfo;

typedef struct _tagProjectConfig
{
	tstring WorksheetStandard;	//引用的工作单标准
	SER_TO_X<tstring,HexString>  CheckCfgStandard;	//引用的检查配置文件标准
	tstring TestReportStandard; //测试报告规范标准。
}ProjectConfig,*PProjectConfig;

typedef struct _tagProjectState
{
	tstring szProjectState;					//报表处理状态 测试新建项目为"新建"，完成报表后为"测试已提交"，研发处理结束后为"研发已提交" 管理员"归档"
	
}ProjectState,*PProjectState;



//白盒测试目录
//CodeTest\

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


//UserInfo\UserOwnProject\xxxx  //xxxx为用户名

//项目 没有对应数据结构，只有目录结构
// WhiteBoxTestProject\  所有项目相关数据结构放在此目录下
//				|----------------Project_XXXX\    每个项目一个目录，XXXX为项目名称
//										|-------Directory_XXXXXX
//													|-------Directory_XXXXXX
//																|-------ChildTest_XXXX\		每次测试项目名称
//																				|----------Worksheet		项目工作单对象XML
//																				|----------CheckCfg		项目检查工具配置对象XML，对应结构_tagProjectConfig		
//																				|----------TestReport		项目测试报告对象XML
//																				|----------ProjectState	项目状态对象
//																				|----------ProjectConfig	项目全局配置信息，为将来扩展做规范定义
//																				|-------Directory_XXXXXX
//																								|-------ChildTest_XXXX\		每次测试项目名称
//																												|----------Worksheet		项目工作单对象XML
//																												|----------CheckCfg		项目检查工具配置对象XML，对应结构_tagProjectConfig		
//																												|----------TestReport		项目测试报告对象XML
//																												|----------ProjectState	项目状态对象
//																												|----------ProjectConfig	项目全局配置信息，为将来扩展做规范定义
//										|-------Directory_XXXXXX
//													|-------Directory_XXXXXX
//																|-------ChildTest_XXXX\		每次测试项目名称
//																				|----------Worksheet		项目工作单对象XML
//																				|----------CheckCfg		项目检查工具配置对象XML，对应结构_tagProjectConfig		
//																				|----------TestReport		项目测试报告对象XML
//																				|----------ProjectState	项目状态对象
//																				|----------ProjectConfig	项目全局配置信息，为将来扩展做规范定义
//										|-------GroupMsg\
//													|----2013-05-27#count#Msg	//消息体
//													|----MsgInfo　//存放与该讨论组相关的总体信息
//										|-------ProjectUser						项目用户列表
//				|----------------Project_XXXX\    每个项目一个目录，XXXX为项目名称
//										|-------Directory_XXXXXX
//													|-------Directory_XXXXXX
//																|-------ChildTest_XXXX\		每次测试项目名称
//																				|----------Worksheet		项目工作单对象XML
//																				|----------CheckCfg		项目检查工具配置对象XML，对应结构_tagProjectConfig		
//																				|----------TestReport		项目测试报告对象XML
//																				|----------ProjectState	项目状态对象
//																				|----------ProjectConfig	项目全局配置信息，为将来扩展做规范定义
//										|-------Directory_XXXXXX
//													|-------Directory_XXXXXX
//																|-------ChildTest_XXXX\		每次测试项目名称
//																				|----------Worksheet		项目工作单对象XML
//																				|----------CheckCfg		项目检查工具配置对象XML，对应结构_tagProjectConfig		
//																				|----------TestReport		项目测试报告对象XML
//																				|----------ProjectState	项目状态对象
//																				|----------ProjectConfig	项目全局配置信息，为将来扩展做规范定义
//										|-------GroupMsg\
//													|----2013-05-27#count#Msg	//消息体
//													|----MsgInfo　//存放与该讨论组相关的总体信息
//										|-------ProjectUser						项目用户列表


// WhiteBoxTestStandard\ 存放白盒测试标准数据库
//		|----------------MachineCheckStandard\		机械走读规范
//								|-------MachineCheckStandard_XXXXXX\							XXXXX是规范名称 (统一规范VER1.0)
//												|-------MachineCheckStandardSpecify				统一规范标准说明书
//												|-------MachineCheckStandardLib					机械走读规范-规则 XML，对应结构MachineCheckStandardLib；文件中应该有版本字段，使用时在界面上显示版本信息
//												|-------MachineCheckStandard-Rule-diff			机械走读规范-规则 更新说明：每一次版本提交都要说明提交人，日期，更新内容等；需专门做界面管理；暂时不做，该功能不重要
//												|-------MachineCheckStandardTypeLib				械走读规范-规则类型 XML，对应结构MachineCheckStandardTypeLib
//												|-------ThirdStandardlib						械走读规范-规则引用 XML，对应结构ThirdStandardlib
//												|-------ErrorWarningDefine						械走读规范-规则引用 XML，对应结构ThirdStandardlib


//WhiteBoxTestProjectConfigTemplate\ 存放项目配置模板数据对象
//					|-------------------CheckToolType_XXXXXX\									XXXX为工具名称
//													|---------ProjectConfigTemplate_XXXXX		XXXX为模板适用类型

//统一规范描述说明书
typedef struct _tagMachineCheckStandardSpecify{
	tstring szMachineCheckStandardSpecify;			//规范说明书
}MachineCheckStandardSpecify,*PMachineCheckStandardSpecify;

//规则类型，参见文档<<YD-测试.工具检查规范.xls>>的“错误类型定义”页面
typedef struct _tagMachineCheckStandardTypeSet {
	tstring id;
	tstring name;								//类型名称，分为大类和子类，大类如“规范性问题”，子类如“语法格式问题”等
	unsigned long min_range;					//类型所包含规则的编号范围
	unsigned long max_range;
	tstring parent_id;							//如果是大类，则该字段为0，否则为父类的ID
} MachineCheckStandardTypeSet, *PMachineCheckStandardTypeSet;

typedef struct _tagErrorWarningSet
{
	SER_TO_X<tstring,HexString> szErrorWarningName;	
	SER_TO_X<tstring,HexString> szErrorWarningDesc;

}ErrorWarningSet,*PErrorWarningSet;


//机械走读统一规范
typedef struct _tagMachineCheckStandardSet {
	tstring szErrorNum;
	tstring szErrorType;			//错误类型
	SER_TO_X<tstring,HexString> szDesc;					//错误描述
	tstring szErrorWarning;			//错误警告类型 建议，警告，严重错误
	tstring szErrorTypeId;				//引用自结构MachineCheckStandardTypeSet
	SER_TO_X<tstring,HexString> szErrorSuggest;
	
} MachineCheckStandardSet, *PMachineCheckStandardSet;

//第三方机械走读规范映射 通过rule_id关联到统一机械走读规范
typedef struct _tagThirdStandardSet {
	tstring szUniteStandardErrorNum;		//机械走读统一规范
	tstring szThirdStandardErrorNum;		//PCLINT或者CTester的错误ID
	SER_TO_X<tstring,HexString> szThirdStandardErrorDesc;
	SER_TO_X<tstring,HexString> szErrorSuggest;					//建议
	BOOL is_manual_check;					//是否需要人工检查
	SER_TO_X<tstring,HexString> szManual_check_MethodSpecify;	//人工复查标准说明，指导测试人员人工复查。
	BOOL is_dealwith;						//是否需要处理

	tstring ToolType;						//类似"PCLINT", "C++ TESTER"
} ThirdStandardSet, *PThirdStandardSet;


//警告类型定义

typedef struct _tagErrorWarningArray
{
	vector<_tagErrorWarningSet> WarningArray;

}ErrorWarningArray,*PErrorWarningArray;

//统一机械走读 "规则类型" 规范库
typedef struct _tagMachineCheckStandardTypeLib
{
	map<tstring,_tagMachineCheckStandardTypeSet,less<tstring> > libmap;
}MachineCheckStandardTypeLib,*PMachineCheckStandardTypeLib;

//统一机械走读规范库
typedef struct _tagMachineCheckStandardLib
{
	map<tstring,_tagMachineCheckStandardSet,less<tstring> > libmap;
}MachineCheckStandardLib,*PMachineCheckStandardLib;

//第三方机械走读规范映射表 通过rule_id关联到统一机械走读规范
typedef struct _tagThirdStandardlib
{
	map<tstring,_tagThirdStandardSet,less<tstring> > libmap;
}ThirdStandardlib,*PThirdStandardlib;

//测试工作单结构，该结构在整个测试过程中都会使用
typedef struct _S_WORKSHEET {
	tstring szProjectNo;
	tstring szModuleNo;
	tstring szWorksheetNo;		
	tstring szApplyDate;
	tstring szApplyMan;
	tstring szResponsiblePerson;
	tstring szDefaultDispatchUser;
	tstring szCheckRange;
	int nCheckType;					//1 为增量检查；2 为全部检查
	tstring szPreWorksheetNo;	
	tstring szSVNCodePath;
	tstring szSourceList;

	tstring szSuggest;
	int nCheckResult;				//0 为成功；1 为异常中止
	tstring szFailReason;
	tstring szSignatureMan;
	tstring szSignatureDate;
} WORKSHEET, *PWORKSHEET;

typedef struct _tagReportLog
{
	tstring	szUserName;
	__int64 tmDate;		//日期
	SER_TO_X<tstring,HexString> szReport_log;
}ReportLog,*PReportLog;

//测试报表结构
typedef struct _S_REPORT_ITEM {
	tstring szTestState;										//测试记录状态 "检查通过" "需要人工复查" "需要充实规范" "忽略"
	tstring szTestItemSource;									//报告来源,"自动生成" "人工复查" "人工检查"	
	tstring szTestToolType;										//工具类型
	tstring szUniteStandardErrorNum;							//机械走读统一规范
	tstring szThirdStandardErrorNum;							//PCLINT或者CTester的错误ID
	SER_TO_X<tstring,Base64ZipString> szErrorCodeContent;				//问题代码所在行的内容
	SER_TO_X<tstring,Base64ZipString> szErrorCodePosition;								//问题代码所在的文件名和行号
	SER_TO_X<tstring,Base64ZipString> szModule;						//所检查源文件的文件名
	SER_TO_X<tstring,Base64ZipString> szSuggest;						//建议
	SER_TO_X<tstring,Base64ZipString> szDesc;							//问题的简要描述

	SER_TO_X<tstring,Base64ZipString> szUniteSuggest;					//统一规范建议
	SER_TO_X<tstring,Base64ZipString> szUniteDesc;					//统一规范问题的简要描述

	SER_TO_X<tstring,Base64ZipString> szThirdSuggest;					//第三方建议
	SER_TO_X<tstring,Base64ZipString> szThirdDesc;					//第三方问题的简要描述

	tstring szErrorType;										//错误类型
	tstring szErrorWarning;										//错误警告类型 建议，警告，严重错误

	tstring szCreateTime;										//创建时间
	tstring szLastEditTime;										//最后修正时间

	//研发反馈信息
	tstring szDevelopState;										//此问题的状态 测试提交后为新增 研发处理后为修复，挂起，未决。
	vector<_tagReportLog>	szReport_log;						//问题交流记录
	tstring szProcessUser;										//问题处理人，默认处理人在工作单配置中
} REPORT_ITEM, *PREPORT_ITEM;


typedef struct _S_REPORT {
	tstring szName;						//报表名称
	unsigned long nTotalErrorCount;		//错误总数
	unsigned long nErrorCount_1;			//严重错误总数
	unsigned long nErrorCount_2;			//中等错误总数
	unsigned long nErrorCount_3;			//一般错误总数
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
	tstring szID;					//本次测试ID
	tstring szInheritID;			//继承的上次测试ID
	vector<_tagUnitReportSet> UnitReportArray;
}UnitReport,*PUnitReport;

//项目配置
typedef struct _S_PROJECT_CONFIG {
	tstring config_content;					//标准参数
} PROJECT_CONFIG, *PPROJECT_CONFIG;



//PCLint 报告
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

// 用于自动化生成分布式对象
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
	unsigned int nDescTotal;		//描述类型总数
	unsigned int nErrorTotal;		//
	unsigned int nComplateTotal;
	unsigned int nManaualTotal;
	unsigned int nIgnoreTotal;
}ReportOutput_Overall;

typedef struct _tagReportOutput
{
	//总体报告overall
	_tagReportOutput_Overall	Overall;
	//摘要Summary
	vector<_tagReportOutput_Summary>	Summary;
	//详细报告detailed
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




//////////////////////////////////////////消息系统//////////////////////////////////////////
//附件
typedef struct _tagMsgData
{
	tstring szType;			//数据类型　bin文件，jpg图片　gif动画，midi音乐，音频，视频 html
	tstring szData;	
}MsgData,*PMsgData;

typedef struct _tagMsgBody
{
	tstring szSenderUser;
	tstring szSendDate;			//发送日期
	tstring szTitle;			//发送标题
	vector<tstring>				szRecvUserList;			//接收用户列表
	vector<_tagMsgData>			tagMsgAppend;			//附件
	_tagMsgData					szMsgData;				//消息数据
}MsgBody,*PMsgBody;

typedef struct _tagUserMsgInfo
{
	tstring szBeginMsgTime;					//开始消息时间
	tstring szEndMsgTime;					//最后消息时间
	unsigned int nMsgNum;					//消息数
	vector<tstring>		szNewMsgIndex;		//新消息索引
}UserMsgInfo,*PUserMsgInfo;

#include "..\ObjectSerDef\_tagMsgData_StructInfo.h"
MAKESTRUCTINFO(_tagMsgData)
#include "..\ObjectSerDef\_tagMsgBody_StructInfo.h"
MAKESTRUCTINFO(_tagMsgBody)
#include "..\ObjectSerDef\_tagUserMsgInfo_StructInfo.h"
MAKESTRUCTINFO(_tagUserMsgInfo)
