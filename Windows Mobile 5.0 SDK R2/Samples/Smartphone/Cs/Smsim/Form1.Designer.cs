namespace SmsIM
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;
        private System.Windows.Forms.MainMenu mainMenu1;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
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
			this.menuItem1 = new System.Windows.Forms.MenuItem();
			this.menuItem2 = new System.Windows.Forms.MenuItem();
			this.labelTo = new System.Windows.Forms.Label();
			this.conversations = new System.Windows.Forms.ComboBox();
			this.label1 = new System.Windows.Forms.Label();
			this.txtMsgToSend = new System.Windows.Forms.TextBox();
			this.txtConversation = new System.Windows.Forms.TextBox();
			this.SuspendLayout();
			// 
			// mainMenu1
			// 
			this.mainMenu1.MenuItems.Add(this.menuItem1);
			this.mainMenu1.MenuItems.Add(this.menuItem2);
			// 
			// menuItem1
			// 
			this.menuItem1.Text = "Add Name";
			this.menuItem1.Click += new System.EventHandler(this.menuAddName_Click);
			// 
			// menuItem2
			// 
			this.menuItem2.Text = "Send";
			this.menuItem2.Click += new System.EventHandler(this.menuSend_Click);
			// 
			// labelTo
			// 
			this.labelTo.Location = new System.Drawing.Point(4, 4);
			this.labelTo.Name = "labelTo";
			this.labelTo.Size = new System.Drawing.Size(21, 22);
			this.labelTo.Text = "To:";
			// 
			// conversations
			// 
			this.conversations.Location = new System.Drawing.Point(41, 4);
			this.conversations.Name = "conversations";
			this.conversations.Size = new System.Drawing.Size(132, 23);
			this.conversations.TabIndex = 1;
			this.conversations.SelectedIndexChanged += new System.EventHandler(this.conversations_SelectedIndexChanged);
			// 
			// label1
			// 
			this.label1.Location = new System.Drawing.Point(4, 30);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(65, 22);
			this.label1.Text = "Message:";
			// 
			// txtMsgToSend
			// 
			this.txtMsgToSend.Location = new System.Drawing.Point(4, 55);
			this.txtMsgToSend.Multiline = true;
			this.txtMsgToSend.Name = "txtMsgToSend";
			this.txtMsgToSend.Size = new System.Drawing.Size(169, 46);
			this.txtMsgToSend.TabIndex = 2;
			this.txtMsgToSend.GotFocus += new System.EventHandler(this.txtMsgToSend_GotFocus);
			// 
			// txtConversation
			// 
			this.txtConversation.Location = new System.Drawing.Point(4, 107);
			this.txtConversation.Multiline = true;
			this.txtConversation.Name = "txtConversation";
			this.txtConversation.ReadOnly = true;
			this.txtConversation.Size = new System.Drawing.Size(169, 70);
			this.txtConversation.TabIndex = 3;
			// 
			// Form1
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(96F, 96F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Dpi;
			this.ClientSize = new System.Drawing.Size(176, 180);
			this.Controls.Add(this.labelTo);
			this.Controls.Add(this.conversations);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.txtMsgToSend);
			this.Controls.Add(this.txtConversation);
			this.Menu = this.mainMenu1;
			this.Name = "Form1";
			this.Text = "SMS";
			this.Load += new System.EventHandler(this.Form1_Load);
			this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Label labelTo;
        private System.Windows.Forms.ComboBox conversations;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox txtMsgToSend;
        private System.Windows.Forms.TextBox txtConversation;
        private System.Windows.Forms.MenuItem menuItem1;
        private System.Windows.Forms.MenuItem menuItem2;
    }
}

