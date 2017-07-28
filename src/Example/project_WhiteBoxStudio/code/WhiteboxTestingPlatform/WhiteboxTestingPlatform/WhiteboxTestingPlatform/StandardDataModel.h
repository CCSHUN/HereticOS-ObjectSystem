#pragma once

//�ṩ �������ݷ���
#include "UiStructDef.h"
class CStandardDataModel
{
public:
	CStandardDataModel(void);
	~CStandardDataModel(void);
	BOOL GoProjectPage(tstring & szAddr);

	BOOL GetStandardTree(CViewTree & TreeCtl);
	BOOL NewStandard(tstring szStandardName);
	BOOL DelStandard(tstring szStandardName);

	//ͨ����׼����ȡ��׼
	BOOL GetStandardByName(IN tstring & szStandardName,OUT _tagMachineCheckStandardLib & MachineCheckStandardLib,OUT _tagThirdStandardlib & ThirdStandardLib);
	BOOL UpDataStandardByName(IN tstring & szStandardName,IN _tagMachineCheckStandardLib & MachineCheckStandardLib,IN _tagThirdStandardlib & ThirdStandardLib);



	BOOL GetUniteStandardByName(IN tstring & szStandardName,OUT _tagMachineCheckStandardLib & MachineCheckStandardLib);
	BOOL UpDataUniteStandardByName(IN tstring & szStandardName,IN _tagMachineCheckStandardLib & MachineCheckStandardLib);
	BOOL GetThirdStandardByName(IN tstring & szStandardName,OUT _tagThirdStandardlib & ThirdStandardLib);
	BOOL UpDataThirdStandardByName(IN tstring & szStandardName,IN _tagThirdStandardlib & ThirdStandardLib);

	BOOL GetUniteStandardByName(IN tstring & szStandardName,OUT _tagMachineCheckStandardLib_Wrap & MachineCheckStandardLib);
	BOOL UpDataUniteStandardByName(IN tstring & szStandardName,IN _tagMachineCheckStandardLib_Wrap & MachineCheckStandardLib);
	BOOL GetThirdStandardByName(IN tstring & szStandardName,OUT _tagThirdStandardlib_Wrap & ThirdStandardLib);
	BOOL UpDataThirdStandardByName(IN tstring & szStandardName,IN _tagThirdStandardlib_Wrap & ThirdStandardLib);



	BOOL GetAllStandardNameArray(vector<tstring> & NameList);

	BOOL GetStandardErrorTypeNameLib(IN tstring & szStandardName,OUT _tagMachineCheckStandardTypeLib & lib);
	BOOL UpdataStandardErrorTypeNameLib(IN tstring & szStandardName,OUT _tagMachineCheckStandardTypeLib & lib);
	BOOL GetStandardErrorWarningNameArray(IN tstring & szStandardName,OUT _tagErrorWarningArray & lib);
	BOOL UpdataStandardErrorWarningNameArray(IN tstring & szStandardName,OUT _tagErrorWarningArray & lib);

	BOOL GetStandardErrorTypeNameLib(IN tstring & szStandardName,OUT _tagMachineCheckStandardTypeLib_Wrap & lib);
	BOOL UpdataStandardErrorTypeNameLib(IN tstring & szStandardName,OUT _tagMachineCheckStandardTypeLib_Wrap & lib);
	BOOL GetStandardErrorWarningNameArray(IN tstring & szStandardName,OUT _tagErrorWarningArray_Wrap & lib);
	BOOL UpdataStandardErrorWarningNameArray(IN tstring & szStandardName,OUT _tagErrorWarningArray_Wrap & lib);


private:
	map<tstring,void * ,less<tstring> > m_IndexMap;
	map<tstring,void * ,less<tstring> > m_TreeIndexMap;
};


class CStandardSharedData :public CUiSharedData
{
public:

	_tagMachineCheckStandardLib_Wrap			m_MachineCheckStandardLib;
	_tagThirdStandardlib_Wrap					m_ThirdStandardLib;
	_tagMachineCheckStandardTypeLib_Wrap		m_MachineCheckStandardTypeLib;
	_tagErrorWarningArray_Wrap					m_ErrorWarningArray;

	tstring m_szStandardName;

	BOOL m_bUniteLibWrited;			// ����༭��ͳһ�淶���е�����
	BOOL m_bThirdLibWrited;			// ����༭�˵������淶���е�����
	BOOL m_bErrorTypeLibWrited;		// �������Ϳ��Ѿ�д��
	BOOL m_bErrorWarningLibWrited;	// ���󾯸����Ϳ��Ѿ�д��

	BOOL m_bIsHopeUpdataUniteUi;		//ϣ�����´ν����л�ʱˢ��ͳһ�淶����������
	BOOL m_bIsHopeUpdataThirdUi;		//ϣ�����´ν����л�ʱˢ�µ������淶����������

	

	CStandardSharedData()
	{
		m_bGet=FALSE;
		m_bUniteLibWrited=FALSE;m_bThirdLibWrited=FALSE;
		m_bErrorTypeLibWrited=FALSE;m_bErrorWarningLibWrited=FALSE;
	};
	~CStandardSharedData(){};
	BOOL GetObject();
	BOOL ReGetObject();
	BOOL UpdataObject();
	BOOL init();
protected:
	BOOL m_bGet;
	
private:
};