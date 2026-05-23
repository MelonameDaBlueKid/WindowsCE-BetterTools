<html>
<head>
<title></title>

</head>

<body>
<%
if Session("profilename") <> "" then
    filename = Server.MapPath("profiles\" & Session("profilename") & "\" & defaultfile)

    set fs=Server.CreateObject("Scripting.FileSystemObject")
    if fs.FileExists(filename) then
	    fs.DeleteFile(filename)
    end if
end if

Session.Abandon
Response.Redirect("default.asp")
%>
</body>
</html>