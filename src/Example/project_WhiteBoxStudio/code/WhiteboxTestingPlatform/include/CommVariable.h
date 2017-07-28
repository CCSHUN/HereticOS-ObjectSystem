#ifndef COMMVARIABLE_H
#define COMMVARIABLE_H

#include "XmlDomOpt.h"

//#define PROJECT_ID_POS				"A1"

#define EXCEL_MMULT					"MMULT"
#define EXCEL_SUM					"SUM"
#define EXCEL_SUB					"SUB"
#define EXCEL_DIV					"DIV"
#define EXCEL_MIX					"MIX"
#define EXCEL_RATE					"RATE"

#define MERGE_TYPE_ROW				0
#define MERGE_TYPE_COL				1

//条件格式的前导符
#define IFSTYLE_E					"E"			//等于
#define IFSTYLE_G					"G"			//大于
#define IFSTYLE_GE					"GE"		//大于等于
#define IFSTYLE_L					"L"			//小于
#define IFSTYLE_LE					"LE"		//小于等于
#define IFSTYLE_NE					"NE"		//不等于
#define IFSTYLE_OPTR_REMARK			"="			
#define	IFSTYLE_AND					"and"		//条件格式中条件之间的连接符

#define NULL_HDOMNODE				(HDOMNODE)NULL

//单元格内容的回车换行标记
#define CELL_RETURN_REMARK			"\\n\\r"
#define CELL_RETURN_REMARK2			"\\r\\n"

//公式计算时用于替换变量
#define MATH_REPLACE_VAR_NAME		"MATH"

//公式中用于替换如 “SUM(H6:H12)” 等表达式
#define MATH_EXPR_NAME				"EXPR"

//在单元格文本内来标示是否是公式内容
#define CELL_MATH_REMARK			"="

//从XML格式文件中导入公式时，复合变量的标记
#define COMPLEX_VAR_MARK			"$"

#define MATH_ERROR_SHOWSTR			"#REF!"

//在Combobox风格的控件中，数据的分隔符号
#define	COMBOBOX_DATA_MARK			"#MARK!"

//单元格为控件时的类名
#define	CELLTYPE_COMBOBOX_CLASSNAME	"CGridCellCombo"
#define	CELLTYPE_STAT_CLASSNAME		"CGridCellStat"
#define	CELLTYPE_CHECK_CLASSNAME	"CGridCellCheck"
#define	CELLTYPE_BUTTON_CLASSNAME	"CGridCellButton"
#define	CELLTYPE_RADIO_CLASSNAME	"CGridCellRadio"
#define	CELLTYPE_DATETIME_CLASSNAME	"CGridCellDateTime"
#define	CELLTYPE_NUMERIC_CLASSNAME	"CGridCellNumeric"
#define	CELLTYPE_URL_CLASSNAME		"CGridURLCell"
#define	CELLTYPE_PICTURE_CLASSNAME	"CGridCellPicture"
#define	CELLTYPE_Default_CLASSNAME	"CGridCell"
#define	CELLTYPE_FLOAT_CLASSNAME	"CGridCellFloat"
#define	CELLTYPE_ALPHA_CLASSNAME	"CGridCellAlpha"

//定义统计cell风格
#define CELLTYPE_STAT_RESULT		"CGridCellStatResult"
#define CELLTYPE_STAT_VAR			"CGridCellStatVar"   

//公式计算错误时的表示
#define MATH_ERROR_DIV_0			"#DIV/0!"		//除数为0 ; 在公式中除数使用了空单元格或是包含零值单元格的单元格引用
#define MATH_ERROR_VALUE			"#VALUE!"		//输入引用文本项的数学公式 ; 使用了不正确的参数或运算符
#define MATH_ERROR_REF				"#REF!"			//删除了被公式引用的单元格范围
#define MATH_ERROR_NAME				"#NAME?"		//在公式中使用了Excel所不能识别的文本
#define MATH_ERROR_UNKNOWN			"#UNKNOWN?"		//未知错误
#define MATH_ERROR_REF_ALIAS		"REF"

//保存为XML样式文件时，样式类型的前缀
#define STYLE_PRE_NAME				"s"

//消息窗口的名称
#define MESSAGEWIN_TITLENAME		"报表管理平台"

//控件版本
#define GRID_VERSION				"3.20.50.30-109"

#define DT_LEFT2					0x00000010

//输出为Excel文件时的样式, Excel样式时打印不输出第0行和第0列, 普通样式输出所有的列
#define	GRIDSTYLE_EXCEL				1
#define	GRIDSTYLE_NORMAL			2

//导入XML数据时记录公式
struct SMATH
{
	CString sPos;
	CString sExpr;
	HDOMNODE hNode;			//当前节点
};

//倒入样式文件时记录公式
struct SMATH_MODE
{
	int nRow;
	int nCol;
	CString sExpr;
};

//更新公式时，记录SUM等子算式的起始行
struct SSUBMATH_ROW
{
	int nStartRow;
	int nEndRow;
};


//计算RATE子算式时, 存放条件
//1: fIF1< x <fIF2		2: fIF1< x <=fIF2		3: fIF1< x   
//4: fIF1<= x <fIF2		5: fIF1<= x <=fIF2		6: fIF1<= x   	
//7: x <fIF2			8: x <=fIF2				9: x   		
struct SMATH_RATE
{
	int   cType;	
	float fIF1;
	float fIF2;
	float fValue;
};

//每个列对应的名字, 限制为100列
#define COLS_COUNT   100
extern CString gCols[COLS_COUNT];


#endif