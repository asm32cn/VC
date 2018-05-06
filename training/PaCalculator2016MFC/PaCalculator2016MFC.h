// PaCalculator2016MFC.h : main header file for the PACALCULATOR2016MFC application
//

#if !defined(AFX_PACALCULATOR2016MFC_H__CB052ED7_BFB3_42A7_9C48_022980BD36FC__INCLUDED_)
#define AFX_PACALCULATOR2016MFC_H__CB052ED7_BFB3_42A7_9C48_022980BD36FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPaCalculator2016MFCApp:
// See PaCalculator2016MFC.cpp for the implementation of this class
//

class CPaCalculator2016MFCApp : public CWinApp
{
public:
	CPaCalculator2016MFCApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPaCalculator2016MFCApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPaCalculator2016MFCApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PACALCULATOR2016MFC_H__CB052ED7_BFB3_42A7_9C48_022980BD36FC__INCLUDED_)
