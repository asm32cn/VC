// PaClock2016SDK.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

/*
错误：unexpected end of file while looking for precompiled headerdirective
分析：工程头文件处理的错误。
解决办法如下：
1、右键点工程名,选设置,然后选c/c++属性页,再选catagory选单中选 precompiled header ,将选项置成no use 或者autometic
2、如果使用的是Win32工程，可能就是错误文件没有包含：#include "stdafx.h" ，添加该包含即可。
*/
#include <math.h>
#include <stdio.h>

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#include <objidl.h>
#include <ocidl.h>
#include <olectl.h>

#include <windows.h>
#include "resource.h"

#define PA_TIMER_INTERVAL 500

double PI = 3.141592653;

char szTitle[32]="PaClock2016SDK";                 //窗口的标题
char szWindowClass[32]="PaClock2016SDK"; //窗口的名称


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void PA_DoAppInitialize();
void PA_DoAppFinalize();
void PA_DoLoadFace();
void PA_DoCacheInterface();
void PA_DoDisplay();
void PA_DoDisplayHand(HDC hdc, POINT &ptCenter, double fAngle, double fBegin, double fEnd);
void PA_DoBeep();

UINT nTimerID = 1;

HBRUSH hbrBackground;
WORD nClientWidth;
WORD nClientHeight;
RECT rectClient = {0};

HWND ghWnd = NULL;
HINSTANCE ghInstance = NULL;

INT clock_nDiameter;
INT clock_nRadius;

HFONT hFont;

HPEN hPen3;
HPEN hPen5;
HPEN hPen7;

SIZE sizeFace = {239, 261};
POINT ptFaceOffset = {105, 130};
HBITMAP hbmFace = NULL;
HDC     hdcFace = NULL;

HBITMAP hbmInterface = NULL;
HDC     hdcInterface = NULL;

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow) {
    MSG msg;
    WNDCLASSEX wc;		//定义一个窗口类，下面赋初值
    HWND hWnd = NULL;

	hbrBackground = CreateSolidBrush(RGB(255, 255, 255));

    wc.cbSize        = sizeof(WNDCLASSEX);                  //类的字节长度
    wc.style         = CS_HREDRAW | CS_VREDRAW;             //窗口式样
    wc.lpfnWndProc   = (WNDPROC)WndProc;                    //窗口处理函数
    wc.cbClsExtra    = 0;                                   //分配给窗口类结构之后的额外字节数
    wc.cbWndExtra    = 0;                                   //
    wc.hInstance     = hInstance;                           //实例句柄
//  wc.hIcon         = LoadIcon(hInstance, (LPCTSTR)IDI_APPLICATION);
    wc.hIcon         = LoadIcon(hInstance, (LPCTSTR)IDI_ICON1);
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
			//INT clock_nDiameter = nClientWidth>nClientHeight ? nClientHeight : nClientWidth;
			clock_nDiameter = nClientWidth>nClientHeight ? nClientHeight : nClientWidth;
			if(clock_nDiameter>0) clock_nDiameter = clock_nDiameter * 19 / 20;
			clock_nRadius = clock_nDiameter / 2;
			if(nClientWidth>0 && nClientHeight>0){
				GetClientRect(hWnd, &rectClient);
				PA_DoCacheInterface();
			}

		}
		break;
    case WM_PAINT:                         //窗口刷新
		{
			HDC hdc;                       //设备文句柄
			PAINTSTRUCT ps;                //客户描画区信息
			hdc = BeginPaint(hWnd, &ps);   //取得设备环境句柄并开始描画
			EndPaint(hWnd, &ps);           //结束描画
			PA_DoDisplay();
		}
        break;
	case WM_TIMER:
		PA_DoDisplay();
		PA_DoBeep();
		break;
    case WM_DESTROY:                       //关闭窗口
        PA_DoAppFinalize();
        PostQuitMessage(0);                //发送关闭消息
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

void PA_DoAppInitialize(){

    hFont = CreateFont(48,  //字体的逻辑高度
        0,  //逻辑平均字符宽度
        0,  //与水平线的角度
        0,  //基线方位角度
        FW_REGULAR,  //字形：常规
        FALSE,  //字形：斜体
        FALSE,  //字形：下划线
        FALSE,  //字形：粗体
        ANSI_CHARSET,  //字符集
        OUT_DEFAULT_PRECIS,  //输出精度
        CLIP_DEFAULT_PRECIS,  //剪截精度
        PROOF_QUALITY,  //输出品质
        FIXED_PITCH | FF_MODERN, //倾斜度
        "Arial Black");  //字体

	hPen3 = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
	hPen5 = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
	hPen7 = CreatePen(PS_SOLID, 7, RGB(0, 0, 0));

	HDC hdc = GetDC(ghWnd);
	hdcInterface = CreateCompatibleDC(hdc);
	ReleaseDC(ghWnd, hdc);

	PA_DoLoadFace();

	SetTimer(ghWnd, nTimerID, 1000, NULL);
}

void PA_DoAppFinalize(){
	KillTimer(ghWnd, nTimerID);
	DeleteObject(hPen3);
	DeleteObject(hPen5);
	DeleteObject(hPen7);
	DeleteObject(hFont);

	DeleteObject(hdcFace);
	DeleteObject(hbmFace);
	DeleteObject(hdcInterface);
	DeleteObject(hbmInterface);
}

void PA_DoLoadFace(){
	HDC hdc = GetDC(ghWnd);
	hdcFace = CreateCompatibleDC(hdc);
	hbmFace = CreateCompatibleBitmap(hdc, sizeFace.cx, sizeFace.cy);
	SelectObject(hdcFace, hbmFace);
	ReleaseDC(ghWnd, hdc);

	// 开始绘制资源里的JPEG图像到缓存里
	// 处理 JPEG GIF 图片资源
	HRSRC hrsrc = FindResource(ghInstance, MAKEINTRESOURCE(IDR_GIF1), "GIF");
	//HRSRC hrsrc = FindResource(ghInstance, MAKEINTRESOURCE(IDR_JPEG1), "JPEG");
	LPVOID lpFaceData = LoadResource(ghInstance,  hrsrc);

	if(lpFaceData){
		//DWORD dwSize = 9004;//6302;
		DWORD dwSize = SizeofResource(ghInstance, hrsrc);

		HGLOBAL hFaceData = ::GlobalAlloc( GMEM_MOVEABLE, dwSize ); 
		LPVOID  pData = ::GlobalLock( hFaceData ); 
		memcpy(pData, lpFaceData, dwSize);
		::GlobalUnlock( hFaceData ); 

		IStream * pStream  = NULL; 
		if(S_OK == ::CreateStreamOnHGlobal( hFaceData, TRUE, &pStream ) )
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
				pPicture->Render( hdcFace, 0, 0, sizeFace.cx, sizeFace.cy, 0, hmHeight, hmWidth, -hmHeight, NULL ); 
				pPicture->Release();
			}
			// 释放流和文件 
			pStream->Release();
		}

		::GlobalFree(hFaceData);
	}

}

void PA_DoCacheInterface(){
	if(hbmInterface) DeleteObject(hbmInterface);
	HDC hdc = GetDC(ghWnd);
	hbmInterface = CreateCompatibleBitmap(hdc, clock_nDiameter, clock_nDiameter);
	ReleaseDC(ghWnd, hdc);
	SelectObject(hdcInterface, hbmInterface);

	SelectObject(hdcInterface, hFont);

	RECT rectInterface = {0, 0, clock_nDiameter, clock_nDiameter};

	FillRect(hdcInterface, &rectInterface, hbrBackground);

	CHAR szDigit[3] = {0};
	//POINT pt = {nClientWidth/2, nClientHeight/2};

	SelectObject(hdcInterface, hPen5);
	Ellipse(hdcInterface, 2, 2, clock_nDiameter-2, clock_nDiameter-2);

	BitBlt(hdcInterface, clock_nRadius-ptFaceOffset.x, clock_nRadius-ptFaceOffset.y, sizeFace.cx, sizeFace.cy, hdcFace, 0, 0, SRCCOPY);

	INT r = clock_nRadius/40;
	Ellipse(hdcInterface, clock_nRadius - r, clock_nRadius - r, clock_nRadius + r, clock_nRadius + r);

	SetTextColor(hdcInterface, RGB(87, 183, 119));

	SetBkMode(hdcInterface, TRANSPARENT);

	INT i;
	for(i=0; i<60; i++){
		double a = sin(PI * i / 30)*(clock_nRadius-5);
		double b = cos(PI * i / 30)*(clock_nRadius-5);
		double st;
		if(i%5){
			st = 0.95;
			SelectObject(hdcInterface, hPen5);
		}else{
			st = 0.9;
			SelectObject(hdcInterface, hPen7);
			sprintf(szDigit, "%d", i/5);
			TextOut(hdcInterface, clock_nRadius+(int)(a*0.8)-9, clock_nRadius-(int)(b*0.8)-24, szDigit, strlen(szDigit));
		}
		MoveToEx(hdcInterface, clock_nRadius+(int)(a*st), clock_nRadius-(int)(b*st), NULL);
		LineTo(hdcInterface, clock_nRadius+(int)a, clock_nRadius-(int)b);
	}

}

void PA_DoDisplay(){
	HDC hdc = GetDC(ghWnd);
	SYSTEMTIME tmNow;
	GetLocalTime(&tmNow);

	char szDisplay[128] = {0};
	sprintf(szDisplay, "%d-%02d-%02d %02d:%02d:%02d", tmNow.wYear, tmNow.wMonth, tmNow.wDay, tmNow.wHour, tmNow.wMinute, tmNow.wSecond);
	TextOut(hdc, 0, 0, szDisplay, 19);

	POINT pt = {nClientWidth/2, nClientHeight/2};

	BitBlt(hdc, pt.x - clock_nRadius, pt.y - clock_nRadius, clock_nDiameter, clock_nDiameter, hdcInterface, 0, 0, SRCCOPY);

	//12 * 60 * 60 = 43200;
	SelectObject(hdc, hPen7);
	PA_DoDisplayHand(hdc, pt, PI*2*(60 * ( 60 * ( tmNow.wHour % 12 ) + tmNow.wMinute) + tmNow.wSecond)/43200, 0.05, 0.4);
	SelectObject(hdc, hPen5);
	PA_DoDisplayHand(hdc, pt, PI*2*(60 * tmNow.wMinute + tmNow.wSecond)/3600, 0.05, 0.5);
	SelectObject(hdc, hPen3);
	PA_DoDisplayHand(hdc, pt, PI*2*tmNow.wSecond/60, 0.05, 0.7);


	ReleaseDC(ghWnd, hdc);
}

void PA_DoDisplayHand(HDC hdc, POINT &ptCenter, double fAngle, double fBegin, double fEnd){
	double a1 = sin(fAngle)*clock_nRadius;
	double b1 = cos(fAngle)*clock_nRadius;
	MoveToEx(hdc, ptCenter.x + (int)(a1*fBegin), ptCenter.y - (int)(b1*fBegin), NULL);
	LineTo(hdc, ptCenter.x + (int)(a1*fEnd), ptCenter.y - (int)(b1*fEnd));
}

void PA_DoBeep(){
	::PlaySound((LPCTSTR)IDR_CLICK,ghInstance,SND_RESOURCE|SND_ASYNC);
}