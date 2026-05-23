<%

bodyXML = bodyXML + "   &lt;characteristic type=&quot;Metabase&quot;&gt;" + vbcrlf
bodyXML = bodyXML + "      &lt;characteristic type=&quot;" + Request.Form("entry") + "&quot;" + "&gt;" + vbcrlf
bodyXML = bodyXML + "         &lt;parm name=&quot;datatype&quot; value=&quot;" + Request.Form("datatype") + "&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "         &lt;parm name=&quot;maxvalue&quot; value=&quot;" + Request.Form("maxvalue") + "&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "         &lt;parm name=&quot;minvalue&quot; value=&quot;" + Request.Form("minvalue") + "&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "         &lt;parm name=&quot;access-role&quot; value=&quot;" + Request.Form("accessrole") + "&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "         &lt;parm name=&quot;rw-access&quot; value=&quot;" + Request.Form("rw") + "&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "         &lt;characteristic type=&quot;label&quot;&gt;" + vbcrlf
bodyXML = bodyXML + "             &lt;parm name=&quot;" + Request.Form("labellocale1") + "&quot;" + " value=&quot;" + Request.Form("labeltext1") + "&quot;" + "/&gt;" + vbcrlf
bodyXML = bodyXML + "             &lt;parm name=&quot;" + Request.Form("labellocale2") + "&quot;" + " value=&quot;" + Request.Form("labeltext2") + "&quot;" + "/&gt;" + vbcrlf
bodyXML = bodyXML + "             &lt;parm name=&quot;" + Request.Form("labellocale3") + "&quot;" + " value=&quot;" + Request.Form("labeltext3") + "&quot;" + "/&gt;" + vbcrlf
bodyXML = bodyXML + "         &lt;/characteristic&gt;" + vbcrlf
bodyXML = bodyXML + "         &lt;characteristic type=&quot;options&quot;&gt;" + vbcrlf
bodyXML = bodyXML + "             &lt;parm name=&quot;" + Request.Form("optionslocale1") + "&quot;" + " value=&quot;" + Request.Form("optionstext1") + "&quot;" + "/&gt;" + vbcrlf
bodyXML = bodyXML + "             &lt;parm name=&quot;" + Request.Form("optionslocale2") + "&quot;" + " value=&quot;" + Request.Form("optionstext2") + "&quot;" + "/&gt;" + vbcrlf
bodyXML = bodyXML + "             &lt;parm name=&quot;" + Request.Form("optionslocale3") + "&quot;" + " value=&quot;" + Request.Form("optionstext3") + "&quot;" + "/&gt;" + vbcrlf
bodyXML = bodyXML + "         &lt;/characteristic&gt;" + vbcrlf
bodyXML = bodyXML + "      &lt;/characteristic&gt;" + vbcrlf
bodyXML = bodyXML + "   &lt;/characteristic&gt;" + vbcrlf

%>
