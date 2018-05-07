// PROTESTDlg.cpp : implementation file
// 

#include "stdafx.h"
#include "PROTEST.h"
#include "PROTESTDlg.h"
#include "math.h"

SOCKADDR_IN addrFrom;	

BYTE recvBuf[1024*1025];
char tempBuf[10];
unsigned short int image_row=0;
unsigned short int image_col=0;

BYTE imagedata1[1024*1025];//8bit上报图像数据

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
// CPROTESTDlg dialog

CPROTESTDlg::CPROTESTDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPROTESTDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPROTESTDlg)
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
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPROTESTDlg, CDialog)
	//{{AFX_MSG_MAP(CPROTESTDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_RECVDATA,OnRecvData)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////
// CPROTESTDlg message handlers

BOOL CPROTESTDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	//创建UDP图像接收线程RecvPro
	InitSocket();
	RECVPARAM *pRecvParam=new RECVPARAM;
	pRecvParam->sock=m_socket;
	pRecvParam->hwnd=m_hWnd;
	HANDLE hThread=CreateThread(NULL,0,RecvPro,(LPVOID)pRecvParam,0,NULL);//RecvProc为线程函数	
	CloseHandle(hThread);
	
	//计算放大倍数
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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPROTESTDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{

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

//初始化UDP端口
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

//UDP数据接收线程
DWORD WINAPI CPROTESTDlg::RecvPro(LPVOID lpParameter)
{
	SOCKET sock=((RECVPARAM*)lpParameter)->sock;	
    HWND hwnd=((RECVPARAM*)lpParameter)->hwnd;
    delete lpParameter;	//释放对象

    int len=sizeof(SOCKADDR);
    while(TRUE)
    {	
 		for(int m=0;m<1024;m++)		//从原来的1025改为1024
 		{
 			recvfrom(sock,(char*)recvBuf,1024,0,(SOCKADDR*)&addrFrom,&len);
			memcpy(imagedata1+m*1024,recvBuf,1024);
 		}                                                                           
        ::PostMessage(hwnd,WM_RECVDATA,0,(LPARAM)tempBuf);//提交消息，触发消息响应
    }
	return 0;
}

//接收图像时的响应函数（根据imagedata1[]的内容绘制图像窗口）
LPARAM CPROTESTDlg::OnRecvData(WPARAM wParam, LPARAM lParam)
{
	//在IDC_DISPLAY上显示图像（根据imagedata1数组全部刷新图像）
	((CPROTESTApp*)AfxGetApp())->do_blending(imagedata1,1024,1025,GetDlgItem(IDC_DISPLAY)->m_hWnd);
			 
	framelastnum++;				//帧号累加
	SetDlgItemInt(IDC_FRAMENUM,framelastnum);		//显示图像帧号

	return 0;
}

//窗口大小变化时的响应函数
void CPROTESTDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);	
	// TODO: Add your message handler code here
}






////发送获取状态指令
// void CPROTESTDlg::OnSend() //获取状态
// {
// //  TODO: Add your control notification handler code here
//	BYTE sendata[4];
//	sendata[0]=0xAA;
// 	sendata[1]=0x00;
// 	sendata[2]=0x00;
// 	sendata[3]=0xAA;
// 	sendto(m_socket,(char*)sendata,4,0,(SOCKADDR*)&addrFrom,sizeof(SOCKADDR));
// }

