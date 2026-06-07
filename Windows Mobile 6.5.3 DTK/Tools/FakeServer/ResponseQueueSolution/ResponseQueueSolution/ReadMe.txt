
Application Name:  ResponseQueueApp

Purpose:

This sample is intended as a demonstration of the ResponseQueue Interface
exposed by the Microsoft.WindowsMobile.Samples.FakeServer.Dll

Description:

In this sample application we will use the fake server interfaces to start
a listener service on port 80.  We will pre-populate the response queue and the 
default response queue with a few HTTP responses.  These responses will be served
to clients that connect to the fake server on port 80.

Usage:
In order to see the ResponseQueueApp in action, build  and run the solution.

Then open up Pocket IE and type in http://localhost/test in the address bar.
The responses from the ResponseQueueApp will be returned to the browser in the 
order in which they were added to the queue.

Default Responses will start getting returned when the application response queue 
runs out of responses.


Special Notes:

We have picked HTTP for the sake of demonstration, the fake server doesnt impose any restrictions on
the response type.  The response interface allows developers to send down any
response data they intend to the client application.