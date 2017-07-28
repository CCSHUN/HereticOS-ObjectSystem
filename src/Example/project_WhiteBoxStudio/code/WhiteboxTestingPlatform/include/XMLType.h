#ifndef XMLTYPE_H
#define XMLTYPE_H

//样式文件中定义的标签
#define NODE_Styles					"Styles"
#define NODE_Style					"Style"
#define NODE_Alignment				"Alignment"
#define NODE_Font					"Font"
#define NODE_Print					"Print"
#define NODE_TextEdit				"TextEdit"
#define NODE_Worksheet				"Worksheet"	
#define NODE_Table					"Table"	
#define NODE_Column					"Column"	
#define NODE_Row					"Row"	
#define NODE_Cell					"Cell"	
#define NODE_Data					"Data"	
#define NODE_TextEdit				"TextEdit"
#define NODE_Display				"Display"
#define NODE_MapMode				"MapMode"

#define ATTRVAL_FALSE				"FALSE"
#define ATTRVAL_TRUE				"TRUE"

#define ATTR_Border					"Border"
#define ATTRVAL_Border_Both			"BOTH"
#define ATTRVAL_Border_Horz			"HORZ"
#define ATTRVAL_Border_Vert			"VERT"
#define ATTRVAL_Border_None			"NONE"

#define ATTR_Vertical				"Vertical"
#define ATTRVAL_Vertical_Center		"Center"
#define ATTRVAL_Vertical_Top		"Top"
#define ATTRVAL_Vertical_Bottom		"Bottom"

#define ATTR_Horizontal				"Horizontal"
#define ATTRVAL_Horizontal_Center	"Center"
#define ATTRVAL_Horizontal_Left		"Left"
#define ATTRVAL_Horizontal_Right	"Right"

#define ATTR_FontName				"FontName"
#define ATTR_Size					"Size"
#define ATTR_Color					"Color"
#define ATTR_BkColor				"BkColor"

#define ATTR_Bold					"Bold"
#define ATTRVAL_Bold_TRUE			ATTRVAL_TRUE
#define ATTRVAL_Bold_FALSE			ATTRVAL_FALSE

#define ATTR_Enable					"Enable"
#define ATTRVAL_Enable_TRUE			ATTRVAL_TRUE
#define ATTRVAL_Enable_FALSE		ATTRVAL_FALSE

#define ATTR_ColumnCount			"ColumnCount"
#define ATTR_RowCount				"RowCount"

#define ATTR_DefaultColumnWidth			"DefaultColumnWidth"
#define ATTRVAL_DefaultColumnWidth_54	"54"

#define ATTR_DefaultRowHeight			"DefaultRowHeight"
#define ATTRVAL_DefaultRowHeight_13		"13.5"

#define ATTR_Width					"Width"
#define ATTR_Height					"Height"

#define ATTR_MergeAcross			"MergeAcross"
#define ATTR_MergeDown				"MergeDown"

#define ATTR_StyleID				"StyleID"
#define ATTR_Index					"Index"

#define ATTRVAL_ID_DEFAULT			"Default"

#define ATTR_PrintBorder			"PrintBorder"
#define ATTRVAL_PrintBorder_FALSE	ATTRVAL_FALSE
#define ATTRVAL_PrintBorder_TRUE	ATTRVAL_TRUE

#define ATTR_ISDELETED				"IsDeleted"
#define ATTRVAL_ISDELETED_FALSE		ATTRVAL_FALSE
#define ATTRVAL_ISDELETED_TRUE		ATTRVAL_TRUE

#define ATTR_ISINSERTED				"IsInserted"
#define ATTRVAL_ISINSERTED_FALSE	ATTRVAL_FALSE
#define ATTRVAL_ISINSERTED_TRUE		ATTRVAL_TRUE

#define ATTR_PrintNoOutputText				"PrintNoOutputText"
#define ATTRVAL_PrintNoOutputText_FALSE		ATTRVAL_FALSE
#define ATTRVAL_PrintNoOutputText_TRUE		ATTRVAL_TRUE




//格式文件和数据文件中定义的标签

#define ATTR_Type					"type"
#define ATTRVAL_Type_Absolulte		"absolute"
#define ATTRVAL_Type_Relative		"relative"
#define ATTRVAL_Type_Dynamic		"dynamic"

#define ATTR_CellType				"CellType"
#define ATTRVAL_CellType_Combobox	"Combobox"
#define ATTRVAL_CellType_Picture	"Picture"
#define ATTRVAL_CellType_Stat_Res   "Stat-Result"
#define ATTRVAL_CellType_Stat_Var   "Stat-Var"

//如果是公式单元格，判断精度
#define ATTR_Precision				"Precision"	

//如果是组合框，还要判断这两个属性
#define ATTR_Combobox_Style			"ComboboxStyle"		
#define ATTR_Combobox_Sort			"ComboboxSort"
#define ATTRVAL_Combobox_Style_DropDown	"DropDown"
#define ATTRVAL_Combobox_Style_DropList	"DropList"
#define ATTRVAL_Combobox_Sort_TRUE	ATTRVAL_TRUE
#define ATTRVAL_Combobox_Sort_FALSE	ATTRVAL_FALSE

#define ATTR_PicRowExpand			"PicRowExpand"
#define ATTR_PicColExpand			"PicColExpand"

#define ATTR_id                     "id"
#define ATTRVAL_id_MEMO				"$MEMO"  
#define ATTRVAL_id_VALUE			"$VALUE"

#define ATTR_Page					"page"

#define ATTR_rid                    "rid"
#define ATTR_File                   "file"
#define ATTR_Name	                "name"

#define ATTR_MergeRow               "MergeRow"
#define ATTR_MergeCol               "MergeCol"

#define ATTR_Read                   "read"
#define ATTR_Write                  "write"
#define ATTRVAL_Read_OMIT           "0"
#define ATTRVAL_Read_VALUE          "1"
#define ATTRVAL_Read_MEMO           "2"
#define ATTRVAL_Write_OMIT          "0"
#define ATTRVAL_Write_VALUE         "1"
#define ATTRVAL_Write_MEMO          "2"

#define ATTR_NoDataHide				"NoDataHide"
#define ATTRVAL_NoDataHide_TRUE		ATTRVAL_TRUE
#define ATTRVAL_NoDataHide_FALSE	ATTRVAL_FALSE

#define ATTR_IFStyle				"ifstyle"
#define ATTR_IFReport				"ifreport"

#define ATTR_Empty					"empty"
#define ATTRVAL_Empty_TRUE			ATTRVAL_TRUE
#define ATTRVAL_Empty_FALSE			ATTRVAL_FALSE

#define ATTR_EmptyCase				"empty-case"
#define ATTRVAL_EmptyCase_TRUE		ATTRVAL_TRUE
#define ATTRVAL_EmptyCase_FALSE		ATTRVAL_FALSE


#define ATTR_Alias                  "alias"
#define ATTR_CopyAlias              "copy-alias"

#define ATTR_StartPos               "start-pos"
#define ATTR_EndPos                 "end-pos"

#define ATTR_Math					"math"

//默认值是FALSE, 即如果 Rs动态行 没有数据则删除行
#define ATTR_Row_NoDymicData_NoDelete			"RowNoDymicDataNoDelete"
#define ATTRVAL_Row_NoDymicData_NoDelete_TRUE	ATTRVAL_TRUE
#define ATTRVAL_Row_NoDymicData_NoDelete_FALSE	ATTRVAL_FALSE

#define ATTR_SubDataNum				"SubDataNum"

#define ATTR_RsHideReplace_ColNum	"RsHideReplace_ColNum"

#define NODE_Root					"root"
#define NODE_Format					"Format"
#define NODE_Project				"Project"
#define NODE_Report					"Report"
#define NODE_Record					"Record"
#define NODE_Rs						"Rs"

//Excel使用的XML标签

#define NODE_Workbook				"Workbook"
#define NODE_DocumentProperties		"DocumentProperties"
#define NODE_Borders				"Borders"
#define NODE_Border					"Border"
#define NODE_NumberFormat			"NumberFormat"
#define NODE_Protection 			"Protection" 
#define NODE_Interior				"Interior"
#define NODE_Author					"Author"
#define NODE_LastAuthor				"LastAuthor"
#define NODE_LastPrinted			"LastPrinted"
#define NODE_Created				"Created"
#define NODE_LastSaved				"LastSaved"
#define NODE_Company				"Company"
#define NODE_Version				"Version"
#define NODE_ExcelWorkbook			"ExcelWorkbook"
#define NODE_WindowHeight			"WindowHeight"
#define NODE_WindowWidth			"WindowWidth"
#define NODE_WindowTopX				"WindowTopX"
#define NODE_WindowTopY				"WindowTopY"
#define NODE_ProtectStructure		"ProtectStructure"
#define NODE_ProtectWindows			"ProtectWindows"
#define NODE_Comment 				"Comment"

//节点的常数文本值
#define NODETEXT_WindowWidth		"14880"
#define NODETEXT_WindowHeight		"7590"
#define NODETEXT_WindowTopX			"240"
#define NODETEXT_WindowTopY			"45"
#define NODETEXT_Version			"12.00"
#define NODETEXT_ProtectStructure	ATTRVAL_FALSE
#define NODETEXT_ProtectWindows		ATTRVAL_FALSE
#define NODETEXT_Author				"ZhangXin"
#define NODETEXT_Company			"IGen soft Development Co.Ltd"

#define ATTR_Formula				"Formula"

#define ATTR_Type_EXCEL				"Type"
#define ATTR_Name_EXCEL				"Name"
#define ATTR_id_EXCEL               "ID"

#define ATTR_ExpandedColumnCount	"ExpandedColumnCount"
#define ATTR_ExpandedRowCount		"ExpandedRowCount"

#define ATTR_FullColumns			"FullColumns"
#define ATTRVAL_FullColumns_1		"1"

#define ATTR_FullRows				"FullRows"
#define ATTRVAL_FullRows_1			"1"

#define ATTR_Position				"Position"
#define ATTRVAL_Position_Bottom		"Bottom"
#define ATTRVAL_Position_Left		"Left"
#define ATTRVAL_Position_Right		"Right"
#define ATTRVAL_Position_Top		"Top"

#define ATTR_LineStyle							"LineStyle"
#define ATTRVAL_LineStyle_Continuous			"Continuous"

#define ATTR_Weight					"Weight"
#define ATTRVAL_Weight_1			"1"

#define ATTR_Pattern				"Pattern"
#define ATTRVAL_Pattern_Solid		"Solid"

#define ATTR_CharSet				"CharSet"
#define ATTRVAL_CharSet_134			"134"

#define ATTRVAL_Type_String			"String"
#define ATTRVAL_Type_Number			"Number"

#define ATTRVAL_Name_SheetName		"Sheet1"

#define ATTR_Author					"Author"
#define ATTRVAL_Author_ZhangXin		"ZhangXin"

#define ATTR_xmlns							"xmlns"
#define ATTRVAL_xmlns_Workbook 				"urn:schemas-microsoft-com:office:spreadsheet"
#define ATTRVAL_xmlns_Comment  				"http://www.w3.org/TR/REC-html40"
#define ATTRVAL_xmlns_ExcelWorkbook			"urn:schemas-microsoft-com:office:excel"
#define ATTRVAL_xmlns_DocumentProperties 	"urn:schemas-microsoft-com:office:office" 

#define ATTR_xmlns_o				"o"
#define ATTRVAL_xmlns_o_Workbook 	"urn:schemas-microsoft-com:office:office"

#define ATTR_xmlns_x				"x"
#define ATTRVAL_xmlns_x_Workbook 	"urn:schemas-microsoft-com:office:excel"

#define ATTR_xmlns_ss				"ss"
#define ATTRVAL_xmlns_ss_Workbook 	"urn:schemas-microsoft-com:office:spreadsheet"

#define ATTR_xmlns_html				"html"
#define ATTRVAL_xmlns_html_Workbook "http://www.w3.org/TR/REC-html40"

//默认的Style
#define ATTRVAL_Vertical_Default 	"Center"
#define ATTRVAL_Horizontal_Default 	"Left"
#define ATTRVAL_FontName_Default 	"宋体"
#define ATTRVAL_FontSize_Default 	"11"
#define ATTRVAL_CharSet_Default 	"134"
#define ATTRVAL_Color_Default 		"#000000"





#endif 
