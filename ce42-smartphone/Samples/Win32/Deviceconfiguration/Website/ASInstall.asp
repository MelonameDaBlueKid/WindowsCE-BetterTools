<%
	TempLoc = Request.ServerVariables("URL")
	TempLoc = Left(TempLoc, InStrRev(TempLoc, "/"))
	
	CPFLocation = "http://" + Request.ServerVariables("SERVER_NAME")
	CPFLocation = CPFLocation + TempLoc + "profiles"
	CPFLocation = CPFLocation + "/" + Session("profilename")
	CPFLocation = CPFLocation + "/cpf/" + Session("profilename") + ".cpf"
%>
<html>
<head>
<script language="JavaScript">
var fDeviceConnected
function PopulateDeviceSelect(index, name, type)
{
	var	x = window.document.InstallCPFUI.devicename_select
	var	y = window.document.InstallCPFUI.devicetype_select
	var newelem1 = document.createElement("OPTION")
    var newelem2 = document.createElement("OPTION")
	
	newelem1.text = name
	newelem1.value = name
	
	x.options.add(newelem1, index)
	
	newelem2.text = type
	newelem2.value = type
	
	y.options.add(newelem2, index)
}
function Initialize()
{
	document.InstallCPFUI.Status.innerText = "Checking for ActiveSync connection..."
	
	fDeviceConnected = CPFInstaller.IsDeviceConnected()
	if (!fDeviceConnected)
	{
		document.all.ActionSelection[0].checked = false
		document.all.ActionSelection[1].disabled = false
		document.all.ActionSelection[1].checked = true
		document.all.devicename_select.disabled = false
		document.all.devicetype_select.disabled = false
		
		Msg = document.InstallCPFUI.Status.innerText
		Msg = Msg + " When you click Install, the CPF will be saved to your desktop for deferred install. It will be installed next time the selected device is cradled."
		document.InstallCPFUI.Status.innerText = Msg
	}
	else
	{
		document.all.ActionSelection[0].checked = true
		document.all.ActionSelection[0].disabled = false
		document.all.ActionSelection[1].disabled = false
		document.all.ActionSelection[1].checked = false
		document.all.devicename_select.disabled = true
		document.all.devicetype_select.disabled = true
	}

	NumProfiles = CPFInstaller.InitProfiles()
	CurrDeviceName = CPFInstaller.GetCurrentDeviceName()

	for (i=0; i<NumProfiles; i++)
	{
		string1 = CPFInstaller.GetProfileString(i+1, "DisplayName")
		string2 = CPFInstaller.GetProfileString(i+1, "DeviceType")
		PopulateDeviceSelect(i, string1, string2)
		if (string1==CurrDeviceName )
		{
			document.all.devicename_select.selectedIndex = i
			document.all.devicetype_select.selectedIndex = i
		}
	}
}

function DoInstall()
{	
	var cpfl = document.all.CPFName.value
	var seldevicename = document.InstallCPFUI.devicename_select.value
	var fSuccess = false
	
	seloption = document.all.ActionSelection[0].checked
	if (seloption)
	{
		fSuccess = CPFInstaller.InstallToCurrentDevice(cpfl)
	}
	else
	{
		fSuccess = CPFInstaller.InstallToDevice(cpfl ,seldevicename)
	}
	
	if (fSuccess)
	{
		document.all.B1.disabled = true
		document.all.B2.value = "  Done  "
	}
}

function GoBack()
{
	window.location ="xmlaction_options.asp"
}

</script>
</head>

<body OnLoad="Initialize()">

<script language=javascript for="CPFInstaller" event="StatusMessage(Msg)">
    document.InstallCPFUI.Status.innerText = Msg
</script>
<script language=javascript for="devicename_select" event="onclick">
	devicetype_select.selectedIndex = devicename_select.selectedIndex
</script>
<script language=javascript for="devicetype_select" event="onclick">
	devicename_select.selectedIndex = devicetype_select.selectedIndex
</script>
<script language=javascript for="ActionSelection" event="onclick">
	if (ActionSelection[0].checked)
	{
		document.all.devicename_select.disabled = true
		document.all.devicetype_select.disabled = true
	}
	else
	{
		document.all.devicename_select.disabled = false
		document.all.devicetype_select.disabled = false
	}	
</script>
<table width="682">
<tr><td width="468">
<form name="InstallCPFUI" enctype="multipart/form-data">
	<table cellspacing="0" cellpadding="0" style="border-collapse: collapse" bordercolor="#111111" width="461">
	<tr><td width="461">
    	<fieldset style="padding: 2; width:493; height:130">
     		<legend><b><font face="Arial" size="2">Activesync CPF Installer: Status</font>:</b></legend>
     		<textarea rows="6" name="Status" cols="58"></textarea>
  		</fieldset></td>
  	<td valign="top"><br>
  		&nbsp;<input type="button" value="  Install " name="B1" onclick="DoInstall()"><br><br>
  		&nbsp;<input type="button" value="Cancel" name="B2" onclick="GoBack()">
  	</td></tr>
  	</table>
  	<fieldset style="padding: 2; width:316; height:137">
    <legend align="left"><font face="Arial" size="2"><b>Select Device</b></font></legend>
    <div align="left">
  		<table align="left" style="border-collapse: collapse" bordercolor="#111111" cellpadding="0" cellspacing="0" width="484">
  			<tr><td width="146">
	   			<p style="margin-top: 3; margin-bottom: 3"><font face="Arial">
     				&nbsp;<input type="radio" name="ActionSelection" value="cradled" checked disabled></font><font size="2" face="Arial">Currently Cradled
     			</font></p>
     		</td><td width="338"></td></tr>
     		<tr><td valign="top" width="146">
     			<p style="margin-top: 3"><font face="Arial">
     				&nbsp;<input type="radio" name="ActionSelection" value="partnered" disabled></font><font size="2" face="Arial">Select Partnership:
     			</font><br>
     		</td><td valign="top" width="338">
      			<font face="Arial" size="1">Device Name&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Device Type</font>
				<br>
     			<SELECT size="4" name="devicename_select" disabled>
     			</SELECT>
     			<SELECT size="4" name="devicetype_select" disabled>
     			</SELECT>
     		</td></tr>
     	</table>
     </div>
     <input type="hidden" name="CPFName" value="<% = CPFLocation%>">
  </fieldset>
</form>
</td>
<td width="204">
<OBJECT ID="CPFInstaller" CLASSID="CLSID:A37C489D-D1AE-442B-BE41-0DB1802732B8" codebase="deviceconfigctl.cab#version=1,0,0,1" width="0" height="0">
</OBJECT>
</td>
</tr>
</table>
</body>
