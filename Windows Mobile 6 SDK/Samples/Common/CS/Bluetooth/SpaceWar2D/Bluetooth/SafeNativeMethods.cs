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
using System.Runtime.InteropServices;

#endregion

namespace Microsoft.WindowsMobile.SharedSource.Bluetooth
{
	internal sealed class SafeNativeMethods
	{
		/// <summary>
		/// constructor so default constructor is not created since all methods are static
		/// </summary>
		private SafeNativeMethods()
		{
			;
		}

		#region Win32 Methods

		const string BTHUTIL_DLL = "bthutil.dll";
		const string BTDRT_DLL = "btdrt.dll";
		const string WINSOCK_DLL = "Ws2.dll";
		const string CORE_DLL = "coredll.dll";

		#region CE Bluetooth Radio Functions
		[DllImport(BTHUTIL_DLL)]
		public static extern int BthGetMode(ref BluetoothRadioMode mode);

		[DllImport(BTHUTIL_DLL)]
		public static extern int BthSetMode(BluetoothRadioMode mode);

		#endregion

		#region Bluetooth Utility Functions

		[DllImport(BTDRT_DLL)]
		public static extern int BthSetPIN(byte[] btAddr, int pinLength, byte[] pin);

		[DllImport(BTDRT_DLL)]
		public static extern int BthRevokePIN(byte[] btAddr);

		[DllImport(BTDRT_DLL)]
		public static extern int BthReadLocalAddr(byte[] btAddr);

		[DllImport(BTDRT_DLL)]
		public static extern int BthAuthenticate( byte[] pba );
		
		[DllImport(BTDRT_DLL)]
		public static extern int BthSetEncryption( byte[] btAddr, int encryptOn );

		#endregion

		#region CE Winsock functions

		[DllImport(WINSOCK_DLL)]
		public static extern int WSAStartup(ushort version, byte[] wsaData);

		[DllImport(WINSOCK_DLL)]
		public static extern int WSACleanup();

		[DllImport(WINSOCK_DLL)]
		public static extern int WSALookupServiceBegin(byte[] querySet, int flags, ref int lookupHandle);

		[DllImport(WINSOCK_DLL)]
		public static extern int WSALookupServiceNext(int lookupHandle, int flags, ref int bufferLen, byte[] results);

		[DllImport(WINSOCK_DLL)]
		public static extern int WSALookupServiceEnd(int lookupHndle);

		[DllImport(WINSOCK_DLL, SetLastError=true)]
		public static extern int WSASetService(byte[] regInfo, int op, int flags);

		[DllImport(WINSOCK_DLL, SetLastError=true)]
		public static extern int WSAGetLastError();

		#endregion
		#endregion
	}
}
