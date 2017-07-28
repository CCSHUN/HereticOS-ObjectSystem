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

	//����XML��ʽ�ļ���Grid
	BOOL ParaseXMLTplFile(const CString &sXMLTplFileName, BOOL bUpdateMapMode = FALSE);

	//����XML��ʽ�������ļ���Grid�ؼ�
	BOOL ParaseXMLFile(const CString &sXMLStyleFileName, const CString &sXMLDataFileName, const CString &sFormatId, int nDataNo);

	//������XML�����ļ�
	BOOL OutXMLDataFile(const CString &sXMLDataFileName, const CString &sXMLStyleFileName);

	//������XML��ʽ�ļ�
	BOOL OutXMLModeFile(const CString &sModeFileName);
	
	//�����excel�ļ�(xml)
	BOOL ExportToExcel(const CString &sExcelFileName);
	BOOL ExportToExcel();

	//�����excel�ļ�
	BOOL ExportToExcelByGrid(const CString &sExcelFileName);
	BOOL ExportToExcelByGrid();

	//��ʽ����Ľӿں���
	BOOL AutoCal(const CString &sVarName, BOOL bInitCal = FALSE);
	BOOL CalAllMath();
	BOOL InitCalAllMath();

	void ClearExprVarName();
	void ClearVecNamePos();

	//�õ���Ԫ��Ĺ�ʽ
	CString GetCellFormula(int nRowNo, int nColNo);
	void	SetCellFormula(int nRowNo, int nColNo, const CString &sFormula);
	CString GetCellFormula(const CString &sPos);
	void	SetCellFormula(const CString &sPos, const CString &sFormula);

	//���ļ��е��빫ʽʱʹ��
	void	SetCellFormula2(const CString &sPos, const CString &sMath);
	void	SetCellFormula2(int nRowNo, int nColNo, const CString &sMath);
	void	SetCellFormula3(const CString &sPos, const CString &sMath);

	void	DeleteFormula(const CString &sPos);

	//�õ���ʽ��Ԫ���������
	CString GetStatCellSubType(int nRow, int nCol);
	CString GetStatCellSubType(const CString &sName);

	//�ϲ�, ȡ����Ԫ��
	void	MergeCell();
	void	MergeCell(int nMinRow, int nMinCol, int nMaxRow, int nMaxCol);
	void	UnMergeCell();
	void	UnMergeCell(int nMinRow, int nMinCol, int nMaxRow, int nMaxCol);
	void	UnMergeCell(int nRow, int nCol);

	//����һ��
	void	AddColumn();
	BOOL    AddColumn(int nColumn);
	void	AppendColumn();
	BOOL	AppendColumn(int nColumn);
	BOOL	ColumnIsCanInserted();
	BOOL	ColumnIsCanInserted(int nColumn);

	//ɾ��һ�л����
	void	DeleteColumn();
	BOOL	ColumnIsCanDeleted(int nCol);
	BOOL	DeleteColumn(int nColumn);
	BOOL	DeleteColumn(int nMinColumn, int nMaxColumn, int nMinRow);

	//�ƶ�����
	void 	MoveUpRow();
	void	MoveDownRow();
	void	MoveUpRow(int nMinRow, int nMaxRow);
	void	MoveDownRow(int nMinRow, int nMaxRow);
 
	//����һ��
	void	AddRow();
	BOOL	AddRow(int nInsertRow, int nCopyRow = -1);
	void	AppendRow();
	BOOL 	AppendRow(int nInsertRow, int nCopyRow = -1);
	BOOL	InsertNRow(int nInsertRow, int nInsertRowCount = 1, BOOL bCopyFormula = FALSE);
	BOOL	AppendNRow(int nAppendRowCount = 1);
	BOOL	RowIsCanInserted();
	BOOL	RowIsCanInserted(int nRow);
	int		InsertRow(LPCTSTR strHeading, int nInsertRow = -1, int nCopyRow = -1);
	void	UpdateRowCellCombine(int nRow, BOOL bAddRow = TRUE);		//�����ӻ�ɾ��һ��ʱ�����¼���������Ӱ�쵥Ԫ��ĺϲ�
	void	SetNewRowCombineAttr(int nNewRow, int nCopyRow);
	void	UpdateRowMath(int nRow, BOOL bAddRow = TRUE);				//���û������ɾ��һ�е�ʱ�򣬸��±��ĵ�Ԫ�����ֺ͹�ʽ
	void	UpdateRowIndex();											//�����к�

	//ɾ��һ��
	void	DeleteRow();
	void	SetNewRowAttr(int nNewRow, int nCopyRow);
	BOOL	RowIsCanDeleted(int nRow);
	BOOL	DeleteRow(int nRow);

	//�ڿؼ������õ�Ԫ����ı���ʽ
	void	SetNameWnd(CWnd *pWnd) { m_pNameWnd = pWnd; }
	CWnd *  GetNameWnd() { return m_pNameWnd; }
	void	SetTextWnd(CWnd *pWnd) { m_pTextWnd = pWnd; }
	CWnd *  GetTextWnd() { return m_pTextWnd; }
	void    SetTextEvent(const CString &sText);
	void    SetNameAndText(int nRow, int nCol);
	BOOL	GetCellCombineInfo(const CString &sPos, int *pRowCount, int *pColCount);
	BOOL	GetCellCombineInfo(int nRow, int nCol, int *pRowCount, int *pColCount);
	void	OnButtonCellMouseLeave(const CCellID &cellID);

	//�ӵ�Ԫ���ƺ�ճ������
	void	OnCopy(const CCellID &idCell);
	void	OnCut(const CCellID &idCell);
	void	OnPaste(const CCellID &idCell);

	//����һ��
	void	HideRow(int nRow);
	void	HideRow(const CString &sPos);
	void	HideRow(int nMinRow, int nMaxRow);

	//���õ�Ԫ��Ϊֻ������ȡ��ֻ��
	void	SetCellReadonly();
	void	SetCellReadonly(int nMinRow, int nMinCol, int nMaxRow, int nMaxCol);

	//����Rs��̬����û������ʱ�Ƿ�ɾ�������Է����еĵ�0��
	void	SetRowNoDymicDataNoDelete();
	void	SetRowNoDymicDataNoDelete(int nRow, BOOL bState);
	void	SetRowNoDymicDataNoDelete(int nMinRow, int nMaxRow, BOOL bState);
	BOOL	RowIsCanNoDymicData_NoDelete(int nRow);

	//���ý��㵥Ԫ��ǰ��ɫ�ͱ���ɫ
	void	SetCellFkColor();
	void	SetCellFkColor(int nMinRow, int nMinCol, int nMaxRow, int nMaxCol);
	void	SetCellBkColor();
	void	SetCellBkColor(int nMinRow, int nMinCol, int nMaxRow, int nMaxCol);

	//���õ�Ԫ���ʽ��ʽ
	void	SetCellAlign(int nAlign);

	//���õ�Ԫ��Ĵ�ӡ����
	void	SetCellPrintBorder(int nPrintBorder);

	//���û�ȡ�����еĿɲ���Ϳ�ɾ������
	void	SetCellIsInsertedAndDeleted(int nAttr);

	//���õ�Ԫ������
	void	SetCellFont();

	//ƽ���иߺ��п�
	void	SetRowHeightAvg();
	void	SetColWidthAvg();
	void	SetRowHeightAvg(int nStartRow, int nEndRow);
	void	SetColWidthAvg(int nStartCol, int nEndCol);

	//���ú�Ӧ�ø�ʽˢ
	void	SetStyleBrush();
	void	SetStyleBrush(int nMinRow, int nMinCol, int nMaxRow, int nMaxCol);
	void	ApplyStyleBrush();
	BOOL	GetStyleBrush();

	//����Grid���
	void	SetGridStyle(int nGridStyle);
	int		GetGridStyle() { return m_nGridStyle; } 
	
	CLockMgr *  GetLockMgr() { return m_pLockMgr; }

	CIFStyleMgr * GetIFStyleMgr() { return m_pIFStyleMgr; } 
	CString GetIFStyle(int nRow, int nCol);

	CRowMove *  GetRowMoveMgr() { return m_pRowMoveMgr; }

	void	SetTitleTip(BOOL bTitleTip) { m_bTitleTip = bTitleTip; }
	BOOL	GetTitleTip() { return m_bTitleTip; }

	//���õ�Ԫ��������
	void	SetCellTypeDefaut(int nMinRow, int nMinCol, int nMaxRow, int nMaxCol);

	//���������Ľӿ�
	BOOL	IsLockRow();
	BOOL	IsLockCol();
	BOOL	LockRow(int nLockRow);
	BOOL	LockCol(int nLockCol);

	//�û����Բ��������е��ߣ��Դ�����С���������еĸ߶ȺͿ��
	void	EnableDataLineValid(BOOL bDataLineValid = TRUE) { m_bDataLineValid = bDataLineValid; }
	BOOL	GetDataLineValid() { return m_bDataLineValid; }

public:
	//���ñ�ǹ�ʽ��Ԫ����߿���ʽ
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

	//��Ԫ��༭����ʽ
	void	_EndEditDealMath(int nRow, int nCol, CString &sText);

	void	_KillFocusAutoCal(int nRow, int nCol);

	//����ֱ�Ӹ������ݵ����ڵ�Ԫ��
	void	_EndEditDealDatetime(int nRow, int nCol, const CString &sText);

	//���ַ�����ȥ�� "0D0A"
	BOOL	_StrRemove0D0A(CString &sText);

private:
	CString CellMathReCal(const CString &sResPos);
	void	RefreshHideMathMarkRow(const vector<CCellID> &vCell);

	//���µ�Ԫ��ʽ
	void	UpdateColumnFormula(int nColumn, int bAddColumn = TRUE);
	void	UpdateRowFormula(int nRow, int bAddRow = TRUE);

	//������ʱ 
	BOOL	SetNewRowCellStyle(int nNewRow, int nCopyRow, int nCol);	//����һ��ʱ���������еĵ�Ԫ����
	BOOL	DealRowSubMath(CString &sExpression, int nNewRowNo,	int nNo, BOOL  bAddRow = TRUE);		//��ɾ����������ʱ������Թ�ʽ����ʽ(SUM, DIV��)��Ӱ��

	//������ʱ
	void	SetNewColumnAttr(int nInsertColumn, int nCopyColumn);
	BOOL	SetNewColumnCellStyle(int nNewColumn, int nCopyColumn, int nRow);
    int  	InsertColumn(LPCTSTR strHeading, int nInsertColumn = -1, int nCopyColumn = -1);
	void	SetNewColumnCombineAttr(int nNewColumn, int nCopyColumn);
	void	UpdateColumnCellCombine(int nColumn, BOOL bAddCol = TRUE);
	void	UpdateColumnMath(int nColumn, BOOL bAddCol = TRUE);
	void	UpdateColumnIndex();
	BOOL	DealColumnSubMath(CString &sExpression, int nNewColumnNo, int nNo, BOOL  bAddColumn = TRUE);

private:
	//�ؼ����Ĺ�����
	CGridCtrl	*m_pGrid;				
	
	//��ʽ���������
	CExpressionMgr		*m_pExprMgr;			

	//���ֺ������ı����֧��
	CWnd		*m_pNameWnd;
	CWnd		*m_pTextWnd;

	//�ؼ����    
    //GRIDSTYLE_EXCEL : Excel��ʽ    GRIDSTYLE_NORMAL: ��ͨ��ʽ
	int			m_nGridStyle;	

	//��������������������
	CLockMgr	*m_pLockMgr;	

	//������ʽ������
	CIFStyleMgr	*m_pIFStyleMgr;

	//���ƶ�������
	CRowMove	*m_pRowMoveMgr;

	//��ʽˢ������
	CStyleBrushMgr *m_pStyleBrushMgr;

	//����Ԫ���е����ݳ����߽�ʱ���Ƿ�����ʾ��
	BOOL		m_bTitleTip;

	//�û����Բ��������е��ߣ��Դ�����С���������еĸ߶ȺͿ��
	BOOL		m_bDataLineValid;

};

#endif // !defined(AFX_GRIDMGR_H__0DA98E1A_85FE_4027_A1E3_E3A7B168B11C__INCLUDED_)
