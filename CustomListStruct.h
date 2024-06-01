#pragma once
#include "CustomListConstant.h"
#include <map>
#include <vector>

using namespace std;

enum	CellWindowType
{
	cellUnknown				= 0,
	cellTextReadOnly		= 1,
	cellTextEdit			= 2,
	cellTextCombo			= 3,
	cellCtrlCheckBox		= 4,
	cellCtrlRadioButton		= 5,
	cellCtrlButton			= 6,
	cellCtrlPictureButton	= 7,
	cellPictureBMP			= 8,
	cellPictureICON			= 9,
};

enum ColumnCompareType
{	
	compareAsNumber		= 1,
	compareAsText		= 2,
	compareAsTime		= 3,
	compareAsDate		= 4,
	compareAsDateTime	= 5,
};

enum CellFormatLevel
{
	levelList		= 1,
	levelRow		= 2,
	levelCell		= 3,
};

struct CustomComboboxItem
{
public:
	long lKey;
	CString strText;
	CString	strValue;
};
typedef std::vector<CustomComboboxItem> CustomComboboxItemList;

struct ListCtrlColumnState
{
	ListCtrlColumnState()
		:m_bVisible(false)
		,m_nOrgWidth(0)
		,m_nOrgPosition(-1)
	{}
	bool m_bVisible;
	int  m_nOrgWidth;	// Width it had before being hidden
	int  m_nOrgPosition;	// Position it had before being hidden
};


struct CustomColumn
{
public:
	CString		strHeaderCaption;
	CString		strHeaderFilter;
	BOOL		bVisible;
	int			nWidth;
	int         nFormat;
	CString		strValidChars;
	CellWindowType	ctrlType;
	ColumnCompareType compareType;
	CustomComboboxItemList		dropdownValueList;

	// Constructor
	CustomColumn()
	{
		Reset();
	}
	void Reset()
	{
		compareType = compareAsText;
		strHeaderCaption = "";
		bVisible = TRUE;
		nWidth   = 210;
		strValidChars = "";
		ctrlType = cellTextEdit;
		dropdownValueList.clear();
		nFormat = LVCFMT_CENTER;
	}
};

typedef std::vector<CustomColumn> CustomColumnList;



struct CellFormat
{
	// The level of the format ( Cell/Row/List )
	CellFormatLevel formatLevel;

	// Format for the cell text
	COLORREF		colorCellBackground;
	COLORREF		colorText;
	UINT			uTextAlign;
	LONG			lfWeight;

	// Format the the cell window
	CellWindowType	cellType;
	CString			strCellCtrlText;
	CRect			rcCellCtrl;

	BOOL			bShowText;
	BOOL			bCellTextChange;
	BOOL			bEnabled;
	HANDLE			hPicture;



	CellFormat()
	{
		colorText = RGB(0,0,0);
		colorCellBackground = RGB(255,255,255);
		cellType = cellTextReadOnly;
		uTextAlign = DT_LEFT;
		bCellTextChange = FALSE;
		bEnabled = TRUE;
		bShowText = TRUE;
		formatLevel = levelList;
		hPicture = NULL;
		lfWeight = FW_NORMAL;
	}

	~CellFormat()
	{
		if ( hPicture != NULL )
		{
			DeleteObject(hPicture);
			hPicture = NULL;
		}
	}

	CellFormat* CopyFormat(CellFormatLevel formatLevel)
	{
		CellFormat* pClone = new CellFormat();

		(*pClone) = (*this);
		pClone->formatLevel = formatLevel;

		return pClone;
	}

	BOOL SetPicture(CString strPictureFile)
	{
		if ( strPictureFile.Right(3).CompareNoCase(_T("bmp")) == 0 )
		{
			hPicture = ::LoadImage(::GetModuleHandle(NULL), 
				strPictureFile,IMAGE_BITMAP,0,0, LR_CREATEDIBSECTION|LR_LOADFROMFILE);
		}
		else if ( strPictureFile.Right(3).CompareNoCase(_T("ico")) == 0 )
		{
			hPicture = ::LoadImage(::GetModuleHandle(NULL), 
				strPictureFile,IMAGE_ICON,0,0, LR_CREATEDIBSECTION|LR_LOADFROMFILE);
		}
		else
		{
			return FALSE;
		}

		return TRUE;


	}

	BOOL SetPicture(UINT nIDResource )
	{
		if ( cellType == cellPictureICON )
		{
			hPicture = ::LoadImage(::GetModuleHandle(NULL), 
				MAKEINTRESOURCE(nIDResource),IMAGE_ICON,0,0, LR_CREATEDIBSECTION);
		}
		else
		{
			hPicture = ::LoadImage(::GetModuleHandle(NULL), 
				MAKEINTRESOURCE(nIDResource),IMAGE_BITMAP,0,0, LR_CREATEDIBSECTION);
		}
		

		return  TRUE;

	}
};

struct RowItemData
{
	map<int,CellFormat*>	mapCellFormat;
	map<int,CString>		mapCellText;
	map<CString,CString>	mapAdditionalData;
	CellFormat*				pDefaultRowFormat;
	BOOL					bSelected;

	RowItemData()
	{
		pDefaultRowFormat	= NULL;
		bSelected = FALSE;
	}

	~RowItemData()
	{
		if ( pDefaultRowFormat )
		{
			delete pDefaultRowFormat;
			pDefaultRowFormat = NULL;
		}

		map<int, CellFormat*>::iterator it;
		for (it = mapCellFormat.begin(); it != mapCellFormat.end(); it ++)
		{
			CellFormat* pCellFormat = it->second;
			delete pCellFormat;
		}
		mapCellFormat.clear();
	}

	CellFormat*	FindCellFormat(int nCol, BOOL bUseRowFormatIfNOTFind)
	{
		map<int, CellFormat*>::iterator it = mapCellFormat.find(nCol);
		if ( it == mapCellFormat.end() )
		{
			if ( bUseRowFormatIfNOTFind )
				return pDefaultRowFormat;
			else
				return NULL;
		}
		else
		{
			return it->second;
		}
	}

	void SetCellFormat(int nCol, CellFormat* pCellFormat)
	{
		map<int, CellFormat*>::iterator it = mapCellFormat.find(nCol);
		if ( it != mapCellFormat.end() )
		{
			// The format is set before, delete it first
			CellFormat* pOldFormat = it->second;
			ASSERT(pOldFormat);
			delete pOldFormat;
			mapCellFormat.erase(it);
		}

		// Set it if the given format is NOT NULL
		if ( pCellFormat != NULL )
		{
			ASSERT(pCellFormat->formatLevel == levelCell);
			mapCellFormat[nCol] = pCellFormat;
		}
	}

	void SetCellText(int nCol, CString strText)
	{
		mapCellText[nCol] = strText;
	}

	CString GetCellText(int nCol)
	{
		return mapCellText[nCol];
	}
};

// notify struct
struct NMCUSTOMHDR : public NMHDR
{
	int		nRow;
	int		nCol;
	char*	szNewText;
	char*	szOldText;
};


class ICustomListUser
{
public:
	virtual BOOL OnCellEditorDisplayed(CListCtrl* pListCtrl, int nRow, int nCol, CellFormat* pCellFormat, CString& strValidChars){ return TRUE; };
	virtual BOOL OnCellComboDisplayed(CListCtrl* pListCtrl, int nRow, int nCol, CellFormat* pCellFormat, CStringList& strComboItem){ return TRUE; };
	virtual BOOL OnFilterTextChanged(CListCtrl* pListCtrl, int nCol, const char* szNewText){ return TRUE; };
	virtual BOOL OnCellTextChanged(CListCtrl* pListCtrl, int nRow, int nCol, CellFormat* pCellFormat, const CString& strOldValue, CString& strNewValue){ return TRUE; };
	virtual BOOL OnCellChangeCancelled(CListCtrl* pListCtrl, int nRow, int nCol, CellFormat* pCellFormat, const CString& strOldValue, CString& strNewValue){ return TRUE; };
	virtual BOOL OnCellCtrlClicked(CListCtrl* pListCtrl, int nRow, int nCol, CellFormat* pCellFormat){ return TRUE; };
	virtual BOOL OnRowLClicked(CListCtrl* pListCtrl, int nRow, int nCol, UINT nFlags, CPoint point){ return TRUE; };
	virtual BOOL OnRowLDblClicked(CListCtrl* pListCtrl, int nRow, int nCol, UINT nFlags, CPoint point){ return TRUE; };
	virtual BOOL OnRowRClicked(CListCtrl* pListCtrl, int nRow, int nCol, UINT nFlags, CPoint point){ return TRUE; };
	virtual BOOL OnKeyPressed(CListCtrl* pListCtrl, WPARAM nKeyCode){ return TRUE;};
};