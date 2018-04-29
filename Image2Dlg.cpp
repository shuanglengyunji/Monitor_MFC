// Image2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "PROTEST.h"
#include "Image2Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImage2Dlg dialog


CImage2Dlg::CImage2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CImage2Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CImage2Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CImage2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImage2Dlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CImage2Dlg, CDialog)
	//{{AFX_MSG_MAP(CImage2Dlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImage2Dlg message handlers
