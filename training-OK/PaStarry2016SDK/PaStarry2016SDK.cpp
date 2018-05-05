// PaStarry2016SDK.cpp : Defines the entry point for the application.
//

/*
错误：unexpected end of file while looking for precompiled headerdirective
分析：工程头文件处理的错误。
解决办法如下：
1、右键点工程名,选设置,然后选c/c++属性页,再选catagory选单中选 precompiled header ,将选项置成no use 或者autometic
2、如果使用的是Win32工程，可能就是错误文件没有包含：#include "stdafx.h" ，添加该包含即可。
*/

#include <windows.h>
#include <stdio.h>
#include "resource.h"

#define PA_TIMER_INTERVAL 500

typedef struct {
	INT x;
	INT y;
	INT r;
	COLORREF color;
} PaStarryItem;


char szTitle[32]="PaStarry2016SDK";                 //窗口的标题
char szWindowClass[32]="PaStarry2016SDK"; //窗口的名称


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void PA_DoAppInitialize();
void PA_DoAppFinalize();

void PA_DoStarryInit();
void PA_DoStarryItemInit(PaStarryItem &psi1);
void PA_DoSarryItemRefresh();
void PA_DoStarryDisplay();

UINT nTimerID = 1;

HBRUSH hbrBackground;
WORD nClientWidth;
WORD nClientHeight;
RECT rectClient = {0};

HWND ghWnd = NULL;
HINSTANCE ghInstance = NULL;

INT psi_nCount = 50;
INT psi_nRefresh = 0;
PaStarryItem psi[50]={0};


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
    //wc.hIcon         = LoadIcon(hInstance, (LPCTSTR)IDI_APPLICATION);
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
				PA_DoStarryInit();
			}
		}
		break;
	case WM_TIMER:
		PA_DoSarryItemRefresh();
		PA_DoStarryDisplay();
		break;
    case WM_PAINT:                         //窗口刷新
		{
			HDC hdc;                       //设备文句柄
			PAINTSTRUCT ps;                //客户描画区信息
			hdc = BeginPaint(hWnd, &ps);   //取得设备环境句柄并开始描画
			EndPaint(hWnd, &ps);           //结束描画
			PA_DoStarryDisplay();
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
	SetTimer(ghWnd, nTimerID, 20, NULL);
}

void PA_DoAppFinalize(){
	KillTimer(ghWnd, nTimerID);
}

void PA_DoStarryInit(){
	for(INT i=0; i<psi_nCount; i++){
		PA_DoStarryItemInit(psi[i]);
	}
	char szBuffer[512] = {0};
	sprintf(szBuffer, "%d %d %x", psi[0].x, psi[0].y, psi[0].color);
	//MessageBox(ghWnd, szBuffer, szTitle, MB_OK);
}

void PA_DoStarryItemInit(PaStarryItem &psi1){
	psi1.x = rand()%nClientWidth;
	psi1.y = rand()%nClientHeight;
	psi1.color = RGB(rand()%255, rand()%255, rand()%255);
	psi1.r = 2 + rand()%3;
}

void PA_DoSarryItemRefresh(){
	psi_nRefresh = psi_nRefresh+1;
	if(psi_nRefresh>=psi_nCount) psi_nRefresh=0;
	PA_DoStarryItemInit(psi[psi_nRefresh]);
}

void PA_DoStarryDisplay(){
	HDC hdc=GetDC(ghWnd);
	HBRUSH hBrush;
	HPEN hPen;
	FillRect(hdc, &rectClient, hbrBackground);
	for(INT i=0; i<psi_nCount; i++){
		INT x = psi[i].x;
		INT y = psi[i].y;
		INT r = psi[i].r;
		hBrush = CreateSolidBrush(psi[i].color);
		hPen = CreatePen(PS_SOLID, 1, psi[i].color);
		SelectObject(hdc, hBrush);
		SelectObject(hdc, hPen);
		Ellipse(hdc, x-r, y-r, x+r, y+r); 
		DeleteObject(hBrush);
		DeleteObject(hPen);
	}
	ReleaseDC(ghWnd, hdc);
}