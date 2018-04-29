#if !defined(AFX_IMAGE2DLG_H__9BBC68CC_A453_4280_A401_90F476C12F36__INCLUDED_)
#define AFX_IMAGE2DLG_H__9BBC68CC_A453_4280_A401_90F476C12F36__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Image2Dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CImage2Dlg dialog

class CImage2Dlg : public CDialog
{
// Construction
public:
	CImage2Dlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CImage2Dlg)
	enum { IDD = IDD_IMAGE2_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImage2Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CImage2Dlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGE2DLG_H__9BBC68CC_A453_4280_A401_90F476C12F36__INCLUDED_)
