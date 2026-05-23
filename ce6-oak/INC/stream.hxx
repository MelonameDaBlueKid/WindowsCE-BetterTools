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
// THE SAMPLE SOURCE CODE IS PROVIDED "AS IS", WITH NO WARRANTIES.
//
#pragma once 
// Classes that allow us to represent a stream of memory. 
// and convert offsets to ptrs.

#include <windows.h>
#include <auto_xxx.hxx>
#include <alignment.hxx>

namespace ce
{

class Stream
{
public:
    // check if offset oData size cbData can fit in the stream, 
    // If so return a fixed up pointer, 
    //  else return NULL.
    virtual void* verify_ptr(size_t oData, size_t cbData)=0;

    // type safe version of verify_ptr
    // returns NULL on error.
    template <typename T>
    T* ptr_from_offset(T const * oData, size_t cbData)
    {
        return (T*)verify_ptr( (UINT_PTR)oData,cbData);
    }
    Stream()
    { }

private:
    Stream(const Stream&);
    void operator=(Stream&);
}; 

// TODO: better name for AllocatedStream.
// Stream that is instantiated with allocated memory.
// This stream should only be used when the memory is not
// expected to change asyncronously. 

class AllocatedStream: public Stream
{
    public:
    AllocatedStream(PVOID pStream,size_t cbStream)
        : m_cbStream(cbStream)
        , m_pStream((BYTE*)pStream)
    { }

    virtual void* verify_ptr(size_t oData, size_t cbData)
    {
        if (!isDataInStream(oData,cbData))
        {
            return NULL;
        }

        return m_pStream+oData;
    }

    size_t size() const
    {
        assert(m_pStream);
        return m_cbStream;
    }

protected:
    bool isDataInStream(size_t offsetData, size_t cbData )
    {
        const bool isDataFits = (offsetData + cbData <= m_cbStream);
        return isDataFits;
    }


    //can't make these const since they are modified 
    // in the CopyInOutStream ctor.

    size_t m_cbStream;
    BYTE * m_pStream;
};

// A CopyInOutStream is a AllocatedStream, except it makes a copy of input buffer.
// On it's destructor, CopyInOutStream, writes back to the client buffer.
// This allows CopyInOutStream to be used if a malicious client is making asyncronous
// changes to the stream.
class CopyInOutStream:public AllocatedStream
{
    public:

    CopyInOutStream(PBYTE pStream,size_t cbStream)
        : AllocatedStream(NULL,0) // will update later.
        , m_pClientBuffer(pStream)

    {
        m_pCopiedBuffer= new BYTE[cbStream];
        if (!m_pCopiedBuffer) return;

        // update members in AllocatedStream
        m_pStream = m_pCopiedBuffer;
        m_cbStream = cbStream;
        // copy clients data.
        memcpy(m_pStream,m_pClientBuffer,cbStream);
    } 

    ~CopyInOutStream()
    {
        write_back();
    }

    private:
    void write_back()
    {
        if (!m_pStream)
        {
            return;
        }
        memcpy(m_pClientBuffer,m_pStream,m_cbStream);
    }

    private:

    ce::auto_ptr<BYTE> m_pCopiedBuffer;
    BYTE * const m_pClientBuffer;
};


// This abstract class does Aligned writes via Append. 
class AppendStream:public Stream
{
    public:
    AppendStream()
        :m_cbFromStart(0)
    { }

    template <typename T>
    DWORD Append(T* const pData, const size_t cbData,T** const ppDataAsOffset)
    {
        const size_t cbPad  = cbPadding<T>();

        UINT_PTR cbDataOffset;
        DWORD ret = Reserve(cbData+cbPad,&cbDataOffset);
        if (ret != NO_ERROR)
        {
            assert(false);
            return ret;
        }

        cbDataOffset += cbPad;

        *ppDataAsOffset = reinterpret_cast<T*>(cbDataOffset);
        writeToOffset(cbDataOffset,pData,cbData);

        return NO_ERROR;
    }

    template <typename T>
    DWORD Append(T const pData, T* const ppDataAsOffset)
    {
        const size_t cbData = sizeof(*pData);
        return Append(pData,cbData,ppDataAsOffset);
    }

    DWORD Reserve(const size_t cbData,UINT_PTR * const pcbOffset=NULL)
    {
        if (!isRoomFor(cbData))
        {
            assert(false);
            return ERROR_OUTOFMEMORY;
        }

        if (pcbOffset)
        {
            *pcbOffset = m_cbFromStart;
        }

        m_cbFromStart +=cbData;
        return NO_ERROR;
    }

    virtual size_t size() const=0;

    protected: 
    virtual bool isRoomFor(const DWORD  cb) const =0;
    virtual void writeToOffset(const DWORD offset,void const * const  pData, const DWORD cbData)=0;

    protected:
    size_t m_cbFromStart;
    private:
    template <typename T> size_t cbPadding()
    {
        return ce::cbPadding<T>(reinterpret_cast<BYTE*>(m_cbFromStart));
    }
};

// This memory used for writing to this class, is allocated once during Create.  
class MemoryAppendStream:public AppendStream
{
    public: // Static Creators 

    static MemoryAppendStream * Create(size_t cbStream)
    {
        ce::auto_ptr<MemoryAppendStream> pRet = new MemoryAppendStream(cbStream);
        if (!pRet->m_pStream) 
        {
            return NULL;
        }

        return pRet.release();
    }

    public: // Used when marshalling.

    size_t size() const
    {
        return m_cbStream;
    }

    BYTE * start() 
    {
        assert(m_pStream);
        return static_cast<BYTE*>(m_pStream);
    }

    void* verify_ptr(size_t oData, size_t)
    {
        // TODO: Assert size will fit.
        return m_pStream + oData;
    }

    private:

    bool isRoomFor(const DWORD cbData) const 
    {
        const bool isEnoughRoom =  (cbData + m_cbFromStart) <= m_cbStream;
        return isEnoughRoom;
    }
    void writeToOffset(const DWORD offset,void const * const  pData, const DWORD cbData)
    {
        BYTE * const pCurStreamPos  = m_pStream+offset;
        memcpy(pCurStreamPos,pData,cbData);
        return;
    }

    MemoryAppendStream(size_t cbStream)
        : m_cbStream(cbStream)
        , m_pStream (new BYTE[cbStream])
    {
    }
    MemoryAppendStream(AppendStream&);
    const ce::auto_ptr<BYTE> m_pStream;
    const size_t m_cbStream;
};

// This class is used  to compute the size required for MemoryAppendStream::Create();
class NullAppendStream:public AppendStream
{
    bool isRoomFor(const DWORD) const 
    { return true; }

    void writeToOffset(const DWORD ,void const * const , const DWORD )
    { return; }

    void* verify_ptr(size_t, size_t)
    {
        assert(false);
        return NULL;
    }
    public:
    size_t size() const
    {
        return m_cbFromStart;
    }
};
};

