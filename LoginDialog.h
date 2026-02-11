#if !defined(AFX_LOGINDIALOG_H__F5ECB3A6_AC22_4875_ABA6_12076F283977__INCLUDED_)
#define AFX_LOGINDIALOG_H__F5ECB3A6_AC22_4875_ABA6_12076F283977__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LoginDialog.h : header file
//


#define PRODUCT_IS		1
#define PRODUCT_IV		2
#define PRODUCT_CT		3
#define PRODUCT_OTHER	4

/////////////////////////////////////////////////////////////////////////////
// CLoginDialog dialog
#include "ado.h"
class CLoginDialog : public CDialog
{
// Construction
public:
	CADODatabase* m_pDBConn;

	int	m_nProductType;
	
	CLoginDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLoginDialog)
	enum { IDD = IDD_DIALOG_LOGIN };
	CComboBox	m_comPassword;
	CString	m_strDatabase;
	CString	m_strServerName;
	CString	m_strUserName;
	CString m_strPassword;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoginDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLoginDialog)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	BOOL DoLogin(BOOL bStopIfFailed);
//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CString m_strProvider;
	void SetProductType(int nProductTypes);
void OnBnClickedRadioIs();
	afx_msg void OnBnClickedRadioIv();
	afx_msg void OnBnClickedRadioCt();
	afx_msg void OnBnClickedRadioOther();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGINDIALOG_H__F5ECB3A6_AC22_4875_ABA6_12076F283977__INCLUDED_)
