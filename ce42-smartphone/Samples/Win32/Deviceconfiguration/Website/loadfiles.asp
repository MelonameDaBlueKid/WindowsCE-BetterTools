<!--#include file="inc/globalvars.inc"-->
<html>
<head>
<meta http-equiv="Content-Language" content="en-us">
<meta http-equiv="Content-Type" content="text/html; charset=windows-1252">
<link rel="stylesheet" type="text/css" href="/css/master.css">
<link rel="stylesheet" type="text/css" href="style.css">

<script language="JavaScript">
<!--
    function GotoDelete()
    {
        window.location = "managefile.asp?action=delete&file=" + document.frmFile.files[document.frmFile.files.selectedIndex].value;
    }

    function GotoRename()
    {
        window.location = "managefile.asp?action=rename&file=" + document.frmFile.files[document.frmFile.files.selectedIndex].value + "&new=" + document.frmFile.iRename.value;
    }

    function GotoLoad()
    {
        window.location = "managefile.asp?action=load&file=" + document.frmFile.files[document.frmFile.files.selectedIndex].value;
    }
    
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
// -->
</script>
</head>
<body>
<%
	Response.Write("<p><b>Current Configuration:</b></p>")
	Response.Write("<p>Nothing configured yet. Start configuring the settings from the links on the left")

	set fs = Server.CreateObject("Scripting.FileSystemObject")
    if not fs.FolderExists(path) = true then
       set f = fs.CreateFolder(path)
       set f = nothing
    end if
    
    set folder = fs.GetFolder(path)
    ReDim arFiles(512)

    for each fil In folder.files
        currfilename = fs.GetFileName(fil)
        if currFileName <> defaultfile then
           arFiles(i) = currfilename
           i = i + 1
        end if
    next

    ReDim Preserve arFiles(i + 1)
    if (i > 0) then
    	Response.Write(" or load pre-configured settings from a saved file.</p>")
        Response.Write("<p><b>Saved config files:</b></p>" & vbcrlf)
        Response.Write("<form name=""frmFile"">" & vbcrlf)
        Response.Write("<select name =""files"" size=""3"">" & vbcrlf)
        selected = "selected"
        dim counter
        counter = 0
        for j = 0 to (UBound(arFiles)) 
           ' select the first element
           if counter = 0 then
               Response.Write("<option selected" & " value=""" & arFiles(j) & """" & ">" & arFiles(j) & vbcrlf)
               counter = counter + 1
           else
               Response.Write("<option value=""" & arFiles(j) & """" & ">" & arFiles(j) & vbcrlf)                    
           end if
        next
        
        Response.Write("</select><br>" & vbcrlf)
        Response.Write("<input type=""button"" onClick=""GotoLoad()"" value=""Load"">&nbsp;" & vbcrlf)
        Response.Write("<input type=""button"" onClick=""GotoDelete()"" value=""Delete"">&nbsp;" & vbcrlf)
        Response.Write("<input disabled type=""button"" onClick=""GotoRename()"" value=""Rename "" name=""cmdRename""> file as: <input type=""text"" name=""iRename"" size=""20"" value="""" onKeyUp=""CheckForEnable(document.frmFile.iRename, document.frmFile.cmdRename)"">" & vbcrlf)
        Response.Write("</form>")
        Response.Write("")

        set folder = nothing
        set fs = nothing
    else
        Response.Write("<p>No configuration files saved.</p>")
    end if
%>


</body>
</html>