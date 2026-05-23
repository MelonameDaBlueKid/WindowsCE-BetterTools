<%

bodyXML = bodyXML + "  &lt;characteristic type=&quot;TAPI&quot;&gt;" + vbcrlf
bodyXML = bodyXML + "    &lt;parm name=&quot;CellBroadcastLanguage&quot; value=&quot;" + Request.Form("language") + "&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "    &lt;parm name=&quot;CellBroadcastEnableTopicList&quot; value=&quot;" + Request.Form("enablelist") + "&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "    &lt;parm name=&quot;CellBroadcastEnabled&quot; value=&quot;" + Request.Form("enablecellbroadcast") + "&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "    &lt;parm name=&quot;Voicemail1&quot; value=&quot;" + Request.Form("voicemail1") + "&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "    &lt;parm name=&quot;Voicemail2&quot; value=&quot;" + Request.Form("voicemail2") + "&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "    &lt;parm name=&quot;TAPI_BARRING_PASSWORD&quot; value=&quot;" + Request.Form("callbarringpassword") + "&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "    &lt;parm name=&quot;TAPI_PIN2&quot; value=&quot;" + Request.Form("pin2") + "&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "    &lt;parm name=&quot;SMSC&quot; value=&quot;" + Request.Form("smsc") + "&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "    &lt;parm name=&quot;TAPI_NETWORK_PREFERRED&quot; value=&quot;" + Request.Form("preferrednetwork") + "&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "    &lt;parm name=&quot;TAPI_NETWORK_SELECT_CURRENT&quot; value=&quot;" + Request.Form("selectmanualnetwork") + "&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "    &lt;parm name=&quot;TAPI_NETWORK_CURRENT&quot; value=&quot;&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "    &lt;parm name=&quot;TAPI_NETWORK_AUTOMATIC&quot; value=&quot;" + Request.Form("selectautonetwork") + "&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "    &lt;parm name=&quot;CountryCode&quot; value=&quot;" + Request.Form("countrycode") + "&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "    &lt;parm name=&quot;AreaCode&quot; value=&quot;" + Request.Form("areacode") + "&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "    &lt;parm name=&quot;TAPI_SEND_CALLID&quot; value=&quot;" + Request.Form("sendcallID") + "&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "    &lt;parm name=&quot;TAPI_FIXEDDIAL_NUMBERS&quot; value=&quot;&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "    &lt;parm name=&quot;TAPI_FIXEDDIAL_ENABLED&quot; value=&quot;" + Request.Form("enablefixeddigit") + "&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "    &lt;parm name=&quot;TAPI_BARRING_OUT&quot; value=&quot;" + Request.Form("baroutgoing") + "&quot;/&gt; " + vbcrlf
bodyXML = bodyXML + "    &lt;parm name=&quot;TAPI_BARRING_IN&quot; value=&quot;" + Request.Form("barincoming") + "&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "    &lt;parm name=&quot;TAPI_WAITING&quot; value=&quot;" + Request.Form("enablecallwaiting") + "&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "  &lt;/characteristic&gt;" + vbcrlf


%>
