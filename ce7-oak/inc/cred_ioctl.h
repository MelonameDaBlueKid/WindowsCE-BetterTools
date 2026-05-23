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
#ifndef _CRED_IOCTL_H

#define _CRED_IOCTL_H
#include <alignment.hxx>
#pragma warning( push )
#pragma warning( disable : 4239)
#include <pc_marshaler.hxx>
#pragma warning( pop )

#define IOCTL_CREDSVC_PSL_MARSHAL       6678

#define CREDSVC_HANDLE_NAME             L"CRD0:"

#define IOCTL_CREDSVC_BASE              0

#define IOCTL_CREDSVC(x)                ((x) + IOCTL_CREDSVC_BASE)

#define IOCTL_CREDSVC_WRITE             IOCTL_CREDSVC(2)
#define IOCTL_CREDSVC_READ              IOCTL_CREDSVC(3)
#define IOCTL_CREDSVC_DELETE            IOCTL_CREDSVC(5)
#define IOCTL_CREDSVC_LIST_PROVIDERS    IOCTL_CREDSVC(6)
#define IOCTL_CREDSVC_DELETE_ALL        IOCTL_CREDSVC(7)
#define IOCTL_CREDSVC_LIST_CREDS        IOCTL_CREDSVC(8)

typedef struct {
    PCRED pCred;
    DWORD dwFlags;
}I_CRED_WRITE, *PI_CRED_WRITE;

typedef struct {
    PCWCHAR     wszTarget;
    DWORD       dwTargetLen;
    DWORD       dwType;
    DWORD       dwFlags;
    PCRED       pCred;
    PDWORD      pdwCredSize;
}I_CRED_READ, *PI_CRED_READ;

typedef struct {
    PCWCHAR     wszTarget;
    DWORD       dwTargetLen;
    DWORD       dwType;
    DWORD       dwFlags;
}I_CRED_DELETE, *PI_CRED_DELETE;

template<>
class ce::pc_marshaler<CRED*>
{
    typedef pc_marshaler<CRED*> my_T;
    public:
    pc_marshaler(CRED* pCred)
        :m_pCred(pCred)
        , m_wszUser(m_pCred?m_pCred->wszUser: NULL)
        , m_wszTarget(m_pCred?m_pCred->wszTarget: NULL)
        , m_Blob(psl_buffer(m_pCred?m_pCred->pBlob:NULL,m_pCred?m_pCred->dwBlobSize:0))
    { }

    CRED* unmarshal(Stream& stream) const 
    {
        if(!m_pCred) return NULL;
        CRED* pUnmarshaled = stream.ptr_from_offset(m_pCred, sizeof(*m_pCred));

        pUnmarshaled->wszUser = const_cast<WCHAR*>(m_wszUser.unmarshal(stream));
        pUnmarshaled->wszTarget = const_cast<WCHAR*>(m_wszTarget.unmarshal(stream));

        psl_buffer_wrapper<BYTE*> blob =  m_Blob.unmarshal(stream);
        pUnmarshaled->pBlob = blob.buffer();
        pUnmarshaled->dwBlobSize = blob.count();
        return pUnmarshaled;
    }

    DWORD marshal (AppendStream& stream, const my_T & rhs)
    {
        m_pCred = rhs.m_pCred;

        if (!m_pCred)
        {
            return NO_ERROR;
        }

        DWORD ret = stream.Append(m_pCred, &m_pCred);
        if (ret != NO_ERROR)
        {
            assert(false);
            return ret;
        }

        ret = m_wszUser.marshal(stream,rhs.m_wszUser);
        if (ret != NO_ERROR)
        {
            assert(false);
            return ret;
        }
        ret = m_wszTarget.marshal(stream,rhs.m_wszTarget);
        if (ret != NO_ERROR)
        {
            assert(false);
            return ret;
        }
        ret = m_Blob.marshal(stream,rhs.m_Blob);
        if (ret != NO_ERROR)
        {
            assert(false);
            return ret;
        }

        return NO_ERROR;
    }

    private:
    PCRED m_pCred;
    ce::pc_marshaler<LPCWSTR> m_wszUser;
    ce::pc_marshaler<LPCWSTR> m_wszTarget;
    ce::pc_marshaler<psl_buffer_wrapper<BYTE*> > m_Blob;
    pc_marshaler(pc_marshaler&);
};


// CRED_OUT is a variable_sized_type<CRED> that is expected to have the
// following format when the PSL exits: 
// a cred, and all embedded pointers pointing to memory within the psl_buffer_wrapper. 
// e.g.


//          |<--------------------psl_buffer_wrapper._buffer------------------->|
//          |                             |                 |                   |
// #bytes   |        <-sizeof(CRED)->     | <- dwUserLen -> |  <- dwBlobSize -> |
// memory   |--wszUser----....--pBlob-----|-----------------|-------------------|
//              +----------------|---------^                 ^
//                               +---------------------------|

// copy_out_cred::copy_arg_out copies the server version of the cred, to 
// the client copy, and then fixups the embedded pointers.

class CRED_OUT:public ce::variable_sized_type<CRED> {
    public:
    CRED_OUT(CRED* b, DWORD c):
        ce::variable_sized_type<CRED>(b,c)
    { }
    CRED_OUT(ce::psl_buffer_wrapper<LPBYTE> &b):
        ce::variable_sized_type<CRED>(b)
    {}
};


// shared between cred_ioctl, and credsvc.
inline DWORD UnMarshallCred(PCRED pCred, DWORD cbCred){
        const UINT_PTR t = (UINT_PTR)pCred;

        if(NULL == pCred){
                assert(0);
                return ERROR_INVALID_PARAMETER;
        }

        const DWORD cbMaxOfStrings = (DWORD)max(pCred->wszUser + pCred->dwUserLen,pCred->wszTarget + pCred->dwUserLen); 
        const DWORD cbForUnmarshal = max( (DWORD)(pCred->pBlob + pCred->dwBlobSize),cbMaxOfStrings);
        if (cbForUnmarshal > cbCred)
        {
            return ERROR_INVALID_PARAMETER;
        }

        if(pCred->pBlob != NULL)
        {
            pCred->pBlob += (UINT_PTR)t;
        }

        pCred->wszTarget = (PWCHAR) ( (PBYTE)pCred->wszTarget + t);
        pCred->wszUser = (PWCHAR) ( (PBYTE)pCred->wszUser + t);

        if (pCred->dwTargetLen ) 
        {
            pCred->wszTarget[pCred->dwTargetLen-1]=0;
        }

        if (pCred->dwUserLen) 
        {
            pCred->wszUser[pCred->dwUserLen-1]=0;
        }

        return ERROR_SUCCESS;
}

template <> 
class ce::pc_marshaler<CRED_OUT>: public pc_marshaler< variable_sized_type<CRED> > 
{
    typedef pc_marshaler<ce::variable_sized_type <CRED> > my_base;
    public:
    pc_marshaler(CRED_OUT x):
        my_base (x)
    { }

    DWORD write_back(const my_base::buffer_wrapper& rhs)
    { 
        // write back the stream.
        DWORD ret = my_base::write_back(rhs);
        if (ret != NO_ERROR)
        {
            return ret;
        }

        if(!data.buffer())
        {
            return NO_ERROR;
        }

        const bool isBufferSmallerThanCred = (data.count() < sizeof(CRED));
        if (isBufferSmallerThanCred)
        {
            // UnMarshallCred will fail if the buffer is too small.  However,
            // since we always call write_back,even if we fail with
            // ERROR_MORE_DATA, we expect this condition, and don't want to
            // stop other write_backs from occuring.
            return NO_ERROR;
        }

        PCRED dst = reinterpret_cast<PCRED>(data.buffer());
        ret = UnMarshallCred(dst,data.count());
        if (ret != NO_ERROR)
        {
            return retInvalidCred(ret,dst);
        }

        return NO_ERROR;
    }

    private:

    DWORD retInvalidCred(DWORD ret, CRED* const dst)
    {
        const CRED null = {0};
        *dst = null;
        return ret;
    }
};


#endif 

