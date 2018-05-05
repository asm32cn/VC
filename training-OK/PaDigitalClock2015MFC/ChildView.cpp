// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "PaDigitalClock2015MFC.h"
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
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_SIZE()
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

	/*
	RECT rect;
	GetClientRect(&rect);
	CBrush cbWindow(RGB(0, 0, 0));
	dc.FillRect(&rect, &cbWindow);
	*/

	m_isRefresh = TRUE;
	PA_DoClockDisplay();	

	// Do not call CWnd::OnPaint() for painting messages
}


void CChildView::PA_DoWindowInitialize()
{

	m_isRefresh = TRUE;

	GetLocalTime(&tmSystem);

	WORD m_wordMask=1;
	for(int i=0; i<12; i++){
		A_wordMask[11-i] = m_wordMask;
		m_wordMask += m_wordMask;
	}
	//A_wordMask = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048};

	srand(GetTickCount());

	HMODULE m_hModule = AfxGetApp()->m_hInstance;
	HRSRC hrsrc;
	hrsrc = FindResource(m_hModule, MAKEINTRESOURCE(IDR_DIGIT_MATRIX), "BIN");
	A_wordDigitMatrix = hrsrc ? (WORD *)LoadResource(m_hModule, hrsrc) : NULL;

	CClientDC dc(this);
	m_cdcChars.CreateCompatibleDC(&dc);
	dc.DeleteDC();

	PA_DoInitBitmapChars();

	SetTimer(1, 10, NULL);
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
	PA_DoClockDisplay();
	CWnd ::OnTimer(nIDEvent);
}

void CChildView::PA_DoWindowFinalize()
{
	KillTimer(1);
}

void CChildView::OnDestroy() 
{
	CWnd ::OnDestroy();

	// TODO: Add your message handler code here
	PA_DoWindowFinalize();

}

void CChildView::PA_DoInitBitmapChars()
{
	INT m_nCellSize = m_nClientWidth / 132;
	INT m_nOffset = 0;
	INT m_nOffsetX = 0;

	if(m_nCellSize<3) m_nCellSize=3;

	if(m_bmpChars.m_hObject) m_bmpChars.DeleteObject();

	CClientDC dc(this);

	m_nBmpCharWidth = m_nCellSize * 12;
	m_nBmpCharHeight = m_nCellSize * 22;

	m_nBmpCharsWidth = m_nBmpCharWidth * 13;
	m_nBmpCharsHeight = m_nBmpCharHeight;

	m_bmpChars.CreateCompatibleBitmap(&dc, m_nBmpCharsWidth, m_nBmpCharsHeight);

	m_cdcChars.SelectObject(m_bmpChars);

	//CBrush cb(RGB(0, 0x60, 0x99));
	CBrush cbBackground(RGB(0, 0, 255));
	RECT m_rectBmpChars = {0, 0, m_nBmpCharsWidth, m_nBmpCharsHeight};
	m_cdcChars.FillRect(&m_rectBmpChars, &cbBackground);

	CBrush cb(RGB(255, 255, 255));
	CPen pen1(PS_SOLID, 1, RGB(255, 255, 255));
	m_cdcChars.SelectObject(pen1);
	m_cdcChars.SelectObject(cb);
	for(int n=0; n<12; n++){
		m_nOffsetX = n * m_nBmpCharWidth;
		for(int i=0; i<22; i++){
			int m_nStartY = i * m_nCellSize + m_nCellSize;
			for(int j=0; j<12; j++){
				if(A_wordMask[j] & A_wordDigitMatrix[i+m_nOffset]){
					INT m_nStartX = m_nOffsetX + j * m_nCellSize;
					m_cdcChars.Ellipse(m_nStartX, m_nStartY, m_nStartX+m_nCellSize-1, m_nStartY+m_nCellSize-1);
					//m_cdcChars.Ellipse(m_nStartX, m_nStartY, m_nStartX+m_nCellSize, m_nStartY+m_nCellSize);
					//m_cdcChars.Rectangle(m_nStartX, m_nStartY, m_nStartX+m_nCellSize-1, m_nStartY+m_nCellSize-1);
					//m_cdcChars.Rectangle(m_nStartX, m_nStartY, m_nStartX+m_nCellSize, m_nStartY+m_nCellSize);
				}
			}
		}
		m_nOffset += 22;
	}
	cb.DeleteObject();

}

void CChildView::PA_DoClockDisplay()
{

	if(IsIconic()) return; // 如果是最小化状态就没必要重绘了

	GetLocalTime(&tmSystem);
	CClientDC dc(this);

	//for(int i=0; i<12; i++){
	//	dc.BitBlt(i*m_nBmpCharWidth, 0, m_nBmpCharWidth, m_nBmpCharHeight, &m_cdcChars, i*m_nBmpCharWidth, 0, SRCCOPY);
	//}

	//INT m_nMaxChars = 12; //12:00:00.000
	INT m_nMaxChars = 11; //12:00:00.00
	INT i;

	//strncpy(A_nCharID_t, A_nCharID, 12); // 有时候不会完整复制所有字节
	memcpy(A_nCharID_t, A_nCharID, 12);    // 完整复制所有字节

	INT m_nOffsetX = (m_nClientWidth - m_nBmpCharWidth*m_nMaxChars)/2;
	INT m_nOffsetY = (m_nClientHeight - m_nBmpCharsHeight)/2;

	CHAR m_cSplitter1 = tmSystem.wMilliseconds<500 ? 10 : 12;
	A_nCharID[0]=tmSystem.wHour/10;
	A_nCharID[1]=tmSystem.wHour%10;
	A_nCharID[2]=m_cSplitter1; // :
	A_nCharID[3]=tmSystem.wMinute/10;
	A_nCharID[4]=tmSystem.wMinute%10;
	A_nCharID[5]=m_cSplitter1; // :
	A_nCharID[6]=tmSystem.wSecond/10;
	A_nCharID[7]=tmSystem.wSecond%10;
	A_nCharID[8]=11; // .
	A_nCharID[9]=tmSystem.wMilliseconds/100;
	A_nCharID[10]=tmSystem.wMilliseconds/10%10;
	//A_nCharID[11]=tmSystem.wMilliseconds%10;

	for(i=0; i<11; i++){
		if(m_isRefresh || A_nCharID[i]!=A_nCharID_t[i]){
			PA_DoClockDisplayChar(dc, A_nCharID[i], m_nOffsetX, m_nOffsetY);
		}
		m_nOffsetX += m_nBmpCharWidth;
	}
	m_isRefresh = FALSE;

}

void CChildView::PA_DoClockDisplayChar(CDC &dc, INT nItem, INT nOffsetX, INT nOffsetY)
{
	INT m_nOffsetX = nItem * m_nBmpCharWidth;
	dc.BitBlt(nOffsetX, nOffsetY, m_nBmpCharWidth, m_nBmpCharHeight, &m_cdcChars, m_nOffsetX, 0, SRCCOPY);
}

void CChildView::OnSize(UINT nType, int cx, int cy) 
{
	CWnd ::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(!(cx>0 && cy>0)) return;
	m_nClientWidth = cx;
	m_nClientHeight = cy;

	PA_DoInitBitmapChars();

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
