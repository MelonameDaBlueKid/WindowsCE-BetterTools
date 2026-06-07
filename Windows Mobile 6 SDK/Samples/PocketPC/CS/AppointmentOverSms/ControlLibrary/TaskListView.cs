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
    /// A list view of tasks that fires an event when a task is selected.
    /// </summary>
    public partial class TaskListView : Microsoft.WindowsMobile.Samples.ControlLibrary.PimItemListView
    {
        /// <summary>
        /// Default constructor
        /// </summary>
        public TaskListView()
        {
            InitializeComponent();
        }   

        /// <summary>
        /// Collection of tasks to be included in the ListView.
        /// </summary>
        public TaskCollection Tasks
        {
            set
            {
                this.PimItems = value;
            }
        }

        /// <summary>
        /// Get/Set the property for the first label of a pimItem
        /// </summary>
        public Microsoft.WindowsMobile.PocketOutlook.TaskProperty PimItemProperty1
        {
            get
            {
                return (TaskProperty) property1;
            }

            set
            {
                property1 = (ContactProperty) value;
            }
        }

        /// <summary>
        /// Get/Set the property for the second label of a pimItem
        /// </summary>
        public Microsoft.WindowsMobile.PocketOutlook.TaskProperty PimItemProperty2
        {
            get
            {
                return (TaskProperty) property2;
            }

            set
            {
                property2 = (ContactProperty) value;
            }
        }

    }
}
