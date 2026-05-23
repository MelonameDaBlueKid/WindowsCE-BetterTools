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
#ifndef __CE_PTR_HPP_INCLUDED__
#define __CE_PTR_HPP_INCLUDED__

#ifndef __WINDOWS__
#include <windows.h>
#endif

/*

    CePtr's provide encapsulation and manipulation of Windows CE pointers.  

*/



class CePtrBase_t
{
private:

    // Handle to the process to which the below ptr belongs to. 
    HPROCESS   m_hProc;

    union
        {
            void*              m_Ptr;
            long                m_PtrLong;
            unsigned long  m_PtrUnsignedLong;
        };

protected:

    //  Default CePtr constructor initializes pointer to 0.
    CePtrBase_t(void);

    CePtrBase_t(void* p, HPROCESS hProcess);

    //    Return the pointer as a C++ pointer.
    void*
    AsCppPtr(
        void
        ) const
    {
        return m_Ptr;
    }

    //    Return the HPROCESS associated with the pointer.
    HPROCESS
    GetProcHandle(
        void
        ) const
    {
        return m_hProc;            
     }

public:

    //    Returns true if the pointer is 0.
    bool
    IsNull(
        void
        ) const
    {
        return m_Ptr == 0;
    }

    //    Returns the pointer as a long value.
    long
    AsLong(
        void
        ) const
    {
        return m_PtrLong;
    }    
};


template <class C_t> class CePtr_t : public CePtrBase_t
{
public:

    CePtr_t<C_t>(
        void
        ) : CePtrBase_t()
    {
    }

    CePtr_t<C_t>(
        C_t         p,
        HPROCESS    hProcess
        ) : CePtrBase_t(p, hProcess)
    {
    }


    C_t
    AsCppPtr(
        void
        ) const
    {
        return static_cast<C_t>(CePtrBase_t::AsCppPtr());
    }

    HPROCESS
    GetProcHandle(
        void
        ) const
    {
        return CePtrBase_t::GetProcHandle();
    }
    
};


#endif


