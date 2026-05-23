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

#ifndef _PHYSICSENGINE_H_
#define _PHYSICSENGINE_H_

#if (_MSC_VER >= 1000)
#pragma once
#endif

#include <windows.h>

/// <summary>
/// Defines a common value for a normal frame delay rate expected to be used when displaying output from the physics engine
/// </summary>
#define GESTURE_ANIMATION_FRAME_DELAY_MS    40

#ifdef __cplusplus
extern "C"
{
#endif

/// <summary>
/// Describes the initialization parameters for a physics engine object
/// </summary>
typedef struct tagPHYSICSENGINEINIT
{
    /// <summary>
    /// Specifies the size of the structure in bytes. This must be set to
    /// sizeof(PHYSICSENGINEINIT).
    /// </summary>
    DWORD cbSize;
    /// <summary>
    /// Reserved engine type - must be set to zero
    /// </summary>
    DWORD dwEngineType;
    /// <summary>
    /// Specifies flags which control the behavior of the engine. Currently only
    /// 0 or PHYSICSENGINE_FLAG_USERTIME is supported. Any other values will
    /// cause CreatePhysicsEngine to fail. Specifying 0 here will cause the
    /// physics engine to operate in its default mode, reading the time from
    /// the system clock.
    /// </summary>
    DWORD dwFlags;
    /// <summary>
    /// Specifies the initial velocity in pixels per second
    /// </summary>
    LONG lInitialVelocity; 
    /// <summary>
    /// Specifies the angle at which the animation should occur. The angle is
    /// specified as a value in the range 0-65536, where 0 is -2pi radians,
    /// pointing east, and 65536 is +2pi radians. Angles increase in an 
    /// anti-clockwise direction.
    /// </summary>
    DWORD dwInitialAngle;
    /// <summary>
    /// Specifies the X-axis movement mode. Acceptable values are
    /// PHYSICSENGINE_MOVEMENT_MODE_DECELERATE. Any other value will cause
    /// CreatePhysicsEngine to fail.
    /// </summary>
    BYTE bXAxisMovementMode;
    /// <summary>
    /// Specifies the X-axis boundary mode. Acceptable values are
    /// PHYSICSENGINE_BOUNDARY_MODE_NONE, PHYSICSENGINE_BOUNDARY_MODE_RUBBERBAND
    /// and PHYSICSENGINE_BOUNDARY_MODE_BOUNCE
    /// </summary>
    BYTE bXAxisBoundaryMode;
    /// <summary>
    /// Specifies the Y-axis movement mode. Acceptable values are
    /// PHYSICSENGINE_MOVEMENT_MODE_DECELERATE. Any other value will cause
    /// CreatePhysicsEngine to fail.
    /// </summary>
    BYTE bYAxisMovementMode;
    /// <summary>
    /// Specifies the Y-axis boundary mode. Acceptable values are
    /// PHYSICSENGINE_BOUNDARY_MODE_NONE, PHYSICSENGINE_BOUNDARY_MODE_RUBBERBAND
    /// and PHYSICSENGINE_BOUNDARY_MODE_BOUNCE
    /// </summary>
    BYTE bYAxisBoundaryMode;
    /// <summary>
    /// Rectangle specifying the boundary
    /// </summary>
    RECT rcBoundary;
    /// <summary>
    /// Size of viewable region
    /// </summary>
    SIZE sizeView;
    /// <summary>
    /// Specifies the initial position of the top-left corner of the viewable
    /// region
    /// </summary>
    POINT ptInitialPosition;
    /// <summary>
    /// Specifies the size of an item for snapping. An item size less than one
    /// in either dimension will be treated the same as a one. The physics engine
    /// will only stop on item boundaries. An item size of one will allow the 
    /// physics engine to stop at any point on that axis.
    /// </summary>
    SIZE sizeItem;

    // OLD_GESTURE code: will be removed when WM7-M4 integration is done.
    DWORD dwAnimationType;  
    float flInitialVelocity; 
    float flInitialOffset;
    DWORD dwAngle;
} PHYSICSENGINEINIT;

/// <summary>
/// Describes the state of the physics engine at the current engine time
/// </summary>
typedef struct tagPHYSICSENGINESTATE
{
    /// <summary>
    /// Specifies the size of the structure in bytes. This must be set to 
    /// sizeof(PHYSICSENGINESTATE).
    /// </summary>
    DWORD cbSize; 
    /// <summary>
    /// Specifies the current engine time in milliseconds
    /// </summary>
    DWORD dwTime;
    /// <summary>
    /// Specifies the current position in pixels
    /// </summary>
    POINT ptPosition;
    /// <summary>
    /// Specifies the velocity along the X-axis in pixels per second
    /// </summary>
    LONG lVelocityX;
    /// <summary>
    /// Specifies the velocity along the Y-axis in pixels per second
    /// </summary>
    LONG lVelocityY;
    /// <summary>
    /// Indicates that the animation is complete
    /// </summary>
    BOOL fComplete;

    // OLD_GESTURE code: will be removed when WM7-M4 integration is done.
    BOOL fAnimationComplete;
    float flOffsetX, flOffsetY;
    float flVelocity; 
} PHYSICSENGINESTATE;

/// <summary>
/// Engine never exceeds limits and has no transition at limit
/// <summary>
#define PHYSICSENGINE_ANIMATION_DECELERATE 0    // OLD_GESTURE code: will be removed when WM7-M4 integration is done.
#define PHYSICSENGINE_ANIMATION_RUBBERBAND 2    // OLD_GESTURE code: will be removed when WM7-M4 integration is done.

#define PHYSICSENGINE_BOUNDARY_MODE_NONE 0
/// <summary>
/// Engine can pass limits as part of transition effect
/// </summary>
#define PHYSICSENGINE_BOUNDARY_MODE_RUBBERBAND 1
/// <summary>
/// Engine cannot pass limits as part of transition effect
/// </summary>
#define PHYSICSENGINE_BOUNDARY_MODE_BOUNCE 2

/// <summary>
/// Engine will decelerate over time
/// </summary>
#define PHYSICSENGINE_MOVEMENT_MODE_DECELERATE 0

/// <summary>
/// Specifies that the physics engine should allow the user to specify the time
/// </summary>
#define PHYSICSENGINE_FLAG_USERTIME 1
/// <summary>
/// Reserved for internal physics engine use
/// </summary>
#define PHYSICSENGINE_FLAG_RESERVED_1 0x80000000
/// <summary>
/// Reserved for internal physics engine use
/// </summary>
#define PHYSICSENGINE_FLAG_RESERVED_2 0x40000000
/// <summary>
/// Specifies that the physics engine should be created in panning mode
/// </summary>
#define PHYSICSENGINE_FLAG_PANNINGMODE 2
/// <summary>
/// Internal mask defines all valid flags. Any flags not covered by this will
/// be rejected
/// </summary>
#define PHYSICSENGINE_ALL_FLAGS (PHYSICSENGINE_FLAG_USERTIME | PHYSICSENGINE_FLAG_PANNINGMODE | PHYSICSENGINE_FLAG_RESERVED_1 | PHYSICSENGINE_FLAG_RESERVED_2)

/// <summary>
/// Handle to an instance of the PhysicsEngine. These objects should be
/// destroyed by calling DestroyPhysicsEngine
/// </summary>
DECLARE_HANDLE(HPHYSICSENGINE);

/// <summary>
/// Creates a PhysicsEngine object and configures it with the specified
/// parameters
/// </summary>
/// <param name="pEngineInit">Pointer to PHYSICSENGINEINIT, used to configure
/// the object</param>
/// <param name="phResult">Pointer to a variable of type HPHYSICSENGINE to
/// receive the result</param>
/// <returns>An HRESULT to indicate success or failure. S_OK is returned on 
/// success.</returns>
HRESULT CreatePhysicsEngine(__in const PHYSICSENGINEINIT* pEngineInit, __out HPHYSICSENGINE* phResult);

/// <summary>
/// Destroys a physics engine object
/// </summary>
/// <param name="hEngine">A handle to a physics engine object</param>
/// <returns>An HRESULT to indicate success or failure. S_OK is returned on 
/// success.</returns>
HRESULT DestroyPhysicsEngine(HPHYSICSENGINE hEngine);

/// <summary>
/// Set the current timestamp of the PhysicsEngine object. The time is set to
/// zero upon construction. The time is specified relative to the start of the 
/// animation
/// </summary>
/// <param name="hEngine">A handle to a physics engine object</param>
/// <param name="dwTime">The timestamp</param>
/// <returns>An HRESULT to indicate success or failure. S_OK is returned on 
/// success.</returns>
HRESULT SetPhysicsEngineUserTime(HPHYSICSENGINE hEngine, DWORD dwTime);

/// <summary>
/// Query the state of the physics engine, retrieving the position offset,
/// velocity and completion status of the engine at the time last specified by
/// a call to SetPhysicsEngineUserTime.
/// </summary>
/// <param name="hEngine">A handle to a physics engine object</param>
/// <param name="pState">A pointer to a PHYSICSENGINESTATE structure which
/// receives the state</param>
/// <returns>An HRESULT to indicate success or failure. S_OK is returned on
/// success.</returns>
HRESULT QueryPhysicsEngine(HPHYSICSENGINE hEngine, __out PHYSICSENGINESTATE* pState);

/// <summary>
/// Moves a physics engine in panning mode. Fails with E_UNEXPECTED if the physics
/// engine object is not in panning mode.
/// </summary>
/// <param name="hEngine">A handle to a physics engine object</param>
/// <param name="lOffsetX">Pan offset along the X axis in pixels</param>
/// <param name="lOffsetY">Pan offset along the Y axis in pixels</param>
/// <returns>An HRESULT to indicate success or failure. S_OK is returned on
/// success.</returns>
HRESULT PanPhysicsEngine(HPHYSICSENGINE hEngine, LONG lOffsetX, LONG lOffsetY);

/// <summary>
/// Cause a physics engine in panning mode to enter flicking mode. Fails
/// with E_UNEXPECTED if the physics engine object is not in panning mode.
/// </summary>
/// <param name="hEngine">A handle to a physics engine object</param>
/// <param name="lFlickSpeed">The initial speed of the flick in the
/// direction of travel in pixels per second</param>
/// <param name="dwFlickAngle">The angle of the flick. The angle is
/// specified as a value in the range 0-65536, where 0 is -2pi radians,
/// pointing east, and 65536 is +2pi radians. Angles increase in an 
/// anti-clockwise direction.</param>
/// <returns>An HRESULT to indicate success or failure. S_OK is returned on
/// success.</returns>
HRESULT FlickPhysicsEngine(HPHYSICSENGINE hEngine, LONG lFlickSpeed, DWORD dwFlickAngle);

#ifdef __cplusplus
}
#endif

#endif // _PHYSICSENGINE_H_
