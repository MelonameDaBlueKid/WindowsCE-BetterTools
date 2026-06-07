//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this sample source code is subject to the terms of the Microsoft
// license agreement under which you licensed this sample source code. If
// you did not accept the terms of the license agreement, you are not
// authorized to use this sample source code. For the terms of the license,
// please see the license agreement between you and Microsoft or, if applicable,
// see the LICENSE.RTF on your install media or the root of your tools installation.
// THE SAMPLE SOURCE CODE IS PROVIDED "AS IS", WITH NO WARRANTIES OR INDEMNITIES.
//

#include <mapidefs.h>
#include <mapicode.h>
#include <mapitags.h>
#include <mapix.h>
#include <mapiutil.h>
#include <cemapi.h>

//Macros
#ifndef EXIT_ON_FAILED
#define EXIT_ON_FAILED(_hr)\
    if (FAILED(_hr))\
    {   \
        RETAILMSG(1,(_T("CEMAPI: FAILED(%x)at %hs:%d\n"), \
            _hr, __FILE__, __LINE__)); \
        goto FuncExit; \
    } 
#endif //EXIT_ON_FAILED

#ifndef RELEASE_OBJ
#define RELEASE_OBJ(s)\
    if (s != NULL)\
    {                   \
        s->Release();   \
        s = NULL;       \
    }
#endif //RELEASE_OBJ

//Function Prototypes
HRESULT CEMAPI_SetMessageRecipients(LPMESSAGE pmsg);
HRESULT CEMAPI_SetMessageProps(LPMESSAGE pmsg);
void CEMAPI_AddRecipients(LPWSTR pszSrc, ULONG ulType, ADRLIST* plst, LPWSTR& pszLocalRecips, LPSPropValue& pval);
ULONG CountRecipsInString(LPCWSTR psz);
HRESULT CEMAPI_AttachFile(LPMESSAGE pmsg);


// **************************************************************************
// Function Name: WinMain
// Purpose: Standard Win32 entry point

// Arguments:
//  none are used for this sample
//
// Return Values:
//    int
//     app exit code
//
// Description: 
//	
//	This function controls the main flow of the application. A summary:
//	Logon to the message store
//	Get the message stores table
//	For each entry(i.e. local account)
//		Open current store entry
//		Get the Drafts folder(necessary for outgoing mail)
//		Create a new message in this folder
//		Set relevant message properties(Recipients, Subject, Body, etc)
//		Send the message
//	Clean up
//


int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPWSTR lpCmdLine,
    int CmdShow
    )
{
	
	HRESULT             hr;
    IMAPISession    *   pSession    =   NULL;
    IMAPITable      *   pTable      =   NULL;
    SRowSet         *   psrs        =   NULL;
    IMsgStore       *   pStore      =   NULL;
    ULONG               rgTags[]    =   { 1, PR_CE_IPM_DRAFTS_ENTRYID };
  
    ULONG               cValues     =   0;
    SPropValue      *   rgprops     =   NULL;
    SPropValue      *   rgpropsMsg  =   NULL;
    LPMAPIFOLDER        pfldrDrafts =   NULL;
    IMessage        *   pmsg        =   NULL;


    // First logon to the store.
    hr = MAPILogonEx(NULL, NULL, NULL, NULL, &pSession);
    EXIT_ON_FAILED(hr);


    // Get the message stores table
    hr = pSession->GetMsgStoresTable(MAPI_UNICODE, &pTable);
    EXIT_ON_FAILED(hr);


    while (SUCCEEDED(pTable->QueryRows(1, 0, &psrs)))
    {
        // Check number of rows returned. Since the above call only asks for one,
		// anything else means we are at the end of the table
        if (1 != psrs->cRows)
        {
            break;
        }

        
        // Make sure we got the props we need
        if ((1 > psrs->aRow[0].cValues)||(PR_ENTRYID != psrs->aRow[0].lpProps[0].ulPropTag))
        {
            MessageBox(NULL, L"Store missing PR_ENTRYID!", L"Error", MB_OK);
            hr = E_FAIL;
            break;
        }

        // Open this message store
        hr = pSession->OpenMsgStore(NULL, 
            psrs->aRow[0].lpProps[0].Value.bin.cb, 
            (ENTRYID *)psrs->aRow[0].lpProps[0].Value.bin.lpb, 
            NULL, 
            0, 
            &pStore);
        EXIT_ON_FAILED(hr);
    
        // Now get the Drafts folder. In order for a message to be sent by MAPI, it must be created 
		// in the Drafts folder
        hr = pStore->GetProps((SPropTagArray *)rgTags, MAPI_UNICODE, &cValues, &rgprops);
        EXIT_ON_FAILED(hr);
    
        ASSERT(rgprops);
        ASSERT(rgprops[0].ulPropTag == PR_CE_IPM_DRAFTS_ENTRYID);
    
        hr = pStore->OpenEntry(rgprops[0].Value.bin.cb, 
            (LPENTRYID)rgprops[0].Value.bin.lpb, 
            NULL, 
            MAPI_MODIFY, 
            NULL, 
            reinterpret_cast <IUnknown **>(&pfldrDrafts));
        EXIT_ON_FAILED(hr);
    
        ASSERT(pfldrDrafts);
    

        // Now create a message...
        hr = pfldrDrafts->CreateMessage(NULL, 0, &pmsg);
        EXIT_ON_FAILED(hr);
    
        ASSERT(pmsg);
    
        
        // Now set the some properies on the message....
        CEMAPI_SetMessageProps(pmsg);

		// attach a bogus file

		hr=CEMAPI_AttachFile(pmsg);
		EXIT_ON_FAILED(hr);
      
		// Now send the message   
        hr = pmsg->SubmitMessage(0);
        EXIT_ON_FAILED(hr);


        // Clean up
        MAPIFreeBuffer(rgprops);       
        MAPIFreeBuffer(rgpropsMsg);    
        FreeProws(psrs);          
        
        rgprops     =   NULL;    
        rgpropsMsg  =   NULL; 
        psrs        =   NULL;       

        RELEASE_OBJ(pmsg);
        RELEASE_OBJ(pfldrDrafts);
        RELEASE_OBJ(pStore);
    }


FuncExit:
	//Clean up
    MAPIFreeBuffer(rgprops);
    MAPIFreeBuffer(rgpropsMsg);
    FreeProws(psrs);

    RELEASE_OBJ(pmsg);
    RELEASE_OBJ(pfldrDrafts);
    RELEASE_OBJ(pStore);
    RELEASE_OBJ(pTable);
    RELEASE_OBJ(pSession);


	return 0;

}


// **************************************************************************
// Function Name: CountRecipsInString
// Purpose: Counts the number of recipient addresses in a given string

// Arguments:
// IN LPCWSTR psz - string of recipients
// 
// Return Values:
//    ULONG
//		Count of recipients(number of semi-colons + 1)contained in the input string
//
// Description: 
//
// This function merely counts the number of semi-colons in a string and returns that 
// number + 1. This can be interpreted as the number of recipients in a properly formatted
// recipient list
//


ULONG CountRecipsInString(
    LPCWSTR psz
    )
{
    ULONG cRecips = 0;

    if (psz != NULL)
    {
        if (*psz != '\0')
        {
            ++cRecips;
        }

        while (*psz != L'\0')
        {
            if (*psz == L';')
            {
                ++cRecips;
            }
            ++psz;
        }
    }

    return cRecips;
}

// **************************************************************************
// Function Name: CEMAPI_AddRecipients
// Purpose: Sets a message's recipient(s)to a hard-coded value

// Arguments:
// IN LPWSTR pszSrc - semi-colon delimited recipient list
// IN ULONG ulType - Recipient type(To, Cc, or Bcc)
// INOUT ADRLIST* plst - Recipient buffer, pointer is incremented and returned
// IN LPWSTR pszLocalRecips& - local copy of pszSrc
// INOUT LPSPropValue& - buffer to hold message props(address type, recip type, etc),
//		incremented and returned
//
// Return Values:
//    void
//
// Description: 
//
//	This function sets recipient properties for a list of recipients. Properties include 
//	the recipient type(To, Cc, or Bcc), the address type(always SMTP), and the e-mail 
//	address list. The properties are returned through the plst parameter.
//


void CEMAPI_AddRecipients(
    LPWSTR pszSrc, 
    ULONG ulType, 
    ADRLIST* plst, 
    LPWSTR& pszLocalRecips, 
    LPSPropValue& pval
    )
{
    if (pszSrc == NULL)
    {
        return;
    }

    LPWSTR psz = pszSrc;
    while (*psz != L'\0')
    {
        while (*psz == L' ' && *psz != '\0')
        {
            ++psz;
        }

        if (*psz == L'\0')
        {
            break;
        }

        LPWSTR pszEnd = psz;
        while (*pszEnd != L' ' && *pszEnd != ';' && *pszEnd != '\0')
        {
            ++pszEnd;
        }

        int cch = pszEnd - psz;

        wcsncpy(pszLocalRecips, psz, cch);
        *(pszLocalRecips + cch)= L'\0';

        plst->aEntries[plst->cEntries].cValues = 3;
        plst->aEntries[plst->cEntries].rgPropVals = pval;

        // Set the type(To, Cc, Bcc)...
        pval->ulPropTag = PR_RECIPIENT_TYPE;
        pval->Value.ul = ulType;
        ++pval;
        
        // Set the address type(SMTP is the only type currently supported)
        pval->ulPropTag = PR_ADDRTYPE;
        pval->Value.lpszW = L"SMTP";
        ++pval;
        
        // Set the address...
        pval->ulPropTag = PR_EMAIL_ADDRESS;
        pval->Value.lpszW = pszLocalRecips;
        ++pval;

        ++plst->cEntries;

        pszLocalRecips += wcslen(pszLocalRecips)+ 1;

        if (*pszEnd != L'\0')
        {
            ++pszEnd;
        }

        psz = pszEnd;
    }
}



// **************************************************************************
// Function Name: CEMAPI_SetMessageRecipients
// Purpose: Sets a message's recipient(s)to a hard-coded value

// Arguments:
// INOUT LPMESSAGE pmsg - pointer to IMessage interface
//
// Return Values:
//    HRESULT
//    returns S_OK if the message's recipients are successfully modified. Otherwise an error
//	  is returned
// 
// Description:  
//
//	This function defines a hard-coded string which represents the recipients for the given
//	message. The list of recipients is semi-colon delimited. The string for each field(To,
//	Cc, and Bcc)is parsed and a count of recipients is calculated.  A buffer is allocated 
//	to hold the list of recipients. The recipients are added to the the buffer by field type,
//	and the the buffer is passed into IMessage::ModifyRecipients.

HRESULT CEMAPI_SetMessageRecipients(
    LPMESSAGE pmsg
    )
{
    ULONG cRecipients = 0;
    ULONG cchTotalRecips = 0;
	
	//hard-coded recip values. Delimit with semi-colons if more than address is used per field
	//Example: LPWSTR pszTo = L"foo@bar.com;test@bar.com";
    LPWSTR pszTo = L"bogus@domain.example.com"; 
    LPWSTR pszCc = L"";
    LPWSTR pszBcc = L"";
    ADRLIST* plst = NULL;
    LPSPropValue pval = NULL;
    BYTE* pb = NULL;
    LPWSTR pszLocalRecips;
    HRESULT hr;

    if (pszTo)
    {
        cRecipients += CountRecipsInString(pszTo);
        cchTotalRecips += wcslen(pszTo)+ 3;
    }

    if (pszCc)
    {
        cRecipients += CountRecipsInString(pszCc);
        cchTotalRecips += wcslen(pszCc)+ 3;
    }

    if (pszBcc)
    {
        cRecipients += CountRecipsInString(pszBcc);
        cchTotalRecips += wcslen(pszBcc)+ 3;
    }

    //
    // Allocate one big block of memory to hold all the strings.
    // The block is arranged as follows:
    //
    //  ADRLIST               SPropValue's         Copy of addresses
    // |---------------------|--------------------|---------------------|
    //

    DWORD cb = sizeof(ADRLIST)+((sizeof(ADRENTRY)+ sizeof(SPropValue)* 3)* cRecipients);

    pb = new BYTE[cb +(cchTotalRecips * sizeof(WCHAR))];
    if (pb == NULL)
    {
        return E_OUTOFMEMORY;
    }

    ZeroMemory(pb, cb +(cchTotalRecips * sizeof(WCHAR)));

    plst =(ADRLIST*)pb;

    pszLocalRecips =(LPWSTR)(pb + cb);

    pb += sizeof(ADRLIST)+(sizeof(ADRENTRY)* cRecipients);

    pval =(SPropValue*)pb;

    CEMAPI_AddRecipients(pszTo, MAPI_TO, plst, pszLocalRecips, pval);
    CEMAPI_AddRecipients(pszCc, MAPI_CC, plst, pszLocalRecips, pval);
    CEMAPI_AddRecipients(pszBcc, MAPI_BCC, plst, pszLocalRecips, pval);

    hr = pmsg->ModifyRecipients(MODRECIP_ADD, plst);

    delete[](BYTE*)plst;
    
    return hr;
}



// **************************************************************************
// Function Name: CEMAPI_SetMessageProps
// Purpose: Sets some hardcoded properties on a given message

// Arguments:
// INOUT LPMESSAGE pmsg - pointer to IMessage interface
//
// Return Values:
//    HRESULT
//    returns S_OK if the properties are successfully set, otherwise an error is returned
// 
// Description:  
//
//	This function sets up message recipients, sets the message properties, then writes the
//	the message body to the message via an IStream interface.	

HRESULT CEMAPI_SetMessageProps(
    LPMESSAGE pmsg
    )
{
    SPropValue  rgprops[3]  = {0};
    ULONG       cProps      = 0;
    HRESULT     hr;
    LPWSTR      pszSubject  = L"Subject";
    LPWSTR      pszBody     = L"Body.";
    LPSTREAM    pstm        = NULL;


    // Set the recipients up.
	hr = CEMAPI_SetMessageRecipients(pmsg);
    EXIT_ON_FAILED(hr);

    // Set the flags and a subject if they exist.
	rgprops[cProps].ulPropTag = PR_MESSAGE_FLAGS;
    rgprops[cProps].Value.ul = MSGFLAG_FROMME | MSGFLAG_UNSENT;
    ++cProps;
    
    rgprops[cProps].ulPropTag = PR_MSG_STATUS;
    rgprops[cProps].Value.ul = MSGSTATUS_RECTYPE_SMTP;
    ++cProps;

    if (pszSubject != NULL)
    {
        rgprops[cProps].ulPropTag = PR_SUBJECT;
        rgprops[cProps].Value.lpszW = pszSubject;
        ++cProps;
    }
	
	// Apply the property values to this message
    hr = pmsg->SetProps(cProps, rgprops, NULL);
    EXIT_ON_FAILED(hr);

    // Stream the body in...
	hr = pmsg->OpenProperty(PR_BODY, NULL, STGM_WRITE, MAPI_MODIFY, 
        (LPUNKNOWN*)&pstm);
    EXIT_ON_FAILED(hr);

    pstm->Write(pszBody,(wcslen(pszBody)+ 1)* sizeof(WCHAR), NULL);
    pstm->Release();

FuncExit:
    return hr;
}

// **************************************************************************
// Function Name: CEMAPI_AttachFile
// Purpose: Attaches a bogus file to the outgoing message

// Arguments:
// INOUT LPMESSAGE pmsg - pointer to IMessage interface
//
// Return Values:
//    HRESULT
//    returns S_OK if the "file" is successfully attached, otherwise an error is returned
// 
// Description:  
//
//	This function sets up a file attachment and associates it with the specified message,
//	and reads in the file data from via IStream. The "file" in this example is just dummy 
//  data. Normally data from a real file would be streamed in and written to the attachment. 

HRESULT CEMAPI_AttachFile(
    LPMESSAGE pmsg
    )
{
	IAttach * pAttachment = NULL;
	SPropValue rgpropsAttch[3];
	ULONG ulAttachNum;
	HRESULT hr;
	// bogus filename...normally would reference a real file
	WCHAR wcsAttachmentName[] = L"test.txt";
	DWORD dwFileSize;
	ULONG ulStatus = MSGSTATUS_RECTYPE_SMTP;
	IStream * pstmAttachment = NULL;
	// our fake file data, normally would be streamed in from a file
	char szBuf[] = "Hello, Windows CE";
	
	
	dwFileSize = strlen(szBuf)+1;
	// create the attachment
    hr = pmsg->CreateAttach(NULL, 0, &ulAttachNum, &pAttachment);
    EXIT_ON_FAILED(hr);
 
    rgpropsAttch[0].ulPropTag    =   PR_ATTACH_FILENAME;
    rgpropsAttch[0].Value.lpszW  =   wcsAttachmentName;
 
    rgpropsAttch[1].ulPropTag    =   PR_ATTACH_SIZE;
    rgpropsAttch[1].Value.ul     =   dwFileSize;
 
    rgpropsAttch[2].ulPropTag    =   PR_MSG_STATUS;
    rgpropsAttch[2].Value.ul     =   ulStatus;
 
    hr = pAttachment->SetProps(sizeof(rgpropsAttch)/ sizeof(rgpropsAttch[0]), rgpropsAttch, NULL);
    EXIT_ON_FAILED(hr);
 
    // open a stream on the attachment
    hr = pAttachment->OpenProperty(PR_ATTACH_DATA_BIN, NULL /*&IID_IStream*/, STGM_WRITE, MAPI_MODIFY,
                                    reinterpret_cast <IUnknown **>(&pstmAttachment));
    EXIT_ON_FAILED(hr);

    // store chunk from our fake file buffer into the stream
    hr = pstmAttachment->Write(szBuf, 5, NULL);
    EXIT_ON_FAILED(hr);

    // commit it
    hr = pstmAttachment->Commit(STGC_DEFAULT);
    EXIT_ON_FAILED(hr);

   
FuncExit:	
	RELEASE_OBJ(pAttachment);
	RELEASE_OBJ(pstmAttachment);
	return hr;

}
