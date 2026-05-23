<html>

<head>
<meta http-equiv="Content-Language" content="en-us">
<meta http-equiv="Content-Type" content="text/html; charset=windows-1252">
<link rel="stylesheet" type="text/css" href="/css/master.css">
<link rel="stylesheet" type="text/css" href="style.css">
<title>Device Configuration - Metabase</title>
<SCRIPT Language="Javascript">
function GoBack()
{
	window.location ="../xmlaction.asp"
}
</SCRIPT>
</head>
<body>
<h3>Device Configuration - Metabase</h3>
<p>Use this page to modify the phone's metabase.</p>
<form method="POST" action="../xmlgen.asp">
    <input type="hidden" name="node" value="19">
  <table>
  <tr>
  <td colspan="2"><h4>Add</h4></td>
  </tr>
    <tr>
        <td>Entry name:</td>
        <td><input type="text" name="entry" size="45" value=""></td>
    </tr>
        <td>Data type:</td>
        <td>
            <select name="datatype">
                <option value="Integer">Integer
                <option value="String">String
                <option value="Float">Float
                <option value="Date">Date
                <option value="Time">Time
                <option value="Boolean">Boolean
                <option value="Binary">Binary
                <option value="Multiplestring">Multi-string
            </select>
        </td>
    </tr>

    <tr>
        <td>Minimum value:</td>
        <td><input type="text" name="minvalue" size="5" value=""></td>
    </tr>
    <tr>
        <td>Maximum value:</td>
        <td><input type="text" name="maxvalue" size="5" value=""></td>
    </tr>
    <tr>
        <td>Access role:</td>
        <td><input type="text" name="accessrole" size="5" value=""></td>
    </tr>

    <tr>
        <td>Read/Write access:</td>
        <td>
            <select name="rw">
                <option value="1">Read-Only
                <option value="2">Write-Only
                <option value="3">Read/Write
            </select>
        </td>
    </tr>
</table>
<table>
    <tr>
        <td><b>Label:</b></td>
        <td>&nbsp;</td>
    </tr>
    <tr>
        <td>Locale: <input type="text" name="labellocale1" size="5" value="0409"> Text: <input type="text" name="labeltext1" size="25" value=""</td>
    </tr>
    <tr>
        <td>Locale: <input type="text" name="labellocale2" size="5" value="0407"> Text: <input type="text" name="labeltext2" size="25" value=""</td>
    </tr>
    <tr>
        <td>Locale: <input type="text" name="labellocale3" size="5" value="040C"> Text: <input type="text" name="labeltext3" size="25" value=""</td>
    </tr>

  </table>
<table>
    <tr>
        <td><b>Options:</b></td>
        <td>&nbsp;</td>
    </tr>
    <tr>
        <td>Locale: <input type="text" name="optionslocale1" size="5" value="0409"> Text: <input type="text" name="optionstext1" size="25" value=""</td>
    </tr>
    <tr>
        <td>Locale: <input type="text" name="optionslocale2" size="5" value="0407"> Text: <input type="text" name="optionstext2" size="25" value=""</td>
    </tr>
    <tr>
        <td>Locale: <input type="text" name="optionslocale3" size="5" value="040C"> Text: <input type="text" name="optionstext3" size="25" value=""</td>
    </tr>

  </table>
  <p><input type="submit" value="Submit">
  <input type="button" value="Cancel" name="CancelBtn" onclick="GoBack()"></p>
  </form>
<table>
<form method="POST" action="../xmlgen.asp">
<input type="hidden" name="node" value="21">
<tr>
  <td colspan="2"><h4>Delete</h4></td>
</tr>
    <tr>
        <td>Entry name:</td>
        <td><input type="text" name="deleteentry" size="45" value=""></td>
    </tr>
</table>
  <p><input type="submit" value="Submit">
  <input type="button" value="Cancel" name="CancelBtn" onclick="GoBack()"></p>
</form>
</body>
</html>
