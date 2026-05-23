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

#ifndef _MARSHAL_HPP_INCLUDED_
#define _MARSHAL_HPP_INCLUDED_


// This class is a wrapper for CeOpenCallerBuffer / CeCloseCallerBuffer and
// CeAllocAsynchronousBuffer / CeFreeAsynchronousBuffer.
// You should only use it with embedded pointers that have NOT already been
// access-checked or marshalled by the kernel.  To duplicate a buffer that has
// already been marshalled, use DuplicatedBuffer_t.  To gain asynchronous
// access to a buffer that has already been marshalled, use AsynchronousBuffer_t.
class MarshalledBuffer_t {
private:
    PVOID  m_pLocalAsync;
    PVOID  m_pLocalSyncMarshalled;
    PVOID  m_pCallerUnmarshalled;
    DWORD  m_cbSize;
    DWORD  m_ArgumentDescriptor;
    
    void Reset() {
        m_pLocalSyncMarshalled = NULL;
        m_pLocalAsync = NULL;
        m_cbSize = 0;
    }

public:

    //
    // Access-checks and marshals a buffer pointer from the source process, so
    // that it may be accessed by the current process.  Exposes the marshalled
    // pointer via the ptr() accessor.  Any allocated resources related to the
    // marshalling are freed only by a subsequent call to Unmarshal(), or by the
    // destructor.
    //
    // Typically, you would either use the default constructor plus Marshal()
    // to marshal the buffer, or you would use the marshalling constructor to
    // accomplish the same task.  Use the former method if you require an
    // HRESULT.  Similarly, you can allow the destructor to release marshalling
    // resources, or use Unmarshal().  If an HRESULT is required, use the 
    // Unmarshal function.
    //

    MarshalledBuffer_t() {
        Reset();
    }

    ~MarshalledBuffer_t() {
        Unmarshal();
    }

    // Please see the description of CeOpenCallerBuffer and
    // CeAllocAsynchronousBuffer for more information about the operation of
    // this function.
    //
    // If marshalling fails, ptr() will return NULL and size() will return zero.
    // Otherwise the marshalled buffer will be accessible via ptr() and size().
    MarshalledBuffer_t(
        PVOID pSrcUnmarshalled,
        DWORD cbSrc,
        DWORD ArgumentDescriptor,
        BOOL  ForceDuplicate = TRUE,
        BOOL  Asynchronous = FALSE
        )
    {
        Reset();
        Marshal(pSrcUnmarshalled, cbSrc, ArgumentDescriptor, ForceDuplicate,
                Asynchronous);
    }

    // Takes a const pSrcUnmarshalled, can only be used with ARG_I_* types
    MarshalledBuffer_t(
        PCVOID pSrcUnmarshalled,
        DWORD cbSrc,
        DWORD ArgumentDescriptor,
        BOOL  ForceDuplicate = TRUE,
        BOOL  Asynchronous = FALSE
        )
    {
        Reset();
        Marshal(pSrcUnmarshalled, cbSrc, ArgumentDescriptor, ForceDuplicate,
                Asynchronous);
    }

    
    // Please see the description of CeOpenCallerBuffer and
    // CeAllocAsynchronousBuffer for more information about the operation of
    // this function.
    //
    // Once a MarshalledBuffer is marshalled (using the marshalling constructor
    // or the Marshal() method, it cannot be re-used by calling Marshal(), until
    // after Unmarshal() is called.  An attempt to do so will return
    // ERROR_ALREADY_EXISTS.
    //
    // If Marshal() fails, ptr() will return NULL and size() will return zero.
    // Otherwise the marshalled buffer will be accessible via ptr() and size().
    HRESULT
    Marshal(
        PVOID pSrcUnmarshalled,
        DWORD cbSrc,
        DWORD ArgumentDescriptor,
        BOOL  ForceDuplicate = TRUE,
        BOOL  Asynchronous = FALSE
        )
    {
        HRESULT result = HRESULT_FROM_WIN32(ERROR_ALREADY_EXISTS);

        if (!m_pLocalSyncMarshalled) {
            // First do the synchronous marshalling
            result = CeOpenCallerBuffer(&m_pLocalSyncMarshalled,
                                        pSrcUnmarshalled, cbSrc,
                                        ArgumentDescriptor, ForceDuplicate);
            if (SUCCEEDED(result)) {
                // These values will now be required in order to clean up
                m_pLocalAsync = NULL;
                m_pCallerUnmarshalled = pSrcUnmarshalled;
                m_cbSize = cbSrc;
                m_ArgumentDescriptor = ArgumentDescriptor;

                if (Asynchronous) {
                    result = CeAllocAsynchronousBuffer(&m_pLocalAsync,
                                                       m_pLocalSyncMarshalled,
                                                       cbSrc, ArgumentDescriptor);
                    if (!SUCCEEDED(result)) {
                        Unmarshal();
                    }
                }
            }
        }
        return result;
    }

    // Takes a const pSrcUnmarshalled, can only be used with ARG_I_* types
    HRESULT
    Marshal(
        PCVOID pSrcUnmarshalled,
        DWORD cbSrc,
        DWORD ArgumentDescriptor,
        BOOL  ForceDuplicate = TRUE,
        BOOL  Asynchronous = FALSE
        )
    {
        if (ArgumentDescriptor & ARG_O_BIT)
        {
            // Failure here means you are trying to marshal a const pointer as
            // an output parameter.

            return E_ACCESSDENIED;
        }

        return Marshal(const_cast<PVOID>(pSrcUnmarshalled),cbSrc,ArgumentDescriptor,ForceDuplicate,Asynchronous);
    }

    
    // Please see the description of CeFlushAsynchronousBuffer for more
    // information about the operation of this function.
    //
    // If the buffer has already been unmarshalled, or if it is not an
    // asynchronous buffer, Flush will fail with ERROR_INVALID_PARAMETER.
    HRESULT
    Flush()
    {
        HRESULT result = HRESULT_FROM_WIN32(ERROR_INVALID_PARAMETER);
        if (m_pLocalSyncMarshalled) {
            if (m_pLocalAsync) {
                result = CeFlushAsynchronousBuffer(m_pLocalAsync,
                                                   m_pLocalSyncMarshalled,
                                                   m_pCallerUnmarshalled,
                                                   m_cbSize, m_ArgumentDescriptor);
            }
        }
        return result;
    }


    // Please see the description of CeCloseCallerBuffer for more information
    // about the operation of this function.
    //
    // If the buffer has already been unmarshalled, Unmarshal will fail with
    // ERROR_ALREADY_EXISTS.
    HRESULT
    Unmarshal()
    {
        HRESULT result = HRESULT_FROM_WIN32(ERROR_ALREADY_EXISTS);

        if (m_pLocalSyncMarshalled) {
            if (m_pLocalAsync) {
                CeFreeAsynchronousBuffer(m_pLocalAsync, m_pLocalSyncMarshalled,
                                         m_cbSize, m_ArgumentDescriptor);
            }

            result = CeCloseCallerBuffer(m_pLocalSyncMarshalled,
                                         m_pCallerUnmarshalled, m_cbSize,
                                         m_ArgumentDescriptor);
            
            Reset();
        }
        return result;
    }

    // Returns a pointer to the marshalled buffer, or NULL if the buffer 
    // has not been marshalled or has already been unmarshalled.
    LPVOID ptr() const {
        if (m_pLocalAsync) {
            return m_pLocalAsync;
        }
        return m_pLocalSyncMarshalled;
    }

    // Returns the size of the marshalled buffer, or zero if the buffer 
    // has not been marshalled or has already been unmarshalled.
    DWORD size() const {
        return m_cbSize;
    }
};



namespace ce {
namespace marshal { 
namespace detail {

#pragma warning(push)
#pragma warning(disable:4512) // assignment operator could not be generated
template <typename  alloc_traits>
class Buffer_t
{
private:
    PVOID  m_pLocal;
    PVOID  m_pCallerMarshalled;
    DWORD  m_cbSize;
    DWORD  m_ArgumentDescriptor;
    const alloc_traits m_Allocator;

    void Reset() {
        m_pLocal = NULL;
        m_pCallerMarshalled = NULL;
        m_cbSize = 0;
    }

public:

    Buffer_t()
    {
        Reset();
    }

    Buffer_t(
        PVOID  pSrcMarshalled,
        DWORD  cbSrc,
        DWORD  ArgumentDescriptor
        )
    {
        Reset();
        Allocate(pSrcMarshalled,cbSrc,ArgumentDescriptor);
    }

    // const version
    Buffer_t(
        PCVOID  pSrcMarshalled,
        DWORD  cbSrc,
        DWORD  ArgumentDescriptor
        )
    {
        Reset();
        Allocate(pSrcMarshalled,cbSrc,ArgumentDescriptor);
    }

    // Returns a pointer to the buffer, or NULL if the buffer has not
    // been allocated.
    LPVOID ptr() const {
        return m_pLocal;
    }

    // Returns the size of the buffer, or zero if the buffer has not
    // been allocated.
    DWORD size() const {
        return m_cbSize;
    }

    virtual ~Buffer_t() {
        Free();
        return;
    }

    HRESULT Free()
    {
        HRESULT result = HRESULT_FROM_WIN32(ERROR_ALREADY_EXISTS);

        if (m_pLocal) {
            result = m_Allocator.free(m_pLocal, 
                    m_pCallerMarshalled, m_cbSize, 
                    m_ArgumentDescriptor);
            Reset();
        }
        return result;

    }

    HRESULT Allocate(
        PVOID  pSrcMarshalled,
        DWORD  cbSrc,
        DWORD  ArgumentDescriptor
        )
    {
        HRESULT result = HRESULT_FROM_WIN32(ERROR_ALREADY_EXISTS);
        if (!m_pLocal) {
            result = m_Allocator.alloc(&m_pLocal, pSrcMarshalled, cbSrc, ArgumentDescriptor);
            if (SUCCEEDED(result)) {
                m_pCallerMarshalled = pSrcMarshalled;
                m_cbSize = cbSrc;
                m_ArgumentDescriptor = ArgumentDescriptor;
            }
        }
        return result;
    }

    HRESULT Allocate(
        PCVOID pSrcMarshalled,
        DWORD  cbSrc,
        DWORD  ArgumentDescriptor
        )
    {
        if (ArgumentDescriptor & ARG_O_BIT) {
            // Failure here means you are trying to marshal a const pointer as
            // an output parameter.
            return E_ACCESSDENIED;
        }

        return Allocate(const_cast<PVOID> (pSrcMarshalled),cbSrc,ArgumentDescriptor);
    }

    HRESULT Flush()
    {
        HRESULT result = HRESULT_FROM_WIN32(ERROR_INVALID_PARAMETER);
        if (m_pLocal) {
            result = m_Allocator.flush(m_pLocal, m_pCallerMarshalled, m_cbSize, 
                                       m_ArgumentDescriptor);
        }
        return result;
    }
};
#pragma warning(pop)

class DuplicateTraits_t
{
public:
    HRESULT alloc(
            PVOID* ppDest,   
            PVOID  pSrc,      
            DWORD  cbSrc,                   
            DWORD  ArgumentDescriptor       
            ) const 
    {
        return CeAllocDuplicateBuffer(ppDest,pSrc,cbSrc,ArgumentDescriptor);
    }

    HRESULT free(
            PVOID  pDest,
            PVOID  pSrc, 
            DWORD  cbSrc,               
            DWORD  ArgumentDescriptor) const 
    {
        return CeFreeDuplicateBuffer(pDest,pSrc,cbSrc,ArgumentDescriptor);
    }

    HRESULT flush(
            PVOID  pDest,
            PVOID  pSrc, 
            DWORD  cbSrc,               
            DWORD  ArgumentDescriptor) const 
    {
        UNREFERENCED_PARAMETER (pDest);
        UNREFERENCED_PARAMETER (pSrc);
        UNREFERENCED_PARAMETER (cbSrc);
        UNREFERENCED_PARAMETER (ArgumentDescriptor);
        
        // Technically we should probably memcpy between src and dest here.
        return HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED);
    }
};


class AsyncTraits_t
{
    public:
    HRESULT alloc(
            PVOID* ppDest,   
            PVOID  pSrc,      
            DWORD  cbSrc,                   
            DWORD  ArgumentDescriptor       
            ) const 
    {
        return CeAllocAsynchronousBuffer(ppDest,pSrc,cbSrc,ArgumentDescriptor);
    }

    HRESULT free(
            PVOID  pDest,
            PVOID  pSrc, 
            DWORD  cbSrc,               
            DWORD  ArgumentDescriptor) const 
    {
        return CeFreeAsynchronousBuffer(pDest,pSrc,cbSrc,ArgumentDescriptor);
    }
    
    HRESULT flush(
            PVOID  pDest,
            PVOID  pSrc, 
            DWORD  cbSrc,               
            DWORD  ArgumentDescriptor) const 
    {
        return CeFlushAsynchronousBuffer(pDest,pSrc,NULL,cbSrc,ArgumentDescriptor);
    }
};

};
};
};


// This class is a wrapper for CeAllocDuplicateBuffer / CeFreeDuplicateBuffer.
// It should only be called with API arguments that have already been
// access-checked and automatically marshalled (if necessary) by the kernel.
// All other duplication can be done by MarshalledBuffer_t.
//
// You can either call the constructor to do the duplication, or use
// the default constructor and then duplicate using the Allocate() method.
// If an HRESULT is required, use Allocate().  Similarly, you can allow the
// destructor to release the duplicate memory, or use the Free() method.  If
// an HRESULT is required, use Free().
//
// If Allocate() fails, ptr() will return NULL and size() will return zero.
// Otherwise the duplicated buffer will be accessible via ptr() and size().
//
// Once a DuplicatedBuffer is allocated (using the constructor or the
// Allocate() method), it cannot be re-used by calling Allocate(), until
// after Free() is called.  An attempt to do so will return
// ERROR_ALREADY_EXISTS.
//
// If the buffer is not currently allocated, Free() will fail with
// ERROR_ALREADY_EXISTS.
//
// Please see the description of CeAllocDuplicateBuffer and
// CeFreeDuplicateBuffer for more information about the operation of
// the Allocate() and Free() methods.
//
// Public methods are:
//      DuplicatedBuffer_t();
//      DuplicatedBuffer_t(PVOID  pSrcMarshalled, DWORD cbSrc, DWORD ArgumentDescriptor);
//      DuplicatedBuffer_t(PCVOID pSrcMarshalled, DWORD cbSrc, DWORD ArgumentDescriptor);
//      ~DuplicatedBuffer_t();
// 
//      HRESULT Free();
//      HRESULT Allocate(PVOID  pSrcMarshalled, DWORD cbSrc, DWORD ArgumentDescriptor);
//      HRESULT Allocate(PCVOID pSrcMarshalled, DWORD cbSrc, DWORD ArgumentDescriptor);
// 
//      LPVOID ptr() const;
//      DWORD size() const;

typedef ce::marshal::detail::Buffer_t<ce::marshal::detail::DuplicateTraits_t> DuplicatedBuffer_t;



// This class is a wrapper for CeAllocAsynchronousBuffer / 
// CeFreeAsynchronousBuffer.  It is meant to be used with pointers
// already access-checked or marshalled by the kernel that require
// asynchronous buffer access.  It should ONLY be used in kernel mode!
// See the description of CeAllocAsynchronousBuffer for information on how to
// access a buffer asynchronously in user mode.
//
// You can either call the constructor to allocate the async buffer, or use 
// the default constructor and then use the Allocate() method.
// If an HRESULT is required, use Allocate().  Similarly, you can allow the
// destructor to release the async buffer, or use the Free() method.  If
// an HRESULT is required, use Free().
//
// If Allocate() fails, ptr() will return NULL and size() will return zero.
// Otherwise the async buffer will be accessible via ptr() and size().
//
// Once an AsynchronousBuffer is allocated (using the constructor or the
// Allocate() method), it cannot be re-used by calling Allocate(), until
// after Free() is called.  An attempt to do so will return
// ERROR_ALREADY_EXISTS.
//
// If the buffer is not currently allocated, Free() will fail with
// ERROR_ALREADY_EXISTS.
//
// Please see the description of CeAllocAsynchronousBuffer and
// CeFreeAsynchronousBuffer for more information about the operation of
// the Allocate() and Free() methods.
//
// Public methods are:
//      AsynchronousBuffer_t();
//      AsynchronousBuffer_t(PVOID  pSrcMarshalled, DWORD cbSrc, DWORD ArgumentDescriptor);
//      AsynchronousBuffer_t(PCVOID pSrcMarshalled, DWORD cbSrc, DWORD ArgumentDescriptor);
//      ~AsynchronousBuffer_t();
// 
//      HRESULT Free();
//      HRESULT Allocate(PVOID  pSrcMarshalled, DWORD cbSrc, DWORD ArgumentDescriptor);
//      HRESULT Allocate(PCVOID pSrcMarshalled, DWORD cbSrc, DWORD ArgumentDescriptor);
//      HRESULT Flush();
// 
//      LPVOID ptr() const;
//      DWORD size() const;
typedef ce::marshal::detail::Buffer_t<ce::marshal::detail::AsyncTraits_t> AsynchronousBuffer_t;


#endif  // _MARSHAL_HPP_INCLUDED_

