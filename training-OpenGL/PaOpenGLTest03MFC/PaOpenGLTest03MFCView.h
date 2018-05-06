// PaOpenGLTest03MFCView.h : interface of the CPaOpenGLTest03MFCView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PAOPENGLTEST03MFCVIEW_H__1ACBF1B0_470D_441B_805A_F0B9AEE07FEF__INCLUDED_)
#define AFX_PAOPENGLTEST03MFCVIEW_H__1ACBF1B0_470D_441B_805A_F0B9AEE07FEF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CPaOpenGLTest03MFCView : public CView
{
protected: // create from serialization only
	CPaOpenGLTest03MFCView();
	DECLARE_DYNCREATE(CPaOpenGLTest03MFCView)

// Attributes
public:
	CPaOpenGLTest03MFCDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPaOpenGLTest03MFCView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPaOpenGLTest03MFCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	CPoint m_RightDownPos; // Initialize to (0,0)
	CPoint m_LeftDownPos; // Initialize to (0,0)
	BOOL m_RightButtonDown; // Initialize to FALSE
	BOOL m_LeftButtonDown; // Initialize to FALSE
	HGLRC m_hGLContext;
	BOOL CreateViewGLContext(HDC hDC);
	int m_GLPixelIndex;
	//{{AFX_MSG(CPaOpenGLTest03MFCView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL SetWindowPixelFormat(HDC hDC);
};

#ifndef _DEBUG  // debug version in PaOpenGLTest03MFCView.cpp
inline CPaOpenGLTest03MFCDoc* CPaOpenGLTest03MFCView::GetDocument()
   { return (CPaOpenGLTest03MFCDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAOPENGLTEST03MFCVIEW_H__1ACBF1B0_470D_441B_805A_F0B9AEE07FEF__INCLUDED_)
