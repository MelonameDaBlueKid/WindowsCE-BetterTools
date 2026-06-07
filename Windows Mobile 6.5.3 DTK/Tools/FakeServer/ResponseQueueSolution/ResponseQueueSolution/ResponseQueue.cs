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

using FakeServerCore = Microsoft.WindowsMobile.Samples.FakeServer.Core;

namespace ResponseQueueSolution
{
    public partial class ResponseQueue : Form
    {
        public ResponseQueue()
        {
            InitializeComponent();
        }

        private void ConnectButton_Click(object sender, EventArgs e)
        {
            UTF8Encoding utf8Enc = new UTF8Encoding();

            //
            // Sample responses to add the response queue

            //
            // NOTE: We have picked HTTP responses only for purposes of demonstration.
            // The response can be in any format as the developer desires, e.g. HTTP, Plain XML, etc
            //
            string responseStr1 = "HTTP/1.1 200 OK\r\nContent-Length: 25\r\n\r\nFirst Response from queue";
            string responseStr2 = "HTTP/1.1 200 OK\r\nContent-Length: 26\r\n\r\nSecond Response from queue";

            //
            // Responses to add to the default response queue
            //
            string responseStrDef = "HTTP/1.1 200 OK\r\nContent-Length: 16\r\n\r\nDEFAULT RESPONSE";

            // 
            // Initialize the FakeServer
            //
            FakeServerCore.FakeServer.Initialize();
            
            //
            // Add a couple of responses to the FakeServer's Response queue
            //
            FakeServerCore.FakeServer.ResponseQueue.Enqueue(new FakeServerCore.FakeResponse(utf8Enc.GetBytes(responseStr1.ToCharArray())));
            FakeServerCore.FakeServer.ResponseQueue.Enqueue(new FakeServerCore.FakeResponse(utf8Enc.GetBytes(responseStr2.ToCharArray())));

            //
            // Add a response as the Default response that will be sent back by the FakeServer once the queue is empty
            //
            FakeServerCore.FakeServer.DefaultResponses.Add(new FakeServerCore.FakeResponse(utf8Enc.GetBytes(responseStrDef.ToCharArray())));

            //
            // Start the fake server
            //
            FakeServerCore.FakeServer.Start();

            ConnectButton.Enabled = false;
            DisconnectButton.Enabled = true;

        }

        private void DisconnectButton_Click(object sender, EventArgs e)
        {
                        
            //
            // Stop the FakeServer
            //
            FakeServerCore.FakeServer.Stop();
            ConnectButton.Enabled = true;
            DisconnectButton.Enabled = false;
        }

    }
}