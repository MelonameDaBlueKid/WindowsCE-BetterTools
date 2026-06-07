//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this sample source code is subject to the terms of the Microsoft
// license agreement under which you licensed this sample source code. If
// you did not accept the terms of the license agreement, you are not
// authorized to use this sample source code. For the terms of the license,
// please see the license agreement between you and Microsoft or, if applicable,
// see the LICENSE.RTF on your install media or the root of your tools installation.
// THE SAMPLE SOURCE CODE IS PROVIDED "AS IS", WITH NO WARRANTIES OR INDEMNITIES.
//
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
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
    /// This class displays the details of an appointment request that
    /// is received.
    /// </summary>
    public class AppointmentDetails : System.Windows.Forms.Form
    {
        #region Private Variables

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox subject;
        private System.Windows.Forms.Label startTime;
        private System.Windows.Forms.Label endTime;
        private System.Windows.Forms.TextBox sendTo;
        private System.Windows.Forms.TextBox body;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label location;
        private System.Windows.Forms.MainMenu mainMenu1;
        private System.Windows.Forms.MenuItem menuItem1;
        private System.Windows.Forms.Button lookupButton;
        private MenuItem menuItem3;
        private Appointment appointmentShowing;
    
        #endregion

        #region Constructor and Dispose

        /// <summary>
        /// Initialize the form.
        /// </summary>
        public AppointmentDetails()
        {
            //
            // Required for Windows Form Designer support
            //
            InitializeComponent();

        }

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        protected override void Dispose( bool disposing )
        {
            base.Dispose( disposing );
        }

        #endregion

        #region Display appointment details
        /// <summary>
        /// This shows the information in an appointment to the user.
        /// </summary>
        /// <param name="appointment"> The appointment to be displayed.</param>
        public void UpdateDisplay(Appointment appointment)
        {
            subject.Text = appointment.Subject;
            startTime.Text = appointment.Start.ToShortDateString() + " " + appointment.Start.ToShortTimeString();
            endTime.Text = appointment.End.ToShortDateString() + " " + appointment.End.ToShortTimeString();
            body.Text = appointment.Body;
            location.Text = appointment.Location;
            appointmentShowing = appointment;

            //Fictitious phone number
            sendTo.Text = "(425) 555-0100";
        }
        #endregion

        #region Windows Form Designer generated code
        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.label1 = new System.Windows.Forms.Label();
            this.subject = new System.Windows.Forms.TextBox();
            this.startTime = new System.Windows.Forms.Label();
            this.endTime = new System.Windows.Forms.Label();
            this.sendTo = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.body = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.location = new System.Windows.Forms.Label();
            this.mainMenu1 = new System.Windows.Forms.MainMenu();
            this.menuItem1 = new System.Windows.Forms.MenuItem();
            this.menuItem3 = new System.Windows.Forms.MenuItem();
            this.lookupButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.Font = new System.Drawing.Font("Tahoma", 10F, System.Drawing.FontStyle.Bold);
            this.label1.Location = new System.Drawing.Point(8, 60);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(104, 23);
            this.label1.Text = "Appointment";
            // 
            // subject
            // 
            this.subject.Location = new System.Drawing.Point(8, 86);
            this.subject.Multiline = true;
            this.subject.Name = "subject";
            this.subject.ReadOnly = true;
            this.subject.ScrollBars = System.Windows.Forms.ScrollBars.None;
            this.subject.Size = new System.Drawing.Size(224, 23);
            this.subject.TabIndex = 11;
            this.subject.Text = "Subject";
            // 
            // startTime
            // 
            this.startTime.Font = new System.Drawing.Font("Tahoma", 8F, System.Drawing.FontStyle.Regular);
            this.startTime.Location = new System.Drawing.Point(72, 112);
            this.startTime.Name = "startTime";
            this.startTime.Size = new System.Drawing.Size(160, 16);
            this.startTime.Text = "Start";
            // 
            // endTime
            // 
            this.endTime.Font = new System.Drawing.Font("Tahoma", 8F, System.Drawing.FontStyle.Regular);
            this.endTime.Location = new System.Drawing.Point(74, 128);
            this.endTime.Name = "endTime";
            this.endTime.Size = new System.Drawing.Size(158, 16);
            this.endTime.Text = "End";
            // 
            // sendTo
            // 
            this.sendTo.Location = new System.Drawing.Point(10, 35);
            this.sendTo.Name = "sendTo";
            this.sendTo.ScrollBars = System.Windows.Forms.ScrollBars.None;
            this.sendTo.Size = new System.Drawing.Size(142, 21);
            this.sendTo.TabIndex = 8;
            this.sendTo.Text = "textBox2";
            // 
            // label4
            // 
            this.label4.Font = new System.Drawing.Font("Tahoma", 9F, System.Drawing.FontStyle.Bold);
            this.label4.Location = new System.Drawing.Point(8, 18);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(48, 17);
            this.label4.Text = "Invite:";
            // 
            // body
            // 
            this.body.Location = new System.Drawing.Point(8, 164);
            this.body.Multiline = true;
            this.body.Name = "body";
            this.body.ReadOnly = true;
            this.body.ScrollBars = System.Windows.Forms.ScrollBars.None;
            this.body.Size = new System.Drawing.Size(224, 87);
            this.body.TabIndex = 5;
            this.body.Text = "Body";
            // 
            // label6
            // 
            this.label6.Font = new System.Drawing.Font("Tahoma", 8F, System.Drawing.FontStyle.Bold);
            this.label6.Location = new System.Drawing.Point(8, 112);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(48, 16);
            this.label6.Text = "Start:";
            // 
            // label7
            // 
            this.label7.Font = new System.Drawing.Font("Tahoma", 8F, System.Drawing.FontStyle.Bold);
            this.label7.Location = new System.Drawing.Point(10, 128);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(48, 16);
            this.label7.Text = "End:";
            // 
            // label2
            // 
            this.label2.Font = new System.Drawing.Font("Tahoma", 8F, System.Drawing.FontStyle.Bold);
            this.label2.Location = new System.Drawing.Point(10, 144);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(56, 16);
            this.label2.Text = "Location:";
            // 
            // location
            // 
            this.location.Font = new System.Drawing.Font("Tahoma", 8F, System.Drawing.FontStyle.Regular);
            this.location.Location = new System.Drawing.Point(72, 144);
            this.location.Name = "location";
            this.location.Size = new System.Drawing.Size(160, 16);
            this.location.Text = "Location";
            // 
            // mainMenu1
            // 
            this.mainMenu1.MenuItems.Add(this.menuItem1);
            this.mainMenu1.MenuItems.Add(this.menuItem3);
            // 
            // menuItem1
            // 
            this.menuItem1.Text = "Close";
            this.menuItem1.Click += new System.EventHandler(this.CloseApplication);
            // 
            // menuItem3
            // 
            this.menuItem3.Text = "Send";
            this.menuItem3.Click += new System.EventHandler(this.SendAppointment);
            // 
            // lookupButton
            // 
            this.lookupButton.Location = new System.Drawing.Point(162, 35);
            this.lookupButton.Name = "lookupButton";
            this.lookupButton.Size = new System.Drawing.Size(70, 22);
            this.lookupButton.TabIndex = 0;
            this.lookupButton.Text = "Lookup";
            this.lookupButton.Click += new System.EventHandler(this.LookUpContact);
            // 
            // AppointmentDetails
            // 
            this.ClientSize = new System.Drawing.Size(240, 268);
            this.Controls.Add(this.lookupButton);
            this.Controls.Add(this.location);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.body);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.sendTo);
            this.Controls.Add(this.endTime);
            this.Controls.Add(this.startTime);
            this.Controls.Add(this.subject);
            this.Controls.Add(this.label1);
            this.Menu = this.mainMenu1;
            this.Name = "AppointmentDetails";
            this.Text = "Details";
            this.ResumeLayout(false);

        }
        #endregion
        
        #region Event handlers
        /// <summary>
        /// This lets the user lookup the contacts and choose a contact
        /// </summary>
        /// <param name="sender">Sender</param>
        /// <param name="e">Event arguments</param>
        private void LookUpContact(object sender, System.EventArgs e)
        {
            ContactChooserDialog contactPickerForm = new ContactChooserDialog(this);
            contactPickerForm.Visible = true;
        }
       
        /// <summary>
        /// SendAppointment sends two sms messages that describe the
        /// appointment proposal.
        /// </summary>
        /// <param name="sender">Sender</param>
        /// <param name="args">Event Arguments</param>
        private void SendAppointment(object sender, EventArgs args)
        {
            string msg;
            string appointmentMessage1 = "";
            string appointmentMessage2 = "";

            //Create appointment request messages. One message for the subject, location, time, etc
            //The second message contains the body of the appointment that can be fit into an SMS.
            SmsCreator.SmsCreateProposalMessages(appointmentShowing, ref appointmentMessage1, ref appointmentMessage2);

            SmsMessage sms = new SmsMessage(sendTo.Text, appointmentMessage1);
            SmsMessage sms2 = new SmsMessage(sendTo.Text, appointmentMessage2);

            try
            {
                sms.Send();
                sms2.Send();

                msg = "The request has been sent over SMS to " + sendTo.Text + 
                      ". You will be notified when the response is obtained.";
            }
            catch (SmsException smsException)
            {
                msg = smsException.Message;
            }

            
            MessageBox.Show(msg, "Confirmation", MessageBoxButtons.OK, MessageBoxIcon.None, MessageBoxDefaultButton.Button1);
            this.Close();
        }


        /// <summary>
        /// Event handler that closes the application.
        /// </summary>
        /// <param name="sender">Sender</param>
        /// <param name="args">Event arguments</param>
        private void CloseApplication(object sender, EventArgs args)
        {
            this.Close();
        }

        /// <summary>
        /// Lets the user set the contact phone number by choosing a contact
        /// </summary>
        /// <param name="phone"> Phone number selected</param>
        public string ContactPhone
        {
            set
            {
                sendTo.Text = value;
            }
        }
        #endregion

    }
}
