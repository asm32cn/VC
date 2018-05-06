// PaOpenGLTest02MFCView.h : interface of the CPaOpenGLTest02MFCView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PAOPENGLTEST02MFCVIEW_H__1E228C24_719E_460C_8D34_5E412274CBB9__INCLUDED_)
#define AFX_PAOPENGLTEST02MFCVIEW_H__1E228C24_719E_460C_8D34_5E412274CBB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CPaOpenGLTest02MFCView : public CView
{
protected: // create from serialization only
	CPaOpenGLTest02MFCView();
	DECLARE_DYNCREATE(CPaOpenGLTest02MFCView)

// Attributes
public:
	CPaOpenGLTest02MFCDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPaOpenGLTest02MFCView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPaOpenGLTest02MFCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	HGLRC m_hGLContext;
	BOOL CreateViewGLContext(HDC hDC);
	//{{AFX_MSG(CPaOpenGLTest02MFCView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_GLPixelIndex;
	BOOL SetWindowPixelFormat(HDC hDC);
};

#ifndef _DEBUG  // debug version in PaOpenGLTest02MFCView.cpp
inline CPaOpenGLTest02MFCDoc* CPaOpenGLTest02MFCView::GetDocument()
   { return (CPaOpenGLTest02MFCDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAOPENGLTEST02MFCVIEW_H__1E228C24_719E_460C_8D34_5E412274CBB9__INCLUDED_)
