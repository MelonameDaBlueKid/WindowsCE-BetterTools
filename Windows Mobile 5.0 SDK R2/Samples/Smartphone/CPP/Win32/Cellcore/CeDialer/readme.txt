Code Sample Name: CeDialer

Feature Area: Cellcore.

Description: 

    To simplify the process of using a modem, Windows CE provides an 
    implementation of the Microsoft Telephony API (TAPI). The CEDialer code 
    sample shows how to dial a call with a modem using TAPI functions.

    Windows CE TAPI supports outbound calls, but does not support inbound calls.
    TAPI also supports installable service providers. The Telephony Service 
    Provider Interface (TSPI) enables developers to create telephony service 
    applications that handle function calls from remote applications to carry 
    out and control communications over the telephone network. 

    In Windows CE, TAPI links to and calls TSPI functions using standard 
    dynamic-link library (DLL) functions. TAPI uses the Unimodem TSPI by default. 

Relevant APIs: 
    lineInitialize, lineNegotiateAPIVersion, lineGetDevCaps, lineDrop, 
    lineDeallocateCall, lineClose.

Usage:

    Using TAPI to make a modem call
    A Windows CE�based application that uses a modem must be able to handle 
    tasks such as initializing the modem, opening the line, dialing a phone 
    number, and disconnecting when the session is complete.

    The following are the main steps and associated functions for dialing a call 
    in CEDialer:

    1. Initializing TAPI

        � InitializeTAPI

        � GetLineInfo

    2. Opening a line and making the call

        � MakePhoneCall

    3. Cleanup

        � CurrentLineClose


    Initializing TAPI
    When initializing TAPI, the application must establish a way to communicate 
    between a Windows CE�based application and TAPI.

     
    The CEDialer InitializeTAPI function:

    1. Calls lineInitialize to initialize TAPI. 

    2. Calls the custom GetLineInfo function to open the line. 

    3. GetLineInfo calls lineNegotiateAPIVersion to find TAPI API version to use.

    4. GetLineInfo calls lineGetDevCaps to obtain information on the line.

     
    lineInitialize
    The lineInitialize function initializes the application�s use of the 
    Tapi.dll for subsequent use. It registers the application-specific 
    notification mechanism and returns the number of line devices available to 
    the application.

    lineCallbackFunc
    To receive status notices, the application must implement a TAPI 
    lineCallbackFunc function to establish a way to communicate with TAPI. 
    An application tells TAPI the address of the callback function in the call 
    to lineInitialize. The callback function is used for notifying applications 
    of changes in the status of calls, lines, and phone devices. TAPI uses the 
    callback function to send messages to the application.

    lineNegotiateAPIVersion
    The lineNegotiateAPIVersion function, called by GetLineInfo indicates which 
    version of TAPI the application supports, and negotiates which API version 
    number TAPI should use. The reason for negotiating the TAPI version is to be
    sure that the correct protocol is used. New versions might define new 
    features, new fields to data structures, and so on. Version numbers 
    therefore indicate how to interpret various data, structures, and messages. 
    If version ranges do not match, the application and API or service provider 
    versions are incompatible and an error is returned. When the function 
    succeeds, the line data such as permanent identifier, number of addresses, 
    and line name, can be obtained from the LINEDEVCAPS structure.

    lineGetDevCaps
    When an application has initiated and negotiated the API, the application 
    needs to verify if the line is usable and ready for dialing out. The 
    application can do this by checking the values filled into the LINEDEVCAPS 
    structure by calling the lineGetDevCaps function. 

    The lineGetDevCaps function fills in the LINEDEVCAPS structure, which the 
    telephone service provider defines. The size of the structure might be 
    different for different service providers, and therefore the application 
    must check to see if the buffer size is adequate. To check if the amount of 
    space supplied for the structure is sufficient for the size of the structure 
    of the provider, compare the dwNeededSize and dwTotalSize fields. If the 
    total size is too small, the application needs to pass a larger buffer to 
    the function.


    Opening a line and making a call
    Once TAPI is initialized using the lineInitialize function, an application
    needs to get an available line using the lineOpen function.

    In the CEDialer sample the MakePhoneCall function:

    1. Calls lineOpen to open the line. 

    2. Calls lineTranslateAdress to translate the phone number.

    3. Sets up call parameters in LINECALLPARAMS structure.

       � The LINECALLPARAMS structure describes parameters supplied when making 
       calls using lineMakeCall. The LINECALLPARAMS structure is also used as a 
       parameter in other operations. 

    4. Calls lineMakeCall. 

     
    lineOpen
    The lineOpen function opens the specified line device and returns a line 
    handle to the opened line device. This line handle is used in subsequent 
    operations on the line device. Later, when the application is finished using 
    the line device, it can close it with lineClose.

    The lineOpen function specifies: 

    A handle to the application registration with TAPI. 

    A value that identifies the line device to be opened. Windows CE does not 
    support the LINEMAPPER value for the dwDeviceID parameter. 

    A pointer to a line handle loaded with the handle representing the opened 
    line device. 

    The API version number under which the application and TAPI operate 
    compatibly. This number is obtained by calling the lineNegotiateAPIVersion.

    The extension version number under which the application and the service 
    provider operate compatibly. Windows CE does not support provider-specific 
    extensions. The dwExtVersion parameter should be set to zero prior to 
    calling the lineOpen function. 

    User-instance data passed back to the application with each message 
    associated with this line or with addresses or calls on this line. This 
    parameter is not interpreted by the TAPI. 

    The privilege the application wants for the calls it is notified for. This 
    parameter can be a combination of the LINECALLPRIVILEGE constants. 

    lineMakeCall
    To place a call, the application must call the lineMakeCall function using 
    the LINECALLPARAMS structure. The CEDialer application provides a dialog box 
    for a user to enter the phone number of their choice. TAPI sends 
    LINE_CALLSTATE messages to indicate the progress of the call. For example, 
    LINE_CALLSTATE indicates states of connection, dialing, proceeding, and so 
    on. The messages vary depending on the type of call and the service 
    provided. The application should not be designed to one type or one special 
    sequence of call states.

    During data transfer, TAPI continues to manage the connection, but the 
    application handles data transmission and reception. When the transmission 
    is complete, TAPI returns a LINE_CALLSTATE message, such as one indicating 
    that a remote disconnect has occurred. The CeDialer sample does not handle 
    data transmission.

    Each call from a Windows CE device is identified by a call handle. A call 
    handle provides a pointer to a value to identify a specific call. TAPI 
    assigns call handles as required. One call handle exists for every call 
    owned by an application. Certain TAPI functions create new calls. As they 
    do so, they return new call handles to the application.

     

    The lineMakeCall function has the following parameters: 

    A handle to the open line device on which a call is originated 

    A pointer to the handle to the call. Use this call handle to identify the 
    call when invoking other telephony operations on the call. 

    A pointer to the destination address. This follows the standard area code 
    and telephone number format. 

    The country code of the called party 

    A pointer to a LINECALLPARAMS structure. This structure enables the 
    application to specify how to set up the call. If NULL is specified, a 
    default 3.1 kHz channel voice call is established and an arbitrary 
    origination address on the line is selected. This structure enables the 
    application to select elements such as the call bearer mode, data rate, 
    expected media, and dialing parameters. 

    The MakePhoneCall function demonstrates how the LPCALLPARAMS structure can 
    be filled in to support an outbound call. 

    After the lineMakeCall function successfully sets up the call, TAPI returns 
    a LINE_REPLY message through the callback function. The LINE_REPLY message 
    also informs the application that the call handle returned by lineMakeCall 
    is valid. This message indicates only that the call has been established at 
    the local end, which is perhaps indicated by a dial tone. The application 
    can then use that line to make outbound calls.



     
    Cleanup
    When the application receives a message indicating that the call has ended,
    the application disconnects the call at the local end with lineDrop. 

     
    The CEDialer CurrentLineClose function:

    1. Calls linedrop to drop the current call.

    2. Calls lineDeallocateCall to release the call handle for the finished call. 

    3. Calls lineClose to close the line connection. 

    linedrop, lineDeallocateCall, lineclose
    When a user ends the call, the application should disconnect and terminate 
    the call with lineDrop call the lineDeallocateCall function to free 
    system-allocated memory related to the call handle. The lineDrop function 
    can also be used to drop a call in progress. To finally close the line, the 
    application should call lineClose. 


Assumptions: 
    None.

Requirements: 
    Visual Studio 2005, 
    Windows Mobile 5.0 Pocket PC SDK or
    Windows Mobile 5.0 Smartphone SDK
    ActiveSync 4.0.

** For more information about this code sample, please see the Windows Mobile SDK help system. **
