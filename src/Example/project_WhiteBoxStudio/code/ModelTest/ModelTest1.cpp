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
	vector<UserProjectSet> OwnProjectArray;
}UserOwnProjectTab,*PUserOwnProjectTab;

//�û�ӵ�е���Ŀ�б�
//��ַ UserInfo\UserOwnProject\xxxx  //xxxxΪ�û���

typedef struct _tagProjectConfig
{
	tstring WorksheetStandard;	//���õĹ�������׼
	tstring CheckCfgStandard;	//���õļ�������ļ���׼
	tstring TestReportStandard; //���Ա���淶��׼��
}ProjectConfig,*PProjectConfig;


//��׼����
//WhiteBoxTestStandard\


//��Ŀ û�ж�Ӧ���ݽṹ��ֻ��Ŀ¼�ṹ
// WhiteBoxTestProject\  ������Ŀ������ݽṹ���ڴ�Ŀ¼��
//		|----------------Project_XXXX\    ÿ����Ŀһ��Ŀ¼��XXXXΪ��Ŀ����
//								|-------ChildTest_XXXX\		ÿ�β�����Ŀ����
//                                            |----------Worksheet		��Ŀ����������XML
//											  |----------CheckCfg		��Ŀ��鹤�����ö���XML		
//											  |----------TestReport		��Ŀ���Ա������XML
//											  |----------ProjectConfig	��Ŀȫ��������Ϣ��Ϊ������չ���淶����
//		|----------------Project_XXXX\    ÿ����Ŀһ��Ŀ¼��XXXXΪ��Ŀ����
//								|-------ChildTest_XXXX\		ÿ�β�����Ŀ����
//                                            |----------Worksheet		��Ŀ����������XML
//											  |----------CheckCfg		��Ŀ��鹤�����ö���XML		
//											  |----------TestReport		��Ŀ���Ա������XML
//											  |----------ProjectConfig	��Ŀȫ��������Ϣ��Ϊ������չ���淶����


//�ݶ��Ľӿ�

class CObjectSystem
{
public:
	struct _tagObjectState 
	{
		BOOL	bLock;			//�����Ƿ�����
		tstring szLockUser;		//��ǰ��ȡ�����û�
		unsigned int nLockTime;	//����ʱ��
	};

	//Ŀ¼��Ϣ
	enum DirectoryObjectType
	{
		Directory=1,
		File=2,
	};

	struct _tagDirectoryInfoSet
	{
		tstring					ObjectName;		//������
		DirectoryObjectType		ObjectType;		//��������
		tstring					OtherInfo;		//����������Ϣ
	};

	struct _tagDirectoryInfo
	{
		unsigned int nTotalOfObject;
		vector<_tagDirectoryInfoSet> DirectoryInfoArray;
	};
	enum SYSTEMERROR
	{
		Logon_PassWordError=1,		//�������
		Logon_UserError=2,			//�û�������
		ObjectAlreadyLock=11,		//�����Ѿ�����
		ObjectAlreadyExist=12,		//�����Ѿ�����
		ObjectNotExist=13,			//���󲻴���
		DirectoryAlreadyExist=21,	//�����Ѿ�����
		DirectoryNotExist=22,		//Ŀ¼������
	};

	CObjectSystem();
	~CObjectSystem();

	//////////////////////////////////////////�����������///////////////////////////////////////

	//�������� ������Ŀ¼����������ļ�����
	virtual BOOL CreateObject(IN tstring & ObjectPath,DirectoryObjectType &ObjectType);
	//ObjectPath	�����ַ
	//Object		���ص�XML����
	//ObjectState	��������ö��������ʱ�� 0����Ϊ���������ظö����������Ϣ����������Ѿ��������û��������򷵻������û�������Ϣ
	virtual BOOL GetObject(IN tstring & ObjectPath,OUT tstring & Object,IN OUT _tagObjectState & ObjectState,OUT SYSTEMERROR * pError);

	//���¶��󵽴洢
	virtual BOOL UpDataObject(IN tstring & ObjectPath,IN tstring & Object,SYSTEMERROR * pError);

	//��ȡĿ¼��Ϣ
	virtual BOOL GetDirectoryInfo(IN tstring & DirectoryPath,OUT _tagDirectoryInfo & DirectoryInfo,OUT SYSTEMERROR * pError);

	//ɾ������
	virtual BOOL DeleteObject(IN tstring & DirectoryPath,SYSTEMERROR * pError);




	//////////////////////////////////////////����ϵͳ��½�ǳ�///////////////////////////////////////
	//��½����洢ϵͳ
	virtual BOOL LogonInSystem(IN tstring & szUserName,IN tstring & szPassword);

	//�ǳ�
	virtual BOOL LogonOutSystem();

	//////////////////////////////////////////����������///////////////////////////////////////

	//���¶�������Ϣ
	virtual BOOL UpDataObjectState(IN tstring & ObjectPath,OUT _tagObjectState & ObjectState,OUT SYSTEMERROR * pError);
	
	//��ȡ��������Ϣ
	virtual BOOL GetObjectState(IN tstring & ObjectPath,OUT _tagObjectState & ObjectState,OUT SYSTEMERROR * pError);


	////////////////////////////////////////��������////////////////////////////////////////////////
	class ObjectEventProcessInterface
	{
	public: 
		ObjectEventProcessInterface();
		~ObjectEventProcessInterface();
		enum EventType
		{
			ObjectEvent_Updata=1,	//����ʱ����
			ObjectEvent_Create=2,	//����ʱ����
			ObjectEvent_Delete=3,	//ɾ��ʱ����
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

