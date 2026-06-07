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
/*=====================================================================
  File:      MainForm.cs
=====================================================================*/

using System;
using System.Collections;
using System.Drawing;
using System.Windows.Forms;

namespace WebCrawler
{
    /// <summary>
    /// Main application form class
    /// </summary>
    public class MainForm : System.Windows.Forms.Form
    {
        protected void Portrait()
        {
            this.crawlTime.Location = new System.Drawing.Point(88, 216);
            this.crawlTime.Size = new System.Drawing.Size(136, 16);
            this.crawlTimeLabel.Location = new System.Drawing.Point(10, 216);
            this.crawlTimeLabel.Size = new System.Drawing.Size(64, 16);
            this.crawlStartTime.Location = new System.Drawing.Point(88, 200);
            this.crawlStartTime.Size = new System.Drawing.Size(136, 16);
            this.crawlStartedLabel.Location = new System.Drawing.Point(10, 200);
            this.crawlStartedLabel.Size = new System.Drawing.Size(64, 16);
            this.light1.Location = new System.Drawing.Point(208, 66);
            this.light1.Size = new System.Drawing.Size(16, 16);
            this.light0.Location = new System.Drawing.Point(192, 66);
            this.light0.Size = new System.Drawing.Size(16, 16);
            this.linkCount.Location = new System.Drawing.Point(88, 182);
            this.linkCount.Size = new System.Drawing.Size(136, 16);
            this.linkCountLabel.Location = new System.Drawing.Point(10, 182);
            this.linkCountLabel.Size = new System.Drawing.Size(64, 16);
            this.currentPageBox.Location = new System.Drawing.Point(10, 84);
            this.currentPageBox.Size = new System.Drawing.Size(214, 90);
            this.currentPageLabel.Location = new System.Drawing.Point(10, 68);
            this.currentPageLabel.Size = new System.Drawing.Size(100, 16);
            this.addressLabel.Location = new System.Drawing.Point(10, 4);
            this.addressLabel.Size = new System.Drawing.Size(214, 16);
            this.noProxyCheck.Location = new System.Drawing.Point(10, 48);
            this.noProxyCheck.Size = new System.Drawing.Size(214, 20);
            this.startButton.Location = new System.Drawing.Point(8, 240);
            this.startButton.Size = new System.Drawing.Size(216, 20);
            this.addressBox.Location = new System.Drawing.Point(10, 24);
            this.addressBox.Size = new System.Drawing.Size(214, 22);
        }
    
        protected void Landscape()
        {
            this.crawlTime.Location = new System.Drawing.Point(216, 136);
            this.crawlTime.Size = new System.Drawing.Size(96, 16);
            this.crawlTimeLabel.Location = new System.Drawing.Point(160, 136);
            this.crawlTimeLabel.Size = new System.Drawing.Size(48, 16);
            this.crawlStartTime.Location = new System.Drawing.Point(64, 120);
            this.crawlStartTime.Size = new System.Drawing.Size(248, 16);
            this.crawlStartedLabel.Location = new System.Drawing.Point(8, 120);
            this.crawlStartedLabel.Size = new System.Drawing.Size(48, 16);
            this.light1.Location = new System.Drawing.Point(296, 48);
            this.light1.Size = new System.Drawing.Size(16, 16);
            this.light0.Location = new System.Drawing.Point(280, 48);
            this.light0.Size = new System.Drawing.Size(16, 16);
            this.linkCount.Location = new System.Drawing.Point(80, 136);
            this.linkCount.Size = new System.Drawing.Size(72, 16);
            this.linkCountLabel.Location = new System.Drawing.Point(8, 136);
            this.linkCountLabel.Size = new System.Drawing.Size(64, 16);
            this.currentPageBox.Location = new System.Drawing.Point(10, 64);
            this.currentPageBox.Size = new System.Drawing.Size(302, 48);
            this.currentPageLabel.Location = new System.Drawing.Point(10, 48);
            this.currentPageLabel.Size = new System.Drawing.Size(100, 16);
            this.addressLabel.Location = new System.Drawing.Point(10, 4);
            this.addressLabel.Size = new System.Drawing.Size(50, 16);
            this.noProxyCheck.Location = new System.Drawing.Point(168, 16);
            this.noProxyCheck.Size = new System.Drawing.Size(152, 24);
            this.startButton.Location = new System.Drawing.Point(8, 160);
            this.startButton.Size = new System.Drawing.Size(304, 20);
            this.addressBox.Location = new System.Drawing.Point(10, 20);
            this.addressBox.Size = new System.Drawing.Size(150, 22);
        }
            
        

        /// <summary>
        /// Form controls
        /// </summary>
        private System.Windows.Forms.TextBox addressBox;
        private System.Windows.Forms.Button startButton;
        private System.Windows.Forms.Label addressLabel;
        private System.Windows.Forms.Label currentPageLabel;
        private System.Windows.Forms.TextBox currentPageBox;
        private System.Windows.Forms.Label linkCountLabel;
        private System.Windows.Forms.Label linkCount;
        private System.Windows.Forms.MainMenu appMenu;
        private System.Windows.Forms.PictureBox light0;
        private System.Windows.Forms.PictureBox light1;
        private System.Windows.Forms.CheckBox noProxyCheck;
        private System.Windows.Forms.Label crawlStartedLabel;
        private System.Windows.Forms.Label crawlStartTime;
        private System.Windows.Forms.Label crawlTimeLabel;
        private System.Windows.Forms.Label crawlTime;
        
        /// <summary>
        /// These are used to handle status updates.
        /// </summary>
        private string CurrentPageText = "";

        /// <summary>
        /// The form's thread
        /// </summary>
        private readonly System.Threading.Thread FormThread = System.Threading.Thread.CurrentThread;
        
        /// <summary>
        /// The crawler worker object
        /// </summary>
        private Crawler crawler = null;
        
        /// <summary>
        /// Is the crawler currently running?
        /// </summary>
        private bool Running = false;

        /// <summary>
        /// The time the current crawl started
        /// </summary>
        private DateTime CrawlStart = DateTime.MinValue;
        
        /// <summary>
        /// Timer to handle blinking the activity lights
        /// </summary>
        private Timer ActivityLightsTimer = null;
        
        /// <summary>
        /// Activity lights components and state
        /// </summary>
        private Bitmap BmpOff = WebCrawler.Resources.DarkGreen;
        private Bitmap BmpOn = WebCrawler.Resources.Green;
        private bool light0State = false;
        private bool light1State = false;
        
        /// <summary>
        /// Constructor
        /// </summary>
        public MainForm()
        {
            //
            // Required for Windows Form Designer support
            //
            InitializeComponent();
            
            // set the initial light images
            this.light0.Image = this.BmpOff;
            this.light1.Image = this.BmpOff;
            
            // create the actvity lights timer
            this.ActivityLightsTimer = new Timer();
            this.ActivityLightsTimer.Interval = 1000;
            this.ActivityLightsTimer.Enabled = false;
            this.ActivityLightsTimer.Tick += new EventHandler(HandleActivityLightsEvent);
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
            this.addressBox = new System.Windows.Forms.TextBox();
            this.startButton = new System.Windows.Forms.Button();
            this.addressLabel = new System.Windows.Forms.Label();
            this.appMenu = new System.Windows.Forms.MainMenu();
            this.currentPageLabel = new System.Windows.Forms.Label();
            this.currentPageBox = new System.Windows.Forms.TextBox();
            this.linkCountLabel = new System.Windows.Forms.Label();
            this.linkCount = new System.Windows.Forms.Label();
            this.light0 = new System.Windows.Forms.PictureBox();
            this.light1 = new System.Windows.Forms.PictureBox();
            this.noProxyCheck = new System.Windows.Forms.CheckBox();
            this.crawlStartedLabel = new System.Windows.Forms.Label();
            this.crawlStartTime = new System.Windows.Forms.Label();
            this.crawlTimeLabel = new System.Windows.Forms.Label();
            this.crawlTime = new System.Windows.Forms.Label();
            this.SuspendLayout();
// 
// addressBox
// 
            this.addressBox.Location = new System.Drawing.Point(10, 24);
            this.addressBox.Name = "addressBox";
            this.addressBox.ScrollBars = System.Windows.Forms.ScrollBars.None;
            this.addressBox.Size = new System.Drawing.Size(214, 21);
            this.addressBox.TabIndex = 13;
// 
// startButton
// 
            this.startButton.Location = new System.Drawing.Point(8, 240);
            this.startButton.Name = "startButton";
            this.startButton.Size = new System.Drawing.Size(216, 20);
            this.startButton.TabIndex = 12;
            this.startButton.Text = "Start";
            this.startButton.Click += new System.EventHandler(this.startButton_Click);
// 
// addressLabel
// 
            this.addressLabel.Location = new System.Drawing.Point(10, 4);
            this.addressLabel.Name = "addressLabel";
            this.addressLabel.Size = new System.Drawing.Size(214, 16);
            this.addressLabel.Text = "Address";
// 
// currentPageLabel
// 
            this.currentPageLabel.Location = new System.Drawing.Point(10, 68);
            this.currentPageLabel.Name = "currentPageLabel";
            this.currentPageLabel.Size = new System.Drawing.Size(100, 16);
            this.currentPageLabel.Text = "Current Page";
// 
// currentPageBox
// 
            this.currentPageBox.Location = new System.Drawing.Point(10, 84);
            this.currentPageBox.Multiline = true;
            this.currentPageBox.Name = "currentPageBox";
            this.currentPageBox.ReadOnly = true;
            this.currentPageBox.ScrollBars = System.Windows.Forms.ScrollBars.None;
            this.currentPageBox.Size = new System.Drawing.Size(214, 90);
            this.currentPageBox.TabIndex = 8;
// 
// linkCountLabel
// 
            this.linkCountLabel.Location = new System.Drawing.Point(10, 182);
            this.linkCountLabel.Name = "linkCountLabel";
            this.linkCountLabel.Size = new System.Drawing.Size(64, 16);
            this.linkCountLabel.Text = "Link count : ";
// 
// linkCount
// 
            this.linkCount.Location = new System.Drawing.Point(88, 182);
            this.linkCount.Name = "linkCount";
            this.linkCount.Size = new System.Drawing.Size(136, 16);
            this.linkCount.Text = "0";
            this.linkCount.TextAlign = System.Drawing.ContentAlignment.TopRight;
// 
// light0
// 
            this.light0.Location = new System.Drawing.Point(192, 66);
            this.light0.Name = "light0";
            this.light0.Size = new System.Drawing.Size(16, 16);
// 
// light1
// 
            this.light1.Location = new System.Drawing.Point(208, 66);
            this.light1.Name = "light1";
            this.light1.Size = new System.Drawing.Size(16, 16);
// 
// noProxyCheck
// 
            this.noProxyCheck.Location = new System.Drawing.Point(10, 48);
            this.noProxyCheck.Name = "noProxyCheck";
            this.noProxyCheck.Size = new System.Drawing.Size(214, 20);
            this.noProxyCheck.TabIndex = 11;
            this.noProxyCheck.Text = "Do not use proxy server";
// 
// crawlStartedLabel
// 
            this.crawlStartedLabel.Location = new System.Drawing.Point(10, 200);
            this.crawlStartedLabel.Name = "crawlStartedLabel";
            this.crawlStartedLabel.Size = new System.Drawing.Size(64, 16);
            this.crawlStartedLabel.Text = "Started:";
// 
// crawlStartTime
// 
            this.crawlStartTime.Location = new System.Drawing.Point(88, 200);
            this.crawlStartTime.Name = "crawlStartTime";
            this.crawlStartTime.Size = new System.Drawing.Size(136, 16);
            this.crawlStartTime.TextAlign = System.Drawing.ContentAlignment.TopRight;
// 
// crawlTimeLabel
// 
            this.crawlTimeLabel.Location = new System.Drawing.Point(10, 216);
            this.crawlTimeLabel.Name = "crawlTimeLabel";
            this.crawlTimeLabel.Size = new System.Drawing.Size(64, 16);
            this.crawlTimeLabel.Text = "Time:";
// 
// crawlTime
// 
            this.crawlTime.Location = new System.Drawing.Point(88, 216);
            this.crawlTime.Name = "crawlTime";
            this.crawlTime.Size = new System.Drawing.Size(136, 16);
            this.crawlTime.TextAlign = System.Drawing.ContentAlignment.TopRight;
// 
// MainForm
// 
            this.ClientSize = new System.Drawing.Size(240, 268);
            this.Controls.Add(this.crawlTime);
            this.Controls.Add(this.crawlTimeLabel);
            this.Controls.Add(this.crawlStartTime);
            this.Controls.Add(this.crawlStartedLabel);
            this.Controls.Add(this.light1);
            this.Controls.Add(this.light0);
            this.Controls.Add(this.linkCount);
            this.Controls.Add(this.linkCountLabel);
            this.Controls.Add(this.currentPageBox);
            this.Controls.Add(this.currentPageLabel);
            this.Controls.Add(this.addressLabel);
            this.Controls.Add(this.noProxyCheck);
            this.Controls.Add(this.startButton);
            this.Controls.Add(this.addressBox);
            this.KeyPreview = true;
            this.Menu = this.appMenu;
            this.Name = "MainForm";
            this.Text = ".NETCF Web Crawler";
            this.Resize += new System.EventHandler(this.MainForm_Resize);
            this.ResumeLayout(false);
        }
        #endregion

        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        static void Main() 
        {
            Application.Run(new MainForm());
        }

        /// <summary>
        /// Click event handler for the Start/Stop button
        /// </summary>
        private void startButton_Click(object sender, System.EventArgs e)
        {
            if(!this.Running)
            {
                this.Running = true;
                
                // get form control states
                bool noProxy = this.noProxyCheck.Checked;
                string startingPage = this.addressBox.Text;
                
                // disable form controls
                this.addressLabel.Enabled = false;
                this.addressBox.Enabled = false;
                this.noProxyCheck.Enabled = false;
                
                // update form control text
                this.startButton.Text = "Stop";
                
                // create our crawler object
                this.crawler = new Crawler(startingPage,
                                        noProxy);
                
                // register our event handlers
                this.crawler.CurrentPageEvent += new Crawler.CurrentPage(this.HandleCurrentPageEvent);
                this.crawler.PageFoundEvent += new EventHandler(this.HandlePageFoundEvent);
                this.crawler.CrawlFinishedEvent += new EventHandler(this.HandleCrawlFinishedEvent);
                
                // get the activity lights blinking
                this.ActivityLightsTimer.Enabled = true;
                
                // start the crawl
                this.linkCount.Text = "0";
                this.crawlTime.Text = "0000:00:00:00";
                this.CrawlStart = DateTime.Now;
                this.crawlStartTime.Text = this.CrawlStart.ToString();
                this.crawler.Start();
                
            }
            else
            {
                // we've been asked to stop
                this.crawler.Stop();
                
                // disable the start/stop button 
                //  we don't want it clicked more than once
                this.startButton.Text = "Please wait, crawler stopping";
                this.startButton.Enabled = false;
            }
        }                                                        

        /// <summary>
        /// Process CurrentPage events
        /// </summary>
        /// <param name="currentPage">
        /// Text to display in the Current Page box
        /// </param>
        private void HandleCurrentPageEvent(string currentPage)
        {
            // since the .NET Compact Framework does not provide an instance of 
            //  Control.Invoke that accepts parameter data, store the current page
            //  value in a class global variable
            lock(this)
            {
                this.CurrentPageText = currentPage;
            }
            
            // check to see if we have been called on our creation thread
            if(CustomInvokeRequired())
            {
                this.currentPageBox.Invoke(new EventHandler(this.HandleCurrentPageEvent));
                return;
            }
            
            // invoke was not required, directly update the value
            this.currentPageBox.Text = currentPage;
        }
        
        /// <summary>
        /// Process CurrentPage events.  This implementation sets the text to 
        //  the value stored in the class global variable CurrentPageText
        /// </summary>
        private void HandleCurrentPageEvent(object sender, EventArgs e)
        {
            // check to see if we have been called on our creation thread
            if(CustomInvokeRequired())
            {
                this.currentPageBox.Invoke(new EventHandler(this.HandleCurrentPageEvent));
                return;
            }
            this.currentPageBox.Text = this.CurrentPageText;
        }
        
        /// <summary>
        /// Process PageFound events
        /// </summary>
        private void HandlePageFoundEvent(object sender, EventArgs e)
        {
            if(CustomInvokeRequired())
            {
                this.linkCount.Invoke(new EventHandler(this.HandlePageFoundEvent));
                return;
            }
            
            try
            {
                this.linkCount.Text = string.Format("{0}", Int32.Parse(this.linkCount.Text)+1);
            }
            catch(FormatException)
            { }
        }
        
        /// <summary>
        /// Process CrawlFinished events
        /// </summary>
        private void HandleCrawlFinishedEvent(object sender, EventArgs e)
        {
            if(CustomInvokeRequired())
            {
                this.linkCount.Invoke(new EventHandler(this.HandleCrawlFinishedEvent));
                return;
            }
            
            this.Running = false;
            this.crawler = null;
            
            if(null == this.crawler)
            {
                this.startButton.Text = "Start";
            }
            
            // re-enable form controls
            this.addressLabel.Enabled = true;
            this.addressBox.Enabled = true;
            this.noProxyCheck.Enabled = true;
            this.startButton.Enabled = true;
            
            // stop the blinking lights
            this.ActivityLightsTimer.Enabled = false;
            this.light0State = false;
            this.light1State = false;
            this.light0.Image = this.BmpOff;
            this.light1.Image = this.BmpOff;
        }

        /// <summary>
        /// Process ActivityLights events
        /// </summary>
        private void HandleActivityLightsEvent(object unused,
                                            EventArgs notused)
        {
            this.light0State = !this.light0State;
            this.light1State = !this.light1State;
            if(this.light0State)
            {
                // turn off light0
                this.light0.Image = this.BmpOff;
                // turn on light1
                this.light1.Image = this.BmpOn;
            }
            else
            {
                // turn off light1
                this.light1.Image = this.BmpOff;
                // turn on light0
                this.light0.Image = this.BmpOn;
            }
            
            // update run time display
            TimeSpan runTime = DateTime.Now - this.CrawlStart;
            this.crawlTime.Text = string.Format("{0:D4}:{1:D2}:{2:D2}:{3:D2}",
                                            runTime.Days,
                                            runTime.Hours,
                                            runTime.Minutes,
                                            runTime.Seconds);
        }

        /// <summary>
        /// Determine if the call that we are servicing came in on this form's thread.
        /// <para>
        /// The .NET Compact Framework does not provide an implementation for Control.InvokeRequired(),
        /// this is a custom implementation of that method.
        /// </para>
        /// </summary>
        /// <returns>
        /// False if the current thread equals the form's thread, true otherwise.
        /// </returns>
        private bool CustomInvokeRequired()
        {
            if(this.FormThread.Equals(System.Threading.Thread.CurrentThread))
            {
                // the call was made on the form's thread
                return false;
            }
            
            // the call was made on a thread other than the form's thread
            return true;
        }

        private void MainForm_Resize(object sender, System.EventArgs e)
        {
            if(Screen.PrimaryScreen.Bounds.Width>Screen.PrimaryScreen.Bounds.Height)
            {
                Landscape();
            }
            else
            {
                Portrait();
            }
        }
    }
}
