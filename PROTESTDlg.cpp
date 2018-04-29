// PROTESTDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PROTEST.h"
#include "PROTESTDlg.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// BYTE image[720*576]={0};
// BYTE image1[720*576]={0};
// BYTE image2[720*576]={0};

SOCKADDR_IN addrFrom;	

//FILE *fpTarget;//目标信息文件
BOOL RECVPIC=FALSE;

//FILE *fp;//图像文件

BYTE recvBuf[1024*1025];//1244160=720*576*3)
char tempBuf[10];
//int num=0;
//BYTE getstate[2]={0};//帧头，指令代码（发送）
unsigned short int image_row=0;
unsigned short int image_col=0;
//BYTE imagedata1[1024*1025];//上报图像数据
BYTE imagedata1[1024*1025];//8bit上报图像数据
//WORD imagedata2[1024*1025];//16bit上报图像数据
//BYTE imga0[1024*1025];//a0
//BYTE imga1[1024*1025];//a1
//BYTE imga2[1024*1025];//a2


int framelastnum=0;

BOOL change_flag=FALSE;
float m_nDlgWidth; 
float m_nDlgHeight;
//计算分辨率
float m_nWidth ; 
float m_nHeight;
//计算放大倍数
float m_Multiple_width ; 
float m_Mutiple_heith ;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPROTESTDlg dialog

CPROTESTDlg::CPROTESTDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPROTESTDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPROTESTDlg)
	m_zhenhao = 0;
	m_imagecol = 0;
	m_imagerow = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
CPROTESTDlg::~CPROTESTDlg()
{
}
///
void CPROTESTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPROTESTDlg)
	DDX_Text(pDX, IDC_PIC_COL, m_imagecol);
	DDX_Text(pDX, IDC_PIC_ROW, m_imagerow);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPROTESTDlg, CDialog)
	//{{AFX_MSG_MAP(CPROTESTDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SEND, OnSend)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON1, OnBtnShow)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_RECVDATA,OnRecvData)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////
// CPROTESTDlg message handlers

BOOL CPROTESTDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.
//   	VERIFY( 1 == SetWindowSkin( this->m_hWnd , "MainFrame" ));
//   	VERIFY( 1 == SetDialogSkin( "Dialog" ) );
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	InitSocket();
	RECVPARAM *pRecvParam=new RECVPARAM;
	pRecvParam->sock=m_socket;
	pRecvParam->hwnd=m_hWnd;
	HANDLE hThread=CreateThread(NULL,0,RecvPro,(LPVOID)pRecvParam,0,NULL);//RecvProc为线程函数	
	CloseHandle(hThread);

//	memset(image2,150,720*576);
// 	CWnd *pWnd;
// 	pWnd = GetDlgItem( IDC_DISPLAY );
// 	pWnd->SetWindowPos( NULL,0,0,720,576,SWP_NOZORDER | SWP_NOMOVE );  //把编辑控件的大小设为(720,576)，位置不变
    SetDlgItemInt(IDC_PIC_ROW,1024);
	SetDlgItemInt(IDC_PIC_COL,1025);


	CRect rect; 
	::GetWindowRect(m_hWnd,rect); 
	ScreenToClient(rect); 
	m_nDlgWidth =(float) (rect.right - rect.left); 
	m_nDlgHeight = (float)(rect.bottom - rect.top);
	//计算分辨率
	m_nWidth = (float)(GetSystemMetrics(SM_CXSCREEN)); 
	m_nHeight = (float)(GetSystemMetrics(SM_CYSCREEN));
	//计算放大倍数
	m_Multiple_width = float(m_nWidth)/float(m_nDlgWidth); 
	m_Mutiple_heith = float(m_nHeight)/float(m_nDlgHeight); 
	change_flag=TRUE;//这个是成员变量bool形，用来判断onsize执行时oninitdlg是否已经执行了
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPROTESTDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;

		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPROTESTDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPROTESTDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CPROTESTDlg::InitSocket()
{
	m_socket=socket(AF_INET,SOCK_DGRAM,0);
	if(INVALID_SOCKET==m_socket)
	{
		MessageBox("套接字创建失败！");
		return FALSE;
	}
	SOCKADDR_IN addrSock;
	addrSock.sin_family=AF_INET;
	addrSock.sin_port=htons(8000);
	addrSock.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
	int retval;	
	retval = bind(m_socket,(SOCKADDR*)&addrSock, sizeof(SOCKADDR));//SOCKADDR是sockaddr的宏定义
	if(SOCKET_ERROR==retval)
	{
		closesocket(m_socket);
		MessageBox("套接字绑定失败");
		return FALSE;
	}
	return TRUE;
}

DWORD WINAPI CPROTESTDlg::RecvPro(LPVOID lpParameter)
{
	SOCKET sock=((RECVPARAM*)lpParameter)->sock;	
    HWND hwnd=((RECVPARAM*)lpParameter)->hwnd;
    delete lpParameter; //释放对象
//	SOCKADDR_IN addrFrom;	
    int len=sizeof(SOCKADDR);	
    while(TRUE)   	
    {	
 		for(int m=0;m<1025;m++)
 		{
 			recvfrom(sock,(char*)recvBuf,1024,0,(SOCKADDR*)&addrFrom,&len);
			memcpy(imagedata1+m*1024,recvBuf,1024);
 		}                                                                           
        ::PostMessage(hwnd,WM_RECVDATA,0,(LPARAM)tempBuf);//提交消息，触发消息响应            	
    }
	return 0;
}
LPARAM CPROTESTDlg::OnRecvData(WPARAM wParam, LPARAM lParam)
{

	((CPROTESTApp*)AfxGetApp())->do_blending(imagedata1,1024,1025,GetDlgItem(IDC_DISPLAY)->m_hWnd);
			 
	framelastnum++;
	SetDlgItemInt(IDC_FRAMENUM,framelastnum);
	SetDlgItemText(IDC_EDIT_WORK,"收图显示中");
	RECVPIC=FALSE;
	return 0;
}
 void CPROTESTDlg::OnSend() //获取状态
 {
 //  TODO: Add your control notification handler code here
	BYTE sendata[4];
	sendata[0]=0xAA;
 	sendata[1]=0x00;
 	sendata[2]=0x00;
 	sendata[3]=0xAA;
 	sendto(m_socket,(char*)sendata,4,0,(SOCKADDR*)&addrFrom,sizeof(SOCKADDR));
 }		

void CPROTESTDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);	
	// TODO: Add your message handler code here
	if (change_flag)//如果确定oninitdlg已经调用完毕.
	{
		ReSize(IDC_STATIC1);
		ReSize(IDC_STATIC5);
		ReSize(IDC_EDIT_WORK);
		ReSize(IDC_SEND);
		ReSize(IDC_DISPLAY);
		ReSize(IDC_PIC_ROW);
		ReSize(IDC_PIC_COL);
		ReSize(IDC_FRAMENUM);
		ReSize(IDC_STATIC111);
		ReSize(IDC_STATIC112);
		//恢复放大倍数，并保存 (确保还原时候能够还原到原来的大小)
		m_Multiple_width = float(1)/ m_Multiple_width ; 
		m_Mutiple_heith = float(1)/m_Mutiple_heith ; 
	}
}
void CPROTESTDlg::ReSize(int nID)
{
	CRect Rect; 
	GetDlgItem(nID)->GetWindowRect(Rect); 
	ScreenToClient(Rect); 
	//计算控件左上角点 
	CPoint OldTLPoint,TLPoint; 
	OldTLPoint = Rect.TopLeft(); 
	TLPoint.x = long(OldTLPoint.x *m_Multiple_width); 
	TLPoint.y = long(OldTLPoint.y * m_Mutiple_heith );
	//计算控件右下角点
	CPoint OldBRPoint,BRPoint; 
	OldBRPoint = Rect.BottomRight(); 
	BRPoint.x = long(OldBRPoint.x *m_Multiple_width); 
	BRPoint.y = long(OldBRPoint.y * m_Mutiple_heith ); 
	//移动控件到新矩形
	Rect.SetRect(TLPoint,BRPoint); 
	GetDlgItem(nID)->MoveWindow(Rect,TRUE); 
}


void CPROTESTDlg::OnBtnShow() 
{
	// TODO: Add your control notification handler code here

		FILE *fp = fopen("0.raw","rb+");
		 if(fp==NULL)
		 {
			 MessageBox("打开图像失败");
		 }
		 else
		 {
		  fread(imagedata1, 1,1024*1025, fp);
		  
		  ((CPROTESTApp*)AfxGetApp())->do_blending(imagedata1,1024,1025,GetDlgItem(IDC_DISPLAY)->m_hWnd);
		  fclose(fp);
		  
		 }
	
}
