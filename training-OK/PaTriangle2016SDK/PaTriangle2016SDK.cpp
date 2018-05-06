// PaTriangle2016SDK.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

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


char szTitle[32]="PaTriangle2016SDK";                 //窗口的标题
char szWindowClass[32]="PaTriangle2016SDK"; //窗口的名称


typedef struct {
	INT x, y;
	INT dx, dy;
} PaPointDEF;

typedef struct {
	INT r, g, b, Dr, Dg, Db;
}PaColorDEF;


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void PA_DoAppInitialize();
void PA_DoAppFinalize();

void PA_DoDisplay(HWND hWnd);

void PA_TrianglePointsInit(INT nMinD, INT nRangeD);
void PA_TrianglePointsSetNext();
void PA_TrianglePointsBackup();
void PA_TrianglePointsRestore();

void PA_TriangleColorInit();
void PA_TriangleColorSetNext();
COLORREF PA_TriangleGetColor();
COLORREF PA_TriangleGetColorEx(INT nMax, INT nPos);
void PA_TriangleColorBackup();
void PA_TriangleColorRestore();


UINT nTimerID = 1;

INT m_nCount;

HBRUSH hbrBackground;
WORD nClientWidth;
WORD nClientHeight;
RECT rectClient = {0};

HDC hdcMemory = NULL;
HBITMAP hBmpMemory = NULL;

HWND ghWnd = NULL;
HINSTANCE ghInstance = NULL;


PaPointDEF tps[3], tps_t[3];
PaColorDEF tc, tc_t;

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
				PA_TrianglePointsInit(2, 10);
			}
		}
		break;
	case WM_TIMER:
		PA_DoDisplay(hWnd);
		break;
    case WM_PAINT:                         //窗口刷新
		{
			HDC hdc;                       //设备文句柄
			PAINTSTRUCT ps;                //客户描画区信息
			hdc = BeginPaint(hWnd, &ps);   //取得设备环境句柄并开始描画
			EndPaint(hWnd, &ps);           //结束描画
			PA_DoDisplay(hWnd);
		}
        break;
	case WM_RBUTTONDOWN:
		PA_TrianglePointsInit(2, 10);
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
	HWND hWnd = ghWnd;
	srand( GetTickCount() ); // 设置随机种子

	m_nCount = 128;

	PA_TriangleColorInit();

	hbrBackground=CreateSolidBrush(RGB(0, 0, 0));
	HDC hdc;
	hdc=GetDC(hWnd);
	hdcMemory=CreateCompatibleDC(hdc);
	ReleaseDC(hWnd, hdc);
	SetTimer(hWnd, 1, 10, NULL);
}

void PA_DoAppFinalize(){
	HWND hWnd = ghWnd;
	KillTimer(hWnd, 1);
	ReleaseDC(hWnd, hdcMemory);
	DeleteObject(hBmpMemory);
}


void PA_DoDisplay(HWND hWnd){
	HPEN m_hPen;
	FillRect(hdcMemory, &rectClient, hbrBackground);
	//DrawText(hdcMemory, szHello, strlen(szHello), &rectClient, DT_CENTER);
	for(int i=0; i<m_nCount; i++){
		m_hPen = CreatePen(PS_SOLID, 1, PA_TriangleGetColorEx(m_nCount, i));
		SelectObject(hdcMemory, m_hPen);
		MoveToEx(hdcMemory, tps[0].x, tps[0].y, NULL);
		LineTo(hdcMemory, tps[1].x, tps[1].y);
		LineTo(hdcMemory, tps[2].x, tps[2].y);
		LineTo(hdcMemory, tps[0].x, tps[0].y);
		DeleteObject(m_hPen);
		if(i==5){
			PA_TrianglePointsBackup();
			PA_TriangleColorBackup();
		}
		PA_TrianglePointsSetNext();
		PA_TriangleColorSetNext();
	}
	PA_TrianglePointsRestore();
	PA_TriangleColorRestore();

	HDC hdc=GetDC(hWnd);
	BitBlt(hdc, 0, 0, nClientWidth, nClientHeight, hdcMemory, 0, 0, SRCCOPY);
	ReleaseDC(hWnd, hdc);
}

void PA_TrianglePointsInit(INT nMinD, INT nRangeD){
	for(INT i=0; i<3; i++){
		tps[i].dx = nMinD + rand() % nRangeD;
		tps[i].dy = nMinD + rand() % nRangeD;
		tps[i].x = rand() % nClientWidth;
		tps[i].y = rand() % nClientHeight;
	}
}

void PA_TrianglePointsSetNext(){
	INT nx, ny;
	for(INT i=0; i<3; i++){
		nx = tps[i].x + tps[i].dx;
		if((nx>nClientWidth && tps[i].dx>0) || (nx<0 && tps[i].dx<0)){
			tps[i].dx = -tps[i].dx;
		}else{
			tps[i].x = nx;
		}
		ny = tps[i].y + tps[i].dy;
		if((ny>nClientHeight && tps[i].dy>0) || (ny<0 && tps[i].dy<0)){
			tps[i].dy = -tps[i].dy;
		}else{
			tps[i].y = ny;
		}
	}
}

void PA_TrianglePointsBackup(){
	for(INT i=0; i<3; i++){
		tps_t[i] = tps[i];
	}
}

void PA_TrianglePointsRestore(){
	for(INT i=0; i<3; i++){
		tps[i] = tps_t[i];
	}
}

void PA_TriangleColorInit(){
	tc.r = 10;
	tc.g = 10;
	tc.b = 10;
	tc.Dr = 5;
	tc.Dg = 5;
	tc.Db = 5;
}

void PA_TriangleColorSetNext(){
	INT nr, ng, nb;
	nb = tc.b + tc.Db;
	if((nb>255 && tc.Db>0) || (nb<0 && tc.Db<0)){
		tc.Db = -tc.Db;
		ng = tc.g + tc.Dg;
		if((ng>255 && tc.Dg>0) || (ng<0 && tc.Dg<0)){
			tc.Dg = -tc.Dg;
			nr = tc.r + tc.Dr;
			if((nr>255 && tc.Dr>0) || (nr<0 && tc.Dr<0)){
				tc.Dr = - tc.Dr;
			}else{
				tc.r = nr;
			}
		}else{
			tc.g = ng;
		}
	}else{
		tc.b = nb;
	}
}

COLORREF PA_TriangleGetColor(){
	return RGB(tc.r, tc.g, tc.b);
}

COLORREF PA_TriangleGetColorEx(INT nMax, INT nPos){
	INT m_nMax = nMax>0 ? nMax : 1;
	INT m_nPos = nPos>nMax ? nMax : nPos;
	return RGB(tc.r * m_nPos / m_nMax, tc.g * m_nPos / m_nMax, tc.b * m_nPos / m_nMax);
}

void PA_TriangleColorBackup(){
	tc_t = tc;
}

void PA_TriangleColorRestore(){
	tc = tc_t;
}
