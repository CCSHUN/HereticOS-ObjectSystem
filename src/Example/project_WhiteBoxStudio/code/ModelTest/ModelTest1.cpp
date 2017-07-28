// ModelTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <map>
#include <vector>

typedef unsigned int BOOL;
using namespace std;

#define IN

#define OUT

typedef string tstring;

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
	vector<UserProjectSet> OwnProjectArray;
}UserOwnProjectTab,*PUserOwnProjectTab;

//用户拥有的项目列表
//地址 UserInfo\UserOwnProject\xxxx  //xxxx为用户名

typedef struct _tagProjectConfig
{
	tstring WorksheetStandard;	//引用的工作单标准
	tstring CheckCfgStandard;	//引用的检查配置文件标准
	tstring TestReportStandard; //测试报告规范标准。
}ProjectConfig,*PProjectConfig;


//标准管理
//WhiteBoxTestStandard\


//项目 没有对应数据结构，只有目录结构
// WhiteBoxTestProject\  所有项目相关数据结构放在此目录下
//		|----------------Project_XXXX\    每个项目一个目录，XXXX为项目名称
//								|-------ChildTest_XXXX\		每次测试项目名称
//                                            |----------Worksheet		项目工作单对象XML
//											  |----------CheckCfg		项目检查工具配置对象XML		
//											  |----------TestReport		项目测试报告对象XML
//											  |----------ProjectConfig	项目全局配置信息，为将来扩展做规范定义
//		|----------------Project_XXXX\    每个项目一个目录，XXXX为项目名称
//								|-------ChildTest_XXXX\		每次测试项目名称
//                                            |----------Worksheet		项目工作单对象XML
//											  |----------CheckCfg		项目检查工具配置对象XML		
//											  |----------TestReport		项目测试报告对象XML
//											  |----------ProjectConfig	项目全局配置信息，为将来扩展做规范定义


//暂定的接口

class CObjectSystem
{
public:
	struct _tagObjectState 
	{
		BOOL	bLock;			//对象是否被锁。
		tstring szLockUser;		//当前获取锁的用户
		unsigned int nLockTime;	//锁定时间
	};

	//目录信息
	enum DirectoryObjectType
	{
		Directory=1,
		File=2,
	};

	struct _tagDirectoryInfoSet
	{
		tstring					ObjectName;		//对象名
		DirectoryObjectType		ObjectType;		//对象类型
		tstring					OtherInfo;		//对象其他信息
	};

	struct _tagDirectoryInfo
	{
		unsigned int nTotalOfObject;
		vector<_tagDirectoryInfoSet> DirectoryInfoArray;
	};
	enum SYSTEMERROR
	{
		Logon_PassWordError=1,		//密码错误
		Logon_UserError=2,			//用户名错误
		ObjectAlreadyLock=11,		//对象已经被锁
		ObjectAlreadyExist=12,		//对象已经存在
		ObjectNotExist=13,			//对象不存在
		DirectoryAlreadyExist=21,	//对象已经存在
		DirectoryNotExist=22,		//目录不存在
	};

	CObjectSystem();
	~CObjectSystem();

	//////////////////////////////////////////对象基本操作///////////////////////////////////////

	//创建对象 可以是目录对象或者是文件对象
	virtual BOOL CreateObject(IN tstring & ObjectPath,DirectoryObjectType &ObjectType);
	//ObjectPath	对象地址
	//Object		返回的XML对象
	//ObjectState	输入申请该对象的锁定时间 0申请为不锁，返回该对象的锁定信息，如果对象已经被其他用户锁定，则返回其他用户的锁信息
	virtual BOOL GetObject(IN tstring & ObjectPath,OUT tstring & Object,IN OUT _tagObjectState & ObjectState,OUT SYSTEMERROR * pError);

	//更新对象到存储
	virtual BOOL UpDataObject(IN tstring & ObjectPath,IN tstring & Object,SYSTEMERROR * pError);

	//获取目录信息
	virtual BOOL GetDirectoryInfo(IN tstring & DirectoryPath,OUT _tagDirectoryInfo & DirectoryInfo,OUT SYSTEMERROR * pError);

	//删除对象
	virtual BOOL DeleteObject(IN tstring & DirectoryPath,SYSTEMERROR * pError);




	//////////////////////////////////////////对象系统登陆登出///////////////////////////////////////
	//登陆对象存储系统
	virtual BOOL LogonInSystem(IN tstring & szUserName,IN tstring & szPassword);

	//登出
	virtual BOOL LogonOutSystem();

	//////////////////////////////////////////对象锁操作///////////////////////////////////////

	//更新对象锁信息
	virtual BOOL UpDataObjectState(IN tstring & ObjectPath,OUT _tagObjectState & ObjectState,OUT SYSTEMERROR * pError);
	
	//获取对象锁信息
	virtual BOOL GetObjectState(IN tstring & ObjectPath,OUT _tagObjectState & ObjectState,OUT SYSTEMERROR * pError);


	////////////////////////////////////////对象事物////////////////////////////////////////////////
	class ObjectEventProcessInterface
	{
	public: 
		ObjectEventProcessInterface();
		~ObjectEventProcessInterface();
		enum EventType
		{
			ObjectEvent_Updata=1,	//更新时触发
			ObjectEvent_Create=2,	//创建时触发
			ObjectEvent_Delete=3,	//删除时触发
		};

		virtual BOOL ObjectEventProcess(IN tstring & ObjectPath,IN EventType & nEvent)
		{

		}
	};
	
	virtual BOOL RegistObjectEvent(IN tstring & ObjectPath,IN ObjectEventProcessInterface::EventType & nEvent,IN ObjectEventProcessInterface  * pEventInterface,OUT SYSTEMERROR * pError);
protected:
	
private:
};

int main(int argc, char* argv[])
{
	printf("Hello World!\n");
	return 0;
}

