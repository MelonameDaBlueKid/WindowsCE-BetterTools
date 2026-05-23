<html>

<head>
<meta http-equiv="Content-Language" content="en-us">
<meta http-equiv="Content-Type" content="text/html; charset=windows-1252">
<link rel="stylesheet" type="text/css" href="/css/master.css">
<link rel="stylesheet" type="text/css" href="style.css">
<title>Device Configuration - TAPI</title>
<SCRIPT Language="Javascript">
function GoBack()
{
	window.location ="../xmlaction.asp"
}
</SCRIPT>
</head>
<body>
<h3>Device Configuration - TAPI</h3>
<p>Use this page to configure the phone's TAPI settings and call forwarding nformation.</p>
<form method="POST" action="../xmlgen.asp" name="forwarding">
    <input type="hidden" name="node" value="15">
  <table>
    <tr>
        <td><h3>Call Forwarding settings</h3></td>
        <td>&nbsp;</td>
    </tr>

    <tr>
        <td>Forwarding code:</td>
        <td>
            <select name="fwdcode">
                <option value="No-Reply">No-Reply
                <option value="Not-Reachable">Not-Reachable
                <option value="Busy">Busy
                <option value="Unconditional">Unconditional
            </select>
        </td>
    </tr>

        <td>Information class:</td>
        <td>
            <select name="infoclass">
                <option value="All-Bearers">All-Bearers
                <option value="Voice">Voice
                <option value="Data">Data
                <option value="Fax">Fax
                <option value="SMS">SMS
            </select>
        </td>
    </tr>

    <tr>
        <td>Forwarding number:</td>
        <td><input type="text" name="forwardnumber" size="10" value=""></td>
    </tr>

    <tr>
        <td>Forwarding timeout (seconds):</td>
        <td>
            <select name="timeout">
                <option value="5">5
                <option value="10">10
                <option value="15">15
                <option value="20">20
                <option value="25">25
                <option selected value="30">30
            </select>
        </td>
    </tr>

    <tr>
    <td><input type="submit" value="Submit">
    <input type="button" value="Cancel" name="CancelBtn" onclick="GoBack()">
    </td>
    <td>&nbsp;</td>
    </tr>
    </form>
</table>
<p>&nbsp;</p>
<form method="POST" action="../xmlgen.asp" name="tapi">
    <input type="hidden" name="node" value="20">
<table>
    <tr>
        <td><h3>TAPI Settings:</h3></td>
        <td>&nbsp;</td>
    </tr>
    <tr>
        <td>Country code:</td>
        <td><input type="text" name="countrycode" size="4" value=""></td>
    </tr>

    <tr>
        <td>Area code:</td>
        <td><input type="text" name="areacode" size="4" value=""></td>
    </tr>
    <tr>
        <td>Cell Broadcast Language:</td>
        <td>
            <select name="language">
                <option value="SMS_DCSLANG_UNKNOWN">Unknown
                <option value="SMS_DCSLANG_GERMAN">German
                <option value="SMS_DCSLANG_ENGLISH">English
                <option value="SMS_DCSLANG_ITALIAN">Italian
                <option value="SMS_DCSLANG_FRENCH">French
                <option value="SMS_DCSLANG_SPANISH">Spanish
                <option value="SMS_DCSLANG_DUTCH">Dutch
                <option value="SMS_DCSLANG_SWEDISH">Swedish
                <option value="SMS_DCSLANG_DANISH">Danish
                <option value="SMS_DCSLANG_PORTUGUESE">Portuguese
                <option value="SMS_DCSLANG_FINNISH">Finnish
                <option value="SMS_DCSLANG_NORWEGIAN">Norwegian
                <option value="SMS_DCSLANG_GREEK">Greek
                <option value="SMS_DCSLANG_TURKISH">Turkish
                <option value="SMS_DCSLANG_HUNGARIAN">Hungarian
                <option value="SMS_DCSLANG_POLISH">Polish
                <option value="SMS_DCSLANG_CZECH">Czech
                <option value="SMS_DCSLANG_ALL">All
            </select>
        </td>
    </tr>
        <td>Enable Cell Broadcast</td>
        <td>
            <select name="enablecellbroadcast">
                <option value="0">Off
                <option value="1">On
            </select>
        </td>
    </tr>
    </tr>
        <td>Enable Cell Broadcast Topic List:</td>
        <td>
            <select name="enablelist">
                <option value="0">Off
                <option value="1">On
            </select>
        </td>
    </tr>
    <tr>
        <td>Voicemail number, line 1:</td>
        <td><input type="text" name="voicemail1" size="10" value=""></td>
    </tr>

    <tr>
        <td>Voicemail number, line 2:</td>
        <td><input type="text" name="voicemail2" size="10" value=""></td>
    </tr>
    <tr>
        <td>Network call barring password:</td>
        <td><input type="text" name="callbarringpassword" size="10" value=""></td>
    </tr>
    <tr>
        <td>Fixed dialing PIN2:</td>
        <td><input type="text" name="pin2" size="4" value=""></td>
    </tr>
    <tr>
        <td>SMSC:</td>
        <td><input type="text" name="smsc" size="10" value=""></td>
    </tr>
    <tr>
        <td>Preferred Network:</td>
        <td><input type="text" name="preferrednetwork" size="15" value=""></td>
    </tr>
    <tr>
        <td>Select a network manually:</td>
        <td><input type="text" name="selectmanualnetwork" size="15" value=""></td>
    </tr>
    <tr>
        <td>Select a network automatically:</td>
        <td><input type="text" name="selectautonetwork" size="15" value=""></td>
    </tr>
    <tr>
        <td>Enable fixed digit dialing:</td>
        <td>
            <select name="enablefixeddigit">
                <option value="0">Off
                <option value="1">On
            </select>
        </td>
    </tr>

    <tr>
        <td>Bar outgoing calls:</td>
        <td>
            <select name="baroutgoing">
                <option value="0">Off
                <option value="1">On
            </select>
        </td>
    </tr>

    <tr>
        <td>Bar incoming calls:</td>
        <td>
            <select name="barincoming">
                <option value="0">Off
                <option value="1">On
            </select>
        </td>
    </tr>
    <tr>
        <td>Enable Call Waiting:</td>
        <td>
            <select name="enablecallwaiting">
                <option value="1">On
                <option value="0">Off
            </select>
        </td>
    </tr>
    <tr>
        <td>Send caller ID information:</td>
        <td>
            <select name="sendcallID">
                <option value="1">Yes
                <option value="0">No
            </select>
        </td>
    </tr>
  </table>
  <p><input type="submit" value="Submit">
  <input type="button" value="Cancel" name="CancelBtn" onclick="GoBack()"></p>
</form>
</body>
</html>
