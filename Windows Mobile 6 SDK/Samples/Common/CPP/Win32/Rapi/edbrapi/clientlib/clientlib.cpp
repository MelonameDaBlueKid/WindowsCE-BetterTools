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
// --------------------------------------------------------------------------
//
// Clientlib.CPP
//
// Implementation of EDB RAPI. Client side functions.
// --------------------------------------------------------------------------


#ifndef EDB
#define EDB
#endif

#include <windows.h>
#include <malloc.h>
#include <strsafe.h>
#include "rapi.h"
#include "edbrapi.h" 
#include "../common/InputStructures.h"
#include "Clientlib.h"

#define EDBRAPIDLL  L"EdbRapiServer"

// This EDB RAPI function issues a mount request for a database volume
BOOL CeEdbMountDBVolEx
(
    PCEGUID pGuid,
    LPWSTR lpwszDBVol,
    CEVOLUMEOPTIONS *pOptions,
    DWORD dwFlags 
)
{
    DWORD    cbOut;
    BYTE*    pOutBuffer;
    HRESULT  hr;

    //transform the input params into CeRapiInvoke Input 
    INMOUNTDBVOLEX edbInput;
    edbInput.dwFlags = dwFlags;
    StringCchCopy(edbInput.wszDBVol, ARRAYSIZE(edbInput.wszDBVol), lpwszDBVol); 
    edbInput.pOptions = pOptions;

    DWORD cbInBuffer;
    
    if ( pOptions )    
    {
        cbInBuffer = sizeof(edbInput) + sizeof(*pOptions);
    }
    else
    {
        cbInBuffer = sizeof(edbInput);
    }
    BYTE *pInBuffer = (BYTE *)LocalAlloc(LPTR, cbInBuffer);  

    memcpy(pInBuffer, &edbInput, sizeof(edbInput));
    if (pOptions)
    {
        memcpy(pInBuffer + sizeof(edbInput), pOptions, sizeof(*pOptions));
    }
     
    hr = CeRapiInvoke(EDBRAPIDLL,
                    EDB_MOUNTDBVOLEX_FNAME, 
                    cbInBuffer, 
                    pInBuffer, 
                    &cbOut, 
                    &pOutBuffer, 
                    NULL, 
                    0);
    LocalFree(pInBuffer);

    //free the DLL allocated memory
    BOOL fRes;
    if (cbOut == sizeof(*pGuid))
    {
        memcpy(pGuid, pOutBuffer, sizeof(*pGuid));        
        fRes = TRUE;
    }
    else 
    {
        SetLastError(hr);
        fRes = FALSE;
    }
    if (cbOut)
    {
        LocalFree(pOutBuffer);
    }
    return fRes;
}

//This EDB RAPI function is used to mount a volume on a Windows CE based device.
//Although this function may be used to mount an EDB volume, applications should call 
//CeEdbMountDBVolEx when mounting an EDB volume.
BOOL CeEdbMountDBVol ( PCEGUID pGuid, LPWSTR lpwszDBVol, DWORD dwFlags )
{
   return CeEdbMountDBVolEx ( pGuid, lpwszDBVol, NULL, dwFlags );  
}

//This EDB RAPI function creates a new database in a mounted volume on a Windows CE based device.
CEOID CeEdbCreateDatabaseWithProps
(
    PCEGUID pGuid,
    CEDBASEINFOEX* pInfo,
    DWORD cProps,
    CEPROPSPEC* prgProps
)
{
    DWORD cbOut;
    BYTE* pOutBuffer;
    HRESULT hr;
    INCREATEDBPROP edbInput;

    DWORD cbInBuffer = sizeof(edbInput) + sizeof(CEPROPSPEC) * cProps;
    BYTE *pInBuffer = (BYTE *) LocalAlloc(LPTR, cbInBuffer);
        
    
    memcpy (&(edbInput.guid), pGuid, sizeof(*pGuid));
    if (pInfo)
    {
        memcpy(&(edbInput.Options), pInfo, sizeof(*pInfo));
    }
    else
    {
        ZeroMemory(&(edbInput.Options), sizeof(*pInfo));
    }
    edbInput.cProps = cProps;
    edbInput.prgProps = prgProps; //used as flag. If it is not NULL, there will be an array of CEPROPSPEC
                                  // at the end of input buffer.
    memcpy (pInBuffer, &edbInput, sizeof(edbInput));

    if ( prgProps && 
        (cProps > 0))
    {
        memcpy (pInBuffer + sizeof(edbInput), prgProps, sizeof(CEPROPSPEC) * cProps);    
    }
 
    hr = CeRapiInvoke (EDBRAPIDLL, 
                    EDB_CREATEDBWITHPROPS_FNAME,
                    cbInBuffer, 
                    pInBuffer, 
                    &cbOut, 
                    &pOutBuffer, 
                    NULL, 
                    0);
    LocalFree (pInBuffer);

    CEOID   oid;  
    if (cbOut == sizeof(oid))
    {        
        memcpy(&oid, pOutBuffer, sizeof(oid)); 
    }
    else 
    {
        SetLastError(hr);
        oid = NULL;
    }
    if (cbOut)
    {
        LocalFree(pOutBuffer);
    }
    return oid;
}

//This EDB RAPI function creates a new database in a mounted volume on a Windows CE based device.
//Although this function may be used to create EDB databases, applications should call 
//CeEdbCreateDatabaseWithProps when creating an EDB database.
CEOID CeEdbCreateDatabaseEx2(PCEGUID pguid, CEDBASEINFOEX* pInfo)
{
    return CeEdbCreateDatabaseWithProps(pguid, pInfo, 0, NULL);    
}

//This EDB RAPI function retrieves information about an object in
// a mounted database volume on a Windows CE based device.
BOOL CeEdbOidGetInfoEx2(PCEGUID pGuid, CEOID oid, CEOIDINFOEX* poidInfo)
{
    DWORD cbOut;
    BYTE* pOutBuffer;
    HRESULT hr;
    
    DWORD cbInBuffer = sizeof(*pGuid) + sizeof(oid);
    BYTE *pInBuffer = (BYTE *) LocalAlloc(LPTR, cbInBuffer);
    memcpy(pInBuffer, pGuid, sizeof(*pGuid));
    memcpy(pInBuffer + sizeof(*pGuid), &oid, sizeof(oid));

    hr = CeRapiInvoke(EDBRAPIDLL, 
                    EDB_OIDGETINFOEX2_FNAME,
                    cbInBuffer, 
                    pInBuffer, 
                    &cbOut, 
                    &pOutBuffer, 
                    NULL, 
                    0);

    LocalFree(pInBuffer);

    BOOL fRes;
    if (cbOut == sizeof(*poidInfo))
    {
        memcpy(poidInfo, pOutBuffer, sizeof(*poidInfo)); 
        fRes = TRUE;
    }
    else 
    {
        SetLastError(hr);
        fRes = FALSE;
    }
    if (cbOut)
    {
        LocalFree(pOutBuffer);
    }
    return fRes;
}

//This EDB RAPI function is used to create a session on a Windows CE based device. 
HANDLE CeEdbCreateSession(CEGUID* pGuid)
{
    DWORD cbOut;
    BYTE* pOutBuffer;
    HRESULT hr;
    
    DWORD cbInBuffer = sizeof(*pGuid);
    BYTE *pInBuffer = (BYTE *)pGuid;

    hr = CeRapiInvoke(EDBRAPIDLL, 
                    EDB_CREATESESSION_FNAME,
                    cbInBuffer, 
                    pInBuffer, 
                    &cbOut, 
                    &pOutBuffer, 
                    NULL, 
                    0);
   
    HANDLE hOutDB;
    if (cbOut == sizeof(hOutDB))
    {
        memcpy(&hOutDB, pOutBuffer, sizeof(hOutDB));        
    }
    else 
    {
        SetLastError(hr);
        hOutDB = INVALID_HANDLE_VALUE ;
    }
    if (cbOut)
    {
        LocalFree(pOutBuffer);
    }
    return hOutDB;
}

//This EDB RAPI function is used to open an existing database that is in a mounted volume 
//on a Windows CE based device. The volume must be mounted by using the CeEdbMountDBVol function.
HANDLE CeEdbOpenDatabaseInSession
(
    HANDLE hSession,
    PCEGUID pGuid, 
    PCEOID poid,
    LPWSTR lpwszName, 
    SORTORDERSPECEX* pSort, 
    DWORD dwFlags,
    CENOTIFYREQUEST* pRequest
)
{
    DWORD cbOut;
    BYTE* pOutBuffer;
    HRESULT hr;

    INOPENDBINSESSION edbInput ;
    edbInput.hSession = hSession;
    memcpy(&(edbInput.guid), pGuid, sizeof(*pGuid));
    memcpy(&(edbInput.oidDbase), poid, sizeof(*poid));
    StringCchCopy(edbInput.wszName, ARRAYSIZE(edbInput.wszName), lpwszName); 
    if (pSort)
    {
        memcpy(&(edbInput.sortorderspec), pSort, sizeof(*pSort));
    }
    else
    {
        edbInput.sortorderspec.wVersion = 0; //used as a flag
    }
    edbInput.dwFlags = dwFlags;
    if (pRequest)
    {
        memcpy(&(edbInput.request), pRequest, sizeof(*pRequest));
    }
    else
    {
        ZeroMemory(&(edbInput.request), sizeof(*pRequest)); 
    }

    DWORD cbInBuffer = sizeof(edbInput);
    BYTE * pInBuffer = (BYTE *) (&edbInput);

    hr = CeRapiInvoke(EDBRAPIDLL, 
                    EDB_OPENDBINSESSION_FNAME,
                    cbInBuffer, 
                    pInBuffer, 
                    &cbOut, 
                    &pOutBuffer, 
                    NULL, 
                    0); 

    HANDLE hOutDB;
    if (cbOut == sizeof(hOutDB))
    {
        memcpy(&hOutDB, pOutBuffer, sizeof(hOutDB));
    }
    else 
    {
        SetLastError(hr);
        hOutDB = INVALID_HANDLE_VALUE ;
    }
    if (cbOut)
    {
        LocalFree(pOutBuffer);
    }
    return hOutDB;
}

//This EDB RAPI function is used to obtain the session of an already 
//opened database on a Windows CE based device.
HANDLE CeEdbGetDatabaseSession(HANDLE hDatabase)
{
    DWORD cbOut;
    BYTE* pOutBuffer;
    HRESULT hr;
    DWORD cbInBuffer = sizeof(hDatabase);
    BYTE * pInBuffer = (BYTE *)(&hDatabase);

    hr = CeRapiInvoke(EDBRAPIDLL, 
                    EDB_GETDBSESSION_FNAME,
                    cbInBuffer, 
                    pInBuffer, 
                    &cbOut, 
                    &pOutBuffer, 
                    NULL, 
                    0);

    HANDLE hOutDB;
    if (cbOut == sizeof(hOutDB))
    {
        memcpy(&hOutDB, pOutBuffer, sizeof(hOutDB));        
    }
    else 
    {
        SetLastError(hr);
        hOutDB = INVALID_HANDLE_VALUE ;
    }
    if (cbOut)
    {
        LocalFree(pOutBuffer);
    }
    return hOutDB;
}

//This EDB RAPI function is used to forcibly flush all pending changes 
//that have been made to a volume on a Windows CE based device.
BOOL CeEdbFlushDBVol(PCEGUID pGuid)
{
    DWORD cbOut;
    BYTE* pOutBuffer;
    HRESULT hr;
    DWORD cbInBuffer;
    BYTE * pInBuffer;
    if (pGuid)
    {
        cbInBuffer = sizeof(*pGuid);
        pInBuffer = (BYTE *)pGuid;
    }
    else
    {
        cbInBuffer = 0;
        pInBuffer = NULL;
    }
  
    hr = CeRapiInvoke(EDBRAPIDLL, 
                EDB_FLUSHVOL_FNAME,
                cbInBuffer, 
                pInBuffer, 
                &cbOut, 
                &pOutBuffer, 
                NULL, 
                0);

    if (cbOut)
    {
        LocalFree(pOutBuffer);
    }
    if (hr == S_OK)
    {
        return TRUE;
    }
    else
    {
        SetLastError(hr);
        return FALSE;
    }
}

//This EDB RAPI function is used to either insert a new record or update 
//the properties of an existing record on a Windows CE based device.
CEOID CeEdbWriteRecordProps
(
    HANDLE hDatabase, 
    CEOID oidRecord, 
    WORD cPropID, 
    CEPROPVAL* prgPropVal
)
{
    HRESULT hr = S_OK;
    DWORD cbOut;
    BYTE* pOutBuffer;

    DWORD cbInBuffer = sizeof(hDatabase) + sizeof(oidRecord) + sizeof(cPropID);
    DWORD dwVarySize = cPropID * sizeof(CEPROPVAL);
    for (int i = 0; i < cPropID; i++)
    {
        switch (TypeFromPropID(prgPropVal[i].propid))
        {
            case CEVT_LPWSTR:
                size_t cch;
                hr = StringCchLength(prgPropVal[i].val.lpwstr, STRSAFE_MAX_CCH, &cch);
                CHR(hr);

                // Include null terminating character.
                cch +=1;

                dwVarySize += (DWORD) (cch * sizeof(WCHAR));
                break;

            case CEVT_BLOB:
                dwVarySize += prgPropVal[i].val.blob.dwCount;
                break;

            default :
                break;
        }
    }  

    DWORD  cbWritten = 0;
    BYTE * pInStream = (BYTE *) LocalAlloc (LPTR, cbInBuffer + dwVarySize + sizeof(dwVarySize));
    

    memcpy(pInStream, &hDatabase, sizeof(hDatabase));
    cbWritten += sizeof(hDatabase);
    memcpy(pInStream + cbWritten, &oidRecord, sizeof(oidRecord));
    cbWritten += sizeof(oidRecord);
    memcpy(pInStream + cbWritten, &cPropID, sizeof(cPropID));
    cbWritten += sizeof(cPropID);

    memcpy(pInStream + cbWritten, &dwVarySize, sizeof(dwVarySize)); //the size of the buffer for prgPropVal 
    cbWritten += sizeof(dwVarySize);
    
    DWORD dwIndex = cPropID * sizeof(CEPROPVAL);

    for (int i = 0; i < cPropID; i++)
    {
        CEPROPVAL propval = prgPropVal[i];
        switch(TypeFromPropID(propval.propid))
        {
            case CEVT_LPWSTR:
                propval.val.lpwstr = (LPWSTR) dwIndex;
                size_t cch;
                hr = StringCchLength(prgPropVal[i].val.lpwstr, STRSAFE_MAX_CCH, &cch);
                CHR(hr);
                dwIndex += (DWORD)(cch * sizeof(WCHAR));
                break;

            case CEVT_BLOB:
                propval.val.blob.lpb = (LPBYTE)dwIndex; 
                dwIndex += propval.val.blob.dwCount;
                break;

            default: 
                break;
        }
        memcpy(pInStream + cbWritten, &propval, sizeof(CEPROPVAL)); 
        cbWritten += sizeof(CEPROPVAL);
    }

    for (int i = 0; i < cPropID; i++)
    {
        CEPROPVAL propval=prgPropVal[i];
        switch (TypeFromPropID(propval.propid))
        {
            case CEVT_LPWSTR:
                size_t cch;
                hr = StringCchLength(prgPropVal[i].val.lpwstr, STRSAFE_MAX_CCH, &cch);
                CHR(hr);
                memcpy(pInStream + cbWritten, propval.val.lpwstr, cch * sizeof(WCHAR));
                cbWritten += ((DWORD)wcslen(propval.val.lpwstr) + 1) * sizeof(WCHAR);
                break;

            case CEVT_BLOB:
                memcpy(pInStream + cbWritten, propval.val.blob.lpb, propval.val.blob.dwCount);
                cbWritten += propval.val.blob.dwCount;
                break;

            default:
                break;
        }
    }
    
    hr = CeRapiInvoke(EDBRAPIDLL, 
                EDB_WRITERECPROPS_FNAME,
                cbInBuffer + dwVarySize + sizeof(DWORD), 
                pInStream, 
                &cbOut, 
                &pOutBuffer, 
                NULL, 
                0);    
    
    CEOID   oid;  
    if (cbOut == sizeof(oid))
    {        
        memcpy(&oid, pOutBuffer, sizeof(oid)); 
    }
    else 
    {
        SetLastError(hr);
        oid = NULL;
    }
    if (cbOut)
    {
        LocalFree(pOutBuffer);
    }
    return oid;

Error:
    SetLastError(hr);
    return NULL;

}

//This EDB RAPI function changes the locale identifier (LCID) of a volume 
//for sort operations on a Windows CE based device.
VOID CeEdbChangeDatabaseLCID(PCEGUID pceguid, DWORD LCID)
{
    DWORD cbOut;
    BYTE* pOutBuffer;
    HRESULT hr;   

    DWORD cbInBuffer = sizeof(*pceguid) + sizeof(LCID);
    BYTE * pInBuffer = (BYTE *) LocalAlloc(LPTR, cbInBuffer);
    memcpy(pInBuffer, pceguid, sizeof(*pceguid));
    memcpy(pInBuffer + sizeof(*pceguid), &LCID, sizeof(LCID));
    
    hr = CeRapiInvoke(EDBRAPIDLL, 
            EDB_CHANGEDBLCID_FNAME,
            cbInBuffer, 
            pInBuffer, 
            &cbOut, 
            &pOutBuffer, 
            NULL, 
            0);
    LocalFree(pInBuffer);
    SetLastError(hr);
}

//This EDB RAPI function is used to seek to a specific record 
//in an open database on a Windows CE based device.
CEOID CeEdbSeekDatabaseEx
(
    HANDLE hDatabase,
    DWORD dwSeekType, 
    DWORD dwValue, 
    WORD wNumVals,
    LPDWORD lpdwIndex
)
{
    DWORD cbOut;
    BYTE* pOutBuffer;
    HRESULT hr;
    
    INSEEKEB edbInput;
    edbInput.hDatabase = hDatabase;
    edbInput.dwSeekType = dwSeekType;
    edbInput.dwValue = dwValue;
    edbInput.wNumVals = wNumVals;

    DWORD cbInBuffer = sizeof(edbInput);
    BYTE * pInBuffer = (BYTE *)(&edbInput);
 
    hr = CeRapiInvoke(EDBRAPIDLL, 
                EDB_SEEKDBEX_FNAME,
                cbInBuffer, 
                pInBuffer, 
                &cbOut, 
                &pOutBuffer, 
                NULL, 
                0);

    CEOID   oid;
    if (cbOut == sizeof(oid) + sizeof(*lpdwIndex))
    {
        
        memcpy(&oid, pOutBuffer, sizeof(oid));
        if (lpdwIndex) 
        {
            memcpy(lpdwIndex, pOutBuffer + sizeof(oid), sizeof(DWORD));
        }
        LocalFree(pOutBuffer);
        return oid;
    }
    else 
    {
        SetLastError(hr);
        return (NULL);
    }
}

//This EDB RAPI function seeks the specified record in an open database on a Windows CE based device. 
//Although this function may be used to seek in EDB databases, applications should call CeEdbSeekDatabaseEx 
//when seeking in an EDB database.
CEOID CeEdbSeekDatabase
( 
    HANDLE hDatabase, 
    DWORD dwSeekType, 
    DWORD dwValue, 
    LPDWORD lpdwIndex
)
{
    return CeEdbSeekDatabaseEx(hDatabase,dwSeekType, dwValue, 1, lpdwIndex);
}

//This EDB RAPI function is used to delete a database that is in a volume 
//that was mounted by using the CeEdbMountDbVolEx function.
BOOL CeEdbDeleteDatabaseEx(PCEGUID pGuid, CEOID oid)
{
    DWORD cbOut;
    BYTE* pOutBuffer;
    HRESULT hr;

    DWORD cbInBuffer = sizeof(*pGuid) + sizeof(oid);
    BYTE *pInBuffer = (BYTE *)LocalAlloc(LPTR, cbInBuffer);

    memcpy(pInBuffer, pGuid, sizeof(*pGuid));
    memcpy(pInBuffer + sizeof(*pGuid), &oid, sizeof(oid));    

    hr = CeRapiInvoke(EDBRAPIDLL, 
                EDB_DELETEDBEX_FNAME,
                cbInBuffer, 
                pInBuffer, 
                &cbOut, 
                &pOutBuffer, 
                NULL, 
                0);
    LocalFree(pInBuffer);

    if (hr == S_OK)
    {
        return TRUE;
    }
    else
    {
        SetLastError(hr);
        return FALSE;
    }
}

//This EDB RAPI function is used to unmount a volume that was previously mounted 
//by calling the CeEdbMountDbVolEx function.
BOOL CeEdbUnmountDBVol(PCEGUID pGuid)
{
    DWORD cbOut;
    BYTE* pOutBuffer;
    HRESULT hr;

    DWORD cbInBuffer = sizeof(*pGuid);
    BYTE *pInBuffer = (BYTE *)pGuid;
   
    hr = CeRapiInvoke(EDBRAPIDLL, 
                EDB_UNMOUNTDBVOL_FNAME,
                cbInBuffer, 
                pInBuffer, 
                &cbOut, 
                &pOutBuffer, 
                NULL, 
                0);

    if (hr == S_OK)
    {
        return TRUE;
    }
    else
    {
        SetLastError(hr);
        return FALSE;
    }
}

//This EDB RAPI function is used to enumerate the file names and GUIDs of all mounted 
//volumes on a Windows CE based device. 
BOOL CeEdbEnumDBVolumes(PCEGUID pGuid, LPWSTR pwszName, DWORD cchMaxName)
{
    DWORD cbOut;
    BYTE* pOutBuffer;
    HRESULT hr;

    DWORD cbInBuffer = sizeof(*pGuid) + sizeof(cchMaxName);
    BYTE * pInBuffer = (BYTE *)LocalAlloc(LPTR, cbInBuffer);
    memcpy(pInBuffer, pGuid, sizeof(*pGuid));
    memcpy(pInBuffer + sizeof(*pGuid), &cchMaxName, sizeof(cchMaxName));    

    hr = CeRapiInvoke(EDBRAPIDLL, 
                EDB_ENUMDBVOLUMES_FNAME,
                cbInBuffer, 
                pInBuffer, 
                &cbOut, 
                &pOutBuffer, 
                NULL, 
                0);
    LocalFree(pInBuffer);

    if (hr == S_OK) 
    {
        memcpy(pGuid, pOutBuffer, sizeof(*pGuid));
        memcpy(pwszName, pOutBuffer + sizeof(*pGuid), cbOut - sizeof(*pGuid));
        LocalFree(pOutBuffer);
        return TRUE;
    }
    else
    {
        SetLastError(hr);
        return FALSE;
    }
}

//This EDB RAPI function is used to read a set of properties from the current record.
CEOID CeEdbReadRecordPropsEx
(
    HANDLE hDatabase, 
    DWORD dwFlags, 
    LPWORD lpcPropID,
    CEPROPID* prgPropID, 
    LPBYTE *lplpBuffer, 
    LPDWORD lpcbBuffer,
    HANDLE hHeap
)
{
    DWORD cbOut;
    BYTE* pOutBuffer;
    HRESULT hr;
    CEPROPVAL* prgPropVal;

    WORD nprop;
    if ((*lpcPropID > 0) && prgPropID)
    {
        nprop = *lpcPropID;
    }
    else 
    {
        nprop = 0;
    }

    INSEEKEB edbInput;
    edbInput.hDatabase     = hDatabase;
    edbInput.dwSeekType    = dwFlags;
    edbInput.dwValue       = *lpcbBuffer;
    edbInput.wNumVals      = nprop;

    DWORD cbInBuffer = sizeof(edbInput) + sizeof(*prgPropID) * edbInput.wNumVals;
    
    BYTE * pInBuffer = (LPBYTE) LocalAlloc(LPTR, cbInBuffer);
    memcpy(pInBuffer, &edbInput, sizeof(edbInput));
    if (edbInput.wNumVals > 0)
        memcpy(pInBuffer + sizeof(edbInput), prgPropID, sizeof(*prgPropID) * edbInput.wNumVals);
  
    hr = CeRapiInvoke(EDBRAPIDLL, 
                EDB_READRECPROPSEX_FNAME,
                cbInBuffer, 
                pInBuffer, 
                &cbOut, 
                &pOutBuffer, 
                NULL, 
                0);
    LocalFree(pInBuffer);

    //unpack data, copy them into desktop buffer 
    if (hr == S_OK)
    {
        CEOID oid ;
        memcpy(&oid, pOutBuffer, sizeof(oid));
        memcpy(lpcPropID, pOutBuffer + sizeof(oid), sizeof(*lpcPropID));
        DWORD dwBuffersize = cbOut - sizeof(oid) - sizeof(*lpcPropID);
        if (*lpcbBuffer >= dwBuffersize)
        {//buffer is large enough
            if ((!(*lplpBuffer)) && dwFlags) 
            {
                prgPropVal =(CEPROPVAL*)LocalAlloc(LPTR, dwBuffersize);
                *lplpBuffer = (BYTE *)prgPropVal;
            }
            else 
            {
                prgPropVal = (CEPROPVAL*) (*lplpBuffer);
            }
        }
        else //buffer is too small
        {
            if (dwFlags == CEDB_ALLOWREALLOC)
            {
                LocalFree(*lplpBuffer);
                prgPropVal = (CEPROPVAL*) LocalAlloc(LPTR, dwBuffersize);
                *lplpBuffer = (BYTE *) prgPropVal;
            }
            else
            {
                SetLastError(ERROR_INSUFFICIENT_BUFFER);
                LocalFree(pOutBuffer);
                return 0;
            }
        }
        memcpy(prgPropVal, pOutBuffer + sizeof(oid) + sizeof(*lpcPropID), dwBuffersize);
        *lpcbBuffer = dwBuffersize;

        //shift the internal offset to the actual pointer
        for (int i = 0; i < *lpcPropID; i++)
        {
            switch(TypeFromPropID(prgPropVal[i].propid))
            {
                case CEVT_LPWSTR:
                    prgPropVal[i].val.lpwstr = reinterpret_cast<LPWSTR>(reinterpret_cast<DWORD>(prgPropVal[i].val.lpwstr) + 
                                                                        reinterpret_cast<DWORD>(prgPropVal));
                    break;

                case CEVT_BLOB:
                    prgPropVal[i].val.blob.lpb = reinterpret_cast<LPBYTE>( reinterpret_cast<DWORD>(prgPropVal[i].val.blob.lpb) + 
                                                                           reinterpret_cast<DWORD>(prgPropVal));
                    break;

                default:
                    break;
            }
        }
        LocalFree(pOutBuffer);
        return oid;
    }
    else 
    {
        SetLastError(hr);
        if (cbOut)
        {
            LocalFree(pOutBuffer);
        }
        return 0;
    }
}

//This EDB RAPI function reads properties from the current record. Although this function 
//may be used to read the properties of an EDB databases, applications should call 
//CeEdbReadRecordPropsEx when working with an EDB database.
CEOID CeEdbReadRecordProps
(
    HANDLE hDatabase, 
    DWORD dwFlags, 
    LPWORD lpcPropID,
    CEPROPID* prgPropID, 
    LPBYTE *lplpBuffer, 
    LPDWORD lpcbBuffer
)
{
    return CeEdbReadRecordPropsEx(hDatabase, dwFlags, lpcPropID,prgPropID, lplpBuffer, lpcbBuffer, NULL);
}

//This EDB RAPI function is used to add properties to an existing database.
BOOL CeEdbAddDatabaseProps
(
    PCEGUID pGuid,
    CEOID oidDb,
    DWORD cProps,
    CEPROPSPEC* prgProps
)
{
    DWORD cbOut;
    BYTE* pOutBuffer;
    HRESULT hr;
    INADDDBPROPS edbInput ;

    DWORD cbInBuffer = sizeof(edbInput) + (sizeof(CEPROPSPEC) + CEDB_MAXDBASENAMELEN * sizeof(WCHAR)) * cProps;
    BYTE * pInBuffer = (BYTE *)LocalAlloc(LPTR, cbInBuffer);
        
    
    memcpy(&(edbInput.guid), pGuid, sizeof(*pGuid));
    edbInput.oidDbase = oidDb;    
    edbInput.cProps = cProps;
    edbInput.prgProps = prgProps;
    
    memcpy(pInBuffer, &edbInput, sizeof(edbInput));

    if (prgProps && (cProps>0))
    {
        memcpy(pInBuffer + sizeof(edbInput), prgProps, sizeof(CEPROPSPEC) * cProps); 
        for (DWORD i = 0; i < cProps; i++)
        {
            if(prgProps[i].pwszPropName)
            {
                BYTE * pIndex = pInBuffer + sizeof(edbInput) + sizeof(CEPROPSPEC) * cProps;
                memcpy( pIndex + CEDB_MAXDBASENAMELEN * sizeof(WCHAR) * i, 
                        prgProps[i].pwszPropName, 
                        CEDB_MAXDBASENAMELEN * sizeof(WCHAR));
            }
        }
    }
    else
    {
        SetLastError(ERROR_INVALID_PARAMETER);
        return FALSE;
    }

    hr = CeRapiInvoke(EDBRAPIDLL, 
                EDB_ADDDBPROPS_FNAME,
                cbInBuffer, 
                pInBuffer, 
                &cbOut, 
                &pOutBuffer, 
                NULL, 
                0);
    
    LocalFree(pInBuffer);
    
    if (hr == S_OK)
    {
        return TRUE;
    }
    else
    {
        SetLastError(hr);
        return FALSE;
    }
}

//This EDB RAPI function is used to delete a record from a database.
BOOL CeEdbDeleteRecord
(
    HANDLE hDatabase, 
    CEOID oidRecord
)
{
    DWORD cbOut;
    BYTE* pOutBuffer;
    HRESULT hr;

    DWORD cbInBuffer = sizeof(hDatabase) + sizeof(oidRecord);
    BYTE * pInBuffer = (BYTE *)LocalAlloc(LPTR, cbInBuffer);

    memcpy(pInBuffer, &hDatabase, sizeof(hDatabase));
    memcpy(pInBuffer + sizeof(hDatabase), &oidRecord, sizeof(oidRecord));

    hr = CeRapiInvoke(EDBRAPIDLL, 
                EDB_DELETEREC_FNAME,
                cbInBuffer, 
                pInBuffer, 
                &cbOut, 
                &pOutBuffer, 
                NULL, 
                0);
    LocalFree(pInBuffer);

    if (hr == S_OK)
    {
        return TRUE;
    }
    else
    {
        SetLastError(hr);
        return FALSE;
    }
}

//This EDB RAPI function is used to create a handle which can then be used with the 
//CeEdbFindNextDatabaseEx function to enumerate databases in a specific volume, 
//or all of the databases across all mounted volumes.
HANDLE CeEdbFindFirstDatabaseEx
( 
    PCEGUID pGuid, 
    DWORD dwDbaseType
)
{
    DWORD cbOut;
    BYTE* pOutBuffer;

    HRESULT hr;

    DWORD cbInBuffer = sizeof(*pGuid) + sizeof(dwDbaseType);
    BYTE * pInBuffer = (BYTE *)LocalAlloc(LPTR, cbInBuffer);

    memcpy(pInBuffer, pGuid, sizeof(*pGuid));
    memcpy(pInBuffer + sizeof(*pGuid), &dwDbaseType, sizeof(dwDbaseType));

    hr = CeRapiInvoke(EDBRAPIDLL, 
                EDB_FINDFIRSTDBEX_FNAME,
                cbInBuffer, 
                pInBuffer, 
                &cbOut, 
                &pOutBuffer, 
                NULL, 
                0);
    LocalFree(pInBuffer);

    HANDLE hOutDB;
    if (cbOut == sizeof(hOutDB))
    {
        memcpy(&hOutDB, pOutBuffer, sizeof(hOutDB));        
    }
    else 
    {
        SetLastError(hr);
        hOutDB = INVALID_HANDLE_VALUE ;
    }
    if (cbOut)
    {
        LocalFree(pOutBuffer);
    }
    return hOutDB;
}

//This EDB RAPI function returns the OID of the next database that matches the enumeration 
//criteria set up by calling the CeEdbFindFirstDatabaseEx function. 
CEOID CeEdbFindNextDatabaseEx
( 
    HANDLE hEnum,
    PCEGUID pGuid
)
{   
    DWORD cbOut;
    BYTE* pOutBuffer;
    HRESULT hr;

    DWORD cbInBuffer = sizeof(*pGuid) + sizeof(hEnum);
    BYTE * pInBuffer = (BYTE *)LocalAlloc(LPTR, cbInBuffer);

    memcpy(pInBuffer, &hEnum, sizeof(hEnum));
    if (pGuid)
    {
        memcpy(pInBuffer + sizeof(hEnum), pGuid, sizeof(*pGuid));
    }
    else
    {
        ZeroMemory(pInBuffer + sizeof(hEnum), sizeof(*pGuid));
    }

    hr = CeRapiInvoke(EDBRAPIDLL, 
                EDB_FINDNEXTDBEX_FNAME,
                cbInBuffer, 
                pInBuffer, 
                &cbOut, 
                &pOutBuffer, 
                NULL, 
                0);
    LocalFree(pInBuffer);

    CEOID   oid;  
    if (cbOut == sizeof(oid))
    {        
        memcpy(&oid, pOutBuffer, sizeof(oid)); 
    }
    else 
    {
        SetLastError(hr);
        oid = NULL;
    }
    if (cbOut)
    {
        LocalFree(pOutBuffer);
    }
    return oid;
}

//This EDB RAPI function is used to retrieve some or all of the properties from a database.
BOOL CeEdbGetDatabaseProps 
(
    HANDLE hDatabase,
    LPWORD lpcPropID,
    CEPROPID* prgPropID,
    CEPROPSPEC* prgProps
)
{
    DWORD cbOut;
    BYTE* pOutBuffer;
    HRESULT hr;

    WORD cPropID = *lpcPropID;
    DWORD cbInBuffer;
    INGETDBPROPS edbInput ;
    if (prgPropID)
    {
        cbInBuffer = sizeof(edbInput) + sizeof(CEPROPSPEC) * cPropID;
    }
    else
    {
        cbInBuffer = sizeof(edbInput);
    }
    BYTE *pInBuffer = (BYTE *)LocalAlloc(LPTR, cbInBuffer);
        
    
    edbInput.hDatabase = hDatabase;
    edbInput.cPropID = cPropID;    
    edbInput.prgPropID = prgPropID; //used as flag for NULL or not
    edbInput.prgProps = prgProps; 

    memcpy(pInBuffer, &edbInput, sizeof(edbInput));
    if (prgPropID && 
        (cPropID > 0))
    {
        memcpy(pInBuffer + sizeof(edbInput), prgPropID, sizeof(CEPROPSPEC) * cPropID); 
    }

    hr = CeRapiInvoke(EDBRAPIDLL, 
                EDB_GETDBPROPS_FNAME,
                cbInBuffer, 
                pInBuffer, 
                &cbOut, 
                &pOutBuffer, 
                NULL, 
                0);
    LocalFree(pInBuffer);

    if (hr == S_OK)
    {
        memcpy(lpcPropID, pOutBuffer, sizeof(*lpcPropID));
        if (prgProps &&
            (cbOut > sizeof(*lpcPropID)))
        {
            memcpy(prgProps, pOutBuffer + sizeof(*lpcPropID), (*lpcPropID) * sizeof(CEPROPSPEC));
        }        
        LocalFree(pOutBuffer);
        return TRUE;
    }
    else
    {
        SetLastError(hr);
        return FALSE;
    }
}

//This EDB RAPI function is used to remove properties from a database.
BOOL CeEdbRemoveDatabaseProps
(
    PCEGUID pGuid,
    CEOID oidDb,
    DWORD cProps,
    CEPROPID* prgProps
)
{
    DWORD cbOut;
    BYTE* pOutBuffer;
    HRESULT hr;

    DWORD cbInBuffer = sizeof(*pGuid) + sizeof(oidDb) + sizeof(cProps) + sizeof(CEPROPID) * cProps;
    BYTE * pInBuffer = (BYTE *)LocalAlloc(LPTR, cbInBuffer);

    memcpy(pInBuffer, pGuid, sizeof(*pGuid));
    memcpy(pInBuffer + sizeof(*pGuid), &oidDb, sizeof(oidDb));
    memcpy(pInBuffer + sizeof(*pGuid) + sizeof(oidDb), &cProps, sizeof(cProps));
    memcpy(pInBuffer + sizeof(*pGuid) + sizeof(oidDb) + sizeof(cProps), prgProps, sizeof(CEPROPID) * cProps);

    hr = CeRapiInvoke(EDBRAPIDLL, 
                EDB_REMOVEDBPROPS_FNAME,
                cbInBuffer, 
                pInBuffer, 
                &cbOut, 
                &pOutBuffer, 
                NULL, 
                0);
    LocalFree(pInBuffer);

    if (hr == S_OK)
    {
        return TRUE;
    }
    else
    {
        SetLastError(hr);
        return FALSE;
    }
}

//This EDB RAPI function obtains information about an open database by using the handle of the database.
BOOL CeEdbGetDBInformationByHandle
(
    HANDLE hDbase, 
    BY_HANDLE_DB_INFORMATION *lpDBInfo
)
{
    HRESULT hr;
    DWORD cbOut;
    BYTE* pOutBuffer;

    if (!lpDBInfo)
    {
        SetLastError(ERROR_INVALID_PARAMETER);
        return FALSE;
    }

    DWORD cbInBuffer = sizeof(hDbase);
    BYTE * pInBuffer = (BYTE *)(&hDbase);

    hr = CeRapiInvoke(EDBRAPIDLL, 
                EDB_GETDBINFOBYHANDLE_FNAME,
                cbInBuffer, 
                pInBuffer, 
                &cbOut, 
                &pOutBuffer, 
                NULL, 
                0);

    BOOL fRes;
    if ((hr == S_OK) &&
        (cbOut == sizeof(*lpDBInfo)))
    {
        memcpy(lpDBInfo, pOutBuffer, sizeof(*lpDBInfo));
        fRes = TRUE;
    }
    else
    {
        SetLastError(hr);
        fRes = FALSE;
    }
    if (cbOut)
    {
        LocalFree(pOutBuffer);
    }
    return fRes;
}

//This EDB RAPI function is used to set various database parameters, including 
//the name, sort orders, and type.
BOOL CeEdbSetDatabaseInfo
(
    CEOID oidDbase,
    CEDBASEINFOEX* pNewInfo
)
{
    HRESULT hr;
    DWORD cbOut;
    BYTE* pOutBuffer;

    DWORD cbInBuffer = sizeof(oidDbase) + sizeof(*pNewInfo);
    BYTE * pInBuffer = (BYTE *)LocalAlloc(LPTR, cbInBuffer);

    memcpy(pInBuffer, &oidDbase, sizeof(oidDbase));
    memcpy(pInBuffer + sizeof(oidDbase), pNewInfo, sizeof(*pNewInfo));

    hr = CeRapiInvoke(EDBRAPIDLL, 
            EDB_SETDBINFO_FNAME,
            cbInBuffer, 
            pInBuffer, 
            &cbOut, 
            &pOutBuffer, 
            NULL, 
            0);
    LocalFree(pInBuffer);

    if (hr == S_OK)
    {
        return TRUE;
    }
    else
    {
        SetLastError(hr);
        return FALSE;
    }
}

//This EDB RAPI function is used to free a CENOTIFICATION pointer that was posted 
//to a client's notification window.
BOOL CeEdbFreeNotification
(
    CENOTIFYREQUEST* pRequest,
    CENOTIFICATION* pNotification
)
{
    HRESULT hr;
    DWORD cbOut;
    BYTE* pOutBuffer;

    DWORD cbInBuffer = sizeof(*pRequest) + sizeof(*pNotification);
    BYTE * pInBuffer = (BYTE *)LocalAlloc(LPTR, cbInBuffer);

    memcpy(pInBuffer , pRequest, sizeof(*pRequest));
    memcpy(pInBuffer + sizeof(*pRequest), pNotification, sizeof(*pNotification));

    hr = CeRapiInvoke(EDBRAPIDLL, 
            EDB_FREENOTIFICATION_FNAME,
            cbInBuffer, 
            pInBuffer, 
            &cbOut, 
            &pOutBuffer, 
            NULL, 
            0);
    LocalFree(pInBuffer);

    if (hr == S_OK)
    {
        return TRUE;
    }
    else
    {
        SetLastError(hr);
        return FALSE;
    }
}

//This EDB RAPI function is used to set a per-session option. 
BOOL CeEdbSetSessionOption
(
    HANDLE hSession,
    ULONG ulOptionId,
    DWORD dwValue
)
{
    HRESULT hr;
    DWORD cbOut;
    BYTE* pOutBuffer;

    DWORD cbInBuffer = sizeof(hSession) + sizeof(ulOptionId) + sizeof(dwValue);
    BYTE * pInBuffer = (BYTE *)LocalAlloc(LPTR, cbInBuffer);

    memcpy(pInBuffer , &hSession, sizeof(hSession));
    memcpy(pInBuffer + sizeof(hSession), &ulOptionId, sizeof(ulOptionId));
    memcpy(pInBuffer + sizeof(hSession) + sizeof(ulOptionId), &dwValue, sizeof(dwValue));

    hr = CeRapiInvoke(EDBRAPIDLL, 
            EDB_SETSESSIONOPT_FNAME,
            cbInBuffer, 
            pInBuffer, 
            &cbOut, 
            &pOutBuffer, 
            NULL, 
            0);
    LocalFree(pInBuffer);

    if (hr == S_OK)
    {
        return TRUE;
    }
    else
    {
        SetLastError(hr);
        return FALSE;
    }
}

//This EDB RAPI function is used to begin a transaction.
BOOL CeEdbBeginTransaction
(
    HANDLE hSession,
    CEDBISOLATIONLEVEL isoLevel
)
{
    HRESULT hr;
    DWORD cbOut;
    BYTE* pOutBuffer;

    DWORD cbInBuffer = sizeof(hSession) + sizeof(isoLevel);
    BYTE * pInBuffer = (BYTE *)LocalAlloc(LPTR, cbInBuffer);

    memcpy(pInBuffer , &hSession, sizeof(hSession));
    memcpy(pInBuffer + sizeof(hSession), &isoLevel, sizeof(isoLevel));

    hr = CeRapiInvoke(EDBRAPIDLL, 
            EDB_BEGINTRANSACTION_FNAME,
            cbInBuffer, 
            pInBuffer, 
            &cbOut, 
            &pOutBuffer, 
            NULL, 
            0);
    LocalFree(pInBuffer);

    if (hr == S_OK)
    {
        return TRUE;
    }
    else
    {
        SetLastError(hr);
        return FALSE;
    }
}

//This EDB RAPI function is used to end a transaction.
BOOL CeEdbEndTransaction
(
    HANDLE hSession,
    BOOL fCommit
)
{
    HRESULT hr;
    DWORD cbOut;
    BYTE* pOutBuffer;

    DWORD cbInBuffer = sizeof(hSession) + sizeof(fCommit);
    BYTE * pInBuffer = (BYTE *)LocalAlloc(LPTR, cbInBuffer);

    memcpy(pInBuffer , &hSession, sizeof(hSession));
    memcpy(pInBuffer + sizeof(hSession), &fCommit, sizeof(fCommit));

    hr = CeRapiInvoke(EDBRAPIDLL, 
            EDB_ENDTRANSACTION_FNAME,
            cbInBuffer, 
            pInBuffer, 
            &cbOut, 
            &pOutBuffer, 
            NULL, 
            0);
    LocalFree(pInBuffer);

    if (hr == S_OK)
    {
        return TRUE;
    }
    else
    {
        SetLastError(hr);
        return FALSE;
    }
}

//This EDB RAPI function is used to open a stream object on a CEVT_STREAM typed property.
HANDLE CeEdbOpenStream
(
    HANDLE hDatabase,
    CEPROPID propid,
    DWORD dwMode
)
{
    HRESULT hr;
    DWORD cbOut;
    BYTE* pOutBuffer;

    DWORD cbInBuffer = sizeof(hDatabase) + sizeof(propid) + sizeof(dwMode);
    BYTE * pInBuffer = (BYTE *)LocalAlloc(LPTR, cbInBuffer);

    memcpy(pInBuffer , &hDatabase, sizeof(hDatabase));
    memcpy(pInBuffer + sizeof(hDatabase), &propid, sizeof(propid));
    memcpy(pInBuffer + sizeof(hDatabase) + sizeof(propid), &dwMode, sizeof(dwMode));

    hr = CeRapiInvoke(EDBRAPIDLL, 
            EDB_OPENSTREAM_FNAME,
            cbInBuffer, 
            pInBuffer, 
            &cbOut, 
            &pOutBuffer, 
            NULL, 
            0);
    LocalFree(pInBuffer);

    HANDLE hOutDB;
    if (cbOut == sizeof(hOutDB))
    {
        memcpy(&hOutDB, pOutBuffer, sizeof(hOutDB));        
    }
    else 
    {
        SetLastError(hr);
        hOutDB = INVALID_HANDLE_VALUE ;
    }
    if (cbOut)
    {
        LocalFree(pOutBuffer);
    }
    return hOutDB;
}

//This EDB RAPI function is used to read data from a stream.
BOOL CeEdbStreamRead
(
    HANDLE hStream,
    LPBYTE lprgbBuffer,
    DWORD cbRead,
    LPDWORD lpcbRead
)
{
    HRESULT hr;
    DWORD cbOut;
    BYTE* pOutBuffer;

    if (!lprgbBuffer)
    {
        SetLastError(ERROR_INVALID_PARAMETER);
        return FALSE;
    }

    DWORD cbInBuffer = sizeof(hStream) + sizeof(cbRead);
    BYTE * pInBuffer = (BYTE *)LocalAlloc(LPTR, cbInBuffer);

    memcpy(pInBuffer , &hStream, sizeof(hStream));
    memcpy(pInBuffer + sizeof(hStream), &cbRead, sizeof(cbRead));

    hr = CeRapiInvoke(EDBRAPIDLL, 
            EDB_STREAMREAD_FNAME,
            cbInBuffer, 
            pInBuffer, 
            &cbOut, 
            &pOutBuffer, 
            NULL, 
            0);
    LocalFree(pInBuffer);

    if (cbOut)
    {
        if (lpcbRead) 
        {
            memcpy(lpcbRead, pOutBuffer, sizeof(*lpcbRead));
        }
        memcpy(lprgbBuffer, pOutBuffer + sizeof(*lpcbRead), cbOut - sizeof(*lpcbRead));
        LocalFree(pOutBuffer);
        return TRUE;
    }
    else
    {
        SetLastError(hr);
        return FALSE;
    }
}

//This EDB RAPI function is used to commit the changes that have been made to 
//the stream using the CeEdbStreamWrite function.
BOOL CeEdbStreamSaveChanges(HANDLE hStream)
{
    HRESULT hr;
    DWORD cbOut;
    BYTE* pOutBuffer;

    DWORD cbInBuffer = sizeof(hStream);
    BYTE * pInBuffer = (BYTE *)(&hStream);

    hr = CeRapiInvoke(EDBRAPIDLL, 
            EDB_STREAMSAVECHANGE_FNAME,
            cbInBuffer, 
            pInBuffer, 
            &cbOut, 
            &pOutBuffer, 
            NULL, 
            0);

    if (hr == S_OK)
    {
        return TRUE;
    }
    else
    {
        SetLastError(hr);
        return FALSE;
    }
}

//This EDB RAPI function is used to set the size of data in a stream
BOOL CeEdbStreamSetSize(HANDLE hStream, DWORD cbSize)
{
    HRESULT hr;
    DWORD cbOut;
    BYTE* pOutBuffer;

    DWORD cbInBuffer = sizeof(hStream) + sizeof(cbSize);
    BYTE * pInBuffer = (BYTE *)LocalAlloc(LPTR, cbInBuffer);

    memcpy(pInBuffer , &hStream, sizeof(hStream));
    memcpy(pInBuffer + sizeof(hStream), &cbSize, sizeof(cbSize));

    hr = CeRapiInvoke(EDBRAPIDLL, 
            EDB_STREAMSETSIZE_FNAME,
            cbInBuffer, 
            pInBuffer, 
            &cbOut, 
            &pOutBuffer, 
            NULL, 
            0);
    LocalFree(pInBuffer);

    if (hr == S_OK)
    {
        return TRUE;
    }
    else
    {
        SetLastError(hr);
        return FALSE;
    }
}

//This EDB RAPI function is used to change the current seek position of an opened stream.
BOOL CeEdbStreamSeek
(
    HANDLE hStream,
    DWORD cbMove,
    DWORD dwOrigin,
    LPDWORD lpcbNewOffset
)
{
    HRESULT hr;
    DWORD cbOut;
    BYTE* pOutBuffer;

    DWORD cbInBuffer = sizeof(hStream) + sizeof(cbMove) + sizeof(dwOrigin);
    BYTE * pInBuffer = (BYTE *)LocalAlloc(LPTR, cbInBuffer);

    memcpy(pInBuffer , &hStream, sizeof(hStream));
    memcpy(pInBuffer + sizeof(hStream), &cbMove, sizeof(cbMove));
    memcpy(pInBuffer + sizeof(hStream) + sizeof(cbMove), &dwOrigin, sizeof(dwOrigin));

    hr = CeRapiInvoke(EDBRAPIDLL, 
            EDB_STREAMSEEK_FNAME,
            cbInBuffer, 
            pInBuffer, 
            &cbOut, 
            &pOutBuffer, 
            NULL, 
            0);
    LocalFree(pInBuffer);

    if(cbOut)
    {
        if(lpcbNewOffset)
        {
            memcpy(lpcbNewOffset, pOutBuffer, sizeof(*lpcbNewOffset));
        }
        return TRUE;
    }
    else
    {
        SetLastError(hr);
        return FALSE;
    }
}

//This EDB RAPI function is used to write data into a stream.
BOOL CeEdbStreamWrite
(
    HANDLE hStream,
    LPBYTE lprgbBuffer,
    DWORD cbWrite,
    LPDWORD lpcbWritten
)
{
    HRESULT hr;
    DWORD cbOut;
    BYTE* pOutBuffer;

    DWORD cbInBuffer = sizeof(hStream) + sizeof(cbWrite) + cbWrite;
    BYTE * pInBuffer = (BYTE *)LocalAlloc(LPTR, cbInBuffer);

    memcpy(pInBuffer, &hStream, sizeof(hStream));
    memcpy(pInBuffer + sizeof(hStream), &cbWrite, sizeof(cbWrite));
    memcpy(pInBuffer + sizeof(hStream) + sizeof(cbWrite), lprgbBuffer, cbWrite);

    hr = CeRapiInvoke(EDBRAPIDLL, 
            EDB_STREAMWRITE_FNAME,
            cbInBuffer, 
            pInBuffer, 
            &cbOut, 
            &pOutBuffer, 
            NULL, 
            0);
    LocalFree(pInBuffer);

    if(cbOut)
    {
        if(lpcbWritten)
        {
            memcpy(lpcbWritten, pOutBuffer, sizeof(DWORD));
        }
        return TRUE;
    }
    else
    {
        SetLastError(hr);
        return FALSE;
    }
}

///////////////////////////////////////////////////////////////////////////////////
//End of EDB RAPI APIs

