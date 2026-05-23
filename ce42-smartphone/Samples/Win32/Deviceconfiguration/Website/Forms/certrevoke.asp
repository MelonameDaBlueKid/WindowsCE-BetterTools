<html>

<head>
<meta http-equiv="Content-Language" content="en-us">
<meta http-equiv="Content-Type" content="text/html; charset=windows-1252">
<link rel="stylesheet" type="text/css" href="/css/master.css">
<link rel="stylesheet" type="text/css" href="style.css">
<title>Device Configuration - Certificate Revocation</title>
<SCRIPT Language="Javascript">
function GoBack()
{
	window.location ="../xmlaction.asp"
}
</SCRIPT>
</head>
<body>
<h3>Device Configuration - Certificate Revocation</h3>
<p>Use this page to revoke a certificate.</p>
<form method="POST" action="../xmlgen.asp">
<input type="hidden" name="node" value="17">
  <table>
    <tr>
      <td >Hash of certificate to be revoked: </td>
        <td>
            <input type="text" name="hash" size="25">
      </td>
    </tr>
  </table>
  <p><input type="submit" value="Submit">
  <input type="button" value="Cancel" name="CancelBtn" onclick="GoBack()"></p>
</form>
</body>
</html>
