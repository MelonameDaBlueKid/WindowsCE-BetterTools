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
/******************************************************************************

	File: SDKEMSViewerRuleClient.cpp
    
    Purpose: 
    Rule client to intercept EMS messages.  It parses the header and user data 
    and writes info to the message for the EMS custom form to read and process.

    Remarks:
    Must set these reg keys to register the rule client
    [HKCR\CLSID\{7D0E1A87-734C-4d46-B715-327A8884D38B}\InProcServer32]
    @="SDKEMSViewerRuleClient.dll"

    [HKLM\Software\Microsoft\Inbox\Svc\SMS\Rules]
    "{7D0E1A87-734C-4d46-B715-327A8884D38B}" = DWORD : 1

    For EMS to work we also need to set a reg key (requires a reboot if the 
    SMS router has been used)
    [HKEY_CURRENT_USER\Software\Microsoft\SMS\TextShared]
    DWORD : EMSHandlerInstalled = 1

******************************************************************************/
#define INITGUID
#include "SDKEMSViewerRuleClient.h"

//GLOBALS  ////////////////////////////////////////////////////////////////////
// {7D0E1A87-734C-4d46-B715-327A8884D38B}
DEFINE_GUID(CLSID_SDKEMSViewerRuleClient, 
0x7d0e1a87, 0x734c, 0x4d46, 0xb7, 0x15, 0x32, 0x7a, 0x88, 0x84, 0xd3, 0x8b);

int         g_cServerLocks  = 0;
HINSTANCE   g_hInstance     = NULL;

/*List of components handled in this DLL, each component must be listed here
if it wants to able to be loaded by the class factory
*/
CFactoryData g_rgFactoryData[] = 
{   
    {&CLSID_SDKEMSViewerRuleClient,     //CLSID
    CRuleClient_EMS::CreateInstance}    //Creation function ptr

    //Add additional component info here...
    //i.e. if you want to add another rule client
};
//Total number of registered components
int g_iFactoryDataEntries = sizeof(g_rgFactoryData) / sizeof(CFactoryData);

/******************************************************************************

    IsMultiPartEMS - Checks header for multipart info.

    Params:
    lpHeaderData[in] - Header data from SM
    lpEMShi[in/out] - Header info struct to fill

    Returns:
    TRUE if Multipart IEIs exits in header, FALSE OTW

    Remarks:

******************************************************************************/
BOOL IsMultiPartEMS(LPBYTE lpHeaderData, LPEMSHEADERINFO lpEMShi)
{
    BOOL bRet = FALSE;
    UINT uCount = 0;

    //Validate Params
    ASSERT((NULL != lpHeaderData) && (NULL != lpEMShi));
    CBR(((NULL != lpHeaderData) && (NULL != lpEMShi)), bRet);    

    //First IEI should be the Multipart ID if it exists
    if(IEI_MULTI_8BIT == lpHeaderData[uCount])
    {
        //Next octet is length of data, should be 3 octets
        uCount++;
        ASSERT(0x03 == lpHeaderData[uCount]);

        //Next octet is the 8-bit reference number
        uCount++;
        lpEMShi->smRefIDVal.chRefID = lpHeaderData[uCount];
        
        //Next is total parts
        uCount++;
        lpEMShi->uNumParts = lpHeaderData[uCount];
        
        //Next is current part
        uCount++;
        lpEMShi->uCurrPart = lpHeaderData[uCount];
               
        lpEMShi->fRef16Bit = FALSE;
        
        bRet = TRUE;
    }
    else
    if(IEI_MULTI_16BIT == lpHeaderData[uCount])
    {
        //Next octet is length of data, should be 3 octets
        uCount++;
        ASSERT(0x03 == lpHeaderData[uCount]);

        //Next 2 octets are the 16-bit reference number
        uCount++;
        lpEMShi->smRefIDVal.wRefID = ((lpHeaderData[uCount] << 8) | lpHeaderData[uCount+1]);

        //Next is total parts
        uCount++;
        lpEMShi->uNumParts = lpHeaderData[uCount];
        
        //Next is current part
        uCount++;
        lpEMShi->uCurrPart = lpHeaderData[uCount];
        
        lpEMShi->fRef16Bit = TRUE;

        bRet = TRUE;
    }
    
Exit:
    return bRet;
}

/******************************************************************************

    ExtractEMSHeaderInfo - Copies header info to struct and fills in ID etc.

    Params:
    lpEMShi[in\out] - EMSHEADERINFO struct to fill in
    lpHeaderData[in] - EMS header data
    cbHeader[in] - size of header data buffer
    pszUserData[in] - User text with SM, can be NULL

    Returns:
    
    Remarks:

******************************************************************************/
HRESULT ExtractEMSHeaderInfo(LPEMSHEADERINFO lpEMShi, 
                             LPBYTE lpHeaderData, 
                             UINT cbHeader,
                             LPCTSTR pszUserData)
{
    HRESULT hr = S_OK;

    //Validate params
    ASSERT((NULL != pszUserData) && (NULL != lpEMShi) && (0 < cbHeader) && (NULL != lpHeaderData));
    CBRH(((NULL != pszUserData) && (NULL != lpEMShi) && (0 < cbHeader) && (NULL != lpHeaderData)), hr);

    //Clear the struct
    FREE_EMSHEADERINFO((*lpEMShi));

    lpEMShi->lpData = (LPBYTE)malloc(cbHeader);
    ASSERT(NULL != lpEMShi->lpData);
    CBRH((NULL != lpEMShi->lpData), hr);

    //Copy header info, check if multipart, etc
    lpEMShi->cbData = cbHeader;
    memcpy(lpEMShi->lpData, lpHeaderData, cbHeader);
    lpEMShi->fMultiPart = IsMultiPartEMS(lpHeaderData, lpEMShi);

    //Copy user data if we need to 
    if(NULL != *pszUserData)
    {
        lpEMShi->pszUserData = (LPTSTR)malloc(sizeof(TCHAR)*(_tcslen(pszUserData) + 1));
        CBRH((NULL != lpEMShi->pszUserData), hr);

        _tcscpy(lpEMShi->pszUserData, pszUserData);
    }

Exit:
    return hr;

}


/******************************************************************************

    SortHeaderInfo - BubbleSorts the list of EMS headers.  Not the fastest
    sorting algorithm, but the number of headers is almost always small.

    Params:
    lpemshi[in] - pointer to array of header info
    uNumHeaders[in] - count of headers stored in the array

    Returns:
    void

    Remarks:
    
******************************************************************************/
void SortHeaderInfo(LPEMSHEADERINFO lpemshi, UINT uNumHeaders)
{
    int             iIndex;
    int             iItem;
    EMSHEADERINFO   emshi;  //Temp storage

    //Bubblesort
    for(iIndex = uNumHeaders - 1; iIndex >= 0; iIndex--)
    {
        for(iItem = 1; iItem <= iIndex; iItem++)
        {
            if(lpemshi[iItem-1].uCurrPart > lpemshi[iItem].uCurrPart)
            {
                //swap headers
                memcpy(&emshi, &(lpemshi[iItem-1]), sizeof(EMSHEADERINFO));
                memcpy(&(lpemshi[iItem-1]), &(lpemshi[iItem]), sizeof(EMSHEADERINFO));
                memcpy(&(lpemshi[iItem]), &emshi, sizeof(EMSHEADERINFO));
            }
        }
    }
}


/******************************************************************************

    ValidateHeaders - Checks if currently collected headers are ok 

    Params:
    lpemshi[in] - pointer to array of headers to validate
    uNumHeaders[in] - number of headers collected so far

    Returns:
    TRUE on success, FALSE OTW

    Remarks:
    Headers are invalid if we have more than one, and all the IDs don't match

******************************************************************************/
BOOL ValidateHeaders(LPEMSHEADERINFO lpemshi, UINT uNumHeaders)
{
    BOOL bRet = TRUE;
    WORD wRefID = 0;    //stuff 8-bit in here too...
    WORD wTemp = 0;
    UINT uIndex = 0;

    //Validate params
    ASSERT(lpemshi);
    ASSERT(uNumHeaders);
    CBR((lpemshi && uNumHeaders), bRet);

    if(1 == uNumHeaders) //Impossible to have a conflict yet
    {
        goto Exit;
    }
    
    //Get the ID from the first element
    wRefID = lpemshi[0].fRef16Bit ? lpemshi[0].smRefIDVal.wRefID : lpemshi[0].smRefIDVal.chRefID;

    //Multiple case
    for(uIndex = 1; uIndex < uNumHeaders; uIndex++)
    {
        //Every other one better match
        wTemp = lpemshi[uIndex].fRef16Bit ? lpemshi[uIndex].smRefIDVal.wRefID : lpemshi[uIndex].smRefIDVal.chRefID;

        CBR((wTemp == wRefID), bRet);
    }

Exit:
    return bRet;
}


/******************************************************************************

    DeleteMessage - Deletes a message

    Params:
    pMsgStore[in] - Store where message exists
    pMsg[in] - message to delete
    cbMsg[in] - size of message in bytes
    lpMsg[in] - entryid of message
    cbDestFolder[in] - size of dest folder
    lpDestFolder[in] - folder where message resides
    pulEventType[in/out] - tracks what's been done to the message
    pHandled[in/out] - has rule client handled the message or not?

    Returns:
    S_OK on success, HRESULT error code OTW

    Remarks:

******************************************************************************/
HRESULT DeleteMessage(IMsgStore *pMsgStore, 
                      IMessage *pMsg, 
                      ULONG cbMsg, 
                      LPENTRYID lpMsg, 
                      ULONG cbDestFolder, 
                      LPENTRYID lpDestFolder, 
                      ULONG *pulEventType, 
                      MRCHANDLED *pHandled)
{
    HRESULT     hr          = S_OK;
    IMAPIFolder *pFolder    = NULL;
    ENTRYLIST   lst;
    SBinary     sbin;

    UNREFERENCED_PARAMETER(pHandled);
    UNREFERENCED_PARAMETER(pMsg);
    
    //Get the folder the message is in
    hr = pMsgStore->OpenEntry(cbDestFolder, lpDestFolder, NULL, 0, NULL, (LPUNKNOWN*)&pFolder);
    if(FAILED(hr))
    {
        RETAILMSG(TRUE, (_T("Couldn't get the folder!\r\n")));
        goto Exit;
    }
    
    //Set up the entry list
    lst.cValues = 1;                //Just the one item
    lst.lpbin   = &sbin;            //binary entry
    sbin.cb     = cbMsg;            //Size of message in bytes
    sbin.lpb    = (LPBYTE)lpMsg;    //Pointer to message
    
    //Delete the message from the folder
    hr = pFolder->DeleteMessages(&lst, NULL, NULL, 0); 
    if(FAILED(hr))
    {
        RETAILMSG(TRUE, (_T("Couldn't delete messages!\r\n")));
        goto Exit;
    }

    //Record action taken on the message
    *pulEventType = fnevObjectDeleted;
    
Exit:
    //Done using the folder
    SAFE_RELEASE(pFolder);
    
    return hr;
}

/******************************************************************************

    ProcessEMS - Process each EMS header.  Order is assured for this function

    Params:
    emshi[in] - header info for current part
    ppszOut[in/out] - Final string to write to message body, if NULL and return
        value is ok, then we're not done processing.  If non-NULL and return
        value is ok, then we're done
    pNumObjects[in/out] - number of objects in EMS, 0 if fail or not done

    Returns:
    S_OK on success, E_FAIL OTW

    Remarks:
    output format in string form is...
    [Obj Len1][Obj Data1]...[Obj'N' Len][Obj Data'N']
        4                         4          
    Bottom number is number of TCHARS... 
    
******************************************************************************/
HRESULT ProcessEMS(EMSHEADERINFO emshi,
                   LPTSTR* ppszOut,
                   UINT* pNumObjects)
{
        HRESULT hr                  = S_OK;
        BYTE    chIEI               = 0;
        BYTE    chIEIDL             = 0;
        UINT    uCount              = 0;
        TCHAR   szBuffer[MAX_PATH]  = _T("");
        LPTSTR  pszTemp             = NULL;
        UINT    uChar               = 0;
        UINT    uLenTemp            = 0;
static  TCHAR*  szBodyOut           = NULL;
static  UINT    uBaseOffset         = 0;
static  UINT    uObjCount           = 0;

    //Validate params, user data can be NULL
    ASSERT(NULL != ppszOut);
    ASSERT(NULL != pNumObjects);
    
    if((NULL == ppszOut) || (NULL == pNumObjects))
    {
        RETAILMSG(TRUE, (_T("ProcessEMS - ERROR!!! invalid argument(s)")));
        hr = E_INVALIDARG;
        goto Exit;
    }

    //skip to first IEI if multipart SM
    if(emshi.fMultiPart)
    {
        uCount += 5; //1 for length, 3 for IEID info, 1 to point to next IEI
    }

    //It's possible a portion of the EMS will contain only text
    //picture or other element won't fix so check for that
    if(uCount == emshi.cbData)
    {
        //[ID = IEI_TEXT_ONLY][Text Len][Text]
        UINT    uConv       = 0;
        UINT    uPos        = 0;
        UINT    uStrLen     = 0;
        TCHAR   szConv[3]   = _T("");

        //We'd better have text or else the message was empty?
        ASSERT(emshi.pszUserData);
        uStrLen = _tcslen(emshi.pszUserData);

        //Allocate room for the user data
        pszTemp = (TCHAR*)malloc(sizeof(TCHAR) * (uStrLen + 5));
        ASSERT(pszTemp);

        ZeroMemory(pszTemp, sizeof(TCHAR) * (_tcslen(emshi.pszUserData) + 5));
        
        //Add the ID
        _tcscat(pszTemp, _T("FF")); //IEI_TEXT_ONLY

        //Add the length
        szConv[0] = _T('0');
        uPos = (uStrLen < 0x10) ? 1 : 0;
        _itot(uStrLen, &(szConv[uPos]), BASE_HEX);
        _tcscat(pszTemp, szConv);

        //Add the data
        _tcscat(pszTemp, emshi.pszUserData);
        
        uObjCount++;            //Increase object count
        uBaseOffset += uStrLen; //Increase offset
    }
    else
    {
        //Get each IEI and IED segments
        while(uCount < emshi.cbData)
        {
            //Now we should be pointing to the next IEI
            chIEI = emshi.lpData[uCount];
            uCount++;

            //In all cases the next octet is the length of data IEIDL
            chIEIDL = emshi.lpData[uCount];
            uCount++;

            switch(chIEI)
            {
                //Only supported objects in the sample
                case IEI_LARGE_PICTURE:
                case IEI_SMALL_PICTURE:
                case IEI_VARIABLE_PICTURE:
                {
                    //This works since the IEIs are in order 0x10, 0x11, 0x12
                    int iType = chIEI - IEI_LARGE_PICTURE;

                    ASSERT((iType >= 0) && (iType <= 2));

                    //Create object to deal with the picture info
                    CEMSPicture* pPicture = new CEMSPicture(&(emshi.lpData[uCount]), 
                                                            chIEIDL, 
                                                            uBaseOffset, 
                                                            emshi.pszUserData, 
                                                            iType);
                    ASSERT(NULL != pPicture);
                    CBRH((NULL != pPicture), hr);
                    
                    //Grab the data
                    CBRH((pPicture->ExtractInfoFromHeader()), hr);
                    
                    //Do some validation on that data
                    CBRH((pPicture->ValidateData()), hr);

                    //Convert data to string for message body
                    CBRH((pPicture->ToString(&pszTemp)), hr);
                    
                    //Done with our picture object
                    SAFE_DELETE(pPicture);

                    //inc the base offset
                    if(emshi.pszUserData)
                    {
                        //Text + the picture
                        uBaseOffset += (_tcslen(emshi.pszUserData));
                    }
                    else
                    {
                        uBaseOffset++; //just the picture
                    }
                    uCount += chIEIDL;  //point to next IEI
                    uObjCount++;        //Increase object count
                    break;
                }

                /*
               NYI...to implement, simply fill in each of the defined 
               classes and place code here to handle their instantiation 
               and use.  Or define your own objects, etc.
               */
                case IEI_TEXT_FORMATTING:
                case IEI_PREDEFINED_SOUND:
                case IEI_USERDEFINED_SOUND:
                case IEI_PREDEFINED_ANIM:
                case IEI_LARGE_ANIM:
                case IEI_SMALL_ANIM:
                case IEI_USER_PROMPT:
                {
                    //For now, skip the object, don't update uBaseOffset or 
                    //uObjCount, it's like it doesn't exist
                    uCount += chIEIDL;

                    if(emshi.pszUserData)   //Still want the text portion
                    {
                        //[ID = IEI_TEXT_ONLY][Text Len][Text]
                        UINT    uConv       = 0;
                        UINT    uPos        = 0;
                        UINT    uStrLen     = 0;
                        TCHAR   szConv[3]   = _T("");

                        ASSERT(emshi.pszUserData);
                        uStrLen = _tcslen(emshi.pszUserData);

                        pszTemp = (TCHAR*)malloc(sizeof(TCHAR) * (uStrLen + 5));
                        ASSERT(pszTemp);

                        ZeroMemory(pszTemp, sizeof(TCHAR) * (_tcslen(emshi.pszUserData) + 5));
                        _tcscat(pszTemp, _T("FF")); //IEI_TEXT_ONLY

                        szConv[0] = _T('0');
                        uPos = (uStrLen < 0x10) ? 1 : 0;
                        _itot(uStrLen, &(szConv[uPos]), BASE_HEX);
                        _tcscat(pszTemp, szConv);

                        _tcscat(pszTemp, emshi.pszUserData);
                        uObjCount++;        //Increase object count
                        uBaseOffset += uStrLen;
                    }
                    break;
                }

                default:
                {
                    //shouldn't get any IEIs here that aren't handled
                    //or at least recognized
                    ASSERT(FALSE);
                    hr = E_FAIL;
                    goto Exit;
                }
            }
        }
    }
        
    if(NULL == szBodyOut)  //First time saving to buffer
    {
        //+1 for NULL +4 for Object Length
        UINT uLen = _tcslen(pszTemp) + 5;
        szBodyOut = (TCHAR*)malloc(sizeof(TCHAR) * (uLen));
        CBRH((NULL != szBodyOut), hr);
        ZeroMemory(szBodyOut, sizeof(TCHAR) * (uLen));
    }
    else
    {
        //Get size of current string, and the new one
        size_t sizeold = sizeof(TCHAR)*_tcslen(szBodyOut);
        size_t size = sizeof(TCHAR)*(_tcslen(pszTemp) + 5) + sizeold;
        
        //Save the old string
        TCHAR* szTemp = (TCHAR*)malloc(sizeold);
        memcpy(szTemp, szBodyOut, sizeold);

        //Allocate additional room for new string
        TCHAR* szNewOut = (TCHAR*)realloc(szBodyOut, size);
        CBRH((NULL != szNewOut), hr);

        szBodyOut = szNewOut; //Save new pointer

        //Clear it
        memset(szBodyOut, 0x00, size);
        
        //Copy old string, delete temp one
        memcpy(szBodyOut, szTemp, sizeold);
        free(szTemp);
    }

    //Append object length
    //force this to 4 TCHARS
    uLenTemp = _tcslen(pszTemp);
    szBuffer[0] = _T('0');
    szBuffer[1] = _T('0');
    szBuffer[2] = _T('0');
    uChar = (uLenTemp < 0x1000) ? 1 : 0;
    uChar = (uLenTemp < 0x100)  ? 2 : uChar;
    uChar = (uLenTemp < 0x10)   ? 3 : uChar;
    _itot(uLenTemp, &(szBuffer[uChar]), BASE_HEX);
    _tcscat(szBodyOut, szBuffer);
        
    //Append object data
    _tcscat(szBodyOut, pszTemp);
    free(pszTemp);
    pszTemp = NULL;

    //Check if last SM in multipart, or just done
    if((emshi.uCurrPart == emshi.uNumParts) || (!emshi.fMultiPart))
    {
        //allocate room for string buffer
        *ppszOut = (TCHAR*)malloc(_msize(szBodyOut));
        CBRH((NULL != *ppszOut), hr);

        //Copy string buffer
        memcpy(*ppszOut, szBodyOut, _msize(szBodyOut));

        //free internal copy
        free(szBodyOut);

        //Write out number of objects processed
        *pNumObjects = uObjCount;

        //Set this so we will cleanup on exit
        emshi.fMultiPart = FALSE;
    }
    
Exit:

    if(FAILED(hr) || (!emshi.fMultiPart))
    {
        if(pszTemp)
        {
            free(pszTemp);
            pszTemp = NULL;
        }
        if(szBodyOut)
        {
            free(szBodyOut);
            szBodyOut = NULL;
        }

        //reset counters
        uObjCount = 0;
        uBaseOffset = 0;
    }

    return hr;
}

/******************************************************************************

    WriteEMSToBody - Write out EMS info to body of message 

    Params:
    szEMSData[in] - String to write to body
    szMessageClass[in] - Message class to set (optional)
    pMsg[in] - Message we're writing to
    uObjCount[in] - number of objects in data string
    Returns:

    Remarks:

******************************************************************************/
HRESULT WriteEMSToBody(LPCTSTR szEMSData, 
                       LPCTSTR szMessageClass, 
                       IMessage* pMsg, 
                       UINT uObjCount)
{
    HRESULT     hr          = S_OK;
    int         cbBody      = 0;
    int         iCount      = 0;
    SPropValue  rgProps[2];         //PR_MESSAGE_CLASS and PR_SUBJECT
    LPSTREAM    pStmBody    = NULL;
    DWORD       cbWritten   = 0;
    TCHAR       szBuffer[3] = _T("");
    BYTE        uChar       = 0x00;
    TCHAR*      pszBody     = NULL;

    //Validate params, szMessageClass can be NULL, then we just don't alter it
    ASSERT(NULL != szEMSData);
    ASSERT(NULL != pMsg);
    ASSERT(uObjCount);
    if((NULL == pMsg) || (NULL == szEMSData) || (0 >= uObjCount))
    {
        hr = E_INVALIDARG;
        goto Exit;
    }

    //Set message class if we have one
    if(NULL != szMessageClass)
    {
        rgProps[iCount].ulPropTag   = PR_MESSAGE_CLASS;
        rgProps[iCount].Value.lpszW = const_cast<LPTSTR>(szMessageClass);
        iCount++;
    }
    rgProps[iCount].ulPropTag   = PR_SUBJECT;
    rgProps[iCount].Value.lpszW = _T("SDK EMS SAMPLE");
    iCount++;
    
    //Open the body property
    if(FAILED(hr = pMsg->OpenProperty(PR_BODY, NULL, 0,
                        MAPI_MODIFY | MAPI_CREATE, (LPUNKNOWN*)&pStmBody)))
    {
        goto Exit;
    }

    //Calculate length of body
    cbBody = sizeof(TCHAR)*(_tcslen(szEMSData) + _tcslen(STR_EMSID) + 3);

    pszBody = (TCHAR*)malloc(cbBody);

    CBRH((NULL != pszBody), hr);
    ZeroMemory(pszBody, cbBody);

    //Append the GUID
    _tcscat(pszBody, STR_EMSID);

    //Append number of objects
    szBuffer[0] = _T('0');
    uChar = (uObjCount < 0x10) ? 1 : 0;
    _itot(uObjCount, &(szBuffer[uChar]), BASE_HEX);
    _tcscat(pszBody, szBuffer);

    //Append rest of data
    _tcscat(pszBody, szEMSData);

    //Write string to body property
    if(FAILED(hr = pStmBody->Write(pszBody, cbBody, &cbWritten)) ||
        (cbWritten != (DWORD)cbBody))
    {
        if(hr == S_OK)
        {
            hr = E_FAIL;
        }
        goto Exit;
    }
    
    //Commit the change and finish
    if(FAILED(hr = pStmBody->Commit(0)))
    {
        goto Exit;
    }

    //Set whatever props
    if(FAILED(hr = pMsg->SetProps(iCount, rgProps, NULL)))
    {
        goto Exit;
    }

Exit:
    if(pszBody)
    {
        free(pszBody);
    }
    if(pStmBody)
    {
        pStmBody->Release();
    }
    return hr;
}

/******************************************************************************

    CFactory::CFactory - C'TOR, called by the static method GetClassObject once
    it determines the type of object the factory will create

******************************************************************************/
CFactory::CFactory(const CFactoryData* pFData) :
m_cRef(1)
{
    //I'm the only one calling this so pFData shouldn't be NULL
    ASSERT(pFData);

    //Init the factory data info
    memcpy(&m_FactoryData, pFData, sizeof(CFactoryData));
}

/******************************************************************************

    CFactory::~CFactory - D'TOR, add whatever you might need here....

******************************************************************************/
CFactory::~CFactory()
{
    RETAILMSG(TRUE, (_T("CFactory - destroying self.")));
}

/******************************************************************************

    CFactory::QueryInterface - IUnknown implementation

    Interfaces implemented:
    IID_IUnknown
    IID_IClassFactory

******************************************************************************/
STDMETHODIMP CFactory::QueryInterface(const IID& iid, LPVOID *ppv)
{
    HRESULT hr = E_NOINTERFACE;

    //Validate params
    if(!ppv)
    {
        hr = E_INVALIDARG;
        goto Exit;
    }
    
    //Check if requested interface is supported
    if((IID_IUnknown == iid) || (IID_IClassFactory == iid))
    {
        //Yes it is
        *ppv = reinterpret_cast<LPVOID>(this);
    }
    else
    {
        //No it isn't
        *ppv = NULL;
    }

    if(*ppv) 
    {
        //Interface was obtained so ref count
        (reinterpret_cast<IUnknown*>(*ppv))->AddRef();
        hr = S_OK;
    }
    
Exit:
    return hr;
}

/******************************************************************************

    CFactory::AddRef - IUnknown implementation, pretty standard

******************************************************************************/
ULONG CFactory::AddRef()
{
    RETAILMSG(TRUE, (_T("CFactory::AddRef->m_cRef is now %d\r\n"), m_cRef+1));
    return InterlockedIncrement(&m_cRef);
}

/******************************************************************************

    CFactory::Release - IUnknown implementation, pretty standard

******************************************************************************/
ULONG CFactory::Release()
{
    InterlockedDecrement(&m_cRef);
    RETAILMSG(TRUE, (_T("CFactory::Release->m_cRef is now %d\r\n"), m_cRef));
    
    int nLocal = m_cRef;    //make a copy in case we're destroyed

    if(!m_cRef) 
    {
        //Ref count is now 0, destroy ourselves
        RETAILMSG(TRUE, (_T("CFactory::Release -> CFactory Deleted!\r\n")));
        delete this; 
    }

    return nLocal; 
}

/******************************************************************************

    CFactory::GetClassObject - called by DllGetClassObject, this enables us to
    host muliple components using the same class factory (yippe!!)

    Params:
    clsid[in] - CLSID of object we're looking to create
    iid[in]   - id of interface we want in said object
    ppv[out]  - gets the class factory ready to create correct object

******************************************************************************/
HRESULT CFactory::GetClassObject(const CLSID& clsid, const IID& iid, void** ppv)
{
    HRESULT hr      = S_OK;
    int     iIndex  = 0;

    //Interface must be one of these
    if((IID_IUnknown != iid) && (IID_IClassFactory != iid))
    {
        hr = E_NOINTERFACE;
        goto Exit;
    }

    //Check listed components this dll can load and match against CLSID
    for(iIndex = 0; iIndex < g_iFactoryDataEntries; iIndex++)
    {
        //Get data for each listed component
        const CFactoryData* pFData = &g_rgFactoryData[iIndex];
        
        //Check if requested CLSID is a match
        if(pFData->IsClassID(clsid))
        {
            //Bingo, create a class factory for this component
            *ppv = reinterpret_cast<IUnknown*>(new CFactory(pFData));

            if(NULL == *ppv)
            {
                hr = E_OUTOFMEMORY;
            }
            goto Exit; //We're done either way
        }
    }
    hr = CLASS_E_CLASSNOTAVAILABLE;

Exit:
    return hr;
}

/******************************************************************************

    CFactory::CreateInstance - Creates an instance of a component hosted in the
    DLL.  At this point we have all the info we need to create the correct one.

    Params:
    pUnknownOuter[in]   - COM aggregation stuff, not allowed here
    iid[in]             - id if interface we want
    ppv[out]            - pointer to requested interface 

******************************************************************************/
STDMETHODIMP CFactory::CreateInstance(IUnknown* pUnknownOuter, 
                                      const IID& iid, void** ppv)
{
    HRESULT     hr              = S_OK;
    IUnknown*   pNewComponent   = NULL;

    //No aggregation
    if(pUnknownOuter)
    {
        hr = CLASS_E_NOAGGREGATION;
        goto Exit;
    }

    //Create the component
    //m_FactoryData is initialized in the constructor, by the time CFactory is
    //created it knows how to create each type of object
    if(FAILED(hr = m_FactoryData.CreateInstance(pUnknownOuter, &pNewComponent)))
    {
        RETAILMSG(TRUE, (_T("CFactory::CreateInstance - m_FactoryData.CreateInstance failed")));
        goto Exit;
    }

    //Get the requested interface
    if(FAILED(hr = pNewComponent->QueryInterface(iid, ppv)))
    {
        RETAILMSG(TRUE, (_T("CFactory::CreateInstance - QueryInterface failed")));
        goto Exit;
    }
    pNewComponent->Release();    
    
Exit:
    return hr;
}


/******************************************************************************

    CFactory::LockServer - COM stuff, used by client to make sure DLL isn't
    unloaded while factory is in use.  In our case the DLL will stay loaded as
    long as tmail.exe is running, so it shouldn't be a real problem, but we 
    have to implement it anyway as part of the IClassFactory interface

    Params:
    bLock[in] - TRUE to add lock, FALSE to release lock

    Returns:
    S_OK - can't really fail.

******************************************************************************/
STDMETHODIMP CFactory::LockServer(BOOL bLock)
{
    if(bLock)
    {
        g_cServerLocks++;
    }
    else
    {
        g_cServerLocks--;
    }

    return S_OK;
}

/******************************************************************************

    CRuleClientBase::CRuleClientBase - C'TOR

******************************************************************************/
CRuleClientBase::CRuleClientBase():
m_cRef(1),
m_mrcAccess(MRC_ACCESS_NONE),
m_mrcHandled(MRC_NOT_HANDLED)
{
}

/******************************************************************************

    CRuleClientBase::~CRuleClientBase - D'TOR

******************************************************************************/
CRuleClientBase::~CRuleClientBase()
{
    RETAILMSG(TRUE, (_T("CRuleClientBase - Destroying self")));
}

/******************************************************************************
******************************************************************************/
HRESULT CRuleClientBase::QueryInterface(const IID& iid, void** ppobj)
{	
    HRESULT hr = E_NOINTERFACE;

    if(!ppobj)
    {
        return E_INVALIDARG;
    }
    
	*ppobj = NULL;
	if((IID_IUnknown == iid) || (IID_IMailRuleClient == iid))
	{
	 	*ppobj = reinterpret_cast<LPVOID>(this);
 	}

    if (*ppobj) 
    {
	 	(reinterpret_cast<IUnknown*>(*ppobj))->AddRef();
		hr = S_OK;
	}
	
	return hr;
}

/******************************************************************************
******************************************************************************/
ULONG CRuleClientBase::AddRef()
{
    return InterlockedIncrement(&m_cRef);
}

/******************************************************************************
******************************************************************************/
ULONG CRuleClientBase::Release()
{
    InterlockedDecrement(&m_cRef);

    int nLocal = m_cRef;

    if(!m_cRef) 
    {
        delete this; 
    }

    return nLocal; 
}

/******************************************************************************

    CRuleClientBase::Initialize - Derived classes need to override

******************************************************************************/
HRESULT CRuleClientBase::Initialize(IMsgStore *pMsgStore, MRCACCESS *pmaDesired)
{
    UNREFERENCED_PARAMETER(pMsgStore);
    UNREFERENCED_PARAMETER(pmaDesired);
    return E_NOTIMPL;
}
            
/******************************************************************************

    CRuleClientBase::ProcessMessage - Derived classes need to override

******************************************************************************/
HRESULT CRuleClientBase::ProcessMessage(IMsgStore *pMsgStore, 
                                        ULONG cbMsg,
                                        LPENTRYID lpMsg, 
                                        ULONG cbDestFolder, 
                                        LPENTRYID lpDestFolder, 
                                        ULONG *pulEventType, 
                                        MRCHANDLED *pHandled)
{
    UNREFERENCED_PARAMETER(pMsgStore);
    UNREFERENCED_PARAMETER(cbMsg);
    UNREFERENCED_PARAMETER(lpMsg);
    UNREFERENCED_PARAMETER(cbDestFolder);
    UNREFERENCED_PARAMETER(lpDestFolder);
    UNREFERENCED_PARAMETER(pulEventType);
    UNREFERENCED_PARAMETER(pHandled);
    return E_NOTIMPL;
}

/******************************************************************************

    CRuleClient_EMS::~CRuleClient_EMS - D'TOR

******************************************************************************/
CRuleClient_EMS::~CRuleClient_EMS()
{
    RETAILMSG(TRUE, (_T("CRuleClient_EMS - Destroying self")));
}

/******************************************************************************

    CRuleClient_EMS::CreateInstance - Each rule client in this DLL must
    implement this function, it's called by CFactory to create each component

    Params:
    pUnknownOuter[in]   - COM aggregation stuff, it will always be null or
                          CFactory won't even call this method, I pass it along
                          in case someday I want to support aggregation, and
                          thus would have to modify CFactory
    ppNewComponent[out] - pointer to component created here

    Returns:
    S_OK on success, or E_OUTOFMEMORY if we can't instantiate the class

******************************************************************************/
HRESULT CRuleClient_EMS::CreateInstance(IUnknown* pUnknownOuter, 
                                        IUnknown** ppNewComponent)
{
    HRESULT hr = S_OK;

    UNREFERENCED_PARAMETER(pUnknownOuter);

    //only CFactory is calling this, ptr* should be good
    *ppNewComponent = new CRuleClient_EMS();

    if(NULL == *ppNewComponent)
    {
        hr = E_OUTOFMEMORY;
    }

    return hr;
}

/******************************************************************************

    CRuleClient_EMS::Initialize - 

******************************************************************************/
HRESULT CRuleClient_EMS::Initialize(IMsgStore *pMsgStore, 
                                    MRCACCESS *pmaDesired)
{
    UNREFERENCED_PARAMETER(pMsgStore);

    RETAILMSG(TRUE, (_T("CRuleClient_EMS::Initialize")));
    
    //Set the Access, Handled, and target string for the client
    m_mrcAccess = MRC_ACCESS_WRITE;
        
    *pmaDesired = m_mrcAccess;

    return S_OK;
}

/******************************************************************************
******************************************************************************/
HRESULT CRuleClient_EMS::ProcessMessage(IMsgStore *pMsgStore, 
                                        ULONG cbMsg,
                                        LPENTRYID lpMsg, 
                                        ULONG cbDestFolder, 
                                        LPENTRYID lpDestFolder,
                                        ULONG *pulEventType, 
                                        MRCHANDLED *pHandled)
{
        SizedSPropTagArray(2, spta) = { 2, PR_CE_EMS_HEADER_DATA, PR_SUBJECT }; 
        HRESULT         hr                      = S_OK;
        IMessage*       pMsg                    = NULL;
        SPropValue*     pspv                    = NULL;
        ULONG           cValues                 = 0;
        MRCHANDLED      mrcHandled              = MRC_NOT_HANDLED;
        UINT            uIndex                  = 0;
static  BOOL            fProcessing             = FALSE;           
static  EMSHEADERINFO   emshi[MAX_EMS_HEADERS]  = {0};
static  UINT            uHeaderCount            = 0;

    //Get the message from the entry ID
    hr = pMsgStore->OpenEntry(cbMsg, lpMsg, NULL, 0, NULL, (LPUNKNOWN *) &pMsg);
    if(FAILED(hr))
    {
        RETAILMSG(TRUE, (_T("CRuleClient_EMS - Unable to get the message!\r\n")));
        goto Exit;
    }
    
    //Try to get the EMS header data
    hr = pMsg->GetProps((SPropTagArray *) &spta, MAPI_UNICODE, &cValues, &pspv);
    if(FAILED(hr))
    {
        //Failed, or it's not an EMS
        RETAILMSG(TRUE, (_T("CRuleClient_EMS - Couldn't get the SM header!\r\n")));
        goto Exit;
    }
    
    //Did we succeed in getting the data, or is there none to get?
    //There might not be any user data, so it could be NULL
    if((2 == cValues) && (NULL != pspv[0].Value.bin.lpb) && (0 != pspv[0].Value.bin.cb))
    {
        /*
        Because the order of the incomming EMS headers can not be assured, we
        have to grab each header (if multipart) then pass them in order to be
        processed.  If we only have one, this is easy.  If we have several, we
        must keep track of the headers collected, determine when we're done,
        then pass the headers to the processing function.  In addition, we'll
        check the IDs of the parts to make sure they all match.  We shouldn't
        get parts of different sequences at the same time.
        */

        //Insert header data into next slot
        if(FAILED(ExtractEMSHeaderInfo(&(emshi[uHeaderCount]),
                                 pspv[0].Value.bin.lpb,
                                 pspv[0].Value.bin.cb,
                                 pspv[1].Value.lpszW)))
        {
            //Massive failure, probably OOM...
            hr = E_FAIL;
            goto Exit;
        }
        fProcessing = TRUE; //got at least one...

        uHeaderCount++;
        if(uHeaderCount >= MAX_EMS_HEADERS)
        {
            //Too many headers...
            hr = E_FAIL;
            goto Exit;
        }

        /*Validate headers. This is needed in case we get a header 
        with a different ID. If this happens we just start over using 
        this header as the first in a new sequence*/
        if(!ValidateHeaders(emshi, uHeaderCount))
        {
            //NYI...reset and store the last header as the first
            //For now just fail
            hr = E_FAIL;
            goto Exit;
        }

        //Check if not done collecting parts
        if((!(emshi[0].fMultiPart)) || !(emshi[0].uNumParts != (uHeaderCount)))
        {
            fProcessing = FALSE;
        }

        //Send the parts to be dealt with
        if(!fProcessing)
        {
            TCHAR*  psz         = NULL;
            UINT    uObjCount   = 0;
            
            //Sort the headers so they get passed in order
            if(1 < uHeaderCount)
            {
                SortHeaderInfo(emshi, uHeaderCount);
            }

            //Process each header
            for(uIndex = 0; uIndex < uHeaderCount; uIndex++)
            {
                //Process each EMS
                if(FAILED(ProcessEMS(emshi[uIndex], &psz, &uObjCount)))
                {
                    //Massive error, maybe OOM...
                    hr = E_FAIL;
                    goto Exit;
                }
            }
            //If we didn't fail above, this should be non-NULL
            ASSERT(psz);
            CBRH((NULL != psz), hr);
            
            //The message class here, is used by the custom form
            //later when the user opens the message for viewing
            WriteEMSToBody(psz, _T("IPM.SMStext.SDKEMS"), pMsg, uObjCount);
            
            free(psz);
        }
        else
        {
            //Still waiting for more, delete this one
            DeleteMessage(pMsgStore, pMsg, cbMsg, lpMsg, cbDestFolder, lpDestFolder, pulEventType, pHandled);
        }

        //We get all EMS...not really the best 'real-world' solution
        //but for this sample don't let any other rules have the message
        mrcHandled = MRC_HANDLED_DONTCONTINUE;
    }
    
Exit:
    if(FAILED(hr) || (!fProcessing))
    {
        fProcessing = FALSE;
        
        //Free header info slots we used
        for(uIndex = 0; uIndex < uHeaderCount; uIndex++)
        {
            FREE_EMSHEADERINFO(emshi[uIndex]);
        }
        uHeaderCount = 0;
    }

    //cleanup
    if(pspv)
    {
        MAPIFreeBuffer(pspv);
    }
    if(pMsg)
    {
        pMsg->Release();
    }
    
    *pHandled = mrcHandled;
    
    return hr;
}


/******************************************************************************

    LibMain - DLL entry point, does a whole lot o' nothing

******************************************************************************/
EXTERN_C BOOL WINAPI LibMain(HINSTANCE hinst, DWORD dwReason, LPVOID lpv)
{
    UNREFERENCED_PARAMETER(lpv);

    g_hInstance = hinst;

    switch(dwReason)
    {
        case DLL_PROCESS_ATTACH:
            break;

        case DLL_PROCESS_DETACH:
            break;
    }

    return TRUE;
}

/******************************************************************************

    DllGetClassObject - COM stuff, client will call this to get interface to
    requested component.  This method delegates that out to 
    CFactory::GetClassObject, which does a lookup of supported components and
    creates the correct one.

******************************************************************************/
STDAPI DllGetClassObject(const CLSID& clsid, const IID& iid, LPVOID *ppv)
{
    HRESULT     hr       = E_FAIL;
    CFactory*   pFactory = NULL;
    
    if(FAILED(hr = CFactory::GetClassObject(clsid, iid, (void**)&pFactory)))
    {
        RETAILMSG(TRUE, (_T("DllGetClassObject - CFactory::GetClassObject failed")));
        goto Exit;
    }

    // Get the requested interface
    if(FAILED(hr = pFactory->QueryInterface(iid, ppv)))
    {
        RETAILMSG(TRUE, (_T("DllGetClassObject - QueryInterface failed")));
        goto Exit;
    }
    pFactory->Release();
    
Exit:
    return hr;
}

/******************************************************************************

    DllCanUnloadNow - COM stuff, client calls this to see if the DLL can be 
    safely unloaded.

******************************************************************************/
STDAPI DllCanUnloadNow()
{
    if(!g_cServerLocks)
    {
        //Save to unload...
        return S_OK;
    }
    else
    {
        return S_FALSE;
    }
}

/******************************************************************************

    DllRegisterServer - COM stuff

******************************************************************************/
STDAPI DllRegisterServer()
{
    return S_OK;
}

/******************************************************************************

    DllUnregisterServer - COM stuff

******************************************************************************/
STDAPI DllUnregisterServer()
{
    return S_OK;
}