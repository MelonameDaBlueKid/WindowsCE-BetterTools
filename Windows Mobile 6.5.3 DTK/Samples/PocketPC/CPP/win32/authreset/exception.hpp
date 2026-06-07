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

#if !defined(EXCEPTION_HPP_92734928)
#define EXCEPTION_HPP_92734928

#include <windows.h>
#include <exception>

//  system_error is an exception that encapsulates HRESULT and WIN32 error code information.
//
class system_error : public std::exception
{
public:
    //  Default constructor gets the error code from GetLastError()
    //
    system_error()
    {
        DWORD error = GetLastError();
        m_hr = HRESULT_FROM_WIN32(error);
    }

    explicit
    system_error(HRESULT hr)
        : m_hr(hr)
    {}
    
    virtual char const * what() const
    {
        return "error from HRESULT";
    }
    
    HRESULT hresult() const
    {
        return m_hr;
    }

private:
    HRESULT m_hr;
};


//  The following functions help check Win32 functions for error
//  return codes and convert errors to appropriate exceptions.
//

inline
void check_hresult(HRESULT hr)
{
    if (FAILED(hr))
        throw system_error(hr);
}

inline
void check_win32result(LONG res)
{
    if (res != ERROR_SUCCESS)
        throw system_error(HRESULT_FROM_WIN32(res));
}

inline
void check_boolresult(BOOL res)
{
    if (!res)
        throw system_error();
}

#endif EXCEPTION_HPP_92734928
