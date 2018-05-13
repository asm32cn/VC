// PaGetScreenColor2011Dlg.h : header file
//

#if !defined(AFX_PaGetScreenColor2011DLG_H__88839FE8_0D62_49B9_A91C_43EA8AB7AC5A__INCLUDED_)
#define AFX_PaGetScreenColor2011DLG_H__88839FE8_0D62_49B9_A91C_43EA8AB7AC5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPaGetScreenColor2011Dlg dialog

class CPaGetScreenColor2011Dlg : public CDialog
{
// Construction
public:
	COLORREF m_sysColor;
	void GetScreenColorXY(INT x,INT y);
	CPaGetScreenColor2011Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPaGetScreenColor2011Dlg)
	enum { IDD = IDD_PaGetScreenColor2011_DIALOG };
	CStatic	m_wndDisplay;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPaGetScreenColor2011Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CBrush br;
	RECT m_rectDisplay;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPaGetScreenColor2011Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PaGetScreenColor2011DLG_H__88839FE8_0D62_49B9_A91C_43EA8AB7AC5A__INCLUDED_)
