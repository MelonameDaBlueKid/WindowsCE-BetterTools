<%
bodyXML = bodyXML + " " + vbcrlf
bodyXML = bodyXML + "   &lt;characteristic type=&quot;UnInstall&quot;&gt;&lt;characteristic type=&quot;" + Request.Form("app") + "&quot;&gt; " + vbcrlf
bodyXML = bodyXML + "          &lt;parm name=&quot;uninstall&quot; value=&quot;1&quot;/&gt;        " + vbcrlf
bodyXML = bodyXML + "       &lt;/characteristic&gt; " + vbcrlf
bodyXML = bodyXML + "   &lt;/characteristic&gt; " + vbcrlf


%>
