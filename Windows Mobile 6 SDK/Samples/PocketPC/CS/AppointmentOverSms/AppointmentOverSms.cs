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
using System.Windows.Forms;
using System.Data;
using Microsoft.WindowsMobile.PocketOutlook;
using Microsoft.WindowsMobile.Samples.ControlLibrary;
using Microsoft.WindowsMobile.PocketOutlook.MessageInterception;

namespace AppointmentOverSms
{

    /// <summary>
    /// Summary description for form.
    /// </summary>
    public partial class AppointmentPicker : System.Windows.Forms.Form
    {
        private MainMenu mainMenu2;
        private MenuItem menuItem1;
        private AppointmentListView appointmentControl;
        private Label label1;                

        /// <summary>
        /// The AppointmentPicker lets the user select an appointment to send
        /// as a meeting proposal.
        /// </summary>
        public AppointmentPicker()
        {
            InitializeComponent();

            OutlookSession mySession = new OutlookSession();

            //Register the click event handler
            appointmentControl.PimItemSelected += new PimItemListView.ClickEventHandler(Clicked);

            //Obtain all future appointments and add them to the control
            string query = "[Start] >= " + DateTime.Now.ToShortDateString(); 
           
            appointmentControl.Appointments = mySession.Appointments.Items.Restrict(query);
            appointmentControl.PimItemProperty1 = AppointmentProperty.Subject;
            appointmentControl.PimItemProperty2 = AppointmentProperty.Start;

        }

        /// <summary>
        /// Initializes the AppointmentPicker form.
        /// </summary>
        private void InitializeComponent()
        {
            this.mainMenu2 = new System.Windows.Forms.MainMenu();
            this.menuItem1 = new System.Windows.Forms.MenuItem();
            this.appointmentControl = new Microsoft.WindowsMobile.Samples.ControlLibrary.AppointmentListView();
            this.label1 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // mainMenu2
            // 
            this.mainMenu2.MenuItems.Add(this.menuItem1);
            // 
            // menuItem1
            // 
            this.menuItem1.Text = "Exit";
            this.menuItem1.Click += new System.EventHandler(this.CloseAppointmentOverSms);
            // 
            // appointmentControl
            // 
            this.appointmentControl.Location = new System.Drawing.Point(5, 28);
            this.appointmentControl.Name = "appointmentControl";
            this.appointmentControl.Size = new System.Drawing.Size(232, 237);
            this.appointmentControl.TabIndex = 0;
            // 
            // label1
            // 
            this.label1.Location = new System.Drawing.Point(7, 6);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(219, 20);
            this.label1.Text = "Pick the appointment to send.";
            // 
            // AppointmentPicker
            // 
            this.ClientSize = new System.Drawing.Size(240, 268);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.appointmentControl);
            this.Menu = this.mainMenu2;
            this.Name = "AppointmentPicker";
            this.Text = "AppointmentOverSms";
            this.ResumeLayout(false);

        }

        #region Events and Handlers
        /// <summary>
        /// Capture the clicked event, get the information of the appointment
        /// and pass it to a new form which will display the details of the
        /// appointment.
        /// </summary>
        /// <param name="sender">Sender</param>
        /// <param name="pimItemEventArgs">Argument that contains the appointment that was clicked</param>
        private void Clicked(object sender, PimItemListView.PimItemListViewEventArgs pimItemEventArgs)
        {
            //Display the appointment details to the user
            AppointmentDetails detailsForm = new AppointmentDetails();

            detailsForm.UpdateDisplay((Appointment)pimItemEventArgs.PimItem);
            detailsForm.Visible = true;
        }
        #endregion


        #region SMS Received Event Handler
        /// <summary>
        /// This event is fired when an SMS with the specified criteria is received.
        /// </summary>
        /// <param name="sender">Sender</param>
        /// <param name="e">Message details</param>
        private void message_Received(object sender, MessageInterceptorEventArgs e)
        {
            string message = ((SmsMessage)e.Message).Body;
            Recipient recipient;
            ActionType action = ActionType.Accept;

            //Parse the message received to determine the type of message
            
            Appointment currentAppointment = SmsParser.ParseMessage(message, e.Message.From.Address, ref action);

            //If parsed succesfully, process the message
            if (currentAppointment != null)
            {

                //If the appointment is a proposal
                if (action == ActionType.ProposalSubject || action == ActionType.ProposalBody)
                {
                    //Find the the contact who sent the proposal
                    Contact contact = Utilities.FindContact(e.Message.From);
                    //Create new form
                    ProposalDialog proposalForm = new ProposalDialog();
                    //Show proposal information
                    proposalForm.UpdateProposalReceived(currentAppointment, contact);
                    proposalForm.Visible = true;
                    proposalForm.Show();
                }
                //If the message is an Acceptance to a meeting request
                else
                {
                    //Find that appointment on your calendar
                    Appointment appointment = Utilities.FindAppointment(currentAppointment);

                    if (appointment != null)
                    {
                        //Find the name of the contact who sent the response
                        Contact contact = Utilities.FindContact(e.Message.From);

                        if (action == ActionType.Accept)
                        {
                            //Add the contact as a recepient of the meeting
                            if (contact.Email1Address != "")
                            {
                                //We can add recipients only if they have an Email Address.
                                recipient = new Recipient(contact.FileAs, contact.Email1Address);
                                appointment.Recipients.Add(recipient);
                                appointment.Update();
                            }
                        }

                        //Notify user about the response sent
                        string msg = MakeMessage(action, appointment, contact);
                        MessageBox.Show(msg, "Confirmation", MessageBoxButtons.OK, MessageBoxIcon.None, MessageBoxDefaultButton.Button1);                            
                    }
                }
            }
        }

        /// <summary>
        /// Make the appropriate response message to notify the user
        /// </summary>
        /// <param name="actionType"> Whether the response is accept/decline/tentative</param>
        /// <param name="appointment"> The appointment information</param>
        /// <param name="contact"> The contact who sent the response</param>
        /// <returns>Message to notify the user</returns>
        private string MakeMessage(ActionType actionType, Appointment appointment, Contact contact)
        {
            string msg = "";

            switch (actionType)
            {
                case ActionType.Accept:
                    msg += contact.FirstName + " " + contact.LastName + " has accepted the meeting: " +
                        "\r\nSubject: " + appointment.Subject + "\r\nStart: " +
                        appointment.Start.ToShortDateString() + " " + appointment.Start.ToShortTimeString() +
                        "\r\nEnd: " + appointment.End.ToShortDateString() + " " + appointment.End.ToShortTimeString();
                    break;
                case ActionType.Decline:
                    msg += contact.FirstName + " " + contact.LastName + " has declined the meeting: " +
                        "\r\nSubject: " + appointment.Subject + "\r\nStart: " +
                        appointment.Start.ToShortDateString() + " " + appointment.Start.ToShortTimeString() +
                        "\r\nEnd: " + appointment.End.ToShortDateString() + " " + appointment.End.ToShortTimeString();

                    break;
                case ActionType.Tentative:
                    msg += contact.FirstName + " " + contact.LastName + " has tentatively accepted the meeting: " +
                           "\r\nSubject: " + appointment.Subject + "\r\nStart: " +
                           appointment.Start.ToShortDateString() + " " + appointment.Start.ToShortTimeString() +
                           "\r\nEnd: " + appointment.End.ToShortDateString() + " " + appointment.End.ToShortTimeString();
                    break;
                default:
                    break;
            }

            return msg;
        }
        #endregion


        /// <summary>
        /// The main entry point for the application. Register application launcher
        /// so that whenever an appointment request comes in, it launches this application
        /// and gives an argument to distinguish between a user starting this application
        /// and the launcher starting it.
        /// </summary>
        /// <param name="args"> 
        /// Null if the user starts, otherwise it is not null.
        /// </param>
        static void Main(string[] args)
        {
            AppointmentPicker picker = new AppointmentPicker();
            MessageInterceptor rule;

            //If the user has started the app for the first time, Register the event
            if (args.Length == 0 && !MessageInterceptor.IsApplicationLauncherEnabled("AppointmentOverSms"))
            {
                rule = new MessageInterceptor(InterceptionAction.NotifyAndDelete);
                MessageCondition condition = new MessageCondition(MessageProperty.Subject,
                    MessagePropertyComparisonType.StartsWith,
                    SmsCreator.identifierProtocol,
                    false);
                rule.MessageCondition = condition;
                rule.EnableApplicationLauncher("AppointmentOverSms", @"\Program Files\AppointmentOverSms\AppointmentOverSms.exe", "EventFired");
                rule.MessageReceived += new MessageInterceptorEventHandler(picker.message_Received);
            }
            else
            {
                //Otherwise jsut hook up the events
                MessageInterceptor messageInterceptor = new MessageInterceptor("AppointmentOverSms");
                messageInterceptor.MessageReceived += new MessageInterceptorEventHandler(picker.message_Received);
            }
            Application.Run(picker);
        }

        /// <summary>
        /// CloseAppointmentOverSms is an event handler that closes the AppointmentOverSms application.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void CloseAppointmentOverSms(object sender, EventArgs e)
        {
            appointmentControl.Dispose();
            this.Close();
        }
    }
}