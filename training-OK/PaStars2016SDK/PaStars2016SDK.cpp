// PaStars2016SDK.cpp : Defines the entry point for the application.
//

/*
错误：unexpected end of file while looking for precompiled headerdirective
分析：工程头文件处理的错误。
解决办法如下：
1、右键点工程名,选设置,然后选c/c++属性页,再选catagory选单中选 precompiled header ,将选项置成no use 或者autometic
2、如果使用的是Win32工程，可能就是错误文件没有包含：#include "stdafx.h" ，添加该包含即可。
*/

#include <windows.h>
#include <math.h>
#include "resource.h"
#include <stdio.h>

#define nTimerInterval 200


char szTitle[32]="PaStars2016SDK";                 //窗口的标题
char szWindowClass[32]="PaStars2016SDK"; //窗口的名称


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void PA_DoAppInitialize();
void PA_DoAppFinalize();
void PA_DoWindowResize();
void PA_DoStarInit(int i);
void PA_DoDisplay();

UINT nTimerID = 1;

HBRUSH hbrBackground;
WORD nClientWidth;
WORD nClientHeight;
RECT rectClient = {0};

HWND ghWnd = NULL;
HINSTANCE ghInstance = NULL;

int nCount = 30;
int nSelected = 0;
POINT A_points[30][10] = {0};
COLORREF A_colors[30] = {0};
double PI2 = 6.283185307179586;
HBRUSH hbrStar = NULL;
BOOL isDisplay = FALSE;

HBITMAP hbmMemory = NULL;
HDC hdcMemory = NULL;

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
			if(nClientWidth>0 && nClientHeight>0){
				GetClientRect(hWnd, &rectClient);
				if(hbmMemory) DeleteObject(hbmMemory);
				HDC hdc = GetDC(ghWnd);
				hbmMemory = CreateCompatibleBitmap(hdc, nClientWidth, nClientHeight);
				SelectObject(hdcMemory, hbmMemory);
				ReleaseDC(ghWnd, hdc);
				PA_DoWindowResize();
				isDisplay = TRUE;
			}else{
				isDisplay = FALSE;
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
		nSelected = (nSelected + 1) % nCount;
		if(isDisplay){
			PA_DoStarInit(nSelected);
			PA_DoDisplay();
		}
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
	hbrStar = CreateSolidBrush(RGB(255, 255, 255));
	SetTimer(ghWnd, nTimerID, nTimerInterval, NULL);
	HDC hdc = GetDC(ghWnd);
	hdcMemory = CreateCompatibleDC(hdc);
	ReleaseDC(ghWnd, hdc);
}

void PA_DoAppFinalize(){
	KillTimer(ghWnd, nTimerID);
	ReleaseDC(ghWnd, hdcMemory);
	DeleteObject(hbmMemory);
}

void PA_DoWindowResize(){
	for(int i=0; i<nCount; i++){
		PA_DoStarInit(i);
	}
}

void PA_DoStarInit(int i){
	int r = 20  + rand() % (nClientWidth / 20);
	int cx = r + rand() % (nClientWidth - r - r);
	int cy = r + rand() % (nClientHeight - r - r);
	int r1 = r / 2;
	double a1 = PI2 / 10;
	for(int n=0; n<5; n++){
		int id = n + n;
		double a2 = PI2 * n / 5;
		A_points[i][id].x = cx + (int)(r * sin(a2));
		A_points[i][id].y = cy - (int)(r * cos(a2));
		a2 += a1;
		A_points[i][id+1].x = cx + (int)(r1 * sin(a2));
		A_points[i][id+1].y = cy - (int)(r1 * cos(a2));
	}
	A_colors[i] = RGB(rand() % 256, rand() % 256, rand() % 256);
}

void PA_DoDisplay(){
	if(!isDisplay) return;
	HDC hdc = GetDC(ghWnd);
	HPEN hPen, hOldPen;  //画笔
	HBRUSH hBrush, hOldBrush;
	FillRect(hdcMemory, &rectClient, hbrBackground);
	for(int i=0; i<nCount; i++){
		hPen = CreatePen(PS_SOLID, 1, A_colors[i]);  //画笔
		hOldPen = (HPEN)SelectObject(hdcMemory, hPen);  //选用新笔保存旧笔
		hBrush = CreateSolidBrush(A_colors[i]);
		hOldBrush = (HBRUSH)SelectObject(hdcMemory, hBrush);
		Polygon(hdcMemory, A_points[i], 10);
		SelectObject(hdcMemory, hOldPen);  //恢复旧笔
		SelectObject(hdcMemory, hOldBrush);
		DeleteObject(hPen);  //删除新笔
		DeleteObject(hBrush);
	}
	BitBlt(hdc, 0, 0, nClientWidth, nClientHeight, hdcMemory, 0, 0, SRCCOPY);
	ReleaseDC(ghWnd, hdc);
}