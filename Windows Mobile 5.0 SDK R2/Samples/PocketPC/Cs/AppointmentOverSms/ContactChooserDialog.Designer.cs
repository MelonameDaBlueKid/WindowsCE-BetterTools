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

namespace AppointmentOverSms
{
    public partial class ContactChooserDialog : System.Windows.Forms.Form
    {
        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.mainMenu1 = new System.Windows.Forms.MainMenu();
            this.contactListView = new Microsoft.WindowsMobile.Samples.ControlLibrary.ContactListView();
            this.SuspendLayout();
// 
// contactListView
// 
            this.contactListView.Location = new System.Drawing.Point(8, 16);
            this.contactListView.Name = "smartControl1";
            this.contactListView.Size = new System.Drawing.Size(224, 232);
// 
// Form1
// 
            this.ClientSize = new System.Drawing.Size(240, 268);
            this.Controls.Add(this.contactListView);
            this.Menu = this.mainMenu1;
            this.Name = "Choose contact";
            this.Text = "Choose contact";
            this.ResumeLayout(false);

        }

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        protected override void Dispose(bool disposing)
        {
            base.Dispose(disposing);
        }

        private Microsoft.WindowsMobile.Samples.ControlLibrary.ContactListView contactListView;
    }
}