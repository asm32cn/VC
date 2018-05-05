// PaDisplayHZ2016SDK.cpp : Defines the entry point for the console application.
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
#include <stdio.h>

#define m_nTimerInterval 25


char szTitle[32]="PaDisplayHZ2016SDK";                 //���ڵı���
char szWindowClass[32]="PaDisplayHZ2016SDK"; //���ڵ�����


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void PA_DoAppInitialize();
void PA_DoAppFinalize();
void PA_DoAction();
void PA_DoAction0();
void PA_DoAction1();
void PA_DoAction2();
void PA_DoAction3();
void PA_DoAction4();
void PA_DoAction5();
void PA_DoAction6();
void PA_DoAction7();
void PA_DoAction8();
void PA_DoAction9();
void PA_DoAction10();
void PA_DoAction11();
void PA_DoAction12();
void PA_DoAction13();
void PA_DoAction14();
void PA_DoAction15();
void PA_DoAction16();
void PA_DoAction17();
void PA_DoAction18();
void PA_DoAction19();

void PA_DoDisplay();
void PA_DoGetNextAction();

UINT nTimerID = 1;

HBRUSH hbrBackground;
WORD nClientWidth;
WORD nClientHeight;
RECT rectClient = {0};

HBITMAP hbmPoints = NULL;

HWND ghWnd = NULL;
HINSTANCE ghInstance = NULL;

BYTE * A_byteMatrix = NULL;
HBRUSH hBrush0 = NULL;
HBRUSH hBrush1 = CreateSolidBrush(RGB(255, 255, 0));
HBRUSH hBrush2 = CreateSolidBrush(RGB(31, 31, 31));
HDC hdcPoints = NULL;
BYTE A_nMatrixBuffer[24][48] = {0};
BYTE A_nDisplayCache[24][48] = {0};
BYTE A_nDisplayBuffer[24][48] = {0};
INT nPoints = 24;
INT nPointsHF = 12;
INT nCountX = 48;
BYTE A_mask[] = {128, 64, 32, 16, 8, 4, 2, 1};
INT nStart = 0;
INT nStart1 = 0;
INT nActionID = 5;
INT nActionID1 = 0;
INT nActionCount = 20;
INT nSleep = 0;
INT d, d1, nStartX, nStartY;
BOOL isRefresh = TRUE;

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

				d1 = nClientWidth / 48;
				d = d1 - 1;
				nStartX = (nClientWidth - d1 * 48 /*nDisplayW*/) / 2;
				nStartY = (nClientHeight - d1 * 24 /*nDisplayH*/) / 2;

				if(hbmPoints!=NULL){
					DeleteObject(hbmPoints);
					hbmPoints=NULL;
				}
				HDC hdc = GetDC(ghWnd);
				hbmPoints = CreateCompatibleBitmap(hdc, d + d, d);
				SelectObject(hdcPoints, hbmPoints);
				hBrush0 = (HBRUSH)SelectObject(hdcPoints, hBrush1);
				Ellipse(hdcPoints, 0, 0, d, d);
				SelectObject(hdcPoints, hBrush0);
				hBrush0 = (HBRUSH)SelectObject(hdcPoints, hBrush2);
				Ellipse(hdcPoints, d, 0, d+d, d);
				SelectObject(hdcPoints, hBrush0);
				ReleaseDC(ghWnd, hdc);

				isRefresh = TRUE;
			}
		}
		break;
	case WM_TIMER:
		PA_DoAction();
		PA_DoDisplay();
		break;
	case WM_PAINT:                         //����ˢ��
		{
			HDC hdc;                       //�豸�ľ��
			PAINTSTRUCT ps;                //�ͻ��軭����Ϣ
			hdc = BeginPaint(hWnd, &ps);   //ȡ���豸�����������ʼ�軭
			EndPaint(hWnd, &ps);           //�����軭

			isRefresh = TRUE;

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
	HRSRC hrsrc = FindResource(ghInstance, MAKEINTRESOURCE(IDR_BIN1), "BIN");
	A_byteMatrix = hrsrc ? (BYTE *)LoadResource(ghInstance, hrsrc) : NULL;

	int id=0;
	for(int n=0; n<2; n++){
		int stx = n * nPoints;
		for(int y=0; y<nPoints; y++){
			for(int x=0; x<nPoints; x++){
				int pos = x % 8;
				A_nMatrixBuffer[y][stx + x] = (A_byteMatrix[id] & A_mask[pos]) ? 1 : 0;
				A_nDisplayBuffer[y][stx + x] = A_nMatrixBuffer[y][stx + x];
				if(pos==7){
					id++;
				}
			}
		}
	}

	HDC hdc = GetDC(ghWnd);
	hdcPoints = CreateCompatibleDC(hdc);
	ReleaseDC(ghWnd, hdc);

	SetTimer(ghWnd, nTimerID, m_nTimerInterval, NULL);
}

void PA_DoAppFinalize(){
	KillTimer(ghWnd, nTimerID);
	ReleaseDC(ghWnd, hdcPoints);
}

void PA_DoDisplay(){
	HDC hdc = GetDC(ghWnd);

	for(int y=0; y<nPoints; y++){
		for(int x=0; x<nCountX; x++){
			if(isRefresh || A_nDisplayBuffer[y][x]!=A_nDisplayCache[y][x]){
				BitBlt(hdc, nStartX + x*d1, nStartY + y*d1, d, d, hdcPoints, (A_nDisplayBuffer[y][x] ? 0 : d), 0, SRCCOPY);
			}
			A_nDisplayCache[y][x] = A_nDisplayBuffer[y][x];
		}
	}

	isRefresh = FALSE;

	ReleaseDC(ghWnd, hdc);
}

void PA_DoGetNextAction(){
	do{
		nActionID = rand() % nActionCount;
	}while(nActionID1==nActionID);
	nActionID1 = nActionID;
}


void PA_DoAction(){
    if(nSleep>0){
        nSleep--;
    }else{
        switch(nActionID){
            case 1: PA_DoAction1(); break;
            case 2: PA_DoAction2(); break;
            case 3: PA_DoAction3(); break;
            case 4: PA_DoAction4(); break;
            case 5: PA_DoAction5(); break;
            case 6: PA_DoAction6(); break;
            case 7: PA_DoAction7(); break;
            case 8: PA_DoAction8(); break;
            case 9: PA_DoAction9(); break;
            case 10: PA_DoAction10(); break;
            case 11: PA_DoAction11(); break;
            case 12: PA_DoAction12(); break;
            case 13: PA_DoAction13(); break;
            case 14: PA_DoAction14(); break;
            case 15: PA_DoAction15(); break;
            case 16: PA_DoAction16(); break;
            case 17: PA_DoAction17(); break;
            case 18: PA_DoAction18(); break;
            case 19: PA_DoAction19(); break;
            default: PA_DoAction0(); break;
        }
        if(nStart1==0){
            nSleep = 25;
            PA_DoGetNextAction();
        }
    }
}

void PA_DoAction0(){
    nStart = nCountX - nStart1;
    for(int y = 0; y<nPoints; y++){
        for(int x = 0; x<nCountX; x++){
            if(x<nStart){
                A_nDisplayBuffer[y][x] = 0;
            }else{
                A_nDisplayBuffer[y][x] = A_nMatrixBuffer[y][x-nStart];
            }
        }
    }
    nStart1 = (nStart1 + 1) % nCountX;
}

void PA_DoAction1(){
    nStart = nCountX - nStart1;
    for(int y = 0; y<nPoints; y++){
        for(int x = 0; x<nCountX; x++){
            if(x<nStart1){
                A_nDisplayBuffer[y][x] = A_nMatrixBuffer[y][nStart + x - 1];
            }else{
                A_nDisplayBuffer[y][x] = 0;
            }
        }
    }
    nStart1 = (nStart1 + 1) % nCountX;
}

void PA_DoAction2(){
    nStart = nCountX - nStart1;
    for(int y = 0; y<nPoints; y++){
        for(int x = 0; x<nCountX; x++){
            A_nDisplayBuffer[y][x] = A_nMatrixBuffer[y][(x + nStart1) % nCountX];
        }
    }
    nStart1 = (nStart1 + 1) % nCountX;
}

void PA_DoAction3(){
    nStart = nCountX - nStart1;
    for(int y = 0; y<nPoints; y++){
        for(int x = 0; x<nCountX; x++){
            A_nDisplayBuffer[y][x] = A_nMatrixBuffer[y][(nCountX + x + nStart - 1) % nCountX];
        }
    }
    nStart1 = (nStart1 + 1) % nCountX;
}

void PA_DoAction4(){
    for(int y = 0; y<nPoints; y++){
        for(int x = 0; x<nCountX; x++){
            if(x < nPoints - nStart1 || x > nPoints + nStart1){
                A_nDisplayBuffer[y][x] = 0;
            }else{
                A_nDisplayBuffer[y][x] = A_nMatrixBuffer[y][x];
            }
        }
    }
    nStart1 = (nStart1 + 1) % nPoints;
}

void PA_DoAction5(){
    nStart = nPoints - nStart1;
    for(int y = 0; y<nPoints; y++){
        for(int x = 0; x<nCountX; x++){
            if(x < nPoints-nStart + 1 || x > nPoints + nStart - 1){
                A_nDisplayBuffer[y][x] = A_nMatrixBuffer[y][x];
            }else{
                A_nDisplayBuffer[y][x] = 0;
            }
        }
    }
    nStart1 = (nStart1 + 1) % nPoints;
}

void PA_DoAction6(){
    nStart = nCountX - nStart1;
    for(int y = 0; y<nPoints; y++){
        for(int x = 0; x<nCountX; x++){
            if(x<nStart1){
                A_nDisplayBuffer[y][x] = A_nMatrixBuffer[y][x];
            }else{
                A_nDisplayBuffer[y][x] = A_nMatrixBuffer[y][nStart1];
            }
        }
    }
    nStart1 = (nStart1 + 1) % nCountX;
}

void PA_DoAction7(){
    nStart = nCountX - nStart1;
    for(int y = 0; y<nPoints; y++){
        for(int x = 0; x<nCountX; x++){
            if(x<nStart){
                A_nDisplayBuffer[y][x] = A_nMatrixBuffer[y][nStart - 1];
            }else{
                A_nDisplayBuffer[y][x] = A_nMatrixBuffer[y][x];
            }
        }
    }
    nStart1 = (nStart1 + 1) % nCountX;
}

void PA_DoAction8(){
    nStart = nCountX - nStart1;
    for(int y = 0; y<nPoints; y++){
        for(int x = 0; x<nCountX; x++){
            if(x<nStart1){
                A_nDisplayBuffer[y][x] = A_nMatrixBuffer[y][x];
            }else{
                A_nDisplayBuffer[y][x] = A_nMatrixBuffer[y][nStart1 + (int)((x - nStart1) / 2) ];
            }
        }
    }
    nStart1 = (nStart1 + 1) % nCountX;
}

void PA_DoAction9(){
    nStart = nCountX - nStart1;
    for(int y = 0; y<nPoints; y++){
        for(int x = 0; x<nCountX; x++){
            if(x<nStart){
                A_nDisplayBuffer[y][x] = A_nMatrixBuffer[y][nStart1 + (int)((nStart-x) / 2)];
            }else{
                A_nDisplayBuffer[y][x] = A_nMatrixBuffer[y][x];
            }
        }
    }
    nStart1 = (nStart1 + 1) % nCountX;
}

void PA_DoAction10(){
    nStart = nPoints - nStart1;
    for(int y = 0; y<nPoints; y++){
        for(int x = 0; x<nCountX; x++){
            if(y<nStart1){
                A_nDisplayBuffer[y][x] = A_nMatrixBuffer[y][x];
            }else{
                A_nDisplayBuffer[y][x] = 0;
            }
        }
    }
    nStart1 = (nStart1 + 1) % nPoints;
}

void PA_DoAction11(){
    nStart = nPoints - nStart1;
    for(int y = 0; y<nPoints; y++){
        for(int x = 0; x<nCountX; x++){
            if(y<nStart){
                A_nDisplayBuffer[y][x] = 0;
            }else{
                A_nDisplayBuffer[y][x] = A_nMatrixBuffer[y][x];
            }
        }
    }
    nStart1 = (nStart1 + 1) % nPoints;
}

void PA_DoAction12(){
    nStart = nPoints - nStart1;
    for(int y = 0; y<nPoints; y++){
        for(int x = 0; x<nCountX; x++){
            if(y<nStart1){
                A_nDisplayBuffer[y][x] = A_nMatrixBuffer[y  + nStart][x];
            }else{
                A_nDisplayBuffer[y][x] = 0;
            }
        }
    }
    nStart1 = (nStart1 + 1) % nPoints;
}

void PA_DoAction13(){
    nStart = nPoints - nStart1;
    for(int y = 0; y<nPoints; y++){
        for(int x = 0; x<nCountX; x++){
            if(y<nStart){
                A_nDisplayBuffer[y][x] = 0;
            }else{
                A_nDisplayBuffer[y][x] = A_nMatrixBuffer[y - nStart][x];
            }
        }
    }
    nStart1 = (nStart1 + 1) % nPoints;
}

void PA_DoAction14(){
    nStart = nPointsHF - nStart1;
    for(int y = 0; y<nPoints; y++){
        for(int x = 0; x<nCountX; x++){
            if(y<nStart || y>nPointsHF + nStart1){
                A_nDisplayBuffer[y][x] = 0;
            }else{
                A_nDisplayBuffer[y][x] = A_nMatrixBuffer[y][x];
            }
        }
    }
    nStart1 = (nStart1 + 1) % nPointsHF;
}

void PA_DoAction15(){
    nStart = nPointsHF - nStart1;
    for(int y = 0; y<nPoints; y++){
        for(int x = 0; x<nCountX; x++){
            if(y<nPointsHF - nStart + 1 || y>nPointsHF + nStart - 2){
                A_nDisplayBuffer[y][x] = A_nMatrixBuffer[y][x];
            }else{
                A_nDisplayBuffer[y][x] = 0;
            }
        }
    }
    nStart1 = (nStart1 + 1) % nPointsHF;
}

void PA_DoAction16(){
    nStart = nPoints - nStart1;
    for(int y = 0; y<nPoints; y++){
        for(int x = 0; x<nCountX; x++){
            if(y<nStart1){
                A_nDisplayBuffer[y][x] = A_nMatrixBuffer[y][x];
            }else{
                A_nDisplayBuffer[y][x] = A_nMatrixBuffer[nStart1 + (int)((y - nStart1) / 2)][x];
            }
        }
    }
    nStart1 = (nStart1 + 1) % nPoints;
}

void PA_DoAction17(){
    nStart = nPoints - nStart1;
    for(int y = 0; y<nPoints; y++){
        for(int x = 0; x<nCountX; x++){
            if(y<nStart){
                A_nDisplayBuffer[y][x] = A_nMatrixBuffer[nStart1 + (int)((nStart - y) / 2)][x];
            }else{
                A_nDisplayBuffer[y][x] = A_nMatrixBuffer[y][x];
            }
        }
    }
    nStart1 = (nStart1 + 1) % nPoints;
}

void PA_DoAction18(){
    nStart = nPoints - nStart1;
    for(int y = 0; y<nPoints; y++){
        for(int x = 0; x<nCountX; x++){
            if(y<nStart1){
                A_nDisplayBuffer[y][x] = A_nMatrixBuffer[y][x];
            }else{
                int y1 = nStart1 + (int)((y - nStart1) / 2);
                A_nDisplayBuffer[y][x] = (((y1 % 2)==0) ^ (x % 2==0) ? A_nMatrixBuffer[y1][x] : (byte)0);
            }
        }
    }
    nStart1 = (nStart1 + 1) % nPoints;
}

void PA_DoAction19(){
    nStart = nPoints - nStart1;
    for(int y = 0; y<nPoints; y++){
        for(int x = 0; x<nCountX; x++){
            if(y<nStart){
                int y1 = nStart1 + (int)((nStart - y) / 2);
                A_nDisplayBuffer[y][x] = (((y1 % 2)==0) ^ (x % 2==0) ? A_nMatrixBuffer[y1][x] : (byte)0);
            }else{
                A_nDisplayBuffer[y][x] = A_nMatrixBuffer[y][x];
            }
        }
    }
    nStart1 = (nStart1 + 1) % nPoints;
}


