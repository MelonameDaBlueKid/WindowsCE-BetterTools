<%

errorstr = ""

' place to do error checking on user input
' if there is an error, set errorstr here

phone = Request.Form("Phone")
profilename = Request.Form("UserName")

if profilename = "" then
	errorstr = "Please enter a user name"
end if

if errorstr <> "" then
    Response.Redirect("default.asp?error=" & errorstr)
else
	Session("phone") = phone
	Session("profilename") = profilename

%>
<!--#include file="inc/globalvars.inc"-->
<%
	set fs = CreateObject("Scripting.FileSystemObject")
	filename = path &  "\" & defaultfile
	if (fs.FileExists(filename)) then
		fs.DeleteFile(filename)
	end if

	Response.Redirect("mainpage.htm")
end if
%>
