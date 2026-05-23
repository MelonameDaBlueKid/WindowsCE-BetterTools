<%

bodyXML = bodyXML + "   &lt;characteristic type=&quot;BrowserFavorite&quot;&gt;" + vbcrlf
bodyXML = bodyXML + "        &lt;characteristic type=&quot;" + Request.Form("name") + "&quot;" + "&gt;" + vbcrlf
bodyXML = bodyXML + "            &lt;parm name=&quot;URL&quot; value=&quot;" + Request.Form("url") + "&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "        &lt;/characteristic&gt;" + vbcrlf
bodyXML = bodyXML + "    &lt;/characteristic&gt;" + vbcrlf

%>
