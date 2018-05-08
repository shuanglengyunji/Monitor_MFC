// PROTESTDlg.cpp : implementation file
// 

#include "stdafx.h"
#include "PROTEST.h"
#include "PROTESTDlg.h"
#include "math.h"

SOCKADDR_IN addrFrom;		//socket�õĶ���

char MessageBuf[10];		//�洢WM_RECVDATA�ź���Я������Ϣ��buff
BYTE recvBuf[1024];			//���ջ�����
BYTE imagedata[1024*1024];	//��ʾ������

UINT8 framelastnum=0;		//֡��(0-255)

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

	//����UDPͼ������߳�RecvPro
	InitSocket();
	RECVPARAM *pRecvParam=new RECVPARAM;
	pRecvParam->sock=m_socket;
	pRecvParam->hwnd=m_hWnd;
	HANDLE hThread=CreateThread(NULL,0,RecvPro,(LPVOID)pRecvParam,0,NULL);//RecvProcΪ�̺߳���	
	CloseHandle(hThread);

	// ����֡�ʼ��㶨ʱ��
	SetTimer(1, 2000, NULL);	//2s����

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

//��ʼ��UDP�˿�
BOOL CPROTESTDlg::InitSocket()
{
	m_socket=socket(AF_INET,SOCK_DGRAM,0);
	if(INVALID_SOCKET==m_socket)
	{
		MessageBox("�׽��ִ���ʧ�ܣ�");
		return FALSE;
	}
	SOCKADDR_IN addrSock;
	addrSock.sin_family=AF_INET;
	addrSock.sin_port=htons(8000);
	addrSock.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
	int retval;	
	retval = bind(m_socket,(SOCKADDR*)&addrSock, sizeof(SOCKADDR));	//SOCKADDR��sockaddr�ĺ궨��
	if(SOCKET_ERROR==retval)
	{
		closesocket(m_socket);
		MessageBox("�׽��ְ�ʧ��");
		return FALSE;
	}
	return TRUE;
}

//UDP���ݽ����߳�
DWORD WINAPI CPROTESTDlg::RecvPro(LPVOID lpParameter)
{
	//����socket
	SOCKET sock=((RECVPARAM*)lpParameter)->sock;	
    HWND hwnd=((RECVPARAM*)lpParameter)->hwnd;
    delete lpParameter;	//�ͷŶ���

    int len=sizeof(SOCKADDR);

	//ѭ������������+����WM_RECVDATA��Ϣ
    while(TRUE)
    {
		//����֡ͷ
		while(1)
		{
			//��������
			recvfrom(sock, (char*)recvBuf, 4, 0, (SOCKADDR*)&addrFrom, &len);

			//�ж��Ƿ�Ϊ֡ͷ
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

			//��֡ͷ��������ѭ��
			break;
		}

		//����ͼ��
 		for(int m=0;m<1024;m++)		//1024��
 		{
 			recvfrom(sock,(char*)recvBuf,1024,0,(SOCKADDR*)&addrFrom,&len);	//ÿ��1024�ֽ�
			memcpy(imagedata+m*1024,recvBuf,1024);
 		}

		//������Ϣ�����յ�1024*1024��
        ::PostMessage(hwnd,WM_RECVDATA,0,(LPARAM)MessageBuf);//�ύ��Ϣ��������Ϣ��Ӧ
    }
	return 0;
}

//���ƴ���
//����ͼ��ʱ����Ӧ����������imagedata[]�����ݻ���ͼ�񴰿ڣ�
LPARAM CPROTESTDlg::OnRecvData(WPARAM wParam, LPARAM lParam)
{
	//��IDC_DISPLAY����ʾͼ�񣨸���imagedata����ȫ��ˢ��ͼ��
	((CPROTESTApp*)AfxGetApp())->do_blending(imagedata,1024,1024,GetDlgItem(IDC_DISPLAY)->m_hWnd);
	
	framelastnum++;									//֡���ۼ�

	return 0;
}

//���ڴ�С�仯ʱ����Ӧ����
void CPROTESTDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);	
	// TODO: Add your message handler code here
}

////���ͻ�ȡ״ָ̬��
// void CPROTESTDlg::OnSend() //��ȡ״̬
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
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

		tmp = tmp / 2;	// ����Ϊ2s

		framelastnum_old = framelastnum_now;

		//��ʾͼ��֡��
		SetDlgItemInt(IDC_FRAMENUM, tmp);
	}

	CDialog::OnTimer(nIDEvent);
}
