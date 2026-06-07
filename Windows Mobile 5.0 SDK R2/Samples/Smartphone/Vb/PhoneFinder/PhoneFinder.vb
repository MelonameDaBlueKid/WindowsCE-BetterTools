'
' Copyright (c) Microsoft Corporation.  All rights reserved.
'
'
' Use of this source code is subject to the terms of the Microsoft end-user
' license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
' If you did not accept the terms of the EULA, you are not authorized to use
' this source code. For a copy of the EULA, please see the LICENSE.RTF on your
' install media.
'
Imports Microsoft.WindowsMobile.PocketOutlook.MessageInterception
Imports Microsoft.WindowsMobile.Status

Public Class PhoneFinder
    Inherits System.Windows.Forms.Form
    Friend WithEvents MenuItem1 As System.Windows.Forms.MenuItem
    Friend WithEvents label As System.Windows.Forms.Label
    Friend WithEvents pinLabel As System.Windows.Forms.Label
    Friend WithEvents pin As System.Windows.Forms.TextBox
    Friend WithEvents enabledCheckBox As System.Windows.Forms.CheckBox
    Friend WithEvents MainMenu1 As System.Windows.Forms.MainMenu

#Region "PlaySound"
    Declare Function PlaySound Lib "coredll.dll" (ByVal pszSound As String, ByVal hMod As IntPtr, ByVal fdwSound As Integer) As Integer

    Const SND_SYNC As Integer = &H0
    Const SND_ASYNC As Integer = &H1
    Const SND_LOOP As Integer = &H8
    Const SND_FILENAME As Integer = &H20000
#End Region


    Const ruleName As String = "Microsoft.PhoneFinder" ' name of the MessageInterceptor rule we will use
    Const soundFile As String = "\Program Files\PhoneFinder\overhere.wav" ' sound to play when event raised
    Dim interceptor As MessageInterceptor

#Region " Windows Form Designer generated code "

    Public Sub New()
        MyBase.New()

        'This call is required by the Windows Form Designer.
        InitializeComponent()

        'Add any initialization after the InitializeComponent() call

    End Sub

    'Form overrides dispose to clean up the component list.
    Protected Overloads Overrides Sub Dispose(ByVal disposing As Boolean)
        MyBase.Dispose(disposing)
    End Sub

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    Private Sub InitializeComponent()
        Me.MainMenu1 = New System.Windows.Forms.MainMenu
        Me.MenuItem1 = New System.Windows.Forms.MenuItem
        Me.label = New System.Windows.Forms.Label
        Me.pinLabel = New System.Windows.Forms.Label
        Me.pin = New System.Windows.Forms.TextBox
        Me.enabledCheckBox = New System.Windows.Forms.CheckBox
        '
        'MainMenu1
        '
        Me.MainMenu1.MenuItems.Add(Me.MenuItem1)
        '
        'MenuItem1
        '
        Me.MenuItem1.Text = "Exit"
        '
        'label
        '
        Me.label.Location = New System.Drawing.Point(3, 11)
        Me.label.Size = New System.Drawing.Size(170, 22)
        Me.label.Text = "Phone Finder"
        Me.label.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'pinLabel
        '
        Me.pinLabel.Location = New System.Drawing.Point(0, 43)
        Me.pinLabel.Size = New System.Drawing.Size(152, 22)
        Me.pinLabel.Text = "Pin:"
        '
        'pin
        '
        Me.pin.Location = New System.Drawing.Point(3, 68)
        Me.pin.Size = New System.Drawing.Size(152, 24)
        Me.pin.Text = "1234"
        '
        'enabledCheckBox
        '
        Me.enabledCheckBox.Location = New System.Drawing.Point(3, 98)
        Me.enabledCheckBox.Size = New System.Drawing.Size(152, 22)
        Me.enabledCheckBox.Text = "Enabled"
        '
        'PhoneFinderForm
        '
        Me.ClientSize = New System.Drawing.Size(176, 180)
        Me.Controls.Add(Me.label)
        Me.Controls.Add(Me.pinLabel)
        Me.Controls.Add(Me.pin)
        Me.Controls.Add(Me.enabledCheckBox)
        Me.Menu = Me.MainMenu1
        Me.Text = "Phone Finder"

    End Sub
#End Region


    Private Sub MenuItem1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MenuItem1.Click

        If enabledCheckBox.Checked Then
            ' the user wants Phone Finder to be enabled, so let's enable it
            Try
                ' need to enable the MessageInterceptor

                interceptor = New MessageInterceptor(InterceptionAction.NotifyAndDelete)
                interceptor.MessageCondition = New MessageCondition()
                interceptor.MessageCondition.CaseSensitive = True
                interceptor.MessageCondition.ComparisonType = MessagePropertyComparisonType.Equal
                interceptor.MessageCondition.ComparisonValue = pin.Text
                interceptor.MessageCondition.Property = MessageProperty.Body
                interceptor.EnableApplicationLauncher(ruleName)
            Catch ex As Microsoft.WindowsMobile.PocketOutlook.PocketOutlookException
                MessageBox.Show(ex.Message)
            End Try
        Else
            ' Phone Finder is disabled, disable the event
            If Not interceptor Is Nothing Then
                interceptor.DisableApplicationLauncher()
            End If
        End If
        Close()
    End Sub

    Private Sub PhoneFinderForm_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        ' Test to see if Phone Finder is enabled
        If MessageInterceptor.IsApplicationLauncherEnabled(ruleName) Then
            ' we have already enabled Phone Finder

            ' load the event data into the MessageInterceptor and hook up our event
            interceptor = New MessageInterceptor(ruleName)
            AddHandler interceptor.MessageReceived, AddressOf interceptor_MessageReceived
            ' set the pin to the value the user set and show that Phone Finder is enabled
            pin.Text = interceptor.MessageCondition.ComparisonValue
            enabledCheckBox.Checked = True
        Else
            enabledCheckBox.Checked = False
        End If
    End Sub

    Private Sub interceptor_MessageReceived(ByVal sender As Object, ByVal e As Microsoft.WindowsMobile.PocketOutlook.MessageInterception.MessageInterceptorEventArgs)
        ' Play the sound in a loop
        PlaySound(soundFile, IntPtr.Zero, SND_FILENAME Or SND_ASYNC Or SND_LOOP)

        '/ While playing the sound, display owner information if we have it.

        ' get the owner name, otherwise default to "the owner"
        Dim owner As String = SystemState.OwnerName
        If owner.Length = 0 Then
            owner = "the owner"
        End If

        ' build the message to display on the phone
        Dim message As String = owner + " is looking for his/her phone.  "
        message += "If you have found this phone, please contact " + owner + ". "

        ' look to see if we have contact information for the owner.  
        ' if we do, then we'll display the ways the owner can be contacted.
        Dim email As String = SystemState.OwnerEmail
        Dim phone As String = SystemState.OwnerPhoneNumber

        If phone.Length > 0 And email.Length > 0 Then
            message += "You can contact " + owner + " via the following: \n"
        End If

        If phone.Length > 0 Then
            message += phone + "\n"
        End If

        If email.Length > 0 Then
            message += email + "\n"
        End If

        ' Show the message
        MessageBox.Show(message)

        ' The message box has been dismissed, stop the sound and exit
        PlaySound(Nothing, IntPtr.Zero, 0)
        Close()
    End Sub
End Class
