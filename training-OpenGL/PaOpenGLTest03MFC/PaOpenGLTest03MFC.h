// PaOpenGLTest03MFC.h : main header file for the PAOPENGLTEST03MFC application
//

#if !defined(AFX_PAOPENGLTEST03MFC_H__E36092BC_12F2_4EE1_892F_C7DCD59E9028__INCLUDED_)
#define AFX_PAOPENGLTEST03MFC_H__E36092BC_12F2_4EE1_892F_C7DCD59E9028__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPaOpenGLTest03MFCApp:
// See PaOpenGLTest03MFC.cpp for the implementation of this class
//

class CPaOpenGLTest03MFCApp : public CWinApp
{
public:
	CPaOpenGLTest03MFCApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPaOpenGLTest03MFCApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CPaOpenGLTest03MFCApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAOPENGLTEST03MFC_H__E36092BC_12F2_4EE1_892F_C7DCD59E9028__INCLUDED_)
