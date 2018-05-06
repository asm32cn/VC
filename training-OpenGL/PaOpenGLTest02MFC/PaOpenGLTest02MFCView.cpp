// PaOpenGLTest02MFCView.cpp : implementation of the CPaOpenGLTest02MFCView class
//

#include "stdafx.h"
#include "PaOpenGLTest02MFC.h"

#include "PaOpenGLTest02MFCDoc.h"
#include "PaOpenGLTest02MFCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPaOpenGLTest02MFCView

IMPLEMENT_DYNCREATE(CPaOpenGLTest02MFCView, CView)

BEGIN_MESSAGE_MAP(CPaOpenGLTest02MFCView, CView)
	//{{AFX_MSG_MAP(CPaOpenGLTest02MFCView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPaOpenGLTest02MFCView construction/destruction

CPaOpenGLTest02MFCView::CPaOpenGLTest02MFCView()
{
	// TODO: add construction code here
	m_hGLContext = NULL;
	m_GLPixelIndex = 0;
}

CPaOpenGLTest02MFCView::~CPaOpenGLTest02MFCView()
{
}

BOOL CPaOpenGLTest02MFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style |= (WS_CLIPCHILDREN | WS_CLIPSIBLINGS);

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPaOpenGLTest02MFCView drawing

void CPaOpenGLTest02MFCView::OnDraw(CDC* pDC)
{
	CPaOpenGLTest02MFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CPaOpenGLTest02MFCView diagnostics

#ifdef _DEBUG
void CPaOpenGLTest02MFCView::AssertValid() const
{
	CView::AssertValid();
}

void CPaOpenGLTest02MFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPaOpenGLTest02MFCDoc* CPaOpenGLTest02MFCView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPaOpenGLTest02MFCDoc)));
	return (CPaOpenGLTest02MFCDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPaOpenGLTest02MFCView message handlers

BOOL CPaOpenGLTest02MFCView::SetWindowPixelFormat(HDC hDC)
{
	PIXELFORMATDESCRIPTOR pixelDesc;
	pixelDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pixelDesc.nVersion = 1;
	pixelDesc.dwFlags = PFD_DRAW_TO_WINDOW |
		PFD_DRAW_TO_BITMAP |
		PFD_SUPPORT_OPENGL |
		PFD_SUPPORT_GDI |
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

int CPaOpenGLTest02MFCView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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

BOOL CPaOpenGLTest02MFCView::CreateViewGLContext(HDC hDC)
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

void CPaOpenGLTest02MFCView::OnDestroy() 
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

void CPaOpenGLTest02MFCView::OnSize(UINT nType, int cx, int cy) 
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
}

void CPaOpenGLTest02MFCView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	glVertex2f(100.0f, 50.0f);
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
	glVertex2f(450.0f, 400.0f);
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
	glVertex2f(450.0f, 50.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	glVertex2f(500.0f, 50.0f);
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
	glVertex2f(650.0f, 400.0f);
	glVertex2f(650.0f, 50.0f);
	glEnd();

	glFlush();	
	// Do not call CView::OnPaint() for painting messages
}
