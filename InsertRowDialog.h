#pragma once

#include "CustomListCtrl.h"
// CInsertRowDialog dialog

class CInsertRowDialog : public CDialog, public ICustomListUser
{
	DECLARE_DYNAMIC(CInsertRowDialog)

public:
	CInsertRowDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CInsertRowDialog();

	CCustomListCtrl	m_listNewRow;

	CCustomListCtrl*	m_pDataList;
	int					m_nRow;
	CString				m_strTableName;
	CString				m_strSQL;
	vector<CString>		m_vecItems;
	BOOL				m_bForInsert;
	int					m_nProductType;
// Dialog Data
	enum { IDD = IDD_DIALOG_INSERT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();


	DECLARE_MESSAGE_MAP()


public:
	virtual BOOL OnCellEditorDisplayed(CListCtrl* pListCtrl, int nRow, int nCol, CellFormat* pCellFormat, CString& strValidChars);
	virtual BOOL OnCellTextChanged(CListCtrl* pListCtrl, int nRow, int nCol, CellFormat* pCellFormat, const CString& strOldValue, CString& strNewValue);
	afx_msg void OnBnClickedOk();
};
