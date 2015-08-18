// AranockAssistDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AranockAssist.h"
#include "AranockAssistDlg.h"

#include <winuser.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define RETRY_TIME 1000
#define TEN_MINUTES 60000 ) { //599500

#define HealthCurrentAddress 0x0063C72C
#define HealthBaseAddress 6539000
#define EnduranceCurrentAddress 6539056
#define EnduranceBaseAddress 6539024
#define ManaCurrentAddress 0x0063C734
#define ManaBaseAddress 0x0063C728


BOOL bInUse = false;
BOOL bKeyInUse = false;



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
// CAranockAssistDlg dialog

CAranockAssistDlg::CAranockAssistDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAranockAssistDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAranockAssistDlg)
		// NOTE: the ClassWizard will add member initialization here

	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAranockAssistDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAranockAssistDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAranockAssistDlg, CDialog)
	//{{AFX_MSG_MAP(CAranockAssistDlg)
	ON_WM_CTLCOLOR()
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CLICK_AUTO, OnClickAuto)
	ON_BN_CLICKED(IDC_MINE_AUTO, OnMineAuto)
	ON_BN_CLICKED(IDC_CHECK_ALL, OnCheckAll)
	ON_BN_CLICKED(IDC_AUTO_SPELL, OnAutoSpell)
	ON_BN_CLICKED(IDC_TEST, OnTest)
	ON_CBN_EDITCHANGE(IDC_HEALTH_ACTION, OnEditchangeHealthAction)
	ON_CBN_EDITCHANGE(IDC_MANA_ACTION, OnEditchangeManaAction)
	ON_CBN_EDITCHANGE(IDC_RECALL_ACTION, OnEditchangeRecallAction)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()




void CAranockAssistDlg::ReadAranockValues()
{
	DWORD pidAranock;
	DWORD tidAranock;
	HWND hWndAranock;

	//_int16 tmpBuffer = 0;;
	//unsigned int tmpBuffer;
	//DWORD tmpBuffer = 0;
	//int tmpBuffer = 0;
	//char tmpBuffer[1];
	char *tmpBuffer = 0;
	//void *tmpBuffer = new BYTE [2];

	DWORD dwBytesRead = 0;
	//debug
	//DWORD getlasterror = NULL;
	//char buffer[300];

	//char *AranockWindowTitle;  
	//strcpy(AranockWindowTitle,"Aranock online version 2.d");
	//char *AranockClassName;  
	//strcpy(AranockClassName,"DDCWin");

	//hWndAranock = ::FindWindow(AranockClassName,AranockWindowTitle);
	hWndAranock = ::FindWindow(IDS_WINDOW_CLASS,0);
	if(IsWindow(hWndAranock)) {
		tidAranock = GetWindowThreadProcessId(hWndAranock,&pidAranock);
		HANDLE hAranock = OpenProcess(PROCESS_ALL_ACCESS,FALSE,pidAranock);
		// Health
		//SuspendThread(hAranock);
		if(ReadProcessMemory(hAranock,(LPVOID)HealthCurrentAddress,&tmpBuffer,4,NULL)) {
			//ResumeThread(hAranock);
			CAranockAssistDlg::SetDlgItemInt(IDC_HEALTH_CURRENT,(unsigned int)tmpBuffer,FALSE);
			//CAranockAssistDlg::SetDlgItemInt(IDC_HEALTH_BASE,(unsigned int)tmpBuffer,FALSE);
			//sprintf(buffer,"SUCCESS!\n\nHealthCurrentAddress: %i\ntmpBuffer: %i\nbytesread: %i\n",HealthCurrentAddress,tmpBuffer,dwBytesRead);
			//CAranockAssistDlg::MessageBox(buffer,"DEBUG",MB_OK);
		} else {
			//ResumeThread(hAranock);
			//getlasterror = GetLastError();
			//sprintf(buffer,"ReadProcessMemory() Failed!\nHealthCurrentAddress: %i\ntmpBuffer: %i\nbytesread: %i\ngetlasterror: %i",HealthCurrentAddress,tmpBuffer,dwBytesRead,getlasterror);
			//CAranockAssistDlg::MessageBox(buffer,"DEBUG",MB_OK);
		}
		if(ReadProcessMemory(hAranock,(LPVOID)HealthBaseAddress,&tmpBuffer,4,NULL)) {
			CAranockAssistDlg::SetDlgItemInt(IDC_HEALTH_BASE,(unsigned int)tmpBuffer,FALSE); }

		// Endurance
		if(ReadProcessMemory(hAranock,(LPVOID)EnduranceCurrentAddress,&tmpBuffer,4,NULL)) {
			CAranockAssistDlg::SetDlgItemInt(IDC_ENDURANCE_CURRENT,(unsigned int)tmpBuffer,FALSE); }
		if(ReadProcessMemory(hAranock,(LPVOID)EnduranceBaseAddress,&tmpBuffer,4,NULL)) {
			CAranockAssistDlg::SetDlgItemInt(IDC_ENDURANCE_BASE,(unsigned int)tmpBuffer,FALSE); }

		// Mana
		if(ReadProcessMemory(hAranock,(LPVOID)ManaCurrentAddress,&tmpBuffer,4,NULL)) {
		CAranockAssistDlg::SetDlgItemInt(IDC_MANA_CURRENT,(unsigned int)tmpBuffer,FALSE); }
		if(ReadProcessMemory(hAranock,(LPVOID)ManaBaseAddress,&tmpBuffer,4,NULL)) {
		CAranockAssistDlg::SetDlgItemInt(IDC_MANA_BASE,(unsigned int)tmpBuffer,FALSE); }
		CloseHandle(hAranock);
	
	} else {
		CAranockAssistDlg::MessageBox("Error: Cannot find Aranock window, perhaps Aranock is not running?\nAranock Assist will now terminate...","Aranock Assist",MB_OK|MB_ICONSTOP);
		CAranockAssistDlg::EndDialog(1);
	}
}

// One second check of checkboxes
void CAranockAssistDlg::CheckAranockValues()
{
	//if(!CAranockAssistDlg::IsDlgButtonChecked(IDC_CLICK_AUTO)) {
		POINT lppPosition;
		POINT lppResult;

		if(GetCursorPos(&lppPosition)) {
			lppResult = CAranockAssistDlg::ConvertXY(lppPosition.x,lppPosition.y);
			CAranockAssistDlg::SetDlgItemInt(IDC_CURPOS_X,lppResult.x,FALSE);
			CAranockAssistDlg::SetDlgItemInt(IDC_CURPOS_Y,lppResult.y,FALSE);
			if(lppResult.x > 50000) {
				if(lppResult.y > 50000) {
					if(CAranockAssistDlg::IsDlgButtonChecked(IDC_CLICK_AUTO)) {
						CAranockAssistDlg::CheckDlgButton(IDC_CLICK_AUTO,BST_UNCHECKED);
						CAranockAssistDlg::OnClickAuto();
					} else {
						CAranockAssistDlg::CheckDlgButton(IDC_CLICK_AUTO,BST_CHECKED);
						CAranockAssistDlg::OnClickAuto();
					}
				}
			}
		}
	//}
	// Recall
	if(CAranockAssistDlg::IsDlgButtonChecked(IDC_RECALL_AUTO)) {
		if(CAranockAssistDlg::GetDlgItemInt(IDC_HEALTH_CURRENT,NULL,FALSE) <= CAranockAssistDlg::GetDlgItemInt(IDC_RECALL_MIN,NULL,FALSE)) {
			
			CAranockAssistDlg::SendKeystroke(VK_F5,true);

			// uncheck auto recall/heal/mana/click			
			CAranockAssistDlg::CheckDlgButton(IDC_RECALL_AUTO,BST_UNCHECKED);
			CAranockAssistDlg::CheckDlgButton(IDC_HEALTH_AUTO,BST_UNCHECKED);
			CAranockAssistDlg::CheckDlgButton(IDC_MANA_AUTO,BST_UNCHECKED);
			CAranockAssistDlg::CheckDlgButton(IDC_CLICK_AUTO,BST_UNCHECKED);
			CAranockAssistDlg::CheckDlgButton(IDC_AUTO_PROTECTION,BST_UNCHECKED);
			CAranockAssistDlg::CheckDlgButton(IDC_AUTO_ENHANCE,BST_UNCHECKED);
			return;
		}
	}
 
	// Health
	if(CAranockAssistDlg::IsDlgButtonChecked(IDC_HEALTH_AUTO)) {
		int iCurrentHealth = CAranockAssistDlg::GetDlgItemInt(IDC_HEALTH_CURRENT,NULL,FALSE);

		// if HEALTH_CURRENT <= HEALTH_MIN
		if(CAranockAssistDlg::GetDlgItemInt(IDC_HEALTH_CURRENT,NULL,FALSE) <= CAranockAssistDlg::GetDlgItemInt(IDC_HEALTH_MIN,NULL,FALSE)) {
			if ( iLastHealth != iCurrentHealth) {
				iLastHealth = iCurrentHealth;
				CAranockAssistDlg::ClickHealthPotion();
				return;
			} else {
				CAranockAssistDlg::CheckDlgButton(IDC_HEALTH_AUTO,BST_UNCHECKED);
			}
		}
	}

	// Mana
	if(CAranockAssistDlg::IsDlgButtonChecked(IDC_MANA_AUTO)) {
		int iCurrentMana = CAranockAssistDlg::GetDlgItemInt(IDC_MANA_CURRENT,NULL,FALSE);

		if(CAranockAssistDlg::GetDlgItemInt(IDC_MANA_CURRENT,NULL,FALSE) <= CAranockAssistDlg::GetDlgItemInt(IDC_MANA_MIN,NULL,FALSE)) {
			if ( iLastMana != iCurrentMana) {
				iLastMana = iCurrentMana;
				CAranockAssistDlg::ClickManaPotion();
				return;
			} else {
				//CAranockAssistDlg::CheckDlgButton(IDC_MANA_AUTO,BST_UNCHECKED);
			}
		}
		
	}
}

void CAranockAssistDlg::CheckAranockSpells() {
	if(CAranockAssistDlg::IsDlgButtonChecked(IDC_AUTO_PROTECTION)) {
			CAranockAssistDlg::SendKeystroke(VK_F1,true);
	}
	if(CAranockAssistDlg::IsDlgButtonChecked(IDC_AUTO_ENHANCE)) {
		CAranockAssistDlg::SendKeystroke(VK_F2,true);
	}
	if(CAranockAssistDlg::IsDlgButtonChecked(IDC_AUTO_BLESS)) {
		CAranockAssistDlg::SendKeystroke(VK_F3,true);
	}
}

void CAranockAssistDlg::OnTimer(UINT nIDEvent) 
{
	HWND hWndAranock = ::FindWindow(IDS_WINDOW_CLASS,0);
	if(IsWindow(hWndAranock)) {
		switch (nIDEvent) 
	   { 
	        case 1: // Auto Heal/Mana/Recall
				CAranockAssistDlg::ReadAranockValues();
				CAranockAssistDlg::CheckAranockValues();
				//if ( ::GetForegroundWindow() == hWndAranock ) {
/*					if( CAranockAssistDlg::GetDlgItemInt(IDC_CLICK_COUNT,NULL,FALSE) > 1 ) {
						CAranockAssistDlg::SetDlgItemInt(
							IDC_CLICK_COUNT,
							(CAranockAssistDlg::GetDlgItemInt(IDC_CLICK_COUNT,NULL,FALSE)) - 1,
							FALSE);
*/				//	CAranockAssistDlg::CheckAranockValues();
				//}
			
	             return; 

			case 2: // Auto Spells
				CAranockAssistDlg::CheckAranockSpells();
				return;
 


//
	        case 7: // Auto Click
				if ( ::GetForegroundWindow() == hWndAranock && GetDlgItemInt(IDC_CLICK_COUNT,NULL,FALSE) > 0 ) {
					SetDlgItemInt(IDC_CLICK_COUNT,(GetDlgItemInt(IDC_CLICK_COUNT,NULL,FALSE) - 1),FALSE);
					CAranockAssistDlg::ClickMouseAuto();
				} else {
					KillTimer(7);
					CAranockAssistDlg::CheckDlgButton(IDC_CLICK_AUTO,BST_UNCHECKED);
				}
				return; 

			case 776: // Auto Mine
				if ( ::GetForegroundWindow() == hWndAranock ) {
					CAranockAssistDlg::MineMouseAuto();
				} else {
					KillTimer(776);
					CAranockAssistDlg::CheckDlgButton(IDC_CLICK_AUTO,BST_UNCHECKED);
				}
				return; 


			case 222: // Auto Protection
				if ( ::GetForegroundWindow() == hWndAranock ) {
					CAranockAssistDlg::SendKeystroke(VK_F6,true);
				}
	           return; 

			case 333: // Auto Enhance
				if ( ::GetForegroundWindow() == hWndAranock
					CAranockAssistDlg::SendKeystroke(VK_F7,true);
				}
	           return; 

			case 444: // Auto Bless
				if ( ::GetForegroundWindow() == hWndAranock ) {
					CAranockAssistDlg::SendKeystroke(VK_F8,true);
				}

	           return; 


	    }
	} else {
		KillTimer(1);
		KillTimer(7);
		KillTimer(223);
		KillTimer(333);
		KillTimer(444);
		KillTimer(776);
	}

	CDialog::OnTimer(nIDEvent);
}

void CAranockAssistDlg::ClickMouseAuto()
{
	Sleep(Random(800));
	CAranockAssistDlg::SendMouseClick(
		GetDlgItemInt(IDC_AUTOCLICK_X,NULL,FALSE) - Random(25),
		GetDlgItemInt(IDC_AUTOCLICK_Y,NULL,FALSE) - Random(25),
		true);
}


void CAranockAssistDlg::MineMouseAuto()
{
		CAranockAssistDlg::SendMouseClick((GetDlgItemInt(IDC_AUTOMINE_X,NULL,FALSE)+250),(GetDlgItemInt(IDC_AUTOMINE_Y,NULL,FALSE)+250),true);
		Sleep(250);
		CAranockAssistDlg::SendMouseClick(GetDlgItemInt(IDC_AUTOMINE_X,NULL,FALSE),GetDlgItemInt(IDC_AUTOMINE_Y,NULL,FALSE),true);
}

void CAranockAssistDlg::ClickHealthPotion()
{
	//CAranockAssistDlg::SendMouseClick(23000,2000,false);
	CAranockAssistDlg::SendKeystroke(VK_F4,true);
}

void CAranockAssistDlg::ClickManaPotion()
{
	CAranockAssistDlg::SendMouseClick(23000,2000,false);
	Sleep(100);
	CAranockAssistDlg::SendMouseClick(24000,2000,false);
}

void CAranockAssistDlg::OnAutoSpell() 
{
	if(CAranockAssistDlg::IsDlgButtonChecked(IDC_AUTO_SPELL)) {
		if(CAranockAssistDlg::IsDlgButtonChecked(IDC_AUTO_PROTECTION))
			SetTimer(222,TEN_MINUTES,NULL);
	
		if(CAranockAssistDlg::IsDlgButtonChecked(IDC_AUTO_ENHANCE))
			SetTimer(333,TEN_MINUTES,NULL);

		if(CAranockAssistDlg::IsDlgButtonChecked(IDC_AUTO_BLESS))
			SetTimer(444,TEN_MINUTES,NULL);
	} else {
		KillTimer(222);
		KillTimer(333);
		KillTimer(444);
	}
}

void CAranockAssistDlg::OnClickAuto() 
{
	if(CAranockAssistDlg::IsDlgButtonChecked(IDC_CLICK_AUTO)) {
		// Tab to aranock
		//::SetForegroundWindow(::FindWindow(IDS_WINDOW_CLASS,0));
		int iDelay = ( CAranockAssistDlg::GetDlgItemInt(IDC_CLICK_SECONDS,NULL,FALSE) * 1000 );
		SetTimer(7,iDelay,NULL);
	} else {
		KillTimer(7);
	}
}

void CAranockAssistDlg::OnMineAuto() 
{
	if(CAranockAssistDlg::IsDlgButtonChecked(IDC_MINE_AUTO)) {
		// Tab to aranock
		//::SetForegroundWindow(::FindWindow(IDS_WINDOW_CLASS,0));
		int iDelay = ( CAranockAssistDlg::GetDlgItemInt(IDC_MINE_SECONDS,NULL,FALSE) * 1000 );
		SetTimer(776,iDelay,NULL);
	} else {
		KillTimer(776);
	}
}

void CAranockAssistDlg::OnCheckAll() 
{
	CAranockAssistDlg::CheckDlgButton(IDC_RECALL_AUTO,BST_CHECKED);
	CAranockAssistDlg::CheckDlgButton(IDC_HEALTH_AUTO,BST_CHECKED);
	CAranockAssistDlg::CheckDlgButton(IDC_MANA_AUTO,BST_CHECKED);
	//CAranockAssistDlg::CheckDlgButton(IDC_CLICK_AUTO,BST_CHECKED);
	CAranockAssistDlg::CheckDlgButton(IDC_AUTO_SPELL,BST_CHECKED);
	CAranockAssistDlg::CheckDlgButton(IDC_AUTO_PROTECTION,BST_CHECKED);
	CAranockAssistDlg::CheckDlgButton(IDC_AUTO_ENHANCE,BST_CHECKED);	
	CAranockAssistDlg::CheckDlgButton(IDC_AUTO_BLESS,BST_CHECKED);
}

void CAranockAssistDlg::SendMouseClick(int x,int y,bool bShift)
{
	if(bInUse) {
		Sleep(RETRY_TIME + Random(250));
		SendMouseClick(x,y,bShift);
		return;
	} else {
		bInUse = true;
		// move mouse
		mouse_event(MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE,
			x,y,
			NULL,NULL);

		if(bShift) {
			// shift down
			keybd_event(VK_SHIFT,NULL,NULL,NULL);
			Sleep(CLICK_PAUSETIME);
		}
		// mouse down
		mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,NULL,NULL);
		Sleep(CLICK_PAUSETIME);
	
		// shift up
		mouse_event(MOUSEEVENTF_LEFTUP,0,0,NULL,NULL);
		Sleep(CLICK_PAUSETIME);
		if(bShift) {
			// mouse up
			keybd_event(VK_SHIFT,NULL,KEYEVENTF_KEYUP,NULL);
		}
		Sleep(CLICK_PAUSETIME);
		bInUse = false;
	}
}

void CAranockAssistDlg::SendKeystroke(BYTE bkey,bool bShift)
{
	if(bKeyInUse) {
		Sleep(RETRY_TIME + Random(250));
		SendKeystroke(bkey,bShift);
		return;
	} else {
		bKeyInUse = true;
		if(bShift) {
		// shift down
			keybd_event(VK_SHIFT,NULL,NULL,NULL);
			Sleep(CLICK_PAUSETIME);
		}	
		// key down
		keybd_event(bkey,NULL,NULL,NULL);
		Sleep(CLICK_PAUSETIME);
	
		if(bShift) {
			// shift up
			keybd_event(bkey,NULL,KEYEVENTF_KEYUP,NULL);
			Sleep(CLICK_PAUSETIME);
		}
		// key up
		keybd_event(bkey,NULL,KEYEVENTF_KEYUP,NULL);
		Sleep(CLICK_PAUSETIME);
		bKeyInUse = false;
	}
}

HBRUSH CAranockAssistDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	// Colors
  HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// Health Static
	if (pWnd->GetDlgCtrlID() == IDC_HEALTH_AUTO) {
		pDC->SetTextColor(RGB(255, 0, 0));
		pDC->SetBkMode(TRANSPARENT); }  
	// Health Edit
	if (pWnd->GetDlgCtrlID() == IDC_HEALTH_MIN) {
		//pDC->SetBkColor(RGB(255, 0, 0));
		pDC->SetTextColor(RGB(255, 0, 0));
		pDC->SetBkMode(TRANSPARENT); }
	// Health Static
	if (pWnd->GetDlgCtrlID() == IDC_HEALTH_STATIC) {
		pDC->SetTextColor(RGB(255, 0, 0));
		pDC->SetBkMode(TRANSPARENT); }

	// Mana
	if (pWnd->GetDlgCtrlID() == IDC_MANA_AUTO) {
		pDC->SetTextColor(RGB(0, 0, 255));
		pDC->SetBkMode(TRANSPARENT); }  
	// Mana Edit
	if (pWnd->GetDlgCtrlID() == IDC_MANA_MIN) {
		pDC->SetTextColor(RGB(0, 0, 255));
		pDC->SetBkMode(TRANSPARENT); }
	// Mana Static
	if (pWnd->GetDlgCtrlID() == IDC_MANA_STATIC) {
		pDC->SetTextColor(RGB(0, 0, 255));
		pDC->SetBkMode(TRANSPARENT); }


	return hbr;
}

BOOL CAranockAssistDlg::OnInitDialog()
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
	

	CAranockAssistDlg::SetDlgItemInt(IDC_HEALTH_MIN,75,FALSE);
	CAranockAssistDlg::SetDlgItemInt(IDC_MANA_MIN,41,FALSE);
	CAranockAssistDlg::SetDlgItemInt(IDC_RECALL_MIN,50,FALSE);
	CAranockAssistDlg::SetDlgItemInt(IDC_CLICK_COUNT,18,false);
	

	// auto click
	CAranockAssistDlg::SetDlgItemInt(IDC_CLICK_SECONDS,10,FALSE);
	CAranockAssistDlg::SetDlgItemInt(IDC_AUTOCLICK_X,31500,FALSE);
	CAranockAssistDlg::SetDlgItemInt(IDC_AUTOCLICK_Y,46000,FALSE);

	// auto mine
	CAranockAssistDlg::SetDlgItemInt(IDC_MINE_SECONDS,15,FALSE);
	CAranockAssistDlg::SetDlgItemInt(IDC_AUTOMINE_X,31250,FALSE);
	CAranockAssistDlg::SetDlgItemInt(IDC_AUTOMINE_Y,45750,FALSE);

	CAranockAssistDlg::SetDlgItemText(IDC_HEALTH_ACTION,"SHIFT + F4");
	CAranockAssistDlg::SetDlgItemText(IDC_MANA_ACTION,"CLICK POTION");
	CAranockAssistDlg::SetDlgItemText(IDC_RECALL_ACTION,"SHIFT + F5");

	srand( (unsigned)time( NULL ) );

/*	char *tbuf = (char*) malloc(32);
	sprintf(tbuf,"Rnd: %i",Random(3));
	::MessageBox(NULL,tbuf,"",MB_OK);*/
	
	CAranockAssistDlg::ReadAranockValues();
	SetTimer(1,2000,0);

	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAranockAssistDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CAranockAssistDlg::OnPaint() 
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
HCURSOR CAranockAssistDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

POINT CAranockAssistDlg::ConvertXY(int x,int y)
{
	POINT lppPosition;

	long temp1 = x * 65535;
	lppPosition.x = temp1 / 1024;

	temp1 = y * 65535;
	lppPosition.y = temp1 / 768;

	return lppPosition;
}


void CAranockAssistDlg::OnTest()
{
	Sleep(15000);

	POINT lppPosition;

	if(GetCursorPos(&lppPosition)) {
		CAranockAssistDlg::SetDlgItemInt(IDC_TEST_EDITX,lppPosition.x,FALSE);
		CAranockAssistDlg::SetDlgItemInt(IDC_TEST_EDITY,lppPosition.y,FALSE);


		int x = 0;
		int y = 0;

		long temp1 = lppPosition.x * 65535;
		x = temp1 / 1024;

		temp1 = lppPosition.y * 65535;
		y = temp1 / 768;

		CAranockAssistDlg::SetDlgItemInt(IDC_TEST_X,x,FALSE);
		CAranockAssistDlg::SetDlgItemInt(IDC_TEST_Y,y,FALSE);
	}

}

int CAranockAssistDlg::Random(int Max)
{
	return (rand() % Max);
}
