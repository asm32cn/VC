// PaCalculator2016MFCDlg.h : header file
//

#if !defined(AFX_PACALCULATOR2016MFCDLG_H__3417AB93_D3AE_4C19_B84F_26346970818A__INCLUDED_)
#define AFX_PACALCULATOR2016MFCDLG_H__3417AB93_D3AE_4C19_B84F_26346970818A__INCLUDED_

#include "LayoutManager.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPaCalculator2016MFCDlg dialog

class CPaCalculator2016MFCDlg : public CDialog
{
// Construction
public:
	CPaCalculator2016MFCDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPaCalculator2016MFCDlg)
	enum { IDD = IDD_PACALCULATOR2016MFC_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPaCalculator2016MFCDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void Do_InitUI();
	CEdit * m_pDisplay;
	Win32Layout::Box m_layout;
	HICON m_hIcon;
	CButton * A_pKeys[18];

	// Generated message map functions
	//{{AFX_MSG(CPaCalculator2016MFCDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PACALCULATOR2016MFCDLG_H__3417AB93_D3AE_4C19_B84F_26346970818A__INCLUDED_)
