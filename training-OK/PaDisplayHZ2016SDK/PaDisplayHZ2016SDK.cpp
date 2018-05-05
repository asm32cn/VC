// PaDisplayHZ2016SDK.cpp : Defines the entry point for the console application.
//

/*
错误：unexpected end of file while looking for precompiled headerdirective
分析：工程头文件处理的错误。
解决办法如下：
1、右键点工程名,选设置,然后选c/c++属性页,再选catagory选单中选 precompiled header ,将选项置成no use 或者autometic
2、如果使用的是Win32工程，可能就是错误文件没有包含：#include "stdafx.h" ，添加该包含即可。
*/

#include <windows.h>
#include "resource.h"
#include <stdio.h>

#define m_nTimerInterval 25


char szTitle[32]="PaDisplayHZ2016SDK";                 //窗口的标题
char szWindowClass[32]="PaDisplayHZ2016SDK"; //窗口的名称


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
	WNDCLASSEX wc;		//定义一个窗口类，下面赋初值
	HWND hWnd = NULL;
	
	hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
	
	wc.cbSize        = sizeof(WNDCLASSEX);                  //类的字节长度
	wc.style         = CS_HREDRAW | CS_VREDRAW;             //窗口式样
	wc.lpfnWndProc   = (WNDPROC)WndProc;                    //窗口处理函数
	wc.cbClsExtra    = 0;                                   //分配给窗口类结构之后的额外字节数
	wc.cbWndExtra    = 0;                                   //
	wc.hInstance     = hInstance;                           //实例句柄
	//wc.hIcon         = LoadIcon(hInstance, (LPCTSTR)IDI_APPLICATION);
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
	case WM_PAINT:                         //窗口刷新
		{
			HDC hdc;                       //设备文句柄
			PAINTSTRUCT ps;                //客户描画区信息
			hdc = BeginPaint(hWnd, &ps);   //取得设备环境句柄并开始描画
			EndPaint(hWnd, &ps);           //结束描画

			isRefresh = TRUE;

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


