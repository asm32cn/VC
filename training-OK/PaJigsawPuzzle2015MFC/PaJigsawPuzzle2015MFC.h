// PaJigsawPuzzle2015MFC.h : main header file for the PAJIGSAWPUZZLE2015MFC application
//

#if !defined(AFX_PAJIGSAWPUZZLE2015MFC_H__AEA75CC2_2FC6_4340_B64D_BBC56BF2670F__INCLUDED_)
#define AFX_PAJIGSAWPUZZLE2015MFC_H__AEA75CC2_2FC6_4340_B64D_BBC56BF2670F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPaJigsawPuzzle2015MFCApp:
// See PaJigsawPuzzle2015MFC.cpp for the implementation of this class
//

class CPaJigsawPuzzle2015MFCApp : public CWinApp
{
public:
	CPaJigsawPuzzle2015MFCApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPaJigsawPuzzle2015MFCApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

public:
	//{{AFX_MSG(CPaJigsawPuzzle2015MFCApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAJIGSAWPUZZLE2015MFC_H__AEA75CC2_2FC6_4340_B64D_BBC56BF2670F__INCLUDED_)
