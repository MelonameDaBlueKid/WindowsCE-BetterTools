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

#if !defined(SCOPE_GUARD_H_9827349009890)
#define SCOPE_GUARD_H_9827349009890

//  ScopeGuard ensures that resources are released
//  at the end of the scope.  It's a template
//  class, but you don't have to specify any template parameters,
//  because it relies on the static polymorphism.
//
//  Usage:
//     {
//         HKEY hKey;
//         RegOpenKey(..., &hKey);                                  // acquire the resource
//         ScopeGuard hKeySc = ScopeProtect(hKey, RegCloseKey);    // ensures that hKey is released RegCloseKey when needed
//         // use hKey here ...
//         // ...
//         // if you want to transfer ownership of hKey, call:
//         // hKeySc.release();  -- releases the ownership of the resource
//     }  // hKey is released with RegCloseKey
//

template <typename T, typename D>
class scope_guard;

template <typename T, typename D>
scope_guard<T, D> ScopeProtect(T, D);


class scope_guard_base
{
    template <typename U, typename D>
    friend
    class scope_guard;

public:
    void release() const
    {
        m_released = true;
    }

    bool released() const
    {
        return m_released;
    }

private:
    scope_guard_base()
        : m_released(false)
    {}

private:
    mutable bool m_released;
};


template <typename T, typename D>
class scope_guard : public scope_guard_base
{
    template <typename U, typename E>
    friend
    scope_guard<U, E> ScopeProtect(U, E);

public:
    ~scope_guard()
    {
        if (!released())
            m_deleter(m_obj);
    }

private:
    scope_guard(T obj, D deleter)
        : m_obj(obj)
        , m_deleter(deleter)
    {}

private:
    T m_obj;
    D m_deleter;
};


template <typename T, typename D>
scope_guard<T, D> ScopeProtect(T obj, D deleter)
{
    return scope_guard<T, D>(obj, deleter);
}

typedef scope_guard_base const & ScopeGuard;

#endif
