// AfteImageDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PROTEST.h"
#include "AfteImageDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAfteImageDlg dialog


CAfteImageDlg::CAfteImageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAfteImageDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAfteImageDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAfteImageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAfteImageDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAfteImageDlg, CDialog)
	//{{AFX_MSG_MAP(CAfteImageDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAfteImageDlg message handlers
