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
/*=====================================================================
  File:      LinkInfo.cs

  
  ---------------------------------------------------------------------

  This source code is intended only as a supplement to Microsoft
  Development Tools and/or on-line documentation.  See these other
  materials for detailed information regarding Microsoft code samples.

  THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
  PARTICULAR PURPOSE.
=====================================================================*/

using System;
using System.Net;

namespace WebCrawler
{
    /// <summary>
    /// Class describing a link
    /// </summary>
    public class LinkInfo
    {
        /// <summary>
        /// The link's address (ex: http://www.microsoft.com)
        /// </summary>
        public readonly string LinkPath;
        
        /// <summary>
        /// HttpStatusCode received when we attempted to
        /// connect to the link
        /// NOTE: Other possible values
        ///  0 == no connection attempted
        /// -1 == generic failure
        /// -2 == link does not point to html data
        /// </summary>
        public HttpStatusCode StatusCode;
        
        /// <summary>
        /// 
        /// </summary>
        /// <param name="linkPath">
        /// The link's address
        /// </param>
        /// <param name="status">
        /// Status code from connection attempt
        /// </param>
        public LinkInfo(string linkPath,
                        HttpStatusCode status)
        {
            this.LinkPath = linkPath;
            this.StatusCode = status;       
        }
    }
}
