//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of your Microsoft Windows CE
// Source Alliance Program license form.  If you did not accept the terms of
// such a license, you are not authorized to use this source code.
//
//////////////////////////////////////////////////////////////////////////////
//
//
//  File:       d3dmxmath.h
//  Content:    D3DMX math types and functions
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __D3DMXMATH_H__
#define __D3DMXMATH_H__

#include <math.h>
#pragma warning(disable:4201) // anonymous unions warning

typedef int FIXED; // signed 15.16 fixed-point format

//===========================================================================
//
// General purpose utilities
//
//===========================================================================
// Handy constants
#define D3DMX_PI    ((FLOAT)  3.141592654f)
#define D3DMX_1BYPI ((FLOAT)  0.318309886f)

#define D3DMX_PI_FXD    ((FIXED)(3.141592654f * 65536.0f))
#define D3DMX_1BYPI_FXD ((FIXED)(0.318309886f * 65536.0f))

// Fixed point conversions
#define D3DMXToFixed( flVal ) ((FIXED)((flVal) * 65536.0f))
#define D3DMXToFloat( fxdVal ) ((FLOAT)(fxdVal) / 65536.0f)

// Fixed point math
#define D3DMXMulFxd( fxdA, fxdB ) ((FIXED)(((_int64)(fxdA) * (_int64)(fxdB)) >> 16))
#define D3DMXDivFxd( fxdA, fxdB ) ((FIXED)(((_int64)(fxdA) << 16) / (_int64)(fxdB)))

// Angle conversions
#define D3DMXToRadian( degree ) ((degree) * (D3DMX_PI / 180.0f))
#define D3DMXToRadianFxd( degree ) D3DMXMulFxd(degree, D3DMXDivFxd(D3DMX_PI_FXD, D3DMXToFixed(180.0f)))
#define D3DMXToDegree( radian ) ((radian) * (180.0f / D3DMX_PI))
#define D3DMXToDegreeFxd( radian ) D3DMXMulFxd(radian, D3DMXDivFxd(D3DMXToFixed(180.0f), D3DMX_PI_FXD))


//===========================================================================
//
// Vectors
//
//===========================================================================

//--------------------------
// 3D Vector
//--------------------------
typedef struct D3DMXVECTOR3
{
#ifdef __cplusplus
public:
    D3DMXVECTOR3() {};
    D3DMXVECTOR3( CONST FLOAT * );
    D3DMXVECTOR3( CONST D3DMVECTOR& );
    D3DMXVECTOR3( FLOAT x, FLOAT y, FLOAT z );

    // casting
    operator FLOAT* ();
    operator CONST FLOAT* () const;

    // assignment operators
    D3DMXVECTOR3& operator += ( CONST D3DMXVECTOR3& );
    D3DMXVECTOR3& operator -= ( CONST D3DMXVECTOR3& );
    D3DMXVECTOR3& operator *= ( FLOAT );
    D3DMXVECTOR3& operator /= ( FLOAT );

    // unary operators
    D3DMXVECTOR3 operator + () const;
    D3DMXVECTOR3 operator - () const;

    // binary operators
    D3DMXVECTOR3 operator + ( CONST D3DMXVECTOR3& ) const;
    D3DMXVECTOR3 operator - ( CONST D3DMXVECTOR3& ) const;
    D3DMXVECTOR3 operator * ( FLOAT ) const;
    D3DMXVECTOR3 operator / ( FLOAT ) const;

    friend D3DMXVECTOR3 operator * ( FLOAT, CONST struct D3DMXVECTOR3& );

    BOOL operator == ( CONST D3DMXVECTOR3& ) const;
    BOOL operator != ( CONST D3DMXVECTOR3& ) const;
    
#endif //__cplusplus
    FLOAT x, y, z;
} D3DMXVECTOR3, *LPD3DMXVECTOR3;

typedef struct D3DMXVECTOR3FXD
{
#ifdef __cplusplus
public:
    D3DMXVECTOR3FXD() {};
    D3DMXVECTOR3FXD( CONST FIXED * );
    D3DMXVECTOR3FXD( CONST D3DMVECTOR& );
    D3DMXVECTOR3FXD( FIXED x, FIXED y, FIXED z );
    D3DMXVECTOR3FXD( FLOAT x, FLOAT y, FLOAT z );

    // casting
    operator FIXED* ();
    operator CONST FIXED* () const;

    // assignment operators
    D3DMXVECTOR3FXD& operator += ( CONST D3DMXVECTOR3FXD& );
    D3DMXVECTOR3FXD& operator -= ( CONST D3DMXVECTOR3FXD& );
    D3DMXVECTOR3FXD& operator *= ( FIXED );
    D3DMXVECTOR3FXD& operator /= ( FIXED );

    // unary operators
    D3DMXVECTOR3FXD operator + () const;
    D3DMXVECTOR3FXD operator - () const;

    // binary operators
    D3DMXVECTOR3FXD operator + ( CONST D3DMXVECTOR3FXD& ) const;
    D3DMXVECTOR3FXD operator - ( CONST D3DMXVECTOR3FXD& ) const;
    D3DMXVECTOR3FXD operator * ( FIXED ) const;
    D3DMXVECTOR3FXD operator / ( FIXED ) const;

    friend D3DMXVECTOR3FXD operator * ( FIXED, CONST struct D3DMXVECTOR3FXD& );

    BOOL operator == ( CONST D3DMXVECTOR3FXD& ) const;
    BOOL operator != ( CONST D3DMXVECTOR3FXD& ) const;
    
#endif //__cplusplus
    FIXED x, y, z;
} D3DMXVECTOR3FXD, *LPD3DMXVECTOR3FXD;

//--------------------------
// 4D Vector
//--------------------------
typedef struct D3DMXVECTOR4
{
#ifdef __cplusplus
public:
    D3DMXVECTOR4() {};
    D3DMXVECTOR4( CONST FLOAT* );
    D3DMXVECTOR4( FLOAT x, FLOAT y, FLOAT z, FLOAT w );

    // casting
    operator FLOAT* ();
    operator CONST FLOAT* () const;

    // assignment operators
    D3DMXVECTOR4& operator += ( CONST D3DMXVECTOR4& );
    D3DMXVECTOR4& operator -= ( CONST D3DMXVECTOR4& );
    D3DMXVECTOR4& operator *= ( FLOAT );
    D3DMXVECTOR4& operator /= ( FLOAT );

    // unary operators
    D3DMXVECTOR4 operator + () const;
    D3DMXVECTOR4 operator - () const;

    // binary operators
    D3DMXVECTOR4 operator + ( CONST D3DMXVECTOR4& ) const;
    D3DMXVECTOR4 operator - ( CONST D3DMXVECTOR4& ) const;
    D3DMXVECTOR4 operator * ( FLOAT ) const;
    D3DMXVECTOR4 operator / ( FLOAT ) const;

    friend D3DMXVECTOR4 operator * ( FLOAT, CONST D3DMXVECTOR4& );

    BOOL operator == ( CONST D3DMXVECTOR4& ) const;
    BOOL operator != ( CONST D3DMXVECTOR4& ) const;

public:
#endif //__cplusplus
    FLOAT x, y, z, w;
} D3DMXVECTOR4, *LPD3DMXVECTOR4;

typedef struct D3DMXVECTOR4FXD
{
#ifdef __cplusplus
public:
    D3DMXVECTOR4FXD() {};
    D3DMXVECTOR4FXD( CONST FIXED* );
    D3DMXVECTOR4FXD( FIXED x, FIXED y, FIXED z, FIXED w );
    D3DMXVECTOR4FXD( FLOAT x, FLOAT y, FLOAT z, FLOAT w );

    // casting
    operator FIXED* ();
    operator CONST FIXED* () const;

    // assignment operators
    D3DMXVECTOR4FXD& operator += ( CONST D3DMXVECTOR4FXD& );
    D3DMXVECTOR4FXD& operator -= ( CONST D3DMXVECTOR4FXD& );
    D3DMXVECTOR4FXD& operator *= ( FIXED );
    D3DMXVECTOR4FXD& operator /= ( FIXED );

    // unary operators
    D3DMXVECTOR4FXD operator + () const;
    D3DMXVECTOR4FXD operator - () const;

    // binary operators
    D3DMXVECTOR4FXD operator + ( CONST D3DMXVECTOR4FXD& ) const;
    D3DMXVECTOR4FXD operator - ( CONST D3DMXVECTOR4FXD& ) const;
    D3DMXVECTOR4FXD operator * ( FIXED ) const;
    D3DMXVECTOR4FXD operator / ( FIXED ) const;

    friend D3DMXVECTOR4FXD operator * ( FIXED, CONST D3DMXVECTOR4FXD& );

    BOOL operator == ( CONST D3DMXVECTOR4FXD& ) const;
    BOOL operator != ( CONST D3DMXVECTOR4FXD& ) const;

public:
#endif //__cplusplus
    FIXED x, y, z, w;
} D3DMXVECTOR4FXD, *LPD3DMXVECTOR4FXD;

//===========================================================================
//
// Matrices
//
//===========================================================================
typedef struct D3DMXMATRIX
{
#ifdef __cplusplus
public:
    D3DMXMATRIX() {};
    D3DMXMATRIX( CONST FLOAT * );
    D3DMXMATRIX( CONST D3DMMATRIX& );
    D3DMXMATRIX( FLOAT _11, FLOAT _12, FLOAT _13, FLOAT _14,
                 FLOAT _21, FLOAT _22, FLOAT _23, FLOAT _24,
                 FLOAT _31, FLOAT _32, FLOAT _33, FLOAT _34,
                 FLOAT _41, FLOAT _42, FLOAT _43, FLOAT _44 );


    // access grants
    FLOAT& operator () ( UINT Row, UINT Col );
    FLOAT  operator () ( UINT Row, UINT Col ) const;

    // casting operators
    operator FLOAT* ();
    operator CONST FLOAT* () const;

    // assignment operators
    D3DMXMATRIX& operator *= ( CONST D3DMXMATRIX& );
    D3DMXMATRIX& operator += ( CONST D3DMXMATRIX& );
    D3DMXMATRIX& operator -= ( CONST D3DMXMATRIX& );
    D3DMXMATRIX& operator *= ( FLOAT );
    D3DMXMATRIX& operator /= ( FLOAT );

    // unary operators
    D3DMXMATRIX operator + () const;
    D3DMXMATRIX operator - () const;

    // binary operators
    D3DMXMATRIX operator * ( CONST D3DMXMATRIX& ) const;
    D3DMXMATRIX operator + ( CONST D3DMXMATRIX& ) const;
    D3DMXMATRIX operator - ( CONST D3DMXMATRIX& ) const;
    D3DMXMATRIX operator * ( FLOAT ) const;
    D3DMXMATRIX operator / ( FLOAT ) const;

    friend D3DMXMATRIX operator * ( FLOAT, CONST D3DMXMATRIX& );

    BOOL operator == ( CONST D3DMXMATRIX& ) const;
    BOOL operator != ( CONST D3DMXMATRIX& ) const;
#endif //__cplusplus
    union {
        struct {
            FLOAT   _11, _12, _13, _14;
            FLOAT   _21, _22, _23, _24;
            FLOAT   _31, _32, _33, _34;
            FLOAT   _41, _42, _43, _44;
        };
        FLOAT m[4][4];
    };

} D3DMXMATRIX, *LPD3DMXMATRIX;

typedef struct D3DMXMATRIXFXD
{
#ifdef __cplusplus
public:
    D3DMXMATRIXFXD() {};
    D3DMXMATRIXFXD( CONST FIXED * );
    D3DMXMATRIXFXD( CONST D3DMMATRIX& );
    D3DMXMATRIXFXD( FIXED _11, FIXED _12, FIXED _13, FIXED _14,
                    FIXED _21, FIXED _22, FIXED _23, FIXED _24,
                    FIXED _31, FIXED _32, FIXED _33, FIXED _34,
                    FIXED _41, FIXED _42, FIXED _43, FIXED _44 );

    // access grants
    FIXED& operator () ( UINT Row, UINT Col );
    FIXED  operator () ( UINT Row, UINT Col ) const;

    // casting operators
    operator FIXED* ();
    operator CONST FIXED* () const;

    // assignment operators
    D3DMXMATRIXFXD& operator *= ( CONST D3DMXMATRIXFXD& );
    D3DMXMATRIXFXD& operator += ( CONST D3DMXMATRIXFXD& );
    D3DMXMATRIXFXD& operator -= ( CONST D3DMXMATRIXFXD& );
    D3DMXMATRIXFXD& operator *= ( FIXED );
    D3DMXMATRIXFXD& operator /= ( FIXED );

    // unary operators
    D3DMXMATRIXFXD operator + () const;
    D3DMXMATRIXFXD operator - () const;

    // binary operators
    D3DMXMATRIXFXD operator * ( CONST D3DMXMATRIXFXD& ) const;
    D3DMXMATRIXFXD operator + ( CONST D3DMXMATRIXFXD& ) const;
    D3DMXMATRIXFXD operator - ( CONST D3DMXMATRIXFXD& ) const;
    D3DMXMATRIXFXD operator * ( FIXED ) const;
    D3DMXMATRIXFXD operator / ( FIXED ) const;

    friend D3DMXMATRIXFXD operator * ( FIXED, CONST D3DMXMATRIXFXD& );

    BOOL operator == ( CONST D3DMXMATRIXFXD& ) const;
    BOOL operator != ( CONST D3DMXMATRIXFXD& ) const;
#endif //__cplusplus
    union {
        struct {
            FIXED   _11, _12, _13, _14;
            FIXED   _21, _22, _23, _24;
            FIXED   _31, _32, _33, _34;
            FIXED   _41, _42, _43, _44;
        };
        FIXED m[4][4];
    };

} D3DMXMATRIXFXD, *LPD3DMXMATRIXFXD;

//===========================================================================
//
// D3DMX math functions:
//
// NOTE:
//  * All these functions can take the same object as in and out parameters.
//
//  * Out parameters are typically also returned as return values, so that
//    the output of one function may be used as a parameter to another.
//
//===========================================================================

//--------------------------
// 3D Vector
//--------------------------

// inline

FLOAT D3DMXVec3Length
    ( CONST D3DMXVECTOR3 *pV );

FIXED D3DMXVec3LengthFxd
    ( CONST D3DMXVECTOR3FXD *pV );

FLOAT D3DMXVec3LengthSq
    ( CONST D3DMXVECTOR3 *pV );

FIXED D3DMXVec3LengthSqFxd
    ( CONST D3DMXVECTOR3FXD *pV );

FLOAT D3DMXVec3Dot
    ( CONST D3DMXVECTOR3 *pV1, CONST D3DMXVECTOR3 *pV2 );

FIXED D3DMXVec3DotFxd
    ( CONST D3DMXVECTOR3FXD *pV1, CONST D3DMXVECTOR3FXD *pV2 );

D3DMXVECTOR3FXD* D3DMXVec3CrossFxd
    ( D3DMXVECTOR3FXD *pOut, CONST D3DMXVECTOR3FXD *pV1, CONST D3DMXVECTOR3FXD *pV2 );

D3DMXVECTOR3* D3DMXVec3Cross
    ( D3DMXVECTOR3 *pOut, CONST D3DMXVECTOR3 *pV1, CONST D3DMXVECTOR3 *pV2 );

D3DMXVECTOR3FXD* D3DMXVec3CrossFxd
    ( D3DMXVECTOR3FXD *pOut, CONST D3DMXVECTOR3FXD *pV1, CONST D3DMXVECTOR3FXD *pV2 );

D3DMXVECTOR3* D3DMXVec3Add
    ( D3DMXVECTOR3 *pOut, CONST D3DMXVECTOR3 *pV1, CONST D3DMXVECTOR3 *pV2 );

D3DMXVECTOR3FXD* D3DMXVec3AddFxd
    ( D3DMXVECTOR3FXD *pOut, CONST D3DMXVECTOR3FXD *pV1, CONST D3DMXVECTOR3FXD *pV2 );

D3DMXVECTOR3* D3DMXVec3Subtract
    ( D3DMXVECTOR3 *pOut, CONST D3DMXVECTOR3 *pV1, CONST D3DMXVECTOR3 *pV2 );

D3DMXVECTOR3FXD* D3DMXVec3SubtractFxd
    ( D3DMXVECTOR3FXD *pOut, CONST D3DMXVECTOR3FXD *pV1, CONST D3DMXVECTOR3FXD *pV2 );

D3DMXVECTOR3* D3DMXVec3Scale
    ( D3DMXVECTOR3 *pOut, CONST D3DMXVECTOR3 *pV, FLOAT s);

D3DMXVECTOR3FXD* D3DMXVec3ScaleFxd
    ( D3DMXVECTOR3FXD *pOut, CONST D3DMXVECTOR3FXD *pV, FIXED s);

// non-inline
#ifdef __cplusplus
extern "C" {
#endif

D3DMXVECTOR3* WINAPI D3DMXVec3Normalize
    ( D3DMXVECTOR3 *pOut, CONST D3DMXVECTOR3 *pV );

D3DMXVECTOR3FXD* WINAPI D3DMXVec3NormalizeFxd
    ( D3DMXVECTOR3FXD *pOut, CONST D3DMXVECTOR3FXD *pV );

// Transform (x, y, z, 1) by matrix.
D3DMXVECTOR4* WINAPI D3DMXVec3Transform
    ( D3DMXVECTOR4 *pOut, CONST D3DMXVECTOR3 *pV, CONST D3DMXMATRIX *pM );

D3DMXVECTOR4FXD* WINAPI D3DMXVec3TransformFxd
    ( D3DMXVECTOR4FXD *pOut, CONST D3DMXVECTOR3FXD *pV, CONST D3DMXMATRIXFXD *pM );

#ifdef __cplusplus
}
#endif



//--------------------------
// 4D Vector
//--------------------------

// inline

FLOAT D3DMXVec4Length
    ( CONST D3DMXVECTOR4 *pV );

FIXED D3DMXVec4LengthFxd
    ( CONST D3DMXVECTOR4FXD *pV );

FLOAT D3DMXVec4LengthSq
    ( CONST D3DMXVECTOR4 *pV );

FIXED D3DMXVec4LengthSqFxd
    ( CONST D3DMXVECTOR4FXD *pV );

FLOAT D3DMXVec4Dot
    ( CONST D3DMXVECTOR4 *pV1, CONST D3DMXVECTOR4 *pV2 );

FIXED D3DMXVec4DotFxd
    ( CONST D3DMXVECTOR4FXD *pV1, CONST D3DMXVECTOR4FXD *pV2 );

D3DMXVECTOR4* D3DMXVec4Add
    ( D3DMXVECTOR4 *pOut, CONST D3DMXVECTOR4 *pV1, CONST D3DMXVECTOR4 *pV2);

D3DMXVECTOR4FXD* D3DMXVec4AddFxd
    ( D3DMXVECTOR4FXD *pOut, CONST D3DMXVECTOR4FXD *pV1, CONST D3DMXVECTOR4FXD *pV2);

D3DMXVECTOR4* D3DMXVec4Subtract
    ( D3DMXVECTOR4 *pOut, CONST D3DMXVECTOR4 *pV1, CONST D3DMXVECTOR4 *pV2);

D3DMXVECTOR4FXD* D3DMXVec4SubtractFxd
    ( D3DMXVECTOR4FXD *pOut, CONST D3DMXVECTOR4FXD *pV1, CONST D3DMXVECTOR4FXD *pV2);

// Minimize each component.  x = min(x1, x2), y = min(y1, y2), ...
D3DMXVECTOR4* D3DMXVec4Scale
    ( D3DMXVECTOR4 *pOut, CONST D3DMXVECTOR4 *pV, FLOAT s);

D3DMXVECTOR4FXD* D3DMXVec4ScaleFxd
    ( D3DMXVECTOR4FXD *pOut, CONST D3DMXVECTOR4FXD *pV, FIXED s);

// non-inline
#ifdef __cplusplus
extern "C" {
#endif

// Cross-product in 4 dimensions.
D3DMXVECTOR4* WINAPI D3DMXVec4Cross
    ( D3DMXVECTOR4 *pOut, CONST D3DMXVECTOR4 *pV1, CONST D3DMXVECTOR4 *pV2,
      CONST D3DMXVECTOR4 *pV3);

D3DMXVECTOR4FXD* WINAPI D3DMXVec4CrossFxd
    ( D3DMXVECTOR4FXD *pOut, CONST D3DMXVECTOR4FXD *pV1, CONST D3DMXVECTOR4FXD *pV2,
      CONST D3DMXVECTOR4FXD *pV3);

D3DMXVECTOR4* WINAPI D3DMXVec4Normalize
    ( D3DMXVECTOR4 *pOut, CONST D3DMXVECTOR4 *pV );

D3DMXVECTOR4FXD* WINAPI D3DMXVec4NormalizeFxd
    ( D3DMXVECTOR4FXD *pOut, CONST D3DMXVECTOR4FXD *pV );

// Transform vector by matrix.
D3DMXVECTOR4* WINAPI D3DMXVec4Transform
    ( D3DMXVECTOR4 *pOut, CONST D3DMXVECTOR4 *pV, CONST D3DMXMATRIX *pM );

D3DMXVECTOR4FXD* WINAPI D3DMXVec4TransformFxd
    ( D3DMXVECTOR4FXD *pOut, CONST D3DMXVECTOR4FXD *pV, CONST D3DMXMATRIXFXD *pM );

#ifdef __cplusplus
}
#endif


//--------------------------
// 4D Matrix
//--------------------------

// inline

D3DMXMATRIX* D3DMXMatrixIdentity
    ( D3DMXMATRIX *pOut );

D3DMXMATRIXFXD* D3DMXMatrixIdentityFxd
    ( D3DMXMATRIXFXD *pOut );

// non-inline
#ifdef __cplusplus
extern "C" {
#endif

FLOAT WINAPI D3DMXMatrixfDeterminant
    ( CONST D3DMXMATRIX *pM );

FIXED WINAPI D3DMXMatrixfDeterminantFxd
    ( CONST D3DMXMATRIXFXD *pM );

// Matrix multiplication.  The result represents the transformation M2
// followed by the transformation M1.  (Out = M1 * M2)
D3DMXMATRIX* WINAPI D3DMXMatrixMultiply
    ( D3DMXMATRIX *pOut, CONST D3DMXMATRIX *pM1, CONST D3DMXMATRIX *pM2 );

D3DMXMATRIXFXD* WINAPI D3DMXMatrixMultiplyFxd
    ( D3DMXMATRIXFXD *pOut, CONST D3DMXMATRIXFXD *pM1, CONST D3DMXMATRIXFXD *pM2 );

D3DMXMATRIX* WINAPI D3DMXMatrixTranspose
    ( D3DMXMATRIX *pOut, CONST D3DMXMATRIX *pM );

D3DMXMATRIXFXD* WINAPI D3DMXMatrixTransposeFxd
    ( D3DMXMATRIXFXD *pOut, CONST D3DMXMATRIXFXD *pM );

// Calculate inverse of matrix.  Inversion my fail, in which case NULL will
// be returned.  The determinant of pM is also returned it pfDeterminant
// is non-NULL.
D3DMXMATRIX* WINAPI D3DMXMatrixInverse
    ( D3DMXMATRIX *pOut, FLOAT *pDeterminant, CONST D3DMXMATRIX *pM );

D3DMXMATRIXFXD* WINAPI D3DMXMatrixInverseFxd
    ( D3DMXMATRIXFXD *pOut, FIXED *pDeterminant, CONST D3DMXMATRIXFXD *pM );

// Build a matrix which scales by (sx, sy, sz)
D3DMXMATRIX* WINAPI D3DMXMatrixScaling
    ( D3DMXMATRIX *pOut, FLOAT sx, FLOAT sy, FLOAT sz );

D3DMXMATRIXFXD* WINAPI D3DMXMatrixScalingFxd
    ( D3DMXMATRIXFXD *pOut, FIXED sx, FIXED sy, FIXED sz );

// Build a matrix which translates by (x, y, z)
D3DMXMATRIX* WINAPI D3DMXMatrixTranslation
    ( D3DMXMATRIX *pOut, FLOAT x, FLOAT y, FLOAT z );

D3DMXMATRIXFXD* WINAPI D3DMXMatrixTranslationFxd
    ( D3DMXMATRIXFXD *pOut, FIXED x, FIXED y, FIXED z );

// Build a matrix which rotates around the X axis
D3DMXMATRIX* WINAPI D3DMXMatrixRotationX
    ( D3DMXMATRIX *pOut, FLOAT Angle );

D3DMXMATRIXFXD* WINAPI D3DMXMatrixRotationXFxd
    ( D3DMXMATRIXFXD *pOut, FIXED Angle );

// Build a matrix which rotates around the Y axis
D3DMXMATRIX* WINAPI D3DMXMatrixRotationY
    ( D3DMXMATRIX *pOut, FLOAT Angle );

D3DMXMATRIXFXD* WINAPI D3DMXMatrixRotationYFxd
    ( D3DMXMATRIXFXD *pOut, FIXED Angle );

// Build a matrix which rotates around the Z axis
D3DMXMATRIX* WINAPI D3DMXMatrixRotationZ
    ( D3DMXMATRIX *pOut, FLOAT Angle );

D3DMXMATRIXFXD* WINAPI D3DMXMatrixRotationZFxd
    ( D3DMXMATRIXFXD *pOut, FIXED Angle );

// Build a matrix which rotates around an arbitrary axis
D3DMXMATRIX* WINAPI D3DMXMatrixRotationAxis
    ( D3DMXMATRIX *pOut, CONST D3DMXVECTOR3 *pV, FLOAT Angle );

D3DMXMATRIXFXD* WINAPI D3DMXMatrixRotationAxisFxd
    ( D3DMXMATRIXFXD *pOut, CONST D3DMXVECTOR3FXD *pV, FIXED Angle );

// Yaw around the Y axis, a pitch around the X axis,
// and a roll around the Z axis.
D3DMXMATRIX* WINAPI D3DMXMatrixRotationYawPitchRoll
    ( D3DMXMATRIX *pOut, FLOAT Yaw, FLOAT Pitch, FLOAT Roll );

D3DMXMATRIXFXD* WINAPI D3DMXMatrixRotationYawPitchRollFxd
    ( D3DMXMATRIXFXD *pOut, FIXED Yaw, FIXED Pitch, FIXED Roll );

// Build a lookat matrix. (left-handed)
D3DMXMATRIX* WINAPI D3DMXMatrixLookAtLH
    ( D3DMXMATRIX *pOut, CONST D3DMXVECTOR3 *pEye, CONST D3DMXVECTOR3 *pAt,
      CONST D3DMXVECTOR3 *pUp );

D3DMXMATRIXFXD* WINAPI D3DMXMatrixLookAtLHFxd
    ( D3DMXMATRIXFXD *pOut, CONST D3DMXVECTOR3FXD *pEye, CONST D3DMXVECTOR3FXD *pAt,
      CONST D3DMXVECTOR3FXD *pUp );

// Build a perspective projection matrix. (left-handed)
D3DMXMATRIX* WINAPI D3DMXMatrixPerspectiveFovLH
    ( D3DMXMATRIX *pOut, FLOAT fovy, FLOAT Aspect, FLOAT zn, FLOAT zf );

D3DMXMATRIXFXD* WINAPI D3DMXMatrixPerspectiveFovLHFxd
    ( D3DMXMATRIXFXD *pOut, FIXED fovy, FIXED Aspect, FIXED zn, FIXED zf );

// Build a perspective projection matrix. (left-handed)
D3DMXMATRIX* WINAPI D3DMXMatrixPerspectiveOffCenterLH
    ( D3DMXMATRIX *pOut, FLOAT l, FLOAT r, FLOAT b, FLOAT t, FLOAT zn,
      FLOAT zf );

D3DMXMATRIXFXD* WINAPI D3DMXMatrixPerspectiveOffCenterLHFxd
    ( D3DMXMATRIXFXD *pOut, FIXED l, FIXED r, FIXED b, FIXED t, FIXED zn,
      FIXED zf );

// Build an ortho projection matrix. (left-handed)
D3DMXMATRIX* WINAPI D3DMXMatrixOrthoOffCenterLH
    ( D3DMXMATRIX *pOut, FLOAT l, FLOAT r, FLOAT b, FLOAT t, FLOAT zn,
      FLOAT zf );

D3DMXMATRIXFXD* WINAPI D3DMXMatrixOrthoOffCenterLHFxd
    ( D3DMXMATRIXFXD *pOut, FIXED l, FIXED r, FIXED b, FIXED t, FIXED zn,
      FIXED zf );

#ifdef __cplusplus
}
#endif

#include "d3dmxmath.inl"

#pragma warning(default:4201)

#endif // __D3DMXMATH_H__
