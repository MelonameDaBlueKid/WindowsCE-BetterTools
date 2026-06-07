//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.
//

Code Sample Name: 
    Mailset

Feature Area: 
    CEMAPI

Description:
    This sample will demonstrate using IMsgStore::GetProps and 
    IMsgStore::SetProps to retrieve and set properties on message stores. 
    It will read in an XML file (mailset.xml) which contains a list of CEMAPI
    store properties that can be changed. The XML document has the following 
    format:

        <store proptag="0x811A000B"
            propname="PR_CE_USE_SIGNATURE"
            display="Use the account signature"
            default="0"
            type="2"/>

        where:
        proptag - The numeric value of the property.
        propname - The name of this property.
        display - A friendly description of this property.
        default - The default value of this property to use if it is not in the 
                    store.
        type - The type of the property:
                0 = String
                1 = Integer
                2 = Boolean

Usage:
    Build and deploy normally using Visual Studio 2005, this will deploy mailset.exe 
    and copy mailset.xml to the same directory. 

Relevant APIs/Associated Help Topics:
    IMAPISession
    IMAPITable
    IMsgStore::GetProps
    IMsgStore::SetProps

Assumptions:
    You have at least one message account (SMS, ActiveSync) set up.

Requirements:
    Visual Studio 2005, 
    Windows Mobile 6 Standard SDK,
    Activesync 4.5


** For more information about this code sample, please see the Windows Mobile SDK help system. **


