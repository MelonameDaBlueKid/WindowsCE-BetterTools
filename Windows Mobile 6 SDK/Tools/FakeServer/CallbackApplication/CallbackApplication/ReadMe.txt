
Application Name:  CallbackApplication

Purpose:

This sample is intended as a demonstration of the Managed Callback Interface
exposed by the Microsoft.WindowsMobile.Samples.FakeServer.Dll  The application defined 
callback will be invoked every time the fake server receives a request.  This allows
applications to read the request and process it before sending any response back to the
caller.

Description:

In this sample application we will use the fake server interfaces to start
a listener service on port 80.  We will also demonstrate how to create a sample
call back function and pass it into the fake server interface.

The callback function will be invoked when the fake server receives a request.
The request will be logged and a sample response will be sent back to the 
client.

Usage:
In order to see the CallbackApplication in action, build & deploy the solution
from visual studio.

Then open up Pocket IE and type in http://localhost/test in the address bar.
The response as defined in the callback function will be sent back to the 
client.

If you set a break point in the applications callback function you can see
the that it will get hit every time a request arrives to the server.  You will
also see the client request (it is an IN parameter from the fake server library).


Special Notes:

We have picked HTTP for the sake of demonstration, the fake server doesn't impose any restrictions on
the response type.  The response interface allows developers to send down any
response data they intend to the client application.
