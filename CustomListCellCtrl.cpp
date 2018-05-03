#include "stdafx.h"
#include "CustomListCellCtrl.h"


/////////////////////////////////////////////////////////////////////////////
// CFilterEdit

CFilterEdit::CFilterEdit()
{
	m_bNotifySent=FALSE;
}

CFilterEdit::~CFilterEdit()
{
}


BEGIN_MESSAGE_MAP(CFilterEdit, CEdit)
	//{{AFX_MSG_MAP(CFilterSortHeaderCtrl::CFilterEdit)
	ON_WM_KILLFOCUS()
	ON_WM_CHAR()
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFilterEdit message handlers

void CFilterEdit::OnRButtonUp(UINT nFlags, CPoint point)
{
	return CEdit::OnRButtonUp(nFlags, point);
}

void CFilterEdit::OnKillFocus(CWnd* pNewWnd) 
{
	CEdit::OnKillFocus(pNewWnd);

	if (!m_bNotifySent)
	{
		m_bNotifySent=TRUE;

		(GetParent())->SendMessage(FLM_EDITTEXTCHANGED,TRUE,0);
	}
}

void CFilterEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default

	if ((m_strValidChars.IsEmpty()) || ((-1 != m_strValidChars.Find(static_cast<TCHAR> (nChar))) || 
		(nChar == VK_BACK) || (nChar == CTRL_C) || (nChar == CTRL_V) || (nChar == CTRL_X)))
	{
		CEdit::OnChar(nChar, nRepCnt, nFlags);
	}
	else
	{
		MessageBeep(MB_ICONEXCLAMATION);
		return;
	}
}

void CFilterEdit::SetValidChars(CString& rstrValidChars)
{
	m_strValidChars = rstrValidChars;	
}

void CFilterEdit::PostNcDestroy()
{
	delete this;
}



BOOL CFilterEdit::PreTranslateMessage(MSG* pMsg) 
{
	BOOL bRetVal=FALSE;

	if (pMsg->message==WM_KEYDOWN)
	{
		if (pMsg->wParam==13) // Enter - input is ok
		{
			m_bNotifySent=TRUE;

			(GetParent())->SendMessage(FLM_EDITTEXTCHANGED,TRUE,0);

			bRetVal=TRUE;
		}
		if (pMsg->wParam==27) // ESCAPE - ignore input
		{
			m_bNotifySent=TRUE;

			(GetParent())->SendMessage(FLM_EDITTEXTCHANGED,FALSE,0);

			bRetVal=TRUE;
		}
	}

	if (!bRetVal)
		bRetVal=CEdit::PreTranslateMessage(pMsg);

	return bRetVal;
}
// End of CFilterEdit
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// CFilterCombo

CFilterCombo::CFilterCombo()
{
	m_bNotifySent=FALSE;
	m_bDropdown = FALSE;
}

CFilterCombo::~CFilterCombo()
{
}


BEGIN_MESSAGE_MAP(CFilterCombo, CComboBox)
	//{{AFX_MSG_MAP(CFilterSortHeaderCtrl::CFilterCombo)
	ON_WM_KILLFOCUS()
	ON_CONTROL_REFLECT(CBN_CLOSEUP, CFilterCombo::OnCloseup)
	ON_CONTROL_REFLECT(CBN_SELCHANGE, &CFilterCombo::OnSelectChanged)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
////CFilterCombo message handlers

void CFilterCombo::OnCloseup() 
{
	// Set the focus to the parent list control
	if (!m_bNotifySent)
	{
		m_bNotifySent=TRUE;

		(GetParent())->SendMessage(FLM_COMBOSELCHANGED,TRUE,0);
	}

	//	GetParent()->SetFocus();
	//	int i = 0;123456

}

void CFilterCombo::OnSelectChanged() 
{
	// Set the focus to the parent list control
	if (!m_bNotifySent)
	{
		m_bNotifySent=TRUE;

		(GetParent())->SendMessage(FLM_COMBOSELCHANGED,TRUE,0);
	}

	//	GetParent()->SetFocus();
	//	int i = 0;123456

}

void CFilterCombo::OnKillFocus(CWnd* pNewWnd) 
{
	CComboBox::OnKillFocus(pNewWnd);
	if (!m_bNotifySent)
	{
		m_bNotifySent=TRUE;

		(GetParent())->SendMessage(FLM_COMBOSELCHANGED,TRUE,0);
	}
}

void CFilterCombo::PostNcDestroy()
{
	delete this;
}

BOOL CFilterCombo::PreTranslateMessage(MSG* pMsg)
{
	BOOL bRetVal=FALSE;

	if (pMsg->message==WM_KEYDOWN)
	{
		if (pMsg->wParam==13) // Enter - input is ok
		{
			m_bNotifySent=TRUE;

			(GetParent())->SendMessage(FLM_COMBOSELCHANGED,TRUE,0);

			bRetVal=TRUE;
		}
		if (pMsg->wParam==27) // ESCAPE - ignore input
		{
			m_bNotifySent=TRUE;

			(GetParent())->SendMessage(FLM_COMBOSELCHANGED,FALSE,0);

			bRetVal=TRUE;
		}
	}

	if (!bRetVal)
		bRetVal=CComboBox::PreTranslateMessage(pMsg);

	return bRetVal;
}