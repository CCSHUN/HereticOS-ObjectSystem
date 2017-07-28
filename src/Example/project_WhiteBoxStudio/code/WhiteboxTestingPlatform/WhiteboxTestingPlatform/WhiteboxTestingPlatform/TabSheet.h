#if !defined(AFX_TABSHEET_H__B25ADB7A_0166_4929_B293_9E3B8EB06C27__INCLUDED_)
#define AFX_TABSHEET_H__B25ADB7A_0166_4929_B293_9E3B8EB06C27__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TabSheet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTabSheet window
#define MAXPAGE 16


class CTabSheet : public CTabCtrl
{
// Construction
public:
	CTabSheet();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL AddPage(LPCTSTR title, CDialog *pDialog,UINT ID);
	int SetCurSelFromID(int nID);
	void SetRect();
	int SetCurSel(int nItem);
	int GetCurSel();
	void Show();
	virtual ~CTabSheet();
	LPCTSTR m_Title[MAXPAGE];
	UINT m_IDD[MAXPAGE];
	CDialog* m_pPages[MAXPAGE];
	int m_nNumOfPages;
	int m_nCurrentPage;
	// Generated message map functions
protected:
	//{{AFX_MSG(CTabSheet)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABSHEET_H__B25ADB7A_0166_4929_B293_9E3B8EB06C27__INCLUDED_)
