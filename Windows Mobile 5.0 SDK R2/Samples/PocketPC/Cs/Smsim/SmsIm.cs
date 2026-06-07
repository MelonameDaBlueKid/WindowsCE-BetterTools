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
#undef PrePopulateConversationsComboBox
#region Using directives

using System;
using System.Drawing;
using System.Collections;
using System.Windows.Forms;
using System.Data;

using System.Text;
using Microsoft.WindowsMobile.Forms;
using Microsoft.WindowsMobile.PocketOutlook;
using Microsoft.WindowsMobile.PocketOutlook.MessageInterception;
#endregion

namespace Microsoft.Samples.SmsInterception
{
    /// <summary>
    /// Summary description for form.
    /// </summary>
    public class SmsIM : System.Windows.Forms.Form
    {
        private ComboBox conversations;
        private TextBox txtMsgToSend;
        private TextBox txtConversation;
        private MenuItem menuAddName;
        private MenuItem menuSend;
        private Label label1;
        private Label label2;
        private Microsoft.WindowsCE.Forms.InputPanel inputPanel;
        /// <summary>
        /// Main menu for the form.
        /// </summary>
        private System.Windows.Forms.MainMenu mainMenu1;
		private	MessageInterceptor interceptor;

        public SmsIM()
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
            this.menuAddName = new System.Windows.Forms.MenuItem();
            this.menuSend = new System.Windows.Forms.MenuItem();
            this.conversations = new System.Windows.Forms.ComboBox();
            this.txtMsgToSend = new System.Windows.Forms.TextBox();
            this.txtConversation = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.inputPanel = new Microsoft.WindowsCE.Forms.InputPanel();
            // 
            // mainMenu1
            // 
            this.mainMenu1.MenuItems.Add(this.menuAddName);
            this.mainMenu1.MenuItems.Add(this.menuSend);
            // 
            // menuAddName
            // 
            this.menuAddName.Text = "Add Name";
            this.menuAddName.Click += new System.EventHandler(this.menuAddName_Click);
            // 
            // menuSend
            // 
            this.menuSend.Text = "Send";
            this.menuSend.Click += new System.EventHandler(this.menuSend_Click);
            // 
            // conversations
            // 
            this.conversations.Location = new System.Drawing.Point(34, 4);
            this.conversations.Size = new System.Drawing.Size(203, 22);
            this.conversations.SelectedIndexChanged += new System.EventHandler(this.conversations_SelectedIndexChanged);
            // 
            // txtMsgToSend
            // 
            this.txtMsgToSend.Location = new System.Drawing.Point(66, 33);
            this.txtMsgToSend.Multiline = true;
            this.txtMsgToSend.ScrollBars = System.Windows.Forms.ScrollBars.None;
            this.txtMsgToSend.Size = new System.Drawing.Size(171, 33);
            this.txtMsgToSend.GotFocus += new System.EventHandler(this.txtMsgToSend_GotFocus);
            // 
            // txtConversation
            // 
            this.txtConversation.Location = new System.Drawing.Point(4, 73);
            this.txtConversation.Multiline = true;
            this.txtConversation.ReadOnly = true;
            this.txtConversation.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.txtConversation.Size = new System.Drawing.Size(233, 192);
            // 
            // label1
            // 
            this.label1.Location = new System.Drawing.Point(0, 5);
            this.label1.Size = new System.Drawing.Size(28, 20);
            this.label1.Text = "To:";
            // 
            // label2
            // 
            this.label2.Location = new System.Drawing.Point(4, 33);
            this.label2.Size = new System.Drawing.Size(56, 20);
            this.label2.Text = "Message:";
            // 
            // inputPanel
            // 
            this.inputPanel.EnabledChanged += new System.EventHandler(this.inputPanel1_EnabledChanged);
            // 
            // SmsIM
            // 
            this.ClientSize = new System.Drawing.Size(240, 268);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.txtConversation);
            this.Controls.Add(this.txtMsgToSend);
            this.Controls.Add(this.conversations);
            this.Menu = this.mainMenu1;
            this.Text = "SMS";
            this.Load += new System.EventHandler(this.SmsIM_Load);
            this.Closed += new System.EventHandler(this.SmsIM_Closed);
            this.Activated += new System.EventHandler(this.SmsIM_Activated);

        }

        #endregion

        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        static void Main()
        {
            Application.Run(new SmsIM());
        }



        private void SwitchToConversation(Conversation conversation)
        {
            conversations.SelectedItem = conversation;
            txtConversation.Text = conversation.Transcript;
            // Put focus back on MsgToSend for convenience
            txtMsgToSend.Focus();
        }

        private void menuSend_Click(object sender, EventArgs e)
        {
            Conversation conv = (Conversation)conversations.SelectedItem;
            if (null == conv)  // if we're not in a conversation
            {
                CreateNewConversation();
                conv = (Conversation)conversations.SelectedItem;
                if (null == conv) // if there's still no conversation
                {
                    return;
                }
            }

            // Send the SMS message
            SmsMessage msg = new SmsMessage(NormalizePhoneNumber(conv.PhoneNumber), txtMsgToSend.Text);
            msg.Send();

            // Update the transcript
            conv.AddToTranscript("Me", txtMsgToSend.Text);
            txtConversation.Text = conv.Transcript;

            // Clear the "Message" edit box
            txtMsgToSend.Text = "";
        }

        private void CreateNewConversation()
        {
            Conversation currentConv = null;
            ChooseContactDialog dlg = new ChooseContactDialog();
            // Choose from everyone who has a MobileTelephoneNumber
            dlg.RequiredProperties = new ContactProperty[] { ContactProperty.AllTextMessaging };
            if (dlg.ShowDialog() == DialogResult.OK)
            {
                // Add the contact to the combobox
                // First check if it's already there
                foreach (Conversation conv in conversations.Items)
                {
                    if (conv.Contact.ItemId == dlg.SelectedContact.ItemId)
                    {
                        // The contact is already in the list of conversations
                        // so just use that conversation.
                        currentConv = conv;
                        break;
                    }
                }
                // if not, make a new one.
                if (currentConv == null)
                {
                    currentConv = new Conversation(dlg.SelectedContact);
                    conversations.Items.Add(currentConv);
                }
                SwitchToConversation(currentConv);
            }

        }

        private void menuAddName_Click(object sender, EventArgs e)
        {
            CreateNewConversation();
        }

        /// <summary>
        /// The MessageInterceptor event handler, which gets called when an SMS 
        /// message arrives.
        /// </summary>
        /// <param name="sender">The MessageInterceptor</param>
        /// <param name="e">Contains the SMS message</param>
        private void OnSmsReceived(object sender, MessageInterceptorEventArgs e)
        {
            Conversation currentConv = null;
            Contact contact = null;
            SmsMessage msg = (SmsMessage)e.Message;

            // First look through the combobox for the phone number
            foreach (Conversation conv in conversations.Items)
            {
                if (PhoneNumbersMatch(conv.PhoneNumber, msg.From.Address))
                {
                    // Found the conversation
                    currentConv = conv;
                    break;
                }
            }
            if (currentConv == null)
            {
                // This phone number is not in the combo box, so look through
                // the full contacts database.
                using (OutlookSession session = new OutlookSession())
                {
                    foreach (Contact c in session.Contacts.Items)
                    {
                        if (c.MobileTelephoneNumber.Length != 0
                            && PhoneNumbersMatch(c.MobileTelephoneNumber, msg.From.Address))
                        {
                            // We have a match
                            contact = c;
                            break;
                        }
                    }
                    if (contact == null)
                    {
                        // There is no contact for this phone number
                        // so create one
                        contact = new Contact();
                        contact.MobileTelephoneNumber = msg.From.Address;
                         
                        session.Contacts.Items.Add(contact);
                    }
                    currentConv = new Conversation(contact);
                    conversations.Items.Add(currentConv);
                }
            }
            currentConv.AddToTranscript(msg.From.Name, msg.Body);
            SwitchToConversation(currentConv);
            // Bring the app forward
            this.BringToFront();
        }

        private void SmsIM_Load(object sender, EventArgs e)
        {
            txtMsgToSend.Focus();

            // Set up SMS interception
            interceptor = new MessageInterceptor();
            interceptor.InterceptionAction = InterceptionAction.NotifyAndDelete;
            interceptor.MessageReceived += new MessageInterceptorEventHandler(OnSmsReceived);

#if PrePopulateConversationsComboBox   
            using (OutlookSession session = new OutlookSession())
            {
                foreach (Contact c in session.Contacts.Items)
                {
                    if (c.MobileTelephoneNumber != "")
                    {
                        conversations.Items.Add(new Conversation(c));
                    }
                }
            }
#endif
        }

        private static string NormalizePhoneNumber(string s)
        {
            StringBuilder sb = new StringBuilder();
            for (int i = 0; i < s.Length; i++)
            {
                if (s[i] >= '0' && s[i] <= '9')
                {
                    sb.Append(s[i]);
                }
            }
            return sb.ToString();
        }

        private static bool PhoneNumbersMatch(string s1, string s2)
        {
            string num1 = NormalizePhoneNumber(s1);
            string num2 = NormalizePhoneNumber(s2);
            return num1.Substring(Math.Max(0, num1.Length - 7)) ==
                   num2.Substring(Math.Max(0, num2.Length - 7));
        }

        private void conversations_SelectedIndexChanged(object sender, EventArgs e)
        {
            SwitchToConversation((Conversation)conversations.SelectedItem);
        }

        private class Conversation
        {
            private Contact contact;
            private string transcript;
            private string phoneNumber;

            public Conversation(Contact c)
            {
                contact = c;
                phoneNumber = c.MobileTelephoneNumber;
            }

            /// <summary>
            /// The person you are having a conversation with
            /// </summary>
            public Contact Contact
            {
                get
                {
                    return contact;
                }
            }

            /// <summary>
            /// The transcript of the entire conversation
            /// </summary>
            public string Transcript
            {
                get
                {
                    return transcript;
                }
            }

            public void AddToTranscript(string sender, string msg)
            {
                transcript = sender + ": " + msg + "\r\n" + transcript;
            }

            public string PhoneNumber
            {
                get
                {
                    return phoneNumber;
                }
            }

            public override string ToString()
            {
                return contact.ToString();
            }
        }

        private void inputPanel1_EnabledChanged(object sender, EventArgs e)
        {
            txtConversation.Height = inputPanel.Enabled ? 104 : 184;
        }

        private void txtMsgToSend_GotFocus(object sender, EventArgs e)
        {
            inputPanel.Enabled = true;
        }

        private void SmsIM_Activated(object sender, EventArgs e)
        {
            inputPanel1_EnabledChanged(null, null);
        }

        private void SmsIM_Closed(object sender, EventArgs e)
        {
            interceptor.Dispose();
        }
    }
}

