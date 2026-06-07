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

#include "enroll.h"
#include "password_history.h"
#include "ar_support.h"
#include "authreset.h"
#include "scope_guard.h"
#include "resource.h"

extern HANDLE           g_hAuthResetThread;
extern CRITICAL_SECTION g_csAuthResetSetup;

namespace
{
//  various internal implementation functions and classes are in the anonymous namespace

    //  Password saver class.
    //  Provides a callback method that allows saving the new password in place of the old one.
    //  The actual password change is defered untill the ARC call to ARCRequest succeeds.
    //
    class AuthResetPasswordSaver : public PasswordSaveCallback
    {
    public:
        virtual void operator()(HWND wnd, PASSWDINFO const & oldPasswd, PASSWDINFO const & newPasswd)
        {
            // just store values, we'll save the new password later
            m_oldPasswd = oldPasswd;
            m_newPasswd = newPasswd;
        }

        HRESULT Save(HWND wnd)
        {
            // Save settings to registry.
            HRESULT hr = SavePasswordInfo(&m_newPasswd);
            if(SUCCEEDED(hr))
            {
                // We successfully enrolled so save a copy 
                // of the policy settings now.
                SaveLKGPolicy(&m_oldPasswd.Policy);

                // Reset the update flag because we've enrolled.
                g_fPolicyRequiresUpdate = FALSE;

                // Save the old password to password history store
                AddPasswordToHistory(&m_newPasswd);

                // Set the return value.
                SetWindowLong(wnd, DWL_MSGRESULT, TRUE);

                return S_OK;
            }
            else
            {
                // An error occurred while saving.
                DisplayMessage(wnd, IDS_ERROR_TITLE, IDS_ERROR_SAVE);

                // Allow the user to exit on error
                // even if we're in secure mode.
                SetWindowLong(wnd, DWL_MSGRESULT, TRUE);

                return hr;
            }
        }

    private:
        PASSWDINFO m_oldPasswd;
        PASSWDINFO m_newPasswd;
    };

    //  EnrollmentDlgHandler class provides a callback
    //  that shows the password enrollment dialog.
    //  It uses AuthResetPasswordSaver to store the password entered by the user.
    //
    class EnrollmentDlgHandler : public function1<void>
    {
    public:
        EnrollmentDlgHandler(HWND parent)
            : m_parent(parent)
        {}

        virtual void operator()()
        {
            WndManager().Reserve(LAP_WINDOW_ENROLL);
            DoEnrollment(m_parent, FALSE, m_passwdSaver);
            WndManager().Clear(LAP_WINDOW_ENROLL);
        }

        AuthResetPasswordSaver & PasswordSaver()
        {
            return m_passwdSaver;
        }

    private:
        HWND m_parent;
        AuthResetPasswordSaver m_passwdSaver;
    };


    //  Checks the existance of a registry value
    // 
    bool RegValueExists(HKEY key, LPCTSTR valName)
    {
        DWORD size = 0;
        long er = RegQueryValueEx(key, valName, NULL, NULL, NULL, &size);

        return er == ERROR_SUCCESS;
    }

    //  Read a string value from the registry.
    //  Return value is valVal.  It's null terminated.
    //  The caller is responsible for freeing it with LocalFree.
    //
    HRESULT RegReadStringValue(HKEY key, LPCTSTR valName, /*out*/ TCHAR ** valVal)
    {
        DWORD size = 0;
        DWORD type = 0;
        long er = RegQueryValueEx(key, valName, NULL, &type, NULL, &size);

        if (er != ERROR_SUCCESS)
        {
            return HResultFromWin32(GetLastError());
        }
        if (type != REG_SZ)
        {
            return E_FAIL;
        }

        BYTE * retVal = new (localalloc) BYTE[size];
        if (!retVal) return E_OUTOFMEMORY;
        ScopeGuard retValSc = ScopeProtect(retVal, LocalFree);

        er = RegQueryValueEx(key, valName, NULL, &type, retVal, &size);
        if (er != ERROR_SUCCESS)
        {
            return HResultFromWin32(GetLastError());
        }
        if (type != REG_SZ)
        {
            return E_FAIL;
        }

        *valVal = reinterpret_cast<TCHAR *>(retVal);
        retValSc.release();
        return S_OK;
    }

    //  Read a binary value from the registry.
    //  Return values are blob and blobSize. The caller is responsible for freeing blob with LocalFree.
    //
    HRESULT ReagReadBinaryValue(HKEY key, LPCTSTR valName, /*out*/ BYTE ** blob, /*out*/ size_t * blobSize)
    {
        DWORD size = 0;
        DWORD type = 0;
        long er = RegQueryValueEx(key, valName, NULL, &type, NULL, &size);

        if (er != ERROR_SUCCESS)
        {
            return HResultFromWin32(GetLastError());
        }
        if (type != REG_BINARY)
        {
            return E_FAIL;
        }

        BYTE * retVal = new (localalloc) BYTE[size];
        if (!retVal) return E_OUTOFMEMORY;
        ScopeGuard retValSc = ScopeProtect(retVal, LocalFree);

        er = RegQueryValueEx(key, valName, NULL, &type, retVal, &size);
        if (er != ERROR_SUCCESS)
        {
            return HResultFromWin32(GetLastError());
        }
        if (type != REG_BINARY)
        {
            return E_FAIL;
        }

        *blob = reinterpret_cast<BYTE *>(retVal);
        *blobSize = size;
        retValSc.release();
        return S_OK;
    }

    //  Checks if the authentication reset policy is enabled.
    //  If not return false.
    //
    bool CheckAuthResetPolicy()
    {
        HKEY arKey;
        long er = RegOpenKeyEx(HKEY_LOCAL_MACHINE, arc::AuthResetPolicyKey, 0, 0, &arKey);
        if (er != ERROR_SUCCESS)
            return false;

        ScopeGuard arKeySc = ScopeProtect(arKey, RegCloseKey);

        DWORD policyVal = 0;
        DWORD size = sizeof(policyVal);
        DWORD type = 0;
        er = RegQueryValueEx(arKey
                           , arc::AuthResetPolicyValue
                           , NULL
                           , &type
                           , reinterpret_cast<BYTE *>(&policyVal)
                           , &size);
        if (er != ERROR_SUCCESS || type != REG_DWORD)
        {
            return false;
        }

        return policyVal != 0;
    }

    //  Save authentication reset data.
    //  The data is saved in registry in binary format.
    //
    HRESULT SaveARData(arc::Data const & data)
    {
        BYTE * dataBlob;
        size_t dataSize;
        HRESULT hr = data.Serialize(dataBlob, dataSize);
        if (FAILED(hr)) return hr;

        ScopeGuard dataBlobSc = ScopeProtect(dataBlob, LocalFree);

        HKEY arKey;
        long er = RegOpenKeyEx(HKEY_LOCAL_MACHINE, arc::AuthResetKey, 0, 0, &arKey);
        if (er != ERROR_SUCCESS)
        {
            return HResultFromWin32(GetLastError());
        }

        ScopeGuard arKeySc = ScopeProtect(arKey, RegCloseKey);

        er = RegSetValueEx(arKey, arc::AuthResetDataValue, 0, REG_BINARY, dataBlob, dataSize);
        if (er != ERROR_SUCCESS)
        {
            return HResultFromWin32(GetLastError());
        }

        return S_OK;
    }

    //  Remove the saved authentication reset data.
    //
    HRESULT RemoveARData()
    {
        // open AuthReset key
        HKEY arKey;
        long er = RegOpenKeyEx(HKEY_LOCAL_MACHINE, arc::AuthResetKey, 0, 0, &arKey);
        if (er != ERROR_SUCCESS)
        {
            return HResultFromWin32(GetLastError());
        }

        ScopeGuard arKeySc = ScopeProtect(arKey, RegCloseKey);

        // delete the value containing AR data
        // it may return error, if the value doesn't exist, but it's fine
        RegDeleteValue(arKey, arc::AuthResetDataValue);

        return S_OK;
    }

    //  Displays the message with the result of the authentication reset operation.
    //
    HRESULT DisplaySetupStatus(HWND parent, HRESULT statusHR, LPCTSTR statusMessage)
    {
        //  LAP read success/failure message
        int statusId = FAILED(statusHR) ? IDS_AR_SETUP_FAILURE : IDS_AR_SETUP_SUCCESS;
        LPCTSTR statusStr = CELOADSZ(statusId);

        //  append ARC status message
        TCHAR * fullMessage;
        HRESULT hr = Concat(statusMessage, statusStr, &fullMessage);
        if (FAILED(hr)) return hr;
        ScopeGuard fullMessageSc = ScopeProtect(fullMessage, LocalFree);

        //  show to the user
        LPCTSTR caption = CELOADSZ(IDS_AR_CAPTION);
        DisplayMessage(parent, caption, fullMessage, 
            BUTTON_INFO_OK, NULL);

        return S_OK;
    }

    struct SetupARParams
    {
        LPCTSTR pszPasswd;      
        HANDLE  hEventDisplayed;
    };

    //  AR setup implementation details.
    //  This function works with the AR ResetWorker and saves AR data into the registry.
    //  This function is expected to be called as the starting address for a new thread.
    //
    DWORD SetupARImpl(LPVOID lpParameter)
    {
        LPTSTR pszStatus = NULL;
        ScopeGuard StatusSc= ScopeProtect(
            pszStatus, LocalFree);

        HANDLE heventMessageDisplayed = NULL;
        ScopeGuard EventSc = ScopeProtect(
            heventMessageDisplayed, CloseHandle);

        // Check for structure of input params.
        if(NULL == lpParameter)
        {
            // Can't continue without this parameter.
            return 0;
        }

        // Interpret the passed-in parameter as a pointer to 
        // a struct of params.
        SetupARParams* pParams = 
            static_cast<SetupARParams*>(lpParameter);
        
        // If an event handle was passed in, create a local copy.
        if(NULL != pParams->hEventDisplayed)
        {
            HANDLE hProcess = GetCurrentProcess();
            (void)DuplicateHandle(hProcess, pParams->hEventDisplayed,
                hProcess, &heventMessageDisplayed, 0, FALSE,
                DUPLICATE_SAME_ACCESS);
        }

        arc::ResetWorker resetWorker(NULL);
        arc::Data arcData;

        HRESULT hr = resetWorker.Setup(pParams->pszPasswd, 
            heventMessageDisplayed, arcData, &pszStatus);
        if (FAILED(hr)) return hr;

        hr = SaveARData(arcData);

        if(hr != E_ABORT)
        {
            //  display the status of the operation, unless it was cancelled by the user
            HRESULT hr1 = DisplaySetupStatus(NULL, hr, pszStatus);
            if (FAILED(hr1)) return hr1;
        }

        return hr;
    }

    //  Load AR data from the registry into a blob.
    //  The caller is responsible for releasing the blob with LocalFree.
    //
    HRESULT LoadARData(/*out*/ BYTE ** blob, /*out*/ size_t * blobSize)
    {
        // open AuthReset key
        HKEY arKey;
        long er = RegOpenKeyEx(HKEY_LOCAL_MACHINE, arc::AuthResetKey, 0, 0, &arKey);
        if (er != ERROR_SUCCESS)
        {
            return HResultFromWin32(GetLastError());
        }

        ScopeGuard arKeySc = ScopeProtect(arKey, RegCloseKey);

        // read Data reg value
        HRESULT hr = ReagReadBinaryValue(arKey, arc::AuthResetDataValue, blob, blobSize);
        if (FAILED(hr)) return hr;

        return S_OK;
    }

    //  AR request implementation details.
    //
    HRESULT RequestARImpl(HWND parent, /*out*/ TCHAR ** status)
    {
        // read AR data
        BYTE * blob;
        size_t blobSize;

        HRESULT hr = LoadARData(&blob, &blobSize);
        if (FAILED(hr)) return hr;

        ScopeGuard blobSc = ScopeProtect(blob, LocalFree);

        arc::Data data(blob, blobSize);
        arc::ResetWorker worker(parent);

        // request the authentication reset
        TCHAR * passwd;
        EnrollmentDlgHandler enroll(parent);
        hr = worker.Request(data, enroll, &passwd, status);
        if (FAILED(hr)) return hr;

        ScopeGuard passwdSc = ScopeProtect(passwd, LocalFree);

        // save the old password, so the new one can be set
        SavePasswordForEnrollment(passwd);

        // auth request succeeded, now we can store the new password
        hr = enroll.PasswordSaver().Save(parent);
        if (FAILED(hr)) return E_ABORT;

        // remove old AR data
        hr = RemoveARData();
        if (FAILED(hr)) return hr;

        return S_OK;
    }

    //  Displays the message with the result of the authentication reset operation.
    //
    HRESULT DisplayRequestStatus(HWND parent, HRESULT statusHR, LPCTSTR statusMessage)
    {
        //  LAP read success/failure message
        int statusId = FAILED(statusHR) ? IDS_AR_REQUEST_FAILURE : IDS_AR_REQUEST_SUCCESS;
        LPCTSTR statusStr = CELOADSZ(statusId);

        //  append ARC status message
        TCHAR * fullMessage;
        HRESULT hr = Concat(statusMessage, statusStr, &fullMessage);
        if (FAILED(hr)) return hr;
        ScopeGuard fullMessageSc = ScopeProtect(fullMessage, LocalFree);

        //  show to the user
        LPCTSTR caption = CELOADSZ(IDS_AR_CAPTION);
        DisplayMessage(parent, caption, fullMessage, 
            BUTTON_INFO_OK, NULL);

        return S_OK;
    }
}


//  Perform the authentication reset setup.
//  Returns after launching a separate thread to perform setup.
//  parent - the window that will be the parent for all dialogs displayed to the user
//           by this function
//  passwd - the password that will be protected by the ARC
//
HRESULT arc::SetupAR(HWND parent, LPCTSTR passwd)
{
    if (!CheckAuthResetPolicy())
    {
        return E_FAIL;
    }

    // We only want to run one instance of AuthReset setup at a time.
    // This critical section protects the g_hAuthResetThread variable.
    if(!TryEnterCriticalSection(&g_csAuthResetSetup))
    {
        return E_FAIL;
    }

    // Check if we have run this thread before.
    if(NULL != g_hAuthResetThread)
    {
        // Proceed only if the previous thread has exited.
        if(WAIT_OBJECT_0 != WaitForSingleObject(g_hAuthResetThread, 0))
        {
            // Exit because another instance is already running.
            LeaveCriticalSection(&g_csAuthResetSetup);
            return E_FAIL;
        }

        // Close previous thread handle.
        (void)CloseHandle(g_hAuthResetThread);
    }

    SetupARParams params;
    params.pszPasswd = passwd;            

    // Create an event that will be signaled when 
    // the AuthReset setup message is displayed.
    params.hEventDisplayed = CreateEvent(NULL, TRUE, FALSE, NULL);
    ScopeGuard EventSc = ScopeProtect(
        params.hEventDisplayed, CloseHandle);

    // Perform setup on a separate thread so we don't block.
    g_hAuthResetThread = CreateThread(NULL, 0, 
        SetupARImpl, &params, 0, NULL);

    // End critical section protecting the g_hAuthResetThread variable.
    LeaveCriticalSection(&g_csAuthResetSetup);

    // Wait for the event to be signaled so that we know the
    // message box has been displayed.
    // Only wait 1 second in case something goes wrong.
    (void)WaitForSingleObject(params.hEventDisplayed, 1000);

    return S_OK;
}

//  Check the state of the AR on the system.
//  The check is based on the AR data stored in the registry.
//  If there is AR data, then the AR has been setup and can be used to request
//  a password reset.  Otherwise, no AR has been setup and password reset throw AR
//  is unavailable.
//
HRESULT arc::CheckARState(arc::ARState & state)
{
    HKEY arKey;
    long er = RegOpenKeyEx(HKEY_LOCAL_MACHINE, arc::AuthResetKey, 0, 0, &arKey);
    if (er != ERROR_SUCCESS)
    {
        return HResultFromWin32(GetLastError());
    }

    ScopeGuard arKeySc = ScopeProtect(arKey, RegCloseKey);

    bool dataExists = RegValueExists(arKey, arc::AuthResetDataValue);
    state = dataExists ? arc::ENABLED : arc::DISABLED;

    return S_OK;
}

//  Perform the authentication setup request.
//  AR request retrives the old password from the ARC,
//  prompts the user for a new password, and changes the old password for a new one.
//
HRESULT arc::RequestAR(HWND parent)
{
    if (!CheckAuthResetPolicy())
    {
        return E_FAIL;
    }

    TCHAR * arStatus = NULL;
    HRESULT hr = RequestARImpl(parent, &arStatus);
    ScopeGuard arStatusSc = ScopeProtect(arStatus, LocalFree);

    if (hr != E_ABORT)
    {
        //  display the status of the operation, unless it was cancelled by the user
        HRESULT hr1 = DisplayRequestStatus(parent, hr, arStatus);
        if (FAILED(hr1)) return hr1;
    }

    return S_OK;
}
