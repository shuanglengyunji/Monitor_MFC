// PROTESTDlg.cpp : implementation file
// 

#include "stdafx.h"
#include "PROTEST.h"
#include "PROTESTDlg.h"
#include "math.h"

SOCKADDR_IN addrFrom;		//socket用的对象

char MessageBuf[10];		//存储WM_RECVDATA信号所携带的信息的buff
BYTE recvBuf[1024];			//接收缓冲区
BYTE imagedata[1024*1024];	//显示缓冲区

UINT8 framelastnum=0;		//帧号(0-255)

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
	ON_WM_TIMER()
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

	// 创建帧率计算定时器
	SetTimer(1, 2000, NULL);	//2s周期

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
	retval = bind(m_socket,(SOCKADDR*)&addrSock, sizeof(SOCKADDR));	//SOCKADDR是sockaddr的宏定义
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
	//建立socket
	SOCKET sock=((RECVPARAM*)lpParameter)->sock;	
    HWND hwnd=((RECVPARAM*)lpParameter)->hwnd;
    delete lpParameter;	//释放对象

    int len=sizeof(SOCKADDR);

	//循环：接收内容+发送WM_RECVDATA消息
    while(TRUE)
    {
		//接收帧头
		while(1)
		{
			//接收数据
			recvfrom(sock, (char*)recvBuf, 4, 0, (SOCKADDR*)&addrFrom, &len);

			//判断是否为帧头
			if (recvBuf[0] != 0xAA)
			{
				continue;
			}
			if (recvBuf[1] != 0xBB)
			{
				continue;
			}
			if (recvBuf[2] != 0xCC)
			{
				continue;
			}
			if (recvBuf[3] != 0xDD)
			{
				continue;
			}

			//是帧头，则跳出循环
			break;
		}

		//接收图像
 		for(int m=0;m<1024;m++)		//1024行
 		{
 			recvfrom(sock,(char*)recvBuf,1024,0,(SOCKADDR*)&addrFrom,&len);	//每行1024字节
			memcpy(imagedata+m*1024,recvBuf,1024);
 		}

		//发送消息（接收到1024*1024）
        ::PostMessage(hwnd,WM_RECVDATA,0,(LPARAM)MessageBuf);//提交消息，触发消息响应
    }
	return 0;
}

//绘制窗口
//接收图像时的响应函数（根据imagedata[]的内容绘制图像窗口）
LPARAM CPROTESTDlg::OnRecvData(WPARAM wParam, LPARAM lParam)
{
	//在IDC_DISPLAY上显示图像（根据imagedata数组全部刷新图像）
	((CPROTESTApp*)AfxGetApp())->do_blending(imagedata,1024,1024,GetDlgItem(IDC_DISPLAY)->m_hWnd);
	
	framelastnum++;									//帧号累加

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


void CPROTESTDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	if (nIDEvent == 1)
	{
		int tmp;
		int framelastnum_now = 0;
		static int framelastnum_old = 0;

		framelastnum_now = framelastnum;
		if (framelastnum_now >= framelastnum_old)
			tmp = framelastnum_now - framelastnum_old;
		else
			tmp = framelastnum_now + (255 - framelastnum_old);

		tmp = tmp / 2;	// 周期为2s

		framelastnum_old = framelastnum_now;

		//显示图像帧率
		SetDlgItemInt(IDC_FRAMENUM, tmp);
	}

	CDialog::OnTimer(nIDEvent);
}
