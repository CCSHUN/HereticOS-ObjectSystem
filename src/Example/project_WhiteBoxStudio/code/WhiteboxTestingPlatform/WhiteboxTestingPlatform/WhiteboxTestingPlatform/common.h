#ifndef _COMMON_H

//���ͷ�Ϊ��������࣬ÿ�������б�ŷ�Χ
#include <string>
using namespace std;

#define tstring string 

//��������
typedef struct _S_RULE_TYPE {
	unsigned long id;
	tstring name;
	unsigned long min_range;	//������������ķ�Χ
	unsigned long max_range;
	unsigned long parent_id;		//������������
} RULE_TYPE, *PRULE_TYPE;

//�Զ������
typedef struct _S_RULE {
	unsigned long id;
	tstring desc;
	tstring class;							//��Ϊ���� �е� һ��
	unsigned long type_id;			//�����ԽṹRULE_TYPE
	tstring suggest;
	char is_manual_check;			//�Ƿ���Ҫ�˹����
	char is_dealwith;					//�Ƿ���Ҫ����
} RULE, *PRULE;

//���������
typedef struct _S_RULE_REFERENCE {
	unsigned long rule_id;			//�����ԽṹRULE
	unsigned long reference_id;	//PCLINT����CTester�Ĵ���ID
	tstring desc;
	tstring type;							//����"PCLINT", "C++ TESTER"
} RULE_REFERENCE, *PRULE_REFERENCE;

//���Թ������ṹ
typedef struct _S_WORKSHEET {
	unsigned long id;
	tstring project_no;
	tstring module_no;
	tstring worksheet_no;		
	tstring apply_date;
	tstring apply_man;
	tstring responsible_person;
	tstring tools_and_params;		//��Ŀ����
	char check_type;					//1 Ϊ������飻2 Ϊȫ�����
	tstring pre_worksheet_no;	
	tstring svn_code_path;
	tstring suggest;
	tstring suggest_attachment_filename;
	tstring signature_man;
	tstring signature_date;
} WORKSHEET, *PWORKSHEET;

//���Ա���ṹ
typedef struct _S_REPORT_ITEM {
	unsigned long id;
	unsigned long no;					//������
	unsigned long rule_id;			//ȡ�ԽṹRULE�� ���Ϊ-1, ���ʾ�ô����ڹ�����ﲻ����
	unsigned long report_id;		//ȡ�ԽṹREPORT
	tstring error_code_content;	//������������е�����
	tstring error_code_position;	//����������ڵ��ļ����к�
	tstring module;						//�����Դ�ļ����ļ���
	tstring summary;					//����ļ�Ҫ����
} REPORT_ITEM, *PREPORT_ITEM;

typedef struct _S_REPORT {
	unsigned long id;
	unsigned long name;						//��������
	unsigned long total_error_count;		//��������
	unsigned long error_count_1;			//���ش�������
	unsigned long error_count_2;			//�еȴ�������
	unsigned long error_count_3;			//һ���������
	vector<REPORT_ITEM> items;
} REPORT, *PREPORT;

//��Ŀ����
typedef struct _S_PROJECT_CONFIG {
	string worksheet_no;				//���������
	string config_content;			//��������
} PROJECT_CONFIG, *PPROJECT_CONFIG;

typedef struct _S_CONFIG {
	unsigned long id;
	string name;							//��������
	string content;						//��������
} CONFIG, *PCONFIG;


#endif