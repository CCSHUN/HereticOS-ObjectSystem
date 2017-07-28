#ifndef _COMMON_H

//类型分为大类和子类，每个类型有编号范围
#include <string>
using namespace std;

#define tstring string 

//规则类型
typedef struct _S_RULE_TYPE {
	unsigned long id;
	tstring name;
	unsigned long min_range;	//类型所属规则的范围
	unsigned long max_range;
	unsigned long parent_id;		//两级规则类型
} RULE_TYPE, *PRULE_TYPE;

//自定义规则
typedef struct _S_RULE {
	unsigned long id;
	tstring desc;
	tstring class;							//分为严重 中等 一般
	unsigned long type_id;			//引用自结构RULE_TYPE
	tstring suggest;
	char is_manual_check;			//是否需要人工检查
	char is_dealwith;					//是否需要处理
} RULE, *PRULE;

//规则的引用
typedef struct _S_RULE_REFERENCE {
	unsigned long rule_id;			//引用自结构RULE
	unsigned long reference_id;	//PCLINT或者CTester的错误ID
	tstring desc;
	tstring type;							//类似"PCLINT", "C++ TESTER"
} RULE_REFERENCE, *PRULE_REFERENCE;

//测试工作单结构
typedef struct _S_WORKSHEET {
	unsigned long id;
	tstring project_no;
	tstring module_no;
	tstring worksheet_no;		
	tstring apply_date;
	tstring apply_man;
	tstring responsible_person;
	tstring tools_and_params;		//项目配置
	char check_type;					//1 为增量检查；2 为全部检查
	tstring pre_worksheet_no;	
	tstring svn_code_path;
	tstring suggest;
	tstring suggest_attachment_filename;
	tstring signature_man;
	tstring signature_date;
} WORKSHEET, *PWORKSHEET;

//测试报表结构
typedef struct _S_REPORT_ITEM {
	unsigned long id;
	unsigned long no;					//问题编号
	unsigned long rule_id;			//取自结构RULE； 如果为-1, 则表示该错误在规则库里不存在
	unsigned long report_id;		//取自结构REPORT
	tstring error_code_content;	//问题代码所在行的内容
	tstring error_code_position;	//问题代码所在的文件和行号
	tstring module;						//所检查源文件的文件名
	tstring summary;					//问题的简要描述
} REPORT_ITEM, *PREPORT_ITEM;

typedef struct _S_REPORT {
	unsigned long id;
	unsigned long name;						//报表名称
	unsigned long total_error_count;		//错误总数
	unsigned long error_count_1;			//严重错误总数
	unsigned long error_count_2;			//中等错误总数
	unsigned long error_count_3;			//一般错误总数
	vector<REPORT_ITEM> items;
} REPORT, *PREPORT;

//项目配置
typedef struct _S_PROJECT_CONFIG {
	string worksheet_no;				//工作单编号
	string config_content;			//配置内容
} PROJECT_CONFIG, *PPROJECT_CONFIG;

typedef struct _S_CONFIG {
	unsigned long id;
	string name;							//配置名称
	string content;						//配置内容
} CONFIG, *PCONFIG;


#endif