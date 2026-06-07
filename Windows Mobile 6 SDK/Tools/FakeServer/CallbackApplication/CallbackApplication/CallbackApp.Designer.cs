//---------------------------------------------------------------------
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
// Use of this source code is subject to the terms of the Microsoft 
// end-user license agreement (EULA) under which you licensed this
// SOFTWARE PRODUCT. If you did not accept the terms of the EULA, you 
// are not authorized to use this source code. For a copy of the EULA, 
// please see the LICENSE.RTF on your install media.
//---------------------------------------------------------------------
namespace CallbackApplication
{
    partial class CallbackApp
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;
        private System.Windows.Forms.MainMenu Start;

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
            this.Start = new System.Windows.Forms.MainMenu();
            this.StartServer = new System.Windows.Forms.MenuItem();
            this.Stop = new System.Windows.Forms.MenuItem();
            this.SuspendLayout();
            // 
            // Start
            // 
            this.Start.MenuItems.Add(this.StartServer);
            this.Start.MenuItems.Add(this.Stop);
            // 
            // StartServer
            // 
            this.StartServer.Text = "Start Server";
            this.StartServer.Click += new System.EventHandler(this.StartServer_Click);
            // 
            // Stop
            // 
            this.Stop.Enabled = false;
            this.Stop.Text = "Stop Server";
            this.Stop.Click += new System.EventHandler(this.Stop_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(96F, 96F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Dpi;
            this.AutoScroll = true;
            this.ClientSize = new System.Drawing.Size(176, 180);
            this.Menu = this.Start;
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.MenuItem StartServer;
        private System.Windows.Forms.MenuItem Stop;
    }
}

