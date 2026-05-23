This Windows CE DLL shows how to implement a OLEDB Simple Provider using the OLEDB Simple Provider
Toolkit.  This provider allows access to a simple flat file format.

Steps for running FileOSP sample application:

1. Compile and download FileOSP.DLL to the device or emulation. 
2. Using ActiveSync, copy sample.txt to the \My Documents folder.
3. Open eMbedded Visual Basic on the desktop.
4. Create a new Pocket PC project.
5. In Project->References dialog, select "Microsoft CE ADO Control 3.0"
6. Add a command button to the main form.
7. Insert the following code into the command button's click event handler.

    Dim rs As ADOCE.Recordset
    Dim Data As String
    Dim iField As Integer
    
    Set rs = CreateObject("ADOCE.Recordset.3.0")
    
    rs.Open "\My Documents\sample.txt", "Provider=FileOSPSample"
    
    While rs.EOF <> True
        
        For iField = 0 To rs.Fields.Count - 1
            Data = Data & "'" & rs.Fields(iField).Value & "' "
        Next iField
        Data = Data & vbCrLf
        rs.MoveNext
    Wend
    
    MsgBox Data, , "\My Documents\sample.txt"
    
    rs.Close

8. Press the "Play" button to run the code on the device or emulation.
9. Click Command1 to see the data from sample.txt

