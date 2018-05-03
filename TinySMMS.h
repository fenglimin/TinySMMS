// TinySMMS.h : main header file for the TINYSMMS application
//

#if !defined(AFX_TINYSMMS_H__AAD33DAA_5A33_422C_8102_433A5A4E4929__INCLUDED_)
#define AFX_TINYSMMS_H__AAD33DAA_5A33_422C_8102_433A5A4E4929__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTinySMMSApp:
// See TinySMMS.cpp for the implementation of this class
//

class CTinySMMSApp : public CWinApp
{
public:
	CTinySMMSApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTinySMMSApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTinySMMSApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TINYSMMS_H__AAD33DAA_5A33_422C_8102_433A5A4E4929__INCLUDED_)
