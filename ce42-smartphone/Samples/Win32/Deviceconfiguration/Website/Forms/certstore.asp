<html>

<head>
<meta http-equiv="Content-Language" content="en-us">
<meta http-equiv="Content-Type" content="text/html; charset=windows-1252">
<link rel="stylesheet" type="text/css" href="/css/master.css">
<link rel="stylesheet" type="text/css" href="style.css">
<title>Device Configuration - Certificate Store</title>
<SCRIPT Language="Javascript">
function GoBack()
{
	window.location ="../xmlaction.asp"
}
</SCRIPT>
</head>
<body>
<h3>Device Configuration - Certificate Store</h3>
<p>Use this page to add a new certificate to the store or to add test provisioning certs.</p>
<form method="POST" action="../xmlgen.asp">
<input type="hidden" name="node" value="16">
  <table>
    <tr>
      <td >Select Store to add cert into: </td>
        <td>
            <select name="authority">
                <option value="Privileged Execution Trust Authorities">Privileged Execution Trust Authorities
                <option value="Unprivileged Execution Trust Authorities">Unprivileged Execution Trust Authorities
                <option value="CA">intermediary Certificate Authorities
                <option value="ROOT">Root (self-signed) Certificate
                <option value="SPC">Sofware Publishing Certificate (cab signing)
                <option value="MY">Personal Certificate
            </select>
      </td>
    </tr>
    <tr>
    <td>Cert hash: </td>
    <td><input type="text" name="hash" size="5"></td>
    </tr>
    <tr>
    <td>Rolemask: </td>
    <td><input type="text" name="rolemask" size="5"></td>
    </tr>
    <tr>
        <td>Paste cert here: </td>
        <td><textarea cols="50" rows="5" name="cert"></textarea></td>
    </tr>
  </table>
  <p><input type="submit" value="Submit">
  <input type="button" value="Cancel" name="CancelBtn" onclick="GoBack()"></p>
</form>
</body>
</html>
