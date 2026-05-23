<%
    Response.Expires = 0
    Response.Buffer = True
%>
<!--#include file="inc/globalvars.inc"-->
<html>
<head>
</head>
<body>
<%
dim action, file, fs, relativepath, relativefilename, newname, tf, objFile, arFiles(), folder
action = Request.querystring("action")
file   = Request.querystring("file")
relativepath = "profiles\" + Session("profilename") + "\"
relativefilename = relativepath + file
tobesaved = relativepath + Session("filename")
newname = relativepath + Request.querystring("new")

set fs = Server.CreateObject("Scripting.FileSystemObject")

if (action = "delete") then
    Set objFile = fs.GetFile(Server.MapPath(relativefilename)) 
    objFile.Delete
    i = 0
    set folder = fs.GetFolder(path)
    ReDim arFiles(512)
    for each relativepath In folder.files
        arFiles(i) = fs.GetFileName(relativepath)
        i = i + 1
    next
    
    Response.Redirect("loadfiles.asp")    
elseif (action = "rename") then
' reset the cookie to the default file
    fs.MoveFile Server.MapPath(relativefilename), Server.MapPath(newname)
    Response.Redirect("loadfiles.asp")
elseif (action = "load") then
' swap cookie here for main page to load
    Session("filename") = file
    Session("SavedFile") = "1"
    Response.Redirect("mainpage.htm")
elseif (action = "save") then
' Copy the temp file to the new filename provided
    Set objFile = fs.GetFile(Server.MapPath(tobesaved)) 
    objFile.Copy Server.MapPath(relativepath) & "\\" & file, true
    set objFile = Nothing 
    set fs = Nothing 
    Response.Redirect("mainpage.htm")
else
    Response.Redirect("mainpage.htm")
end if

%>

</body>
</html>
