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
#include <windows.h>
#include <wincrypt.h>
#include <stdio.h>
#include <tchar.h>
#include "base64.h"
#include <string.h>
#include "wininet_bridge.h"
#include "enroll.h"

TCHAR tHoldPrintString[OUTPUT_MAX_LEN]; // Used when we're doing the output of one arg.
TCHAR tHoldForOuput[OUTPUT_MAX_LEN]; //Global Variable used for debugging.
PMessageBox lpMessageBox=0;            // Another global used for debugging.

#ifndef UNICODE
#error // We Don't do the imports of non unicode  wininet!!
// Can be fixed easily if needed.
#endif 

// From crypt_web.cpp
BOOL CreateKeyAndGetContext  (CRYPT_KEY_PROV_INFO *pKeyProvInfo, HCRYPTPROV*  phCryptProv) ;
BOOL GenerateCertRequest(HCRYPTPROV hCryptProv,CRYPT_KEY_PROV_INFO *pKeyProvInfo,char **pB64CertReq);
int  SendCertRequestToWebServer(TCHAR *gServer ,TCHAR *page, TCHAR *userName, TCHAR *password, char * B64CertReq);
DWORD Base64DecodeExA( IN CHAR const *pchIn, IN DWORD cchIn, OUT BYTE *pbOut, OUT DWORD *pcbOut, OUT DWORD *pchConsumed);
BOOL GetCertFromWebServer(TCHAR *Server, TCHAR *Page ,char **B64Cert);
BOOL AddCertToStore( char *Cert, CRYPT_KEY_PROV_INFO* pKeyProvInfo,TCHAR *CertStore,HCRYPTPROV phProvWithKey,BOOL bIsCertChain);
BOOL  SetOptions (TCHAR *PassedInFileName);
char*  BuildPutRequest(TCHAR *tCertAttribs,TCHAR *tCertTemplate,char *B64CertReq);
HINSTANCE SetupWinInet();





// Static Defaults used in SetOptions
static const TCHAR  defCertStore[] = _T("MY");   
static const TCHAR  defServer[] = _T("defserver"); 
static const TCHAR  defCertRequestPage[] = _T("/certsrv/certfnsh.asp"); 
static const TCHAR  defCertPickupTemplate[] = _T("/certsrv/certnew.cer?ReqId=%i&Enc=b64"); 
static const TCHAR  defCertPickupChainTemplate[] = _T("/certsrv/certnew.p7b?ReqId=%i&Enc=b64"); 
static const TCHAR  defUserName[] = _T(""); 
static const TCHAR  defPassword[] = _T(""); 
static const TCHAR  defCertAttribs[] = _T(""); 
static const TCHAR  defCertTemplate[] = _T("ClientAuth"); 


//
// Global Variables used for options, 
// Shared between DoEnroll and SetOptions.
//
#define MAX_SIZE 255
static CRYPT_KEY_PROV_INFO gKeyProvInfo;
static TCHAR  gCertStore[MAX_SIZE] ; 
static TCHAR  gServer[MAX_SIZE];
static TCHAR  gCertRequestPage[MAX_SIZE] ;
static TCHAR  gCertPickupTemplate[MAX_SIZE];
static TCHAR  gCertPickupChainTemplate[MAX_SIZE];
static TCHAR  gUserName[MAX_SIZE];
static TCHAR  gPassword[MAX_SIZE];
static TCHAR  gCertAttribs[MAX_SIZE];
static TCHAR  gDeprecated[MAX_SIZE]; //Used to store deprecated Values
static TCHAR  gCertTemplate[MAX_SIZE];
static DWORD  gCertPickupChain;

// Used when setting params from file.
// These are pointed to when data is needed for keyProvInfo string
// fields to point at.
static TCHAR  gKeyContainerName[MAX_SIZE] ; 
static TCHAR  gKeyProviderName[MAX_SIZE];

////////////////////////////////////////////////////////
// This main procedure does the enrollment.
// The only other thing that may need to be change is 
// the ParseWebPageToFindReqNo
///////////////////////////////////////////////////////
void DoEnroll()
{

	// Glue Variables.
	char* B64CertReq=0;
	char* PutRequest=0;
	char* B64Cert=0;
	BOOL bWorked=FALSE;
	int iReqNo = -1;
	HCRYPTPROV hCryptProv=0;
	TCHAR certPickupPage[MAX_PATH+1];
    certPickupPage[MAX_PATH]=0; // Terminate the string

	bWorked = 	CreateKeyAndGetContext(&gKeyProvInfo,&hCryptProv);
	if(!bWorked || !hCryptProv)
	{
	  OUTPUT("CreateKeyAndGetContext Failed\n");
	  goto done;
  }


	bWorked = GenerateCertRequest(hCryptProv,&gKeyProvInfo,&B64CertReq);

	if( !bWorked || !B64CertReq)
	{
	  OUTPUT("GenerateCertReq Failed\n");
	  goto done;
  }

	// We build the full put request here.
	PutRequest =  BuildPutRequest(gCertAttribs,gCertTemplate,B64CertReq);
	if (!PutRequest)
	{
	  OUTPUT("BuildPutRequest Failed\n");
	  goto done;
  }

	// Send the put request to the CertServer. It includes the cert and certattribs.
	iReqNo= SendCertRequestToWebServer(gServer,gCertRequestPage,gUserName,gPassword,PutRequest);
	if (iReqNo == -1)
	{
	  OUTPUT("SendCertRequestToWebServer Failed\n");
	  goto done;
  }


	// 4) Fill Template, depends on if we want the chain or the cert.
	if (gCertPickupChain)
	{
	  _sntprintf(certPickupPage,MAX_PATH,gCertPickupChainTemplate,iReqNo);
    }
	else
	{
	  _sntprintf(certPickupPage,MAX_PATH,gCertPickupTemplate,iReqNo);
    }

	bWorked = GetCertFromWebServer(gServer,certPickupPage,&B64Cert);
	if(!bWorked || !B64Cert) 
	{

	  OUTPUT("GetCertFromWebServer Failed\n");
	  goto done;
  }

	// Handles Both Chains and Certs
	// This also sets the smart card options
	// 
	bWorked = AddCertToStore(B64Cert,&gKeyProvInfo,gCertStore,hCryptProv,gCertPickupChain);

	if (!bWorked)
	{
	  OUTPUT("AddCertToStore Failed\n");
	  goto done;
  }

	OUTPUT("Cert Has Been Added Succesfully\n");
done:
	if (B64CertReq) free(B64CertReq);
	if (PutRequest) free(PutRequest);
	if (B64Cert) free(B64Cert);
	if (hCryptProv) CryptReleaseContext(hCryptProv,0);

}

//  Hex numbers start with 0x
//  Handy function.
//    If Line doesn't Starts with strToFind returns 0
//    If Line does Starts with strToFind 
//    {
//      cpy option to OptToSet and return OptToSet
//    }
//    
BOOL getInt(char *Line , char* strToFind ,DWORD *OptToSet) 
{
	int n = strlen(strToFind);

	// Not Found. return 0
	if (_strnicmp(Line,strToFind,n)) return 0;
	if (!OptToSet) 
	{
	  ASSERT(0);
	  return 0;
  }

	// Skip the option itself.
	Line+=n;

	// Lets use sscanf to read the input.
	// this will let us pick up hex numbers.
	int i = sscanf(Line,"0x%X",OptToSet);
	if (1 != i)  // sscanf failed.
	{
	  // Try scanf again with 0X
	  i = sscanf(Line,"0X%X",OptToSet);
	  if(1 != i ) 
	  {
		// The number should be base 10.
		*OptToSet = atoi(Line);
	}
  }
	return 1;
}
// 
//  Handy function.
//    If Line doesn't Starts with strToFind returns 0
//    If Line does Starts with strToFind an OptToSet 0 then return 1
//    If Line does Starts with strToFind an OptToSet valid then 
//    {
//      cpy option to OptToSet and return 1 
//    }
//    
BOOL  getString(char *Line , char* strToFind ,TCHAR *OptToSet) 
{
	int n = strlen(strToFind);

	// Not Found. return 0
	if (_strnicmp(Line,strToFind,n)) return 0;
	if (!OptToSet) return 1;

	// Skip the option itself.
	Line+=n;

	// End the line at first \r or \n
	int LineLen = strlen(Line);
	for(int i=0;i<LineLen;i++)
	{
	  if (Line[i] == '\r' || Line[i] == '\n') 
	  {
		Line[i] = 0;
		break;
	}
  }

	//XXX: Unicode TO FIX!!
	mbstowcs( OptToSet, Line, strlen(Line) + 1 );
	return 1;
}

#define MAX_OPTION_LINE 200
BOOL  SetOptions (TCHAR *PassedInFileName)
{
	TCHAR *tFileName ;

	///////////////////////////////
	// Set the default options.
	//////////////////////////////
	gKeyProvInfo.pwszContainerName = L"enroll"; 
	gKeyProvInfo.pwszProvName = 0; 
	gKeyProvInfo.dwProvType = PROV_RSA_FULL;
	gKeyProvInfo.dwFlags = 0; 
	gKeyProvInfo.cProvParam = 0;
	gKeyProvInfo.rgProvParam = NULL;
	gKeyProvInfo.dwKeySpec = AT_SIGNATURE; 

	gCertPickupChain=1; // By Default Pickup Cert Chain.
	_tcscpy(gCertStore,defCertStore);
	_tcscpy(gCertRequestPage,defCertRequestPage);
	_tcscpy(gCertPickupTemplate,defCertPickupTemplate);
	_tcscpy(gCertPickupChainTemplate,defCertPickupChainTemplate);
	_tcscpy(gUserName,defUserName);
	_tcscpy(gPassword,defPassword);
	_tcscpy(gCertAttribs,defCertAttribs);
	_tcscpy(gCertTemplate,defCertTemplate);


	if (PassedInFileName && _tcslen(PassedInFileName))  tFileName = PassedInFileName;
	else return TRUE;

	FILE* fOpt = _tfopen (tFileName,_T("r"));
	if(!fOpt)
	{
	  _tprintf(_T("Unable to open Option File[%s] -Fatal since Can't Get a Server\n"),tFileName);
	  return FALSE;
    }

	// While we have data.
	char MaxLine[MAX_OPTION_LINE];

    MaxLine[sizeof(MaxLine)-1]=0;// Null Terminate the buffer

	BOOL bServerFound=0; // Set to true when server field is set.

	while ( fgets (MaxLine,sizeof(MaxLine)-1,fOpt))
	{
        if (strlen(MaxLine) < 3) continue; // Skip Blanks
        if (getString(MaxLine,"//",0)) continue; // Skip comments
        else if (getString(MaxLine,"%",0)) continue; // Skip comments
        else if (getString(MaxLine,";",0)) continue; // Skip comments

        // Get the String Options.
        else if (getString(MaxLine,"USERNAME=",gUserName));
        else if (getString(MaxLine,"PASSWORD=",gPassword)) ;
        else if (getString(MaxLine,"CERT_STORE=",gCertStore));
        else if (getString(MaxLine,"SERVER=",gServer)) bServerFound=TRUE;
        else if (getString(MaxLine,"CERT_REQ_PAGE=",gCertRequestPage));
        else if (getString(MaxLine,"CERT_PICKUP_TEMPLATE=",gCertPickupTemplate));
        else if (getString(MaxLine,"CERT_PICKUP_CHAIN_TEMPLATE=",gCertPickupChainTemplate));
        else if (getString(MaxLine,"CERT_ATTRIBS=",gCertAttribs));
        else if (getString(MaxLine,"CERT_OTHER_ATTRIBS=",gDeprecated))
        {
            OUTPUT("CERT_OTHER_ATTRIBS has been deprecated\n");
            OUTPUT("Please update your .cfg file to use \n");
            OUTPUT("CERT_ATTRIBS and/or CERT_TEMPLATE instead\n");
        }
        else if (getString(MaxLine,"CERT_TEMPLATE=",gCertTemplate));

        else if (getString(MaxLine,"KEY_PROVIDER_NAME=",gKeyProviderName))
        {
            gKeyProvInfo.pwszProvName = gKeyProviderName; 
        }
        else if (getString(MaxLine,"KEY_CONTAINER_NAME=",gKeyContainerName))
        {
            gKeyProvInfo.pwszContainerName = gKeyContainerName; 
        }
        // Get the integer options.
        else if (getInt(MaxLine,"DW_KEY_SPEC=",&gKeyProvInfo.dwKeySpec));
        else if (getInt(MaxLine,"DW_PROV_TYPE=",&gKeyProvInfo.dwProvType));
        else if (getInt(MaxLine,"DW_FLAGS=",&gKeyProvInfo.dwFlags));
        else if (getInt(MaxLine,"CERT_CHAIN=",&gCertPickupChain));
        else
        {
            OUTPUT_1_ARG( "Unable to process line [%S]",MaxLine );
        }
    }

	if (!bServerFound) 
	{
	  OUTPUT( "SERVER not set in config file. This is a Fatal Error \n");
	  return FALSE;
    }
	fclose(fOpt);
	return TRUE;
}



/////////////////////
// Entry Point.
//////////////////
int WINAPI WinMain(
		HINSTANCE    hInstance, HINSTANCE hPrevInstance,
		TCHAR *pCmdLine, int    nShowCmd)
{

    // Try to get us a MsgBox pointer.
    HINSTANCE coreDll =  LoadLibrary(_T("COREDLL.DLL"));
    if (coreDll)
    {
        lpMessageBox = (PMessageBox ) GetProcAddress(coreDll,_T("MessageBoxW"));
    }
    // Must have Wininet
    HINSTANCE winInet =  SetupWinInet();
    if (!winInet)
    {
        OUTPUT("LoadLibrary failed to load WinInet");
        goto done;
    }

    if (!_tcsncicmp(pCmdLine,_T("-s"),2))
    {
        // Server Passed In.
        _tcsncpy(gServer,(pCmdLine+2),MAX_SIZE-1);
        if (!SetOptions(0)) goto done;
    }
    else if (!_tcsncicmp(pCmdLine,_T("-f"),2))
    {
        // FileName Passed in.
        if (!SetOptions((pCmdLine+2))) goto done;
    }
    else if (!_tcsncicmp(pCmdLine,_T("-d"),2))
    {
        // We're in diagnostics mode.
        OUTPUT("Entering Diagnostics Mode:\n");
        OUTPUT("Checking For NTLMSSP:\n");
        if (!(winInet = LoadLibrary(_T("ntlmssp.dll"))))
        {
            OUTPUT("ERROR nltmssp.dll not found.\n Check for SYSGEN_AUTH_NTLM\n");
        }
        else
        {
            OUTPUT("NTLMSSP found!\n");
            OUTPUT("Everything looks good.\n");
        }
        goto done;
    }
    else if (!_tcsncicmp(pCmdLine,_T(""),1))
    {
        TCHAR tExecPath[MAX_PATH+1];
        DWORD dwLen;

        tExecPath[MAX_PATH]=0;// Null terminate the string

        // If nothing passed in try to read <exename>.cfg in dir our exe lives in.
        // Usually this will be enroll.cfg

        // Grab the ModuleFileName , change .exe to .cfg
        dwLen = GetModuleFileName(
                0, // hModule 
                tExecPath,
                MAX_PATH
                );
        // Make Sure the . is in the right spot.
        if (dwLen && _T('.') == tExecPath[dwLen -4] )
        {
            // Replace exe with cfg
            _tcscpy(&tExecPath[dwLen-3],_T("cfg"));
        }
        else
        {
            if(!dwLen)
            {
                OUTPUT_1_ARG("GetModuleFileName Failed: 0x%x or ",GetLastError());
            }
            OUTPUT_1_ARG(". in wrong spot %s",tExecPath);
            _tcscpy(tExecPath,_T(""));
        }

        if (!SetOptions(tExecPath)) 
        {
            OUTPUT("Error Input must be -d , -sServerName , or -fFileName\n");
            goto done;
        }
    }
    else
    {
        // no setttings we understand and enroll.cfg not in current dir.
        OUTPUT_1_ARG("Error Input must be -d , -sServerName , or -fFileName\n[%s] - is not acceptable\n",pCmdLine);
        goto done;
    }

    DoEnroll();  

done:
    if (winInet) FreeLibrary(winInet);
    if (coreDll) FreeLibrary(coreDll);
    return 0;
}
