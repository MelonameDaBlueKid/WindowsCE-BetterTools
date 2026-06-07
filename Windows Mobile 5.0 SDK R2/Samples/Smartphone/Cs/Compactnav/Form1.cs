//
// Copyright (c) Microsoft Corporation.  All rights reserved.
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
using System.IO;
using System.Runtime.InteropServices;

namespace CompactNav
{    
    /// <summary>
    /// Summary description for Form1.
    /// </summary>
    public class CompactNav : System.Windows.Forms.Form
    {
        private System.Windows.Forms.ListView listView1;
        private System.Windows.Forms.MainMenu mainMenu1;
        private System.Windows.Forms.MenuItem menuItem1;
        private System.Windows.Forms.MenuItem menuItem2;
        Bitmap folderIcon;
        Bitmap fileIcon;
        private string[] fullPath;
        int depth;
        
        //class for PROCESSINFO struct pinvoke
        public class ProcessInfo
        {
            public IntPtr hProcess;
            public IntPtr hThread;
            public Int32 ProcessId;
            public Int32 ThreadId;
        }
        // protoytpe for platform-invoked CreateProcess call
        [DllImport("CoreDll.DLL", SetLastError=true)]
        private extern static
            int CreateProcess( String imageName,
            String cmdLine,
            IntPtr lpProcessAttributes,
            IntPtr lpThreadAttributes,
            Int32 boolInheritHandles,
            Int32 dwCreationFlags,
            IntPtr lpEnvironment,
            IntPtr lpszCurrentDir,
            byte [] si,
            ProcessInfo pi );
        
        // CreateProcess wrapper
        public static bool CreateProcess( String ExeName, String 
            CmdLine, ProcessInfo pi )
        {
            if ( pi == null )
                pi = new ProcessInfo();
            
            byte [] si = new byte[128];
 
            return CreateProcess(ExeName, CmdLine, IntPtr.Zero, 
                IntPtr.Zero,
                0, 0, IntPtr.Zero, IntPtr.Zero, si, pi) != 0;
        }
        
        public CompactNav()
        {
            //
            // Required for Windows Form Designer support
            //
            InitializeComponent();

            //
            // TODO: Add any constructor code after InitializeComponent call
            //
            
            depth = 0;
            menuItem2.Enabled = false;
            listView1.View = View.List;
            ImageList imageListSmall = new ImageList();
            fullPath = new string[128];
            try
            {    
                //load icon images
                 folderIcon = new Bitmap(@"storage\windows\foldericon.bmp");
                 fileIcon = new Bitmap(@"\storage\windows\fileicon.bmp");
            }
            catch (System.IO.IOException)
            {
                folderIcon = null;
                fileIcon = null;
            }
        
            if (folderIcon != null && fileIcon != null)
            {
                // create and populate icon list
                imageListSmall.Images.Add(folderIcon);
                imageListSmall.Images.Add(fileIcon);
                listView1.SmallImageList = imageListSmall;
            }

            fullPath[0] = @"\";
        
            ShowDir(fullPath[0]);
        
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
            this.menuItem1 = new System.Windows.Forms.MenuItem();
            this.menuItem2 = new System.Windows.Forms.MenuItem();
            this.listView1 = new System.Windows.Forms.ListView();
            // 
            // mainMenu1
            // 
            this.mainMenu1.MenuItems.Add(this.menuItem1);
            this.mainMenu1.MenuItems.Add(this.menuItem2);
            // 
            // menuItem1
            // 
            this.menuItem1.Text = "Quit";
            this.menuItem1.Click += new System.EventHandler(this.menuItem1_Click);
            // 
            // menuItem2
            // 
            this.menuItem2.Text = "UpDir";
            this.menuItem2.Click += new System.EventHandler(this.menuItem2_Click);
            // 
            // listView1
            // 
            this.listView1.Location = new System.Drawing.Point(0, 0);
            this.listView1.Size = new System.Drawing.Size(184, 192);
            this.listView1.ItemActivate += new System.EventHandler(this.listView1_ItemActivate);
            // 
            // CompactNav
            // 
            this.ClientSize = new System.Drawing.Size(176, 180);
            this.Controls.Add(this.listView1);
            this.Menu = this.mainMenu1;
            this.Text = "CompactNav";
            this.Load += new System.EventHandler(this.CompactNav_Load);

        }
        #endregion

        /// <summary>
        /// The main entry point for the application.
        /// </summary>

        static void Main() 
        {
            Application.Run(new CompactNav());
        }

        private void menuItem1_Click(object sender, System.EventArgs e)
        {
            Application.Exit();
        }

        private void listView1_ItemActivate(object sender, System.EventArgs e)
        {
            // item activation handler
            string nextPath;
            // grab the selected item
            ListViewItem lvi = listView1.Items[listView1.SelectedIndices[0]];
        
            if (lvi.Text != "..")
            {
                // track the current path depth as we have no GetCurrentDirectory facility
                ++depth;
                
                if (depth == 1)
                {
                    nextPath = lvi.Text;
                }
                else
                    nextPath = @"\" + lvi.Text;
                
                // set the next path to show
                fullPath[depth] = fullPath[depth-1] + nextPath;
            }
            else
            {
                // if ".." was selected, back up a directory
                --depth;
        
            }
        
            // check if an executable file was selected
            if (fullPath[depth].EndsWith(".exe"))
            {
                ProcessInfo pi = new ProcessInfo();
                // launch the exe using our pinvoked CreateProcess call
                CreateProcess(fullPath[depth], "", pi);
                // back up since we didn't actually enter the directory
                --depth;
            }
            else
            {
                // otherwise, show the directory we selected
                ShowDir(fullPath[depth]);
            }
                
        }
        
        private void ShowDir(string newdir)
        {
            string[] dirs;
            string[] files;
            string shortdir;
            string shortfile;
            string lvidir;
            string lvifile;
            
            //this could take awhile so show the wait cursor
            Cursor.Current = Cursors.WaitCursor;

            try
            {
                // get directories and files from the given path
                dirs = Directory.GetDirectories(newdir);
                files = Directory.GetFiles(newdir);
            }
            catch (System.IO.DirectoryNotFoundException)
            {
                // oops, we are trying to show something that isn't a directory
                --depth;
                return;
            }
            
            listView1.Items.Clear();
            menuItem2.Enabled = false;
            if (depth != 0)
            {
                // add the ".." pseudo directory for parent access
                ListViewItem lvi = new ListViewItem("..");
                lvi.ImageIndex = 0;
                listView1.Items.Add(lvi);
                menuItem2.Enabled = true;
            }
            listView1.BeginUpdate();
            foreach(string dir in dirs)
            {
                // remove the full path leaving only the current directory's subdir names
                if (depth == 0)
                    shortdir = dir;
                else
                    shortdir = dir.Remove(0, newdir.Length);

                // remove the leading "\"
                lvidir = shortdir.Remove(0, 1);
                ListViewItem lvi = new ListViewItem(lvidir);
                // set the appropriate icon
                lvi.ImageIndex = 0;
                listView1.Items.Add(lvi);
            }
            foreach(string file in files)
            {
                // remove the full path leaving only the current directory's file names
                if (depth == 0)
                    shortfile = file;
                else
                    shortfile = file.Remove(0, newdir.Length);

                lvifile = shortfile.Remove(0,1);
                // remove the leading "\"
                ListViewItem lvi = new ListViewItem(lvifile);
                // set the appropriate icon
                lvi.ImageIndex = 1;
                listView1.Items.Add(lvi);
                
            }
            listView1.EndUpdate();
            Cursor.Current = Cursors.Default;

        }

        private void menuItem2_Click(object sender, System.EventArgs e)
        {
            // handler for the "UpDir" menu, just decrease the current depth
            --depth;
            ShowDir(fullPath[depth]);
        }

        private void CompactNav_Load(object sender, EventArgs e)
        {

            listView1.Width = Screen.PrimaryScreen.WorkingArea.Width;
            listView1.Height = Screen.PrimaryScreen.WorkingArea.Height;
        }
    }
}
