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
#include <math.h>
#include "resource.h"

//#define PA_TIMER_INTERVAL 500


char szTitle[32]="PaEllipse2016SDK";                 //窗口的标题
char szWindowClass[32]="PaEllipse2016SDK"; //窗口的名称


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void PA_DoAppInitialize();
void PA_DoAppFinalize();

void PA_DoEllipseDisplay();
void PA_DoEllipseRotate();


UINT nTimerID = 1;

HBRUSH hbrBackground;
HBRUSH hbrEllipse;
HPEN hpenEllipse;
WORD nClientWidth;
WORD nClientHeight;
RECT rectClient = {0};

HWND ghWnd = NULL;
HINSTANCE ghInstance = NULL;

DOUBLE fStartAngle = 0;
DOUBLE PI = 3.141593F;

typedef struct {
	INT x;
	INT y;
	INT a;
	INT b;
	DOUBLE angle;
	DOUBLE rotate;
} PaEllipseSettings;

PaEllipseSettings pes1={0, 0, 300, 75, 0, 0}, pes2={0, 0, 50, 200, 0, 0};

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
			}
		}
		break;
	case WM_TIMER:
		PA_DoEllipseRotate();
		PA_DoEllipseDisplay();
		break;
    case WM_PAINT:                         //窗口刷新
		{
			HDC hdc;                       //设备文句柄
			PAINTSTRUCT ps;                //客户描画区信息
			hdc = BeginPaint(hWnd, &ps);   //取得设备环境句柄并开始描画
			EndPaint(hWnd, &ps);           //结束描画
			PA_DoEllipseDisplay();
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
	COLORREF color = RGB(255,255,0);
	hbrEllipse = CreateSolidBrush(color);
	hpenEllipse = CreatePen(PS_SOLID, 1, color);
	SetTimer(ghWnd, nTimerID, 20, NULL);
}

void PA_DoAppFinalize(){
	KillTimer(ghWnd, nTimerID);
	DeleteObject(hbrBackground);
	DeleteObject(hbrEllipse);
}

void Rotate(INT &x, INT &y, DOUBLE angle){
	DOUBLE sin1 = sin(angle);
	DOUBLE cos1 = cos(angle);
	DOUBLE x1 = x, y1 = y;
	x = (INT)(cos1 * x1 - sin1 * y1);
	y = (INT)(cos1 * y1 + sin1 * x1);
}

void PA_DoEllipseDisplay(){
	INT x0 = nClientWidth/2;
	INT y0 = nClientHeight/2;
	DOUBLE step=PI/20;
	HDC hdc=GetDC(ghWnd);
	FillRect(hdc, &rectClient, hbrBackground);
	SelectObject(hdc, hbrEllipse);
	SelectObject(hdc, hpenEllipse);
	int r = 0;
	for(DOUBLE i = 0; i<PI*2; i+=step){
		DOUBLE sin1=sin(i+fStartAngle);
		DOUBLE cos1=cos(i+fStartAngle);
		r = r==3 ? 6 : 3;
		INT x1, y1;
		x1 = (INT)(pes1.a * sin1);
		y1 = (INT)(pes1.b * cos1);
		//Rotate(x1, y1, PI/10);
		Rotate(x1, y1, fStartAngle);
		x1 += x0;
		y1 += y0;
		Ellipse(hdc, x1-r, y1-r, x1+r, y1+r);
		//SetPixel(hdc, x1, y1, RGB(255,255,0));
		x1 = (INT)(pes2.a * sin1);
		y1 = (INT)(pes2.b * cos1);
		//Rotate(x1, y1, PI/10);
		Rotate(x1, y1, fStartAngle);
		x1 += x0;
		y1 += y0;
		Ellipse(hdc, x1-r, y1-r, x1+r, y1+r);
	}
	ReleaseDC(ghWnd, hdc);
}

void PA_DoEllipseRotate(){
	fStartAngle += PI/80;
	if(fStartAngle>=PI*2) fStartAngle=0;
}