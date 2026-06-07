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

namespace AppointmentOverSms
{
    /// <summary>
    /// ContactChooserDialog lets the user select a contact.
    /// </summary>
    public partial class ContactChooserDialog : System.Windows.Forms.Form
    {
        private System.Windows.Forms.MainMenu mainMenu1;

        #region Private Variables
        private AppointmentDetails parent;
        #endregion

        /// <summary>
        /// Set the parent for sending the contact picked
        /// </summary>
        /// <param name="parent"> The form that called this constructor</param>
        public ContactChooserDialog(AppointmentDetails parent)
        {
            InitializeComponent();

            this.parent = parent;

            // Initialize PimItemListView.
            this.contactListView.PimItemProperty1 = ContactProperty.FileAs;
            this.contactListView.PimItemProperty2 = ContactProperty.MobileTelephoneNumber;
            this.contactListView.ShowPicture = true;
            contactListView.PimItemSelected += new PimItemListView.ClickEventHandler(Clicked);
            OutlookSession mySession = new OutlookSession();

            // Only display the contacts that have a mobile telephone number.
            contactListView.Contacts = mySession.Contacts.Items.Restrict("[MobileTelephoneNumber] <> \"\"");
        }

        /// <summary>
        /// Sends the contact selected by the user to the parent.
        /// </summary>
        /// <param name="sender">Sender</param>
        /// <param name="pimItemEventArgs">The event arguments that contain the contact selected</param>
        private void Clicked(object sender, PimItemListView.PimItemListViewEventArgs pimItemEventArgs)
        {
            parent.ContactPhone = ((Contact)pimItemEventArgs.PimItem).MobileTelephoneNumber;
            contactListView.Dispose();
            this.Close();
        }

    }
}