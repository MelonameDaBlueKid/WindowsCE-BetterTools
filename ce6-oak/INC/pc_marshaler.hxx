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
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.
//

#include <windows.h>
#include "auto_xxx.hxx"
#include "hash_map.hxx"
#include "singleton.hxx"
#include "sync.hxx"
#include "string.hxx"
#include "stream.hxx"
#include "psl_marshaler.hxx"

#pragma once 

//
// Set of templates implementing generic and extensible proxy and stub for 
// PC (procedure calls) in Windows CE. 
//

#if 0
/**/
/**/    //////////////////////////////////////////////////////////////////////////////////////////
/**/    // 1. Implementing "remote" API using psl_proxy and psl_stub
/**/    //////////////////////////////////////////////////////////////////////////////////////////
/**/
/**/    #define XYZ_IOCTL_INVOKE    100
/**/    #define FOO                 1
/**/    #define BAR                 2
/**/
/**/    //***************
/**/    // Client process
/**/    //***************
/**/
/**/    //
/**/    // psl_proxy object for server hosted in device/service XYZ1:
/**/    // Lifetime of the object typically should be equal to the lifetime of the client.
/**/    // When the psl_proxy object is destroyed it will close device/service handle 
/**/    // (which potentially will clean client's context on the device/service).
/**/    // Usually psl_proxy object will be declared as global or singleton.
/**/    //
/**/    ce::pc_proxy<> proxy(L"XYZ1:", XYZ_IOCTL_INVOKE, NULL);
/**/
/**/    DWORD Foo(DWORD* pdwSize, VOID* pszBuffer)
/**/    {
/**/        return proxy.call(FOO, pdwSize, pszBuffer);
/**/    }
/**/    
/**/    BOOL Bar(DWORD dwCount, const Record* pRecords)
/**/    {
/**/        // proxy.call returns DWORD error even for functions that return TRUE or FALSE
/**/        // The error code is also available to the caller via GetLastError
/**/        return ERROR_SUCCESS == proxy.call(BAR, dwCount, pRecords);
/**/    }
/**/    
/**/
/**/    //***************
/**/    // Server process
/**/    //***************
/**/    
/**/    // Server side implementation of Foo API.
/**/    // Note that the name of the server side functions may be but don't have to be 
/**/    // the same as name of appropriate client side functions. Signatures of the
/**/    // functions have to be the same on server and client side.
/**/    
/**/    // Server function that returns DWORD indicating success (ERROR_SUCCESS) or failure
/**/    DWORD Foo(DWORD* pdwSize, VOID* pszBuffer)
/**/    {
/**/        ...
/**/    }
/**/    
/**/    // Server function that returns TRUE or FALSE and sets last error in case of failure
/**/    BOOL Bar(DWORD dwCount, const Record* pRecords)
/**/    {
/**/        ...
/**/    }
/**/
/**/    // IOControl function for driver/service that is hosting the server
/**/    BOOL XYZ_IOControl(..., DWORD dwCode, IN PBYTE pBufIn, IN DWORD dwLenIn, ...)
/**/    {
/**/        DWORD dwErr = ERROR_INVALID_PARAMETER;
/**/
/**/        switch(dwCode)
/**/        {
/**/            case XYZ_IOCTL_INVOKE:
/**/            {
/**/                //
/**/                // Initialize stub object from input buffer and validate that input buffer
/**/                // is valid in the context of the calling process.
/**/                //
/**/                ce::pc_stub<> stub(pBufIn, dwLenIn);
/**/                
/**/                // Get ID of API that is being called; will return ce::INVALID_FUNCTION_ID if the
/**/                // validation of the input buffer failed. 
/**/                switch(stub.function())
/**/                {
/**/                    //
/**/                    // Call appropriate API implementation based on the ID.
/**/                    // psl_stub will extract arguments from the input buffer and call the API implementation.
/**/                    // For any arguments that are pointers, psl_stub will validate that the memory
/**/                    // region they are pointing to is valid in context of the client process (by default caller
/**/                    // process is used; handle of another process can be passed as 3rd argument to psl_stub ctor). 
/**/                    // psl_stub wraps call to the API implementation in __try{}__except block. If exception 
/**/                    // happens during execution of the API call ERROR_EXCEPTION_IN_SERVICE error is returned 
/**/                    // to the client. Note that exception handler in psl_stub is a last resort. Usually server 
/**/                    // implementation should locally handle exceptions when accessing memory from the client
/**/                    // to avoid leaks.
/**/                    //
/**/                    // IMPORTANT: If an argument points to an array of items or otherwise to a region 
/**/                    //            larger than the type of pointer would indicate, it is responsibility
/**/                    //            of the server to call verify_ptr on the pointer with appropriate
/**/                    //            size. For example, for a LPCWSTR argument, psl_stub will only validate
/**/                    //            that the calling process has access to sizeof(wchar_t) bytes.
/**/                    //            If the size of the buffer is passed in the call then psl_buffer_wrapper
/**/                    //            can be used to guarantee proper mapping of the whole buffer (see #5 below).
/**/                    //
/**/                    case FOO:       dwErr = stub.call(Foo);
/**/                                    break;
/**/
/**/                                    // Bar returns TRUE or FALSE and sets last error in case of failure.
/**/                    case BAR:       return stub.call(Bar);
/**/                }
/**/                break;
/**/            }
/**/        }
/**/        
/**/        if(ERROR_SUCCESS == dwErr)
/**/            return TRUE;
/**/        else
/**/        {
/**/            SetLastError(dwErr);
/**/            return FALSE;
/**/        }    
/**/    }
/**/
/**/
/**/    //////////////////////////////////////////////////////////////////////////////////////////
/**/    // 2. Implementing server in a class
/**/    //////////////////////////////////////////////////////////////////////////////////////////
/**/
/**/
/**/    class CServer
/**/    {
/**/    public:
/**/        DWORD Foo(DWORD* pdwSize, VOID* pszBuffer);
/**/        BOOL Bar(DWORD dwCount, const Record* pRecords);
/**/    }*g_pServer, g_Server;
/**/
/**/    // ...
/**/                switch(stub.function())
/**/                {
/**/                    case FOO:       dwErr = stub.call(g_pServer, CServer::Foo);
/**/                                    break;
/**/
/**/                    case BAR:       return stub.call(g_Server, CServer::Bar);
/**/                }
/**/                break;
/**/    // ...
/**/
/**/
/**/    //////////////////////////////////////////////////////////////////////////////////////////
/**/    // 3. Tracking per-client state on the server 
/**/    //////////////////////////////////////////////////////////////////////////////////////////
/**/
/**/    // Server often needs to track per-client state so that it can be cleaned if the client
/**/    // process is terminated w/o proper shutdown. Typically server will associate client 
/**/    // state with dwOpenData argument of DeviceIoControl.
/**/    // 
/**/    // This scheme can be implemented with psl marshaler classes in a following 
/**/    // manner (modification to the server side code from example #1):
/**/
/**/
/**/    // Intermediate function that takes additional dwOpenData argument in addition to
/**/    // the parameters of the Bar function.
/**/    BOOL _Bar(DWORD dwOpenData, DWORD dwCount, const Record* pRecords)
/**/    {
/**/        // Map dwOpenData back to the client state; in this example dwOpenData contains a pointer
/**/        // to a ClientState object representing the client's state. 
/**/        ClientState* pClientState = reinterpret_cast<ClientState*>(dwOpenData);
/**/
/**/        // Call actual server implementation of Bar
/**/        BOOL bRet = Bar(dwCount, pRecords);
/**/
/**/        // Update client state in pClientState as appropriate for Bar
/**/
/**/        return bRet;
/**/    }
/**/
/**/    BOOL XYZ_Close(DWORD dwOpenData)
/**/    {
/**/        // Map dwOpenData back to the client state; in this example dwOpenData contains a pointer
/**/        // to a ClientState object representing the client's state. Value of dwOpenData
/**/        // for a client is established in XYZ_Open. 
/**/        ClientState* pClientState = reinterpret_cast<ClientState*>(dwOpenData);
/**/        
/**/        // Cleanup any outstanding state of the client in pClientState
/**/        
/**/        return TRUE;
/**/    }
/**/
/**/    BOOL XYZ_IOControl(DWORD dwOpenData, DWORD dwCode, IN PBYTE pBufIn, IN DWORD dwLenIn, ...)
/**/    {
/**/        switch(dwCode)
/**/        {
/**/            case XYZ_IOCTL_INVOKE:
/**/            {
/**/                ce::pc_stub<> stub(pBufIn, dwLenIn);
/**/                
/**/                switch(stub.function())
/**/                {
/**/                    // dwOpenData can be passed to some (or all) server functions as an extra argument 
/**/                    case BAR:   return stub.call(_Bar, dwOpenData);
/**/
/**/                    // ...
/**/                }
/**/                break;
/**/            }
/**/        }
/**/
/**/        // ...
/**/    }
/**/
/**/
/**/    //////////////////////////////////////////////////////////////////////////////////////////
/**/    // 4. Passing handle via PC calls 
/**/    //////////////////////////////////////////////////////////////////////////////////////////
/**/
/**/    //
/**/    // Handles require special handling when used as arguments to calls made with psl marshaler.  
/**/    // Handles are declared as pointers and they would be verified by psl_stub. Typically this is 
/**/    // not desired because handles must be treated as opaque values. To prevent treating handles  
/**/    // as regular pointer one needs to provide specialization of pc_marshaler class template
/**/    // for the handle type.
/**/    //
/**/    // IMPORTANT: Handles often are declared as simple typedef of void*. Such a handle can't be used
/**/    //            for specialization of pc_marshaler because it would result in all void* arguments
/**/    //            not being mapped properly by the server's psl_stub. Only handles declared using
/**/    //            DECLARE_HANDLE macro should be used to specialize pc_marshaler.
/**/    //
/**/    // psl_marshaler provides a predefined ce::PSL_HANDLE type and appropriate specialization of 
/**/    // pc_marshaler class template:
/**/    //
/**/
/**/    // Server
/**/    DWORD Foo(ce::PSL_HANDLE hpslEvent)
/**/    {
/**/        HANDLE hEvent = reinterpret_cast<HANDLE>(hpslEvent);
/**/    }
/**/
/**/    // Client
/**/    DWORD Foo(HANDLE hEvent)
/**/    {
/**/        return proxy.call(FOO, reinterpret_cast<ce::PSL_HANDLE>(hEvent));
/**/    }
/**/
/**/    // Alternatively user can declare their own handle(s) using DECALRE_HANDLE and specialize
/**/    // pc_marshaler class template for it:
/**/
/**/    DECLARE_HANDLE(USER_HANDLE);
/**/
/**/    template<>
/**/    class ce::pc_marshaler<USER_HANDLE> : public pc_marshaler_no_stream_storage
/**/    { 
/**/        public: pc_marshaler(USER_HANDLE x): pc_marshaler_no_stream_storage(x) { } 
/**/    };
/**/
/**/    
/**/
/**/    //////////////////////////////////////////////////////////////////////////////////////////
/**/    // 5 Passing sized buffer
/**/    //////////////////////////////////////////////////////////////////////////////////////////
/**/
/**/    // Server
/**/    DWORD Foo(ce::psl_buffer_wrapper<int*> numbers)
/**/    {
/**/        return FooImpl(numbers.buffer(), numbers.count());
/**/    }
/**/
/**/    DWORD FooImpl(const int *pNumbers, size_t nCount)
/**/    {
/**/        // buffer pNumbers is valid for nCount elements of type int
/**/    }
/**/
/**/
/**/    // Client
/**/    DWORD Foo_ReadOnly(const int *pNumbers, size_t nCount)
/**/    {
/**/        // Any changes made on server will not be reflected in clients buffer.
/**/        return proxy.call(FOO, ce::psl_buffer(pNumbers, nCount));
/**/    }
/**/
/**/    // Client
/**/    DWORD Foo(const int *pNumbers, size_t nCount)
/**/    {
/**/        // Any changes made on server will *be* reflected in clients buffer.
/**/        return proxy.call(FOO, in_out_argument(ce::psl_buffer(pNumbers, nCount)));
/**/    }
/**/
/**/    //////////////////////////////////////////////////////////////////////////////////////////
/**/    // 6. Passing Pointers across an PC boundry.
/**/    //////////////////////////////////////////////////////////////////////////////////////////
/**/     
/**/    // copy in means a pointer is copied into the stubs memory space.
/**/    // copy out means a poitner is copied out of a stubs memory space.  
/**/
/**/    // The default copy semantics for pointers is copy in, e.g.
/**/
/**/    void stub_SetTo7(DWORD *p);
/**/
/**/    #define SET_TO_7 1
/**/
/**/    DWORD stub_entryPoint(LPVOID p, DWORD cb)
/**/    {
/**/        ce::pc_stub<> stub(p, cb);
/**/
/**/        switch(stub.function())
/**/        {
/**/            case SET_TO_7:
/**/                stub.call(stub_setTo7);
/**/                return NO_ERROR;
/**/        }
/**/
/**/        return ERROR_INVALID_PARAMETER;
/**/    }
/**/
/**/    DWORD stub_setTo7(DWORD *p)
/**/    { 
/**/        *p = 7; 
/**/        return NO_ERROR; 
/**/    }
/**/
/**/    void proxy_brokenSetTo7()
/**/    {
/**/        local_proxy proxy(stub_entryPoint);
/**/        DWORD d=3;
/**/        proxy.call(SET_TO_7,&d);
/**/        assert (d == 3); // d not changed, since default semantic is copy in.
/**/    }
/**/
/**/    // copy out or copy in out semenatics are specified using the out and 
/**/    // in_out functions respectivly. e.g:
/**/
/**/    void proxy_workingSetTo7()
/**/    {
/**/        DWORD d=3;
/**/        local_proxy proxy(localStub);
/**/        proxy.call(SET_TO_7,ce::out(&d));
/**/        assert (d == 7);
/**/
/**/        d = 4;
/**/        proxy.call(SET_TO_7,ce::in_out(&d));
/**/        assert (d == 7); 
/**/    }
/**/
/**/
/**/
/**/    //////////////////////////////////////////////////////////////////////////////////////////
/**/    // 7. Passing Null terminated strings across an PC boundry
/**/    //////////////////////////////////////////////////////////////////////////////////////////
/**/
/**/    const NULL terminated strings are automatically marshaled across the
/**/    PC boundry. No special code is required.
/**/
/**/    //////////////////////////////////////////////////////////////////////////////////////////
/**/    // 8. Structures with embedded pointers
/**/    //////////////////////////////////////////////////////////////////////////////////////////
/**/
/**/    // Structure with embedded pointers
/**/    struct  customStruct
/**/    {
/**/        DWORD dw;
/**/        WCHAR const * str;
/**/        int * pInts;
/**/        DWORD cInts;
/**/    };
/**/    
/**/    // Following specialization of pc_marshaler class template is required if one or more 
/**/    // functions called via psl marshaler have parameter(s) of customStruct* type.
/**/    //
/**/    // IMPORTANT: The specialization must be for exact type that is being used as a function argument.
/**/    //            For example in this case it is for customStruct* because this is type of argument
/**/    //            of the function Bar. 
/**/    

template <>
class pc_marshaler<customStruct*> : private_copy_ctor
{
    typedef pc_marshaler<customStruct*> my_T;
    typedef psl_buffer_wrapper<int*>  IntWrapper;

    public:
        pc_marshaler(customStruct *x)
            :p(x)
            ,str(p?p->str:NULL)
            ,ints(psl_buffer(p?p->pInts:NULL,p?p->cInts:NULL))
        { } 
        
        customStruct* unmarshal(Stream& stream) const 
        {
            if (!p) return NULL;

            customStruct* pUnmarshaled =  stream.ptr_from_offset(p,sizeof(*p));
            if(!pUnmarshaled)
            {
                assert(false);
                return NULL;
            }

            pUnmarshaled->str = str.unmarshal(stream);
            IntWrapper tmp = this->ints.unmarshal(stream);
            pUnmarshaled->pInts = tmp.buffer();
            pUnmarshaled->cInts = tmp.count();

            return pUnmarshaled;
        }

        DWORD marshal (AppendStream& stream, const my_T & rhs)
        { 
            p = rhs.p;
            DWORD ret = stream.Append(p,&p);
            if (ret != NO_ERROR)
            {
                assert(false);
                return ret;
            }

            ret = str.marshal(stream, rhs.str);
            if (ret != NO_ERROR)
            {
                assert(false);
                return ret;
            }

            ret = ints.marshal(stream, rhs.ints);
            if (ret != NO_ERROR)
            {
                assert(false);
                return ret;
            }

            return NO_ERROR;
        }

        
        DWORD write_back( const customStruct * &  rhs)
        { 
            if (!p) return NO_ERROR;

            // write back the int_wrapper.
            DWORD ret = ints.write_back(psl_buffer(rhs->pInts,rhs->cInts));
            if (ret != NO_ERROR)
            {
                return ret;
            }

            // write back the scalars.
            p->dw = rhs->dw;

            // don't write back str since it's const.
            return NO_ERROR; 
        }

    private:
        customStruct* p;
        pc_marshaler<WCHAR const*> str;
        pc_marshaler<IntWrapper> ints;
    };
/**/ 
/**/    //////////////////////////////////////////////////////////////////////////////////////////
/**/    // 9. Passing Variable length objects to the stub. 
/**/    //////////////////////////////////////////////////////////////////////////////////////////
/**/   
/**/    A common pattern is to pass an output structure to a function that contains both data and pointers.
/**/    Those pointers will then point to the data at the end of the structure. 
/**/   
/**/   
/**/    For an example of this pattern see : 
/**/        pc_marshaler.hxx - class variable_sized_type 
/**/        cred_ioctl.h - class CRED_OUT 
/**/        cred_ioctl.h - class ce::pc_marshaler<CRED_OUT>
/**/ 
/**/    //////////////////////////////////////////////////////////////////////////////////////////
/**/    // 10. pc_stub -  security, copies, and performance
/**/    //////////////////////////////////////////////////////////////////////////////////////////
/**/    
/**/    pc_stub is aliased to pc_stub_copy_in_out which makes a copy of its input buffer. 
/**/    
/**/    The choices for stubs are: 
/**/    
/**/     pc_stub_copy_in_out 
/**/       Should be used when:
/**/         The proxy has a lower trust level then the stub
/**/         AND the procedure call transport does not copy the proxies buffer (e.g. DeviceIOControl) 
/**/       This is needed to prevent the threat of: 
/**/          Another proxy thread changing the buffer while the stub is operating on it. 
/**/  
/**/     pc_stub_no_copy 
/**/       Should be used when:
/**/          The proxy has a trust level greater than or equal to stubs.
/**/          OR the procedure call makes a copy of the proxies buffer (e.g. Sockets) 
/**/  
/**/     pc_stub_no_copy will provide a performance benefit. However, it should only be used
/**/     if the above security conditions are met. 
/**/  

#endif

namespace ce
{
    class private_copy_ctor
    {
        public:
        private_copy_ctor(){ } 

        private:
        private_copy_ctor(private_copy_ctor&);
        void operator=(private_copy_ctor&);
    };
namespace detail
{

// argument_holder:
//   allow specialization of pc_data_wrapper at compile time.
//   allow syntatic sugar on proxy of : in_out_argument, in_argumnet

template <typename T>
class argument_holder
{
public:
    argument_holder(T p)
        : m_p(p)
    {}
    
    T argument()
    {
        return m_p;
    }
    
private:
    T m_p;
};

template <typename T> 
class out_argument: public argument_holder<T>
{
public:
	  explicit out_argument(T p)
        : argument_holder(p)
	  {}
};

template <typename T>
class in_out_argument: public argument_holder<T>
{
public:
    // not explicit so we can have pc_data_wrapper<out_argument<T> > : pc_data_wrapper<in_out_argument<T> > 
    // XXX: What problems does this cause?
    // Should this be fixed some other way??
	in_out_argument(T p)
        : argument_holder(p)
	{}
};

};

// decorator for [out]
template <typename T>
detail::out_argument<T> out(T x)
{
    return detail::out_argument<T>(x);
}

// decorator for [in out]
template <typename T>
detail::in_out_argument<T> in_out(T x)
{
    return detail::in_out_argument<T>(x);
}


// forward decl.
template <typename T> class  pc_marshaler;

// pc_marshaler that is used when no stream storage is required.
template <typename T> 
class pc_marshaler_no_stream_storage : private_copy_ctor
{
public:
    pc_marshaler_no_stream_storage(T x)
    :data(x)
    { } 

    typedef pc_marshaler<T> my_T;

    DWORD marshal (AppendStream&, my_T const & rhs)
    { 
        data = rhs.data; 
        return NO_ERROR;
    }

    DWORD write_back(const my_T& rhs)
    { return NO_ERROR; }
    
    T unmarshal(Stream&) const
        {return data; }

protected:
    T data;
};


template<typename T>
class pc_marshaler: public pc_marshaler_no_stream_storage<T> 
{
    public: pc_marshaler(T x): pc_marshaler_no_stream_storage(x) { } 
};

template<>
class pc_marshaler<PSL_HANDLE>: public pc_marshaler_no_stream_storage<PSL_HANDLE>
{ 
    public: pc_marshaler(PSL_HANDLE x): pc_marshaler_no_stream_storage(x) { } 
};

template<>
class pc_marshaler<HWND>: public pc_marshaler_no_stream_storage<HWND>
{ 
    public: pc_marshaler(HWND x): pc_marshaler_no_stream_storage(x) { } 
};


// Only const strings support marshaling. Force compiler error for non const strings.
template <>
class pc_marshaler<WCHAR*>
{ };

template <>
class pc_marshaler<CHAR*>
{ };


template <typename T>
class pc_marshaler_string:private_copy_ctor
{
    // Optimize: This class is very in-efficient.
public:
    typedef pc_marshaler<T*> my_T;
    typedef ce::_string_t<typename detail::remove_const<T>::type> my_str;

    pc_marshaler_string(T* x)
        : ptr(x)
        { }

    DWORD marshal (AppendStream& stream, const my_T& rhs)
    {
        if (rhs.ptr == NULL)
        {
            ptr = NULL;
            return NO_ERROR;
        }

        DWORD ret = stream.Append(rhs.ptr,rhs.cbStream(),&ptr);
        return ret;
    }

    
    T* unmarshal(Stream& stream) const 
    {
        if (!ptr)
        {
            return NULL;
        }

        // Get the first byte.
        T* pStartOfString = stream.ptr_from_offset(ptr,1);

        my_str s = pStartOfString;
        return stream.ptr_from_offset(ptr,cbString(s));
    }

private:
    DWORD cbStream() const 
    {
        my_str str = ptr;
        return cbString(str);
    }

    DWORD cbString(my_str& s ) const
    {
        const size_t cchWithNull = s.length()+1;
        const bool isIntegerOverFlow = (cchWithNull > UINT_MAX/ sizeof(T) );
        if (isIntegerOverFlow)
        {
            return UINT_MAX;
        }
        return (cchWithNull) * sizeof(T);
    }

    T* ptr;

private:
    // write back not supported for strings.
    DWORD write_back(my_T rhs);
};


template <>
class pc_marshaler<WCHAR const *> : public pc_marshaler_string<const WCHAR>
{ 
    public: pc_marshaler(WCHAR const * x) : pc_marshaler_string(x) { }
};

template <>
class pc_marshaler<CHAR const *> : public pc_marshaler_string<const CHAR>
{ 
    public: pc_marshaler(CHAR const * x) : pc_marshaler_string(x) { }
};



template<typename T>
class pc_marshaler <T*>
{
public:
    typedef pc_marshaler<T*> my_T;

    pc_marshaler(T* x):
        ptr(x)
        { }

    DWORD marshal (AppendStream& stream, my_T const & rhs)
    {
        ptr = rhs.ptr;

        if (!ptr) 
            return NO_ERROR;

        DWORD ret = stream.Append(rhs.ptr, detail::size_of<T>::value,&ptr);
        return ret;
    }


    DWORD write_back(T* const & rhs)
    { 
        if (ptr)
        {
            *ptr = *rhs;
        }

        return NO_ERROR; 
    }
    
    T* unmarshal(Stream& stream) const 
    {
        if (!ptr)
        {
            return NULL;
        }

        return stream.ptr_from_offset(ptr, detail::size_of<T>::value);
    }

protected:

    T* ptr;
};

namespace detail 
{

// default <in>
template <typename T> 
class pc_data_wrapper:private_copy_ctor
{

protected:
    typedef pc_data_wrapper<T> my_T;
public:
    explicit pc_data_wrapper(T x) 
        : marshaler(x)
    { }

    typedef T data_type;

    DWORD marshal (AppendStream& stream, my_T const & rhs)
    { 
        marshaler.marshal(stream,rhs.marshaler);
        return NO_ERROR;
    }

    DWORD write_back(const T&)
    { 
        return NO_ERROR;
    }
    
    T unmarshal(Stream& stream) const
    {
        return marshaler.unmarshal(stream);
    }

public:
    pc_marshaler<T> marshaler;
};

template <typename T> 
class pc_data_wrapper<in_out_argument<T> > : public pc_data_wrapper<T>
{
    public:
    typedef pc_data_wrapper<T> my_base;
    pc_data_wrapper(in_out_argument<T> x):
        my_base(x.argument())
    {
    }

    DWORD write_back(const T& rhs)
    { 
        return marshaler.write_back(rhs);
    }
};

// IMPL DETAIL: out_arg and in_out_arg are identical.
// PERF:
// BENEFIT: out_arg's won't be smoked in cases where, the out_arg wasn't written by the stub. 
template <typename T> 
class pc_data_wrapper<out_argument<T> > : public pc_data_wrapper<in_out_argument<T> >
{
    public:
    typedef pc_data_wrapper<in_out_argument<T> > my_base;
    pc_data_wrapper(out_argument<T> x):
        my_base(x.argument())
    {
    }
};

}; // namespace detail

namespace detail { 


template<typename _extra_info_t> class pc_message0 : private_copy_ctor
{
public:
    typedef pc_message0<_extra_info_t> my_T;
    pc_message0(WORD wFunction, _extra_info_t ExtraInfo)
        : m_wFunction(wFunction)
        , m_ExtraInfo(ExtraInfo)
    {
        // INVALID_FUNCTION_ID is used to indicate invalid message and shouldn't be used 
        assert(m_wFunction != INVALID_FUNCTION_ID);
    }
    
    _extra_info_t unmarshal_extra_info(Stream& stream)
    {
        return m_ExtraInfo.unmarshal(stream); 
    }

    DWORD marshal(AppendStream& stream, const my_T& rhs)
    {
        m_wFunction = rhs.m_wFunction;
        return m_ExtraInfo.marshal(stream,rhs.m_ExtraInfo);
    }
    DWORD write_back(Stream& stream, const my_T& rhs)
    {
        return m_ExtraInfo.write_back(rhs.m_ExtraInfo.unmarshal(stream));
    }

    WORD function() const
        {return m_wFunction; }
    
protected:
    WORD m_wFunction;
    pc_data_wrapper<_extra_info_t>   m_ExtraInfo;
};


// pc_message classes are generated using developr/igord/pc_marshal.py 
#include <pc_generated.h>

};


// TODO: Push these to psl_marshaler.hxx

template <typename T> 
bool operator==(psl_buffer_wrapper<T*>& lhs, psl_buffer_wrapper<T*>& rhs )
{
    if (rhs.count() != lhs.count())
    {
        return false;
    }

    return (memcmp(rhs.buffer(),lhs.buffer(),sizeof(T)*(lhs.count()))==0);
}

template <typename T> 
bool operator!=(psl_buffer_wrapper<T*>& lhs, psl_buffer_wrapper<T*>& rhs )
{
    return (! (rhs == lhs));
}


template <typename T,typename T_ALIGNMENT> 
class pc_marshaler_for_psl_buffer_wrapper : private_copy_ctor
{
protected:
    typedef psl_buffer_wrapper<T*> buffer_wrapper;
    typedef pc_marshaler_for_psl_buffer_wrapper<T,T_ALIGNMENT> my_T;
    buffer_wrapper data; 

public:
    pc_marshaler_for_psl_buffer_wrapper(buffer_wrapper x)
        : data (x) 
    { }

    buffer_wrapper unmarshal(Stream& s) const
    {
        T * buffer = NULL;
        if (cbStream() != 0 )
        {
            T const * offsetInStream =  data.buffer();
            buffer = s.ptr_from_offset(offsetInStream, cbStream());
        }

        return buffer_wrapper(buffer, buffer ? data.count() : 0);
    }
    

    DWORD marshal (AppendStream& stream, my_T const &  rhs)
    { 
        return marshal_w_alignment_of<T_ALIGNMENT>(stream,rhs);
    }

    // Need so that we can force alignment when someone uses a psl_buffer_wrapper<BYTE*> to 
    // marshall a more complicated type.

    template <typename T1> 
    DWORD marshal_w_alignment_of(AppendStream& stream, my_T const & rhs)
    {
        // need to befriend the psl_buffer_wrapper for the marshal operation 
        // ( accessing _buffer)
        data =  buffer_wrapper(rhs.data.buffer(),rhs.data.count());
        DWORD ret = stream.Append<T1>(
                reinterpret_cast<T1*>(data.buffer()),
                rhs.cbStream(),
                reinterpret_cast<T1**>(&data._buffer));
        return ret;
    }

    DWORD write_back(const buffer_wrapper& rhs)
    { 
        if (data.count() != rhs.count())
        {
            assert(false);
            return ERROR_INVALID_PARAMETER;
        }

        memcpy(data.buffer(),rhs.buffer(),cbStream());
        return NO_ERROR; 
    }

protected:
    DWORD cbStream() const
    {
        // can't use sizeof(T) since we support psl_buffer_wrapper<PVOID>
        const bool isIntegerOverFlow = (data.count() > UINT_MAX / detail::size_of<T>::value );
        if (isIntegerOverFlow)
        {
            return UINT_MAX;
        }
        return data.count() * detail::size_of<T>::value;
    }
};

template<typename T>
class pc_marshaler<psl_buffer_wrapper<T*> > : public pc_marshaler_for_psl_buffer_wrapper<T,T>
{ 
    public:
    pc_marshaler(buffer_wrapper x)
        : pc_marshaler_for_psl_buffer_wrapper<T,T> (x) 
    { }
};

// byte_array_w_alignment and variable_sized_type are  used when you need to
// marshal a variable sized entity which requires specific alignment. 

// byte_array_w_alignment has the same interface as a psl_buffer_wrapper<LPBYTE> 

// It's recommened that you use variable_sized_type instead of byte_array_w_alignment
// since variable_sized_type has a higher level of type safety.


template <typename T> 
class byte_array_w_alignment:public ce::psl_buffer_wrapper<LPBYTE> {
    public:
    byte_array_w_alignment(BYTE* b, DWORD c):
        ce::psl_buffer_wrapper<LPBYTE>(b,c)
    { }
    byte_array_w_alignment(ce::psl_buffer_wrapper<BYTE*> &b):
        ce::psl_buffer_wrapper<LPBYTE>(b.buffer(),b.count())
    {}
};

template<typename T>
class pc_marshaler<byte_array_w_alignment<T> > : public pc_marshaler_for_psl_buffer_wrapper<BYTE,T>
{
protected:
    typedef pc_marshaler_for_psl_buffer_wrapper<BYTE,T> my_base;
    
public:
    pc_marshaler(my_base::buffer_wrapper x)
        : my_base (x) 
    { }

    // A pc_marshaler<byte_array_w_alignment> is a pc_marshaler<psl_buffer_wrapper<BYTE*>>
    // so add a cast operator.
    operator pc_marshaler<psl_buffer_wrapper<BYTE*> > () const {
        return my_base::buffer_wrapper (data.buffer(),data.count());  
    } ;
};

template <typename T> 
class variable_sized_type:public ce::psl_buffer_wrapper<BYTE*> {

    typedef ce::psl_buffer_wrapper<BYTE*> my_base;

    public:
    variable_sized_type(T* p, DWORD cb):
        my_base(reinterpret_cast<BYTE*>(p),cb)
    { }

    variable_sized_type(ce::psl_buffer_wrapper<BYTE*> &b):
        my_base(b.buffer(),b.count())
    {}

    T* buffer()
    {
        return reinterpret_cast<T*>(my_base::buffer());
    }
};

C_ASSERT(sizeof(variable_sized_type<DWORD>)==sizeof(psl_buffer_wrapper<BYTE*>));


template<typename T>
class pc_marshaler<variable_sized_type<T> > : public pc_marshaler_for_psl_buffer_wrapper<BYTE,T>
{
protected:
    typedef pc_marshaler_for_psl_buffer_wrapper<BYTE,T> my_base;
    
public:
    pc_marshaler(my_base::buffer_wrapper x)
        : my_base (x)
    { }

    // A pc_marshaler<variable_sized_type> is a pc_marshaler<psl_buffer_wrapper<BYTE*>>
    // so add a cast operator.
    operator pc_marshaler<psl_buffer_wrapper<BYTE*> > () const {
        return my_base::buffer_wrapper (data.buffer(),data.count());  
    } ;
};


#define STUB_EXTRA_ARG arg,

// can use pc_stub_base directly, however we provide classes (
// pc_stub_copy_in_out, pc_stub_no_copy) that specify the stream for you to cut
// down on passed in template paramaters.
template <typename _stream_t, typename _extra_info_t = void*>
class pc_stub_base : private_copy_ctor
{
public:
    typedef pc_stub_base<_stream_t,_extra_info_t> _Myt;
    typedef list<_Myt*>             psl_stub_stack;
    //
    // Singleton instance of thread local storage helper. 
    // Singleton guarantees that the instance is created in an atomic way on the first usage.
    //
    typedef singleton<detail::psl_tls<psl_stub_stack> > psl_stub_tls;

    pc_stub_base(__in_bcount(nInBufferSize) LPVOID pInBuffer, DWORD nInBufferSize)
        : m_pMessage0(NULL)
        , m_nInBufferSize(0)
        , m_Stream((LPBYTE)pInBuffer,nInBufferSize)

    {
        //
        // Static instance of singleton_lifetime assures that psl_stub_tls singleton 
        // is destroyed during module unload. singleton_lifetime ctor is thread safe.
        //
        static singleton_lifetime<psl_stub_tls> psl_tls_lifetime;
        
        //
        // Push this instance of psl_stub on the thread local stack.
        //
        if(psl_stub_stack* pPslStubStack = psl_stub_tls::instance().get_thread_data())
        {
            if(pPslStubStack->push_front(this))
            {
                // pInBuffer is validated by the caller
                        
                //
                // Check if the size of input buffer is at least the size of minimal message
                //
                PVOID pStartOfStream = m_Stream.verify_ptr(0,sizeof(sizeof(detail::pc_message0<_extra_info_t>)));
                if (pStartOfStream)
                {
                    m_pMessage0 = reinterpret_cast<detail::pc_message0<_extra_info_t>*>(pStartOfStream);
                    m_nInBufferSize = m_Stream.size();
                }
            }
        }
    }
    
    virtual ~pc_stub_base()
    {
        if(psl_stub_stack* pPslStubStack = psl_stub_tls::instance().get_thread_data())
        {
            // Pop his instance of the stub from the thread local stack
            if(!pPslStubStack->empty())
                pPslStubStack->pop_front();
        
            // Clean the thread local data if the stack is empty
            if(pPslStubStack->empty())
                psl_stub_tls::instance().clean_thread_data();
        }
    }
    
    static _Myt* get_thread_stub()
    {
        //
        // Static instance of singleton_lifetime assures that psl_stub_tls singleton 
        // is destroyed during module unload. singleton_lifetime ctor is thread safe.
        //
        static singleton_lifetime<psl_stub_tls> psl_tls_lifetime;
        
        // Return pointer to the instance of stub on top of thread local stack
        if(psl_stub_stack* pPslStubStack = psl_stub_tls::instance().get_thread_data())
        {
            if(!pPslStubStack->empty())
                return pPslStubStack->front();
        }
        
        return NULL;
    }
    
    WORD function() const
    {
        if(m_pMessage0)
            return m_pMessage0->function();
        else
            return INVALID_FUNCTION_ID;
    }
    
    bool extra_info(_extra_info_t& info) const
    {
        if(m_pMessage0)
            return NULL != (info = m_pMessage0->unmarshal_extra_info(m_Stream));
        else
            return false;
    }
    
    template<typename T>
    T call(T(*Fun)(void))
    {
        PC_STUB_CALL_0_ARG(*Fun,)
    }    
    
    template<typename T, typename T0>
    T call(T(*Fun)(T0), T0 arg)
    {
        PC_STUB_CALL_0_ARG(*Fun, arg)
    }
    
    template<typename C, typename T>
    T call(C* p, T(C::*Fun)(void))
    {
        PC_STUB_CALL_0_ARG(p->*Fun,)
    }    
    
    template<typename C, typename T, typename T0>
    T call(C* p, T(C::*Fun)(T0), T0 arg)
    {
        PC_STUB_CALL_0_ARG(p->*Fun, arg)
    }
    
    template<typename C, typename T>
    T call(C& o, T(C::*Fun)(void))
    {
        PC_STUB_CALL_0_ARG(o.*Fun,)
    }    
    
    template<typename C, typename T, typename T0>
    T call(C& o, T(C::*Fun)(T0), T0 arg)
    {
        PC_STUB_CALL_0_ARG(o.*Fun, arg)
    }
    
    template<typename T, typename T1>
    T call(T(*Fun)(T1))
    {
        PC_STUB_CALL_1_ARG(*Fun,)
    }    
    
    template<typename T, typename T0, typename T1>
    T call(T(*Fun)(T0, T1), T0 arg)
    {
        PC_STUB_CALL_1_ARG(*Fun, STUB_EXTRA_ARG)
    }
    
    template<typename C, typename T, typename T1>
    T call(C* p, T(C::*Fun)(T1))
    {
        PC_STUB_CALL_1_ARG(p->*Fun,)
    }    
    
    template<typename C, typename T, typename T0, typename T1>
    T call(C* p, T(C::*Fun)(T0, T1), T0 arg)
    {
        PC_STUB_CALL_1_ARG(p->*Fun, STUB_EXTRA_ARG)
    }
    
    template<typename C, typename T, typename T1>
    T call(C& o, T(C::*Fun)(T1))
    {
        PC_STUB_CALL_1_ARG(o.*Fun,)
    }    
    
    template<typename C, typename T, typename T0, typename T1>
    T call(C& o, T(C::*Fun)(T0, T1), T0 arg)
    {
        PC_STUB_CALL_1_ARG(o.*Fun, STUB_EXTRA_ARG)
    }
    
    template<typename T, typename T1, typename T2>
    T call(T(*Fun)(T1, T2))
    {
        PC_STUB_CALL_2_ARG(*Fun,)
    }    
    
    template<typename T, typename T0, typename T1, typename T2>
    T call(T(*Fun)(T0, T1, T2), T0 arg)
    {
        PC_STUB_CALL_2_ARG(*Fun, STUB_EXTRA_ARG)
    }
    
    template<typename C, typename T, typename T1, typename T2>
    T call(C* p, T(C::*Fun)(T1, T2))
    {
        PC_STUB_CALL_2_ARG(p->*Fun,)
    }    
    
    template<typename C, typename T, typename T0, typename T1, typename T2>
    T call(C* p, T(C::*Fun)(T0, T1, T2), T0 arg)
    {
        PC_STUB_CALL_2_ARG(p->*Fun, STUB_EXTRA_ARG)
    }
    
    template<typename C, typename T, typename T1, typename T2>
    T call(C& o, T(C::*Fun)(T1, T2))
    {
        PC_STUB_CALL_2_ARG(o.*Fun,)
    }    
    
    template<typename C, typename T, typename T0, typename T1, typename T2>
    T call(C& o, T(C::*Fun)(T0, T1, T2), T0 arg)
    {
        PC_STUB_CALL_2_ARG(o.*Fun, STUB_EXTRA_ARG)
    }
    
    
    
    template<typename T, typename T1, typename T2, typename T3>
    T call(T(*Fun)(T1, T2, T3))
    {
        PC_STUB_CALL_3_ARG(*Fun,)
    }    
    
    template<typename T, typename T0, typename T1, typename T2, typename T3>
    T call(T(*Fun)(T0, T1, T2, T3), T0 arg)
    {
        PC_STUB_CALL_3_ARG(*Fun, STUB_EXTRA_ARG)
    }
    
    template<typename C, typename T, typename T1, typename T2, typename T3>
    T call(C* p, T(C::*Fun)(T1, T2, T3))
    {
        PC_STUB_CALL_3_ARG(p->*Fun,)
    }    
    
    template<typename C, typename T, typename T0, typename T1, typename T2, typename T3>
    T call(C* p, T(C::*Fun)(T0, T1, T2, T3), T0 arg)
    {
        PC_STUB_CALL_3_ARG(p->*Fun, STUB_EXTRA_ARG)
    }
    
    template<typename C, typename T, typename T1, typename T2, typename T3>
    T call(C& o, T(C::*Fun)(T1, T2, T3))
    {
        PC_STUB_CALL_3_ARG(o.*Fun,)
    }    
    
    template<typename C, typename T, typename T0, typename T1, typename T2, typename T3>
    T call(C& o, T(C::*Fun)(T0, T1, T2, T3), T0 arg)
    {
        PC_STUB_CALL_3_ARG(o.*Fun, STUB_EXTRA_ARG)
    }
    
    
    template<typename T, typename T1, typename T2, typename T3, typename T4>
    T call(T(*Fun)(T1, T2, T3, T4))
    {
        PC_STUB_CALL_4_ARG(*Fun,)
    }    
    
    template<typename T, typename T0, typename T1, typename T2, typename T3, typename T4>
    T call(T(*Fun)(T0, T1, T2, T3, T4), T0 arg)
    {
        PC_STUB_CALL_4_ARG(*Fun, STUB_EXTRA_ARG)
    }
    
    template<typename C, typename T, typename T1, typename T2, typename T3, typename T4>
    T call(C* p, T(C::*Fun)(T1, T2, T3, T4))
    {
        PC_STUB_CALL_4_ARG(p->*Fun,)
    }    
    
    template<typename C, typename T, typename T0, typename T1, typename T2, typename T3, typename T4>
    T call(C* p, T(C::*Fun)(T0, T1, T2, T3, T4), T0 arg)
    {
        PC_STUB_CALL_4_ARG(p->*Fun, STUB_EXTRA_ARG)
    }
    
    template<typename C, typename T, typename T1, typename T2, typename T3, typename T4>
    T call(C& o, T(C::*Fun)(T1, T2, T3, T4))
    {
        PC_STUB_CALL_4_ARG(o.*Fun,)
    }    
    
    template<typename C, typename T, typename T0, typename T1, typename T2, typename T3, typename T4>
    T call(C& o, T(C::*Fun)(T0, T1, T2, T3, T4), T0 arg)
    {
        PC_STUB_CALL_4_ARG(o.*Fun, STUB_EXTRA_ARG)
    }
    
    
    
    template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5>
    T call(T(*Fun)(T1, T2, T3, T4, T5))
    {
        PC_STUB_CALL_5_ARG(*Fun,)
    }    
    
    template<typename T, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
    T call(T(*Fun)(T0, T1, T2, T3, T4, T5), T0 arg)
    {
        PC_STUB_CALL_5_ARG(*Fun, STUB_EXTRA_ARG)
    }
    
    template<typename C, typename T, typename T1, typename T2, typename T3, typename T4, typename T5>
    T call(C* p, T(C::*Fun)(T1, T2, T3, T4, T5))
    {
        PC_STUB_CALL_5_ARG(p->*Fun,)
    }    
    
    template<typename C, typename T, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
    T call(C* p, T(C::*Fun)(T0, T1, T2, T3, T4, T5), T0 arg)
    {
        PC_STUB_CALL_5_ARG(p->*Fun, STUB_EXTRA_ARG)
    }
    
    template<typename C, typename T, typename T1, typename T2, typename T3, typename T4, typename T5>
    T call(C& o, T(C::*Fun)(T1, T2, T3, T4, T5))
    {
        PC_STUB_CALL_5_ARG(o.*Fun,)
    }    
    
    template<typename C, typename T, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
    T call(C& o, T(C::*Fun)(T0, T1, T2, T3, T4, T5), T0 arg)
    {
        PC_STUB_CALL_5_ARG(o.*Fun, STUB_EXTRA_ARG)
    }
    
    template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
    T call(T(*Fun)(T1, T2, T3, T4, T5, T6))
    {
        PC_STUB_CALL_6_ARG(*Fun,)
    }    
    
    template<typename T, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
    T call(T(*Fun)(T0, T1, T2, T3, T4, T5, T6), T0 arg)
    {
        PC_STUB_CALL_6_ARG(*Fun, STUB_EXTRA_ARG)
    }
    
    template<typename C, typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
    T call(C* p, T(C::*Fun)(T1, T2, T3, T4, T5, T6))
    {
        PC_STUB_CALL_6_ARG(p->*Fun,)
    }    
    
    template<typename C, typename T, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
    T call(C* p, T(C::*Fun)(T0, T1, T2, T3, T4, T5, T6), T0 arg)
    {
        PC_STUB_CALL_6_ARG(p->*Fun, STUB_EXTRA_ARG)
    }
    
    template<typename C, typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
    T call(C& o, T(C::*Fun)(T1, T2, T3, T4, T5, T6))
    {
        PC_STUB_CALL_6_ARG(o.*Fun,)
    }    
    
    template<typename C, typename T, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
    T call(C& o, T(C::*Fun)(T0, T1, T2, T3, T4, T5, T6), T0 arg)
    {
        PC_STUB_CALL_6_ARG(o.*Fun, STUB_EXTRA_ARG)
    }
    
    template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
    T call(T(*Fun)(T1, T2, T3, T4, T5, T6, T7))
    {
        PC_STUB_CALL_7_ARG(*Fun,)
    }    
    
    template<typename T, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
    T call(T(*Fun)(T0, T1, T2, T3, T4, T5, T6, T7), T0 arg)
    {
        PC_STUB_CALL_7_ARG(*Fun, STUB_EXTRA_ARG)
    }
    
    template<typename C, typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
    T call(C* p, T(C::*Fun)(T1, T2, T3, T4, T5, T6, T7))
    {
        PC_STUB_CALL_7_ARG(p->*Fun,)
    }    
    
    template<typename C, typename T, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
    T call(C* p, T(C::*Fun)(T0, T1, T2, T3, T4, T5, T6, T7), T0 arg)
    {
        PC_STUB_CALL_7_ARG(p->*Fun, STUB_EXTRA_ARG)
    }
    
    template<typename C, typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
    T call(C& o, T(C::*Fun)(T1, T2, T3, T4, T5, T6, T7))
    {
        PC_STUB_CALL_7_ARG(o.*Fun,)
    }    
    
    template<typename C, typename T, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
    T call(C& o, T(C::*Fun)(T0, T1, T2, T3, T4, T5, T6, T7), T0 arg)
    {
        PC_STUB_CALL_7_ARG(o.*Fun, STUB_EXTRA_ARG)
    }
    
    
    template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
    T call(T(*Fun)(T1, T2, T3, T4, T5, T6, T7, T8))
    {
        PC_STUB_CALL_8_ARG(*Fun,)
    }    
    
    template<typename T, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
    T call(T(*Fun)(T0, T1, T2, T3, T4, T5, T6, T7, T8), T0 arg)
    {
        PC_STUB_CALL_8_ARG(*Fun, STUB_EXTRA_ARG)
    }
    
    template<typename C, typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
    T call(C* p, T(C::*Fun)(T1, T2, T3, T4, T5, T6, T7, T8))
    {
        PC_STUB_CALL_8_ARG(p->*Fun,)
    }    
    
    template<typename C, typename T, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
    T call(C* p, T(C::*Fun)(T0, T1, T2, T3, T4, T5, T6, T7, T8), T0 arg)
    {
        PC_STUB_CALL_8_ARG(p->*Fun, STUB_EXTRA_ARG)
    }
    
    template<typename C, typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
    T call(C& o, T(C::*Fun)(T1, T2, T3, T4, T5, T6, T7, T8))
    {
        PC_STUB_CALL_8_ARG(o.*Fun,)
    }    
    
    template<typename C, typename T, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
    T call(C& o, T(C::*Fun)(T0, T1, T2, T3, T4, T5, T6, T7, T8), T0 arg)
    {
        PC_STUB_CALL_8_ARG(o.*Fun, STUB_EXTRA_ARG)
    }
    
    
    template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
    T call(T(*Fun)(T1, T2, T3, T4, T5, T6, T7, T8, T9))
    {
        PC_STUB_CALL_9_ARG(*Fun,)
    }    
    
    template<typename T, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
    T call(T(*Fun)(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9), T0 arg)
    {
        PC_STUB_CALL_9_ARG(*Fun, STUB_EXTRA_ARG)
    }
    
    template<typename C, typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
    T call(C* p, T(C::*Fun)(T1, T2, T3, T4, T5, T6, T7, T8, T9))
    {
        PC_STUB_CALL_9_ARG(p->*Fun,)
    }    
    
    template<typename C, typename T, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
    T call(C* p, T(C::*Fun)(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9), T0 arg)
    {
        PC_STUB_CALL_9_ARG(p->*Fun, STUB_EXTRA_ARG)
    }
    
    template<typename C, typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
    T call(C& o, T(C::*Fun)(T1, T2, T3, T4, T5, T6, T7, T8, T9))
    {
        PC_STUB_CALL_9_ARG(o.*Fun,)
    }    
    
    template<typename C, typename T, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
    T call(C& o, T(C::*Fun)(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9), T0 arg)
    {
        PC_STUB_CALL_9_ARG(o.*Fun, STUB_EXTRA_ARG)
    }
    
    
    template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
    T call(T(*Fun)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10))
    {
        PC_STUB_CALL_10_ARG(*Fun,)
    }    
    
    template<typename T, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
    T call(T(*Fun)(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10), T0 arg)
    {
        PC_STUB_CALL_10_ARG(*Fun, STUB_EXTRA_ARG)
    }
    
    template<typename C, typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
    T call(C* p, T(C::*Fun)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10))
    {
        PC_STUB_CALL_10_ARG(p->*Fun,)
    }    
    
    template<typename C, typename T, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
    T call(C* p, T(C::*Fun)(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10), T0 arg)
    {
        PC_STUB_CALL_10_ARG(p->*Fun, STUB_EXTRA_ARG)
    }
    
    template<typename C, typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
    T call(C& o, T(C::*Fun)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10))
    {
        PC_STUB_CALL_10_ARG(o.*Fun,)
    }    
    
    template<typename C, typename T, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
    T call(C& o, T(C::*Fun)(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10), T0 arg)
    {
        PC_STUB_CALL_10_ARG(o.*Fun, STUB_EXTRA_ARG)
    }
    
    template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
    T call(T(*Fun)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11))
    {
        PC_STUB_CALL_11_ARG(*Fun,)
    }    
    
    template<typename T, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
    T call(T(*Fun)(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11), T0 arg)
    {
        PC_STUB_CALL_11_ARG(*Fun, STUB_EXTRA_ARG)
    }
    
    template<typename C, typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
    T call(C* p, T(C::*Fun)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11))
    {
        PC_STUB_CALL_11_ARG(p->*Fun,)
    }    
    
    template<typename C, typename T, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
    T call(C* p, T(C::*Fun)(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11), T0 arg)
    {
        PC_STUB_CALL_11_ARG(p->*Fun, STUB_EXTRA_ARG)
    }
    
    template<typename C, typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
    T call(C& o, T(C::*Fun)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11))
    {
        PC_STUB_CALL_11_ARG(o.*Fun,)
    }    
    
    template<typename C, typename T, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
    T call(C& o, T(C::*Fun)(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11), T0 arg)
    {
        PC_STUB_CALL_11_ARG(o.*Fun, STUB_EXTRA_ARG)
    }
    
    template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
    T call(T(*Fun)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12))
    {
        PC_STUB_CALL_12_ARG(*Fun,)
    }    
    
    template<typename T, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
    T call(T(*Fun)(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12), T0 arg)
    {
        PC_STUB_CALL_12_ARG(*Fun, STUB_EXTRA_ARG)
    }
    
    template<typename C, typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
    T call(C* p, T(C::*Fun)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12))
    {
        PC_STUB_CALL_12_ARG(p->*Fun,)
    }    
    
    template<typename C, typename T, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
    T call(C* p, T(C::*Fun)(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12), T0 arg)
    {
        PC_STUB_CALL_12_ARG(p->*Fun, STUB_EXTRA_ARG)
    }
    
    template<typename C, typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
    T call(C& o, T(C::*Fun)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12))
    {
        PC_STUB_CALL_12_ARG(o.*Fun,)
    }    
    
    template<typename C, typename T, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
    T call(C& o, T(C::*Fun)(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12), T0 arg)
    {
        PC_STUB_CALL_12_ARG(o.*Fun, STUB_EXTRA_ARG)
    }
    
protected:
    // general template not defined
    template<typename T>
    T error(DWORD dwError);
    
    // specialization for DWORD
    template<>
    DWORD error<DWORD>(DWORD dwError)
        {return dwError; }
        
    // specialization for HRESULT
    template<>
    HRESULT error<HRESULT>(DWORD dwError)
        {return HRESULT_FROM_WIN32(dwError); }
    
    // specialization for BOOL
    template<>
    BOOL error<BOOL>(DWORD dwError)
    {
        SetLastError(dwError);
        return dwError == ERROR_SUCCESS;
    }

protected:
    detail::pc_message0<_extra_info_t>*    m_pMessage0;
    DWORD                                   m_nInBufferSize;
    _stream_t                         m_Stream;
private:
    void operator=(pc_stub_base&);
};



template <typename _extra_info_t=void*>
class pc_stub_copy_in_out: public pc_stub_base<CopyInOutStream,_extra_info_t>
{
    public: 
       pc_stub_copy_in_out(__in_bcount(nInBufferSize) LPVOID pInBuffer, DWORD nInBufferSize):pc_stub_base(pInBuffer,nInBufferSize)
       {}
};

template <typename _extra_info_t=void*>
class pc_stub_no_copy: public pc_stub_base<AllocatedStream,_extra_info_t>
{
    public: 
       pc_stub_no_copy(__in_bcount(nInBufferSize) LPVOID pInBuffer, DWORD nInBufferSize):pc_stub_base(pInBuffer,nInBufferSize)
       {}
};

// To error on the side of security, pc_stub is aliased to pc_stub_copy_in_out. 
template <typename _extra_info_t=void*>
class pc_stub: public pc_stub_copy_in_out<_extra_info_t> 
{
    public: 
       pc_stub(__in_bcount(nInBufferSize) LPVOID pInBuffer, DWORD nInBufferSize):pc_stub_copy_in_out(pInBuffer,nInBufferSize)
       {}
};

template<typename _extra_info_t = void*> 
class pc_proxy: private_copy_ctor
{
protected:
    virtual DWORD pc_call(__out_bcount(nInBufferSize) LPVOID pInBuffer, DWORD nInBufferSize)=0;

public:
    pc_proxy(_extra_info_t ExtraInfo):
        m_ExtraInfo(ExtraInfo)
    {
    }
    ~pc_proxy()
    {
    }
public:     // the following code is generated.

    DWORD call(WORD wFunction )
    {
        detail::pc_message0<_extra_info_t > message(wFunction , m_ExtraInfo);

        return prepare_message_and_pc_call(message);
    };


    template<typename T1>
    DWORD call(WORD wFunction, T1 arg1)
    {
        detail::pc_message1<_extra_info_t, T1> message(wFunction,  m_ExtraInfo,arg1);

        return prepare_message_and_pc_call(message);
    };


    template<typename T1, typename T2>
    DWORD call(WORD wFunction, T1 arg1, T2 arg2)
    {
        detail::pc_message2<_extra_info_t, T1, T2> message(wFunction,  m_ExtraInfo,arg1, arg2);

        return prepare_message_and_pc_call(message);
    };


    template<typename T1, typename T2, typename T3>
    DWORD call(WORD wFunction, T1 arg1, T2 arg2, T3 arg3)
    {
        detail::pc_message3<_extra_info_t, T1, T2, T3> message(wFunction,  m_ExtraInfo,arg1, arg2, arg3);

        return prepare_message_and_pc_call(message);
    };


    template<typename T1, typename T2, typename T3, typename T4>
    DWORD call(WORD wFunction, T1 arg1, T2 arg2, T3 arg3, T4 arg4)
    {
        detail::pc_message4<_extra_info_t, T1, T2, T3, T4> message(wFunction,  m_ExtraInfo,arg1, arg2, arg3, arg4);

        return prepare_message_and_pc_call(message);
    };


    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    DWORD call(WORD wFunction, T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5)
    {
        detail::pc_message5<_extra_info_t, T1, T2, T3, T4, T5> message(wFunction,  m_ExtraInfo,arg1, arg2, arg3, arg4, arg5);

        return prepare_message_and_pc_call(message);
    };


    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
    DWORD call(WORD wFunction, T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5, T6 arg6)
    {
        detail::pc_message6<_extra_info_t, T1, T2, T3, T4, T5, T6> message(wFunction,  m_ExtraInfo,arg1, arg2, arg3, arg4, arg5, arg6);

        return prepare_message_and_pc_call(message);
    };


    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
    DWORD call(WORD wFunction, T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5, T6 arg6, T7 arg7)
    {
        detail::pc_message7<_extra_info_t, T1, T2, T3, T4, T5, T6, T7> message(wFunction,  m_ExtraInfo,arg1, arg2, arg3, arg4, arg5, arg6, arg7);

        return prepare_message_and_pc_call(message);
    };


    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
    DWORD call(WORD wFunction, T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5, T6 arg6, T7 arg7, T8 arg8)
    {
        detail::pc_message8<_extra_info_t, T1, T2, T3, T4, T5, T6, T7, T8> message(wFunction,  m_ExtraInfo,arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);

        return prepare_message_and_pc_call(message);
    };


    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
    DWORD call(WORD wFunction, T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5, T6 arg6, T7 arg7, T8 arg8, T9 arg9)
    {
        detail::pc_message9<_extra_info_t, T1, T2, T3, T4, T5, T6, T7, T8, T9> message(wFunction,  m_ExtraInfo,arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);

        return prepare_message_and_pc_call(message);
    };


    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
    DWORD call(WORD wFunction, T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5, T6 arg6, T7 arg7, T8 arg8, T9 arg9, T10 arg10)
    {
        detail::pc_message10<_extra_info_t, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> message(wFunction,  m_ExtraInfo,arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);

        return prepare_message_and_pc_call(message);
    };


    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
    DWORD call(WORD wFunction, T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5, T6 arg6, T7 arg7, T8 arg8, T9 arg9, T10 arg10, T11 arg11)
    {
        detail::pc_message11<_extra_info_t, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11> message(wFunction,  m_ExtraInfo,arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11);

        return prepare_message_and_pc_call(message);
    };


    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
    DWORD call(WORD wFunction, T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5, T6 arg6, T7 arg7, T8 arg8, T9 arg9, T10 arg10, T11 arg11, T12 arg12)
    {
        detail::pc_message12<_extra_info_t, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12> message(wFunction,  m_ExtraInfo,arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12);

        return prepare_message_and_pc_call(message);
    };


    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
    DWORD call(WORD wFunction, T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5, T6 arg6, T7 arg7, T8 arg8, T9 arg9, T10 arg10, T11 arg11, T12 arg12, T13 arg13)
    {
        detail::pc_message13<_extra_info_t, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13> message(wFunction,  m_ExtraInfo,arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13);

        return prepare_message_and_pc_call(message);
    };

protected:
    template <typename msg_t>
    DWORD getCbForStream(const msg_t& message,DWORD& cbStream)
    {
        NullAppendStream countingStream;
        BYTE memory[sizeof(msg_t)];
        DWORD ret = countingStream.Reserve(sizeof(msg_t));

        msg_t*  msgToComputeStreamSize = reinterpret_cast<msg_t*>(memory);
        ret = msgToComputeStreamSize->marshal(countingStream,message);
        if (ret != NO_ERROR)
        {
            return ret;
        }

        cbStream =  countingStream.size();
        return NO_ERROR;
    }
    template <typename msg_t>
    DWORD prepare_message_and_pc_call(msg_t& message)
    {
        DWORD cbStream;
        DWORD ret = getCbForStream(message,cbStream);
        if (ret != NO_ERROR)
        {
            assert(false);
            return ERROR_INVALID_PARAMETER;
        }

        // Allocate memory to store the cloned data.
        ce::auto_ptr<MemoryAppendStream> pStream = MemoryAppendStream::Create(cbStream);
        if (!pStream.valid())
        {
            return ERROR_OUTOFMEMORY;
        }

        MemoryAppendStream& stream = *pStream;

        // Storage for message is the start of the stream.
        stream.Reserve(sizeof(message));
        msg_t* pStubMessage = reinterpret_cast<msg_t*>(stream.start());

        // Marshall the members.
        ret = pStubMessage->marshal(stream,message);
        if (ret != NO_ERROR)
        {
            assert(false);
            return ret;
        }

        const DWORD ret_pc_call = pc_call(pStubMessage, cbStream);

        ret = message.write_back(stream,*pStubMessage);
        // can't do anything on write back error.
        assert (ret == NO_ERROR); 

        return ret_pc_call;
    }

    _extra_info_t m_ExtraInfo;
};

// local_proxy perfrom the pc_call to the function
// passed to local_proxy(PFN_STUB_FUNCTION)
// Useful for unit testing.

class local_proxy:public pc_proxy<>
{
    typedef DWORD (*PFN_STUB_FUNCTION)(LPVOID pInBuffer, DWORD nInBufferSize);
    public:
    local_proxy(PFN_STUB_FUNCTION pfn)
        :m_pfnStub(pfn)
        ,pc_proxy<>(NULL)
    {
    }

    private:
    DWORD pc_call(__out_bcount(nInBufferSize) LPVOID pInBuffer, DWORD nInBufferSize)
    {
        return m_pfnStub(pInBuffer,nInBufferSize);
    }

    const PFN_STUB_FUNCTION m_pfnStub;
    private: 
    void operator=(local_proxy&);
};


// Ioctl proxy will transport an PC call across an IOCTL.
// Can be constructed with a DeviceName and IOCTL or a handle and ioctl.

// TODO: Sample both custroctors.

template<typename _extra_info_t=PVOID>
class ioctl_proxy : public pc_proxy <_extra_info_t>
{
public:
    typedef pc_proxy<_extra_info_t> _Mybase;

    ioctl_proxy(LPCTSTR pszDevice, DWORD dwIoControlCode, _extra_info_t ExtraInfo)
        : m_pszDevice(pszDevice)
          ,m_dwIoControlCode(dwIoControlCode)
          ,_Mybase(ExtraInfo)
          ,m_hDevice(INVALID_HANDLE_VALUE)
          ,m_bOwnDevice(false)
    {}

    ioctl_proxy(HANDLE hDevice,DWORD dwIoControlCode,_extra_info_t ExtraInfo=NULL)
          : _Mybase(ExtraInfo)
          ,m_dwIoControlCode(dwIoControlCode)
          ,m_bOwnDevice(false)
    { 
        attach(hDevice);
    }
    
    ~ioctl_proxy()
    {
        if(m_bOwnDevice && INVALID_HANDLE_VALUE != m_hDevice)
            CloseHandle(m_hDevice);
    }
    
    void attach(HANDLE hDevice)
    {
        if(m_bOwnDevice && INVALID_HANDLE_VALUE != m_hDevice)
            CloseHandle(m_hDevice);
            
        m_hDevice = hDevice;
        m_bOwnDevice = false;
    }

    HANDLE detach()
    {
        HANDLE hRet = m_hDevice;
        m_hDevice = NULL;
        m_bOwnDevice = false;
        return hRet;
    } 
        
protected:
    DWORD pc_call(__out_bcount(nInBufferSize) LPVOID pInBuffer, DWORD nInBufferSize)
    {
        if(INVALID_HANDLE_VALUE == m_hDevice)
        {
            HANDLE hDevice = CreateFile(m_pszDevice, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, 0);
            
            if(INVALID_HANDLE_VALUE != hDevice)
            {
                m_bOwnDevice = true;
                
                if(INVALID_HANDLE_VALUE != InterlockedCompareExchangePointer(&m_hDevice, hDevice, INVALID_HANDLE_VALUE))
                    CloseHandle(hDevice);
        
                assert(INVALID_HANDLE_VALUE != m_hDevice);
            }
        }
        
        if(DeviceIoControl(m_hDevice, 
                           m_dwIoControlCode, 
                           pInBuffer, 
                           nInBufferSize, 
                           NULL, 
                           NULL, 
                           NULL, 
                           NULL))
        {
            return ERROR_SUCCESS;
        }
        else
        {
            // Server function returned FALSE but didn't set last error
            assert(ERROR_SUCCESS != GetLastError());
            
            return GetLastError();
        }
    }
    
protected:
    HANDLE          m_hDevice;
    bool            m_bOwnDevice;
    LPCTSTR         m_pszDevice;
    DWORD           m_dwIoControlCode;
};

}; // namespace ce
