// PaDigitalClock2015SDK.cpp : Defines the entry point for the application.
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

//#define PA_TIMER_INTERVAL 500


char szTitle[32]="PaEllipse2016SDK";                 //���ڵı���
char szWindowClass[32]="PaEllipse2016SDK"; //���ڵ�����


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
			}
		}
		break;
	case WM_TIMER:
		PA_DoEllipseRotate();
		PA_DoEllipseDisplay();
		break;
    case WM_PAINT:                         //����ˢ��
		{
			HDC hdc;                       //�豸�ľ��
			PAINTSTRUCT ps;                //�ͻ��軭����Ϣ
			hdc = BeginPaint(hWnd, &ps);   //ȡ���豸�����������ʼ�軭
			EndPaint(hWnd, &ps);           //�����軭
			PA_DoEllipseDisplay();
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