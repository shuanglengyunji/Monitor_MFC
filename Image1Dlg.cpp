// Image1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "PROTEST.h"
#include "Image1Dlg.h"
#include "PROTEST.h"
#include "PROTESTDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImage1Dlg dialog


CImage1Dlg::CImage1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CImage1Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CImage1Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CImage1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImage1Dlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CImage1Dlg, CDialog)
	//{{AFX_MSG_MAP(CImage1Dlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImage1Dlg message handlers

BOOL CImage1Dlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
//	((CPROTESTApp*)AfxGetApp())->do_blending(image2,720,576,GetDlgItem(IDC_DISPLAY1)->m_hWnd);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


