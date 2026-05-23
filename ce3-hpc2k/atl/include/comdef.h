/***
* comdef.h - Native C++ compiler COM support - main definitions header
*
*	Copyright (C) 1996-2000 Microsoft Corporation
*	All rights reserved.
*
****/

#if _MSC_VER > 1000
#pragma once
#endif

#if !defined(_INC_COMDEF)
#define _INC_COMDEF

#ifndef  __cplusplus
#error Native Compiler support only available in C++ compiler
#endif

#if !defined(_COM_SMARTPTR)
 #if !defined(_INC_COMIP)
  #include <comip.h>
 #endif
 #define _COM_SMARTPTR        _com_ptr_t
 #define _COM_SMARTPTR_LEVEL2 _com_IIID
#endif
#if defined(_COM_SMARTPTR)
 #if !defined(_COM_SMARTPTR_TYPEDEF)
  #if defined(_COM_SMARTPTR_LEVEL2
   #define _COM_SMARTPTR_TYPEDEF(Interface, IID) \
    typedef _COM_SMARTPTR<_COM_SMARTPTR_LEVEL2<Interface, &IID> > \
            Interface ## Ptr
  #else
   #define _COM_SMARTPTR_TYPEDEF(Interface, IID) \
    typedef _COM_SMARTPTR<Interface, &IID> \
            Interface ## Ptr
  #endif
 #endif
#endif

#endif  /* _INC_COMDEF */

