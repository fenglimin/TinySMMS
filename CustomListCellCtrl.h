#pragma once


#include "CustomListStruct.h"

///////////////////////////////////////////////////////////////////
// CFilterEdit
///////////////////////////////////////////////////////////////////
class CFilterEdit : public CEdit
{
public:
	BOOL	m_bNotifySent;
	void	SetValidChars(CString& rstrValidChars);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void PostNcDestroy( ); 
	virtual ~CFilterEdit();
	CFilterEdit();		

private:
	CString m_strValidChars;

protected:
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
};




///////////////////////////////////////////////////////////////////
// CFilterCombo
///////////////////////////////////////////////////////////////////
class CFilterCombo : public CComboBox
{
public:		
	BOOL m_bNotifySent;
	BOOL	m_bDropdown;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void PostNcDestroy( ); 
	CFilterCombo();
	virtual ~CFilterCombo();
	// Generated message map functions
protected:
	//{{AFX_MSG(CFilterCombo)
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnCloseup();
	afx_msg void OnSelectChanged();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};



///////////////////////////////////////////////////////////////////
// CFilterInfo
///////////////////////////////////////////////////////////////////
class CFilterInfo
{
public:
	CFilterInfo(){ m_nStatus=FILTER_ENABLED; };
	CString m_strFilter;
	int		m_nStatus;
};