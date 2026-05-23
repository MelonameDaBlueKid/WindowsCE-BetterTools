; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CServerDoc
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "chatsrvr.h"
LastPage=0

ClassCount=6
Class1=CServerApp
Class2=CAboutDlg
Class3=CDiscussionDlg
Class4=CMainFrame
Class5=CServerDoc
Class6=CServerView

ResourceCount=3
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX
Resource3=IDD_DISCUSSION

[CLS:CServerApp]
Type=0
BaseClass=CWinApp
HeaderFile=chatsrvr.h
ImplementationFile=chatsrvr.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=chatsrvr.cpp
ImplementationFile=chatsrvr.cpp
LastObject=CAboutDlg

[CLS:CDiscussionDlg]
Type=0
BaseClass=CDialog
HeaderFile=dialogs.h
ImplementationFile=dialogs.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=mainfrm.h
ImplementationFile=mainfrm.cpp

[CLS:CServerDoc]
Type=0
BaseClass=CDocument
HeaderFile=srvrdoc.h
ImplementationFile=srvrdoc.cpp
LastObject=CServerDoc

[CLS:CServerView]
Type=0
BaseClass=CEditView
HeaderFile=srvrvw.h
ImplementationFile=srvrvw.cpp

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_DISCUSSION]
Type=1
Class=CDiscussionDlg
ControlCount=3
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT1,edit,1350631424
Control3=IDOK,button,1342242817

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_SAVE
Command3=ID_APP_EXIT
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_VIEW_TOOLBAR
Command9=ID_VIEW_STATUS_BAR
Command10=ID_APP_ABOUT
CommandCount=10

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_FILE_NEW
Command3=ID_FILE_SAVE
Command4=ID_EDIT_PASTE
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_NEXT_PANE
Command8=ID_PREV_PANE
Command9=ID_EDIT_COPY
Command10=ID_EDIT_PASTE
Command11=ID_EDIT_CUT
Command12=ID_EDIT_UNDO
CommandCount=12

