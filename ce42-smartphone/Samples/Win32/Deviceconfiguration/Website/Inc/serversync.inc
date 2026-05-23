<%


bodyXML = bodyXML + "    &lt;characteristic type=&quot;Sync&quot;&gt;" + vbcrlf
bodyXML = bodyXML + "        &lt;characteristic type=&quot;Connection&quot;&gt;" + vbcrlf
bodyXML = bodyXML + "	        &lt;parm name=&quot;User&quot; value=&quot;" + Request.Form("login") + "&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "            &lt;parm name=&quot;Password&quot; value=&quot;" + Request.Form("password") + "&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "	        &lt;parm name=&quot;Server&quot; value=&quot;" + Request.Form("server") + "&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "	        &lt;parm name=&quot;Domain&quot; value=&quot;" + Request.Form("domain") + "&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "    	&lt;/characteristic&gt;" + vbcrlf
bodyXML = bodyXML + "    " + vbcrlf
bodyXML = bodyXML + "		&lt;characteristic type=&quot;Mail&quot;&gt;" + vbcrlf
bodyXML = bodyXML + "			&lt;parm name=&quot;Enabled&quot; value=&quot;" + z + "&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "			&lt;parm name=&quot;SyncSwitchPurge&quot; value=&quot;3&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "		&lt;/characteristic&gt;" + vbcrlf
bodyXML = bodyXML + "    " + vbcrlf
bodyXML = bodyXML + "		&lt;characteristic type=&quot;Contacts&quot;&gt;" + vbcrlf
bodyXML = bodyXML + "			&lt;parm name=&quot;Enabled&quot; value=&quot;" + y + "&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "			&lt;parm name=&quot;SyncSwitchPurge&quot; value=&quot;3&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "		&lt;/characteristic&gt;" + vbcrlf
bodyXML = bodyXML + "    " + vbcrlf
bodyXML = bodyXML + "		&lt;characteristic type=&quot;Calendar&quot;&gt;" + vbcrlf
bodyXML = bodyXML + "			&lt;parm name=&quot;Enabled&quot; value=&quot;" + x + "&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "			&lt;parm name=&quot;SyncSwitchPurge&quot; value=&quot;3&quot;/&gt;" + vbcrlf
bodyXML = bodyXML + "		&lt;/characteristic&gt;" + vbcrlf
bodyXML = bodyXML + "    " + vbcrlf
bodyXML = bodyXML + "    &lt;/characteristic&gt;" + vbcrlf



%>
