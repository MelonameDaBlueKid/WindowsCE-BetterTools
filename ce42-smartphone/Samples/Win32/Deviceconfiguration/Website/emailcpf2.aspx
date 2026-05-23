<html>
<head>
<meta http-equiv="Content-Language" content="en-us">
<meta http-equiv="Content-Type" content="text/css; charset=windows-1252">
<meta name="GENERATOR" content="Microsoft FrontPage 5.0">
<meta name="ProgId" content="FrontPage.Editor.Document">
</head>
<SCRIPT Language="Javascript">
function GoBack()
{
	window.location ="xmlaction_options.asp"
}
</SCRIPT>
<html>
<% @Page Language="C#" Debug=true%>
<% @Import Namespace="System.Web.Mail" %>
<% @Import Namespace="System.IO" %>
<%

string emailaddress;
string attachmentname;
string attachmentnamefull;
string adminEmailAddress;
string SMTPServerAddress;

emailaddress= Request.QueryString["mailto"];
attachmentname = Request.QueryString["cpffile"];
adminEmailAddress = Request.QueryString["from"];
SMTPServerAddress = Request.QueryString["using"];
attachmentnamefull = Server.MapPath(attachmentname);

MailMessage msgMail = new MailMessage();
MailAttachment MyAttachment = new MailAttachment(attachmentnamefull);

msgMail.To = emailaddress;
msgMail.From = adminEmailAddress;
msgMail.Subject = "Device Configuration File";
msgMail.Attachments.Add(MyAttachment);
msgMail.Body = "Install the attached CPF file to provision your device";


SmtpMail.SmtpServer= SMTPServerAddress;
SmtpMail.Send(msgMail);

Response.Write("Email has been queued to be sent to <b>");
Response.Write(emailaddress);
Response.Write("</b>");

%>
<form name="ReturnForm">
<input type="button" value="Done" name="B2" onclick="GoBack()">
</form>
</html>
