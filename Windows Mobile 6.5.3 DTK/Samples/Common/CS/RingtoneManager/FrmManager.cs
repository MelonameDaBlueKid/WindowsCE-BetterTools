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
//---------------------------------------------------------------------
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
// Use of this source code is subject to the terms of the Microsoft 
// end-user license agreement (EULA) under which you licensed this
// SOFTWARE PRODUCT. If you did not accept the terms of the EULA, you 
// are not authorized to use this source code. For a copy of the EULA, 
// please see the LICENSE.RTF on your install media.
//---------------------------------------------------------------------

namespace Microsoft.WindowsMobile.Samples.RingToneManager
{
    using System;
    using System.Collections;
    using System.Collections.Generic;
    using System.ComponentModel;
    using System.Data;
    using System.Drawing;
    using System.Text;
    using System.Windows.Forms;
    using System.IO;
    using System.Runtime.InteropServices;
   
    /// <summary>
    /// The main form
    /// </summary>
    public partial class FrmManager : Form
    {
        #region Private Members
        /// <summary>
        /// The handle for sounds 
        /// </summary>
        private IntPtr sndHandle;

        /// <summary>
        /// This is the offset size in bytes of each string returned by the sound directories array 
        /// returned from the native method SndGetSoundDirectoriesList 
        /// MAXPATH = 260 , Bytes = 2
        /// OffSet = MAXPATH * Bytes
        /// </summary>
        private const int OffSet = 520;

        #endregion

        #region Constructor

        /// <summary>
        /// Constructor
        /// </summary>
        public FrmManager()
        {
            this.InitializeComponent();

            // Creating a NULL handle
            this.sndHandle = new IntPtr();
            this.mnuPreview.Enabled = false;
            this.mnuAddRingTone.Enabled = false;
        }
        #endregion

        #region Enums
        /// <summary>
        /// The HRESULT Constants.
        /// </summary>
        public enum HResultValues : uint
        {
            /// <summary>
            /// S_OK
            /// </summary>
            Ok = 0,

            /// <summary>
            /// E_NOTIMPL
            /// </summary>
            NotImplemented = 0x80004001,
            
            /// <summary>
            /// E_FAIL
            /// </summary>
            Fail = 0x80004005,

            /// <summary>
            /// E_INVALIDARG
            /// </summary>
            InvalidArgument = 0x80070057,

            /// <summary>
            /// ERROR_DEVICE_NOT_CONNECTED
            /// </summary>
            DeviceNotConnected = 0x8018048f
        }

        /// <summary>
        /// SndScope describes a set of sounds.
        /// </summary>
        public enum SndScope
        {
            /// <summary>
            /// SND_SCOPE_PROCESS
            /// </summary>
            Process = 0x1
        }

        /// <summary>
        /// Bitmask for the locations of the sounds
        /// </summary>
        [FlagsAttribute]
        public enum SndLocation
        {
            /// <summary>
            /// Sound files from the Storage Card
            /// </summary>
            StorageCard = 0x1,

            /// <summary>
            /// Sound files from the user data (ie, \My Documents)
            /// </summary>
            UserData = 0x2,

            /// <summary>
            /// Sound files from the ROM
            /// </summary>
            Rom = 0x4
        }

        /// <summary>
        /// This enum indicates which sound event type that we want to set or query
        /// </summary>
        public enum SndEvent
        {
            /// <summary>
            /// All Events
            /// </summary>
            All = 0x0,

            /// <summary>
            /// The ringtone for line 1
            /// </summary>
            RingToneLine1 = 0x1,

            /// <summary>
            /// The ringtone for line 2
            /// </summary>
            RingToneLine2 = 0x2,

            /// <summary>
            /// The ringtone to play for  a caller on the contact list
            /// </summary>
            KnowCallerRingTone = 0x3,

            /// <summary>
            /// The ringtone to play while roaming
            /// </summary>
            RoamingRingTone = 0x4,

            /// <summary>
            /// The ringtone for VoIP line on the phone
            /// </summary>
            VoipRingTone = 5
        }

        #endregion
        /// <summary>
        /// This method recursivly scans all the subdirectories on "directory" for media files.
        /// It also adds those files to the list view.
        /// </summary>
        /// <param name="directory">The directory to be scanned</param>
        private void ScanDirectories(string directory)
        {
            #region processing files
            // We want to skip all the files on the windows directory to speed up the scan
            // and we don't want to scan directories that are already include on the list of 
            // ring tone directories.
            if (!directory.Equals(@"\Windows") && !this.IsDirectoryRingToneDirectory(directory))
            {
                foreach (string file in Directory.GetFiles(directory))
                {
                    if (progressBar1.Value == progressBar1.Maximum)
                    {
                        // Resetting the Progress bar
                        progressBar1.Value = progressBar1.Minimum;
                    }

                    progressBar1.Value++;

                    // If your device suports MIDI files then you can add ".Mid" to 
                    // list of supported media files
                    if (Path.GetExtension(file).ToLower().Equals(".wav") || Path.GetExtension(file).ToLower().Equals(".mp3"))
                    {
                        string[] fileInfo = new string[2];
                        fileInfo[0] = Path.GetFileName(file);
                        fileInfo[1] = Path.GetFullPath(file);
                        FileItem soundFile = new FileItem(fileInfo);                   
                        lvwSoundFiles.Items.Add(soundFile);
                    }
                }
            }
            #endregion

            #region processing subdirectories
            foreach (string subDirectory in Directory.GetDirectories(directory))
            {
                this.ScanDirectories(subDirectory);
            }
            #endregion
        }

        private void MnuExit_Click(object sender, EventArgs e)
        {
            this.StopAllSounds();

            // We want to make sure is a valid handle before we try to close the handle
            if (!this.sndHandle.Equals(new IntPtr(0x0)))
            {
                // We just want to close the handle if it is a valid handle
                if (SafeNativeMethods.SndClose(this.sndHandle) != (uint)HResultValues.Ok)
                {
                    throw new NativeException("Unable to close handle");
                }
            }

            Application.Exit();         
        }

        /// <summary>
        /// Event handler for Preview menu item
        /// </summary>
        /// <param name="sender">The sender</param>
        /// <param name="e">Event Arguments</param>
        private void MnuPreview_Click(object sender, EventArgs e)
        {
            this.PreviewSound();
        }

        /// <summary>
        /// Event hanler for Scan menu item
        /// </summary>
        /// <param name="sender">The sender</param>
        /// <param name="e">Event Arguments</param>
        private void MnuScan_Click(object sender, EventArgs e)
        {
            mnuScan.Enabled = false;
            mnuAddRingTone.Enabled = false;
            mnuPreview.Enabled = false;

            // To speed up the scanning process we prevent lvwSoundFiles
            // from updatating until the scan is done.
            lvwSoundFiles.BeginUpdate();
            lvwSoundFiles.Items.Clear();
            // Resetting the progress bar
            progressBar1.Value = progressBar1.Minimum;

            // Ideally we should create a separate thread to run ScanDirectories()
            // for simplicity purposes we make a syncronous call
            this.ScanDirectories(@"\");

            // Updating lvwSoundFiles since ScanDirectories() is done
            lvwSoundFiles.EndUpdate();

            // Setting progress bar to be fill 100%
            progressBar1.Value = progressBar1.Maximum;
            if (lvwSoundFiles.Items.Count < 1)
            {
                ListViewItem noFiles = new ListViewItem();
                noFiles.Text = "No files found";
                lvwSoundFiles.Items.Add(noFiles);                
            }
            else
            {
                mnuAddRingTone.Enabled = true;
                mnuPreview.Enabled = true;
            }
            lvwSoundFiles.Items[0].Focused = true;
            lvwSoundFiles.Items[0].Selected = true;
            mnuScan.Enabled = true;
        }

        /// <summary>
        /// It stops all current sounds and start playing the file that is selected 
        /// on the ListView
        /// </summary>
        private void PreviewSound()
        {
            // Before previewing a sound we stop all the current sounds
            this.StopAllSounds();

            if (this.sndHandle != IntPtr.Zero)
            {
                // We want to make sure that we close the handle
                if (SafeNativeMethods.SndClose(this.sndHandle) != (uint)HResultValues.Ok)
                {
                    throw new NativeException("Unable to close handle");
                }
            }
            
            FileItem file = (FileItem)this.lvwSoundFiles.FocusedItem;
            uint result;
            if (File.Exists(file.FilePath))
            {
                result = SafeNativeMethods.SndOpen(file.FilePath, ref this.sndHandle);
            }
            else
            {
                throw new FileNotFoundException("The file that you selected is not longer available");
            }

            // Checking that the handle was successfully created
            if ((uint)HResultValues.Ok != result)
            {
                throw new NativeException("Unable to Open handle");
            }

            // Calling the API to play the sound asynchronous
            // The second parameter contains the flags 
            // 0x1 is the equivalent to SND_PLAY_IGNOREUSERSETTINGS
            result = SafeNativeMethods.SndPlayAsync(this.sndHandle, 0x1);
            
            // Checking if the sound was able to start
            if ((uint)HResultValues.Ok != result)
            {
                throw new NativeException("Unable Play Sound");
            }
        }

        /// <summary>
        /// It stops all the current sounds
        /// </summary>
        private void StopAllSounds()
        {
            IntPtr nullHandle = new IntPtr();
            nullHandle = IntPtr.Zero;
            
            // From documentation we know that we need to set the second paramenter of SndStop to NULL
            // This parameter is reserved for future use.
            if ((uint)HResultValues.Ok != SafeNativeMethods.SndStop((int)SndScope.Process, nullHandle))
            {
                throw new NativeException("Unable to Stop Sounds");
            }
        }

        /// <summary>
        /// Event handler for menu item Stop all Sounds
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void MnuStop_Click(object sender, EventArgs e)
        {
            this.StopAllSounds();
        }

        /// <summary>
        /// Event handler for menu item Add Ring Tone
        /// </summary>
        /// <param name="sender">The sender</param>
        /// <param name="e">Event Arguments</param>
        private void MnuAddRingTone_Click(object sender, EventArgs e)
        {
            FileItem file = (FileItem)lvwSoundFiles.FocusedItem;
            FileInfo ringToneFile = new FileInfo(file.FilePath);
            
            // We just need one directory where we can copy the ringtone. Since SndGetSoundDirectoriesList 
            // returns an array of string containing all the sound directories we just take the first one.
            // Notice that there is not guarantee that it will always be the same directory. 
            if (!File.Exists(Path.Combine(this.GetRingToneDirectories()[0], file.FileName)))
            {
                ringToneFile.CopyTo(Path.Combine(this.GetRingToneDirectories()[0], file.FileName));
            }
            else
            {
                MessageBox.Show("The file " + file.FileName + " already exists under " + 
                    this.GetRingToneDirectories()[0].ToString());
            }
        }

        /// <summary>
        /// It calls SndGetSoundDirectoriesList to get the list of directories in user data for ringtone line 1. 
        /// </summary>
        /// <returns>An Array that contains the list of ringtone directories</returns>
        private string[] GetRingToneDirectories()
        {
            IntPtr directoryList = new IntPtr();
            IntPtr directoryCount = new IntPtr();
            SafeNativeMethods.SndGetSoundDirectoriesList(
                (uint) SndEvent.RingToneLine1, 
                (uint) SndLocation.UserData, 
                ref directoryList, 
                ref directoryCount);

            ArrayList result = new ArrayList();
            int numberOfDirectories = directoryCount.ToInt32();
            for (int i = 0; i < numberOfDirectories; i++)
            {
                // We are offsetting the pointer by the slot on the array that we want to read
                IntPtr nextDirectory = new IntPtr(directoryList.ToInt32() + i * OffSet);
                result.Add(Marshal.PtrToStringUni(nextDirectory));
            }                     

            // We need to free the memory that was created by SndGetSoundDirectoriesList. We use Local Free
            // to free the memory.
            if (SafeNativeMethods.LocalFree(directoryList) != IntPtr.Zero)
            {
                throw new NativeException("Cannot free memory");
            }

            return (string[]) result.ToArray(typeof(string));
        }

        /// <summary>
        /// This method checks if the directory is part of the list of ringtone directories
        /// </summary>
        /// <param name="directory">The directory to compare</param>
        /// <returns>True if the directory is part of the ring tone line 1 directoy</returns>
        private bool IsDirectoryRingToneDirectory(string directory)
        {
            string[] listOfDirectories = this.GetRingToneDirectories();
            bool found = false;
            for (int i = 0; (!found) && (i < listOfDirectories.Length); i++)
            {
                if (directory.ToLower().Equals(listOfDirectories[i].ToLower()))
                {
                    found = true;
                }
            }

            return found;
        }
    }

    /// <summary>
    /// Native methods that we will invoke
    /// </summary>
    internal sealed class SafeNativeMethods
    {
        [DllImport("coredll.dll", SetLastError = true)]
        public static extern IntPtr LocalFree(IntPtr hMem);

        [DllImport("aygshell.dll")]
        internal static extern uint SndPlaySync(string file, uint flags);

        [DllImport("aygshell.dll")]
        internal static extern uint SndOpen(string file, ref IntPtr phSound);

        [DllImport("aygshell.dll")]
        internal static extern uint SndPlayAsync(IntPtr hSound, uint flags);

        [DllImport("aygshell.dll")]
        internal static extern uint SndStop(int soundScope, IntPtr hSound);

        [DllImport("aygshell.dll")]
        internal static extern uint SndClose(IntPtr hSound);

        [DllImport("aygshell.dll")]
        internal static extern uint SndGetSoundDirectoriesList(
            uint soundEvent,
            uint location, 
            ref IntPtr soundDirectories,
            ref IntPtr directoriesCount);
    }

    #region File Item Class
    /// <summary>
    /// This class represents a ListViewItem that contains information about a file
    /// </summary>
    public class FileItem : ListViewItem
    {
        /// <summary>
        /// The file name
        /// </summary>
        private string Name;

        /// <summary>
        /// The full path of the file
        /// </summary>
        private string Path;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="elements">The array of strings that represent the file item </param>
        public FileItem(string[] elements)
            : base(elements)
        {
            this.Name = elements[0];
            this.Path = elements[1];
        }

        /// <summary>
        /// The name of the file
        /// </summary>
        public string FileName
        {
            get
            {
                return this.Name;
            }
        }

        /// <summary>
        /// The file name with complete path
        /// </summary>
        public string FilePath
        {
            get
            {
                return this.Path;
            }
        }
    }

    /// <summary>
    /// The generic exception for this application.
    /// </summary>

    public class NativeException : System.ApplicationException
    {
        /// <summary>
        /// Initializes a new instance of the NativeException class. 
        /// <remarks>The default Constructor.</remarks>
        /// </summary>
        public NativeException()
            : base()
        {

        }

        /// <summary>
        /// Initializes a new instance of the NativeException class, using the specified exception message string.
        /// </summary>
        /// <param name="message">Exception message.</param>
        public NativeException(String message)
            : base(message)
        {
        }

        /// <summary>
        /// Initializes a new instance of the NativeException class, using the specified exception message string, and specified inner exception.
        /// </summary>
        /// <param name="message">Exception message.</param>
        /// <param name="innerException">Inner exception.</param>
        public NativeException(String message, Exception innerException)
            : base(message, innerException)
        {
        }
    }


    #endregion
}