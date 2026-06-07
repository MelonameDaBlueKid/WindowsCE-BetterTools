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
// Server.CPP
//
// Implementation of EDB RAPI. Device side DLL.
// --------------------------------------------------------------------------


#ifndef EDB
#define EDB
#endif

#include <windows.h>
#include "rapi.h"

#include "../common/InputStructures.h"

HRESULT DevCeMountDBVolEx
(  
    DWORD cbInput, 
    BYTE* pInput,
    DWORD* pcbOutput, 
    BYTE** ppOutBufferput,
    IRAPIStream* pStream
)
{   
    DWORD dwAttributes = 0;
    HRESULT hr = S_OK;   
    
    INMOUNTDBVOLEX * pBuffer = (INMOUNTDBVOLEX *)pInput;    
    CEGUID *pguidDBVol = new CEGUID;

    if (pBuffer->pOptions)
    {
        pBuffer->pOptions = (CEVOLUMEOPTIONS *) (pInput + sizeof(*pBuffer));
    }    

    // Verify that either the file does not exist or the file is not a system file.    
    dwAttributes = GetFileAttributes(pBuffer->wszDBVol);
    if ((dwAttributes != 0xFFFFFFFF) && (dwAttributes & FILE_ATTRIBUTE_SYSTEM))
    {
        hr = E_FAIL;
    }
    else if (!CeMountDBVolEx(pguidDBVol, 
                pBuffer->wszDBVol, 
                pBuffer->pOptions, 
                pBuffer->dwFlags))
    {
        *pcbOutput = 0;
        delete pguidDBVol;
        hr = HRESULT_FROM_WIN32(GetLastError());
    }    
    else 
    {
        *pcbOutput = sizeof(*pguidDBVol);
        *ppOutBufferput = (BYTE *)pguidDBVol;
    }
    return hr;
}

HRESULT DevCeCreateDatabaseWithProps
(  
    DWORD cbInput, 
    BYTE* pInput,
    DWORD* pcbOutput, 
    BYTE** ppOutBufferput,
    IRAPIStream* pStream
)
{
    HRESULT hr = S_OK;
    INCREATEDBPROP *pBuffer = (INCREATEDBPROP *)pInput;    
    CEOID * poid = new CEOID;   

    if (pBuffer->prgProps)
    {
        pBuffer->prgProps = (CEPROPSPEC*)(pInput + sizeof(*pBuffer));
    }
    CEDBASEINFOEX *pOptions;
    if(pBuffer->Options.wVersion != CEDBASEINFOEX_VERSION)
    {
        pOptions = NULL;
    }
    else
    {
        pOptions = &(pBuffer->Options);
    }

    if (!(*poid = CeCreateDatabaseWithProps( &(pBuffer->guid), 
                                             pOptions, 
                                             pBuffer->cProps, 
                                             pBuffer->prgProps)))
    {
        *pcbOutput = 0;
        delete poid;
        hr = HRESULT_FROM_WIN32(GetLastError());;
    }
    else
    {                   
        *pcbOutput = sizeof(*poid);
        *ppOutBufferput = (BYTE *) poid;
    }

    return hr;
}

HRESULT  DevCeOidGetInfoEx2
(  
    DWORD cbInput, 
    BYTE* pInput,
    DWORD* pcbOutput, 
    BYTE** ppOutBufferput,
    IRAPIStream* pStream
)
{
    HRESULT hr = S_OK;
    PCEGUID pGuid = (PCEGUID)pInput;
    CEOID oid;

    memcpy(&oid, pInput + sizeof(*pGuid), sizeof(oid));
    CEOIDINFOEX* poidInfo = (CEOIDINFOEX*) LocalAlloc(LPTR, sizeof(CEOIDINFOEX));
    poidInfo->wVersion = CEOIDINFOEX_VERSION;
    
    if ( !CeOidGetInfoEx2(pGuid, oid, poidInfo) )
    {
        *pcbOutput = 0;
        delete poidInfo;
        hr = HRESULT_FROM_WIN32(GetLastError());;
    }
    else
    {                                                  
        *pcbOutput = sizeof(*poidInfo);
        *ppOutBufferput = (BYTE *) poidInfo;
    }
    return hr;
}

HRESULT  DevCeCreateSession
(  
    DWORD cbInput, 
    BYTE* pInput,
    DWORD* pcbOutput, 
    BYTE** ppOutBufferput,
    IRAPIStream* pStream
)
{
    HRESULT hr = S_OK;    

    CEGUID* pGuid = (CEGUID *)pInput;
    HANDLE * hDB = new HANDLE ;
    *hDB = CeCreateSession(pGuid);

    if (*hDB == INVALID_HANDLE_VALUE )
    {
        *pcbOutput = 0;
        delete hDB;
        hr = HRESULT_FROM_WIN32(GetLastError());;
    }
    else
    {
        *pcbOutput = sizeof(*hDB);
        *ppOutBufferput = (BYTE*)hDB;
    }
    return hr;
}

HRESULT  DevCeOpenDatabaseInSession 
(  
    DWORD cbInput, 
    BYTE* pInput,
    DWORD* pcbOutput, 
    BYTE** ppOutBufferput,
    IRAPIStream* pStream
)
{
    HRESULT hr = S_OK;

    INOPENDBINSESSION *pBuffer = (INOPENDBINSESSION *)pInput;
    HANDLE hSession;
    if (pBuffer->hSession) 
    {
        hSession = pBuffer->hSession;
    }
    else 
    {
        hSession = NULL;
    }

    SORTORDERSPECEX * pSort;
    if (pBuffer->sortorderspec.wVersion == 0)
    {
        pSort = NULL;
    }
    else 
    {
        pSort = &(pBuffer->sortorderspec);
    }

    CENOTIFYREQUEST* pRequest;
    if (pBuffer->request.dwSize == 0)
    {
        pRequest = NULL;
    }
    else 
    {
        pRequest = &(pBuffer->request);
    }    

    HANDLE hDB = CeOpenDatabaseInSession(hSession, 
                                      &(pBuffer->guid),
                                      &(pBuffer->oidDbase),
                                      pBuffer->wszName,
                                      pSort,
                                      pBuffer->dwFlags,
                                      pRequest);
    if (hDB == INVALID_HANDLE_VALUE )
    {
        *pcbOutput = 0;
        hr = HRESULT_FROM_WIN32(GetLastError());;
    }
    else
    {
        *pcbOutput = sizeof(hDB);
        *ppOutBufferput = (BYTE*)LocalAlloc(LPTR, sizeof(hDB));
        memcpy(*ppOutBufferput, &hDB, sizeof(hDB) );
    }
    return hr;    
}

HRESULT  DevCeGetDatabaseSession
(  
    DWORD cbInput, 
    BYTE* pInput,
    DWORD* pcbOutput, 
    BYTE** ppOutBufferput,
    IRAPIStream* pStream
)
{
    HRESULT hr = S_OK;

    HANDLE *hdb = (HANDLE *)pInput;
    HANDLE hSession = CeGetDatabaseSession(*hdb);

    if (hSession == INVALID_HANDLE_VALUE )
    {
        *pcbOutput = 0;
        hr = HRESULT_FROM_WIN32(GetLastError());;
    }
    else
    {
        *pcbOutput = sizeof(hSession);
        *ppOutBufferput = (BYTE*)LocalAlloc(LPTR, sizeof(hSession));
        memcpy(*ppOutBufferput, &hSession,sizeof(hSession) );
    }
    return hr;

}

HRESULT  DevCeFlushDBVol
(  
    DWORD cbInput, 
    BYTE* pInput,
    DWORD* pcbOutput, 
    BYTE** ppOutBufferput,
    IRAPIStream* pStream
)
{
    HRESULT hr = S_OK;
    PCEGUID pGuid;
    if (cbInput == 0)
    {
        pGuid = NULL;
    }
    else 
    {
        pGuid = (PCEGUID)pInput;
    }

    if (!CeFlushDBVol(pGuid)) 
    {
        hr = HRESULT_FROM_WIN32(GetLastError());;    
    }
    *pcbOutput = 0;
    return hr;
}

HRESULT  DevCeWriteRecordProps
(  
    DWORD cbInput, 
    BYTE* pInput,
    DWORD* pcbOutput, 
    BYTE** ppOutBufferput,
    IRAPIStream* pStream
)
{
    HRESULT hr = S_OK;

    HANDLE hDatabase; 
    CEOID oidRecord;
    WORD cPropID;
    DWORD dwVarSize;
    DWORD cbWritten = 0;

    memcpy(&hDatabase, pInput, sizeof(hDatabase));
    cbWritten += sizeof(hDatabase);
    memcpy(&oidRecord, pInput + cbWritten, sizeof(oidRecord));
    cbWritten += sizeof(oidRecord);
    memcpy(&cPropID, pInput + cbWritten, sizeof(cPropID));
    cbWritten += sizeof(cPropID);
    memcpy(&dwVarSize, pInput + cbWritten, sizeof(dwVarSize)); //buffer size
    cbWritten += sizeof(dwVarSize);

    CEPROPVAL* prgPropVal = (CEPROPVAL*) LocalAlloc( LPTR, dwVarSize);
    memcpy(prgPropVal, pInput + cbWritten, dwVarSize);

    //shift the pointer in the CEPROPVAL from internal offset to actual position
    for (int i = 0; i < cPropID; i++)
    {
        switch (TypeFromPropID(prgPropVal[i].propid))
        {
            case CEVT_LPWSTR:
                prgPropVal[i].val.lpwstr = (LPWSTR)((DWORD)prgPropVal[i].val.lpwstr + (DWORD)prgPropVal);
                break;
            case CEVT_BLOB:
                prgPropVal[i].val.blob.lpb = (LPBYTE)( (DWORD)prgPropVal[i].val.blob.lpb + (DWORD)prgPropVal);
                break;
            default:
                break;
        }
    }
    
    CEOID * poid = new CEOID;
    if (!(*poid = CeWriteRecordProps(hDatabase, 
                                    oidRecord, 
                                    cPropID, 
                                    prgPropVal)))
    {
        *pcbOutput = 0;
        delete poid;
        hr = HRESULT_FROM_WIN32(GetLastError());;
    }
    else
    {                                                                                                           
        *pcbOutput = sizeof(*poid);
        *ppOutBufferput  = (BYTE *) poid;
    }
    LocalFree(prgPropVal);
    return hr;
}

HRESULT  DevCeChangeDatabaseLCID
(  
    DWORD cbInput, 
    BYTE* pInput,
    DWORD* pcbOutput, 
    BYTE** ppOutBufferput,
    IRAPIStream* pStream
)
{
    HRESULT hr = S_OK;
    
    PCEGUID pGuid = (PCEGUID)pInput;
    DWORD lcid;
    memcpy(&lcid, pInput + sizeof(*pGuid), sizeof(lcid));

    CeChangeDatabaseLCID( pGuid, lcid);
    hr = HRESULT_FROM_WIN32(GetLastError());;
    *pcbOutput = 0;
    return hr;
}

HRESULT  DevCeSeekDatabaseEx
(  
    DWORD cbInput, 
    BYTE* pInput,
    DWORD* pcbOutput, 
    BYTE** ppOutBufferput,
    IRAPIStream* pStream
)
{
    HRESULT hr = S_OK;
    INSEEKEB *pBuffer = (INSEEKEB *)pInput;
    DWORD index;
    CEOID oid = CeSeekDatabaseEx(pBuffer->hDatabase, 
                                pBuffer->dwSeekType, 
                                pBuffer->dwValue, 
                                pBuffer->wNumVals, 
                                &index );

    if (oid)
    {
        *pcbOutput = sizeof(index) + sizeof(oid);
        *ppOutBufferput = (BYTE*)LocalAlloc(LPTR, sizeof(index) + sizeof(oid));
        memcpy(*ppOutBufferput, &oid, sizeof(oid));
        memcpy((*ppOutBufferput) + sizeof(oid), &index, sizeof(index));         
    }
    else
    {
        *pcbOutput = 0;
        hr = HRESULT_FROM_WIN32(GetLastError());;
    }
    return hr;
}


HRESULT DevCeDeleteDatabaseEx
(  
    DWORD cbInput, 
    BYTE* pInput,
    DWORD* pcbOutput, 
    BYTE** ppOutBufferput,
    IRAPIStream* pStream
)
{
    HRESULT hr = S_OK;
    PCEGUID pGuid = (PCEGUID)pInput;
    CEOID oid;
    memcpy(&oid, pInput + sizeof(*pGuid), sizeof(oid));
    
    if (!CeDeleteDatabaseEx(pGuid, oid))
    {
        hr = HRESULT_FROM_WIN32(GetLastError());;
    }
    *pcbOutput = 0;
    return hr;
}

HRESULT  DevCeUnmountDBVol
(  
    DWORD cbInput, 
    BYTE* pInput,
    DWORD* pcbOutput, 
    BYTE** ppOutBufferput,
    IRAPIStream* pStream
)
{
    HRESULT hr = S_OK;
    PCEGUID pGuid = (PCEGUID)pInput;
    if (!CeUnmountDBVol(pGuid))
    {
        hr = HRESULT_FROM_WIN32(GetLastError());;
    }
    *pcbOutput = 0;
    return hr;
}

HRESULT  DevCeEnumDBVolumes
(  
    DWORD cbInput, 
    BYTE* pInput,
    DWORD* pcbOutput, 
    BYTE** ppOutBufferput,
    IRAPIStream* pStream
)
{
    HRESULT hr = S_OK;
    DWORD cchMaxName;
    CEGUID *pGuid = (CEGUID *)pInput;
    memcpy(&cchMaxName, pInput + sizeof(*pGuid), sizeof(cchMaxName));
    WCHAR *pwszName = (WCHAR *)LocalAlloc(LPTR, sizeof(WCHAR) * cchMaxName);

    if (CeEnumDBVolumes(pGuid, pwszName, cchMaxName))
    {
        *pcbOutput = sizeof(*pGuid)+(wcslen(pwszName) + 1) * sizeof(WCHAR);
        *ppOutBufferput = (BYTE*)LocalAlloc(LPTR, *pcbOutput);
        memcpy(*ppOutBufferput, pGuid, sizeof(*pGuid));
        memcpy(*ppOutBufferput + sizeof(*pGuid), pwszName , (wcslen(pwszName) + 1) * sizeof(WCHAR));
    }
    else
    {
        *pcbOutput = 0;
        hr = HRESULT_FROM_WIN32(GetLastError());;
    }
    LocalFree(pwszName);
    return hr;
}

HRESULT  DevCeReadRecordPropsEx
(  
    DWORD cbInput, 
    BYTE* pInput,
    DWORD* pcbOutput, 
    BYTE** ppOutBufferput,
    IRAPIStream* pStream
)
{
    HRESULT hr = S_OK;
    INSEEKEB *pBuffer = (INSEEKEB *)pInput;
    WORD cPropID = pBuffer->wNumVals;
    DWORD cbBuffer = 0; //do not use pBuffer->dwValue
    CEPROPID* prgPropID;
    if (cPropID>0)
    {
        prgPropID = (CEPROPID*)(pInput + sizeof(*pBuffer));
    }
    else 
    {
        prgPropID = NULL;
    }
    
    CEPROPVAL* prgPropVal = NULL;

    CEOID oid = CeReadRecordPropsEx(pBuffer->hDatabase, 
                                  CEDB_ALLOWREALLOC, //do not use pBuffer->dwSeekType
                                  &cPropID, 
                                  prgPropID, 
                                  (LPBYTE *)&prgPropVal,
                                  &cbBuffer, 
                                  NULL);
        
    //pack the return data
    DWORD dwVarySize = 0;
    if (oid)
    {
        *pcbOutput = sizeof(oid) + sizeof(cPropID) + cbBuffer;
        *ppOutBufferput = (BYTE*)LocalAlloc(LPTR, *pcbOutput);
        memcpy(*ppOutBufferput, &oid, sizeof(oid));
        memcpy(*ppOutBufferput + sizeof(oid), &cPropID, sizeof(cPropID));

        //shift the pointer position for string and blob property to offset        
        for(int i = 0; i < cPropID; i++)
        {
            switch(TypeFromPropID(prgPropVal[i].propid))
            {
                case CEVT_LPWSTR:
                    prgPropVal[i].val.lpwstr = (LPWSTR)((DWORD)prgPropVal[i].val.lpwstr - (DWORD)prgPropVal);
                    break;
                case CEVT_BLOB:
                    prgPropVal[i].val.blob.lpb = (LPBYTE)( (DWORD)prgPropVal[i].val.blob.lpb - (DWORD)prgPropVal);
                    break;
                default:
                    break;
            }
        }
        memcpy((*ppOutBufferput) + sizeof(CEOID) + sizeof(WORD), prgPropVal, cbBuffer );
    }
    else
    {
        *pcbOutput = 0;
        hr = HRESULT_FROM_WIN32(GetLastError());;
    }
    LocalFree(prgPropVal);
    LocalFree(prgPropID);
    return hr;
}

HRESULT  DevCeAddDatabaseProps
(  
    DWORD cbInput, 
    BYTE* pInput,
    DWORD* pcbOutput, 
    BYTE** ppOutBufferput,
    IRAPIStream* pStream
)
{
    HRESULT hr = S_OK;

    INADDDBPROPS *pBuffer = (INADDDBPROPS *)pInput;  
    CEPROPSPEC* prgProps;
    if (pBuffer->prgProps)
    {
        prgProps = (CEPROPSPEC*)(pInput + sizeof(*pBuffer));
    }

    for (DWORD i = 0; i < pBuffer->cProps; i++)
    {
        if (prgProps[i].pwszPropName)
        {
            BYTE *pIndex =  pInput + 
                            sizeof(*pBuffer) + 
                            sizeof(CEPROPSPEC) * pBuffer->cProps + 
                            CEDB_MAXDBASENAMELEN * sizeof(WCHAR) * i;
            prgProps[i].pwszPropName = (LPWSTR)pIndex;
        }
    }

    if (!CeAddDatabaseProps(&pBuffer->guid, pBuffer->oidDbase, pBuffer->cProps, prgProps))
    {
        hr = HRESULT_FROM_WIN32(GetLastError());;
    }
    *pcbOutput = 0;
    return hr;
}

HRESULT  DevCeDeleteRecord
(  
    DWORD cbInput, 
    BYTE* pInput,
    DWORD* pcbOutput, 
    BYTE** ppOutBufferput,
    IRAPIStream* pStream
)
{
    HRESULT hr = S_OK;
    HANDLE hDatabase;
    CEOID oidRecord;

    memcpy(&hDatabase, pInput, sizeof(hDatabase));
    memcpy(&oidRecord, pInput + sizeof(hDatabase), sizeof(oidRecord));

    if (!CeDeleteRecord(hDatabase, oidRecord))
    {
        hr = HRESULT_FROM_WIN32(GetLastError());;
    }
    *pcbOutput = 0;
    return hr;
}

HRESULT  DevCeFindFirstDatabaseEx
(  
    DWORD cbInput, 
    BYTE* pInput,
    DWORD* pcbOutput, 
    BYTE** ppOutBufferput,
    IRAPIStream* pStream
)
{
    HRESULT hr = S_OK;
    
    CEGUID Guid;
    DWORD dwDbaseType;
    
    memcpy(&Guid, pInput, sizeof(Guid));
    memcpy(&dwDbaseType, pInput + sizeof(Guid), sizeof(dwDbaseType));

    HANDLE * hDB = new HANDLE ;
    *hDB = CeFindFirstDatabaseEx(&Guid, dwDbaseType);

    if (*hDB == INVALID_HANDLE_VALUE )
    {
        *pcbOutput = 0;
        delete hDB;
        hr = HRESULT_FROM_WIN32(GetLastError());;
    }
    else
    {
        *pcbOutput = sizeof(*hDB);
        *ppOutBufferput = (BYTE*)hDB;
    }
    return hr;
}

HRESULT  DevCeFindNextDatabaseEx
(  
    DWORD cbInput, 
    BYTE* pInput,
    DWORD* pcbOutput, 
    BYTE** ppOutBufferput,
    IRAPIStream* pStream
)
{
    HRESULT hr = S_OK;
    HANDLE hEnum;
    CEGUID Guid;
    PCEGUID pGuid;
    
    memcpy(&hEnum, pInput, sizeof(hEnum));
    memcpy(&Guid, pInput + sizeof(hEnum), sizeof(Guid));

    if((Guid.Data1 == 0) &&
       (Guid.Data2 == 0) &&
       (Guid.Data3 == 0) &&
       (Guid.Data4 == 0))
    {
        pGuid = NULL;
    }
    else
    {
        pGuid = &Guid;
    }

    CEOID * poid = (CEOID *)LocalAlloc(LPTR, sizeof(*poid));

    if (!(*poid = CeFindNextDatabaseEx(hEnum, pGuid)))
    {
        *pcbOutput = 0;
        LocalFree(poid);
        hr = HRESULT_FROM_WIN32(GetLastError());;
    }
    else
    {                   
        *pcbOutput = sizeof(*poid);
        *ppOutBufferput = (BYTE *) poid;
    }
    return hr;
}

HRESULT  DevCeGetDatabaseProps
(  
    DWORD cbInput, 
    BYTE* pInput,
    DWORD* pcbOutput, 
    BYTE** ppOutBufferput,
    IRAPIStream* pStream
)
{
    INGETDBPROPS *pBuffer = (INGETDBPROPS *)pInput;
    HRESULT hr = S_OK;
    HANDLE hDatabase = pBuffer->hDatabase;
    WORD cPropID = pBuffer->cPropID;
    CEPROPID* prgPropID;
    CEPROPSPEC* prgProps;

    if (pBuffer->prgPropID)
    {
        prgPropID = (CEPROPID*)((DWORD)pInput + sizeof(*pBuffer));
    }
    else
    {
        prgPropID = NULL;
    }

    if (pBuffer->prgProps)
    {
        prgProps = (CEPROPSPEC*) LocalAlloc (LPTR, sizeof(CEPROPSPEC) * pBuffer->cPropID);
        for (int i = 0; i < pBuffer->cPropID; i++)
        {
            prgProps[i].wVersion = CEPROPSPEC_VERSION;
        }
    }
    else 
    {
        prgProps = NULL;
    }

    if (CeGetDatabaseProps(hDatabase, &cPropID, prgPropID, prgProps))
    {//pack the return data
        if(prgProps)
        {
            *pcbOutput = sizeof(cPropID) + sizeof(CEPROPSPEC) * cPropID;
            *ppOutBufferput = (BYTE *) LocalAlloc(LPTR, *pcbOutput);
            memcpy(*ppOutBufferput, &cPropID, sizeof(cPropID));
            memcpy(*ppOutBufferput + sizeof(cPropID), prgProps, sizeof(CEPROPSPEC) * cPropID);
        }
        else
        {
            *pcbOutput = sizeof(cPropID);
            *ppOutBufferput = (BYTE *) LocalAlloc(LPTR, *pcbOutput);
            memcpy(*ppOutBufferput, &cPropID, sizeof(cPropID));
        }
    }
    else
    {
        *pcbOutput = 0;
        hr = HRESULT_FROM_WIN32(GetLastError());;
    }
    LocalFree(prgProps);
    return hr;
}

HRESULT  DevCeRemoveDatabaseProps
(  
    DWORD cbInput, 
    BYTE* pInput,
    DWORD* pcbOutput, 
    BYTE** ppOutBufferput,
    IRAPIStream* pStream
)
{
    HRESULT hr = S_OK;
    PCEGUID pGuid = (PCEGUID)pInput;
    CEOID oidDb;
    DWORD cProps;
    CEPROPID* prgProps;

    memcpy(&oidDb, pInput + sizeof(*pGuid), sizeof(oidDb));
    memcpy(&cProps, pInput + sizeof(*pGuid) + sizeof(oidDb), sizeof(cProps));
    if (cProps > 0)
    {
        prgProps = (CEPROPID*)(pInput + sizeof(*pGuid) + sizeof(oidDb) + sizeof(cProps));
    }
    else 
    {
        prgProps = NULL;
    }

    if (!CeRemoveDatabaseProps(pGuid, oidDb, cProps, prgProps))
    {
        hr = HRESULT_FROM_WIN32(GetLastError());;
    }
    *pcbOutput = 0;
    return hr;
}

HRESULT  DevCeGetDBInformationByHandle
(  
    DWORD cbInput, 
    BYTE* pInput,
    DWORD* pcbOutput, 
    BYTE** ppOutBufferput,
    IRAPIStream* pStream
)
{
    HRESULT hr = S_OK;
    BY_HANDLE_DB_INFORMATION * DBInfo = new BY_HANDLE_DB_INFORMATION;
    DBInfo->wVersion = BY_HANDLE_DB_INFORMATION_VERSION;
    HANDLE hDbase;
    memcpy(&hDbase, pInput, sizeof(hDbase));
    if (CeGetDBInformationByHandle(hDbase, DBInfo))
    {
        *pcbOutput = sizeof(*DBInfo);
        *ppOutBufferput = (BYTE *)DBInfo;
    }
    else
    {
        *pcbOutput = 0;
        hr = HRESULT_FROM_WIN32(GetLastError());;
        delete DBInfo; 
    }
    return hr;
}

HRESULT  DevCeSetDatabaseInfo
(  
    DWORD cbInput, 
    BYTE* pInput,
    DWORD* pcbOutput, 
    BYTE** ppOutBufferput,
    IRAPIStream* pStream
)
{
    HRESULT hr = S_OK;
    CEOID oidDbase;
    memcpy(&oidDbase, pInput, sizeof(oidDbase));
    CEDBASEINFO* pNewInfo = (CEDBASEINFO*)(pInput + sizeof(oidDbase));

    if (!CeSetDatabaseInfo(oidDbase, pNewInfo))
    {
        hr = HRESULT_FROM_WIN32(GetLastError());;
    }
    *pcbOutput = 0;
    return hr;
}

HRESULT  DevCeFreeNotification
(  
    DWORD cbInput, 
    BYTE* pInput,
    DWORD* pcbOutput, 
    BYTE** ppOutBufferput,
    IRAPIStream* pStream
)
{
    HRESULT hr = S_OK;
    CENOTIFYREQUEST* pRequest = (CENOTIFYREQUEST*) pInput;
    CENOTIFICATION* pNotification = (CENOTIFICATION*) (pInput + sizeof(*pRequest));

    if (!CeFreeNotification(pRequest, pNotification))
    {
        hr = HRESULT_FROM_WIN32(GetLastError());;
    }
    *pcbOutput = 0;
    return hr;
}

HRESULT  DevCeSetSessionOption
(  
    DWORD cbInput, 
    BYTE* pInput,
    DWORD* pcbOutput, 
    BYTE** ppOutBufferput,
    IRAPIStream* pStream
)
{
    HRESULT hr = S_OK;
    HANDLE hSession;
    ULONG ulOptionId;
    DWORD dwValue;

    memcpy(&hSession, pInput, sizeof(hSession));
    memcpy(&ulOptionId, pInput + sizeof(hSession), sizeof(ulOptionId));
    memcpy(&dwValue, pInput + sizeof(hSession) + sizeof(ulOptionId), sizeof(dwValue));

    if (!CeSetSessionOption(hSession, ulOptionId, dwValue))
    {
        hr = HRESULT_FROM_WIN32(GetLastError());;
    }
    *pcbOutput = 0;
    return hr;
}

HRESULT  DevCeBeginTransaction
(  
    DWORD cbInput, 
    BYTE* pInput,
    DWORD* pcbOutput, 
    BYTE** ppOutBufferput,
    IRAPIStream* pStream
)
{
    HRESULT hr = S_OK;
    HANDLE hSession;
    CEDBISOLATIONLEVEL isoLevel;

    memcpy(&hSession, pInput, sizeof(hSession));
    memcpy(&isoLevel, pInput + sizeof(hSession), sizeof(isoLevel));

    if (!CeBeginTransaction(hSession, isoLevel))
    {
        hr = HRESULT_FROM_WIN32(GetLastError());;
    }
    *pcbOutput = 0;
    return hr;
}

HRESULT  DevCeEndTransaction
(  
    DWORD cbInput, 
    BYTE* pInput,
    DWORD* pcbOutput, 
    BYTE** ppOutBufferput,
    IRAPIStream* pStream
)
{
    HRESULT hr = S_OK;
    HANDLE hSession;
    BOOL fCommit;

    memcpy(&hSession, pInput, sizeof(hSession));
    memcpy(&fCommit, pInput + sizeof(hSession), sizeof(fCommit));

    if (!CeEndTransaction(hSession, fCommit))
    {
        hr = HRESULT_FROM_WIN32(GetLastError());;
    }
    *pcbOutput = 0;
    return hr;
}

HRESULT  DevCeOpenStream
(  
    DWORD cbInput, 
    BYTE* pInput,
    DWORD* pcbOutput, 
    BYTE** ppOutBufferput,
    IRAPIStream* pStream
)
{
    HRESULT hr = S_OK;
    HANDLE hDatabase;
    CEPROPID propid;
    DWORD dwMode;

    memcpy(&hDatabase, pInput, sizeof(hDatabase));
    memcpy(&propid, pInput + sizeof(hDatabase),  sizeof(propid));
    memcpy(&dwMode, pInput + sizeof(hDatabase) + sizeof(propid),  sizeof(dwMode));

    HANDLE * hDB = (HANDLE *)LocalAlloc(LPTR, sizeof(HANDLE));
    *hDB = CeOpenStream(hDatabase, propid, dwMode);

    if (*hDB == INVALID_HANDLE_VALUE )
    {
        *pcbOutput = 0;
        delete hDB;
        hr = HRESULT_FROM_WIN32(GetLastError());;
    }
    else
    {
        *pcbOutput = sizeof(*hDB);
        *ppOutBufferput = (BYTE*)hDB;
    }
    return hr;
}

HRESULT  DevCeStreamRead
(  
    DWORD cbInput, 
    BYTE* pInput,
    DWORD* pcbOutput, 
    BYTE** ppOutBufferput,
    IRAPIStream* pStream
)
{
    HRESULT hr = S_OK;
    HANDLE hStream;
    DWORD cbRead;

    memcpy(&hStream, pInput, sizeof(hStream));
    memcpy(&cbRead, pInput + sizeof(hStream),  sizeof(cbRead));

    LPBYTE lprgbBuffer = (LPBYTE)LocalAlloc(LPTR, cbRead);
    DWORD cbActualRead;

    if (CeStreamRead(hStream, lprgbBuffer, cbRead, &cbActualRead))
    {
        *pcbOutput = sizeof(cbActualRead) + cbActualRead;
        *ppOutBufferput = (BYTE *)LocalAlloc(LPTR, *pcbOutput);
        memcpy(*ppOutBufferput, &cbActualRead, sizeof(cbActualRead));
        memcpy(*ppOutBufferput + sizeof(cbActualRead), lprgbBuffer, cbActualRead);
        
    }
    else
    {
        *pcbOutput = 0;
        hr = HRESULT_FROM_WIN32(GetLastError());;
    }
    LocalFree(lprgbBuffer);
    return hr;
}

HRESULT  DecCeStreamSaveChanges
(  
    DWORD cbInput, 
    BYTE* pInput,
    DWORD* pcbOutput, 
    BYTE** ppOutBufferput,
    IRAPIStream* pStream
)
{
    HRESULT hr = S_OK;
    HANDLE *hStream = (HANDLE *)pInput;
    if(!CeStreamSaveChanges(*hStream))
    {
        hr = HRESULT_FROM_WIN32(GetLastError());;
    }
    *pcbOutput = 0;
    return hr;
}

HRESULT  DevCeStreamSetSize
(  
    DWORD cbInput, 
    BYTE* pInput,
    DWORD* pcbOutput, 
    BYTE** ppOutBufferput,
    IRAPIStream* pStream
)
{
    HRESULT hr = S_OK;
    HANDLE hStream;
    DWORD cbSize;

    memcpy(&hStream, pInput, sizeof(hStream));
    memcpy(&cbSize, pInput + sizeof(hStream),  sizeof(cbSize));

    if(!CeStreamSetSize(hStream, cbSize))
    {
        hr = HRESULT_FROM_WIN32(GetLastError());;
    }
    *pcbOutput = 0;
    return hr;
}

HRESULT  DevCeStreamSeek
(  
    DWORD cbInput, 
    BYTE* pInput,
    DWORD* pcbOutput, 
    BYTE** ppOutBufferput,
    IRAPIStream* pStream
)
{
    HRESULT hr = S_OK;
    HANDLE hStream;
    DWORD cbMove;
    DWORD dwOrigin;
    DWORD cbNewOffset;

    memcpy(&hStream, pInput, sizeof(hStream));
    memcpy(&cbMove, pInput + sizeof(hStream),  sizeof(cbMove));
    memcpy(&dwOrigin, pInput + sizeof(hStream) + sizeof(cbMove),  sizeof(dwOrigin));

    if(!CeStreamSeek(hStream, cbMove, dwOrigin, &cbNewOffset))
    {
        hr = HRESULT_FROM_WIN32(GetLastError());;
        *pcbOutput = 0;
    }
    else
    {
        *pcbOutput = sizeof(DWORD);
        *ppOutBufferput = (BYTE *)LocalAlloc(LPTR, *pcbOutput);
        memcpy(*ppOutBufferput, &cbNewOffset, sizeof(cbNewOffset));
    }
    return hr;
}

HRESULT  DevCeStreamWrite
(  
    DWORD cbInput, 
    BYTE* pInput,
    DWORD* pcbOutput, 
    BYTE** ppOutBufferput,
    IRAPIStream* pStream
)
{
    HRESULT hr = S_OK;
    HANDLE hStream;
    LPBYTE lprgbBuffer;
    DWORD cbWrite;
    DWORD cbWritten;

    memcpy(&hStream, pInput, sizeof(hStream));
    memcpy(&cbWrite, pInput + sizeof(hStream),  sizeof(cbWrite));
    lprgbBuffer = (LPBYTE)(pInput + sizeof(hStream) + sizeof(cbWrite));

    if(!CeStreamWrite(hStream, lprgbBuffer, cbWrite, &cbWritten))
    {
        hr = HRESULT_FROM_WIN32(GetLastError());;
        *pcbOutput = 0;
    }
    else
    {
        *pcbOutput = sizeof(cbWritten);
        *ppOutBufferput = (BYTE *)LocalAlloc(LPTR, *pcbOutput);
        memcpy(*ppOutBufferput, &cbWritten, sizeof(cbWritten));
    }
    return hr;
}