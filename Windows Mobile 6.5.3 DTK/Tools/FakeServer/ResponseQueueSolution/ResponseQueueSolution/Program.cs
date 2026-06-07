//---------------------------------------------------------------------
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
// Use of this source code is subject to the terms of the Microsoft 
// end-user license agreement (EULA) under which you licensed this
// SOFTWARE PRODUCT. If you did not accept the terms of the EULA, you 
// are not authorized to use this source code. For a copy of the EULA, 
// please see the LICENSE.RTF on your install media.
//---------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace ResponseQueueSolution
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [MTAThread]
        static void Main()
        {
            Application.Run(new ResponseQueue());
        }
    }
}