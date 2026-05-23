// DeferredInstaller.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//***************************************************************************
// Function Name: GetCurrentDeviceID
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
HRESULT GetCurrentDeviceID(DWORD * pdwCurrDeviceID)
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

	*pdwCurrDeviceID = _tcstoul(szLastDevice, &pszEnd, 16);

Error:
	if (hDevice)
		CeSvcClose(hDevice);

	return hr;
}


//***************************************************************************
// Function Name: GetCurrentDeviceString
//
// Purpose: This function retrieves the value of a given profile key, for the
//			currently cradled or selected device
//
// Arguments:
//  IN LPCTSTR pszValueName - Name of the profile key whose value is to be
//							  retrieved
//  OUT LPTSTR pszProfileValue - Value of the given key name in the currently
//								 selected/cradled device's profile
//
// Return Value:
//  HRESULT return code
//***************************************************************************
HRESULT GetCurrentDeviceString(LPCTSTR pszValueName, LPTSTR pszProfileValue)
{
	HRESULT hr = S_OK;
	HCESVC hDevice = NULL;
	DWORD dwDeviceId = 0;
	TCHAR szDeviceString[MAX_PROFILE_ENTRY_LEN] = {0};

	if (!pszProfileValue)
	{
		CHR(E_POINTER);
	}

	hr = GetCurrentDeviceID(&dwDeviceId);
	CHR(hr); 

	hr = CeSvcOpen(CESVC_DEVICEX, (LPTSTR)dwDeviceId, FALSE, &hDevice);
	CHR(hr); 

	hr = CeSvcGetString(hDevice, pszValueName, szDeviceString, MAX_PROFILE_ENTRY_LEN);
	CHR(hr);

	lstrcpy(pszProfileValue, szDeviceString);

Error:
	if (hDevice)
		CeSvcClose(hDevice);

	return hr;
}

//***************************************************************************
// Function Name: GetCurrentDeviceType
//
// Purpose: This function retrieves the Device Type of the currently cradled 
//			or selected device
//
// Arguments:
//  OUT LPTSTR pszCurrDeviceType - Device type of the currently selected or
//								   cradled device.
//
// Return Value:
//  HRESULT return code
//***************************************************************************
HRESULT GetCurrentDeviceType(LPTSTR pszCurrDeviceType)
{
	return GetCurrentDeviceString(_T("DeviceType"), pszCurrDeviceType);
}


//***************************************************************************
// Function Name: GetCurrentDeviceName
//
// Purpose: This function retrieves the Device Name of the currently cradled 
//			or selected device
//
// Arguments:
//  OUT LPTSTR pszDeviceName - Partnership name of the currently selected or
//							   cradled device.
//
// Return Value:
//  HRESULT return code
//***************************************************************************
HRESULT GetCurrentDeviceName(LPTSTR pszDeviceName)
{
	return GetCurrentDeviceString(_T("DisplayName"), pszDeviceName);
}


//***************************************************************************
// Function Name: CopyFileToDevice
//
// Purpose: This function copies a file from the desktop to the device
//
// Arguments:
//  IN LPTSTR szDesktopFileName - Name of the desktop file to download to device
//  IN LPTSTR szDeviceFileName - Filename to save the file as on the device
//
// Return Value:
//  HRESULT return code
//***************************************************************************
HRESULT CopyFileToDevice(LPTSTR szDesktopFileName, LPTSTR szDeviceFileName)
{
	HRESULT hr = S_OK;
	DWORD cbSize;
	PBYTE pbBuffer = NULL;
	WCHAR szwDeviceFileName[MAX_PATH] = {0};
	RAPIINIT ri = {0};
    ri.cbSize = sizeof(ri);
	INT iRetVal = 0;

	HANDLE hFile = NULL;
	hFile = CreateFile(szDesktopFileName,
						GENERIC_READ,
						0,
						NULL,
						OPEN_EXISTING,
						0,
						NULL);

	if (INVALID_HANDLE_VALUE == hFile || NULL == hFile)
	{
		CWR(0);
	}

	cbSize = GetFileSize(hFile, NULL);
	pbBuffer = (PBYTE) new BYTE[cbSize];
	if (pbBuffer == NULL)
	{
		hr = E_OUTOFMEMORY;
		CHR(hr);
	}

	DWORD dwRead = 0;
	if (!ReadFile(hFile, pbBuffer, cbSize, &dwRead, NULL))
	{
		CWR(0);
	}
	CloseHandle(hFile);
	hFile = NULL;

	hr = CeRapiInitEx(&ri);
	CHR(hr);

    if (WaitForSingleObject(ri.heRapiInit, 1000) != WAIT_OBJECT_0)
    {
		hr = E_FAIL;
		CHR(hr);
    }

	iRetVal = MultiByteToWideChar(CP_ACP,
							0, 
							szDeviceFileName, 
							-1, 
							szwDeviceFileName, 
							MAX_PATH);
	CWR(iRetVal);

	HANDLE hDevFile = CeCreateFile(szwDeviceFileName, 
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
	if (hFile)
		CloseHandle(hFile);

	if (hDevFile)
		CeCloseHandle(hDevFile);

	CeRapiUninit();

	delete [] pbBuffer;
	return hr;
}


//***************************************************************************
// Function Name: InstallToCurrentDevice
//
// Purpose: This function copies a CPF file to the currently cradled device
//			and fires off its installation on the device
//
// Arguments:
//  IN LPTSTR pszCPFFileName - URL of the CPF file to download and install
//
// Return Value:
//  HRESULT return code
//***************************************************************************
HRESULT InstallToCurrentDevice(LPTSTR pszCPFFileName)
{
	HRESULT hr = S_OK;
	BOOL fResult = FALSE;
	BOOL fDevicePPC = FALSE;
	TCHAR szDeviceType[MAX_PROFILE_ENTRY_LEN] = {0};
	PROCESS_INFORMATION pi;
	TCHAR szCmdLine[MAX_PATH] = {0};
	WCHAR szwCmdLine[MAX_PATH] = {0};
	RAPIINIT ri = {0};
    ri.cbSize = sizeof(ri);
	INT iRetVal = 0;

	hr = CopyFileToDevice(pszCPFFileName, (LPTSTR)c_szDeviceFileName);
	CHR(hr);

	_stprintf(szCmdLine, 
				_T("%s %s"), 
				c_szDeviceFileName, 
				_T("/silent /confignotify /verifyconfig"));

	// CeCreateProcess takes in only WCHAR. So convert the command line to Unicode
	iRetVal = MultiByteToWideChar(CP_ACP,0, szCmdLine, -1, szwCmdLine, MAX_PATH);
	CWR(iRetVal);

	hr = CeRapiInitEx(&ri);
	CHR(hr);

    if (WaitForSingleObject(ri.heRapiInit, 1000) != WAIT_OBJECT_0)
    {
		hr = E_FAIL;
		CHR(hr);
    }
    
	hr = GetCurrentDeviceType(szDeviceType);
	CHR(hr);

	if ( 0 == _tcscmp(szDeviceType, c_szDeviceTypePPC))
		fDevicePPC = TRUE;

	fResult = CeCreateProcess( fDevicePPC ? c_szwPPCInstaller : c_szwSPInstaller,
								szwCmdLine, 
								NULL, 
								NULL,
								FALSE,
								0,
								NULL, 
								NULL, 
								NULL,
								&pi);
	CWR(fResult);

Error:
	
	CeRapiUninit();
	return hr;
}


//***************************************************************************
// Function Name: RemoveSelf
//
// Purpose: This function removes the registry entry that triggered ActiveSync
//			to call this module when a device was connected. It also deletes
//			the CPF file and tries to remove the temp directory
//
// Arguments:
//  IN LPTSTR pszCPFFileName - The CPF file to delete

//
// Return Value:
//  HRESULT return code
//***************************************************************************
HRESULT RemoveSelf(LPTSTR pszCPFFileName)
{
	HRESULT hr = S_OK;
	HCESVC hCeSvc = NULL;

	// First delete the CPF file
	if (!DeleteFile(pszCPFFileName))
	{
		hr = HRESULT_FROM_WIN32(GetLastError());
		CHR(hr);
	}

	// Strip off the file name and try to delete the temp directory that
	// was created. Failure of this step is not critical.
	if (PathRemoveFileSpec(pszCPFFileName))
	{
		RemoveDirectory(pszCPFFileName);
	}

	// Remove the registry key
	hr = CeSvcOpen(CESVC_ROOT_MACHINE, 
					_T("AutoStartOnConnect"), 
					FALSE, 
					&hCeSvc);
	CHR(hr);

	if (ERROR_SUCCESS != RegDeleteValue((HKEY)hCeSvc, 
									_T("MicrosoftDeferredInstallerSample")))
	{
		CWR(0);
	}

Error:
	if (hCeSvc)
		CeSvcClose(hCeSvc);
	return hr;
}


//***************************************************************************
// Function Name: ConvertCHARToWCHAR
//
// Purpose: This function converts an ANSI string into a UNICODE string. Space
//			for the Unicode string is allocated in this function and should
//			be freed by the caller.
//
// Arguments:
//  IN LPSTR pszChar - ANSI string to convert
//  OUT LPWSTR* ppszwChar - Pointer to the converted Unicode string
//
// Return Value:
//  HRESULT return code
//***************************************************************************
HRESULT ConvertCHARToWCHAR(LPSTR pszChar, LPWSTR *ppszwChar)
{
	HRESULT hr = S_OK;
	INT iRetVal = 0;

	iRetVal = MultiByteToWideChar(CP_ACP,
									0,
									pszChar,
									-1,
									NULL,
									0);
	CWR(iRetVal);
	
	*ppszwChar = (LPWSTR) new WCHAR[iRetVal]; // iRetVal includes Null.
	CPR(*ppszwChar);

	iRetVal = MultiByteToWideChar(CP_ACP,
									0,
									pszChar,
									-1,
									*ppszwChar,
									iRetVal);
	CWR(iRetVal);

Error:
	return hr;
}


//***************************************************************************
// Function Name: ConvertWCHARToCHAR
//
// Purpose: This function converts an UNICODE string into a ANSI string. Space
//			for the ANSI string is allocated in this function and should
//			be freed by the caller.
//
// Arguments:
//  IN LPWSTR pszwChar - Unicode string to convert
//  OUT LPSTR* ppszChar - Pointer to the converted ANSI string
//
// Return Value:
//  HRESULT return code
//***************************************************************************
HRESULT ConvertWCHARToCHAR(LPWSTR pszwChar, LPSTR *ppszChar)
{
	HRESULT hr = S_OK;
	INT iRetVal = 0;

	iRetVal = WideCharToMultiByte(CP_ACP,
									0,
									pszwChar,
									-1,
									NULL,
									0,
									NULL,
									NULL);
	CWR(iRetVal);
	
	*ppszChar = (LPSTR) new BYTE[iRetVal]; // iRetVal includes Null.
	CPR(*ppszChar);

	iRetVal = WideCharToMultiByte(CP_ACP,
									0,
									pszwChar,
									-1,
									*ppszChar,
									iRetVal,
									NULL,
									NULL);
	CWR(iRetVal);

Error:
	return hr;
}


//***************************************************************************
// Function Name: ProcessCommandLine
//
// Purpose: This function takes in the concatenated command line (as received 
//			from WinMain) and extracts the two individual expected arguments.
//
// Arguments:
//  IN LPTSTR pszCmdLine - The concatenated command line
//  OUT LPTSTR szArg1 - Buffer for the first argument
//	IN DWORD dwArg1BuffLength - Length of the szArg1 buffer
//  OUT LPTSTR szArg2 - Buffer for the second argument
//	IN DWORD dwArg2BuffLength - Length of the szArg2 buffer
//
// Return Value:
//  DWORD - number of arguments parsed
//***************************************************************************
DWORD ProcessCommandLine(LPTSTR pszCmdLine, 
						 LPTSTR szArg1,
						 DWORD dwArg1BuffLength,
						 LPTSTR szArg2,
						 DWORD dwArg2BuffLength)
{
	HRESULT hr = S_OK;
	LPWSTR *ppszwArgv = NULL;
	LPWSTR pszwCmdLine = NULL;
	LPSTR pszConvertedArg1 = NULL;
	LPSTR pszConvertedArg2 = NULL;
	INT iNumArgs = 0;

	if (!*pszCmdLine)
	{
		CHR(E_FAIL);
	}

	hr = ConvertCHARToWCHAR(pszCmdLine, &pszwCmdLine);
	CHR(hr);

	ppszwArgv = CommandLineToArgvW(pszwCmdLine, &iNumArgs);
	if (!ppszwArgv || iNumArgs < 2)
	{
		CHR(E_FAIL);
	}

	hr = ConvertWCHARToCHAR(ppszwArgv[0], &pszConvertedArg1);
	CHR(hr);

	hr = ConvertWCHARToCHAR(ppszwArgv[1], &pszConvertedArg2);
	CHR(hr);

	strncpy(szArg1, pszConvertedArg1, dwArg1BuffLength);
	strncpy(szArg2, pszConvertedArg2, dwArg2BuffLength);

Error:
	delete [] pszConvertedArg1;
	delete [] pszConvertedArg2;
	delete [] pszwCmdLine;
	
	if (SUCCEEDED(hr))
		return iNumArgs;
	else
		return 0;
}


int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	HRESULT hr = S_OK;
	TCHAR szCmdLineDeviceName[MAX_PROFILE_ENTRY_LEN] = {0};
	TCHAR szDeviceName[MAX_PROFILE_ENTRY_LEN] = {0};
	TCHAR szCPFFileName[MAX_PATH] = {0};
	LPTSTR pszTemp = NULL;
	DWORD dwNumArgs;

	dwNumArgs = ProcessCommandLine(lpCmdLine, 
								szCPFFileName,
								MAX_PATH,
								szCmdLineDeviceName,
								MAX_PROFILE_ENTRY_LEN);
	
	// Fail if we got less than the expected number of arguments
	if (dwNumArgs < 2)
	{
		MessageBox(NULL, 
					_T("Incorrect command line arguments"), 
					_T("ActiveSync Deferred (CPF) Installer"), 
					MB_OK);
		goto Error;
	}

	// Get the currently connected device name and check if that 
	// is the device name passed in the command line
	hr = GetCurrentDeviceName(szDeviceName);
	CHR(hr);

	if (0 == _tcscmp(szCmdLineDeviceName, szDeviceName))
	{
		// Install only if the device names match
		hr = InstallToCurrentDevice(szCPFFileName);
		if (FAILED(hr))
		{
			MessageBox(NULL, 
						_T("Provisioning file could not be sent to device."), 
						_T("ActiveSync Deferred (CPF) Installer"), 
						MB_OK);
			goto Error;
		}

		MessageBox(NULL, 
		_T("Provisioning file successfully sent to device. Check Device Inbox to see further results"), 
		_T("ActiveSync Deferred (CPF) Installer"), MB_OK);

		// Since the install was successful, remove the registry entry 
		// that invoked this program and delete the CPF file.
		hr = RemoveSelf(szCPFFileName);
		CHR(hr);
	}

Error:
	if (FAILED(hr))
	{
		TCHAR szMsg[256] = {0};
		_stprintf(szMsg, _T("Error: hr = 0x%08x"), hr);
		MessageBox(NULL, szMsg, _T("ActiveSync Deferred (CPF) Installer"), MB_OK);
	}
	return 0;
}

