// TinySMMSDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TinySMMS.h"
#include "TinySMMSDlg.h"
#include "LoginDialog.h"
#include "resource.h"
#include "InsertRowDialog.h"
#include <algorithm>

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
#define WM_MSG_QUERY_SMS			(WM_USER +104)

#define WM_MSG_DELETE_PATIENT		(WM_USER +114)
#define WM_MSG_DELETE_STUDY			(WM_USER +115)
#define WM_MSG_DELETE_SERIES		(WM_USER +116)
#define WM_MSG_DELETE_IMAGE			(WM_USER +117)

#define WM_MSG_VIEW_PSSI			(WM_USER +118)

#define WM_MSG_OPEN_STUDY_DIR		(WM_USER +119)
#define WM_MSG_OPEN_IMAGE			(WM_USER +120)

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
	DDX_Control(pDX, IDC_LIST_PATIENT, m_listPatient);
	DDX_Control(pDX, IDC_LIST_STUDY, m_listStudy); 
	DDX_Control(pDX, IDC_LIST_SERIES, m_listSeries); 
	DDX_Control(pDX, IDC_LIST_IMAGE, m_listImage); 
	DDX_Control(pDX, IDC_LIST_SMS, m_listSms);
	DDX_Control(pDX, IDC_LIST_MWLORDER, m_listMwlOrder);
	DDX_Control(pDX, IDC_LIST_MWLVIEW, m_listMwlView);
	DDX_Control(pDX, IDC_LIST_USER_PROFILE, m_listUserProfile);
	DDX_Control(pDX, IDC_LIST_ROLE_PROFILE, m_listRoleProfile);
	DDX_Control(pDX, IDC_LIST_SYSTEM_PROFILE, m_listSystemProfile);
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
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_POPUP_DELETEALLSELECTEDROW, &CTinySMMSDlg::OnPopupDeleteallselectedrow)
	ON_COMMAND(ID_POPUP_INSERTCOPY32775, &CTinySMMSDlg::OnPopupInsertcopy32775)
	ON_BN_CLICKED(IDC_BUTTON_RELOAD, &CTinySMMSDlg::OnBnClickedButtonReload)
	ON_BN_CLICKED(IDC_BUTTON_USER_PROFILE, &CTinySMMSDlg::OnBnClickedButtonUserProfile)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_PSSI, &CTinySMMSDlg::OnBnClickedButtonClearPssi)
	ON_BN_CLICKED(IDC_BUTTON_SMS1, &CTinySMMSDlg::OnBnClickedButtonSms1)
	ON_BN_CLICKED(IDC_BUTTON_WMLORDER, &CTinySMMSDlg::OnBnClickedButtonWmlorder)
	ON_BN_CLICKED(IDC_BUTTON_MWLVIEW, &CTinySMMSDlg::OnBnClickedButtonMwlview)
	ON_BN_CLICKED(IDC_BUTTON_ROLE_PROFILE, &CTinySMMSDlg::OnBnClickedButtonRoleProfile)
	ON_BN_CLICKED(IDC_BUTTON_SYSTEM_PROFILE, &CTinySMMSDlg::OnBnClickedButtonSystemProfile)
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

	m_mapTableResult["Patient"] = &m_listPatient;
	m_mapTableResult["Study"] = &m_listStudy; 
	m_mapTableResult["Series"] = &m_listSeries; 
	m_mapTableResult["Image"] = &m_listImage; 
	m_mapTableResult["SMS"] = &m_listSms;
	m_mapTableResult["MwlOrder"] = &m_listMwlOrder;
	m_mapTableResult["MwlView"] = &m_listMwlView;
	m_mapTableResult["UserProfile"] = &m_listUserProfile;
	m_mapTableResult["RoleProfile"] = &m_listRoleProfile;
	m_mapTableResult["SystemProfile"] = &m_listSystemProfile;
	m_mapTableResult["OtherTable"] = &m_listResult;

	for (map<CString, CCustomListCtrl*>::iterator it = m_mapTableResult.begin(); it != m_mapTableResult.end(); it++)
	{
		it->second->SetUser(this);
		it->second->SetHeaderHeight(48);
		it->second->SetRowHeigt(24);
		it->second->AddDefaultRowColor(RGB(207, 207, 207));
		it->second->AddDefaultRowColor(RGB(239, 239, 239));
		it->second->SetMultipleSelection(TRUE);
		it->second->SetShowSelection(TRUE);
		it->second->m_defaultListFormat.cellType = cellTextEdit;

		it->second->ShowWindow(SW_HIDE);
	}

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


	ChangeCurrentTable("Unknown");
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

	vector<CString> vecCommonTables;
	vecCommonTables.push_back("Patient");
	vecCommonTables.push_back("Study");
	vecCommonTables.push_back("Series");
	vecCommonTables.push_back("Image");
	vecCommonTables.push_back("SMS");
	vecCommonTables.push_back("MWLOrder");
	vecCommonTables.push_back("MWLView");
	vecCommonTables.push_back("SystemProfile");
	vecCommonTables.push_back("RoleProfile");
	vecCommonTables.push_back("UserProfile");
	vecCommonTables.push_back("RoleProfile");
	vecCommonTables.push_back("NetAE");
	vecCommonTables.push_back("StorageAE");
	vecCommonTables.push_back("PrintJob");
	vecCommonTables.push_back("RuleJob");
	vecCommonTables.push_back("RuleJobItem");
	vecCommonTables.push_back("TagMapping");
	vecCommonTables.push_back("UserDefinedField");
	vecCommonTables.push_back("------------------------------");

	m_listTables.ResetContent();
	while (!dbrs.IsEof())
	{
		CString strTable;
		dbrs.GetFieldValue(_T("Table Name"), strTable);
		if ( strTable != "" )
		{
			if (std::find(vecCommonTables.begin(), vecCommonTables.end(), strTable) == vecCommonTables.end())
			{
				vecCommonTables.push_back(strTable);
			}
		}

		dbrs.MoveNext();
	}

	dbrs.Close();

	for(int i = 0; i < vecCommonTables.size(); i++)
	{
		m_listTables.AddString(vecCommonTables[i]);
	}
}



void CTinySMMSDlg::OnDblclkListTabs() 
{
	CString strTable;
	m_listTables.GetText(m_listTables.GetCurSel(), strTable);
	if (strTable == "------------------------------")
	{
		return;
	}

	ChangeCurrentTable(strTable);
	RunSQL("SELECT * FROM " + m_strCurrentTable,TRUE);
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
		
		m_pCurrentList->DeleteAllItems();

		
		int nFieldCount = m_pCurrentList->m_ctrlHeader.GetItemCount();
		if ( bColumnsChange )
		{
			while ( m_pCurrentList->DeleteColumn(0) );
			m_pCurrentList->m_ColumnStates.RemoveAll();
			m_pCurrentList->m_ctrlHeader.Invalidate(TRUE);

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

			m_pCurrentList->SetColumnInfo(gridColumnsList, strColumnOrder);
			m_pCurrentList->m_ctrlHeader.SetSortArrow(0, TRUE);
		}

		int nRow = 0;
		while(!dbrs.IsEOF())
		{
			nRow = m_pCurrentList->AppendRow();
			for ( int i = 0; i < nFieldCount; i++)
			{
				CString strText;
				BOOL B = dbrs.GetFieldValue(i, strText, "");
				m_pCurrentList->SetCell(nRow,i, strText);

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
	CustomColumn column = m_pCurrentList->m_ctrlHeader.m_gridColumnsList[nCol];
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
	int nColCount = m_pCurrentList->m_ctrlHeader.GetItemCount();
	CString strWhere;
	CString strSelect = "SELECT ";

	for ( int i = 0; i < nColCount; i++)
	{
		CustomColumn column = m_pCurrentList->m_ctrlHeader.m_gridColumnsList[i];
		strSelect += column.strHeaderCaption + ", ";

		CString strFilterText = m_pCurrentList->m_ctrlHeader.GetFilterText(i);
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

	strSelect = strSelect.Left(strSelect.GetLength()-2);

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

	CustomColumn column = m_pCurrentList->m_ctrlHeader.m_gridColumnsList[nCol];
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
	m_pCurrentList->ClientToScreen(&point);
	menu.LoadMenu(IDR_MENU1);

	CString strUpTable, strDownTable, strUpTableKeyColumn, strDownTableKeyColumn;
	CString strSqlPatient, strSqlStudy, strSqlSeries, strSqlImage;
	CString strKeyValueDown, strKeyValueUp, strMenuText, strDeleteKey;
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

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);
		AddViewPssiMenu(menu.GetSubMenu(0), GetPssiDetail(GetPatientGUID(WM_MSG_QUERY_PATIENT, strKeyValueDown)));

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_DELETE_PATIENT, "Delete Patient ( PatientID = " + strMenuText + " )");
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

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);
		AddViewPssiMenu(menu.GetSubMenu(0), GetPssiDetail(GetPatientGUID(WM_MSG_QUERY_STUDY, strKeyValueDown)));

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_DELETE_STUDY, "Delete Study ( AccessionNo = " + strMenuText + " )");

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);
		menu.GetSubMenu(0)->AppendMenu(MF_STRING | MF_ENABLED, WM_MSG_OPEN_STUDY_DIR, "Open Study Dir( StudyInstanceUID = " + strKeyValueDown + " )");
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

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);
		AddViewPssiMenu(menu.GetSubMenu(0), GetPssiDetail(GetPatientGUID(WM_MSG_QUERY_SERIES, strKeyValueDown)));

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_DELETE_SERIES, "Delete Series ( BodyPart = " + strMenuText + " )");
	}
	else if ( m_strCurrentTable.CompareNoCase("image") == 0 )
	{
		strKeyValueUp = GetTextByColumnName(pList, nRow, "SeriesInstanceUID");
		strMenuText = GetTextByColumnName(pList, nRow, "SOPInstanceUID");
		strKeyValueDown = strMenuText;

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);

		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_PATIENT, "Query Patient ( SOPInstanceUID = " + strMenuText + " )");
		strSqlPatient.Format("SELECT * FROM Patient WHERE PatientGUID IN ( SELECT PatientGUID FROM Study WHERE StudyInstanceUID IN ( SELECT StudyInstanceUID FROM Series WHERE SeriesInstanceUID = '%s'))", strKeyValueUp );

		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_STUDY, "Query Study ( SOPInstanceUID = " + strMenuText + " )");
		strSqlStudy.Format("SELECT * FROM Study WHERE StudyInstanceUID IN ( SELECT StudyInstanceUID FROM Series WHERE SeriesInstanceUID = '%s')", strKeyValueUp );

		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_SERIES, "Query Series ( SOPInstanceUID = " + strMenuText + " )");
		strSqlSeries.Format("SELECT * FROM Series WHERE SeriesInstanceUID = '%s'",strKeyValueUp );

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);
		AddViewPssiMenu(menu.GetSubMenu(0), GetPssiDetail(GetPatientGUID(WM_MSG_QUERY_IMAGE, strKeyValueDown)));

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_DELETE_IMAGE, "Delete Image ( SOPInstanceUID = " + strMenuText + " )");

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);
		menu.GetSubMenu(0)->AppendMenu(MF_STRING | MF_ENABLED, WM_MSG_OPEN_IMAGE, "Open Image ( SOPInstanceUID = " + strMenuText + " )");
	}
	else if ( m_strCurrentTable.CompareNoCase("SMS") == 0 )
	{
		strMenuText = GetTextByColumnName(pList, nRow, "SUID");
		strKeyValueDown = strMenuText;

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);
		AddViewPssiMenu(menu.GetSubMenu(0), GetPssiDetail(GetPatientGUID(WM_MSG_QUERY_SMS, strKeyValueDown)));
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
		ChangeCurrentTable("Patient");
		RunSQL(strSqlPatient, TRUE);
		break;
	case WM_MSG_QUERY_STUDY:
		ChangeCurrentTable("Study");
		RunSQL(strSqlStudy, TRUE);
		break;
	case WM_MSG_QUERY_SERIES:
		ChangeCurrentTable("Series");
		RunSQL(strSqlSeries, TRUE);
		break;
	case WM_MSG_QUERY_IMAGE:
		ChangeCurrentTable("Image");
		RunSQL(strSqlImage, TRUE);
		break;
	case WM_MSG_DELETE_IMAGE:
	case WM_MSG_DELETE_SERIES:
	case WM_MSG_DELETE_STUDY:
	case WM_MSG_DELETE_PATIENT:
		DeletePSSI(nResult, strKeyValueDown);
		m_pCurrentList->DeleteItem(nRow);
		break;
	case WM_MSG_OPEN_STUDY_DIR:
		OpenStudyDir(strKeyValueDown);
		break;
	case WM_MSG_OPEN_IMAGE:
		OpenImage(strKeyValueDown);
		break;
	}
	return TRUE;
}

void CTinySMMSDlg::OnPopupDeleteallselectedrow()
{
	POSITION pos = m_pCurrentList->GetFirstSelectedItemPosition();
	while ( pos )
	{
		int nRow = m_pCurrentList->GetNextSelectedItem(pos);

		CString strSQL = _T("DELETE ") + m_strCurrentTable + GetWhereStatement(nRow);
		UpdateData(FALSE);
		if ( !RunSQL(strSQL,FALSE) )
		{
			CString strMsg;
			strMsg.Format(_T("Error delete item %d, SQL : %s"), nRow, strSQL );
			AfxMessageBox(strMsg);
			return;
		}
		
		m_pCurrentList->DeleteItem(nRow);
		pos = m_pCurrentList->GetFirstSelectedItemPosition();

	}
	
}

void CTinySMMSDlg::OnPopupInsertcopy32775()
{
	CInsertRowDialog dlg;

	dlg.m_pDataList = m_pCurrentList;
	dlg.m_nRow = m_nClickedRow;
	dlg.m_strTableName = m_strCurrentTable;
	
	if ( dlg.DoModal() == IDOK )
	{
		UpdateData(FALSE);
		if ( RunSQL(dlg.m_strSQL,FALSE) )
		{
			int nRow = m_pCurrentList->InsertRow(m_nClickedRow);
			for ( int i = 0; i < (int)dlg.m_vecItems.size(); i++)
			{
				m_pCurrentList->SetCell(nRow, i, dlg.m_vecItems[i]);
			}
		}
	}
	
}

CString CTinySMMSDlg::GetWhereStatement(int nRow)
{
	
	int nColCount = m_pCurrentList->m_ctrlHeader.GetItemCount();
	if ( nRow < 0 || nRow >= m_pCurrentList->GetItemCount() )
		return _T("");
	
	CString strWhere;

	for ( int i = 0; i < nColCount; i++)
	{
		CustomColumn column = m_pCurrentList->m_ctrlHeader.m_gridColumnsList[i];
		CString strTemp;

		CString strOldCellValue = m_pCurrentList->GetItemText(nRow,i);
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


void CTinySMMSDlg::DeletePSSI( int nType, CString strUID )
{
	vector<CString> vecSqlList;

	if (nType == WM_MSG_DELETE_PATIENT)
	{
		vecSqlList.push_back("Delete Image from Image, Series, Study where Image.SeriesInstanceUID = Series.SeriesInstanceUID and Series.StudyInstanceUID = Study.StudyInstanceUID and Study.PatientGUID = '" + strUID + "'");
		vecSqlList.push_back("Delete Series from Series, Study where Series.StudyInstanceUID = Study.StudyInstanceUID and Study.PatientGUID = '" + strUID + "'");
		vecSqlList.push_back("Delete SMS from SMS, Study where SMS.SUID = Study.StudyInstanceUID and Study.PatientGUID = '" + strUID + "'");
		vecSqlList.push_back("Delete MWLView from MWLView, MWLOrder, Study where MWLView.MWLOrderKey = MWLOrder.MWLOrderKey and MWLOrder.StudyInstanceUID = Study.StudyInstanceUID and Study.PatientGUID = '" + strUID + "'");
		vecSqlList.push_back("Delete MWLOrder from MWLOrder, Study where MWLOrder.StudyInstanceUID = Study.StudyInstanceUID and Study.PatientGUID = '" + strUID + "'");
		vecSqlList.push_back("Delete from Study where PatientGUID = '" + strUID + "'");
		vecSqlList.push_back("Delete from Patient where PatientGUID = '" + strUID + "'");
	}
	else if (nType == WM_MSG_DELETE_STUDY)
	{
		vecSqlList.push_back("Delete Image from Image, Series, Study where Image.SeriesInstanceUID = Series.SeriesInstanceUID and Series.StudyInstanceUID = '" + strUID + "'");
		vecSqlList.push_back("Delete Series from Series, Study where Series.StudyInstanceUID = '" + strUID + "'");
		vecSqlList.push_back("Delete SMS from SMS, Study where SMS.SUID = '" + strUID + "'");
		vecSqlList.push_back("Delete MWLView from MWLView, MWLOrder, Study where MWLView.MWLOrderKey = MWLOrder.MWLOrderKey and MWLOrder.StudyInstanceUID = '" + strUID + "'");
		vecSqlList.push_back("Delete from MWLOrder where StudyInstanceUID = '" + strUID + "'");
		vecSqlList.push_back("Delete from Study where StudyInstanceUID = '" + strUID + "'");
	}
	else if (nType == WM_MSG_DELETE_SERIES)
	{
		vecSqlList.push_back("Delete from Image where Image.SeriesInstanceUID = '" + strUID + "'");
		vecSqlList.push_back("Delete from Series where Series.SeriesInstanceUID = '" + strUID + "'");
	}
	else 
	{
		vecSqlList.push_back("Delete from Image where Image.SopInstanceUID = '" + strUID + "'");
	}

	m_pDBConn->RunTransaction(vecSqlList);
}



void CTinySMMSDlg::OnBnClickedButtonClearPssi()
{
	if (AfxMessageBox("Are you sure to clear Pssi?", MB_YESNO) == IDNO)
	{
		return;
	}

	vector<CString> vecSqlList;

	vecSqlList.push_back("Delete from Image");
	vecSqlList.push_back("Delete from Series");
	vecSqlList.push_back("Delete from SMS");
	vecSqlList.push_back("Delete from MWLView");
	vecSqlList.push_back("Delete from MWLOrder");
	vecSqlList.push_back("Delete from Study");
	vecSqlList.push_back("Delete from Patient");

	m_pDBConn->RunTransaction(vecSqlList);
}

CString CTinySMMSDlg::GetPatientGUID( int nIDType, const CString& strUID )
{
	CString strSql;

	m_nViewPssiClickedType = nIDType;
	m_strViewPssiClickeUID = strUID;

	if (nIDType == WM_MSG_QUERY_PATIENT)
	{
		return strUID;	
	}
	else if (nIDType == WM_MSG_QUERY_STUDY || nIDType == WM_MSG_QUERY_SMS)
	{
		strSql = "SELECT Study.PatientGUID from Study where Study.StudyInstanceUID = '" + strUID + "'";
	}
	else if (nIDType == WM_MSG_QUERY_SERIES)
	{
		strSql = "SELECT Study.PatientGUID from Series, Study where Series.StudyInstanceUID = Study.StudyInstanceUID and Series.SeriesInstanceUID = '" + strUID + "'";
	}
	else 
	{
		strSql = "SELECT Study.PatientGUID from Image, Series, Study where Image.SeriesInstanceUID = Series.SeriesInstanceUID and Series.StudyInstanceUID = Study.StudyInstanceUID and Image.SopInstanceUID = '" + strUID + "'";
	}

	CADORecordset dbrs(m_pDBConn);
	if(!dbrs.Open((LPCTSTR)strSql)) 
	{
		AfxMessageBox(dbrs.GetLastErrorString());
		return "";
	}


	CString strPatientGUID;
	if(!dbrs.IsEOF())
	{
		BOOL B = dbrs.GetFieldValue("PatientGUID", strPatientGUID);
	}
	dbrs.Close();

	return strPatientGUID;
}

vector<CString> CTinySMMSDlg::GetPssiDetail( const CString& strPatientGUID )
{
	vector<CString> vecPssi;
	CString strSql;

	strSql = "SELECT PatientName, PatientID FROM Patient WHERE PatientGUID = '" + strPatientGUID + "'";

	CADORecordset dbrs(m_pDBConn);
	if(!dbrs.Open((LPCTSTR)strSql)) 
	{
		AfxMessageBox(dbrs.GetLastErrorString());
		return vecPssi;
	}


	CString strPatientName, strPatientID;
	if(!dbrs.IsEOF())
	{
		dbrs.GetFieldValue("PatientName", strPatientName);
		dbrs.GetFieldValue("PatientID", strPatientID);
	}
	dbrs.Close();

	vecPssi.push_back("Patient - Name : " + strPatientName + ", ID : " + strPatientID);

	//////////////////////////////////////////////////////////////////////////////////////////////
	strSql = "SELECT StudyInstanceUID, StudyDate, StudyTime, AccessionNo, ScanStatus FROM Study WHERE PatientGUID = '" + strPatientGUID + "'";
	if(!dbrs.Open((LPCTSTR)strSql)) 
	{
		AfxMessageBox(dbrs.GetLastErrorString());
		return vecPssi;
	}


	CString strStudyInstnaceUID, strStudyDate, strStudyTime, strAccessionNo;
	int nScanStatus;
	while(!dbrs.IsEOF())
	{
		dbrs.GetFieldValue("StudyInstanceUID", strStudyInstnaceUID);
		dbrs.GetFieldValue("StudyDate", strStudyDate);
		dbrs.GetFieldValue("StudyTime", strStudyTime);
		dbrs.GetFieldValue("AccessionNo", strAccessionNo);
		dbrs.GetFieldValue("ScanStatus", nScanStatus);

		CString strPrefix = "    ";
		if (m_nViewPssiClickedType == WM_MSG_QUERY_STUDY && m_strViewPssiClickeUID == strStudyInstnaceUID)
			strPrefix = "  * ";

		CString strLine;
		strLine.Format("%sStudy - Date : %s, Time : %s, AccessionNo : %s, ScanStatus : %d", strPrefix, strStudyDate, strStudyTime, strAccessionNo, nScanStatus);
		vecPssi.push_back(strLine);
		
		vector<CString> vecSMS = GetSMSDetail(strStudyInstnaceUID);
		for (int i = 0; i < vecSMS.size(); i ++)
		{
			vecPssi.push_back(vecSMS[i]);
		}

		vector<CString> vecSeries = GetSeriesDetail(strStudyInstnaceUID);
		for (int i = 0; i < vecSeries.size(); i ++)
		{
			vecPssi.push_back(vecSeries[i]);
		}

		dbrs.MoveNext();
	}
	dbrs.Close();

	return vecPssi;
}

vector<CString> CTinySMMSDlg::GetSMSDetail( const CString& strStudyInstnaceUID )
{
	vector<CString> vecSMS;
	CString strSql;

	strSql = "SELECT sms_name, sms_type, status, compressed FROM SMS WHERE SUID = '" + strStudyInstnaceUID + "'";

	CADORecordset dbrs(m_pDBConn);
	if(!dbrs.Open((LPCTSTR)strSql)) 
	{
		AfxMessageBox(dbrs.GetLastErrorString());
		return vecSMS;
	}


	CString strSMSName;
	int nType, nStatus, nCompressed;
	while(!dbrs.IsEOF())
	{
		dbrs.GetFieldValue("sms_name", strSMSName);
		dbrs.GetFieldValue("sms_type", nType);
		dbrs.GetFieldValue("status", nStatus);
		dbrs.GetFieldValue("compressed", nCompressed);

		CString strPrefix = "        ";
		if (m_nViewPssiClickedType == WM_MSG_QUERY_SMS && m_strViewPssiClickeUID == strStudyInstnaceUID)
			strPrefix = "      * ";

		CString strLine;
		strLine.Format("%sSMS - Name : %s, Type : %d, Status : %d, Compressed : %d", strPrefix, strSMSName, nType, nStatus, nCompressed);
		vecSMS.push_back(strLine);

		dbrs.MoveNext();
	}
	dbrs.Close();



	return vecSMS;
}

void CTinySMMSDlg::OpenStudyDir(const CString & strStudyUid)
{
	CString strSql;

	strSql = "SELECT S.StudyDir, AE.root_dir FROM Study S, SMS, StorageAE AE WHERE S.StudyInstanceUID = '" + strStudyUid +
		"' AND SMS.SUID = S.StudyInstanceUID AND SMS.sms_type = 1 AND SMS.sms_name = AE.StorageAEName";

	CADORecordset dbrs(m_pDBConn);
	if (!dbrs.Open((LPCTSTR)strSql))
	{
		AfxMessageBox(dbrs.GetLastErrorString());
		return;
	}
	
	CString strStudyDir, strRootDir;
	if (dbrs.IsEOF())
	{
		AfxMessageBox("Can not find study dir in the database");
		dbrs.Close();
		return;
	}
	else
	{
		dbrs.GetFieldValue("StudyDir", strStudyDir);
		dbrs.GetFieldValue("root_dir", strRootDir);
		dbrs.Close();
	}
	
	WinExec("explorer.exe " + strRootDir + "\\" + strStudyDir, SW_SHOW);
}

void CTinySMMSDlg::OpenImage(const CString & strImageSopUid)
{
	CString strSql;

	strSql = "SELECT I.ObjectFile, AE.root_dir FROM Study S, Series SS, Image I, SMS, StorageAE AE WHERE I.SOPInstanceUID = '" + strImageSopUid +
		"' AND I.SeriesInstanceUID = SS.SeriesInstanceUID AND SS.StudyInstanceUID = SMS.SUID AND SMS.sms_type = 1 AND SMS.sms_name = AE.StorageAEName";

	CADORecordset dbrs(m_pDBConn);
	if (!dbrs.Open((LPCTSTR)strSql))
	{
		AfxMessageBox(dbrs.GetLastErrorString());
		return;
	}

	CString strObjectFile, strRootDir;
	if (dbrs.IsEOF())
	{
		AfxMessageBox("Can not find image file in the database");
		dbrs.Close();
		return;
	}
	else
	{
		dbrs.GetFieldValue("ObjectFile", strObjectFile);
		dbrs.GetFieldValue("root_dir", strRootDir);
		dbrs.Close();
	}

	ShellExecute(NULL, _T("Open"), strRootDir + "\\" + strObjectFile, _T(""), strRootDir, SW_SHOW);
}

void CTinySMMSDlg::ChangeCurrentTable(const CString & strTableName)
{
	BOOL bFind = FALSE;
	for (map<CString, CCustomListCtrl*>::iterator it = m_mapTableResult.begin(); it != m_mapTableResult.end(); it++)
	{
		if (it->first.CompareNoCase(strTableName) == 0)
		{
			m_strCurrentTable = strTableName;
			m_pCurrentList = it->second;
			m_pCurrentList->ShowWindow(SW_SHOW);
			bFind = TRUE;
		}
		else
		{
			it->second->ShowWindow(SW_HIDE);
		}
	}

	if (!bFind)
	{
		m_strCurrentTable = strTableName;
		m_pCurrentList = &m_listResult;
		m_pCurrentList->ShowWindow(SW_SHOW);
	}
}

vector<CString> CTinySMMSDlg::GetSeriesDetail( const CString& strStudyInstnaceUID )
{
	vector<CString> vecSeries;
	CString strSql;

	strSql = "SELECT SeriesInstanceUID, BodyPart, ViewPosition, Modality, StationName FROM Series WHERE StudyInstanceUID = '" + strStudyInstnaceUID + "'";

	CADORecordset dbrs(m_pDBConn);
	if(!dbrs.Open((LPCTSTR)strSql)) 
	{
		AfxMessageBox(dbrs.GetLastErrorString());
		return vecSeries;
	}


	CString strSeriesInstanceUID, strBodyPart, strViewPosition, strModality, strStationName;
	while(!dbrs.IsEOF())
	{
		dbrs.GetFieldValue("SeriesInstanceUID", strSeriesInstanceUID);
		dbrs.GetFieldValue("BodyPart", strBodyPart);
		dbrs.GetFieldValue("ViewPosition", strViewPosition);
		dbrs.GetFieldValue("Modality", strModality);
		dbrs.GetFieldValue("StationName", strStationName);

		CString strPrefix = "        ";
		if (m_nViewPssiClickedType == WM_MSG_QUERY_SERIES && m_strViewPssiClickeUID == strSeriesInstanceUID)
			strPrefix = "      * ";

		vecSeries.push_back(strPrefix + "Series - BodyPart : " + strBodyPart + ", ViewPosition : " + strViewPosition + ", Modality : " + strModality + ", StationName : " + strStationName);

		vector<CString> vecImage = GetImageDetail(strSeriesInstanceUID);
		for (int i = 0; i < vecImage.size(); i ++)
		{
			vecSeries.push_back(vecImage[i]);
		}

		dbrs.MoveNext();
	}
	dbrs.Close();



	return vecSeries;
}

void CTinySMMSDlg::AddViewPssiMenu( CMenu* pMenu, vector<CString> vecMenuText )
{
	for (int i = 0; i < vecMenuText.size(); i ++)
	{
		pMenu->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_VIEW_PSSI, vecMenuText[i]);
	}
	
}

vector<CString> CTinySMMSDlg::GetImageDetail( const CString& strSeriesInstanceUID )
{
	vector<CString> vecImage;
	CString strSql;

	strSql = "SELECT SOPInstanceUID, ImageNo, ImageRows, ImageColumns, ObjectFile FROM Image WHERE SeriesInstanceUID = '" + strSeriesInstanceUID + "'";

	CADORecordset dbrs(m_pDBConn);
	if(!dbrs.Open((LPCTSTR)strSql)) 
	{
		AfxMessageBox(dbrs.GetLastErrorString());
		return vecImage;
	}


	CString strSOPInstanceUID, strImageNo, strObjectFile;
	int nImageRows, nImageColumns;
	while(!dbrs.IsEOF())
	{
		dbrs.GetFieldValue("SOPInstanceUID", strSOPInstanceUID);
		dbrs.GetFieldValue("ImageNo", strImageNo);
		dbrs.GetFieldValue("ImageRows", nImageRows);
		dbrs.GetFieldValue("ImageColumns", nImageColumns);
		dbrs.GetFieldValue("ObjectFile", strObjectFile);

		CString strPrefix = "            ";
		if (m_nViewPssiClickedType == WM_MSG_QUERY_IMAGE && m_strViewPssiClickeUID == strSOPInstanceUID)
			strPrefix = "          * ";

		CString strLine;
		strLine.Format(strPrefix + "Image - ImageNo : %s, Width : %d, Height : %d, ObjectFile : %s", strImageNo, nImageColumns, nImageRows, strObjectFile);
		vecImage.push_back(strLine);

		dbrs.MoveNext();
	}
	dbrs.Close();



	return vecImage;
}

void CTinySMMSDlg::OnButtonPatient()
{
	ChangeCurrentTable("Patient");
	if (m_pCurrentList->GetHeaderCtrl()->GetItemCount() == 0)
	{
		RunSQL("SELECT TOP 100 * FROM Patient ORDER BY SerialNo", TRUE);
	}
}

void CTinySMMSDlg::OnButtonStudy()
{
	ChangeCurrentTable("Study");
	if (m_pCurrentList->GetHeaderCtrl()->GetItemCount() == 0)
	{
		RunSQL("SELECT TOP 100 * FROM Study ORDER BY SerialNo", TRUE);
	}
}

void CTinySMMSDlg::OnButtonSeries()
{
	ChangeCurrentTable("Series");
	if (m_pCurrentList->GetHeaderCtrl()->GetItemCount() == 0)
	{
		RunSQL("SELECT TOP 100 * FROM Series ORDER BY SerialNo", TRUE);
	}
}

void CTinySMMSDlg::OnButtonImage()
{
	ChangeCurrentTable("Image");
	if (m_pCurrentList->GetHeaderCtrl()->GetItemCount() == 0)
	{
		RunSQL("SELECT TOP 100 * FROM Image ORDER BY SerialNo", TRUE);
	}
}


void CTinySMMSDlg::OnBnClickedButtonSms1()
{
	ChangeCurrentTable("SMS");
	if (m_pCurrentList->GetHeaderCtrl()->GetItemCount() == 0)
	{
		RunSQL("SELECT TOP 100 * FROM SMS ORDER BY SUID", TRUE);
	}
}


void CTinySMMSDlg::OnBnClickedButtonWmlorder()
{
	ChangeCurrentTable("MWLOrder");
	if (m_pCurrentList->GetHeaderCtrl()->GetItemCount() == 0)
	{
		RunSQL("SELECT TOP 100 * FROM MWLOrder ORDER BY MWLOrderKey", TRUE);
	}
}


void CTinySMMSDlg::OnBnClickedButtonMwlview()
{
	ChangeCurrentTable("MWLView");
	if (m_pCurrentList->GetHeaderCtrl()->GetItemCount() == 0)
	{
		RunSQL("SELECT TOP 100 * FROM MWLView ORDER BY MWLViewKey", TRUE);
	}
}

void CTinySMMSDlg::OnBnClickedButtonUserProfile()
{
	ChangeCurrentTable("UserProfile");
	if (m_pCurrentList->GetHeaderCtrl()->GetItemCount() == 0)
	{
		RunSQL("SELECT TOP 100 * FROM UserProfile", TRUE);
	}
}

void CTinySMMSDlg::OnBnClickedButtonRoleProfile()
{
	ChangeCurrentTable("RoleProfile");
	if (m_pCurrentList->GetHeaderCtrl()->GetItemCount() == 0)
	{
		RunSQL("SELECT TOP 100 * FROM RoleProfile", TRUE);
	}
}

void CTinySMMSDlg::OnBnClickedButtonSystemProfile()
{
	ChangeCurrentTable("SystemProfile");
	if (m_pCurrentList->GetHeaderCtrl()->GetItemCount() == 0)
	{
		RunSQL("SELECT TOP 100 * FROM SystemProfile", TRUE);
	}
}
