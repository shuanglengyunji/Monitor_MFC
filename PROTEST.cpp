// PROTEST.cpp : Defines the class behaviors for the application.
// 

#include "stdafx.h"
#include "PROTEST.h"
#include "PROTESTDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPROTESTApp

BEGIN_MESSAGE_MAP(CPROTESTApp, CWinApp)
	//{{AFX_MSG_MAP(CPROTESTApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPROTESTApp construction

CPROTESTApp::CPROTESTApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CPROTESTApp object

CPROTESTApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CPROTESTApp initialization

BOOL CPROTESTApp::InitInstance()
{	
	if(!AfxSocketInit())
	{
		AfxMessageBox("加载套接字库失败!");
		return FALSE;
	}
	initial_draw(NULL);
	AfxEnableControlContainer();
// 	VERIFY( 1 == InitSkinMagicLib(AfxGetInstanceHandle(), NULL, NULL, NULL));
// 	VERIFY( 1 == LoadSkinFile("corona.smf")); //载入皮肤文件，x-plus.smf可以更换。
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	
	CPROTESTDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.

	return FALSE;
}
int CPROTESTApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	deinitial_draw();
//	ExitSkinMagicLib();
	return CWinApp::ExitInstance();
}
LPDIRECTDRAWSURFACE7 CPROTESTApp::create_surface_rgb32(int width, int height)
{
	DDSURFACEDESC2 ddsd;
	HRESULT hret;
	LPDIRECTDRAWSURFACE7 psur=NULL;
	ZeroMemory(&ddsd, sizeof(ddsd));
	ddsd.dwSize  = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH| DDSD_PIXELFORMAT;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN |DDSCAPS_VIDEOMEMORY;// DDSCAPS_SYSTEMMEMORY;
	ddsd.dwHeight = height;
	ddsd.dwWidth  = width;
	
	ddsd.ddpfPixelFormat.dwSize  = sizeof(DDPIXELFORMAT);
	ddsd.ddpfPixelFormat.dwFlags =DDPF_RGB;
	
	ddsd.ddpfPixelFormat.dwRGBBitCount=32;
	ddsd.ddpfPixelFormat.dwRBitMask=0xff0000;
	ddsd.ddpfPixelFormat.dwGBitMask=0xff00;
	ddsd.ddpfPixelFormat.dwBBitMask=0xff;
	ddsd.ddpfPixelFormat.dwRGBAlphaBitMask=0xff000000;
	
	hret=m_pDD->CreateSurface(&ddsd, &psur, NULL);
	if(hret!= DD_OK) {
		return NULL;
	}
	return psur;
}
BOOL CPROTESTApp::initial_draw(GUID *pdisplay)
{
	HRESULT hret;
	DDSURFACEDESC2 ddsd;
//create directdraw object	
	m_pDD=NULL;
	m_pDDSBack=NULL;
	m_pDDSprimary_window=NULL;
	m_pDDClipper=NULL;
	m_pYsur=NULL;
	m_img_height=m_img_width=0;

	hret = DirectDrawCreateEx(pdisplay, (VOID**)&m_pDD, IID_IDirectDraw7, NULL);
	if (hret != DD_OK) {
		goto fail_ret_ddraw;
	}

//set ddraw cooperative level
	hret=m_pDD->SetCooperativeLevel(AfxGetMainWnd()->GetSafeHwnd(), DDSCL_NORMAL);
	if (hret != DD_OK) {
		goto fail_ret_ddraw;
	}
	
//create ddraw primary surface	
	ZeroMemory(&ddsd, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS ;
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

	hret=m_pDD->CreateSurface(&ddsd, &m_pDDSprimary_window, NULL);
	if(hret!= DD_OK) {
		goto fail_ret_ddraw;
	}
	DDPIXELFORMAT pf;
	ZeroMemory(&pf,sizeof(DDPIXELFORMAT));
	pf.dwSize=sizeof(DDPIXELFORMAT);
	hret=m_pDDSprimary_window->GetPixelFormat(&pf);
	if(hret!=DD_OK)
		goto fail_ret_ddraw;

// Create a clipper for the primary surface
	hret=m_pDD->CreateClipper(0, &m_pDDClipper,NULL);
	if (hret!=DD_OK) {
		goto fail_ret_ddraw;
	}
//set the clipper for ddraw primary surface
	hret=m_pDDSprimary_window->SetClipper(m_pDDClipper);
	if (hret != DD_OK) {
		goto fail_ret_ddraw;
	}
	return TRUE;
fail_ret_ddraw:
	if(m_pDD!=NULL) {
		if(m_pDDSprimary_window!=NULL) {
			m_pDDSprimary_window->SetClipper(NULL);
			m_pDDSprimary_window->Release();
			m_pDDSprimary_window=NULL;
		}

		if(m_pDDClipper!=NULL) {
			m_pDDClipper->Release();
			m_pDDClipper=NULL;
		}
		m_pDD->Release();
		m_pDD=NULL;
	}
	return FALSE;	
}

BOOL CPROTESTApp::deinitial_draw()
{
	if(m_pDD!=NULL) {
		if(m_pDDSprimary_window!=NULL) {
			m_pDDSprimary_window->SetClipper(NULL);
			m_pDDSprimary_window->Release();
			m_pDDSprimary_window=NULL;
		}
		if(m_pDDClipper!=NULL) {
			m_pDDClipper->Release();
			m_pDDClipper=NULL;
		}
		m_pDD->Release();
		m_pDD=NULL;
	}
	if(m_pYsur!=NULL)
		m_pYsur->Release();
	return TRUE;
}


void CPROTESTApp::DoBlending(LPDIRECTDRAWSURFACE7 psur,HWND hdestwnd)
{
	HRESULT hRet;
	RECT rc;
	if(psur!=NULL) {
		if(::GetWindowRect(hdestwnd,&rc)) {
			m_pDDClipper->SetHWnd(0,hdestwnd);
			hRet=m_pDDSprimary_window->Blt(&rc,psur,NULL,DDBLT_WAIT,NULL);
			if(hRet!=DD_OK) {
				if(hRet==DDERR_SURFACELOST) {
					m_pDDSprimary_window->Restore();
				}
			}
		}
	}
}

void CPROTESTApp::do_blending(unsigned char *pYbuf,int width,int height,HWND hdestwnd)
{
	CPROTESTApp *papp=(CPROTESTApp *)AfxGetApp();
	if(papp!=NULL) {
		if(papp->m_img_height!=height||papp->m_img_width!=width) {
			if(papp->m_pYsur!=NULL) {
				papp->m_pYsur->Release();
				papp->m_pYsur=NULL;
			}
			papp->m_pYsur=papp->create_surface_rgb32(width,height);
			if(papp->m_pYsur!=NULL) {
				papp->m_img_height=height;
				papp->m_img_width=width;
			}
		}
		if(papp->m_pYsur!=NULL) {
			DDSURFACEDESC2 ddsd;
			HRESULT hret;

			ddsd.dwSize = sizeof(ddsd);
			hret=papp->m_pYsur->Lock(NULL, &ddsd, DDLOCK_NOSYSLOCK, NULL);
			if(hret== DD_OK) {
				BYTE *pline, *psrc;
				int i,j,t;

				pline=(BYTE *)ddsd.lpSurface;
#if 1
				for(i=0;i<height;i++) {
					psrc=pYbuf+/*(height-i-1)*/i*width;
					for(j=0,t=0;t<width;t++) {
						*(pline+j++)=*(psrc+t);
						*(pline+j++)=*(psrc+t);
						*(pline+j++)=*(psrc+t);
						*(pline+j++)=0xff;
					}
					pline+=ddsd.lPitch;
				}
#else
				memset(pline,0,ddsd.lPitch*papp->m_img_height);	
#endif
				papp->m_pYsur->Unlock(NULL);
				papp->DoBlending(papp->m_pYsur,hdestwnd);
			}else if(hret==DDERR_SURFACELOST)//may surface lost ?
				papp->m_pYsur->Restore();
		}
	}
}



