// PaGetScreenColor2011.h : main header file for the PaGetScreenColor2011 application
//

#if !defined(AFX_PaGetScreenColor2011_H__7D1FB723_41AE_4AAB_951C_CC5ADC365DB8__INCLUDED_)
#define AFX_PaGetScreenColor2011_H__7D1FB723_41AE_4AAB_951C_CC5ADC365DB8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPaGetScreenColor2011App:
// See PaGetScreenColor2011.cpp for the implementation of this class
//

class CPaGetScreenColor2011App : public CWinApp
{
public:
	CPaGetScreenColor2011App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPaGetScreenColor2011App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPaGetScreenColor2011App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PaGetScreenColor2011_H__7D1FB723_41AE_4AAB_951C_CC5ADC365DB8__INCLUDED_)
