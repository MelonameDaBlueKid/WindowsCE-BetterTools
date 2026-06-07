//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.
//
#include "stdafx.h"
#include "PIEHelper.h"
#include "PIEHlprObj.h"


const TCHAR * const pszAppName = TEXT("PIEHelper");

_ATL_FUNC_INFO CIEHlprObj::OnDocumentCompleteInfo   = {CC_STDCALL, VT_EMPTY, 2, {VT_DISPATCH, VT_BYREF|VT_VARIANT} };
_ATL_FUNC_INFO CIEHlprObj::OnTitleChangeInfo        = {CC_STDCALL, VT_EMPTY, 1, {VT_BSTR} };
_ATL_FUNC_INFO CIEHlprObj::OnBeforeNavigate2Info    = {CC_STDCALL, VT_EMPTY, 7, {VT_DISPATCH, VT_BYREF|VT_VARIANT, VT_BYREF|VT_VARIANT, VT_BYREF|VT_VARIANT, VT_BYREF|VT_VARIANT, VT_BYREF|VT_VARIANT, VT_BYREF|VT_BOOL} };
_ATL_FUNC_INFO CIEHlprObj::OnNavigateComplete2Info  = {CC_STDCALL, VT_EMPTY, 2, {VT_DISPATCH, VT_BYREF|VT_VARIANT} };

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
      ATLTRACE(TEXT("SetSite(): pUnkSite is NULL\r\n"));
   else
   {
      // Query pUnkSite for the IWebBrowser2 interface.
      m_spWebBrowser2 = pUnkSite;

      if (m_spWebBrowser2 != NULL)
      {
         // Create the events dialog box
         m_dlgEvents.Create(::GetDesktopWindow());
         m_dlgEvents.ShowWindow(SW_SHOWNORMAL);

         // Connect to the browser in order to handle events.
         if (FAILED(DispEventAdvise(pUnkSite)))
         {
            ATLTRACE(TEXT("\n%s: SetSite(): Failed to Advise\n\n"), pszAppName);
            ::MessageBox(   NULL,
                            _T("Failure sinking events from IWebBrowser2"),
                            pszAppName,
                            MB_OK);
        }
      }
   }

   return S_OK;
}

void __stdcall CIEHlprObj::OnDocumentComplete(IDispatch * pDisp, VARIANT * pvtURL)
{
    CComBSTR strEventInfo;
    strEventInfo += TEXT("DocumentComplete: ");
    strEventInfo += V_BSTR(pvtURL);
    m_dlgEvents.AddEventToList(strEventInfo);
}

void __stdcall CIEHlprObj::OnTitleChange(BSTR bstrTitleText)
{
    CComBSTR strEventInfo;
    strEventInfo += TEXT("TitleChange: ");
    strEventInfo += bstrTitleText;
    m_dlgEvents.AddEventToList(strEventInfo);
}

void __stdcall CIEHlprObj::OnBeforeNavigate2(IDispatch* pDisp,
                                    VARIANT * URL, 
                                    VARIANT * pvtFlags, 
                                    VARIANT * pvtTargetFrameName, 
                                    VARIANT * pvtPostData, 
                                    VARIANT * pvtHeaders,
                                    VARIANT_BOOL * pvbCancel)
{
    CComBSTR strEventInfo;
    strEventInfo += TEXT("BeforeNavigate: ");
    strEventInfo += V_BSTR(URL);
    m_dlgEvents.AddEventToList(strEventInfo);
}

void __stdcall CIEHlprObj::OnNavigateComplete2(IDispatch * pDisp, VARIANT * pvtURL)
{
    CComBSTR strEventInfo;
    strEventInfo += TEXT("NavigateComplete: ");
    strEventInfo += V_BSTR(pvtURL);
    m_dlgEvents.AddEventToList(strEventInfo);
}

