#pragma once

#include <afxtempl.h>
#include "CustomListCellCtrl.h"

class CCustomListCtrlHeader : public CHeaderCtrl
{

	///////////////////////////////////////////////////////////////////
	// Members added by XIAOMING.ZHAO Start from here
	// ---------------------- Start ----------------------
	///////////////////////////////////////////////////////////////////
public:
	CellWindowType GetColumnCtrlType(int nColumn);
	CustomColumnList m_gridColumnsList;
	void		SetColumnsList (CustomColumnList& p_gridColumnsList) { m_gridColumnsList = p_gridColumnsList; };	
	bool		GetComboItemsList(int nColumn, CStringList& clComboItemsList, bool AddAll = true);	
	LRESULT		OnLayout( WPARAM wParam, LPARAM lParam );
	void		EnableFilter( BOOL bEnabled = TRUE );


public:
	afx_msg	void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);


public:
	int			m_Height;		//��ͷ�߶�
	int			m_fontHeight;	//����߶�
	int			m_fontWith;		//������
	COLORREF	m_color;
	CString		m_Format;		//��ʾ�������͵���������,0��ʾ����룬1��ʾ�м���룬2��ʾ�Ҷ���
	CBitmap		m_bmpArrowUp;
	CBitmap		m_bmpArrowDown;
	HBITMAP		m_hPicLoadFailed;
	///////////////////////////////////////////////////////////////////
	// ---------------------- End ----------------------
	// Members added by XIAOMING.ZHAO End from here
	///////////////////////////////////////////////////////////////////


public:	
	void	SetReadOnly(BOOL bRdOnly = FALSE);
	void	SetFilterRect();
	void	SetFilterType();
	void	SetFilterDisabledString(CString strText);
	void	SetFilterStatus(int nIndex, UINT uStatus);
	void	SetFilterText(int nIndex, CString strText);
	CString GetFilterText(int nIndex);
	int		GetFilterStatus(int nIndex);
	int		IndexToOrder(int nIndex);
	BOOL	FilterEditing();
	void	SetFilterFont(CFont* pFont);
	void	CalcFontHeight();
	void	SetSortArrow( const int iColumn, const BOOL bAscending );
	void	SetComboColumns(int iColumnIndex, BOOL bSet = TRUE);
	BOOL	IsCombo(int iColumnIndex);
	void	SetDisableStatus();	
	void	ResetFilter();
	CCustomListCtrlHeader();
	virtual ~CCustomListCtrlHeader();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

	HBITMAP CreateTextBMP(CString strText);


private:	
	BOOL			m_bReadOnly;
	CFilterEdit*	m_pEdit;
	int				m_nEditColumn;
	int				m_nComboColumn;
	int				m_nCurrentWorkingColumn;
	CString			m_strFilterDisabled;
	CPtrArray		m_arFilters;
	CFont			m_FilterFont;
	int				m_nFont1Height;
	int				m_nFont2Height;
	BOOL			m_bEndEditSent;
	BOOL			m_bEnableFilter;
	CList<int, int> m_ComboSupportColumnsList;
	CFilterCombo*	m_pCombo;
		CFilterInfo* GetFilter(int nIndex)	{ return (CFilterInfo*)m_arFilters[nIndex]; }
	void HideEdit(BOOL bValidate);
	void ShowEdit(int nColumn,CString& rStrValidChars);
	void HideCombo(BOOL bValidate);
	void ShowCombo(int nColumn,CStringList& rComboItemsList);
	void HideCheckCombo(BOOL bValidate);
	void ShowCheckCombo(int nColumn,CStringList& rComboItemsList);
	HBITMAP CreateSortBitmap(BOOL bAscending);
	


protected:
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg LRESULT OnEditTextChanged(WPARAM, LPARAM);
	afx_msg LRESULT OnComboSelChanged(WPARAM, LPARAM);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	int		m_iSortColumn;
	BOOL	m_bSortAscending;
	DECLARE_MESSAGE_MAP()
};
