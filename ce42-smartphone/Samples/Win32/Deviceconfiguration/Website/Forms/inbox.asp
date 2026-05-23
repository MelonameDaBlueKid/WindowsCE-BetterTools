<html>
<head>
<meta http-equiv="Content-Language" content="en-us">
<meta http-equiv="Content-Type" content="text/html; charset=windows-1252">
<link rel="stylesheet" type="text/css" href="/css/master.css">
<link rel="stylesheet" type="text/css" href="style.css">
<title>Device Configuration - Email</title>
<SCRIPT Language="Javascript">
function GoBack()
{
	window.location ="../xmlaction.asp"
}
</SCRIPT>
</head>
<body>
<h3>Device Configuration - Email</h3>
<p>Use this page to configure Inbox to receive Internet email.  Please note that Inbox cannot receive both Server ActiveSync messages and Internet email messages.  Any configuration of one will cause the other's store and configuration information to be deleted.</p>
<p>For security reasons, the phone will prompt for your password when syncing mail for the first time.</p>
<form method="POST" action="../xmlgen.asp">
<input type="hidden" name="node" value="11">
  <table>
    <tr>
      <td class="label">Name: </td>
      <td><input type="text" name="name" size="25" value=""></td>
    </tr>
    <tr>
        <td>Email address: </td>
        <td><input type="text" name="email" size="25" value=""></td>
    </tr>
    
    <tr>
        <td>Protocol: </td>
        <td>
            <select name="protocol">
                <option value="IMAP4">IMAP4
                <option value="POP3">POP3
            </select>
        </td>
    </tr>

    <tr>
        <td>Incoming Server <br>(POP3 or IMAP4): </td>
        <td><input type="text" name="incomingserver" size="30" value=""></td>
    </tr>

    <tr>
        <td>Outgoing Server <br>(SMTP): </td>
        <td><input type="text" name="outgoingserver" size="30" value=""></td>
    </tr>

    <tr>
        <td>Login: </td>
        <td><input type="text" name="username" size="10" value=""></td>
    </tr>

    <tr>
        <td>Network: </td>
        <td>
            <select name="network">
                <option selected value="{436EF144-B4FB-4863-A041-8F905A62C572}">The Internet
                <option value="{A1182988-0D73-439e-87AD-2A5B369F808B}">Work
            </select>
        </td>
    </tr>

    <tr>
        <td>Password:</td>
        <td><input type="password" name="password" size="8" value=""></td>
    </tr>

    <tr>
        <td>Domain Name: </td>
        <td><input type="text" name="domain" size="10" value=""></td>
    </tr>
  </table>
  <p><input type="submit" value="Submit">
  <input type="button" value="Cancel" name="CancelBtn" onclick="GoBack()">
  </p>
</form>
</body>
</html>
