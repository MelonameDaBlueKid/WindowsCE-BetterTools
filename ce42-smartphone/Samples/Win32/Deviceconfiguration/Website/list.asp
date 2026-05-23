<%

    function IsConfigured(cookie)
        if (Session(cookie) = "1") then
            Response.Write("<b class=""infotext""> (Configured)</b>")
        end if 
    end function

%>
<html>
<head>
<meta http-equiv="Content-Language" content="en-us">
<meta http-equiv="Content-Type" content="text/html; charset=windows-1252">
<link rel="stylesheet" type="text/css" href="/css/master.css">
<link rel="stylesheet" type="text/css" href="style.css">

</head>
<body>

<base target="main">
<h4>Settings</h4>
<p><a href="forms/bootstrap.asp">Bootstrap</a> </p>
<p><a href="forms/inbox.asp">Email</a> <%IsConfigured("Inbox")%><br><b>
<font size="2">(Smartphone 2003 and Pocket PC 2003 only) </font></b> </p>
<p><a href="forms/serversync.asp">ServerSync</a><%IsConfigured("ServerSync")%></p>
<p><a href="forms/favorite.asp">pIE Favorites</a> <%IsConfigured("Favorite")%> </p>
<p><a href="forms/clock.asp">Date and Time Settings</a> <%IsConfigured("Clock")%> </p>
<p><a href="forms/connmgr.asp">Connection Manager</a>
<p><a href="forms/uninstall.asp">Remove Programs</a> <%IsConfigured("Uninstall")%>
	<br><b><font size="2">(Smartphone only)</font></b><br></p>
<p><a href="forms/tapi.asp">TAPI</a><%IsConfigured("TAPI")%> <a href="forms/tapi.asp">and Call Forwarding</a> <%IsConfigured("CallForward")%>
	<br><b><font size="2">(Smartphone only)</font></b><br></p>
<p><a href="forms/certstore.asp">Certificate Store</a><%IsConfigured("CertStore")%></p>
<p><a href="forms/certrevoke.asp">Certificate Revocation</a><%IsConfigured("CertRevoke")%>
	<br><b><font size="2">(Smartphone only)</font></b><br></p>
<p><a href="forms/securitypolicy.asp">Security Policy</a><%IsConfigured("Security")%></p>
<p><a href="forms/metabase.asp">Metabase add</a> <%IsConfigured("MetabaseAdd")%> <a href="forms/metabase.asp"> and delete</a> <%IsConfigured("MetabaseDelete")%></p>

</body>
</html>
