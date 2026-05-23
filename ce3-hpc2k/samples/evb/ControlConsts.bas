' -----------------------------------------------------------------------------
' Enums.bas
' Enumerations for Windows CE Controls
' Copyright (c) 1998 Microsoft Corporation
' -----------------------------------------------------------------------------

' -----------------------------------------------------------------------------
' ADOCE
' -----------------------------------------------------------------------------

' Cursor Types
Const adOpenForwardOnly = 0
Const adOpenKeyset = 1
Const adOpenDynamic = 2
Const adOpenStatic = 3

' Position
Const adPosUnknown = -1
Const adPosBOF = -2
Const adPosEOF = -3

' Command type
Const adCmdText = 1
Const adCmdTable = 2
Const adCmdStoredProc = 4
Const adCmdUnknown = 8

' Data Types
Const adBoolean = 11
Const adDate = 7
Const adDouble = 5
Const adInteger = 3
Const adLongVarBinary = 205
Const adLongVarWChar = 203
Const adSmallInt = 2
Const adUnsignedInt = 19
Const adUnsignedSmallInt = 18
Const adVarBinary = 204
Const adVarWChar = 202

' Cursor Options
Const adAddNew = &H1000400
Const adApproxPosition = &H4000
Const adBookmark = &H2000
Const adDelete = &H1000800
Const adHoldRecords = &H100
Const adMovePrevious = &H200
Const adResync = &H20000
Const adUpdate = &H1008000

' Lock Types
Const adLockReadOnly = 1
Const adLockOptimistic = 3

' Edit Modes
Const adEditNone = &H0
Const adEditInProgress = &H1
Const adEditAdd = &H2

' Error Values
Const adErrInvalidArgument = &HBB9
Const adErrNoCurrentRecord = &HBCD
Const adErrIllegalOperation = &HC93
Const adErrFeatureNotAvailable = &HCB3
Const adErrItemNotFound = &HCC1
Const adErrObjectNotSet = &HD5C
Const adErrDataConversion = &HD5D
Const adErrObjectClosed = &HE78
Const adErrObjectOpen = &HE79
Const adErrProviderNotFound = &HE7A
Const adErrInvalidParamInfo = &HE7C
Const adErrInvalidConnection = &HE7D

' Field Attributes
Const adFldMayDefer = 2
Const adFldUpdatable = 4
Const adFldUnknownUpdatable = 8
Const adFldFixed = 16
Const adFldIsNullable = 32
Const adFldMayBeNull = 64
Const adFldLong = 128
Const adFldRowID = 256

' -----------------------------------------------------------------------------
' Comm Control
' -----------------------------------------------------------------------------

' Input Mode
Const comInputModeText = 0
Const comInputModeBinary = 1

' Handshaking
Const comNone = 0
Const comXOnXOff = 1
Const comRTS = 2
Const comRTSXOnXOff = 3

' Errors
Const comNoError = 0
Const comEventBreak = 1001         ' A Break siganl was received
Const comEventCTSTO = 1002         ' Clear To Send Timeout.
Const comEventDSRTO = 1003         ' Data Set REady Timeout.
Const comEventFrame = 1004         ' Framing Error
Const comEventOverrun = 1006       ' Port Overrun.
Const comEventCDTO = 1007          ' Carrier Detect Timeout.
Const comEventRxOver = 1008        ' Receive Buffer Overflow.
Const comEventRxParity = 1009      ' Parity Error.
Const comEventTxFull = 1010        ' Transmit Buffer Full.
Const comEventDCB = 1011           ' Unexpected error retrieving Device Control Block (DCB) for the port.


' Events
Const comEvSend = 1        ' There are fewer than Sthreshold number of characters in the transmit buffer.
Const comEvReceive = 2     ' Received Rthreshold number of characters.
Const comEvCTS = 3         ' Change in Clear To Send line.
Const comEvDSR = 4         ' Change in Data Set Ready line.
Const comEvCD = 5          ' Change in Carrier Detect line.
Const comEvRing = 6        ' Ring detected.
Const comEvEOF = 7         ' End Of File (ASCII character 26) character received.

' -----------------------------------------------------------------------------
' File/FileSystem Control
' -----------------------------------------------------------------------------

' File Mode
Const fsModeInput = 1
Const fsModeOutput = 2
Const fsModeRandom = 4
Const fsModeAppend = 8
Const fsModeBinary = 32

' File Access Type
Const fsAccessRead = 1
Const fsAccessWrite = 2
Const fsAccessReadWrite = 3

' File Lock Mode
Const fsLockReadWrite = 0
Const fsLockWrite = 1
Const fsLockRead = 2
Const fsLockShared = 3

' File Attributes
Const fsAttrNormal = 0
Const fsAttrReadOnly = 1
Const fsAttrHidden = 2
Const fsAttrSystem = 4
Const fsAttrVolume = 8
Const fsAttrDirectory = 16
Const fsAttrArchive = 32

' -----------------------------------------------------------------------------
' Winsock control
' -----------------------------------------------------------------------------

' Erorrs
Const sckOutOfMemory = 7                    ' Out of memory
Const sckInvalidPropertyValue = 380         ' The property value is invalid.
Const sckGetNotSupported = 394              ' The property can't be read.
Const sckSetNotSupported = 383              ' The property is read-only.
Const sckBadState = 40006                   ' Wrong protocol or connection state for the requested transaction or request.
Const sckInvalidArg = 40014                 ' The argument passed to a function was not in the correct format or in the specified range.
Const sckSuccess = 40017                    ' Successful.
Const sckUnsupported = 40018                ' Unsupported variant type.
Const sckInvalidOp = 40020                  ' Invalid operation at current state
Const sckOutOfRange = 40021                 ' Argument is out of range.
Const sckWrongProtocol = 40026              ' Wrong protocol for the requested transaction or request
Const sckOpCanceled = 10004                 ' The operation was canceled.
Const sckInvalidArgument = 10014            ' The requested address is a broadcast address, but flag is not set.
Const sckWouldBlock = 10035                 ' Socket is non-blocking and the specified operation will block.
Const sckInProgress = 10036                 ' A blocking Winsock operation in progress.
Const sckAlreadyComplete = 10037            ' The operation is completed. No blocking operation in progress
Const sckNotSocket = 10038                  ' The descriptor is not a socket.
Const sckMsgTooBig = 10040                  ' The datagram is too large to fit into the buffer and is truncated.
Const sckPortNotSupported = 10043           ' The specified port is not supported.
Const sckEAFNoSupport = 10047               ' Address family not supported by protocol family
Const sckAddressInUse = 10048               ' Address in use.
Const sckAddressNotAvailable = 10049        ' Address not available from the local machine.
Const sckNetworkSubsystemFailed = 10050     ' Network subsystem failed.
Const sckNetworkUnreachable = 10051         ' The network cannot be reached from this host at this time.
Const sckNetReset = 10052                   ' Connection has timed out when SO_KEEPALIVE is set.
Const sckConnectAborted = 10053             ' Connection is aborted due to timeout or other failure.
Const sckConnectionReset = 10054            ' The connection is reset by remote side.
Const sckNoBufferSpace = 10055              ' No buffer space is available.
Const sckAlreadyConnected = 10056           ' Socket is already connected.
Const sckNotConnected = 10057               ' Socket is not connected.
Const sckSocketShutdown = 10058             ' Socket has been shut down.
Const sckTimedout = 10060                   ' Socket has been shut down.
Const sckConnectionRefused = 10061          ' Connection is forcefully rejected.
Const sckNotInitialized = 10093             ' WinsockInit should be called first.
Const sckHostNotFound = 11001               ' Authoritative answer: Host not found.
Const sckHostNotFoundTryAgain = 11002       ' Non-Authoritative answer: Host not found.
Const sckNonRecoverableError = 11003        ' Non-recoverable errors.
Const sckNoData = 11004                     ' Valid name, no data record of requested type.

' Protocols
Const sckTCPProtocol = 0
Const sckIRDAProtocol = 2

' Socket state
Const sckClosed = 0
Const sckOpen = 1
Const sckListening = 2
Const sckConnectionPending = 3
Const sckResolvingHost = 4
Const sckHostResolved = 5
Const sckConnecting = 6
Const sckConnected = 7
Const sckClosing = 8
Const sckError = 9

