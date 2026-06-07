//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.
//
#region Using directives

using System;
using System.Drawing;
using System.Collections;
using System.Windows.Forms;
using System.Data;

using Microsoft.WindowsMobile.Status;
using Microsoft.WindowsMobile.PocketOutlook;

#endregion

namespace Microsoft.WindowsMobile.Samples.NotificationBrokerViewer
{
    /// <summary>
    /// Summary description for form.
    /// </summary>
    public class SnbViewer : System.Windows.Forms.Form
    {
        private TextBox txtDump;
        private TextBox txtChanges;
        private MenuItem menuQuit;
        private MenuItem menuItem2;
        private MenuItem menuValues;
        private MenuItem menuProperties;
        private Label label1;
        private Label label2;
        /// <summary>
        /// Main menu for the form.
        /// </summary>
        private System.Windows.Forms.MainMenu mainMenu1;

        public SnbViewer()
        {
            InitializeComponent();
        }

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        protected override void Dispose(bool disposing)
        {
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code
        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.mainMenu1 = new System.Windows.Forms.MainMenu();
            this.menuQuit = new System.Windows.Forms.MenuItem();
            this.menuItem2 = new System.Windows.Forms.MenuItem();
            this.menuValues = new System.Windows.Forms.MenuItem();
            this.menuProperties = new System.Windows.Forms.MenuItem();
            this.txtDump = new System.Windows.Forms.TextBox();
            this.txtChanges = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // mainMenu1
            // 
            this.mainMenu1.MenuItems.Add(this.menuQuit);
            this.mainMenu1.MenuItems.Add(this.menuItem2);
            // 
            // menuQuit
            // 
            this.menuQuit.Text = "Quit";
            this.menuQuit.Click += new System.EventHandler(this.menuQuit_Click);
            // 
            // menuItem2
            // 
            this.menuItem2.MenuItems.Add(this.menuValues);
            this.menuItem2.MenuItems.Add(this.menuProperties);
            this.menuItem2.Text = "Menu";
            // 
            // menuValues
            // 
            this.menuValues.Text = "Get States As Raw Values";
            this.menuValues.Click += new System.EventHandler(this.menuValues_Click);
            // 
            // menuProperties
            // 
            this.menuProperties.Text = "Get States As Properties";
            this.menuProperties.Click += new System.EventHandler(this.menuProperties_Click);
            // 
            // txtDump
            // 
            this.txtDump.Location = new System.Drawing.Point(0, 26);
            this.txtDump.Multiline = true;
            this.txtDump.Name = "txtDump";
            this.txtDump.ReadOnly = true;
            this.txtDump.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.txtDump.Size = new System.Drawing.Size(240, 157);
            this.txtDump.TabIndex = 0;
            // 
            // txtChanges
            // 
            this.txtChanges.Location = new System.Drawing.Point(0, 211);
            this.txtChanges.Multiline = true;
            this.txtChanges.Name = "txtChanges";
            this.txtChanges.ReadOnly = true;
            this.txtChanges.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.txtChanges.Size = new System.Drawing.Size(240, 57);
            this.txtChanges.TabIndex = 1;
            // 
            // label1
            // 
            this.label1.Location = new System.Drawing.Point(0, 4);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(176, 19);
            this.label1.Text = "States:  ";
            // 
            // label2
            // 
            this.label2.Location = new System.Drawing.Point(0, 186);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(152, 22);
            this.label2.Text = "Notifications:";
            // 
            // SnbViewer
            // 
            this.ClientSize = new System.Drawing.Size(240, 268);
            this.Controls.Add(this.txtChanges);
            this.Controls.Add(this.txtDump);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.label2);
            this.Menu = this.mainMenu1;
            this.Name = "SnbViewer";
            this.Text = "Notification Broker Viewer";
            this.Load += new System.EventHandler(this.SnbViewer_Load);
            this.ResumeLayout(false);

        }

        #endregion

        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        static void Main()
        {
            Application.Run(new SnbViewer());
        }



        private ArrayList stateList = new ArrayList();

        public void ChangeOccurred(object sender, ChangeEventArgs args)
        {
            SystemState state = (SystemState)sender;
            txtChanges.Text += state.Property.ToString() + " = " + ConvertToString(args.NewValue) + "\r\n";
        }

        private string ConvertToString(object o)
        {
            return (o == null) ? "<null>" : o.ToString();
        }

        public void ViewAllProperties()
        {
            txtDump.Text = "";
            txtDump.Text += " ActiveApplication" + " = " + ConvertToString(SystemState.ActiveApplication) + "\r\n";
            txtDump.Text += " DisplayRotation" + " = " + ConvertToString(SystemState.DisplayRotation) + "\r\n";
            txtDump.Text += " KeyboardPresent" + " = " + ConvertToString(SystemState.KeyboardPresent) + "\r\n";
            txtDump.Text += " CradlePresent" + " = " + ConvertToString(SystemState.CradlePresent) + "\r\n";
            txtDump.Text += " CameraPresent" + " = " + ConvertToString(SystemState.CameraPresent) + "\r\n";
            txtDump.Text += " MessagingSmsUnread" + " = " + ConvertToString(SystemState.MessagingSmsUnread) + "\r\n";
            txtDump.Text += " MessagingVoiceMailTotalUnread" + " = " + ConvertToString(SystemState.MessagingVoiceMailTotalUnread) + "\r\n";
            txtDump.Text += " MessagingVoiceMail1Unread" + " = " + ConvertToString(SystemState.MessagingVoiceMail1Unread) + "\r\n";
            txtDump.Text += " MessagingVoiceMail2Unread" + " = " + ConvertToString(SystemState.MessagingVoiceMail2Unread) + "\r\n";
            txtDump.Text += " MessagingActiveSyncEmailUnread" + " = " + ConvertToString(SystemState.MessagingActiveSyncEmailUnread) + "\r\n";
            txtDump.Text += " MessagingTotalEmailUnread" + " = " + ConvertToString(SystemState.MessagingTotalEmailUnread) + "\r\n";
            txtDump.Text += " MessagingOtherEmailUnread" + " = " + ConvertToString(SystemState.MessagingOtherEmailUnread) + "\r\n";
            txtDump.Text += " MessagingLastEmailAccountName" + " = " + ConvertToString(SystemState.MessagingLastEmailAccountName) + "\r\n";
            txtDump.Text += " MessagingSmsAccountName" + " = " + ConvertToString(SystemState.MessagingSmsAccountName) + "\r\n";
            txtDump.Text += " MessagingActiveSyncAccountName" + " = " + ConvertToString(SystemState.MessagingActiveSyncAccountName) + "\r\n";
            txtDump.Text += " TasksActive" + " = " + ConvertToString(SystemState.TasksActive) + "\r\n";
            txtDump.Text += " TasksHighPriority" + " = " + ConvertToString(SystemState.TasksHighPriority) + "\r\n";
            txtDump.Text += " TasksDueToday" + " = " + ConvertToString(SystemState.TasksDueToday) + "\r\n";
            txtDump.Text += " TasksOverdue" + " = " + ConvertToString(SystemState.TasksOverdue) + "\r\n";
            txtDump.Text += " CalendarNextAppointmentSubject" + " = " + ConvertToString(SystemState.CalendarNextAppointmentSubject) + "\r\n";
            txtDump.Text += " CalendarNextAppointmentLocation" + " = " + ConvertToString(SystemState.CalendarNextAppointmentLocation) + "\r\n";
            txtDump.Text += " CalendarNextAppointmentStart" + " = " + ConvertToString(SystemState.CalendarNextAppointmentStart) + "\r\n";
            txtDump.Text += " CalendarNextAppointmentEnd" + " = " + ConvertToString(SystemState.CalendarNextAppointmentEnd) + "\r\n";
            txtDump.Text += " MediaPlayerAlbumArtist" + " = " + ConvertToString(SystemState.MediaPlayerAlbumArtist) + "\r\n";
            txtDump.Text += " MediaPlayerTrackBitrate" + " = " + ConvertToString(SystemState.MediaPlayerTrackBitrate) + "\r\n";
            txtDump.Text += " MediaPlayerTrackTitle" + " = " + ConvertToString(SystemState.MediaPlayerTrackTitle) + "\r\n";
            txtDump.Text += " MediaPlayerAlbumTitle" + " = " + ConvertToString(SystemState.MediaPlayerAlbumTitle) + "\r\n";
            txtDump.Text += " MediaPlayerTrackArtist" + " = " + ConvertToString(SystemState.MediaPlayerTrackArtist) + "\r\n";
            txtDump.Text += " MediaPlayerTrackNumber" + " = " + ConvertToString(SystemState.MediaPlayerTrackNumber) + "\r\n";
            txtDump.Text += " MediaPlayerTrackGenre" + " = " + ConvertToString(SystemState.MediaPlayerTrackGenre) + "\r\n";
            txtDump.Text += " MediaPlayerTrackTimeElapsed" + " = " + ConvertToString(SystemState.MediaPlayerTrackTimeElapsed) + "\r\n";
            txtDump.Text += " PowerBatteryStrength" + " = " + ConvertToString(SystemState.PowerBatteryStrength) + "\r\n";
            txtDump.Text += " PowerBatteryState" + " = " + ConvertToString(SystemState.PowerBatteryState) + "\r\n";
            txtDump.Text += " PowerBatteryBackupStrength" + " = " + ConvertToString(SystemState.PowerBatteryBackupStrength) + "\r\n";
            txtDump.Text += " PowerBatteryBackupState" + " = " + ConvertToString(SystemState.PowerBatteryBackupState) + "\r\n";
            txtDump.Text += " Time" + " = " + ConvertToString(SystemState.Time) + "\r\n";
            txtDump.Text += " Date" + " = " + ConvertToString(SystemState.Date) + "\r\n";
            txtDump.Text += " PhoneSignalStrength" + " = " + ConvertToString(SystemState.PhoneSignalStrength) + "\r\n";
            txtDump.Text += " PhoneOperatorName" + " = " + ConvertToString(SystemState.PhoneOperatorName) + "\r\n";
            txtDump.Text += " PhoneTalkingCallerName" + " = " + ConvertToString(SystemState.PhoneTalkingCallerName) + "\r\n";
            txtDump.Text += " PhoneActiveCallCount" + " = " + ConvertToString(SystemState.PhoneActiveCallCount) + "\r\n";
            txtDump.Text += " PhoneProfileName" + " = " + ConvertToString(SystemState.PhoneProfileName) + "\r\n";
            txtDump.Text += " PhoneProfile" + " = " + ConvertToString(SystemState.PhoneProfile) + "\r\n";
            txtDump.Text += " PhoneCellBroadcast" + " = " + ConvertToString(SystemState.PhoneCellBroadcast) + "\r\n";
            txtDump.Text += " CalendarNextAppointmentHasConflict" + " = " + ConvertToString(SystemState.CalendarNextAppointmentHasConflict) + "\r\n";
            txtDump.Text += " OwnerName" + " = " + ConvertToString(SystemState.OwnerName) + "\r\n";
            txtDump.Text += " OwnerPhoneNumber" + " = " + ConvertToString(SystemState.OwnerPhoneNumber) + "\r\n";
            txtDump.Text += " OwnerEmail" + " = " + ConvertToString(SystemState.OwnerEmail) + "\r\n";
            txtDump.Text += " OwnerNotes" + " = " + ConvertToString(SystemState.OwnerNotes) + "\r\n";
            txtDump.Text += " ActiveSyncStatus" + " = " + ConvertToString(SystemState.ActiveSyncStatus) + "\r\n";
            txtDump.Text += " PhoneMissedCalls" + " = " + ConvertToString(SystemState.PhoneMissedCalls) + "\r\n";
            txtDump.Text += " HeadsetPresent" + " = " + ConvertToString(SystemState.HeadsetPresent) + "\r\n";
            txtDump.Text += " CarKitPresent" + " = " + ConvertToString(SystemState.CarKitPresent) + "\r\n";
            txtDump.Text += " SpeakerPhoneActive" + " = " + ConvertToString(SystemState.SpeakerPhoneActive) + "\r\n";
            txtDump.Text += " PhoneMultiLine" + " = " + ConvertToString(SystemState.PhoneMultiLine) + "\r\n";
            txtDump.Text += " PhoneSimFull" + " = " + ConvertToString(SystemState.PhoneSimFull) + "\r\n";
            txtDump.Text += " PhoneNoSim" + " = " + ConvertToString(SystemState.PhoneNoSim) + "\r\n";
            txtDump.Text += " PhoneInvalidSim" + " = " + ConvertToString(SystemState.PhoneInvalidSim) + "\r\n";
            txtDump.Text += " PhoneBlockedSim" + " = " + ConvertToString(SystemState.PhoneBlockedSim) + "\r\n";
            txtDump.Text += " PhoneRadioOff" + " = " + ConvertToString(SystemState.PhoneRadioOff) + "\r\n";
            txtDump.Text += " PhoneRadioPresent" + " = " + ConvertToString(SystemState.PhoneRadioPresent) + "\r\n";
            txtDump.Text += " PhoneRingerOff" + " = " + ConvertToString(SystemState.PhoneRingerOff) + "\r\n";
            txtDump.Text += " PhoneLine1Selected" + " = " + ConvertToString(SystemState.PhoneLine1Selected) + "\r\n";
            txtDump.Text += " PhoneLine2Selected" + " = " + ConvertToString(SystemState.PhoneLine2Selected) + "\r\n";
            txtDump.Text += " PhoneRoaming" + " = " + ConvertToString(SystemState.PhoneRoaming) + "\r\n";
            txtDump.Text += " PhoneCallForwardingOnLine1" + " = " + ConvertToString(SystemState.PhoneCallForwardingOnLine1) + "\r\n";
            txtDump.Text += " PhoneMissedCall" + " = " + ConvertToString(SystemState.PhoneMissedCall) + "\r\n";
            txtDump.Text += " PhoneActiveDataCall" + " = " + ConvertToString(SystemState.PhoneActiveDataCall) + "\r\n";
            txtDump.Text += " PhoneCallBarring" + " = " + ConvertToString(SystemState.PhoneCallBarring) + "\r\n";
            txtDump.Text += " PhoneCallOnHold" + " = " + ConvertToString(SystemState.PhoneCallOnHold) + "\r\n";
            txtDump.Text += " PhoneConferenceCall" + " = " + ConvertToString(SystemState.PhoneConferenceCall) + "\r\n";
            txtDump.Text += " PhoneIncomingCall" + " = " + ConvertToString(SystemState.PhoneIncomingCall) + "\r\n";
            txtDump.Text += " PhoneCallCalling" + " = " + ConvertToString(SystemState.PhoneCallCalling) + "\r\n";
            txtDump.Text += " PhoneGprsCoverage" + " = " + ConvertToString(SystemState.PhoneGprsCoverage) + "\r\n";
            txtDump.Text += " PhoneNoService" + " = " + ConvertToString(SystemState.PhoneNoService) + "\r\n";
            txtDump.Text += " PhoneSearchingForService" + " = " + ConvertToString(SystemState.PhoneSearchingForService) + "\r\n";
            txtDump.Text += " PhoneHomeService" + " = " + ConvertToString(SystemState.PhoneHomeService) + "\r\n";
            txtDump.Text += " Phone1xRttCoverage" + " = " + ConvertToString(SystemState.Phone1xRttCoverage) + "\r\n";
            txtDump.Text += " PhoneCallTalking" + " = " + ConvertToString(SystemState.PhoneCallTalking) + "\r\n";
            txtDump.Text += " PhoneCallForwardingOnLine2" + " = " + ConvertToString(SystemState.PhoneCallForwardingOnLine2) + "\r\n";
            txtDump.Text += " CalendarNextAppointment" + " = " + ConvertToString(SystemState.CalendarNextAppointment) + "\r\n";
            txtDump.Text += " CalendarNextAppointmentBusyStatus" + " = " + ConvertToString(SystemState.CalendarNextAppointmentBusyStatus) + "\r\n";
            txtDump.Text += " CalendarNextAppointmentCategories" + " = " + ConvertToString(SystemState.CalendarNextAppointmentCategories) + "\r\n";
            txtDump.Text += " CalendarAppointment" + " = " + ConvertToString(SystemState.CalendarAppointment) + "\r\n";
            txtDump.Text += " CalendarAppointmentSubject" + " = " + ConvertToString(SystemState.CalendarAppointmentSubject) + "\r\n";
            txtDump.Text += " CalendarAppointmentLocation" + " = " + ConvertToString(SystemState.CalendarAppointmentLocation) + "\r\n";
            txtDump.Text += " CalendarAppointmentStartTime" + " = " + ConvertToString(SystemState.CalendarAppointmentStartTime) + "\r\n";
            txtDump.Text += " CalendarAppointmentEndTime" + " = " + ConvertToString(SystemState.CalendarAppointmentEndTime) + "\r\n";
            txtDump.Text += " CalendarAppointmentHasConflict" + " = " + ConvertToString(SystemState.CalendarAppointmentHasConflict) + "\r\n";
            txtDump.Text += " CalendarAppointmentBusyStatus" + " = " + ConvertToString(SystemState.CalendarAppointmentBusyStatus) + "\r\n";
            txtDump.Text += " CalendarAppointmentCategories" + " = " + ConvertToString(SystemState.CalendarAppointmentCategories) + "\r\n";
            txtDump.Text += " CalendarHomeScreenAppointment" + " = " + ConvertToString(SystemState.CalendarHomeScreenAppointment) + "\r\n";
            txtDump.Text += " CalendarHomeScreenAppointmentSubject" + " = " + ConvertToString(SystemState.CalendarHomeScreenAppointmentSubject) + "\r\n";
            txtDump.Text += " CalendarHomeScreenAppointmentLocation" + " = " + ConvertToString(SystemState.CalendarHomeScreenAppointmentLocation) + "\r\n";
            txtDump.Text += " CalendarHomeScreenAppointmentStartTime" + " = " + ConvertToString(SystemState.CalendarHomeScreenAppointmentStartTime) + "\r\n";
            txtDump.Text += " CalendarHomeScreenAppointmentEndTime" + " = " + ConvertToString(SystemState.CalendarHomeScreenAppointmentEndTime) + "\r\n";
            txtDump.Text += " CalendarHomeScreenAppointmentHasConflict" + " = " + ConvertToString(SystemState.CalendarHomeScreenAppointmentHasConflict) + "\r\n";
            txtDump.Text += " CalendarHomeScreenAppointmentBusyStatus" + " = " + ConvertToString(SystemState.CalendarHomeScreenAppointmentBusyStatus) + "\r\n";
            txtDump.Text += " CalendarHomeScreenAppointmentCategories" + " = " + ConvertToString(SystemState.CalendarHomeScreenAppointmentCategories) + "\r\n";
            txtDump.Text += " PhoneIncomingCallerName" + " = " + ConvertToString(SystemState.PhoneIncomingCallerName) + "\r\n";
            txtDump.Text += " PhoneLastIncomingCallerName" + " = " + ConvertToString(SystemState.PhoneLastIncomingCallerName) + "\r\n";
            txtDump.Text += " PhoneIncomingCallerNumber" + " = " + ConvertToString(SystemState.PhoneIncomingCallerNumber) + "\r\n";
            txtDump.Text += " PhoneLastIncomingCallerNumber" + " = " + ConvertToString(SystemState.PhoneLastIncomingCallerNumber) + "\r\n";
            txtDump.Text += " PhoneIncomingCallerContactPropertyName" + " = " + ConvertToString(SystemState.PhoneIncomingCallerContactPropertyName) + "\r\n";
            txtDump.Text += " PhoneLastIncomingCallerContactPropertyName" + " = " + ConvertToString(SystemState.PhoneLastIncomingCallerContactPropertyName) + "\r\n";
            txtDump.Text += " PhoneIncomingCallerContactPropertyID" + " = " + ConvertToString(SystemState.PhoneIncomingCallerContactPropertyID) + "\r\n";
            txtDump.Text += " PhoneLastIncomingCallerContactPropertyID" + " = " + ConvertToString(SystemState.PhoneLastIncomingCallerContactPropertyID) + "\r\n";
            txtDump.Text += " PhoneIncomingCallerContact" + " = " + ConvertToString(SystemState.PhoneIncomingCallerContact) + "\r\n";
            txtDump.Text += " PhoneLastIncomingCallerContact" + " = " + ConvertToString(SystemState.PhoneLastIncomingCallerContact) + "\r\n";
            txtDump.Text += " PhoneTalkingCallerNumber" + " = " + ConvertToString(SystemState.PhoneTalkingCallerNumber) + "\r\n";
            txtDump.Text += " PhoneTalkingCallerContactPropertyName" + " = " + ConvertToString(SystemState.PhoneTalkingCallerContactPropertyName) + "\r\n";
            txtDump.Text += " PhoneTalkingCallerContactPropertyID" + " = " + ConvertToString(SystemState.PhoneTalkingCallerContactPropertyID) + "\r\n";
            txtDump.Text += " PhoneTalkingCallerContact" + " = " + ConvertToString(SystemState.PhoneTalkingCallerContact) + "\r\n";
            txtDump.Text += " ConnectionsCount" + " = " + ConvertToString(SystemState.ConnectionsCount) + "\r\n";
            txtDump.Text += " ConnectionsBluetoothCount" + " = " + ConvertToString(SystemState.ConnectionsBluetoothCount) + "\r\n";
            txtDump.Text += " ConnectionsBluetoothDescriptions" + " = " + ConvertToString(SystemState.ConnectionsBluetoothDescriptions) + "\r\n";
            txtDump.Text += " ConnectionsCellularCount" + " = " + ConvertToString(SystemState.ConnectionsCellularCount) + "\r\n";
            txtDump.Text += " ConnectionsCellularDescriptions" + " = " + ConvertToString(SystemState.ConnectionsCellularDescriptions) + "\r\n";
            txtDump.Text += " ConnectionsNetworkCount" + " = " + ConvertToString(SystemState.ConnectionsNetworkCount) + "\r\n";
            txtDump.Text += " ConnectionsNetworkDescriptions" + " = " + ConvertToString(SystemState.ConnectionsNetworkDescriptions) + "\r\n";
            txtDump.Text += " ConnectionsNetworkAdapters" + " = " + ConvertToString(SystemState.ConnectionsNetworkAdapters) + "\r\n";
            txtDump.Text += " ConnectionsDesktopCount" + " = " + ConvertToString(SystemState.ConnectionsDesktopCount) + "\r\n";
            txtDump.Text += " ConnectionsDesktopDescriptions" + " = " + ConvertToString(SystemState.ConnectionsDesktopDescriptions) + "\r\n";
            txtDump.Text += " ConnectionsProxyCount" + " = " + ConvertToString(SystemState.ConnectionsProxyCount) + "\r\n";
            txtDump.Text += " ConnectionsProxyDescriptions" + " = " + ConvertToString(SystemState.ConnectionsProxyDescriptions) + "\r\n";
            txtDump.Text += " ConnectionsModemCount" + " = " + ConvertToString(SystemState.ConnectionsModemCount) + "\r\n";
            txtDump.Text += " ConnectionsModemDescriptions" + " = " + ConvertToString(SystemState.ConnectionsModemDescriptions) + "\r\n";
            txtDump.Text += " ConnectionsUnknownCount" + " = " + ConvertToString(SystemState.ConnectionsUnknownCount) + "\r\n";
            txtDump.Text += " ConnectionsUnknownDescriptions" + " = " + ConvertToString(SystemState.ConnectionsUnknownDescriptions) + "\r\n";
            txtDump.Text += " ConnectionsVpnCount" + " = " + ConvertToString(SystemState.ConnectionsVpnCount) + "\r\n";
            txtDump.Text += " ConnectionsVpnDescriptions" + " = " + ConvertToString(SystemState.ConnectionsVpnDescriptions) + "\r\n";
            txtDump.Text += " CalendarEvent" + " = " + ConvertToString(SystemState.CalendarEvent) + "\r\n";
            txtDump.Text += " CalendarEventSubject" + " = " + ConvertToString(SystemState.CalendarEventSubject) + "\r\n";
            txtDump.Text += " CalendarEventLocation" + " = " + ConvertToString(SystemState.CalendarEventLocation) + "\r\n";
            txtDump.Text += " CalendarEventStartTime" + " = " + ConvertToString(SystemState.CalendarEventStartTime) + "\r\n";
            txtDump.Text += " CalendarEventEndTime" + " = " + ConvertToString(SystemState.CalendarEventEndTime) + "\r\n";
            txtDump.Text += " CalendarEventHasConflict" + " = " + ConvertToString(SystemState.CalendarEventHasConflict) + "\r\n";
            txtDump.Text += " CalendarEventBusyStatus" + " = " + ConvertToString(SystemState.CalendarEventBusyStatus) + "\r\n";
            txtDump.Text += " CalendarEventCategories" + " = " + ConvertToString(SystemState.CalendarEventCategories) + "\r\n";

        }

        public void ViewAllRawValues()
        {
            txtDump.Text = "";
            txtDump.Text += " ActiveApplication" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.ActiveApplication)) + "\r\n";
            txtDump.Text += " DisplayRotation" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.DisplayRotation)) + "\r\n";
            txtDump.Text += " KeyboardPresent" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.KeyboardPresent)) + "\r\n";
            txtDump.Text += " CradlePresent" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.CradlePresent)) + "\r\n";
            txtDump.Text += " CameraPresent" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.CameraPresent)) + "\r\n";
            txtDump.Text += " MessagingSmsUnread" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.MessagingSmsUnread)) + "\r\n";
            txtDump.Text += " MessagingVoiceMailTotalUnread" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.MessagingVoiceMailTotalUnread)) + "\r\n";
            txtDump.Text += " MessagingVoiceMail1Unread" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.MessagingVoiceMail1Unread)) + "\r\n";
            txtDump.Text += " MessagingVoiceMail2Unread" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.MessagingVoiceMail2Unread)) + "\r\n";
            txtDump.Text += " MessagingActiveSyncEmailUnread" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.MessagingActiveSyncEmailUnread)) + "\r\n";
            txtDump.Text += " MessagingTotalEmailUnread" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.MessagingTotalEmailUnread)) + "\r\n";
            txtDump.Text += " MessagingOtherEmailUnread" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.MessagingOtherEmailUnread)) + "\r\n";
            txtDump.Text += " MessagingLastEmailAccountName" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.MessagingLastEmailAccountName)) + "\r\n";
            txtDump.Text += " MessagingSmsAccountName" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.MessagingSmsAccountName)) + "\r\n";
            txtDump.Text += " MessagingActiveSyncAccountName" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.MessagingActiveSyncAccountName)) + "\r\n";
            txtDump.Text += " TasksActive" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.TasksActive)) + "\r\n";
            txtDump.Text += " TasksHighPriority" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.TasksHighPriority)) + "\r\n";
            txtDump.Text += " TasksDueToday" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.TasksDueToday)) + "\r\n";
            txtDump.Text += " TasksOverdue" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.TasksOverdue)) + "\r\n";
            txtDump.Text += " CalendarNextAppointmentSubject" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.CalendarNextAppointmentSubject)) + "\r\n";
            txtDump.Text += " CalendarNextAppointmentLocation" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.CalendarNextAppointmentLocation)) + "\r\n";
            txtDump.Text += " CalendarNextAppointmentStart" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.CalendarNextAppointmentStart)) + "\r\n";
            txtDump.Text += " CalendarNextAppointmentEnd" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.CalendarNextAppointmentEnd)) + "\r\n";
            txtDump.Text += " MediaPlayerAlbumArtist" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.MediaPlayerAlbumArtist)) + "\r\n";
            txtDump.Text += " MediaPlayerTrackBitrate" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.MediaPlayerTrackBitrate)) + "\r\n";
            txtDump.Text += " MediaPlayerTrackTitle" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.MediaPlayerTrackTitle)) + "\r\n";
            txtDump.Text += " MediaPlayerAlbumTitle" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.MediaPlayerAlbumTitle)) + "\r\n";
            txtDump.Text += " MediaPlayerTrackArtist" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.MediaPlayerTrackArtist)) + "\r\n";
            txtDump.Text += " MediaPlayerTrackNumber" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.MediaPlayerTrackNumber)) + "\r\n";
            txtDump.Text += " MediaPlayerTrackGenre" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.MediaPlayerTrackGenre)) + "\r\n";
            txtDump.Text += " MediaPlayerTrackTimeElapsed" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.MediaPlayerTrackTimeElapsed)) + "\r\n";
            txtDump.Text += " PowerBatteryStrength" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.PowerBatteryStrength)) + "\r\n";
            txtDump.Text += " PowerBatteryState" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.PowerBatteryState)) + "\r\n";
            txtDump.Text += " PowerBatteryBackupStrength" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.PowerBatteryBackupStrength)) + "\r\n";
            txtDump.Text += " PowerBatteryBackupState" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.PowerBatteryBackupState)) + "\r\n";
            txtDump.Text += " Time" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.Time)) + "\r\n";
            txtDump.Text += " Date" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.Date)) + "\r\n";
            txtDump.Text += " PhoneSignalStrength" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.PhoneSignalStrength)) + "\r\n";
            txtDump.Text += " PhoneOperatorName" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.PhoneOperatorName)) + "\r\n";
            txtDump.Text += " PhoneTalkingCallerName" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.PhoneTalkingCallerName)) + "\r\n";
            txtDump.Text += " PhoneActiveCallCount" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.PhoneActiveCallCount)) + "\r\n";
            txtDump.Text += " PhoneProfileName" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.PhoneProfileName)) + "\r\n";
            txtDump.Text += " PhoneProfile" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.PhoneProfile)) + "\r\n";
            txtDump.Text += " PhoneCellBroadcast" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.PhoneCellBroadcast)) + "\r\n";
            txtDump.Text += " CalendarNextAppointmentHasConflict" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.CalendarNextAppointmentHasConflict)) + "\r\n";
            txtDump.Text += " OwnerName" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.OwnerName)) + "\r\n";
            txtDump.Text += " OwnerPhoneNumber" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.OwnerPhoneNumber)) + "\r\n";
            txtDump.Text += " OwnerEmail" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.OwnerEmail)) + "\r\n";
            txtDump.Text += " OwnerNotes" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.OwnerNotes)) + "\r\n";
            txtDump.Text += " ActiveSyncStatus" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.ActiveSyncStatus)) + "\r\n";
            txtDump.Text += " PhoneMissedCalls" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.PhoneMissedCalls)) + "\r\n";
            txtDump.Text += " HeadsetPresent" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.HeadsetPresent)) + "\r\n";
            txtDump.Text += " CarKitPresent" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.CarKitPresent)) + "\r\n";
            txtDump.Text += " SpeakerPhoneActive" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.SpeakerPhoneActive)) + "\r\n";
            txtDump.Text += " PhoneMultiLine" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.PhoneMultiLine)) + "\r\n";
            txtDump.Text += " PhoneSimFull" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.PhoneSimFull)) + "\r\n";
            txtDump.Text += " PhoneNoSim" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.PhoneNoSim)) + "\r\n";
            txtDump.Text += " PhoneInvalidSim" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.PhoneInvalidSim)) + "\r\n";
            txtDump.Text += " PhoneBlockedSim" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.PhoneBlockedSim)) + "\r\n";
            txtDump.Text += " PhoneRadioOff" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.PhoneRadioOff)) + "\r\n";
            txtDump.Text += " PhoneRadioPresent" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.PhoneRadioPresent)) + "\r\n";
            txtDump.Text += " PhoneRingerOff" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.PhoneRingerOff)) + "\r\n";
            txtDump.Text += " PhoneLine1Selected" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.PhoneLine1Selected)) + "\r\n";
            txtDump.Text += " PhoneLine2Selected" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.PhoneLine2Selected)) + "\r\n";
            txtDump.Text += " PhoneRoaming" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.PhoneRoaming)) + "\r\n";
            txtDump.Text += " PhoneCallForwardingOnLine1" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.PhoneCallForwardingOnLine1)) + "\r\n";
            txtDump.Text += " PhoneMissedCall" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.PhoneMissedCall)) + "\r\n";
            txtDump.Text += " PhoneActiveDataCall" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.PhoneActiveDataCall)) + "\r\n";
            txtDump.Text += " PhoneCallBarring" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.PhoneCallBarring)) + "\r\n";
            txtDump.Text += " PhoneCallOnHold" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.PhoneCallOnHold)) + "\r\n";
            txtDump.Text += " PhoneConferenceCall" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.PhoneConferenceCall)) + "\r\n";
            txtDump.Text += " PhoneIncomingCall" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.PhoneIncomingCall)) + "\r\n";
            txtDump.Text += " PhoneCallCalling" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.PhoneCallCalling)) + "\r\n";
            txtDump.Text += " PhoneGprsCoverage" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.PhoneGprsCoverage)) + "\r\n";
            txtDump.Text += " PhoneNoService" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.PhoneNoService)) + "\r\n";
            txtDump.Text += " PhoneSearchingForService" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.PhoneSearchingForService)) + "\r\n";
            txtDump.Text += " PhoneHomeService" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.PhoneHomeService)) + "\r\n";
            txtDump.Text += " Phone1xRttCoverage" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.Phone1xRttCoverage)) + "\r\n";
            txtDump.Text += " PhoneCallTalking" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.PhoneCallTalking)) + "\r\n";
            txtDump.Text += " PhoneCallForwardingOnLine2" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.PhoneCallForwardingOnLine2)) + "\r\n";
            txtDump.Text += " CalendarNextAppointment" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.CalendarNextAppointment)) + "\r\n";
            txtDump.Text += " CalendarNextAppointmentBusyStatus" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.CalendarNextAppointmentBusyStatus)) + "\r\n";
            txtDump.Text += " CalendarNextAppointmentCategories" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.CalendarNextAppointmentCategories)) + "\r\n";
            txtDump.Text += " CalendarAppointment" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.CalendarAppointment)) + "\r\n";
            txtDump.Text += " CalendarAppointmentSubject" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.CalendarAppointmentSubject)) + "\r\n";
            txtDump.Text += " CalendarAppointmentLocation" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.CalendarAppointmentLocation)) + "\r\n";
            txtDump.Text += " CalendarAppointmentStartTime" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.CalendarAppointmentStartTime)) + "\r\n";
            txtDump.Text += " CalendarAppointmentEndTime" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.CalendarAppointmentEndTime)) + "\r\n";
            txtDump.Text += " CalendarAppointmentHasConflict" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.CalendarAppointmentHasConflict)) + "\r\n";
            txtDump.Text += " CalendarAppointmentBusyStatus" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.CalendarAppointmentBusyStatus)) + "\r\n";
            txtDump.Text += " CalendarAppointmentCategories" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.CalendarAppointmentCategories)) + "\r\n";
            txtDump.Text += " CalendarHomeScreenAppointment" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.CalendarHomeScreenAppointment)) + "\r\n";
            txtDump.Text += " CalendarHomeScreenAppointmentSubject" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.CalendarHomeScreenAppointmentSubject)) + "\r\n";
            txtDump.Text += " CalendarHomeScreenAppointmentLocation" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.CalendarHomeScreenAppointmentLocation)) + "\r\n";
            txtDump.Text += " CalendarHomeScreenAppointmentStartTime" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.CalendarHomeScreenAppointmentStartTime)) + "\r\n";
            txtDump.Text += " CalendarHomeScreenAppointmentEndTime" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.CalendarHomeScreenAppointmentEndTime)) + "\r\n";
            txtDump.Text += " CalendarHomeScreenAppointmentHasConflict" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.CalendarHomeScreenAppointmentHasConflict)) + "\r\n";
            txtDump.Text += " CalendarHomeScreenAppointmentBusyStatus" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.CalendarHomeScreenAppointmentBusyStatus)) + "\r\n";
            txtDump.Text += " CalendarHomeScreenAppointmentCategories" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.CalendarHomeScreenAppointmentCategories)) + "\r\n";
            txtDump.Text += " PhoneIncomingCallerName" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.PhoneIncomingCallerName)) + "\r\n";
            txtDump.Text += " PhoneLastIncomingCallerName" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.PhoneLastIncomingCallerName)) + "\r\n";
            txtDump.Text += " PhoneIncomingCallerNumber" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.PhoneIncomingCallerNumber)) + "\r\n";
            txtDump.Text += " PhoneLastIncomingCallerNumber" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.PhoneLastIncomingCallerNumber)) + "\r\n";
            txtDump.Text += " PhoneIncomingCallerContactPropertyName" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.PhoneIncomingCallerContactPropertyName)) + "\r\n";
            txtDump.Text += " PhoneLastIncomingCallerContactPropertyName" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.PhoneLastIncomingCallerContactPropertyName)) + "\r\n";
            txtDump.Text += " PhoneIncomingCallerContactPropertyID" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.PhoneIncomingCallerContactPropertyID)) + "\r\n";
            txtDump.Text += " PhoneLastIncomingCallerContactPropertyID" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.PhoneLastIncomingCallerContactPropertyID)) + "\r\n";
            txtDump.Text += " PhoneIncomingCallerContact" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.PhoneIncomingCallerContact)) + "\r\n";
            txtDump.Text += " PhoneLastIncomingCallerContact" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.PhoneLastIncomingCallerContact)) + "\r\n";
            txtDump.Text += " PhoneTalkingCallerNumber" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.PhoneTalkingCallerNumber)) + "\r\n";
            txtDump.Text += " PhoneTalkingCallerContactPropertyName" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.PhoneTalkingCallerContactPropertyName)) + "\r\n";
            txtDump.Text += " PhoneTalkingCallerContactPropertyID" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.PhoneTalkingCallerContactPropertyID)) + "\r\n";
            txtDump.Text += " PhoneTalkingCallerContact" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.PhoneTalkingCallerContact)) + "\r\n";
            txtDump.Text += " ConnectionsCount" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.ConnectionsCount)) + "\r\n";
            txtDump.Text += " ConnectionsBluetoothCount" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.ConnectionsBluetoothCount)) + "\r\n";
            txtDump.Text += " ConnectionsBluetoothDescriptions" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.ConnectionsBluetoothDescriptions)) + "\r\n";
            txtDump.Text += " ConnectionsCellularCount" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.ConnectionsCellularCount)) + "\r\n";
            txtDump.Text += " ConnectionsCellularDescriptions" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.ConnectionsCellularDescriptions)) + "\r\n";
            txtDump.Text += " ConnectionsNetworkCount" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.ConnectionsNetworkCount)) + "\r\n";
            txtDump.Text += " ConnectionsNetworkDescriptions" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.ConnectionsNetworkDescriptions)) + "\r\n";
            txtDump.Text += " ConnectionsNetworkAdapters" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.ConnectionsNetworkAdapters)) + "\r\n";
            txtDump.Text += " ConnectionsDesktopCount" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.ConnectionsDesktopCount)) + "\r\n";
            txtDump.Text += " ConnectionsDesktopDescriptions" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.ConnectionsDesktopDescriptions)) + "\r\n";
            txtDump.Text += " ConnectionsProxyCount" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.ConnectionsProxyCount)) + "\r\n";
            txtDump.Text += " ConnectionsProxyDescriptions" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.ConnectionsProxyDescriptions)) + "\r\n";
            txtDump.Text += " ConnectionsModemCount" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.ConnectionsModemCount)) + "\r\n";
            txtDump.Text += " ConnectionsModemDescriptions" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.ConnectionsModemDescriptions)) + "\r\n";
            txtDump.Text += " ConnectionsUnknownCount" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.ConnectionsUnknownCount)) + "\r\n";
            txtDump.Text += " ConnectionsUnknownDescriptions" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.ConnectionsUnknownDescriptions)) + "\r\n";
            txtDump.Text += " ConnectionsVpnCount" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.ConnectionsVpnCount)) + "\r\n";
            txtDump.Text += " ConnectionsVpnDescriptions" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.ConnectionsVpnDescriptions)) + "\r\n";
            txtDump.Text += " CalendarEvent" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.CalendarEvent)) + "\r\n";
            txtDump.Text += " CalendarEventSubject" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.CalendarEventSubject)) + "\r\n";
            txtDump.Text += " CalendarEventLocation" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.CalendarEventLocation)) + "\r\n";
            txtDump.Text += " CalendarEventStartTime" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.CalendarEventStartTime)) + "\r\n";
            txtDump.Text += " CalendarEventEndTime" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.CalendarEventEndTime)) + "\r\n";
            txtDump.Text += " CalendarEventHasConflict" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.CalendarEventHasConflict)) + "\r\n";
            txtDump.Text += " CalendarEventBusyStatus" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.CalendarEventBusyStatus)) + "\r\n";
            txtDump.Text += " CalendarEventCategories" + " = " + ConvertToString(SystemState.GetValue(SystemProperty.CalendarEventCategories)) + "\r\n";

        }



        public void SetUpNotifications()
        {
            SystemState s;
            s = new SystemState(SystemProperty.ActiveApplication);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.DisplayRotation);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.KeyboardPresent);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.CradlePresent);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.CameraPresent);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.MessagingSmsUnread);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.MessagingVoiceMailTotalUnread);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.MessagingVoiceMail1Unread);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.MessagingVoiceMail2Unread);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.MessagingActiveSyncEmailUnread);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.MessagingTotalEmailUnread);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.MessagingOtherEmailUnread);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.MessagingLastEmailAccountName);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.MessagingSmsAccountName);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.MessagingActiveSyncAccountName);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.TasksActive);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.TasksHighPriority);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.TasksDueToday);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.TasksOverdue);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.CalendarNextAppointmentSubject);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.CalendarNextAppointmentLocation);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.CalendarNextAppointmentStart);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.CalendarNextAppointmentEnd);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.MediaPlayerAlbumArtist);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.MediaPlayerTrackBitrate);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.MediaPlayerTrackTitle);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.MediaPlayerAlbumTitle);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.MediaPlayerTrackArtist);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.MediaPlayerTrackNumber);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.MediaPlayerTrackGenre);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.MediaPlayerTrackTimeElapsed);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.PowerBatteryStrength);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.PowerBatteryState);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.PowerBatteryBackupStrength);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.PowerBatteryBackupState);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.Time);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.Date);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.PhoneSignalStrength);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.PhoneOperatorName);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.PhoneTalkingCallerName);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.PhoneActiveCallCount);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.PhoneProfileName);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.PhoneProfile);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.PhoneCellBroadcast);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.CalendarNextAppointmentHasConflict);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.OwnerName);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.OwnerPhoneNumber);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.OwnerEmail);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.OwnerNotes);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.ActiveSyncStatus);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.PhoneMissedCalls);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.HeadsetPresent);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.CarKitPresent);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.SpeakerPhoneActive);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.PhoneMultiLine);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.PhoneSimFull);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.PhoneNoSim);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.PhoneInvalidSim);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.PhoneBlockedSim);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.PhoneRadioOff);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.PhoneRadioPresent);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.PhoneRingerOff);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.PhoneLine1Selected);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.PhoneLine2Selected);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.PhoneRoaming);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.PhoneCallForwardingOnLine1);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.PhoneMissedCall);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.PhoneActiveDataCall);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.PhoneCallBarring);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.PhoneCallOnHold);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.PhoneConferenceCall);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.PhoneIncomingCall);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.PhoneCallCalling);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.PhoneGprsCoverage);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.PhoneNoService);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.PhoneSearchingForService);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.PhoneHomeService);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.Phone1xRttCoverage);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.PhoneCallTalking);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.PhoneCallForwardingOnLine2);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.CalendarNextAppointment);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.CalendarNextAppointmentBusyStatus);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.CalendarNextAppointmentCategories);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.CalendarAppointment);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.CalendarAppointmentSubject);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.CalendarAppointmentLocation);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.CalendarAppointmentStartTime);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.CalendarAppointmentEndTime);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.CalendarAppointmentHasConflict);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.CalendarAppointmentBusyStatus);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.CalendarAppointmentCategories);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.CalendarHomeScreenAppointment);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.CalendarHomeScreenAppointmentSubject);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.CalendarHomeScreenAppointmentLocation);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.CalendarHomeScreenAppointmentStartTime);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.CalendarHomeScreenAppointmentEndTime);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.CalendarHomeScreenAppointmentHasConflict);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.CalendarHomeScreenAppointmentBusyStatus);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.CalendarHomeScreenAppointmentCategories);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.PhoneIncomingCallerName);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.PhoneLastIncomingCallerName);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.PhoneIncomingCallerNumber);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.PhoneLastIncomingCallerNumber);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.PhoneIncomingCallerContactPropertyName);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.PhoneLastIncomingCallerContactPropertyName);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.PhoneIncomingCallerContactPropertyID);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.PhoneLastIncomingCallerContactPropertyID);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.PhoneIncomingCallerContact);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.PhoneLastIncomingCallerContact);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.PhoneTalkingCallerNumber);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.PhoneTalkingCallerContactPropertyName);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.PhoneTalkingCallerContactPropertyID);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.PhoneTalkingCallerContact);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.ConnectionsCount);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.ConnectionsBluetoothCount);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.ConnectionsBluetoothDescriptions);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.ConnectionsCellularCount);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.ConnectionsCellularDescriptions);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.ConnectionsNetworkCount);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.ConnectionsNetworkDescriptions);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.ConnectionsNetworkAdapters);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.ConnectionsDesktopCount);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.ConnectionsDesktopDescriptions);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.ConnectionsProxyCount);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.ConnectionsProxyDescriptions);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.ConnectionsModemCount);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.ConnectionsModemDescriptions);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.ConnectionsUnknownCount);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.ConnectionsUnknownDescriptions);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.ConnectionsVpnCount);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.ConnectionsVpnDescriptions);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.CalendarEvent);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.CalendarEventSubject);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.CalendarEventLocation);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.CalendarEventStartTime);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.CalendarEventEndTime);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.CalendarEventHasConflict);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.CalendarEventBusyStatus);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);
            s = new SystemState(SystemProperty.CalendarEventCategories);
            s.Changed += new ChangeEventHandler(ChangeOccurred);
            stateList.Add(s);

        }

        private void menuClear_Click(object sender, EventArgs e)
        {
            txtDump.Text = "";
        }

        private void menuValues_Click(object sender, EventArgs e)
        {
            ViewAllRawValues();
        }

        private void menuProperties_Click(object sender, EventArgs e)
        {
            ViewAllProperties();
        }

        private void SnbViewer_Load(object sender, EventArgs e)
        {
            SetUpNotifications();
            ViewAllProperties();
        }

        private void menuQuit_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

    }
}

