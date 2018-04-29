; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPROTESTDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "PROTEST.h"

ClassCount=6
Class1=CPROTESTApp
Class2=CPROTESTDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CImage2Dlg
Class5=CImage1Dlg
Class6=CAfteImageDlg
Resource3=IDD_PROTEST_DIALOG

[CLS:CPROTESTApp]
Type=0
HeaderFile=PROTEST.h
ImplementationFile=PROTEST.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CPROTESTApp

[CLS:CPROTESTDlg]
Type=0
HeaderFile=PROTESTDlg.h
ImplementationFile=PROTESTDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_DISPLAY

[CLS:CAboutDlg]
Type=0
HeaderFile=PROTESTDlg.h
ImplementationFile=PROTESTDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_PROTEST_DIALOG]
Type=1
Class=CPROTESTDlg
ControlCount=11
Control1=IDC_DISPLAY,button,1476427776
Control2=IDC_SEND,button,1342242816
Control3=IDC_EDIT_WORK,edit,1350631552
Control4=IDC_STATIC1,static,1342308352
Control5=IDC_PIC_ROW,edit,1350631552
Control6=IDC_PIC_COL,edit,1350631552
Control7=IDC_FRAMENUM,edit,1350631552
Control8=IDC_STATIC5,static,1342308352
Control9=IDC_STATIC112,static,1342308352
Control10=IDC_STATIC111,static,1342308352
Control11=IDC_BUTTON1,button,1342242816

[CLS:CImage2Dlg]
Type=0
HeaderFile=Image2Dlg.h
ImplementationFile=Image2Dlg.cpp
BaseClass=CDialog
Filter=D

[CLS:CImage1Dlg]
Type=0
HeaderFile=Image1Dlg.h
ImplementationFile=Image1Dlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

[CLS:CAfteImageDlg]
Type=0
HeaderFile=AfteImageDlg.h
ImplementationFile=AfteImageDlg.cpp
BaseClass=CDialog
Filter=D

