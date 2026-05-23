<%

bodyXML = bodyXML + "  &lt;characteristic type=&quot;TAPI&quot;&gt;" + vbcrlf
bodyXML = bodyXML + "    &lt;characteristic type=&quot;" + Request.Form("fwdcode") + "&quot;&gt;" + vbcrlf
bodyXML = bodyXML + "      &lt;characteristic type=&quot;" + Request.Form("infoclass") + "&quot;&gt;" + vbcrlf
bodyXML = bodyXML + "        &lt;parm name=&quot;TAPI_FORWARD_ADDRESS&quot; value=&quot;" + Request.Form("forwardnumber") + "&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "        &lt;parm name=&quot;TAPI_FORWARD_TIMEOUT&quot; value=&quot;" + Request.Form("timeout") + "&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "        &lt;parm name=&quot;TAPI_FORWARD_ENABLED&quot; value=&quot;" + "1" + "&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "      &lt;/characteristic&gt;" + vbcrlf
bodyXML = bodyXML + "    &lt;/characteristic&gt;" + vbcrlf
bodyXML = bodyXML + "  &lt;/characteristic&gt;" + vbcrlf


%>
