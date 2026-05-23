<html>

<head>
<meta http-equiv="Content-Language" content="en-us">
<meta http-equiv="Content-Type" content="text/html; charset=windows-1252">
<link rel="stylesheet" type="text/css" href="/css/master.css">
<link rel="stylesheet" type="text/css" href="style.css">
<title>Device Configuration - Security Policy</title>
<SCRIPT Language="Javascript">
function GoBack()
{
	window.location ="../xmlaction.asp"
}
</SCRIPT>
</head>
<body>
<h3>Device Configuration - Security Policy</h3>
<p>Use this page to modify device security policy.</p>
<form method="POST" action="../xmlgen.asp">
<input type="hidden" name="node" value="18">
  <table>
    <tr>
      <td>Policy ID </td>
      <td><input type="text" name="id" size="4"></td>
      <td> Rolemask</td>
      <td><input type="text" name="rolemask" size="4"></td>
    </tr>
  </table>
  <p><input type="submit" value="Submit">
  <input type="button" value="Cancel" name="CancelBtn" onclick="GoBack()"></p>
</form>
</body>
</html>
