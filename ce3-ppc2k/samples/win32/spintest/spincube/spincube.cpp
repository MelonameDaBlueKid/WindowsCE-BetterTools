/******************************************************************************\
*
*  MODULE:      SPINCUBE.C
*
*
*  PURPOSE:     To provide a generic Windows CE dynamic link library
*               sample demonstrating the use of DLL entry points, exported
*               variables, using C runtime in a DLL, etc...
*
*               This module also provides a functional example of how
*               to create a custom control library which may be used by
*               applications (i.e. SPINTEST.EXE).
*
*
*  FUNCTIONS:   DLLMain()      - Registers spincube class when a
*                                      process loads this DLL.
*               SpincubeSizeToText() - Called by DLGEDIT if user requests
*                                      that control be sized to fit text.
*               SpincubeWndProc()    - Window procedure for spincube
*                                      control.
*               SpincubeDlgProc()    - Procedure for control style dialog.
*
*                           Microsoft Developer Support
*                  Copyright (c) 1992-1997 Microsoft Corporation
*
\******************************************************************************/

#include <windows.h>
#include <stdlib.h>
#include "spincube.h"

//
// function prototype for Paint() in PAINT.C
//

void Paint (HWND);


//
// Declared below are the module's 2 exported variables.
//
//   giNumSpincubesThisProcess is an instance variable that contains
//   the number of (existing) Spincube controls created by the
//   current process.
//
//   giNumSpincubesAllProcesses is a shared (between processes) variable
//   which contains the total number of (existing) Spincube controls
//   created by all processes in the system.
//
//

int giNumSpincubesThisProcess = 0;
int giNumSpincubesAllProcesses = 0;

//
// Some global vars for this module
//

HANDLE    ghMod;   // DLL's module handle

/******************************************************************************\
*
*  FUNCTION:    DLLMain
*
*  INPUTS:      hDLL       - DLL module handle
*               dwReason   - reason being called (e.g. process attaching)
*               lpReserved - reserved
*
*  RETURNS:     TRUE if initialization passed, or
*               FALSE if initialization failed.
*
*  COMMENTS:    On DLL_PROCESS_ATTACH registers the SPINCUBECLASS
*
*               DLL initialization serialization is guaranteed within a
*               process (if multiple threads then DLL entry points are
*               serialized), but is not guaranteed across processes.
*
*               When synchronization objects are created, it is necesaary
*               to check the return code of GetLastError even if the create
*               call succeeded. If the object existed, ERROR_ALREADY_EXISTED
*               will be returned.
*
*               If your DLL uses any C runtime functions then you should
*               always call _CRT_INIT so that the C runtime can initialize
*               itself appropriately. Failure to do this may result in
*               indeterminate behavior. When the DLL entry point is called
*               for DLL_PROCESS_ATTACH & DLL_THREAD_ATTACH circumstances,
*               _CRT_INIT should be called before any other initilization
*               is performed. When the DLL entry point is called for
*               DLL_PROCESS_DETACH & DLL_THREAD_DETACH circumstances,
*               _CRT_INIT should be called after all cleanup has been
*               performed, i.e. right before the function returns.
*
\******************************************************************************/

BOOL WINAPI DllMain (HANDLE hDLL, DWORD dwReason, LPVOID lpReserved)
{
  ghMod = hDLL;
  switch (dwReason)
  {
    case DLL_PROCESS_ATTACH:
    {
      WNDCLASS wc;

      wc.style = 0;  
      wc.lpfnWndProc   = (WNDPROC) SpincubeWndProc;
      wc.cbClsExtra    = 0;
      wc.cbWndExtra    = SPINCUBE_EXTRA;
      wc.hInstance     = (HINSTANCE) hDLL;
      wc.hIcon         = NULL;
      wc.hCursor     = NULL;
      wc.hbrBackground = NULL;
      wc.lpszMenuName  = NULL;
      wc.lpszClassName = SPINCUBECLASS;

      if (!RegisterClass (&wc))
      {
        MessageBox (NULL,
                    (LPCTSTR) TEXT("DLLMain(): RegisterClass() failed"),
                    (LPCTSTR) TEXT("Err! - SPINCUBE.DLL"),
                    MB_OK | MB_ICONEXCLAMATION);

        return FALSE;
      }
      break;
    }

    case DLL_PROCESS_DETACH:
    {
      if (!UnregisterClass ((LPCTSTR) SPINCUBECLASS, (HINSTANCE) hDLL ))
      {
        MessageBox (NULL,
                    (LPCTSTR) TEXT("DLLMain(): UnregisterClass() failed"),
                    (LPCTSTR) TEXT("Err! - SPINCUBE.DLL"),
                    MB_OK | MB_ICONEXCLAMATION);

        return FALSE;
      }
      break;
    }

    default:
      break;
  }
  return TRUE;
}


/******************************************************************************\
*
*  FUNCTION:    SpincubeSizeToText
*
*  INPUTS:      flStyle    - control style
*               flExtStyle - control extended style
*               hFont      - handle of font used to draw text
*               pszText    - control text
*
*  RETURNS:     Width (in pixels) control must be to accomodate text, or
*               -1 if an error occurs.
*
*  COMMENTS:    Just no-op here (since we never actually display text in
*               the control it doesn't need to be resized).
*
\******************************************************************************/

INT CALLBACK SpincubeSizeToText (DWORD flStyle,
                         DWORD flExtStyle,
                                 HFONT hFont,
                         LPTSTR pszText)
{
  return -1;
}



/******************************************************************************\
*
*  FUNCTION:    SpincubeWndProc (standard window procedure INPUTS/RETURNS)
*
*  COMMENTS:    This is the window procedure for our custom control. At
*               creation we alloc a SPINCUBEINFO struct, initialize it,
*               and associate it with this particular control. We also
*               start a timer which will invalidate the window every so
*               often; this causes a repaint, and the cube gets drawn in
*               a new position. Left button clicks will turn toggle the
*               erase option, causing a "trail" of cubes to be left when
*               off. Right button clicks will toggle the motion state of
*               the control (and turn the timer on/off).
*
\******************************************************************************/

LRESULT CALLBACK SpincubeWndProc (HWND hwnd, UINT msg, WPARAM wParam,
                                  LPARAM lParam)
{
  switch (msg)
  {
    case WM_CREATE:
    {
      //
      // Alloc & init a SPINCUBEINFO struct for this particular control
      //
      HDC            hdc;
      LPCREATESTRUCT lpcs = (LPCREATESTRUCT) lParam;
      PSPINCUBEINFO  pSCI = (PSPINCUBEINFO) LocalAlloc (LPTR,
                                                        sizeof(SPINCUBEINFO));
      if (!pSCI)
      {
        MessageBox (NULL,
                    (LPCTSTR) TEXT("SpincubeWndProc(): LocalAlloc() failed"),
                    (LPCTSTR) TEXT("Err! - SPINCUBE.DLL"),
                    MB_OK | MB_ICONEXCLAMATION);
        return -1;
      }

      //
      // Alloc the compatible DC for this control.
      //
      hdc = GetDC (hwnd);

      if ((pSCI->hdcCompat = CreateCompatibleDC (hdc)) == NULL)
      {
        MessageBox (NULL,
                    (LPCTSTR) TEXT("SpincubeWndProc(): CreateCompatibleDC() failed"),
                    (LPCTSTR) TEXT("Err! - SPINCUBE.DLL"),
                    MB_OK | MB_ICONEXCLAMATION);
        return -1;
      }
      ReleaseDC (hwnd, hdc);

      //
      // Initialize this instance structure
      //
      pSCI->fCurrentXRotation =
      pSCI->fCurrentYRotation =
      pSCI->fCurrentZRotation = (float) 0.0;

      pSCI->fCurrentXRotationInc =
      pSCI->fCurrentYRotationInc =
      pSCI->fCurrentZRotationInc = (float) 0.2617; // a random # (15 degrees)

      pSCI->iCurrentXTranslation =
      pSCI->iCurrentYTranslation =
      pSCI->iCurrentZTranslation = 0;

      //
      // All these calculations so the cubes start out with random movements.
      //
      if ((pSCI->iCurrentXTranslationInc = (Random() % 10) + 2) > 7)
        pSCI->iCurrentXTranslationInc = -pSCI->iCurrentXTranslationInc;

      if ((pSCI->iCurrentYTranslationInc = (Random() % 10) + 2) <= 7)
        pSCI->iCurrentYTranslationInc = -pSCI->iCurrentYTranslationInc;

    if ((pSCI->iCurrentZTranslationInc = (Random() % 10) + 2) > 7)
        pSCI->iCurrentZTranslationInc = -pSCI->iCurrentZTranslationInc;

      pSCI->rcCubeBoundary.left   =
      pSCI->rcCubeBoundary.top    = 0;
      pSCI->rcCubeBoundary.right  = lpcs->cx;
      pSCI->rcCubeBoundary.bottom = lpcs->cy;

      pSCI->iOptions  = SPINCUBE_REPAINT_BKGND;
      pSCI->hbmCompat = NULL;

      SetWindowLong (hwnd, GWL_SPINCUBEDATA, (LONG) pSCI);
      SetTimer (hwnd, SPIN_EVENT, SPIN_INTERVAL, NULL);

      //
      // Increment the count vars
      //
      giNumSpincubesThisProcess++;
      giNumSpincubesAllProcesses++;

      break;
    }

    case WM_PAINT:
      Paint (hwnd);
      break;

    case WM_TIMER:
      switch (wParam)
      {
        case SPIN_EVENT:
        {
          PSPINCUBEINFO pSCI = (PSPINCUBEINFO) GetWindowLong (hwnd,
                                                              GWL_SPINCUBEDATA);

          InvalidateRect (hwnd, &pSCI->rcCubeBoundary, FALSE);

          break;
        }
      }
      break;

    case WM_LBUTTONUP:
    {
      // Since the Right button on Windows CE is not supported,
      // we use the state of the CTRL button at the time of
      // processing this message to simulate an RBUTTONUP event.
      // IF so, we stop the cube from spinning.
      // ELSE, we toggle the erase state of the control
      //        and hence the trailings.
      if ( wParam == MK_CONTROL )
      {
        //
        // Toggle the motion state of the control
        //
        if (IN_MOTION(hwnd))
        {
        KillTimer (hwnd, SPIN_EVENT);
        SetWindowLong (hwnd, GWL_STYLE,
                 GetWindowLong (hwnd, GWL_STYLE) & ~SS_INMOTION);
        }
        else
        {
        SetTimer (hwnd, SPIN_EVENT, SPIN_INTERVAL, NULL);
        SetWindowLong (hwnd, GWL_STYLE,
                 GetWindowLong (hwnd, GWL_STYLE) | SS_INMOTION);
        }
        break;
      }
      else
      {
        //
        // Toggle the erase state of the control
        //
        if (DO_ERASE(hwnd))
          SetWindowLong (hwnd, GWL_STYLE,
                   GetWindowLong (hwnd, GWL_STYLE) & ~SS_ERASE);
        else
        {
          //
          // Repaint the entire control to get rid of the cube trails
          //
          PSPINCUBEINFO pSCI = (PSPINCUBEINFO) GetWindowLong (hwnd,
                                    GWL_SPINCUBEDATA);
          SetWindowLong (hwnd, GWL_STYLE,
                   GetWindowLong (hwnd, GWL_STYLE) | SS_ERASE);
          pSCI->iOptions |= SPINCUBE_REPAINT_BKGND;
          InvalidateRect (hwnd, NULL, FALSE);
          SendMessage (hwnd, WM_PAINT, 0, 0);
        }
      }
    }
    break;

    case WM_SIZE:
      if (wParam == SIZE_MAXIMIZED || wParam == SIZE_RESTORED)
      {
        PSPINCUBEINFO pSCI = (PSPINCUBEINFO) GetWindowLong (hwnd,
                                                            GWL_SPINCUBEDATA);
        //
        // Get a new bitmap which is the new size of our window
        //

        HDC hdc = GetDC (hwnd);
        HBITMAP hbmTemp = CreateCompatibleBitmap (hdc,
                                                  (int) LOWORD (lParam),
                                                  (int) HIWORD (lParam));
        if (!hbmTemp)
        {
          //
          // Scream, yell, & committ an untimely demise...
          //

          MessageBox (NULL,
                      (LPCTSTR) TEXT("SpincubeWndProc(): CreateCompatibleBitmap() failed"),
                      (LPCTSTR) TEXT("Err! - SPINCUBE.DLL"),
                      MB_OK | MB_ICONEXCLAMATION);
          DestroyWindow (hwnd);
        }

        pSCI->hbmSave = (HBITMAP) SelectObject (pSCI->hdcCompat, hbmTemp);
        if (pSCI->hbmCompat)
          DeleteObject (pSCI->hbmCompat);
        ReleaseDC    (hwnd, hdc);
        pSCI->hbmCompat = hbmTemp;


        //
        // Reset the translation so the cube doesn't go spinning off into
        //   space somewhere- we'd never see it again!
        //

        pSCI->iCurrentXTranslation =
        pSCI->iCurrentYTranslation =
        pSCI->iCurrentZTranslation = 0;

        //
        // All these calculations so the cube starts out with random movements,
        //
        if ((pSCI->iCurrentXTranslationInc = (Random() % 10) + 2) > 7)
        pSCI->iCurrentXTranslationInc = -pSCI->iCurrentXTranslationInc;

    if ((pSCI->iCurrentYTranslationInc = (Random() % 10) + 2) <= 7)
        pSCI->iCurrentYTranslationInc = -pSCI->iCurrentYTranslationInc;

    if ((pSCI->iCurrentZTranslationInc = (Random() % 10) + 2) > 7)
        pSCI->iCurrentZTranslationInc = -pSCI->iCurrentZTranslationInc;

        pSCI->rcCubeBoundary.left   =
        pSCI->rcCubeBoundary.top    = 0;
        pSCI->rcCubeBoundary.right  = (int) LOWORD (lParam);
        pSCI->rcCubeBoundary.bottom = (int) HIWORD (lParam);

        pSCI->iOptions |= SPINCUBE_REPAINT_BKGND;

        InvalidateRect (hwnd, NULL, FALSE);
      }

      break;

    case WM_DESTROY:
    {
      PSPINCUBEINFO pSCI = (PSPINCUBEINFO) GetWindowLong (hwnd,
                                                          GWL_SPINCUBEDATA);
      //
      // Clean up all the resources used for this control
      //

      if (IN_MOTION(hwnd))

        KillTimer (hwnd, SPIN_EVENT);

      SelectObject (pSCI->hdcCompat, pSCI->hbmSave);
      DeleteObject (pSCI->hbmCompat);
      DeleteDC     (pSCI->hdcCompat);

      LocalFree (LocalHandle ((LPVOID) pSCI));


      //
      // Decrement the global count vars
      //

      giNumSpincubesThisProcess--;
      giNumSpincubesAllProcesses--;

      break;
    }

    default:
      return (DefWindowProc(hwnd, msg, wParam, lParam));
  }

  return ((LONG) TRUE);
}



int GetgiNumSpincubesThisProcess( void )
{
  return giNumSpincubesThisProcess;
}

int GetgiNumSpincubesAllProcesses( void )
{
  return giNumSpincubesAllProcesses;
}
