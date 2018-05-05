// PaDigitalClock2015SDK.cpp : Defines the entry point for the application.
//

/*
错误：unexpected end of file while looking for precompiled headerdirective
分析：工程头文件处理的错误。
解决办法如下：
1、右键点工程名,选设置,然后选c/c++属性页,再选catagory选单中选 precompiled header ,将选项置成no use 或者autometic
2、如果使用的是Win32工程，可能就是错误文件没有包含：#include "stdafx.h" ，添加该包含即可。
*/

#include <windows.h>
#include "resource.h"

#define PA_TIMER_INTERVAL 500


char szTitle[32]="PaDigitalClock2015SDK";                 //窗口的标题
char szWindowClass[32]="PaDigitalClock2015SDK"; //窗口的名称

char szBuffer[512] = {0};


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void PA_DoAppInitialize();
void PA_DoAppFinalize();
void PA_DoClockDisplay();
void PA_DoInitBitmapChars();
void PA_DoClockDisplayChar(HDC hdc, INT nItem, INT nOffsetX, INT nOffsetY);

UINT nTimerID = 1;
HDC hdcChars = NULL;
HBITMAP hBmpChars = NULL;
HBRUSH hbrBackground;
WORD nClientWidth;
WORD nClientHeight;
WORD * A_wordDigitMatrix;
WORD A_wordMask[12] = {2048, 1024, 512, 256, 128, 64, 32, 16, 8, 4, 2, 1};
RECT rectClient = {0};
CHAR A_nCharID[12]={0};
CHAR A_nCharID_t[12]={0};
BOOL isRefresh = TRUE;

INT nBmpCharsWidth;
INT nBmpCharsHeight;
INT nBmpCharWidth;
INT nBmpCharHeight;
SYSTEMTIME tmSystem;
HWND ghWnd = NULL;
HINSTANCE ghInstance = NULL;

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow) {
    MSG msg;
    WNDCLASSEX wc;		//定义一个窗口类，下面赋初值
    HWND hWnd = NULL;

	hbrBackground = CreateSolidBrush(RGB(0, 0, 0));

    wc.cbSize        = sizeof(WNDCLASSEX);                  //类的字节长度
    wc.style         = CS_HREDRAW | CS_VREDRAW;             //窗口式样
    wc.lpfnWndProc   = (WNDPROC)WndProc;                    //窗口处理函数
    wc.cbClsExtra    = 0;                                   //分配给窗口类结构之后的额外字节数
    wc.cbWndExtra    = 0;                                   //
    wc.hInstance     = hInstance;                           //实例句柄
    wc.hIcon         = LoadIcon(hInstance, (LPCTSTR)IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);         //光标
//  wc.hbrBackground = (HBRUSH)GetStockObject(COLOR_WINDOWFRAME);//背景
    wc.hbrBackground = hbrBackground;
    wc.lpszMenuName  = NULL;                                //菜单
    wc.lpszClassName = szWindowClass;                       //窗口名
    wc.hIconSm       = LoadIcon(wc.hInstance, (LPCTSTR)IDI_APPLICATION);

    if(!RegisterClassEx(&wc)) return FALSE;

    //创建窗口
    hWnd = CreateWindow( szWindowClass,      //窗口名
                         szTitle,            //窗口标题
                         WS_OVERLAPPEDWINDOW,//窗口风格
                         100,                //窗口左上角的x坐标
                         100,                //窗口左上角的y坐标
                         CW_USEDEFAULT,      //窗口的宽度
                         CW_USEDEFAULT,      //窗口的高度
                         NULL,               //父窗口句柄
                         NULL,               //菜单句柄
                         hInstance,          //实例句柄
                         NULL);              //创建参数

    if (!hWnd) {
       return FALSE;
    }

	ghInstance = hInstance;
	ghWnd = hWnd;

    ShowWindow(hWnd, nCmdShow);	          //显示窗口
    UpdateWindow(hWnd);                   //立即显示

    while (GetMessage(&msg, NULL, 0, 0)){ //消息循环
        TranslateMessage(&msg);	          //消息解释
        DispatchMessage(&msg);            //消息发送
    }

    return msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message)
    {
	case WM_SHOWWINDOW:
		PA_DoAppInitialize();
		break;
	case WM_SIZE:
		{
			nClientWidth  = LOWORD(lParam);
			nClientHeight = HIWORD(lParam);
			if(nClientWidth>0 && nClientHeight>0){
				GetClientRect(hWnd, &rectClient);
				PA_DoInitBitmapChars();
			}
			isRefresh = TRUE;
		}
		break;
	case WM_TIMER:
		PA_DoClockDisplay();
		break;
    case WM_PAINT:                         //窗口刷新
		{
			HDC hdc;                       //设备文句柄
			PAINTSTRUCT ps;                //客户描画区信息
			hdc = BeginPaint(hWnd, &ps);   //取得设备环境句柄并开始描画
			isRefresh = TRUE;
			PA_DoClockDisplay();
			EndPaint(hWnd, &ps);           //结束描画
		}
        break;
    case WM_DESTROY:                       //关闭窗口
        PostQuitMessage(0);                //发送关闭消息
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

void PA_DoAppInitialize(){
	HRSRC hrsrc = FindResource(ghInstance, MAKEINTRESOURCE(IDR_DIGIT_MATRIX), "BIN");
	A_wordDigitMatrix = hrsrc ? (WORD *)LoadResource(ghInstance, hrsrc) : NULL;
	HDC hdc = GetDC(ghWnd);
	hdcChars = CreateCompatibleDC(hdc);
	ReleaseDC(ghWnd, hdc);

	SetTimer(ghWnd, nTimerID, 10, NULL);
}

void PA_DoAppFinalize(){
	KillTimer(ghWnd, nTimerID);
}

void PA_DoInitBitmapChars(){
	INT m_nCellSize = nClientWidth / 132;
	INT m_nOffset = 0;
	INT m_nOffsetX = 0;

	if(m_nCellSize<3) m_nCellSize=3;

	if(hBmpChars) DeleteObject(hBmpChars);


	nBmpCharWidth  = m_nCellSize * 12;
	nBmpCharHeight = m_nCellSize * 22;

	nBmpCharsWidth  = nBmpCharWidth * 13;
	nBmpCharsHeight = nBmpCharHeight;

	HDC hdc=GetDC(ghWnd);
	hBmpChars = CreateCompatibleBitmap(hdc, nBmpCharsWidth, nBmpCharsHeight);
	SelectObject(hdcChars, hBmpChars);
	ReleaseDC(ghWnd, hdc);

	RECT m_rectBmpChars = {0, 0, nBmpCharsWidth, nBmpCharsHeight};
	m_rectBmpChars.right = nBmpCharsWidth;
	m_rectBmpChars.bottom = nBmpCharsHeight;
	HBRUSH m_hbrBackground = CreateSolidBrush(RGB(0, 0, 255));
	FillRect(hdcChars, &m_rectBmpChars, m_hbrBackground);

	HBRUSH m_hbrChar=CreateSolidBrush(RGB(255, 255, 255));
	HPEN m_hPenChar = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	SelectObject(hdcChars, m_hPenChar);
	SelectObject(hdcChars, m_hbrChar);
	for(int n=0; n<12; n++){
		m_nOffsetX = n * nBmpCharWidth;
		for(int i=0; i<22; i++){
			int m_nStartY = i * m_nCellSize + m_nCellSize;
			for(int j=0; j<12; j++){
				if(A_wordMask[j] & A_wordDigitMatrix[i+m_nOffset]){
					INT m_nStartX = m_nOffsetX + j * m_nCellSize;
					Ellipse(hdcChars, m_nStartX, m_nStartY, m_nStartX+m_nCellSize-1, m_nStartY+m_nCellSize-1);
					//Ellipse(hdcChars, m_nStartX, m_nStartY, m_nStartX+m_nCellSize, m_nStartY+m_nCellSize);
					//Rectangle(hdcChars, m_nStartX, m_nStartY, m_nStartX+m_nCellSize-1, m_nStartY+m_nCellSize-1);
					//Rectangle(hdcChars, m_nStartX, m_nStartY, m_nStartX+m_nCellSize, m_nStartY+m_nCellSize);
				}
			}
		}
		m_nOffset += 22;
	}

	DeleteObject(m_hbrBackground);
	DeleteObject(m_hPenChar);
	DeleteObject(m_hbrChar);
}

void PA_DoClockDisplay(){

	if(IsIconic(ghWnd)) return; // 如果是最小化状态就没必要重绘了

	GetLocalTime(&tmSystem);
	HDC hdc = GetDC(ghWnd);

	//for(int i=0; i<12; i++){
	//	BitBlt(hdc, i*m_nBmpCharWidth, 0, m_nBmpCharWidth, m_nBmpCharHeight, hdcChars, i*nBmpCharWidth, 0, SRCCOPY);
	//}

	INT i;
	INT m_nMaxChars = 11; //12:00:00.000
	//INT m_nMaxChars = 11; //12:00:00.00

	INT m_nOffsetX = (nClientWidth - nBmpCharWidth*m_nMaxChars)/2;
	INT m_nOffsetY = (nClientHeight - nBmpCharsHeight)/2;

	//strncpy(A_nCharID_t, A_nCharID, 12); // 有时候不会完整复制所有字节
	memcpy(A_nCharID_t, A_nCharID, 12);    // 完整复制所有字节

	CHAR m_cSplitter1 = tmSystem.wMilliseconds<500 ? 10 : 12;
	A_nCharID[0]=tmSystem.wHour/10;
	A_nCharID[1]=tmSystem.wHour%10;
	A_nCharID[2]=m_cSplitter1; // :
	A_nCharID[3]=tmSystem.wMinute/10;
	A_nCharID[4]=tmSystem.wMinute%10;
	A_nCharID[5]=m_cSplitter1;	// :
	A_nCharID[6]=tmSystem.wSecond/10;
	A_nCharID[7]=tmSystem.wSecond%10;
	A_nCharID[8]=11;	// .
	A_nCharID[9]=tmSystem.wMilliseconds/100;
	A_nCharID[10]=tmSystem.wMilliseconds/10%10;
	//A_nCharID[11]=tmSystem.wMilliseconds%10;

	for(i=0; i<11; i++){
		if(isRefresh || A_nCharID[i]!=A_nCharID_t[i]){
			PA_DoClockDisplayChar(hdc, A_nCharID[i], m_nOffsetX, m_nOffsetY);
		}
		m_nOffsetX += nBmpCharWidth;
	}
	isRefresh = FALSE;

	ReleaseDC(ghWnd, hdc);

}

void PA_DoClockDisplayChar(HDC hdc, INT nItem, INT nOffsetX, INT nOffsetY){
	INT m_nOffsetX = nItem * nBmpCharWidth;
	BitBlt(hdc, nOffsetX, nOffsetY, nBmpCharWidth, nBmpCharHeight, hdcChars, m_nOffsetX, 0, SRCCOPY);
}

