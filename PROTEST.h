// PROTEST.h : main header file for the PROTEST application
// 

#if !defined(AFX_PROTEST_H__8D3E4819_B57A_4023_A1F2_44BEDA0E742A__INCLUDED_)
#define AFX_PROTEST_H__8D3E4819_B57A_4023_A1F2_44BEDA0E742A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include <ddraw.h>
/////////////////////////////////////////////////////////////////////////////
// CPROTESTApp:
// See PROTEST.cpp for the implementation of this class
//

class CPROTESTApp : public CWinApp
{
public:
	CPROTESTApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPROTESTApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPROTESTApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL deinitial_draw();
	BOOL initial_draw(GUID *pdisplay);
public:
		void DoBlending(LPDIRECTDRAWSURFACE7 psur,HWND hdestwnd);
		LPDIRECTDRAW7 m_pDD;
		LPDIRECTDRAWCLIPPER m_pDDClipper;
		LPDIRECTDRAWSURFACE7 m_pDDSprimary_window,m_pDDSBack;
		LPDIRECTDRAWSURFACE7 m_pYsur;
		int m_img_width,m_img_height;
		static void do_blending(unsigned char *pYbuf,int width,int height,HWND hdestwnd);
		LPDIRECTDRAWSURFACE7 create_surface_rgb32(int width, int height);

};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROTEST_H__8D3E4819_B57A_4023_A1F2_44BEDA0E742A__INCLUDED_)
