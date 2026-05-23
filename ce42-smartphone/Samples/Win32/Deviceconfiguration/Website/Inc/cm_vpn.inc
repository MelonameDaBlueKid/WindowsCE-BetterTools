<%

bodyXML = bodyXML + "    &lt;characteristic type=&quot;CM_VPNEntries&quot;&gt;" + vbcrlf
bodyXML = bodyXML + "        &lt;characteristic type=&quot;" + Request.Form("name") + "&quot;" + "&gt;" + vbcrlf
bodyXML = bodyXML + "            &lt;parm name=&quot;SrcId&quot; value=&quot;" + Request.Form("src") + "&quot; /&gt;" + vbcrlf
bodyXML = bodyXML + "            &lt;parm name=&quot;DestId&quot; value=&quot;" + Request.Form("dest") + "&quot; /&gt;" + vbcrlf
bodyXML = bodyXML + "            &lt;parm name=&quot;Phone&quot; value=&quot;" + Request.Form("phone") + "&quot; /&gt;" + vbcrlf
bodyXML = bodyXML + "            &lt;parm name=&quot;UserName&quot; value=&quot;" + Request.Form("username") + "&quot; /&gt;" + vbcrlf
bodyXML = bodyXML + "            &lt;parm name=&quot;Password&quot; value=&quot;" + Request.Form("password") + "&quot; /&gt;" + vbcrlf
bodyXML = bodyXML + "            &lt;parm name=&quot;Domain&quot; value=&quot;" + Request.Form("domain") + "&quot; /&gt;" + vbcrlf
bodyXML = bodyXML + "            &lt;parm name=&quot;Type&quot; value=&quot;" + Request.Form("type") + "&quot; /&gt;" + vbcrlf
if Request.Form("type")="1" then
  bodyXML = bodyXML + "            &lt;parm name=&quot;IPSecAuth&quot; value=&quot;" + Request.Form("ipsecauth") + "&quot; /&gt;" + vbcrlf
  if Request.Form("ipsecauth")="1" then
    bodyXML = bodyXML + "            &lt;parm name=&quot;PresharedKey&quot; value=&quot;" + Request.Form("presharedkey") + "&quot; /&gt;" + vbcrlf
  end if
end if
bodyXML = bodyXML + "        &lt;/characteristic&gt;" + vbcrlf
bodyXML = bodyXML + "    &lt;/characteristic&gt;" + vbcrlf


%>
