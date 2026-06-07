Code Sample Name: SendMail

Feature Area: Messaging

Description: 
    This sample demonstrates the use of several CEMAPI APIs. Using these APIs, 
    the sample application sends an e-mail message per account to a list of 
    recipients. One message per each account on the device (POP3, ActiveSync, 
    etc) will be stored in that account’s outbox. The recipient list, subject, 
    and message body are specified in code and can be changed. When the program 
    is complete, the message(s) will either be in the device’s outbox, or will 
    have been sent if the appropriate partnership is set up.
    

    Basic program flow:
        Logon to the message store
        Get the message stores table
        For each entry (i.e. local account)
                  Open current store entry
                  Get the Drafts folder (necessary for outgoing mail)
                  Create a new message in this folder
                  Set relevant message properties (Recipients, Subject, Body, etc)
                  Create a file attachment
                  Send the message
        Clean up

Usage: 
    Load the project from Visual Studio 2005, and build normally.

    Run the application normally. The sample application has no UI and requires 
    no interaction. After running the application, check your Outbox 
    or Sent Items (depending on your network / partnership access) and you 
    should see your message(s).

Relevant APIs/Associated Help Topics:     
    CEMAPI
    MapiLogonEx
    SRowSet
    IMapiSession::GetMsgStoresTable
    IMapiSession::OpenMsgStore
    IMapiTable::QueryRows
    IMsgStore::OpenEntry
    IMsgStore::GetProps
    IMapiFolder::CreateMessage
    IMessage::SubmitMessage
    MAPIFreeBuffer
    FreeProws

Assumptions: none.

Requirements: 
    Visual Studio 2005, 
    Windows Mobile 6 Professional SDK or
    Windows Mobile 6 Standard SDK
    Activesync 4.5.

** For more information about this code sample, please see the Windows Mobile 
SDK help system. **
