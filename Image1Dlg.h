#if !defined(AFX_IMAGE1DLG_H__1DDEFBFE_10E1_453D_844C_2D86752D3638__INCLUDED_)
#define AFX_IMAGE1DLG_H__1DDEFBFE_10E1_453D_844C_2D86752D3638__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Image1Dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CImage1Dlg dialog

class CImage1Dlg : public CDialog
{
// Construction
public:
	CImage1Dlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CImage1Dlg)
	enum { IDD = IDD_IMAGE1_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImage1Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CImage1Dlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGE1DLG_H__1DDEFBFE_10E1_453D_844C_2D86752D3638__INCLUDED_)
