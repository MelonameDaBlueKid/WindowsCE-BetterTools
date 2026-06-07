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

#endregion

namespace Microsoft.WindowsMobile.SharedSource.Bluetooth
{
	/// <summary>
	/// Represents a collection of Bluetooth devices.
	/// </summary>
	public class BluetoothDeviceCollection : System.Collections.ICollection, System.Collections.IList
	{
		internal BluetoothDeviceCollection()
		{
			devices = new ArrayList();
		}

		public void CopyTo(System.Array array, System.Int32 index)
		{
			devices.CopyTo(array, index);
		}

		public void CopyTo(BluetoothDeviceCollection array, System.Int32 index)
		{
			devices.CopyTo(array.devices.ToArray(), index);
		}

		public int Count
		{
			get
			{
				return devices.Count;
			}
		}

		public bool IsSynchronized
		{
			get
			{
				return devices.IsSynchronized;
			}
		}

		public object SyncRoot
		{
			get
			{
				return devices.SyncRoot;
			}
		}

		public System.Collections.IEnumerator GetEnumerator()
		{
			return devices.GetEnumerator();
		}

		public System.Int32 Add(System.Object value)
		{
			return devices.Add(value);
		}

		public System.Int32 Add(BluetoothDevice value)
		{
			return devices.Add(value);
		}

		public void Clear()
		{
			devices.Clear();
		}

		public System.Int32 IndexOf(System.Object value)
		{
			return devices.IndexOf(value);
		}

		public System.Int32 IndexOf(BluetoothDevice value)
		{
			return devices.IndexOf(value);
		}

		public Boolean Contains(System.Object value)
		{
			return devices.Contains(value);
		}

		public Boolean Contains(BluetoothDevice value)
		{
			return devices.Contains(value);
		}

		public void Insert(System.Int32 index, System.Object value)
		{
			devices.Insert(index, value);
		}

		public void Insert(System.Int32 index, BluetoothDevice value)
		{
			devices.Insert(index, value);
		}

		public void Remove(System.Object value)
		{
			devices.Remove(value);
		}

		public void Remove(BluetoothDevice value)
		{
			devices.Remove(value);
		}

		public void RemoveAt(System.Int32 index)
		{
			devices.RemoveAt(index);
		}

		public bool IsFixedSize
		{
			get
			{
				return devices.IsFixedSize;
			}
		}

		public bool IsReadOnly
		{
			get
			{
				return devices.IsReadOnly;
			}
		}

		public object this[int index]
		{
			get
			{
				return devices[index];
			}
			set
			{
				devices[index] = value;
			}
		}

		// backing container is an ArrayList
		private ArrayList devices;
	}
}
