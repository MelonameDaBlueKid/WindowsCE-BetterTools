// CPFInstaller.cpp : Implementation of CCPFInstaller
#include "stdafx.h"
#include "rapi.h"
#include "ceutil.h"
#include <urlmon.h>
#include "CPFInstaller.h"


//***************************************************************************
// Function Name: InitProfiles
// Function Type: ActiveX control Method
//
// Purpose: This function initializes a cached list of ActiveSync partnership 
//			profiles and returns the number of profiles
//
// Arguments:
//  OUT  LONG* dwProfileCount - Number of ActiveSync partnership profiles
//
// Return Value:
//  HRESULT return code
//***************************************************************************
STDMETHODIMP CCPFInstaller::InitProfiles(LONG* dwProfileCount)
{
	HRESULT hr = S_OK;
	HCESVC hCeSvc = NULL;
	HCESVC hDevice = NULL;
	DWORD dwProfile = 0;
	DWORD dwProfIndex = 0;

	// First get the count of profiles
	while ( SUCCEEDED(CeSvcEnumProfiles(&hCeSvc, dwProfIndex++, &dwProfile)));

	// dwProfIndex will have the count now.
	m_dwNumProfiles = dwProfIndex-1;

	// Allocate storage for caching the profile information
	m_pProfiles = (PROFILEENTRY *) new PROFILEENTRY[m_dwNumProfiles];
	CPR(m_pProfiles);
	
	// Loop through each profile, retrieve the information we want and 
	// store it in the local cache
	dwProfIndex = 0;
	hCeSvc = NULL;
	while ( SUCCEEDED(CeSvcEnumProfiles(&hCeSvc, dwProfIndex, &dwProfile)))
	{
		if ((DWORD)-1 == dwProfile || (WORD)-1 == dwProfile)
		{
			continue;
		}

		if (SUCCEEDED(CeSvcOpen(CESVC_DEVICEX, 
								(LPTSTR)dwProfile, 
								FALSE, 
								&hDevice)))
		{
			hr = CeSvcGetString(hDevice, 
								_T("DisplayName"), 
								m_pProfiles[dwProfIndex].szProfileName, 
								MAX_PROFILE_ENTRY_LEN);
			CHR(hr);

			hr = CeSvcGetString(hDevice, 
								_T("DeviceType"), 
								m_pProfiles[dwProfIndex].szDeviceType, 
								MAX_PROFILE_ENTRY_LEN);
			CHR(hr);

			CeSvcClose(hDevice);
			hDevice = NULL;
		}
		dwProfIndex++;
	}

	// Return the profile count to the user
	*dwProfileCount = m_dwNumProfiles;
	m_fProfileInitd = TRUE;

Error:
	if (hDevice)
		CeSvcClose(hDevice);

	return hr;
}


//***************************************************************************
// Function Name: GetProfileString
// Function Type: ActiveX control Method
//
// Purpose: This function retrieves the value of a profile key, given the name
//			of the key and the index of the profile entry in the cached list.
//
// Arguments:
//  IN   LONG  dwProfileIndex    - Index of the profile entry
//  IN   BSTR  bstrValueName     - Name of the profile key whose value is to
//								   be retirieved
//  OUT  BSTR* pbstrProfileValue - Value of the prescribed profile key
//
// Return Value:
//  HRESULT return code
//***************************************************************************
STDMETHODIMP CCPFInstaller::GetProfileString(LONG dwProfileIndex, 
											 BSTR bstrValueName, 
											 BSTR* pbstrProfileValue)
{
	HRESULT hr = S_OK;
	USES_CONVERSION;

	// Check if the index passed in is within bounds
	if (!m_fProfileInitd || dwProfileIndex > m_dwNumProfiles || dwProfileIndex < 1)
		CHR(E_FAIL);

	if (!pbstrProfileValue)
		CHR(E_POINTER);

	*pbstrProfileValue = NULL;

	if (0 == _tcscmp(OLE2T(bstrValueName), _T("DisplayName")))
	{
		*pbstrProfileValue = SysAllocString(T2OLE(m_pProfiles[dwProfileIndex-1].szProfileName));
	}
	else if (0 == _tcscmp(OLE2T(bstrValueName), _T("DeviceType")))
	{
		*pbstrProfileValue = SysAllocString(T2OLE(m_pProfiles[dwProfileIndex-1].szDeviceType));
	}
	else
	{
		CHR(E_FAIL);
	}

Error:
	return hr;
}


//***************************************************************************
// Function Name: GetCurrentDeviceName
// Function Type: ActiveX control Method
//
// Purpose: This function returns the partnership name of the currently
//			connected/selected device.
//
// Arguments:
//  OUT  BSTR* pbstrDeviceName - Partnership name
//
// Return Value:
//  HRESULT return code
//***************************************************************************
STDMETHODIMP CCPFInstaller::GetCurrentDeviceName(BSTR* pbstrDeviceName)
{
	return GetCurrentDeviceString(_T("DisplayName"), pbstrDeviceName);
}


//***************************************************************************
// Function Name: IsDeviceConnected
// Function Type: ActiveX control Method
//
// Purpose: This function checks if a device is currently cradled or not
//
// Arguments:
//  OUT  VARIANT_BOOL* pfDeviceConnected - connection status returned
//
// Return Value:
//  HRESULT return code
//***************************************************************************
STDMETHODIMP CCPFInstaller::IsDeviceConnected(VARIANT_BOOL* pfDeviceConnected)
{
	HRESULT hr = S_OK;
	RAPIINIT ri = {0};
    ri.cbSize = sizeof(ri);
	USES_CONVERSION;

	hr = CeRapiInitEx(&ri);
	CHR(hr);

	// Wait for 1 second for the connection handle to be signalled
    if (WaitForSingleObject(ri.heRapiInit, 1000) != WAIT_OBJECT_0)
    {
		// No device is cradled. So return S_FALSE instead of E_FAIL
		// so that the caller can continue
		*pfDeviceConnected = VARIANT_FALSE;

		// Fire the appropriate StatusMessage ActiveX control Event
		Fire_StatusMessage(T2OLE(_T("No device connected.")));
        hr = S_FALSE;
    }
	else
	{
		// Fire the appropriate StatusMessage ActiveX control Event
		Fire_StatusMessage(T2OLE(_T("Connected to device.")));
		*pfDeviceConnected = VARIANT_TRUE;
	}

Error:
	CeRapiUninit();
	return hr;
}


//***************************************************************************
// Function Name: InstallToDevice
// Function Type: ActiveX control Method
//
// Purpose: This function saves a CPF file and the deferred installer EXE to a
//			temp location on the desktop for Deferred Install
//
// Arguments:
//  IN BSTR bstrServerCPFLocation - URL of the CPF file to download and install
//  IN BSTR bstrDeviceName - Partnership name of the device to install the CPF
//  OUT VARIANT_BOOL* pfSuccess - indicates whether the install was successful
//
// Return Value:
//  HRESULT return code
//***************************************************************************
STDMETHODIMP CCPFInstaller::InstallToDevice(BSTR bstrServerCPFLocation, 
											BSTR bstrDeviceName, 
											VARIANT_BOOL* pfSuccess)
{
	HRESULT hr = S_OK;
	TCHAR szLocalPath[MAX_PATH] = {0};
	TCHAR szRegEntryString[MAX_PATH*2] = {0};
	TCHAR szInstallerPath[MAX_PATH]= {0};
	BOOL fProfileNameFound = FALSE;
	HCESVC hCeSvc = NULL;

	USES_CONVERSION;

	*pfSuccess = VARIANT_FALSE;

	hr = CreateTempFolder(szLocalPath);
	CHR(hr);

	// Download the CPF file to desktop
	if( !PathAppend(szLocalPath, _T("DeviceConfig.cpf")))
	{
		CHR(E_FAIL);
	}

	hr = CopyFileServerToDesktop(OLE2T(bstrServerCPFLocation), 
								szLocalPath);
	CHR(hr);

	// Get the location of the deferred installer. This EXE would be installed
	// along with this control's DLL
	if (!GetModuleFileName((HINSTANCE)_AtlBaseModule.m_hInst, 
							szInstallerPath, 
							MAX_PATH))
	{
		CWR(0);
	}

	// strip the DLL's name off to get the path
	if (!PathRemoveFileSpec(szInstallerPath))
	{
		CHR(E_FAIL);
	}

	// Add the installer's name to the path
	if (!PathAppend(szInstallerPath, _T("DeferredInstaller.exe")))
	{
		CHR(E_FAIL);
	}

	// Create the registry entries to execute installer on next connect
	_tcscpy(szRegEntryString, _T("\""));
	_tcscat(szRegEntryString, szInstallerPath);
	_tcscat(szRegEntryString, _T("\" "));
	_tcscat(szRegEntryString, szLocalPath);
	_tcscat(szRegEntryString, " ");

	// In order to be safe, compare the device name passed in to this 
	// function to the list that has been cached
	for ( DWORD i=0; i<m_dwNumProfiles; i++)
	{
		if ( 0== _tcscmp(OLE2CT(bstrDeviceName), m_pProfiles[i].szProfileName))
		{
			_tcscat(szRegEntryString, m_pProfiles[i].szProfileName);
			fProfileNameFound = TRUE;
		}
	}

	if (!fProfileNameFound)
	{
		CHR(E_FAIL);
	}

	hr = CeSvcOpen(CESVC_ROOT_MACHINE, 
					_T("AutoStartOnConnect"), 
					FALSE, 
					&hCeSvc);
	CHR(hr);

	hr = CeSvcSetString(hCeSvc, 
						_T("MicrosoftDeferredInstallerSample"), 
						szRegEntryString);
	CHR(hr);

	Fire_StatusMessage(T2OLE(_T("CPF file successfully downloaded. It will be installed the next time device is connected.")));
	*pfSuccess = VARIANT_TRUE;

Error:
	if (hCeSvc)
		CeSvcClose(hCeSvc);
	return hr;
}


//***************************************************************************
// Function Name: InstallToCurrentDevice
// Function Type: ActiveX control Method
//
// Purpose: This function installs a CPF file to the currently cradled device
//
// Arguments:
//  IN BSTR bstrServerCPFLocation - URL of the CPF file to download and install
//  OUT VARIANT_BOOL* pfSuccess - indicates whether the install was successful
//
// Return Value:
//  HRESULT return code
//***************************************************************************
STDMETHODIMP CCPFInstaller::InstallToCurrentDevice(BSTR bstrServerCPFLocation, 
												   VARIANT_BOOL* pfSuccess)
{
	HRESULT hr = S_OK;
	BOOL fResult = FALSE;
	BOOL fDevicePPC = FALSE;
	BSTR bstrDeviceType = NULL;
	PROCESS_INFORMATION pi;
	TCHAR szCmdLine[MAX_PATH] = {0};
	RAPIINIT ri = {0};
    ri.cbSize = sizeof(ri);

	USES_CONVERSION;

	// First download the CPF file and copy it to the device
	hr = CopyFileServerToDevice(bstrServerCPFLocation, 
								T2OLE(c_szDeviceFileName));
	CHR(hr);

	_stprintf(szCmdLine, 
				_T("%s %s"), 
				c_szDeviceFileName, 
				_T("/silent /confignotify /verifyconfig"));

	// Initialize the RAPI connection
	hr = CeRapiInitEx(&ri);
	CHR(hr);

    if (WaitForSingleObject(ri.heRapiInit, 1000) != WAIT_OBJECT_0)
    {
		// if there is no RAPI connection, return failure
		hr = E_FAIL;
		CHR(hr);
    }
    
	hr = GetCurrentDeviceType(&bstrDeviceType);
	CHR(hr);

	if ( 0 == _tcscmp(OLE2CT(bstrDeviceType), c_szDeviceTypePPC))
		fDevicePPC = TRUE;

	fResult = CeCreateProcess( fDevicePPC ? T2CW(c_szPPCInstaller) : T2CW(c_szSPInstaller),
								T2CW(szCmdLine), 
								NULL, 
								NULL,
								FALSE,
								0,
								NULL, 
								NULL, 
								NULL,
								&pi);
	CWR(fResult);

	Fire_StatusMessage(T2OLE(_T("CPF file successfully installed to the cradled device.")));
	*pfSuccess = VARIANT_TRUE;

Error:
	CeRapiUninit();
	SysFreeString(bstrDeviceType);
	return hr;
}


//***************************************************************************
// Function Name: CopyFileServerToDevice
// Function Type: Private Helper function
//
// Purpose: This function downloads a file from the internet and saves it on
//			the device
//
// Arguments:
//  IN BSTR bstrServerFileName - URL of the file to download
//  IN BSTR bstrDeviceFileName - Filename to save the file as on the device
//
// Return Value:
//  HRESULT return code
//***************************************************************************
HRESULT CCPFInstaller::CopyFileServerToDevice(BSTR bstrServerFileName, 
											BSTR bstrDeviceFileName)
{
	HRESULT hr = S_OK;
	LPSTREAM pStream = NULL;
	STATSTG StreamInfo;
	DWORD cbSize;
	PBYTE pbBuffer = NULL;
	RAPIINIT ri = {0};
    ri.cbSize = sizeof(ri);
	USES_CONVERSION;

	// Get the file as an ISTREAM object
	hr = URLOpenBlockingStream( NULL,
								OLE2T(bstrServerFileName),
								&pStream,
								0,
								NULL);
	CHR(hr); 

	hr = pStream->Stat(&StreamInfo, STATFLAG_NONAME);
	CHR(hr);
	
	// Allocate a buffer large enough to copy all bytes from the stream
	cbSize = StreamInfo.cbSize.LowPart;
	pbBuffer = (PBYTE) new BYTE[cbSize];
	if (pbBuffer == NULL)
	{
		hr = E_OUTOFMEMORY;
		CHR(hr);
	}

	// Read from the stream into the local buffer
	DWORD dwRead = 0;
	hr = pStream->Read( (void *)pbBuffer, cbSize, &dwRead);
	CHR(hr);

	// Initialize RAPI connection
	hr = CeRapiInitEx(&ri);
	CHR(hr);

    if (WaitForSingleObject(ri.heRapiInit, 1000) != WAIT_OBJECT_0)
    {
		// If there is no RAPI connection, the file cannot be written
		// to the device. So return failure.
		hr = E_FAIL;
		CHR(hr);
    }

	HANDLE hDevFile = CeCreateFile(bstrDeviceFileName, 
									GENERIC_WRITE, 
									0, 
									NULL, 
									CREATE_NEW, 
									FILE_ATTRIBUTE_NORMAL, 
									NULL);
	if (INVALID_HANDLE_VALUE == hDevFile || NULL == hDevFile)
	{
		CWR(0);
	}

	if (!CeWriteFile(hDevFile, (LPCVOID)pbBuffer, cbSize, &dwRead, NULL))
	{
		CWR(0);
	}

Error:
	if (hDevFile)
		CeCloseHandle(hDevFile);

	CeRapiUninit();
	return hr;
}


//***************************************************************************
// Function Name: CopyFileServerToDesktop
// Function Type: Private Helper function
//
// Purpose: This function downloads a file from the internet and saves it on
//			the desktop
//
// Arguments:
//  IN LPTSTR szServerFileName - URL of the file to download
//  IN LPTSTR szDesktopFileName - Filename to save the file as on desktop
//
// Return Value:
//  HRESULT return code
//***************************************************************************
HRESULT CCPFInstaller::CopyFileServerToDesktop(LPTSTR szServerFileName, 
											 LPTSTR szDesktopFileName)
{
	return URLDownloadToFile( NULL,
							szServerFileName,
							szDesktopFileName,
							0,
							NULL);

}



//***************************************************************************
// Function Name: CreateTempFolder
// Function Type: Private Helper function
//
// Purpose: This function creates a temp sub-folder in user's temp directory
//
// Arguments:
//  OUT LPTSTR szFolderName - Contains the name of the newly created temp folder
//
// Return Value:
//  HRESULT return code
//***************************************************************************
HRESULT CCPFInstaller::CreateTempFolder(LPTSTR szFolderName)
{
	HRESULT hr = S_OK;
	TCHAR szTempPath[MAX_PATH] = {0};
    TCHAR szTempFileName[MAX_PATH] = {0};
    LPTSTR pszExt = NULL;

    if (!GetTempPath(MAX_PATH, szTempPath))
    {
        CWR(0);
    }

    if (!GetTempFileName(szTempPath, _T("ASAX"), 0, szTempFileName))
    {
        CWR(0);
    }

	// GetTempFileName actually creates the file. So delete it now
    DeleteFile(szTempFileName);

	// strip of the .tmp extension
	PathRemoveExtension(szTempFileName);

    if (!CreateDirectory(szTempFileName, NULL))
    {
        CWR(0);
    }

	// return the name of the newly created folder
    _tcscpy(szFolderName, szTempFileName);

Error:
	return hr;
}


//***************************************************************************
// Function Name: GetCurrentDeviceID
// Function Type: Private Helper function
//
// Purpose: This function retrieves the Device ID of the currently cradled or
//	        currently selected device (if not cradled)
//
// Arguments:
//  OUT DWORD* pdwCurrDeviceID - The retrieved Device ID
//
// Return Value:
//  HRESULT return code
//***************************************************************************
HRESULT CCPFInstaller::GetCurrentDeviceID(DWORD* pdwCurrDeviceID)
{
	HRESULT hr = S_OK;
	HCESVC hDevice = NULL;
	LPTSTR pszEnd = NULL;
	TCHAR szLastDevice[MAX_PROFILE_ENTRY_LEN] = {0};

	hr = CeSvcOpen(CESVC_ROOT_USER, NULL, FALSE, &hDevice);
	CHR(hr);

	hr = CeSvcGetString(hDevice, 
						_T("Last Device"), 
						szLastDevice, 
						MAX_PROFILE_ENTRY_LEN);
	CHR(hr);

	// The device ID is stored as a string in the registry. 
	// Convert it to DWORD and return
	*pdwCurrDeviceID = strtoul(szLastDevice, &pszEnd, 16);

Error:

	if (hDevice)
		CeSvcClose(hDevice);
	return hr;
}


//***************************************************************************
// Function Name: GetCurrentDeviceString
// Function Type: Private Helper function
//
// Purpose: This function creates a temp sub-folder in user's temp directory
//
// Arguments:
//  IN LPCTSTR pszValueName - Name of the profile key whose value is to be
//							  retrieved
//  OUT BSTR* pbstrProfileValue - Value of the given key name in the currently
//								  selected/cradled device's profile
//
// Return Value:
//  HRESULT return code
//***************************************************************************
HRESULT CCPFInstaller::GetCurrentDeviceString(LPCTSTR pszValueName, 
											BSTR* pbstrProfileValue)
{
	HRESULT hr = S_OK;
	HCESVC hDevice = NULL;
	DWORD dwDeviceId = 0;
	TCHAR szDeviceString[MAX_PROFILE_ENTRY_LEN] = {0};
	USES_CONVERSION;

	if (!pbstrProfileValue)
		CHR(E_POINTER);

	*pbstrProfileValue = NULL;

	hr = GetCurrentDeviceID(&dwDeviceId);
	CHR(hr); 

	hr = CeSvcOpen(CESVC_DEVICEX, (LPTSTR)dwDeviceId, FALSE, &hDevice);
	CHR(hr); 

	hr = CeSvcGetString(hDevice, pszValueName, szDeviceString, MAX_PROFILE_ENTRY_LEN);
	CHR(hr);

	*pbstrProfileValue = SysAllocString(T2OLE(szDeviceString));

Error:
	if (hDevice)
		CeSvcClose(hDevice);
	return hr;
}


//***************************************************************************
// Function Name: GetCurrentDeviceType
// Function Type: Private Helper function
//
// Purpose: This function creates a temp sub-folder in user's temp directory
//
// Arguments:
//  OUT BSTR* pbstrCurrDeviceType - Device type of the currently selected or
//									cradled device.
//
// Return Value:
//  HRESULT return code
//***************************************************************************
HRESULT CCPFInstaller::GetCurrentDeviceType(BSTR* pbstrCurrDeviceType)
{
	return GetCurrentDeviceString(_T("DeviceType"), pbstrCurrDeviceType);
}
