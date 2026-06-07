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
// Copyright (c)  Microsoft Corporation.  All rights reserved.
//
//
// This source code is licensed under Microsoft Shared Source License
// Version 1.0 for Windows CE.
// For a copy of the license visit http://go.microsoft.com/?linkid=2933443.
//

#region Using directives

using System;
using System.Net.Sockets;
using System.Runtime.InteropServices;

#endregion

namespace Microsoft.WindowsMobile.SharedSource.Bluetooth
{
	/// <summary>
	/// Represents a Bluetooth Service identified by a GUID.
	/// 
	/// Use this class to publish a new service and accept client connections.
	/// </summary>
	public class BluetoothService
	{
		/// <summary>
		/// Constructs a new Bluetooth Service identified by a GUID
		/// </summary>
		/// <param name="serviceGuid">GUID identifying this service</param>
		public BluetoothService(Guid serviceGuid)
		{
			this.serviceGuid = serviceGuid;
			serverSocket = null;
			started = false;
		}

		/// <summary>
		/// Registers this service with the system and enables clients to connect
		/// </summary>
		public void Start()
		{
			PublishService();

			serverSocket.Listen(100);
			started = true;
		}

		/// <summary>
		/// Stops this service
		/// </summary>
		public void Stop()
		{
			if (serverSocket != null)
			{
				serverSocket.Close();
				started = false;
			}
		}

		/// <summary>
		/// Indicates whether the service has been started or not
		/// </summary>
		public bool Started
		{
			get
			{
				return started;
			}
		}

		/// <summary>
		/// Indicates whether there are clients waiting to connect on this service
		/// </summary>
		public bool ConnectionPending
		{
			get
			{
				return serverSocket.Poll(0, SelectMode.SelectRead);
			}
		}

		/// <summary>
		/// Accepts a connection on this service
		/// </summary>
		/// <returns>A NetworkStream object used to communicate between the two devices</returns>
		public NetworkStream AcceptConnection()
		{
			Socket clientSocket = serverSocket.Accept();

			return new NetworkStream(clientSocket, true);
		}

		/// <summary>
		/// GUID identifying this service
		/// </summary>
		public Guid ServiceGuid
		{
			get
			{
				return serviceGuid;
			}
		}

		private void PublishService()
		{
			serverSocket = new Socket((AddressFamily)32, SocketType.Stream, (ProtocolType)3);

			BluetoothEndPoint btep = new BluetoothEndPoint();

			serverSocket.Bind(btep);

			// extract port number
			int port = ((BluetoothEndPoint)serverSocket.LocalEndPoint).Port;

			byte[] sdpRecord = GenerateSDPRecord(ServiceGuid, port);

			// set up BTHNS_BLOB

			byte[] bthnsBlob = new byte[36 + sdpRecord.Length];

			int sdpVersion = 1;
			int serviceHandle = 0;

			GCHandle sdpVersionHandle = GCHandle.Alloc(sdpVersion, GCHandleType.Pinned);
			GCHandle recordHandle = GCHandle.Alloc(serviceHandle, GCHandleType.Pinned);

			BitConverter.GetBytes(sdpVersionHandle.AddrOfPinnedObject().ToInt32()).CopyTo(bthnsBlob, 0);
			BitConverter.GetBytes(recordHandle.AddrOfPinnedObject().ToInt32()).CopyTo(bthnsBlob, 4);

			BitConverter.GetBytes(sdpRecord.Length).CopyTo(bthnsBlob, 32);

			Buffer.BlockCopy(sdpRecord, 0, bthnsBlob, 36, sdpRecord.Length);

			// end BTHNS_BLOB

			// create a BLOB to hold the BTHNS_BLOB

			byte[] querySetBlob = new byte[8];

			GCHandle bthnsBlobHandle = GCHandle.Alloc(bthnsBlob, GCHandleType.Pinned);

			BitConverter.GetBytes( bthnsBlob.Length ).CopyTo( querySetBlob, 0 );

			int netCFv1WorkAround = 0;

			// Adding 4 to work around a bug with AddrOfPinnedObject on arrays in NETCF v1
			if ( System.Environment.Version.Major == 1 ) 
			{
				netCFv1WorkAround = 4;
			}
			
			// Adding 4 to work around a bug with AddrOfPinnedObject on arrays in NETCF v1
			BitConverter.GetBytes(bthnsBlobHandle.AddrOfPinnedObject().ToInt32() + netCFv1WorkAround).CopyTo(querySetBlob, 4);

			// end BLOB

			// query set setup
			const int querySetLengthOffset = 0;
			const int querySetNamespaceOffset = 20;
			const int querySetLength = 60;
			const int NS_BTH = 16;

			byte[] querySet = new byte[querySetLength];

			BitConverter.GetBytes(querySetLength).CopyTo(querySet, querySetLengthOffset);
			BitConverter.GetBytes(NS_BTH).CopyTo(querySet, querySetNamespaceOffset);

			GCHandle querySetBlobHandle = GCHandle.Alloc(querySetBlob, GCHandleType.Pinned);

			// Adding 4 to work around a bug with AddrOfPinnedObject on arrays in NETCF v1
			BitConverter.GetBytes(querySetBlobHandle.AddrOfPinnedObject().ToInt32() + netCFv1WorkAround).CopyTo(querySet, 56);

			// end query set setup

			// register the service

			try 
			{
				int result = SafeNativeMethods.WSASetService(querySet, 0, 0);

				int lastError = SafeNativeMethods.WSAGetLastError();

				if ( result != 0 ) 
				{
					throw new System.ApplicationException( "Could not register service (" + result + ") : " + lastError + "\n" +
						"Port: " + port );
				}

			}
			finally 
			{
				querySetBlobHandle.Free();
				bthnsBlobHandle.Free();
				sdpVersionHandle.Free();
				recordHandle.Free();
			}
			// end register service
		}

		private static byte[] GetLocalAddress()
		{
			byte[] localAddr = new byte[8];

			SafeNativeMethods.BthReadLocalAddr(localAddr);

			return localAddr;
		}


		private static byte[] GenerateSDPRecord(Guid serviceGuid, int channel)
		{
			// build the most basic SDP record specifying the service GUID and channel

			byte[] sdpRecord = new byte[] { 0x35, 0x00, 0x09, 0x00, 0x01, 0x35, 0x11, 0x1c,
				/* guid goes here */		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
											0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				/* L2CAP + RFCOMM */		0x09, 0x00, 0x04, 0x35, 0x0c, 0x35, 0x03, 0x19,
											0x01, 0x00, 0x35, 0x05, 0x19, 0x00, 0x03, 0x08,
				/* channel number here */	0x00 };

			// set sdp record length
			sdpRecord[1] = Convert.ToByte(sdpRecord.Length - 2);

			// copy in the service guid in network byte order
			byte[] guidArray = serviceGuid.ToByteArray();

			sdpRecord[8] = guidArray[3];
			sdpRecord[9] = guidArray[2];
			sdpRecord[10] = guidArray[1];
			sdpRecord[11] = guidArray[0];

			sdpRecord[12] = guidArray[5];
			sdpRecord[13] = guidArray[4];

			sdpRecord[14] = guidArray[7];
			sdpRecord[15] = guidArray[6];

			Array.Copy(guidArray, 8, sdpRecord, 16, 8);

			// last byte is the RFCOMM channel
			sdpRecord[sdpRecord.Length - 1] = Convert.ToByte(channel);

			return sdpRecord;
		}

		private bool started = false;
		private Guid serviceGuid;
		private Socket serverSocket;
	}
}
