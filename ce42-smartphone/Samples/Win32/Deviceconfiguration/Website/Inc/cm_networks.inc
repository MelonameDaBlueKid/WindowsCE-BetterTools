<%

bodyXML = bodyXML + "  &lt;characteristic type=&quot;CM_Networks&quot;&gt;" + vbcrlf
bodyXML = bodyXML + "    &lt;characteristic type=&quot;" + Request.Form("name") + "&quot;" + "&gt;" + vbcrlf
bodyXML = bodyXML + "      &lt;parm name=&quot;DestId&quot; value=&quot;" + Request.Form("guid") + "&quot; /&gt;" + vbcrlf
bodyXML = bodyXML + "    &lt;/characteristic&gt;" + vbcrlf
bodyXML = bodyXML + "  &lt;/characteristic&gt;" + vbcrlf


%>
