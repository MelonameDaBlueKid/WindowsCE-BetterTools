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
#ifndef ALIGNED_STORAGE__
#define ALIGNED_STORAGE__

namespace ce
{
    namespace detail
    {
        // workaround for "broken" __declspec(align)
        template <typename T, size_t N>
        struct type_with_alignment;

#define TYPE_WITH_ALIGNMENT(N)                          \
        template <typename T>                           \
        struct type_with_alignment<T, N>                \
        {                                               \
            typedef __declspec(align(N)) T type;        \
        }                                               \

        TYPE_WITH_ALIGNMENT(1);
        TYPE_WITH_ALIGNMENT(2);
        TYPE_WITH_ALIGNMENT(4);
        TYPE_WITH_ALIGNMENT(8);
        TYPE_WITH_ALIGNMENT(16);
        TYPE_WITH_ALIGNMENT(32);
        TYPE_WITH_ALIGNMENT(64);
        TYPE_WITH_ALIGNMENT(128);
        TYPE_WITH_ALIGNMENT(256);
        TYPE_WITH_ALIGNMENT(512);
        TYPE_WITH_ALIGNMENT(1024);

#undef TYPE_WITH_ALIGNMENT

        template <typename T>
        struct align_of
        {
            enum { value = __alignof(T) };
        };

        template <typename T>
        class aligned_storage
        {
        public:
            void * address()
            {
                return &data_[0];
            }

            void const * address() const
            {
                return &data_[0];
            }

            T * ptr()
            {
                return reinterpret_cast<T *>(address());
            }

            T const * ptr() const
            {
                return reinterpret_cast<T const *>(address());
            }

            T & ref()
            {
                return *ptr();
            }

            T const & ref() const
            {
                return *ptr();
            }

        private:
            typename type_with_alignment<char, align_of<T>::value>::type   data_[sizeof(T)];

#ifdef DEBUG
            // reveal a pointer to the internal data with the static type,
            // this simplifies access to the internal data in the debugger
        public:
            aligned_storage()
                : pointer_(ptr())
            {}

        private:
            T const * pointer_;
#endif
        };
    }
}

#endif // ALIGNED_STORAGE__
