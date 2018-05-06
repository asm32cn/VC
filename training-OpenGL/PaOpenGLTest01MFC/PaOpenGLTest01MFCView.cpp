// PaOpenGLTest01MFCView.cpp : implementation of the CPaOpenGLTest01MFCView class
//

#include "stdafx.h"
#include "PaOpenGLTest01MFC.h"

#include "PaOpenGLTest01MFCDoc.h"
#include "PaOpenGLTest01MFCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPaOpenGLTest01MFCView

IMPLEMENT_DYNCREATE(CPaOpenGLTest01MFCView, CView)

BEGIN_MESSAGE_MAP(CPaOpenGLTest01MFCView, CView)
	//{{AFX_MSG_MAP(CPaOpenGLTest01MFCView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPaOpenGLTest01MFCView construction/destruction

CPaOpenGLTest01MFCView::CPaOpenGLTest01MFCView()
{
	// TODO: add construction code here
	m_hGLContext = NULL;
    m_GLPixelIndex = 0;
}

CPaOpenGLTest01MFCView::~CPaOpenGLTest01MFCView()
{
}

BOOL CPaOpenGLTest01MFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style |= (WS_CLIPCHILDREN | WS_CLIPSIBLINGS);

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPaOpenGLTest01MFCView drawing

void CPaOpenGLTest01MFCView::OnDraw(CDC* pDC)
{
	CPaOpenGLTest01MFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CPaOpenGLTest01MFCView printing

BOOL CPaOpenGLTest01MFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPaOpenGLTest01MFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPaOpenGLTest01MFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPaOpenGLTest01MFCView diagnostics

#ifdef _DEBUG
void CPaOpenGLTest01MFCView::AssertValid() const
{
	CView::AssertValid();
}

void CPaOpenGLTest01MFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPaOpenGLTest01MFCDoc* CPaOpenGLTest01MFCView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPaOpenGLTest01MFCDoc)));
	return (CPaOpenGLTest01MFCDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPaOpenGLTest01MFCView message handlers

BOOL CPaOpenGLTest01MFCView::SetWindowPixelFormat(HDC hDC)
{
    PIXELFORMATDESCRIPTOR pixelDesc;
    pixelDesc.nSize   = sizeof(PIXELFORMATDESCRIPTOR);
    pixelDesc.nVersion  = 1;
    pixelDesc.dwFlags   = PFD_DRAW_TO_WINDOW |
        PFD_DRAW_TO_BITMAP | PFD_SUPPORT_OPENGL |
        PFD_SUPPORT_GDI |PFD_STEREO_DONTCARE;
    pixelDesc.iPixelType  = PFD_TYPE_RGBA;
    pixelDesc.cColorBits = 32;
    pixelDesc.cRedBits = 8;
    pixelDesc.cRedShift = 16;
    pixelDesc.cGreenBits = 8;
    pixelDesc.cGreenShift = 8;
    pixelDesc.cBlueBits = 8;
    pixelDesc.cBlueShift = 0;
    pixelDesc.cAlphaBits = 0;
    pixelDesc.cAlphaShift = 0;
    pixelDesc.cAccumBits= 64;
    pixelDesc.cAccumRedBits = 16;
    pixelDesc.cAccumGreenBits = 16;
    pixelDesc.cAccumBlueBits = 16;
    pixelDesc.cAccumAlphaBits= 0;
    pixelDesc.cDepthBits = 32;
    pixelDesc.cStencilBits= 8;
    pixelDesc.cAuxBuffers = 0;
    pixelDesc.iLayerType= PFD_MAIN_PLANE;
    pixelDesc.bReserved = 0;
    pixelDesc.dwLayerMask= 0;
    pixelDesc.dwVisibleMask= 0;
    pixelDesc.dwDamageMask= 0;
    m_GLPixelIndex = ChoosePixelFormat( hDC, &pixelDesc);
    if (m_GLPixelIndex==0) // Let's choose a default index.
    {
        m_GLPixelIndex = 1;
        if (DescribePixelFormat(hDC, m_GLPixelIndex, sizeof
            (PIXELFORMATDESCRIPTOR), &pixelDesc)==0)
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

int CPaOpenGLTest01MFCView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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

BOOL CPaOpenGLTest01MFCView::CreateViewGLContext(HDC hDC)
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

void CPaOpenGLTest01MFCView::OnDestroy() 
{
    if(wglGetCurrentContext()!=NULL)
    {
        wglMakeCurrent(NULL, NULL) ;
    }
    if (m_hGLContext!=NULL)
    {
        wglDeleteContext(m_hGLContext);
        m_hGLContext = NULL;
    }

	CView::OnDestroy();
	
	// TODO: Add your message handler code here

}

void CPaOpenGLTest01MFCView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
    GLsizei width, height;
    GLdouble aspect;
    width = cx; height = cy;
    if (cy==0)
        aspect = (GLdouble)width;
    else
        aspect = (GLdouble)width/(GLdouble)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, aspect, 1, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	
}

void CPaOpenGLTest01MFCView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
    CPaOpenGLTest01MFCDoc * pDoc = GetDocument();
    pDoc ->RenderScene();

	// Do not call CView::OnPaint() for painting messages
}
