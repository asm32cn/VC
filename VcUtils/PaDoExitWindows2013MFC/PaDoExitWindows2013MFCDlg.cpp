// PaDoExitWindows2013MFCDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PaDoExitWindows2013MFC.h"
#include "PaDoExitWindows2013MFCDlg.h"

//#include <winuser.h>
//#include <winbase.h>
#define EWX_FORCEIFHUNG  0x010

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char szWinTitle[] = "PaDoExitWindows2013MFC";

/////////////////////////////////////////////////////////////////////////////
// CPaDoExitWindows2013MFCDlg dialog

CPaDoExitWindows2013MFCDlg::CPaDoExitWindows2013MFCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPaDoExitWindows2013MFCDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPaDoExitWindows2013MFCDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPaDoExitWindows2013MFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPaDoExitWindows2013MFCDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPaDoExitWindows2013MFCDlg, CDialog)
	//{{AFX_MSG_MAP(CPaDoExitWindows2013MFCDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_DO_LOGOFF, OnDoLogoff)
	ON_BN_CLICKED(IDC_DO_POWEROFF, OnDoPoweroff)
	ON_BN_CLICKED(IDC_DO_REBOOT, OnDoReboot)
	ON_BN_CLICKED(IDC_DO_SHUTDOWN, OnDoShutdown)
	ON_BN_CLICKED(IDC_OPT_SAFE, OnOptSafe)
	ON_BN_CLICKED(IDC_OPT_FORCE, OnOptForce)
	ON_BN_CLICKED(IDC_OPT_RISK, OnOptRisk)
	ON_BN_CLICKED(IDC_DO_SUSPEND, OnDoSuspend)
	ON_BN_CLICKED(IDC_DO_SCREENOFF, OnDoScreenoff)
	ON_BN_CLICKED(IDC_DO_HIBERNATE, OnDoHibernate)
	ON_BN_CLICKED(IDC_DO_LOCK_WORKSTATION, OnDoLockWorkstation)
	ON_BN_CLICKED(IDC_DO_SCREENOFF_LOCK, OnDoScreenoffLock)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPaDoExitWindows2013MFCDlg message handlers

BOOL CPaDoExitWindows2013MFCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	PA_InitDialog();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPaDoExitWindows2013MFCDlg::OnPaint() 
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
HCURSOR CPaDoExitWindows2013MFCDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CPaDoExitWindows2013MFCDlg::PA_DoExitWindowsEx(DWORD dwPlatformId, UINT uFlags, UINT uFlagsExtra)
{

	PA_EnabledButtons(FALSE);

	if(!PA_Confirm("确定进行关闭系统操作么?")){
		PA_EnabledButtons(TRUE);
		return;
	}

	if( PA_OpenShutdownProcessToken() ){
		if( dwPlatformId!=VER_PLATFORM_WIN32_NT && uFlagsExtra==EWX_FORCEIFHUNG){
			PA_AlertInfo("No EWX_FORCEIFHUNG encouraged!");
		} else {
			ExitWindowsEx(uFlags | uFlagsExtra, NULL);
			if(GetLastError() != ERROR_SUCCESS){
				PA_AlertInfo("ExitWindowsEx Fail !");
			}
		}
	
	}
	PA_EnabledButtons(TRUE);
}

BOOL CPaDoExitWindows2013MFCDlg::PA_Confirm(LPCTSTR szInfo)
{
	return (AfxMessageBox(szInfo, MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2)==IDYES);
}

void CPaDoExitWindows2013MFCDlg::PA_AlertInfo(LPCTSTR szInfo)
{
	::MessageBox(NULL, szInfo, szWinTitle, MB_OK | MB_ICONINFORMATION);
}

void CPaDoExitWindows2013MFCDlg::PA_InitDialog()
{

	uFlagsExtra = 0;

	memset(&osvi, 0, sizeof(osvi));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&osvi);
	//dwSystemMajorVersion = osvi.dwMajorVersion;
	dwPlatformId         = osvi.dwPlatformId;
	((CButton *)GetDlgItem(IDC_OPT_SAFE))->SetCheck(1);
}

void CPaDoExitWindows2013MFCDlg::OnDoLogoff() 
{
	// TODO: Add your control notification handler code here
	PA_DoExitWindowsEx(dwPlatformId, EWX_LOGOFF, uFlagsExtra);
}

void CPaDoExitWindows2013MFCDlg::OnDoPoweroff() 
{
	// TODO: Add your control notification handler code here
	PA_DoExitWindowsEx(dwPlatformId, EWX_POWEROFF, uFlagsExtra);
}

void CPaDoExitWindows2013MFCDlg::OnDoReboot() 
{
	// TODO: Add your control notification handler code here
	PA_DoExitWindowsEx(dwPlatformId, EWX_REBOOT, uFlagsExtra);
}

void CPaDoExitWindows2013MFCDlg::OnDoShutdown() 
{
	// TODO: Add your control notification handler code here
	PA_DoExitWindowsEx(dwPlatformId, EWX_SHUTDOWN, uFlagsExtra);
}

void CPaDoExitWindows2013MFCDlg::OnOptSafe() 
{
	// TODO: Add your control notification handler code here
	uFlagsExtra = 0;
}

void CPaDoExitWindows2013MFCDlg::OnOptForce() 
{
	// TODO: Add your control notification handler code here
	uFlagsExtra = EWX_FORCEIFHUNG;
}

void CPaDoExitWindows2013MFCDlg::OnOptRisk() 
{
	// TODO: Add your control notification handler code here
	uFlagsExtra = EWX_FORCE;
}

void CPaDoExitWindows2013MFCDlg::OnDoSuspend() 
{
	// TODO: Add your control notification handler code here
	//AfxMessageBox("OnDoSuspend()");
}

void CPaDoExitWindows2013MFCDlg::OnDoScreenoff() 
{
	PA_EnabledButtons(FALSE);
	PA_OnDoScreenoff();
	PA_EnabledButtons(TRUE);
}

void CPaDoExitWindows2013MFCDlg::OnDoHibernate() 
{
	// TODO: Add your control notification handler code here
	PA_EnabledButtons(FALSE);
	if(!PA_Confirm("本过程可能需要等待10秒钟以上, 确定要休眠(Hibernate)系统么?")) return;
	if( PA_OpenShutdownProcessToken() ){
	    ::SetSystemPowerState(FALSE,  TRUE); // 第一个参数FALSE为休眠, 第二个参数TRUE表示强制休眠
	}
	PA_EnabledButtons(TRUE);
}

void CPaDoExitWindows2013MFCDlg::PA_EnabledButtons(BOOL isEnabled)
{
	GetDlgItem(IDC_OPT_SAFE)->EnableWindow(isEnabled);
	GetDlgItem(IDC_OPT_FORCE)->EnableWindow(isEnabled);
	GetDlgItem(IDC_OPT_RISK)->EnableWindow(isEnabled);
	GetDlgItem(IDC_DO_LOGOFF)->EnableWindow(isEnabled);
	GetDlgItem(IDC_DO_POWEROFF)->EnableWindow(isEnabled);
	GetDlgItem(IDC_DO_REBOOT)->EnableWindow(isEnabled);
	GetDlgItem(IDC_DO_SHUTDOWN)->EnableWindow(isEnabled);
	GetDlgItem(IDC_DO_HIBERNATE)->EnableWindow(isEnabled);
	//GetDlgItem(IDC_DO_SUSPEND)->EnableWindow(isEnabled);
	GetDlgItem(IDC_DO_SCREENOFF)->EnableWindow(isEnabled);
	GetDlgItem(IDC_DO_SCREENOFF_LOCK)->EnableWindow(isEnabled);
}

BOOL CPaDoExitWindows2013MFCDlg::PA_OpenShutdownProcessToken()
{
	BOOL m_bSuccessed = FALSE;

	if(dwPlatformId == VER_PLATFORM_WIN32_NT){
		// 4 Windows 98
		// 5 Windiows 2000 / XP / Vista
		HANDLE           m_hCurrentProcess=NULL;
		HANDLE	         m_hToken;
		TOKEN_PRIVILEGES m_tkp;
		UINT             m_uResult;
		//char m_szSeShutdownName[]="SeShutdownPrivilege";

		// Get Token for this process
		m_hCurrentProcess = GetCurrentProcess();
		m_uResult = OpenProcessToken(m_hCurrentProcess, TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &m_hToken);
		if(m_uResult){
			//	Get the LUID
			LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &m_tkp.Privileges[0].Luid);
			m_tkp.PrivilegeCount = 1;
			m_tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

			//	Get the shutdown privilege for this process
			AdjustTokenPrivileges(m_hToken, FALSE, &m_tkp, 0, NULL, 0);
			if(GetLastError()==ERROR_SUCCESS){
				m_bSuccessed = TRUE;
			} else {
				//	AdjustTokenPrivileges Fail !
				PA_AlertInfo("AdjustTokenPrivileges Fail !");
			}
		} else {
			PA_AlertInfo("OpenProcessToken Fail !");
		}
	} else {
		m_bSuccessed = TRUE;
	}

	return m_bSuccessed;

}

void CPaDoExitWindows2013MFCDlg::OnDoLockWorkstation() 
{
	// TODO: Add your control notification handler code here
	if(!PA_DoLockWorkStation()){
		AfxMessageBox("Lock WorkStation Fail.");
	}
}

BOOL CPaDoExitWindows2013MFCDlg::PA_DoLockWorkStation()
{
	BOOL isSucceed = TRUE;
	HMODULE hUser32dll;
	PROC MyLockWorkStation;

	hUser32dll=GetModuleHandle("user32.dll");
	MyLockWorkStation=GetProcAddress(hUser32dll,"LockWorkStation");
	if(MyLockWorkStation){
		MyLockWorkStation();
	}else{
		isSucceed = FALSE;
	}
	return isSucceed;
}

void CPaDoExitWindows2013MFCDlg::OnDoScreenoffLock() 
{
	// TODO: Add your control notification handler code here
	PA_EnabledButtons(FALSE);
	PA_OnDoScreenoff();
	PA_DoLockWorkStation();
	PA_EnabledButtons(TRUE);
}

void CPaDoExitWindows2013MFCDlg::PA_OnDoScreenoff()
{
	// TODO: Add your control notification handler code here
	//VC++模拟关闭显示器（显示器待机）省电模式，双击生成的EXE文件，显示器即黑屏，按ESC键可恢复正常状态。函数解释： 
	//SendMessage 进队消息，将消息放入与创建窗口的线程相关联的消息队列后立即返回。 
	//PostMessage 不进队消息，将消息直接发送给窗口，窗口过程处理完消息后才返回。 
	//WM_SYSCOMMAND 窗口消息_系统指令 
	//WM_MONITORPOWER 系统指令_显示器电源 
	// 
	//最后一个参数含义： 
	//2 关闭显示器 
	//1 低电状态 
	//-1 打开显示器 
	// 
	//Sleep(1000); 主要是防止太过灵敏，你的手还没离开鼠标，显示器又被激活。
	Sleep(1000);        //防止太过灵敏，你的手还没离开鼠标，显示器又被激活   
	::SendMessage(HWND_BROADCAST,WM_SYSCOMMAND,SC_MONITORPOWER,2);
}
