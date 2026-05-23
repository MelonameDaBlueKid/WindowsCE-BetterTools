<%
dim hardpath, path, defaultfile
hardpath = Server.MapPath("profiles")
path = hardpath & "\" & Session("profilename")
defaultfile = "scratchpad.xml"
%>
