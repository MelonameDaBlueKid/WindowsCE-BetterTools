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
//  File:       d3dmxmath.inl
//  Content:    D3DMX math inline functions
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __D3DMXMATH_INL__
#define __D3DMXMATH_INL__

#ifdef UNDER_CE
#define sqrtf(d)        (FLOAT)sqrt((double)d)
#define sinf(d)         (FLOAT)sin((double)d)
#define cosf(d)         (FLOAT)cos((double)d)
#define asinf(d)        (FLOAT)asin((double)d)
#define acosf(d)        (FLOAT)acos((double)d)
#define atan2f(d1,d2)   (FLOAT)atan2((double)d1,(double)d2)
#define floorf(d)       (FLOAT)floor((double)d)
#endif

//===========================================================================
//
// Inline Class Methods
//
//===========================================================================

#ifdef __cplusplus


//--------------------------
// 3D Vector
//--------------------------
D3DMXINLINE
D3DMXVECTOR3::D3DMXVECTOR3( CONST FLOAT *pf )
{
#ifdef D3DMX_DEBUG
    if(!pf)
        return;
#endif

    x = pf[0];
    y = pf[1];
    z = pf[2];
}

D3DMXINLINE
D3DMXVECTOR3FXD::D3DMXVECTOR3FXD( CONST FIXED *pf )
{
#ifdef D3DMX_DEBUG
    if(!pf)
        return;
#endif

    x = pf[0];
    y = pf[1];
    z = pf[2];
}

D3DMXINLINE
D3DMXVECTOR3::D3DMXVECTOR3( CONST D3DMVECTOR& v )
{
    x = *(FLOAT*)&v.x;
    y = *(FLOAT*)&v.y;
    z = *(FLOAT*)&v.z;
}

D3DMXINLINE
D3DMXVECTOR3FXD::D3DMXVECTOR3FXD( CONST D3DMVECTOR& v )
{
    x = *(FIXED*)&v.x;
    y = *(FIXED*)&v.y;
    z = *(FIXED*)&v.z;
}

D3DMXINLINE
D3DMXVECTOR3::D3DMXVECTOR3( FLOAT fx, FLOAT fy, FLOAT fz )
{
    x = fx;
    y = fy;
    z = fz;
}

D3DMXINLINE
D3DMXVECTOR3FXD::D3DMXVECTOR3FXD( FIXED fx, FIXED fy, FIXED fz )
{
    x = fx;
    y = fy;
    z = fz;
}

D3DMXINLINE
D3DMXVECTOR3FXD::D3DMXVECTOR3FXD( FLOAT fx, FLOAT fy, FLOAT fz )
{
    x = D3DMXToFixed(fx);
    y = D3DMXToFixed(fy);
    z = D3DMXToFixed(fz);
}

// casting
D3DMXINLINE
D3DMXVECTOR3::operator FLOAT* ()
{
    return (FLOAT *) &x;
}

D3DMXINLINE
D3DMXVECTOR3FXD::operator FIXED* ()
{
    return (FIXED *) &x;
}

D3DMXINLINE
D3DMXVECTOR3::operator CONST FLOAT* () const
{
    return (CONST FLOAT *) &x;
}

D3DMXINLINE
D3DMXVECTOR3FXD::operator CONST FIXED* () const
{
    return (CONST FIXED *) &x;
}

// assignment operators
D3DMXINLINE D3DMXVECTOR3&
D3DMXVECTOR3::operator += ( CONST D3DMXVECTOR3& v )
{
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

D3DMXINLINE D3DMXVECTOR3FXD&
D3DMXVECTOR3FXD::operator += ( CONST D3DMXVECTOR3FXD& v )
{
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

D3DMXINLINE D3DMXVECTOR3&
D3DMXVECTOR3::operator -= ( CONST D3DMXVECTOR3& v )
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

D3DMXINLINE D3DMXVECTOR3FXD&
D3DMXVECTOR3FXD::operator -= ( CONST D3DMXVECTOR3FXD& v )
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

D3DMXINLINE D3DMXVECTOR3&
D3DMXVECTOR3::operator *= ( FLOAT f )
{
    x *= f;
    y *= f;
    z *= f;
    return *this;
}

D3DMXINLINE D3DMXVECTOR3FXD&
D3DMXVECTOR3FXD::operator *= ( FIXED f )
{
    x = D3DMXMulFxd(x, f);
    y = D3DMXMulFxd(y, f);
    z = D3DMXMulFxd(z, f);
    return *this;
}

D3DMXINLINE D3DMXVECTOR3&
D3DMXVECTOR3::operator /= ( FLOAT f )
{
    FLOAT fInv = 1.0f / f;
    x *= fInv;
    y *= fInv;
    z *= fInv;
    return *this;
}

D3DMXINLINE D3DMXVECTOR3FXD&
D3DMXVECTOR3FXD::operator /= ( FIXED f )
{
    FIXED fInv = D3DMXDivFxd(D3DMXToFixed(1.0f), f);
    x = D3DMXMulFxd(x, fInv);
    y = D3DMXMulFxd(y, fInv);
    z = D3DMXMulFxd(z, fInv);
    return *this;
}

// unary operators
D3DMXINLINE D3DMXVECTOR3
D3DMXVECTOR3::operator + () const
{
    return *this;
}

D3DMXINLINE D3DMXVECTOR3FXD
D3DMXVECTOR3FXD::operator + () const
{
    return *this;
}

D3DMXINLINE D3DMXVECTOR3
D3DMXVECTOR3::operator - () const
{
    return D3DMXVECTOR3(-x, -y, -z);
}

D3DMXINLINE D3DMXVECTOR3FXD
D3DMXVECTOR3FXD::operator - () const
{
    return D3DMXVECTOR3FXD(-x, -y, -z);
}


// binary operators
D3DMXINLINE D3DMXVECTOR3
D3DMXVECTOR3::operator + ( CONST D3DMXVECTOR3& v ) const
{
    return D3DMXVECTOR3(x + v.x, y + v.y, z + v.z);
}

D3DMXINLINE D3DMXVECTOR3FXD
D3DMXVECTOR3FXD::operator + ( CONST D3DMXVECTOR3FXD& v ) const
{
    return D3DMXVECTOR3FXD(x + v.x, y + v.y, z + v.z);
}

D3DMXINLINE D3DMXVECTOR3
D3DMXVECTOR3::operator - ( CONST D3DMXVECTOR3& v ) const
{
    return D3DMXVECTOR3(x - v.x, y - v.y, z - v.z);
}

D3DMXINLINE D3DMXVECTOR3FXD
D3DMXVECTOR3FXD::operator - ( CONST D3DMXVECTOR3FXD& v ) const
{
    return D3DMXVECTOR3FXD(x - v.x, y - v.y, z - v.z);
}

D3DMXINLINE D3DMXVECTOR3
D3DMXVECTOR3::operator * ( FLOAT f ) const
{
    return D3DMXVECTOR3(x * f, y * f, z * f);
}

D3DMXINLINE D3DMXVECTOR3FXD
D3DMXVECTOR3FXD::operator * ( FIXED f ) const
{
    return D3DMXVECTOR3FXD(D3DMXMulFxd(x, f), D3DMXMulFxd(y, f), D3DMXMulFxd(z, f));
}

D3DMXINLINE D3DMXVECTOR3
D3DMXVECTOR3::operator / ( FLOAT f ) const
{
    FLOAT fInv = 1.0f / f;
    return D3DMXVECTOR3(x * fInv, y * fInv, z * fInv);
}

D3DMXINLINE D3DMXVECTOR3FXD
D3DMXVECTOR3FXD::operator / ( FIXED f ) const
{
    FIXED fInv = D3DMXDivFxd(D3DMXToFixed(1.0f), f);
    return D3DMXVECTOR3FXD(D3DMXMulFxd(x, fInv), D3DMXMulFxd(y, fInv), D3DMXMulFxd(z, fInv));
}

D3DMXINLINE D3DMXVECTOR3
operator * ( FLOAT f, CONST struct D3DMXVECTOR3& v )
{
    return D3DMXVECTOR3(f * v.x, f * v.y, f * v.z);
}

D3DMXINLINE D3DMXVECTOR3FXD
operator * ( FIXED f, CONST struct D3DMXVECTOR3FXD& v )
{
    return D3DMXVECTOR3FXD(D3DMXMulFxd(f, v.x), D3DMXMulFxd(f, v.y), D3DMXMulFxd(f, v.z));
}

D3DMXINLINE BOOL
D3DMXVECTOR3::operator == ( CONST D3DMXVECTOR3& v ) const
{
    return x == v.x && y == v.y && z == v.z;
}

D3DMXINLINE BOOL
D3DMXVECTOR3FXD::operator == ( CONST D3DMXVECTOR3FXD& v ) const
{
    return x == v.x && y == v.y && z == v.z;
}

D3DMXINLINE BOOL
D3DMXVECTOR3::operator != ( CONST D3DMXVECTOR3& v ) const
{
    return x != v.x || y != v.y || z != v.z;
}

D3DMXINLINE BOOL
D3DMXVECTOR3FXD::operator != ( CONST D3DMXVECTOR3FXD& v ) const
{
    return x != v.x || y != v.y || z != v.z;
}


//--------------------------
// 4D Vector
//--------------------------
D3DMXINLINE
D3DMXVECTOR4::D3DMXVECTOR4( CONST FLOAT *pf )
{
#ifdef D3DMX_DEBUG
    if(!pf)
        return;
#endif

    x = pf[0];
    y = pf[1];
    z = pf[2];
    w = pf[3];
}

D3DMXINLINE
D3DMXVECTOR4FXD::D3DMXVECTOR4FXD( CONST FIXED *pf )
{
#ifdef D3DMX_DEBUG
    if(!pf)
        return;
#endif

    x = pf[0];
    y = pf[1];
    z = pf[2];
    w = pf[3];
}

D3DMXINLINE
D3DMXVECTOR4::D3DMXVECTOR4( FLOAT fx, FLOAT fy, FLOAT fz, FLOAT fw )
{
    x = fx;
    y = fy;
    z = fz;
    w = fw;
}

D3DMXINLINE
D3DMXVECTOR4FXD::D3DMXVECTOR4FXD( FIXED fx, FIXED fy, FIXED fz, FIXED fw )
{
    x = fx;
    y = fy;
    z = fz;
    w = fw;
}

D3DMXINLINE
D3DMXVECTOR4FXD::D3DMXVECTOR4FXD( FLOAT fx, FLOAT fy, FLOAT fz, FLOAT fw )
{
    x = D3DMXToFixed(fx);
    y = D3DMXToFixed(fy);
    z = D3DMXToFixed(fz);
    w = D3DMXToFixed(fw);
}

// casting
D3DMXINLINE
D3DMXVECTOR4::operator FLOAT* ()
{
    return (FLOAT *) &x;
}

D3DMXINLINE
D3DMXVECTOR4FXD::operator FIXED* ()
{
    return (FIXED *) &x;
}

D3DMXINLINE
D3DMXVECTOR4::operator CONST FLOAT* () const
{
    return (CONST FLOAT *) &x;
}

D3DMXINLINE
D3DMXVECTOR4FXD::operator CONST FIXED* () const
{
    return (CONST FIXED *) &x;
}

// assignment operators
D3DMXINLINE D3DMXVECTOR4&
D3DMXVECTOR4::operator += ( CONST D3DMXVECTOR4& v )
{
    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;
    return *this;
}

D3DMXINLINE D3DMXVECTOR4FXD&
D3DMXVECTOR4FXD::operator += ( CONST D3DMXVECTOR4FXD& v )
{
    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;
    return *this;
}

D3DMXINLINE D3DMXVECTOR4&
D3DMXVECTOR4::operator -= ( CONST D3DMXVECTOR4& v )
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    w -= v.w;
    return *this;
}

D3DMXINLINE D3DMXVECTOR4FXD&
D3DMXVECTOR4FXD::operator -= ( CONST D3DMXVECTOR4FXD& v )
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    w -= v.w;
    return *this;
}

D3DMXINLINE D3DMXVECTOR4&
D3DMXVECTOR4::operator *= ( FLOAT f )
{
    x *= f;
    y *= f;
    z *= f;
    w *= f;
    return *this;
}

D3DMXINLINE D3DMXVECTOR4FXD&
D3DMXVECTOR4FXD::operator *= ( FIXED f )
{
    x = D3DMXMulFxd(x, f);
    y = D3DMXMulFxd(y, f);
    z = D3DMXMulFxd(z, f);
    w = D3DMXMulFxd(w, f);
    return *this;
}

D3DMXINLINE D3DMXVECTOR4&
D3DMXVECTOR4::operator /= ( FLOAT f )
{
    FLOAT fInv = 1.0f / f;
    x *= fInv;
    y *= fInv;
    z *= fInv;
    w *= fInv;
    return *this;
}

D3DMXINLINE D3DMXVECTOR4FXD&
D3DMXVECTOR4FXD::operator /= ( FIXED f )
{
    FIXED fInv = D3DMXDivFxd(D3DMXToFixed(1.0f), f);
    x = D3DMXMulFxd(x, fInv);
    y = D3DMXMulFxd(y, fInv);
    z = D3DMXMulFxd(z, fInv);
    w = D3DMXMulFxd(w, fInv);
    return *this;
}


// unary operators
D3DMXINLINE D3DMXVECTOR4
D3DMXVECTOR4::operator + () const
{
    return *this;
}

D3DMXINLINE D3DMXVECTOR4FXD
D3DMXVECTOR4FXD::operator + () const
{
    return *this;
}

D3DMXINLINE D3DMXVECTOR4
D3DMXVECTOR4::operator - () const
{
    return D3DMXVECTOR4(-x, -y, -z, -w);
}

D3DMXINLINE D3DMXVECTOR4FXD
D3DMXVECTOR4FXD::operator - () const
{
    return D3DMXVECTOR4FXD(-x, -y, -z, -w);
}


// binary operators
D3DMXINLINE D3DMXVECTOR4
D3DMXVECTOR4::operator + ( CONST D3DMXVECTOR4& v ) const
{
    return D3DMXVECTOR4(x + v.x, y + v.y, z + v.z, w + v.w);
}

D3DMXINLINE D3DMXVECTOR4FXD
D3DMXVECTOR4FXD::operator + ( CONST D3DMXVECTOR4FXD& v ) const
{
    return D3DMXVECTOR4FXD(x + v.x, y + v.y, z + v.z, w + v.w);
}

D3DMXINLINE D3DMXVECTOR4
D3DMXVECTOR4::operator - ( CONST D3DMXVECTOR4& v ) const
{
    return D3DMXVECTOR4(x - v.x, y - v.y, z - v.z, w - v.w);
}

D3DMXINLINE D3DMXVECTOR4FXD
D3DMXVECTOR4FXD::operator - ( CONST D3DMXVECTOR4FXD& v ) const
{
    return D3DMXVECTOR4FXD(x - v.x, y - v.y, z - v.z, w - v.w);
}

D3DMXINLINE D3DMXVECTOR4
D3DMXVECTOR4::operator * ( FLOAT f ) const
{
    return D3DMXVECTOR4(x * f, y * f, z * f, w * f);
}

D3DMXINLINE D3DMXVECTOR4FXD
D3DMXVECTOR4FXD::operator * ( FIXED f ) const
{
    return D3DMXVECTOR4FXD(D3DMXMulFxd(x, f), D3DMXMulFxd(y, f), D3DMXMulFxd(z, f), D3DMXMulFxd(w, f));
}

D3DMXINLINE D3DMXVECTOR4
D3DMXVECTOR4::operator / ( FLOAT f ) const
{
    FLOAT fInv = 1.0f / f;
    return D3DMXVECTOR4(x * fInv, y * fInv, z * fInv, w * fInv);
}

D3DMXINLINE D3DMXVECTOR4FXD
D3DMXVECTOR4FXD::operator / ( FIXED f ) const
{
    FIXED fInv = D3DMXDivFxd(D3DMXToFixed(1.0f), f);
    return D3DMXVECTOR4FXD(D3DMXMulFxd(x, fInv), D3DMXMulFxd(y, fInv), D3DMXMulFxd(z, fInv), D3DMXMulFxd(w, fInv));
}

D3DMXINLINE D3DMXVECTOR4
operator * ( FLOAT f, CONST D3DMXVECTOR4& v )
{
    return D3DMXVECTOR4(f * v.x, f * v.y, f * v.z, f * v.w);
}

D3DMXINLINE D3DMXVECTOR4FXD
operator * ( FIXED f, CONST D3DMXVECTOR4FXD& v )
{
    return D3DMXVECTOR4FXD(D3DMXMulFxd(f, v.x), D3DMXMulFxd(f, v.y), D3DMXMulFxd(f, v.z), D3DMXMulFxd(f, v.w));
}

D3DMXINLINE BOOL
D3DMXVECTOR4::operator == ( CONST D3DMXVECTOR4& v ) const
{
    return x == v.x && y == v.y && z == v.z && w == v.w;
}

D3DMXINLINE BOOL
D3DMXVECTOR4FXD::operator == ( CONST D3DMXVECTOR4FXD& v ) const
{
    return x == v.x && y == v.y && z == v.z && w == v.w;
}

D3DMXINLINE BOOL
D3DMXVECTOR4::operator != ( CONST D3DMXVECTOR4& v ) const
{
    return x != v.x || y != v.y || z != v.z || w != v.w;
}

D3DMXINLINE BOOL
D3DMXVECTOR4FXD::operator != ( CONST D3DMXVECTOR4FXD& v ) const
{
    return x != v.x || y != v.y || z != v.z || w != v.w;
}


//--------------------------
// Matrix
//--------------------------
D3DMXINLINE
D3DMXMATRIX::D3DMXMATRIX( CONST FLOAT* pf )
{
#ifdef D3DMX_DEBUG
    if(!pf)
        return;
#endif

    memcpy(&_11, pf, sizeof(D3DMMATRIX));
}

D3DMXINLINE
D3DMXMATRIXFXD::D3DMXMATRIXFXD( CONST FIXED* pf )
{
#ifdef D3DMX_DEBUG
    if(!pf)
        return;
#endif

    memcpy(&_11, pf, sizeof(D3DMMATRIX));
}

D3DMXINLINE
D3DMXMATRIX::D3DMXMATRIX( CONST D3DMMATRIX& mat )
{
    memcpy(&_11, &mat, sizeof(D3DMMATRIX));
}

D3DMXINLINE
D3DMXMATRIXFXD::D3DMXMATRIXFXD( CONST D3DMMATRIX& mat )
{
    memcpy(&_11, &mat, sizeof(D3DMMATRIX));
}

D3DMXINLINE
D3DMXMATRIX::D3DMXMATRIX( FLOAT f11, FLOAT f12, FLOAT f13, FLOAT f14,
                        FLOAT f21, FLOAT f22, FLOAT f23, FLOAT f24,
                        FLOAT f31, FLOAT f32, FLOAT f33, FLOAT f34,
                        FLOAT f41, FLOAT f42, FLOAT f43, FLOAT f44 )
{
    _11 = f11; _12 = f12; _13 = f13; _14 = f14;
    _21 = f21; _22 = f22; _23 = f23; _24 = f24;
    _31 = f31; _32 = f32; _33 = f33; _34 = f34;
    _41 = f41; _42 = f42; _43 = f43; _44 = f44;
}

D3DMXINLINE
D3DMXMATRIXFXD::D3DMXMATRIXFXD( FIXED f11, FIXED f12, FIXED f13, FIXED f14,
                        FIXED f21, FIXED f22, FIXED f23, FIXED f24,
                        FIXED f31, FIXED f32, FIXED f33, FIXED f34,
                        FIXED f41, FIXED f42, FIXED f43, FIXED f44 )
{
    _11 = f11; _12 = f12; _13 = f13; _14 = f14;
    _21 = f21; _22 = f22; _23 = f23; _24 = f24;
    _31 = f31; _32 = f32; _33 = f33; _34 = f34;
    _41 = f41; _42 = f42; _43 = f43; _44 = f44;
}



// access grants
D3DMXINLINE FLOAT&
D3DMXMATRIX::operator () ( UINT iRow, UINT iCol )
{
    return m[iRow][iCol];
}

D3DMXINLINE FIXED&
D3DMXMATRIXFXD::operator () ( UINT iRow, UINT iCol )
{
    return m[iRow][iCol];
}

D3DMXINLINE FLOAT
D3DMXMATRIX::operator () ( UINT iRow, UINT iCol ) const
{
    return m[iRow][iCol];
}

D3DMXINLINE FIXED
D3DMXMATRIXFXD::operator () ( UINT iRow, UINT iCol ) const
{
    return m[iRow][iCol];
}

// casting operators
D3DMXINLINE
D3DMXMATRIX::operator FLOAT* ()
{
    return (FLOAT *) &_11;
}

D3DMXINLINE
D3DMXMATRIXFXD::operator FIXED* ()
{
    return (FIXED *) &_11;
}

D3DMXINLINE
D3DMXMATRIX::operator CONST FLOAT* () const
{
    return (CONST FLOAT *) &_11;
}

D3DMXINLINE
D3DMXMATRIXFXD::operator CONST FIXED* () const
{
    return (CONST FIXED *) &_11;
}


// assignment operators
D3DMXINLINE D3DMXMATRIX&
D3DMXMATRIX::operator *= ( CONST D3DMXMATRIX& mat )
{
    D3DMXMatrixMultiply(this, this, &mat);
    return *this;
}

D3DMXINLINE D3DMXMATRIXFXD&
D3DMXMATRIXFXD::operator *= ( CONST D3DMXMATRIXFXD& mat )
{
    D3DMXMatrixMultiplyFxd(this, this, &mat);
    return *this;
}

D3DMXINLINE D3DMXMATRIX&
D3DMXMATRIX::operator += ( CONST D3DMXMATRIX& mat )
{
    _11 += mat._11; _12 += mat._12; _13 += mat._13; _14 += mat._14;
    _21 += mat._21; _22 += mat._22; _23 += mat._23; _24 += mat._24;
    _31 += mat._31; _32 += mat._32; _33 += mat._33; _34 += mat._34;
    _41 += mat._41; _42 += mat._42; _43 += mat._43; _44 += mat._44;
    return *this;
}

D3DMXINLINE D3DMXMATRIXFXD&
D3DMXMATRIXFXD::operator += ( CONST D3DMXMATRIXFXD& mat )
{
    _11 += mat._11; _12 += mat._12; _13 += mat._13; _14 += mat._14;
    _21 += mat._21; _22 += mat._22; _23 += mat._23; _24 += mat._24;
    _31 += mat._31; _32 += mat._32; _33 += mat._33; _34 += mat._34;
    _41 += mat._41; _42 += mat._42; _43 += mat._43; _44 += mat._44;
    return *this;
}

D3DMXINLINE D3DMXMATRIX&
D3DMXMATRIX::operator -= ( CONST D3DMXMATRIX& mat )
{
    _11 -= mat._11; _12 -= mat._12; _13 -= mat._13; _14 -= mat._14;
    _21 -= mat._21; _22 -= mat._22; _23 -= mat._23; _24 -= mat._24;
    _31 -= mat._31; _32 -= mat._32; _33 -= mat._33; _34 -= mat._34;
    _41 -= mat._41; _42 -= mat._42; _43 -= mat._43; _44 -= mat._44;
    return *this;
}

D3DMXINLINE D3DMXMATRIXFXD&
D3DMXMATRIXFXD::operator -= ( CONST D3DMXMATRIXFXD& mat )
{
    _11 -= mat._11; _12 -= mat._12; _13 -= mat._13; _14 -= mat._14;
    _21 -= mat._21; _22 -= mat._22; _23 -= mat._23; _24 -= mat._24;
    _31 -= mat._31; _32 -= mat._32; _33 -= mat._33; _34 -= mat._34;
    _41 -= mat._41; _42 -= mat._42; _43 -= mat._43; _44 -= mat._44;
    return *this;
}

D3DMXINLINE D3DMXMATRIX&
D3DMXMATRIX::operator *= ( FLOAT f )
{
    _11 *= f; _12 *= f; _13 *= f; _14 *= f;
    _21 *= f; _22 *= f; _23 *= f; _24 *= f;
    _31 *= f; _32 *= f; _33 *= f; _34 *= f;
    _41 *= f; _42 *= f; _43 *= f; _44 *= f;
    return *this;
}

D3DMXINLINE D3DMXMATRIXFXD&
D3DMXMATRIXFXD::operator *= ( FIXED f )
{
    _11 = D3DMXMulFxd(_11, f); _12 = D3DMXMulFxd(_12, f); _13 = D3DMXMulFxd(_13, f); _14 = D3DMXMulFxd(_14, f);
    _21 = D3DMXMulFxd(_21, f); _22 = D3DMXMulFxd(_22, f); _23 = D3DMXMulFxd(_23, f); _24 = D3DMXMulFxd(_24, f);
    _31 = D3DMXMulFxd(_31, f); _32 = D3DMXMulFxd(_32, f); _33 = D3DMXMulFxd(_33, f); _34 = D3DMXMulFxd(_34, f);
    _41 = D3DMXMulFxd(_41, f); _42 = D3DMXMulFxd(_42, f); _43 = D3DMXMulFxd(_43, f); _44 = D3DMXMulFxd(_44, f);
    return *this;
}

D3DMXINLINE D3DMXMATRIX&
D3DMXMATRIX::operator /= ( FLOAT f )
{
    FLOAT fInv = 1.0f / f;
    _11 *= fInv; _12 *= fInv; _13 *= fInv; _14 *= fInv;
    _21 *= fInv; _22 *= fInv; _23 *= fInv; _24 *= fInv;
    _31 *= fInv; _32 *= fInv; _33 *= fInv; _34 *= fInv;
    _41 *= fInv; _42 *= fInv; _43 *= fInv; _44 *= fInv;
    return *this;
}

D3DMXINLINE D3DMXMATRIXFXD&
D3DMXMATRIXFXD::operator /= ( FIXED f )
{
    FIXED fInv = D3DMXDivFxd(D3DMXToFixed(1.0f), f);
    _11 = D3DMXMulFxd(_11, fInv); _12 = D3DMXMulFxd(_12, fInv); _13 = D3DMXMulFxd(_13, fInv); _14 = D3DMXMulFxd(_14, fInv);
    _21 = D3DMXMulFxd(_21, fInv); _22 = D3DMXMulFxd(_22, fInv); _23 = D3DMXMulFxd(_23, fInv); _24 = D3DMXMulFxd(_24, fInv);
    _31 = D3DMXMulFxd(_31, fInv); _32 = D3DMXMulFxd(_32, fInv); _33 = D3DMXMulFxd(_33, fInv); _34 = D3DMXMulFxd(_34, fInv);
    _41 = D3DMXMulFxd(_41, fInv); _42 = D3DMXMulFxd(_42, fInv); _43 = D3DMXMulFxd(_43, fInv); _44 = D3DMXMulFxd(_44, fInv);
    return *this;
}


// unary operators
D3DMXINLINE D3DMXMATRIX
D3DMXMATRIX::operator + () const
{
    return *this;
}

D3DMXINLINE D3DMXMATRIXFXD
D3DMXMATRIXFXD::operator + () const
{
    return *this;
}

D3DMXINLINE D3DMXMATRIX
D3DMXMATRIX::operator - () const
{
    return D3DMXMATRIX(-_11, -_12, -_13, -_14,
                      -_21, -_22, -_23, -_24,
                      -_31, -_32, -_33, -_34,
                      -_41, -_42, -_43, -_44);
}

D3DMXINLINE D3DMXMATRIXFXD
D3DMXMATRIXFXD::operator - () const
{
    return D3DMXMATRIXFXD(-_11, -_12, -_13, -_14,
                      -_21, -_22, -_23, -_24,
                      -_31, -_32, -_33, -_34,
                      -_41, -_42, -_43, -_44);
}


// binary operators
D3DMXINLINE D3DMXMATRIX
D3DMXMATRIX::operator * ( CONST D3DMXMATRIX& mat ) const
{
    D3DMXMATRIX matT;
    D3DMXMatrixMultiply(&matT, this, &mat);
    return matT;
}

D3DMXINLINE D3DMXMATRIXFXD
D3DMXMATRIXFXD::operator * ( CONST D3DMXMATRIXFXD& mat ) const
{
    D3DMXMATRIXFXD matT;
    D3DMXMatrixMultiplyFxd(&matT, this, &mat);
    return matT;
}

D3DMXINLINE D3DMXMATRIX
D3DMXMATRIX::operator + ( CONST D3DMXMATRIX& mat ) const
{
    return D3DMXMATRIX(_11 + mat._11, _12 + mat._12, _13 + mat._13, _14 + mat._14,
                      _21 + mat._21, _22 + mat._22, _23 + mat._23, _24 + mat._24,
                      _31 + mat._31, _32 + mat._32, _33 + mat._33, _34 + mat._34,
                      _41 + mat._41, _42 + mat._42, _43 + mat._43, _44 + mat._44);
}

D3DMXINLINE D3DMXMATRIXFXD
D3DMXMATRIXFXD::operator + ( CONST D3DMXMATRIXFXD& mat ) const
{
    return D3DMXMATRIXFXD(_11 + mat._11, _12 + mat._12, _13 + mat._13, _14 + mat._14,
                      _21 + mat._21, _22 + mat._22, _23 + mat._23, _24 + mat._24,
                      _31 + mat._31, _32 + mat._32, _33 + mat._33, _34 + mat._34,
                      _41 + mat._41, _42 + mat._42, _43 + mat._43, _44 + mat._44);
}

D3DMXINLINE D3DMXMATRIX
D3DMXMATRIX::operator - ( CONST D3DMXMATRIX& mat ) const
{
    return D3DMXMATRIX(_11 - mat._11, _12 - mat._12, _13 - mat._13, _14 - mat._14,
                      _21 - mat._21, _22 - mat._22, _23 - mat._23, _24 - mat._24,
                      _31 - mat._31, _32 - mat._32, _33 - mat._33, _34 - mat._34,
                      _41 - mat._41, _42 - mat._42, _43 - mat._43, _44 - mat._44);
}

D3DMXINLINE D3DMXMATRIXFXD
D3DMXMATRIXFXD::operator - ( CONST D3DMXMATRIXFXD& mat ) const
{
    return D3DMXMATRIXFXD(_11 - mat._11, _12 - mat._12, _13 - mat._13, _14 - mat._14,
                      _21 - mat._21, _22 - mat._22, _23 - mat._23, _24 - mat._24,
                      _31 - mat._31, _32 - mat._32, _33 - mat._33, _34 - mat._34,
                      _41 - mat._41, _42 - mat._42, _43 - mat._43, _44 - mat._44);
}

D3DMXINLINE D3DMXMATRIX
D3DMXMATRIX::operator * ( FLOAT f ) const
{
    return D3DMXMATRIX(_11 * f, _12 * f, _13 * f, _14 * f,
                      _21 * f, _22 * f, _23 * f, _24 * f,
                      _31 * f, _32 * f, _33 * f, _34 * f,
                      _41 * f, _42 * f, _43 * f, _44 * f);
}

D3DMXINLINE D3DMXMATRIXFXD
D3DMXMATRIXFXD::operator * ( FIXED f ) const
{
    return D3DMXMATRIXFXD(D3DMXMulFxd(_11, f), D3DMXMulFxd(_12, f), D3DMXMulFxd(_13, f), D3DMXMulFxd(_14, f),
                        D3DMXMulFxd(_21, f), D3DMXMulFxd(_22, f), D3DMXMulFxd(_23, f), D3DMXMulFxd(_24, f),
                        D3DMXMulFxd(_31, f), D3DMXMulFxd(_32, f), D3DMXMulFxd(_33, f), D3DMXMulFxd(_34, f),
                        D3DMXMulFxd(_41, f), D3DMXMulFxd(_42, f), D3DMXMulFxd(_43, f), D3DMXMulFxd(_44, f));
}

D3DMXINLINE D3DMXMATRIX
D3DMXMATRIX::operator / ( FLOAT f ) const
{
    FLOAT fInv = 1.0f / f;
    return D3DMXMATRIX(_11 * fInv, _12 * fInv, _13 * fInv, _14 * fInv,
                      _21 * fInv, _22 * fInv, _23 * fInv, _24 * fInv,
                      _31 * fInv, _32 * fInv, _33 * fInv, _34 * fInv,
                      _41 * fInv, _42 * fInv, _43 * fInv, _44 * fInv);
}

D3DMXINLINE D3DMXMATRIXFXD
D3DMXMATRIXFXD::operator / ( FIXED f ) const
{
    FIXED fInv = D3DMXDivFxd(D3DMXToFixed(1.0f), f);
    return D3DMXMATRIXFXD(D3DMXMulFxd(_11, fInv), D3DMXMulFxd(_12, fInv), D3DMXMulFxd(_13, fInv), D3DMXMulFxd(_14, fInv),
                        D3DMXMulFxd(_21, fInv), D3DMXMulFxd(_22, fInv), D3DMXMulFxd(_23, fInv), D3DMXMulFxd(_24, fInv),
                        D3DMXMulFxd(_31, fInv), D3DMXMulFxd(_32, fInv), D3DMXMulFxd(_33, fInv), D3DMXMulFxd(_34, fInv),
                        D3DMXMulFxd(_41, fInv), D3DMXMulFxd(_42, fInv), D3DMXMulFxd(_43, fInv), D3DMXMulFxd(_44, fInv));
}


D3DMXINLINE D3DMXMATRIX
operator * ( FLOAT f, CONST D3DMXMATRIX& mat )
{
    return D3DMXMATRIX(f * mat._11, f * mat._12, f * mat._13, f * mat._14,
                      f * mat._21, f * mat._22, f * mat._23, f * mat._24,
                      f * mat._31, f * mat._32, f * mat._33, f * mat._34,
                      f * mat._41, f * mat._42, f * mat._43, f * mat._44);
}

D3DMXINLINE D3DMXMATRIXFXD
operator * ( FIXED f, CONST D3DMXMATRIXFXD& mat )
{
    return D3DMXMATRIXFXD(D3DMXMulFxd(f, mat._11), D3DMXMulFxd(f, mat._12), D3DMXMulFxd(f, mat._13), D3DMXMulFxd(f, mat._14),
                                    D3DMXMulFxd(f, mat._21), D3DMXMulFxd(f, mat._22), D3DMXMulFxd(f, mat._23), D3DMXMulFxd(f, mat._24),
                                    D3DMXMulFxd(f, mat._31), D3DMXMulFxd(f, mat._32), D3DMXMulFxd(f, mat._33), D3DMXMulFxd(f, mat._34),
                                    D3DMXMulFxd(f, mat._41), D3DMXMulFxd(f, mat._42), D3DMXMulFxd(f, mat._43), D3DMXMulFxd(f, mat._44));
}


D3DMXINLINE BOOL
D3DMXMATRIX::operator == ( CONST D3DMXMATRIX& mat ) const
{
    return 0 == memcmp(this, &mat, sizeof(D3DMXMATRIX));
}

D3DMXINLINE BOOL
D3DMXMATRIXFXD::operator == ( CONST D3DMXMATRIXFXD& mat ) const
{
    return 0 == memcmp(this, &mat, sizeof(D3DMXMATRIXFXD));
}

D3DMXINLINE BOOL
D3DMXMATRIX::operator != ( CONST D3DMXMATRIX& mat ) const
{
    return 0 != memcmp(this, &mat, sizeof(D3DMXMATRIX));
}

D3DMXINLINE BOOL
D3DMXMATRIXFXD::operator != ( CONST D3DMXMATRIXFXD& mat ) const
{
    return 0 != memcmp(this, &mat, sizeof(D3DMXMATRIXFXD));
}

#endif // __cplusplus

//===========================================================================
//
// Inline functions
//
//===========================================================================


//--------------------------
// 3D Vector
//--------------------------

D3DMXINLINE FLOAT D3DMXVec3Length
    ( CONST D3DMXVECTOR3 *pV )
{
#ifdef D3DMX_DEBUG
    if(!pV)
        return 0.0f;
#endif

#ifdef __cplusplus
    return sqrtf(pV->x * pV->x + pV->y * pV->y + pV->z * pV->z);
#else
    return (FLOAT) sqrt(pV->x * pV->x + pV->y * pV->y + pV->z * pV->z);
#endif
}

D3DMXINLINE FIXED D3DMXVec3LengthFxd
    ( CONST D3DMXVECTOR3FXD *pV )
{
#ifdef D3DMX_DEBUG
    if(!pV)
        return D3DMXToFixed(0.0f);
#endif

#ifdef __cplusplus
    return D3DMXToFixed(sqrtf(D3DMXToFloat(D3DMXMulFxd(pV->x, pV->x) + D3DMXMulFxd(pV->y, pV->y) + D3DMXMulFxd(pV->z, pV->z))));
#else
    return D3DMXToFixed((float)sqrt((double)D3DMXToFloat(D3DMXMulFxd(pV->x, pV->x) + D3DMXMulFxd(pV->y, pV->y) + D3DMXMulFxd(pV->z, pV->z)));
#endif
}

D3DMXINLINE FLOAT D3DMXVec3LengthSq
    ( CONST D3DMXVECTOR3 *pV )
{
#ifdef D3DMX_DEBUG
    if(!pV)
        return 0.0f;
#endif

    return pV->x * pV->x + pV->y * pV->y + pV->z * pV->z;
}

D3DMXINLINE FIXED D3DMXVec3LengthSqFxd
    ( CONST D3DMXVECTOR3FXD *pV )
{
#ifdef D3DMX_DEBUG
    if(!pV)
        return D3DMXToFixed(0.0f);
#endif

    return D3DMXMulFxd(pV->x, pV->x) + D3DMXMulFxd(pV->y, pV->y) + D3DMXMulFxd(pV->z, pV->z);
}

D3DMXINLINE FLOAT D3DMXVec3Dot
    ( CONST D3DMXVECTOR3 *pV1, CONST D3DMXVECTOR3 *pV2 )
{
#ifdef D3DMX_DEBUG
    if(!pV1 || !pV2)
        return 0.0f;
#endif

    return pV1->x * pV2->x + pV1->y * pV2->y + pV1->z * pV2->z;
}

D3DMXINLINE FIXED D3DMXVec3DotFxd
    ( CONST D3DMXVECTOR3FXD *pV1, CONST D3DMXVECTOR3FXD *pV2 )
{
#ifdef D3DMX_DEBUG
    if(!pV1 || !pV2)
        return D3DMXToFixed(0.0f);
#endif

    return D3DMXMulFxd(pV1->x, pV2->x) + D3DMXMulFxd(pV1->y, pV2->y) + D3DMXMulFxd(pV1->z, pV2->z);
}

D3DMXINLINE D3DMXVECTOR3* D3DMXVec3Cross
    ( D3DMXVECTOR3 *pOut, CONST D3DMXVECTOR3 *pV1, CONST D3DMXVECTOR3 *pV2 )
{
    D3DMXVECTOR3 v;

#ifdef D3DMX_DEBUG
    if(!pOut || !pV1 || !pV2)
        return NULL;
#endif

    v.x = pV1->y * pV2->z - pV1->z * pV2->y;
    v.y = pV1->z * pV2->x - pV1->x * pV2->z;
    v.z = pV1->x * pV2->y - pV1->y * pV2->x;

    *pOut = v;
    return pOut;
}

D3DMXINLINE D3DMXVECTOR3FXD* D3DMXVec3CrossFxd
    ( D3DMXVECTOR3FXD *pOut, CONST D3DMXVECTOR3FXD *pV1, CONST D3DMXVECTOR3FXD *pV2 )
{
    D3DMXVECTOR3FXD v;

#ifdef D3DMX_DEBUG
    if(!pOut || !pV1 || !pV2)
        return NULL;
#endif

    v.x = D3DMXMulFxd(pV1->y, pV2->z) - D3DMXMulFxd(pV1->z, pV2->y);
    v.y = D3DMXMulFxd(pV1->z, pV2->x) - D3DMXMulFxd(pV1->x, pV2->z);
    v.z = D3DMXMulFxd(pV1->x, pV2->y) - D3DMXMulFxd(pV1->y, pV2->x);

    *pOut = v;
    return pOut;
}

D3DMXINLINE D3DMXVECTOR3* D3DMXVec3Add
    ( D3DMXVECTOR3 *pOut, CONST D3DMXVECTOR3 *pV1, CONST D3DMXVECTOR3 *pV2 )
{
#ifdef D3DMX_DEBUG
    if(!pOut || !pV1 || !pV2)
        return NULL;
#endif

    pOut->x = pV1->x + pV2->x;
    pOut->y = pV1->y + pV2->y;
    pOut->z = pV1->z + pV2->z;
    return pOut;
}

D3DMXINLINE D3DMXVECTOR3FXD* D3DMXVec3AddFxd
    ( D3DMXVECTOR3FXD *pOut, CONST D3DMXVECTOR3FXD *pV1, CONST D3DMXVECTOR3FXD *pV2 )
{
#ifdef D3DMX_DEBUG
    if(!pOut || !pV1 || !pV2)
        return NULL;
#endif

    pOut->x = pV1->x + pV2->x;
    pOut->y = pV1->y + pV2->y;
    pOut->z = pV1->z + pV2->z;
    return pOut;
}

D3DMXINLINE D3DMXVECTOR3* D3DMXVec3Subtract
    ( D3DMXVECTOR3 *pOut, CONST D3DMXVECTOR3 *pV1, CONST D3DMXVECTOR3 *pV2 )
{
#ifdef D3DMX_DEBUG
    if(!pOut || !pV1 || !pV2)
        return NULL;
#endif

    pOut->x = pV1->x - pV2->x;
    pOut->y = pV1->y - pV2->y;
    pOut->z = pV1->z - pV2->z;
    return pOut;
}

D3DMXINLINE D3DMXVECTOR3FXD* D3DMXVec3SubtractFxd
    ( D3DMXVECTOR3FXD *pOut, CONST D3DMXVECTOR3FXD *pV1, CONST D3DMXVECTOR3FXD *pV2 )
{
#ifdef D3DMX_DEBUG
    if(!pOut || !pV1 || !pV2)
        return NULL;
#endif

    pOut->x = pV1->x - pV2->x;
    pOut->y = pV1->y - pV2->y;
    pOut->z = pV1->z - pV2->z;
    return pOut;
}

D3DMXINLINE D3DMXVECTOR3* D3DMXVec3Scale
    ( D3DMXVECTOR3 *pOut, CONST D3DMXVECTOR3 *pV, FLOAT s)
{
#ifdef D3DMX_DEBUG
    if(!pOut || !pV)
        return NULL;
#endif

    pOut->x = pV->x * s;
    pOut->y = pV->y * s;
    pOut->z = pV->z * s;
    return pOut;
}

D3DMXINLINE D3DMXVECTOR3FXD* D3DMXVec3ScaleFxd
    ( D3DMXVECTOR3FXD *pOut, CONST D3DMXVECTOR3FXD *pV, FIXED s)
{
#ifdef D3DMX_DEBUG
    if(!pOut || !pV)
        return NULL;
#endif

    pOut->x = D3DMXMulFxd(pV->x, s);
    pOut->y = D3DMXMulFxd(pV->y, s);
    pOut->z = D3DMXMulFxd(pV->z, s);
    return pOut;
}

//--------------------------
// 4D Vector
//--------------------------

D3DMXINLINE FLOAT D3DMXVec4Length
    ( CONST D3DMXVECTOR4 *pV )
{
#ifdef D3DMX_DEBUG
    if(!pV)
        return 0.0f;
#endif

#ifdef __cplusplus
    return sqrtf(pV->x * pV->x + pV->y * pV->y + pV->z * pV->z + pV->w * pV->w);
#else
    return (FLOAT) sqrt(pV->x * pV->x + pV->y * pV->y + pV->z * pV->z + pV->w * pV->w);
#endif
}

D3DMXINLINE FIXED D3DMXVec4LengthFxd
    ( CONST D3DMXVECTOR4FXD *pV )
{
#ifdef D3DMX_DEBUG
    if(!pV)
        return D3DMXToFixed(0.0f);
#endif

#ifdef __cplusplus
    return D3DMXToFixed(sqrtf(D3DMXToFloat(D3DMXMulFxd(pV->x, pV->x) + D3DMXMulFxd(pV->y, pV->y) + D3DMXMulFxd(pV->z, pV->z) + D3DMXMulFxd(pV->w, pV->w))));
#else
    return D3DMXToFixed((float)sqrt((double)D3DMXToFloat(D3DMXMulFxd(pV->x, pV->x) + D3DMXMulFxd(pV->y, pV->y) + D3DMXMulFxd(pV->z, pV->z) + D3DMXMulFxd(pV->w, pV->w))));
#endif
}

D3DMXINLINE FLOAT D3DMXVec4LengthSq
    ( CONST D3DMXVECTOR4 *pV )
{
#ifdef D3DMX_DEBUG
    if(!pV)
        return 0.0f;
#endif

    return pV->x * pV->x + pV->y * pV->y + pV->z * pV->z + pV->w * pV->w;
}

D3DMXINLINE FIXED D3DMXVec4LengthSqFxd
    ( CONST D3DMXVECTOR4FXD *pV )
{
#ifdef D3DMX_DEBUG
    if(!pV)
        return D3DMXToFixed(0.0f);
#endif

    return D3DMXMulFxd(pV->x, pV->x) + D3DMXMulFxd(pV->y, pV->y) + D3DMXMulFxd(pV->z, pV->z) + D3DMXMulFxd(pV->w, pV->w);
}

D3DMXINLINE FLOAT D3DMXVec4Dot
    ( CONST D3DMXVECTOR4 *pV1, CONST D3DMXVECTOR4 *pV2 )
{
#ifdef D3DMX_DEBUG
    if(!pV1 || !pV2)
        return 0.0f;
#endif

    return pV1->x * pV2->x + pV1->y * pV2->y + pV1->z * pV2->z + pV1->w * pV2->w;
}

D3DMXINLINE FIXED D3DMXVec4DotFxd
    ( CONST D3DMXVECTOR4FXD *pV1, CONST D3DMXVECTOR4FXD *pV2 )
{
#ifdef D3DMX_DEBUG
    if(!pV1 || !pV2)
        return D3DMXToFixed(0.0f);
#endif

    return D3DMXMulFxd(pV1->x, pV2->x) + D3DMXMulFxd(pV1->y, pV2->y) + D3DMXMulFxd(pV1->z, pV2->z) + D3DMXMulFxd(pV1->w, pV2->w);
}

D3DMXINLINE D3DMXVECTOR4* D3DMXVec4Add
    ( D3DMXVECTOR4 *pOut, CONST D3DMXVECTOR4 *pV1, CONST D3DMXVECTOR4 *pV2)
{
#ifdef D3DMX_DEBUG
    if(!pOut || !pV1 || !pV2)
        return NULL;
#endif

    pOut->x = pV1->x + pV2->x;
    pOut->y = pV1->y + pV2->y;
    pOut->z = pV1->z + pV2->z;
    pOut->w = pV1->w + pV2->w;
    return pOut;
}

D3DMXINLINE D3DMXVECTOR4FXD* D3DMXVec4AddFxd
    ( D3DMXVECTOR4FXD *pOut, CONST D3DMXVECTOR4FXD *pV1, CONST D3DMXVECTOR4FXD *pV2)
{
#ifdef D3DMX_DEBUG
    if(!pOut || !pV1 || !pV2)
        return NULL;
#endif

    pOut->x = pV1->x + pV2->x;
    pOut->y = pV1->y + pV2->y;
    pOut->z = pV1->z + pV2->z;
    pOut->w = pV1->w + pV2->w;
    return pOut;
}

D3DMXINLINE D3DMXVECTOR4* D3DMXVec4Subtract
    ( D3DMXVECTOR4 *pOut, CONST D3DMXVECTOR4 *pV1, CONST D3DMXVECTOR4 *pV2)
{
#ifdef D3DMX_DEBUG
    if(!pOut || !pV1 || !pV2)
        return NULL;
#endif

    pOut->x = pV1->x - pV2->x;
    pOut->y = pV1->y - pV2->y;
    pOut->z = pV1->z - pV2->z;
    pOut->w = pV1->w - pV2->w;
    return pOut;
}

D3DMXINLINE D3DMXVECTOR4FXD* D3DMXVec4SubtractFxd
    ( D3DMXVECTOR4FXD *pOut, CONST D3DMXVECTOR4FXD *pV1, CONST D3DMXVECTOR4FXD *pV2)
{
#ifdef D3DMX_DEBUG
    if(!pOut || !pV1 || !pV2)
        return NULL;
#endif

    pOut->x = pV1->x - pV2->x;
    pOut->y = pV1->y - pV2->y;
    pOut->z = pV1->z - pV2->z;
    pOut->w = pV1->w - pV2->w;
    return pOut;
}

D3DMXINLINE D3DMXVECTOR4* D3DMXVec4Scale
    ( D3DMXVECTOR4 *pOut, CONST D3DMXVECTOR4 *pV, FLOAT s)
{
#ifdef D3DMX_DEBUG
    if(!pOut || !pV)
        return NULL;
#endif

    pOut->x = pV->x * s;
    pOut->y = pV->y * s;
    pOut->z = pV->z * s;
    pOut->w = pV->w * s;
    return pOut;
}

D3DMXINLINE D3DMXVECTOR4FXD* D3DMXVec4ScaleFxd
    ( D3DMXVECTOR4FXD *pOut, CONST D3DMXVECTOR4FXD *pV, FIXED s)
{
#ifdef D3DMX_DEBUG
    if(!pOut || !pV)
        return NULL;
#endif

    pOut->x = D3DMXMulFxd(pV->x, s);
    pOut->y = D3DMXMulFxd(pV->y, s);
    pOut->z = D3DMXMulFxd(pV->z, s);
    pOut->w = D3DMXMulFxd(pV->w, s);
    return pOut;
}

//--------------------------
// 4D Matrix
//--------------------------

D3DMXINLINE D3DMXMATRIX* D3DMXMatrixIdentity
    ( D3DMXMATRIX *pOut )
{
#ifdef D3DMX_DEBUG
    if(!pOut)
        return NULL;
#endif

    pOut->m[0][1] = pOut->m[0][2] = pOut->m[0][3] =
    pOut->m[1][0] = pOut->m[1][2] = pOut->m[1][3] =
    pOut->m[2][0] = pOut->m[2][1] = pOut->m[2][3] =
    pOut->m[3][0] = pOut->m[3][1] = pOut->m[3][2] = 0.0f;

    pOut->m[0][0] = pOut->m[1][1] = pOut->m[2][2] = pOut->m[3][3] = 1.0f;
    return pOut;
}

D3DMXINLINE D3DMXMATRIXFXD* D3DMXMatrixIdentityFxd
    ( D3DMXMATRIXFXD *pOut )
{
#ifdef D3DMX_DEBUG
    if(!pOut)
        return NULL;
#endif

    pOut->m[0][1] = pOut->m[0][2] = pOut->m[0][3] =
    pOut->m[1][0] = pOut->m[1][2] = pOut->m[1][3] =
    pOut->m[2][0] = pOut->m[2][1] = pOut->m[2][3] =
    pOut->m[3][0] = pOut->m[3][1] = pOut->m[3][2] = D3DMXToFixed(0.0f);

    pOut->m[0][0] = pOut->m[1][1] = pOut->m[2][2] = pOut->m[3][3] = D3DMXToFixed(1.0f);
    return pOut;
}

#endif // __D3DMXMATH_INL__
