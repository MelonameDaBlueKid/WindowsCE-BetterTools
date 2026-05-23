<%

bodyXML = bodyXML + "    &lt;characteristic type=&quot;BOOTSTRAP&quot;&gt;" + vbcrlf
bodyXML = bodyXML + "        &lt;parm name=&quot;PROVURL&quot; value=&quot;" + Request.Form("TPPG") + "&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "        &lt;parm name=&quot;NAME&quot; value=&quot;" + Request.Form("TPPGNAME") + "&quot; /&gt;" + vbcrlf
bodyXML = bodyXML + "    &lt;/characteristic&gt;" + vbcrlf
bodyXML = bodyXML + " " + vbcrlf
bodyXML = bodyXML + "	&lt;characteristic type=&quot;PXLOGICAL&quot;&gt;" + vbcrlf
bodyXML = bodyXML + "		&lt;parm name=&quot;PROXY-ID&quot; value=&quot;LogPush1&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "		&lt;parm name=&quot;NAME&quot; value=&quot;LameSMSC&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "		&lt;parm name=&quot;TRUST&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "		&lt;characteristic type=&quot;PXPHYSICAL&quot;&gt;" + vbcrlf
bodyXML = bodyXML + "			&lt;parm name=&quot;PHYSICAL-PROXY-ID&quot; value=&quot;PhyPush1&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "			&lt;parm name=&quot;PXADDR&quot; value=&quot;14254435250&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "			&lt;parm name=&quot;PXADDRTYPE&quot; value=&quot;E164&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "			&lt;parm name=&quot;TO-NAPID&quot; value=&quot;SMSNAP1&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "			&lt;parm name=&quot;PUSHENABLED&quot; value=&quot;1&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "		&lt;/characteristic&gt;" + vbcrlf
bodyXML = bodyXML + "	&lt;/characteristic&gt;" + vbcrlf

bodyXML = bodyXML + "    &lt;characteristic type=&quot;NAPDEF&quot;&gt;" + vbcrlf
bodyXML = bodyXML + "        &lt;parm name=&quot;NAPID&quot; value=&quot;SMSNAP1&quot; /&gt; " + vbcrlf
bodyXML = bodyXML + "        &lt;parm name=&quot;BEARER&quot; value=&quot;GSM-SMS&quot; /&gt; " + vbcrlf
bodyXML = bodyXML + "    	&lt;parm name=&quot;NAME&quot; value=&quot;WAP SMSC&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "        &lt;parm name=&quot;NAP-ADDRESS&quot; value=&quot;+1000000&quot; /&gt; " + vbcrlf
bodyXML = bodyXML + "    &lt;/characteristic&gt;" + vbcrlf

bodyXML = bodyXML + "    &lt;characteristic type=&quot;PXLOGICAL&quot;&gt;" + vbcrlf
bodyXML = bodyXML + "        &lt;parm name=&quot;PROXY-ID&quot; value=&quot;Log1&quot; /&gt; " + vbcrlf
bodyXML = bodyXML + "        &lt;parm name=&quot;STARTPAGE&quot; value=&quot;" + Request.Form("startpage") + "&quot; /&gt; " + vbcrlf
bodyXML = bodyXML + "        &lt;parm name=&quot;NAME&quot; value=&quot;" + Request.Form("friendlyname") + "&quot; /&gt; " + vbcrlf
bodyXML = bodyXML + "        &lt;characteristic type=&quot;PXPHYSICAL&quot;&gt;" + vbcrlf
bodyXML = bodyXML + "            &lt;parm name=&quot;PHYSICAL-PROXY-ID&quot; value=&quot;Phy1&quot; /&gt; " + vbcrlf
bodyXML = bodyXML + "            &lt;parm name=&quot;PXADDR&quot; value=&quot;" + Request.Form("servername") + "&quot; /&gt; " + vbcrlf
bodyXML = bodyXML + "            &lt;parm name=&quot;TO-NAPID&quot; value=&quot;NAP1&quot; /&gt; " + vbcrlf
bodyXML = bodyXML + "            &lt;characteristic type=&quot;PORT&quot;&gt;" + vbcrlf
bodyXML = bodyXML + "                &lt;parm name=&quot;PORTNBR&quot; value=&quot;9201&quot; /&gt; " + vbcrlf
bodyXML = bodyXML + "            &lt;/characteristic&gt;" + vbcrlf
bodyXML = bodyXML + "        &lt;/characteristic&gt;" + vbcrlf
bodyXML = bodyXML + "    &lt;/characteristic&gt;" + vbcrlf
bodyXML = bodyXML + " " + vbcrlf
bodyXML = bodyXML + "    &lt;characteristic type=&quot;NAPDEF&quot;&gt;" + vbcrlf
bodyXML = bodyXML + "        &lt;parm name=&quot;NAPID&quot; value=&quot;NAP1&quot; /&gt; " + vbcrlf
bodyXML = bodyXML + "        &lt;parm name=&quot;BEARER&quot; value=&quot;GSM-CSD&quot; /&gt; " + vbcrlf
bodyXML = bodyXML + "        &lt;parm name=&quot;NAME&quot; value=&quot;" + Request.Form("friendlyname") + "&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "        &lt;parm name=&quot;NAP-ADDRESS&quot; value=&quot;" + Request.Form("wapphone") + "&quot; /&gt; " + vbcrlf
bodyXML = bodyXML + "        &lt;characteristic type=&quot;NAPAUTHINFO&quot;&gt;" + vbcrlf
bodyXML = bodyXML + "            &lt;parm name=&quot;AUTHNAME&quot; value=&quot;" + Request.Form("wapusername") + "&quot; /&gt; " + vbcrlf
bodyXML = bodyXML + "            &lt;parm name=&quot;AUTHTYPE&quot; value=&quot;PAP&quot; /&gt; " + vbcrlf
bodyXML = bodyXML + "            &lt;parm name=&quot;AUTHSECRET&quot; value=&quot;password&quot; /&gt; " + vbcrlf
bodyXML = bodyXML + "        &lt;/characteristic&gt;" + vbcrlf
bodyXML = bodyXML + "    &lt;/characteristic&gt;" + vbcrlf
bodyXML = bodyXML + " " + vbcrlf
bodyXML = bodyXML + "    &lt;characteristic type=&quot;CM_PPPEntries&quot;&gt;" + vbcrlf
bodyXML = bodyXML + "        &lt;characteristic type=&quot;SFone&quot;&gt;" + vbcrlf
bodyXML = bodyXML + "            &lt;parm name=&quot;DestId&quot; value=&quot;" + Request.Form("dest") + "&quot; /&gt;" + vbcrlf
bodyXML = bodyXML + "            &lt;parm name=&quot;CountryCode&quot; value=&quot;" + Request.Form("countrycode") + "&quot; /&gt;" + vbcrlf
bodyXML = bodyXML + "            &lt;parm name=&quot;AreaCode&quot; value=&quot;" + Request.Form("areacode") + "&quot; /&gt;" + vbcrlf
bodyXML = bodyXML + "            &lt;parm name=&quot;Phone&quot; value=&quot;" + Request.Form("phone") + "&quot; /&gt;" + vbcrlf
bodyXML = bodyXML + "            &lt;parm name=&quot;UserName&quot; value=&quot;" + Request.Form("username") + "&quot; /&gt;" + vbcrlf
bodyXML = bodyXML + "            &lt;parm name=&quot;Password&quot; value=&quot;" + Request.Form("password") + "&quot; /&gt;" + vbcrlf
bodyXML = bodyXML + "            &lt;parm name=&quot;Domain&quot; value=&quot;" + Request.Form("domain") + "&quot; /&gt;" + vbcrlf
bodyXML = bodyXML + "        &lt;/characteristic&gt;" + vbcrlf
bodyXML = bodyXML + "    &lt;/characteristic&gt;" + vbcrlf
bodyXML = bodyXML + " " + vbcrlf


%>
