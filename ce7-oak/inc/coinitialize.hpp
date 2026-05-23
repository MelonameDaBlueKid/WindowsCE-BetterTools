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

#ifndef		__INCLUDED_COINITIALIZE_HPP__
#define		__INCLUDED_COINITIALIZE_HPP__


// CoInitialize_t
class CoInitialize_t
{
private:
	bool		m_IsValid;

public:
	CoInitialize_t(
		void
		): m_IsValid( false )
	{
		
		HRESULT Result = CoInitializeEx(NULL, COINIT_MULTITHREADED);
		m_IsValid = SUCCEEDED( Result );
		if( !m_IsValid )
			{
			RETAILMSG( 1, ( L"Error starting COM; HResult %d", Result ) );
			}
	}

	~CoInitialize_t(
		void
		)
	{
		
		CoUninitialize(); 
	}

	bool
	IsValid(
		void
		)
	{
		return	m_IsValid;
	}
};


#endif	//__INCLUDED_COINITIALIZE_HPP__

