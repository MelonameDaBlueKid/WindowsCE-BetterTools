<html>

<head>
<meta http-equiv="Content-Language" content="en-us">
<meta http-equiv="Content-Type" content="text/html; charset=windows-1252">
<link rel="stylesheet" type="text/css" href="/css/master.css">
<link rel="stylesheet" type="text/css" href="style.css">
<title>Device Configuration - Add URL to Favorites</title>
<script language="JavaScript">
<!--
function SwapFav()
{
    var f = document.favorite;
    var u = f.url
    var n = f.name
        
    switch(f.PickFav[f.PickFav.selectedIndex].value)
    {

    case "MSN":
        n.value = "MSN Mobile";
        u.value = "http://mobile.msn.com";
        break;

    case "google":
        n.value = "Google";
        u.value = "http://www.google.com";
        break;

    case "none":
        n.value = "";
        u.value = "";
        break;

    default:
        return 1;
    }
}

function GoBack()
{
	window.location ="../xmlaction.asp"
}
// -->
</script>


</head>

<body>

<h3>Device Configuration - Add URL to Favorites</h3>
<p>Use this page to add entries to your device's favorites list, through over-the-air configuration.</p>
<form name="favorite" method="POST" action="../xmlgen.asp">
<input type="hidden" name="node" value="10">
  <table>
    <tr>
        <td>
            <select name="PickFav" onChange="SwapFav()">
                <option selected value="none">Select Favorite
                <option value="MSN">MSN
                <option value="google">Google
            </select>
        </td>
    </tr>
    <tr>
      <td class="label">Favorite title:</td>
      <td><input type="text" name="name" size="50" value=""></td>
    </tr>
    <tr>
      <td class="label">URL:</td>
      <td><input type="text" name="url" size="50" value=""></td>
    </tr>
  </table>
  <p><input type="submit" value="Submit">
  <input type="button" value="Cancel" name="CancelBtn" onclick="GoBack()">
  </p>
</form>
</body>
</html>
