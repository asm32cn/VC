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
#include "resource.h"

#define PA_TIMER_INTERVAL 500


char szTitle[32]="PaDigitalClock2015SDK";                 //���ڵı���
char szWindowClass[32]="PaDigitalClock2015SDK"; //���ڵ�����

char szBuffer[512] = {0};


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void PA_DoAppInitialize();
void PA_DoAppFinalize();
void PA_DoClockDisplay();
void PA_DoInitBitmapChars();
void PA_DoClockDisplayChar(HDC hdc, INT nItem, INT nOffsetX, INT nOffsetY);

UINT nTimerID = 1;
HDC hdcChars = NULL;
HBITMAP hBmpChars = NULL;
HBRUSH hbrBackground;
WORD nClientWidth;
WORD nClientHeight;
WORD * A_wordDigitMatrix;
WORD A_wordMask[12] = {2048, 1024, 512, 256, 128, 64, 32, 16, 8, 4, 2, 1};
RECT rectClient = {0};
CHAR A_nCharID[12]={0};
CHAR A_nCharID_t[12]={0};
BOOL isRefresh = TRUE;

INT nBmpCharsWidth;
INT nBmpCharsHeight;
INT nBmpCharWidth;
INT nBmpCharHeight;
SYSTEMTIME tmSystem;
HWND ghWnd = NULL;
HINSTANCE ghInstance = NULL;

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
    wc.hIcon         = LoadIcon(hInstance, (LPCTSTR)IDI_APPLICATION);
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
				PA_DoInitBitmapChars();
			}
			isRefresh = TRUE;
		}
		break;
	case WM_TIMER:
		PA_DoClockDisplay();
		break;
    case WM_PAINT:                         //����ˢ��
		{
			HDC hdc;                       //�豸�ľ��
			PAINTSTRUCT ps;                //�ͻ��軭����Ϣ
			hdc = BeginPaint(hWnd, &ps);   //ȡ���豸�����������ʼ�軭
			isRefresh = TRUE;
			PA_DoClockDisplay();
			EndPaint(hWnd, &ps);           //�����軭
		}
        break;
    case WM_DESTROY:                       //�رմ���
        PostQuitMessage(0);                //���͹ر���Ϣ
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

void PA_DoAppInitialize(){
	HRSRC hrsrc = FindResource(ghInstance, MAKEINTRESOURCE(IDR_DIGIT_MATRIX), "BIN");
	A_wordDigitMatrix = hrsrc ? (WORD *)LoadResource(ghInstance, hrsrc) : NULL;
	HDC hdc = GetDC(ghWnd);
	hdcChars = CreateCompatibleDC(hdc);
	ReleaseDC(ghWnd, hdc);

	SetTimer(ghWnd, nTimerID, 10, NULL);
}

void PA_DoAppFinalize(){
	KillTimer(ghWnd, nTimerID);
}

void PA_DoInitBitmapChars(){
	INT m_nCellSize = nClientWidth / 132;
	INT m_nOffset = 0;
	INT m_nOffsetX = 0;

	if(m_nCellSize<3) m_nCellSize=3;

	if(hBmpChars) DeleteObject(hBmpChars);


	nBmpCharWidth  = m_nCellSize * 12;
	nBmpCharHeight = m_nCellSize * 22;

	nBmpCharsWidth  = nBmpCharWidth * 13;
	nBmpCharsHeight = nBmpCharHeight;

	HDC hdc=GetDC(ghWnd);
	hBmpChars = CreateCompatibleBitmap(hdc, nBmpCharsWidth, nBmpCharsHeight);
	SelectObject(hdcChars, hBmpChars);
	ReleaseDC(ghWnd, hdc);

	RECT m_rectBmpChars = {0, 0, nBmpCharsWidth, nBmpCharsHeight};
	m_rectBmpChars.right = nBmpCharsWidth;
	m_rectBmpChars.bottom = nBmpCharsHeight;
	HBRUSH m_hbrBackground = CreateSolidBrush(RGB(0, 0, 255));
	FillRect(hdcChars, &m_rectBmpChars, m_hbrBackground);

	HBRUSH m_hbrChar=CreateSolidBrush(RGB(255, 255, 255));
	HPEN m_hPenChar = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	SelectObject(hdcChars, m_hPenChar);
	SelectObject(hdcChars, m_hbrChar);
	for(int n=0; n<12; n++){
		m_nOffsetX = n * nBmpCharWidth;
		for(int i=0; i<22; i++){
			int m_nStartY = i * m_nCellSize + m_nCellSize;
			for(int j=0; j<12; j++){
				if(A_wordMask[j] & A_wordDigitMatrix[i+m_nOffset]){
					INT m_nStartX = m_nOffsetX + j * m_nCellSize;
					Ellipse(hdcChars, m_nStartX, m_nStartY, m_nStartX+m_nCellSize-1, m_nStartY+m_nCellSize-1);
					//Ellipse(hdcChars, m_nStartX, m_nStartY, m_nStartX+m_nCellSize, m_nStartY+m_nCellSize);
					//Rectangle(hdcChars, m_nStartX, m_nStartY, m_nStartX+m_nCellSize-1, m_nStartY+m_nCellSize-1);
					//Rectangle(hdcChars, m_nStartX, m_nStartY, m_nStartX+m_nCellSize, m_nStartY+m_nCellSize);
				}
			}
		}
		m_nOffset += 22;
	}

	DeleteObject(m_hbrBackground);
	DeleteObject(m_hPenChar);
	DeleteObject(m_hbrChar);
}

void PA_DoClockDisplay(){

	if(IsIconic(ghWnd)) return; // �������С��״̬��û��Ҫ�ػ���

	GetLocalTime(&tmSystem);
	HDC hdc = GetDC(ghWnd);

	//for(int i=0; i<12; i++){
	//	BitBlt(hdc, i*m_nBmpCharWidth, 0, m_nBmpCharWidth, m_nBmpCharHeight, hdcChars, i*nBmpCharWidth, 0, SRCCOPY);
	//}

	INT i;
	INT m_nMaxChars = 11; //12:00:00.000
	//INT m_nMaxChars = 11; //12:00:00.00

	INT m_nOffsetX = (nClientWidth - nBmpCharWidth*m_nMaxChars)/2;
	INT m_nOffsetY = (nClientHeight - nBmpCharsHeight)/2;

	//strncpy(A_nCharID_t, A_nCharID, 12); // ��ʱ�򲻻��������������ֽ�
	memcpy(A_nCharID_t, A_nCharID, 12);    // �������������ֽ�

	CHAR m_cSplitter1 = tmSystem.wMilliseconds<500 ? 10 : 12;
	A_nCharID[0]=tmSystem.wHour/10;
	A_nCharID[1]=tmSystem.wHour%10;
	A_nCharID[2]=m_cSplitter1; // :
	A_nCharID[3]=tmSystem.wMinute/10;
	A_nCharID[4]=tmSystem.wMinute%10;
	A_nCharID[5]=m_cSplitter1;	// :
	A_nCharID[6]=tmSystem.wSecond/10;
	A_nCharID[7]=tmSystem.wSecond%10;
	A_nCharID[8]=11;	// .
	A_nCharID[9]=tmSystem.wMilliseconds/100;
	A_nCharID[10]=tmSystem.wMilliseconds/10%10;
	//A_nCharID[11]=tmSystem.wMilliseconds%10;

	for(i=0; i<11; i++){
		if(isRefresh || A_nCharID[i]!=A_nCharID_t[i]){
			PA_DoClockDisplayChar(hdc, A_nCharID[i], m_nOffsetX, m_nOffsetY);
		}
		m_nOffsetX += nBmpCharWidth;
	}
	isRefresh = FALSE;

	ReleaseDC(ghWnd, hdc);

}

void PA_DoClockDisplayChar(HDC hdc, INT nItem, INT nOffsetX, INT nOffsetY){
	INT m_nOffsetX = nItem * nBmpCharWidth;
	BitBlt(hdc, nOffsetX, nOffsetY, nBmpCharWidth, nBmpCharHeight, hdcChars, m_nOffsetX, 0, SRCCOPY);
}

