<%

bodyXML = bodyXML + "    &lt;characteristic type=&quot;CM_ProxyEntries&quot;&gt;" + vbcrlf
bodyXML = bodyXML + "        &lt;characteristic type=&quot;" + Request.Form("name") + "&quot;" + "&gt;" + vbcrlf
bodyXML = bodyXML + "       &lt;parm name=&quot;SrcId&quot; value=&quot;" + Request.Form("src") + "&quot; /&gt; " + vbcrlf
bodyXML = bodyXML + "       &lt;parm name=&quot;DestId&quot; value=&quot;" + Request.Form("dest") + "&quot; /&gt; " + vbcrlf
bodyXML = bodyXML + "       &lt;parm name=&quot;Proxy&quot; value=&quot;" + Request.Form("server") + "&quot; /&gt;" + vbcrlf
bodyXML = bodyXML + "       &lt;parm name=&quot;Username&quot; value=&quot;" + Request.Form("username") + "&quot; /&gt;" + vbcrlf
bodyXML = bodyXML + "       &lt;parm name=&quot;Password&quot; value=&quot;" + Request.Form("password") + "&quot; /&gt;" + vbcrlf
bodyXML = bodyXML + "       &lt;parm name=&quot;Type&quot; value=&quot;" + Request.Form("type") + "&quot; /&gt; " + vbcrlf
bodyXML = bodyXML + "   &lt;/characteristic&gt;" + vbcrlf
bodyXML = bodyXML + "    &lt;/characteristic&gt;" + vbcrlf


%>
