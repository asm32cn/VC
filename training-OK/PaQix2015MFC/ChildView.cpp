// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "PaQix2015MFC.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView,CWnd )
	//{{AFX_MSG_MAP(CChildView)
	ON_WM_PAINT()
	ON_WM_SHOWWINDOW()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_COMMAND(ID_SET_HORIZONTAL, OnSetHorizontal)
	ON_COMMAND(ID_SET_RANDOM, OnSetRandom)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CWnd::OnPaint() for painting messages
}


void CChildView::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CWnd ::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	PA_DoWindowInitialize();
}

void CChildView::PA_DoWindowInitialize()
{
	m_nCount = 255;
	m_nMinD = 2;
	m_nRangeD = 10;

	CClientDC dc(this);
	m_cdcMemory.CreateCompatibleDC(&dc);
	ReleaseDC(&dc);
	SetTimer(1, 10, NULL);
	m_brBackground.CreateSolidBrush(RGB(0, 0, 0));
	//AfxMessageBox("Init");
}

void CChildView::PA_DoWIndowFinalize()
{
	KillTimer(1);
	ReleaseDC(&m_cdcMemory);
}


void CChildView::OnDestroy() 
{
	CWnd ::OnDestroy();
	
	// TODO: Add your message handler code here
	PA_DoWIndowFinalize();
}

void CChildView::OnSize(UINT nType, int cx, int cy) 
{
	CWnd ::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(cx<=0 || cy<=0) return;

	GetClientRect(&m_rectClient);

	m_nClientWidth = cx;
	m_nClientHeight = cy;

	if(m_bmpMemory.m_hObject)
		m_bmpMemory.DeleteObject();

	CClientDC dc(this);
	m_bmpMemory.CreateCompatibleBitmap(&dc, cx, cy);\
	m_cdcMemory.SelectObject(&m_bmpMemory);
	ReleaseDC(&dc);

	qps.SetViewport(0, 0, cx, cy);
	qps.Init(m_nClientWidth, m_nClientHeight, m_nMinD, m_nRangeD);
}

void CChildView::PA_OnDisplay()
{
	CPen pen;
	m_cdcMemory.FillRect(&m_rectClient, &m_brBackground);
	for(int i=0; i<m_nCount; i++){
		pen.CreatePen(PS_SOLID, 1, qc.GetColorEx(m_nCount, i));
		m_cdcMemory.SelectObject(&pen);
		m_cdcMemory.MoveTo(qps.x1, qps.y1);
		m_cdcMemory.LineTo(qps.x2, qps.y2);
		pen.DeleteObject();
		if(i==5){
			qps.Backup();
			qc.Backup();
		}
		qps.SetNextPoints();
		qc.SetNextColor();
	}
	qps.Restore();
	qc.Restore();

	CClientDC dc(this);
	dc.BitBlt(0, 0, m_nClientWidth, m_nClientHeight, &m_cdcMemory, 0, 0, SRCCOPY);
	ReleaseDC(&dc);
}

void CChildView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default

	PA_OnDisplay();

	CWnd ::OnTimer(nIDEvent);
}

void CChildView::OnSetHorizontal() 
{
	// TODO: Add your command handler code here
	qps.dx2 = qps.dx1 = m_nMinD + rand() % m_nRangeD;
	qps.dy2 = qps.dy1 = 0;
	qps.x2 = qps.x1;
	qps.y1 = 0;
	qps.y2 = m_nClientHeight;
}

void CChildView::OnSetRandom() 
{
	// TODO: Add your command handler code here
	qps.Init(m_nClientWidth, m_nClientHeight, m_nMinD, m_nRangeD);
}

BOOL CChildView::OnEraseBkgnd(CDC* pDC) 
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
	
	//return CWnd ::OnEraseBkgnd(pDC);
}
