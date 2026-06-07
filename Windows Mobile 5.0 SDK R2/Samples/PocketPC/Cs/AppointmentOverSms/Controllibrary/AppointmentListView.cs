//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.
//

using System;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using Microsoft.WindowsMobile.PocketOutlook;

namespace Microsoft.WindowsMobile.Samples.ControlLibrary
{
    /// <summary>
    /// A list view of appointments that fires an event when an appointment is selected.
    /// </summary>
    public partial class AppointmentListView : Microsoft.WindowsMobile.Samples.ControlLibrary.PimItemListView
    {
        /// <summary>
        /// Default constructor.
        /// </summary>
        public AppointmentListView()
        {
            InitializeComponent();
        }

        /// <summary>
        /// Collection of appointments to be included in the ListView.
        /// </summary>
        public AppointmentCollection Appointments
        {
            set
            {
                this.PimItems = value;
            }
        }

        /// <summary>
        /// Get/Set the property for the first label in the cell.
        /// </summary>
        public Microsoft.WindowsMobile.PocketOutlook.AppointmentProperty PimItemProperty1
        {
            get
            {
                return (AppointmentProperty) property1;
            }

            set
            {
                property1 = (ContactProperty) value;
            }
        }

        /// <summary>
        /// Get/Set the property for the second label in the cell.
        /// </summary>
        public Microsoft.WindowsMobile.PocketOutlook.AppointmentProperty PimItemProperty2
        {
            get
            {
                return (AppointmentProperty) property2;
            }

            set
            {
                property2 = (ContactProperty) value;
            }
        }

    }
}
