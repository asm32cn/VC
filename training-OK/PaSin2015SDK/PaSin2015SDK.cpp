// PaSin2015SDK.cpp : Defines the entry point for the application.
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

#define PA_TIMER_INTERVAL 500


char szTitle[32]="PaSin2015SDK";                 //窗口的标题
char szWindowClass[32]="PaSin2015SDK"; //窗口的名称


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void PA_DoAppInitialize();
void PA_DoAppFinalize();

void PA_DoDisplay();

UINT nTimerID = 1;

HBRUSH hbrBackground;
HBRUSH hbrDraw;
WORD nClientWidth;
WORD nClientHeight;
RECT rectClient = {0};

HWND ghWnd = NULL;
HINSTANCE ghInstance = NULL;

DOUBLE PI = 3.141593f;
INT m_nCount = 200;
INT m_nOffset = 0;

HDC hdcMemory = NULL;
HBITMAP hBmpMemory = NULL;
BOOL isDisplay = FALSE;


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
				HDC hdc=GetDC(hWnd);
				hBmpMemory=CreateCompatibleBitmap(hdc, nClientWidth, nClientHeight);
				SelectObject(hdcMemory, hBmpMemory);
				ReleaseDC(hWnd, hdc);
				isDisplay = TRUE;
			}else{
				isDisplay = FALSE;
			}
		}
		break;
	case WM_TIMER:
		m_nOffset = (m_nOffset + 5) % m_nCount;
		PA_DoDisplay();
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
	SetTimer(ghWnd, nTimerID, 10, NULL);
	hbrDraw = CreateSolidBrush(RGB(255,255,0));
	HDC hdc;
	hdc=GetDC(ghWnd);
	hdcMemory=CreateCompatibleDC(hdc);
	SelectObject(hdcMemory, hbrDraw);
	ReleaseDC(ghWnd, hdc);
}

void PA_DoAppFinalize(){
	KillTimer(ghWnd, nTimerID);
	DeleteObject(hbrDraw);
	ReleaseDC(ghWnd, hdcMemory);
	DeleteObject(hBmpMemory);
}

void PA_DoDisplay(){
	if(!isDisplay) return;

	FillRect(hdcMemory, &rectClient, hbrBackground);
	//INT m_nCount = 200;
	//INT m_nOffset = 10;
	for(INT i=0; i<m_nCount; i++){
		INT pos = (m_nOffset + i)%200;
		DOUBLE sin1 = sin(PI*2*pos/m_nCount);
		INT h = (INT)(nClientHeight/2*sin1);
		INT x = nClientWidth * i / m_nCount;
		INT y = nClientHeight/2 + h;
		INT y2 = nClientHeight/2 + h*9/10;
		Rectangle(hdcMemory, x-2, y, x+2, y2);
	}

	HDC hdc = GetDC(ghWnd);
	BitBlt(hdc, 0, 0, nClientWidth, nClientHeight, hdcMemory, 0, 0, SRCCOPY);
	ReleaseDC(ghWnd, hdc);
}
