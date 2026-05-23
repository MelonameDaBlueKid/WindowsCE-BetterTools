<%

bodyXML = bodyXML + "    &lt;characteristic type=&quot;CM_PPPEntries&quot;&gt;" + vbcrlf
bodyXML = bodyXML + "        &lt;characteristic type=&quot;" + Request.Form("name") + "&quot;" + "&gt;" + vbcrlf
bodyXML = bodyXML + "            &lt;parm name=&quot;DestId&quot; value=&quot;" + Request.Form("dest") + "&quot; /&gt;" + vbcrlf
bodyXML = bodyXML + "            &lt;parm name=&quot;CountryCode&quot; value=&quot;" + Request.Form("countrycode") + "&quot; /&gt;" + vbcrlf
bodyXML = bodyXML + "            &lt;parm name=&quot;AreaCode&quot; value=&quot;" + Request.Form("areacode") + "&quot; /&gt;" + vbcrlf
bodyXML = bodyXML + "            &lt;parm name=&quot;Phone&quot; value=&quot;" + Request.Form("phone") + "&quot; /&gt;" + vbcrlf
bodyXML = bodyXML + "            &lt;parm name=&quot;UserName&quot; value=&quot;" + Request.Form("username") + "&quot; /&gt;" + vbcrlf
bodyXML = bodyXML + "            &lt;parm name=&quot;Password&quot; value=&quot;" + Request.Form("password") + "&quot; /&gt;" + vbcrlf
bodyXML = bodyXML + "            &lt;parm name=&quot;Domain&quot; value=&quot;" + Request.Form("domain") + "&quot; /&gt;" + vbcrlf
if trim(Request.Form("dns1"))<>"" then
  bodyXML = bodyXML + "            &lt;parm name=&quot;DnsAddr&quot; value=&quot;" + Request.Form("dns1") + "&quot; /&gt;" + vbcrlf
end if
if trim(Request.Form("dns2"))<>"" then
  bodyXML = bodyXML + "            &lt;parm name=&quot;AltDnsAddr&quot; value=&quot;" + Request.Form("dns2") + "&quot; /&gt;" + vbcrlf
end if
if trim(Request.Form("wins1"))<>"" then
  bodyXML = bodyXML + "            &lt;parm name=&quot;WinsAddr&quot; value=&quot;" + Request.Form("wins1") + "&quot; /&gt;" + vbcrlf
end if
if trim(Request.Form("wins2"))<>"" then
  bodyXML = bodyXML + "            &lt;parm name=&quot;AltWinsAddr&quot; value=&quot;" + Request.Form("wins2") + "&quot; /&gt;" + vbcrlf
end if
bodyXML = bodyXML + "        &lt;/characteristic&gt;" + vbcrlf
bodyXML = bodyXML + "    &lt;/characteristic&gt;" + vbcrlf


%>
