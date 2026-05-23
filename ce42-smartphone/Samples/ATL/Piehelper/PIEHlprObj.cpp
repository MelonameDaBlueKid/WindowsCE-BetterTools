#include "stdafx.h"
#include "PIEHelper.h"
#include "PIEHlprObj.h"


const TCHAR * const pszAppName = TEXT("PIEHelper");

/////////////////////////////////////////////////////////////////////////////
// CIEHlprObj::ManageConnection
/////////////////////////////////////////////////////////////////////////////
BOOL CIEHlprObj::ManageConnection
(
    enum ConnectType eConnectType
)
{
   if (!m_spBrowser2)
      return S_OK;

   HRESULT hrResult;

   //
   // If eConnectType is Advise then we are advising IE that we
   // want to handle events.  If eConnectType is Unadvise, we are
   // telling IE that we no longer want to handle events.
   //
   CComQIPtr<IConnectionPointContainer,
             &IID_IConnectionPointContainer> spCPContainer(m_spBrowser2);

   if (spCPContainer != NULL)
   {
      CComPtr<IConnectionPoint> spConnectionPoint;

      if (SUCCEEDED(hrResult = spCPContainer->FindConnectionPoint(
                                        IID_IDispatch,
                                        &spConnectionPoint)))
      {
         if (eConnectType == Advise)
         {
            //
            // Advise the client site of our desire to be handle events
            //
            if (FAILED(hrResult = spConnectionPoint->Advise((IDispatch*)this,
                                                            &m_dwCookie)))
            {
               ATLTRACE("\n%s: ManageConnection(): Failed to Advise\n\n", pszAppName);
            }
         }
         else
         {
            // Remove us from the list of people interested...
            if (FAILED(hrResult = spConnectionPoint->Unadvise(m_dwCookie)))
               ATLTRACE("\npszAppName: ManageConnection(): Failed to Unadvise\n\n", pszAppName);
         }
      }
   }

   return SUCCEEDED(hrResult);
}

/////////////////////////////////////////////////////////////////////////////
// IOleObjectWithSite
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// IOleObjectWithSite::SetSite
/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CIEHlprObj::SetSite
(
    IUnknown * pUnkSite
)
{
   USES_CONVERSION;

   if (pUnkSite == NULL)
      ATLTRACE("SetSite(): pUnkSite is NULL\r\n");
   else
   {
      // Query pUnkSite for the IWebBrowser2 interface.
      m_spBrowser2 = pUnkSite;

      if (m_spBrowser2 != NULL)
      {
         // Create the events dialog box
         m_dlgEvents.Create(::GetDesktopWindow());
         m_dlgEvents.ShowWindow(SW_SHOWNORMAL);

         // Connect to the browser in order to handle events.
         if (!ManageConnection(Advise))
         {
            ::MessageBox(   NULL,
                            _T("Failure sinking events from IWebBrowser2"),
                            pszAppName,
                            MB_OK);
        }
      }
   }

   return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IDispatch
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// IDispatch::Invoke
/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CIEHlprObj::Invoke
(
    DISPID          dispidMember,
    REFIID          riid,
    LCID            lcid,
    WORD            wFlags,
    DISPPARAMS *    pDispParams,
    VARIANT *       pvarResult,
    EXCEPINFO *     pExcepInfo,
    UINT *          puArgErr
)
{
   CComBSTR strEventInfo;

    switch (dispidMember)
    {
        case DISPID_DOCUMENTCOMPLETE:
        {
            // The parameters for this DISPID are as follows:
            //
            // [0]: URL navigated to - VT_BSTR
            // [1]: An error occurred during download - VT_BOOL
 
            strEventInfo += TEXT("DocumentComplete: ");

            if (V_BOOL(&(pDispParams->rgvarg[1])) == VARIANT_TRUE)
                strEventInfo += TEXT("Error");
            else
                strEventInfo += V_BSTR(&(pDispParams->rgvarg[0]));

            break;
        }

        case DISPID_TITLECHANGE:
        {
            // The parameters for this DISPID are as follows:
            //
            // [0]: The title - VT_BSTR

            strEventInfo += TEXT("TitleChange: ");
            strEventInfo += V_BSTR(&(pDispParams->rgvarg[0]));
            break;
        }

        case DISPID_BEFORENAVIGATE:
        {
            // The parameters for this DISPID are as follows:
            //
            // [0]: Cancel flag  - VT_BYREF | VT_I4
            // [1]: HTTP headers - VT_BSTR
            // [2]: Address of HTTP POST data  - VT_BSTR 
            // [3]: Target frame name - VT_BSTR 
            // [4]: Option flags - VT_I4
            // [5]: URL to navigate to - VT_BSTR

            strEventInfo += TEXT("BeforeNavigate: ");
            strEventInfo += V_BSTR(&(pDispParams->rgvarg[5]));
            break;
        }

        case DISPID_NAVIGATECOMPLETE:
        {
            // The parameters for this DISPID are as follows:
            //
            // [0]: URL navigated to - VT_BSTR

            strEventInfo += TEXT("NavigateComplete: ");
            strEventInfo += V_BSTR(&(pDispParams->rgvarg[0]));
            break;
        }

        default:
        {
            strEventInfo += TEXT("Unknown message");
            break;
        }
    }

    m_dlgEvents.AddEventToList(strEventInfo);

    return S_OK;
}
