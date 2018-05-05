// PaQix2015MFC.h : main header file for the PAQIX2015MFC application
//

#if !defined(AFX_PAQIX2015MFC_H__5A36ADC6_F211_46F7_B3C7_6704615293D9__INCLUDED_)
#define AFX_PAQIX2015MFC_H__5A36ADC6_F211_46F7_B3C7_6704615293D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPaQix2015MFCApp:
// See PaQix2015MFC.cpp for the implementation of this class
//

class CPaQix2015MFCApp : public CWinApp
{
public:
	CPaQix2015MFCApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPaQix2015MFCApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

public:
	//{{AFX_MSG(CPaQix2015MFCApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAQIX2015MFC_H__5A36ADC6_F211_46F7_B3C7_6704615293D9__INCLUDED_)
