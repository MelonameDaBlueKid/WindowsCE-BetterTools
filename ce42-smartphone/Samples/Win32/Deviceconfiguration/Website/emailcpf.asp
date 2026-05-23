<!--#include file="inc/globalvars.inc"-->
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
<%

szFileName = Request.QueryString("cpffile")
szTo = Request.QueryString("mailto")
szFrom = Request.QueryString("mailfrom")
szServer = Request.QueryString("emailserver")

on error resume next
Set objMsg = Server.CreateObject ("CDONTS.NewMail")
if err <> 0 then
	Response.Redirect("emailcpf2.aspx?mailto=" & szTo & "&cpffile=" & szFileName & "&from=" & szFrom & "&using=" & szServer)
else
	Set objFS = Server.CreateObject("Scripting.FileSystemObject")
	Set objAttachment = objFS.GetFile(Server.MapPath(szFileName))

	objMsg.AttachFile objAttachment, szPhone & ".cpf"
	objMsg.To = szTo
	objMsg.From = AdminEmailAddress
	objMsg.Body = "Install the attached file to provision your device"
	objMSg.Subject = "Your CPF file"

	objMsg.Send
end if

set objMsg = nothing
set objAttachment = nothing
set objFS = nothing

%>
Mail containing <%=Request.QueryString("userdata")("profilename")%>.cpf was sent to <%=szTo%> at <%=time%> <%=date%>.<br>
<br><br>
<form name="ReturnForm">
<input type="button" value="Done" name="B2" onclick="GoBack()">
</form>

</body>
</html>
