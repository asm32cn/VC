// LinearGradientBrush.h : main header file for the LINEARGRADIENTBRUSH application
//

#if !defined(AFX_LINEARGRADIENTBRUSH_H__DB74ABB0_B57E_4C6C_B21C_CF78A8464138__INCLUDED_)
#define AFX_LINEARGRADIENTBRUSH_H__DB74ABB0_B57E_4C6C_B21C_CF78A8464138__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CLinearGradientBrushApp:
// See LinearGradientBrush.cpp for the implementation of this class
//

class CLinearGradientBrushApp : public CWinApp
{
public:
	CLinearGradientBrushApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLinearGradientBrushApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CLinearGradientBrushApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LINEARGRADIENTBRUSH_H__DB74ABB0_B57E_4C6C_B21C_CF78A8464138__INCLUDED_)
