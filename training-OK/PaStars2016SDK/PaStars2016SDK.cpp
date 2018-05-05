// PaStars2016SDK.cpp : Defines the entry point for the application.
//

/*
����unexpected end of file while looking for precompiled headerdirective
����������ͷ�ļ�����Ĵ���
����취���£�
1���Ҽ��㹤����,ѡ����,Ȼ��ѡc/c++����ҳ,��ѡcatagoryѡ����ѡ precompiled header ,��ѡ���ó�no use ����autometic
2�����ʹ�õ���Win32���̣����ܾ��Ǵ����ļ�û�а�����#include "stdafx.h" ����Ӹð������ɡ�
*/

#include <windows.h>
#include <math.h>
#include "resource.h"
#include <stdio.h>

#define nTimerInterval 200


char szTitle[32]="PaStars2016SDK";                 //���ڵı���
char szWindowClass[32]="PaStars2016SDK"; //���ڵ�����


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
    WNDCLASSEX wc;		//����һ�������࣬���渳��ֵ
    HWND hWnd = NULL;

	hbrBackground = CreateSolidBrush(RGB(0, 0, 0));

    wc.cbSize        = sizeof(WNDCLASSEX);                  //����ֽڳ���
    wc.style         = CS_HREDRAW | CS_VREDRAW;             //����ʽ��
    wc.lpfnWndProc   = (WNDPROC)WndProc;                    //���ڴ�����
    wc.cbClsExtra    = 0;                                   //�����������ṹ֮��Ķ����ֽ���
    wc.cbWndExtra    = 0;                                   //
    wc.hInstance     = hInstance;                           //ʵ�����
    wc.hIcon         = LoadIcon(hInstance, (LPCTSTR)IDI_ICON1);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);         //���
//  wc.hbrBackground = (HBRUSH)GetStockObject(COLOR_WINDOWFRAME);//����
    wc.hbrBackground = hbrBackground;
    wc.lpszMenuName  = NULL;                                //�˵�
    wc.lpszClassName = szWindowClass;                       //������
    wc.hIconSm       = LoadIcon(wc.hInstance, (LPCTSTR)IDI_APPLICATION);

    if(!RegisterClassEx(&wc)) return FALSE;

    //��������
    hWnd = CreateWindow( szWindowClass,      //������
                         szTitle,            //���ڱ���
                         WS_OVERLAPPEDWINDOW,//���ڷ��
                         100,                //�������Ͻǵ�x����
                         100,                //�������Ͻǵ�y����
                         CW_USEDEFAULT,      //���ڵĿ��
                         CW_USEDEFAULT,      //���ڵĸ߶�
                         NULL,               //�����ھ��
                         NULL,               //�˵����
                         hInstance,          //ʵ�����
                         NULL);              //��������

    if (!hWnd) {
       return FALSE;
    }

	ghInstance = hInstance;
	ghWnd = hWnd;

    ShowWindow(hWnd, nCmdShow);	          //��ʾ����
    UpdateWindow(hWnd);                   //������ʾ

    while (GetMessage(&msg, NULL, 0, 0)){ //��Ϣѭ��
        TranslateMessage(&msg);	          //��Ϣ����
        DispatchMessage(&msg);            //��Ϣ����
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
    case WM_PAINT:                         //����ˢ��
		{
			HDC hdc;                       //�豸�ľ��
			PAINTSTRUCT ps;                //�ͻ��軭����Ϣ
			hdc = BeginPaint(hWnd, &ps);   //ȡ���豸�����������ʼ�軭
			EndPaint(hWnd, &ps);           //�����軭
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
    case WM_DESTROY:                       //�رմ���
        PA_DoAppFinalize();
        PostQuitMessage(0);                //���͹ر���Ϣ
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
	HPEN hPen, hOldPen;  //����
	HBRUSH hBrush, hOldBrush;
	FillRect(hdcMemory, &rectClient, hbrBackground);
	for(int i=0; i<nCount; i++){
		hPen = CreatePen(PS_SOLID, 1, A_colors[i]);  //����
		hOldPen = (HPEN)SelectObject(hdcMemory, hPen);  //ѡ���±ʱ���ɱ�
		hBrush = CreateSolidBrush(A_colors[i]);
		hOldBrush = (HBRUSH)SelectObject(hdcMemory, hBrush);
		Polygon(hdcMemory, A_points[i], 10);
		SelectObject(hdcMemory, hOldPen);  //�ָ��ɱ�
		SelectObject(hdcMemory, hOldBrush);
		DeleteObject(hPen);  //ɾ���±�
		DeleteObject(hBrush);
	}
	BitBlt(hdc, 0, 0, nClientWidth, nClientHeight, hdcMemory, 0, 0, SRCCOPY);
	ReleaseDC(ghWnd, hdc);
}