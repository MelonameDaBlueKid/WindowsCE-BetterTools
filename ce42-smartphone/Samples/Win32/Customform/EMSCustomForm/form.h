/******************************************************************************

    File: form.h

    Purpose: 

    Author: Matthew S. Baker (mbaker)

    Modified: 11/6/2002

******************************************************************************/
#pragma once
#include "stdinc.h"

HRESULT ExtractPicsFromBody(LPTSTR pszBody, UINT* puNumPics, LPEMSPICINFO* ppEMSPics);
HRESULT ConvertToMonoBitmap(UINT uNumPics, LPEMSPICINFO* ppEMSPics, LPBITMAP pBitmap);

/******************************************************************************

    CFormProvider - IFormProviderEx implementation

******************************************************************************/
class CFormProvider : public IFormProviderEx
{
public:
    // Constructor and destructor
    CFormProvider();
    ~CFormProvider();

    // IFormProvider methods
    MAPIMETHOD(QueryInterface)(REFIID iid, void** ppvObject);
    MAPIMETHOD_(ULONG, AddRef)();
    MAPIMETHOD_(ULONG, Release)();

    MAPIMETHOD(GetMsgStatusIconIndex)(
            LPMAPIFOLDER    pfldr,          // Folder for message
            LPENTRYID       pid,            // Id of message
            ULONG           cbid,           // count of bytes for the id
            ULONG           ffFlags,        // Flags for the message
            ULONG           ffStatus,       // Status for the message
            LPCWSTR         pszMsgClass, 
            ULONG           cAttachments,
            ULONG*          pnIndex         // OUT: Index for the correct glyph
    );

    MAPIMETHOD(CreateComposeForm)(
            IMessageFormHostEx* pHost, 
            LPMESSAGE       pMsg,       // Object to compose
            FORMTYPE        eFormType,  // Reply, Reply All, Forward
            LPMESSAGE       pMsgBase,   // Message to prefill the form if necessary
            MESSAGEFIELDS*  pMsgFields, // message fields for the new message
            HWND            hwndForm,   // HWND of the form frame
            HWND*           phwndBody,  // HWND of the form-created body
            IMessageFormEx**  ppForm    // Form object
    );

    MAPIMETHOD(CreateReadForm)(
            IMessageFormHostEx* pHost,
            LPMESSAGE       pMsg,       // Object to read
            HWND            hwndForm,   // HWND of the form frame
            HWND*           phwndBody,  // HWND of the form-created body
            IMessageFormEx**  ppForm    // Form object
    );

    // Other public methods
    MAPIMETHOD(Init)(LPCWSTR pszMessageClass);

private:
    HRESULT CleanUpReadForm(VOID);

    static BOOL     m_fInitPropTags;
    static ULONG    m_tagSMSUnicode;

    ULONG           m_cRef;
    LPTSTR          m_pszMessageClass;
    ICEMAPISession* m_pSession;
    IMsgStore*      m_pMsgStore;
};