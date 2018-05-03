// TinySMMSDlg.h : header file
//

#if !defined(AFX_TINYSMMSDLG_H__32356279_97FD_4104_BBEE_A57C5359C15A__INCLUDED_)
#define AFX_TINYSMMSDLG_H__32356279_97FD_4104_BBEE_A57C5359C15A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTinySMMSDlg dialog
#include "CustomListCtrl.h"

#include "LoginDialog.h"
#include "afxwin.h"
struct Columns
{
	Columns() {};
	CString strTableName;
	CString strColumnName;
	CString strColumnType;
} ;

class CTinySMMSDlg : public CDialog, public ICustomListUser
{
// Construction
public:
	CString	m_strCurrentTable;
	BOOL RunSQL(CString strSQL, BOOL bColumnsChange, BOOL bAddToCommandList=TRUE );
	CString GetWhereStatement(int nRow);
	Columns* m_pAllColumns;
	CADODatabase* m_pDBConn;
	CString	m_strDbConnStr;
	void LoadAllTables();
	CString	GetTextByColumnName(CCustomListCtrl* pList, int nRow, const CString& strColumnName);
	CTinySMMSDlg(CWnd* pParent = NULL);	// standard constructor
	~CTinySMMSDlg();

// Dialog Data
	//{{AFX_DATA(CTinySMMSDlg)
	enum { IDD = IDD_TINYSMMS_DIALOG };
	CListBox	m_listTables;
	CCustomListCtrl	m_listResult;
	CString	m_strSQL;
	int		m_nClickedRow;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTinySMMSDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnNotify( WPARAM wParam, LPARAM lParam, LRESULT* pResult );
	//}}AFX_VIRTUAL

// Implementation
protected:

	
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTinySMMSDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonRun();
	afx_msg void OnDblclkListTabs();
	afx_msg void OnButtonPatient();
	afx_msg void OnButtonStudy();
	afx_msg void OnButtonSeries();
	afx_msg void OnButtonImage();
	afx_msg void OnButtonSms();
	afx_msg void OnButtonWebreport();
	afx_msg void OnButtonClearall();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:

	virtual BOOL OnCellEditorDisplayed(CListCtrl* pListCtrl, int nRow, int nCol, CellFormat* pCellFormat, CString& strValidChars);
	virtual BOOL OnCellComboDisplayed(CListCtrl* pListCtrl, int nRow, int nCol, CellFormat* pCellFormat, CStringList& strComboItem);
	virtual BOOL OnFilterTextChanged(CListCtrl* pListCtrl, int nCol, const char* szNewText);
	virtual BOOL OnCellTextChanged(CListCtrl* pListCtrl, int nRow, int nCol, CellFormat* pCellFormat, const CString& strOldValue, CString& strNewValue);
	virtual BOOL OnCellCtrlClicked(CListCtrl* pListCtrl, int nRow, int nCol, CellFormat* pCellFormat);
	virtual BOOL OnRowLClicked(CListCtrl* pListCtrl, int nRow, int nCol, UINT nFlags, CPoint point);
	virtual BOOL OnRowLDblClicked(CListCtrl* pListCtrl, int nRow, int nCol, UINT nFlags, CPoint point);
	virtual BOOL OnRowRClicked(CListCtrl* pListCtrl, int nRow, int nCol, UINT nFlags, CPoint point);
	afx_msg void OnPopupDeleteallselectedrow();
	afx_msg void OnPopupInsertcopy32775();
	CEdit m_editSQL;
	afx_msg void OnBnClickedButtonReload();
	afx_msg void OnBnClickedButtonUserProfile();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TINYSMMSDLG_H__32356279_97FD_4104_BBEE_A57C5359C15A__INCLUDED_)
