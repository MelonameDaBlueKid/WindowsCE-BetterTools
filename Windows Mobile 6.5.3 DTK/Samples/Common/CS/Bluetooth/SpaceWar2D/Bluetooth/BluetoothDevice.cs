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

#endregion

namespace Microsoft.WindowsMobile.SharedSource.Bluetooth
{
	/// <summary>
	/// Represents a unique Bluetooth device and provides the ability to connect with it on a
	/// specified service.
	/// </summary>
	public class BluetoothDevice
	{
		/// <summary>
		/// Constructs an object to represent the Bluetooth device described with a name and address
		/// </summary>
		/// <param name="name">Describes the Bluetooth device</param>
		/// <param name="address">8 byte bluetooth address</param>
		public BluetoothDevice(string name, byte[] address)
		{
			if (name == null)
			{
				throw new ArgumentNullException("name");
			}

			if (address == null)
			{
				throw new ArgumentNullException("address");
			}

			this.name = name;
			this.address = address;
		}

		
		/// <summary>
		/// Describes a Bluetooth device
		/// </summary>
		public string Name
		{
			get
			{
				return name;
			}
		}

		/// <summary>
		/// 8 byte Bluetooth address
		/// </summary>
		public byte[] Address
		{
			get
			{
				return address;
			}
		}

		/// <summary>
		/// Provides the ability to connect to this device and transfer data
		/// </summary>
		/// <param name="serviceGuid">Specifies the Guid of the service to connect with on the remote device</param>
		/// <param name="secure">Indicates whether this connection should be encrypted</param>
		/// <returns>A NetworkStream object used to communicate between the two devices</returns>
		public NetworkStream Connect(Guid serviceGuid, bool secure)
		{
			Socket clientSocket = new Socket((AddressFamily)32, SocketType.Stream, (ProtocolType)3);

			BluetoothEndPoint endPoint = new BluetoothEndPoint(this, serviceGuid);


			clientSocket.Connect(endPoint);
	
			if ( secure ) 
			{
				// turn on authentication
				SafeNativeMethods.BthAuthenticate( this.address );

				// turn on link encryption
				SafeNativeMethods.BthSetEncryption( this.address, 1 );
			}


			// the network stream will own the socket so that it will clean up nicely
			return new NetworkStream(clientSocket, true);
		}

		/// <summary>
		/// Provides the ability to connect to this device and transfer data with encryption turned off
		/// </summary>
		/// <param name="serviceGuid">Specifies the Guid of the service to connect with on the remote device</param>
		/// <returns>A NetworkStream object used to communicate between the two devices</returns>
		public NetworkStream Connect(Guid serviceGuid)
		{
			return Connect( serviceGuid, false );
		}

		private string name;
		private byte[] address;
	}
}
