#!usr/bin/perl -w
#use strict;
use File::Copy;
use CGI;
use Cwd;

$query = new CGI;

print $query->header ("text/html");
print "<HTML>";
print "<SCRIPT Language=\"Javascript\">";
print "function GoBack()";
print "{";
print "	window.location =\"xmlaction_options.asp\"";
print "}";
print "</SCRIPT>";
print "<BODY>";
print "Generating CPF. Please wait...";


$MAKECAB = "/makecab.exe";
$SIGNCODE = "/signcode.exe";

$profname = $query->param('profilename');
$xmlfile = "_setup.xml";
$cpffile = "$profname.cpf";
$xmlbody = $query->param('xmlbody');
$xmlroot = "<wap-provisioningdoc>";
$cpfchar = "\n<characteristic type=\"Install\">\n<parm name=\"InstallPhase\" value=\"install\" />\n<parm name=\"AppName\" value=\"MyDevice CPF File\"/>\n<parm name=\"NoUninstall\" value=\"1\" />\n</characteristic>";
$xmlbody =~ s/$xmlroot/$xmlroot$cpfchar/;

$here = getcwd();
mkdir "profiles\\$profname\\cpf",0;

open(MYXML, ">profiles\\$profname\\cpf\\$xmlfile") or die print "Can't open pipe to mydevice\\profiles\\$profname\\cpf\\$xmlfile; $!<br>cwd is $here - file is $0\n";
print MYXML "$xmlbody";
close(MYXML) or die "Can't close pipe to mydevice\\profiles\\$profname\\cpf\\$xmlfile";

$output = system ("makecab.exe /D Compress=OFF profiles\\$profname\\cpf\\$xmlfile profiles\\$profname\\cpf\\$cpffile /v1 > nul");
if ( 256 == $output)
{
    print "<BR><BR>ERROR: Can't open makecab.exe for profiles\\$profname\\cpf\\$cpffile";
    print "<br><br><br><form name=\"ReturnForm\">";
    print "<input type=\"button\" value=\"Go Back\" name=\"B2\" onclick=\"GoBack()\">";
    print "</form>";
    print "</BODY></HTML>";
}
else
{

    # Add scripting code here to sign the CPF file, if it is intended for locked down smartphones.
    # For security reasons it is not recommended to store the private key (used for signing) in the webserver.


    print "Done";
    print "<meta http-equiv=\"Refresh\" content=\"1; URL=profiles/$profname/cpf/$cpffile\">";
    print "<p>Download of the CPF file will start automatically now. <BR>";
    print "If your download does not start, click <a href=\"profiles/$profname/cpf/$cpffile\">here</a>";
    print "<br><br><br><form name=\"ReturnForm\">";
    print "<input type=\"button\" value=\"Done\" name=\"B2\" onclick=\"GoBack()\">";
    print "</form>";
    print "</BODY></HTML>";
}