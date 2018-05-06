// PaCalculator2016MFCDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LayoutManager.h"
#include "PaCalculator2016MFC.h"
#include "PaCalculator2016MFCDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPaCalculator2016MFCDlg dialog

CPaCalculator2016MFCDlg::CPaCalculator2016MFCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPaCalculator2016MFCDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPaCalculator2016MFCDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPaCalculator2016MFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPaCalculator2016MFCDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPaCalculator2016MFCDlg, CDialog)
	//{{AFX_MSG_MAP(CPaCalculator2016MFCDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPaCalculator2016MFCDlg message handlers

BOOL CPaCalculator2016MFCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	Do_InitUI();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPaCalculator2016MFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPaCalculator2016MFCDlg::OnPaint() 
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
HCURSOR CPaCalculator2016MFCDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CPaCalculator2016MFCDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	m_layout.Layout(3, 3, cx - 6, cy - 6);
}

void CPaCalculator2016MFCDlg::Do_InitUI()
{
	char * A_szKeys[] = {"7", "8", "9", "*", "¡û",
						"4", "5", "6", "/", "C",
						"1", "2", "3", "-", "=",
						"0", ".", "+"};
	static CFont font;
	font.CreatePointFont(160, "Arial");
	DWORD dwStyle = WS_CHILD | WS_VISIBLE;
	m_layout.SetType(Win32Layout::VERTICAL);
	m_pDisplay = new CEdit();
	SetDlgItemText(IDC_EDIT1, "3.14159265358979323846264338");
	Win32Layout::Box* box1 = m_layout.AddHBox(0, 0, Win32Layout::FILL, Win32Layout::FILL);
	box1->AddWindow(::GetDlgItem(m_hWnd, IDC_EDIT1), 0, 0, Win32Layout::FILL, Win32Layout::FILL);
	Win32Layout::Box* box2;// = m_layout.AddHBox(0, 0, Win32Layout::FILL, Win32Layout::FILL);
	for(int i=0; i<18; i++){
		A_pKeys[i] = new CButton();
		A_pKeys[i]->Create( A_szKeys[i], WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(20,10,100,100), this, IDC_MYBUTTONS+i );
		A_pKeys[i]->SetFont(&font);
		if(i%5==0){
			box2 = m_layout.AddHBox(0, 0, Win32Layout::FILL, Win32Layout::FILL);
		}
		int nPercentW = i==15? 40: 20;
		int nPercentH = i==14? 100: 100;
		box2->AddWindow(A_pKeys[i]->m_hWnd, nPercentW, nPercentH, Win32Layout::PERCENTAGE, Win32Layout::PERCENTAGE);
	}
	//m_pDisplay->Create(dwStyle, NULL, this, IDC_DISPLAY);
	m_layout.Layout(3, 3, 360 - 6, 330 - 6);
}
