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
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.

using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Threading;
using System.Net.Sockets;
using Microsoft.WindowsMobile.SharedSource.Bluetooth;

namespace SpaceWar2D
{
    class ConnectionManager
    {
        /// <summary>
        /// The Bluetooth radio.
        /// </summary>
        private BluetoothRadio radio = new BluetoothRadio();


        /// <summary>
        /// Guid of the Bluetooth service
        /// </summary>
        private Guid guid;

        /// <summary>
        /// Thread function that processes data from the stream.
        /// </summary>
        private ThreadStart streamProcessor;

        /// <summary>
        /// The two-way communication stream to the other Bluetooth device.
        /// </summary>
        private NetworkStream stream;

        /// <summary>
        /// A BinaryReader on top of this.stream
        /// </summary>
        private BinaryReader reader;

        /// <summary>
        /// A BinaryWriter on top of this.stream
        /// </summary>
        private BinaryWriter writer;

        /// <summary>
        /// Should we stop the service thread, in preparation for 
        /// exiting the app?
        /// </summary>
        private bool exiting = false;

        /// <summary>
        /// The Bluetooth service.
        /// </summary>
        private BluetoothService bluetoothService;

        /// <summary>
        /// A BinaryWriter used to write to the other Bluetooth device.
        /// </summary>
        public BinaryWriter Writer
        {
            get { return writer; }
        }

        /// <summary>
        /// A BinaryReader used to read from the other Bluetooth device.
        /// </summary>
        public BinaryReader Reader
        {
            get { return reader; }
        }

        /// <summary>
        /// Gets a value indicating whether a connection is established with 
        /// the other Bluetooth device.
        /// </summary>
        public bool Connected
        {
            get { return stream != null; }
        }


        /// <summary>
        /// The two-way communication stream to the other Bluetooth device.
        /// </summary>
        private NetworkStream Stream
        {
            get { return stream; }
            set
            {
                stream = value;
                if (stream == null)
                {
                    writer.Close();
                    writer = null;
                    reader.Close();
                    reader = null;
                }
                else
                {
                    writer = new BinaryWriter(stream);
                    reader = new BinaryReader(stream);
                }
            }
        }


        /// <summary>
        /// Creates a new instance of a ConnectionManager.
        /// </summary>
        /// <param name="guid">The Bluetooth service guid.</param>
        /// <param name="streamProcessor">A callback function that will read and process data from the stream.</param>
        public ConnectionManager(Guid guid, ThreadStart dataProcessor)
        {
            this.guid = guid;
            this.streamProcessor = dataProcessor;
            Thread t = new Thread(new ThreadStart(ServiceThread));
            t.Start();
        }



        /// <summary>
        /// The thread that listens for Bluetooth connections, and processes
        /// the data read from a connection once established.
        /// </summary>
        private void ServiceThread()
        {
            bluetoothService = new BluetoothService(this.guid);

            while (!exiting)
            {
                if (!bluetoothService.Started)
                {
                    bluetoothService.Start();
                }
                try
                {
                    this.Stream = bluetoothService.AcceptConnection();
                }
                catch (System.Net.Sockets.SocketException)
                {
                    // bluetoothService.Stop() was called.  
                    // Treat this like a graceful return from AcceptConnection().
                }
                if (!exiting)
                {
                    // Call the streamProcessor to handle the data from the stream.
                    streamProcessor();
                }
            }
        }

        /// <summary>
        /// Force the service thread to exit.
        /// </summary>
        public void Exit()
        {
            // This will cause us to fall out of the ServiceThread() loop.
            exiting = true;

            if (!Connected)
            {
                // We must be waiting on AcceptConnection(), so we need to
                // force an exception to break out.
                bluetoothService.Stop();
            }
        }


        /// <summary>
        /// Connect to another Bluetooth device.
        /// </summary>
        public void Connect()
        {
            FormPlayerPicker formPicker = new FormPlayerPicker(radio);
            formPicker.ShowDialog();
            BluetoothDevice device = formPicker.Device;
            if (device != null)
            {
                try
                {
                    this.Stream = device.Connect(this.guid);
                }
                catch (System.Net.Sockets.SocketException)
                {
                    // Couldn't connect.
                }

                if (this.Stream == null)
                {
                    System.Windows.Forms.MessageBox.Show("Could not connect to device " + device.Name);
                }
                else
                {
                    // Forcibly break out of the AcceptConnection in 
                    // ServiceThread(), and continue on to streamProcessor().
                    bluetoothService.Stop();
                }
            }
        }

        /// <summary>
        /// Disconnect from the other Bluetooth device.
        /// </summary>
        public void Disconnect()
        {
            Stream = null;
        }

    }
}
