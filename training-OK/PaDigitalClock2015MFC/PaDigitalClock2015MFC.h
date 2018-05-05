// PaDigitalClock2015MFC.h : main header file for the PADIGITALCLOCK2015MFC application
//

#if !defined(AFX_PADIGITALCLOCK2015MFC_H__81B24106_A313_4F79_BBF7_7E3C0AF93CFB__INCLUDED_)
#define AFX_PADIGITALCLOCK2015MFC_H__81B24106_A313_4F79_BBF7_7E3C0AF93CFB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPaDigitalClock2015MFCApp:
// See PaDigitalClock2015MFC.cpp for the implementation of this class
//

class CPaDigitalClock2015MFCApp : public CWinApp
{
public:
	CPaDigitalClock2015MFCApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPaDigitalClock2015MFCApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

public:
	//{{AFX_MSG(CPaDigitalClock2015MFCApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PADIGITALCLOCK2015MFC_H__81B24106_A313_4F79_BBF7_7E3C0AF93CFB__INCLUDED_)
