// PaDoExitWindows2013MFC.h : main header file for the PADOEXITWINDOWS2013MFC application
//

#if !defined(AFX_PADOEXITWINDOWS2013MFC_H__6E513078_04A8_4E5A_B234_5B3B6E23E0B6__INCLUDED_)
#define AFX_PADOEXITWINDOWS2013MFC_H__6E513078_04A8_4E5A_B234_5B3B6E23E0B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPaDoExitWindows2013MFCApp:
// See PaDoExitWindows2013MFC.cpp for the implementation of this class
//

class CPaDoExitWindows2013MFCApp : public CWinApp
{
public:
	CPaDoExitWindows2013MFCApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPaDoExitWindows2013MFCApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPaDoExitWindows2013MFCApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PADOEXITWINDOWS2013MFC_H__6E513078_04A8_4E5A_B234_5B3B6E23E0B6__INCLUDED_)
