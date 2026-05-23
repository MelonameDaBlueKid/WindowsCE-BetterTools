VERSION 5.00
Object = "{CBF9C2B0-E8CB-11D0-AFAE-00600811D2B6}#1.0#0"; "Sketch.dll"
Begin VB.Form Form1 
   Caption         =   "Sketchomatic"
   ClientHeight    =   2820
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   7125
   LinkTopic       =   "Form1"
   ScaleHeight     =   2820
   ScaleWidth      =   7125
   Begin VB.CommandButton Command1 
      Caption         =   "Erase"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   18
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1695
      Left            =   5760
      TabIndex        =   3
      Top             =   0
      Width           =   1335
   End
   Begin VB.OptionButton Option3 
      Caption         =   "Thick"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   5760
      TabIndex        =   2
      Top             =   2520
      Width           =   1335
   End
   Begin VB.OptionButton Option2 
      Caption         =   "Medium"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   5760
      TabIndex        =   1
      Top             =   2160
      Width           =   1335
   End
   Begin VB.OptionButton Option1 
      Caption         =   "Thin"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   5760
      TabIndex        =   0
      Top             =   1800
      Width           =   1335
   End
   Begin SKETCHLibCtl.SketcCtl SketcCtl1 
      Height          =   2775
      Left            =   0
      OleObjectBlob   =   "Demo.frx":0000
      TabIndex        =   4
      Top             =   0
      Width           =   5655
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit


Private Sub Command1_Click()
SketcCtl1.Erase
End Sub

Private Sub Form_Load()

End Sub

Private Sub Option1_Click()
SketcCtl1.PenWidth = 1
End Sub

Private Sub Option2_Click()
SketcCtl1.PenWidth = 4
End Sub

Private Sub Option3_Click()
SketcCtl1.PenWidth = 6
End Sub

Private Sub SketcCtl1_GotFocus()

End Sub
