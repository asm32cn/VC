// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "PaBezier2015MFC.h"
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
	ON_WM_SIZE()
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
	ON_COMMAND(ID_SWITCH_START, OnSwitchStart)
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
	PA_DoBezierDisplay();	
	// Do not call CWnd::OnPaint() for painting messages
}


void CChildView::PA_DoWindowInitialize()
{
	m_nTimerID = 1;
	pts_nCount = 4;//10;
	ptds_nMin = 2;
	ptds_nRange = 10;
	srand(GetTickCount());
	//PA_DoInitBezier();
	m_cbrBackground.CreateSolidBrush(RGB(0xa5, 0xcb, 0xf7));

	m_cPen1.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	m_cPen2.CreatePen(PS_SOLID, 1, RGB(255, 255, 255));

	//SetTimer(1, 10, NULL);
	PA_DoSwitchTimer();

}

void CChildView::PA_DoBezierInit()
{
	for(int i=0; i<pts_nCount; i++){
		//if(i%3==2){
		//	pts[i]=pts[i-1];
		//	ptds[i]=ptds[i-1];
		//}else{
			pts[i].x = rand()%m_nClientWidth;
			pts[i].y = rand()%m_nClientHeight;
			ptds[i].x = ptds_nMin + rand()%ptds_nRange;
			ptds[i].y = ptds_nMin + rand()%ptds_nRange;
		//}
	}
	/*
	pts[4].x = pts[3].x + pts[3].x - pts[2].x;
	pts[4].y = pts[3].y + pts[3].y - pts[2].y;
	//pts[7].x = pts[6].x + pts[6].x - pts[5].x;
	//pts[7].y = pts[6].y + pts[6].y - pts[5].y;
	int n=pts_nCount-1;
	pts[n]=pts[0];
	pts[1].x = pts[0].x+pts[0].x - pts[n-1].x;
	pts[1].y = pts[0].y+pts[0].y - pts[n-1].y;
	*/

}

void CChildView::OnSize(UINT nType, int cx, int cy) 
{
	CWnd ::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(! (cx>0 && cy>0) ) return;
	m_nClientWidth = cx;
	m_nClientHeight = cy;

	GetClientRect(&m_rectClient);

	PA_DoBezierInit();
}

void CChildView::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CWnd ::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	PA_DoWindowInitialize();
	
}

void CChildView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	PA_DoBezierMove();
	PA_DoBezierDisplay();
	CWnd ::OnTimer(nIDEvent);
}

void CChildView::PA_DoBezierMove()
{
	INT nx,ny;
	for(int i=0; i<pts_nCount; i++){
		nx = pts[i].x + ptds[i].x;
		if(nx>m_nClientWidth || nx<0){
			ptds[i].x = -ptds[i].x;
		}else{
			pts[i].x = nx;
		}
		ny = pts[i].y + ptds[i].y;
		if(ny>m_nClientHeight || ny<0){
			ptds[i].y = -ptds[i].y;
		}else{
			pts[i].y = ny;
		}
	}
	/*
	*/
}

void CChildView::PA_DoBezierDisplay()
{
	/*
	*/
	ptbs[0].x = pts[0].x+(pts[1].x - pts[0].x)*2/3;
	ptbs[0].y = pts[0].y+(pts[1].y - pts[0].y)*2/3;
	ptbs[1]=pts[1];
	ptbs[2]=pts[2];
	ptbs[3].x = (pts[2].x + pts[3].x)/2;
	ptbs[3].y = (pts[2].y + pts[3].y)/2;
	ptbs[4]=pts[3];
	ptbs[5]=pts[0];
	ptbs[6]=ptbs[0];

	CClientDC dc(this);
	dc.FillRect(&m_rectClient, &m_cbrBackground);
	for(int i=0; i<pts_nCount; i++){
		CString s; s.Format("%d", i);
		dc.TextOut(pts[i].x, pts[i].y, s);
		dc.Ellipse(pts[i].x-2,pts[i].y-2,pts[i].x+2,pts[i].y+2);
		s.Format("%3d %3d %2d %2d", pts[i].x, pts[i].y, ptds[i].x, ptds[i].y);
		//dc.TextOut(0, i*25, s);
	}
	dc.Ellipse(ptbs[0].x-2, ptbs[0].y-2, ptbs[0].x+2, ptbs[0].y+2);
	dc.Ellipse(ptbs[3].x-2, ptbs[3].y-2, ptbs[3].x+2, ptbs[3].y+2);

	dc.SelectObject(&m_cPen2);


	dc.MoveTo(pts[0]);
	dc.LineTo(pts[1]);
	dc.LineTo(pts[2]);
	dc.LineTo(pts[3]);
	dc.LineTo(pts[0]);

	dc.SelectObject(&m_cPen1);
	//dc.PolyBezier(pts, pts_nCount);
	dc.PolyBezier(ptbs, 7);

	//CString s ; s.Format("%d %d rec", pts[0].x, pts[0].y);

	//dc.TextOut(0, 200, s);
}

void CChildView::OnSwitchStart() 
{
	// TODO: Add your command handler code here
	PA_DoSwitchTimer();
}

void CChildView::PA_DoSwitchTimer()
{
	static UINT m_nTimerStatus;
	if(m_nTimerStatus){
		KillTimer(m_nTimerID);
		m_nTimerStatus = 0;
	}else{
		SetTimer(m_nTimerID, 10, NULL);
		m_nTimerStatus=1;
	}
}
