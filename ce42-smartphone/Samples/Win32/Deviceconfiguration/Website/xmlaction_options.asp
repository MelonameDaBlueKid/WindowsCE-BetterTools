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
%>
<html>
<head>
<script language="JavaScript">
<!--
    function CheckForEnable(input, button) 
    {
        if (input.value.length > 0)
        {
            button.disabled = false;
        }
        else
        {
            button.disabled = true;
        }
    }
// -->
</script>
</head>
<body>
		<p style="margin-top: 0"><b>Submit Current Configuration:</b></p>
		<form name="sendData" method="POST" action="submitSMSC.asp">
		<input type="Submit" value="Submit">
		via Short Message Service (SMS) to device
		</form>
		<form name="emailCPF" method="POST" action="emailcpf.pl">
		<input type="hidden" name="xmlbody" value="<% = tagstart & bodyXML & tagend%>">
		<input type="hidden" name="profilename" value="<% = Session("profilename")%>">
		<input type="hidden" name="emailserver" value="<!-- #include file="inc/SMTP_Server.inc" -->">
		<input type="hidden" name="mailfrom" value="<!-- #include file="inc/Admin_Email.inc" -->">
		<input disabled type="submit" value="Submit" name="SubmitBtn">
		via Email as CPF attachment to:
		<input type="text" name="mailto" value="" size="30" onKeyUp="CheckForEnable(document.emailCPF.mailto, document.emailCPF.SubmitBtn)"> (enter email address here)
		</form>
		<form name="sendActiveSync" method="POST" action="makeandinstallcpf.pl">
		<input type="hidden" name="xmlbody" value="<% = tagstart & bodyXML & tagend%>">
		<input type="hidden" name="profilename" value="<% = Session("profilename")%>">
        <input type="submit" value="Submit">
		via desktop ActiveSync connection as CPF file
		</form>
        <form name="makeCPF" method="POST" action="makecpf.pl">
		<input type="hidden" name="xmlbody" value="<% = tagstart & bodyXML & tagend%>">
		<input type="hidden" name="profilename" value="<% = Session("profilename")%>">
        <input type=submit value="  Save ">
		to desktop as a CPF File
        </form>
</body>
</html>
