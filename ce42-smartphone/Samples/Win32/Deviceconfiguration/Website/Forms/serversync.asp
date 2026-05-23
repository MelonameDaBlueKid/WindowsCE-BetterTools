<html>

<head>
<meta http-equiv="Content-Language" content="en-us">
<meta http-equiv="Content-Type" content="text/html; charset=windows-1252">
<link rel="stylesheet" type="text/css" href="/css/master.css">
<link rel="stylesheet" type="text/css" href="style.css">
<title>Device Configuration - Server Sync</title>
<SCRIPT Language="Javascript">
function GoBack()
{
	window.location ="../xmlaction.asp"
}
</SCRIPT>
</head>
<body>
<h3>Device Configuration - Server Sync</h3>
<p>Use this page to configure Pocket Outlook applications to receive Outlook items via Server ActiveSync.  Please note that Inbox cannot receive both ServerSync messages and Internet email messages.  Any configuration of one will cause the other's store and configuration information to be deleted.</p>
<p>For security reasons, the phone will prompt for your password when syncing mail for the first time.</p>
<form method="POST" action="../xmlgen.asp">
<input type="hidden" name="node" value="12">
  <table>
    <tr>
      <td class="label">Login: </td>
      <td><input type="text" name="login" size="25" value=""></td>
    </tr>

    <tr>
        <td>Password:</td>
        <td><input type="password" name="password" size="8" value=""></td>
    </tr>

    <tr>
        <td>Server: </td>
        <td><input type="text" name="server" size="30" value=""></td>
    </tr>

    <tr>
        <td>Domain Name: </td>
        <td><input type="text" name="domain" size="10" value=""></td>
    </tr>
   <tr>
        <td>Items to sync: </td>
        <td>
        Email 
        <input type="checkbox" name="Mail" value="1" checked>
        &nbsp; Contacts 
        <input type="checkbox" name="Contacts" value="1" checked>
        &nbsp; Calendar 
        <input type="checkbox" name="Calendar" value="1" checked></td>
    </tr>
     
  </table>
  <p><input type="submit" value="Submit">
  <input type="button" value="Cancel" name="CancelBtn" onclick="GoBack()"></p>
</form>
</body>
</html>
