<html>

<head>
<meta http-equiv="Content-Language" content="en-us">
<meta http-equiv="Content-Type" content="text/html; charset=windows-1252">
<link rel="stylesheet" type="text/css" href="/css/master.css">
<link rel="stylesheet" type="text/css" href="style.css">
<title>Device Configuration - Remove Programs</title>
<SCRIPT Language="Javascript">
function GoBack()
{
	window.location ="../xmlaction.asp"
}
</SCRIPT>
</head>

<body>

<h3>Device Configuration - Remove Programs</h3>
<p>Use this page to uninstall applications through over-the-air configuration.</p>
<form name="uninstall" method="POST" action="../xmlgen.asp">
<input type="hidden" name="node" value="9">
  <table>
    <tr>
      <td class="label">Name of the application to uninstall: </td>
      <td><input type="text" name="app" size="50" value=""></td>
    </tr>
  </table>
  <p><input type="submit" value="Submit">
  <input type="button" value="Cancel" name="CancelBtn" onclick="GoBack()"></p>
</form>
</body>
</html>
