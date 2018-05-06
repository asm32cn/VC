// LinearGradientBrushDlg.h : header file
//

#if !defined(AFX_LINEARGRADIENTBRUSHDLG_H__7D19DDCD_27DA_4C57_9A8B_AEF7F2D0BC62__INCLUDED_)
#define AFX_LINEARGRADIENTBRUSHDLG_H__7D19DDCD_27DA_4C57_9A8B_AEF7F2D0BC62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CLinearGradientBrushDlg dialog

class CLinearGradientBrushDlg : public CDialog
{
// Construction
public:
	CLinearGradientBrushDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CLinearGradientBrushDlg)
	enum { IDD = IDD_LINEARGRADIENTBRUSH_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLinearGradientBrushDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CLinearGradientBrushDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LINEARGRADIENTBRUSHDLG_H__7D19DDCD_27DA_4C57_9A8B_AEF7F2D0BC62__INCLUDED_)
