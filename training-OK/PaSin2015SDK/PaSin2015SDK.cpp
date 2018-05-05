// PaSin2015SDK.cpp : Defines the entry point for the application.
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

#define PA_TIMER_INTERVAL 500


char szTitle[32]="PaSin2015SDK";                 //���ڵı���
char szWindowClass[32]="PaSin2015SDK"; //���ڵ�����


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
    case WM_PAINT:                         //����ˢ��
		{
			HDC hdc;                       //�豸�ľ��
			PAINTSTRUCT ps;                //�ͻ��軭����Ϣ
			hdc = BeginPaint(hWnd, &ps);   //ȡ���豸�����������ʼ�軭
			EndPaint(hWnd, &ps);           //�����軭
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
