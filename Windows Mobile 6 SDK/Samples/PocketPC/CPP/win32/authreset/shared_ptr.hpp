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

#if !defined(SHARED_PTR_HPP_9287492)
#define SHARED_PTR_HPP_9287492

#include <algorithm>
#include <cassert>

//  This file provides shared_ptr and shared_array class
//  that allow automate memory and resource management.
//  These classes are not safe for use in multithreaded environment.
//

//  Parametrization of shared_ptr that allows it to be used
//  for managing resources as well as memory.
//
template <typename T>
struct shared_ptr_traits
{
    typedef T element_type;
    typedef T value_type;
    typedef T * pointer;
    typedef T & reference;
};


namespace detail
{
    //  A base class for ref count and disposal policies.
    //  By factoring the disposal into this class
    //  shared_ptr is allowed to have different disposal strategies
    //  without the need to have a separate template parameter for it.
    //
    template <typename T>
    class ref_counted_ptr
    {
    public:
        //  type parametrization
        typedef typename shared_ptr_traits<T>::element_type element_type;
        typedef typename shared_ptr_traits<T>::value_type value_type;
        typedef typename shared_ptr_traits<T>::pointer pointer;
        typedef typename shared_ptr_traits<T>::reference reference;

        ref_counted_ptr(pointer p)
            : m_count(1)
            , m_ptr(p)
        {}

        virtual ~ref_counted_ptr() {}

        void addref()
        {
            ++m_count;
        }

        int release()
        {
            assert(m_count);

            if (--m_count == 0)
                dispose();
            return m_count;
        }

        pointer get() const
        {
            return m_ptr;
        }

        void set(pointer p)
        {
            m_ptr = p;
        }

        virtual void dispose() = 0;

    protected:
        int m_count;
        pointer m_ptr;
    };

    //  Concrete implementation for dispose policy
    //  defined by a template parameter.
    //  Virtual dispose() method allows to hide that template parameter from
    //  shared_ptr class.
    //
    template <typename T, typename D>
    class ref_counted_ptr_impl : public ref_counted_ptr<T>
    {
    public:
        //  type parametrization
        typedef typename shared_ptr_traits<T>::element_type element_type;
        typedef typename shared_ptr_traits<T>::value_type value_type;
        typedef typename shared_ptr_traits<T>::pointer pointer;
        typedef typename shared_ptr_traits<T>::reference reference;

        ref_counted_ptr_impl(pointer p)
            : ref_counted_ptr(p)
        {}

        ref_counted_ptr_impl(pointer p, D d)
            : ref_counted_ptr(p)
            , m_deleter(d)
        {}

        //  Dispose the object what we own with a deleter
        //  that was used to instantiate this class
        //
        virtual void dispose()
        {
            m_deleter(m_ptr);
        }

    private:
        D m_deleter;
    };

    //  Default deleter for pointers
    //
    template <typename T>
    struct default_deleter
    {
        void operator()(T * p) const
        {
            delete p;
        }
    };

    //  Default deleter for arrays
    //
    template <typename T>
    struct default_array_deleter
    {
        void operator()(T * p) const
        {
            delete [] p;
        }
    };
}


//  shared_ptr class provides the ability to manage
//  memory and other resources in a shared manner.
//  It uses reference counting strategy.
//
template <typename T>
class shared_ptr
{
public:
    //  type parametrization
    typedef typename shared_ptr_traits<T>::element_type element_type;
    typedef typename shared_ptr_traits<T>::value_type value_type;
    typedef typename shared_ptr_traits<T>::pointer pointer;
    typedef typename shared_ptr_traits<T>::reference reference;

    shared_ptr(pointer p = NULL)
        : m_ptr(new detail::ref_counted_ptr_impl<T, detail::default_deleter<T> >(p))
    {}

    //  Create a shared_ptr with a specified deleter.
    //  A deleter can be a function, or a class with operator().
    //
    template <typename D>
    shared_ptr(pointer p, D d)
        : m_ptr(new detail::ref_counted_ptr_impl<T, D>(p, d))
    {}

    shared_ptr(shared_ptr<T> const & rhs)
        : m_ptr(rhs.m_ptr)
    {
        m_ptr->addref();
    }

    shared_ptr<T> & operator=(shared_ptr<T> const & rhs)
    {
        shared_ptr<T>(rhs.get()).swap(*this);
        return *this;
    }

    ~shared_ptr()
    {
        if (m_ptr->release() == 0)
            delete m_ptr;
    }

    void swap(shared_ptr<T> & rhs)
    {
        std::swap(m_ptr, rhs->m_ptr);
    }

    //  get pointer explicitly
    pointer get() const
    {
        return m_ptr->get();
    }

    //  release ownership
    pointer release()
    {
        pointer ret = m_ptr->get();
        m_ptr->set(NULL);
        return ret;
    }

    //  dereference
    reference operator*() const
    {
        return *get();
    }

    pointer operator->() const
    {
        return get();
    }

    //  conversion to bool
    typedef pointer (shared_ptr<T>::*unspecified_bool_type)() const;
    
    operator unspecified_bool_type() const
    {
        if (m_ptr->get())
            return &shared_ptr<T>::get;
        else
            return NULL;
    }

private:
    detail::ref_counted_ptr<T> * m_ptr;
};


//  shared_ptr class provides the ability to manage arrays in a shared manner.
//  It uses reference counting strategy.
//  There is a partial support for using shared_array with standard algorithms.
//
template <typename T>
class shared_array
{
public:
    //  type parametrization
    typedef typename shared_ptr_traits<T>::element_type element_type;
    typedef typename shared_ptr_traits<T>::value_type value_type;
    typedef typename shared_ptr_traits<T>::pointer pointer;
    typedef typename shared_ptr_traits<T>::reference reference;

    shared_array(pointer p, size_t s)
        : m_ptr(new detail::ref_counted_ptr_impl<T, detail::default_array_deleter<T> >(p))
        , m_size(s)
    {}

    //  Create a shared_ptr with a specified deleter.
    //  A deleter can be a function, or a class with operator().
    //
    template <typename D>
    shared_array(pointer p, size_t s, D d)
        : m_ptr(new detail::ref_counted_ptr_impl<T, D>(p, d))
        , m_size(s)
    {}

    shared_array(shared_array<T> const & rhs)
        : m_ptr(rhs.m_ptr)
        , m_size(rhs.m_size)
    {
        m_ptr->addref();
    }

    shared_array<T> & operator=(shared_array<T> const & rhs)
    {
        shared_array<T>(rhs.get()).swap(*this);
        return *this;
    }

    ~shared_array()
    {
        if (m_ptr->release() == 0)
            delete m_ptr;
    }

    void swap(shared_array<T> & rhs)
    {
        std::swap(m_ptr, rhs.m_ptr);
        std::swap(m_size, rhs.m_size);
    }

    //  get pointer explicitly
    pointer get() const
    {
        return m_ptr->get();
    }

    //  release ownership
    pointer release()
    {
        pointer ret = m_ptr->get();
        m_ptr->set(NULL);
        return ret;
    }

    // array operations

    reference operator[](ptrdiff_t ind) const
    {
        assert(0 <= ind && ind < static_cast<ptrdiff_t>(m_size));
        return m_ptr->get()[ind];
    }

    size_t size() const
    {
        return m_size;
    }

    pointer begin() const
    {
        return get();
    }

    pointer end() const
    {
        return get() + size();
    }

    //  conversion to bool
    typedef pointer (shared_array<T>::*unspecified_bool_type)() const;
    
    operator unspecified_bool_type() const
    {
        if (m_ptr->get())
            return &shared_array<T>::get;
        else
            return NULL;
    }

private:
    detail::ref_counted_ptr<T> * m_ptr;
    size_t m_size;
};


//  Null deleter.
//  Allows to implement non-owning shared_ptr.
//
template <typename T>
struct null_deleter
{
    void operator()(T *) const {}
};


//  Template specializations for shared_ptr traits
//  that allow shared_ptr to manage Win32 resources.
//  Resources types cannot be dereferenced in any meaningful way
//  and usually they are defined as aliases to integer or pointer types.
//
#define SMART_PTR_HANDLE_TRAITS(HandleT)    \
    template <>                             \
    struct shared_ptr_traits<HandleT>       \
    {                                       \
        typedef HandleT element_type;       \
        typedef HandleT value_type;         \
        typedef HandleT pointer;            \
        typedef HandleT reference;          \
    }                                       \

#endif  // SHARED_PTR_HPP_9287492
