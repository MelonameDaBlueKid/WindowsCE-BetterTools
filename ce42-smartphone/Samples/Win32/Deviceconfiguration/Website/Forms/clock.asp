<html>
<head>
<meta http-equiv="Content-Language" content="en-us">
<meta http-equiv="Content-Type" content="text/html; charset=windows-1252">
<link rel="stylesheet" type="text/css" href="/css/master.css">
<link rel="stylesheet" type="text/css" href="style.css">
<title>Device Configuration - Clock Settings</title>
<SCRIPT Language="Javascript">
function GoBack()
{
	window.location ="../xmlaction.asp"
}
</SCRIPT>
</head>
<body>
<h3>Device Configuration - Clock Settings</h3>
<p>Here you can set the phone's date and time, set an alarm and turn it on and off, and change the time zone.  
</p>

<form name="user" method="POST" action="../xmlgen.asp">
<input type="hidden" name="node" value="6">
<table>
    <tr><td colspan="8"><h4>Device Time</h4></td></tr>
    <tr>
        <td><b>Month </b></td>
        <td> 
            <select name="month">
            <%
                for i = 1 to 12
                    if (i = Month(Now)) then
                        Response.Write("<option selected value=""" & i & """>" & i & " (" & MonthName(i) & ")" & vbcrlf)
                    else
                        Response.Write("<option value=""" & i & """>" & i & " (" & MonthName(i) & ")" & vbcrlf)
                    end if
                next
            %>
            </select>
        </td>
        
        <td><b>Day </b></td>
        <td>
            <select name="day">
            <%
                for i = 1 to 31
                    if (i = Day(Now)) then
                        Response.Write("<option selected value=""" & i & """>" & i & vbcrlf)
                    else
                        Response.Write("<option value=""" & i & """>" & i & vbcrlf)
                    end if
                next
            %>
            </select>
        </td>
        
        <td><b>Year </b></td>
        <td> 
            <select name="year">
                <option value="1999">1999
                <option value="2000">2000
                <option value="2001">2001
                <option selected value="2002">2002
                <option value="2003">2003
                <option value="2004">2004
                <option value="2005">2005
            </select>
        </td>
        
    </tr>
    <tr>
        <td><b>Hour </b></td>
        <td>
            <select name="hour">
            <%
                dim pm, hr
                hr = Hour(Now)
                if (hr > 11) then
                    pm = "1"
                    if (hr > 12) then
                        hr = hr - 12
                    end if
                end if

                for i = 1 to 12
                    if (i = hr) then
                        Response.Write("<option selected value=""" & i & """>" & i & vbcrlf)
                    else
                        Response.Write("<option value=""" & i & """>" & i & vbcrlf)
                    end if
                next
            %>
            </select>
        </td>
        <td><b>Minute </b></td>
        <td>
            <select name="minute">
            <%
                dim min
                for i = 0 to 59
                    min = i
                    if (min < 10) then
                        min = "0" & i
                    end if
                    if (i = Minute(Now)) then
                        Response.Write("<option selected value=""" & min & """>" & min & vbcrlf)
                    else
                        Response.Write("<option value=""" & min & """>" & min & vbcrlf)
                    end if
                next
            %>
            </select>
        </td>
        <td><b>Second </b></td>
        <td>
            <select name="second">
            <%
                dim sec
                for i = 0 to 59
                    sec = i
                    if (sec < 10) then
                        sec = "0" & i
                    end if
                    if (i = Second(Now)) then
                        Response.Write("<option selected value=""" & sec & """>" & sec & vbcrlf)
                    else
                        Response.Write("<option value=""" & sec & """>" & sec & vbcrlf)
                    end if
                next
            %>
            </select>
        </td>
        <td>&nbsp;</td>
        <td>
            <select name="ampm">
            <%
                if (pm = "1") then
                    Response.Write("<option value=""AM"">AM" & vbcrlf)
                    Response.Write("<option selected value=""PM"">PM" & vbcrlf)
                else
                    Response.Write("<option selected value=""AM"">AM" & vbcrlf)
                    Response.Write("<option value=""PM"">PM" & vbcrlf)
                end if
            %>
            </select>
        </td>        
    </tr>
    <tr><td colspan="8">&nbsp;</td></tr>
</table>

<table>
    <tr><td colspan="8"><h4>Alarm Settings</h4></td></tr>
    <tr>
        <td><b>Alarm: </b></td>
        <td>
            <select name="alarm">
                <option value="1">On
                <option selected value="0">Off    
            </select>
        </td>
        <td colspan="4">&nbsp;</td>
    </tr>

    <tr>
        <td><b>Hour </b></td>
        <td>
            <select name="alarmhour">
            <%
                for i = 1 to 12
                    Response.Write("<option value=""" & i & """>" & i & vbcrlf)
                next
            %>
            </select>
        </td>
        <td><b>Minute </b></td>
        <td>
            <select name="alarmminute">
            <%
                for i = 0 to 59
                    min = i
                    if (min < 10) then
                        min = "0" & i
                    end if
                    Response.Write("<option value=""" & min & """>" & min & vbcrlf)
                next
            %>
            </select>
        </td>
        <td><b>Second </b></td>
        <td>
            <select name="alarmsecond">
            <%
                for i = 0 to 59
                    sec = i
                    if (sec < 10) then
                        sec = "0" & i
                    end if
                    Response.Write("<option value=""" & sec & """>" & sec & vbcrlf)
                next
            %>
            </select>
        </td>
        <td>&nbsp;</td>
        <td>
            <select name="alarmampm">
            <%
                Response.Write("<option value=""AM"">AM" & vbcrlf)
                Response.Write("<option value=""PM"">PM" & vbcrlf)
            %>
            </select>
        </td>        

    </tr>
</table>

<table>
    <tr><td colspan="2"><h4>Time Zone</h4></td></tr>
    <tr>
        <td><b>Time Zone: </b></td>
        <td>
            <select name="timezone">
                <option value="0">GMT-12 Kwajalein 
                <option value="1">GMT-11 Samoa,Midway 
                <option value="2">GMT-10 Hawaii 
                <option value="3">GMT-9 Alaska 
                <option selected value="4">GMT-8 Pacific US 
                <option value="10">GMT-7 Mountain US 
                <option value="13">GMT-7 Chihuahua, La Paz 
                <option value="15">GMT-7 Arizona
                <option value="20">GMT-6 Central US
                <option value="25">GMT-6 Saskatchewan
                <option value="30">GMT-6 Mexico City, Monterrey
                <option value="33">GMT-6 Cent. America
                <option value="35">GMT-5 Eastern US
                <option value="40">GMT-5 Indiana (USA)
                <option value="45">GMT-5 Bogota,Lima
                <option value="50">GMT-4 Atlantic
                <option value="55">GMT-4 Caracas,La Paz
                <option value="56">GMT-4 Santiago
                <option value="60">GMT-3:30 Newfoundland
                <option value="65">GMT-3 Brasilia
                <option value="70">GMT-3 Buenos Aires
                <option value="73">GMT-3 Greenland
                <option value="75">GMT-2 Mid-Atlantic
                <option value="80">GMT-1 Azores
                <option value="83">GMT-1 Cape Verde
                <option value="85">GMT London,Dublin
                <option value="90">GMT Casablanca
                <option value="95">GMT+1 Prague,Budapest
                <option value="100">GMT+1 Warsaw,Sofija
                <option value="105">GMT+1 Paris,Madrid
                <option value="110">GMT+1 Berlin,Rome
                <option value="113">GMT+1 W Cent Africa 
                <option value="115">GMT+2 Bucharest
                <option value="120">GMT+2 Cairo
                <option value="125">GMT+2 Helsinki,Riga
                <option value="130">GMT+2 Athens,Istanbul
                <option value="135">GMT+2 Jerusalem
                <option value="140">GMT+2 Pretoria
                <option value="145">GMT+3 Moscow
                <option value="150">GMT+3 Riyadh, Kuwait
                <option value="155">GMT+3 Nairobi
                <option value="158">GMT+3 Baghdad
                <option value="160">GMT+3:30 Tehran
                <option value="165">GMT+4 Abu Dhabi
                <option value="170">GMT+4 Baku,Tbilisi
                <option value="175">GMT+4:30 Kabul
                <option value="180">GMT+5 Yekaterinburg
                <option value="185">GMT+5 Islamabad
                <option value="190">GMT+5:30 New Delhi
                <option value="193">GMT+5:45 Kathmandu
                <option value="195">GMT+6 Astana,Dhaka
                <option value="200">GMT+6 Sri Lanka
                <option value="201">GMT+6 Almaty
                <option value="203">GMT+6:30 Yangoon
                <option value="205">GMT+7 Bangkok,Hanoi
                <option value="207">GMT+7 Krasnoyarsk
                <option value="210">GMT+8 Beijing, HK
                <option value="215">GMT+8 Malaysia,Singapore
                <option value="220">GMT+8 Taipei
                <option value="225">GMT+8 Perth
                <option value="227">GMT+8 Ulaanbataar
                <option value="230">GMT+9 Seoul
                <option value="235">GMT+9 Tokyo,Osaka
                <option value="240">GMT+9 Yakutsk
                <option value="245">GMT+9:30 Darwin
                <option value="250">GMT+9:30 Adelaide
                <option value="255">GMT+10 Sydney
                <option value="260">GMT+10 Brisbane
                <option value="265">GMT+10 Hobart
                <option value="270">GMT+10 Vladivostok
                <option value="275">GMT+10 Guam
                <option value="280">GMT+11 Magadan
                <option value="285">GMT+12 Fiji Islands
                <option value="290">GMT+12 New Zealand
                <option value="300">GMT+13 Tonga
            </select>
        </td>
        <td colspan="2">&nbsp;</td>
    </tr>
</table>

<table>
    <tr>       
        <td><input type="submit" value="submit">
        <input type="button" value="Cancel" name="CancelBtn" onclick="GoBack()">
        </td>
    </tr>
</table>
</form>
</body>
</html>
