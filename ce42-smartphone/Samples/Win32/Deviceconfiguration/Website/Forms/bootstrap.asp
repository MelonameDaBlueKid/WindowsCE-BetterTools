<html>
<head>
<meta http-equiv="Content-Language" content="en-us">
<meta http-equiv="Content-Type" content="text/html; charset=windows-1252">
<link rel="stylesheet" type="text/css" href="/css/master.css">
<link rel="stylesheet" type="text/css" href="style.css">
<title>Device Configuration - Bootstrap Information</title>
<SCRIPT Language="Javascript">
function GoBack()
{
	window.location ="../xmlaction.asp"
}
</SCRIPT>
</head>
<body>
<h3>Device Configuration - Bootstrap Information</h3>
<p>The bootstrap document is information about WAP proxies, PPP dialup accounts and 
trusted gateways required by the phone to process some types of configuration documents and to make data calls. 
</p>
<p>For security reasons, your phone will prompt you for a password the first time you connect to the network.</p>

<form name="user" method="POST" action="../xmlgen.asp">
<input type="hidden" name="node" value="1">
<input type="hidden" name="TPPG" value="<!-- #include file="../inc/TPPG_address.inc" -->">
<input type="hidden" name="TPPGNAME" value="<!-- #include file="../inc/TPPG_name.inc" -->">
<table>
  <tr>
      <td colspan="2"><h4>WAP Bootstrap</h4></td>
  </tr>
    <tr>
        <td>RAS username: </td>
		<td><input type="text" name="wapusername" size="30" value=""></td>
        
    </tr>
    <tr>
        <td>RAS phone number: </td>
		<td><input type="text" name="wapphone" size="13" value=""></td>
        
    </tr>
    <tr>
        <td>WAP connection name:</td>
		<td><input type="text" name="friendlyname" size="20" value=""></td>     
    </tr>
    <tr>
        <td>WAP startpage:</td>
		<td><input type="text" name="startpage" size="40" value=""></td>     
    </tr>
    <tr>
        <td>WAP Gateway Address:</td>
		<td><input type="text" name="servername" size="30" value=""></td>     
    </tr>
  <tr>
      <td colspan="2"><p>&nbsp;<p><h4>PPP Connection</h4></td>
  </tr>
    <tr>
        <td>Friendly Name:</td>
        <td><input type="text" name="name" size="10" value=""></td>
    </tr>
    <tr>
        <td>Destination:</td>
        <td>
            <select name="dest">
                <option selected value="{436EF144-B4FB-4863-A041-8F905A62C572}">The Internet
                <option value="{A1182988-0D73-439e-87AD-2A5B369F808B}">Work
                <option value="{7022E968-5A97-4051-BC1C-C578E2FBA5D9}">Wap Network
                <option value="{F28D1F74-72BE-4394-A4A7-4E296219390C}">Secure Wap Network
            </select>
        </td>
    </tr>
    <tr>
        <td>Country Code:</td>
        <td><input type="text" name="countrycode" size="3" value=""></td>
    </tr>
    <tr>
        <td>Area Code:</td>
        <td><input type="text" name="areacode" size="3" value=""></td>
    </tr>
    <tr>
        <td>Phone Number:</td>
        <td><input type="text" name="phone" size="7" value=""></td>
    </tr>
    <tr>
        <td>Username:</td>
        <td><input type="text" name="username" size="8" value=""></td>
    </tr>
    <tr>
        <td>Password:</td>
        <td><input type="password" name="password" size="8" value=""></td>
    </tr>
    <tr>
        <td>Domain:</td>
        <td><input type="text" name="domain" size="8" value=""></td>
    </tr>
    <tr>
        <td><input type="submit" value="Submit">
        <input type="button" value="Cancel" name="CancelBtn" onclick="GoBack()">
        </td>
        <td>&nbsp;</td>
    </tr>
</table>
</form>
</body>
</html>
