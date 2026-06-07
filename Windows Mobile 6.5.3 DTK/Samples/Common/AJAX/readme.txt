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

Code Sample Name: Exchange Rate Calculator

Feature Area: Ajax demonstration for Internet Explorer Mobile



Description: 

Ajax is a design model that aims to create web sites that are close to applications in terms of responsiveness and usability. Ajax applications are very suited to mobile devices, as they do not require any code to be installed on the device itself, and can be accessed remotely.

This sample demonstrates how to use the Ajax-model of web page design in a way that is compatible with Internet Explorer Mobile. Although completely compatible with Ajax-style applications, there are a few points that developers targeting Windows Mobile devices need to take into consideration.



Code organization:

  This project consists of a web page (Rates.html) and an XML file (ExchangeRates.xml). Both files must be present in the same directory, and located on the same web server. 

Rates.html 	
	This HTML page consists of Jscript that uses an Ajax-approach to asynchronously load an XML file from the web server, parse it, and use the date to perform a simple calculation and update a control. It also displays text in a <div/> on the web page.

ExchangeRates.xml
	This XML file contains some sample data, listing four counties and their supposed exchange rate compared to the US dollar. A real-world application would need to consider how this file could be updated: one apporach would be to write an application to run on the server that would create it every day or every few hours.



Usage:

Place both files in the same directory on a web server, and access using Internet Explorer Mobile from a Windows Mobile-based device. To use, enter a number of dollars in the first input box, and select a currency from the pop-down select box. 



Notes: 

The degree of DOM support provided by Internet Explorer Mobile has been improved from Windows Mobile 5.0 to Windows Mobile 6. In particular, Windows Mobile 5.0 does not support the getElementById method, and so instead the name of the element is used as a reference. For example, given a text box element with the ID of “results”, it might be common to use the following statement:

getElementById(“results”).innerText  = “The exchange rate is 0.50”

However, to make this compatible with Windows Mobile 5, it would have to become:

results.innerText = “The exchange rate is 0.50”

There are a few other idiosyncrasies – for example, in the Internet Explorer Mobile implementation the collection that stores the Select box’s options is Read Only. The new options need to be appended to the control using Add(“menu option”)  rather than assigning them to the control’s existing list of options. See the HTML file for the implementation.



Requirements: 
    Web server

** For more information about this code sample, please see the Windows Mobile SDK help system. **
