<html>
<head>
<meta http-equiv="Content-Language" content="en-us">
<meta http-equiv="Content-Type" content="text/html; charset=windows-1252">
<link rel="stylesheet" type="text/css" href="/css/master.css">
<link rel="stylesheet" type="text/css" href="style.css">
<title>Device Configuration - Connection Manager</title>
<SCRIPT Language="Javascript">
function GoBack()
{
	window.location ="../xmlaction.asp"
}
</SCRIPT>
</head>
<body>
<h3>Device Configuration - Connection Manager</h3>
<p>Use this page to add Connection Manager settings.</p>
<form method="POST" action="../xmlgen.asp" name="ppp">
    <input type="hidden" name="node" value="23">
  <table>
  <tr>
      <td colspan="2"><h4>Add PPP Connection</h4></td>
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

    <tr><td colspan=2><table style="border:thin black solid;background-color:lightgrey;">
    <tr>
	<td><i>Advanced:</i></td>
	<td></td>
    </tr>
    <tr>
        <td>DNS1:</td>
        <td><input type="text" name="dns1" size="15" value=""></td>
    </tr>
    <tr>
        <td>DNS2:</td>
        <td><input type="text" name="dns2" size="15" value=""></td>
    </tr>
    <tr>
        <td>WINS1:</td>
        <td><input type="text" name="wins1" size="15" value=""></td>
    </tr>
    <tr>
        <td>WINS2:</td>
        <td><input type="text" name="wins2" size="15" value=""></td>
    </tr>
    </table></td></tr>
    <tr>
        <td><input type="submit" value="Submit">
        <input type="button" value="Cancel" name="CancelBtn" onclick="GoBack()"></td>
        <td>&nbsp;</td>
    </tr>
</table>
</form>

<form method="POST" action="../xmlgen.asp" name="proxy">
    <input type="hidden" name="node" value="24">
  <table>
  <tr>
  <td colspan="2"><h4>Add Proxy Entry</h4></td>
  </tr>
    <tr>
        <td>Proxy name:</td>
        <td><input type="text" name="name" size="10" value=""></td>
    </tr>
    <tr>
        <td>Type:</td>
        <td>
            <select name="type">
                <option selected value="1">HTTP
                <option value="4">SOCKS4
                <option value="8">SOCKS5
            </select>
        </td>
    </tr>

    <tr>
        <td>Source:</td>
        <td>
            <select name="src">
                <option selected value="{436EF144-B4FB-4863-A041-8F905A62C572}">The Internet
                <option value="{A1182988-0D73-439e-87AD-2A5B369F808B}">Work
                <option value="{7022E968-5A97-4051-BC1C-C578E2FBA5D9}">Wap Network
                <option value="{F28D1F74-72BE-4394-A4A7-4E296219390C}">Secure Wap Network
            </select>
        </td>
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
        <td>Servername:port:</td>
        <td><input type="text" name="server" size="20" value=""></td>
    </tr>

    <tr>
        <td>Username: (blank if none)</td>
        <td><input type="text" name="username" size="8" value=""></td>
    </tr>
    <tr>
        <td>Password: (blank if none)</td>
        <td><input type="password" name="password" size="12" value=""></td>
    </tr>
    <tr>
        <td><input type="submit" value="Submit">
        <input type="button" value="Cancel" name="CancelBtn" onclick="GoBack()">
        </td>
        <td>&nbsp;</td>
    </tr>
</table>
</form>

<form method="POST" action="../xmlgen.asp" name="VPN">
    <input type="hidden" name="node" value="25">
  <table>
  <tr>
  <td colspan="2"><h4>Add VPN Entry</h4></td>
  </tr>
    <tr>
        <td>VPN name:</td>
        <td><input type="text" name="name" size="12" value=""></td>
    </tr>
    <tr>
        <td>Source:</td>
        <td>
            <select name="src">
                <option selected value="{436EF144-B4FB-4863-A041-8F905A62C572}">The Internet
                <option value="{A1182988-0D73-439e-87AD-2A5B369F808B}">Work
                <option value="{7022E968-5A97-4051-BC1C-C578E2FBA5D9}">Wap Network
                <option value="{F28D1F74-72BE-4394-A4A7-4E296219390C}">Secure Wap Network
            </select>
        </td>
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
        <td>Phone:</td>
        <td><input type="text" name="phone" size="30" value=""></td>
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
        <td><input type="text" name="domain" size="10" value=""></td>
    </tr>

    <tr>
        <td>Type:</td>
        <td>
            <select name="type" >
                <option selected value="0">PPTP
                <option value="1">IPSec/L2TP
            </select>
        </td>
    </tr>
    <tr id=ipsecauthrow style="display:none">
        <td>IP Sec Auth:</td>
        <td>
            <select name="ipsecauth" >
                <option selected value="0">Certificate
                <option value="1">Pre-shared Key
            </select>
        </td>
    </tr>
    <tr id=presharedkeyrow style="display:none">
        <td>Pre-Shared Key:</td>
        <td><input type="text" name="presharedkey" size="16" value=""></td>
    </tr>
    <tr>
        <td><input type="submit" value="Submit">
        <input type="button" value="Cancel" name="CancelBtn" onclick="GoBack()">
        </td>
        <td>&nbsp;</td>
    </tr>

</table>
</form>

<form method="POST" action="../xmlgen.asp" name="GPRS">
    <input type="hidden" name="node" value="28">
  <table>
  <tr>
      <td>
      <h4>Add a GPRS Connection</h4>
      </td>
      <td>&nbsp;</td>
  </tr>
  <tr>

  </tr>
    <tr>
        <td>Friendly Name:</td>
        <td><input type="text" name="name" size="17" value=""></td>
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
        <td>Bearer Info Valid:</td>
        <td>
            <select name="bearerinfovalid">
                <option selected value="1">Yes
                <option value="0">No
            </select>
        </td>
    </tr>
    <tr>
        <td>GPRS Info Valid:</td>
        <td>
            <select name="gprsinfovalid">
                <option selected value="1">Yes
                <option value="0">No
            </select>
        </td>
    </tr>
    <tr>
        <td>GPRS Protocol Type:</td>
        <td>
            <select name="gprsprotocol">
                <option value="1">X25
                <option selected value="2">IP
                <option value="3">IHOSP
                <option value="4">PPP
            </select>
        </td>
    </tr>
    <tr>
        <td>GPRS L2 Protocol Type:</td>
        <td>
            <select name="gprsl2protocol">
                <option value="1">NULL
                <option selected value="2">PPP
                <option value="3">PAD
                <option value="4">X25
            </select>
        </td>
    </tr>
    <tr>
        <td>Info access point name:</td>
        <td><input type="text" name="pointname" size="30" value=""></td>
    </tr>
    <tr>
        <td>Info address:</td>
        <td><input type="text" name="infoaddress" size="30" value=""></td>
    </tr>
    <tr>
        <td>GPRS Data Compression:</td>
        <td>
            <select name="gprsdatacompression">
                <option selected value="1">Yes
                <option value="0">No
            </select>
        </td>
    </tr>
    <tr>
        <td>GPRS Header Compression:</td>
        <td>
            <select name="gprsheadercompression">
                <option selected value="1">Yes
                <option value="0">No
            </select>
        </td>
    </tr>
    <tr>
        <td><input type="submit" value="Submit">
        <input type="button" value="Cancel" name="CancelBtn" onclick="GoBack()">
        </td>
        <td>&nbsp;</td>
    </tr>
</table>
</form>
<form method="POST" action="../xmlgen.asp" name="mapping">
    <input type="hidden" name="node" value="26">
  <table>
  <tr>
  <td colspan="2"><h4>Add Connection Manager Mapping</h4></td>
  </tr>
    <tr>
        <td>Mapping index: (must be &gt; 500)</td>
        <td><input type="text" name="index" size="5" value=""></td>
    </tr>
    <tr>
        <td>Pattern:</td>
        <td><input type="text" name="pattern" size="25" value="*://*.msn.com/*"></td>
    </tr>
    <tr>
        <td>Network:</td>
        <td>
            <select name="network">
                <option selected value="{436EF144-B4FB-4863-A041-8F905A62C572}">The Internet
                <option value="{A1182988-0D73-439e-87AD-2A5B369F808B}">Work
                <option value="{7022E968-5A97-4051-BC1C-C578E2FBA5D9}">Wap Network
                <option value="{F28D1F74-72BE-4394-A4A7-4E296219390C}">Secure Wap Network
            </select>
        </td>
    </tr>
    <tr>
        <td><input type="submit" value="Submit">
        <input type="button" value="Cancel" name="CancelBtn" onclick="GoBack()">
        </td>
        <td>&nbsp;</td>
    </tr>

</table>
</form>

<form method="POST" action="../xmlgen.asp" name="network">
    <input type="hidden" name="node" value="27">
  <table>
  <tr>
      <td colspan="2"><h4>Add a Network</h4></td>
  </tr>
    <tr>
        <td>Friendly Name:</td>
        <td><input type="text" name="name" size="10" value=""></td>
    </tr>
    <tr>
        <td>GUID:</td>
        <td><input type="text" name="guid" size="25" value=""></td>
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
