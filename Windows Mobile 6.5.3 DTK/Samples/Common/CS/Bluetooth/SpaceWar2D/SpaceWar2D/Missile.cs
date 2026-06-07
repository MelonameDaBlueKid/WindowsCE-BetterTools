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
using System.Drawing;
using System.Text;

namespace SpaceWar2D
{
    class Missile : PhysicalObject
    {
        /// <summary>
        /// Is the missile launched?
        /// </summary>
        private bool launched;

        /// <summary>
        /// How long a missile stays launched.
        /// </summary>
        private const int launchLifetime = 3500;

        /// <summary>
        /// When the launched missile will expire.
        /// </summary>
        private int timeout;

        /// <summary>
        /// Is the missile launched?
        /// </summary>
        public bool Launched
        {
            get { return launched; }
            set { launched = value;}
        }

        /// <summary>
        /// What the sink thinks the state of the missile is.
        /// </summary>
        private bool sinkThinksItIsLaunched;

        public bool SinkThinksItIsLaunched
        {
            get { return sinkThinksItIsLaunched; }
            set { sinkThinksItIsLaunched = value; }
        }


        public Missile() :
            base(Vector.Null, Vector.Null, 
                 /*radius*/ Game.MaxPosition / 50)
        {
        }


       /// <summary>
       /// Launch the missile
       /// </summary>
       /// <param name="vPos">Initial position</param>
       /// <param name="vVel">Initial velocity</param>
        public void Launch(Vector vPos, Vector vVel) 
        {
            this.Position = vPos;
            this.Velocity = vVel;
            this.timeout = Environment.TickCount + launchLifetime;
            Launched = true;
        }

        /// <summary>
        /// Check for a collision between this missile and the specified object.
        /// </summary>
        /// <param name="obj">The object to check for a collision with.</param>
        /// <returns>True if there is a collision.</returns>
        public bool CheckForCollision(PhysicalObject obj)
        {
            // If the distance between the missile and object 
            // is less than the object's size, then it's a collision.
            int distance = (Position - obj.Position).Magnitude;
            if (distance < obj.Radius)
            {
                // The missile goes away when it collides with something.
                Launched = false;
                return true;
            }
            else
            {
                return false;
            }
        }


        /// <summary>
        /// Update the position of the missile and check for the 
        /// end of the lifetime of a launched missile.
        /// </summary>
        /// <param name="ticks"></param>
        public new void Update(int ticks)
        {
            System.Diagnostics.Debug.Assert(Launched);

            base.Update(ticks);

            if (Launched && Environment.TickCount > timeout)
            {
                // We've reached the end of the missile lifetime.
                Launched = false;
            }
        }


    }
}
