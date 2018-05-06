// PaBezier2015MFC.h : main header file for the PABEZIER2015MFC application
//

#if !defined(AFX_PABEZIER2015MFC_H__98BA1927_84CC_4871_AE1E_AC3E79D8BE10__INCLUDED_)
#define AFX_PABEZIER2015MFC_H__98BA1927_84CC_4871_AE1E_AC3E79D8BE10__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPaBezier2015MFCApp:
// See PaBezier2015MFC.cpp for the implementation of this class
//

class CPaBezier2015MFCApp : public CWinApp
{
public:
	CPaBezier2015MFCApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPaBezier2015MFCApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

public:
	//{{AFX_MSG(CPaBezier2015MFCApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PABEZIER2015MFC_H__98BA1927_84CC_4871_AE1E_AC3E79D8BE10__INCLUDED_)
