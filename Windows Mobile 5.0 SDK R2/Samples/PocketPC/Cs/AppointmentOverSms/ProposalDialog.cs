//
// Copyright (c) Microsoft Corporation.� All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.
//

using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using Microsoft.WindowsMobile.PocketOutlook;
using Microsoft.WindowsMobile.PocketOutlook.MessageInterception;

namespace AppointmentOverSms
{
    /// <summary>
    /// This class shows the user the appointment request that is sent.
    /// Depending on the response that the user select it sends the
    /// corresponding SMS back to the meeting organizer.
    /// </summary>
    public class ProposalDialog : System.Windows.Forms.Form
    {

        #region Private Variables

        private System.Windows.Forms.TextBox subject;
        private System.Windows.Forms.Label startTime;
        private System.Windows.Forms.Label endTime;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Button acceptButton;
        private System.Windows.Forms.Button declineButton;
        private System.Windows.Forms.Button tentativeButton;
        private System.Windows.Forms.Label senderLabel;
        private System.Windows.Forms.Label conflictLabel;
        private Appointment appointmentShowing;
        private System.Windows.Forms.Label sentByLabel;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox body;
        private System.Windows.Forms.Label location;
        private Contact senderContact;
    
        #endregion

        #region Constructor

        public ProposalDialog()
        {
            //
            // Required for Windows Form Designer support
            //
            InitializeComponent();

        }
        #endregion
      
        #region Display appointment request information

        /// <summary>
        /// This notifies the user if a meeting request is received
        /// </summary>
        /// <param name="appointment"> The appointment request</param>
        /// <param name="contact"> The contact who sent the proposal</param>
        public void UpdateProposalReceived(Appointment appointment, Contact contact)
        {
            appointmentShowing = appointment;

            //Find conflicts ( appointments during the same time) for the appointment request
            string conflict = Utilities.FindConflicts(appointment);

            subject.Text = appointment.Subject;
            startTime.Text = appointment.Start.ToShortDateString() + " " + appointment.Start.ToShortTimeString();
            endTime.Text = appointment.End.ToShortDateString() + " " + appointment.End.ToShortTimeString();
            location.Text = appointment.Location;
            senderLabel.Text = contact.FirstName+" "+contact.LastName;
            senderContact = contact;
            body.Text = appointment.Body +"...";
            conflictLabel.Text = conflict;
        }
        #endregion

        #region Windows Form Designer generated code
        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.subject = new System.Windows.Forms.TextBox();
            this.startTime = new System.Windows.Forms.Label();
            this.endTime = new System.Windows.Forms.Label();
            this.sentByLabel = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.senderLabel = new System.Windows.Forms.Label();
            this.acceptButton = new System.Windows.Forms.Button();
            this.declineButton = new System.Windows.Forms.Button();
            this.tentativeButton = new System.Windows.Forms.Button();
            this.conflictLabel = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.location = new System.Windows.Forms.Label();
            this.body = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // subject
            // 
            this.subject.BackColor = System.Drawing.Color.White;
            this.subject.Font = new System.Drawing.Font("Tahoma", 9F, System.Drawing.FontStyle.Bold);
            this.subject.Location = new System.Drawing.Point(8, 13);
            this.subject.Multiline = true;
            this.subject.Name = "subject";
            this.subject.ReadOnly = true;
            this.subject.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.subject.Size = new System.Drawing.Size(224, 18);
            this.subject.TabIndex = 13;
            this.subject.Text = "Subject";
            // 
            // startTime
            // 
            this.startTime.Font = new System.Drawing.Font("Tahoma", 8F, System.Drawing.FontStyle.Regular);
            this.startTime.Location = new System.Drawing.Point(56, 38);
            this.startTime.Name = "startTime";
            this.startTime.Size = new System.Drawing.Size(176, 16);
            this.startTime.Text = "Start";
            // 
            // endTime
            // 
            this.endTime.Font = new System.Drawing.Font("Tahoma", 8F, System.Drawing.FontStyle.Regular);
            this.endTime.Location = new System.Drawing.Point(56, 54);
            this.endTime.Name = "endTime";
            this.endTime.Size = new System.Drawing.Size(176, 16);
            this.endTime.Text = "End";
            // 
            // sentByLabel
            // 
            this.sentByLabel.Font = new System.Drawing.Font("Tahoma", 8F, System.Drawing.FontStyle.Bold);
            this.sentByLabel.Location = new System.Drawing.Point(8, 70);
            this.sentByLabel.Name = "sentByLabel";
            this.sentByLabel.Size = new System.Drawing.Size(56, 16);
            this.sentByLabel.Text = "Sent by:";
            // 
            // label6
            // 
            this.label6.Font = new System.Drawing.Font("Tahoma", 8F, System.Drawing.FontStyle.Bold);
            this.label6.Location = new System.Drawing.Point(8, 38);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(48, 16);
            this.label6.Text = "Start:";
            // 
            // label7
            // 
            this.label7.Font = new System.Drawing.Font("Tahoma", 8F, System.Drawing.FontStyle.Bold);
            this.label7.Location = new System.Drawing.Point(8, 54);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(48, 16);
            this.label7.Text = "End:";
            // 
            // senderLabel
            // 
            this.senderLabel.Font = new System.Drawing.Font("Tahoma", 8F, System.Drawing.FontStyle.Regular);
            this.senderLabel.Location = new System.Drawing.Point(64, 70);
            this.senderLabel.Name = "senderLabel";
            this.senderLabel.Size = new System.Drawing.Size(168, 16);
            this.senderLabel.Text = "Sender";
            // 
            // acceptButton
            // 
            this.acceptButton.Location = new System.Drawing.Point(8, 223);
            this.acceptButton.Name = "acceptButton";
            this.acceptButton.Size = new System.Drawing.Size(66, 24);
            this.acceptButton.TabIndex = 6;
            this.acceptButton.Text = "Accept";
            this.acceptButton.Click += new System.EventHandler(this.acceptButton_Click);
            // 
            // declineButton
            // 
            this.declineButton.Location = new System.Drawing.Point(80, 223);
            this.declineButton.Name = "declineButton";
            this.declineButton.Size = new System.Drawing.Size(68, 24);
            this.declineButton.TabIndex = 5;
            this.declineButton.Text = "Decline";
            this.declineButton.Click += new System.EventHandler(this.declineButton_Click);
            // 
            // tentativeButton
            // 
            this.tentativeButton.Location = new System.Drawing.Point(155, 223);
            this.tentativeButton.Name = "tentativeButton";
            this.tentativeButton.Size = new System.Drawing.Size(77, 24);
            this.tentativeButton.TabIndex = 4;
            this.tentativeButton.Text = "Tentative";
            this.tentativeButton.Click += new System.EventHandler(this.tentativeButton_Click);
            // 
            // conflictLabel
            // 
            this.conflictLabel.Location = new System.Drawing.Point(8, 196);
            this.conflictLabel.Name = "conflictLabel";
            this.conflictLabel.Size = new System.Drawing.Size(216, 14);
            this.conflictLabel.Text = "Conflicts";
            // 
            // label2
            // 
            this.label2.Font = new System.Drawing.Font("Tahoma", 8F, System.Drawing.FontStyle.Bold);
            this.label2.Location = new System.Drawing.Point(8, 86);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(56, 16);
            this.label2.Text = "Location:";
            // 
            // location
            // 
            this.location.Font = new System.Drawing.Font("Tahoma", 8F, System.Drawing.FontStyle.Regular);
            this.location.Location = new System.Drawing.Point(64, 86);
            this.location.Name = "location";
            this.location.Size = new System.Drawing.Size(160, 16);
            this.location.Text = "Location";
            // 
            // body
            // 
            this.body.BackColor = System.Drawing.Color.White;
            this.body.Location = new System.Drawing.Point(8, 105);
            this.body.Multiline = true;
            this.body.Name = "body";
            this.body.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.body.Size = new System.Drawing.Size(224, 88);
            this.body.TabIndex = 0;
            this.body.Text = "Body";
            // 
            // ShowProposal
            // 
            this.ClientSize = new System.Drawing.Size(240, 294);
            this.Controls.Add(this.body);
            this.Controls.Add(this.location);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.conflictLabel);
            this.Controls.Add(this.tentativeButton);
            this.Controls.Add(this.declineButton);
            this.Controls.Add(this.acceptButton);
            this.Controls.Add(this.senderLabel);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.sentByLabel);
            this.Controls.Add(this.endTime);
            this.Controls.Add(this.startTime);
            this.Controls.Add(this.subject);
            this.Name = "ShowProposal";
            this.Text = "Appointment Request";
            this.ResumeLayout(false);

        }
        #endregion

        #region Handle user action - accept/decline/tentative

        /// <summary>
        /// This is triggered when the user hits accept to a meeting request.
        /// It will make and send the SMS.
        /// </summary>
        /// <param name="sender">Sender</param>
        /// <param name="eventArgs">Event sent by control</param>
        private void acceptButton_Click(object sender, System.EventArgs eventArgs)
        {
            AddAppointment(appointmentShowing);
            SendResponse(ActionType.Accept);
            this.Close();
        }
        /// <summary>
        /// This is triggered when the user hits decline to a meeting request.
        /// It will make and send the SMS.
        /// </summary>
        /// <param name="sender">Sender</param>
        /// <param name="eventArgs">Event sent by control</param>
        private void declineButton_Click(object sender, System.EventArgs eventArgs)
        {
            SendResponse(ActionType.Decline);
            this.Close();
        }

        /// <summary>
        /// This is triggered when the user hits tentative to a meeting request.
        /// It will make and send the SMS.
        /// </summary>
        /// <param name="sender">Sender</param>
        /// <param name="eventArgs">Event sent by control</param>
        private void tentativeButton_Click(object sender, System.EventArgs eventArgs)
        {
            appointmentShowing.BusyStatus = BusyStatus.Tentative;
            AddAppointment(appointmentShowing);
            SendResponse(ActionType.Tentative);
            this.Close();
        }

        /// <summary>
        /// Common method used to accept appointments and accept them as tentative appointments.
        /// </summary>
        /// <param name="a">Appointment to add</param>
        public void AddAppointment(Appointment a)
        {
            OutlookSession mySession = new OutlookSession();
            Appointment duplicate = Utilities.FindAppointment(a);

            if (duplicate == null)
            {
                //Add the new appointment
                if (senderContact.Email1Address.Length != 0)
                {
                    appointmentShowing.Recipients.Add(new Recipient(senderContact.FileAs, senderContact.Email1Address));
                }
                mySession.Appointments.Items.Add(appointmentShowing);
            }
            else
            {
                // Just add recipients to the already existing appointment.
                // We need to add the email address to the recipients.
                if (senderContact.Email1Address != "")
                {
                    duplicate.Recipients.Add(new Recipient(senderContact.FileAs, senderContact.Email1Address));
                    duplicate.Update();
                }
            }
        }
        #endregion

        #region Send user response
      
        /// <summary>
        /// This creates the SMS with the specified action type that the user specifies,
        /// and sends the created SMS.
        /// </summary>
        /// <param name="actionChosen"></param>
        private void SendResponse(ActionType actionChosen)
        {
            //Create the SMS message
            string appointmentMessage = "";
            SmsCreator.SmsCreateResponseMessage(appointmentShowing, actionChosen, ref appointmentMessage);

            SmsMessage sms = new SmsMessage(senderContact.MobileTelephoneNumber, appointmentMessage);
            sms.Send();

            //Show confirmation to the user
            string msg = "The response has been sent.";            
            MessageBox.Show(msg, "Confirmation", MessageBoxButtons.OK, MessageBoxIcon.None, MessageBoxDefaultButton.Button1);
        }

        #endregion
    }
}
