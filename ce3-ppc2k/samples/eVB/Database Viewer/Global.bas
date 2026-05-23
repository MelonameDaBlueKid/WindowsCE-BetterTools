Attribute VB_Name = "Global"
'THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
'ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
'THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
'PARTICULAR PURPOSE.

'Copyright  2000  Microsoft Corporation.  All Rights Reserved

Option Explicit

'Field type constants
Const adBoolean = 11
Const adDouble = 5
Const adDate = 7
Const adInteger = 3
Const adLongVarBinary = 205
Const adLongVarWChar = 203
Const adSmallInt = 2
Const adUnsignedSmallInt = 18
Const adVarBinary = 204
Const adVarWChar = 202


'Field attributes constants
Const adFldMayDefer = 2
Const adFldUpdatable = 4
Const adFldUnknownUpdatable = 8
Const adFldFixed = 16
Const adFldIsNullable = 32
Const adFldMayBeNull = 64
Const adFldLong = 128
Const adFldRowID = 256

Const SYSTEM_TABLE_LIST = "MSysTables; MSysIndexes; MSysFields; MSysProcs"

Public objConn, objRecTables, objRecFields, strActiveConnection, strSQL
Dim unexpectedError

Public Function AppPath()
    Dim path
    path = App.path
    If path = "\" Then
        AppPath = "\"
    Else
        AppPath = path & "\"
    End If
End Function

Public Sub DBConnect()
    Err.Clear
    unexpectedError = False
    
    Set objConn = CreateObject("ADOCE.Connection.3.0")
    Set objRecTables = CreateObject("ADOCE.Recordset.3.0")
    Set objRecFields = CreateObject("ADOCE.Recordset.3.0")
    
    objConn.ConnectionString = "provider=cedb;data source=" & strActiveConnection & ";"
    objConn.Open
    
    If Err Then
        unexpectedError = True
        MsgBox "Error occurred while connecting to database", vbCritical
        Err.Clear
    End If
End Sub


Public Sub GetTables()

    Err.Clear
    unexpectedError = False
    
    objRecTables.Open "msystables", strActiveConnection
    
    If Err Then
        unexpectedError = True
        MsgBox "Error occurred while open msystables table", vbCritical
        Err.Clear
    End If
    
End Sub


Public Sub GetFields(tbName)

    Err.Clear
    unexpectedError = False

    objRecFields.Open "'" & tbName & "'", strActiveConnection
    
    If Err Then
        unexpectedError = True
        MsgBox "Error occurred while open table " & tbName, vbCritical
        Err.Clear
    End If

End Sub


Public Sub DBClose()
    
    Err.Clear
    unexpectedError = False
    
    objRecTables.Close
    Set objRecTables = Nothing
    
    'objRecFields had already been closed
    Set objRecFields = Nothing
    
    objConn.Close
    Set objConn = Nothing
    
    If Err Then
        unexpectedError = True
        MsgBox "Error occurred while closing database", vbCritical
        Err.Clear
    End If
    
End Sub


Public Function IsSystemTable(tbName)
    
    If InStr(1, SYSTEM_TABLE_LIST, tbName, 1) = 0 Then
        IsSystemTable = False
    Else
        IsSystemTable = True
    End If
    
End Function


Public Function GetFieldAttributes(fieldAttributes)

    Select Case fieldAttributes
        Case adFldMayDefer: GetFieldAttributes = "adFldMayDefer"
        Case adFldUpdatable: GetFieldAttributes = "adFldUpdatable"
        Case adFldUnknownUpdatable: GetFieldAttributes = "adFldUnknownUpdatable"
        Case adFldFixed: GetFieldAttributes = "adFldFixed"
        Case adFldIsNullable: GetFieldAttributes = "adFldIsNullable"
        Case adFldMayBeNull: GetFieldAttributes = "adFldMayBeNull"
        Case adFldLong: GetFieldAttributes = "adFldLong"
        Case adFldRowID: GetFieldAttributes = "adFldRowID"
        Case Else: GetFieldAttributes = CStr(fieldAttributes)
    End Select
    
End Function


Public Function GetFieldType(fieldType)

    Select Case fieldType
        Case adBoolean: GetFieldType = "adBoolean"
        Case adDouble: GetFieldType = "adDouble"
        Case adDate: GetFieldType = "adDate"
        Case adInteger: GetFieldType = "adInteger"
        Case adLongVarBinary: GetFieldType = "adLongVarBinary"
        Case adLongVarWChar: GetFieldType = "adLongVarWChar"
        Case adSmallInt: GetFieldType = "adSmallInt"
        Case adUnsignedSmallInt: GetFieldType = "adUnsignedSmallInt"
        Case adVarBinary: GetFieldType = "adVarBinary"
        Case adVarWChar: GetFieldType = "adVarWChar"
        Case Else: GetFieldType = CStr(fieldType)
    End Select
    
End Function
