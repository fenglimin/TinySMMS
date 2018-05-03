// TinySMMSDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TinySMMS.h"
#include "TinySMMSDlg.h"
#include "LoginDialog.h"
#include "resource.h"
#include "InsertRowDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

#define WM_MSG_QUERY_PATIENT		(WM_USER +100)
#define WM_MSG_QUERY_STUDY			(WM_USER +101)
#define WM_MSG_QUERY_SERIES			(WM_USER +102)
#define WM_MSG_QUERY_IMAGE			(WM_USER +103)

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTinySMMSDlg dialog

CTinySMMSDlg::CTinySMMSDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTinySMMSDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTinySMMSDlg)
	m_strSQL = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CTinySMMSDlg::~CTinySMMSDlg()
{
	if ( m_pDBConn )
	{
		delete m_pDBConn;
		m_pDBConn = NULL;
	}
}
void CTinySMMSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTinySMMSDlg)
	DDX_Control(pDX, IDC_LIST_TABS, m_listTables);
	DDX_Control(pDX, IDC_LIST_RESULT, m_listResult);
	DDX_Text(pDX, IDC_EDIT_SQL, m_strSQL);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_EDIT_SQL, m_editSQL);
}

BEGIN_MESSAGE_MAP(CTinySMMSDlg, CDialog)
	//{{AFX_MSG_MAP(CTinySMMSDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_RUN, OnButtonRun)
	ON_LBN_DBLCLK(IDC_LIST_TABS, OnDblclkListTabs)
	ON_BN_CLICKED(IDC_BUTTON_PATIENT, OnButtonPatient)
	ON_BN_CLICKED(IDC_BUTTON_STUDY, OnButtonStudy)
	ON_BN_CLICKED(IDC_BUTTON_SERIES, OnButtonSeries)
	ON_BN_CLICKED(IDC_BUTTON_IMAGE, OnButtonImage)
	ON_BN_CLICKED(IDC_BUTTON_SMS, OnButtonSms)
	ON_BN_CLICKED(IDC_BUTTON_WEBREPORT, OnButtonWebreport)
	ON_BN_CLICKED(IDC_BUTTON_CLEARALL, OnButtonClearall)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_POPUP_DELETEALLSELECTEDROW, &CTinySMMSDlg::OnPopupDeleteallselectedrow)
	ON_COMMAND(ID_POPUP_INSERTCOPY32775, &CTinySMMSDlg::OnPopupInsertcopy32775)
	ON_BN_CLICKED(IDC_BUTTON_RELOAD, &CTinySMMSDlg::OnBnClickedButtonReload)
	ON_BN_CLICKED(IDC_BUTTON_USER_PROFILE, &CTinySMMSDlg::OnBnClickedButtonUserProfile)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTinySMMSDlg message handlers

BOOL CTinySMMSDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);
	
	// Set small icon

	CLoginDialog loginDlg;
	if ( loginDlg.DoModal() != IDOK )
	{
		OnCancel();
	}

	m_pDBConn = loginDlg.m_pDBConn;

	m_listResult.SetUser(this);
	m_listResult.SetHeaderHeight(48);
	m_listResult.SetRowHeigt(24);
	m_listResult.AddDefaultRowColor(RGB(207,207,207));
	m_listResult.AddDefaultRowColor(RGB(239,239,239));
//	m_listResult.SetFont(GetFont());


	m_listResult.SetMultipleSelection(TRUE);
	m_listResult.SetShowSelection(TRUE);

	m_listResult.m_defaultListFormat.cellType = cellTextEdit;

	LoadAllTables();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTinySMMSDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTinySMMSDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTinySMMSDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTinySMMSDlg::OnButtonRun() 
{
	int nStartChar, nEndChar;
	m_editSQL.GetSel(nStartChar, nEndChar);
	
	if ( nStartChar == nEndChar )
	{
		AfxMessageBox(_T("Please select a SQL statement!"));
		return;
	}

	UpdateData();
	CString strSQL = m_strSQL.Mid(nStartChar, nEndChar-nStartChar);



	RunSQL(strSQL,TRUE, FALSE);

}

void CTinySMMSDlg::LoadAllTables()
{
	CString strQuery = _T("SELECT     (CASE WHEN a.colorder = 1 THEN d .name ELSE '' END) N'Table Name', a.colorder N'Column SQ', a.name N'Column Name', "
						  "(CASE WHEN COLUMNPROPERTY(a.id, a.name, 'IsIdentity') = 1 THEN '¡Ì' ELSE '' END) N'Idnetity FG', (CASE WHEN"
                          "(SELECT     count(*)"
                           " FROM          sysobjects"
                           " WHERE      (name IN"
                                                       "(SELECT     name"
                                                       "  FROM          sysindexes"
                                                        " WHERE      (id = a.id) AND (indid IN"
                                                                                   " (SELECT     indid"
                                                                                   "   FROM          sysindexkeys"
                                                                                    "  WHERE      (id = a.id) AND (colid IN"
                                                                                                                 "(SELECT     colid"
                                                                                                                  " FROM          syscolumns"
                                                                                                                  " WHERE      (id = a.id) AND (name = a.name))))))) AND (xtype = 'PK')) > 0 THEN '¡Ì' ELSE '' END) N'PK', "
                      " b.name N'Type', a.length N'Bit Length', COLUMNPROPERTY(a.id, a.name, 'PRECISION') AS N'Length', isnull(COLUMNPROPERTY(a.id, a.name, "
                      " 'Scale'), 0) AS N'DataScale', (CASE WHEN a.isnullable = 1 THEN '¡Ì' ELSE '' END) N'Null', isnull(e.text, '') N'Default'"
							" FROM         syscolumns a LEFT JOIN"
											" systypes b ON a.xtype = b.xusertype INNER JOIN"
											" sysobjects d ON a.id = d .id AND d .xtype = 'U' AND d .name <> 'dtproperties' LEFT JOIN"
											" syscomments e ON a.cdefault = e.id"
							" ORDER BY object_name(a.id), a.colorder");
	CADORecordset dbrs(m_pDBConn);
	if(!dbrs.Open((LPCTSTR)strQuery)) 
	{
		//m_pDBConn->Close();
		return;
	}

	m_listTables.ResetContent();
	while (!dbrs.IsEof())
	{
		CString strTable;
		dbrs.GetFieldValue(_T("Table Name"), strTable);
		if ( strTable != "" )
			m_listTables.AddString(strTable);

		dbrs.MoveNext();
	}

	dbrs.Close();
}



void CTinySMMSDlg::OnDblclkListTabs() 
{
	m_listTables.GetText(m_listTables.GetCurSel(), m_strCurrentTable);

	RunSQL("SELECT * FROM " + m_strCurrentTable,TRUE);
	
}

void CTinySMMSDlg::OnButtonPatient() 
{
	m_strCurrentTable = "Patient";
	RunSQL("SELECT * FROM Patient",TRUE);
	
}

void CTinySMMSDlg::OnButtonStudy() 
{
	m_strCurrentTable = "Study";
	RunSQL("SELECT * FROM Study",TRUE);
	
}

void CTinySMMSDlg::OnButtonSeries() 
{
	m_strCurrentTable = "Series";
	RunSQL("SELECT * FROM Series",TRUE);	
}

void CTinySMMSDlg::OnButtonImage() 
{
	m_strCurrentTable = "Image";
	RunSQL("SELECT * FROM Image",TRUE);	
	
}

void CTinySMMSDlg::OnButtonSms() 
{
	m_strCurrentTable = "SystemProfile";
	RunSQL("SELECT * FROM SystemProfile",TRUE);	
	
}

void CTinySMMSDlg::OnButtonWebreport() 
{
	m_strCurrentTable = "RoleProfile";
	RunSQL("SELECT * FROM RoleProfile",TRUE);	
	
}

void CTinySMMSDlg::OnButtonClearall() 
{
	//RunSQL("Delete from Image");	
	//RunSQL("Delete from Series");	
	//RunSQL("Delete from SMS");	
	//RunSQL("Delete from WebReport");	
	//RunSQL("Delete from Study");	
	//RunSQL("Delete from Patient");	

	int i = sizeof(double);
	i = sizeof(float);
	i = 1;

	int aa = m_listResult.GetScrollPos(SB_VERT);

	aa = m_listResult.GetCountPerPage();
}

BOOL CTinySMMSDlg::RunSQL(CString strSQL, BOOL bColumnsChange, BOOL bAddToCommandList)
{
	
	UpdateData();

	if ( bAddToCommandList )
	{
		m_strSQL = strSQL + "\r\n" + m_strSQL;
		UpdateData(FALSE);
	}

	if ( strSQL.Left(6).CompareNoCase("select") == 0 )
	{
		CADORecordset dbrs(m_pDBConn);
		if(!dbrs.Open((LPCTSTR)strSQL)) 
		{
			AfxMessageBox(dbrs.GetLastErrorString());
			return FALSE;
		}
		
		m_listResult.DeleteAllItems();

		
		int nFieldCount = m_listResult.m_ctrlHeader.GetItemCount();
		if ( bColumnsChange )
		{
			while ( m_listResult.DeleteColumn(0) );
			m_listResult.m_ColumnStates.RemoveAll();
			m_listResult.m_ctrlHeader.Invalidate(TRUE);

			CustomColumn		gridColumn;
			CustomColumnList	gridColumnsList;

			nFieldCount = dbrs.GetFieldCount();
			CString strColumnOrder;

			for ( int i = 0; i < nFieldCount; i++)
			{
				CADOFieldInfo fieldInfo;
				dbrs.GetFieldInfo(i, &fieldInfo);

				gridColumn.Reset();

				int nCoumnWidth = 30;
				gridColumn.nFormat = LVCFMT_LEFT;
				switch ( fieldInfo.m_nType)
				{
				case 131:	// numberic
				case 3:		// int
				case 2:		// small int
					nCoumnWidth = 20;
					gridColumn.compareType = compareAsNumber;
					break;
				case 135:	// date
					nCoumnWidth = fieldInfo.m_lSize * 2;
					gridColumn.compareType = compareAsDateTime;
					break;
				case 129:	// char
				case 200:	// varchar
					nCoumnWidth = (int)(fieldInfo.m_lSize * 2.5);
					
				}

				int nTextWidth = GetDC()->GetTextExtent(fieldInfo.m_strName).cx + 15;
				if ( nCoumnWidth < nTextWidth )
					nCoumnWidth = nTextWidth;
				
				
				gridColumn.strHeaderCaption = fieldInfo.m_strName;
				gridColumn.nWidth = nCoumnWidth;
//				gridColumn.ctrlType = cellTextCombo;
				gridColumnsList.push_back(gridColumn);

				CString strOrder;
				strOrder.Format(_T("%d;"), i);
				strColumnOrder += strOrder;
			}

			m_listResult.SetColumnInfo(gridColumnsList, strColumnOrder);
			m_listResult.m_ctrlHeader.SetSortArrow(0, TRUE);
		}

		int nRow = 0;
		while(!dbrs.IsEOF())
		{
			nRow = m_listResult.AppendRow();
			for ( int i = 0; i < nFieldCount; i++)
			{
				CString strText;
				BOOL B = dbrs.GetFieldValue(i, strText, "");
				m_listResult.SetCell(nRow,i, strText);

			}
			dbrs.MoveNext();
			nRow ++;
		}

		dbrs.Close();

		CString strTitle;
		strTitle.Format("TinySMMS - Total %d rows selected!", nRow);
		SetWindowText(strTitle);

		

		return TRUE;
	}
	else
	{
		int nAffect = 0;
		CString strTitle;
		if ( !m_pDBConn->Execute((LPCTSTR)strSQL) )
		{
			strTitle = "SQL error!";
		}
		else
		{
			nAffect = m_pDBConn->GetAffectRecords();
			strTitle.Format("TinySMMS - Total %d rows affected!", nAffect );
		}

		SetWindowText(strTitle);
		return (nAffect!=0);
	}

	
	
}

BOOL CTinySMMSDlg::OnNotify( WPARAM wParam, LPARAM lParam, LRESULT* pResult )
{
	return CDialog::OnNotify(wParam, lParam, pResult);
}

BOOL CTinySMMSDlg::OnCellEditorDisplayed(CListCtrl* pListCtrl, int nRow, int nCol, CellFormat* pCellFormat, CString& strValidChars)
{
	CustomColumn column = m_listResult.m_ctrlHeader.m_gridColumnsList[nCol];
	if ( column.compareType == compareAsNumber )
	{
		strValidChars = _T("0123456789.-");
	}

	return TRUE;
}

BOOL CTinySMMSDlg::OnCellComboDisplayed(CListCtrl* pListCtrl, int nRow, int nCol, CellFormat* pCellFormat, CStringList& strComboItem)
{
	strComboItem.AddTail(_T("1"));
	strComboItem.AddTail(_T("2"));
	strComboItem.AddTail(_T("3"));

	return TRUE;
}

BOOL CTinySMMSDlg::OnFilterTextChanged(CListCtrl* pListCtrl, int nCol, const char* szNewText)
{
	int nColCount = m_listResult.m_ctrlHeader.GetItemCount();
	CString strWhere;
	CString strSelect = "SELECT ";

	for ( int i = 0; i < nColCount; i++)
	{
		CustomColumn column = m_listResult.m_ctrlHeader.m_gridColumnsList[i];
		strSelect += column.strHeaderCaption + ",";

		CString strFilterText = m_listResult.m_ctrlHeader.GetFilterText(i);
		if ( strFilterText == "")
			continue;
		strFilterText.Replace("'", "''");

		if ( column.compareType != compareAsNumber )
		{
			strWhere += column.strHeaderCaption + " LIKE '%" + strFilterText + "%' " + " AND ";
		}
		else
		{
			strWhere += column.strHeaderCaption + " = " + strFilterText + " AND ";
		}
	}

	strSelect = strSelect.Left(strSelect.GetLength()-1);

	CString strSQL = strSelect + " FROM " + m_strCurrentTable;
	if ( strWhere.GetLength() != 0 )
	{
		strSQL += " WHERE " + strWhere.Left(strWhere.GetLength() - 5);
	}

	RunSQL(strSQL,FALSE);

	return TRUE;
}

BOOL CTinySMMSDlg::OnCellTextChanged(CListCtrl* pListCtrl, int nRow, int nCol, CellFormat* pCellFormat, const CString& strOldValue, CString& strNewValue)
{
	CString strWhere = GetWhereStatement(nRow);
	CString strUpdate = _T("UPDATE ") + m_strCurrentTable + _T(" SET ");

	CustomColumn column = m_listResult.m_ctrlHeader.m_gridColumnsList[nCol];
	CString strTemp = strNewValue;
	strTemp.Replace("'", "''");



	if ( column.compareType != compareAsNumber )
	{
		strUpdate += column.strHeaderCaption + " = '" + strTemp + "' ";
	}
	else
	{
		strUpdate += column.strHeaderCaption + " = " + strTemp + " ";
	}

	return RunSQL(strUpdate + strWhere,FALSE);
}

BOOL CTinySMMSDlg::OnCellCtrlClicked(CListCtrl* pListCtrl, int nRow, int nCol, CellFormat* pCellFormat)
{
	if ( nCol == 5 )
	{
		AfxMessageBox("aa");
	}
	return TRUE;
}

BOOL CTinySMMSDlg::OnRowLClicked(CListCtrl* pListCtrl, int nRow, int nCol, UINT nFlags, CPoint point)
{
	return TRUE;
}

BOOL CTinySMMSDlg::OnRowLDblClicked(CListCtrl* pListCtrl, int nRow, int nCol, UINT nFlags, CPoint point)
{
	return TRUE;
}

BOOL CTinySMMSDlg::OnRowRClicked(CListCtrl* pListCtrl, int nRow, int nCol, UINT nFlags, CPoint point)
{
	CCustomListCtrl* pList = (CCustomListCtrl*)pListCtrl;
	m_nClickedRow = nRow;

	CMenu menu;
	m_listResult.ClientToScreen(&point);
	menu.LoadMenu(IDR_MENU1);

	CString strUpTable, strDownTable, strUpTableKeyColumn, strDownTableKeyColumn;
	CString strSqlPatient, strSqlStudy, strSqlSeries, strSqlImage;
	CString strKeyValueDown, strKeyValueUp, strMenuText;
	if ( m_strCurrentTable.CompareNoCase("patient") == 0 )
	{
		strKeyValueDown = GetTextByColumnName(pList, nRow, "PatientGUID");
		strMenuText = GetTextByColumnName(pList, nRow, "PatientID");
		
		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);

		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_STUDY, "Query Study ( PatientID = " + strMenuText + " )");
		strSqlStudy.Format("SELECT * FROM Study WHERE PatientGUID = '%s'", strKeyValueDown );

		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_SERIES, "Query Series ( PatientID = " + strMenuText + " )");
		strSqlSeries.Format("SELECT * FROM Series WHERE StudyInstanceUID IN ( SELECT StudyInstanceUID FROM Study WHERE PatientGUID = '%s')",strKeyValueDown );

		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_IMAGE, "Query Image ( PatientID = " + strMenuText + " )");
		strSqlImage.Format("SELECT * FROM Image WHERE SeriesInstanceUID IN ( SELECT SeriesInstanceUID FROM Series WHERE StudyInstanceUID IN ( SELECT StudyInstanceUID FROM Study WHERE PatientGUID = '%s'))",strKeyValueDown );
	}
	else if ( m_strCurrentTable.CompareNoCase("study") == 0 )
	{
		strKeyValueUp = GetTextByColumnName(pList, nRow, "PatientGUID");
		strKeyValueDown = GetTextByColumnName(pList, nRow, "StudyInstanceUID");
		strMenuText = GetTextByColumnName(pList, nRow, "AccessionNo");

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);

		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_PATIENT, "Query Patient ( AccessionNo = " + strMenuText + " )");
		strSqlPatient.Format("SELECT * FROM Patient WHERE PatientGUID = '%s'", strKeyValueUp );

		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_SERIES, "Query Series ( AccessionNo = " + strMenuText + " )");
		strSqlSeries.Format("SELECT * FROM Series WHERE StudyInstanceUID = '%s'",strKeyValueDown );

		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_IMAGE, "Query Image ( AccessionNo = " + strMenuText + " )");
		strSqlImage.Format("SELECT * FROM Image WHERE SeriesInstanceUID IN ( SELECT SeriesInstanceUID FROM Series WHERE StudyInstanceUID = '%s')",strKeyValueDown );
	}
	else if ( m_strCurrentTable.CompareNoCase("series") == 0 )
	{
		strKeyValueUp = GetTextByColumnName(pList, nRow, "StudyInstanceUID");
		strKeyValueDown = GetTextByColumnName(pList, nRow, "SeriesInstanceUID");
		strMenuText = GetTextByColumnName(pList, nRow, "BodyPart");

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);

		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_PATIENT, "Query Patient ( BodyPart = " + strMenuText + " )");
		strSqlPatient.Format("SELECT * FROM Patient WHERE PatientGUID IN ( SELECT PatientGUID FROM Study WHERE StudyInstanceUID = '%s')", strKeyValueUp );

		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_STUDY, "Query Study ( BodyPart = " + strMenuText + " )");
		strSqlStudy.Format("SELECT * FROM Study WHERE StudyInstanceUID = '%s'",strKeyValueUp );

		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_IMAGE, "Query Image ( BodyPart = " + strMenuText + " )");
		strSqlImage.Format("SELECT * FROM Image WHERE SeriesInstanceUID = '%s'",strKeyValueDown );
	}
	else if ( m_strCurrentTable.CompareNoCase("image") == 0 )
	{
		strKeyValueUp = GetTextByColumnName(pList, nRow, "SeriesInstanceUID");
		strMenuText = GetTextByColumnName(pList, nRow, "ImageNo");

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);

		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_PATIENT, "Query Patient ( ImageNo = " + strMenuText + " )");
		strSqlPatient.Format("SELECT * FROM Patient WHERE PatientGUID IN ( SELECT PatientGUID FROM Study WHERE StudyInstanceUID IN ( SELECT StudyInstanceUID FROM Series WHERE SeriesInstanceUID = '%s'))", strKeyValueUp );

		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_STUDY, "Query Study ( ImageNo = " + strMenuText + " )");
		strSqlStudy.Format("SELECT * FROM Study WHERE StudyInstanceUID IN ( SELECT StudyInstanceUID FROM Series WHERE SeriesInstanceUID = '%s')", strKeyValueUp );

		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_SERIES, "Query Series ( ImageNo = " + strMenuText + " )");
		strSqlSeries.Format("SELECT * FROM Series WHERE SeriesInstanceUID = '%s'",strKeyValueUp );
	}


	CString strSql;	
	int nResult = menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|TPM_RETURNCMD, point.x, point.y, this);
	switch ( nResult)
	{
	//case WM_MSG_QUERY_DOWN:
	//	OnQueryDown()
	case ID_POPUP_DELETEALLSELECTEDROW:
		OnPopupDeleteallselectedrow();
		break;
	case ID_POPUP_INSERTCOPY32775:
		OnPopupInsertcopy32775();
		break;
	case WM_MSG_QUERY_PATIENT:
		RunSQL(strSqlPatient, TRUE);
		m_strCurrentTable = "Patient";
		break;
	case WM_MSG_QUERY_STUDY:
		RunSQL(strSqlStudy, TRUE);
		m_strCurrentTable = "Study";
		break;
	case WM_MSG_QUERY_SERIES:
		RunSQL(strSqlSeries, TRUE);
		m_strCurrentTable = "Series";
		break;
	case WM_MSG_QUERY_IMAGE:
		RunSQL(strSqlImage, TRUE);
		m_strCurrentTable = "Image";
		break;
	}
	return TRUE;
}

void CTinySMMSDlg::OnPopupDeleteallselectedrow()
{
	POSITION pos = m_listResult.GetFirstSelectedItemPosition();
	while ( pos )
	{
		int nRow = m_listResult.GetNextSelectedItem(pos);

		CString strSQL = _T("DELETE ") + m_strCurrentTable + GetWhereStatement(nRow);
		UpdateData(FALSE);
		if ( !RunSQL(strSQL,FALSE) )
		{
			CString strMsg;
			strMsg.Format(_T("Error delete item %d, SQL : %s"), nRow, strSQL );
			AfxMessageBox(strMsg);
			return;
		}
		
		m_listResult.DeleteItem(nRow);
		pos = m_listResult.GetFirstSelectedItemPosition();

	}
	
}

void CTinySMMSDlg::OnPopupInsertcopy32775()
{
	CInsertRowDialog dlg;

	dlg.m_pDataList = &m_listResult;
	dlg.m_nRow = m_nClickedRow;
	dlg.m_strTableName = m_strCurrentTable;
	
	if ( dlg.DoModal() == IDOK )
	{
		UpdateData(FALSE);
		if ( RunSQL(dlg.m_strSQL,FALSE) )
		{
			int nRow = m_listResult.InsertRow(m_nClickedRow);
			for ( int i = 0; i < (int)dlg.m_vecItems.size(); i++)
			{
				m_listResult.SetCell(nRow, i, dlg.m_vecItems[i]);
			}
		}
	}
	
}

CString CTinySMMSDlg::GetWhereStatement(int nRow)
{
	
	int nColCount = m_listResult.m_ctrlHeader.GetItemCount();
	if ( nRow < 0 || nRow >= m_listResult.GetItemCount() )
		return _T("");
	
	CString strWhere;

	for ( int i = 0; i < nColCount; i++)
	{
		CustomColumn column = m_listResult.m_ctrlHeader.m_gridColumnsList[i];
		CString strTemp;

		CString strOldCellValue = m_listResult.GetItemText(nRow,i);
		if ( strOldCellValue.IsEmpty() )
			continue;

		strOldCellValue.Replace("'", "''");

		if ( column.compareType != compareAsNumber )
		{
			strWhere += column.strHeaderCaption + " = '" + strOldCellValue  + "' AND ";
		}
		else
		{
			strWhere += column.strHeaderCaption + " = " + strOldCellValue + " AND ";
		}
	}



	if ( strWhere.GetLength() != 0 )
	{
		strWhere = _T(" WHERE ") + strWhere.Left(strWhere.GetLength() - 5);
	}

	return strWhere;
}

//BOOL IsAutoIncrementField(CString strTableName, CString strFieldName)

void CTinySMMSDlg::OnBnClickedButtonReload()
{
	LoadAllTables();
}


void CTinySMMSDlg::OnBnClickedButtonUserProfile()
{
	m_strCurrentTable = "UserProfile";
	RunSQL("SELECT * FROM UserProfile",TRUE);
}

CString CTinySMMSDlg::GetTextByColumnName( CCustomListCtrl* pList, int nRow, const CString& strColumnName )
{
	HDITEM hdi; 
	char szBuffer[1024];

	hdi.mask = HDI_TEXT | HDI_FORMAT | HDI_IMAGE;
	hdi.pszText = szBuffer;
	hdi.cchTextMax = 1024;

	int nCount = pList->m_ctrlHeader.GetItemCount();
	for ( int i = 0; i < nCount; i ++ )
	{
		pList->m_ctrlHeader.GetItem(i, &hdi);
		if ( strColumnName.CompareNoCase(hdi.pszText) == 0 )
			return pList->GetItemText(nRow, i);
	}

	return "";
}
