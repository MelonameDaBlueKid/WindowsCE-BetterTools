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
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using Microsoft.WindowsMobile.PocketOutlook;

namespace Microsoft.WindowsMobile.Samples.ContactSample
{
    /// <summary>
    /// Lets the user edit a few fields a contact object.
    /// </summary>
    public class ContactEditor : System.Windows.Forms.Form
    {
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox txtGivenName;
        private System.Windows.Forms.TextBox txtSurname;
        private System.Windows.Forms.TextBox txteMail1;
        private System.Windows.Forms.TextBox txtBusinessPhone;
        private System.Windows.Forms.Button OkButton;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox txtCustomerId;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox txtCell;
        private System.Windows.Forms.TextBox txtCompanyName;
        private System.Windows.Forms.MainMenu mainMenu1;
        private Contact contacttoCreate;

        /// <summary>
        /// Constructs a Form that can be used to Edit a POOM Contact.
        /// </summary>
        /// <param name="ctoEdit">Contact to Edit</param>
        public ContactEditor()
        {
            this.InitializeComponent();
        }

        /// <summary>
        /// Opens the Edit form for the contact passed in.
        /// </summary>
        /// <param name="contact">Contact to Edit.</param>
        public void Edit(ref Contact contact)
        {
            this.contacttoCreate = contact;
            this.ShowDialog();
        }

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if this class has already started disposing, false otherwise</param>
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
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.txtGivenName = new System.Windows.Forms.TextBox();
            this.txtSurname = new System.Windows.Forms.TextBox();
            this.txtCompanyName = new System.Windows.Forms.TextBox();
            this.txteMail1 = new System.Windows.Forms.TextBox();
            this.txtBusinessPhone = new System.Windows.Forms.TextBox();
            this.OkButton = new System.Windows.Forms.Button();
            this.label6 = new System.Windows.Forms.Label();
            this.txtCustomerId = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.txtCell = new System.Windows.Forms.TextBox();
            this.mainMenu1 = new System.Windows.Forms.MainMenu();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.Font = new System.Drawing.Font("Tahoma", 8F, System.Drawing.FontStyle.Regular);
            this.label1.Location = new System.Drawing.Point(4, 16);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(70, 17);
            this.label1.Text = "First Name";
            // 
            // label2
            // 
            this.label2.Font = new System.Drawing.Font("Tahoma", 8F, System.Drawing.FontStyle.Regular);
            this.label2.Location = new System.Drawing.Point(4, 39);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(70, 14);
            this.label2.Text = "Last Name";
            // 
            // label3
            // 
            this.label3.Font = new System.Drawing.Font("Tahoma", 8F, System.Drawing.FontStyle.Regular);
            this.label3.Location = new System.Drawing.Point(4, 64);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(70, 16);
            this.label3.Text = "Company";
            // 
            // label4
            // 
            this.label4.Font = new System.Drawing.Font("Tahoma", 8F, System.Drawing.FontStyle.Regular);
            this.label4.Location = new System.Drawing.Point(4, 112);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(70, 17);
            this.label4.Text = "Email1";
            // 
            // label5
            // 
            this.label5.Font = new System.Drawing.Font("Tahoma", 8F, System.Drawing.FontStyle.Regular);
            this.label5.Location = new System.Drawing.Point(4, 89);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(70, 17);
            this.label5.Text = "Work Phone";
            // 
            // txtGivenName
            // 
            this.txtGivenName.Location = new System.Drawing.Point(80, 16);
            this.txtGivenName.Name = "txtGivenName";
            this.txtGivenName.Size = new System.Drawing.Size(144, 21);
            this.txtGivenName.TabIndex = 7;
            // 
            // txtSurname
            // 
            this.txtSurname.Location = new System.Drawing.Point(80, 40);
            this.txtSurname.Name = "txtSurname";
            this.txtSurname.Size = new System.Drawing.Size(144, 21);
            this.txtSurname.TabIndex = 8;
            // 
            // txtCompanyName
            // 
            this.txtCompanyName.Location = new System.Drawing.Point(80, 64);
            this.txtCompanyName.Name = "txtCompanyName";
            this.txtCompanyName.Size = new System.Drawing.Size(144, 21);
            this.txtCompanyName.TabIndex = 9;
            // 
            // txteMail1
            // 
            this.txteMail1.Location = new System.Drawing.Point(80, 112);
            this.txteMail1.Name = "txteMail1";
            this.txteMail1.Size = new System.Drawing.Size(144, 21);
            this.txteMail1.TabIndex = 11;
            // 
            // txtBusinessPhone
            // 
            this.txtBusinessPhone.Location = new System.Drawing.Point(80, 88);
            this.txtBusinessPhone.Name = "txtBusinessPhone";
            this.txtBusinessPhone.Size = new System.Drawing.Size(144, 21);
            this.txtBusinessPhone.TabIndex = 10;
            // 
            // OkButton
            // 
            this.OkButton.Location = new System.Drawing.Point(152, 192);
            this.OkButton.Name = "OkButton";
            this.OkButton.Size = new System.Drawing.Size(72, 32);
            this.OkButton.TabIndex = 14;
            this.OkButton.Text = "OK";
            this.OkButton.Click += new System.EventHandler(this.OkButton_Click);
            // 
            // label6
            // 
            this.label6.Font = new System.Drawing.Font("Tahoma", 8F, System.Drawing.FontStyle.Regular);
            this.label6.Location = new System.Drawing.Point(4, 133);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(70, 21);
            this.label6.Text = "CustomerId";
            // 
            // txtCustomerId
            // 
            this.txtCustomerId.Location = new System.Drawing.Point(80, 136);
            this.txtCustomerId.Name = "txtCustomerId";
            this.txtCustomerId.Size = new System.Drawing.Size(144, 21);
            this.txtCustomerId.TabIndex = 12;
            // 
            // label7
            // 
            this.label7.Font = new System.Drawing.Font("Tahoma", 8F, System.Drawing.FontStyle.Regular);
            this.label7.Location = new System.Drawing.Point(4, 160);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(70, 21);
            this.label7.Text = "Mobile";
            // 
            // txtCell
            // 
            this.txtCell.Location = new System.Drawing.Point(80, 160);
            this.txtCell.Name = "txtCell";
            this.txtCell.Size = new System.Drawing.Size(144, 21);
            this.txtCell.TabIndex = 13;
            // 
            // ContactEditor
            // 
            this.ClientSize = new System.Drawing.Size(240, 268);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.txtGivenName);
            this.Controls.Add(this.txtSurname);
            this.Controls.Add(this.txtCompanyName);
            this.Controls.Add(this.txtBusinessPhone);
            this.Controls.Add(this.txteMail1);
            this.Controls.Add(this.txtCustomerId);
            this.Controls.Add(this.txtCell);
            this.Controls.Add(this.OkButton);
            this.Menu = this.mainMenu1;
            this.MinimizeBox = false;
            this.Name = "ContactEditor";
            this.Text = "Contact Editor";
            this.Load += new System.EventHandler(this.ContactEditor_Load);
            this.ResumeLayout(false);

        }
        #endregion

        /// <summary>
        /// Loads a new contact and bind the data of the contact to the form.
        /// Notice that this function is a delegate of the event handler this.Load.
        /// </summary>
        /// <param name="sender">sender</param>
        /// <param name="e">Event arguments</param>
        private void ContactEditor_Load(object sender, System.EventArgs e)
        {
            this.txtGivenName.DataBindings.Add("text", this.contacttoCreate, "FirstName");
            this.txtSurname.DataBindings.Add("text", this.contacttoCreate, "LastName");
            this.txtCompanyName.DataBindings.Add("text", this.contacttoCreate , "CompanyName");
            this.txteMail1.DataBindings.Add("text", this.contacttoCreate, "Email1Address");
            this.txtBusinessPhone.DataBindings.Add("text", this.contacttoCreate, "BusinessTelephoneNumber");
            this.txtCustomerId.DataBindings.Add("text", this.contacttoCreate, "CustomerId");
            this.txtCell.DataBindings.Add("text", this.contacttoCreate, "MobileTelephoneNumber");
        }

        /// <summary>
        /// This event hander gets triggered when the user presses the "OK" button on the Contact Editor dialog.
        /// Sets the FileAs field as 'LastName, FirstName' and updates the Contact. 
        /// It closes the contact Editor dialog form.
        /// </summary>
        /// <param name="sender">Sender of the Event.</param>
        /// <param name="e">Event arguments.</param>
        private void OkButton_Click(object sender, System.EventArgs e)
        {
            this.contacttoCreate.FileAs=this.contacttoCreate.LastName + ", " + this.contacttoCreate.FirstName;
            this.contacttoCreate.Update();
            this.Close();
        }
    }
}
