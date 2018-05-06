// LinearGradientBrushDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LinearGradientBrush.h"
#include "LinearGradientBrushDlg.h"

#include <GdiPlus.h>
using namespace Gdiplus;
#pragma comment(lib,"gdiplus.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLinearGradientBrushDlg dialog

CLinearGradientBrushDlg::CLinearGradientBrushDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLinearGradientBrushDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLinearGradientBrushDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLinearGradientBrushDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLinearGradientBrushDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLinearGradientBrushDlg, CDialog)
	//{{AFX_MSG_MAP(CLinearGradientBrushDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLinearGradientBrushDlg message handlers

BOOL CLinearGradientBrushDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	GdiplusStartupInput gdiplusStartupInput; 
	ULONG_PTR gdiplusToken; 
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL); 
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CLinearGradientBrushDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CLinearGradientBrushDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CLinearGradientBrushDlg::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	COLORREF Color1 = RGB(255, 0, 0);
	COLORREF Color2 = RGB(0, 255, 0);
	int iRotation = 45;
	CDialog::OnEraseBkgnd(pDC); 
	//  取得第一种颜色的R，G，B值
	int r1 = GetRValue(Color1);
	int g1 = GetGValue(Color1);
	int b1 = GetBValue(Color1);

	//  取得第二种颜色的R，G，B值
	int r2 = GetRValue(Color2);
	int g2 = GetGValue(Color2);
	int b2 = GetBValue(Color2);

	//  得到绘制区域
	CRect rect;
	GetClientRect(&rect);

	//  GDI+对象
	Gdiplus::Graphics graphics(pDC->GetSafeHdc()); 

	//  刷子
	Gdiplus::LinearGradientBrush linGrBrush(Gdiplus::Rect(0, 0, rect.Width(), rect.Height()),  //  绘制区域
			Gdiplus::Color(255, r1, g1, b1),  //  第一种颜色
			Gdiplus::Color(255, r2, g2, b2),  //  第二种颜色 
			(Gdiplus::REAL)(90 - iRotation));  //  渐变色的角度

	graphics.FillRectangle(&linGrBrush, Gdiplus::Rect(0, 0, rect.Width(), rect.Height()));


	return TRUE;
	//return CDialog::OnEraseBkgnd(pDC);
}

BOOL CLinearGradientBrushDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	ULONG_PTR gdiplusToken = NULL; 
	GdiplusShutdown(gdiplusToken);
	return CDialog::DestroyWindow();
}

void CLinearGradientBrushDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	// InvalidateRect(NULL);
}
