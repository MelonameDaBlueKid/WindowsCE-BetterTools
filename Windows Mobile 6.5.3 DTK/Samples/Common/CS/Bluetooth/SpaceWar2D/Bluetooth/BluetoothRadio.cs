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
using System.Collections;
using Microsoft.WindowsMobile.SharedSource.Utilities;

#endregion

namespace Microsoft.WindowsMobile.SharedSource.Bluetooth
{
	/// <summary>
	/// Represents the state of the Bluetooth radio and paired devices.
	/// </summary>
	public class BluetoothRadio : IDisposable
	{
		/// <summary>
		/// Initializes the networking system
		/// </summary>
		public BluetoothRadio()
		{
			disposed = false;

			// init winsock
			ushort winsockVersion = ((ushort)(((byte)(2)) | ((ushort)((byte)(2))) << 8));

			byte[] wsaData = new byte[512];

			int result = 0;

			result = SafeNativeMethods.WSAStartup(winsockVersion, wsaData);

			if (result != 0)
			{
				throw new System.Net.Sockets.SocketException();
			}
		}

		~BluetoothRadio()
		{
			Dispose();
		}

		/// <summary>
		/// A collection representing Bluetooth devices which have been previously paired with this device.
		/// </summary>
		public BluetoothDeviceCollection PairedDevices
		{
			get
			{
				BluetoothDeviceCollection pairedDevices = new BluetoothDeviceCollection();

				const string BT_DEVICE_KEY_NAME = "Software\\Microsoft\\Bluetooth\\Device";

				IntPtr btDeviceKey = Registry.OpenKey(Registry.GetRootKey(Registry.HKey.LocalMachine), BT_DEVICE_KEY_NAME);

                if (btDeviceKey != IntPtr.Zero)
                {
                    ArrayList subKeyNames = Registry.GetSubKeyNames(btDeviceKey);

                    foreach (string deviceAddr in subKeyNames)
                    {
                        long longDeviceAddress;
                        try
                        {
                            longDeviceAddress = long.Parse(deviceAddr, System.Globalization.NumberStyles.HexNumber);
                        }
                        catch
                        {
                            longDeviceAddress = 0;
                        }
                        if (longDeviceAddress != 0)
                        {
                            string deviceName = "";
                            byte[] deviceAddress = new byte[8];

                            IntPtr currentDeviceKey = Registry.OpenKey(btDeviceKey, deviceAddr);

                            deviceName = (string)Registry.GetValue(currentDeviceKey, "name");

                            Registry.CloseKey(currentDeviceKey);

                            BitConverter.GetBytes(longDeviceAddress).CopyTo(deviceAddress, 0);

                            BluetoothDevice currentDevice = new BluetoothDevice(deviceName, deviceAddress);

                            pairedDevices.Add(currentDevice);
                        }
                    }

                    Registry.CloseKey(btDeviceKey); 
                }

				return pairedDevices;
			}
		}

		/// <summary>
		/// The current state of the Bluetooth radio
		/// </summary>
		public BluetoothRadioMode BluetoothRadioMode
		{
			get
			{
				BluetoothRadioMode currentMode = BluetoothRadioMode.Off;

				SafeNativeMethods.BthGetMode(ref currentMode);

				return currentMode;
			}

			set
			{
				SafeNativeMethods.BthSetMode(value);
			}
		}

		#region IDisposable Members

		public void Dispose()
		{
			if (!disposed)
			{
				SafeNativeMethods.WSACleanup();
				disposed = true;
			}
		}

		#endregion

		bool Disposed
		{
			get
			{
				return disposed;
			}
		}

		private bool disposed = false;
	}

	/// <summary>
	/// Represents the Bluetooth radio state
	/// </summary>
	public enum BluetoothRadioMode : int
	{
		/// <summary>
		/// Off: Bluetooth hardware is powered off
		/// </summary>
		Off,
		/// <summary>
		/// On: Bluetooth hardware is powered on
		/// </summary>
		On,
		/// <summary>
		/// Discoverable: Bluetooth hardware is powered on and device advertises itself to others
		/// </summary>
		Discoverable
	};
}
