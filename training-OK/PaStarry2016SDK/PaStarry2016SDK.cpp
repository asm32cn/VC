// PaStarry2016SDK.cpp : Defines the entry point for the application.
//

/*
����unexpected end of file while looking for precompiled headerdirective
����������ͷ�ļ�����Ĵ���
����취���£�
1���Ҽ��㹤����,ѡ����,Ȼ��ѡc/c++����ҳ,��ѡcatagoryѡ����ѡ precompiled header ,��ѡ���ó�no use ����autometic
2�����ʹ�õ���Win32���̣����ܾ��Ǵ����ļ�û�а�����#include "stdafx.h" ����Ӹð������ɡ�
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


char szTitle[32]="PaStarry2016SDK";                 //���ڵı���
char szWindowClass[32]="PaStarry2016SDK"; //���ڵ�����


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
    WNDCLASSEX wc;		//����һ�������࣬���渳��ֵ
    HWND hWnd = NULL;

	hbrBackground = CreateSolidBrush(RGB(0, 0, 0));

    wc.cbSize        = sizeof(WNDCLASSEX);                  //����ֽڳ���
    wc.style         = CS_HREDRAW | CS_VREDRAW;             //����ʽ��
    wc.lpfnWndProc   = (WNDPROC)WndProc;                    //���ڴ�����
    wc.cbClsExtra    = 0;                                   //�����������ṹ֮��Ķ����ֽ���
    wc.cbWndExtra    = 0;                                   //
    wc.hInstance     = hInstance;                           //ʵ�����
    //wc.hIcon         = LoadIcon(hInstance, (LPCTSTR)IDI_APPLICATION);
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
				PA_DoStarryInit();
			}
		}
		break;
	case WM_TIMER:
		PA_DoSarryItemRefresh();
		PA_DoStarryDisplay();
		break;
    case WM_PAINT:                         //����ˢ��
		{
			HDC hdc;                       //�豸�ľ��
			PAINTSTRUCT ps;                //�ͻ��軭����Ϣ
			hdc = BeginPaint(hWnd, &ps);   //ȡ���豸�����������ʼ�軭
			EndPaint(hWnd, &ps);           //�����軭
			PA_DoStarryDisplay();
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