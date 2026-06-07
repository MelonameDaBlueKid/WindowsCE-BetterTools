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
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

using Microsoft.WindowsMobile.Forms;
using Microsoft.WindowsMobile.PocketOutlook;
using Microsoft.WindowsMobile.PocketOutlook.MessageInterception;

namespace SmsIM
{
    public partial class Form1 : Form
    {
        private MessageInterceptor interceptor;

        public Form1()
        {
            InitializeComponent();
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
                        // TODO: prompt for name from user?
                        session.Contacts.Items.Add(contact);
                    }
                    currentConv = new Conversation(contact);
                    conversations.Items.Add(currentConv);
                }
            }
            currentConv.AddToTranscript(msg.From.Name/*contact.FirstName + " " + contact.LastName*/, msg.Body);
            SwitchToConversation(currentConv);
            // Bring the app forward
            this.BringToFront();
        }

        private void Form1_Load(object sender, EventArgs e)
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

        private void txtMsgToSend_GotFocus(object sender, EventArgs e)
        {
        }

        private void Form1_Closed(object sender, EventArgs e)
        {
            interceptor.Dispose();
        }
    }
}