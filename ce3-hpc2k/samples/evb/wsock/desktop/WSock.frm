VERSION 5.00
Object = "{248DD890-BB45-11CF-9ABC-0080C7E7B78D}#1.0#0"; "MSWINSCK.OCX"
Begin VB.Form frmWSock 
   Caption         =   "Universal Winsock Connector"
   ClientHeight    =   3465
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   10680
   LinkTopic       =   "Form1"
   ScaleHeight     =   3465
   ScaleWidth      =   10680
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Command2 
      Caption         =   "Clear"
      Height          =   255
      Left            =   7740
      TabIndex        =   22
      Top             =   1845
      Width           =   960
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Clear"
      Height          =   255
      Left            =   1695
      TabIndex        =   21
      Top             =   1845
      Width           =   960
   End
   Begin VB.CommandButton cmdClear 
      Caption         =   "X"
      Height          =   375
      Left            =   5640
      TabIndex        =   14
      ToolTipText     =   "Clear Messages"
      Top             =   1320
      Width           =   375
   End
   Begin VB.CommandButton cmdBuildString 
      Caption         =   "$"
      Height          =   375
      Left            =   4800
      TabIndex        =   13
      ToolTipText     =   "BuildString"
      Top             =   1320
      Width           =   375
   End
   Begin VB.TextBox txtRecv 
      Height          =   1245
      Left            =   6120
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   12
      Top             =   2115
      Width           =   4455
   End
   Begin VB.CommandButton cmdSend 
      Caption         =   "Send"
      Height          =   375
      Left            =   1455
      TabIndex        =   11
      Top             =   945
      Width           =   1050
   End
   Begin VB.CommandButton cmdErr 
      Caption         =   "!"
      Height          =   375
      Left            =   5220
      TabIndex        =   10
      ToolTipText     =   "Errors"
      Top             =   1320
      Width           =   375
   End
   Begin MSWinsockLib.Winsock W2 
      Left            =   8400
      Top             =   600
      _ExtentX        =   741
      _ExtentY        =   741
      _Version        =   393216
   End
   Begin VB.TextBox txtSend 
      Height          =   1245
      Left            =   120
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   9
      Top             =   2115
      Width           =   5775
   End
   Begin VB.CommandButton cmdListen 
      Caption         =   "Start as Server"
      Height          =   375
      Left            =   2880
      TabIndex        =   8
      Top             =   1320
      Width           =   1815
   End
   Begin VB.CommandButton cmdConnect 
      Caption         =   "Connect to Server"
      Height          =   375
      Left            =   2880
      TabIndex        =   7
      Top             =   840
      Width           =   1815
   End
   Begin VB.OptionButton optIRDA 
      Caption         =   "2 - IRDA"
      Height          =   255
      Left            =   0
      TabIndex        =   6
      Top             =   1080
      Width           =   1095
   End
   Begin VB.OptionButton optUDP 
      Caption         =   "1 - UDP"
      Height          =   255
      Left            =   0
      TabIndex        =   5
      Top             =   720
      Width           =   1095
   End
   Begin VB.OptionButton optTCP 
      Caption         =   "0 - TCP"
      Height          =   255
      Left            =   0
      TabIndex        =   4
      Top             =   360
      Value           =   -1  'True
      Width           =   1095
   End
   Begin VB.CommandButton cmdStatus 
      Caption         =   "Status"
      Height          =   375
      Left            =   4800
      TabIndex        =   3
      Top             =   840
      Width           =   1215
   End
   Begin VB.ListBox lstRecv 
      Height          =   1230
      Left            =   6120
      TabIndex        =   0
      Top             =   360
      Width           =   4455
   End
   Begin VB.TextBox txtServer 
      Height          =   375
      Left            =   1320
      TabIndex        =   1
      Top             =   360
      Width           =   2775
   End
   Begin VB.TextBox txtPort 
      Height          =   375
      Left            =   4200
      TabIndex        =   2
      Top             =   360
      Width           =   1695
   End
   Begin MSWinsockLib.Winsock W1 
      Left            =   9240
      Top             =   720
      _ExtentX        =   741
      _ExtentY        =   741
      _Version        =   393216
   End
   Begin VB.Label Label6 
      Caption         =   "Protocol:"
      Height          =   255
      Left            =   120
      TabIndex        =   20
      Top             =   120
      Width           =   1095
   End
   Begin VB.Label Label5 
      Caption         =   "Messages:"
      Height          =   255
      Left            =   6120
      TabIndex        =   19
      Top             =   120
      Width           =   1095
   End
   Begin VB.Label Label4 
      Caption         =   "Data to Send:"
      Height          =   255
      Left            =   120
      TabIndex        =   18
      Top             =   1875
      Width           =   1455
   End
   Begin VB.Label Label3 
      Caption         =   "Data Received:"
      Height          =   255
      Left            =   6120
      TabIndex        =   17
      Top             =   1875
      Width           =   1575
   End
   Begin VB.Label Label2 
      Caption         =   "Port Number:"
      Height          =   255
      Left            =   4200
      TabIndex        =   16
      Top             =   120
      Width           =   1095
   End
   Begin VB.Label Label1 
      Caption         =   "Server Name:"
      Height          =   255
      Left            =   1320
      TabIndex        =   15
      Top             =   120
      Width           =   2055
   End
End
Attribute VB_Name = "frmWSock"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'********************************************************************************
'*
'*  WSock - VB 6 side of the CE winsock sample
'*
'*  Copyright (c) 1998 Microsoft Corporation

Option Explicit

Private Sub cmdBuildString_Click()
    txtSend = ""
    Dim m As String
    m = ""
    Dim N
    For N = 1 To Val(InputBox("How many K do you want to send?", "Data Amount to be Pumped Thru the Winsock"))
    m = m & String$(1024, "*") & vbCrLf
    Next
    txtSend.Text = m
    lstRecv.AddItem "Buffering " & Len(m) & " bytes of data. Hit Send to send."
End Sub

Private Sub cmdClear_Click()
    lstRecv.Clear
    txtRecv.Text = ""
End Sub

Private Sub cmdConnect_Click()

    'After attempting a connection of any kind, we set the caption of this button to "Disconnect"
    'Saves on screen real estate to have a multi-use button and prevents multiple connects
    
    If cmdConnect.Caption = "Disconnect" Then
        lstRecv.AddItem "Closing Connection"
        W1.Close
        W1.LocalPort = 0
        cmdListen.Enabled = True
        cmdConnect.Caption = "Connect to Server"
        Exit Sub ' Don't try to re-establish a connection--we just closed it!
    End If
    
    ' If we don't already have a connection, let's try to make a new one
    ' based on which protocol we're trying to use...
    
    ' If the protocol is TCP, then we set up a server listening for a request
    ' to connect to a particular port
    
    If optTCP Then
        W1.Protocol = 0
        W1.RemotePort = Val(txtPort.Text)
        W1.RemoteHost = txtServer.Text
        lstRecv.AddItem "Connecting to " & W1.RemoteHost & ":" & W1.RemotePort & ", State = " & GetState(W1)
        W1.Connect
        
        'modify UI to show we're
        cmdListen.Enabled = False
        cmdConnect.Caption = "Disconnect"
    
    'If the protocol is UDP, then we bind to a local port and listen to it
    'We also have to set a  remote port to talk to, so we do that in the connect button
    'NOTE: UDP is not an available option in the VBCE winsock control!
    'Because we only put one port box on the form, we must query the user for it
    
    ElseIf optUDP Then
        W1.Protocol = 1
        W1.RemotePort = Val(txtPort.Text)
        W1.RemoteHost = txtServer.Text
        lstRecv.AddItem "Connecting to " & W1.RemoteHost & ":" & W1.RemotePort
        cmdListen.Enabled = False
        W1.Bind Val(InputBox("What port do you want to bind to?", "UDP Local Port Options"))
        lstRecv.AddItem "Binding to Local Port: " & W1.LocalPort
        cmdConnect.Caption = "Disconnect"
        
    'IF the protocol is set to IRDA then we set it up to connect to a service
    'The information in the port box will be the service name
    'The regular VB5 winsock does not have this functionality
        
    ElseIf optIRDA Then
        W1.Protocol = 2
        'W1.ServiceName = txtPort.Text
        W1.Listen
        cmdListen.Enabled = False
        cmdConnect.Caption = "Disconnect"
        
    'Make sure we've covered all our bases
    'The VB5 winsock control gives an error 380 if we try to use a bogus protocol number
        
    Else
        MsgBox "Unknown Protocol Request"
    End If

End Sub

Private Sub cmdErr_Click()
    MsgBox Err.Description, vbExclamation, Err
End Sub

Private Sub cmdListen_Click()
    
    ' If the protocol is TCP, then we set up a server listening for a request
    ' to connect to a particular port
    
    If optTCP Then
        W1.Protocol = 0
        W1.LocalPort = Val(txtPort.Text)
        W1.Listen
        lstRecv.AddItem "Listening at Port " & W1.LocalPort & ", State = " & GetState(W1)
        cmdListen.Enabled = False
        cmdConnect.Caption = "Disconnect"
    
    'If the protocol is UDP, then we bind to a local port and listen to it
    'We also have to set a  remote port to talk to, so we do that in the connect button
    'NOTE: UDP is not an available option in the VBCE winsock control!
    'Because we only put one port box on the form, we must query the user for it
    
    ElseIf optUDP Then
        W1.Protocol = 1
        W1.Bind Val(txtPort.Text)
        lstRecv.AddItem "Binding to Local Port: " & W1.LocalPort
        cmdListen.Enabled = False
        cmdConnect.Caption = "Disconnect"
        W1.RemoteHost = txtServer.Text
        cmdListen.Enabled = False
        W1.RemotePort = Val(InputBox("What port do you want to connect to?" & vbCrLf & "You are bound to Local Port " & W1.LocalPort, "UDP Remote Port Options"))
        lstRecv.AddItem "Connecting to " & W1.RemoteHost & ":" & W1.RemotePort
        
        
    'IF the protocol is set to IRDA then we set it up to connect to a service
    'The information in the port box will be the service name
    'The regular VB5 winsock does not have this functionality
        
    ElseIf optIRDA Then
        W1.Protocol = 2
        'W1.ServiceName = txtPort.Text
        W1.Listen
        cmdListen.Enabled = False
        cmdConnect.Caption = "Disconnect"
        
    'Make sure we've covered all our bases
    'The VB5 winsock control gives an error 380 if we try to use a bogus protocol number
        
    Else
        MsgBox "Unknown Protocol Request"
    End If

End Sub

Private Sub cmdSend_Click()
    W1.SendData txtSend.Text
End Sub

Private Sub cmdStatus_Click()
    Dim m
    m = m & "BytesReceived= " & W1.BytesReceived & vbCrLf
    m = m & "LocalHostName= " & W1.LocalHostName & vbCrLf
    m = m & "LocalIP= " & W1.LocalIP & vbCrLf
    m = m & "LocalPort= " & W1.LocalPort & vbCrLf
    m = m & "Protocol= " & W1.Protocol & vbCrLf
    m = m & "RemoteHost= " & W1.RemoteHost & vbCrLf
    m = m & "RemoteHostIP= " & W1.RemoteHostIP & vbCrLf
    m = m & "RemotePort= " & W1.RemotePort & vbCrLf
    m = m & "SocketHandle= " & W1.SocketHandle & vbCrLf
    m = m & "State= " & GetState(W1) & vbCrLf
    MsgBox m, vbInformation, "Winsock Control Status"
End Sub

Private Sub Command1_Click()
    txtSend.Text = ""
End Sub

Private Sub Command2_Click()
    txtRecv.Text = ""
End Sub

Private Sub W1_Close()
    lstRecv.AddItem "Close Confirmed" & ", State = " & GetState(W1)
End Sub

Private Sub W1_Connect()
    lstRecv.AddItem "Connect Confirmed" & ", State = " & GetState(W1)
End Sub

'TCP Servers can receive a connection request while listening on a Socket
'The requestID is an encoded version of the requesting socket's IP and port (or so rumor has it)
'I don't know why the connection needs to be closed before it's accepted
'In theory, you can use W2 to accept the connection and keep listening on W1
'In theory, that is...

Private Sub W1_ConnectionRequest(ByVal requestID As Long)
    If W1.State <> 0 Then W1.Close
    lstRecv.AddItem "Connection Request (" & requestID & ")" & ", State = " & GetState(W1)
    W1.Accept requestID
    lstRecv.AddItem "Connection Accepted" & ", State = " & GetState(W1)
        
    End Sub

Private Sub W1_DataArrival(ByVal bytesTotal As Long)
    Dim sockdata As String, retstuff As String
    W1.GetData sockdata, vbString, bytesTotal
    txtRecv.Text = txtRecv.Text & sockdata
    lstRecv.AddItem bytesTotal & " bytes received"
End Sub

Private Sub W1_Error(ByVal Number As Integer, Description As String, ByVal Scode As Long, ByVal Source As String, ByVal HelpFile As String, ByVal HelpContext As Long, CancelDisplay As Boolean)
    lstRecv.AddItem "ERROR (" & Number & ") " & Description
End Sub

Function GetState(WS)
    Select Case WS.State
        Case 0
             GetState = "Closed (0)"
        Case 1
             GetState = "Open (1)"
        Case 2
             GetState = "Listening (2)"
        Case 3
             GetState = "Connection Pending (3)"
        Case 4
             GetState = "Resolving Host (4)"
        Case 5
             GetState = "Host Resolved (5)"
        Case 6
             GetState = "Connecting (6)"
        Case 7
             GetState = "Connected (7)"
        Case 8
             GetState = "Closing (8)"
        Case 9
             GetState = "Error (9)"
     End Select
End Function

Private Sub W1_SendComplete()
    lstRecv.AddItem "Send Complete"
End Sub

Private Sub W1_SendProgress(ByVal bytesSent As Long, ByVal bytesRemaining As Long)
    lstRecv.AddItem "Progress: " & bytesSent & " sent, " & bytesRemaining & " to go"
End Sub
