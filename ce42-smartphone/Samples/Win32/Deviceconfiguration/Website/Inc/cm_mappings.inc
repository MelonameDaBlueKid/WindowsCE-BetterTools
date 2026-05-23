<%

bodyXML = bodyXML + "  &lt;characteristic type=&quot;CM_Mappings&quot;&gt;" + vbcrlf
bodyXML = bodyXML + "    &lt;characteristic type=&quot;" + Request.Form("index") + "&quot;" + "&gt;" + vbcrlf
bodyXML = bodyXML + "      &lt;parm name=&quot;pattern&quot; value=&quot;" + Request.Form("pattern") + "&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "      &lt;parm name=&quot;network&quot; value=&quot;" + Request.Form("network") + "&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "    &lt;/characteristic&gt;" + vbcrlf
bodyXML = bodyXML + "  &lt;/characteristic&gt;" + vbcrlf


%>
