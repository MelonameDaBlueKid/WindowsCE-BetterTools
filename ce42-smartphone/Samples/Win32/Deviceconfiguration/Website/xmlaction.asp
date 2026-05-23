<% 
    if (Session("filename") = "") then
        Response.Redirect("loadfiles.asp")
   end if
%>
<html>
<head>
<meta http-equiv="Content-Language" content="en-us">
<meta name="GENERATOR" content="Microsoft FrontPage 5.0">
<meta name="ProgId" content="FrontPage.Editor.Document">
<meta http-equiv="Content-Type" content="text/html; charset=windows-1252">
<title>View Current Configuration</title>
<script language="JavaScript">
<!--
    function GotoSave()
    {
        window.location = "managefile.asp?action=save&file=" + document.frmSave.iFileSave.value;
    }
    
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

function Initialize()
{
<% 
	if (Session.Contents.Count > 1) then
        Response.Write("document.seexml.location = ""viewxml.asp?filename=" & Session("filename") & """ " & vbcrlf)
    end if
%>
	document.xmloption.location = "xmlaction_options.asp"
}
// -->
</script>
</head>

<body OnLoad="Initialize()">

<p style="margin-bottom: 0"><b>Current Configuration:</b></p>

<table>
<tr><td>
<p>
<iframe name="seexml" width="725" height="240" src="">
Your browser does not support inline frames or is currently configured not to display inline frames.</iframe>
</p>
</td></tr>
</table>
<table width="730">
<tr><td align="left">
<br>
<form name="frmSave">
Save current configuration on server for future use (Enter Filename): <input type="text" name="iFileSave" size="15" onKeyUp="CheckForEnable(document.frmSave.iFileSave, document.frmSave.cmdSave)">
<input disabled type="button" value="Save" onClick="GotoSave()" name="cmdSave">
</form>
</td>
<td align="right" >
<br>
<form name=save method=POST action=clearsession.asp>
	<input type=submit value="Clear Session">
</form>
</td></tr>
</table>
<hr>
<p style="margin-top: 0">
<iframe name="xmloption" width="725" height="350" src="">
Your browser does not support inline frames or is currently configured not to display inline frames.</iframe>
</p>
</body>
</html>
