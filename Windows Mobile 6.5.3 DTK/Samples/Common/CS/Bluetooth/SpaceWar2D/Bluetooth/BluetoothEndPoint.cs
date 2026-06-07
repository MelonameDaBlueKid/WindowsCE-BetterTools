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
	internal class BluetoothEndPoint : System.Net.EndPoint
	{
		public BluetoothEndPoint() 
		{
			this.deviceAddress = new byte[8];
			this.serviceGuid = Guid.Empty;
			this.port = 0;
		}

		public BluetoothEndPoint(BluetoothDevice device, Guid serviceGuid)
		{
			this.deviceAddress = (byte[])device.Address.Clone();
			this.serviceGuid = serviceGuid;
			this.port = 0;
		}

		public BluetoothEndPoint(byte[] deviceAddress, Guid serviceGuid)
		{
			this.deviceAddress = (byte[])deviceAddress.Clone();
			this.serviceGuid = serviceGuid;
			this.port = 0;
		}

		public BluetoothEndPoint(byte[] deviceAddress, Guid serviceGuid, int port)
		{
			this.deviceAddress = (byte[])deviceAddress.Clone();
			this.serviceGuid = serviceGuid;
			this.port = port;
		}

		public override System.Net.SocketAddress Serialize()
		{
			System.Net.SocketAddress sa = new System.Net.SocketAddress(AddressFamily.Unspecified, saLength);

			// AddressFamily
			sa[0] = 32;

			// copy in the remote bt address
			for (int i = 0; i < 8; i++)
			{
				sa[addressOffset + i] = deviceAddress[i];
			}

			// copy in the guid of the service we want to connect with
			byte[] guidArray = serviceGuid.ToByteArray();
			for (int i = 0; i < guidArray.Length; i++)
			{
				sa[guidOffset + i] = guidArray[i];
			}

			return sa;
		}

		public override System.Net.EndPoint Create(System.Net.SocketAddress socketAddress)
		{
			// device Address

			byte[] addr = new byte[8];

			for (int i = 0; i < 8; i++)
			{
				addr[i] = socketAddress[addressOffset + i];
			}

			// guid

			byte[] serviceGuid = new byte[16];

			for (int i = 0; i < 16; i++)
			{
				serviceGuid[i] = socketAddress[guidOffset + i];
			}

			byte[] deviceAddr = addr;

			Guid g = new Guid(serviceGuid);

			// port number

			byte[] portNumArray = new byte[4];

			for (int i = 0; i < 4; i++)
			{
				portNumArray[i] = socketAddress[channelOffset + i];
			}

			int portNum = BitConverter.ToInt32(portNumArray, 0);

			return new BluetoothEndPoint(deviceAddr, g, portNum);
		}

		public override AddressFamily AddressFamily
		{
			get
			{
				return (AddressFamily) 32;
			}
		}

		public int Port
		{
			get 
			{
				return port;
			}
		}

		private byte[] deviceAddress;
		private Guid serviceGuid;
		private int port;

		private const int saLength = 40;
		private const int addressOffset = 8;
		private const int guidOffset = 16;
		private const int channelOffset = 32;
	}
}
