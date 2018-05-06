// PaOpenGLTest01MFC.h : main header file for the PAOPENGLTEST01MFC application
//

#if !defined(AFX_PAOPENGLTEST01MFC_H__AFD649F6_E0D1_48B3_8C54_430E19FF39A4__INCLUDED_)
#define AFX_PAOPENGLTEST01MFC_H__AFD649F6_E0D1_48B3_8C54_430E19FF39A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPaOpenGLTest01MFCApp:
// See PaOpenGLTest01MFC.cpp for the implementation of this class
//

class CPaOpenGLTest01MFCApp : public CWinApp
{
public:
	CPaOpenGLTest01MFCApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPaOpenGLTest01MFCApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CPaOpenGLTest01MFCApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAOPENGLTEST01MFC_H__AFD649F6_E0D1_48B3_8C54_430E19FF39A4__INCLUDED_)
