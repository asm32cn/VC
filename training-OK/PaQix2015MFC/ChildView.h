// ChildView.h : interface of the CChildView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDVIEW_H__95770658_DC56_465F_84A5_DE41700F3459__INCLUDED_)
#define AFX_CHILDVIEW_H__95770658_DC56_465F_84A5_DE41700F3459__INCLUDED_

#include "PaQixColor.h"	// Added by ClassView
#include "PaQixPoints.h"	// Added by ClassView

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
	INT m_nCount;
	INT m_nRangeD;
	INT m_nMinD;
	CPaQixPoints qps;
	CPaQixColor qc;
	virtual ~CChildView();

	// Generated message map functions
protected:
	RECT m_rectClient;
	CBrush m_brBackground;
	void PA_OnDisplay();
	int m_nClientHeight;
	int m_nClientWidth;
	void PA_DoWIndowFinalize();
	void PA_DoWindowInitialize();
	CBitmap m_bmpMemory;
	CDC m_cdcMemory;
	//{{AFX_MSG(CChildView)
	afx_msg void OnPaint();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSetHorizontal();
	afx_msg void OnSetRandom();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDVIEW_H__95770658_DC56_465F_84A5_DE41700F3459__INCLUDED_)
