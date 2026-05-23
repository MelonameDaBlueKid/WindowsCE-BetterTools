<%
' Force Authentication from the client browser
if (Request.ServerVariables("LOGON_USER") = "")  then
	Response.Status = "401 Access Denied"
	Response.End
end if
%>
<!--#include file="inc/server.inc"-->
<HTML>
<HEAD>
<meta HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=windows-1252">
<meta http-equiv="Content-Language" content="en-us">
<TITLE>Device Configuration Page</TITLE>
<SCRIPT LANGUAGE="JAVASCRIPT">
<!-- Hide from old Browsers
if (top != self) top.location.href = location.href;
// Stop hiding from old browsers -->
</SCRIPT>
</HEAD>
<BODY>
<H1 align="center">Device Configuration Page</H1>
<p align="center">For Smartphone 2002, Smartphone 2003 and Pocket PC 2003 
Devices</p>
<HR>
<%
pageerror = Request.querystring("error")
if pageerror <> "" then
	Response.Write (pageerror & "<br>")
end if
%>
<FORM METHOD="POST" ACTION="userset.asp">

<TABLE>
<TR>
<TD>
Enter your phone number: (optional)
</TD>
<TD>
<INPUT TYPE=TEXT NAME="Phone" SIZE=25 MAXLENGTH=25>
</TD>
</TR>
<TR>
<TD>
Enter your user name:
</TD>
<TD>
<INPUT TYPE=TEXT NAME="UserName" VALUE="<%=GetUser()%>" SIZE=25 MAXLENGTH=25>
</TD>
</TR>
</TABLE>
</BLOCKQUOTE>
<INPUT TYPE=SUBMIT VALUE="Submit">&nbsp;
</FORM>
<HR>
</BODY>
</HTML>