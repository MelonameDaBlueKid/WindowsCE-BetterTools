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
using System.IO;
using System.Data;
using System.Text;
using System.Drawing;
using System.Windows.Forms;
using System.ComponentModel;
using System.Collections.Generic;
using Microsoft.WindowsMobile.Forms;
using Microsoft.WindowsMobile.PocketOutlook;

namespace Microsoft.WindowsMobile.Samples.AddPictureToContact
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void mnuChooseContact_Click(object sender, EventArgs e)
        {
            ChooseContactDialog chooseContactDialog = new ChooseContactDialog();
            SelectPictureDialog selectPictureDialog = new SelectPictureDialog();
            Contact contact = new Contact();

            this.mnuChooseContact.Enabled = false;

            // Open a PocketOutlook session
            using (OutlookSession session = new OutlookSession())
            {
                // Create a single contact
                if (session.Contacts.Items.Count <= 0)
                {
                    contact.FirstName = "Contact";
                    contact.LastName = "With Picture";
                    session.Contacts.Items.Add(contact);
                }
                else
                {
                    contact = session.Contacts.Items[0];
                }

                // Open a ChooseContactDialog and a SelectPictureDialog. If a contact was selected and a picture was chosen,
                // assign the picture to the contact.
                if ((DialogResult.OK == chooseContactDialog.ShowDialog()) && (DialogResult.OK == selectPictureDialog.ShowDialog()))
                {
                    contact.SetPicture(selectPictureDialog.FileName);
                    contact.Update();
                    contact.ShowDialog();
                }
            }

            this.mnuChooseContact.Enabled = true;
        }

        private void menuItemExit_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
