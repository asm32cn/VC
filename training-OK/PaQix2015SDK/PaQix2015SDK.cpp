// PaQix2015SDK.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"

#define MAX_LOADSTRING 100

typedef struct {
	INT x1, x2, y1, y2, dx1, dx2, dy1, dy2;
} PaQixPointsDEF;

typedef struct {
	INT r, g, b, Dr, Dg, Db;
} PaQixColorDEF;

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];								// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];								// The title bar text

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

void PA_AppInitialize(HWND hWnd);
void PA_AppFinalize(HWND hWnd);
void PA_DoDisplay(HWND hWnd);

void PA_AlertInfo(LPCTSTR szMessage);

void PA_QixPointsInit(INT nMinD, INT nRangeD);
void PA_QixPointsSetNext();
void PA_QixPointsBackup();
void PA_QixPointsRestore();

void PA_QixColorInit();
void PA_QixColorSetNext();
COLORREF PA_QixGetColor();
COLORREF PA_QixGetColorEx(INT nMax, INT nPos);
void PA_QixColorBackup();
void PA_QixColorRestore();

void PA_QixSetHorizontal();

TCHAR szHello[MAX_LOADSTRING];

RECT rectClient={0};
WORD m_nClientWidth=0;
WORD m_nClientHeight=0;
HDC hdcMemory = NULL;
HBITMAP hBmpMemory = NULL;
HBRUSH hbrBackground=0;
HWND ghWnd = NULL;
INT m_nCount = 255;

INT m_nRangeD;
INT m_nMinD;

PaQixPointsDEF qps={0}, qps_t={0};
PaQixColorDEF qc={0}, qc_t={0};

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_PAQIX2015SDK, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_PAQIX2015SDK);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_PAQIX2015SDK);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCSTR)IDC_PAQIX2015SDK;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ghWnd = hWnd;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message) 
	{
	case WM_SHOWWINDOW:
		PA_AppInitialize(hWnd);
		break;
	case WM_SIZE:
		m_nClientWidth = LOWORD(lParam);
		m_nClientHeight = HIWORD(lParam);
		if(m_nClientWidth>0 && m_nClientHeight>0){
			if(hBmpMemory) DeleteObject(hBmpMemory);
			GetClientRect(hWnd, &rectClient);
			hdc=GetDC(hWnd);
			hBmpMemory=CreateCompatibleBitmap(hdc, m_nClientWidth, m_nClientHeight);
			SelectObject(hdcMemory, hBmpMemory);
			ReleaseDC(hWnd, hdc);
			PA_QixPointsInit(2, 10);
		}
		break;
	case WM_TIMER:
		PA_DoDisplay(hWnd);
		break;
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
				case ID_SET_HORIZONTAL:
					PA_QixSetHorizontal();
					break;
				case ID_SET_RANDOM:
					PA_QixPointsInit(m_nMinD, m_nRangeD);
					break;
				case IDM_ABOUT:
				   DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
				   break;
				case IDM_EXIT:
				   DestroyWindow(hWnd);
				   break;
				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code here...
			//RECT rt;
			//GetClientRect(hWnd, &rt);
			EndPaint(hWnd, &ps);
			PA_DoDisplay(hWnd);
			break;
		case WM_RBUTTONDOWN:
			PA_QixPointsInit(m_nMinD, m_nRangeD);
			break;
		case WM_DESTROY:
			PA_AppFinalize(hWnd);
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

// Mesage handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}

void PA_AppInitialize(HWND hWnd){

/*
	CreateToolbarEx(hWnd,
		WS_CHILD | WS_BORDER | WS_VISIBLE | TBSTYLE_TOOLTIPS,// | TBSTYLE_FLAT,
		IDC_MAINTOOLBAR,
		2,
		hInst,
		IDC_MAINTOOLBAR,
		tbButton,
		sizeof(tbButton)/sizeof(TBBUTTON),
		BUTTONWIDTH,
		BUTTONHEIGHT,
		IMAGEWIDTH,
		IMAGEHEIGHT,
		sizeof(TBBUTTON));
*/

	srand( GetTickCount() ); // 设置随机种子

	LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);

	m_nCount = 255;

	m_nMinD = 2;
	m_nRangeD = 10;


	PA_QixColorInit();

	hbrBackground=CreateSolidBrush(RGB(0, 0, 0));
	HDC hdc;
	hdc=GetDC(hWnd);
	hdcMemory=CreateCompatibleDC(hdc);
	ReleaseDC(hWnd, hdc);
	SetTimer(hWnd, 1, 10, NULL);
}

void PA_AppFinalize(HWND hWnd){
	KillTimer(hWnd, 1);
	ReleaseDC(hWnd, hdcMemory);
	DeleteObject(hBmpMemory);
}

void PA_DoDisplay(HWND hWnd){
	HPEN m_hPen;
	FillRect(hdcMemory, &rectClient, hbrBackground);
	//DrawText(hdcMemory, szHello, strlen(szHello), &rectClient, DT_CENTER);
	for(int i=0; i<m_nCount; i++){
		m_hPen = CreatePen(PS_SOLID, 1, PA_QixGetColorEx(m_nCount, i));
		SelectObject(hdcMemory, m_hPen);
		MoveToEx(hdcMemory, qps.x1, qps.y1, NULL);
		LineTo(hdcMemory, qps.x2, qps.y2);
		DeleteObject(m_hPen);
		if(i==5){
			PA_QixPointsBackup();
			PA_QixColorBackup();
		}
		PA_QixPointsSetNext();
		PA_QixColorSetNext();
	}
	PA_QixPointsRestore();
	PA_QixColorRestore();

	HDC hdc=GetDC(hWnd);
	BitBlt(hdc, 0, 0, m_nClientWidth, m_nClientHeight, hdcMemory, 0, 0, SRCCOPY);
	ReleaseDC(hWnd, hdc);
}

void PA_AlertInfo(LPCTSTR szMessage){
	MessageBox(ghWnd, szMessage, szTitle, MB_OK | MB_ICONINFORMATION);
}

void PA_QixColorInit(){
	qc.r = 10;
	qc.g = 10;
	qc.b = 10;
	qc.Dr = 5;
	qc.Dg = 5;
	qc.Db = 5;
}

void PA_QixColorSetNext(){
	INT nr, ng, nb;
	nb = qc.b + qc.Db;
	if((nb>255 && qc.Db>0) || (nb<0 && qc.Db<0)){
		qc.Db = -qc.Db;
		ng = qc.g + qc.Dg;
		if((ng>255 && qc.Dg>0) || (ng<0 && qc.Dg<0)){
			qc.Dg = -qc.Dg;
			nr = qc.r + qc.Dr;
			if((nr>255 && qc.Dr>0) || (nr<0 && qc.Dr<0)){
				qc.Dr = - qc.Dr;
			}else{
				qc.r = nr;
			}
		}else{
			qc.g = ng;
		}
	}else{
		qc.b = nb;
	}
}

COLORREF PA_QixGetColor(){
	return RGB(qc.r, qc.g, qc.b);
}

COLORREF PA_QixGetColorEx(INT nMax, INT nPos){
	INT m_nMax = nMax>0 ? nMax : 1;
	INT m_nPos = nPos>nMax ? nMax : nPos;
	return RGB(qc.r * m_nPos / m_nMax, qc.g * m_nPos / m_nMax, qc.b * m_nPos / m_nMax);
}

void PA_QixColorBackup(){
	qc_t = qc;
}

void PA_QixColorRestore(){
	qc = qc_t;
}

void PA_QixPointsInit(INT nMinD, INT nRangeD){
	qps.dx1 = nMinD + rand() % nRangeD;
	qps.dy1 = nMinD + rand() % nRangeD;
	qps.dx2 = nMinD + rand() % nRangeD;
	qps.dy2 = nMinD + rand() % nRangeD;

	qps.x1 = rand() % m_nClientWidth;
	qps.y1 = rand() % m_nClientHeight;
	qps.x2 = rand() % m_nClientWidth;
	qps.y2 = rand() % m_nClientHeight;
}

void PA_QixPointsSetNext(){
	INT nx, ny;
	nx = qps.x1 + qps.dx1;
	if((nx>m_nClientWidth && qps.dx1>0) || (nx<0 && qps.dx1<0)){
		qps.dx1 = -qps.dx1;
	}else{
		qps.x1 = nx;
	}
	ny = qps.y1 + qps.dy1;
	if((ny>m_nClientHeight && qps.dy1>0) || (ny<0 && qps.dy1<0)){
		qps.dy1 = -qps.dy1;
	}else{
		qps.y1 = ny;
	}

	nx = qps.x2 + qps.dx2;
	if((nx>m_nClientWidth && qps.dx2>0) || (nx<0 && qps.dx2<0)){
		qps.dx2 = -qps.dx2;
	}else{
		qps.x2 = nx;
	}
	ny = qps.y2 + qps.dy2;
	if((ny>m_nClientHeight && qps.dy2>0) || (ny<0 && qps.dy2<0)){
		qps.dy2 = -qps.dy2;
	}else{
		qps.y2 = ny;
	}
}

void PA_QixPointsBackup(){
	qps_t = qps;
}

void PA_QixPointsRestore(){
	qps = qps_t;
}

void PA_QixSetHorizontal(){
	qps.dx2 = qps.dx1 = m_nMinD + rand() % m_nRangeD;
	qps.dy2 = qps.dy1 = 0;
	qps.x2 = qps.x1;
	qps.y1 = 0;
	qps.y2 = m_nClientHeight;

}