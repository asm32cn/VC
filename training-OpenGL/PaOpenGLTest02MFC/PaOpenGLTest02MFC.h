// PaOpenGLTest02MFC.h : main header file for the PAOPENGLTEST02MFC application
//

#if !defined(AFX_PAOPENGLTEST02MFC_H__76AABD45_1067_4F14_AA87_99F76C1F5F84__INCLUDED_)
#define AFX_PAOPENGLTEST02MFC_H__76AABD45_1067_4F14_AA87_99F76C1F5F84__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPaOpenGLTest02MFCApp:
// See PaOpenGLTest02MFC.cpp for the implementation of this class
//

class CPaOpenGLTest02MFCApp : public CWinApp
{
public:
	CPaOpenGLTest02MFCApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPaOpenGLTest02MFCApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CPaOpenGLTest02MFCApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAOPENGLTEST02MFC_H__76AABD45_1067_4F14_AA87_99F76C1F5F84__INCLUDED_)
