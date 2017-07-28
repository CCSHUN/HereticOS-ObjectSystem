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

//������ʽ��ǰ����
#define IFSTYLE_E					"E"			//����
#define IFSTYLE_G					"G"			//����
#define IFSTYLE_GE					"GE"		//���ڵ���
#define IFSTYLE_L					"L"			//С��
#define IFSTYLE_LE					"LE"		//С�ڵ���
#define IFSTYLE_NE					"NE"		//������
#define IFSTYLE_OPTR_REMARK			"="			
#define	IFSTYLE_AND					"and"		//������ʽ������֮������ӷ�

#define NULL_HDOMNODE				(HDOMNODE)NULL

//��Ԫ�����ݵĻس����б��
#define CELL_RETURN_REMARK			"\\n\\r"
#define CELL_RETURN_REMARK2			"\\r\\n"

//��ʽ����ʱ�����滻����
#define MATH_REPLACE_VAR_NAME		"MATH"

//��ʽ�������滻�� ��SUM(H6:H12)�� �ȱ��ʽ
#define MATH_EXPR_NAME				"EXPR"

//�ڵ�Ԫ���ı�������ʾ�Ƿ��ǹ�ʽ����
#define CELL_MATH_REMARK			"="

//��XML��ʽ�ļ��е��빫ʽʱ�����ϱ����ı��
#define COMPLEX_VAR_MARK			"$"

#define MATH_ERROR_SHOWSTR			"#REF!"

//��Combobox���Ŀؼ��У����ݵķָ�����
#define	COMBOBOX_DATA_MARK			"#MARK!"

//��Ԫ��Ϊ�ؼ�ʱ������
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

//����ͳ��cell���
#define CELLTYPE_STAT_RESULT		"CGridCellStatResult"
#define CELLTYPE_STAT_VAR			"CGridCellStatVar"   

//��ʽ�������ʱ�ı�ʾ
#define MATH_ERROR_DIV_0			"#DIV/0!"		//����Ϊ0 ; �ڹ�ʽ�г���ʹ���˿յ�Ԫ����ǰ�����ֵ��Ԫ��ĵ�Ԫ������
#define MATH_ERROR_VALUE			"#VALUE!"		//���������ı������ѧ��ʽ ; ʹ���˲���ȷ�Ĳ����������
#define MATH_ERROR_REF				"#REF!"			//ɾ���˱���ʽ���õĵ�Ԫ��Χ
#define MATH_ERROR_NAME				"#NAME?"		//�ڹ�ʽ��ʹ����Excel������ʶ����ı�
#define MATH_ERROR_UNKNOWN			"#UNKNOWN?"		//δ֪����
#define MATH_ERROR_REF_ALIAS		"REF"

//����ΪXML��ʽ�ļ�ʱ����ʽ���͵�ǰ׺
#define STYLE_PRE_NAME				"s"

//��Ϣ���ڵ�����
#define MESSAGEWIN_TITLENAME		"�������ƽ̨"

//�ؼ��汾
#define GRID_VERSION				"3.20.50.30-109"

#define DT_LEFT2					0x00000010

//���ΪExcel�ļ�ʱ����ʽ, Excel��ʽʱ��ӡ�������0�к͵�0��, ��ͨ��ʽ������е���
#define	GRIDSTYLE_EXCEL				1
#define	GRIDSTYLE_NORMAL			2

//����XML����ʱ��¼��ʽ
struct SMATH
{
	CString sPos;
	CString sExpr;
	HDOMNODE hNode;			//��ǰ�ڵ�
};

//������ʽ�ļ�ʱ��¼��ʽ
struct SMATH_MODE
{
	int nRow;
	int nCol;
	CString sExpr;
};

//���¹�ʽʱ����¼SUM������ʽ����ʼ��
struct SSUBMATH_ROW
{
	int nStartRow;
	int nEndRow;
};


//����RATE����ʽʱ, �������
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

//ÿ���ж�Ӧ������, ����Ϊ100��
#define COLS_COUNT   100
extern CString gCols[COLS_COUNT];


#endif