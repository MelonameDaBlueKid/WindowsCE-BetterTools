<!--#include file="inc/globalvars.inc" -->
<html>

<head>
<meta http-equiv="Content-Language" content="en-us">
<meta http-equiv="Content-Type" content="text/html; charset=windows-1252">
<link rel="stylesheet" type="text/css" href="/css/master.css">
<link rel="stylesheet" type="text/css" href="style.css">
<title>Device Config - View XML</title>

</head>

<body>

<%
    Response.Write("&lt;wap-provisioningdoc&gt<br>")
    dim re, match
    filepath = "profiles\" + Session("profilename") + "\" + Request.querystring("filename")
    Set fs=Server.CreateObject("Scripting.FileSystemObject")
    Set f=fs.OpenTextFile(Server.MapPath(filepath), 1)
    do while f.AtEndOfStream = false
        Response.Write(f.ReadLine & "<br>")
    loop
    f.Close
    Set f=Nothing
    Set fs=Nothing
    Response.Write("&lt;/wap-provisioningdoc&gt;<br>")
%>


</body>
</html>
