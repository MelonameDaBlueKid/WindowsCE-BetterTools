using System;
using System.Drawing;
using System.Collections;
using System.Windows.Forms;
using System.Data;
using Microsoft.WindowsMobile.PocketOutlook;
using Microsoft.WindowsMobile.Telephony;

namespace Microsoft.WindowsMobile.Samples.ContactSample
{
    /// <summary>
    /// Summary description for Form1.
    /// </summary>
    public class ContactSelector : System.Windows.Forms.Form
    {
        private System.Windows.Forms.ListBox  listBox1;
        private System.Windows.Forms.MainMenu mainMenu1;

        private OutlookSession outlookSession;
        private System.Windows.Forms.TextBox smsText;
        private System.Windows.Forms.Button btnCallWork;
        private System.Windows.Forms.Button btnEdit;
        private System.Windows.Forms.Button btnNew;
        private System.Windows.Forms.Button btnSendSms;
        private System.Windows.Forms.Button btnClose;
        private Contact   contactToSelect;

        /// <summary>
        /// Constructor
        /// </summary>
        public ContactSelector()
        {            
            this.outlookSession = new OutlookSession();
            this.InitializeComponent();
            this.InitializeListBox();            
        }

        /// <summary>
        /// This function displays a dialog that lets the user pick a contact from a List or
        /// create a new contact. 
        /// </summary>
        /// <returns>The function returns the Contact chosen or a new Contact object if the user pressed "New" on the dialog.</returns>
        public Contact Select()
        {     
            this.ShowDialog();
            return this.contactToSelect;
            
        }

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        protected override void Dispose( bool disposing )
        {
            base.Dispose( disposing );
        }

        #region Windows Form Designer generated code
        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.mainMenu1 = new System.Windows.Forms.MainMenu();
            this.btnEdit = new System.Windows.Forms.Button();
            this.listBox1 = new System.Windows.Forms.ListBox();
            this.btnNew = new System.Windows.Forms.Button();
            this.btnSendSms = new System.Windows.Forms.Button();
            this.smsText = new System.Windows.Forms.TextBox();
            this.btnCallWork = new System.Windows.Forms.Button();
            this.btnClose = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // btnEdit
            // 
            this.btnEdit.Location = new System.Drawing.Point(158, 40);
            this.btnEdit.Name = "btnEdit";
            this.btnEdit.Size = new System.Drawing.Size(72, 24);
            this.btnEdit.TabIndex = 7;
            this.btnEdit.Text = "Edit";
            this.btnEdit.Click += new System.EventHandler(this.EditButton_Click);
            // 
            // listBox1
            // 
            this.listBox1.Location = new System.Drawing.Point(16, 10);
            this.listBox1.Name = "listBox1";
            this.listBox1.Size = new System.Drawing.Size(136, 184);
            this.listBox1.TabIndex = 6;
            // 
            // btnNew
            // 
            this.btnNew.Location = new System.Drawing.Point(158, 10);
            this.btnNew.Name = "btnNew";
            this.btnNew.Size = new System.Drawing.Size(72, 24);
            this.btnNew.TabIndex = 5;
            this.btnNew.Text = "New";
            this.btnNew.Click += new System.EventHandler(this.NewButton_Click);
            // 
            // btnSendSms
            // 
            this.btnSendSms.Location = new System.Drawing.Point(158, 100);
            this.btnSendSms.Name = "btnSendSms";
            this.btnSendSms.Size = new System.Drawing.Size(72, 24);
            this.btnSendSms.TabIndex = 4;
            this.btnSendSms.Text = "Send SMS";
            this.btnSendSms.Click += new System.EventHandler(this.SendSmsButton_Click);
            // 
            // smsText
            // 
            this.smsText.Location = new System.Drawing.Point(16, 200);
            this.smsText.Name = "smsText";
            this.smsText.Size = new System.Drawing.Size(216, 21);
            this.smsText.TabIndex = 3;
            this.smsText.Text = "Write SMS Text here.";
            // 
            // btnCallWork
            // 
            this.btnCallWork.Location = new System.Drawing.Point(158, 70);
            this.btnCallWork.Name = "btnCallWork";
            this.btnCallWork.Size = new System.Drawing.Size(72, 24);
            this.btnCallWork.TabIndex = 1;
            this.btnCallWork.Text = "Call Work";
            this.btnCallWork.Click += new System.EventHandler(this.CallWorkButton_Click);
            // 
            // btnClose
            // 
            this.btnClose.Location = new System.Drawing.Point(158, 130);
            this.btnClose.Name = "btnClose";
            this.btnClose.Size = new System.Drawing.Size(72, 24);
            this.btnClose.TabIndex = 0;
            this.btnClose.Text = "Close";
            this.btnClose.Click += new System.EventHandler(this.btnClose_Click);
            // 
            // ContactSelector
            // 
            this.ClientSize = new System.Drawing.Size(240, 256);
            this.Controls.Add(this.btnClose);
            this.Controls.Add(this.btnCallWork);
            this.Controls.Add(this.smsText);
            this.Controls.Add(this.btnSendSms);
            this.Controls.Add(this.btnNew);
            this.Controls.Add(this.listBox1);
            this.Controls.Add(this.btnEdit);
            this.KeyPreview = true;
            this.Name = "ContactSelector";
            this.Text = "Contact Selector";
            this.ResumeLayout(false);

        }

        private void InitializeListBox()
        {            
            // I assign the listBox1 to null first to Reset it.
            // This is needed as currently there is no support for BeginUpdate
            // and EndUpdate in the Compact Framework.
            this.listBox1.DataSource = null; 
            this.listBox1.DataSource = this.outlookSession.Contacts.Items;
            this.listBox1.DisplayMember = "FileAs";
            this.listBox1.ValueMember = "ItemId";
        }

        #endregion

        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        static void Main() 
        {            
            Application.Run(new ContactSelector());
        }

        /// <summary>
        /// This event handler gets called when the "New" button is pressed.
        /// It creates a new Contact object and assigns it to contactToSelect.        
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void NewButton_Click(object sender, System.EventArgs e)
        {                   
            // Add contact to the contacts folder. 
            // Just do an update once the information has been entered.
            contactToSelect = new Contact();                        
            this.outlookSession.Contacts.Items.Add(contactToSelect);
            
            // Edit the newly created contact.
            ContactEditor contactDialog = new ContactEditor();
            contactDialog.Edit(ref contactToSelect);    
         
            this.InitializeListBox();
        }

        /// <summary>
        /// This event handler gets called when the "Edit" button is pressed.
        /// It sets contactToSelect as the contact selected on the ListBox.         
        /// </summary>
        /// <param name="sender">Sender of the event.</param>
        /// <param name="e">Event arguments.</param>
        private void EditButton_Click(object sender, System.EventArgs e)
        {            
            if (this.listBox1.SelectedItem != null)
            {
                contactToSelect = (Contact)this.listBox1.SelectedItem;
            } 
            
            ContactEditor contactDialog = new ContactEditor();
            contactDialog.Edit(ref contactToSelect);
        }

        /// <summary>
        /// This will send an SMS Message.
        /// </summary>
        /// <param name="sender">Sender of the message</param>
        /// <param name="e">Event arguments.</param>
        private void SendSmsButton_Click(object sender, System.EventArgs e)
        {
           try
           {
                contactToSelect = (Contact)this.listBox1.SelectedItem;
                if (outlookSession.SmsAccount == null)
                    throw new ArgumentException("The account is not initialized");
                MessageBox.Show("Transport:"+outlookSession.SmsAccount.Name);
                SmsMessage s = new SmsMessage(contactToSelect.MobileTelephoneNumber, this.smsText.Text);
                s.Body = this.smsText.Text; //Create some input.
                s.Send();
           }
           catch (NullReferenceException except)
           {
                MessageBox.Show(except.ToString());
           }
        }
        
        /// <summary>
        /// Call BusinessTelephoneNumber
        /// </summary>
        /// <param name="sender">Sender of event.</param>
        /// <param name="e">Event Arguments</param>
        private void CallWorkButton_Click(object sender, System.EventArgs e)
        {
           contactToSelect = (Contact)this.listBox1.SelectedItem;
            Phone p = new Phone();
            p.Talk(contactToSelect.BusinessTelephoneNumber);
            
        }

        /// <summary>
        /// Close The sample.
        /// </summary>
        /// <param name="sender">Sender of Event.</param>
        /// <param name="e">Event Arguments</param>
        private void btnClose_Click(object sender, System.EventArgs e)
        {
            this.Close();
        }

    }
}
