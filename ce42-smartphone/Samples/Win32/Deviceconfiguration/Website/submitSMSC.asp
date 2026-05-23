<% 
        ' Fill in the XML body field
        ' Assumption is that there will be a config XML file present.
        filename = "profiles\" + Session("profilename") + "\" + Session("filename")

        set fs=Server.CreateObject("Scripting.FileSystemObject")
        
        if ( not fs.FileExists(Server.MapPath(filename)) ) then
        	Response.Redirect("loadfiles.asp")
        end if
        set f=fs.OpenTextFile(Server.MapPath(filename), 1)

        bodyXML = ""
        do while f.AtEndOfStream = false
            bodyXML = bodyXML + f.ReadLine
        loop
        f.Close

        set f=Nothing
        set fs=Nothing
        set re=Nothing

        tagstart = "&lt;wap-provisioningdoc&gt;" 
        tagend   = "&lt;/wap-provisioningdoc&gt;"
        
        TempLoc = Request.ServerVariables("URL")
		TempLoc = Left(TempLoc, InStrRev(TempLoc, "/")-1)	
		extraheaders = "X-WAP-Initiator-URI: http://" + Request.ServerVariables("SERVER_NAME")
		extraheaders = extraheaders + TempLoc + vbcrlf
        extraheaders = extraheaders + "X-MS-Desc: Device Config Website" + vbcrlf
        
        szPhone = Session("phone")
%>
<html>
<head>
<SCRIPT Language="Javascript">
function GoBack()
{
	window.location ="xmlaction_options.asp"
}
</SCRIPT>
</head>
<body>
<form name="sendData" method="POST" action="<!-- #include file="inc/TPPG_address.inc" -->">
<table>
<tr>
    <td>Phone Number</td><td><input type="text" name="destaddr" size="20" value="<% = szPhone%>"></td>
</tr><tr>
		<!--
		Here, put additional information that the SMSC requires.
		The first two hidden fields are samples of such information.
		-->
        <input type="hidden" name="destport" value="2006">
        <input type="hidden" name="sourceport" value="1052">
        <input type="hidden" name="body" value="<% = tagstart & bodyXML & tagend%>">
        <input type="hidden" name="extraheaders" value="<% = extraheaders%>">
        <input type="hidden" name="sec" value="2">
    <td>IMSI</td><td><input type="text" name="imsi" size="35"> </td>
</tr><tr>
    <td>Pin</td><td><input type="text" name="pin" size="4"></td>
</tr>
</table>
<input type="submit" value="Send SMS">
</form>
<form name="ReturnForm">
<input type="button" value="  Go Back  " name="B2" onclick="GoBack()">
</form>
</body>
</html>
