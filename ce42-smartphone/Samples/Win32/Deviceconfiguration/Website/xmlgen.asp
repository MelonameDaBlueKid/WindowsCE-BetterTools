<!--#include file="inc/globalvars.inc"-->
<html>
<head>
<title></title>

</head>
<body>
<%
function htmlize(rawstr)
        dim newstr
        set re = New RegExp

        re.Pattern = "&(?!amp;|lt;|gt;|quot;)"
        re.Global = true
        ' string to search, replace value
        newstr = re.Replace(rawstr, "&amp;")
        
        re.Pattern = "<"
        re.Global = true
        ' string to search, replace value
        newstr = re.Replace(newstr, "&lt;")
        
        re.Pattern = ">"
        re.Global = true
        ' string to search, replace value
        newstr = re.Replace(newstr, "&gt;")
        
        re.Pattern = """"
        re.Global = true
        ' string to search, replace value
        newstr = re.Replace(newstr, "&quot;")
        set re = nothing
        htmlize = newstr
end function

dim f, fs, tf, filename, node, bodyXML
dim fileNew
fileNew = false
node = Request.Form("node")

set fs=Server.CreateObject("Scripting.FileSystemObject")

' Make sure directory exists for the current profile
if not fs.FolderExists(path) = true then
    set f = fs.CreateFolder(path)
    set f = nothing
end if

if not (Session("used") = "1") then
    ' This is the first setting we've configured this session.  Clear the default file.
    defaultfilename = path + "\" & defaultfile
    Response.Write(defaultfilename)
    if (fs.FileExists(defaultfilename)) then
	    Set objFile = fs.GetFile(defaultfilename) 
    	objFile.Delete
    	set objFile = Nothing 
    end if
    
    relativepath = "profiles\" + Session("profilename") + "\"
    
    if Session("SavedFile") = 1 then
	    Set objFile = fs.GetFile(Server.MapPath(relativepath) & "\\" & Session("filename")) 
    	objFile.Copy Server.MapPath(relativepath) & "\\" & defaultfile, true
	    set objFile = Nothing 
	    
	    filename = path + "\" & defaultfile
    	set tf=fs.OpenTextFile(filename, 8, True)
    else 
    	filename = path + "\" & defaultfile
    	set tf=fs.CreateTextFile(filename)
    end if
    
    Session("used") = "1"
    Session("filename") = defaultfile
else
    ' We are appending to an existing configuration file.
    filename = path + "\" & Session("filename")
	set tf = fs.OpenTextFile(filename, 8, True)
end if

select case node
    ' no node
    case 0
'        bodyXML = bodyXML + "WARNING: NO NODE SELECTED" + vbcrlf
        bodyXML = ""

    ' Bootstrap, bootstrap.asp
    case 1
        %><!--#include file="inc/bootstrap.inc"--><%
        Session("Bootstrap") = "1"
                     
    ' Clock Settings, clock.asp
    case 6
        %><!--#include file="inc/clock.inc"--><%
        Session("Clock") = "1"
        
    ' Remove Programs, uninstall.asp
    case 9
        %><!--#include file="inc/uninstall.inc"--><%
        Session("Uninstall") = "1"
        
    ' PIE Favorites, favorite.asp
    case 10
        %><!--#include file="inc/favorite.inc"--><%
        Session("Favorite") = "1"
        
    ' Email, inbox.asp
    case 11
        %><!--#include file="inc/inbox.inc"--><%
        Session("Inbox") = "1"

    'Server Sync, serversync.asp
    case 12
        dim x, y, z
        x = Request.Form("Calendar")
        y = Request.Form("Contacts")
        z = Request.Form("Mail")
        if (not x = "1") then
            x = "0"
        end if
        if (not y = "1") then
            y = "0"
        end if
        if (not z = "1") then
            z = "0"
        end if
        %><!--#include file="inc/serversync.inc"--><%
        Session("ServerSync") = "1"
        
        
    'TAPI, tapi.asp
    case 15
        %><!--#include file="inc/callforwarding.inc"--><%
        Session("CallForward") = "1"
        
    'Certificate Store, certstore.asp
    case 16
        %><!--#include file="inc/certstore.inc"--><%
        Session("CertStore") = "1"

    'Certificate Revocation, certrevoke.asp
    case 17
        %><!--#include file="inc/certrevoke.inc"--><%
        Session("CertRevoke") = "1"

    'Security Policy, securitypolicy.asp
    case 18
        %><!--#include file="inc/securitypolicy.inc"--><%
        Session("Security") = "1"
        
    'Metabase add, metabase.asp
    case 19
        %><!--#include file="inc/metabaseadd.inc"--><%
        Session("MetabaseAdd") = "1"

    'TAPI, tapi.asp
    case 20
        %><!--#include file="inc/tapi.inc"--><%
        Session("TAPI") = "1"
    'Metabase delete, metabase.asp
    case 21
        %><!--#include file="inc/metabasedelete.inc"--><%
        Session("MetabaseDelete") = "1"
        
    ' PPP, connmgr.asp
    case 23
        %><!--#include file="inc/cm_ppp.inc"--><%
        Session("PPP") = "1"

    ' Proxy, connmgr.asp
    case 24
        %><!--#include file="inc/cm_proxy.inc"--><%
        Session("Proxy") = "1"

    ' VPN, connmgr.asp
    case 25
        %><!--#include file="inc/cm_vpn.inc"--><%
        Session("VPN") = "1"

    ' Mapping, connmgr.asp
    case 26
        %><!--#include file="inc/cm_mappings.inc"--><%
        Session("Mapping") = "1"

    ' Networks, connmgr.asp
    case 27
        %><!--#include file="inc/cm_networks.inc"--><%
        Session("Networks") = "1"

    ' GPRS, connmgr.asp
    case 28    
        %><!--#include file="inc/cm_gprs.inc"--><%
        Session("GPRS") = "1"
        
    case else
    Response.Write("Invalid node type")
end select

    bodyXML = htmlize(bodyXML)
    tf.Write(bodyXML)
    tf.Close
    set tf = nothing
    set fs = nothing

    Response.Redirect("mainpage.htm")
%>

</body>
</html>