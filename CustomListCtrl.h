#pragma once
#include "CustomListHeaderCtrl.h"

class CCustomListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(CCustomListCtrl)

public:
	CCustomListCtrl();
	virtual ~CCustomListCtrl();

protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual void PreSubclassWindow();
	virtual void PostNcDestroy( ); 
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg BOOL OnDoubleClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg LRESULT OnEditTextChanged(WPARAM, LPARAM);
	afx_msg LRESULT OnComboSelChanged(WPARAM, LPARAM);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnDestroy();
	afx_msg void OnColumnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnPaint();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
public:

	CCustomListCtrlHeader	m_ctrlHeader;
	CSimpleArray<ListCtrlColumnState>	m_ColumnStates;	
	
	CellFormat	m_defaultListFormat;

	int	m_nNumColumns;

	vector<COLORREF>	m_vecRowColors;
	vector<vector<CString>>	m_vecCache;

	CFilterEdit*	m_pEdit;
	CFilterCombo*	m_pCombo;

	BOOL			m_bShowSelection;
	BOOL			m_bEndEditSent;
	BOOL			m_bSortAscending;
	BOOL			m_bCellButtonClicked;
	BOOL			m_bIgnoreMouse;
	BOOL			m_bAllowMultlSelection;
	BOOL			m_bHighlightChangedCellText;
	BOOL			m_bClickSelectedCellToEdit;

	int				m_nEditRow;
	int				m_nEditCol;
	int				m_nSortColumn;
	int				m_nRowHeight;
	int				m_nFontHeight;
	HFONT			m_hCellTextFont;

	ICustomListUser*	m_pUser;

	CString			m_strEmptyMarkupText;
	CPen			m_penHorLine;
	CPen			m_penVerLine;

	CFont			m_FilterFont;

public:
	
	void 		DrawAllBelowEmptyCells(CDC* pDC, CRect rcCell, int nRow, int nBottom);
	void 		DrawCellBackground(CDC* pDC, CRect rcCell, int nRow);
	void 		DrawCellBorder(CDC* pDC, CRect rcCell, BOOL bRightMost = FALSE);
	void 		DrawCellBorder(CDC* pDC, int nRow, int nCol);
	void 		DrawCellText(CDC* pDC, CellFormat* pCellFormat, CString strCellText, CRect rcItem, BOOL bSelected );
	void 		DrawCellText(CDC* pDC, CString strCellText, CRect rcItem, UINT uTextAlign, COLORREF colorText, BOOL bSelected, BOOL bCheckSelection);
	void 		DrawCellCtrl(CDC* pDC, CellFormat* pCellFormat, int nRow, int nCol, CRect rcCtrl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	void 		DrawCellBMP(CDC* pDC, CellFormat* pCellFormat, CRect& rcCtrl, BOOL bSetCtrlRect);
	void 		DrawCellICON(CDC* pDC, CellFormat* pCellFormat, CRect& rcCtrl, BOOL bSetCtrlRect);
	void 		DrawCellButton(CDC* pDC, CellFormat* pCellFormat, BOOL bPushed);
	void 		DrawCellPictureButton(CDC* pDC, CellFormat* pCellFormat, BOOL bPushed);

	
	int			AppendRow(CellFormat* pDefaultRowFormat = NULL);
	int			InsertRow(int nInsertAfter, CellFormat* pDefaultRowFormat = NULL);
	void		SetCell(int nRow, int nCol, CString strCellText, CellFormat* pCellFormat = NULL);
	void		SetCellFormat(int nRow, int nCol, CellFormat* pCellFormat);
	CellFormat*	GetCellFormat(int nRow, int nCol, BOOL bGetForUpdate = FALSE);
	CellFormat* GetRowFormat(int nRow, BOOL bGetForUpdate = FALSE);
	BOOL		SetItemText(int nRow, int nCol, CString strCellText);
	void		SetRowStatus(int nRow, BOOL bEnable, BOOL bRepaint);
	BOOL		ConsistentRowSelection(int nRow);
	void		SetAdditionalRowData(int nRow, CString strKey, CString strData);
	void		SetAdditionalRowData(int nRow, CString strKey, int nData);
	CString		GetAdditionalRowData(int nRow, CString strKey);
	BOOL		SwapRow(int nRow1, int nRow2);

	void		SetClickSelectedCellToEdit(BOOL bClickSelectedCellToEdit) { m_bClickSelectedCellToEdit = bClickSelectedCellToEdit;}
	void		SetHighlightChangedCellText(BOOL bHighlightChangedCellText) { m_bHighlightChangedCellText = bHighlightChangedCellText; }
	void		SetIgnoreMouse(BOOL bIgnoreMouse) { m_bIgnoreMouse = bIgnoreMouse; }
	void		SetUser(ICustomListUser* pUser) { m_pUser = pUser; }
	void		SetShowSelection(BOOL bShowSelectionBackground) { m_bShowSelection = bShowSelectionBackground; }
	void		SetMultipleSelection(BOOL bMultiple);
	void 		SetHeaderHeight(int nHeight) { m_ctrlHeader.m_Height = nHeight; }
	void 		SetRowHeigt(int nHeight);
	void 		SetGridLineColor(COLORREF colorHorLine, COLORREF colorVerLine);
	void 		EnableFilter(BOOL bEnabled) { m_ctrlHeader.EnableFilter(bEnabled);}
	void 		AddDefaultRowColor(COLORREF colorRow) { m_vecRowColors.push_back(colorRow);}
	void		SetFontHeight(int nFontHeight) { m_nFontHeight = nFontHeight; }

	BOOL		DeleteItem( int nItem );
	BOOL		DeleteAllItems();
	void		FreeItemMemory( const int nItem );

	void		SetColumnInfo(CString strColumnInfo, CString strColumnOrder);
	void		SetColumnInfo(CustomColumnList& headerList, CString strColumnOrder);
	void		SetColumnOrder(CString strColumnOrder);
	void		GetColumnInfo(CString &strColumnInfo, CString &strColumnOrder);
	BOOL		SetHeadings( const CString& strHeadings );
	void		InsertColumnState(int nCol, bool bVisible, int nOrgWidth);

	void		FilterValueFromCache(int nCol, CString strFilterValue);

	void		StartCellEdit(int nRow, int nCol, CellFormat* pCellFormat);
	void		ShowEdit(int nRow, int nCol, CString& rStrValidChars);;
	void		HideEdit(BOOL bValidate);
	void 		ShowCombo(int nRow, int nCol,CStringList& rComboItemsList);
	void 		HideCombo(BOOL bValidate);

	void		HitTest(LV_HITTESTINFO&  ht);
	BOOL		CheckClick(int& nRow, int& nCol, CellFormat** pCellFormat);

	void		Sort( int iColumn, BOOL bAscending );
	void		SortPrevious();
	int			NumberCompare( LPCTSTR pszNumber1, LPCTSTR pszNumber2 );
	int			DateCompare( const CString& strDate1, const CString& strDate2, ColumnCompareType iType);
	static int CALLBACK CompareFunction( LPARAM lParam1, LPARAM lParam2, LPARAM lParamData );
	ColumnCompareType IsDateTime( LPCTSTR pszText );

	
};
