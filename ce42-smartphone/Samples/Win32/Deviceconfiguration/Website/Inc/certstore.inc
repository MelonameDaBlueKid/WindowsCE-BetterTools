<%

bodyXML = bodyXML + "	&lt;characteristic type=&quot;CertificateStore&quot;&gt; " + vbcrlf
bodyXML = bodyXML + "		&lt;characteristic type=&quot;" + Request.Form("authority") + "&quot;&gt; " + vbcrlf
bodyXML = bodyXML + "			&lt;characteristic type=&quot;" + Request.Form("hash") + "&quot;&gt; " + vbcrlf
bodyXML = bodyXML + "				&lt;parm name=&quot;EncodedCertificate&quot; value=&quot;" + Request.Form("cert") + "&quot;/&gt;  " + vbcrlf
bodyXML = bodyXML + "				&lt;parm name=&quot;Role&quot; value=&quot;" + Request.Form("rolemask") + "&quot;/&gt; " + vbcrlf
bodyXML = bodyXML + "			&lt;/characteristic&gt; " + vbcrlf
bodyXML = bodyXML + "		&lt;/characteristic&gt; " + vbcrlf
bodyXML = bodyXML + "	&lt;/characteristic&gt;  " + vbcrlf


%>
