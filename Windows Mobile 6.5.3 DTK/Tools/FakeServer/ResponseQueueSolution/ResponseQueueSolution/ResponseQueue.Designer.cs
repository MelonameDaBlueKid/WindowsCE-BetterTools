//---------------------------------------------------------------------
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
// Use of this source code is subject to the terms of the Microsoft 
// end-user license agreement (EULA) under which you licensed this
// SOFTWARE PRODUCT. If you did not accept the terms of the EULA, you 
// are not authorized to use this source code. For a copy of the EULA, 
// please see the LICENSE.RTF on your install media.
//---------------------------------------------------------------------

namespace ResponseQueueSolution
{
    partial class ResponseQueue
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
            this.ConnectButton = new System.Windows.Forms.MenuItem();
            this.DisconnectButton = new System.Windows.Forms.MenuItem();
            this.SuspendLayout();
            // 
            // mainMenu1
            // 
            this.mainMenu1.MenuItems.Add(this.ConnectButton);
            this.mainMenu1.MenuItems.Add(this.DisconnectButton);
            // 
            // ConnectButton
            // 
            this.ConnectButton.Text = "Connect";
            this.ConnectButton.Click += new System.EventHandler(this.ConnectButton_Click);
            // 
            // DisconnectButton
            // 
            this.DisconnectButton.Enabled = false;
            this.DisconnectButton.Text = "Disconnect";
            this.DisconnectButton.Click += new System.EventHandler(this.DisconnectButton_Click);
            // 
            // ResponseQueue
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(96F, 96F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Dpi;
            this.AutoScroll = true;
            this.ClientSize = new System.Drawing.Size(320, 188);
            this.Menu = this.mainMenu1;
            this.Name = "ResponseQueue";
            this.Text = "Form1";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.MenuItem ConnectButton;
        private System.Windows.Forms.MenuItem DisconnectButton;
    }
}

