
#if !defined(AFX_NOTIFY_H__79845343_D4AA_4273_99BE_DF3EB0BFEE6E__INCLUDED_)
#define AFX_NOTIFY_H__79845343_D4AA_4273_99BE_DF3EB0BFEE6E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"

#define MENU_HEIGHT 26

// Defined Below are all of the Strings Used in the application
#define IDS_SHNP_ICONIC			TEXT("SHNP_ICONIC")
#define IDS_SHNP_INFORM			TEXT("SHNP_INFORM")
#define IDS_UPDATED				TEXT("Updated")
#define	IDS_CUSTOM				TEXT("Custom")
#define	IDS_INFORM_MESSAGE		TEXT("Normal (INFORM) priority notification with a duration of 20 seconds and no flags")
#define IDS_ICONIC_MESSAGE		TEXT("ICONIC priority notification with a duration of 10 seconds and no flags")
#define IDS_UPDATED_MESSAGE		TEXT("INFORM priority notification with a duration of 30 seconds and no flags.  Updated after 20 seconds with a new title")
#define IDS_CUSTOM_MESSAGE		TEXT("Notification as defined in the Custom dialog")
#define IDS_DEFAULTHTMLMESSAGE	TEXT("<html><body><form method=\"POST\" action=><p>This is an <font color=\"#0000FF\"><b>HTML</b></font> notification stored in a  <font color=\"#FF0000\"><i>string</i></font> table!</p><p align=right><input type=button name='cmd:10' value='Ok'>&nbsp;<input type=button name='cmd:2' value='Cancel'></p></body></html>");
#define IDS_DEFAULTTITLE		TEXT("Sample Notification...")
#define IDS_DEFUALT_CUSTOM_TIME	TEXT("10")
#define IDS_CUSTOM_HTML_SAMPLE	TEXT("<HTML><BODY>\r\nThis is test HTML\r\n</BODY></HTML>")
#define	IDS_CUSTOM_TITLE		TEXT("Test")
#define IDS_APP_TITLE			TEXT("Notify")
#define IDC_NOTIFY				Text("NOTIFY")

// Other Defines for Listbox Controls, string 
#define MAX_STRINGLEN 100
#define MAX_MESSAGELEN 1000
#define UPDATE_NOTIFICATION 2950
#define CUSTOM_NOTIFICATION 2951
#define WM_MESSAGEBOX 12500

#endif // !defined(AFX_NOTIFY_H__79845343_D4AA_4273_99BE_DF3EB0BFEE6E__INCLUDED_)
