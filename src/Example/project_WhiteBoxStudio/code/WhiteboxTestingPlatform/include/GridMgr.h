// GridMgr.h: interface for the CGridMgr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRIDMGR_H__0DA98E1A_85FE_4027_A1E3_E3A7B168B11C__INCLUDED_)
#define AFX_GRIDMGR_H__0DA98E1A_85FE_4027_A1E3_E3A7B168B11C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
using namespace std;

class CCellID;
class CGridCtrl;
class CCellRange;
class CExpressionMgr;
class CLockMgr;
class CIFStyleMgr;
class CRowMove;
class CStyleBrushMgr;

class IFL_EXPORT_CLASS CGridMgr  
{
public:
	CGridMgr();
	virtual ~CGridMgr();

public:
	void SetGridCtrl(CGridCtrl *pGrid);
	CGridCtrl * GetGridCtrl() {return m_pGrid;}

	CExpressionMgr * GetExpressionMgr(){ return m_pExprMgr; }

	//导入XML样式文件到Grid
	BOOL ParaseXMLTplFile(const CString &sXMLTplFileName, BOOL bUpdateMapMode = FALSE);

	//导入XML格式和数据文件到Grid控件
	BOOL ParaseXMLFile(const CString &sXMLStyleFileName, const CString &sXMLDataFileName, const CString &sFormatId, int nDataNo);

	//导出到XML数据文件
	BOOL OutXMLDataFile(const CString &sXMLDataFileName, const CString &sXMLStyleFileName);

	//导出到XML样式文件
	BOOL OutXMLModeFile(const CString &sModeFileName);
	
	//输出到excel文件(xml)
	BOOL ExportToExcel(const CString &sExcelFileName);
	BOOL ExportToExcel();

	//输出到excel文件
	BOOL ExportToExcelByGrid(const CString &sExcelFileName);
	BOOL ExportToExcelByGrid();

	//公式计算的接口函数
	BOOL AutoCal(const CString &sVarName, BOOL bInitCal = FALSE);
	BOOL CalAllMath();
	BOOL InitCalAllMath();

	void ClearExprVarName();
	void ClearVecNamePos();

	//得到单元格的公式
	CString GetCellFormula(int nRowNo, int nColNo);
	void	SetCellFormula(int nRowNo, int nColNo, const CString &sFormula);
	CString GetCellFormula(const CString &sPos);
	void	SetCellFormula(const CString &sPos, const CString &sFormula);

	//从文件中导入公式时使用
	void	SetCellFormula2(const CString &sPos, const CString &sMath);
	void	SetCellFormula2(int nRowNo, int nColNo, const CString &sMath);
	void	SetCellFormula3(const CString &sPos, const CString &sMath);

	void	DeleteFormula(const CString &sPos);

	//得到公式单元格的子类型
	CString GetStatCellSubType(int nRow, int nCol);
	CString GetStatCellSubType(const CString &sName);

	//合并, 取消单元格
	void	MergeCell();
	void	MergeCell(int nMinRow, int nMinCol, int nMaxRow, int nMaxCol);
	void	UnMergeCell();
	void	UnMergeCell(int nMinRow, int nMinCol, int nMaxRow, int nMaxCol);
	void	UnMergeCell(int nRow, int nCol);

	//增加一列
	void	AddColumn();
	BOOL    AddColumn(int nColumn);
	void	AppendColumn();
	BOOL	AppendColumn(int nColumn);
	BOOL	ColumnIsCanInserted();
	BOOL	ColumnIsCanInserted(int nColumn);

	//删除一列或多列
	void	DeleteColumn();
	BOOL	ColumnIsCanDeleted(int nCol);
	BOOL	DeleteColumn(int nColumn);
	BOOL	DeleteColumn(int nMinColumn, int nMaxColumn, int nMinRow);

	//移动多行
	void 	MoveUpRow();
	void	MoveDownRow();
	void	MoveUpRow(int nMinRow, int nMaxRow);
	void	MoveDownRow(int nMinRow, int nMaxRow);
 
	//增加一行
	void	AddRow();
	BOOL	AddRow(int nInsertRow, int nCopyRow = -1);
	void	AppendRow();
	BOOL 	AppendRow(int nInsertRow, int nCopyRow = -1);
	BOOL	InsertNRow(int nInsertRow, int nInsertRowCount = 1, BOOL bCopyFormula = FALSE);
	BOOL	AppendNRow(int nAppendRowCount = 1);
	BOOL	RowIsCanInserted();
	BOOL	RowIsCanInserted(int nRow);
	int		InsertRow(LPCTSTR strHeading, int nInsertRow = -1, int nCopyRow = -1);
	void	UpdateRowCellCombine(int nRow, BOOL bAddRow = TRUE);		//当增加或删除一行时，重新计算所有受影响单元格的合并
	void	SetNewRowCombineAttr(int nNewRow, int nCopyRow);
	void	UpdateRowMath(int nRow, BOOL bAddRow = TRUE);				//当用户插入或删除一行的时候，更新表格的单元格名字和公式
	void	UpdateRowIndex();											//更新行号

	//删除一行
	void	DeleteRow();
	void	SetNewRowAttr(int nNewRow, int nCopyRow);
	BOOL	RowIsCanDeleted(int nRow);
	BOOL	DeleteRow(int nRow);

	//在控件外设置单元格的文本或公式
	void	SetNameWnd(CWnd *pWnd) { m_pNameWnd = pWnd; }
	CWnd *  GetNameWnd() { return m_pNameWnd; }
	void	SetTextWnd(CWnd *pWnd) { m_pTextWnd = pWnd; }
	CWnd *  GetTextWnd() { return m_pTextWnd; }
	void    SetTextEvent(const CString &sText);
	void    SetNameAndText(int nRow, int nCol);
	BOOL	GetCellCombineInfo(const CString &sPos, int *pRowCount, int *pColCount);
	BOOL	GetCellCombineInfo(int nRow, int nCol, int *pRowCount, int *pColCount);
	void	OnButtonCellMouseLeave(const CCellID &cellID);

	//从单元格复制和粘贴数据
	void	OnCopy(const CCellID &idCell);
	void	OnCut(const CCellID &idCell);
	void	OnPaste(const CCellID &idCell);

	//隐藏一行
	void	HideRow(int nRow);
	void	HideRow(const CString &sPos);
	void	HideRow(int nMinRow, int nMaxRow);

	//设置单元格为只读或者取消只读
	void	SetCellReadonly();
	void	SetCellReadonly(int nMinRow, int nMinCol, int nMaxRow, int nMaxCol);

	//设置Rs动态行在没有数据时是否删除，属性放在行的第0列
	void	SetRowNoDymicDataNoDelete();
	void	SetRowNoDymicDataNoDelete(int nRow, BOOL bState);
	void	SetRowNoDymicDataNoDelete(int nMinRow, int nMaxRow, BOOL bState);
	BOOL	RowIsCanNoDymicData_NoDelete(int nRow);

	//设置焦点单元格前景色和背景色
	void	SetCellFkColor();
	void	SetCellFkColor(int nMinRow, int nMinCol, int nMaxRow, int nMaxCol);
	void	SetCellBkColor();
	void	SetCellBkColor(int nMinRow, int nMinCol, int nMaxRow, int nMaxCol);

	//设置单元格格式样式
	void	SetCellAlign(int nAlign);

	//设置单元格的打印格线
	void	SetCellPrintBorder(int nPrintBorder);

	//设置或取消行列的可插入和可删除属性
	void	SetCellIsInsertedAndDeleted(int nAttr);

	//设置单元格字体
	void	SetCellFont();

	//平均行高和列宽
	void	SetRowHeightAvg();
	void	SetColWidthAvg();
	void	SetRowHeightAvg(int nStartRow, int nEndRow);
	void	SetColWidthAvg(int nStartCol, int nEndCol);

	//设置和应用格式刷
	void	SetStyleBrush();
	void	SetStyleBrush(int nMinRow, int nMinCol, int nMaxRow, int nMaxCol);
	void	ApplyStyleBrush();
	BOOL	GetStyleBrush();

	//设置Grid风格
	void	SetGridStyle(int nGridStyle);
	int		GetGridStyle() { return m_nGridStyle; } 
	
	CLockMgr *  GetLockMgr() { return m_pLockMgr; }

	CIFStyleMgr * GetIFStyleMgr() { return m_pIFStyleMgr; } 
	CString GetIFStyle(int nRow, int nCol);

	CRowMove *  GetRowMoveMgr() { return m_pRowMoveMgr; }

	void	SetTitleTip(BOOL bTitleTip) { m_bTitleTip = bTitleTip; }
	BOOL	GetTitleTip() { return m_bTitleTip; }

	//设置单元格区域风格
	void	SetCellTypeDefaut(int nMinRow, int nMinCol, int nMaxRow, int nMaxCol);

	//行列锁定的接口
	BOOL	IsLockRow();
	BOOL	IsLockCol();
	BOOL	LockRow(int nLockRow);
	BOOL	LockCol(int nLockCol);

	//用户可以操作数据行的线，以此来缩小和扩大行列的高度和宽度
	void	EnableDataLineValid(BOOL bDataLineValid = TRUE) { m_bDataLineValid = bDataLineValid; }
	BOOL	GetDataLineValid() { return m_bDataLineValid; }

public:
	//设置标记公式单元格的线框样式
	void	_ClearMathCellLinesRect(int row1, int col1, int row2, int col2);
	void	_ClearMathCellLinesRect(const CString &sStartCell, const CString &sEndCell);

	void	_ClearMathCellLines(int row, int col);
	void	_ClearMathCellLines(const CString &sCell);

	void	_SetMathCellLines(int row, int col, UINT state);
	void	_SetMathCellLines(const CString &sCell, UINT state);

	void	_SetMathCellLinesRect(int row1, int col1, int row2, int col2);
	void	_SetMathCellLinesRect(const CString &sCell, const CString &sEndCell);

	void	_MarkMathCell(int row, int col);
	void	_UnMarkMathCell(int row, int col);

	//单元格编辑后处理公式
	void	_EndEditDealMath(int nRow, int nCol, CString &sText);

	void	_KillFocusAutoCal(int nRow, int nCol);

	//处理直接复制数据到日期单元格
	void	_EndEditDealDatetime(int nRow, int nCol, const CString &sText);

	//从字符串中去掉 "0D0A"
	BOOL	_StrRemove0D0A(CString &sText);

private:
	CString CellMathReCal(const CString &sResPos);
	void	RefreshHideMathMarkRow(const vector<CCellID> &vCell);

	//更新单元格公式
	void	UpdateColumnFormula(int nColumn, int bAddColumn = TRUE);
	void	UpdateRowFormula(int nRow, int bAddRow = TRUE);

	//新增行时 
	BOOL	SetNewRowCellStyle(int nNewRow, int nCopyRow, int nCol);	//复制一行时，设置新行的单元格风格
	BOOL	DealRowSubMath(CString &sExpression, int nNewRowNo,	int nNo, BOOL  bAddRow = TRUE);		//当删除或增加行时，处理对公式子算式(SUM, DIV等)的影响

	//增加列时
	void	SetNewColumnAttr(int nInsertColumn, int nCopyColumn);
	BOOL	SetNewColumnCellStyle(int nNewColumn, int nCopyColumn, int nRow);
    int  	InsertColumn(LPCTSTR strHeading, int nInsertColumn = -1, int nCopyColumn = -1);
	void	SetNewColumnCombineAttr(int nNewColumn, int nCopyColumn);
	void	UpdateColumnCellCombine(int nColumn, BOOL bAddCol = TRUE);
	void	UpdateColumnMath(int nColumn, BOOL bAddCol = TRUE);
	void	UpdateColumnIndex();
	BOOL	DealColumnSubMath(CString &sExpression, int nNewColumnNo, int nNo, BOOL  bAddColumn = TRUE);

private:
	//控件核心功能类
	CGridCtrl	*m_pGrid;				
	
	//公式计算管理类
	CExpressionMgr		*m_pExprMgr;			

	//名字和内容文本框的支持
	CWnd		*m_pNameWnd;
	CWnd		*m_pTextWnd;

	//控件风格    
    //GRIDSTYLE_EXCEL : Excel样式    GRIDSTYLE_NORMAL: 普通样式
	int			m_nGridStyle;	

	//行锁定和列锁定管理类
	CLockMgr	*m_pLockMgr;	

	//条件格式管理类
	CIFStyleMgr	*m_pIFStyleMgr;

	//行移动管理类
	CRowMove	*m_pRowMoveMgr;

	//格式刷管理类
	CStyleBrushMgr *m_pStyleBrushMgr;

	//当单元格中的内容超过边界时，是否有提示框
	BOOL		m_bTitleTip;

	//用户可以操作数据行的线，以此来缩小和扩大行列的高度和宽度
	BOOL		m_bDataLineValid;

};

#endif // !defined(AFX_GRIDMGR_H__0DA98E1A_85FE_4027_A1E3_E3A7B168B11C__INCLUDED_)
