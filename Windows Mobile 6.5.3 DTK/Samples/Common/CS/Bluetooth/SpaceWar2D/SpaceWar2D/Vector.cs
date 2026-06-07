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
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.

using System;
using System.Collections.Generic;
using System.Text;

namespace SpaceWar2D
{
    /// <summary>
    /// A vector in two-dimensional space.
    /// </summary>
    public struct Vector
    {
        private int x;
        private int y;
        static Vector nullVector = new Vector();

        static public Vector Null
        {
            get { return nullVector; }
        }


        public int X
        {
            get { return x; }
            set { x = value; }
        }

        public int Y
        {
            get { return y; }
            set { y = value; }
        }


        public Vector(int x, int y)
        {
            this.x = x;
            this.y = y;
        }

        public static Vector operator+ (Vector v1, Vector v2)
        {
            return new Vector(v1.x + v2.x, v1.y + v2.y);
        }

        public static Vector operator- (Vector v1, Vector v2)
        {
            return new Vector(v1.x - v2.x, v1.y - v2.y);
        }

        public static Vector operator* (Vector v, int scalar)
        {
            return new Vector(v.x * scalar, v.y * scalar);
        }

        public static Vector operator* (Vector v, double scalar)
        {
            return new Vector((int)(v.x * scalar), (int)(v.y * scalar));
        }

        public static Vector operator- (Vector v)
        {
            return new Vector(-v.x, -v.y);
        }

        public void SetMagnitude(int newMagnitude)
        {
            double oldMagnitude = Math.Sqrt((long)x*(long)x + (long)y*(long)y);
            double scale = (double)newMagnitude / oldMagnitude;
            x = (int)(x * scale);
            y = (int)(y * scale);
        }

        public int Magnitude
        {
            get 
            { 
                return (int)Math.Sqrt((long)x * (long)x + (long)y * (long)y); 
            }
        }
    }
}
