<%

bodyXML = bodyXML + "  &lt;characteristic type=&quot;CM_GPRSEntries&quot;&gt;" + vbcrlf
bodyXML = bodyXML + "    &lt;characteristic type=&quot;" + Request.Form("name") + "&quot;" + "&gt;" + vbcrlf
bodyXML = bodyXML + "      &lt;parm name=&quot;DestId&quot; value=&quot;" + Request.Form("dest") + "&quot; /&gt;" + vbcrlf
bodyXML = bodyXML + "      &lt;characteristic type=&quot;DevSpecificCellular&quot;&gt;" + vbcrlf
bodyXML = bodyXML + "        &lt;parm name=&quot;BearerInfoValid&quot; value=&quot;" + Request.Form("bearerinfovalid") + "&quot; /&gt;" + vbcrlf
bodyXML = bodyXML + "        &lt;parm name=&quot;GPRSInfoValid&quot; value=&quot;" + Request.Form("gprsinfovalid") + "&quot; /&gt;" + vbcrlf
bodyXML = bodyXML + "        &lt;parm name=&quot;GPRSInfoProtocolType&quot; value=&quot;" + Request.Form("gprsprotocol") + "&quot; /&gt; " + vbcrlf
bodyXML = bodyXML + "        &lt;parm name=&quot;GPRSInfoL2ProtocolType&quot; value=&quot;" + Request.Form("gprsl2protocol") + "&quot; /&gt;" + vbcrlf
bodyXML = bodyXML + "        &lt;parm name=&quot;GPRSInfoAccessPointName&quot; value=&quot;" + Request.Form("pointname") + "&quot; /&gt;" + vbcrlf
bodyXML = bodyXML + "        &lt;parm name=&quot;GPRSInfoAddress&quot; value=&quot;" + Request.Form("infoaddress") + "&quot; /&gt;" + vbcrlf
bodyXML = bodyXML + "        &lt;parm name=&quot;GPRSInfoDataCompression&quot; value=&quot;" + Request.Form("gprsdatacompression") + "&quot; /&gt;" + vbcrlf
bodyXML = bodyXML + "        &lt;parm name=&quot;GPRSInfoHeaderCompression&quot; value=&quot;" + Request.Form("gprsheadercompression") + "&quot; /&gt;" + vbcrlf
bodyXML = bodyXML + "      &lt;/characteristic&gt;" + vbcrlf
bodyXML = bodyXML + "    &lt;/characteristic&gt;" + vbcrlf
bodyXML = bodyXML + "  &lt;/characteristic&gt;" + vbcrlf


%>
