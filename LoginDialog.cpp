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
	m_pDBConn = new CADODatabase;
	m_nProductType = PRODUCT_IS;
}

void CLoginDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoginDialog)
	DDX_Text(pDX, IDC_EDIT_SERVERNAME, m_strServerName);
	DDX_Text(pDX, IDC_EDIT_DATABASE, m_strDatabase);
	DDX_Text(pDX, IDC_EDIT_PROVIDER, m_strProvider);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLoginDialog, CDialog)
	//{{AFX_MSG_MAP(CLoginDialog)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_RADIO_IS, &CLoginDialog::OnBnClickedRadioIs)
	ON_BN_CLICKED(IDC_RADIO_IV, &CLoginDialog::OnBnClickedRadioIv)
	ON_BN_CLICKED(IDC_RADIO_CT, &CLoginDialog::OnBnClickedRadioCt)
	ON_BN_CLICKED(IDC_RADIO_OTHER, &CLoginDialog::OnBnClickedRadioOther)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoginDialog message handlers

void CLoginDialog::OnOK() 
{	
	UpdateData();
	
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
	m_strProvider = "SQLOLEDB";

	((CButton*)GetDlgItem(IDC_RADIO_IS))->SetCheck(BST_CHECKED);

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CLoginDialog::DoLogin(BOOL bStopIfFailed)
{
	//CString strDbConnStr = "Password=" + m_strPassword +
	//	";Provider=" + m_strProvider + 
	//	";Data Source=" + m_strServerName +
	//	";Initial Catalog=" + m_strDatabase +
	//	";User ID=" + m_strUserName + ";ole db services = -2;";

	CString strDbConnStr = "Provider=" + m_strProvider + 
		";Data Source=" + m_strServerName +
		";Initial Catalog=" + m_strDatabase +
		";Trusted_Connection=Yes;";

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

void CLoginDialog::OnBnClickedRadioIs()
{
	SetProductType(PRODUCT_IS);
}


void CLoginDialog::OnBnClickedRadioIv()
{
	SetProductType(PRODUCT_IV);
}


void CLoginDialog::OnBnClickedRadioCt()
{
	SetProductType(PRODUCT_CT);
}


void CLoginDialog::OnBnClickedRadioOther()
{
	SetProductType(PRODUCT_OTHER);
}

void CLoginDialog::SetProductType(int nProductTypes)
{
	m_nProductType = nProductTypes;

	if (m_nProductType == PRODUCT_OTHER)
		return;

	if (m_nProductType == PRODUCT_IS)
	{
		m_strServerName = "localhost\\GCPACSWS";
		m_strDatabase = "WGGC";
	}
	else if (m_nProductType == PRODUCT_IV || m_nProductType == PRODUCT_CT)
	{
		m_strServerName = "localhost\\CARESTREAM";
		m_strDatabase = "CARESTREAM";
	}

	UpdateData(FALSE);
}