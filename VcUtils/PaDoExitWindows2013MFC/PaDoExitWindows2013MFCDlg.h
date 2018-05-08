// PaDoExitWindows2013MFCDlg.h : header file
//

#if !defined(AFX_PADOEXITWINDOWS2013MFCDLG_H__E8971F1D_35B0_4B72_B4F1_22E8312349B6__INCLUDED_)
#define AFX_PADOEXITWINDOWS2013MFCDLG_H__E8971F1D_35B0_4B72_B4F1_22E8312349B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPaDoExitWindows2013MFCDlg dialog

class CPaDoExitWindows2013MFCDlg : public CDialog
{
// Construction
public:
	void PA_OnDoScreenoff();
	BOOL PA_DoLockWorkStation();
	BOOL PA_OpenShutdownProcessToken();
	void PA_EnabledButtons(BOOL isEnabled);
	UINT uFlagsExtra;
	void PA_InitDialog();
	OSVERSIONINFO osvi;
	DWORD dwPlatformId;
	void PA_AlertInfo(LPCTSTR szInfo);
	BOOL PA_Confirm(LPCTSTR szInfo);
	void PA_DoExitWindowsEx(DWORD dwPlatformId, UINT uFlags, UINT uFlagsExtra);
	CPaDoExitWindows2013MFCDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPaDoExitWindows2013MFCDlg)
	enum { IDD = IDD_PADOEXITWINDOWS2013MFC_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPaDoExitWindows2013MFCDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPaDoExitWindows2013MFCDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDoLogoff();
	afx_msg void OnDoPoweroff();
	afx_msg void OnDoReboot();
	afx_msg void OnDoShutdown();
	afx_msg void OnOptSafe();
	afx_msg void OnOptForce();
	afx_msg void OnOptRisk();
	afx_msg void OnDoSuspend();
	afx_msg void OnDoScreenoff();
	afx_msg void OnDoHibernate();
	afx_msg void OnDoLockWorkstation();
	afx_msg void OnDoScreenoffLock();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PADOEXITWINDOWS2013MFCDLG_H__E8971F1D_35B0_4B72_B4F1_22E8312349B6__INCLUDED_)
