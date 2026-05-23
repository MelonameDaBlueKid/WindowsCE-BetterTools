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
//
// This file has all the crypto, and web related 
//  functions.
/////////////////////////////////////////////////

#include <windows.h>
#include <wincrypt.h>
#include <stdio.h>
#include <tchar.h>
#include "base64.h"
#include <string.h>
#include "wininet_bridge.h"
#include "enroll.h"

#define MY_ENCODING_TYPE  (PKCS_7_ASN_ENCODING | X509_ASN_ENCODING)
DWORD Base64DecodeExA( IN CHAR const *pchIn, IN DWORD cchIn, OUT BYTE *pbOut, OUT DWORD *pcbOut, OUT DWORD *pchConsumed);
//
// We'll Dynamically Link to WinInet
// 
PInternetOpen lpInternetOpen;
PInternetErrorDlg lpInternetErrorDlg;
PInternetConnect  lpInternetConnect;
PHttpOpenRequest lpHttpOpenRequest;
PHttpSendRequest lpHttpSendRequest;
PHttpQueryInfo lpHttpQueryInfo;
PInternetCloseHandle lpInternetCloseHandle;
PInternetReadFile lpInternetReadFile;
PInternetSetOption lpInternetSetOption;

// Returns the number of cert to read..
// WebPage Must be null terminiated.
// -1 if error.
//  Else cert number.
int ParseWebPageToFindReqNo(char *cWebPage )
{
	int RetValue = -1;

	//XXX: If certfnsh.asp changes need to change the following lines.

	// If this worked, we'll see a string like...
	char *pStartReq = strstr(cWebPage,"certnew.cer?"); 

	if (pStartReq) // Don't do unless we're found
	{
		// Search forward till the = and then walk till the & and keep the rest of the string.
		// then copy into tUrl;
		while(*pStartReq != '=') ++pStartReq; 

		char *tFindEndNum=++pStartReq; // Eat the = sign.

		while(*tFindEndNum !='&')++tFindEndNum;
		// Zero tFindEndNum
		*(tFindEndNum) = 0;

		RetValue = atoi(pStartReq);

	}
	else
	{

		OUTPUT_1_ARG( "Cert Denied! - Reason Unknown Webpage is:\n%S\n ",cWebPage) ;
	}
	return RetValue;
}

// Conversion need to write an URL.
// Returns lenght of Out.
int Base64ToURL(char *B64,DWORD dwB64Len,char *Out)
{
	char *Start=Out;
	for ( unsigned int i=0;i<dwB64Len;i++)
	{
		switch  (B64[i])
		{
			case '/':
				strncpy(Out,"%2F",3);
				Out+=3;
				break;
			case '+':
				strncpy(Out,"%2B",3);
				Out+=3;
				break;
			case '=':
				strncpy(Out,"%3D",3);
				Out+=3;
				break;
			default:
				*Out = B64[i];
				++Out;
				break;
		}
	}
	return Out-Start;
}


void HandleError(char *s)
{
	OUTPUT("An error occurred in running the program. \n");
	// s is ascii copy it over.
	OUTPUT_1_ARG( "%S\n",s) ;
	OUTPUT_1_ARG("Error number %x.\n", GetLastError());
	OUTPUT( "Program terminating. \n");
	return;
} // End of HandleError

BOOL SetSmartCardCert( HCRYPTPROV hProv, CRYPT_KEY_PROV_INFO *pKeyProvInfo,PCCERT_CONTEXT pCert)
{
	HCRYPTKEY hCurKey=0;
	BOOL ret=TRUE;
	int error;

	// 1 Get the user key
   if (!CryptGetUserKey(hProv, pKeyProvInfo->dwKeySpec, &hCurKey))
   {
	   ret=FALSE;
	   goto done;
   }
   
   // 2 set the certificate parameter.
   if (!CryptSetKeyParam(hCurKey,KP_CERTIFICATE,pCert->pbCertEncoded, 0))
   {

	   error = GetLastError();
	   if (error != NTE_BAD_TYPE) {
		   // If error is bad_type then we just can't set the property.
		   // Likely means our provider isn't a smart card.
		   // If there was another error, we should report it.
		   OUTPUT_1_ARG("CryptSetKeyParam Failed (0x80090020 usually means no room on card) 0x%x\n",error);
	   }
	   ret=FALSE;
	   goto done;
   }
done:
   if (hCurKey) CryptDestroyKey(hCurKey);
   return ret; 

}

BOOL AddCAandRootCertsToStores(PCCERT_CONTEXT  pClientCert, const HCERTSTORE hPKCS7ChainCertStore)
{

    HCERTSTORE hRootCertStore = 0; 
    HCERTSTORE hCACertStore=0; // For Intermediate Certs.
	BOOL ret = TRUE; // The return value.
	BOOL bSuccess;
    PCCERT_CHAIN_CONTEXT pCertChainContext=0;
    PCCERT_CONTEXT pRootCert=0; // Pointer To the Root CERT.
    PCERT_SIMPLE_CHAIN pChain=0;
    DWORD err,i,dwChainTrust,dwRootCertTrust,dwAllowErrors;

    ASSERT(pClientCert);
    ASSERT(hPKCS7ChainCertStore);

    // Open the CA And ROOT stores
    //////////////////////////////////////

	hRootCertStore = CertOpenStore(CERT_STORE_PROV_SYSTEM,0,0, CERT_SYSTEM_STORE_CURRENT_USER , TEXT("ROOT"));
    if (!hRootCertStore)
    {
		OUTPUT(" hRootCertStore = CertOpenStore Failed.  \n");
		ret = FALSE;
		goto done;

    }

	hCACertStore = CertOpenStore(CERT_STORE_PROV_SYSTEM,0,0, CERT_SYSTEM_STORE_CURRENT_USER , TEXT("CA"));
    if (!hCACertStore)
    {
		OUTPUT(" hCACertStore = CertOpenStore Failed. \n");
		ret = FALSE;
		goto done;

    }


    CERT_CHAIN_PARA ChainPara;
    ZeroMemory(&ChainPara, sizeof(ChainPara));
    ChainPara.cbSize = sizeof(ChainPara);

    bSuccess = CertGetCertificateChain(NULL, pClientCert, NULL, hPKCS7ChainCertStore, &ChainPara, 0, NULL, &pCertChainContext);
	if (!bSuccess )
	{
		OUTPUT("CertGetCertificateChain Failed. \n");
		ret = FALSE;
		goto done;
	}

    /*///////////////////////////////////////
      Certificate Chain is a list of cElement certs.
      rgpElement[0] is the user cert
      rgpElement[cElement-1] is the root cert.
    /////////////////////////////////////// */

    pChain =  pCertChainContext->rgpChain[0];
    pRootCert= pChain->rgpElement[pChain->cElement-1]->pCertContext;
    dwRootCertTrust =  pChain->rgpElement[pChain->cElement-1]->TrustStatus.dwInfoStatus;

    
    dwChainTrust = pChain->TrustStatus.dwErrorStatus;

    // We'll allow the following errors.
    dwAllowErrors =     CERT_TRUST_IS_UNTRUSTED_ROOT |  // Since we haven't added the root cert expected!
                        CERT_TRUST_IS_NOT_TIME_VALID;  // Happens if Time is wrong.

    if (dwChainTrust & ~dwAllowErrors)
    {
        OUTPUT_1_ARG("Warning CertChain is not Trusted dwChainTrust = 0x%x \n",dwChainTrust);
    }

    if (!(dwRootCertTrust & CERT_TRUST_IS_SELF_SIGNED))
    {
        OUTPUT_1_ARG("Warning Root CERT is not self signed  dwRootCertTrust = 0x%x\n ",dwRootCertTrust);
    }


    // Add Root CERT.
    bSuccess = CertAddCertificateContextToStore(
            hRootCertStore,
            pRootCert,
            CERT_STORE_ADD_NEW , // DWORD dwAddDisposition, 
            NULL // Would have been a pCertContext for Added Cert
            );
    err = GetLastError();

    if (!bSuccess && err != CRYPT_E_EXISTS)
    {
        OUTPUT(" Unable to add Root  Cert  to Root Cert store \n");
        ret = FALSE;
        goto done;
    }


    // Now Walk rest of the Cert Chain
    // Add every other cert to the Intermediate (CA) Cert Store.

    for (i=1;i<pChain->cElement-1;i++)
    {
        PCCERT_CONTEXT  pCACert= pChain->rgpElement[i]->pCertContext;
        ASSERT(pCACert);

        // Add Intermediate Cert
        bSuccess = CertAddCertificateContextToStore(
                hCACertStore,
                pCACert,
                CERT_STORE_ADD_NEW , // DWORD dwAddDisposition, 
                NULL // Would have been a pCertContext for Added Cert
                );
        err = GetLastError();
        if (!bSuccess && err != CRYPT_E_EXISTS)
        {
            OUTPUT(" Unable to add CA  Cert  to CA  store \n");
            ret = FALSE;
            goto done;
        }
    }
    // If we made it this far, we've succeeded.
    ret=TRUE;

done:
	if (hRootCertStore) CertCloseStore(hRootCertStore,CERT_CLOSE_STORE_FORCE_FLAG);
	if (hCACertStore) CertCloseStore(hCACertStore,CERT_CLOSE_STORE_FORCE_FLAG);
    if (pCertChainContext) CertFreeCertificateChain(pCertChainContext);
    return ret;
}

// Takes  A decoded Cert Chain
// Returns the client cert in it's store *ppCert Upto the caller to free.
BOOL AddEncodedCertificateChainToStore( HCERTSTORE hClientCertStore, CRYPT_DATA_BLOB *pCryptBlob, CRYPT_KEY_PROV_INFO* pKeyProvInfo,HCRYPTPROV hProvWithKey, PCCERT_CONTEXT  *ppClientCert)
{
    PCCERT_CONTEXT pClientCertInClientCertStore=0; // The Pointer to the created cert XXX: Caller Free's.
    PCCERT_CONTEXT pClientCert=0; // Pointer To the Client CERT in the chain.

    PCERT_PUBLIC_KEY_INFO pCertPubKeyInfo=0;
    DWORD dwSize=0;

    HCERTSTORE  hPKCS7ChainCertStore=0;

	BOOL ret = TRUE; // The return value.
	BOOL bSuccess=FALSE;


    ASSERT(hClientCertStore);
    *ppClientCert = NULL;


    // Open the CertStore with the BASE 64 Decoded Data.
	hPKCS7ChainCertStore = CertOpenStore(CERT_STORE_PROV_PKCS7,
                                        X509_ASN_ENCODING| PKCS_7_ASN_ENCODING ,
                                        0, 
                                        0 ,
                                        pCryptBlob);
	if (!hPKCS7ChainCertStore)
	{
		OUTPUT(" hPKCS7ChainCertStore = CertOpenStore failed\n");
		ret = FALSE;
		goto done;
	}

    /////////////////////////////////////////////////////////////
    //Find the user cert in the chain. 
    //Do this by finding the cert associated with our public key.
    /////////////////////////////////////////////////////////////


    // Get the public key. Takes 2 calls, first for getting size to allocate
    // Second To populate the key.

    dwSize=0;
    bSuccess = CryptExportPublicKeyInfo(
       hProvWithKey,
       pKeyProvInfo->dwKeySpec,
       MY_ENCODING_TYPE,
       pCertPubKeyInfo,
       &dwSize // dwSize=0;
            );
	if (!bSuccess || !dwSize)
	{
		OUTPUT(" Unable to get size of the public key.\n");
		ret = FALSE;
		goto done;
	}

    pCertPubKeyInfo = (PCERT_PUBLIC_KEY_INFO)malloc(dwSize);
    if (!pCertPubKeyInfo)
    {
		OUTPUT(" Unable to alloc  the public key.\n");
		ret = FALSE;
		goto done;
    }

    // Second Call to get the actual Key.
    bSuccess = CryptExportPublicKeyInfo(
       hProvWithKey,
       pKeyProvInfo->dwKeySpec, 
       MY_ENCODING_TYPE,
       pCertPubKeyInfo,
       &dwSize
            );
	if (!bSuccess )
	{
		OUTPUT(" Unable to get actual PubKeyInfo.\n");
		ret = FALSE;
		goto done;
	}

    // Get the client cert from the chain.
    pClientCert = CertFindCertificateInStore( hPKCS7ChainCertStore,
            MY_ENCODING_TYPE,
            0,
            CERT_FIND_PUBLIC_KEY,
            pCertPubKeyInfo,
            NULL);
    if(!pClientCert)
	{
		OUTPUT(" CertFindCertificateInStore failed. \n");
		ret = FALSE;
		goto done;
	}

    /*/////////////////////////////////////////////////////
      Add our cert to the client cert store which was passed
     caller needs to have the ClientCert so 
     we won't do a free
    //////////////////////////////////////////////////// */

    bSuccess = CertAddCertificateContextToStore(
            hClientCertStore,
            pClientCert,
            CERT_STORE_ADD_ALWAYS , // DWORD dwAddDisposition, 
            &pClientCertInClientCertStore
            );

    if (!bSuccess)
    {
		OUTPUT(" CertAddCertificateContextToStore Failed. \n");
		ret = FALSE;
		goto done;

    }

    // Deal with the rest of the intermediate certs.
    bSuccess = AddCAandRootCertsToStores(pClientCert,hPKCS7ChainCertStore);

    if(!bSuccess)
    {
        OUTPUT("AddCAandRootCertsToStores failed - continuing execution! Please Examine your Cert Stores");
    }


    // if got this far should return true.
    ret = TRUE;

done:
	// Cleanup.
    *ppClientCert = pClientCertInClientCertStore;
    if (pCertPubKeyInfo) free(pCertPubKeyInfo);
	if (pClientCert) CertFreeCertificateContext(pClientCert);
	if (hPKCS7ChainCertStore) CertCloseStore(hPKCS7ChainCertStore,CERT_CLOSE_STORE_FORCE_FLAG);

	return ret;
}

BOOL AddCertToStore( char *Cert, CRYPT_KEY_PROV_INFO* pKeyProvInfo,TCHAR *CertStore,HCRYPTPROV hProvWithKey,BOOL bIsCertChain)
{
	BOOL ret = TRUE; // The return value.
    PCCERT_CONTEXT pCert=0; // The Pointer to the created cert.
	BOOL bSuccess;
	DWORD err;

	// Open the cert store.
	HCERTSTORE hStore = CertOpenStore(CERT_STORE_PROV_SYSTEM,0,0, CERT_SYSTEM_STORE_CURRENT_USER , CertStore);

	// Find start of base 64 encoded cert.
	char *pStartCert = strstr(Cert,"\r\n"); pStartCert+=2; // Find the start of the cert.

	// XXX: Use better buffer size calculator. 
	DWORD certLen = strlen(Cert);
	DWORD cbDecodeLen = certLen  * 2;
	BYTE *pDecodedCert =  (BYTE*) malloc (cbDecodeLen);

	if(!pDecodedCert)
	{
		OUTPUT("Not enough Memory to Create pDecodedCert\n");
		ret = FALSE;
		goto done;
	}

	err = Base64DecodeExA (pStartCert,certLen, pDecodedCert,&cbDecodeLen,&cbDecodeLen) ;
	if ( err) 
	{
		OUTPUT("Base64DecodeExA Failed\n");
		ret = FALSE;
		goto done;
	}


    // Call Correct function based on bIsCertChain
    if (bIsCertChain)
    {
        // Pass the Encoded Cert in a CryptBlob
        CRYPT_DATA_BLOB CryptBlob;
        CryptBlob.cbData=cbDecodeLen;
        CryptBlob.pbData=pDecodedCert; 

        // Upto us to free the pCert
        bSuccess = AddEncodedCertificateChainToStore( 
                hStore,
                &CryptBlob, 
                pKeyProvInfo,
                hProvWithKey,
                &pCert);
    }

    else
    {
        bSuccess = CertAddEncodedCertificateToStore(hStore,
                X509_ASN_ENCODING,
                (unsigned char*)pDecodedCert,
                cbDecodeLen, 
                CERT_STORE_ADD_NEWER_INHERIT_PROPERTIES, 
                &pCert);
    }

	if (!bSuccess || !pCert)
	{
		OUTPUT("CertAdd Failed\n");
		ret = FALSE;
		goto done;
	}

    // Associate the private key to the Cert.
    bSuccess = CertSetCertificateContextProperty( pCert,CERT_KEY_PROV_INFO_PROP_ID, 0, pKeyProvInfo); 
	if (!bSuccess )
	{
		OUTPUT("CertSetCertificateContextProperty Failed\n");
		ret = FALSE;
		goto done;
	}

	// Associate the cert to the key on the smart card.
	SetSmartCardCert(hProvWithKey,pKeyProvInfo,pCert);

    // If got this far, then we should return true.
    ret=TRUE;
done:
	// Cleanup.
	if (pDecodedCert) free(pDecodedCert);
	if(pCert) CertFreeCertificateContext(pCert);
	if (hStore) CertCloseStore(hStore,CERT_CLOSE_STORE_FORCE_FLAG);
	return ret;
}



// mallocs the B64 Cert, upto someone else to free
BOOL GetCertFromWebServer(TCHAR *Server, TCHAR *Page ,char **pB64Cert)
{
	DWORD cbBytesRead,cbSize,cbPageLen;
	BOOL bWorked,ret=TRUE;
	int  error;

	*pB64Cert=0; // Set to zero, so we don't free something we didn't alloc.

	// for clarity, error-checking has been removed
	HINTERNET hSession = lpInternetOpen(L"capi-GetCert", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	HINTERNET hConnect = lpInternetConnect(hSession, Server, INTERNET_DEFAULT_HTTP_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 1);
	HINTERNET hRequest = lpHttpOpenRequest(hConnect, _T("GET"), Page, _T("HTTP/1.1"), NULL, 0, 0, 1);

	bWorked = lpHttpSendRequest(hRequest, NULL, 0, NULL, 0);
	if (bWorked == FALSE)
	{
		error = GetLastError();
		OUTPUT_1_ARG( "HttpSendRequest Failed : %i",error );
		ret = FALSE;
		goto done;
	}
	cbPageLen=0;
	cbSize=sizeof(cbPageLen);

	bWorked = lpHttpQueryInfo(hRequest,HTTP_QUERY_CONTENT_LENGTH|HTTP_QUERY_FLAG_NUMBER,&cbPageLen,&cbSize,0);
	if (bWorked == FALSE || cbPageLen == 0)
	{
		error = GetLastError();
		if (error == 12150)
		{
			OUTPUT_1_ARG("The host name [%s] could not be found, are you sure it is right?\n",Server);
		}
		else
		{
			OUTPUT_1_ARG("HttpQueryInfo Failed %i ",error);

		}
		ret = FALSE;
		goto done;
	}

	// Give an extra byte so can null terminate.
	cbPageLen+=1;

	*pB64Cert = (char*) malloc ( cbPageLen);
	if (!*pB64Cert)
	{
		error = GetLastError();
		OUTPUT_1_ARG("malloc failed error:%i ",error);
		ret = FALSE;
		goto done;
	}

	(*pB64Cert)[cbPageLen-1] =0x77; // For Debugging 
	bWorked = lpInternetReadFile(hRequest,*pB64Cert,cbPageLen,&cbBytesRead);
	ASSERT(cbBytesRead == cbPageLen-1);
	if (bWorked == FALSE )
	{
		error = GetLastError();
		OUTPUT_1_ARG("InternetReadFile Failed : %i ",error);
		ret = FALSE;
		goto done;
	}
	// Null Terminate that web page.
	(*pB64Cert)[cbPageLen-1] =0x66; // For Debugging 
	(*pB64Cert)[cbPageLen-1] =0; // Null terminate
done:
	if (hConnect) lpInternetCloseHandle(hConnect);
	if (hRequest) lpInternetCloseHandle(hRequest);
	if (hSession) lpInternetCloseHandle(hSession);
	return ret;
}

// Generates a Key and the  container if necassary
// Behavior:
//   If Default container doesn't exist create it. If it does exist use it.
//   If a key doesn't exist create it. If it does exist use it.
// Returns 1 if success 
//         0 if failure.
//
BOOL CreateKeyAndGetContext  (CRYPT_KEY_PROV_INFO *pKeyProvInfo, HCRYPTPROV*  phCryptProv) 
{
	HCRYPTKEY  hCurKey= 0;

	BOOL bWorked,ret=TRUE;
	*phCryptProv = 0; // Start by setting it to 0.

	// 1) Try to open  the container.
	bWorked =  CryptAcquireContext(
			phCryptProv,        // Address for handle to be returned.
			pKeyProvInfo->pwszContainerName,               // Use the current user's logon name.
			pKeyProvInfo->pwszProvName,               // Use the default provider.
			pKeyProvInfo->dwProvType,      // Need to both encrypt and sign.
			NULL);

	// 2) If that doesn't work try to create the container.
	if (!bWorked)
	{
		bWorked = CryptAcquireContext(
				phCryptProv,        // Address for handle to be returned.
				pKeyProvInfo->pwszContainerName,               // Use the current user's logon name.
				pKeyProvInfo->pwszProvName,               // Use the default provider.
				pKeyProvInfo->dwProvType,      // Need to both encrypt and sign.
				CRYPT_NEWKEYSET);              // No flags needed.
	}


	// See if it worked.
	if (!bWorked)
	{
		OUTPUT_1_ARG("CryptAcquireContext failed. %x\n",GetLastError());
		ret=FALSE;
		goto done;
	}

    if (!*phCryptProv)
    {
        OUTPUT("No key container selected\n");
		ret=FALSE;
		goto done;
    }

	//
	// Check if a key already exisis, 
	//If it don't generate a key!
	///////////////////////////////////////////
	if (!CryptGetUserKey(*phCryptProv,pKeyProvInfo->dwKeySpec,&hCurKey))
	{
		int error = GetLastError();
		// Make sure error is no key.
		if (error != NTE_NO_KEY) 
		{
			OUTPUT_1_ARG("First Call to CryptGenKey Failed- with error other than NTE_NO_KEY: [0x%X]\n",error);
			ret=FALSE;
			goto done;
		}

		// If key doesn't exist create the key.
		if (!CryptGenKey(*phCryptProv, pKeyProvInfo->dwKeySpec, pKeyProvInfo->dwFlags, &hCurKey))
		{
			OUTPUT_1_ARG("Second Call to Error: CryptGenKey Failed [%x] \n",error);
			ret=FALSE;
			goto done;
		}

	}
done:
	if (hCurKey) CryptDestroyKey(hCurKey);
	return ret;
}

// Builds the CertRequest
// This char* will need to be freed.
// Returns 0 if there was some sort of error.
char*  BuildPutRequest(TCHAR *tCertAttribs,TCHAR *tCertTemplate,char *B64CertReq)
{
	char ReqBase[]  =  "TargetStoreFlags=0&Mode=newreq&SaveCert=yes&CertRequest=";
	char CertAttrib[] = "&CertAttrib=";
	char CertAttribWTemplatePrefix[] =  "CertificateTemplate%3a";
	char CertTemplateSuffix[] = "%0D%0A"; 

    ASSERT(tCertTemplate);

    // If we didn't pass in a cert template we need to remove the TemplatePrefix and Suffix.
    if (!_tcslen(tCertTemplate))
    {
        strncpy(CertAttribWTemplatePrefix,"",1);
        strncpy(CertTemplateSuffix,"",1);
    }

	DWORD dwCertLen = strlen ( B64CertReq); 
	ASSERT(dwCertLen > 1); // Otherwise, we might over/underflow some buggers.
	if(dwCertLen <= 1)
		return NULL;
	
	// Make room for the conversion.
	CHAR *URLEncodeCertReq  = (char*) malloc(dwCertLen + 100);
	if (!URLEncodeCertReq)
	{
		OUTPUT("malloc failed\n");
		return 0 ;
	}

	int iLenCertReq = Base64ToURL(B64CertReq,dwCertLen,URLEncodeCertReq);
	// Last 2 bytes are: 0D 0A 00
	// Clear the CR/CF Pair
	if ( URLEncodeCertReq[iLenCertReq-2] == 0x0D)  
	{
		URLEncodeCertReq[iLenCertReq-2] = 0; 
		// Could be two sets of 0D 0A pairs coming from 
		// the B64 encoding ending at an end of line
		if ( URLEncodeCertReq[iLenCertReq-4] == 0x0D)  URLEncodeCertReq[iLenCertReq-4] =0;
	}
	else
	{
        // Something Fishy with our base 64 decoding.
        ASSERT(0);
	}


    int iPutRequestSize = iLenCertReq  
        + strlen(ReqBase) 
        + _tcslen(tCertAttribs)  
        + strlen(CertAttribWTemplatePrefix) 
        + _tcslen(tCertTemplate)  
        + strlen(CertTemplateSuffix) 
        + strlen(CertAttrib)  
        + 1; // For terminating \0

	// Now Malloc the FrmData. + len of the 
	CHAR* ActualPutRequest= (char*)malloc(iPutRequestSize);

	if (!ActualPutRequest)
	{
		free(URLEncodeCertReq);
		OUTPUT("malloc failed\n");
		return FALSE ;
	}


    // Be very careful if changing this call.
    _snprintf(ActualPutRequest,
            iPutRequestSize,
            "%s%s%s%s%S%s%S",
            ReqBase, // Base
            URLEncodeCertReq, // Add the Encoded URL
            CertAttrib, // Add &CertAttrib
            CertAttribWTemplatePrefix, // Add =ClientTemplate%3a (or blank)
            tCertTemplate, // Copy out of unicode before concat.
            CertTemplateSuffix, // Add 0A0D (or blank)
            tCertAttribs// Copy out of unicode before concat.
    ); 

	free(URLEncodeCertReq);
	return (ActualPutRequest);
}


// Returns CertRequestNo.
// or -1 if error.
int  SendCertRequestToWebServer(TCHAR *server ,TCHAR *page, TCHAR *userName, TCHAR *password, char * PutRequest)
{
	TCHAR hdrs[] = _T("Content-Type: application/x-www-form-urlencoded"); // Necessary.
	TCHAR accept[] = _T("Accept: */*");
	TCHAR *acArray[2] = {accept,0};
	DWORD cbBytesRead,dwErrorCode,dwError;
	BOOL bWorked;
	int  error;
	int frmLen =0;
	char *cWebPage=0;
	DWORD cbPageLen=0,cbSize=0;
	int iReqNo=-1; // Set to error by default, will get set to correct value in ParseWebPageToFindReqNo


	// for clarity, error-checking has been removed
	HINTERNET hSession = lpInternetOpen(L"capi-Export", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0); 
	HINTERNET hConnect = lpInternetConnect(hSession, server, INTERNET_DEFAULT_HTTP_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 1);
	HINTERNET hRequest = lpHttpOpenRequest(hConnect, _T("POST"), page, _T("HTTP/1.1"), NULL, 0, 0, 1);

	int noRetries=0;
	// If given , send the username and password to the server.
	if (_tcslen(userName))
	{
		// Set username and password.
		lpInternetSetOption(hRequest,INTERNET_OPTION_USERNAME,userName,_tcslen(userName));
		lpInternetSetOption(hRequest,INTERNET_OPTION_PASSWORD,password,_tcslen(password));

	}

resend:
	bWorked = lpHttpSendRequest(hRequest, hdrs, _tcslen(hdrs), PutRequest, strlen(PutRequest));


	// dwErrorCode stores the error code associated with the call to
	// HttpSendRequest.   XXX: If you are getting a failure here, be sure ntlmssp is around.

	dwErrorCode = hRequest ? ERROR_SUCCESS : GetLastError();

	dwError = lpInternetErrorDlg(GetDesktopWindow(), hRequest, dwErrorCode, 
			FLAGS_ERROR_UI_FILTER_FOR_ERRORS | 
			FLAGS_ERROR_UI_FLAGS_CHANGE_OPTIONS |
			FLAGS_ERROR_UI_FLAGS_GENERATE_DATA,
			NULL);
	if (noRetries  >= NUM_AUTH_FAIL)
	{
		OUTPUT_1_ARG(" You have failed to authenticate several times. Maybe something else is wrong!.\n Is Server[%s] correct?",server);
		OUTPUT_1_ARG(" You have failed to authenticate several times. Maybe something else is wrong!.\n Is Page[%s] correct?",page);
		goto done;

	}
	if (dwError == ERROR_INTERNET_FORCE_RETRY) 
	{
		noRetries++;
		goto resend;
	}

	// At this point, we have data.
	cbSize=sizeof(cbPageLen);

	bWorked = lpHttpQueryInfo(hRequest,HTTP_QUERY_CONTENT_LENGTH|HTTP_QUERY_FLAG_NUMBER,&cbPageLen,&cbSize,0);
	if (bWorked == FALSE || cbPageLen == 0)
	{
		error = GetLastError();
		if (error == 12150)
		{
			OUTPUT_1_ARG("The host name [%s] could not be found, are you sure it is right?\n",server);
		}
		else
		{
			OUTPUT_1_ARG("HttpQueryInfo Failed %i\n ",error);
		}
		goto done;

	}

	cbPageLen+=1; // Add an extra byte so we can null terminate.

	cWebPage = (char*) malloc ( cbPageLen);
	if (!cWebPage)
	{
		OUTPUT_1_ARG("malloc failed error:%i ",GetLastError());
		goto done;
	}

	cWebPage[cbPageLen-1] =0x77; // For debug purposes.
	bWorked = lpInternetReadFile(hRequest,cWebPage,cbPageLen,&cbBytesRead);
	if (bWorked == FALSE )
	{
		OUTPUT_1_ARG("InternetReadFile Failed : %i ",GetLastError());
		goto done;
	}
    ASSERT(cbBytesRead == cbPageLen-1);
    // 0 terminate our webpage.
    cWebPage[cbPageLen-1] =0x66; // For debug purposes.
    cWebPage[cbPageLen-1] =0;


    iReqNo = ParseWebPageToFindReqNo(cWebPage);
    if (-1 == iReqNo  )
    {
        OUTPUT("Client send the following Request:\n");
        OUTPUT_1_ARG("%S\n",PutRequest);

    }
    // Returns -1 on error.
done:
    // close any valid internet-handles "
    if (hConnect) lpInternetCloseHandle(hConnect);
    if (hRequest) lpInternetCloseHandle(hRequest);
    if (hSession) lpInternetCloseHandle(hSession);
    if (cWebPage) free (cWebPage);

    return iReqNo;
}
#define CERT_SUBJECT_NAME "SubjectName-Should Be OverWritten by CA"
// Generates a Cert Req, which if true will need to be freed
// Somewhere else.
BOOL GenerateCertRequest(HCRYPTPROV hCryptProv,CRYPT_KEY_PROV_INFO *pKeyProvInfo,char **pB64CertReq)
{
	//-------------------------------------------------------------------
	// Declare and initialize variables 


	// Declare and initialize a CERT_RDN_ATTR array.
	// In this code, only one array element is used.
	CERT_RDN_ATTR rgNameAttr[] = {
		"2.5.4.3",                             // pszObjId 
		CERT_RDN_PRINTABLE_STRING,             // dwValueType
		strlen(CERT_SUBJECT_NAME),             // value.cbData
		(BYTE*)CERT_SUBJECT_NAME};             // value.pbData

	//-------------------------------------------------------------------
	// Declare and initialize a CERT_RDN array.
	// In this code, only one array element is used.

	CERT_RDN rgRDN[] = {
	1,                 // rgRDN[0].cRDNAttr
	&rgNameAttr[0]};   // rgRDN[0].rgRDNAttr

	//-------------------------------------------------------------------
	// Declare and initialize a CERT_NAME_INFO structure.

	CERT_NAME_INFO Name = {
		1,                  // Name.cRDN
		rgRDN};             // Name.rgRDN

	//-------------------------------------------------------------------
	// Declare and initialize all other variables and structures.

	CERT_REQUEST_INFO  CertReqInfo;
	CERT_NAME_BLOB  SubjNameBlob;
	DWORD  cbNameEncoded;
	BYTE*  pbNameEncoded;
	DWORD  cbEncodedCertReqSize;
	CERT_PUBLIC_KEY_INFO*  pbPublicKeyInfo=0;
	CRYPT_OBJID_BLOB  Parameters;
	DWORD  cbPublicKeyInfo;
	CRYPT_ALGORITHM_IDENTIFIER  SigAlg;
	BYTE*  pbSignedEncodedCertReq;


	//-------------------------------------------------------------------
	//    Begin processing.

	if(!CryptEncodeObject(
				MY_ENCODING_TYPE,     // Encoding type
				X509_NAME,            // Structure type
				&Name,                // Address of CERT_NAME_INFO structure
				NULL,                 // pbEncoded
				&cbNameEncoded))      // pbEncoded size
	{
		HandleError("First call to CryptEncodeObject failed.\
				\nA public/private key pair may not exit in the container. \n");
		return FALSE;
	}
	//-------------------------------------------------------------------
	//     Allocate memory for the encoded name.

	if(!(pbNameEncoded = (BYTE*)malloc(cbNameEncoded)))
	{
		HandleError("pbNamencoded malloc operation failed.\n");
		return FALSE;
	}

	//-------------------------------------------------------------------
	//  Call CryptEncodeObject to do the actual encoding of the name.

	if(!CryptEncodeObject(
				MY_ENCODING_TYPE,    // Encoding type
				X509_NAME,           // Structure type
				&Name,               // Address of CERT_NAME_INFO structure
				pbNameEncoded,       // pbEncoded
				&cbNameEncoded))     // pbEncoded size
	{
		free(pbNameEncoded);
		HandleError("Second call to CryptEncodeObject failed.\n");
		return FALSE;
	}
	//--------------------------------------------------------------------
	// Set the subject member of CertReqInfo to point to 
	// a CERT_NAME_INFO structure that 
	// has been initialized with the data from cbNameEncoded
	// and pbNameEncoded.

	SubjNameBlob.cbData = cbNameEncoded;
	SubjNameBlob.pbData = pbNameEncoded;
	CertReqInfo.Subject = SubjNameBlob;

	//--------------------------------------------------------------------
	// Generate custom information. This step is not
	// implemented in this code.

	CertReqInfo.cAttribute = 0;
	CertReqInfo.rgAttribute = NULL;
	CertReqInfo.dwVersion = CERT_REQUEST_V1;

	//--------------------------------------------------------------------
	// Call CryptExportPublicKeyInfo to get the size of the returned
	// information.

	if(!CryptExportPublicKeyInfo(
				hCryptProv,            // Provider handle
				pKeyProvInfo->dwKeySpec,          // Key spec
				MY_ENCODING_TYPE,      // Encoding type
				NULL,                  // pbPublicKeyInfo
				&cbPublicKeyInfo))     // Size of PublicKeyInfo
	{
		free(pbNameEncoded);
		HandleError("First call to CryptExportPublickKeyInfo failed.\
				\nProbable cause: No key pair in the key container. \n");
		return FALSE;
	}
	//--------------------------------------------------------------------
	// Allocate the necessary memory.

	if(!(pbPublicKeyInfo = (CERT_PUBLIC_KEY_INFO*)malloc(cbPublicKeyInfo)))
	{
		free(pbNameEncoded);
		HandleError("Memory allocation failed.");
		return FALSE;
	}
	//--------------------------------------------------------------------
	// Call CryptExportPublicKeyInfo to get pbPublicKeyInfo.

	if(!CryptExportPublicKeyInfo(
				hCryptProv,            // Provider handle
				pKeyProvInfo->dwKeySpec,          // Key spec
				MY_ENCODING_TYPE,      // Encoding type
				pbPublicKeyInfo,       // pbPublicKeyInfo
				&cbPublicKeyInfo))     // Size of PublicKeyInfo
	{
		free(pbNameEncoded);
		free(pbPublicKeyInfo);
		HandleError("Second call to CryptExportPublicKeyInfo failed.");
		return FALSE;
	}
	//--------------------------------------------------------------------
	// Set the SubjectPublicKeyInfo member of the 
	// CERT_REQUEST_INFO structure to point to the CERT_PUBLIC_KEY_INFO 
	// structure created.

	CertReqInfo.SubjectPublicKeyInfo = *pbPublicKeyInfo;

	memset(&Parameters, 0, sizeof(Parameters));
	SigAlg.pszObjId = szOID_OIWSEC_sha1RSASign; 
	SigAlg.Parameters = Parameters;

	//--------------------------------------------------------------------
	// Call CryptSignAndEncodeCertificate to get the size of the
	// returned BLOB.


	if(!CryptSignAndEncodeCertificate(
				hCryptProv,                      // Crypto provider
				pKeyProvInfo->dwKeySpec,                  // Key spec
				MY_ENCODING_TYPE,                // Encoding type
				X509_CERT_REQUEST_TO_BE_SIGNED,  // Structure type
				&CertReqInfo,                    // Structure information
				&SigAlg,                         // Signature algorithm
				NULL,                            // Not used
				NULL,                            // pbSignedEncodedCertReq
				&cbEncodedCertReqSize))          // Size of certificate 
		// required
	{
		free(pbNameEncoded);
		free(pbPublicKeyInfo);
		HandleError("First call to CryptSignandEncode failed.");
		return false;
	}
	//--------------------------------------------------------------------
	// Allocate memory for the encoded certificate request.

	if(!(pbSignedEncodedCertReq = (BYTE*)malloc(cbEncodedCertReqSize)))
	{
		free(pbNameEncoded);
		free(pbPublicKeyInfo);
		HandleError("Malloc operation failed.");
		return false;
	}
	//--------------------------------------------------------------------
	// Call CryptSignAndEncodeCertificate to get the 
	// returned BLOB.

	if(!CryptSignAndEncodeCertificate(
				hCryptProv,                     // Crypto provider
				pKeyProvInfo->dwKeySpec,                 // Key spec
				MY_ENCODING_TYPE,               // Encoding type
				X509_CERT_REQUEST_TO_BE_SIGNED, // Struct type
				&CertReqInfo,                   // Struct info        
				&SigAlg,                        // Signature algorithm
				NULL,                           // Not used
				pbSignedEncodedCertReq,         // Pointer
				&cbEncodedCertReqSize))         // Length of the message
	{
		free(pbNameEncoded);
		free(pbPublicKeyInfo);
		free(pbSignedEncodedCertReq);
		HandleError("Second call to CryptSignAndEncode failed.");
		return false;
	}
	//--------------------------------------------------------------------
	//  I can free the PublicKey and encoded name now.
	free(pbNameEncoded);
	free(pbPublicKeyInfo);

	// UUENCODEing expands a string by about 33% + CRLFs.
	DWORD cbB64Len = cbEncodedCertReqSize * 2 + 6;
	
	*pB64CertReq = (char*)malloc(cbB64Len);
	if (!*pB64CertReq)
	{
		OUTPUT("malloc failed");
		free(pbSignedEncodedCertReq);
		return FALSE;
	}


	Base64EncodeA(pbSignedEncodedCertReq,cbEncodedCertReqSize,*pB64CertReq,&cbB64Len);
	// cbB64Len has been set to the end of the string.
	// We have room, so write the 0.
	(*pB64CertReq)[cbB64Len] =0x66; // For Debugging 
	(*pB64CertReq)[cbB64Len] =0; // Zero Terminate the string

	// Free the req blobl.
	free(pbSignedEncodedCertReq);


	return TRUE;
}

// Does the link to Wininet and sets up the global variables.
// It's up to the application to free the HINSTANCE
// returns  0 if error.
HINSTANCE SetupWinInet()
{
	HINSTANCE winInet =  LoadLibrary(_T("WININET.DLL"));
	// Do some GetProcAddress for our stuffs.
	if (!winInet)
	{
		OUTPUT("LoadLibrary failed to load WinInet");
		return 0;
	}

	//XXX: Change these to use unicodable constants..
	lpInternetOpen =
		(PInternetOpen ) GetProcAddress(winInet,_T("InternetOpenW"));
	lpHttpQueryInfo =
		(PHttpQueryInfo ) GetProcAddress(winInet,_T("HttpQueryInfoW"));
	lpInternetConnect =
		( PInternetConnect ) GetProcAddress(winInet,_T("InternetConnectW"));
	lpHttpOpenRequest =
		(PHttpOpenRequest ) GetProcAddress(winInet,_T("HttpOpenRequestW"));
	lpHttpSendRequest =
		(PHttpSendRequest ) GetProcAddress(winInet,_T("HttpSendRequestW"));
	lpInternetSetOption = 
		(PInternetSetOption) GetProcAddress(winInet,_T("InternetSetOptionW"));

	lpInternetCloseHandle =
		(PInternetCloseHandle ) GetProcAddress(winInet,_T("InternetCloseHandle"));
	lpInternetErrorDlg =
		(PInternetErrorDlg ) GetProcAddress(winInet,_T("InternetErrorDlg"));
	lpInternetReadFile =
		(PInternetReadFile ) GetProcAddress(winInet,_T("InternetReadFile"));

	if ( !lpInternetOpen || !lpInternetErrorDlg || !lpInternetConnect || 
			!lpHttpOpenRequest || !lpHttpSendRequest || !lpHttpQueryInfo  ||
			!lpInternetCloseHandle || !lpInternetReadFile || !lpInternetSetOption)
	{
		OUTPUT("Get ProcAddress Failed");
		return 0 ;
	}
	return winInet;
}
