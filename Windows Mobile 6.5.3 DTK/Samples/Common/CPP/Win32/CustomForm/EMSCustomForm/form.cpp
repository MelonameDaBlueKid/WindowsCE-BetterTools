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

    File: form.cpp

******************************************************************************/
#include "form.h"
#include "msgform.h"


/******************************************************************************

    CFormProvider static member values initialization

******************************************************************************/
BOOL  CFormProvider::m_fInitPropTags = FALSE;
ULONG CFormProvider::m_tagSMSUnicode = PR_NULL; 

/******************************************************************************

    FormFactoryEx - Entrypoint for the Inbox application to use to create forms

    Params:
    pszMsgClass[in] - specifies message class for forms
    ppvObject[out]  - address to store the retrieved interface.  Set to NULL 
                      if the incoming parameters are valid but the object could 
                      not be created.  Not touched if the incoming parameters 
                      are invalid.

    Returns:
    S_OK if the object implementing the interface requested is available and 
           created.
    MAPI_E_INVALID_PARAMETER if one or both of the incoming parameters
          is NULL.
    MAPI_E_NOT_ENOUGH_MEMORY if a memory allocation fails.

 Side effects:  
    A CFormProvider object is created.
 
 Description:  
    This is the entrypoint in the DLL that the Inbox application will look
    for in order to retrieve an IFormProviderEx interface.  This interface
    provides two methods that the app will use to create message forms,
    CreateComposeForm() and CreateReadForm(), as well as a method to
    retrieve the index of the image to be used in the application's
    listview for this type of message, GetMsgStatusIconIndex().

******************************************************************************/
HRESULT WINAPI FormFactoryEx(LPCWSTR pszMsgClass, 
                             IFormProviderEx** ppvObject)
{
    HRESULT hr = S_OK;

    //Validate params
    ASSERT(NULL != pszMsgClass);
    ASSERT(NULL != ppvObject);

    if (NULL == pszMsgClass ||
        NULL == ppvObject)
    {
        RETAILMSG(TRUE, (_T("FormFactoryEx::Invalid argument\n")));
        return MAPI_E_INVALID_PARAMETER;
    }

    //Create the new CFormProvider object to hand back to the application.
    *ppvObject = new CFormProvider;
    
    MAPI_EXIT_ON_NULL(*ppvObject);

    //Now take any action required to use the provider.
    hr = ((CFormProvider*)(*ppvObject))->Init(pszMsgClass);
    
    EXIT_ON_FAILED(hr);
    
Exit:
    if(FAILED(hr))
    {
        SAFE_DELETE(*ppvObject);
    }
    return hr;
}

/******************************************************************************

    CFormProvider::CFormProvider - C'TOR

******************************************************************************/
CFormProvider::CFormProvider() :
m_cRef(1),
m_pMsgStore(NULL),
m_pSession(NULL),
m_pszMessageClass(NULL)
{
}

/******************************************************************************

    CFormProvider::~CFormProvider - D'TOR

******************************************************************************/
CFormProvider::~CFormProvider()
{
    //SAFE_RELEASE(m_pMsg); 
    SAFE_RELEASE(m_pMsgStore);

    //Release session object last
    SAFE_RELEASE(m_pSession);

    delete [] m_pszMessageClass;
}

/******************************************************************************

    CFormProvider::QueryInterface - Standard COM QueryInterface method.

******************************************************************************/
HRESULT CFormProvider::QueryInterface(REFIID iid, void** ppvObject)
{
    // Any interface on this object is the object pointer
    if(IID_IUnknown == iid)
    {
        *ppvObject = this;
    }
    else if(IID_IFormProviderEx == iid)
    {
        *ppvObject = reinterpret_cast<IFormProviderEx*>(this);
    }
    else
    {
        *ppvObject = NULL;
        return(MAPI_E_INTERFACE_NOT_SUPPORTED);
    }

    //Increment the refcount and return success
    AddRef();
    return S_OK;
}

/******************************************************************************
    
    CFormProvider::AddRef - Standard COM AddRef method.

******************************************************************************/
ULONG CFormProvider::AddRef()
{
    return InterlockedIncrement((long*)&m_cRef);
}

/******************************************************************************

    CFormProvider::Release - Standard COM Release method.

******************************************************************************/
ULONG CFormProvider::Release()
{
    if(0 == InterlockedDecrement((long*)&m_cRef))
    {
        delete this;
        return 0;
    }
    return m_cRef;
}

/******************************************************************************

    CFormProvider::GetMsgStatusIconIndex - 
        IFormProviderEx::GetMsgStatusIconIndex implementation.

    Params:
    pfldr[in]       - ignored
    pid[in]         - ignored
    cbId[in]        - ignored
    ffFlags[in]     - ignored
    ffStatus[in]    - ignored
    pszMsgClass[in] - ignored
    cAttachments[in]- ignored
    pnIndex[in/out] - image index to use for the message icon

    Returns:
    S_OK is always returned when pnIndex is non-NULL.
    MAPI_E_INVALID_PARAMETER is returned when pnIndex is NULL.

    Remarks:
    Returns the image index to use for the message icon.  0 is the standard 
    unread normal message icon index.

******************************************************************************/
HRESULT CFormProvider::GetMsgStatusIconIndex(LPMAPIFOLDER pfldr,
                                             LPENTRYID pid,
                                             ULONG cbId,
                                             ULONG ffFlags,
                                             ULONG ffStatus,
                                             LPCWSTR pszMsgClass,
                                             ULONG cAttachments,
                                             ULONG* pnIndex)
{
    HRESULT hr = S_OK;

    //Validate param(s)
    ASSERT(NULL != pnIndex);
    MAPI_CHP(pnIndex);

    //Start off with Unread normal message.
    *pnIndex = 0;

Exit:

    return S_OK;
}

/******************************************************************************

    CFormProvider::CreateComposeForm - IFormProviderEx::CreateComposeForm 
        implementation.

    Params:
    pHost[in]       - Interface for the Inbox application.
    pMsg[in]        - Interface of message to be composed.
    eFormType[in]   - Form type (Read, Reply, Reply All, Forward)
    pMsgBase[in]    - Base message for pMsg
    pMsgFields[in]  - Message field flags
    hwndForm[in]    - HWND of the form frame
    phwndBody[in]   - HWND of the form-created body
    ppForm[in]      - Interface of compose form for created.


    Returns:
    S_OK if the compose form was successfully created.
    MAPI_E_INVALID_PARAMETER if ppForm is NULL.
    MAPI_E_NOT_ENOUGH_MEMORY if a memory allocation fails.
    E_FAIL if any other error occurs.

    Remarks:
    Creates a compose message form and returns an interface to that form's
    IMessageForm interface to the caller.

******************************************************************************/
HRESULT CFormProvider::CreateComposeForm(IMessageFormHostEx* pHost, 
                                         LPMESSAGE pMsg,
                                         FORMTYPE eFormType,
                                         LPMESSAGE pMsgBase,
                                         MESSAGEFIELDS* pMsgFields,
                                         HWND hwndForm,
                                         HWND* phwndBody,
                                         IMessageFormEx** ppForm)
{
    //We don't support compose EMS in this sample
    HRESULT     hr = E_FAIL;
    
    return hr;
}

/******************************************************************************

    CFormProvider::CreateReadForm - IFormProviderEx::CreateReadForm 
        implementation.

    Params:
    pHost[in] - Interface for the Inbox application.
    pMsg[in] - Message to fill the form.
    hwndForm[in] - HWND of the form frame
    phwndBody[in/out] - HWND of the form-created body
    ppForm[in/out] - Interface of read form for created.

    Returns:
    S_OK if the read form was successfully created.
    MAPI_E_INVALID_PARAMETER if ppForm is NULL.
    MAPI_E_NOT_ENOUGH_MEMORY if a memory allocation fails.
    Also, any valid return value from MAPILogonEx(), OpenMsgStore(), or
    GetIDsFromNames() may be returned if one of those calls fails.

    Remarks:
    Creates a read message form and returns an interface to that form's
    IMessageForm interface to the caller.
    
******************************************************************************/
HRESULT CFormProvider::CreateReadForm(IMessageFormHostEx* pHost,
                                      LPMESSAGE pMsg,
                                      HWND hwndForm,
                                      HWND* phwndBody,
                                      IMessageFormEx** ppForm)
{
    MESSAGEFIELDS   msgFields   = {0};
    HRESULT         hr          = E_FAIL;
    CMsgForm*       pForm       = NULL;
    
    // Validate input
    ASSERT (pMsg != NULL);
    ASSERT(NULL != ppForm);
    MAPI_CHP(ppForm);

    *ppForm = NULL;

    //Clean up any other previous sessions
    CleanUpReadForm();

    //Inbox cleans up this new, when the form calls .  This is
    //done whenever the user quits, sends, replies, or deletes a form.
    pForm = new CMsgForm(pHost, pMsg);
    MAPI_EXIT_ON_NULL(pForm);

    //Now initialize the form.
    hr = pForm->Init(this, hwndForm, phwndBody, &msgFields);
    EXIT_ON_FAILED(hr);

    // Let the form know if we'll be prefilling with an existing message's data.
    hr = pForm->SetMessage(0, pMsg);
    EXIT_ON_FAILED(hr);

    // Everything worked ok.
    *ppForm = pForm;
    hr = S_OK;

Exit:

    return hr;
}

/******************************************************************************

    CFormProvider::Init - Initialize the CFormProvider object

    Params:
    pszMsgClass[in] - message class of this form

    Returns:
    S_OK if we initialize properly
    MAPI_E_NOT_ENOUGH_MEMORY if a memory allocation fails

    Remarks:
    Initializes the CFormProvider object, caching off the message class and
    optionally initializing the property tags

******************************************************************************/
HRESULT WINAPI CFormProvider::Init(LPCWSTR pszMsgClass)
{
    HRESULT hr = S_OK;

    ASSERT(NULL != pszMsgClass);
    ASSERT (m_pszMessageClass == NULL);

    MAPI_EXIT_ON_NULL((m_pszMessageClass = new WCHAR[wcslen(pszMsgClass) + 1]));

    wcscpy(m_pszMessageClass, pszMsgClass);

Exit:
    return S_OK;
}

// **************************************************************************
// Function Name: CleanUpReadForm
// 
// Purpose: Do cleanup of any already-open read form handles.
//
// Arguments:
//    None.
//
// Return Values:
//    S_OK is always returned
//
// Side effects:
//    All MAPI handles are released.
// 
// Description:  
//    Releases the reference held on the message, message store, and MAPI
//    session.
/******************************************************************************

    CFormProvider::CleanUpReadForm - Cleanup any already-opened read form
        allocations

    Params:
    None

    Returns:
    S_OK

    Remarks:
    Releases all the the CEMAPI stuff

******************************************************************************/
HRESULT CFormProvider::CleanUpReadForm()
{
    // Release the message and message store
    SAFE_RELEASE(m_pMsgStore);

    // Release session object last
    SAFE_RELEASE(m_pSession);

    return S_OK;
}

/******************************************************************************

    ExtractPicsFromBody - Parses the body of the message for picture objects
    and text we want to display

    Returns:
    S_OK on success, E_xxx OTW

    Remarks:
    We expect the body to be in a certain format.  This is defined in the EMS
    Rule client sample code.

******************************************************************************/
HRESULT ExtractPicsFromBody(LPTSTR pszBody, 
                            UINT* puNumPics, 
                            LPEMSPICINFO* ppEMSPics)
{
    HRESULT hr      = E_FAIL;
    TCHAR*  pCurr   = pszBody;
    TCHAR*  pTemp   = NULL;
    TCHAR*  pEnd    = NULL;
    UINT    uIndex  = 0;
    UINT    uCount  = 0;
    UINT    uNumObj = 0;            //Total object count
    TCHAR   szBuffer[10] = _T("");

    //Validate params
    ASSERT(pszBody);
    ASSERT(puNumPics);
    ASSERT(ppEMSPics);

    if((NULL == pszBody) || (NULL == puNumPics) || (NULL == ppEMSPics))
    {
        goto Exit;
    }

    //Read in the total number of objects
    *puNumPics = 0;
    pCurr += _tcslen(kszEMSID); //Skip the GUID Message ID
    
    //The next 2 TCHARS is the object count in HEX
    memcpy(szBuffer, pCurr, sizeof(TCHAR)*2);
    uNumObj = _tcstol(szBuffer, &pTemp, 16);
    pCurr += 2; //Now point to 1st object
    ZeroMemory(szBuffer, sizeof(szBuffer));

    ASSERT(uNumObj);

    //Now allocate space for each object, these might not all
    //get used if we have objects other than pictures
    *ppEMSPics = (LPEMSPICINFO)malloc(sizeof(EMSPICINFO)*uNumObj);
    ZeroMemory(*ppEMSPics, sizeof(EMSPICINFO)*uNumObj);

    if(NULL == *ppEMSPics)
    {
        goto Exit;
    }

    //Now read in each object
    while(uCount++ < uNumObj)
    {
        UINT uSize = 0;
        UINT uID = 0;
    
        //First 4 TCHARS is the object size
        memcpy(szBuffer, pCurr, sizeof(TCHAR)*4);
        uSize = _tcstol(szBuffer, &pTemp, 16);
        ZeroMemory(szBuffer, sizeof(szBuffer));

        ASSERT(uSize);
        pCurr +=4;      //skip to object data

        //The next 2 TCHARS should be a picture ID
        //either 0x10, 0x11, or 0x12
        memcpy(szBuffer, pCurr, sizeof(TCHAR)*2);
        uID = _tcstol(szBuffer, &pTemp, 16);
        ZeroMemory(szBuffer, sizeof(szBuffer));
        
        if(((uID >= 0x10) && (uID <= 0x12)) || (uID == 0xFF))
        {
            (*puNumPics)++; //found a supported object, PICTURE

            pCurr += 2;

            if(uID != 0xFF) //IEI_TEXT_ONLY skips this
            {
                //OFFSET
                memcpy(szBuffer, pCurr, sizeof(TCHAR)*2);
                (*ppEMSPics + uIndex)->uOffset = _tcstol(szBuffer, &pTemp, 16);
                ZeroMemory(szBuffer, sizeof(szBuffer));
                
                //HRES
                pCurr += 2;
                memcpy(szBuffer, pCurr, sizeof(TCHAR)*2);
                (*ppEMSPics + uIndex)->uHRes = _tcstol(szBuffer, &pTemp, 16);
                ZeroMemory(szBuffer, sizeof(szBuffer));
                
                
                //VRES
                pCurr += 2;
                memcpy(szBuffer, pCurr, sizeof(TCHAR)*2);
                (*ppEMSPics + uIndex)->uVRes = _tcstol(szBuffer, &pTemp, 16);
                ZeroMemory(szBuffer, sizeof(szBuffer));
                
                //PIXEL DATA
                UINT uSizePixels = ((*ppEMSPics + uIndex)->uHRes/4) * 
                            (*ppEMSPics + uIndex)->uVRes;

                pCurr += 2;
                (*ppEMSPics + uIndex)->pszData = 
                    (TCHAR*)malloc(sizeof(TCHAR) * (uSizePixels + 1));
                
                //Fill with byte pattern for debugging
                memset((*ppEMSPics + uIndex)->pszData, 0xBB, sizeof(TCHAR) * (uSizePixels + 1));
                
                //Copy picture data
                memcpy((*ppEMSPics + uIndex)->pszData, pCurr, 
                    sizeof(TCHAR) * uSizePixels);

                //Append NULL
                *((*ppEMSPics + uIndex)->pszData + uSizePixels) = _T('\0');
            
                //TEXT LEN
                pCurr += uSizePixels;
            }

            //Get the length of the text
            memcpy(szBuffer, pCurr, sizeof(TCHAR)*2);
            UINT uTextLen = _tcstol(szBuffer, &pTemp, 16);
            ZeroMemory(szBuffer, sizeof(szBuffer));
            
            pCurr += 2;
                
            //TEXT (IF EXISTS)
            if(uTextLen)
            {
                //Allocate storage
                (*ppEMSPics + uIndex)->pszText = (TCHAR*)malloc(
                sizeof(TCHAR) * (uTextLen + 1));
                ZeroMemory((*ppEMSPics + uIndex)->pszText, sizeof(TCHAR) * (uTextLen + 1));

                //copy the text
                _tcsncpy((*ppEMSPics + uIndex)->pszText, pCurr, uTextLen);

                pCurr += uTextLen;
            }
            
            uIndex++;
        }
        else
        {
            //Somehow an object ID we aren't expecting got here
            ASSERT(TRUE);
        }
    }        

    hr = S_OK;  //Everything was processed ok

Exit:
    
    return hr;
}

/******************************************************************************

    ConvertToMonoBitmap - Converts info obtained from ExtractPicsFromBody() 
    into a monochrome formatted BITMAP.  
     
******************************************************************************/
HRESULT ConvertToMonoBitmap(UINT uNumPics, 
                            LPEMSPICINFO* ppEMSPics, 
                            LPBITMAP pBitmap)
{
    HRESULT hr          = E_FAIL;
    UINT    uCount      = 0;
    LPBYTE  pDest       = NULL;     //Bitmap pixel data
    TCHAR*  pSrc        = NULL;     //String data from EMS
    UINT    uConv       = 0;        //converted byte storage
    TCHAR   szBuffer[3] = _T("");   //String byte to convert
    TCHAR*  pTemp       = NULL;     //conversion end marker

    //Validate params
    ASSERT(uNumPics);
    ASSERT(ppEMSPics);
    ASSERT(pBitmap);

    if((NULL == pBitmap) || (NULL == ppEMSPics))
    {
        goto Exit;
    }

    //Process each pic
    while(uCount < uNumPics)
    {
        //Convert each byte to monochrome format, byte by byte
        //0 = BLACK, 1 = WHITE
        UINT uLen;
        UINT uCurr;

        //Find start of data to convert
        pSrc = (*ppEMSPics + uCount)->pszData;
        
        if(NULL == pSrc) //Text only, has no picture data
        {
            //skip it
            uCount++;
            continue;            
        }

        //Get the length of the data
        uLen = _tcslen(pSrc);

        //Allocate space for the bits
        (pBitmap + uCount)->bmBits = malloc((*ppEMSPics + uCount)->uHRes/4 * 
            (*ppEMSPics + uCount)->uVRes);

        //Set info on the bitmap
        (pBitmap + uCount)->bmType = 0;
        (pBitmap + uCount)->bmPlanes = 1;
        (pBitmap + uCount)->bmBitsPixel = 1;
        (pBitmap + uCount)->bmWidth = (*ppEMSPics + uCount)->uHRes;
        (pBitmap + uCount)->bmHeight = (*ppEMSPics + uCount)->uVRes;
        (pBitmap + uCount)->bmWidthBytes = (*ppEMSPics + uCount)->uHRes/4;
        
        //Do the conversion
        for(uCurr = 0; uCurr < uLen; uCurr++)
        {
            //First convert the string to hex
            ZeroMemory(szBuffer, sizeof(szBuffer));
            memcpy(szBuffer, pSrc, sizeof(TCHAR)*2);
            uConv = ~(_tcstol(szBuffer, &pTemp, 16));
            
            //Invert the number and store it
            memcpy(
                LPBYTE((pBitmap + uCount)->bmBits) + uCurr, 
                (LPBYTE)&uConv, 
                1);
            pSrc+=2;
        }
        uCount++;
    }

    hr = S_OK;

Exit:    
    return hr;
}
