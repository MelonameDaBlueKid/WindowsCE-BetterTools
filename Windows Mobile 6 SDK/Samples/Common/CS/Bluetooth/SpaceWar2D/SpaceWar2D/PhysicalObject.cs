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
    class PhysicalObject
    {
        /// <summary>
        /// How strong the sun's gravity is.
        /// </summary>
        private const int gravityMagnitude = 2;

        private Vector vPosition, vVelocity, vAcceleration;
        private int radius;

        public PhysicalObject()
        {
        }

        public PhysicalObject(Vector vPos, Vector vVel, int radius)
        {
            vPosition = vPos;
            vVelocity = vVel;
            this.radius = radius;
        }

        public int Radius
        {
            get { return radius; }
            set { radius = value;}
        }

        public Vector Position
        {
            get { return vPosition; }
            set { vPosition = value; }
        }

        public Vector Velocity
        {
            get { return vVelocity; }
            set { vVelocity = value; }
        }

        public Vector Acceleration
        {
            get { return vAcceleration; }
            set { vAcceleration = value; }
        }


        /// <summary>
        /// Update the position and velocity of the object
        /// </summary>
        /// <param name="ticks">The number of milliseconds since the last update.</param>
        public void Update(int ticks)
        {
            // Gravity points away from the position vector,
            // and it has a constant magnitude.
            Vector vGravity = -vPosition;
            vGravity.SetMagnitude(gravityMagnitude);

            // Update the velocity
            vVelocity += (vAcceleration + vGravity) * ticks;

            // Update the position
            vPosition += vVelocity * ticks;

            // Keep object within the bounds of the game.
            if (vPosition.X > Game.MaxPosition)
            {
                vPosition.X -= 2 * Game.MaxPosition;
            }
            else if (vPosition.X < -Game.MaxPosition)
            {
                vPosition.X += 2 * Game.MaxPosition;
            }
            if (vPosition.Y > Game.MaxPosition)
            {
                vPosition.Y -= 2 * Game.MaxPosition;
            }
            else if (vPosition.Y < -Game.MaxPosition)
            {
                vPosition.Y += 2 * Game.MaxPosition;
            }
        }
    }
}
