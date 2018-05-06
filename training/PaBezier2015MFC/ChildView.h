// ChildView.h : interface of the CChildView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDVIEW_H__6CFC7312_E1AD_4CD8_A523_E928623AB8B2__INCLUDED_)
#define AFX_CHILDVIEW_H__6CFC7312_E1AD_4CD8_A523_E928623AB8B2__INCLUDED_

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
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	UINT m_nTimerID;
	void PA_DoSwitchTimer();
	CPen m_cPen1;
	CPen m_cPen2;
	RECT m_rectClient;
	CBrush m_cbrBackground;
	void PA_DoBezierDisplay();
	void PA_DoBezierMove();
	WORD m_nClientWidth;
	WORD m_nClientHeight;
	void PA_DoBezierInit();
	POINT pts[10];
	POINT ptbs[10];
	POINT ptds[10];
	INT pts_nCount;
	INT ptds_nMin;
	INT ptds_nRange;
	void PA_DoWindowInitialize();
	virtual ~CChildView();

	// Generated message map functions
protected:
	//{{AFX_MSG(CChildView)
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSwitchStart();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDVIEW_H__6CFC7312_E1AD_4CD8_A523_E928623AB8B2__INCLUDED_)
