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
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using Microsoft.WindowsMobile.SharedSource.Bluetooth;

namespace SpaceWar2D
{
    public partial class FormPlayerPicker : Form
    {
        private BluetoothRadio radio;
        private BluetoothDevice device;

        public FormPlayerPicker(BluetoothRadio radio)
        {
            InitializeComponent();
            this.radio = radio;
        }

        public BluetoothDevice Device
        {
            get { return device; }
        }

        private void FormPlayerPicker_Load(object sender, EventArgs e)
        {
            comboBoxPlayers.DataSource = radio.PairedDevices;
            comboBoxPlayers.DisplayMember = "Name";
            comboBoxPlayers.Width = this.Size.Width - 8;
            label1.Width = this.Size.Width - 8;
        }

        private void menuConnect_Click(object sender, EventArgs e)
        {
            this.device = comboBoxPlayers.SelectedItem as BluetoothDevice;
            this.Close();
        }
    }
}
