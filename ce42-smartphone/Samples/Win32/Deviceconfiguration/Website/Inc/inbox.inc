<%
select case Request.Form("protocol")
  case "IMAP4"
    protocolGUID = "{D671C70B-8EE3-4881-8045-2AEE6F731B55}"
  case "POP3"
    protocolGUID = "{4FE84006-9E8A-4158-864D-A2E1E98C3786}"
end select

bodyXML = bodyXML + "    &lt;characteristic type=&quot;EMAIL2&quot;&gt;" + vbcrlf
bodyXML = bodyXML + "        &lt;characteristic type=&quot;" + protocolGUID + "&quot;" + "&gt;" + vbcrlf
bodyXML = bodyXML + "            &lt;parm name=&quot;SERVICENAME&quot; value=&quot;My" + Request.Form("protocol") + "&quot; /&gt;" + vbcrlf
bodyXML = bodyXML + "            &lt;parm name=&quot;SERVICETYPE&quot; value=&quot;" + Request.Form("protocol") + "&quot; /&gt;" + vbcrlf
bodyXML = bodyXML + "            &lt;parm name=&quot;INSERVER&quot; value=&quot;" + Request.Form("incomingserver") + "&quot; /&gt;" + vbcrlf
bodyXML = bodyXML + "            &lt;parm name=&quot;OUTSERVER&quot; value=&quot;" + Request.Form("outgoingserver") + "&quot; /&gt;" + vbcrlf
bodyXML = bodyXML + "            &lt;parm name=&quot;NAME&quot; value=&quot;" + Request.Form("name") + "&quot; /&gt;" + vbcrlf
bodyXML = bodyXML + "            &lt;parm name=&quot;REPLYADDR&quot; value=&quot;" + Request.Form("email") + "&quot; /&gt;" + vbcrlf
bodyXML = bodyXML + "            &lt;parm name=&quot;AUTHNAME&quot; value=&quot;" + Request.Form("username") + "&quot; /&gt;" + vbcrlf
bodyXML = bodyXML + "            &lt;parm name=&quot;DOMAIN&quot; value=&quot;" + Request.Form("domain") + "&quot; /&gt;" + vbcrlf
bodyXML = bodyXML + "        &lt;/characteristic&gt;" + vbcrlf
bodyXML = bodyXML + "    &lt;/characteristic&gt;" + vbcrlf


%>
