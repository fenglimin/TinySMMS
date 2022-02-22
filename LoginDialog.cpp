// LoginDialog.cpp : implementation file
//

#include "stdafx.h"
#include "TinySMMS.h"
#include "LoginDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoginDialog dialog


CLoginDialog::CLoginDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginDialog::IDD, pParent)
	, m_strProvider(_T(""))
{
	//{{AFX_DATA_INIT(CLoginDialog)
	m_strDatabase = _T("");
	m_strServerName = _T("");
	m_strUserName = _T("");
	//}}AFX_DATA_INIT

	m_pDBConn = new CADODatabase;
}

void CLoginDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoginDialog)
	DDX_Control(pDX, IDC_COMBO_PASSWORD, m_comPassword);
	DDX_Text(pDX, IDC_EDIT_DATABASE, m_strDatabase);
	DDX_Text(pDX, IDC_EDIT_SERVERNAME, m_strServerName);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_strUserName);
	DDX_Text(pDX, IDC_EDIT_PROVIDER, m_strProvider);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLoginDialog, CDialog)
	//{{AFX_MSG_MAP(CLoginDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoginDialog message handlers

void CLoginDialog::OnOK() 
{
	m_comPassword.GetLBText(m_comPassword.GetCurSel(), m_strPassword);
	UpdateData();

	CString strDbConnStr = "Password=" + m_strPassword +
					 ";Provider=" + m_strProvider + 
					 ";Data Source=" + m_strServerName +
					 ";Initial Catalog=" + m_strDatabase +
					 ";User ID=" + m_strUserName + ";ole db services = -2;";
	
	
	if(!DoLogin(FALSE))
	{
		if (m_strProvider == "SQLNCLI10")
		{
			m_strProvider = "SQLNCLI11";
			DoLogin(TRUE);	
		}
		else if (m_strProvider == "SQLNCLI11")
		{
			m_strProvider = "SQLNCLI10";
			DoLogin(TRUE);
		}
		else
		{
			return;	
		}		
	}
	
	CDialog::OnOK();
}

BOOL CLoginDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_strServerName = "localhost\\GCPACSWS";
	m_strDatabase = "WGGC";
	m_strUserName = "pdchi";
	m_strProvider = "SQLNCLI10";

	m_comPassword.SetCurSel(0);
	
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CLoginDialog::DoLogin(BOOL bStopIfFailed)
{
	CString strDbConnStr = "Password=" + m_strPassword +
		";Provider=" + m_strProvider + 
		";Data Source=" + m_strServerName +
		";Initial Catalog=" + m_strDatabase +
		";User ID=" + m_strUserName + ";ole db services = -2;";

	if (m_pDBConn->Open(strDbConnStr, "", "", !bStopIfFailed))
	{
		return TRUE;
	}

	if (bStopIfFailed)
	{
		AfxMessageBox("Can't open Database!(" + strDbConnStr + ")");
	}

	return FALSE;
}