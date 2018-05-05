// PaClock2016SDK.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

/*
����unexpected end of file while looking for precompiled headerdirective
����������ͷ�ļ�����Ĵ���
����취���£�
1���Ҽ��㹤����,ѡ����,Ȼ��ѡc/c++����ҳ,��ѡcatagoryѡ����ѡ precompiled header ,��ѡ���ó�no use ����autometic
2�����ʹ�õ���Win32���̣����ܾ��Ǵ����ļ�û�а�����#include "stdafx.h" ����Ӹð������ɡ�
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

char szTitle[32]="PaClock2016SDK";                 //���ڵı���
char szWindowClass[32]="PaClock2016SDK"; //���ڵ�����


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
    WNDCLASSEX wc;		//����һ�������࣬���渳��ֵ
    HWND hWnd = NULL;

	hbrBackground = CreateSolidBrush(RGB(255, 255, 255));

    wc.cbSize        = sizeof(WNDCLASSEX);                  //����ֽڳ���
    wc.style         = CS_HREDRAW | CS_VREDRAW;             //����ʽ��
    wc.lpfnWndProc   = (WNDPROC)WndProc;                    //���ڴ�����
    wc.cbClsExtra    = 0;                                   //�����������ṹ֮��Ķ����ֽ���
    wc.cbWndExtra    = 0;                                   //
    wc.hInstance     = hInstance;                           //ʵ�����
//  wc.hIcon         = LoadIcon(hInstance, (LPCTSTR)IDI_APPLICATION);
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
		PA_DoDisplay();
		PA_DoBeep();
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

    hFont = CreateFont(48,  //������߼��߶�
        0,  //�߼�ƽ���ַ����
        0,  //��ˮƽ�ߵĽǶ�
        0,  //���߷�λ�Ƕ�
        FW_REGULAR,  //���Σ�����
        FALSE,  //���Σ�б��
        FALSE,  //���Σ��»���
        FALSE,  //���Σ�����
        ANSI_CHARSET,  //�ַ���
        OUT_DEFAULT_PRECIS,  //�������
        CLIP_DEFAULT_PRECIS,  //���ؾ���
        PROOF_QUALITY,  //���Ʒ��
        FIXED_PITCH | FF_MODERN, //��б��
        "Arial Black");  //����

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

	// ��ʼ������Դ���JPEGͼ�񵽻�����
	// ���� JPEG GIF ͼƬ��Դ
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
			//	������װ��ͼƬ 
			IPicture * pPicture = NULL; 
			if( SUCCEEDED( OleLoadPicture( pStream, dwSize, TRUE, IID_IPicture,( LPVOID* )&pPicture ) ) ) 
			{ 
				//	��DC�л�ͼ 
				OLE_XSIZE_HIMETRIC hmWidth;
				OLE_YSIZE_HIMETRIC hmHeight; 
				pPicture->get_Width( &hmWidth ); 
				pPicture->get_Height( &hmHeight ); 
				pPicture->Render( hdcFace, 0, 0, sizeFace.cx, sizeFace.cy, 0, hmHeight, hmWidth, -hmHeight, NULL ); 
				pPicture->Release();
			}
			// �ͷ������ļ� 
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