// InsertRowDialog.cpp : implementation file
//

#include "stdafx.h"
#include "TinySMMS.h"
#include "InsertRowDialog.h"


// CInsertRowDialog dialog

IMPLEMENT_DYNAMIC(CInsertRowDialog, CDialog)

CInsertRowDialog::CInsertRowDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CInsertRowDialog::IDD, pParent)
{

}

CInsertRowDialog::~CInsertRowDialog()
{
}

void CInsertRowDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_INSERT, m_listNewRow);
}


BEGIN_MESSAGE_MAP(CInsertRowDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CInsertRowDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CInsertRowDialog message handlers
BOOL CInsertRowDialog::OnInitDialog()
{
	CDialog::OnInitDialog();


	CustomColumn		gridColumn;
	CustomColumnList	gridColumnsList;

	// ID
	gridColumn.Reset();
	gridColumn.strHeaderCaption = _T("Field Name");
	gridColumn.nWidth = 120;
	gridColumnsList.push_back(gridColumn);

	// Exam Date
	gridColumn.Reset();
	gridColumn.strHeaderCaption = _T("Field Value");
	gridColumn.nWidth = 248;
	gridColumnsList.push_back(gridColumn);


	CString strColumnOrder = "0;1";
	m_listNewRow.SetColumnInfo(gridColumnsList, strColumnOrder);

	// Set Row Bk Color
	m_listNewRow.AddDefaultRowColor(RGB(239,239,239));
	m_listNewRow.AddDefaultRowColor(RGB(207,207,207));

	// Height
	m_listNewRow.SetRowHeigt(24);
	m_listNewRow.SetHeaderHeight(24);

	m_listNewRow.EnableFilter(FALSE);
	m_listNewRow.SetMultipleSelection(FALSE);


	int nColCount = m_pDataList->m_ctrlHeader.GetItemCount();

	int nRow;
	CellFormat* pCellFormat;
	for ( int i = 0; i < nColCount; i++)
	{
		CustomColumn column = m_pDataList->m_ctrlHeader.m_gridColumnsList[i];
		CString strTemp;

		nRow = m_listNewRow.AppendRow();
		
		pCellFormat = m_listNewRow.m_defaultListFormat.CopyFormat(levelCell);
		pCellFormat->uTextAlign = DT_RIGHT;
		pCellFormat->lfWeight = FW_BOLD;
		m_listNewRow.SetCell(nRow, 0, column.strHeaderCaption, pCellFormat);


		pCellFormat = m_listNewRow.m_defaultListFormat.CopyFormat(levelCell);
		pCellFormat->cellType = cellTextEdit;

		CString strValue;
		if ( m_nRow == -1 )
			strValue = _T("");
		else
			strValue =  m_pDataList->GetItemText(m_nRow, i);
		m_listNewRow.SetCell(nRow, 1, strValue, pCellFormat);
	}

	m_listNewRow.SetUser(this);

	return TRUE;
}

BOOL CInsertRowDialog::OnCellEditorDisplayed(CListCtrl* pListCtrl, int nRow, int nCol, CellFormat* pCellFormat, CString& strValidChars)
{

	CustomColumn column = m_pDataList->m_ctrlHeader.m_gridColumnsList[nRow];
	if ( column.compareType == compareAsNumber )
	{
		strValidChars = _T("0123456789.-");
	}
	
	//	
	return TRUE;
}

void CInsertRowDialog::OnBnClickedOk()
{
	int nCount = m_listNewRow.GetItemCount();

	CString strFields, strValues;

	for ( int i = 0; i < nCount; i++)
	{
		CString strField = m_listNewRow.GetItemText(i,0);
		CString strValue = m_listNewRow.GetItemText(i,1);

		m_vecItems.push_back(strValue);

		if ( strValue.IsEmpty() )
			continue;
		strValue.Replace("'", "''");

		strFields += strField + _T(", ");

		CustomColumn column = m_pDataList->m_ctrlHeader.m_gridColumnsList[i];
		if ( column.compareType != compareAsNumber )
		{
			strValues += _T("'") + strValue + _T("', ");
		}
		else
		{
			strValues += strValue + _T(", ");
		}
	}


	if ( !strFields.IsEmpty())
	{
		strFields = _T(" ( ") + strFields.Left(strFields.GetLength()-2) + _T(" ) ");
	}

	if ( !strValues.IsEmpty())
	{
		strValues = _T(" VALUES ( ") + strValues.Left(strValues.GetLength()-2) + _T(" ) ");
	}

	m_strSQL = _T("INSERT INTO ") + m_strTableName + strFields + strValues;

	CDialog::OnOK();
}
