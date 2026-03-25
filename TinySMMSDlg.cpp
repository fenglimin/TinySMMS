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

#define WM_MSG_QUERY_PATIENT						(WM_USER +100)
#define WM_MSG_QUERY_STUDY							(WM_USER +101)
#define WM_MSG_QUERY_SERIES							(WM_USER +102)
#define WM_MSG_QUERY_IMAGE							(WM_USER +103)
#define WM_MSG_QUERY_SMS							(WM_USER +104)
#define WM_MSG_QUERY_ORDER							(WM_USER +105)
#define WM_MSG_QUERY_VIEW							(WM_USER +106)
#define WM_MSG_QUERY_PROCEDURESTEP					(WM_USER +107)
#define WM_MSG_QUERY_PROTOCOL						(WM_USER +108)
#define WM_MSG_QUERY_SCAN							(WM_USER +109)
#define WM_MSG_QUERY_RECON							(WM_USER +110)
#define WM_MSG_QUERY_SCAN_PRRAM						(WM_USER +111)
#define WM_MSG_QUERY_RECON_PRRAM					(WM_USER +112)

#define WM_MSG_DELETE_PATIENT						(WM_USER +200)
#define WM_MSG_DELETE_STUDY							(WM_USER +201)
#define WM_MSG_DELETE_SERIES						(WM_USER +202)
#define WM_MSG_DELETE_IMAGE							(WM_USER +203)
#define WM_MSG_DELETE_ORDER							(WM_USER +204)
#define WM_MSG_DELETE_VIEW							(WM_USER +205)
#define WM_MSG_DELETE_PROCEDURESTEP					(WM_USER +206)

#define WM_MSG_DELETE_ALL_SELECTED_PATIENT			(WM_USER +300)
#define WM_MSG_DELETE_ALL_SELECTED_STUDY			(WM_USER +301)
#define WM_MSG_DELETE_ALL_SELECTED_SERIES			(WM_USER +302)
#define WM_MSG_DELETE_ALL_SELECTED_IMAGE			(WM_USER +303)
#define WM_MSG_DELETE_ALL_SELECTED_ORDER			(WM_USER +304)
#define WM_MSG_DELETE_ALL_SELECTED_VIEW				(WM_USER +305)
#define WM_MSG_DELETE_ALL_SELECTED_PROCEDURESTEP	(WM_USER +306)

#define WM_MSG_VIEW_PSSI							(WM_USER +400)

#define WM_MSG_OPEN_STUDY_DIR						(WM_USER +500)
#define WM_MSG_OPEN_IMAGE							(WM_USER +501)


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
	
	
	
	DDX_Control(pDX, IDC_BUTTON_PATIENT, m_btnPatient);
	DDX_Control(pDX, IDC_BUTTON_STUDY, m_btnStudy);
	DDX_Control(pDX, IDC_BUTTON_SERIES, m_btnSeries);
	DDX_Control(pDX, IDC_BUTTON_IMAGE, m_btnImage);
	DDX_Control(pDX, IDC_BUTTON_SMS1, m_btnSms);
	DDX_Control(pDX, IDC_BUTTON_WMLORDER, m_btnMwlOrder);
	DDX_Control(pDX, IDC_BUTTON_MWLVIEW, m_btnMwlView);
	DDX_Control(pDX, IDC_BUTTON_USER_PROFILE, m_btnUserProfile);
	DDX_Control(pDX, IDC_BUTTON_ROLE_PROFILE, m_btnRoleProfile);
	DDX_Control(pDX, IDC_BUTTON_SYSTEM_PROFILE, m_btnSystemProfile);

	DDX_Control(pDX, IDC_BUTTON_SYSTEM_INFO, m_btnSysInfo);

	DDX_Control(pDX, IDC_LIST_SYSTEM_INFO, m_listSystemInfo);
	DDX_Control(pDX, IDC_BUTTON_CLEAR_PSSI, m_btnClearPssi);
	DDX_Control(pDX, IDC_BUTTON_RUN, m_btnRunSql);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_EDIT_SQL, m_editSQL);
	DDX_Text(pDX, IDC_EDIT_SQL, m_strSQL);
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
	ON_BN_CLICKED(IDC_BUTTON_SYSTEM_INFO, &CTinySMMSDlg::OnBnClickedButtonSystemInfo)
	ON_WM_SIZE()
	ON_BN_DOUBLECLICKED(IDC_BUTTON_PATIENT, &CTinySMMSDlg::OnBnDoubleclickedButtonPatient)
	ON_BN_DOUBLECLICKED(IDC_BUTTON_STUDY, &CTinySMMSDlg::OnBnDoubleclickedButtonStudy)
	ON_BN_DOUBLECLICKED(IDC_BUTTON_SERIES, &CTinySMMSDlg::OnBnDoubleclickedButtonSeries)
	ON_BN_DOUBLECLICKED(IDC_BUTTON_IMAGE, &CTinySMMSDlg::OnBnDoubleclickedButtonImage)
	ON_BN_DOUBLECLICKED(IDC_BUTTON_SMS1, &CTinySMMSDlg::OnBnDoubleclickedButtonSms1)
	ON_BN_DOUBLECLICKED(IDC_BUTTON_WMLORDER, &CTinySMMSDlg::OnBnDoubleclickedButtonWmlorder)
	ON_BN_DOUBLECLICKED(IDC_BUTTON_MWLVIEW, &CTinySMMSDlg::OnBnDoubleclickedButtonMwlview)
	ON_BN_DOUBLECLICKED(IDC_BUTTON_USER_PROFILE, &CTinySMMSDlg::OnBnDoubleclickedButtonUserProfile)
	ON_BN_DOUBLECLICKED(IDC_BUTTON_ROLE_PROFILE, &CTinySMMSDlg::OnBnDoubleclickedButtonRoleProfile)
	ON_BN_DOUBLECLICKED(IDC_BUTTON_SYSTEM_PROFILE, &CTinySMMSDlg::OnBnDoubleclickedButtonSystemProfile)
	ON_BN_DOUBLECLICKED(IDC_BUTTON_SYSTEM_INFO, &CTinySMMSDlg::OnBnDoubleclickedButtonSystemInfo)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTinySMMSDlg message handlers

BOOL CTinySMMSDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_F5)
	{
		//CWnd* pWnd = dynamic_cast<CEdit*>(GetFocus());
		if (GetFocus()->m_hWnd == m_editSQL.m_hWnd)
		{
			OnButtonRun();
		}
		return TRUE;
	}

	return __super::PreTranslateMessage(pMsg);
}

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
	m_pDBConn = NULL;
	
	CLoginDialog loginDlg;
	if ( loginDlg.DoModal() != IDOK )
	{
		OnCancel();
		return FALSE;
	}

	m_pDBConn = loginDlg.m_pDBConn;
	m_nProductType = loginDlg.m_nProductType;

	if (m_nProductType != PRODUCT_IS)
	{
		m_vecCommonTables.push_back("Patient");
		m_vecCommonTables.push_back("Study");		
	}
	
	if (m_nProductType == PRODUCT_IS)
	{
		m_vecCommonTables.push_back("Series");
		m_vecCommonTables.push_back("Image");
		m_vecCommonTables.push_back("SMS");
		m_vecCommonTables.push_back("MWLOrder");
		m_vecCommonTables.push_back("MWLView");
		m_vecCommonTables.push_back("SystemProfile");
		m_vecCommonTables.push_back("RoleProfile");
		m_vecCommonTables.push_back("UserProfile");
		m_vecCommonTables.push_back("NetAE");
		m_vecCommonTables.push_back("StorageAE");
		m_vecCommonTables.push_back("PrintJob");
		m_vecCommonTables.push_back("RuleJob");
		m_vecCommonTables.push_back("RuleJobItem");
		m_vecCommonTables.push_back("TagMapping");
		m_vecCommonTables.push_back("UserDefinedField");		
	}
	else if (m_nProductType == PRODUCT_IV)
	{
		m_vecCommonTables.push_back("ProcedureStep");
		m_vecCommonTables.push_back("Series");
		m_vecCommonTables.push_back("CaptureImage");
	}
	else if (m_nProductType == PRODUCT_CT)
	{
		m_vecCommonTables.push_back("ProcedureStep");
		m_vecCommonTables.push_back("Series");
		m_vecCommonTables.push_back("CaptureImage");
		m_vecCommonTables.push_back("ProtocolTemplate");
		m_vecCommonTables.push_back("ScanTemplate");
		m_vecCommonTables.push_back("ReconTemplate");
		m_vecCommonTables.push_back("ScanParamTemplate");
		m_vecCommonTables.push_back("ReconParamTemplate");
		m_vecCommonTables.push_back("ScanExecution");
		m_vecCommonTables.push_back("CtParameterConfig");
	}

	if (m_nProductType != PRODUCT_OTHER)
	{
		m_vecCommonTables.push_back("------------------------------");
		
		m_mapTableResult["Patient"] = &m_listPatient;
		m_mapTableResult["Study"] = &m_listStudy; 
		m_mapTableResult["Series"] = &m_listSeries;
	}

	if (m_nProductType == PRODUCT_IS)
	{
		m_mapTableResult["Image"] = &m_listImage; 
		m_mapTableResult["MwlOrder"] = &m_listMwlOrder;
		m_mapTableResult["MwlView"] = &m_listMwlView;
		m_mapTableResult["SMS"] = &m_listSms;
		m_mapTableResult["UserProfile"] = &m_listUserProfile;
		m_mapTableResult["RoleProfile"] = &m_listRoleProfile;
		m_mapTableResult["SystemProfile"] = &m_listSystemProfile;		
	}
	else if (m_nProductType == PRODUCT_IV)
	{
		m_mapTableResult["CaptureImage"] = &m_listImage;
		m_mapTableResult["ProcedureStep"] = &m_listSms;
		SetDlgItemText(IDC_BUTTON_SMS1, "ProcStep");

		m_mapTableResult["MwlOrder"] = &m_listMwlOrder;
		GetDlgItem(IDC_BUTTON_WMLORDER)->ShowWindow(SW_HIDE);

		m_mapTableResult["MwlView"] = &m_listMwlView;
		GetDlgItem(IDC_BUTTON_MWLVIEW)->ShowWindow(SW_HIDE);

		m_mapTableResult["UserProfile"] = &m_listUserProfile;
		GetDlgItem(IDC_BUTTON_USER_PROFILE)->ShowWindow(SW_HIDE);

		m_mapTableResult["RoleProfile"] = &m_listRoleProfile;
		GetDlgItem(IDC_BUTTON_ROLE_PROFILE)->ShowWindow(SW_HIDE);

		m_mapTableResult["SystemProfile"] = &m_listSystemProfile;
		GetDlgItem(IDC_BUTTON_SYSTEM_PROFILE)->ShowWindow(SW_HIDE);
	}
	else if (m_nProductType == PRODUCT_CT)
	{
		m_mapTableResult["CaptureImage"] = &m_listImage;
		m_mapTableResult["ProcedureStep"] = &m_listSms;
		SetDlgItemText(IDC_BUTTON_SMS1, "ProcStep");

		m_mapTableResult["ProtocolTemplate"] = &m_listMwlOrder;
		SetDlgItemText(IDC_BUTTON_WMLORDER, "Protocol");

		m_mapTableResult["ScanTemplate"] = &m_listMwlView;
		SetDlgItemText(IDC_BUTTON_MWLVIEW, "Scan");

		m_mapTableResult["ReconTemplate"] = &m_listUserProfile;
		SetDlgItemText(IDC_BUTTON_USER_PROFILE, "Recon");
		
		m_mapTableResult["ScanParamTemplate"] = &m_listRoleProfile;
		SetDlgItemText(IDC_BUTTON_ROLE_PROFILE, "ScanPara");

		m_mapTableResult["ReconParamTemplate"] = &m_listSystemProfile;
		SetDlgItemText(IDC_BUTTON_SYSTEM_PROFILE, "ReconPara");
	}

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

		it->second->SetExtendedStyle(it->second->GetExtendedStyle() | LVS_EX_DOUBLEBUFFER);
		it->second->ShowWindow(SW_HIDE);
	}

	LoadAllTables();
	
	InitSystemInfoTable();

	m_pActiveButton = NULL;
	LoadSystemInfo();
	CreateMapForButton();
	SetActiveButton(&m_btnSysInfo);

	if (m_nProductType == PRODUCT_IV || m_nProductType == PRODUCT_CT)
	{
		SwitchButtonLocation(IDC_BUTTON_SMS1, IDC_BUTTON_SERIES);
		SwitchButtonLocation(IDC_BUTTON_IMAGE, IDC_BUTTON_SERIES);
	}

	GetClientRect(&m_rectClient);
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
	
	CString strSqlToRun;
	if ( nStartChar == nEndChar )
	{
		CString strSql = m_strSQL;
		vector<CString> vecSqlList;
		while(TRUE)
		{
			int nIndex = strSql.Find("\r\n");
			if (nIndex == -1)
			{
				break;
			}
			vecSqlList.push_back(strSql.Left(nIndex));
			strSql = strSql.Right(strSql.GetLength() - nIndex - 2);
		}
		
		int nRealStart = 0;
		for(int i = 0; i < vecSqlList.size(); i++)
		{
			nRealStart += vecSqlList[i].GetLength() + 2;
			if (nRealStart >= nStartChar )
			{
				strSqlToRun = vecSqlList[i];
				 break;
			}
		}		
	}
	else
	{
		strSqlToRun = m_strSQL.Mid(nStartChar, nEndChar-nStartChar);
	}

	UpdateData();
	ChangeCurrentTable("Unknown");
	RunSQL(strSqlToRun,TRUE, FALSE);

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

	
	vector<CString> vecOtherTables;

	m_listTables.ResetContent();
	while (!dbrs.IsEof())
	{
		CString strTable;
		dbrs.GetFieldValue(_T("Table Name"), strTable);
		if ( strTable != "" )
		{
			if (std::find(m_vecCommonTables.begin(), m_vecCommonTables.end(), strTable) == m_vecCommonTables.end())
			{
				vecOtherTables.push_back(strTable);
			}
		}

		dbrs.MoveNext();
	}

	dbrs.Close();

	for(int i = 0; i < m_vecCommonTables.size(); i++)
	{
		m_listTables.AddString(m_vecCommonTables[i]);
	}

	for(int i = 0; i < vecOtherTables.size(); i++)
	{
		m_listTables.AddString(vecOtherTables[i]);
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
	RunSQL("SELECT * FROM [" + m_strCurrentTable + "]",TRUE);
}

BOOL CTinySMMSDlg::RunSQL(CString strSQL, BOOL bColumnsChange, BOOL bAddToCommandList)
{
	
	UpdateData();

	if ( bAddToCommandList )
	{
		m_strSQL = strSQL + "\r\n" + m_strSQL;
		UpdateData(FALSE);
	}

	CString strTableName;
	if ( strSQL.Left(6).CompareNoCase("select") == 0 )
	{
		int nIndex = strSQL.MakeUpper().Find("FROM ");
		if (nIndex != -1)
		{
			strTableName = strSQL.Right(strSQL.GetLength() - nIndex - 4);
			strTableName.TrimLeft();
			strTableName.Replace("\t", " ");
			nIndex = strTableName.Find(" ");
			if (nIndex != -1)
			{
				strTableName = strTableName.Left(nIndex);
			}

			if (strTableName.GetAt(0) == '[' && strTableName.GetAt(strTableName.GetLength()-1) == ']')
			{
				strTableName = strTableName.Mid(1, strTableName.GetLength()-2);
			}
			ChangeCurrentTable(strTableName);
		}
		else
		{
			AfxMessageBox("Cannot get table name from sql string");
		}

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
					break;
				case 72:	// ID
					nCoumnWidth = 300;
					break;	
				default:
					nCoumnWidth = 300;
				}

				int nTextWidth = GetDC()->GetTextExtent(fieldInfo.m_strName).cx + 10;
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

			strColumnOrder = ReorderColumn(strTableName, strColumnOrder);
			m_pCurrentList->SetColumnInfo(gridColumnsList, strColumnOrder);
			m_pCurrentList->m_ctrlHeader.SetSortArrow(0, FALSE);
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
		
		AutoFitWidth();		

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

	if (m_nProductType == PRODUCT_IS || m_nProductType == PRODUCT_OTHER)
	{
		CString strWhere = GetWhereStatement(nRow);
		if(!RunSQL(strUpdate + strWhere,FALSE))
		{
			CString strNewWhere = GetWhereStatement(nRow, TRUE);
			if (AfxMessageBox("Cannot update table using condition " + strWhere + "\r\n\r\nDo you want to using condition " + strNewWhere + " to update table?", MB_YESNO) == IDNO)
			{
				return FALSE;
			}
			return RunSQL(strUpdate + strNewWhere,FALSE);
		}	
	}
	else
	{
		CString strWhere = GetWhereStatement(nRow, TRUE);
		return RunSQL(strUpdate + strWhere,FALSE);
	}	

	return TRUE;
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
	if (pListCtrl == &m_listSystemInfo)
		return TRUE;

	CInsertRowDialog dlg;

	dlg.m_pDataList = m_pCurrentList;
	dlg.m_nRow = nRow;
	dlg.m_strTableName = m_strCurrentTable;
	dlg.m_bViewOnly = TRUE;
	dlg.m_nProductType = m_nProductType;

	dlg.DoModal();

	return TRUE;
}

BOOL CTinySMMSDlg::OnRowRClicked(CListCtrl* pListCtrl, int nRow, int nCol, UINT nFlags, CPoint point)
{
	if (nRow == -1)
		return TRUE;

	if (m_nProductType == PRODUCT_IS)
		OnIsContextMenu(pListCtrl, nRow, nCol, nFlags, point);
	else if (m_nProductType == PRODUCT_CT)
		OnCtContextMenu(pListCtrl, nRow, nCol, nFlags, point);

	return TRUE;
}

void CTinySMMSDlg::OnCtContextMenu( CListCtrl* pListCtrl, int nRow, int nCol, UINT nFlags, CPoint point )
{
	CCustomListCtrl* pList = (CCustomListCtrl*)pListCtrl;
	m_nClickedRow = nRow;

	CMenu menu;
	m_pCurrentList->ClientToScreen(&point);
	menu.LoadMenu(IDR_MENU1);

	CString strUpTable, strDownTable, strUpTableKeyColumn, strDownTableKeyColumn;
	CString strSqlPatient, strSqlStudy, strSqlProcedureStep, strSqlSeries, strSqlImage, strSqlProtocolTemplate, strSqlScanTemplate, strSqlReconTemplate, strSqlScanParamTemplate, strSqlReconParamTemplate;
	CString strKeyValueDown, strKeyValueUp, strMenuText, strDeleteKey;
	if ( m_strCurrentTable.CompareNoCase("patient") == 0 )
	{
		strKeyValueDown = GetTextByColumnName(pList, nRow, "Id");
		strMenuText = GetTextByColumnName(pList, nRow, "DicomPatientId");

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_STUDY, "Query Study ( PatientID = " + strMenuText + " )");
		strSqlStudy.Format("SELECT * FROM Study WHERE PatientId = '%s'", strKeyValueDown );
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_PROCEDURESTEP, "Query ProcedureStep ( PatientID = " + strMenuText + " )");
		strSqlProcedureStep.Format("SELECT * FROM ProcedureStep WHERE StudyId IN ( SELECT Id FROM Study WHERE PatientId = '%s')", strKeyValueDown );
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_SERIES, "Query Series ( PatientID = " + strMenuText + " )");
		strSqlSeries.Format("SELECT * FROM Series WHERE ProcedureStepId IN ( SELECT Id FROM ProcedureStep WHERE StudyId IN ( SELECT Id FROM Study WHERE PatientId = '%s'))",strKeyValueDown );
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_IMAGE, "Query Image ( PatientID = " + strMenuText + " )");
		strSqlImage.Format("SELECT * FROM CaptureImage WHERE SeriesId IN ( SELECT Id FROM Series WHERE ProcedureStepId IN ( SELECT Id FROM ProcedureStep WHERE StudyId IN ( SELECT Id FROM Study WHERE PatientId = '%s')))",strKeyValueDown );

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_DELETE_PATIENT, "Delete Patient ( PatientID = " + strMenuText + " )");
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_DELETE_ALL_SELECTED_PATIENT, "Delete All Selected Patients");

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);
		AddMenuList(menu.GetSubMenu(0), GetCtPssiDetail(GetCtPatientId(WM_MSG_QUERY_PATIENT, strKeyValueDown)));
	}
	else if ( m_strCurrentTable.CompareNoCase("study") == 0 )
	{
		strKeyValueUp = GetTextByColumnName(pList, nRow, "PatientId");
		strKeyValueDown = GetTextByColumnName(pList, nRow, "Id");
		strMenuText = GetTextByColumnName(pList, nRow, "AccessionNumber");

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_PATIENT, "Query Patient ( AccessionNo = " + strMenuText + " )");
		strSqlPatient.Format("SELECT * FROM Patient WHERE Id = '%s'", strKeyValueUp );
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_PROCEDURESTEP, "Query ProcedureStep ( AccessionNo = " + strMenuText + " )");
		strSqlProcedureStep.Format("SELECT * FROM ProcedureStep WHERE StudyId = '%s'", strKeyValueDown );
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_SERIES, "Query Series ( AccessionNo = " + strMenuText + " )");
		strSqlSeries.Format("SELECT * FROM Series WHERE ProcedureStepId IN ( SELECT Id FROM ProcedureStep WHERE StudyId = '%s')", strKeyValueDown );
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_IMAGE, "Query Image ( AccessionNo = " + strMenuText + " )");
		strSqlImage.Format("SELECT * FROM CaptureImage WHERE SeriesId IN ( SELECT Id FROM Series WHERE ProcedureStepId IN ( SELECT Id FROM ProcedureStep WHERE StudyId = '%s'))",strKeyValueDown );

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_DELETE_STUDY, "Delete Study ( AccessionNo = " + strMenuText + " )");
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_DELETE_ALL_SELECTED_STUDY, "Delete All Selected Studies");

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);
		menu.GetSubMenu(0)->AppendMenu(MF_STRING | MF_ENABLED, WM_MSG_OPEN_STUDY_DIR, "Open Study Dir( StudyInstanceUID = " + strKeyValueDown + " )");

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);
		AddMenuList(menu.GetSubMenu(0), GetCtPssiDetail(GetCtPatientId(WM_MSG_QUERY_STUDY, strKeyValueDown)));
	}
	else if ( m_strCurrentTable.CompareNoCase("procedurestep") == 0 )
	{
		strKeyValueUp = GetTextByColumnName(pList, nRow, "StudyId");
		strKeyValueDown = GetTextByColumnName(pList, nRow, "Id");
		strMenuText = GetTextByColumnName(pList, nRow, "ProcedureName");

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_PATIENT, "Query Patient ( ProcedureName = " + strMenuText + " )");
		strSqlPatient.Format("SELECT * FROM Patient WHERE Id IN (SELECT PatientId FROM Study WHERE Id = '%s')", strKeyValueUp );
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_STUDY, "Query Study ( ProcedureName = " + strMenuText + " )");
		strSqlStudy.Format("SELECT * FROM Study WHERE Id = '%s'", strKeyValueUp );
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_SERIES, "Query Series ( ProcedureName = " + strMenuText + " )");
		strSqlSeries.Format("SELECT * FROM Series WHERE ProcedureStepId  = '%s'", strKeyValueDown );
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_IMAGE, "Query Image ( ProcedureName = " + strMenuText + " )");
		strSqlImage.Format("SELECT * FROM CaptureImage WHERE SeriesId IN ( SELECT Id FROM Series WHERE ProcedureStepId = '%s')", strKeyValueDown );

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_DELETE_PROCEDURESTEP, "Delete ProcedureStep ( ProcedureName = " + strMenuText + " )");
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_DELETE_ALL_SELECTED_PROCEDURESTEP, "Delete All Selected ProcedureSteps");

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);
		AddMenuList(menu.GetSubMenu(0), GetCtPssiDetail(GetCtPatientId(WM_MSG_QUERY_PROCEDURESTEP, strKeyValueDown)));
	}
	else if ( m_strCurrentTable.CompareNoCase("series") == 0 )
	{
		strKeyValueUp = GetTextByColumnName(pList, nRow, "ProcedureStepId");
		strKeyValueDown = GetTextByColumnName(pList, nRow, "Id");
		strMenuText = GetTextByColumnName(pList, nRow, "BodyPartDicomName");

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_PATIENT, "Query Patient ( BodyPart = " + strMenuText + " )");
		strSqlPatient.Format("SELECT * FROM Patient WHERE Id IN ( SELECT PatientId FROM Study WHERE Id In (SELECT StudyId FROM ProcedureStep WHERE Id = '%s'))", strKeyValueUp );
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_STUDY, "Query Study ( BodyPart = " + strMenuText + " )");
		strSqlStudy.Format("SELECT * FROM Study WHERE Id In (SELECT StudyId FROM ProcedureStep WHERE Id = '%s')",strKeyValueUp );
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_PROCEDURESTEP, "Query ProcedureStep ( BodyPart = " + strMenuText + " )");
		strSqlProcedureStep.Format("SELECT * FROM ProcedureStep WHERE Id = '%s'", strKeyValueUp );
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_IMAGE, "Query Image ( BodyPart = " + strMenuText + " )");
		strSqlImage.Format("SELECT * FROM CaptureImage WHERE SeriesId = '%s'",strKeyValueDown );

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_DELETE_SERIES, "Delete Series ( BodyPart = " + strMenuText + " )");
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_DELETE_ALL_SELECTED_SERIES, "Delete All Selected Series");

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);
		AddMenuList(menu.GetSubMenu(0), GetCtPssiDetail(GetCtPatientId(WM_MSG_QUERY_SERIES, strKeyValueDown)));
	}
	else if ( m_strCurrentTable.CompareNoCase("captureimage") == 0 )
	{
		strKeyValueUp = GetTextByColumnName(pList, nRow, "SeriesId");
		strKeyValueDown = GetTextByColumnName(pList, nRow, "Id");
		strMenuText = GetTextByColumnName(pList, nRow, "SopInstanceUid");

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_PATIENT, "Query Patient ( SOPInstanceUID = " + strMenuText + " )");
		strSqlPatient.Format("SELECT * FROM Patient WHERE Id IN ( SELECT PatientId FROM Study WHERE Id In (SELECT StudyId FROM ProcedureStep WHERE Id IN ( SELECT ProcedureStepId FROM Series WHERE Id = '%s')))", strKeyValueUp );
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_STUDY, "Query Study ( SOPInstanceUID = " + strMenuText + " )");
		strSqlStudy.Format("SELECT * FROM Study WHERE Id In (SELECT StudyId FROM ProcedureStep WHERE Id IN ( SELECT ProcedureStepId FROM Series WHERE Id = '%s'))", strKeyValueUp );
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_PROCEDURESTEP, "Query ProcedureStep ( SOPInstanceUID = " + strMenuText + " )");
		strSqlProcedureStep.Format("SELECT * FROM ProcedureStep WHERE Id IN ( SELECT ProcedureStepId FROM Series WHERE Id = '%s')", strKeyValueUp );
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_SERIES, "Query Series ( SOPInstanceUID = " + strMenuText + " )");
		strSqlSeries.Format("SELECT * FROM Series WHERE Id = '%s'",strKeyValueUp );

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_DELETE_IMAGE, "Delete Image ( SOPInstanceUID = " + strMenuText + " )");
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_DELETE_ALL_SELECTED_IMAGE, "Delete All Selected Images");

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);
		menu.GetSubMenu(0)->AppendMenu(MF_STRING | MF_ENABLED, WM_MSG_OPEN_IMAGE, "Open Image ( SOPInstanceUID = " + strMenuText + " )");

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);
		AddMenuList(menu.GetSubMenu(0), GetCtPssiDetail(GetCtPatientId(WM_MSG_QUERY_IMAGE, strKeyValueDown)));
	}
	else if ( m_strCurrentTable.CompareNoCase("ProtocolTemplate") == 0 )
	{
		strKeyValueDown = GetTextByColumnName(pList, nRow, "Id");
		strMenuText = GetTextByColumnName(pList, nRow, "UniqueName");

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_SCAN, "Query CT Scan ( " + strMenuText + " )");
		strSqlScanTemplate.Format("SELECT * FROM ScanTemplate WHERE ProtocolTemplateId = '%s'", strKeyValueDown );
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_RECON, "Query CT Reconstruction ( " + strMenuText + " )");
		strSqlReconTemplate.Format("SELECT * FROM ReconTemplate WHERE ScanTemplateId IN (SELECT Id FROM ScanTemplate WHERE ProtocolTemplateId = '%s')", strKeyValueDown );

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);
		m_strCtDetailId = strKeyValueDown;
		AddMenuList(menu.GetSubMenu(0), GetCtProtolDetail(strKeyValueDown));
	}
	else if ( m_strCurrentTable.CompareNoCase("ScanTemplate") == 0 )
	{
		strKeyValueDown = GetTextByColumnName(pList, nRow, "Id");
		strKeyValueUp = GetTextByColumnName(pList, nRow, "ProtocolTemplateId");
		strMenuText = GetTextByColumnName(pList, nRow, "UniqueName");

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_PROTOCOL, "Query CT Protocol ( " + strMenuText + " )");
		strSqlProtocolTemplate.Format("SELECT * FROM ProtocolTemplate WHERE Id = '%s'", strKeyValueUp );
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_RECON, "Query CT Reconstruction  ( " + strMenuText + " )");
		strSqlReconTemplate.Format("SELECT * FROM ReconTemplate WHERE ScanTemplateId = '%s'", strKeyValueDown );

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_SCAN_PRRAM, "Query Scan Params  ( " + strMenuText + " )");
		strSqlScanParamTemplate.Format("SELECT * FROM ScanParamTemplate WHERE ScanTemplateId = '%s'", strKeyValueDown );

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);
		m_strCtDetailId = strKeyValueDown;
		AddMenuList(menu.GetSubMenu(0), GetCtProtolDetail(strKeyValueUp));
	}
	else if ( m_strCurrentTable.CompareNoCase("ReconTemplate") == 0 )
	{
		strKeyValueDown = GetTextByColumnName(pList, nRow, "Id");
		strKeyValueUp = GetTextByColumnName(pList, nRow, "ScanTemplateId");
		strMenuText = GetTextByColumnName(pList, nRow, "UniqueName");
		CString strProtocolId = GetProtocolTemplateIdFromScanId(strKeyValueUp);

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_PROTOCOL, "Query CT Protocol ( " + strMenuText + " )");
		strSqlProtocolTemplate.Format("SELECT * FROM ProtocolTemplate WHERE Id = '%s'", strProtocolId );
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_SCAN, "Query CT Scan  ( " + strMenuText + " )");
		strSqlScanTemplate.Format("SELECT * FROM ScanTemplate WHERE Id = '%s'", strKeyValueUp );

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_RECON_PRRAM, "Query CT Recon Params  ( " + strMenuText + " )");
		strSqlReconParamTemplate.Format("SELECT * FROM ReconParamTemplate WHERE ReconTemplateId = '%s'", strKeyValueDown );

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);
		m_strCtDetailId = strKeyValueDown;
		AddMenuList(menu.GetSubMenu(0), GetCtProtolDetail(strProtocolId));				
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
	case WM_MSG_QUERY_PROCEDURESTEP:
		ChangeCurrentTable("ProcedureStep");
		RunSQL(strSqlProcedureStep, TRUE);
		break;
	case WM_MSG_QUERY_SERIES:
		ChangeCurrentTable("Series");
		RunSQL(strSqlSeries, TRUE);
		break;
	case WM_MSG_QUERY_IMAGE:
		ChangeCurrentTable("CaptureImage");
		RunSQL(strSqlImage, TRUE);
		break;
	//case WM_MSG_QUERY_ORDER:
	//	ChangeCurrentTable("MWLOrder");
	//	RunSQL(strSqlOrder, TRUE);
	//	break;
	//case WM_MSG_QUERY_VIEW:
	//	ChangeCurrentTable("MWLView");
	//	RunSQL(strSqlView, TRUE);
	//	break;
	case WM_MSG_DELETE_IMAGE:
	case WM_MSG_DELETE_SERIES:
	case WM_MSG_DELETE_STUDY:
	case WM_MSG_DELETE_PATIENT:
	case WM_MSG_DELETE_ORDER:
	case WM_MSG_DELETE_VIEW:
	case WM_MSG_DELETE_PROCEDURESTEP:
		if (m_nProductType == PRODUCT_CT || m_nProductType == PRODUCT_IV)
		{
			if(DeletePSSIForCt(nResult, strKeyValueDown))
			{
				m_pCurrentList->DeleteItem(nRow);
			}
		}
		else
		{
			if(DeletePSSI(nResult, strKeyValueDown))
			{
				m_pCurrentList->DeleteItem(nRow);
			}
		}
				
		break;
	case WM_MSG_OPEN_STUDY_DIR:
		OpenStudyDir(strKeyValueDown);
		break;
	case WM_MSG_OPEN_IMAGE:
		OpenImage(strKeyValueDown);
		break;
	case WM_MSG_DELETE_ALL_SELECTED_IMAGE:
	case WM_MSG_DELETE_ALL_SELECTED_SERIES:
	case WM_MSG_DELETE_ALL_SELECTED_STUDY:
	case WM_MSG_DELETE_ALL_SELECTED_PATIENT:
	case WM_MSG_DELETE_ALL_SELECTED_ORDER:
	case WM_MSG_DELETE_ALL_SELECTED_VIEW:
	case WM_MSG_DELETE_ALL_SELECTED_PROCEDURESTEP:
		if (m_nProductType == PRODUCT_CT || m_nProductType == PRODUCT_IV)
			DeleteAllSelectedPssiForCt(nResult - 100);
		else
			DeleteAllSelectedPssi(nResult - 100);
		
		break;

	case WM_MSG_QUERY_PROTOCOL:
		ChangeCurrentTable("ProtocolTemplate");
		RunSQL(strSqlProtocolTemplate, TRUE);
		break;

	case WM_MSG_QUERY_SCAN:
		ChangeCurrentTable("ScanTemplate");
		RunSQL(strSqlScanTemplate, TRUE);
		break;

	case WM_MSG_QUERY_RECON:
		ChangeCurrentTable("ReconTemplate");
		RunSQL(strSqlReconTemplate, TRUE);
		break;

	case WM_MSG_QUERY_SCAN_PRRAM:
		ChangeCurrentTable("ScanParamTemplate");
		RunSQL(strSqlScanParamTemplate, TRUE);
		break;

	case WM_MSG_QUERY_RECON_PRRAM:
		ChangeCurrentTable("ReconParamTemplate");
		RunSQL(strSqlReconParamTemplate, TRUE);
		break;
		
	}
}

void CTinySMMSDlg::OnIsContextMenu(CListCtrl* pListCtrl, int nRow, int nCol, UINT nFlags, CPoint point)
{
	CCustomListCtrl* pList = (CCustomListCtrl*)pListCtrl;
	m_nClickedRow = nRow;

	CMenu menu;
	m_pCurrentList->ClientToScreen(&point);
	menu.LoadMenu(IDR_MENU1);

	CString strUpTable, strDownTable, strUpTableKeyColumn, strDownTableKeyColumn;
	CString strSqlPatient, strSqlStudy, strSqlSeries, strSqlImage, strSqlOrder, strSqlView;
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
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_ORDER, "Query Order ( PatientID = " + strMenuText + " )");
		strSqlOrder.Format("SELECT * FROM MWLOrder WHERE PatientID = '%s'", strMenuText );
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_VIEW, "Query View ( PatientID = " + strMenuText + " )");
		strSqlView.Format("SELECT * FROM MWLView WHERE MWLOrderKey IN (SELECT MWLOrderKey FROM MWLOrder WHERE PatientID = '%s')", strMenuText );

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_DELETE_PATIENT, "Delete Patient ( PatientID = " + strMenuText + " )");
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_DELETE_ALL_SELECTED_PATIENT, "Delete All Selected Patients");

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);
		AddMenuList(menu.GetSubMenu(0), GetPssiDetail(GetPatientGUID(WM_MSG_QUERY_PATIENT, strKeyValueDown)));
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
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_ORDER, "Query Order ( AccessionNo = " + strMenuText + " )");
		strSqlOrder.Format("SELECT * FROM MWLOrder WHERE StudyInstanceUID = '%s'", strKeyValueDown );
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_VIEW, "Query View ( AccessionNo = " + strMenuText + " )");
		strSqlView.Format("SELECT * FROM MWLView WHERE MWLOrderKey IN (SELECT MWLOrderKey FROM MWLOrder WHERE StudyInstanceUID = '%s')", strKeyValueDown );

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_DELETE_STUDY, "Delete Study ( AccessionNo = " + strMenuText + " )");
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_DELETE_ALL_SELECTED_STUDY, "Delete All Selected Studies");

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);
		menu.GetSubMenu(0)->AppendMenu(MF_STRING | MF_ENABLED, WM_MSG_OPEN_STUDY_DIR, "Open Study Dir( StudyInstanceUID = " + strKeyValueDown + " )");

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);
		AddMenuList(menu.GetSubMenu(0), GetPssiDetail(GetPatientGUID(WM_MSG_QUERY_STUDY, strKeyValueDown)));
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
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_ORDER, "Query Order ( BodyPart = " + strMenuText + " )");
		strSqlOrder.Format("SELECT * FROM MWLOrder WHERE StudyInstanceUID = '%s'", strKeyValueUp );
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_VIEW, "Query View ( BodyPart = " + strMenuText + " )");
		strSqlView.Format("SELECT * FROM MWLView WHERE Bodypart = '%s' AND MWLOrderKey IN (SELECT MWLOrderKey FROM MWLOrder WHERE StudyInstanceUID = '%s')", strMenuText, strKeyValueUp );

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_DELETE_SERIES, "Delete Series ( BodyPart = " + strMenuText + " )");
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_DELETE_ALL_SELECTED_SERIES, "Delete All Selected Series");

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);
		AddMenuList(menu.GetSubMenu(0), GetPssiDetail(GetPatientGUID(WM_MSG_QUERY_SERIES, strKeyValueDown)));
	}
	else if ( m_strCurrentTable.CompareNoCase("image") == 0 )
	{
		strKeyValueUp = GetTextByColumnName(pList, nRow, "SeriesInstanceUID");
		strMenuText = GetTextByColumnName(pList, nRow, "SOPInstanceUID");
		strKeyValueDown = strMenuText;
		CString strImageSerialNo = GetTextByColumnName(pList, nRow, "SerialNo");

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_PATIENT, "Query Patient ( SOPInstanceUID = " + strMenuText + " )");
		strSqlPatient.Format("SELECT * FROM Patient WHERE PatientGUID IN ( SELECT PatientGUID FROM Study WHERE StudyInstanceUID IN ( SELECT StudyInstanceUID FROM Series WHERE SeriesInstanceUID = '%s'))", strKeyValueUp );
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_STUDY, "Query Study ( SOPInstanceUID = " + strMenuText + " )");
		strSqlStudy.Format("SELECT * FROM Study WHERE StudyInstanceUID IN ( SELECT StudyInstanceUID FROM Series WHERE SeriesInstanceUID = '%s')", strKeyValueUp );
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_SERIES, "Query Series ( SOPInstanceUID = " + strMenuText + " )");
		strSqlSeries.Format("SELECT * FROM Series WHERE SeriesInstanceUID = '%s'",strKeyValueUp );

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_ORDER, "Query Order ( SOPInstanceUID = " + strMenuText + " )");
		strSqlOrder.Format("SELECT * FROM MWLOrder WHERE StudyInstanceUID IN ( SELECT StudyInstanceUID FROM Series WHERE SeriesInstanceUID = '%s')", strKeyValueUp );
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_VIEW, "Query View ( SOPInstanceUID = " + strMenuText + " )");
		strSqlView.Format("SELECT * FROM MWLView WHERE ImageKey = '%s'", strImageSerialNo );

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_DELETE_IMAGE, "Delete Image ( SOPInstanceUID = " + strMenuText + " )");
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_DELETE_ALL_SELECTED_IMAGE, "Delete All Selected Images");

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);
		menu.GetSubMenu(0)->AppendMenu(MF_STRING | MF_ENABLED, WM_MSG_OPEN_IMAGE, "Open Image ( SOPInstanceUID = " + strMenuText + " )");

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);
		AddMenuList(menu.GetSubMenu(0), GetPssiDetail(GetPatientGUID(WM_MSG_QUERY_IMAGE, strKeyValueDown)));
	}
	else if ( m_strCurrentTable.CompareNoCase("SMS") == 0 )
	{
		strMenuText = GetTextByColumnName(pList, nRow, "SUID");
		strKeyValueDown = strMenuText;

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);
		AddMenuList(menu.GetSubMenu(0), GetPssiDetail(GetPatientGUID(WM_MSG_QUERY_SMS, strKeyValueDown)));
	}
	else if ( m_strCurrentTable.CompareNoCase("MWLOrder") == 0 )
	{
		strKeyValueDown = GetTextByColumnName(pList, nRow, "MWLOrderKey");
		strMenuText = GetTextByColumnName(pList, nRow, "PatientID");

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_PATIENT, "Query Patient ( PatientID = " + strMenuText + " )");
		strSqlPatient.Format("SELECT * FROM Patient WHERE PatientID = '%s'", strMenuText );
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_STUDY, "Query Study ( PatientID = " + strMenuText + " )");
		strSqlStudy.Format("SELECT * FROM Study WHERE PatientGUID IN (SELECT PatientGUID FROM Patient WHERE PatientID = '%s')", strMenuText );
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_SERIES, "Query Series ( PatientID = " + strMenuText + " )");
		strSqlSeries.Format("SELECT * FROM Series WHERE StudyInstanceUID IN (SELECT StudyInstanceUID FROM Study WHERE PatientGUID IN (SELECT PatientGUID FROM Patient WHERE PatientID = '%s'))",strMenuText );
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_IMAGE, "Query Image ( PatientID = " + strMenuText + " )");
		strSqlImage.Format("SELECT * FROM Image WHERE SeriesInstanceUID IN (SELECT SeriesInstanceUID FROM Series WHERE StudyInstanceUID IN (SELECT StudyInstanceUID FROM Study WHERE PatientGUID IN (SELECT PatientGUID FROM Patient WHERE PatientID = '%s')))",strMenuText );

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_QUERY_VIEW, "Query View ( MWLOrderKey = " + strKeyValueDown + " )");
		strSqlView.Format("SELECT * FROM MWLView WHERE MWLOrderKey = '%s'", strKeyValueDown );

		menu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_DELETE_ORDER, "Delete Order ( PatientID = " + strMenuText + ", OrderKey = " + strKeyValueDown + " )");
		menu.GetSubMenu(0)->AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_DELETE_ALL_SELECTED_ORDER, "Delete All Selected Orders");
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
	case WM_MSG_QUERY_ORDER:
		ChangeCurrentTable("MWLOrder");
		RunSQL(strSqlOrder, TRUE);
		break;
	case WM_MSG_QUERY_VIEW:
		ChangeCurrentTable("MWLView");
		RunSQL(strSqlView, TRUE);
		break;
	case WM_MSG_DELETE_IMAGE:
	case WM_MSG_DELETE_SERIES:
	case WM_MSG_DELETE_STUDY:
	case WM_MSG_DELETE_PATIENT:
	case WM_MSG_DELETE_ORDER:
	case WM_MSG_DELETE_VIEW:
		if(DeletePSSI(nResult, strKeyValueDown))
		{
			m_pCurrentList->DeleteItem(nRow);
		}		
		break;
	case WM_MSG_OPEN_STUDY_DIR:
		OpenStudyDir(strKeyValueDown);
		break;
	case WM_MSG_OPEN_IMAGE:
		OpenImage(strKeyValueDown);
		break;
	case WM_MSG_DELETE_ALL_SELECTED_IMAGE:
	case WM_MSG_DELETE_ALL_SELECTED_SERIES:
	case WM_MSG_DELETE_ALL_SELECTED_STUDY:
	case WM_MSG_DELETE_ALL_SELECTED_PATIENT:
	case WM_MSG_DELETE_ALL_SELECTED_ORDER:
	case WM_MSG_DELETE_ALL_SELECTED_VIEW:
		DeleteAllSelectedPssi(nResult - 100);
		break;
	}
}

void CTinySMMSDlg::OnPopupDeleteallselectedrow()
{
	POSITION pos = m_pCurrentList->GetFirstSelectedItemPosition();
	while ( pos )
	{
		int nRow = m_pCurrentList->GetNextSelectedItem(pos);

		CString strSQL = _T("DELETE ") + m_strCurrentTable + GetWhereStatement(nRow, m_nProductType == PRODUCT_CT || m_nProductType == PRODUCT_IV);
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

void CTinySMMSDlg::DeleteAllSelectedPssi(int nType)
{
	POSITION pos = m_pCurrentList->GetFirstSelectedItemPosition();
	while ( pos )
	{
		int nRow = m_pCurrentList->GetNextSelectedItem(pos);
		
		CString strKeyColumnName;
		if (nType == WM_MSG_DELETE_PATIENT)
		{
			strKeyColumnName = "PatientGUID";
		}
		else if (nType == WM_MSG_DELETE_STUDY)
		{
			strKeyColumnName = "StudyInstanceUID";
		}
		else if (nType == WM_MSG_DELETE_SERIES)
		{
			strKeyColumnName = "SeriesInstanceUID";
		}
		else if (nType == WM_MSG_DELETE_IMAGE)
		{
			strKeyColumnName = "SOPInstanceUID";
		}
		else if (nType == WM_MSG_DELETE_ORDER)
		{
			strKeyColumnName = "MWLOrderKey";
		}
		else if (nType == WM_MSG_DELETE_VIEW)
		{
			strKeyColumnName = "MWLViewKey";
		}

		CString strUID = GetTextByColumnName(m_pCurrentList, nRow, strKeyColumnName);
		if (DeletePSSI(nType, strUID))
		{
			m_pCurrentList->DeleteItem(nRow);	
		}
		else
		{
			return;
		}		
		
		pos = m_pCurrentList->GetFirstSelectedItemPosition();
	}
}

void CTinySMMSDlg::DeleteAllSelectedPssiForCt(int nType)
{
	POSITION pos = m_pCurrentList->GetFirstSelectedItemPosition();
	while ( pos )
	{
		int nRow = m_pCurrentList->GetNextSelectedItem(pos);
		

		CString strUID = GetTextByColumnName(m_pCurrentList, nRow, "Id");
		if (DeletePSSIForCt(nType, strUID))
		{
			m_pCurrentList->DeleteItem(nRow);	
		}
		else
		{
			return;
		}		

		pos = m_pCurrentList->GetFirstSelectedItemPosition();
	}
}

void CTinySMMSDlg::OnPopupInsertcopy32775()
{
	CInsertRowDialog dlg;

	dlg.m_pDataList = m_pCurrentList;
	dlg.m_nRow = m_nClickedRow;
	dlg.m_strTableName = m_strCurrentTable;
	dlg.m_bViewOnly = FALSE;
	dlg.m_nProductType = m_nProductType;
	
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

CString CTinySMMSDlg::GetWhereStatement(int nRow, BOOL bOnlyFirstColumn)
{
	
	int nColCount = m_pCurrentList->m_ctrlHeader.GetItemCount();
	if ( nRow < 0 || nRow >= m_pCurrentList->GetItemCount() )
		return _T("");
	
	CString strWhere;
	if (bOnlyFirstColumn)
	{
		nColCount = 1;
	}

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


BOOL CTinySMMSDlg::DeletePSSI( int nType, CString strUID )
{
	vector<CString> vecSqlList;

	if (nType == WM_MSG_DELETE_PATIENT)
	{
		vecSqlList.push_back("Delete Image from Image, Series, Study where Image.SeriesInstanceUID = Series.SeriesInstanceUID and Series.StudyInstanceUID = Study.StudyInstanceUID and Study.PatientGUID = '" + strUID + "'");
		vecSqlList.push_back("Delete Series from Series, Study where Series.StudyInstanceUID = Study.StudyInstanceUID and Study.PatientGUID = '" + strUID + "'");
		vecSqlList.push_back("Delete SMS from SMS, Study where SMS.SUID = Study.StudyInstanceUID and Study.PatientGUID = '" + strUID + "'");
		vecSqlList.push_back("Delete MWLView from MWLView, MWLOrder, Study where MWLView.MWLOrderKey = MWLOrder.MWLOrderKey and MWLOrder.StudyInstanceUID = Study.StudyInstanceUID and Study.PatientGUID = '" + strUID + "'");
		vecSqlList.push_back("Delete MWLOrderExtendField from MWLOrderExtendField, MWLOrder, Study where MWLOrderExtendField.MWLOrderKey = MWLOrder.MWLOrderKey and MWLOrder.StudyInstanceUID = Study.StudyInstanceUID and Study.PatientGUID = '" + strUID + "'");
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
		vecSqlList.push_back("Delete MWLOrderExtendField from MWLOrderExtendField, MWLOrder where MWLOrderExtendField.MWLOrderKey = MWLOrder.MWLOrderKey and MWLOrder.StudyInstanceUID = '" + strUID + "'");
		vecSqlList.push_back("Delete from MWLOrder where StudyInstanceUID = '" + strUID + "'");
		vecSqlList.push_back("Delete from Study where StudyInstanceUID = '" + strUID + "'");
	}
	else if (nType == WM_MSG_DELETE_SERIES)
	{
		vecSqlList.push_back("Delete from Image where Image.SeriesInstanceUID = '" + strUID + "'");
		vecSqlList.push_back("Delete from Series where Series.SeriesInstanceUID = '" + strUID + "'");
	}
	else if (nType == WM_MSG_DELETE_IMAGE)
	{
		vecSqlList.push_back("Delete from Image where Image.SopInstanceUID = '" + strUID + "'");
	}
	else if (nType == WM_MSG_DELETE_ORDER)
	{
		vecSqlList.push_back("Delete Image from Image, Series, Study, MWLOrder where Image.SeriesInstanceUID = Series.SeriesInstanceUID and Series.StudyInstanceUID = Study.StudyInstanceUID and Study.SerialNo = MWLOrder.StudyKey and MWLOrder.MWLOrderKey =" + strUID);
		vecSqlList.push_back("Delete Series from Series, Study, MWLOrder where Series.StudyInstanceUID = Study.StudyInstanceUID and Study.SerialNo = MWLOrder.StudyKey and MWLOrder.MWLOrderKey =" + strUID);
		vecSqlList.push_back("Delete SMS from SMS, Study, MWLOrder where SMS.SUID = Study.StudyInstanceUID and Study.SerialNo = MWLOrder.StudyKey and MWLOrder.MWLOrderKey =" + strUID);
		vecSqlList.push_back("Delete from MWLView where MWLOrderKey =" + strUID);
		vecSqlList.push_back("Delete from MWLOrderExtendField where MWLOrderKey =" + strUID);
		vecSqlList.push_back("Delete Study from Study, MWLOrder where Study.SerialNo = MWLOrder.StudyKey and MWLOrder.MWLOrderKey =" + strUID);
		vecSqlList.push_back("Delete from MWLOrder where MWLOrderKey =" + strUID);		
	}
	else if (nType == WM_MSG_DELETE_VIEW)
	{
		vecSqlList.push_back("Delete from Image where Image.SopInstanceUID = '" + strUID + "'");
	}

	return m_pDBConn->RunTransaction(vecSqlList);
}



void CTinySMMSDlg::OnBnClickedButtonClearPssi()
{
	if (AfxMessageBox("Are you sure to clear Pssi?", MB_YESNO) == IDNO)
	{
		return;
	}

	vector<CString> vecSqlList;

	if (m_nProductType == PRODUCT_IV || m_nProductType == PRODUCT_CT)
	{
		vecSqlList.push_back("Delete from CaptureImage");
		vecSqlList.push_back("Delete from Series");
		vecSqlList.push_back("Delete from ScanExecution");
		vecSqlList.push_back("Delete from ProcedureStep");
		vecSqlList.push_back("Delete from Study");
		vecSqlList.push_back("Delete from Patient");
	}
	else
	{
		vecSqlList.push_back("Delete from Image");
		vecSqlList.push_back("Delete from Series");
		vecSqlList.push_back("Delete from SMS");
		vecSqlList.push_back("Delete from MWLOrderExtendField");
		vecSqlList.push_back("Delete from MWLView");
		vecSqlList.push_back("Delete from MWLOrder");
		vecSqlList.push_back("Delete from Study");
		vecSqlList.push_back("Delete from Patient");
	}	

	if (m_pDBConn->RunTransaction(vecSqlList))
	{
		AfxMessageBox("Pssi data cleared!");
	}
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
	m_listSystemInfo.ShowWindow(SW_HIDE);

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

	m_pCurrentList->SetFocus();
	m_pCurrentList->SortPrevious();

	for (map<CString, CColorButton*>::iterator it = m_mapTableButton.begin(); it != m_mapTableButton.end(); it++)
	{
		if (it->first.CompareNoCase(strTableName) == 0)
		{
			bFind = TRUE;
			SetActiveButton(it->second);
			break;
		}
	}

	if (!bFind)
	{
		SetActiveButton(NULL);
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

void CTinySMMSDlg::AddMenuList( CMenu* pMenu, vector<CString> vecMenuText )
{
	for (int i = 0; i < vecMenuText.size(); i ++)
	{
		if (vecMenuText[i].Find("ProcedureStep") != -1)
		{
			CString strMenuText = vecMenuText[i].Left(vecMenuText[i].GetLength() - 39);
			CString strProtocolId = vecMenuText[i].Right(38);
			vector<CString> vecProtocol = GetCtProtolDetail( strProtocolId );

			CMenu menuProtocol;
			menuProtocol.CreatePopupMenu();
			for (int j = 0; j < vecProtocol.size(); j ++)
				menuProtocol.AppendMenu(MF_STRING|MF_ENABLED, WM_MSG_VIEW_PSSI, vecProtocol[j]);

			pMenu->AppendMenu(MF_POPUP, (UINT_PTR)menuProtocol.GetSafeHmenu(), 	strMenuText);
		}
		else
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
		if (m_nProductType == PRODUCT_IS)
		{
			RunSQL("SELECT * FROM Patient ORDER BY SerialNo DESC", TRUE);
			m_pCurrentList->Sort(0, FALSE, TRUE);
		}
		else
		{
			RunSQL("SELECT * FROM Patient ORDER BY DicomPatientId DESC", TRUE);
			m_pCurrentList->Sort(6, FALSE, TRUE);
		}		
	}
}

void CTinySMMSDlg::OnButtonStudy()
{
	ChangeCurrentTable("Study");
	if (m_pCurrentList->GetHeaderCtrl()->GetItemCount() == 0)
	{
		if (m_nProductType == PRODUCT_IS)
		{
			RunSQL("SELECT * FROM Study ORDER BY SerialNo DESC", TRUE);
			m_pCurrentList->Sort(0, FALSE, TRUE);	
		}
		else
		{
			RunSQL("SELECT * FROM Study ORDER BY AccessionNumber DESC", TRUE);
			m_pCurrentList->Sort(1, FALSE, TRUE);
		}
	}
}

void CTinySMMSDlg::OnButtonSeries()
{
	ChangeCurrentTable("Series");
	if (m_pCurrentList->GetHeaderCtrl()->GetItemCount() == 0)
	{
		if (m_nProductType == PRODUCT_IS)
		{
			RunSQL("SELECT * FROM Series ORDER BY SerialNo DESC", TRUE);
			m_pCurrentList->Sort(0, FALSE, TRUE);	
		}
		else
		{
			RunSQL("SELECT * FROM Series ORDER BY InstanceUid DESC", TRUE);
			m_pCurrentList->Sort(4, FALSE, TRUE);
		}
		
	}
}

void CTinySMMSDlg::OnButtonImage()
{
	if (m_nProductType == PRODUCT_IS)
	{
		ChangeCurrentTable("Image");
		if (m_pCurrentList->GetHeaderCtrl()->GetItemCount() == 0)
		{
			RunSQL("SELECT * FROM Image ORDER BY SerialNo DESC", TRUE);
			m_pCurrentList->Sort(0, FALSE, TRUE);
		}	
	}
	else
	{
		ChangeCurrentTable("CaptureImage");
		if (m_pCurrentList->GetHeaderCtrl()->GetItemCount() == 0)
		{
			RunSQL("SELECT * FROM CaptureImage ORDER BY AcquisitionDateTimeCombinedDateTime DESC", TRUE);
			m_pCurrentList->Sort(2, FALSE, TRUE);
		}
	}	
}


void CTinySMMSDlg::OnBnClickedButtonSms1()
{
	if (m_nProductType == PRODUCT_IS)
	{
		ChangeCurrentTable("SMS");
		if (m_pCurrentList->GetHeaderCtrl()->GetItemCount() == 0)
		{
			RunSQL("SELECT * FROM SMS ORDER BY SUID DESC", TRUE);
			m_pCurrentList->Sort(0, FALSE, TRUE);
		}	
	}
	else
	{
		ChangeCurrentTable("ProcedureStep");
		if (m_pCurrentList->GetHeaderCtrl()->GetItemCount() == 0)
		{
			RunSQL("SELECT * FROM ProcedureStep ORDER BY CreationDateTime DESC", TRUE);
			m_pCurrentList->Sort(1, FALSE, TRUE);
		}
	}	
}


void CTinySMMSDlg::OnBnClickedButtonWmlorder()
{
	if (m_nProductType == PRODUCT_IS)
	{
		ChangeCurrentTable("MWLOrder");
		if (m_pCurrentList->GetHeaderCtrl()->GetItemCount() == 0)
		{
			RunSQL("SELECT * FROM MWLOrder ORDER BY MWLOrderKey DESC", TRUE);
			m_pCurrentList->Sort(0, FALSE, TRUE);
		}	
	}
	else
	{
		ChangeCurrentTable("ProtocolTemplate");
		if (m_pCurrentList->GetHeaderCtrl()->GetItemCount() == 0)
		{
			RunSQL("SELECT * FROM ProtocolTemplate ORDER BY Id DESC", TRUE);
			m_pCurrentList->Sort(0, FALSE, TRUE);
		}
	}
	
}


void CTinySMMSDlg::OnBnClickedButtonMwlview()
{
	if (m_nProductType == PRODUCT_IS)
	{
		ChangeCurrentTable("MWLView");
		if (m_pCurrentList->GetHeaderCtrl()->GetItemCount() == 0)
		{
			RunSQL("SELECT * FROM MWLView ORDER BY MWLViewKey DESC", TRUE);
			m_pCurrentList->Sort(0, FALSE, TRUE);
		}	
	}
	else
	{
		ChangeCurrentTable("ScanTemplate");
		if (m_pCurrentList->GetHeaderCtrl()->GetItemCount() == 0)
		{
			RunSQL("SELECT * FROM ScanTemplate ORDER BY Id DESC", TRUE);
			m_pCurrentList->Sort(0, FALSE, TRUE);
		}
	}	
}

void CTinySMMSDlg::OnBnClickedButtonUserProfile()
{
	if (m_nProductType == PRODUCT_IS)
	{
		ChangeCurrentTable("UserProfile");
		if (m_pCurrentList->GetHeaderCtrl()->GetItemCount() == 0)
		{
			RunSQL("SELECT TOP 100 * FROM UserProfile", TRUE);
		}	
	}
	else
	{
		ChangeCurrentTable("ReconTemplate");
		if (m_pCurrentList->GetHeaderCtrl()->GetItemCount() == 0)
		{
			RunSQL("SELECT * FROM ReconTemplate ORDER BY Id DESC", TRUE);
			m_pCurrentList->Sort(0, FALSE, TRUE);
		}
	}	
}

void CTinySMMSDlg::OnBnClickedButtonRoleProfile()
{
	if (m_nProductType == PRODUCT_IS)
	{
		ChangeCurrentTable("RoleProfile");
		if (m_pCurrentList->GetHeaderCtrl()->GetItemCount() == 0)
		{
			RunSQL("SELECT TOP 100 * FROM RoleProfile", TRUE);
		}	
	}
	else
	{
		ChangeCurrentTable("ScanParamTemplate");
		if (m_pCurrentList->GetHeaderCtrl()->GetItemCount() == 0)
		{
			RunSQL("SELECT * FROM ScanParamTemplate ORDER BY Id DESC", TRUE);
			m_pCurrentList->Sort(0, FALSE, TRUE);
		}		
	}	
}

void CTinySMMSDlg::OnBnClickedButtonSystemProfile()
{
	if (m_nProductType == PRODUCT_IS)
	{
		ChangeCurrentTable("SystemProfile");
		if (m_pCurrentList->GetHeaderCtrl()->GetItemCount() == 0)
		{
			RunSQL("SELECT TOP 100 * FROM SystemProfile", TRUE);
		}	
	}
	else
	{
		ChangeCurrentTable("ReconParamTemplate");
		if (m_pCurrentList->GetHeaderCtrl()->GetItemCount() == 0)
		{
			RunSQL("SELECT * FROM ReconParamTemplate ORDER BY Id DESC", TRUE);
			m_pCurrentList->Sort(0, FALSE, TRUE);
		}		
	}
}


void CTinySMMSDlg::OnBnClickedButtonSystemInfo()
{
	for (map<CString, CCustomListCtrl*>::iterator it = m_mapTableResult.begin(); it != m_mapTableResult.end(); it++)
	{
		it->second->ShowWindow(SW_HIDE);
	}
	m_listSystemInfo.ShowWindow(SW_SHOW);
}

void CTinySMMSDlg::InitSystemInfoTable()
{
	CustomColumn		gridColumn;
	CustomColumnList	gridColumnsList;

	gridColumn.Reset();
	gridColumn.strHeaderCaption = _T("Name");
	gridColumn.nWidth = 300;
	gridColumn.nFormat = LVCFMT_LEFT;
	gridColumnsList.push_back(gridColumn);

	gridColumn.Reset();
	gridColumn.strHeaderCaption = _T("Value");
	gridColumn.nWidth = 700;
	gridColumn.nFormat = LVCFMT_LEFT;
	gridColumnsList.push_back(gridColumn);


	CString strColumnOrder = "0;1";
	m_listSystemInfo.SetColumnInfo(gridColumnsList, strColumnOrder);

	// Set Row Bk Color
	m_listSystemInfo.AddDefaultRowColor(RGB(239,239,239));
	m_listSystemInfo.AddDefaultRowColor(RGB(207,207,207));

	// Height
	m_listSystemInfo.SetRowHeigt(24);
	m_listSystemInfo.SetHeaderHeight(24);

	m_listSystemInfo.EnableFilter(FALSE);
	m_listSystemInfo.SetMultipleSelection(FALSE);

	int nRow;
	nRow = m_listSystemInfo.AppendRow();
	m_listSystemInfo.SetCell(nRow, 0, "Version");

	nRow = m_listSystemInfo.AppendRow();
	m_listSystemInfo.SetCell(nRow, 0, "Install Time");

	nRow = m_listSystemInfo.AppendRow();
	m_listSystemInfo.SetCell(nRow, 0, "Language");

	nRow = m_listSystemInfo.AppendRow();
	m_listSystemInfo.SetCell(nRow, 0, "Product Name");

	nRow = m_listSystemInfo.AppendRow();
	m_listSystemInfo.SetCell(nRow, 0, "System Name");

	nRow = m_listSystemInfo.AppendRow();
	m_listSystemInfo.SetCell(nRow, 0, "Patient Count");

	nRow = m_listSystemInfo.AppendRow();
	m_listSystemInfo.SetCell(nRow, 0, "Study Count");

	if (m_nProductType == PRODUCT_IV || m_nProductType == PRODUCT_CT)
	{
		nRow = m_listSystemInfo.AppendRow();
		m_listSystemInfo.SetCell(nRow, 0, "ProcedureStep Count");
	}

	nRow = m_listSystemInfo.AppendRow();
	m_listSystemInfo.SetCell(nRow, 0, "Series Count");

	nRow = m_listSystemInfo.AppendRow();
	m_listSystemInfo.SetCell(nRow, 0, "Image Count");


	if (m_nProductType == PRODUCT_CT)
	{
		nRow = m_listSystemInfo.AppendRow();
		m_listSystemInfo.SetCell(nRow, 0, "ScanExecution Count");

		nRow = m_listSystemInfo.AppendRow();
		m_listSystemInfo.SetCell(nRow, 0, "ProtocolTemplate Count");

		nRow = m_listSystemInfo.AppendRow();
		m_listSystemInfo.SetCell(nRow, 0, "ScanTemplate Count");

		nRow = m_listSystemInfo.AppendRow();
		m_listSystemInfo.SetCell(nRow, 0, "ReconTemplate Count");
	}
	else if (m_nProductType == PRODUCT_IS)
	{
		nRow = m_listSystemInfo.AppendRow();
		m_listSystemInfo.SetCell(nRow, 0, "SMS Count");

		nRow = m_listSystemInfo.AppendRow();
		m_listSystemInfo.SetCell(nRow, 0, "MWLOrder Count");

		nRow = m_listSystemInfo.AppendRow();
		m_listSystemInfo.SetCell(nRow, 0, "MWLView Count");
	}
	

	m_listSystemInfo.SetUser(this);
}

void CTinySMMSDlg::LoadSystemInfo()
{
	int nRow = 0;

	if (m_nProductType == PRODUCT_IS)
	{
		m_listSystemInfo.SetCell(nRow++, 1, GetProfileValue("GI_Version"));
		m_listSystemInfo.SetCell(nRow++, 1, GetProfileValue("GI_InstallTime"));
		m_listSystemInfo.SetCell(nRow++, 1, GetProfileValue("GI_Language"));
		m_listSystemInfo.SetCell(nRow++, 1, GetProfileValue("GI_ProductName"));
		m_listSystemInfo.SetCell(nRow++, 1, GetProfileValue("GI_SystemName"));
		m_listSystemInfo.SetCell(nRow++, 1, GetTableRowCount("Patient"));
		m_listSystemInfo.SetCell(nRow++, 1, GetTableRowCount("Study"));
		m_listSystemInfo.SetCell(nRow++, 1, GetTableRowCount("Series"));
		m_listSystemInfo.SetCell(nRow++, 1, GetTableRowCount("Image"));
		m_listSystemInfo.SetCell(nRow++, 1, GetTableRowCount("SMS"));
		m_listSystemInfo.SetCell(nRow++, 1, GetTableRowCount("MWLOrder"));
		m_listSystemInfo.SetCell(nRow++, 1, GetTableRowCount("MWLView"));
	}
	else
	{
		m_listSystemInfo.SetCell(nRow++, 1, "");
		m_listSystemInfo.SetCell(nRow++, 1, "");
		m_listSystemInfo.SetCell(nRow++, 1, "");
		m_listSystemInfo.SetCell(nRow++, 1, "ImageView");
		m_listSystemInfo.SetCell(nRow++, 1, "CT");
		m_listSystemInfo.SetCell(nRow++, 1, GetTableRowCount("Patient"));
		m_listSystemInfo.SetCell(nRow++, 1, GetTableRowCount("Study"));
		m_listSystemInfo.SetCell(nRow++, 1, GetTableRowCount("ProcedureStep"));
		m_listSystemInfo.SetCell(nRow++, 1, GetTableRowCount("Series"));
		m_listSystemInfo.SetCell(nRow++, 1, GetTableRowCount("CaptureImage"));
		m_listSystemInfo.SetCell(nRow++, 1, GetTableRowCount("ScanExecution"));
		m_listSystemInfo.SetCell(nRow++, 1, GetTableRowCount("ProtocolTemplate"));
		m_listSystemInfo.SetCell(nRow++, 1, GetTableRowCount("ScanTemplate"));
		m_listSystemInfo.SetCell(nRow++, 1, GetTableRowCount("ReconTemplate"));
	}
}

CString CTinySMMSDlg::GetTableRowCount( const CString& strTableName )
{
	CString strSql = "SELECT count(*) Count FROM " + strTableName;
	CADORecordset dbrs(m_pDBConn);
	if (!dbrs.Open((LPCTSTR)strSql))
	{
		AfxMessageBox(dbrs.GetLastErrorString());
		return "Error";
	}

	int nCount = 0;
	if (dbrs.IsEOF())
	{
		AfxMessageBox("Cannot get count for table" + strTableName);
		dbrs.Close();
		return "Error";
	}
	else
	{
		dbrs.GetFieldValue("Count", nCount);
		dbrs.Close();
	}

	CString strRet;
	strRet.Format("%d", nCount);
	return strRet;
}

CString CTinySMMSDlg::GetProfileValue( const CString& strPropertyName )
{
	CString strSql = "SELECT PropertyValue FROM SystemProfile WHERE PropertyName = '" + strPropertyName + "'";
	CADORecordset dbrs(m_pDBConn);
	if (!dbrs.Open((LPCTSTR)strSql))
	{
		AfxMessageBox(dbrs.GetLastErrorString());
		return "Error";
	}

	CString strRet;
	if (dbrs.IsEOF())
	{
		AfxMessageBox("Cannot get value for " + strPropertyName);
		dbrs.Close();
		return "Error";
	}
	else
	{
		dbrs.GetFieldValue("PropertyValue", strRet);
		dbrs.Close();
	}

	return strRet;
}

BOOL CTinySMMSDlg::OnKeyPressed( CListCtrl* pListCtrl, WPARAM nKeyCode )
{
	if (nKeyCode == VK_F5)
	{
		if (m_listSystemInfo.IsWindowVisible())
			LoadSystemInfo();
		else
			OnFilterTextChanged(pListCtrl, -1, "");
	}

	return TRUE;
}


void CTinySMMSDlg::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);

	CRect rectOld = m_rectClient;
	GetClientRect(&m_rectClient);

	if (rectOld.Width() == 0 || cx == 0 || cy == 0)
		return;

	int nWidthDiff = m_rectClient.right - rectOld.right;
	int nHeightDiff = m_rectClient.bottom - rectOld.bottom;

	MoveControl(nWidthDiff, nHeightDiff, IDC_BUTTON_RELOAD, FALSE, TRUE, FALSE, FALSE);
	MoveControl(nWidthDiff, nHeightDiff, IDC_LIST_TABS, FALSE, FALSE, TRUE, FALSE);
	MoveControl(nWidthDiff, nHeightDiff, IDC_EDIT_SQL, FALSE, FALSE, FALSE, TRUE);
	MoveControl(nWidthDiff, nHeightDiff, IDC_LIST_RESULT, FALSE, FALSE, TRUE, TRUE);
	MoveControl(nWidthDiff, nHeightDiff, IDC_LIST_SYSTEM_INFO, FALSE, FALSE, TRUE, TRUE);

	for (map<CString, CCustomListCtrl*>::iterator it = m_mapTableResult.begin(); it != m_mapTableResult.end(); it++)
	{
		MoveControl(nWidthDiff, nHeightDiff, it->second->GetDlgCtrlID(), FALSE, FALSE, TRUE, TRUE);
	}
}

void CTinySMMSDlg::MoveControl(int nWidthDiff, int nHeightDiff, int nID, BOOL bMoveLeft, BOOL bMoveTop, BOOL bChangeHeight, BOOL bChangeWidth)
{
	CWnd* pChildWnd = GetDlgItem(nID);
	CRect rect;
	pChildWnd->GetWindowRect(&rect);
	ScreenToClient(&rect);

	int nOldHeight = rect.Height();
	int nOldWidth = rect.Width();

	if (bMoveLeft)
	{
		rect.left += nWidthDiff;
		rect.right += nWidthDiff;
	}

	if (bMoveTop)
	{
		rect.top += nHeightDiff;
		rect.bottom += nHeightDiff;
	}

	if (bChangeWidth)
		rect.right = rect.left + nOldWidth + nWidthDiff;

	if (bChangeHeight)
		rect.bottom = rect.top + nOldHeight + nHeightDiff;

	pChildWnd->MoveWindow(&rect);
}

CString CTinySMMSDlg::GetCtPatientId( int nIDType, const CString& strId )
{
	CString strSql;

	m_nViewPssiClickedType = nIDType;
	m_strViewPssiClickeUID = strId;

	if (nIDType == WM_MSG_QUERY_PATIENT)
	{
		return strId;	
	}
	else if (nIDType == WM_MSG_QUERY_STUDY)
	{
		strSql = "SELECT PatientId from Study where Id = '" + strId + "'";
	}
	else if (nIDType == WM_MSG_QUERY_PROCEDURESTEP)
	{
		strSql = "SELECT PatientId from Study, ProcedureStep WHERE Study.Id = ProcedureStep.StudyId AND ProcedureStep.Id = '" + strId + "'";
	}
	else if (nIDType == WM_MSG_QUERY_SERIES)
	{
		strSql = "SELECT PatientId from Study, ProcedureStep, Series WHERE Study.Id = ProcedureStep.StudyId AND ProcedureStep.Id = Series.ProcedureStepId AND Series.Id = '" + strId + "'";
	}
	else 
	{
		strSql = "SELECT PatientId from Study, ProcedureStep, Series, CaptureImage WHERE Study.Id = ProcedureStep.StudyId AND ProcedureStep.Id = Series.ProcedureStepId AND Series.Id = CaptureImage.SeriesId AND CaptureImage.Id = '" + strId + "'";
	}

	CADORecordset dbrs(m_pDBConn);
	if(!dbrs.Open((LPCTSTR)strSql)) 
	{
		AfxMessageBox(dbrs.GetLastErrorString());
		return "";
	}


	CString strPatientId;
	if(!dbrs.IsEOF())
	{
		BOOL B = dbrs.GetFieldValue("PatientId", strPatientId);
	}
	dbrs.Close();

	return strPatientId;
}

vector<CString> CTinySMMSDlg::GetCtPssiDetail( const CString& Id )
{
	vector<CString> vecPssi;
	CString strSql;

	strSql = "SELECT DicomPatientId, NameDicomFormatName FROM Patient WHERE Id = '" + Id + "'";

	CADORecordset dbrs(m_pDBConn);
	if(!dbrs.Open((LPCTSTR)strSql)) 
	{
		AfxMessageBox(dbrs.GetLastErrorString());
		return vecPssi;
	}


	CString strPatientName, strPatientID;
	if(!dbrs.IsEOF())
	{
		dbrs.GetFieldValue("NameDicomFormatName", strPatientName);
		dbrs.GetFieldValue("DicomPatientId", strPatientID);
	}
	dbrs.Close();

	vecPssi.push_back("Patient - Name : " + strPatientName + ", ID : " + strPatientID);

	//////////////////////////////////////////////////////////////////////////////////////////////
	strSql = "SELECT Id, StudyDateTimeCombinedDateTime, AccessionNumber FROM Study WHERE PatientId = '" + Id + "'";
	if(!dbrs.Open((LPCTSTR)strSql)) 
	{
		AfxMessageBox(dbrs.GetLastErrorString());
		return vecPssi;
	}


	CString strStudyId, strStudyDateTime, strAccessionNo;
	int nScanStatus;
	while(!dbrs.IsEOF())
	{
		dbrs.GetFieldValue("Id", strStudyId);
		dbrs.GetFieldValue("StudyDateTimeCombinedDateTime", strStudyDateTime);
		dbrs.GetFieldValue("AccessionNumber", strAccessionNo);

		CString strPrefix = "    ";
		if (m_nViewPssiClickedType == WM_MSG_QUERY_STUDY && m_strViewPssiClickeUID == strStudyId)
			strPrefix = "  * ";

		CString strLine;
		strLine.Format("%sStudy - DateTime : %s, AccessionNo : %s", strPrefix, strStudyDateTime, strAccessionNo);
		vecPssi.push_back(strLine);

		vector<CString> vecProcedureStep = GetProcedureStepDetail(strStudyId);
		for (int i = 0; i < vecProcedureStep.size(); i ++)
		{
			vecPssi.push_back(vecProcedureStep[i]);
		}

		dbrs.MoveNext();
	}
	dbrs.Close();

	return vecPssi;	
}

vector<CString> CTinySMMSDlg::GetProcedureStepDetail( const CString& strStudyId )
{
	vector<CString> vecProcedureStep;
	CString strSql;

	strSql = "SELECT Id, ProcedureName, ProcedureCode, ProtocolTemplateId FROM ProcedureStep WHERE StudyId = '" + strStudyId + "'";

	CADORecordset dbrs(m_pDBConn);
	if(!dbrs.Open((LPCTSTR)strSql)) 
	{
		AfxMessageBox(dbrs.GetLastErrorString());
		return vecProcedureStep;
	}


	CString strProcedureStepId, strProcedureName, strProcedureCode, stsrProtocolTemplateId;
	while(!dbrs.IsEOF())
	{
		dbrs.GetFieldValue("Id", strProcedureStepId);
		dbrs.GetFieldValue("ProcedureName", strProcedureName);
		dbrs.GetFieldValue("ProcedureCode", strProcedureCode);
		dbrs.GetFieldValue("ProtocolTemplateId", stsrProtocolTemplateId);

		CString strPrefix = "        ";
		if (m_nViewPssiClickedType == WM_MSG_QUERY_PROCEDURESTEP && m_strViewPssiClickeUID == strProcedureStepId)
			strPrefix = "      * ";

		vecProcedureStep.push_back(strPrefix + "ProcedureStep - Name : " + strProcedureName + ", Code : " + strProcedureCode + stsrProtocolTemplateId);

		vector<CString> vecImage = GetCtSeriesDetail(strProcedureStepId);
		for (int i = 0; i < vecImage.size(); i ++)
		{
			vecProcedureStep.push_back(vecImage[i]);
		}

		dbrs.MoveNext();
	}
	dbrs.Close();
	
	return vecProcedureStep;
}

vector<CString> CTinySMMSDlg::GetCtSeriesDetail( const CString& strProcedureStepId )
{
	vector<CString> vecSeries;
	CString strSql;

	strSql = "SELECT Id, BodyPartDicomName, Modality FROM Series WHERE ProcedureStepId = '" + strProcedureStepId + "'";

	CADORecordset dbrs(m_pDBConn);
	if(!dbrs.Open((LPCTSTR)strSql)) 
	{
		AfxMessageBox(dbrs.GetLastErrorString());
		return vecSeries;
	}


	CString strSeriesId, strBodyPart, strModality;
	while(!dbrs.IsEOF())
	{
		dbrs.GetFieldValue("Id", strSeriesId);
		dbrs.GetFieldValue("BodyPartDicomName", strBodyPart);
		dbrs.GetFieldValue("Modality", strModality);

		CString strPrefix = "            ";
		if (m_nViewPssiClickedType == WM_MSG_QUERY_SERIES && m_strViewPssiClickeUID == strSeriesId)
			strPrefix = "          * ";

		vecSeries.push_back(strPrefix + "Series - BodyPart : " + strBodyPart + ", Modality : " + strModality);

		vector<CString> vecImage = GetCtImageDetail(strSeriesId);
		for (int i = 0; i < vecImage.size(); i ++)
		{
			vecSeries.push_back(vecImage[i]);
		}

		dbrs.MoveNext();
	}
	dbrs.Close();



	return vecSeries;
}

vector<CString> CTinySMMSDlg::GetCtImageDetail( const CString& strSeriesId )
{
	vector<CString> vecImage;
	CString strSql;

	strSql = "SELECT Id, ImageType, TotalSliceCount, FolderPath FROM CaptureImage WHERE SeriesId = '" + strSeriesId + "'";

	CADORecordset dbrs(m_pDBConn);
	if(!dbrs.Open((LPCTSTR)strSql)) 
	{
		AfxMessageBox(dbrs.GetLastErrorString());
		return vecImage;
	}


	CString strId, strImageType, strFolderPath;
	int nSliceCount, nSliceThickness;
	while(!dbrs.IsEOF())
	{
		dbrs.GetFieldValue("Id", strId);
		dbrs.GetFieldValue("ImageType", strImageType);
		dbrs.GetFieldValue("TotalSliceCount", nSliceCount);
		//dbrs.GetFieldValue("SliceThickness", nSliceThickness);
		dbrs.GetFieldValue("FolderPath", strFolderPath);

		CString strPrefix = "                ";
		if (m_nViewPssiClickedType == WM_MSG_QUERY_IMAGE && m_strViewPssiClickeUID == strId)
			strPrefix = "              * ";

		CString strLine;
		strLine.Format(strPrefix + "Image - ImageType : %s, SliceCount : %d, FolderPath : %s", strImageType, nSliceCount, strFolderPath);
		vecImage.push_back(strLine);

		dbrs.MoveNext();
	}
	dbrs.Close();



	return vecImage;
}

void CTinySMMSDlg::SwitchButtonLocation(int nId1, int nId2)
{
	CWnd* pBtn1 = GetDlgItem(nId1);
	CWnd* pBtn2 = GetDlgItem(nId2);

	CRect rect1, rect2;

	// Get screen coordinates
	pBtn1->GetWindowRect(&rect1);
	pBtn2->GetWindowRect(&rect2);

	// Convert to client coordinates
	ScreenToClient(&rect1);
	ScreenToClient(&rect2);

	// Swap positions
	pBtn1->MoveWindow(rect2);
	pBtn2->MoveWindow(rect1);
}

vector<CString> CTinySMMSDlg::GetReconTemplateList( CString strScanId )
{
	vector<CString> vecReconList;
	CString strSql;

	strSql = "SELECT Id, UniqueName FROM ReconTemplate WHERE ScanTemplateId = '" + strScanId + "'";

	CADORecordset dbrs(m_pDBConn);
	if(!dbrs.Open((LPCTSTR)strSql)) 
	{
		AfxMessageBox(dbrs.GetLastErrorString());
		return vecReconList;
	}


	CString strCtReconId, strUniqueName;
	while(!dbrs.IsEOF())
	{
		dbrs.GetFieldValue("Id", strCtReconId);
		dbrs.GetFieldValue("UniqueName", strUniqueName);

		CString strPrefix = "        ";
		if ( m_strCurrentTable.CompareNoCase("ReconTemplate") == 0 && m_strCtDetailId == strCtReconId)
			strPrefix = "      * ";

		CString strLine;
		strLine.Format("%sRecon - Name : %s", strPrefix, strUniqueName);
		vecReconList.push_back(strLine);

		dbrs.MoveNext();
	}
	dbrs.Close();

	return vecReconList;	
}

vector<CString> CTinySMMSDlg::GetCtProtolDetail( const CString& strProtocolId )
{
	vector<CString> vecDetail;

	CString strSql;
	strSql = "SELECT Category.Id, Category.Name, ProtocolTemplate.UniqueName FROM Category, ProtocolTemplate WHERE Category.Id = ProtocolTemplate.CategoryId AND ProtocolTemplate.Id = '" + strProtocolId + "'";

	CADORecordset dbrs(m_pDBConn);
	if(!dbrs.Open((LPCTSTR)strSql)) 
	{
		AfxMessageBox(dbrs.GetLastErrorString());
		return vecDetail;
	}

	CString strLine;
	CString strId, strCategoryName, strProtocolName;
	if(!dbrs.IsEOF())
	{
		dbrs.GetFieldValue("Id", strId);
		dbrs.GetFieldValue("Name", strCategoryName);
		dbrs.GetFieldValue("UniqueName", strProtocolName);

		strLine.Format("Category - Name : %s", strCategoryName);
		vecDetail.push_back(strLine);
		strLine.Format("Protocol - Name : %s", strProtocolName);
		vecDetail.push_back(strLine);
	}
	dbrs.Close();

	// Load Scan info
	strSql = "SELECT Id, UniqueName, PatientSize, ScanType FROM ScanTemplate WHERE ProtocolTemplateId = '" + strProtocolId + "'";

	if(!dbrs.Open((LPCTSTR)strSql)) 
	{
		AfxMessageBox(dbrs.GetLastErrorString());
		return vecDetail;
	}
	
	CString strScanId, strScanName;
	int nPatientSize, nScanType;
	while(!dbrs.IsEOF())
	{
		dbrs.GetFieldValue("Id", strScanId);
		dbrs.GetFieldValue("UniqueName", strScanName);
		dbrs.GetFieldValue("PatientSize", nPatientSize);
		dbrs.GetFieldValue("ScanType", nScanType);

		CString strPrefix = "    ";
		if ( m_strCurrentTable.CompareNoCase("ScanTemplate") == 0 && m_strCtDetailId == strScanId)
			strPrefix = "  * ";

		strLine.Format("%sScan - Name: %s, PatientSize: %d, ScanType : %d", strPrefix, strScanName, nPatientSize, nScanType);
		vecDetail.push_back(strLine);

		vector<CString> vecRecon = GetReconTemplateList(strScanId);
		for (int i = 0; i < vecRecon.size(); i ++)
		{
			vecDetail.push_back(vecRecon[i]);
		}

		dbrs.MoveNext();
	}
	dbrs.Close();

	return vecDetail;
}

BOOL CTinySMMSDlg::DeletePSSIForCt( int nType, const CString& strId )
{
	vector<CString> vecSqlList;

	if (nType == WM_MSG_DELETE_PATIENT)
	{
		vecSqlList.push_back("Delete CaptureImage from CaptureImage, Series, ProcedureStep, Study where CaptureImage.SeriesId = Series.Id and Series.ProcedureStepId = ProcedureStep.Id and ProcedureStep.StudyId = Study.Id and Study.PatientId = '" + strId + "'");
		vecSqlList.push_back("Delete Series from Series, ProcedureStep, Study where Series.ProcedureStepId = ProcedureStep.Id and ProcedureStep.StudyId = Study.Id and Study.PatientId = '" + strId + "'");
		vecSqlList.push_back("Delete ScanExecution from ScanExecution, ProcedureStep, Study where ScanExecution.ProcedureStepId = ProcedureStep.Id and ProcedureStep.StudyId = Study.Id and Study.PatientId = '" + strId + "'");
		vecSqlList.push_back("Delete ProcedureStep from ProcedureStep, Study where ProcedureStep.StudyId = Study.Id and Study.PatientId = '" + strId + "'");
		vecSqlList.push_back("Delete Study where Study.PatientId = '" + strId + "'");
		vecSqlList.push_back("Delete Patient where Id = '" + strId + "'");
	}
	else if (nType == WM_MSG_DELETE_STUDY)
	{
		vecSqlList.push_back("Delete CaptureImage from CaptureImage, Series, ProcedureStep where CaptureImage.SeriesId = Series.Id and Series.ProcedureStepId = ProcedureStep.Id and ProcedureStep.StudyId = '" + strId + "'");
		vecSqlList.push_back("Delete Series from Series, ProcedureStep where Series.ProcedureStepId = ProcedureStep.Id and ProcedureStep.StudyId = '" + strId + "'");
		vecSqlList.push_back("Delete ScanExecution from ScanExecution, ProcedureStep where ScanExecution.ProcedureStepId = ProcedureStep.Id and ProcedureStep.StudyId = '" + strId + "'");
		vecSqlList.push_back("Delete ProcedureStep where ProcedureStep.StudyId = '" + strId + "'");
		vecSqlList.push_back("Delete Study where Id = '" + strId + "'");
	}
	else if (nType == WM_MSG_DELETE_PROCEDURESTEP)
	{
		vecSqlList.push_back("Delete CaptureImage from CaptureImage, Series where CaptureImage.SeriesId = Series.Id and Series.ProcedureStepId = '" + strId + "'");
		vecSqlList.push_back("Delete Series where ProcedureStepId = '" + strId + "'");
		vecSqlList.push_back("Delete ScanExecution where ProcedureStepId = '" + strId + "'");
		vecSqlList.push_back("Delete ProcedureStep where Id = '" + strId + "'");	
	}
	else if (nType == WM_MSG_DELETE_SERIES)
	{
		vecSqlList.push_back("Delete CaptureImage where SeriesId = '" + strId + "'");
		vecSqlList.push_back("Delete Series where Id = '" + strId + "'");
	}
	else if (nType == WM_MSG_DELETE_IMAGE)
	{
		vecSqlList.push_back("Delete CaptureImage where Id = '" + strId + "'");
	}

	return m_pDBConn->RunTransaction(vecSqlList);
}

CString CTinySMMSDlg::GetProtocolTemplateIdFromScanId( const CString& strScanId )
{
	CString strSql;

	strSql = "SELECT ProtocolTemplateId FROM ScanTemplate WHERE Id = '" + strScanId + "'";

	CADORecordset dbrs(m_pDBConn);
	if(!dbrs.Open((LPCTSTR)strSql)) 
	{
		AfxMessageBox(dbrs.GetLastErrorString());
		return "";
	}

	CString strId;
	if(!dbrs.IsEOF())
	{
		dbrs.GetFieldValue("ProtocolTemplateId", strId);
	}
	dbrs.Close();

	return strId;	
}


void CTinySMMSDlg::OnBnDoubleclickedButtonPatient()
{
	OnForceRefresh("Patient");
}

void CTinySMMSDlg::OnForceRefresh(const CString& strTableName)
{
	ChangeCurrentTable(strTableName);
	RunSQL("SELECT * FROM [" + m_strCurrentTable + "]",TRUE);
}

void CTinySMMSDlg::OnBnDoubleclickedButtonStudy()
{
	OnForceRefresh("Study");
}


void CTinySMMSDlg::OnBnDoubleclickedButtonSeries()
{
	OnForceRefresh("Series");
}


void CTinySMMSDlg::OnBnDoubleclickedButtonImage()
{
	if (m_nProductType == PRODUCT_IS)
	{
		OnForceRefresh("Image");
	}
	else
	{
		OnForceRefresh("CaptureImage");
	}
}


void CTinySMMSDlg::OnBnDoubleclickedButtonSms1()
{
	if (m_nProductType == PRODUCT_IS)
	{
		OnForceRefresh("SMS");
	}
	else
	{
		OnForceRefresh("ProcedureStep");
	}
}


void CTinySMMSDlg::OnBnDoubleclickedButtonWmlorder()
{
	if (m_nProductType == PRODUCT_IS)
	{
		OnForceRefresh("MWLOrder");
	}
	else
	{
		OnForceRefresh("ProtocolTemplate");
	}
}


void CTinySMMSDlg::OnBnDoubleclickedButtonMwlview()
{
	if (m_nProductType == PRODUCT_IS)
	{
		OnForceRefresh("MWLView");
	}
	else
	{
		OnForceRefresh("ScanTemplate");
	}
}


void CTinySMMSDlg::OnBnDoubleclickedButtonUserProfile()
{
	if (m_nProductType == PRODUCT_IS)
	{
		OnForceRefresh("UserProfile");
	}
	else
	{
		OnForceRefresh("ReconTemplate");
	}
}


void CTinySMMSDlg::OnBnDoubleclickedButtonRoleProfile()
{
	if (m_nProductType == PRODUCT_IS)
	{
		OnForceRefresh("RoleProfile");
	}
	else
	{
		OnForceRefresh("ScanParamTemplate");
	}
}


void CTinySMMSDlg::OnBnDoubleclickedButtonSystemProfile()
{
	if (m_nProductType == PRODUCT_IS)
	{
		OnForceRefresh("SystemProfile");
	}
	else
	{
		OnForceRefresh("ReconParamTemplate");
	}
}


void CTinySMMSDlg::OnBnDoubleclickedButtonSystemInfo()
{
	LoadSystemInfo();
}

CString CTinySMMSDlg::ReorderColumn( const CString& strTableName, const CString& strColumnOrder )
{
	if (m_nProductType == PRODUCT_IS)
		return strColumnOrder;

	CString newOrder;
	if (strTableName.CompareNoCase("Patient") == 0)
		newOrder = "0;6;10;1;2;3;4;5;7;8;9;";
	else if (strTableName.CompareNoCase("Study") == 0)
		newOrder = "0;1;12;14;4;2;3;5;6;7;8;9;10;11;13;";
	else
		return strColumnOrder;

	return  newOrder + strColumnOrder.Right(strColumnOrder.GetLength() - newOrder.GetLength());
}

void CTinySMMSDlg::AutoFitWidth()
{
	int nFieldCount = m_pCurrentList->m_ctrlHeader.GetItemCount();

	m_pCurrentList->SetRedraw(FALSE);
	m_pCurrentList->m_ctrlHeader.SetRedraw(FALSE);

	// Step 1: autosize all columns
	int totalWidth = 0;
	for (int i = 0; i < nFieldCount; ++i)
	{
		m_pCurrentList->SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
		totalWidth += m_pCurrentList->GetColumnWidth(i);
	}

	// Step 2: get client width
	CRect rect;
	m_pCurrentList->GetClientRect(&rect);
	int clientWidth = rect.Width();

	// Step 3: if there is extra space ¡ú expand last column
	if (totalWidth < clientWidth)
	{
		int lastCol = nFieldCount - 1;
		int lastWidth = m_pCurrentList->GetColumnWidth(lastCol);

		m_pCurrentList->SetColumnWidth(lastCol, lastWidth + (clientWidth - totalWidth));
	}
	m_pCurrentList->SetRedraw(TRUE);
	m_pCurrentList->m_ctrlHeader.SetRedraw(TRUE);
	m_pCurrentList->Invalidate(FALSE);
}

void CTinySMMSDlg::SetActiveButton( CColorButton* pButton )
{
	if (m_pActiveButton)
	{
		m_pActiveButton->m_textColor = RGB(0, 0, 0);
		m_pActiveButton->Invalidate(FALSE);
	}

	m_pActiveButton = pButton;
	if (m_pActiveButton)
	{
		m_pActiveButton->m_textColor = RGB(255, 0, 0);
		m_pActiveButton->Invalidate(FALSE);
	}
}

void CTinySMMSDlg::CreateMapForButton()
{
	// Common tables
	if (m_nProductType != PRODUCT_OTHER) 
	{
		m_mapTableButton["Patient"] = &m_btnPatient;
		m_mapTableButton["Study"]   = &m_btnStudy;
		m_mapTableButton["Series"]  = &m_btnSeries;
	}

	// PRODUCT_IS
	if (m_nProductType == PRODUCT_IS)
	{
		m_mapTableButton["Image"]         = &m_btnImage;
		m_mapTableButton["MwlOrder"]      = &m_btnMwlOrder;
		m_mapTableButton["MwlView"]       = &m_btnMwlView;
		m_mapTableButton["SMS"]           = &m_btnSms;
		m_mapTableButton["UserProfile"]   = &m_btnUserProfile;
		m_mapTableButton["RoleProfile"]   = &m_btnRoleProfile;
		m_mapTableButton["SystemProfile"] = &m_btnSystemProfile;
	}
	else if (m_nProductType == PRODUCT_IV)
	{
		m_mapTableButton["CaptureImage"]  = &m_btnImage;
		m_mapTableButton["ProcedureStep"] = &m_btnSms;
		m_mapTableButton["MwlOrder"]      = &m_btnMwlOrder;
		m_mapTableButton["MwlView"]       = &m_btnMwlView;
		m_mapTableButton["UserProfile"]   = &m_btnUserProfile;
		m_mapTableButton["RoleProfile"]   = &m_btnRoleProfile;
		m_mapTableButton["SystemProfile"] = &m_btnSystemProfile;
	}
	else if (m_nProductType == PRODUCT_CT)
	{
		m_mapTableButton["CaptureImage"]       = &m_btnImage;
		m_mapTableButton["ProcedureStep"]      = &m_btnSms;
		m_mapTableButton["ProtocolTemplate"]   = &m_btnMwlOrder;
		m_mapTableButton["ScanTemplate"]       = &m_btnMwlView;
		m_mapTableButton["ReconTemplate"]      = &m_btnUserProfile;
		m_mapTableButton["ScanParamTemplate"]  = &m_btnRoleProfile;
		m_mapTableButton["ReconParamTemplate"] = &m_btnSystemProfile;
	}
}
