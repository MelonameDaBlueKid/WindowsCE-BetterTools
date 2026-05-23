<%

bodyXML = bodyXML + "	&lt;characteristic type=&quot;SecurityPolicy&quot;&gt;" + vbcrlf
bodyXML = bodyXML + "		&lt;parm name=&quot;" + Request.Form("id") + "&quot; value=&quot;" + Request.Form("rolemask") + "&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "	&lt;/characteristic&gt;" + vbcrlf


%>
