// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "PaJigsawPuzzle2015MFC.h"
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
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_COMMAND(ID_DO_GAME_INIT, OnDoGameInit)
	ON_COMMAND(ID_DO_GAME_AUTO, OnDoGameAuto)
	ON_COMMAND_RANGE(ID_SELECT_GAME1, ID_SELECT_GAME6, PA_DoSelectNewGame)
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
	PA_DoGameDisplay();
	// Do not call CWnd::OnPaint() for painting messages
}

void CChildView::PA_DoWindowInitialize()
{
	A_objGameConfigure[0].Init(IDR_JPEG1, 490, 280, 70, 70);
	A_objGameConfigure[1].Init(IDR_JPEG2, 960, 340, 80, 85);
	A_objGameConfigure[2].Init(IDR_JPEG3, 1024, 660, 128, 110);
	A_objGameConfigure[3].Init(IDR_JPEG4, 1000, 660, 125, 110);
	A_objGameConfigure[4].Init(IDR_JPEG5, 768, 660, 192, 110);
	A_objGameConfigure[5].Init(IDR_JPEG6, 872, 660, 109, 110);

	m_nTimerID = 1;

	m_nGameSelected = 0;
	m_nGameSelectedPrevious = -1;

	m_penHover.CreatePen(PS_DOT, 1, RGB(255,255,0) );
	m_cbBackground.CreateSolidBrush(RGB(166, 202, 240));

	CClientDC dc(this);
	m_cdcMemory.CreateCompatibleDC(&dc);
	m_cdcGameRes.CreateCompatibleDC(&dc);
	m_cdcGameResDark.CreateCompatibleDC(&dc);
	ReleaseDC(&dc);

	PA_DoGameInit();
}

void CChildView::PA_DoWindowFinalize()
{
	m_bmpGameRes.DeleteObject();
}

void CChildView::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CWnd ::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	PA_DoWindowInitialize();
	
}

void CChildView::OnDestroy() 
{
	CWnd ::OnDestroy();
	
	// TODO: Add your message handler code here
	PA_DoWindowFinalize();
}

void CChildView::PA_DoGameDisplay()
{

	m_cdcMemory.FillRect(&m_rectClient, &m_cbBackground);
	for(int i=0; i<m_nItemCount; i++){
		int id = A_nCachedID[i];
		if(m_bGameSucceed || id<m_nItemCount-1){
			int x = (i % m_nCountX) * m_nItemWidth1;
			int y = (i / m_nCountX) * m_nItemHeight1;
			CDC * pDC = (id==i || m_nHoverID==i) ? &m_cdcGameRes : &m_cdcGameResDark;
			m_cdcMemory.BitBlt(x, y, m_nItemWidth, m_nItemHeight, pDC, A_objItems[id].m_nImageStartX, A_objItems[id].m_nImageStartY, SRCCOPY);

			if(m_isAutoMove && (m_nSelectedID==id || m_nSelected2ID==id)){
				m_cdcMemory.SelectObject(&m_penHover);
				m_cdcMemory.MoveTo(x-1, y-1);
				m_cdcMemory.LineTo(x+m_nItemWidth, y-1);
				m_cdcMemory.LineTo(x+m_nItemWidth, y+m_nItemHeight);
				m_cdcMemory.LineTo(x-1, y+m_nItemHeight);
				m_cdcMemory.LineTo(x-1, y-1);
				//m_cdcMemory.Rectangle(rect);
			}
		}
	}
	//dc.BitBlt(0, 0, m_nGameResWidth, m_nGameResHeight, &m_cdcGameRes, 0, 0, SRCCOPY);
	CClientDC dc(this);
	dc.BitBlt(0, 0, m_nClientWidth, m_nClientHeight, &m_cdcMemory, 0, 0, SRCCOPY);
	//dc.TextOut(0, 500, m_strDebug);
	ReleaseDC(&dc);

	CString s="";
	CString s1;
	s.Format("Succeed=%d, Hover=%d, HoverID=%d ,", m_bGameSucceed, m_nHoverID, A_nCachedID[m_nHoverID]);
	for(i=0; i<m_nItemCount; i++){
		s1.Format("%d ", A_nCachedID[i]);
		s += s1;
	}

	s.Format("移动次数:%d", m_nCountStep);
	ShowStatusString(s);

	//ShowStatusString(s);
}

void CChildView::PA_DoGameInit()
{
	INT i;

	if(m_bGameSucceed || m_isAutoMove) KillTimer(m_nTimerID);

	if(m_nGameSelectedPrevious!=m_nGameSelected){

		m_nCountX = A_objGameConfigure[m_nGameSelected].m_nCountX;
		m_nCountY = A_objGameConfigure[m_nGameSelected].m_nCountY;
		m_nItemWidth  = A_objGameConfigure[m_nGameSelected].m_nItemWidth;
		m_nItemHeight = A_objGameConfigure[m_nGameSelected].m_nItemHeight;

		m_nItemWidth1  = m_nItemWidth + 1;
		m_nItemHeight1 = m_nItemHeight + 1;

		m_nItemCount  = m_nCountX * m_nCountY;

		m_nGameResWidth  = A_objGameConfigure[m_nGameSelected].m_nGameResWidth;
		m_nGameResHeight = A_objGameConfigure[m_nGameSelected].m_nGameResHeight;
		INT m_nGameResID = A_objGameConfigure[m_nGameSelected].m_nGameResID;

		m_nDisplayWidth = m_nCountX * m_nItemWidth1;
		m_nDisplayHeight = m_nCountY * m_nItemHeight1;

		if(m_bmpGameRes.m_hObject) m_bmpGameRes.DeleteObject();
		if(m_bmpGameResDark.m_hObject) m_bmpGameResDark.DeleteObject();
		CClientDC dc(this);
		m_bmpGameRes.CreateCompatibleBitmap(&dc, m_nGameResWidth, m_nGameResHeight);
		m_bmpGameResDark.CreateCompatibleBitmap(&dc, m_nGameResWidth, m_nGameResHeight);
		ReleaseDC(&dc);

		m_cdcGameRes.SelectObject(&m_bmpGameRes);
		m_cdcGameResDark.SelectObject(&m_bmpGameResDark);

		PA_RenderResource(m_cdcGameRes, m_nGameResID, "JPEG", m_nGameResWidth, m_nGameResHeight);
		m_cdcGameResDark.BitBlt(0, 0, m_nGameResWidth, m_nGameResHeight, &m_cdcGameRes, 0, 0, SRCCOPY);

		/*
		*/
		BITMAP bmInfo;
		m_bmpGameResDark.GetBitmap(&bmInfo);
		INT m_nBitsPixel = bmInfo.bmBitsPixel;
		INT m_nSizePixel = m_nBitsPixel / 8;
		BOOL m_isSucceed = FALSE;
		if(m_nBitsPixel==32 || m_nBitsPixel==24 || m_nBitsPixel==16){
			DWORD m_dwBufferSize = bmInfo.bmWidth * bmInfo.bmHeight * m_nSizePixel;
			LPVOID m_lpBuffer = ::GlobalAlloc( GMEM_MOVEABLE, m_dwBufferSize);
			if(m_lpBuffer){
				BYTE * m_lpbBuffer = (BYTE *)::GlobalLock(m_lpBuffer);
				DWORD m_dwDataSize = m_bmpGameResDark.GetBitmapBits(m_dwBufferSize, m_lpbBuffer);
				if(m_dwDataSize){
					//CString s;
					//s.Format("%d, %d, %d, %d, %lu, %lx, %lu, %lx\n%x %x %x %x %x %x %x %x",
					//	bmInfo.bmWidth, bmInfo.bmHeight, m_nBitsPixel, m_nSizePixel, m_dwBufferSize, m_dwBufferSize, m_dwDataSize, m_dwDataSize,
					//	m_lpbBuffer[0], m_lpbBuffer[1], m_lpbBuffer[2], m_lpbBuffer[3], m_lpbBuffer[4], m_lpbBuffer[5], m_lpbBuffer[6], m_lpbBuffer[7]);
					//AfxMessageBox(s);
					if(m_nBitsPixel==16){ // 16位位图 亮度降低到1/2
						WORD * m_lpwBuffer = (WORD *)m_lpbBuffer;
						DWORD m_dwDataCount = m_dwDataSize/2;
						for(UINT n=0; n<m_dwDataCount; n++){
							m_lpwBuffer[n] = (m_lpwBuffer[n] >> 1) & 0x7bef;
						}
					}else{ // 24位 32位 位图 亮度降低到 1/4
						for(UINT n=0; n<m_dwDataSize; n++){
							m_lpbBuffer[n] = (m_lpbBuffer[n] >> 1) & 0x7f;
						}
					}
					m_bmpGameResDark.SetBitmapBits(m_dwDataSize, m_lpbBuffer);
					m_isSucceed = TRUE;
				}
				::GlobalUnlock(m_lpBuffer);
				::GlobalFree(m_lpBuffer);
			}
		}
		if(!m_isSucceed){
			for(int y=0; y<m_nGameResHeight; y++){
				for(int x=0; x<m_nGameResWidth; x++){
					m_cdcGameResDark.SetPixel(x, y, ((m_cdcGameResDark.GetPixel(x, y) >> 1) & 0x7f7f7f) );
				}
			}
		}

		for(i=0; i<m_nItemCount; i++){
			int m = i % m_nCountX;
			int n = i / m_nCountX;
			A_objItems[i].m_nImageStartX = m * m_nItemWidth;
			A_objItems[i].m_nImageStartY = n * m_nItemHeight;
			A_objItems[i].m_nPosition = i;
			A_objItems[i].m_nStartX = m;
			A_objItems[i].m_nStartY = n;
		}
	}// end load configure

	m_nGameSelectedPrevious = m_nGameSelected;

	//memset(A_nCachedID, 0, sizeof(A_nCachedID));
	ZeroMemory(A_nCachedID, sizeof(A_nCachedID));

	srand(GetTickCount());

	INT m_nCachedID_blank = m_nItemCount-1;
	for(i=0; i<m_nItemCount; i++){
		A_nCachedID[i] = i;
	}
	/*
	for(i=0; i<m_nItemCount-2; i++){
		int o = m_nItemCount-i-2;
		int n = rand() % (m_nItemCount-i-1);
		int t = A_nCachedID[n];
		A_nCachedID[n] = A_nCachedID[o];
		A_nCachedID[o] = t;
	}
	*/
	/*
	*/
	INT m_nMoveCount = m_nItemCount*10;
	BYTE A_byDirectionStatus[4];
	m_nPosID_blank = m_nCachedID_blank;//初始位置在右下
	INT m_byDirectionStatusPrev = 0;
	for(i=0; i<m_nMoveCount; i++){
		INT m_nDicectionCount=0;
		INT x = m_nPosID_blank%m_nCountX;
		INT y = m_nPosID_blank/m_nCountX;
		if(m_byDirectionStatusPrev!=3 && x>0) A_byDirectionStatus[m_nDicectionCount++]=1;
		if(m_byDirectionStatusPrev!=4 && y>0) A_byDirectionStatus[m_nDicectionCount++]=2;
		if(m_byDirectionStatusPrev!=1 && (x+1)<m_nCountX) A_byDirectionStatus[m_nDicectionCount++]=3;
		if(m_byDirectionStatusPrev!=2 && (y+1)<m_nCountY) A_byDirectionStatus[m_nDicectionCount++]=4;
		INT m_nDirectionStatus = A_byDirectionStatus[rand() % m_nDicectionCount];
		INT m_nPosID_blank_new;
		switch(m_nDirectionStatus){
		case 1:
			m_nPosID_blank_new = m_nPosID_blank-1;
			break;
		case 2:
			m_nPosID_blank_new = m_nPosID_blank-m_nCountX;
			break;
		case 3:
			m_nPosID_blank_new = m_nPosID_blank+1;
			break;
		case 4:
			m_nPosID_blank_new = m_nPosID_blank+m_nCountX;
			break;
		}
		A_nCachedID[m_nPosID_blank]=A_nCachedID[m_nPosID_blank_new];
		A_nCachedID[m_nPosID_blank_new]=m_nCachedID_blank;
		m_nPosID_blank = m_nPosID_blank_new;
	}

	m_nHoverID = -1;
	m_bGameSucceed = FALSE;
	m_isAutoMove = FALSE;

	m_nCountStep = 0;


	PA_DoGameCheckSucceed();
}

void CChildView::OnDoGameInit() 
{
	// TODO: Add your command handler code here
	PA_DoGameInit();
	PA_DoGameDisplay();
}

void CChildView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_bGameSucceed || m_isAutoMove) return;
	if(point.x<m_nDisplayWidth && point.y<m_nDisplayHeight){
		INT m_nPos = point.y / m_nItemHeight1 * m_nCountX + point.x/m_nItemWidth1;
		PA_DoGameMoveItem( m_nPos );
	}

	CWnd ::OnLButtonUp(nFlags, point);
}

void CChildView::ShowStatusString(CString strDisplay)
{
	CStatusBar * pStatus = (CStatusBar *)AfxGetApp()->m_pMainWnd->GetDescendantWindow(ID_VIEW_STATUS_BAR);
	if(pStatus){
		pStatus->SetPaneText(0, strDisplay);
	}
}

void CChildView::PA_DoGameMoveItem(INT m_nPosID)
{
	BOOL isMoveable = FALSE;

	if(m_nPosID==m_nPosID_blank) return;
	INT m_nPosX_blank = m_nPosID_blank%m_nCountX;
	INT m_nPosY_blank = m_nPosID_blank/m_nCountX;
	INT m_nPosX = m_nPosID%m_nCountX;
	INT m_nPosY = m_nPosID/m_nCountX;
	if( ( (m_nPosX+1==m_nPosX_blank) || (m_nPosX==m_nPosX_blank+1) ) && m_nPosY==m_nPosY_blank ||
		( (m_nPosY+1==m_nPosY_blank) || (m_nPosY==m_nPosY_blank+1) ) && m_nPosX==m_nPosX_blank){
		INT t = A_nCachedID[m_nPosID];
		A_nCachedID[m_nPosID] = A_nCachedID[m_nPosID_blank];
		A_nCachedID[m_nPosID_blank] = t;

		m_nPosID_blank = m_nPosID;

		m_nCountStep++;

		PA_DoGameCheckSucceed();
		PA_DoGameDisplay();
	}
}



void CChildView::PA_DoGameCheckSucceed()
{
	// 检查输赢
	BOOL isSucceed = TRUE;
	for(INT i=0; i<m_nItemCount; i++){
		if(A_nCachedID[i]!=i){
			isSucceed = FALSE;
			break;
		}
	}
	m_bGameSucceed = isSucceed;
	if(isSucceed){
		m_isAutoMove = FALSE;
		SetTimer(m_nTimerID, 50, NULL);
	}
}

void CChildView::PA_RenderResource(CDC &dc, INT nResourceID, LPCTSTR szType, INT cx, INT cy)
{
	HINSTANCE hModule = AfxGetApp()->m_hInstance;
	HRSRC hr;
	HGLOBAL lpData;
	if( hr = FindResource(hModule, MAKEINTRESOURCE(nResourceID), szType) ){
		if(lpData = LoadResource(hModule,  hr)){
			DWORD dwSize = SizeofResource(hModule, hr);

			HGLOBAL ghData = ::GlobalAlloc( GMEM_MOVEABLE, dwSize ); 
			LPVOID  pData = ::GlobalLock( ghData ); 
			memcpy(pData, lpData, dwSize);
			::GlobalUnlock( ghData ); 

			IStream * pStream  = NULL; 
			if(S_OK == ::CreateStreamOnHGlobal( ghData, FALSE, &pStream ) )
			{
				//	从流中装入图片 
				IPicture * pPicture = NULL; 
				if( SUCCEEDED( OleLoadPicture( pStream, dwSize, TRUE, IID_IPicture,( LPVOID* )&pPicture ) ) ) 
				{ 
					//	向DC中绘图 
					OLE_XSIZE_HIMETRIC hmWidth;
					OLE_YSIZE_HIMETRIC hmHeight; 
					pPicture->get_Width( &hmWidth ); 
					pPicture->get_Height( &hmHeight ); 
					pPicture->Render( dc.m_hDC, 0, 0, cx, cy, 0, hmHeight, hmWidth, -hmHeight, NULL ); 
					pPicture->Release();
				}
				// 释放流和文件 
				pStream->Release();
			}
			::GlobalFree(ghData);
		}
	}
}

void CChildView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_bGameSucceed || m_isAutoMove) return;
	m_nCursorX = point.x;
	m_nCursorY = point.y;

	if(m_nCursorX>=0 && m_nCursorX<m_nDisplayWidth && m_nCursorY>=0 && m_nCursorY<m_nDisplayHeight){
		m_nHoverID = m_nCursorY / m_nItemHeight1 * m_nCountX + m_nCursorX / m_nItemWidth1;
	}else{
		m_nHoverID = -1;
	}

	PA_DoGameDisplay();

	CWnd ::OnMouseMove(nFlags, point);
}

void CChildView::OnSize(UINT nType, int cx, int cy) 
{
	CWnd ::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(cx==0 || cy==0) return;
	m_nClientWidth = cx;
	m_nClientHeight = cy;
	GetClientRect(&m_rectClient);

	if(m_bmpMemory.m_hObject) m_bmpMemory.DeleteObject();
	CClientDC dc(this);
	m_bmpMemory.CreateCompatibleBitmap(&dc, m_nClientWidth, m_nClientHeight);
	ReleaseDC(&dc);
	m_cdcMemory.SelectObject(&m_bmpMemory);
}


void CChildView::PA_DoSelectNewGame(UINT nID)
{
	m_nGameSelected = nID - ID_SELECT_GAME1;
	if(m_nGameSelected<0 || m_nGameSelected>5) m_nGameSelected=0;

	PA_DoGameInit();
	PA_DoGameDisplay();
}

void CChildView::OnDoGameAuto() 
{
	// TODO: Add your command handler code here
	if(m_isAutoMove){
		m_isAutoMove = FALSE;
		PA_DoGameDisplay();
	}else{
		m_isAutoMove = TRUE;
		PA_DoGameAuto();
	}
}

void CChildView::PA_DoGameAuto()
{
	if(m_bGameSucceed) return;
	//AfxMessageBox(s);
	SetTimer(m_nTimerID, 50, NULL);
}

void CChildView::PA_DoGameAutoStop()
{
	if(m_isAutoMove){
		m_isAutoMove = FALSE;
		KillTimer(m_nTimerID);
	}
}

void CChildView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_bGameSucceed){
		PA_DoGameWinFlash();
	}else if(m_isAutoMove){
		PA_DoGameAutoMove();
	}else{
		KillTimer(m_nTimerID);
	}
	CWnd ::OnTimer(nIDEvent);
}

void CChildView::PA_DoGameAutoMove(){
	if(m_bGameSucceed){
		m_isAutoMove = FALSE;
		return;
	} else if(m_nItemCount<m_nCountX + m_nCountX){
		PA_DoGameAutoStop();
		AfxMessageBox("Should two rows or more.");
		return;
	}
	//KillTimer(m_nTimerID);m_isAutoMove=FALSE;
	static INT A_nBufferedMove[32]={0};
	static INT m_nBufferedMove_Count=0;
	static INT m_nBufferedMove_Current=0;
	INT i;

	INT m_nPosID_blank_new = -1;

	m_nSelected2ID = -1;

	if(m_nBufferedMove_Count>m_nBufferedMove_Current){
		m_nPosID_blank_new = m_nPosID_blank + A_nBufferedMove[m_nBufferedMove_Current++];

		INT t=A_nCachedID[m_nPosID_blank];
		A_nCachedID[m_nPosID_blank] = A_nCachedID[m_nPosID_blank_new];
		A_nCachedID[m_nPosID_blank_new] = t;

		m_nCountStep++;

		m_nPosID_blank = m_nPosID_blank_new;

		if(m_nBufferedMove_Count==m_nBufferedMove_Current) m_nBufferedMove_Count=0;

	} else {
		for(i=0; i<m_nItemCount; i++){
			if(A_nCachedID[i]!=i){
				m_nSelectedID=i;
				break;
			}
		}
		INT m_nPosID_sel = 0;
		for(i=0; i<m_nItemCount; i++){
			if(A_nCachedID[i]==m_nSelectedID){
				m_nPosID_sel=i;
				break;
			}
		}

		INT m_nStep2 = m_nItemCount - m_nCountX - m_nCountX;
		INT m_nBlank_Row = m_nPosID_blank / m_nCountX;
		INT m_nBlank_Col = m_nPosID_blank % m_nCountX;
		BOOL m_bBlank_Row1 = m_nPosID_blank < m_nStep2 + m_nCountX;

		if(m_nSelectedID >= m_nStep2){ // 最后两行的复位
			
			INT m_nSelected_Col=0;
			INT m_nPostID_t;

			for(i=0; i<m_nCountX; i++){
				m_nPostID_t = m_nStep2+i;
				if(A_nCachedID[m_nPostID_t]!=m_nStep2+i || A_nCachedID[m_nPostID_t+m_nCountX]!=m_nPostID_t+m_nCountX){
					m_nSelected_Col=i;
					break;
				}
			}

			INT m_nSelected1 = m_nStep2+m_nSelected_Col;
			INT m_nSelected2 = m_nStep2+m_nSelected_Col+m_nCountX;
			INT m_nPosID_sel1;
			INT m_nPosID_sel2;

			m_nSelected2ID = m_nSelected2;

			for(i=0; i<m_nCountX+m_nCountX; i++){
				m_nPostID_t = m_nStep2+i;
				if(A_nCachedID[m_nPostID_t]==m_nSelected1) m_nPosID_sel1=m_nPostID_t;
				if(A_nCachedID[m_nPostID_t]==m_nSelected2) m_nPosID_sel2=m_nPostID_t;
			}

			INT m_nSelected1_Col = m_nPosID_sel1 % m_nCountX;
			INT m_nSelected2_Col = m_nPosID_sel2 % m_nCountX;

			BOOL m_bFirst1 = m_nSelected1_Col<=m_nSelected2_Col;
			INT m_nPosID_first = m_bFirst1 ? m_nPosID_sel1 : m_nPosID_sel2;
			INT m_nPosID_second = m_bFirst1 ? m_nPosID_sel2 : m_nPosID_sel1;
			BOOL m_bFirst_Row1 = m_nStep2 + m_nCountX > m_nPosID_first;
			//INT m_nFirst = A_nCachedID[m_nPosID_first];
			//INT m_nSecond = A_nCachedID[m_nPosID_second];
			BOOL m_bSecond_Row1 = m_nStep2 + m_nCountX > m_nPosID_second;

			INT m_nFirst_new=-1;
			INT m_nFirst_new_Col;
			INT m_nSecond_new=-1;
			INT m_nSecond_new_Col;

			if(A_nCachedID[m_nSelected1]==m_nSelected2 && A_nCachedID[m_nSelected2]==m_nSelected1 && m_nBlank_Col==m_nSelected_Col+1){
				if(m_bBlank_Row1){
					INT A_nPosID_move[6] = {-1,m_nCountX, 1, 1, -m_nCountX, -1};
					memcpy(A_nBufferedMove, A_nPosID_move, sizeof(A_nPosID_move));
					m_nBufferedMove_Count = 6;
					m_nBufferedMove_Current = 1;
					m_nPosID_blank_new = m_nPosID_blank + A_nPosID_move[0];
				}else{
					INT A_nPosID_move[6] = {-1,-m_nCountX, 1, 1, m_nCountX, -1};
					memcpy(A_nBufferedMove, A_nPosID_move, sizeof(A_nPosID_move));
					m_nBufferedMove_Count = 6;
					m_nBufferedMove_Current = 1;
					m_nPosID_blank_new = m_nPosID_blank + A_nPosID_move[0];
				}
			}else{

				if(A_nCachedID[m_nSelected1]==m_nSelected1 && A_nCachedID[m_nSelected2+1]==m_nSelected2 && m_nSelected2==m_nPosID_blank ||
					A_nCachedID[m_nSelected2]==m_nSelected2 && A_nCachedID[m_nSelected1+1]==m_nSelected1 && m_nSelected1==m_nPosID_blank){
					m_nPosID_blank_new = m_nPosID_blank+1;
				}else if(A_nCachedID[m_nSelected1]==m_nSelected2 && A_nCachedID[m_nSelected1+1]==m_nSelected1 ||
					A_nCachedID[m_nSelected2]==m_nSelected1 && A_nCachedID[m_nSelected2+1]==m_nSelected2){
					if(m_nSelected2==m_nPosID_blank){
						m_nPosID_blank_new = m_nSelected1;
					}else if(m_nSelected1==m_nPosID_blank){
						m_nPosID_blank_new = m_nSelected2;
					}else if(m_nBlank_Col>m_nSelected_Col){
						m_nPostID_t = m_nPosID_blank-1;
						if(A_nCachedID[m_nPostID_t]==m_nSelected1 || A_nCachedID[m_nPostID_t]==m_nSelected2){
							m_nPosID_blank_new = m_nPosID_blank+(m_bFirst1?-m_nCountX:m_nCountX);
						}else{
							m_nPosID_blank_new = m_nPosID_blank-1;
						}
					}
				}else if(A_nCachedID[m_nSelected1]==m_nSelected2 && A_nCachedID[m_nSelected1+1]==m_nSelected1 && m_nSelected2==m_nPosID_blank){
					m_nPosID_blank_new = m_nSelected1;
				}else if(A_nCachedID[m_nSelected2]==m_nSelected1 && A_nCachedID[m_nSelected2+1]==m_nSelected2 && m_nSelected1==m_nPosID_blank){
					m_nPosID_blank_new = m_nSelected1;
				}else{
					if(m_bFirst1){
						if(m_nSelected1_Col>m_nSelected_Col){
							m_nFirst_new = m_nPosID_sel1-1;
						}else if(m_nPosID_sel1==m_nSelected1){
							m_nFirst_new = m_nSelected2;
						}
					}else{ //m_nFirst==m_nSelected2
						if(m_nSelected2_Col>m_nSelected_Col){
							m_nFirst_new = m_nPosID_sel2-1;
						}else if(m_nPosID_sel2==m_nSelected2){
							m_nFirst_new = m_nSelected1;
						}
					}
					if(m_nFirst_new!=-1){
						m_nFirst_new_Col = m_nFirst_new % m_nCountX;
						if(m_nBlank_Col<m_nFirst_new_Col){
							m_nPosID_blank_new = m_nPosID_blank+1;
						}else if(m_nPosID_blank==m_nFirst_new){
							m_nPosID_blank_new = m_nPosID_first;
						}else if(m_nBlank_Col==m_nFirst_new_Col){
							m_nPosID_blank_new = m_nFirst_new;
						}else if(m_nBlank_Col>m_nFirst_new_Col){
							if(m_nPosID_blank==m_nPosID_first+1){
								m_nPosID_blank_new = m_nPosID_blank + (m_bBlank_Row1?m_nCountX:-m_nCountX);
							}else{
								m_nPosID_blank_new = m_nPosID_blank-1;
							}
						}
					}else{
						if(m_bFirst_Row1!=m_bSecond_Row1){
							m_nSecond_new = m_nPosID_second + (m_bSecond_Row1?m_nCountX:-m_nCountX);
						}else{
							m_nSecond_new = m_nPosID_second - 1;
						}
						m_nSecond_new_Col = m_nSecond_new % m_nCountX;
						if(m_nBlank_Col<m_nSecond_new_Col){
							m_nPosID_blank_new = m_nPosID_blank + 1;
						}else if(m_nPosID_blank==m_nSecond_new){
							m_nPosID_blank_new = m_nPosID_second;
						}else if(m_nBlank_Col==m_nSecond_new_Col){
							m_nPosID_blank_new = m_nSecond_new;
						}else{
							if(m_nPosID_blank==m_nPosID_second+1){
								m_nPosID_blank_new = m_nPosID_blank + (m_bBlank_Row1?m_nCountX:-m_nCountX);
							}else{
								m_nPosID_blank_new = m_nPosID_blank - 1;
							}
						}
					}
				}
			}

			/*
			m_strDebug.Format("SelectCol=%d[%d,%d]Col[%d,%d],First=%d,FirstPos=%d,FirstNew=%d,"
				"Second=%d,SecondPos=%d,SecondNew=%d,SecondNewCol=%d,"
				"BlankNew=%d",
				m_nSelected_Col, m_nSelected1, m_nSelected2, m_nSelected1_Col, m_nSelected2_Col, m_nFirst, m_nPosID_first, 
				m_nFirst_new, m_nSecond, m_nPosID_second, m_nSecond_new,m_nSecond_new_Col,
				m_nPosID_blank_new);
			ShowStatusString(m_strDebug);
			*/
			if(m_nPosID_blank_new==-1){
				PA_DoGameAutoStop();
				return;
			}
		}else{ //

			INT m_nTarget_Col = m_nSelectedID % m_nCountX;

			INT m_nSelected_Row=m_nPosID_sel / m_nCountX;
			INT m_nSelected_Col=m_nPosID_sel % m_nCountX;

			if(m_nTarget_Col+1==m_nCountX){
				if(m_nPosID_sel==m_nSelectedID+m_nCountX+m_nCountX && m_nPosID_blank==m_nSelectedID+m_nCountX){
					INT A_nPosID_move[10] = {-m_nCountX, -1, m_nCountX, 1, m_nCountX, -1, -m_nCountX, -m_nCountX, 1, m_nCountX};
					memcpy(A_nBufferedMove, A_nPosID_move, sizeof(A_nPosID_move));
					m_nBufferedMove_Count = 10;
					m_nBufferedMove_Current = 1;
					m_nPosID_blank_new = m_nPosID_blank + A_nPosID_move[0];

				}else if(m_nPosID_sel==m_nSelectedID+m_nCountX-1){
					if(m_nPosID_blank==m_nSelectedID + m_nCountX){
						m_nPosID_blank_new = m_nPosID_blank + m_nCountX;
					} else if(m_nPosID_blank==m_nSelectedID + m_nCountX + m_nCountX) {
						m_nPosID_blank_new = m_nPosID_blank - 1;
					}else if(m_nPosID_blank==m_nSelectedID + m_nCountX + m_nCountX - 1) {
						m_nPosID_blank_new = m_nPosID_blank - m_nCountX;
					}
				}else if(m_nPosID_sel==m_nSelectedID+m_nCountX){
					if(m_nPosID_blank==m_nSelectedID){
						m_nPosID_blank_new = m_nPosID_blank + m_nCountX;
					} else if(m_nPosID_blank==m_nSelectedID + m_nCountX - 1) {
						m_nPosID_blank_new = m_nPosID_blank + m_nCountX;
					}else if(m_nPosID_blank==m_nSelectedID + m_nCountX + m_nCountX - 1) {
						m_nPosID_blank_new = m_nPosID_blank + 1;
					}else if(m_nPosID_blank==m_nSelectedID + m_nCountX + m_nCountX){
						m_nPosID_blank_new = m_nPosID_blank - m_nCountX;
					}
				}
			}

			if(m_nPosID_blank_new==-1){

				INT m_nPosID_sel_new;
				if(m_nTarget_Col==m_nSelected_Col){
					m_nPosID_sel_new = m_nPosID_sel - m_nCountX;
				}else if(m_nTarget_Col>m_nSelected_Col){
					m_nPosID_sel_new = m_nPosID_sel + 1;
				}else{ // m_nTarget_Col<m_nSelected_Col
					m_nPosID_sel_new = m_nPosID_sel - 1;
				}


				INT A_nPosID_around[8] = {0};
				INT m_nPosID_around_nCount=8;
				BOOL A_bPosState[4] = {m_nSelected_Row>0, m_nSelected_Row+1<m_nCountY, m_nSelected_Col>0, m_nSelected_Col+1<m_nCountX};
				INT m_nPosID_t;
				m_nPosID_t = m_nPosID_sel - m_nCountX - 1;
				A_nPosID_around[0]=A_bPosState[0] && A_bPosState[2] && m_nPosID_t >= m_nSelectedID ? m_nPosID_t : -1;
				m_nPosID_t = m_nPosID_sel - m_nCountX;
				A_nPosID_around[1]=A_bPosState[0] && m_nPosID_t >= m_nSelectedID ? m_nPosID_t : -1;
				m_nPosID_t = m_nPosID_sel - m_nCountX + 1;
				A_nPosID_around[2]=A_bPosState[0] && A_bPosState[3] && m_nPosID_t >= m_nSelectedID ? m_nPosID_t : -1;
				m_nPosID_t = m_nPosID_sel + 1;
				A_nPosID_around[3]=A_bPosState[3] && m_nPosID_t >= m_nSelectedID ? m_nPosID_t : -1;
				m_nPosID_t = m_nPosID_sel + m_nCountX + 1;
				A_nPosID_around[4]=A_bPosState[1] && A_bPosState[3] && m_nPosID_t >= m_nSelectedID ? m_nPosID_t : -1;
				m_nPosID_t = m_nPosID_sel + m_nCountX;
				A_nPosID_around[5]=A_bPosState[1] && m_nPosID_t >= m_nSelectedID ? m_nPosID_t : -1;
				m_nPosID_t = m_nPosID_sel + m_nCountX -1;
				A_nPosID_around[6]=A_bPosState[1] && A_bPosState[2] && m_nPosID_t >= m_nSelectedID ? m_nPosID_t : -1;
				m_nPosID_t = m_nPosID_sel -1;
				A_nPosID_around[7]=A_bPosState[2] && m_nPosID_t >= m_nSelectedID ? m_nPosID_t : -1;

				INT m_nDirection = 0; // 1左 2上 3右 4下
				INT m_nRange_RowT, m_nRange_RowB;
				INT m_nRange_ColL, m_nRange_ColR;
				m_nRange_RowT = m_nSelected_Row == 0 ? 0 : m_nSelected_Row-1;
				m_nRange_RowB = m_nSelected_Row+1 == m_nCountY ? m_nSelected_Row : m_nSelected_Row+1;
				m_nRange_ColL = m_nSelected_Col == 0 ? 0 : m_nSelected_Col-1;
				m_nRange_ColR = m_nSelected_Col+1 == m_nCountX ? m_nSelected_Col : m_nSelected_Col+1;

				INT m_nDirection_blank=-1;
				if(m_nPosID_sel_new==m_nPosID_blank){

					m_nPosID_blank_new = m_nPosID_sel;

				} else{

					if(m_nBlank_Row<m_nRange_RowT){
						m_nDirection = 4;
					} else if(m_nBlank_Row>m_nRange_RowB){
						m_nDirection = 2;
					} else { // m_nRange_RowT <= m_nBlank_Row <= m_nRange_RowB
						if(m_nPosID_blank==m_nSelectedID){
							m_nDirection = 4;
						}else if(m_nBlank_Col<m_nRange_ColL){
							m_nDirection = 3;
						}else if(m_nBlank_Col>m_nRange_ColR){
							m_nDirection = 1;
						}else { // m_nRange_ColL <= m_nSelected_Col <= m_nRange_ColR
							// 不用处理已经到达的那个，最外层已经处理好了
							// 围绕式移动, 检测最短路径
							for(i=0; i<m_nPosID_around_nCount; i++){
								if(A_nPosID_around[i]==m_nPosID_blank){
									m_nDirection_blank=i;
									break;
								}
							}
							INT m_nDirection_around=0;
							BOOL m_bRoll1 = TRUE;
							BOOL m_bRoll2 = TRUE;
							for(i=1; i<m_nPosID_around_nCount; i++){
								if(m_bRoll1){
									m_nPosID_t = A_nPosID_around[(m_nPosID_around_nCount + m_nDirection_blank - i) % m_nPosID_around_nCount];
									if(m_nPosID_t==-1){
										m_bRoll1 = FALSE;
									} else if(m_nPosID_t==m_nPosID_sel_new){
										m_nDirection_around = -1;
										break;
									}
								}
								if(m_bRoll2){
									m_nPosID_t = A_nPosID_around[(m_nPosID_around_nCount + m_nDirection_blank + i) % m_nPosID_around_nCount];
									if(m_nPosID_t==-1){
										m_bRoll2 = FALSE;
									} else if(m_nPosID_t==m_nPosID_sel_new){
										m_nDirection_around = 1;
										break;
									}
								}
							}
							if(m_nDirection_around==1){
								m_nPosID_blank_new = A_nPosID_around[(m_nPosID_around_nCount + m_nDirection_blank + 1) % m_nPosID_around_nCount];
							}else if(m_nDirection_around==-1){
								m_nPosID_blank_new = A_nPosID_around[(m_nPosID_around_nCount + m_nDirection_blank - 1) % m_nPosID_around_nCount];
							}else{
								PA_DoGameAutoStop();
								AfxMessageBox("Fail");
								return;
							}
						}
					}

					if(m_nDirection){
						switch(m_nDirection){
						case 1:
							m_nPosID_blank_new = m_nPosID_blank - 1;
							break;
						case 2:
							m_nPosID_blank_new = m_nPosID_blank - m_nCountX;
							break;
						case 3:
							m_nPosID_blank_new = m_nPosID_blank + 1;
							break;
						case 4:
							m_nPosID_blank_new = m_nPosID_blank + m_nCountX;
						}
					}

				}

				/*
				m_strDebug.Format("Sel=%d(%d,%d),Target=%d(%d,%d),SelNew=%d(%d,%d),Blank=%d(%d,%d),BlankNew=%d,"
					"around[%d](%d,%d,%d,%d,%d,%d,%d,%d),dir=%d,[%d,%d,%d,%d](%d,%d)",
					m_nPosID_sel, m_nSelected_Row, m_nSelected_Col,
					m_nSelectedID, m_nSelectedID / m_nCountX, m_nTarget_Col,
					m_nPosID_sel_new, m_nPosID_sel_new/m_nCountX, m_nPosID_sel_new%m_nCountX,
					m_nPosID_blank, m_nBlank_Row, m_nBlank_Col,
					m_nPosID_blank_new,
					m_nPosID_around_nCount,
					A_nPosID_around[0], A_nPosID_around[1], A_nPosID_around[2], A_nPosID_around[3],
					A_nPosID_around[4], A_nPosID_around[5], A_nPosID_around[6], A_nPosID_around[7],
					m_nDirection,
					m_nRange_RowT, m_nRange_RowB, m_nRange_ColL, m_nRange_ColR,
					m_nDirection_blank);
				ShowStatusString(m_strDebug);
				*/
			}
		}

		BOOL m_bMoveSucceed = FALSE;
		if(m_nPosID_blank>=0 && m_nPosID_blank<m_nItemCount && 
			m_nPosID_blank_new>=0 && m_nPosID_blank_new<m_nItemCount && 
			(m_nPosID_blank+1==m_nPosID_blank_new || m_nPosID_blank-1==m_nPosID_blank_new ||
			m_nPosID_blank+m_nCountX==m_nPosID_blank_new || m_nPosID_blank-m_nCountX==m_nPosID_blank_new )){
			m_bMoveSucceed = TRUE;
		}

		if(m_bMoveSucceed){
			INT t=A_nCachedID[m_nPosID_blank];
			A_nCachedID[m_nPosID_blank] = A_nCachedID[m_nPosID_blank_new];
			A_nCachedID[m_nPosID_blank_new] = t;
			m_nCountStep++;
		}
		if(m_bMoveSucceed) m_nPosID_blank = m_nPosID_blank_new;
	}

	PA_DoGameCheckSucceed();
	PA_DoGameDisplay();

}

void CChildView::PA_DoGameWinFlash()
{
	static m_nCurX=0;
	CClientDC dc(this);
	for(INT i=0; i<m_nItemCount; i++){
		INT nx = i % m_nCountX;
		int ny = i / m_nCountX;
		CDC * pDC = (nx==m_nCurX) ? &m_cdcGameResDark : &m_cdcGameRes;
		dc.BitBlt(nx * m_nItemWidth1, ny * m_nItemHeight1, m_nItemWidth, m_nItemHeight,
			pDC, A_objItems[i].m_nImageStartX, A_objItems[i].m_nImageStartY, SRCCOPY);
	}
	ReleaseDC(&dc);
	m_nCurX=m_nCurX+1;
	if(m_nCurX>=m_nCountX+20) m_nCurX=0;
}
