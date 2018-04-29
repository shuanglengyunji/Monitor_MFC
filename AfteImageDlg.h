#if !defined(AFX_AFTEIMAGEDLG_H__C0A77EF9_286F_42CD_B92A_74AB579AF6BB__INCLUDED_)
#define AFX_AFTEIMAGEDLG_H__C0A77EF9_286F_42CD_B92A_74AB579AF6BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AfteImageDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAfteImageDlg dialog

class CAfteImageDlg : public CDialog
{
// Construction
public:
	CAfteImageDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAfteImageDlg)
	enum { IDD = IDD_LASTIMAGE_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAfteImageDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAfteImageDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AFTEIMAGEDLG_H__C0A77EF9_286F_42CD_B92A_74AB579AF6BB__INCLUDED_)
