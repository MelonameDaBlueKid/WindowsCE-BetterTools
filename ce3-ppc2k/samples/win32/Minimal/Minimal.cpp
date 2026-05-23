/*****************************************************************************

  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
  PARTICULAR PURPOSE.
  
    This is sample code and is freely distributable.
    
****************************************************************************/
// Minimal.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

int WINAPI WinMain(	HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPTSTR    lpCmdLine,
                   int       nCmdShow)
{
 	// TODO: Place code here.
  MessageBox (NULL, TEXT ("Hello, Windows CE!"), TEXT ("Hello World"), 0) ;
  
  return 0 ;
}

