// ChildView.h : interface of the CChildView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDVIEW_H__F3E7F174_6480_4A21_A3AF_990D3663C9AD__INCLUDED_)
#define AFX_CHILDVIEW_H__F3E7F174_6480_4A21_A3AF_990D3663C9AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CChildView window

class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildView)
	public:
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL m_isRefresh;
	WORD m_nClientWidth;
	WORD m_nClientHeight;
	void PA_DoClockDisplayChar(CDC &dc, INT nItem, INT nOffsetX, INT nOffsetY);
	INT m_nBmpCharsWidth;
	INT m_nBmpCharsHeight;
	INT m_nBmpCharWidth;
	INT m_nBmpCharHeight;
	void PA_DoClockDisplay();
	void PA_DoInitBitmapChars();
	CDC m_cdcChars;
	CBitmap m_bmpChars;
	void PA_DoWindowFinalize();
	SYSTEMTIME tmSystem;
	WORD A_wordMask[12];
	WORD * A_wordDigitMatrix;
	void PA_DoWindowInitialize();
	virtual ~CChildView();
	CHAR A_nCharID[12];
	CHAR A_nCharID_t[12];

	// Generated message map functions
protected:
	//{{AFX_MSG(CChildView)
	afx_msg void OnPaint();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDVIEW_H__F3E7F174_6480_4A21_A3AF_990D3663C9AD__INCLUDED_)
