// PaGetScreenColor2011Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "PaGetScreenColor2011.h"
#include "PaGetScreenColor2011Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPaGetScreenColor2011Dlg dialog

CPaGetScreenColor2011Dlg::CPaGetScreenColor2011Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPaGetScreenColor2011Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPaGetScreenColor2011Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPaGetScreenColor2011Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPaGetScreenColor2011Dlg)
	DDX_Control(pDX, IDC_DISPLAY, m_wndDisplay);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPaGetScreenColor2011Dlg, CDialog)
	//{{AFX_MSG_MAP(CPaGetScreenColor2011Dlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPaGetScreenColor2011Dlg message handlers

BOOL CPaGetScreenColor2011Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_sysColor = 0xFFFFFF;
	br.CreateSolidBrush(m_sysColor);
	m_wndDisplay.GetClientRect(&m_rectDisplay);
	//m_wndDisplay.GetWindowRect(&m_rectDisplay);

	if(false){
		CString m_strDebug;
		m_strDebug.Format("%d %d %d %d",
			m_rectDisplay.left, m_rectDisplay.top, m_rectDisplay.right, m_rectDisplay.bottom);
		AfxMessageBox(m_strDebug);
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPaGetScreenColor2011Dlg::OnPaint()
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
		// Draw Display Window
		CPaintDC dc(&m_wndDisplay);
		dc.FillRect(&m_rectDisplay, &br);

		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPaGetScreenColor2011Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CPaGetScreenColor2011Dlg::GetScreenColorXY(INT x, INT y){
	HDC   hDC   =   ::GetDC(NULL);
	//COLORREF color  = ::GetPixel(hDC, x, y);
	m_sysColor = ::GetPixel(hDC, x, y);
	::ReleaseDC(NULL,   hDC);
	BYTE ColorR = GetRValue(m_sysColor); //ºìÉ«
	BYTE ColorG = GetGValue(m_sysColor);  //ÂÌÉ«
	BYTE ColorB = GetBValue(m_sysColor); //À¶É«
	CString m_strResult;
	m_strResult.Format("#%02X%02X%02X", ColorR, ColorG, ColorB);
	SetDlgItemText(IDC_COLOR, m_strResult);
	m_strResult.Format("(%d, %d, %d)", ColorR, ColorG, ColorB);
	SetDlgItemText(IDC_RGB, m_strResult);
	m_strResult.Format("(%d, %d)", x, y);
	SetDlgItemText(IDC_POSI, m_strResult);

	br.DeleteObject();
	br.CreateSolidBrush(m_sysColor);

	CDC * hdc = m_wndDisplay.GetDC();
	hdc->FillRect(&m_rectDisplay, &br);
	m_wndDisplay.ReleaseDC(hdc);

	//CRect rect;
	//m_wndDisplay.GetWindowRect(&rect);
	//ValidateRect(&rect);
	//m_wndDisplay.ValidateRect(&rect);
}

void CPaGetScreenColor2011Dlg::OnOK()
{
	// TODO: Add extra validation here
	POINT pt;
	GetCursorPos(&pt);
	GetScreenColorXY(pt.x,pt.y);
	// CDialog::OnOK();
}




