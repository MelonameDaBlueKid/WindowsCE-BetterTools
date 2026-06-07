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
#region Using directives

using System;
using System.Drawing;
using System.Collections;
using System.Windows.Forms;
using System.Data;

#endregion
using Microsoft.WindowsMobile.PocketOutlook.MessageInterception;
using Microsoft.WindowsMobile.Status;

namespace PhoneFinder
{
    /// <summary>
    /// Summary description for form.
    /// </summary>
    public class PhoneFinderForm : System.Windows.Forms.Form
    {
        private Label label1;
        private MenuItem exitMenuItem;
        /// <summary>
        /// Main menu for the form.
        /// </summary>
        private System.Windows.Forms.MainMenu mainMenu1;

        const string ruleName = "Microsoft.PhoneFinder";   // name of the MessageInterceptor rule we will use
        const string soundFile = "\\Program Files\\PhoneFinder\\overhere.wav"; // sound to play when event raised
        MessageInterceptor interceptor;

        private TextBox pin;
        private Label label2;
        private CheckBox enabledCheckBox;

        #region PlaySound
        // To play a sound, we need to PInvoke into coredll.dll and call PlaySound
        [System.Runtime.InteropServices.DllImport("coredll.dll")]
        static extern int PlaySound(string pszSound, IntPtr hMod, int fdwSound);

        const int SND_FILENAME = 0x20000;
        const int SND_SYNC = 0x0;
        const int SND_ASYNC = 0x1;
        const int SND_LOOP = 0x8;
        #endregion

        public PhoneFinderForm()
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(PhoneFinderForm));
            this.mainMenu1 = new System.Windows.Forms.MainMenu();
            this.exitMenuItem = new System.Windows.Forms.MenuItem();
            this.label1 = new System.Windows.Forms.Label();
            this.pin = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.enabledCheckBox = new System.Windows.Forms.CheckBox();
            // 
            // mainMenu1
            // 
            this.mainMenu1.MenuItems.Add(this.exitMenuItem);
            // 
            // exitMenuItem
            // 
            this.exitMenuItem.Text = "Exit";
            this.exitMenuItem.Click += new System.EventHandler(this.exitMenuItem_Click);
            // 
            // label1
            // 
            this.label1.Location = new System.Drawing.Point(4, 4);
            this.label1.Size = new System.Drawing.Size(169, 20);
            this.label1.Text = "Phone Finder";
            this.label1.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // pin
            // 
            this.pin.Location = new System.Drawing.Point(4, 68);
            this.pin.Size = new System.Drawing.Size(152, 24);
            this.pin.Text = "1234";
            // 
            // label2
            // 
            this.label2.Location = new System.Drawing.Point(4, 43);
            this.label2.Size = new System.Drawing.Size(152, 22);
            this.label2.Text = "Pin:";
            // 
            // enabledCheckBox
            // 
            this.enabledCheckBox.Location = new System.Drawing.Point(4, 108);
            this.enabledCheckBox.Size = new System.Drawing.Size(152, 22);
            this.enabledCheckBox.Text = "Enabled";
            // 
            // PhoneFinderForm
            // 
            this.ClientSize = new System.Drawing.Size(176, 180);
            this.Controls.Add(this.enabledCheckBox);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.pin);
            this.Controls.Add(this.label2);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Menu = this.mainMenu1;
            this.Text = "Phone Finder";
            this.Load += new System.EventHandler(this.Form1_Load);

        }

        #endregion

        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        static void Main()
        {
            Application.Run(new PhoneFinderForm());
        }

        /// <summary>
        /// Called when the user chooses to exit the application
        /// </summary>
        /// <param name="sender">object that raised the event</param>
        /// <param name="e">event arguments</param>
        private void exitMenuItem_Click(object sender, EventArgs e)
        {
            if (enabledCheckBox.Checked)
            {
                // the user wants Phone Finder to be enabled, so let's enable it
                try
                {
                    // need to enable the MessageInterceptor
                    interceptor = new MessageInterceptor(InterceptionAction.NotifyAndDelete);
                    interceptor.MessageCondition = new MessageCondition();
                    interceptor.MessageCondition.CaseSensitive = true;
                    interceptor.MessageCondition.ComparisonType = MessagePropertyComparisonType.Equal;
                    interceptor.MessageCondition.ComparisonValue = pin.Text;
                    interceptor.MessageCondition.Property = MessageProperty.Body;
                    interceptor.EnableApplicationLauncher(ruleName);
                }
                catch (Microsoft.WindowsMobile.PocketOutlook.PocketOutlookException ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }
            else
            {
                // Phone Finder is disabled, disable the event
                if (interceptor != null)
                {
                    interceptor.DisableApplicationLauncher();
                }
            }

            Close();
        }

        /// <summary>
        /// Method that is called with the main form is loaded.  On loading of the 
        /// form, the app tests for a MessageInterceptor that has previously been
        /// set up using the same unique name for the rule.  If so, it loads the data.
        /// </summary>
        /// <param name="sender">object that raised the event</param>
        /// <param name="e">event arguments</param>
        private void Form1_Load(object sender, EventArgs e)
        {
            // Test to see if Phone Finder is enabled
            if (MessageInterceptor.IsApplicationLauncherEnabled(ruleName))
            {
                // we have already enabled Phone Finder

                // load the event data into the MessageInterceptor and hook up our event
                interceptor = new MessageInterceptor(ruleName);
                interceptor.MessageReceived += new MessageInterceptorEventHandler(interceptor_MessageReceived);

                // set the pin to the value the user set and show that Phone Finder is enabled
                pin.Text = interceptor.MessageCondition.ComparisonValue;
                enabledCheckBox.Checked = true;
            }
            else
            {
                enabledCheckBox.Checked = false;
            }

        }

        /// <summary>
        /// The event code that is called when an SMS with exactly the PIN 
        /// specified by the user is received.
        /// </summary>
        /// <param name="sender">object that raised the event</param>
        /// <param name="e">event arguments</param>
        void interceptor_MessageReceived(object sender, MessageInterceptorEventArgs e)
        {
            // Play the sound in a loop
            PlaySound(soundFile, IntPtr.Zero, SND_FILENAME | SND_ASYNC | SND_LOOP);

            // While playing the sound, display owner information if we have it.

            // get the owner name, otherwise default to "the owner"
            string owner = SystemState.OwnerName;
            if (owner.Length == 0)
            {
                owner = "the owner";
            }

            // build the message to display on the phone
            string message = owner + " is looking for his/her phone.  ";
            message += "If you have found this phone, please contact " + owner + ". ";

            // look to see if we have contact information for the owner.  
            // if we do, then we'll display the ways the owner can be contacted.
            string email = SystemState.OwnerEmail;
            string phone = SystemState.OwnerPhoneNumber;

            if (phone.Length > 0 || email.Length > 0)
            {
                message += "You can contact " + owner + " via the following: \n";
            }

            if (phone.Length > 0)
            {
                message += phone + "\n";
            }

            if (email.Length > 0)
            {
                message += email + "\n";
            }

            // Show the message
            MessageBox.Show(message);

            // The message box has been dismissed, stop the sound and exit
            PlaySound(null, IntPtr.Zero, 0);
            Close();
        }

    }
}

