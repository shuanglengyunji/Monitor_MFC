// PROTESTDlg.h : header file
// 

#if !defined(AFX_PROTESTDLG_H__D2C3901E_C1C7_43D3_9887_D640D422FCB4__INCLUDED_)
#define AFX_PROTESTDLG_H__D2C3901E_C1C7_43D3_9887_D640D422FCB4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define  WM_RECVDATA  WM_USER+1
/////////////////////////////////////////////////////////////////////////////
// CPROTESTDlg dialog
struct RECVPARAM
{
	SOCKET sock;
	HWND hwnd;
};
class CPROTESTDlg : public CDialog
{
// Construction
public:
	static DWORD WINAPI RecvPro(LPVOID lpParameter);
	BOOL InitSocket();
	CPROTESTDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CPROTESTDlg();
// Dialog Data
	//{{AFX_DATA(CPROTESTDlg)
	enum { IDD = IDD_PROTEST_DIALOG };

	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPROTESTDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPROTESTDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	afx_msg LPARAM OnRecvData(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
private:
	CPoint m_ptOrigin;
	SOCKET m_socket;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedGetImage();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROTESTDLG_H__D2C3901E_C1C7_43D3_9887_D640D422FCB4__INCLUDED_)
