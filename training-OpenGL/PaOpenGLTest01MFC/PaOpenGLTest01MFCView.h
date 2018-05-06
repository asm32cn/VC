// PaOpenGLTest01MFCView.h : interface of the CPaOpenGLTest01MFCView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PAOPENGLTEST01MFCVIEW_H__BDE1E43A_A285_441B_866F_6988835C21A6__INCLUDED_)
#define AFX_PAOPENGLTEST01MFCVIEW_H__BDE1E43A_A285_441B_866F_6988835C21A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CPaOpenGLTest01MFCView : public CView
{
protected: // create from serialization only
	CPaOpenGLTest01MFCView();
	DECLARE_DYNCREATE(CPaOpenGLTest01MFCView)

// Attributes
public:
	CPaOpenGLTest01MFCDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPaOpenGLTest01MFCView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPaOpenGLTest01MFCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	HGLRC m_hGLContext;
	BOOL CreateViewGLContext(HDC hDC);
	int m_GLPixelIndex;
	BOOL SetWindowPixelFormat(HDC hDC);
	//{{AFX_MSG(CPaOpenGLTest01MFCView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in PaOpenGLTest01MFCView.cpp
inline CPaOpenGLTest01MFCDoc* CPaOpenGLTest01MFCView::GetDocument()
   { return (CPaOpenGLTest01MFCDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAOPENGLTEST01MFCVIEW_H__BDE1E43A_A285_441B_866F_6988835C21A6__INCLUDED_)
