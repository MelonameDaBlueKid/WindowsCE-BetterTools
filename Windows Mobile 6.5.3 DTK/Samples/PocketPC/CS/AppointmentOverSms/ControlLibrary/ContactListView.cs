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
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.
//

#region Using directives

using System;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using Microsoft.WindowsMobile.PocketOutlook;

#endregion


namespace Microsoft.WindowsMobile.Samples.ControlLibrary
{
    /// <summary>
    /// A list view of contacts that fires an event when a contact is selected.
    /// </summary>
    public partial class ContactListView : Microsoft.WindowsMobile.Samples.ControlLibrary.PimItemListView
    {
        /// <summary>
        /// Default constructor
        /// </summary>
        public ContactListView()
        {
            InitializeComponent();
        }

        /// <summary>
        /// Collection of contacts to be included in the ListView.
        /// </summary>
        public ContactCollection Contacts
        {
            set
            {
                this.PimItems = value;
            }
        }

        /// <summary>
        /// Set/Get whether picture should be shown 
        /// </summary>
        /// <remarks>blah blah blah</remarks>
        /// <value>true</value>
        public bool ShowPicture
        {
            get
            {
                return showPicture;
            }

            set
            {
                showPicture = value;
                UpdateDisplay();
            }
        }

        /// <summary>
        /// Get/Set the property for the first label of a pimItem
        /// </summary>
        public Microsoft.WindowsMobile.PocketOutlook.ContactProperty PimItemProperty1
        {
            get
            {
                return property1;
            }

            set
            {
                property1 = value;
            }
        }

        /// <summary>
        /// Get/Set the property for the second label of a pimItem
        /// </summary>
        public Microsoft.WindowsMobile.PocketOutlook.ContactProperty PimItemProperty2
        {
            get
            {
                return property2;
            }

            set
            {
                property2 = value;
            }
        }

    }
}
