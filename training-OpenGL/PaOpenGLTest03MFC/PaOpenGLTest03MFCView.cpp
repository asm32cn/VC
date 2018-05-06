// PaOpenGLTest03MFCView.cpp : implementation of the CPaOpenGLTest03MFCView class
//

#include "stdafx.h"
#include "PaOpenGLTest03MFC.h"

#include "PaOpenGLTest03MFCDoc.h"
#include "PaOpenGLTest03MFCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPaOpenGLTest03MFCView

IMPLEMENT_DYNCREATE(CPaOpenGLTest03MFCView, CView)

BEGIN_MESSAGE_MAP(CPaOpenGLTest03MFCView, CView)
	//{{AFX_MSG_MAP(CPaOpenGLTest03MFCView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPaOpenGLTest03MFCView construction/destruction

CPaOpenGLTest03MFCView::CPaOpenGLTest03MFCView()
{
	// TODO: add construction code here
	m_hGLContext = NULL;
	m_GLPixelIndex = 0;
}

CPaOpenGLTest03MFCView::~CPaOpenGLTest03MFCView()
{
}

BOOL CPaOpenGLTest03MFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style |= (WS_CLIPCHILDREN | WS_CLIPSIBLINGS);
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPaOpenGLTest03MFCView drawing

void CPaOpenGLTest03MFCView::OnDraw(CDC* pDC)
{
	CPaOpenGLTest03MFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CPaOpenGLTest03MFCView diagnostics

#ifdef _DEBUG
void CPaOpenGLTest03MFCView::AssertValid() const
{
	CView::AssertValid();
}

void CPaOpenGLTest03MFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPaOpenGLTest03MFCDoc* CPaOpenGLTest03MFCView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPaOpenGLTest03MFCDoc)));
	return (CPaOpenGLTest03MFCDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPaOpenGLTest03MFCView message handlers

BOOL CPaOpenGLTest03MFCView::SetWindowPixelFormat(HDC hDC)
{
	PIXELFORMATDESCRIPTOR pixelDesc;
	pixelDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pixelDesc.nVersion = 1;
	/*
	pixelDesc.dwFlags = PFD_DRAW_TO_WINDOW |
		PFD_DRAW_TO_BITMAP |
		PFD_SUPPORT_OPENGL |
		PFD_SUPPORT_GDI |
		PFD_STEREO_DONTCARE;
	*/
	pixelDesc.dwFlags = PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER |
		PFD_STEREO_DONTCARE;
	pixelDesc.iPixelType = PFD_TYPE_RGBA;
	pixelDesc.cColorBits = 32;
	pixelDesc.cRedBits = 8;
	pixelDesc.cRedShift = 16;
	pixelDesc.cGreenBits = 8;
	pixelDesc.cGreenShift = 8;
	pixelDesc.cBlueBits = 8;
	pixelDesc.cBlueShift = 0;
	pixelDesc.cAlphaBits = 0;
	pixelDesc.cAlphaShift = 0;
	pixelDesc.cAccumBits = 64;
	pixelDesc.cAccumRedBits = 16;
	pixelDesc.cAccumGreenBits = 16;
	pixelDesc.cAccumBlueBits = 16;
	pixelDesc.cAccumAlphaBits = 0;
	pixelDesc.cDepthBits = 32;
	pixelDesc.cStencilBits = 8;
	pixelDesc.cAuxBuffers = 0;
	pixelDesc.iLayerType = PFD_MAIN_PLANE;
	pixelDesc.bReserved = 0;
	pixelDesc.dwLayerMask = 0;
	pixelDesc.dwVisibleMask = 0;
	pixelDesc.dwDamageMask = 0;
	m_GLPixelIndex = ChoosePixelFormat( hDC, &pixelDesc);
	if (m_GLPixelIndex==0) // Let's choose a default index.
	{
		m_GLPixelIndex = 1;
		if (DescribePixelFormat(hDC, m_GLPixelIndex,
			sizeof(PIXELFORMATDESCRIPTOR),
			&pixelDesc)==0)
		{
			return FALSE;
		}
	}
	if (SetPixelFormat( hDC, m_GLPixelIndex, &pixelDesc)==FALSE)
	{
		return FALSE;
	}
	return TRUE;
}

int CPaOpenGLTest03MFCView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	HWND hWnd = GetSafeHwnd();
	HDC hDC = ::GetDC(hWnd);
	if (SetWindowPixelFormat(hDC)==FALSE)
		return 0;
	if (CreateViewGLContext(hDC)==FALSE)
		return 0;

	return 0;
}

BOOL CPaOpenGLTest03MFCView::CreateViewGLContext(HDC hDC)
{
	m_hGLContext = wglCreateContext(hDC);
	if (m_hGLContext == NULL)
	{
		return FALSE;
	}
	if (wglMakeCurrent(hDC, m_hGLContext)==FALSE)
	{
		return FALSE;
	}
	return TRUE;

}

void CPaOpenGLTest03MFCView::OnDestroy() 
{
	if(wglGetCurrentContext()!=NULL)
	{
		// make the rendering context not current
		wglMakeCurrent(NULL, NULL) ;
	}
	if (m_hGLContext!=NULL)
	{
		wglDeleteContext(m_hGLContext);
		m_hGLContext = NULL;
	}
	// Now the associated DC can be released.
	CView::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

void CPaOpenGLTest03MFCView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here

	CPaOpenGLTest03MFCDoc* pDoc = GetDocument();
	pDoc->RenderScene();
	
	SwapBuffers(dc.m_ps.hdc);
	// Do not call CView::OnPaint() for painting messages
}

void CPaOpenGLTest03MFCView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_LeftButtonDown = FALSE;
	CView::OnLButtonUp(nFlags, point);
}

void CPaOpenGLTest03MFCView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_LeftButtonDown = TRUE;
	m_LeftDownPos = point;
	CView::OnLButtonDown(nFlags, point);
}

void CPaOpenGLTest03MFCView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_RightButtonDown = FALSE;
	CView::OnRButtonUp(nFlags, point);
}

void CPaOpenGLTest03MFCView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_RightButtonDown = TRUE;
	m_RightDownPos = point;
	CView::OnRButtonDown(nFlags, point);
}

void CPaOpenGLTest03MFCView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_RightButtonDown)
	{
		CPaOpenGLTest03MFCDoc* pDoc = GetDocument();
		CSize rotate = m_RightDownPos - point;
		m_RightDownPos = point;
		pDoc->m_angle1 += rotate.cx/3;
		pDoc->m_angle2 += rotate.cy/3;
		InvalidateRect(NULL);
	}
	if (m_LeftButtonDown)
	{
		CPaOpenGLTest03MFCDoc* pDoc = GetDocument();
		CSize translate = m_LeftDownPos - point;
		m_LeftDownPos = point;
		pDoc->m_transX -= translate.cx/3;
		pDoc->m_transY += translate.cy/3;
		InvalidateRect(NULL);
	}
	CView::OnMouseMove(nFlags, point);
}

void CPaOpenGLTest03MFCView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);

	
	// TODO: Add your message handler code here
	GLsizei width, height;
	GLdouble aspect;
	width = cx;
	height = cy;
	if (cy==0)
		aspect = (GLdouble)width;
	else
		aspect = (GLdouble)width/(GLdouble)height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 500.0*aspect, 0.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	

	glDrawBuffer(GL_BACK);
}

BOOL CPaOpenGLTest03MFCView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default

	// Set brush to desired background color
	CBrush backBrush(RGB(0, 0, 0));

	// Save old brush
	CBrush* pOldBrush = pDC->SelectObject(&backBrush);

	CRect rect;
	pDC->GetClipBox(&rect);     // Erase the area needed

	pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY);

	pDC->SelectObject(pOldBrush);
	return TRUE;	

	//return CView::OnEraseBkgnd(pDC);
}
