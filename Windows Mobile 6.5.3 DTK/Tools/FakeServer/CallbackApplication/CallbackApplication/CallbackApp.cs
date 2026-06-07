//---------------------------------------------------------------------
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
// Use of this source code is subject to the terms of the Microsoft 
// end-user license agreement (EULA) under which you licensed this
// SOFTWARE PRODUCT. If you did not accept the terms of the EULA, you 
// are not authorized to use this source code. For a copy of the EULA, 
// please see the LICENSE.RTF on your install media.
//---------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Diagnostics;
using System.Runtime.InteropServices;

using FakeServerCore = Microsoft.WindowsMobile.Samples.FakeServer.Core;

namespace CallbackApplication
{
    public partial class CallbackApp : Form
    {
        public CallbackApp()
        {
            InitializeComponent();
        }


        private void Stop_Click(object sender, EventArgs e)
        {
            FakeServerCore.FakeServer.Stop();
            StartServer.Enabled = true;
            Stop.Enabled = false;
        }

        private void StartServer_Click(object sender, EventArgs e)
        {
            //
            // Initialize the server on port 80 and specify a call back function
            //
            FakeServerCore.FakeServer.InitializeEx("80", 0, null, null, new FakeServerCore.FakeServerRequestCallback(SimpleCallback));
            FakeServerCore.FakeServer.Start();
            StartServer.Enabled = false;
            Stop.Enabled = true;
        }

        //
        // Simple callback function that will be called everytime the fakeserver receives a request
        //
        static Int32 SimpleCallback(IntPtr pbRequest, Int32 cbRequest, ref IntPtr pbResponse, ref Int32 cbResponse)
        {
            UTF8Encoding utf8Encoding = new UTF8Encoding();

            //
            // Send a sample response
            //
            string response = "HTTP/1.1 200 OK\r\nContent-Length: 22\r\n\r\nResponse from callback";

            
            //
            // Populate and copy the response
            //
            cbResponse = utf8Encoding.GetByteCount(response.ToCharArray());
            pbResponse = Marshal.AllocCoTaskMem(cbResponse);
            Marshal.Copy(utf8Encoding.GetBytes(response.ToCharArray()), 0, pbResponse, cbResponse);

            //
            // Dump the request to a log file
            //
            byte[] request = new byte[cbRequest];
            Marshal.Copy(pbRequest, request, 0, cbRequest);

            BinaryWriter writer = new BinaryWriter(new FileStream(@"fakeserverlog.txt", FileMode.Append));

            writer.Write("-------- " + DateTime.Now.ToString() + " --------");
            writer.Write("-------- REQUEST --------");
            writer.Write(request);

            
            return 0;
        }	

    }
}