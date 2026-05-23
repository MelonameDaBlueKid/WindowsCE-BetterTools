<%

bodyXML = bodyXML + "  &lt;characteristic type=&quot;CLOCK&quot;&gt;" + vbcrlf
bodyXML = bodyXML + "    &lt;parm name=&quot;Date&quot; value=&quot;" + Request.Form("month") + "/" + Request.Form("day") + "/" + Request.Form("year") + "&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "    &lt;parm name=&quot;Time&quot; value=&quot;" + Request.Form("hour") + ":" + Request.Form("minute") + ":" + Request.Form("second") + " " + Request.Form("ampm") + "&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "    &lt;parm name=&quot;AlarmOn&quot; value=&quot;" + Request.Form("alarm") + "&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "    &lt;parm name=&quot;AlarmTime&quot; value=&quot;" + Request.Form("alarmhour") + ":" + Request.Form("alarmminute") + ":" + Request.Form("alarmsecond") + " " + Request.Form("alarmampm") + "&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "    &lt;parm name=&quot;TimeZone&quot; value=&quot;" + Request.Form("timezone") + "&quot;/&gt;    " + vbcrlf
bodyXML = bodyXML + "  &lt;/characteristic&gt;" + vbcrlf


%>
