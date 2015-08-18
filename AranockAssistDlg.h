// AranockAssistDlg.h : header file
//

#if !defined(AFX_ARANOCKASSISTDLG_H__F9FD6B70_7C45_4E48_99A2_7D7C0D2D94CB__INCLUDED_)
#define AFX_ARANOCKASSISTDLG_H__F9FD6B70_7C45_4E48_99A2_7D7C0D2D94CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define IDS_WINDOW_CLASS "DDCWin"
#define CLICK_PAUSETIME 50

//#define dfHealthCurrentAddress 0x0063C72C

/////////////////////////////////////////////////////////////////////////////
// CAranockAssistDlg dialog

class CAranockAssistDlg : public CDialog
{
// Construction
public:
	CAranockAssistDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CAranockAssistDlg)
	enum { IDD = IDD_ARANOCKASSIST_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAranockAssistDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CAranockAssistDlg)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC,CWnd* pWnd,UINT nCtlColor);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void SpellTimer(HWND hwnd,UINT uMsg,UINT idEvent,DWORD dwTime);
	afx_msg void ClickTimer(HWND hwnd,UINT uMsg,UINT idEvent,DWORD dwTime);
	afx_msg void ReadAranockValues();
	afx_msg void CheckAranockValues();
	afx_msg void CheckAranockSpells();
	afx_msg void OnClickAuto();
	afx_msg void OnMineAuto();
	afx_msg void OnAutoProtection();
	afx_msg void OnAutoEnhance();
	afx_msg void SendMouseClick(int x,int y,bool bShift);
	afx_msg void SendKeystroke(BYTE bkey,bool bShift);
	afx_msg void ClickHealthPotion();
	afx_msg void ClickManaPotion();
	afx_msg void ClickMouseAuto();
	afx_msg void MineMouseAuto();
	afx_msg void OnCheckAll();
	afx_msg void OnAutoBless();
	afx_msg void OnAutoSpell();
	afx_msg void OnTest();
	afx_msg POINT ConvertXY(int x,int y);
	afx_msg void OnEditchangeHealthAction();
	afx_msg void OnEditchangeManaAction();
	afx_msg void OnEditchangeRecallAction();
	afx_msg int Random(int Max);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARANOCKASSISTDLG_H__F9FD6B70_7C45_4E48_99A2_7D7C0D2D94CB__INCLUDED_)
